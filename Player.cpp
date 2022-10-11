#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "StageManager.h"

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
	key = Key::GetInstance();
	stageManager_ = StageManager::GetInstance();

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
	speedY = defaultSpeedY;

	// --ブーストの時間[s]-- //
	boostTime = 5.0f;

	// --ブーストの経過時間[s]-- //
	boostTimer = 0.0f;

	// --ブーストが始まった時の時間-- //
	boostStartTime = 0;
}

void Player::Coliision()
{
#pragma region 四点の情報更新
	// white
	vPosW.leftTop = whiteObj.pos - Vector2(whiteObj.radius, whiteObj.radius);     // 中心(x,y) - 半径(x,y)
	vPosW.rightTop = whiteObj.pos - Vector2(-whiteObj.radius, whiteObj.radius);   // 中心(x,y) - 半径(-x,y)
	vPosW.leftBottom = whiteObj.pos + Vector2(-whiteObj.radius, whiteObj.radius); // 中心(x,y) + 半径(-x,y)
	vPosW.rightBottom = whiteObj.pos + Vector2(whiteObj.radius, whiteObj.radius); // 中心(x,y) + 半径(x,y)
	// black
	vPosB.leftTop = blackObj.pos - Vector2(blackObj.radius, blackObj.radius);     // 中心(x,y) - 半径(x,y)
	vPosB.rightTop = blackObj.pos - Vector2(-blackObj.radius, blackObj.radius);   // 中心(x,y) - 半径(-x,y)
	vPosB.leftBottom = blackObj.pos + Vector2(-blackObj.radius, blackObj.radius); // 中心(x,y) + 半径(-x,y)
	vPosB.rightBottom = blackObj.pos + Vector2(blackObj.radius, blackObj.radius); // 中心(x,y) + 半径(x,y)
#pragma endregion

#pragma region 四点の座標をマップチップ単位に置換
	// white : 左上
	vElemsW.leftTop.x = vPosW.leftTop.x / StageManager::blockSize_;
	vElemsW.leftTop.y = vPosW.leftTop.y / StageManager::blockSize_;
	// : 左下
	vElemsW.leftBottom.x = vPosW.leftBottom.x / StageManager::blockSize_;
	vElemsW.leftBottom.y = vPosW.leftBottom.y / StageManager::blockSize_;
	// : 右上
	vElemsW.rightTop.x = vPosW.rightTop.x / StageManager::blockSize_;
	vElemsW.rightTop.y = vPosW.rightTop.y / StageManager::blockSize_;
	// : 右下
	vElemsW.rightBottom.x = vPosW.rightBottom.x / StageManager::blockSize_;
	vElemsW.rightBottom.y = vPosW.rightBottom.y / StageManager::blockSize_;

	// black : 左上
	vElemsB.leftTop.x = vPosB.leftTop.x / StageManager::blockSize_;
	vElemsB.leftTop.y = vPosB.leftTop.y / StageManager::blockSize_;
	// : 左下
	vElemsB.leftBottom.x = vPosB.leftBottom.x / StageManager::blockSize_;
	vElemsB.leftBottom.y = vPosB.leftBottom.y / StageManager::blockSize_;
	// : 右上
	vElemsB.rightTop.x = vPosB.rightTop.x / StageManager::blockSize_;
	vElemsB.rightTop.y = vPosB.rightTop.y / StageManager::blockSize_;
	// : 右下
	vElemsB.rightBottom.x = vPosB.rightBottom.x / StageManager::blockSize_;
	vElemsB.rightBottom.y = vPosB.rightBottom.y / StageManager::blockSize_;
#pragma endregion

#pragma region 当たり判定
	// プレイヤー座標が障害物と重なった場合 : 同色
	if (stageManager_->GetMapchipData()->at(vElemsW.leftTop.y).at(vElemsW.leftTop.x) == static_cast<int>(BlockId::White) ||			// 左上
		stageManager_->GetMapchipData()->at(vElemsW.leftBottom.y).at(vElemsW.leftBottom.x) == static_cast<int>(BlockId::White) ||	// 左下
		stageManager_->GetMapchipData()->at(vElemsW.rightTop.y).at(vElemsW.rightTop.x) == static_cast<int>(BlockId::White) ||		// 右上
		stageManager_->GetMapchipData()->at(vElemsW.rightBottom.y).at(vElemsW.rightBottom.x) == static_cast<int>(BlockId::White) ||	// 右下
		stageManager_->GetMapchipData()->at(vElemsB.leftTop.y).at(vElemsB.leftTop.x) == static_cast<int>(BlockId::Black) ||				// 左上
		stageManager_->GetMapchipData()->at(vElemsB.leftBottom.y).at(vElemsB.leftBottom.x) == static_cast<int>(BlockId::Black) ||		// 左下
		stageManager_->GetMapchipData()->at(vElemsB.rightTop.y).at(vElemsB.rightTop.x) == static_cast<int>(BlockId::Black) ||			// 右上
		stageManager_->GetMapchipData()->at(vElemsB.leftBottom.y).at(vElemsB.leftBottom.x) == static_cast<int>(BlockId::Black)) {		// 右下

		// スピードゲージを増やす
	}

	// プレイヤー座標が障害物と重なった場合 : 異色 : 正面
	if (stageManager_->GetMapchipData()->at(vElemsW.leftTop.y).at(vElemsW.leftTop.x) == static_cast<int>(BlockId::Black) &&			// 左上
		stageManager_->GetMapchipData()->at(vElemsW.rightTop.y).at(vElemsW.rightTop.x) == static_cast<int>(BlockId::Black) &&		// 右上
		stageManager_->GetMapchipData()->at(vElemsW.leftBottom.y).at(vElemsW.leftBottom.x) != static_cast<int>(BlockId::Black)&&	// 左下
		stageManager_->GetMapchipData()->at(vElemsW.rightBottom.y).at(vElemsW.rightBottom.x) != static_cast<int>(BlockId::Black)) {	// 右下

		SetKnock();
	}
	if (stageManager_->GetMapchipData()->at(vElemsB.leftTop.y).at(vElemsB.leftTop.x) == static_cast<int>(BlockId::White) &&			// 左上
		stageManager_->GetMapchipData()->at(vElemsB.rightTop.y).at(vElemsB.rightTop.x) == static_cast<int>(BlockId::White) &&		// 右上
		stageManager_->GetMapchipData()->at(vElemsB.leftBottom.y).at(vElemsB.leftBottom.x) != static_cast<int>(BlockId::White)&&	// 左下
		stageManager_->GetMapchipData()->at(vElemsB.rightBottom.y).at(vElemsB.rightBottom.x) != static_cast<int>(BlockId::White)) {	// 右下

		SetKnock();
	}

	// プレイヤー座標が障害物と重なった場合 : 異色 : 横 : 左から右へ
	if (stageManager_->GetMapchipData()->at(vElemsW.rightTop.y).at(vElemsW.rightTop.x) == static_cast<int>(BlockId::Black) &&		// 右上
		stageManager_->GetMapchipData()->at(vElemsW.rightBottom.y).at(vElemsW.rightBottom.x) == static_cast<int>(BlockId::Black) &&	// 右下
		stageManager_->GetMapchipData()->at(vElemsW.leftTop.y).at(vElemsW.leftTop.x) != static_cast<int>(BlockId::Black) &&			// 左上
		stageManager_->GetMapchipData()->at(vElemsW.leftBottom.y).at(vElemsW.leftBottom.x) != static_cast<int>(BlockId::Black)) {	// 左下

		SetBoost();
	}
	if (stageManager_->GetMapchipData()->at(vElemsB.rightTop.y).at(vElemsB.rightTop.x) == static_cast<int>(BlockId::Black) &&		// 右上
		stageManager_->GetMapchipData()->at(vElemsB.rightBottom.y).at(vElemsB.rightBottom.x) == static_cast<int>(BlockId::Black) &&	// 右下
		stageManager_->GetMapchipData()->at(vElemsB.leftTop.y).at(vElemsB.leftTop.x) != static_cast<int>(BlockId::Black) &&			// 左上
		stageManager_->GetMapchipData()->at(vElemsB.leftBottom.y).at(vElemsB.leftBottom.x) != static_cast<int>(BlockId::Black)) {	// 左下

		SetBoost();
	}

	// プレイヤー座標が障害物と重なった場合 : 異色 : 横 : 右から左へ
	if (stageManager_->GetMapchipData()->at(vElemsW.leftTop.y).at(vElemsW.leftTop.x) == static_cast<int>(BlockId::Black) &&			// 左上
		stageManager_->GetMapchipData()->at(vElemsW.leftBottom.y).at(vElemsW.leftBottom.x) == static_cast<int>(BlockId::Black) &&	// 左下
		stageManager_->GetMapchipData()->at(vElemsW.rightTop.y).at(vElemsW.rightTop.x) != static_cast<int>(BlockId::Black) &&		// 右上
		stageManager_->GetMapchipData()->at(vElemsW.rightBottom.y).at(vElemsW.rightBottom.x) != static_cast<int>(BlockId::Black)) {	// 右下

		SetBoost();
	}
	if (stageManager_->GetMapchipData()->at(vElemsB.leftTop.y).at(vElemsB.leftTop.x) == static_cast<int>(BlockId::Black) &&			// 左上
		stageManager_->GetMapchipData()->at(vElemsB.leftBottom.y).at(vElemsB.leftBottom.x) == static_cast<int>(BlockId::Black) &&	// 左下
		stageManager_->GetMapchipData()->at(vElemsB.rightTop.y).at(vElemsB.rightTop.x) != static_cast<int>(BlockId::Black) &&		// 右上
		stageManager_->GetMapchipData()->at(vElemsB.rightBottom.y).at(vElemsB.rightBottom.x) != static_cast<int>(BlockId::Black)) {	// 右下

		SetBoost();
	}
#pragma endregion
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
		// --速度を加算-- //
		speedY += 0.5f;

		// --Y軸の速度が基礎値を越したら通常状態に変更-- //
		if (speedY >= defaultSpeedY) {
			SetNormal();
		}
	}

	// --ブースト状態だったら-- //
	else if (state == Boost) {
		// --ブースト状態になってからの経過時間-- //
		float nowTime = (GetNowCount() - boostStartTime) / 1000.0f;

		// --指定されているブースト時間が過ぎたら-- //
		if (boostTime <= nowTime) {
			// --ブースト状態から通常状態に変更-- //
			SetBoost();
		}
	}

	// --一定まで行くとプレイヤーの座標を反対側に変更-- //
	if (whiteObj.pos.x >= 960.0f) whiteObj.pos.x -= 1280.0f;
	else if (whiteObj.pos.x <= -320.0f) whiteObj.pos.x += 1280.0f;

	if (blackObj.pos.x >= 960.0f) blackObj.pos.x -= 1280.0f;
	else if (blackObj.pos.x <= -320.0f) blackObj.pos.x += 1280.0f;

	Coliision();
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

// --通常状態に変更-- //
void Player::SetNormal() {
	// --Y軸の速度を規定値に設定-- //
	speedY = defaultSpeedY;

	// --通常状態に変更-- //
	state = Normal;
}

// --ノックバックに変更-- //
void Player::SetKnock() {
	// --Y軸の速度をノックバック時の速度に設定-- //
	speedY = defaultKnockSpeedY;

	// --通常状態に変更-- //
	state = Knock;
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
}