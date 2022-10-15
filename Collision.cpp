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
	// --フラグがtrueになると多重ループを抜ける-- //
	bool isActive = false;

	// --プレイヤーの情報を格納-- //
	Box playerObj[2];
	playerObj[0] = { {player_->GetPlayer1Obj().pos.x, player_->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer1Obj().radius, player_->GetPlayer1Obj().radius };
	playerObj[1] = { {player_->GetPlayer2Obj().pos.x, player_->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer2Obj().radius, player_->GetPlayer2Obj().radius };

	// --障害物の数だけ当たり判定を行う-- //
	for (int i = 0; i < stage_->obstacles_.size(); i++) {
		// --障害物の情報を格納-- //
		Box obstacle = { stage_->obstacles_[i].GetPos(), stage_->obstacles_[i].GetRadiusX(), stage_->obstacles_[i].GetRadiusY() };

		// --プレイヤーの数分当たり判定を行う-- //
		for (int j = 0; j < 2; j++) {
			// --プレイヤーと障害物が当たっていたら-- //
			if (BoxCollision(playerObj[j], obstacle) == true) {
				// --プレイヤーと当たっている障害物がブロックだったら-- //
				if (stage_->obstacles_[i].GetBlockType() == Block) {
					// --プレイヤーがオブジェクトの正面から当たっていたら-- //
					if (BoxCenterCol(oldPlayerObj_[j], obstacle) == true) {
						// --プレイヤーの状態が通常状態だったら-- //
						if (player_->GetState() == Normal) {
							// --プレイヤーと障害物のY軸距離-- //
							float len = playerObj[j].pos.y - obstacle.pos.y;

							// --プレイヤーと障害物のY軸半径を足した値-- //
							float radius = playerObj[j].radiusY + obstacle.radiusY;

							// --カメラに距離と半径を引いた数を加算-- //
							Camera::AddScroll(radius - len);

							// --状態をノックバック状態に変更-- //
							player_->SetKnock();
						}

						// --状態がブースト状態なら-- //
						else if (player_->GetState() == Boost) {
							// --当たった障害物を消す-- //
							stage_->obstacles_.erase(stage_->obstacles_.begin() + i);
						}
					}

					// --横から当たっていたら-- //
					else {
						// --プレイヤーと障害物のX軸距離-- //
						float len = abs(playerObj[j].pos.x - obstacle.pos.x);

						// --プレイヤーと障害物のY軸半径を足した値-- //
						float radius = playerObj[j].radiusX + obstacle.radiusX;

						// --プレイヤーが障害物の右側にいたら-- //
						if (playerObj[j].pos.x >= obstacle.pos.x) {
							// --プレイヤーに距離と半径を引いた数を加算-- //
							player_->AddPlayerPosX(radius - len);
						}

						// --プレイヤーが障害物の左側にいたら-- //
						else {
							// --カメラに距離と半径を引いた数を加算-- //
							player_->AddPlayerPosX(-(radius - len));
						}

						// --状態をブースト状態に変更-- //
						player_->SetBoost();

						isActive = true;

						break;
					}
				}

				// --プレイヤーと当たっている障害物がコインブロックだったら-- //
				else if (stage_->obstacles_[i].GetBlockType() == CoinBlock) {
					// --プレイヤーがオブジェクトの正面から当たっていたら-- //
					if (BoxCenterCol(oldPlayerObj_[j], obstacle) == true) {
						// --プレイヤーの状態が通常状態だったら-- //
						if (player_->GetState() == Normal) {
							// --プレイヤーと障害物のY軸距離-- //
							float len = playerObj[j].pos.y - obstacle.pos.y;

							// --プレイヤーと障害物のY軸半径を足した値-- //
							float radius = playerObj[j].radiusY + obstacle.radiusY;

							// --カメラに距離と半径を引いた数を加算-- //
							Camera::AddScroll(radius - len);

							// --状態をノックバック状態に変更-- //
							player_->SetKnock();
						}

						// --状態がブースト状態なら-- //
						else if (player_->GetState() == Boost) {
							// --当たった障害物を消す-- //
							stage_->obstacles_.erase(stage_->obstacles_.begin() + i);

							// --現在のコイン数にプラス1-- //
							stage_->AddCoin();
						}
					}

					// --横から当たっていたら-- //
					else {
						// --プレイヤーと障害物のX軸距離-- //
						float len = abs(playerObj[j].pos.x - obstacle.pos.x);

						// --プレイヤーと障害物のY軸半径を足した値-- //
						float radius = playerObj[j].radiusX + obstacle.radiusX;

						// --プレイヤーが障害物の右側にいたら-- //
						if (playerObj[j].pos.x >= obstacle.pos.x) {
							// --プレイヤーに距離と半径を引いた数を加算-- //
							player_->AddPlayerPosX(radius - len);
						}

						// --プレイヤーが障害物の左側にいたら-- //
						else {
							// --カメラに距離と半径を引いた数を加算-- //
							player_->AddPlayerPosX(-(radius - len));
						}

						// --状態をブースト状態に変更-- //
						player_->SetBoost();

						isActive = true;

						break;
					}
				}

				// --プレイヤーと当たっている障害物がコインだったら-- //
				else if (stage_->obstacles_[i].GetBlockType() == Coin) {
					// --当たった障害物を消す-- //
					stage_->obstacles_.erase(stage_->obstacles_.begin() + i);

					// --現在のコイン数にプラス1-- //
					stage_->AddCoin();
				}

				// --プレイヤーと当たっている障害物が即死ブロックだったら-- //
				else if (stage_->obstacles_[i].GetBlockType() == DeathBlock) {
					player_->SetDeath();
				}
			}
		}

		// --多重ループを抜ける-- //
		if (isActive == true) {
			break;
		}
	}

	// --次のフレームで使うためにプレイヤーの情報を格納-- //
	oldPlayerObj_[0] = { {player_->GetPlayer1Obj().pos.x, player_->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer1Obj().radius, player_->GetPlayer1Obj().radius };
	oldPlayerObj_[1] = { {player_->GetPlayer2Obj().pos.x, player_->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer2Obj().radius, player_->GetPlayer2Obj().radius };
}