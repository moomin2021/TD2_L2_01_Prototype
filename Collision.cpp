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
//void Collision::Update() {
//	// --プレイヤーの当たり判定フラグがONだったら-- //
//	if (player->GetCollisionFlag() == true) {
//		// --黒と白のプレイヤーの座標と半径の情報を格納-- //
//		Box player1Obj = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player->GetPlayer1Obj().radius, player->GetPlayer1Obj().radius };
//		Box player2Obj = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player->GetPlayer2Obj().radius, player->GetPlayer2Obj().radius };
//
//		// --障害物の数分当たり判定をとる-- //
//		for (int i = 0; i < stage->obstacles.size(); i++) {
//			// --障害物の座標と半径を格納-- //
//			Box obstacle = { stage->obstacles[i].GetPos(), stage->obstacles[i].GetRadiusX(), stage->obstacles[i].GetRadiusY() };
//
//			// --白プレイヤーの当たり判定-- //
//			if (BoxCollision(player1Obj, obstacle)) {
//
//				// --当たった障害物が黒色だったら-- //
//				if (stage->obstacles[i].GetBlockType() == Block) {
//					// --正面から当たっていたら-- //
//					if (BoxCenterCol(oldPlayer1Box, obstacle)) {
//						// --通常状態なら-- //
//						if (player->GetState() == Normal) {
//							// --プレイヤーと障害物のY軸距離-- //
//							float len = player1Obj.pos.y - obstacle.pos.y;
//
//							// --プレイヤーと障害物のY軸半径を足した値-- //
//							float radius = player1Obj.radiusY + obstacle.radiusY;
//
//							// --カメラに距離と半径を引いた数を加算-- //
//							Camera::AddScroll(radius - len);
//
//							// --状態をノックバック状態に変更-- //
//							player->SetKnock();
//
//							// --当たった障害物を消す-- //
//							//stage->obstacles.erase(stage->obstacles.begin() + i);
//						}
//
//						// --状態がブースト状態なら-- //
//						else if (player->GetState() == Boost) {
//							// --当たった障害物を消す-- //
//							stage->obstacles.erase(stage->obstacles.begin() + i);
//						}
//					}
//
//					// --横から当たっていたら
//					else {
//						// --プレイヤーと障害物のX軸距離-- //
//						float len = abs(player1Obj.pos.x - obstacle.pos.x);
//
//						// --プレイヤーと障害物のY軸半径を足した値-- //
//						float radius = player2Obj.radiusX + obstacle.radiusX;
//
//						// --プレイヤーが障害物の右側にいたら-- //
//						if (player1Obj.pos.x >= obstacle.pos.x) {
//							// --カメラに距離と半径を引いた数を加算-- //
//							player->AddPlayerPosX(radius - len);
//						}
//
//						// --プレイヤーが障害物の左側にいたら-- //
//						else {
//							// --カメラに距離と半径を引いた数を加算-- //
//							player->AddPlayerPosX(-(radius - len));
//						}
//
//						// --状態をブースト状態に変更-- //
//						player->SetBoost();
//					}
//
//					break;
//				}
//			}
//
//			// --黒プレイヤーの当たり判定-- //
//			if (BoxCollision(player2Obj, obstacle)) {
//
//				// --当たった障害物が黒色だったら-- //
//				if (stage->obstacles[i].GetBlockType() == Block) {
//					// --正面から当たっていたら-- //
//					if (BoxCenterCol(oldPlayer2Box, obstacle)) {
//						// --通常状態なら-- //
//						if (player->GetState() == Normal) {
//							// --プレイヤーと障害物のY軸距離-- //
//							float len = player2Obj.pos.y - obstacle.pos.y;
//
//							// --プレイヤーと障害物のY軸半径を足した値-- //
//							float radius = player2Obj.radiusY + obstacle.radiusY;
//
//							// --カメラに距離と半径を引いた数を加算-- //
//							Camera::AddScroll(radius - len);
//
//							// --状態をノックバック状態に変更-- //
//							player->SetKnock();
//
//							// --当たった障害物を消す-- //
//							//stage->obstacles.erase(stage->obstacles.begin() + i);
//						}
//
//						// --状態がブースト状態なら-- //
//						else if (player->GetState() == Boost) {
//							// --当たった障害物を消す-- //
//							stage->obstacles.erase(stage->obstacles.begin() + i);
//						}
//					}
//
//					// --横から当たっていたら
//					else {
//						// --プレイヤーと障害物のX軸距離-- //
//						float len = abs(player2Obj.pos.x - obstacle.pos.x);
//
//						// --プレイヤーと障害物のY軸半径を足した値-- //
//						float radius = player2Obj.radiusX + obstacle.radiusX;
//
//						// --プレイヤーが障害物の右側にいたら-- //
//						if (player2Obj.pos.x >= obstacle.pos.x) {
//							// --プレイヤーに距離と半径を引いた数を加算-- //
//							player->AddPlayerPosX(radius - len);
//						}
//
//						// --プレイヤーが障害物の左側にいたら-- //
//						else {
//							// --カメラに距離と半径を引いた数を加算-- //
//							player->AddPlayerPosX(-(radius - len));
//						}
//
//						// --状態をブースト状態に変更-- //
//						player->SetBoost();
//					}
//
//					break;
//				}
//			}
//		}
//	}
//
//	// --プレイヤーの情報を格納-- //
//	oldPlayer1Box = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, 32, 32 };
//	oldPlayer2Box = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, 32, 32 };
//}

//void Collision::Update() {
//	// --プレイヤーの情報を格納-- //
//	Box playerObj[2];
//	playerObj[0] = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player->GetPlayer1Obj().radius, player->GetPlayer1Obj().radius };
//	playerObj[1] = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player->GetPlayer2Obj().radius, player->GetPlayer2Obj().radius };
//
//	// --プレイヤーオブジェクトの数分当たり判定をとる-- //
//	for (int i = 0; i < 2; i++) {
//		// --障害物の数分当たり判定をとる-- //
//		for (int j = 0; j < stage->obstacles.size(); j++) {
//			// --障害物の情報を格納-- //
//			Box obstacle = { stage->obstacles[j].GetPos(), stage->obstacles[j].GetRadiusX(), stage->obstacles[j].GetRadiusY() };
//
//			// --プレイヤーと障害物が当たっていたら-- //
//			if (BoxCollision(playerObj[i], obstacle) == true) {
//				// --プレイヤーと当たっている障害物がブロックだったら-- //
//				if (stage->obstacles[j].GetBlockType() == Block) {
//					// --プレイヤーがオブジェクトの正面から当たっていたら-- //
//					if (BoxCenterCol(oldPlayerObj[i], obstacle) == true) {
//						// --プレイヤーの状態が通常状態だったら-- //
//						if (player->GetState() == Normal) {
//							// --プレイヤーと障害物のY軸距離-- //
//							float len = playerObj[i].pos.y - obstacle.pos.y;
//
//							// --プレイヤーと障害物のY軸半径を足した値-- //
//							float radius = playerObj[i].radiusY + obstacle.radiusY;
//
//							// --カメラに距離と半径を引いた数を加算-- //
//							Camera::AddScroll(radius - len);
//
//							// --状態をノックバック状態に変更-- //
//							player->SetKnock();
//						}
//
//						// --状態がブースト状態なら-- //
//						else if (player->GetState() == Boost) {
//							// --当たった障害物を消す-- //
//							stage->obstacles.erase(stage->obstacles.begin() + i);
//						}
//					}
//
//					// --横から当たっていたら-- //
//					else {
//						// --プレイヤーと障害物のX軸距離-- //
//						float len = abs(playerObj[i].pos.x - obstacle.pos.x);
//
//						// --プレイヤーと障害物のY軸半径を足した値-- //
//						float radius = playerObj[i].radiusX + obstacle.radiusX;
//
//						// --プレイヤーが障害物の右側にいたら-- //
//						if (playerObj[i].pos.x >= obstacle.pos.x) {
//							// --プレイヤーに距離と半径を引いた数を加算-- //
//							player->AddPlayerPosX(radius - len);
//						}
//
//						// --プレイヤーが障害物の左側にいたら-- //
//						else {
//							// --カメラに距離と半径を引いた数を加算-- //
//							player->AddPlayerPosX(-(radius - len));
//						}
//
//						// --状態をブースト状態に変更-- //
//						player->SetBoost();
//					}
//				}
//
//				// --プレイヤーと当たっている障害物がコインブロックだったら-- //
//				else if (stage->obstacles[j].GetBlockType() == CoinBlock) {
//					// --プレイヤーがオブジェクトの正面から当たっていたら-- //
//					if (BoxCenterCol(oldPlayerObj[i], obstacle) == true) {
//						// --プレイヤーの状態が通常状態だったら-- //
//						if (player->GetState() == Normal) {
//							// --プレイヤーと障害物のY軸距離-- //
//							float len = playerObj[i].pos.y - obstacle.pos.y;
//
//							// --プレイヤーと障害物のY軸半径を足した値-- //
//							float radius = playerObj[i].radiusY + obstacle.radiusY;
//
//							// --カメラに距離と半径を引いた数を加算-- //
//							Camera::AddScroll(radius - len);
//
//							// --状態をノックバック状態に変更-- //
//							player->SetKnock();
//						}
//
//						// --状態がブースト状態なら-- //
//						else if (player->GetState() == Boost) {
//							// --当たった障害物を消す-- //
//							stage->obstacles.erase(stage->obstacles.begin() + i);
//
//							// --現在のコイン数にプラス1-- //
//							stage->AddCoin();
//						}
//					}
//
//					// --横から当たっていたら-- //
//					else {
//						// --プレイヤーと障害物のX軸距離-- //
//						float len = abs(playerObj[i].pos.x - obstacle.pos.x);
//
//						// --プレイヤーと障害物のY軸半径を足した値-- //
//						float radius = playerObj[i].radiusX + obstacle.radiusX;
//
//						// --プレイヤーが障害物の右側にいたら-- //
//						if (playerObj[i].pos.x >= obstacle.pos.x) {
//							// --プレイヤーに距離と半径を引いた数を加算-- //
//							player->AddPlayerPosX(radius - len);
//						}
//
//						// --プレイヤーが障害物の左側にいたら-- //
//						else {
//							// --カメラに距離と半径を引いた数を加算-- //
//							player->AddPlayerPosX(-(radius - len));
//						}
//
//						// --状態をブースト状態に変更-- //
//						player->SetBoost();
//					}
//				}
//
//				// --プレイヤーと当たっている障害物がコインだったら-- //
//				else if (stage->obstacles[j].GetBlockType() == Coin) {
//					// --当たった障害物を消す-- //
//					stage->obstacles.erase(stage->obstacles.begin() + i);
//
//					// --現在のコイン数にプラス1-- //
//					stage->AddCoin();
//				}
//
//				break;
//			}
//		}
//	}
//
//	// --次のフレームで使うためにプレイヤーの情報を格納-- //
//	oldPlayerObj[0] = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player->GetPlayer1Obj().radius, player->GetPlayer1Obj().radius };
//	oldPlayerObj[1] = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player->GetPlayer2Obj().radius, player->GetPlayer2Obj().radius };
//}

void Collision::Update() {
	// --フラグがtrueになると多重ループを抜ける-- //
	bool isActive = false;

	// --プレイヤーの情報を格納-- //
	Box playerObj[2];
	playerObj[0] = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player->GetPlayer1Obj().radius, player->GetPlayer1Obj().radius };
	playerObj[1] = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player->GetPlayer2Obj().radius, player->GetPlayer2Obj().radius };

	// --障害物の数だけ当たり判定を行う-- //
	for (int i = 0; i < stage->obstacles.size(); i++) {
		// --障害物の情報を格納-- //
		Box obstacle = { stage->obstacles[i].GetPos(), stage->obstacles[i].GetRadiusX(), stage->obstacles[i].GetRadiusY() };

		// --プレイヤーの数分当たり判定を行う-- //
		for (int j = 0; j < 2; j++) {
			// --プレイヤーと障害物が当たっていたら-- //
			if (BoxCollision(playerObj[j], obstacle) == true) {
				// --プレイヤーと当たっている障害物がブロックだったら-- //
				if (stage->obstacles[i].GetBlockType() == Block) {
					// --プレイヤーがオブジェクトの正面から当たっていたら-- //
					if (BoxCenterCol(oldPlayerObj[j], obstacle) == true) {
						// --プレイヤーの状態が通常状態だったら-- //
						if (player->GetState() == Normal) {
							// --プレイヤーと障害物のY軸距離-- //
							float len = playerObj[j].pos.y - obstacle.pos.y;

							// --プレイヤーと障害物のY軸半径を足した値-- //
							float radius = playerObj[j].radiusY + obstacle.radiusY;

							// --カメラに距離と半径を引いた数を加算-- //
							Camera::AddScroll(radius - len);

							// --状態をノックバック状態に変更-- //
							player->SetKnock();
						}

						// --状態がブースト状態なら-- //
						else if (player->GetState() == Boost) {
							// --当たった障害物を消す-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);
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
							player->AddPlayerPosX(radius - len);
						}

						// --プレイヤーが障害物の左側にいたら-- //
						else {
							// --カメラに距離と半径を引いた数を加算-- //
							player->AddPlayerPosX(-(radius - len));
						}

						// --状態をブースト状態に変更-- //
						player->SetBoost();

						isActive = true;

						break;
					}
				}

				// --プレイヤーと当たっている障害物がコインブロックだったら-- //
				else if (stage->obstacles[i].GetBlockType() == CoinBlock) {
					// --プレイヤーがオブジェクトの正面から当たっていたら-- //
					if (BoxCenterCol(oldPlayerObj[j], obstacle) == true) {
						// --プレイヤーの状態が通常状態だったら-- //
						if (player->GetState() == Normal) {
							// --プレイヤーと障害物のY軸距離-- //
							float len = playerObj[j].pos.y - obstacle.pos.y;

							// --プレイヤーと障害物のY軸半径を足した値-- //
							float radius = playerObj[j].radiusY + obstacle.radiusY;

							// --カメラに距離と半径を引いた数を加算-- //
							Camera::AddScroll(radius - len);

							// --状態をノックバック状態に変更-- //
							player->SetKnock();
						}

						// --状態がブースト状態なら-- //
						else if (player->GetState() == Boost) {
							// --当たった障害物を消す-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);

							// --現在のコイン数にプラス1-- //
							stage->AddCoin();
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
							player->AddPlayerPosX(radius - len);
						}

						// --プレイヤーが障害物の左側にいたら-- //
						else {
							// --カメラに距離と半径を引いた数を加算-- //
							player->AddPlayerPosX(-(radius - len));
						}

						// --状態をブースト状態に変更-- //
						player->SetBoost();

						isActive = true;

						break;
					}
				}

				// --プレイヤーと当たっている障害物がコインだったら-- //
				else if (stage->obstacles[i].GetBlockType() == Coin) {
					// --当たった障害物を消す-- //
					stage->obstacles.erase(stage->obstacles.begin() + i);

					// --現在のコイン数にプラス1-- //
					stage->AddCoin();
				}
			}
		}

		// --多重ループを抜ける-- //
		if (isActive == true) {
			break;
		}
	}

	// --次のフレームで使うためにプレイヤーの情報を格納-- //
	oldPlayerObj[0] = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player->GetPlayer1Obj().radius, player->GetPlayer1Obj().radius };
	oldPlayerObj[1] = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player->GetPlayer2Obj().radius, player->GetPlayer2Obj().radius };
}