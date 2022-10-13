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
void Collision::Update() {
	// --�v���C���[�̓����蔻��t���O��ON��������-- //
	if (player->GetCollisionFlag() == true) {
		// --���Ɣ��̃v���C���[�̍��W�Ɣ��a�̏����i�[-- //
		Box blackObj = { {player->GetBlackObj().pos.x, player->GetBlackObj().pos.y + Camera::GetScroll()}, player->GetBlackObj().radius, player->GetBlackObj().radius };
		Box whiteObj = { {player->GetWhiteObj().pos.x, player->GetWhiteObj().pos.y + Camera::GetScroll()}, player->GetWhiteObj().radius, player->GetWhiteObj().radius };

		// --��Q���̐��������蔻����Ƃ�-- //
		for (int i = 0; i < stage->obstacles.size(); i++) {
			// --��Q���̍��W�Ɣ��a���i�[-- //
			Box obstacle = { stage->obstacles[i].GetPos(), stage->obstacles[i].GetRadiusX(), stage->obstacles[i].GetRadiusY() };

			// --���v���C���[�̓����蔻��-- //
			if (BoxCollision(whiteObj, obstacle)) {

				// --����������Q�������F��������-- //
				if (stage->obstacles[i].GetColor() == 0x000000) {
					// --���ʂ��瓖�����Ă�����-- //
					if (BoxCenterCol(oldWhiteBox, obstacle)) {
						// --�ʏ��ԂȂ�-- //
						if (player->GetState() == Normal) {
							// --�v���C���[�Ə�Q����Y������-- //
							float len = whiteObj.pos.y - obstacle.pos.y;

							// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
							float radius = whiteObj.radiusY + obstacle.radiusY;

							// --�J�����ɋ����Ɣ��a���������������Z-- //
							Camera::AddScroll(radius - len);

							// --��Ԃ��m�b�N�o�b�N��ԂɕύX-- //
							player->SetKnock();

							// --����������Q��������-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}

						// --��Ԃ��u�[�X�g��ԂȂ�-- //
						else if (player->GetState() == Boost) {
							// --����������Q��������-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}
					}

					// --�����瓖�����Ă�����
					else {
						// --�v���C���[�Ə�Q����X������-- //
						float len = abs(whiteObj.pos.x - obstacle.pos.x);

						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
						float radius = whiteObj.radiusX + obstacle.radiusX;

						// --�v���C���[����Q���̉E���ɂ�����-- //
						if (whiteObj.pos.x >= obstacle.pos.x) {
							// --�J�����ɋ����Ɣ��a���������������Z-- //
							player->AddPlayerPosX(radius - len);
						}

						// --�v���C���[����Q���̍����ɂ�����-- //
						else {
							// --�J�����ɋ����Ɣ��a���������������Z-- //
							player->AddPlayerPosX(-(radius - len));
						}

						// --��Ԃ��u�[�X�g��ԂɕύX-- //
						player->SetBoost();
					}

					break;
				}
			}

			// --���v���C���[�̓����蔻��-- //
			if (BoxCollision(blackObj, obstacle)) {

				// --����������Q�������F��������-- //
				if (stage->obstacles[i].GetColor() == 0xFFFFFF) {
					// --���ʂ��瓖�����Ă�����-- //
					if (BoxCenterCol(oldBlackBox, obstacle)) {
						// --�ʏ��ԂȂ�-- //
						if (player->GetState() == Normal) {
							// --�v���C���[�Ə�Q����Y������-- //
							float len = blackObj.pos.y - obstacle.pos.y;

							// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
							float radius = blackObj.radiusY + obstacle.radiusY;

							// --�J�����ɋ����Ɣ��a���������������Z-- //
							Camera::AddScroll(radius - len);

							// --��Ԃ��m�b�N�o�b�N��ԂɕύX-- //
							player->SetKnock();

							// --����������Q��������-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}

						// --��Ԃ��u�[�X�g��ԂȂ�-- //
						else if (player->GetState() == Boost) {
							// --����������Q��������-- //
							stage->obstacles.erase(stage->obstacles.begin() + i);
						}
					}

					// --�����瓖�����Ă�����
					else {
						// --�v���C���[�Ə�Q����X������-- //
						float len = abs(blackObj.pos.x - obstacle.pos.x);

						// --�v���C���[�Ə�Q����Y�����a�𑫂����l-- //
						float radius = blackObj.radiusX + obstacle.radiusX;

						// --�v���C���[����Q���̉E���ɂ�����-- //
						if (blackObj.pos.x >= obstacle.pos.x) {
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
					}

					break;
				}
			}
		}
	}

	// --�v���C���[�̏����i�[-- //
	oldWhiteBox = { {player->GetWhiteObj().pos.x, player->GetWhiteObj().pos.y + Camera::GetScroll()}, 32, 32 };
	oldBlackBox = { {player->GetBlackObj().pos.x, player->GetBlackObj().pos.y + Camera::GetScroll()}, 32, 32 };
}