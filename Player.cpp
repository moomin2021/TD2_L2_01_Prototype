#include "DxLib.h"
#include "Player.h"

// --��-- //
#define BLACK 0x000000

// --��-- //
#define WHITE 0xFFFFFF

// --����-- //
#define LEFT -1
#define RIGHT 1

// --�I�u�W�F�N�g�̕`��p�̊֐�-- //
void DrawBoxAA(Object obj, bool fillFlag) {
	DrawBoxAA(
		obj.pos.x - obj.radius, obj.pos.y - obj.radius,
		obj.pos.x + obj.radius, obj.pos.y + obj.radius,
		0xFFFFFF, fillFlag);
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
}

// --�f�X�g���N�^-- //
Player::~Player() {
	
}

// --����������-- //
void Player::Initialize() {
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

	// --�v���C���[�I�u�W�F�N�g��X���W�ɑ��x�����Z-- //
	whiteObj.pos.x += speedX * direction;
	blackObj.pos.x += speedX * direction;

	// --���܂ōs���ƃv���C���[�̍��W�𔽑Α��ɕύX-- //
	if (whiteObj.pos.x >= 900.0f) whiteObj.pos.x -= 1200.0f;
	else if (whiteObj.pos.x <= -300.0f) whiteObj.pos.x += 1200.0f;

	if (blackObj.pos.x >= 900.0f) blackObj.pos.x -= 1200.0f;
	else if (blackObj.pos.x <= -300.0f) blackObj.pos.x += 1200.0f;
}

// --�`�揈��-- //
void Player::Draw() {
	// --�����v���C���[�`��-- //
	DrawBoxAA(whiteObj, true);

	// --�����v���C���[�`��-- //
	DrawBoxAA(blackObj, false);
}

// --�����I�u�W�F�N�g�̎Q��-- //
Object Player::GetWhiteObj() { return whiteObj; }

// --�����I�u�W�F�N�g�̎Q��-- //
Object Player::GetBlackObj() { return blackObj; }

// --�v���C���[�̏�Ԃ�ύX-- //
void Player::SetState(int state) { this->state = state; }