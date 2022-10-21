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

#define UP -1
#define DOWN 1

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
#pragma region プレイヤーの速度変数
	// --Y軸基本速度-- //
	defSpeedY_(5.0f),

	// --Y軸の最高速度-- //
	maxSpeedY_(30.0f),

	// --Y軸の最低速度-- //
	minSpeedY_(5.0f),

	// --X座標の最高座標-- //
	maxPosX_(616.0f),

	// --X座標の最低座標-- //
	minPosX_(24.0f),

	// --壁キックの速度-- //
	wallKickSpeedX_(20.0f),

	// --回転状態の時間[s]-- //
	rotateTime_(0.5f),

	// --Y軸の減速値-- //
	decelerationY_(0.2f),

	// --Y軸の加速値-- //
	accelerationY_(5.0f)
#pragma endregion
{
#pragma region クラス定義
	// --キーボード入力-- //
	key_ = Key::GetInstance();

	// --ステージ管理-- //
	stageManager_ = StageManager::GetInstance();
#pragma endregion

	// --プレイヤーオブジェクト-- //
	object_ = { {24.0f, 100.0f}, 24.0f, 24.0f };

	// --プレイヤーの状態-- //
	state_ = NormalWallHit;

	// --速度-- //
	speedX_ = 0.0f;// -------> X軸
	speedY_ = minSpeedY_;// -> Y軸

	// --空中にいるか-- //
	isAir_ = false;

	// --空中キックができるか-- //
	isAirKickActive_ = true;

	// --移動する向き-- //
	directionX_ = LEFT;
	directionY_ = DOWN;

	// --ブーストの経過時間[s]-- //
	rotateTimer_ = 0.0f;

	// --ブーストが始まった時の時間-- //
	rotateStartTime_ = 0;
}

// --デストラクタ-- //
Player::~Player() {

}

// --初期化処理-- //
void Player::Initialize() {
	// --プレイヤーオブジェクト-- //
	object_ = { {minPosX_, 100.0f}, 24.0f, 24.0f };

	// --プレイヤーの状態-- //
	state_ = NormalWallHit;

	// --速度-- //
	speedX_ = 0.0f;
	speedY_ = defSpeedY_;

	// --移動する向き-- //
	directionX_ = LEFT;
	directionY_ = DOWN;

	// --ブーストの経過時間[s]-- //
	rotateTimer_ = 0.0f;

	// --ブーストが始まった時の時間-- //
	rotateStartTime_ = 0;

	// --空中にいるか-- //
	isAir_ = false;

	// --空中キックができるか-- //
	isAirKickActive_ = true;
}

// --更新処理-- //
void Player::Update() {

#pragma region 通常状態かつ壁伝い中の処理
	if (state_ == NormalWallHit) {
		// --[SPACE]を押したら-- //
		if (key_->IsTrigger(KEY_INPUT_SPACE)) {
			// --左右の向きを変える-- //
			ChangeDireX();

			// --状態を変える-- //
			state_ = NormalAir;// -> 通常状態かつ空中

			// --X軸の速度を変える-- //
			speedX_ = wallKickSpeedX_;// --壁キックしたときの速度-- //

			// --Y軸の移動方向が上だったら-- //
			if (directionY_ == UP) {
				speedY_ -= accelerationY_;
			}

			// --Y軸の移動方向が下だったら-- //
			else if (directionY_ == DOWN) {
				speedY_ += accelerationY_;
			}
		}

		// --減速処理-- //
		if (directionY_ == DOWN) {
			speedY_ -= decelerationY_;
			speedY_ = Util::Clamp(speedY_, maxSpeedY_, minSpeedY_);
		}

		else if (directionY_ == UP) {
			speedY_ -= decelerationY_;
			if (speedY_ <= 0) {
				directionY_ = DOWN;
			}
		}
	}
#pragma endregion

#pragma region 通常状態かつ空中にいる
	else if (state_ == NormalAir) {
		
	}
#pragma endregion

#pragma region 回転状態かつ壁伝い中
	else if (state_ == RotateWallHit) {
		// --[SPACE]を押したら-- //
		if (key_->IsTrigger(KEY_INPUT_SPACE)) {
			// --左右の向きを変える-- //
			ChangeDireX();

			// --状態を変える-- //
			state_ = NormalAir;// -> 通常状態かつ空中

			// --X軸の速度を変える-- //
			speedX_ = wallKickSpeedX_;// --壁キックしたときの速度-- //
		}

		// --ブースト状態になってからの経過時間-- //
		float nowTime = (GetNowCount() - rotateStartTime_) / 1000.0f;

		// --指定されているブースト時間が過ぎたら-- //
		if (rotateTime_ <= nowTime) {
			// --ブースト状態から通常状態に変更-- //
			state_ = NormalWallHit;
		}
	}
#pragma endregion

#pragma region 回転状態かつ空中にいる
	else if (state_ == RotateAir) {
		// --ブースト状態になってからの経過時間-- //
		float nowTime = (GetNowCount() - rotateStartTime_) / 1000.0f;

		// --指定されているブースト時間が過ぎたら-- //
		if (rotateTime_ <= nowTime) {
			// --ブースト状態から通常状態に変更-- //
			state_ = NormalAir;
		}
	}
#pragma endregion

	// --プレイヤーのX軸に加算-- //
	object_.pos.x += speedX_ * directionX_;

	// --プレイヤーの移動分スクロール-- //
	Camera::AddScroll(speedY_ * directionY_);

	// --x座標が最低座標以下になったら-- //
	if (object_.pos.x < minPosX_) {
		// --x座標を変更-- //
		object_.pos.x = minPosX_;

		// --状態を変更-- //
		state_ = NormalWallHit;// -> 通常状態かつ壁伝い中

		// --X軸の速度を変える-- //
		speedX_ = 0.0f;// -> 動かないように
	}

	// --x座標が最高座標以上になったら-- //
	else if (object_.pos.x > maxPosX_) {
		// --X座標を変更-- //
		object_.pos.x = maxPosX_;

		// --状態を変更-- //
		state_ = NormalWallHit;// -> 通常状態かつ壁伝い中

		// --X軸の速度を変える-- //
		speedX_ = 0.0f;// -> 動かないように
	}
}

// --描画処理-- //
void Player::Draw() {

	DrawBoxAA(object_, BLACK, true);

	DrawFormatString(0, 40, WHITE, "speedX_ : %f", speedX_);
	DrawFormatString(0, 60, WHITE, "speedY_ : %f", speedY_);
	DrawFormatString(0, 80, WHITE, "direX : %d", directionX_);
	DrawFormatString(0, 100, WHITE, "Pos : (%f, %f)", object_.pos.x, object_.pos.y);
	DrawFormatString(0, 120, WHITE, "Scroll : %f", Camera::GetScroll());

}

// --オブジェクトの参照-- //
BoxObj Player::GetBoxObj() { return object_; }

// --プレイヤーの状態を変更-- //
int Player::GetState() { return state_; }

// --プレイヤーの状態を変更-- //
void Player::SetState(int state) { state_ = state; }
//
// --死亡状態に変更-- //
void Player::SetDeath() {
	SceneManager::SetScene(RESULTSCENE);
}

float& Player::GetSpeedX() { return speedX_; }
float& Player::GetSpeedY() { return speedY_; }

// --X軸の向きを変える-- //
void Player::ChangeDireX() {
	if (directionX_ == LEFT) directionX_ = RIGHT;
	else directionX_ = LEFT;
}

void Player::ChangeDireY() {
	if (directionY_ == UP) directionY_ = DOWN;
	else directionY_ = UP;
}

// --回転状態にする-- //
void Player::SetRotate() {
	speedY_ = maxSpeedY_;

	state_ = RotateAir;
	rotateStartTime_ = GetNowCount();
}