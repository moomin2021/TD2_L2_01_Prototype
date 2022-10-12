#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "StageManager.h"

// --��-- //
#define BLACK 0x000000

// --��-- //
#define WHITE 0xFFFFFF

// --����-- //
#define LEFT -1
#define RIGHT 1

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
Player* Player::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
Player* Player::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new Player();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --���������-- //
void Player::Release() {
	// --���������-- //
	delete myInstance;

	// --NULL����-- //
	myInstance = nullptr;
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
	key = Key::GetInstance();
	stageManager_ = StageManager::GetInstance();

	// --�����v���C���[�I�u�W�F�N�g-- //
	whiteObj = { {300.0f, 700.0f}, 32.0f };

	// --�����v���C���[�I�u�W�F�N�g-- //
	blackObj = { {900.0f, 700.0f}, 32.0f };

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
	boostTime = 1.0f;

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
	// --�����v���C���[�I�u�W�F�N�g-- //
	whiteObj = { {320.0f, 700.0f}, 32.0f };

	// --�����v���C���[�I�u�W�F�N�g-- //
	blackObj = { {960.0f, 700.0f}, 32.0f };

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
	speedY = 10.0f;

	// --�u�[�X�g�̌o�ߎ���[s]-- //
	boostTimer = 0.0f;
}

// --�X�V����-- //
void Player::Update() {

	// --[SPACE]���������������ς���-- //
	if (key->IsTrigger(KEY_INPUT_SPACE)) {
		// --�������E�������獶�ɕύX-- //
		if (direction == RIGHT) {
			direction = LEFT;
#ifdef _DEBUG
			if (debug_changeDirectionMode == static_cast<int>(DirectionMode::New)) {
				xAxisState = static_cast<int>(XAxisState::Boost);
				boostStartTime = GetNowCount();
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
			}
#endif
		}
	}

#ifdef _DEBUG
	if (key->IsTrigger(KEY_INPUT_C)) {
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
		whiteObj.pos.x += 2 * speedX * direction;
		blackObj.pos.x += 2 * speedX * direction;
	}

	// --�ʏ��Ԃ�������-- //
	if (state == Normal) {
		// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
		whiteObj.pos.x += speedX * direction;
		blackObj.pos.x += speedX * direction;
	}

	// --�m�b�N�o�b�N��Ԃ�������-- //
	else if (state == Knock) {
		// --���x�����Z-- //
		speedY += 0.40f;

		// --Y���̑��x����b�l���z������ʏ��ԂɕύX-- //
		if (speedY >= defaultSpeedY) {
			SetNormal();
		}

		//if (speedY >= 0.0f) {
		//	// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
		//	whiteObj.pos.x += speedX * direction;
		//	blackObj.pos.x += speedX * direction;
		//}

		// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
		whiteObj.pos.x += speedX * direction;
		blackObj.pos.x += speedX * direction;

		speedX += 0.2f;

		if (speedX >= defaultSpeedX) {
			speedX = defaultSpeedX;
		}
	}

	// --�u�[�X�g��Ԃ�������-- //
	else if (state == Boost) {
		// --�u�[�X�g��ԂɂȂ��Ă���̌o�ߎ���-- //
		float nowTime = (GetNowCount() - boostStartTime) / 1000.0f;

		DrawFormatString(0, 40, 0x000000, "nowTime = %f", nowTime);

		// --�w�肳��Ă���u�[�X�g���Ԃ��߂�����-- //
		if (boostTime <= nowTime) {
			// --�u�[�X�g��Ԃ���ʏ��ԂɕύX-- //
			SetNormal();
		}

		// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
		whiteObj.pos.x += speedX * direction;
		blackObj.pos.x += speedX * direction;
	}

	// --�v���C���[�̈ړ����X�N���[��-- //
	Camera::AddScroll(-speedY);

	// --���܂ōs���ƃv���C���[�̍��W�𔽑Α��ɕύX-- //
	if (whiteObj.pos.x >= 960.0f) whiteObj.pos.x -= 1280.0f;
	else if (whiteObj.pos.x <= -320.0f) whiteObj.pos.x += 1280.0f;

	if (blackObj.pos.x >= 960.0f) blackObj.pos.x -= 1280.0f;
	else if (blackObj.pos.x <= -320.0f) blackObj.pos.x += 1280.0f;

	//Collision();
}

// --�`�揈��-- //
void Player::Draw() {

	// --�����v���C���[�`��-- //
	DrawBoxAA(whiteObj, 0xFFFFFF, true);

	// --�����v���C���[�`��-- //
	DrawBoxAA(blackObj, 0x000000, true);

	DrawFormatString(0, 0, 0x000000, "speedY = %f", speedY);
	DrawFormatString(0, 20, 0x000000, "state = %d", state);
	DrawFormatString(0, 60, 0x000000, "xAxisState = %d", xAxisState);
	DrawFormatString(0, 80, 0x000000, "directionMode = %d : changeMode [C]", debug_changeDirectionMode);
}

// --�����I�u�W�F�N�g�̎Q��-- //
Object Player::GetWhiteObj() { return whiteObj; }

// --�����I�u�W�F�N�g�̎Q��-- //
Object Player::GetBlackObj() { return blackObj; }

// --�v���C���[�̏�Ԃ�ύX-- //
int Player::GetState() { return state; }

// --�ʏ��ԂɕύX-- //
void Player::SetNormal() {
	// --Y���̑��x���K��l�ɐݒ�-- //
	speedY = defaultSpeedY;

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

bool Player::GetCollisionFlag() { return isCollision; }

// --Y���̑��x���Q��
float Player::GetSpeedY() { return speedY; }

// --X���̑��x���Q��
float Player::GetSpeedX() { return speedX; }