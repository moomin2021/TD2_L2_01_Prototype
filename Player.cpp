#include "DxLib.h"
#include "Player.h"

// --��-- //
#define BLACK 0x000000

// --��-- //
#define WHITE 0xFFFFFF

// --����-- //
#define LEFT -1
#define RIGHT 1

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
	defaultSpeedX(10.0f)

#pragma endregion
{
	// --�N���X��`-- //
	key = Key::GetInstance();

	// --���W-- //
	pos[0] = { 300.0f, 700.0f };
	pos[1] = { 900.0f, 700.0f };

	// --���a-- //
	radius = 16.0f;

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
	// --���W-- //
	pos[0] = { 300.0f, 700.0f };
	pos[1] = { 900.0f, 700.0f };

	// --���a-- //
	radius = 16.0f;

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

	// --�v���C���[��X���W�ɑ��x�����Z-- //
	pos[0].x += speedX * direction;
	pos[1].x += speedX * direction;

	// --���܂ōs���ƃv���C���[�̍��W�𔽑Α��ɕύX-- //
	if (pos[0].x >= 900.0f) pos[0].x -= 1200.0f;
	else if (pos[0].x <= -300.0f) pos[0].x += 1200.0f;

	if (pos[1].x >= 900.0f) pos[1].x -= 1200.0f;
	else if (pos[1].x <= -300.0f) pos[1].x += 1200.0f;
}

// --�`�揈��-- //
void Player::Draw() {
	// --�v���C���[�`��-- //
	DrawBoxAA(pos[0].x - radius, pos[0].y - radius, pos[0].x + radius, pos[0].y + radius,
		WHITE, true);

	DrawBoxAA(pos[1].x - radius, pos[1].y - radius, pos[1].x + radius, pos[1].y + radius,
		WHITE, false);
}