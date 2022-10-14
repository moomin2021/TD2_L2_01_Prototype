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

// --�C���X�^���X��NULL����-- //
Collision* Collision::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
Collision* Collision::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new Collision();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --���������-- //
void Collision::Release() {
	// --���������-- //
	delete myInstance;

	// --NULL����-- //
	myInstance = nullptr;
}

// --�R���X�g���N�^
Collision::Collision() {
	player = Player::GetInstance();
	stage = StageManager::GetInstance();
}

// --�f�X�g���N�^
Collision::~Collision() {

}

// --����������
void Collision::Initialize() {

}

// --�X�V����-- //
//void Collision::Update() {
//	// --�v���C���[�̓����蔻��t���O��ON��������-- //
//	if (player->GetCollisionFlag() == true) {
//		// --���Ɣ��̃v���C���[�̍��W�Ɣ��a�̏����i�[-- //
//		Box player1Obj = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player->GetPlayer1Obj().radius, player->GetPlayer1Obj().radius };
//		Box player2Obj = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player->GetPlayer2Obj().radius, player->GetPlayer2Obj().radius };
//
//		// --��Q���̐��������蔻����Ƃ�-- //
//		for (int i = 0; i < stage->obstacles.size(); i++) {
//			// --��Q���̍��W�Ɣ��a���i�[-- //
//			Box obstacle = { stage->obstacles[i].GetPos(), stage->obstacles[i].GetRadiusX(), stage->obstacles[i].GetRadiusY() };
//
//			// --���v���C���[�̓����蔻��-- //
//			if (BoxCollision(player1Obj, obstacle)) {
//
//				// --����������Q�������F��������-- //
//				if (stage->obstacles[i].GetBlockType() == Block) {
//					// --���ʂ��瓖�����Ă�����-- //
//					if (BoxCenterCol(oldPlayer1Box, obstacle)) {
//						// --�ʏ��ԂȂ�-- //
//						if (player->GetState() == Normal) {
//							// --�v���C���[�Ə�Q����Y������-- //
//							float len = player1Obj.pos.y - obstacle.pos.y;
//
//							// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//							float radius = player1Obj.radiusY + obstacle.radiusY;
//
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							Camera::AddScroll(radius - len);
//
//							// --��Ԃ��m�b�N�o�b�N��ԂɕύX-- //
//							player->SetKnock();
//
//							// --����������Q��������-- //
//							//stage->obstacles.erase(stage->obstacles.begin() + i);
//						}
//
//						// --��Ԃ��u�[�X�g��ԂȂ�-- //
//						else if (player->GetState() == Boost) {
//							// --����������Q��������-- //
//							stage->obstacles.erase(stage->obstacles.begin() + i);
//						}
//					}
//
//					// --�����瓖�����Ă�����
//					else {
//						// --�v���C���[�Ə�Q����X������-- //
//						float len = abs(player1Obj.pos.x - obstacle.pos.x);
//
//						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//						float radius = player2Obj.radiusX + obstacle.radiusX;
//
//						// --�v���C���[����Q���̉E���ɂ�����-- //
//						if (player1Obj.pos.x >= obstacle.pos.x) {
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							player->AddPlayerPosX(radius - len);
//						}
//
//						// --�v���C���[����Q���̍����ɂ�����-- //
//						else {
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							player->AddPlayerPosX(-(radius - len));
//						}
//
//						// --��Ԃ��u�[�X�g��ԂɕύX-- //
//						player->SetBoost();
//					}
//
//					break;
//				}
//			}
//
//			// --���v���C���[�̓����蔻��-- //
//			if (BoxCollision(player2Obj, obstacle)) {
//
//				// --����������Q�������F��������-- //
//				if (stage->obstacles[i].GetBlockType() == Block) {
//					// --���ʂ��瓖�����Ă�����-- //
//					if (BoxCenterCol(oldPlayer2Box, obstacle)) {
//						// --�ʏ��ԂȂ�-- //
//						if (player->GetState() == Normal) {
//							// --�v���C���[�Ə�Q����Y������-- //
//							float len = player2Obj.pos.y - obstacle.pos.y;
//
//							// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//							float radius = player2Obj.radiusY + obstacle.radiusY;
//
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							Camera::AddScroll(radius - len);
//
//							// --��Ԃ��m�b�N�o�b�N��ԂɕύX-- //
//							player->SetKnock();
//
//							// --����������Q��������-- //
//							//stage->obstacles.erase(stage->obstacles.begin() + i);
//						}
//
//						// --��Ԃ��u�[�X�g��ԂȂ�-- //
//						else if (player->GetState() == Boost) {
//							// --����������Q��������-- //
//							stage->obstacles.erase(stage->obstacles.begin() + i);
//						}
//					}
//
//					// --�����瓖�����Ă�����
//					else {
//						// --�v���C���[�Ə�Q����X������-- //
//						float len = abs(player2Obj.pos.x - obstacle.pos.x);
//
//						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//						float radius = player2Obj.radiusX + obstacle.radiusX;
//
//						// --�v���C���[����Q���̉E���ɂ�����-- //
//						if (player2Obj.pos.x >= obstacle.pos.x) {
//							// --�v���C���[�ɋ����Ɣ��a���������������Z-- //
//							player->AddPlayerPosX(radius - len);
//						}
//
//						// --�v���C���[����Q���̍����ɂ�����-- //
//						else {
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							player->AddPlayerPosX(-(radius - len));
//						}
//
//						// --��Ԃ��u�[�X�g��ԂɕύX-- //
//						player->SetBoost();
//					}
//
//					break;
//				}
//			}
//		}
//	}
//
//	// --�v���C���[�̏����i�[-- //
//	oldPlayer1Box = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, 32, 32 };
//	oldPlayer2Box = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, 32, 32 };
//}

//void Collision::Update() {
//	// --�v���C���[�̏����i�[-- //
//	Box playerObj[2];
//	playerObj[0] = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player->GetPlayer1Obj().radius, player->GetPlayer1Obj().radius };
//	playerObj[1] = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player->GetPlayer2Obj().radius, player->GetPlayer2Obj().radius };
//
//	// --�v���C���[�I�u�W�F�N�g�̐��������蔻����Ƃ�-- //
//	for (int i = 0; i < 2; i++) {
//		// --��Q���̐��������蔻����Ƃ�-- //
//		for (int j = 0; j < stage->obstacles.size(); j++) {
//			// --��Q���̏����i�[-- //
//			Box obstacle = { stage->obstacles[j].GetPos(), stage->obstacles[j].GetRadiusX(), stage->obstacles[j].GetRadiusY() };
//
//			// --�v���C���[�Ə�Q�����������Ă�����-- //
//			if (BoxCollision(playerObj[i], obstacle) == true) {
//				// --�v���C���[�Ɠ������Ă����Q�����u���b�N��������-- //
//				if (stage->obstacles[j].GetBlockType() == Block) {
//					// --�v���C���[���I�u�W�F�N�g�̐��ʂ��瓖�����Ă�����-- //
//					if (BoxCenterCol(oldPlayerObj[i], obstacle) == true) {
//						// --�v���C���[�̏�Ԃ��ʏ��Ԃ�������-- //
//						if (player->GetState() == Normal) {
//							// --�v���C���[�Ə�Q����Y������-- //
//							float len = playerObj[i].pos.y - obstacle.pos.y;
//
//							// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//							float radius = playerObj[i].radiusY + obstacle.radiusY;
//
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							Camera::AddScroll(radius - len);
//
//							// --��Ԃ��m�b�N�o�b�N��ԂɕύX-- //
//							player->SetKnock();
//						}
//
//						// --��Ԃ��u�[�X�g��ԂȂ�-- //
//						else if (player->GetState() == Boost) {
//							// --����������Q��������-- //
//							stage->obstacles.erase(stage->obstacles.begin() + i);
//						}
//					}
//
//					// --�����瓖�����Ă�����-- //
//					else {
//						// --�v���C���[�Ə�Q����X������-- //
//						float len = abs(playerObj[i].pos.x - obstacle.pos.x);
//
//						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//						float radius = playerObj[i].radiusX + obstacle.radiusX;
//
//						// --�v���C���[����Q���̉E���ɂ�����-- //
//						if (playerObj[i].pos.x >= obstacle.pos.x) {
//							// --�v���C���[�ɋ����Ɣ��a���������������Z-- //
//							player->AddPlayerPosX(radius - len);
//						}
//
//						// --�v���C���[����Q���̍����ɂ�����-- //
//						else {
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							player->AddPlayerPosX(-(radius - len));
//						}
//
//						// --��Ԃ��u�[�X�g��ԂɕύX-- //
//						player->SetBoost();
//					}
//				}
//
//				// --�v���C���[�Ɠ������Ă����Q�����R�C���u���b�N��������-- //
//				else if (stage->obstacles[j].GetBlockType() == CoinBlock) {
//					// --�v���C���[���I�u�W�F�N�g�̐��ʂ��瓖�����Ă�����-- //
//					if (BoxCenterCol(oldPlayerObj[i], obstacle) == true) {
//						// --�v���C���[�̏�Ԃ��ʏ��Ԃ�������-- //
//						if (player->GetState() == Normal) {
//							// --�v���C���[�Ə�Q����Y������-- //
//							float len = playerObj[i].pos.y - obstacle.pos.y;
//
//							// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//							float radius = playerObj[i].radiusY + obstacle.radiusY;
//
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							Camera::AddScroll(radius - len);
//
//							// --��Ԃ��m�b�N�o�b�N��ԂɕύX-- //
//							player->SetKnock();
//						}
//
//						// --��Ԃ��u�[�X�g��ԂȂ�-- //
//						else if (player->GetState() == Boost) {
//							// --����������Q��������-- //
//							stage->obstacles.erase(stage->obstacles.begin() + i);
//
//							// --���݂̃R�C�����Ƀv���X1-- //
//							stage->AddCoin();
//						}
//					}
//
//					// --�����瓖�����Ă�����-- //
//					else {
//						// --�v���C���[�Ə�Q����X������-- //
//						float len = abs(playerObj[i].pos.x - obstacle.pos.x);
//
//						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//						float radius = playerObj[i].radiusX + obstacle.radiusX;
//
//						// --�v���C���[����Q���̉E���ɂ�����-- //
//						if (playerObj[i].pos.x >= obstacle.pos.x) {
//							// --�v���C���[�ɋ����Ɣ��a���������������Z-- //
//							player->AddPlayerPosX(radius - len);
//						}
//
//						// --�v���C���[����Q���̍����ɂ�����-- //
//						else {
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							player->AddPlayerPosX(-(radius - len));
//						}
//
//						// --��Ԃ��u�[�X�g��ԂɕύX-- //
//						player->SetBoost();
//					}
//				}
//
//				// --�v���C���[�Ɠ������Ă����Q�����R�C����������-- //
//				else if (stage->obstacles[j].GetBlockType() == Coin) {
//					// --����������Q��������-- //
//					stage->obstacles.erase(stage->obstacles.begin() + i);
//
//					// --���݂̃R�C�����Ƀv���X1-- //
//					stage->AddCoin();
//				}
//
//				break;
//			}
//		}
//	}
//
//	// --���̃t���[���Ŏg�����߂Ƀv���C���[�̏����i�[-- //
//	oldPlayerObj[0] = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player->GetPlayer1Obj().radius, player->GetPlayer1Obj().radius };
//	oldPlayerObj[1] = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player->GetPlayer2Obj().radius, player->GetPlayer2Obj().radius };
//}

void Collision::Update() {
	// --�t���O��true�ɂȂ�Ƒ��d���[�v�𔲂���-- //
	bool isActive = false;

	// --�v���C���[�̏����i�[-- //
	Box playerObj[2];
	playerObj[0] = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player->GetPlayer1Obj().radius, player->GetPlayer1Obj().radius };
	playerObj[1] = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player->GetPlayer2Obj().radius, player->GetPlayer2Obj().radius };

	// --��Q���̐����������蔻����s��-- //
	for (int i = 0; i < stage->obstacles.size(); i++) {
		// --��Q���̏����i�[-- //
		Box obstacle = { stage->obstacles[i].GetPos(), stage->obstacles[i].GetRadiusX(), stage->obstacles[i].GetRadiusY() };

		// --�v���C���[�̐��������蔻����s��-- //
		for (int j = 0; j < 2; j++) {
			// --�v���C���[�Ə�Q�����������Ă�����-- //
			if (BoxCollision(playerObj[j], obstacle) == true) {
				// --�v���C���[�Ɠ������Ă����Q�����u���b�N��������-- //
				if (stage->obstacles[i].GetBlockType() == Block) {
					// --�v���C���[���I�u�W�F�N�g�̐��ʂ��瓖�����Ă�����-- //
					if (BoxCenterCol(oldPlayerObj[j], obstacle) == true) {
						// --�v���C���[�̏�Ԃ��ʏ��Ԃ�������-- //
						if (player->GetState() == Normal) {
							// --�v���C���[�Ə�Q����Y������-- //
							float len = playerObj[j].pos.y - obstacle.pos.y;

							// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
							float radius = playerObj[j].radiusY + obstacle.radiusY;

							// --�J�����ɋ����Ɣ��a���������������Z-- //
							Camera::AddScroll(radius - len);

							// --��Ԃ��m�b�N�o�b�N��ԂɕύX-- //
							player->SetKnock();
						}

						// --��Ԃ��u�[�X�g��ԂȂ�-- //
						else if (player->GetState() == Boost) {
							// --����������Q��������-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}
					}

					// --�����瓖�����Ă�����-- //
					else {
						// --�v���C���[�Ə�Q����X������-- //
						float len = abs(playerObj[j].pos.x - obstacle.pos.x);

						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
						float radius = playerObj[j].radiusX + obstacle.radiusX;

						// --�v���C���[����Q���̉E���ɂ�����-- //
						if (playerObj[j].pos.x >= obstacle.pos.x) {
							// --�v���C���[�ɋ����Ɣ��a���������������Z-- //
							player->AddPlayerPosX(radius - len);
						}

						// --�v���C���[����Q���̍����ɂ�����-- //
						else {
							// --�J�����ɋ����Ɣ��a���������������Z-- //
							player->AddPlayerPosX(-(radius - len));
						}

						// --��Ԃ��u�[�X�g��ԂɕύX-- //
						player->SetBoost();

						isActive = true;

						break;
					}
				}

				// --�v���C���[�Ɠ������Ă����Q�����R�C���u���b�N��������-- //
				else if (stage->obstacles[i].GetBlockType() == CoinBlock) {
					// --�v���C���[���I�u�W�F�N�g�̐��ʂ��瓖�����Ă�����-- //
					if (BoxCenterCol(oldPlayerObj[j], obstacle) == true) {
						// --�v���C���[�̏�Ԃ��ʏ��Ԃ�������-- //
						if (player->GetState() == Normal) {
							// --�v���C���[�Ə�Q����Y������-- //
							float len = playerObj[j].pos.y - obstacle.pos.y;

							// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
							float radius = playerObj[j].radiusY + obstacle.radiusY;

							// --�J�����ɋ����Ɣ��a���������������Z-- //
							Camera::AddScroll(radius - len);

							// --��Ԃ��m�b�N�o�b�N��ԂɕύX-- //
							player->SetKnock();
						}

						// --��Ԃ��u�[�X�g��ԂȂ�-- //
						else if (player->GetState() == Boost) {
							// --����������Q��������-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);

							// --���݂̃R�C�����Ƀv���X1-- //
							stage->AddCoin();
						}
					}

					// --�����瓖�����Ă�����-- //
					else {
						// --�v���C���[�Ə�Q����X������-- //
						float len = abs(playerObj[j].pos.x - obstacle.pos.x);

						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
						float radius = playerObj[j].radiusX + obstacle.radiusX;

						// --�v���C���[����Q���̉E���ɂ�����-- //
						if (playerObj[j].pos.x >= obstacle.pos.x) {
							// --�v���C���[�ɋ����Ɣ��a���������������Z-- //
							player->AddPlayerPosX(radius - len);
						}

						// --�v���C���[����Q���̍����ɂ�����-- //
						else {
							// --�J�����ɋ����Ɣ��a���������������Z-- //
							player->AddPlayerPosX(-(radius - len));
						}

						// --��Ԃ��u�[�X�g��ԂɕύX-- //
						player->SetBoost();

						isActive = true;

						break;
					}
				}

				// --�v���C���[�Ɠ������Ă����Q�����R�C����������-- //
				else if (stage->obstacles[i].GetBlockType() == Coin) {
					// --����������Q��������-- //
					stage->obstacles.erase(stage->obstacles.begin() + i);

					// --���݂̃R�C�����Ƀv���X1-- //
					stage->AddCoin();
				}
			}
		}

		// --���d���[�v�𔲂���-- //
		if (isActive == true) {
			break;
		}
	}

	// --���̃t���[���Ŏg�����߂Ƀv���C���[�̏����i�[-- //
	oldPlayerObj[0] = { {player->GetPlayer1Obj().pos.x, player->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player->GetPlayer1Obj().radius, player->GetPlayer1Obj().radius };
	oldPlayerObj[1] = { {player->GetPlayer2Obj().pos.x, player->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player->GetPlayer2Obj().radius, player->GetPlayer2Obj().radius };
}