#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "StageManager.h"
#include "SceneManager.h"
#include "Util.h"

// --��-- //
#define BLACK 0x000000

// --��-- //
#define WHITE 0xFFFFFF

// --����-- //
#define LEFT -1
#define RIGHT 1

// --�����]�����̃T�C�Y-- //
#define MAX_SIZE_P 32;
#define MIN_SIZE_P 27;

// --�I�u�W�F�N�g�̕`��p�̊֐�-- //
void DrawBoxAA(Object obj, unsigned int color, bool fillFlag) {
	DrawBoxAA(
		obj.pos.x - obj.radius, obj.pos.y - obj.radius,
		obj.pos.x + obj.radius, obj.pos.y + obj.radius,
		color, fillFlag);

	DrawLineAA(obj.pos.x - obj.radius, obj.pos.y - obj.radius, obj.pos.x + obj.radius, obj.pos.y - obj.radius, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x - obj.radius, obj.pos.y + obj.radius, obj.pos.x + obj.radius, obj.pos.y + obj.radius, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x - obj.radius, obj.pos.y - obj.radius, obj.pos.x - obj.radius, obj.pos.y + obj.radius, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x + obj.radius, obj.pos.y - obj.radius, obj.pos.x + obj.radius, obj.pos.y + obj.radius, color ^ 0xFFFFFF, 3);
}

// --�C���X�^���X��NULL����-- //
Player* Player::myInstance_ = nullptr;

// --�C���X�^���X�ǂݍ���-- //
Player* Player::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance_ == nullptr) myInstance_ = new Player();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance_;
}

// --���������-- //
void Player::Release() {
	// --���������-- //
	delete myInstance_;

	// --NULL����-- //
	myInstance_ = nullptr;
}

// --�R���X�g���N�^-- //
Player::Player() :
#pragma region �萔�����o�̏�����

	// --���ړ����x�̊�b�l-- //
	defaultSpeedX(5.0f),

	// --�c�ړ����x�̊�b�l-- //
	defaultSpeedY(10.0f),

	// --�u�[�X�g���̏����X�s�[�h-- //
	defaultBoostSpeedY(20.0f),

	// --�m�b�N�o�b�N���̏����X�s�[�h-- //
	defaultKnockSpeedY(-10.0f)

#pragma endregion
{
	// --�N���X��`-- //
	key_ = Key::GetInstance();
	stageManager_ = StageManager::GetInstance();

	// --�v���C���[�I�u�W�F�N�g-- //
	player_[0] = { {300.0f, 700.0f}, 32.0f };
	player_[1] = { {900.0f, 700.0f}, 32.0f };

	// --�����蔻�肪�L����
	isCollision = true;

	// --�v���C���[�̏��-- //
	state = Normal;
	xAxisState = static_cast<int>(XAxisState::Default);
#ifdef _DEBUG
	debug_changeDirectionMode = static_cast<int>(DirectionMode::Old);
#endif

	// --���ړ��̑��x-- //
	speedX = defaultSpeedX;

	// --�ړ��������-- //
	direction = RIGHT;

	// --�c�ړ��̑��x-- //
	speedY = defaultSpeedY;

	// --�u�[�X�g�̎���[s]-- //
	boostTime = 0.5f;

	// --�u�[�X�g�̌o�ߎ���[s]-- //
	boostTimer = 0.0f;

	// --�u�[�X�g���n�܂������̎���-- //
	boostStartTime = 0;
}

// --�f�X�g���N�^-- //
Player::~Player() {

}

// --����������-- //
void Player::Initialize() {
	// --�v���C���[�I�u�W�F�N�g-- //
	player_[0] = { {300.0f, 700.0f}, 32.0f };
	player_[1] = { {900.0f, 700.0f}, 32.0f };

	// --�����蔻�肪�L����
	isCollision = true;

	// --�v���C���[�̏��-- //
	state = Normal;
	xAxisState = static_cast<int>(XAxisState::Default);
//#ifdef _DEBUG
//	debug_changeDirectionMode = static_cast<int>(DirectionMode::Old);
//#endif

	// --���ړ��̑��x-- //
	speedX = defaultSpeedX;

	// --�ړ��������-- //
	direction = RIGHT;

	// --�c�ړ��̑��x-- //
	speedY = 10.0f;

	// --�u�[�X�g�̌o�ߎ���[s]-- //
	boostTimer = 0.0f;
}

// --�X�V����-- //
void Player::Update() {

	// --[SPACE]���������������ς���-- //
	if (key_->IsTrigger(KEY_INPUT_SPACE)) {
		// --�������E�������獶�ɕύX-- //
		if (direction == RIGHT) {
			direction = LEFT;
#ifdef _DEBUG // �f�o�b�O����
			if (debug_changeDirectionMode == static_cast<int>(DirectionMode::New)) { // �f�o�b�O�p[SPACE]
				xAxisState = static_cast<int>(XAxisState::Boost);
				boostStartTime = GetNowCount();
				isEaseDraw = true;
				easeStartTime = GetNowCount();
			}
#endif
		}

		// --����������������E�ɕύX-- //
		else if (direction == LEFT) {
			direction = RIGHT;
#ifdef _DEBUG
			if (debug_changeDirectionMode == static_cast<int>(DirectionMode::New)) {
				xAxisState = static_cast<int>(XAxisState::Boost);
				boostStartTime = GetNowCount();
				isEaseDraw = true;
				easeStartTime = GetNowCount();
			}
#endif
		}
	}

#ifdef _DEBUG
	if (key_->IsTrigger(KEY_INPUT_C)) {
		if (debug_changeDirectionMode == static_cast<int>(DirectionMode::Old)) debug_changeDirectionMode = static_cast<int>(DirectionMode::New);
		else if (debug_changeDirectionMode == static_cast<int>(DirectionMode::New)) debug_changeDirectionMode = static_cast<int>(DirectionMode::Old);
	}
#endif

	// --x����state��Boost��������-- //
	if (xAxisState == static_cast<int>(XAxisState::Boost)) {
		// --�u�[�X�g��ԂɂȂ��Ă���̌o�ߎ���-- //
		float nowTime = (GetNowCount() - boostStartTime) / 1000.0f;

		DrawFormatString(0, 40, 0x000000, "nowTime = %f", nowTime);

		// --�w�肳��Ă���u�[�X�g���Ԃ��߂�����-- //
		if (0.1f <= nowTime) {
			// --�u�[�X�g��Ԃ���ʏ��ԂɕύX-- //
			xAxisState = static_cast<int>(XAxisState::Default);
		}

		// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
		player_[0].pos.x += 2 * speedX * direction;
		player_[1].pos.x += 2 * speedX * direction;
	}

	// --�ʏ��Ԃ�������-- //
	if (state == Normal) {
		// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
		player_[0].pos.x += speedX * direction;
		player_[1].pos.x += speedX * direction;
	}

	// --�m�b�N�o�b�N��Ԃ�������-- //
	else if (state == Knock) {
		// --���x�����Z-- //
		speedY += 0.4f;

		// --Y���̑��x����b�l���z������ʏ��ԂɕύX-- //
		if (speedY > 0) {
			SetNormal();
		}

		//if (speedY >= 0.0f) {
		//	// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
		//	whiteObj.pos.x += speedX * direction;
		//	blackObj.pos.x += speedX * direction;
		//}

		speedX += 0.2f;

		if (speedX >= defaultSpeedX) {
			speedX = defaultSpeedX;
		}

		// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
		player_[0].pos.x += speedX * direction;
		player_[1].pos.x += speedX * direction;
	}

	// --�u�[�X�g��Ԃ�������-- //
	else if (state == Boost) {
		// --�u�[�X�g��ԂɂȂ��Ă���̌o�ߎ���-- //
		float nowTime = (GetNowCount() - boostStartTime) / 1000.0f;

		//DrawFormatString(0, 40, 0x000000, "nowTime = %f", nowTime);

		// --�w�肳��Ă���u�[�X�g���Ԃ��߂�����-- //
		if (boostTime <= nowTime) {
			// --�u�[�X�g��Ԃ���ʏ��ԂɕύX-- //
			SetNormal();
		}

		// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
		player_[0].pos.x += speedX * direction;
		player_[1].pos.x += speedX * direction;
	}

	// --�v���C���[�̈ړ����X�N���[��-- //
	Camera::AddScroll(-speedY);

	// --���܂ōs���ƃv���C���[�̍��W�𔽑Α��ɕύX-- //
	if (player_[0].pos.x >= 960.0f) player_[0].pos.x -= 1280.0f;
	else if (player_[0].pos.x <= -320.0f) player_[0].pos.x += 1280.0f;

	if (player_[1].pos.x >= 960.0f) player_[1].pos.x -= 1280.0f;
	else if (player_[1].pos.x <= -320.0f) player_[1].pos.x += 1280.0f;
	//Collision();
}

// --�`�揈��-- //
void Player::Draw() {
	if (isEaseDraw == true) {
		// --�u�[�X�g��ԂɂȂ��Ă���̌o�ߎ���-- //
		float nowTime = (GetNowCount() - easeStartTime) / 1000.0f;

		DrawFormatString(200, 40, 0x000000, "nowTime = %f", nowTime);

		// 
		player_[0].radius = MIN_SIZE_P;
		player_[1].radius = MIN_SIZE_P;

		// --�w�肳��Ă���u�[�X�g���Ԃ��߂�����-- //
		if (0.1f <= nowTime) {
			// --�u�[�X�g��Ԃ���ʏ��ԂɕύX-- //
			isEaseDraw = false;
			player_[0].radius = MAX_SIZE_P;
			player_[1].radius = MAX_SIZE_P;
		}
	}

	// --�����v���C���[�`��-- //
	DrawBoxAA(player_[0], 0xFFFFFF, true);

	// --�����v���C���[�`��-- //
	DrawBoxAA(player_[1], 0xFFFFFF, true);

	DrawFormatString(0, 40, 0x000000, "speedY = %f", speedY);
	DrawFormatString(0, 60, 0x000000, "state = %d", state);
	DrawFormatString(0, 100, 0x000000, "xAxisState = %d", xAxisState);
	DrawFormatString(0, 120, 0x000000, "directionMode = %d : changeMode [C]", debug_changeDirectionMode);
	DrawFormatString(0, 140, 0x000000, "isEase = %d", isEaseDraw);
	DrawFormatString(0, 160, 0x000000, "Pos = (%f, %f)", player_[0].pos.x, player_[0].pos.y);

}

// --�����I�u�W�F�N�g�̎Q��-- //
Object Player::GetPlayer1Obj() { return player_[0]; }

// --�����I�u�W�F�N�g�̎Q��-- //
Object Player::GetPlayer2Obj() { return player_[1]; }

// --�v���C���[�̏�Ԃ�ύX-- //
int Player::GetState() { return state; }

// --�ʏ��ԂɕύX-- //
void Player::SetNormal() {
	// --Y���̑��x���K��l�ɐݒ�-- //
	speedY = defaultSpeedY;

	// --X���̑��x���K��l�ɐݒ�-- //
	speedX = defaultSpeedX;

	// --�ʏ��ԂɕύX-- //
	state = Normal;

	// --�����蔻���ON�ɂ���
	isCollision = true;
}

// --�m�b�N�o�b�N�ɕύX-- //
void Player::SetKnock() {
	// --Y���̑��x���m�b�N�o�b�N���̑��x�ɐݒ�-- //
	speedY = defaultKnockSpeedY;

	// --�ʏ��ԂɕύX-- //
	state = Knock;

	speedX = 0.4f;

	// --�����蔻���OFF�ɂ���
	isCollision = false;
}

// --�u�[�X�g��ԂɕύX-- //
void Player::SetBoost() {
	// --Y���̑��x���u�[�X�g���̋K��l�ɐݒ�-- //
	speedY = defaultBoostSpeedY;

	// --�������E�������獶�ɕύX-- //
	if (direction == RIGHT) direction = LEFT;

	// --����������������E�ɕύX-- //
	else if (direction == LEFT) direction = RIGHT;

	// --�u�[�X�g��ԂɕύX-- //
	state = Boost;

	boostStartTime = GetNowCount();
}

// --���S��ԂɕύX-- //
void Player::SetDeath() {
	SceneManager::SetScene(RESULTSCENE);
}

bool Player::GetCollisionFlag() { return isCollision; }

// --Y���̑��x���Q��
float Player::GetSpeedY() { return speedY; }

// --X���̑��x���Q��
float Player::GetSpeedX() { return speedX; }

// --�����v���C���[�̍��WX�ɉ��Z-- //
void Player::AddPlayerPosX(float value) {
	player_[0].pos.x += value;
	player_[1].pos.x += value;
}