#include "DxLib.h"
#include "Player.h"
#include "Camera.h"

// --黒-- //
#define BLACK 0x000000

// --白-- //
#define WHITE 0xFFFFFF

// --向き-- //
#define LEFT -1
#define RIGHT 1

// --オブジェクトの描画用の関数-- //
void DrawBoxAA(Object obj, unsigned int color,  bool fillFlag) {
	DrawBoxAA(
		obj.pos.x - obj.radius, obj.pos.y - obj.radius,
		obj.pos.x + obj.radius, obj.pos.y + obj.radius,
		color, fillFlag);
}

// --インスタンスにNULLを代入-- //
Player* Player::myInstance = nullptr;

// --インスタンス読み込み-- //
Player* Player::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new Player();

	// --インスタンスを返す-- //
	return myInstance;
}

// --メモリ解放-- //
void Player::Release() {
	// --メモリ解放-- //
	delete myInstance;

	// --NULLを代入-- //
	myInstance = nullptr;
}

// --コンストラクタ-- //
Player::Player() :
#pragma region 定数メンバの初期化

	// --横移動速度の基礎値-- //
	defaultSpeedX(5.0f)

#pragma endregion
{
	// --クラス定義-- //
	key = Key::GetInstance();

	// --白いプレイヤーオブジェクト-- //
	whiteObj = { {300.0f, 700.0f}, 32.0f };

	// --黒いプレイヤーオブジェクト-- //
	blackObj = { {900.0f, 700.0f}, 32.0f };

	// --プレイヤーの状態-- //
	state = Normal;

	// --横移動の速度-- //
	speedX = defaultSpeedX;

	// --移動する向き-- //
	direction = RIGHT;

	// --縦移動の速度-- //
	speedY = 10.0f;

	// --ブーストの時間[s]-- //
	boostTime = 5.0f;

	// --ブーストの経過時間[s]-- //
	boostTimer = 0.0f;

	// --ブーストが始まった時の時間-- //
	boostStartTime = 0;
}

void Player::Coliision()
{

}

// --デストラクタ-- //
Player::~Player() {
	
}

// --初期化処理-- //
void Player::Initialize() {
	// --白いプレイヤーオブジェクト-- //
	whiteObj = { {320.0f, 700.0f}, 32.0f };

	// --黒いプレイヤーオブジェクト-- //
	blackObj = { {960.0f, 700.0f}, 32.0f };

	// --プレイヤーの状態-- //
	state = Normal;

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
	if (key->IsTrigger(KEY_INPUT_SPACE)) {
		// --向きが右だったら左に変更-- //
		if (direction == RIGHT) direction = LEFT;

		// --向きが左だったら右に変更-- //
		else if (direction == LEFT) direction = RIGHT;
	}

	// --通常状態だったら-- //
	if (state == Normal) {
		// --プレイヤーオブジェクトのX座標に速度を加算-- //
		whiteObj.pos.x += speedX * direction;
		blackObj.pos.x += speedX * direction;

		// --プレイヤーの移動分スクロール-- //
		Camera::AddScroll(-speedY);
	}

	// --ノックバック状態だったら-- //
	else if (state == Knock) {

	}

	// --ブースト状態だったら-- //
	else if (state == Boost) {
		// --ブースト状態になってからの経過時間-- //
		float nowTime = (GetNowCount() - boostStartTime) / 1000.0f;

		// --指定されているブースト時間が過ぎたら-- //
		if (boostTime <= nowTime) {
			// --ブースト状態から通常状態に変更-- //
			state = Normal;
		}
	}

	// --一定まで行くとプレイヤーの座標を反対側に変更-- //
	if (whiteObj.pos.x >= 960.0f) whiteObj.pos.x -= 1280.0f;
	else if (whiteObj.pos.x <= -320.0f) whiteObj.pos.x += 1280.0f;

	if (blackObj.pos.x >= 960.0f) blackObj.pos.x -= 1280.0f;
	else if (blackObj.pos.x <= -320.0f) blackObj.pos.x += 1280.0f;
}

// --描画処理-- //
void Player::Draw() {
	// --白いプレイヤー描画-- //
	DrawBoxAA(whiteObj, 0xFFFFFF, true);

	// --黒いプレイヤー描画-- //
	DrawBoxAA(blackObj, 0x000000, true);
}

// --白いオブジェクトの参照-- //
Object Player::GetWhiteObj() { return whiteObj; }

// --黒いオブジェクトの参照-- //
Object Player::GetBlackObj() { return blackObj; }

// --プレイヤーの状態を変更-- //
void Player::SetState(int state) { this->state = state; }