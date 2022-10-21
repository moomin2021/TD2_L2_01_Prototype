#include "Collision.h"
#include "Camera.h"
#include "DxLib.h"

bool BoxCollision(BoxObj box1, BoxObj box2) {
	if (box1.pos.x - box1.radiusX >= box2.pos.x + box2.radiusX) return false;
	if (box1.pos.x + box1.radiusX <= box2.pos.x - box2.radiusX) return false;
	if (box1.pos.y - box1.radiusY >= box2.pos.y + box2.radiusY) return false;
	if (box1.pos.y + box1.radiusY <= box2.pos.y - box2.radiusY) return false;
	return true;
}

bool BoxCenterCol(BoxObj box1, BoxObj box2) {
	if (box1.pos.x - box1.radiusX > box2.pos.x + box2.radiusX) return false;
	if (box1.pos.x + box1.radiusX < box2.pos.x - box2.radiusX) return false;
	return true;
}

enum Dire {
	UP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4
};

int BoxXYCol(BoxObj box1, BoxObj box2) {


	float len1 = abs((box1.pos.y - box1.radiusY) - (box2.pos.y + box2.radiusY));
	float len2 = abs((box1.pos.y + box1.radiusY) - (box2.pos.y - box2.radiusY));
	float len3 = abs((box1.pos.x - box1.radiusX) - (box2.pos.x + box2.radiusX));
	float len4 = abs((box1.pos.x + box1.radiusX) - (box2.pos.x - box2.radiusX));

	if (len1 <= len2) {
		if (len1 <= len3) {
			if (len1 <= len4) return 1;
		}
	}

	if (len2 <= len1) {
		if (len2 <= len3) {
			if (len2 <= len4) return 2;
		}
	}

	if (len3 <= len1) {
		if (len3 <= len2) {
			if (len3 <= len4) return 3;
		}
	}

	return 4;
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

//void Collision::Update() {
//	// --プレイヤーと衝突した障害物のデータ-- //
//	std::vector<int> colObsIndex;// -> 衝突した要素番号を記録
//	std::vector<int> colObsXY;// ----> 衝突した障害物どの方向から衝突したか記録
//	int closestObsIndex = 0;// ---> 衝突したなかで一番近い障害物の要素番号
//	float length = 100.0f;// -----> 衝突したプレイヤーと障害物の最も短い距離を記録
//
//	// --衝突したか-- //
//	bool isCollision = false;
//
//	// --最新プレイヤー情報を格納-- //
//	BoxObj newObj = player_->GetBoxObj();
//	newObj.pos.y += Camera::GetScroll();
//
//	// --古いプレイヤーから最新プレイヤーまでのベクトルを計算-- //
//	Vector2 old2newVec = newObj.pos - oldObj_.pos;
//
//	// --できるだけ細かく衝突判定をとるために10回に分ける-- //
//	for (int i = 0; i < 10; i++) {
//		// --ループを抜けるか-- //
//		bool isOutLoop = false;
//
//		// --古いプレイヤーに10で割ったベクトルを足す-- //
//		oldObj_.pos += old2newVec / 10;
//
//		// --障害物の数だけループさせる-- //
//		for (int j = 0; j < stage_->obstacles_.size(); j++) {
//
//			// --プレイヤーと障害物の衝突判定を行う-- //
//			if (BoxCollision(oldObj_, stage_->obstacles_[j].GetBoxObj())) {
//				int blockType = stage_->obstacles_[j].GetBlockType();
//
//				if (blockType == Coin) {
//					stage_->AddCoin();
//					stage_->obstacles_.erase(stage_->obstacles_.begin() + j);
//				}
//
//				else {
//					// --衝突した障害物の要素数を保存-- //
//					colObsIndex.push_back(j);
//
//					// --衝突した障害物にどの方向から当たったか-- //
//					colObsXY.push_back(BoxXYCol(oldObj_, stage_->obstacles_[j].GetBoxObj()));
//
//					// --プレイヤーから障害物までのベクトル-- //
//					Vector2 player2Obs = stage_->obstacles_[j].GetBoxObj().pos - oldObj_.pos;
//
//					// --プレイヤーから障害物までのいままでより短いなら-- //
//					if (player2Obs.length() < length) {
//						// --長さを更新-- //
//						length = player2Obs.length();
//
//						// --要素数を更新-- //
//						closestObsIndex = j;
//					}
//
//					// --多重ループを抜ける-- //
//					isOutLoop = true;
//
//					// --衝突フラグをONにする-- //
//					isCollision = true;
//				}
//			}
//		}
//		// --フラグがONならループを抜ける-- //
//		if (isOutLoop == true) break;
//	}
//
//	// --衝突していたら-- //
//	if (isCollision == true) {
//		bool isLeft = false;
//		bool isRight = false;
//		bool isUp = false;
//		bool isDown = false;
//
//		for (int i = 0; i < colObsXY.size(); i++) {
//			if (colObsXY[i] == LEFT) isLeft = true;
//			if (colObsXY[i] == RIGHT) isRight = true;
//			if (colObsXY[i] == UP) isUp = true;
//			if (colObsXY[i] == DOWN) isDown = true;
//		}
//
//		// --横から当たっていたら-- //
//		if (isLeft == true || isRight == true) {
//			// --プレイヤーの状態を変える-- //
//			player_->SetRotate();// --回転状態に-- //
//
//			// --X軸の移動方向を変える-- //
//			player_->ChangeDireX();
//
//			// --プレイヤーの状態が通常状態かつ空中にいたら-- //
//			if (player_->GetState() == NormalAir) {
//				// --プレイヤーの状態を変更-- //
//				player_->SetState(RotateAir);// -> 回転状態かつ空中
//			}
//		}
//
//		// --縦から当たっていたら-- //
//		if (isUp == true || isDown == true) {
//			// --プレイヤーの状態を変える-- //
//			player_->SetRotate();// --回転状態に-- //
//
//			// --プレイヤーのY軸の移動方向を変える-- //
//			player_->ChangeDireY();
//		}
//
//		for (int i = colObsIndex.size() - 1; i >= 0; i--) {
//			if (stage_->obstacles_[colObsIndex[i]].GetBlockType() == DeathBlock) {
//				// --プレイヤーの状態が通常状態なら-- //
//				if (player_->GetState() == NormalAir || player_->GetState() == NormalWallHit) {
//					// --プレイヤーの状態を変更-- //
//					player_->SetState(Death);// -> 死亡状態
//				}
//
//				// --プレイヤーが回転状態なら-- //
//				else if (player_->GetState() == RotateWallHit || player_->GetState() == RotateAir) {
//					// --障害物を削除-- //
//					stage_->obstacles_.erase(stage_->obstacles_.begin() + colObsIndex[i]);
//				}
//			}
//		}
//
//		// --押し戻し処理-- //
//		for (int i = 0; i < colObsIndex.size(); i++) {
//			// --障害物の情報を格納-- //
//			BoxObj obstacle = stage_->obstacles_[colObsIndex[i]].GetBoxObj();
//
//			// --プレイヤーと障害物が当たっていたら-- //
//			if (BoxCollision(oldObj_, obstacle) == true) {
//				if (BoxXYCol(oldObj_, obstacle) >= 3) {
//					// --プレイヤーと障害物のX軸距離-- //
//					float len = abs(oldObj_.pos.x - obstacle.pos.x);
//
//					// --プレイヤーと障害物のY軸半径を足した値-- //
//					float radius = oldObj_.radiusX + obstacle.radiusX;
//
//					// --プレイヤーが障害物の右側にいたら-- //
//					if (oldObj_.pos.x >= obstacle.pos.x) {
//						// --プレイヤーに距離と半径を引いた数を加算-- //
//						oldObj_.pos.x += radius - len;
//						player_->object_.pos.x = oldObj_.pos.x;
//					}
//
//					// --プレイヤーが障害物の左側にいたら-- //
//					else if (oldObj_.pos.x < obstacle.pos.x) {
//						// --カメラに距離と半径を引いた数を加算-- //
//						oldObj_.pos.x -= radius - len;
//						player_->object_.pos.x = oldObj_.pos.x;
//					}
//				}
//
//				else if (BoxXYCol(oldObj_, obstacle) <= 2) {
//					// --プレイヤーと障害物のY軸距離-- //
//					float len = abs(oldObj_.pos.y - obstacle.pos.y);
//
//					// --プレイヤーと障害物のY軸半径を足した値-- //
//					float radius = oldObj_.radiusY + obstacle.radiusY;
//
//					// --プレイヤーが障害物の下側にいたら-- //
//					if (oldObj_.pos.y >= obstacle.pos.y) {
//						// --カメラに距離と半径を引いた数を加算-- //
//						Camera::AddScroll(radius - len);
//					}
//
//					// --プレイヤーが障害物の左側にいたら-- //
//					else if (oldObj_.pos.y < obstacle.pos.y) {
//						// --カメラに距離と半径を引いた数を加算-- //
//						Camera::AddScroll(-(radius - len));
//					}
//				}
//			}
//		}
//	}
//
//	// --古いプレイヤー情報を格納-- //
//	oldObj_ = player_->GetBoxObj();
//	oldObj_.pos.y += Camera::GetScroll();
//}

void Collision::Update() {
	// --最新プレイヤー情報を格納-- //
	BoxObj newObj = player_->GetBoxObj();
	newObj.pos.y += Camera::GetScroll();

	// --古いプレイヤーから最新プレイヤーまでのベクトルを計算-- //
	Vector2 old2newVec = newObj.pos - oldObj_.pos;

	float scroll = Camera::GetScroll();

	bool isOutLoop = false;

	// --細かく判定をとるために移動量を10で割って当たり判定をとる-- //
	for (int i = 0; i < 10; i++) {
		if (isOutLoop == true) break;

		bool isCollision = true;

		oldObj_.pos += old2newVec / 10;

		while (isCollision) {
			BoxObj colObs = {};
			int colObsXY = 0;// ----------> どの方向から衝突したら
			int closestObsIndex = 0;// ---> 衝突したなかで一番近い障害物の要素番号
			float length = 100.0f;// -----> 衝突したプレイヤーと障害物の最も短い距離を記録

			// --障害物の数分ループする-- //
			for (int j = 0; j < stage_->obstacles_.size(); j++) {
				BoxObj obstacle = stage_->obstacles_[j].GetBoxObj();

				// --衝突している-- //
				if (BoxCollision(oldObj_, obstacle)) {
					float player2ObsLen = (obstacle.pos - oldObj_.pos).length();
  					if (player2ObsLen <= length) {
						colObsXY = BoxXYCol(oldObj_, obstacle);
						closestObsIndex = j;
						length = player2ObsLen;
						colObs = stage_->obstacles_[j].GetBoxObj();
					}
				}
			}

			if (length == 100.0f) {
				isCollision = false;
			}

			if (isCollision == true) {
				if (stage_->obstacles_[closestObsIndex].GetBlockType() == DeathBlock) {
					stage_->obstacles_.erase(stage_->obstacles_.begin() + closestObsIndex);

					// --プレイヤーの状態が通常状態なら-- //
					if (player_->GetState() == NormalAir || player_->GetState() == NormalWallHit) {
						// --プレイヤーの状態を変更-- //
						player_->SetDeath();// -> 死亡状態
					}

					//// --プレイヤーが回転状態なら-- //
					//else if (player_->GetState() == RotateWallHit || player_->GetState() == RotateAir) {
					//	// --障害物を削除-- //
					//	stage_->obstacles_.erase(stage_->obstacles_.begin() + colObsIndex[i]);
					//}
				}

				else if (stage_->obstacles_[closestObsIndex].GetBlockType() == Coin) {
					stage_->AddCoin();
					stage_->obstacles_.erase(stage_->obstacles_.begin() + closestObsIndex);
				}

				else if (stage_->obstacles_[closestObsIndex].GetBlockType() == BoundBlock) {

					if (colObsXY >= 3) {
						// --プレイヤーの状態を変える-- //
						player_->SetRotate();// --回転状態に-- //

						// --X軸の移動方向を変える-- //
						player_->ChangeDireX();

						// --プレイヤーの状態が通常状態かつ空中にいたら-- //
						if (player_->GetState() == NormalAir) {
							// --プレイヤーの状態を変更-- //
							player_->SetState(RotateAir);// -> 回転状態かつ空中
						}

						// --プレイヤーと障害物のX軸距離-- //
						float len = abs(oldObj_.pos.x - colObs.pos.x);

						// --プレイヤーと障害物のY軸半径を足した値-- //
						float radius = oldObj_.radiusX + colObs.radiusX;

						// --プレイヤーが障害物の右側にいたら-- //
						if (oldObj_.pos.x >= colObs.pos.x) {
							// --プレイヤーに距離と半径を引いた数を加算-- //
							oldObj_.pos.x += radius - len;
							player_->object_.pos.x = oldObj_.pos.x;
						}

						// --プレイヤーが障害物の左側にいたら-- //
						else if (oldObj_.pos.x < colObs.pos.x) {
							// --カメラに距離と半径を引いた数を加算-- //
							oldObj_.pos.x -= radius - len;
							player_->object_.pos.x = oldObj_.pos.x;
						}
					}

					else if (colObsXY <= 2) {
						// --プレイヤーの状態を変える-- //
						player_->SetRotate();// --回転状態に-- //

						// --プレイヤーのY軸の移動方向を変える-- //
						player_->ChangeDireY();

						// --プレイヤーと障害物のY軸距離-- //
						float len = abs(oldObj_.pos.y - colObs.pos.y);

						// --プレイヤーと障害物のY軸半径を足した値-- //
						float radius = oldObj_.radiusY + colObs.radiusY;

						// --プレイヤーが障害物の下側にいたら-- //
						if (oldObj_.pos.y >= colObs.pos.y) {
							// --カメラに距離と半径を引いた数を加算-- //
							oldObj_.pos.y += radius - len;
							Camera::AddScroll(radius - len);
						}

						// --プレイヤーが障害物の左側にいたら-- //
						else if (oldObj_.pos.y < colObs.pos.y) {
							// --カメラに距離と半径を引いた数を加算-- //
							oldObj_.pos.y -= radius - len;
							Camera::AddScroll(-(radius - len));
							scroll = Camera::GetScroll();
						}
					}

					isOutLoop = true;
				}
			}
		}

		if (i == 9) {
			oldObj_ = newObj;
		}
	}

	// --古いプレイヤー情報を格納-- //
	oldObj_ = player_->GetBoxObj();
	oldObj_.pos.y += Camera::GetScroll();
}