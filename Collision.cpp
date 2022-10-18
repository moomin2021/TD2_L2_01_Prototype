#include "Collision.h"
#include "Camera.h"
#include "DxLib.h"

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

int BoxXYCol(Box& box1, Box& box2) {
	float len1 = abs((box1.pos.y - box1.radiusY) - (box2.pos.y + box2.radiusY));
	float len2 = abs((box1.pos.x - box1.radiusX) - (box2.pos.x + box2.radiusX));
	float len3 = abs((box1.pos.x + box1.radiusX) - (box2.pos.x - box2.radiusX));

	if (len1 < len2) {
		if (len1 < len3) return 1;
	}
	return 2;
}

// --�C���X�^���X��NULL����-- //
Collision* Collision::myInstance_ = nullptr;

// --�C���X�^���X�ǂݍ���-- //
Collision* Collision::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance_ == nullptr) myInstance_ = new Collision();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance_;
}

// --���������-- //
void Collision::Release() {
	// --���������-- //
	delete myInstance_;

	// --NULL����-- //
	myInstance_ = nullptr;
}

// --�R���X�g���N�^
Collision::Collision() {
	player_ = Player::GetInstance();
	stage_ = StageManager::GetInstance();
}

// --�f�X�g���N�^
Collision::~Collision() {

}

// --����������
void Collision::Initialize() {

}

//void Collision::Update() {
//	// --�t���O��true�ɂȂ�Ƒ��d���[�v�𔲂���-- //
//	bool isActive = false;
//
//	// --�v���C���[�̏����i�[-- //
//	Box playerObj[2];
//	playerObj[0] = { {player_->GetPlayer1Obj().pos.x, player_->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer1Obj().radius, player_->GetPlayer1Obj().radius };
//	playerObj[1] = { {player_->GetPlayer2Obj().pos.x, player_->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer2Obj().radius, player_->GetPlayer2Obj().radius };
//
//	// --��Q���̐����������蔻����s��-- //
//	for (int i = 0; i < stage_->obstacles_.size(); i++) {
//		// --��Q���̏����i�[-- //
//		Box obstacle = { stage_->obstacles_[i].GetPos(), stage_->obstacles_[i].GetRadiusX(), stage_->obstacles_[i].GetRadiusY() };
//
//		// --�v���C���[�̐��������蔻����s��-- //
//		for (int j = 0; j < 2; j++) {
//			// --�v���C���[�Ə�Q�����������Ă�����-- //
//			if (BoxCollision(playerObj[j], obstacle) == true) {
//				// --�v���C���[�Ɠ������Ă����Q�����u���b�N��������-- //
//				if (stage_->obstacles_[i].GetBlockType() == Block) {
//					// --�v���C���[���I�u�W�F�N�g�̐��ʂ��瓖�����Ă�����-- //
//					if (BoxCenterCol(oldPlayerObj_[j], obstacle) == true) {
//						// --�v���C���[�̏�Ԃ��ʏ��Ԃ�������-- //
//						if (player_->GetState() == Normal) {
//							// --�v���C���[�Ə�Q����Y������-- //
//							float len = playerObj[j].pos.y - obstacle.pos.y;
//
//							// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//							float radius = playerObj[j].radiusY + obstacle.radiusY;
//
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							Camera::AddScroll(radius - len);
//
//							// --��Ԃ��m�b�N�o�b�N��ԂɕύX-- //
//							player_->SetKnock();
//						}
//
//						// --��Ԃ��u�[�X�g��ԂȂ�-- //
//						else if (player_->GetState() == Boost) {
//							// --����������Q��������-- //
//							stage_->obstacles_.erase(stage_->obstacles_.begin() + i);
//						}
//					}
//
//					// --�����瓖�����Ă�����-- //
//					else {
//						// --�v���C���[�Ə�Q����X������-- //
//						float len = abs(playerObj[j].pos.x - obstacle.pos.x);
//
//						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//						float radius = playerObj[j].radiusX + obstacle.radiusX;
//
//						// --�v���C���[����Q���̉E���ɂ�����-- //
//						if (playerObj[j].pos.x >= obstacle.pos.x) {
//							// --�v���C���[�ɋ����Ɣ��a���������������Z-- //
//							player_->AddPlayerPosX(radius - len);
//						}
//
//						// --�v���C���[����Q���̍����ɂ�����-- //
//						else {
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							player_->AddPlayerPosX(-(radius - len));
//						}
//
//						if (player_->GetState() != Knock) {
//							// --��Ԃ��u�[�X�g��ԂɕύX-- //
//							player_->SetBoost();
//						}
//
//						isActive = true;
//
//						break;
//					}
//				}
//
//				// --�v���C���[�Ɠ������Ă����Q�����R�C���u���b�N��������-- //
//				else if (stage_->obstacles_[i].GetBlockType() == CoinBlock) {
//					// --�v���C���[���I�u�W�F�N�g�̐��ʂ��瓖�����Ă�����-- //
//					if (BoxCenterCol(oldPlayerObj_[j], obstacle) == true) {
//						// --�v���C���[�̏�Ԃ��ʏ��Ԃ�������-- //
//						if (player_->GetState() == Normal) {
//							// --�v���C���[�Ə�Q����Y������-- //
//							float len = playerObj[j].pos.y - obstacle.pos.y;
//
//							// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//							float radius = playerObj[j].radiusY + obstacle.radiusY;
//
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							Camera::AddScroll(radius - len);
//
//							// --��Ԃ��m�b�N�o�b�N��ԂɕύX-- //
//							player_->SetKnock();
//						}
//
//						// --��Ԃ��u�[�X�g��ԂȂ�-- //
//						else if (player_->GetState() == Boost) {
//							// --����������Q��������-- //
//							stage_->obstacles_.erase(stage_->obstacles_.begin() + i);
//
//							// --���݂̃R�C�����Ƀv���X1-- //
//							stage_->AddCoin();
//						}
//					}
//
//					// --�����瓖�����Ă�����-- //
//					else {
//						// --�v���C���[�Ə�Q����X������-- //
//						float len = abs(playerObj[j].pos.x - obstacle.pos.x);
//
//						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
//						float radius = playerObj[j].radiusX + obstacle.radiusX;
//
//						// --�v���C���[����Q���̉E���ɂ�����-- //
//						if (playerObj[j].pos.x >= obstacle.pos.x) {
//							// --�v���C���[�ɋ����Ɣ��a���������������Z-- //
//							player_->AddPlayerPosX(radius - len);
//						}
//
//						// --�v���C���[����Q���̍����ɂ�����-- //
//						else {
//							// --�J�����ɋ����Ɣ��a���������������Z-- //
//							player_->AddPlayerPosX(-(radius - len));
//						}
//
//						// --��Ԃ��u�[�X�g��ԂɕύX-- //
//						player_->SetBoost();
//
//						isActive = true;
//
//						break;
//					}
//				}
//
//				// --�v���C���[�Ɠ������Ă����Q�����R�C����������-- //
//				else if (stage_->obstacles_[i].GetBlockType() == Coin) {
//					// --����������Q��������-- //
//					stage_->obstacles_.erase(stage_->obstacles_.begin() + i);
//
//					// --���݂̃R�C�����Ƀv���X1-- //
//					stage_->AddCoin();
//				}
//
//				// --�v���C���[�Ɠ������Ă����Q���������u���b�N��������-- //
//				else if (stage_->obstacles_[i].GetBlockType() == DeathBlock) {
//					player_->SetDeath();
//				}
//			}
//		}
//
//		// --���d���[�v�𔲂���-- //
//		if (isActive == true) {
//			break;
//		}
//	}
//
//	// --���̃t���[���Ŏg�����߂Ƀv���C���[�̏����i�[-- //
//	oldPlayerObj_[0] = { {player_->GetPlayer1Obj().pos.x, player_->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer1Obj().radius, player_->GetPlayer1Obj().radius };
//	oldPlayerObj_[1] = { {player_->GetPlayer2Obj().pos.x, player_->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer2Obj().radius, player_->GetPlayer2Obj().radius };
//}

void Collision::Update() {

	// --�v���C���[�̏����i�[-- //
	Box playerObj[2];
	playerObj[0] = { {player_->GetPlayer1Obj().pos.x, player_->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer1Obj().radius, player_->GetPlayer1Obj().radius };
	playerObj[1] = { {player_->GetPlayer2Obj().pos.x, player_->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer2Obj().radius, player_->GetPlayer2Obj().radius };

	// ��ԋ߂��������Ă���I�u�W�F�N�g�̗v�f��-- //
	std::vector<int> obsIndex;
	std::vector<int> obsXY;
	int closestObsIndex = 0;
	float length = 100.0f;
	bool isCol = false;

	// --�I�u�W�F�N�g�̋���-- //

	// --��Q���̐����������蔻����s��-- //
	for (int i = 0; i < stage_->obstacles_.size(); i++) {
		// --��Q���̏����i�[-- //
		Box obstacle = { stage_->obstacles_[i].GetPos(), stage_->obstacles_[i].GetRadiusX(), stage_->obstacles_[i].GetRadiusY() };

		// --�v���C���[�̐��������蔻����s��-- //
		for (int j = 0; j < 2; j++) {
			// --�v���C���[�Ə�Q�����������Ă�����-- //
			if (BoxCollision(playerObj[j], obstacle) == true) {
				isCol = true;
				obsIndex.push_back(i);
				if (stage_->obstacles_[i].GetBlockType() == Coin) {
					obsXY.push_back(0);
				}
				else if (stage_->obstacles_[i].GetBlockType() == DeathBlock) {
					player_->SetDeath();
					return;
				}
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

	if (isCol == true) {

		//float nyum;
		//if (fmodf(playerObj[0].pos.x, 0.1f) != 0) {
		//	nyum = fmodf(playerObj[0].pos.x, 0.1f);
		//}

		int xCol = 0;
		int yCol = 0;
		for (int i = 0; i < obsXY.size(); i++) {
			if (obsXY[i] == 1) yCol += 1;
			else if (obsXY[i] == 2) xCol += 1;
		}

		if (player_->GetState() == Boost) {
			if (xCol > 0) player_->SetBoost();

			for (int i = obsIndex.size() - 1; i >= 0; i--) {
				if (obsXY[i] == 1) {
					if (stage_->obstacles_[obsIndex[i]].GetBlockType() == CoinBlock) {
						// --���݂̃R�C�����Ƀv���X1-- //
						stage_->AddCoin();
					}
					stage_->obstacles_.erase(stage_->obstacles_.begin() + obsIndex[i]);
					obsIndex.erase(obsIndex.begin() + i);
					obsXY.erase(obsXY.begin() + i);
				}

				else if (obsXY[i] == 0) {
					// --���݂̃R�C�����Ƀv���X1-- //
					stage_->AddCoin();
					stage_->obstacles_.erase(stage_->obstacles_.begin() + obsIndex[i]);
					obsIndex.erase(obsIndex.begin() + i);
					obsXY.erase(obsXY.begin() + i);
				}
			}
		}

		else if (player_->GetState() == Normal) {
			if (obsXY[closestObsIndex] == 1) player_->SetKnock();
			else if(obsXY[closestObsIndex] == 2) player_->SetBoost();

			for (int i = obsIndex.size() - 1; i >= 0; i--) {
				if (obsXY[i] == 0) {
					// --���݂̃R�C�����Ƀv���X1-- //
					stage_->AddCoin();
					stage_->obstacles_.erase(stage_->obstacles_.begin() + obsIndex[i]);
					obsIndex.erase(obsIndex.begin() + i);
					obsXY.erase(obsXY.begin() + i);
				}
			}
		}

		for (int i = 0; i < obsIndex.size(); i++) {
			for (int j = 0; j < 2; j++) {
				// --��Q���̏����i�[-- //
				Box obstacle = { stage_->obstacles_[obsIndex[i]].GetPos(), stage_->obstacles_[obsIndex[i]].GetRadiusX(), stage_->obstacles_[obsIndex[i]].GetRadiusY() };

				// --�v���C���[�Ə�Q�����������Ă�����-- //
				if (BoxCollision(playerObj[j], obstacle) == true) {
					if (BoxXYCol(playerObj[j], obstacle) == 2) {
						// --�v���C���[�Ə�Q����X������-- //
						float len = abs(playerObj[j].pos.x - obstacle.pos.x);

						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
						float radius = playerObj[j].radiusX + obstacle.radiusX;

						// --�v���C���[����Q���̉E���ɂ�����-- //
						if (playerObj[j].pos.x >= obstacle.pos.x) {
							// --�v���C���[�ɋ����Ɣ��a���������������Z-- //
							//player_->AddPlayerPosX(radius - len);
							player_->player_[0].pos.x += radius - len;
							player_->player_[1].pos.x += radius - len;
						}

						// --�v���C���[����Q���̍����ɂ�����-- //
						else if(playerObj[j].pos.x < obstacle.pos.x) {
							// --�J�����ɋ����Ɣ��a���������������Z-- //
							//player_->AddPlayerPosX(-(radius - len));
							player_->player_[0].pos.x -= radius - len;
							player_->player_[1].pos.x -= radius - len;
						}
					}

					else if (player_->GetState() != Boost) {
						// --�v���C���[�Ə�Q����Y������-- //
						float len = playerObj[j].pos.y - obstacle.pos.y;

						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
						float radius = playerObj[j].radiusY + obstacle.radiusY;

						// --�J�����ɋ����Ɣ��a���������������Z-- //
						Camera::AddScroll(radius - len);
					}
				}

				playerObj[0] = { {player_->GetPlayer1Obj().pos.x, player_->GetPlayer1Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer1Obj().radius, player_->GetPlayer1Obj().radius };
				playerObj[1] = { {player_->GetPlayer2Obj().pos.x, player_->GetPlayer2Obj().pos.y + Camera::GetScroll()}, player_->GetPlayer2Obj().radius, player_->GetPlayer2Obj().radius };
			}
		}
	}
}