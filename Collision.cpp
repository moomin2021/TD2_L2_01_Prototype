#include "Collision.h"
#include "Camera.h"

bool BoxCollision(Box box1, Box box2) {
	if (box1.pos.x - box1.radiusX > box2.pos.x + box2.radiusX) return false;
	if (box1.pos.x + box1.radiusX < box2.pos.x - box2.radiusX) return false;
	if (box1.pos.y - box1.radiusY > box2.pos.y + box2.radiusY) return false;
	if (box1.pos.y + box1.radiusY < box2.pos.y - box2.radiusY) return false;
	return true;
}

bool BoxCenterCol(Box box1, Box box2) {
	if (box1.pos.x - box1.radiusX > box2.pos.x + box2.radiusX) return false;
	if (box1.pos.x + box1.radiusX < box2.pos.x - box2.radiusX) return false;
	return true;
}

// --インスタンスにNULLを代入-- //
Collision* Collision::myInstance = nullptr;

// --インスタンス読み込み-- //
Collision* Collision::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new Collision();

	// --インスタンスを返す-- //
	return myInstance;
}

// --メモリ解放-- //
void Collision::Release() {
	// --メモリ解放-- //
	delete myInstance;

	// --NULLを代入-- //
	myInstance = nullptr;
}

// --コンストラクタ
Collision::Collision() {
	player = Player::GetInstance();
	stage = StageManager::GetInstance();
}

// --デストラクタ
Collision::~Collision() {

}

// --初期化処理
void Collision::Initialize() {

}

// --更新処理-- //
void Collision::Update() {
	// --プレイヤーの当たり判定フラグがONだったら-- //
	if (player->GetCollisionFlag() == true) {
		// --黒と白のプレイヤーの座標と半径の情報を格納-- //
		Box blackObj = { {player->GetBlackObj().pos.x, player->GetBlackObj().pos.y + Camera::GetScroll()}, player->GetBlackObj().radius, player->GetBlackObj().radius };
		Box whiteObj = { {player->GetWhiteObj().pos.x, player->GetWhiteObj().pos.y + Camera::GetScroll()}, player->GetWhiteObj().radius, player->GetWhiteObj().radius };

		// --障害物の数分当たり判定をとる-- //
		for (int i = 0; i < stage->obstacles.size(); i++) {
			// --障害物の座標と半径を格納-- //
			Box obstacle = { stage->obstacles[i].GetPos(), stage->obstacles[i].GetRadiusX(), stage->obstacles[i].GetRadiusY() };

			// --白プレイヤーの当たり判定-- //
			if (BoxCollision(whiteObj, obstacle)) {

				// --当たった障害物が黒色だったら-- //
				if (stage->obstacles[i].GetColor() == 0x000000) {
					// --正面から当たっていたら-- //
					if (BoxCenterCol(oldWhiteBox, obstacle)) {
						// --通常状態なら-- //
						if (player->GetState() == Normal) {
							// --プレイヤーと障害物のY軸距離-- //
							float len = whiteObj.pos.y - obstacle.pos.y;

							// --プレイヤーと障害物のY軸半径を足した値-- //
							float radius = whiteObj.radiusY + obstacle.radiusY;

							// --カメラに距離と半径を引いた数を加算-- //
							Camera::AddScroll(radius - len);

							// --状態をノックバック状態に変更-- //
							player->SetKnock();

							// --当たった障害物を消す-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}

						// --状態がブースト状態なら-- //
						else if (player->GetState() == Boost) {
							// --当たった障害物を消す-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}
					}

					// --横から当たっていたら
					else {
						// --プレイヤーと障害物のX軸距離-- //
						float len = abs(whiteObj.pos.x - obstacle.pos.x);

						// --プレイヤーと障害物のY軸半径を足した値-- //
						float radius = whiteObj.radiusX + obstacle.radiusX;

						// --プレイヤーが障害物の右側にいたら-- //
						if (whiteObj.pos.x >= obstacle.pos.x) {
							// --カメラに距離と半径を引いた数を加算-- //
							player->AddPlayerPosX(radius - len);
						}

						// --プレイヤーが障害物の左側にいたら-- //
						else {
							// --カメラに距離と半径を引いた数を加算-- //
							player->AddPlayerPosX(-(radius - len));
						}

						// --状態をブースト状態に変更-- //
						player->SetBoost();
					}

					break;
				}
			}

			// --黒プレイヤーの当たり判定-- //
			if (BoxCollision(blackObj, obstacle)) {

				// --当たった障害物が黒色だったら-- //
				if (stage->obstacles[i].GetColor() == 0xFFFFFF) {
					// --正面から当たっていたら-- //
					if (BoxCenterCol(oldBlackBox, obstacle)) {
						// --通常状態なら-- //
						if (player->GetState() == Normal) {
							// --プレイヤーと障害物のY軸距離-- //
							float len = blackObj.pos.y - obstacle.pos.y;

							// --プレイヤーと障害物のY軸半径を足した値-- //
							float radius = blackObj.radiusY + obstacle.radiusY;

							// --カメラに距離と半径を引いた数を加算-- //
							Camera::AddScroll(radius - len);

							// --状態をノックバック状態に変更-- //
							player->SetKnock();

							// --当たった障害物を消す-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}

						// --状態がブースト状態なら-- //
						else if (player->GetState() == Boost) {
							// --当たった障害物を消す-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}
					}

					// --横から当たっていたら
					else {
						// --プレイヤーと障害物のX軸距離-- //
						float len = abs(blackObj.pos.x - obstacle.pos.x);

						// --プレイヤーと障害物のY軸半径を足した値-- //
						float radius = blackObj.radiusX + obstacle.radiusX;

						// --プレイヤーが障害物の右側にいたら-- //
						if (blackObj.pos.x >= obstacle.pos.x) {
							// --プレイヤーに距離と半径を引いた数を加算-- //
							player->AddPlayerPosX(radius - len);
						}

						// --プレイヤーが障害物の左側にいたら-- //
						else {
							// --カメラに距離と半径を引いた数を加算-- //
							player->AddPlayerPosX(-(radius - len));
						}

						// --状態をブースト状態に変更-- //
						player->SetBoost();
					}

					break;
				}
			}
		}
	}

	// --プレイヤーの情報を格納-- //
	oldWhiteBox = { {player->GetWhiteObj().pos.x, player->GetWhiteObj().pos.y + Camera::GetScroll()}, 32, 32 };
	oldBlackBox = { {player->GetBlackObj().pos.x, player->GetBlackObj().pos.y + Camera::GetScroll()}, 32, 32 };
}