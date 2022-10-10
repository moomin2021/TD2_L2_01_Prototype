#include "DxLib.h"
#include "Player.h"

// --黒-- //
#define BLACK 0x000000

// --白-- //
#define WHITE 0xFFFFFF

// --向き-- //
#define LEFT -1
#define RIGHT 1

// --オブジェクトの描画用の関数-- //
void DrawBoxAA(Object obj, bool fillFlag) {
	DrawBoxAA(
		obj.pos.x - obj.radius, obj.pos.y - obj.radius,
		obj.pos.x + obj.radius, obj.pos.y + obj.radius,
		0xFFFFFF, fillFlag);
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
}

// --デストラクタ-- //
Player::~Player() {
	
}

// --初期化処理-- //
void Player::Initialize() {
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

	// --プレイヤーオブジェクトのX座標に速度を加算-- //
	whiteObj.pos.x += speedX * direction;
	blackObj.pos.x += speedX * direction;

	// --一定まで行くとプレイヤーの座標を反対側に変更-- //
	if (whiteObj.pos.x >= 900.0f) whiteObj.pos.x -= 1200.0f;
	else if (whiteObj.pos.x <= -300.0f) whiteObj.pos.x += 1200.0f;

	if (blackObj.pos.x >= 900.0f) blackObj.pos.x -= 1200.0f;
	else if (blackObj.pos.x <= -300.0f) blackObj.pos.x += 1200.0f;
}

// --描画処理-- //
void Player::Draw() {
	// --白いプレイヤー描画-- //
	DrawBoxAA(whiteObj, true);

	// --黒いプレイヤー描画-- //
	DrawBoxAA(blackObj, false);
}

// --白いオブジェクトの参照-- //
Object Player::GetWhiteObj() { return whiteObj; }

// --黒いオブジェクトの参照-- //
Object Player::GetBlackObj() { return blackObj; }

// --プレイヤーの状態を変更-- //
void Player::SetState(int state) { this->state = state; }