#include "DxLib.h"
#include "Player.h"
#include "Camera.h"

// --��-- //
#define BLACK 0x000000

// --��-- //
#define WHITE 0xFFFFFF

// --����-- //
#define LEFT -1
#define RIGHT 1

// --�I�u�W�F�N�g�̕`��p�̊֐�-- //
void DrawBoxAA(Object obj, unsigned int color,  bool fillFlag) {
	DrawBoxAA(
		obj.pos.x - obj.radius, obj.pos.y - obj.radius,
		obj.pos.x + obj.radius, obj.pos.y + obj.radius,
		color, fillFlag);
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
	defaultSpeedX(5.0f)

#pragma endregion
{
	// --�N���X��`-- //
	key = Key::GetInstance();

	// --�����v���C���[�I�u�W�F�N�g-- //
	whiteObj = { {300.0f, 700.0f}, 32.0f };

	// --�����v���C���[�I�u�W�F�N�g-- //
	blackObj = { {900.0f, 700.0f}, 32.0f };

	// --�v���C���[�̏��-- //
	state = Normal;

	// --���ړ��̑��x-- //
	speedX = defaultSpeedX;

	// --�ړ��������-- //
	direction = RIGHT;

	// --�c�ړ��̑��x-- //
	speedY = 10.0f;

	// --�u�[�X�g�̎���[s]-- //
	boostTime = 5.0f;

	// --�u�[�X�g�̌o�ߎ���[s]-- //
	boostTimer = 0.0f;

	// --�u�[�X�g���n�܂������̎���-- //
	boostStartTime = 0;
}

void Player::Coliision()
{

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

	// --�v���C���[�̏��-- //
	state = Normal;

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
		if (direction == RIGHT) direction = LEFT;

		// --����������������E�ɕύX-- //
		else if (direction == LEFT) direction = RIGHT;
	}

	// --�ʏ��Ԃ�������-- //
	if (state == Normal) {
		// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
		whiteObj.pos.x += speedX * direction;
		blackObj.pos.x += speedX * direction;

		// --�v���C���[�̈ړ����X�N���[��-- //
		Camera::AddScroll(-speedY);
	}

	// --�m�b�N�o�b�N��Ԃ�������-- //
	else if (state == Knock) {

	}

	// --�u�[�X�g��Ԃ�������-- //
	else if (state == Boost) {
		// --�u�[�X�g��ԂɂȂ��Ă���̌o�ߎ���-- //
		float nowTime = (GetNowCount() - boostStartTime) / 1000.0f;

		// --�w�肳��Ă���u�[�X�g���Ԃ��߂�����-- //
		if (boostTime <= nowTime) {
			// --�u�[�X�g��Ԃ���ʏ��ԂɕύX-- //
			state = Normal;
		}
	}

	// --���܂ōs���ƃv���C���[�̍��W�𔽑Α��ɕύX-- //
	if (whiteObj.pos.x >= 960.0f) whiteObj.pos.x -= 1280.0f;
	else if (whiteObj.pos.x <= -320.0f) whiteObj.pos.x += 1280.0f;

	if (blackObj.pos.x >= 960.0f) blackObj.pos.x -= 1280.0f;
	else if (blackObj.pos.x <= -320.0f) blackObj.pos.x += 1280.0f;
}

// --�`�揈��-- //
void Player::Draw() {
	// --�����v���C���[�`��-- //
	DrawBoxAA(whiteObj, 0xFFFFFF, true);

	// --�����v���C���[�`��-- //
	DrawBoxAA(blackObj, 0x000000, true);
}

// --�����I�u�W�F�N�g�̎Q��-- //
Object Player::GetWhiteObj() { return whiteObj; }

// --�����I�u�W�F�N�g�̎Q��-- //
Object Player::GetBlackObj() { return blackObj; }

// --�v���C���[�̏�Ԃ�ύX-- //
void Player::SetState(int state) { this->state = state; }