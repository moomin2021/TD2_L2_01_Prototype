#include "Collision.h"
#include "Camera.h"
#include "DxLib.h"

bool BoxCollision(BoxObj box1, BoxObj box2) {
	if (box1.pos.x - box1.radiusX > box2.pos.x + box2.radiusX) return false;
	if (box1.pos.x + box1.radiusX < box2.pos.x - box2.radiusX) return false;
	if (box1.pos.y - box1.radiusY > box2.pos.y + box2.radiusY) return false;
	if (box1.pos.y + box1.radiusY < box2.pos.y - box2.radiusY) return false;
	return true;
}

bool BoxCenterCol(BoxObj box1, BoxObj box2) {
	if (box1.pos.x - box1.radiusX > box2.pos.x + box2.radiusX) return false;
	if (box1.pos.x + box1.radiusX < box2.pos.x - box2.radiusX) return false;
	return true;
}

int BoxXYCol(BoxObj& box1, BoxObj& box2) {
	float len1 = abs((box1.pos.y - box1.radiusY) - (box2.pos.y + box2.radiusY));
	float len2 = abs((box1.pos.y + box1.radiusY) - (box2.pos.y - box2.radiusY));
	float len3 = abs((box1.pos.x - box1.radiusX) - (box2.pos.x + box2.radiusX));
	float len4 = abs((box1.pos.x + box1.radiusX) - (box2.pos.x - box2.radiusX));

	if (len1 < len3) {
		if (len1 < len4) return 1;
	}

	if (len2 < len3) {
		if (len2 < len4) return 3;
	}
	return 2;
}

// --インスタンスにNULLを代入-- //
Collision* Collision::myInstance_ = nullptr;

// --インスタンス読み込み-- //
Collision* Collision::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance_ == nullptr) myInstance_ = new Collision();

	// --インスタンスを返す-- //
	return myInstance_;
}

// --メモリ解放-- //
void Collision::Release() {
	// --メモリ解放-- //
	delete myInstance_;

	// --NULLを代入-- //
	myInstance_ = nullptr;
}

// --コンストラクタ
Collision::Collision() {
	player_ = Player::GetInstance();
	stage_ = StageManager::GetInstance();
}

// --デストラクタ
Collision::~Collision() {

}

// --初期化処理
void Collision::Initialize() {

}

void Collision::Update() {

	// --プレイヤーの情報を格納-- //
	BoxObj playerObj[2];
	playerObj[0] = player_->GetPlayer1Obj();
	playerObj[1] = player_->GetPlayer2Obj();
	playerObj[0].pos.y += Camera::GetScroll();
	playerObj[1].pos.y += Camera::GetScroll();

	// --プレイヤーと衝突した障害物のデータ-- //
	std::vector<int> obsIndex;// -> 衝突した要素番号を記録
	std::vector<int> obsXY;// ----> 衝突した障害物どの方向から衝突したか記録
	int closestObsIndex = 0;// ---> 衝突したなかで一番近い障害物の要素番号
	float length = 100.0f;// -----> 衝突したプレイヤーと障害物の最も短い距離を記録

	// --プレイヤーと障害物が衝突したか-- //
	bool isCol = false;

	// --オブジェクトの距離-- //

	// --障害物の数だけ当たり判定を行う-- //
	for (int i = 0; i < stage_->obstacles_.size(); i++) {
		// --障害物の情報を格納-- //
		BoxObj obstacle = stage_->obstacles_[i].GetBoxObj();

		// --プレイヤーの数分当たり判定を行う-- //
		for (int j = 0; j < 2; j++) {
			// --プレイヤーと障害物が当たっていたら-- //
			if (BoxCollision(playerObj[j], obstacle) == true) {
				isCol = true;
				obsIndex.push_back(i);

				// --衝突した障害物がコインなら-- //
				if (stage_->obstacles_[i].GetBlockType() == Coin) {
					obsXY.push_back(0);
				}

				// --衝突した障害物が即死ブロックだった-- //
				else if (stage_->obstacles_[i].GetBlockType() == DeathBlock) {
					player_->SetDeath();
					return;
				}

				// --衝突した障害物がそれ以外なら-- //
				else {
					obsXY.push_back(BoxXYCol(playerObj[j], obstacle));
					if (length > abs(Vector2(obstacle.pos - playerObj[j].pos).length())) {
						length = abs(Vector2(obstacle.pos - playerObj[j].pos).length());
						closestObsIndex = obsIndex.size() - 1;
					}
				}
			}
		}
	}

	// --衝突したなら-- //
	if (isCol == true) {

		// --縦横どちらから当たったかを集計-- //
		int xCol = 0;
		int yCol = 0;
		for (int i = 0; i < obsXY.size(); i++) {
			if (obsXY[i] == 1) yCol += 1;
			else if (obsXY[i] == 2) xCol += 1;
		}

		// --プレイヤーがブースト状態なら-- //
		if (player_->GetState() == Boost) {
			// --一回でも横から衝突していたらブースト状態にする-- //
			if (xCol > 0) player_->SetBoost();

			// --衝突した障害物分ループ-- //
			for (int i = obsIndex.size() - 1; i >= 0; i--) {

				// --正面から当たっていたら-- //
				if (obsXY[i] == 1) {
					if (stage_->obstacles_[obsIndex[i]].GetBlockType() == CoinBlock) {
						// --現在のコイン数にプラス1-- //
						stage_->AddCoin();
					}
					stage_->obstacles_.erase(stage_->obstacles_.begin() + obsIndex[i]);
					obsIndex.erase(obsIndex.begin() + i);
					obsXY.erase(obsXY.begin() + i);
				}

				// --衝突したのがコインなら-- //
				else if (obsXY[i] == 0) {
					// --現在のコイン数にプラス1-- //
					stage_->AddCoin();
					stage_->obstacles_.erase(stage_->obstacles_.begin() + obsIndex[i]);
					obsIndex.erase(obsIndex.begin() + i);
					obsXY.erase(obsXY.begin() + i);
				}
			}
		}


		// --プレイヤーが通常状態なら-- //
		else if (player_->GetState() == Normal) {
			// --プレイヤーに一番近い障害物に衝突したのが正面からなら
			if (obsXY[closestObsIndex] == 1) player_->SetKnock();

			// --衝突したのが横からなら-- //
			else if(obsXY[closestObsIndex] == 2) player_->SetBoost();

			for (int i = obsIndex.size() - 1; i >= 0; i--) {
				if (obsXY[i] == 0) {
					// --現在のコイン数にプラス1-- //
					stage_->AddCoin();
					stage_->obstacles_.erase(stage_->obstacles_.begin() + obsIndex[i]);
					obsIndex.erase(obsIndex.begin() + i);
					obsXY.erase(obsXY.begin() + i);
				}
			}
		}

		else if (player_->GetState() == Knock) {
			for (int i = obsIndex.size() - 1; i >= 0; i--) {
				if (obsXY[i] == 0) {
					// --現在のコイン数にプラス1-- //
					stage_->AddCoin();
					stage_->obstacles_.erase(stage_->obstacles_.begin() + obsIndex[i]);
					obsIndex.erase(obsIndex.begin() + i);
					obsXY.erase(obsXY.begin() + i);
				}
			}
		}

		// --押し戻し処理-- //
		for (int i = 0; i < obsIndex.size(); i++) {
			for (int j = 0; j < 2; j++) {
				// --最新のプレイヤーの情報格納-- //
				playerObj[0] = player_->GetPlayer1Obj();
				playerObj[1] = player_->GetPlayer2Obj();
				playerObj[0].pos.y += Camera::GetScroll();
				playerObj[1].pos.y += Camera::GetScroll();

				// --障害物の情報を格納-- //
				BoxObj obstacle = stage_->obstacles_[obsIndex[i]].GetBoxObj();

				// --プレイヤーと障害物が当たっていたら-- //
				if (BoxCollision(playerObj[j], obstacle) == true) {
					if (BoxXYCol(playerObj[j], obstacle) == 2) {
						// --プレイヤーと障害物のX軸距離-- //
						float len = abs(playerObj[j].pos.x - obstacle.pos.x);

						// --プレイヤーと障害物のY軸半径を足した値-- //
						float radius = playerObj[j].radiusX + obstacle.radiusX;

						// --プレイヤーが障害物の右側にいたら-- //
						if (playerObj[j].pos.x >= obstacle.pos.x) {
							// --プレイヤーに距離と半径を引いた数を加算-- //
							player_->object_[0].pos.x += radius - len;
							player_->object_[1].pos.x += radius - len;
						}

						// --プレイヤーが障害物の左側にいたら-- //
						else if(playerObj[j].pos.x < obstacle.pos.x) {
							// --カメラに距離と半径を引いた数を加算-- //
							player_->object_[0].pos.x -= radius - len;
							player_->object_[1].pos.x -= radius - len;
						}
					}

					else if (player_->GetState() != Boost) {
						// --プレイヤーと障害物のY軸距離-- //
						float len = abs(playerObj[j].pos.y - obstacle.pos.y);

						// --プレイヤーと障害物のY軸半径を足した値-- //
						float radius = playerObj[j].radiusY + obstacle.radiusY;

						// --プレイヤーが障害物の下側にいたら-- //
						if (playerObj[j].pos.y >= obstacle.pos.y) {
							// --カメラに距離と半径を引いた数を加算-- //
							Camera::AddScroll(radius - len);
						}

						// --プレイヤーが障害物の左側にいたら-- //
						else if (playerObj[j].pos.y < obstacle.pos.y) {
							// --カメラに距離と半径を引いた数を加算-- //
							Camera::AddScroll(-(radius - len));
						}
					}
				}
			}
		}
	}
}