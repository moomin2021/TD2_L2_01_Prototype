#include "DxLib.h"
#include "Player.h"

// --黒-- //
#define BLACK 0x000000

// --白-- //
#define WHITE 0xFFFFFF

// --向き-- //
#define LEFT -1
#define RIGHT 1

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
	defaultSpeedX(10.0f)

#pragma endregion
{
	// --クラス定義-- //
	key = Key::GetInstance();

	// --座標-- //
	pos[0] = { 300.0f, 700.0f };
	pos[1] = { 900.0f, 700.0f };

	// --半径-- //
	radius = 16.0f;

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
	// --座標-- //
	pos[0] = { 300.0f, 700.0f };
	pos[1] = { 900.0f, 700.0f };

	// --半径-- //
	radius = 16.0f;

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

	// --プレイヤーのX座標に速度を加算-- //
	pos[0].x += speedX * direction;
	pos[1].x += speedX * direction;

	// --一定まで行くとプレイヤーの座標を反対側に変更-- //
	if (pos[0].x >= 900.0f) pos[0].x -= 1200.0f;
	else if (pos[0].x <= -300.0f) pos[0].x += 1200.0f;

	if (pos[1].x >= 900.0f) pos[1].x -= 1200.0f;
	else if (pos[1].x <= -300.0f) pos[1].x += 1200.0f;
}

// --描画処理-- //
void Player::Draw() {
	// --プレイヤー描画-- //
	DrawBoxAA(pos[0].x - radius, pos[0].y - radius, pos[0].x + radius, pos[0].y + radius,
		WHITE, true);

	DrawBoxAA(pos[1].x - radius, pos[1].y - radius, pos[1].x + radius, pos[1].y + radius,
		WHITE, false);
}