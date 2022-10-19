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

void Collision::Update() {

	// --�v���C���[�̏����i�[-- //
	BoxObj playerObj[2];
	playerObj[0] = player_->GetPlayer1Obj();
	playerObj[1] = player_->GetPlayer2Obj();
	playerObj[0].pos.y += Camera::GetScroll();
	playerObj[1].pos.y += Camera::GetScroll();

	// --�v���C���[�ƏՓ˂�����Q���̃f�[�^-- //
	std::vector<int> obsIndex;// -> �Փ˂����v�f�ԍ����L�^
	std::vector<int> obsXY;// ----> �Փ˂�����Q���ǂ̕�������Փ˂������L�^
	int closestObsIndex = 0;// ---> �Փ˂����Ȃ��ň�ԋ߂���Q���̗v�f�ԍ�
	float length = 100.0f;// -----> �Փ˂����v���C���[�Ə�Q���̍ł��Z���������L�^

	// --�v���C���[�Ə�Q�����Փ˂�����-- //
	bool isCol = false;

	// --�I�u�W�F�N�g�̋���-- //

	// --��Q���̐����������蔻����s��-- //
	for (int i = 0; i < stage_->obstacles_.size(); i++) {
		// --��Q���̏����i�[-- //
		BoxObj obstacle = stage_->obstacles_[i].GetBoxObj();

		// --�v���C���[�̐��������蔻����s��-- //
		for (int j = 0; j < 2; j++) {
			// --�v���C���[�Ə�Q�����������Ă�����-- //
			if (BoxCollision(playerObj[j], obstacle) == true) {
				isCol = true;
				obsIndex.push_back(i);

				// --�Փ˂�����Q�����R�C���Ȃ�-- //
				if (stage_->obstacles_[i].GetBlockType() == Coin) {
					obsXY.push_back(0);
				}

				// --�Փ˂�����Q���������u���b�N������-- //
				else if (stage_->obstacles_[i].GetBlockType() == DeathBlock) {
					player_->SetDeath();
					return;
				}

				// --�Փ˂�����Q��������ȊO�Ȃ�-- //
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

	// --�Փ˂����Ȃ�-- //
	if (isCol == true) {

		// --�c���ǂ��炩�瓖�����������W�v-- //
		int xCol = 0;
		int yCol = 0;
		for (int i = 0; i < obsXY.size(); i++) {
			if (obsXY[i] == 1) yCol += 1;
			else if (obsXY[i] == 2) xCol += 1;
		}

		// --�v���C���[���u�[�X�g��ԂȂ�-- //
		if (player_->GetState() == Boost) {
			// --���ł�������Փ˂��Ă�����u�[�X�g��Ԃɂ���-- //
			if (xCol > 0) player_->SetBoost();

			// --�Փ˂�����Q�������[�v-- //
			for (int i = obsIndex.size() - 1; i >= 0; i--) {

				// --���ʂ��瓖�����Ă�����-- //
				if (obsXY[i] == 1) {
					if (stage_->obstacles_[obsIndex[i]].GetBlockType() == CoinBlock) {
						// --���݂̃R�C�����Ƀv���X1-- //
						stage_->AddCoin();
					}
					stage_->obstacles_.erase(stage_->obstacles_.begin() + obsIndex[i]);
					obsIndex.erase(obsIndex.begin() + i);
					obsXY.erase(obsXY.begin() + i);
				}

				// --�Փ˂����̂��R�C���Ȃ�-- //
				else if (obsXY[i] == 0) {
					// --���݂̃R�C�����Ƀv���X1-- //
					stage_->AddCoin();
					stage_->obstacles_.erase(stage_->obstacles_.begin() + obsIndex[i]);
					obsIndex.erase(obsIndex.begin() + i);
					obsXY.erase(obsXY.begin() + i);
				}
			}
		}


		// --�v���C���[���ʏ��ԂȂ�-- //
		else if (player_->GetState() == Normal) {
			// --�v���C���[�Ɉ�ԋ߂���Q���ɏՓ˂����̂����ʂ���Ȃ�
			if (obsXY[closestObsIndex] == 1) player_->SetKnock();

			// --�Փ˂����̂�������Ȃ�-- //
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

		else if (player_->GetState() == Knock) {
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

		// --�����߂�����-- //
		for (int i = 0; i < obsIndex.size(); i++) {
			for (int j = 0; j < 2; j++) {
				// --�ŐV�̃v���C���[�̏��i�[-- //
				playerObj[0] = player_->GetPlayer1Obj();
				playerObj[1] = player_->GetPlayer2Obj();
				playerObj[0].pos.y += Camera::GetScroll();
				playerObj[1].pos.y += Camera::GetScroll();

				// --��Q���̏����i�[-- //
				BoxObj obstacle = stage_->obstacles_[obsIndex[i]].GetBoxObj();

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
							player_->object_[0].pos.x += radius - len;
							player_->object_[1].pos.x += radius - len;
						}

						// --�v���C���[����Q���̍����ɂ�����-- //
						else if(playerObj[j].pos.x < obstacle.pos.x) {
							// --�J�����ɋ����Ɣ��a���������������Z-- //
							player_->object_[0].pos.x -= radius - len;
							player_->object_[1].pos.x -= radius - len;
						}
					}

					else if (player_->GetState() != Boost) {
						// --�v���C���[�Ə�Q����Y������-- //
						float len = abs(playerObj[j].pos.y - obstacle.pos.y);

						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
						float radius = playerObj[j].radiusY + obstacle.radiusY;

						// --�v���C���[����Q���̉����ɂ�����-- //
						if (playerObj[j].pos.y >= obstacle.pos.y) {
							// --�J�����ɋ����Ɣ��a���������������Z-- //
							Camera::AddScroll(radius - len);
						}

						// --�v���C���[����Q���̍����ɂ�����-- //
						else if (playerObj[j].pos.y < obstacle.pos.y) {
							// --�J�����ɋ����Ɣ��a���������������Z-- //
							Camera::AddScroll(-(radius - len));
						}
					}
				}
			}
		}
	}
}