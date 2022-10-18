#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "StageManager.h"
#include "SceneManager.h"
#include "Util.h"

// --黒-- //
#define BLACK 0x000000

// --白-- //
#define WHITE 0xFFFFFF

// --向き-- //
#define LEFT -1
#define RIGHT 1

// --方向転換時のサイズ-- //
#define MAX_SIZE_P 32;
#define MIN_SIZE_P 27;

// --オブジェクトの描画用の関数-- //
void DrawBoxAA(Object obj, unsigned int color, bool fillFlag) {
	DrawBoxAA(
		obj.pos.x - obj.radius, obj.pos.y - obj.radius,
		obj.pos.x + obj.radius, obj.pos.y + obj.radius,
		color, fillFlag);

	DrawLineAA(obj.pos.x - obj.radius, obj.pos.y - obj.radius, obj.pos.x + obj.radius, obj.pos.y - obj.radius, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x - obj.radius, obj.pos.y + obj.radius, obj.pos.x + obj.radius, obj.pos.y + obj.radius, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x - obj.radius, obj.pos.y - obj.radius, obj.pos.x - obj.radius, obj.pos.y + obj.radius, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x + obj.radius, obj.pos.y - obj.radius, obj.pos.x + obj.radius, obj.pos.y + obj.radius, color ^ 0xFFFFFF, 3);
}

// --インスタンスにNULLを代入-- //
Player* Player::myInstance_ = nullptr;

// --インスタンス読み込み-- //
Player* Player::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance_ == nullptr) myInstance_ = new Player();

	// --インスタンスを返す-- //
	return myInstance_;
}

// --メモリ解放-- //
void Player::Release() {
	// --メモリ解放-- //
	delete myInstance_;

	// --NULLを代入-- //
	myInstance_ = nullptr;
}

// --コンストラクタ-- //
Player::Player() :
#pragma region 定数メンバの初期化

	// --横移動速度の基礎値-- //
	defaultSpeedX(5.0f),

	// --縦移動速度の基礎値-- //
	defaultSpeedY(10.0f),

	// --ブースト時の初期スピード-- //
	defaultBoostSpeedY(20.0f),

	// --ノックバック時の初期スピード-- //
	defaultKnockSpeedY(-10.0f)

#pragma endregion
{
	// --クラス定義-- //
	key_ = Key::GetInstance();
	stageManager_ = StageManager::GetInstance();

	// --プレイヤーオブジェクト-- //
	player_[0] = { {300.0f, 700.0f}, 32.0f };
	player_[1] = { {900.0f, 700.0f}, 32.0f };

	// --当たり判定が有効か
	isCollision = true;

	// --プレイヤーの状態-- //
	state = Normal;
	xAxisState = static_cast<int>(XAxisState::Default);
#ifdef _DEBUG
	debug_changeDirectionMode = static_cast<int>(DirectionMode::Old);
#endif

	// --横移動の速度-- //
	speedX = defaultSpeedX;

	// --移動する向き-- //
	direction = RIGHT;

	// --縦移動の速度-- //
	speedY = defaultSpeedY;

	// --ブーストの時間[s]-- //
	boostTime = 0.5f;

	// --ブーストの経過時間[s]-- //
	boostTimer = 0.0f;

	// --ブーストが始まった時の時間-- //
	boostStartTime = 0;
}

// --デストラクタ-- //
Player::~Player() {

}

// --初期化処理-- //
void Player::Initialize() {
	// --プレイヤーオブジェクト-- //
	player_[0] = { {300.0f, 700.0f}, 32.0f };
	player_[1] = { {900.0f, 700.0f}, 32.0f };

	// --当たり判定が有効か
	isCollision = true;

	// --プレイヤーの状態-- //
	state = Normal;
	xAxisState = static_cast<int>(XAxisState::Default);
//#ifdef _DEBUG
//	debug_changeDirectionMode = static_cast<int>(DirectionMode::Old);
//#endif

	// --横移動の速度-- //
	speedX = defaultSpeedX;

	// --移動する向き-- //
	direction = RIGHT;

	// --縦移動の速度-- //
	speedY = 10.0f;

	// --ブーストの経過時間[s]-- //
	boostTimer = 0.0f;
}

// --更新処理-- //
void Player::Update() {

	// --[SPACE]を押したら向きを変える-- //
	if (key_->IsTrigger(KEY_INPUT_SPACE)) {
		// --向きが右だったら左に変更-- //
		if (direction == RIGHT) {
			direction = LEFT;
#ifdef _DEBUG // デバッグ限定
			if (debug_changeDirectionMode == static_cast<int>(DirectionMode::New)) { // デバッグ用[SPACE]
				xAxisState = static_cast<int>(XAxisState::Boost);
				boostStartTime = GetNowCount();
				isEaseDraw = true;
				easeStartTime = GetNowCount();
			}
#endif
		}

		// --向きが左だったら右に変更-- //
		else if (direction == LEFT) {
			direction = RIGHT;
#ifdef _DEBUG
			if (debug_changeDirectionMode == static_cast<int>(DirectionMode::New)) {
				xAxisState = static_cast<int>(XAxisState::Boost);
				boostStartTime = GetNowCount();
				isEaseDraw = true;
				easeStartTime = GetNowCount();
			}
#endif
		}
	}

#ifdef _DEBUG
	if (key_->IsTrigger(KEY_INPUT_C)) {
		if (debug_changeDirectionMode == static_cast<int>(DirectionMode::Old)) debug_changeDirectionMode = static_cast<int>(DirectionMode::New);
		else if (debug_changeDirectionMode == static_cast<int>(DirectionMode::New)) debug_changeDirectionMode = static_cast<int>(DirectionMode::Old);
	}
#endif

	// --x軸のstateがBoostだったら-- //
	if (xAxisState == static_cast<int>(XAxisState::Boost)) {
		// --ブースト状態になってからの経過時間-- //
		float nowTime = (GetNowCount() - boostStartTime) / 1000.0f;

		DrawFormatString(0, 40, 0x000000, "nowTime = %f", nowTime);

		// --指定されているブースト時間が過ぎたら-- //
		if (0.1f <= nowTime) {
			// --ブースト状態から通常状態に変更-- //
			xAxisState = static_cast<int>(XAxisState::Default);
		}

		// --プレイヤーオブジェクトのX座標に速度を加算-- //
		player_[0].pos.x += 2 * speedX * direction;
		player_[1].pos.x += 2 * speedX * direction;
	}

	// --通常状態だったら-- //
	if (state == Normal) {
		// --プレイヤーオブジェクトのX座標に速度を加算-- //
		player_[0].pos.x += speedX * direction;
		player_[1].pos.x += speedX * direction;
	}

	// --ノックバック状態だったら-- //
	else if (state == Knock) {
		// --速度を加算-- //
		speedY += 0.4f;

		// --Y軸の速度が基礎値を越したら通常状態に変更-- //
		if (speedY > 0) {
			SetNormal();
		}

		//if (speedY >= 0.0f) {
		//	// --プレイヤーオブジェクトのX座標に速度を加算-- //
		//	whiteObj.pos.x += speedX * direction;
		//	blackObj.pos.x += speedX * direction;
		//}

		speedX += 0.2f;

		if (speedX >= defaultSpeedX) {
			speedX = defaultSpeedX;
		}

		// --プレイヤーオブジェクトのX座標に速度を加算-- //
		player_[0].pos.x += speedX * direction;
		player_[1].pos.x += speedX * direction;
	}

	// --ブースト状態だったら-- //
	else if (state == Boost) {
		// --ブースト状態になってからの経過時間-- //
		float nowTime = (GetNowCount() - boostStartTime) / 1000.0f;

		//DrawFormatString(0, 40, 0x000000, "nowTime = %f", nowTime);

		// --指定されているブースト時間が過ぎたら-- //
		if (boostTime <= nowTime) {
			// --ブースト状態から通常状態に変更-- //
			SetNormal();
		}

		// --プレイヤーオブジェクトのX座標に速度を加算-- //
		player_[0].pos.x += speedX * direction;
		player_[1].pos.x += speedX * direction;
	}

	// --プレイヤーの移動分スクロール-- //
	Camera::AddScroll(-speedY);

	// --一定まで行くとプレイヤーの座標を反対側に変更-- //
	if (player_[0].pos.x >= 960.0f) player_[0].pos.x -= 1280.0f;
	else if (player_[0].pos.x <= -320.0f) player_[0].pos.x += 1280.0f;

	if (player_[1].pos.x >= 960.0f) player_[1].pos.x -= 1280.0f;
	else if (player_[1].pos.x <= -320.0f) player_[1].pos.x += 1280.0f;
	//Collision();
}

// --描画処理-- //
void Player::Draw() {
	if (isEaseDraw == true) {
		// --ブースト状態になってからの経過時間-- //
		float nowTime = (GetNowCount() - easeStartTime) / 1000.0f;

		DrawFormatString(200, 40, 0x000000, "nowTime = %f", nowTime);

		// 
		player_[0].radius = MIN_SIZE_P;
		player_[1].radius = MIN_SIZE_P;

		// --指定されているブースト時間が過ぎたら-- //
		if (0.1f <= nowTime) {
			// --ブースト状態から通常状態に変更-- //
			isEaseDraw = false;
			player_[0].radius = MAX_SIZE_P;
			player_[1].radius = MAX_SIZE_P;
		}
	}

	// --白いプレイヤー描画-- //
	DrawBoxAA(player_[0], 0xFFFFFF, true);

	// --黒いプレイヤー描画-- //
	DrawBoxAA(player_[1], 0xFFFFFF, true);

	DrawFormatString(0, 40, 0x000000, "speedY = %f", speedY);
	DrawFormatString(0, 60, 0x000000, "state = %d", state);
	DrawFormatString(0, 100, 0x000000, "xAxisState = %d", xAxisState);
	DrawFormatString(0, 120, 0x000000, "directionMode = %d : changeMode [C]", debug_changeDirectionMode);
	DrawFormatString(0, 140, 0x000000, "isEase = %d", isEaseDraw);
	DrawFormatString(0, 160, 0x000000, "Pos = (%f, %f)", player_[0].pos.x, player_[0].pos.y);

}

// --白いオブジェクトの参照-- //
Object Player::GetPlayer1Obj() { return player_[0]; }

// --黒いオブジェクトの参照-- //
Object Player::GetPlayer2Obj() { return player_[1]; }

// --プレイヤーの状態を変更-- //
int Player::GetState() { return state; }

// --通常状態に変更-- //
void Player::SetNormal() {
	// --Y軸の速度を規定値に設定-- //
	speedY = defaultSpeedY;

	// --X軸の速度を規定値に設定-- //
	speedX = defaultSpeedX;

	// --通常状態に変更-- //
	state = Normal;

	// --当たり判定をONにする
	isCollision = true;
}

// --ノックバックに変更-- //
void Player::SetKnock() {
	// --Y軸の速度をノックバック時の速度に設定-- //
	speedY = defaultKnockSpeedY;

	// --通常状態に変更-- //
	state = Knock;

	speedX = 0.4f;

	// --当たり判定をOFFにする
	isCollision = false;
}

// --ブースト状態に変更-- //
void Player::SetBoost() {
	// --Y軸の速度をブースト時の規定値に設定-- //
	speedY = defaultBoostSpeedY;

	// --向きが右だったら左に変更-- //
	if (direction == RIGHT) direction = LEFT;

	// --向きが左だったら右に変更-- //
	else if (direction == LEFT) direction = RIGHT;

	// --ブースト状態に変更-- //
	state = Boost;

	boostStartTime = GetNowCount();
}

// --死亡状態に変更-- //
void Player::SetDeath() {
	SceneManager::SetScene(RESULTSCENE);
}

bool Player::GetCollisionFlag() { return isCollision; }

// --Y軸の速度を参照
float Player::GetSpeedY() { return speedY; }

// --X軸の速度を参照
float Player::GetSpeedX() { return speedX; }

// --白黒プレイヤーの座標Xに加算-- //
void Player::AddPlayerPosX(float value) {
	player_[0].pos.x += value;
	player_[1].pos.x += value;
}