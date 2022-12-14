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
void DrawBoxAA(BoxObj obj, unsigned int color, bool fillFlag) {
	DrawBoxAA(
		obj.pos.x - obj.radiusX, obj.pos.y - obj.radiusY,
		obj.pos.x + obj.radiusX, obj.pos.y + obj.radiusY,
		color, fillFlag);

	DrawLineAA(obj.pos.x - obj.radiusX, obj.pos.y - obj.radiusY, obj.pos.x + obj.radiusX, obj.pos.y - obj.radiusY, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x - obj.radiusX, obj.pos.y + obj.radiusY, obj.pos.x + obj.radiusX, obj.pos.y + obj.radiusY, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x - obj.radiusX, obj.pos.y - obj.radiusY, obj.pos.x - obj.radiusX, obj.pos.y + obj.radiusY, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x + obj.radiusX, obj.pos.y - obj.radiusY, obj.pos.x + obj.radiusX, obj.pos.y + obj.radiusY, color ^ 0xFFFFFF, 3);
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
	object_[0] = { {300.0f, 700.0f}, 32.0f, 32.0f };
	object_[1] = { {900.0f, 700.0f}, 32.0f, 32.0f };

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
	object_[0] = { {300.0f, 700.0f}, 32.0f, 32.0f };
	object_[1] = { {900.0f, 700.0f}, 32.0f, 32.0f };

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

	// --通常状態だったら-- //
	if (state == Normal) {
		speedX += 0.2f;

		if (speedX >= defaultSpeedX) {
			speedX = defaultSpeedX;
		}

		// --速度を加算-- //
		speedY += 0.4f;

		if (speedY >= defaultSpeedY) {
			speedY = defaultSpeedY;
		}
	}

	// --ノックバック状態だったら-- //
	else if (state == Knock) {
		// --速度を加算-- //
		speedY += 0.4f;

		// --Y軸の速度が基礎値を越したら通常状態に変更-- //
		if (speedY > 0) {
			SetNormal();
		}

		speedX += 0.2f;

		if (speedX >= defaultSpeedX) {
			speedX = defaultSpeedX;
		}
	}

	// --ブースト状態だったら-- //
	else if (state == Boost) {
		// --ブースト状態になってからの経過時間-- //
		float nowTime = (GetNowCount() - boostStartTime) / 1000.0f;

		// --指定されているブースト時間が過ぎたら-- //
		if (boostTime <= nowTime) {
			// --ブースト状態から通常状態に変更-- //
			SetNormal();
		}
	}

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
		object_[0].pos.x += 2 * speedX * direction;
		object_[1].pos.x += 2 * speedX * direction;
	}
	else {
		// --プレイヤーオブジェクトのX座標に速度を加算-- //
		object_[0].pos.x += speedX * direction;
		object_[1].pos.x += speedX * direction;
	}

	// --プレイヤーの移動分スクロール-- //
	Camera::AddScroll(-speedY);

	// --一定まで行くとプレイヤーの座標を反対側に変更-- //
	if (object_[0].pos.x >= 960.0f) object_[0].pos.x -= 1280.0f;
	else if (object_[0].pos.x <= -320.0f) object_[0].pos.x += 1280.0f;

	if (object_[1].pos.x >= 960.0f) object_[1].pos.x -= 1280.0f;
	else if (object_[1].pos.x <= -320.0f) object_[1].pos.x += 1280.0f;
	//Collision();
}

// --描画処理-- //
void Player::Draw() {
	if (isEaseDraw == true) {
		// --ブースト状態になってからの経過時間-- //
		float nowTime = (GetNowCount() - easeStartTime) / 1000.0f;

		DrawFormatString(200, 40, 0x000000, "nowTime = %f", nowTime);

		// 
		object_[0].radiusX = MIN_SIZE_P;
		object_[1].radiusX = MIN_SIZE_P;

		// --指定されているブースト時間が過ぎたら-- //
		if (0.1f <= nowTime) {
			// --ブースト状態から通常状態に変更-- //
			isEaseDraw = false;
			object_[0].radiusX = MAX_SIZE_P;
			object_[1].radiusX = MAX_SIZE_P;
		}
	}

	// --ノックバック状態なら
	if (state == Knock) {
		// --オブジェクト1描画-- //
		DrawBoxAA(object_[0], 0x000000, true);

		// --オブジェクト2描画-- //
		DrawBoxAA(object_[1], 0x000000, true);
	}
	else {
		// --オブジェクト1描画-- //
		DrawBoxAA(object_[0], 0xFFFFFF, true);

		// --オブジェクト2描画-- //
		DrawBoxAA(object_[1], 0xFFFFFF, true);
	}

	DrawFormatString(0, 40, 0x000000, "speedY = %f", speedY);
	DrawFormatString(0, 60, 0x000000, "state = %d", state);
	DrawFormatString(0, 100, 0x000000, "xAxisState = %d", xAxisState);
	DrawFormatString(0, 120, 0x000000, "directionMode = %d : changeMode [C]", debug_changeDirectionMode);
	DrawFormatString(0, 140, 0x000000, "isEase = %d", isEaseDraw);
	DrawFormatString(0, 160, 0x000000, "Pos = (%f, %f)", object_[0].pos.x, object_[0].pos.y);

}

// --白いオブジェクトの参照-- //
BoxObj Player::GetPlayer1Obj() { return object_[0]; }

// --黒いオブジェクトの参照-- //
BoxObj Player::GetPlayer2Obj() { return object_[1]; }

// --プレイヤーの状態を変更-- //
int Player::GetState() { return state; }

// --通常状態に変更-- //
void Player::SetNormal() {

	// --X軸の速度を規定値に設定-- //
	speedX = defaultSpeedX;

	// --通常状態に変更-- //
	state = Normal;
}

// --ノックバックに変更-- //
void Player::SetKnock() {
	// --Y軸の速度をノックバック時の速度に設定-- //
	speedY = defaultKnockSpeedY;

	// --通常状態に変更-- //
	state = Knock;

	speedX = 0.4f;
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