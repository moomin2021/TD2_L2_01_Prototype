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

// --更新処理
void Collision::Update() {
	// --プレイヤーの当たり判定フラグがtrueだったら当たり判定を行う
	if (player->GetCollisionFlag() == true) {
		Box blackObj = { {player->GetBlackObj().pos.x, player->GetBlackObj().pos.y + Camera::GetScroll()}, player->GetBlackObj().radius, player->GetBlackObj().radius };
		Box whiteObj = { {player->GetWhiteObj().pos.x, player->GetWhiteObj().pos.y + Camera::GetScroll()}, player->GetWhiteObj().radius, player->GetWhiteObj().radius };
		for (int i = 0; i < stage->obstacles.size(); i++) {
			Box obstacle = { stage->obstacles[i].GetPos(), stage->obstacles[i].GetRadiusX(), stage->obstacles[i].GetRadiusY() };
			if (BoxCollision(whiteObj, obstacle)) {
				if (stage->obstacles[i].GetColor() == 0x000000) {
					// --正面から当たっていたら
					if (BoxCenterCol(oldWhiteBox, obstacle)) {
						if (player->GetState() == Normal) {
							player->SetKnock();
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}
						else if (player->GetState() == Boost) {
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}
					}

					// --横から当たっていたら
					else {
						player->SetBoost();
					}

					break;
				}
			}

			if (BoxCollision(blackObj, obstacle)) {
				if (stage->obstacles[i].GetColor() == 0xFFFFFF) {
					// --正面から当たっていたら
					if (BoxCenterCol(oldBlackBox, obstacle)) {
						if (player->GetState() == Normal) {
							player->SetKnock();
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}
						else if (player->GetState() == Boost) {
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}
					}

					// --横から当たっていたら
					else {
						player->SetBoost();
					}

					break;
				}
			}
		}
	}

	oldWhiteBox = { {player->GetWhiteObj().pos.x, player->GetWhiteObj().pos.y  + Camera::GetScroll()}, 32, 32 };
	oldBlackBox = { {player->GetBlackObj().pos.x, player->GetBlackObj().pos.y  + Camera::GetScroll()}, 32, 32 };
}

// --更新処理-- //
//void Collision::Update() {
//	// --プレイヤーの当たり判定フラグがONだったら-- //
//	if (player->GetCollisionFlag() == true) {
//		// --黒と白のプレイヤーの座標と半径の情報を格納-- //
//		Box blackObj = { {player->GetBlackObj().pos.x, player->GetBlackObj().pos.y + Camera::GetScroll()}, player->GetBlackObj().radius, player->GetBlackObj().radius };
//		Box whiteObj = { {player->GetWhiteObj().pos.x, player->GetWhiteObj().pos.y + Camera::GetScroll()}, player->GetWhiteObj().radius, player->GetWhiteObj().radius };
//
//		// --障害物の数分当たり判定をとる-- //
//		for (int i = 0; i < stage->obstacles.size(); i++) {
//			// --障害物の座標と半径を格納-- //
//			Box obstacle = { stage->obstacles[i].GetPos(), stage->obstacles[i].GetRadiusX(), stage->obstacles[i].GetRadiusY() };
//
//			// --
//			if (BoxCollision(whiteObj, obstacle) || BoxCollision(blackObj, obstacle)) {
//
//			}
//		}
//	}
//}