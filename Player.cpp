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
	stageManager_ = StageManager::GetInstance();

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
#pragma region �l�_�̏��X�V
	// white
	vPosW.leftTop = whiteObj.pos - Vector2(whiteObj.radius, whiteObj.radius);     // ���S(x,y) - ���a(x,y)
	vPosW.rightTop = whiteObj.pos - Vector2(-whiteObj.radius, whiteObj.radius);   // ���S(x,y) - ���a(-x,y)
	vPosW.leftBottom = whiteObj.pos + Vector2(-whiteObj.radius, whiteObj.radius); // ���S(x,y) + ���a(-x,y)
	vPosW.rightBottom = whiteObj.pos + Vector2(whiteObj.radius, whiteObj.radius); // ���S(x,y) + ���a(x,y)
	// black
	vPosB.leftTop = blackObj.pos - Vector2(blackObj.radius, blackObj.radius);     // ���S(x,y) - ���a(x,y)
	vPosB.rightTop = blackObj.pos - Vector2(-blackObj.radius, blackObj.radius);   // ���S(x,y) - ���a(-x,y)
	vPosB.leftBottom = blackObj.pos + Vector2(-blackObj.radius, blackObj.radius); // ���S(x,y) + ���a(-x,y)
	vPosB.rightBottom = blackObj.pos + Vector2(blackObj.radius, blackObj.radius); // ���S(x,y) + ���a(x,y)
#pragma endregion

#pragma region �l�_�̍��W���}�b�v�`�b�v�P�ʂɒu��
	// white : ����
	vElemsW.leftTop.x = vPosW.leftTop.x / StageManager::blockSize_;
	vElemsW.leftTop.y = vPosW.leftTop.y / StageManager::blockSize_;
	// : ����
	vElemsW.leftBottom.x = vPosW.leftBottom.x / StageManager::blockSize_;
	vElemsW.leftBottom.y = vPosW.leftBottom.y / StageManager::blockSize_;
	// : �E��
	vElemsW.rightTop.x = vPosW.rightTop.x / StageManager::blockSize_;
	vElemsW.rightTop.y = vPosW.rightTop.y / StageManager::blockSize_;
	// : �E��
	vElemsW.rightBottom.x = vPosW.rightBottom.x / StageManager::blockSize_;
	vElemsW.rightBottom.y = vPosW.rightBottom.y / StageManager::blockSize_;

	// black : ����
	vElemsB.leftTop.x = vPosB.leftTop.x / StageManager::blockSize_;
	vElemsB.leftTop.y = vPosB.leftTop.y / StageManager::blockSize_;
	// : ����
	vElemsB.leftBottom.x = vPosB.leftBottom.x / StageManager::blockSize_;
	vElemsB.leftBottom.y = vPosB.leftBottom.y / StageManager::blockSize_;
	// : �E��
	vElemsB.rightTop.x = vPosB.rightTop.x / StageManager::blockSize_;
	vElemsB.rightTop.y = vPosB.rightTop.y / StageManager::blockSize_;
	// : �E��
	vElemsB.rightBottom.x = vPosB.rightBottom.x / StageManager::blockSize_;
	vElemsB.rightBottom.y = vPosB.rightBottom.y / StageManager::blockSize_;
#pragma endregion

#pragma region �����蔻��
	// �v���C���[���W����Q���Əd�Ȃ����ꍇ : ���F
	if (stageManager_->GetMapchipData()->at(vElemsW.leftTop.y).at(vElemsW.leftTop.x) == static_cast<int>(BlockId::White) ||			// ����
		stageManager_->GetMapchipData()->at(vElemsW.leftBottom.y).at(vElemsW.leftBottom.x) == static_cast<int>(BlockId::White) ||	// ����
		stageManager_->GetMapchipData()->at(vElemsW.rightTop.y).at(vElemsW.rightTop.x) == static_cast<int>(BlockId::White) ||		// �E��
		stageManager_->GetMapchipData()->at(vElemsW.rightBottom.y).at(vElemsW.rightBottom.x) == static_cast<int>(BlockId::White) ||	// �E��
		stageManager_->GetMapchipData()->at(vElemsB.leftTop.y).at(vElemsB.leftTop.x) == static_cast<int>(BlockId::Black) ||				// ����
		stageManager_->GetMapchipData()->at(vElemsB.leftBottom.y).at(vElemsB.leftBottom.x) == static_cast<int>(BlockId::Black) ||		// ����
		stageManager_->GetMapchipData()->at(vElemsB.rightTop.y).at(vElemsB.rightTop.x) == static_cast<int>(BlockId::Black) ||			// �E��
		stageManager_->GetMapchipData()->at(vElemsB.leftBottom.y).at(vElemsB.leftBottom.x) == static_cast<int>(BlockId::Black)) {		// �E��

		// �X�s�[�h�Q�[�W�𑝂₷
	}

	// �v���C���[���W����Q���Əd�Ȃ����ꍇ : �ِF : ����
	if (stageManager_->GetMapchipData()->at(vElemsW.leftTop.y).at(vElemsW.leftTop.x) == static_cast<int>(BlockId::Black) &&			// ����
		stageManager_->GetMapchipData()->at(vElemsW.rightTop.y).at(vElemsW.rightTop.x) == static_cast<int>(BlockId::Black) &&		// �E��
		stageManager_->GetMapchipData()->at(vElemsW.leftBottom.y).at(vElemsW.leftBottom.x) != static_cast<int>(BlockId::Black)&&	// ����
		stageManager_->GetMapchipData()->at(vElemsW.rightBottom.y).at(vElemsW.rightBottom.x) != static_cast<int>(BlockId::Black)) {	// �E��

		state = Knock;
	}
	if (stageManager_->GetMapchipData()->at(vElemsB.leftTop.y).at(vElemsB.leftTop.x) == static_cast<int>(BlockId::White) &&			// ����
		stageManager_->GetMapchipData()->at(vElemsB.rightTop.y).at(vElemsB.rightTop.x) == static_cast<int>(BlockId::White) &&		// �E��
		stageManager_->GetMapchipData()->at(vElemsB.leftBottom.y).at(vElemsB.leftBottom.x) != static_cast<int>(BlockId::White)&&	// ����
		stageManager_->GetMapchipData()->at(vElemsB.rightBottom.y).at(vElemsB.rightBottom.x) != static_cast<int>(BlockId::White)) {	// �E��

		state = Knock;
	}

	// �v���C���[���W����Q���Əd�Ȃ����ꍇ : �ِF : �� : ������E��
	if (stageManager_->GetMapchipData()->at(vElemsW.rightTop.y).at(vElemsW.rightTop.x) == static_cast<int>(BlockId::Black) &&		// �E��
		stageManager_->GetMapchipData()->at(vElemsW.rightBottom.y).at(vElemsW.rightBottom.x) == static_cast<int>(BlockId::Black) &&	// �E��
		stageManager_->GetMapchipData()->at(vElemsW.leftTop.y).at(vElemsW.leftTop.x) != static_cast<int>(BlockId::Black) &&			// ����
		stageManager_->GetMapchipData()->at(vElemsW.leftBottom.y).at(vElemsW.leftBottom.x) != static_cast<int>(BlockId::Black)) {	// ����

		state = Boost;
	}
	if (stageManager_->GetMapchipData()->at(vElemsB.rightTop.y).at(vElemsB.rightTop.x) == static_cast<int>(BlockId::Black) &&		// �E��
		stageManager_->GetMapchipData()->at(vElemsB.rightBottom.y).at(vElemsB.rightBottom.x) == static_cast<int>(BlockId::Black) &&	// �E��
		stageManager_->GetMapchipData()->at(vElemsB.leftTop.y).at(vElemsB.leftTop.x) != static_cast<int>(BlockId::Black) &&			// ����
		stageManager_->GetMapchipData()->at(vElemsB.leftBottom.y).at(vElemsB.leftBottom.x) != static_cast<int>(BlockId::Black)) {	// ����

		state = Boost;
	}

	// �v���C���[���W����Q���Əd�Ȃ����ꍇ : �ِF : �� : �E���獶��
	if (stageManager_->GetMapchipData()->at(vElemsW.leftTop.y).at(vElemsW.leftTop.x) == static_cast<int>(BlockId::Black) &&			// ����
		stageManager_->GetMapchipData()->at(vElemsW.leftBottom.y).at(vElemsW.leftBottom.x) == static_cast<int>(BlockId::Black) &&	// ����
		stageManager_->GetMapchipData()->at(vElemsW.rightTop.y).at(vElemsW.rightTop.x) != static_cast<int>(BlockId::Black) &&		// �E��
		stageManager_->GetMapchipData()->at(vElemsW.rightBottom.y).at(vElemsW.rightBottom.x) != static_cast<int>(BlockId::Black)) {	// �E��

		state = Boost;
	}
	if (stageManager_->GetMapchipData()->at(vElemsB.leftTop.y).at(vElemsB.leftTop.x) == static_cast<int>(BlockId::Black) &&			// ����
		stageManager_->GetMapchipData()->at(vElemsB.leftBottom.y).at(vElemsB.leftBottom.x) == static_cast<int>(BlockId::Black) &&	// ����
		stageManager_->GetMapchipData()->at(vElemsB.rightTop.y).at(vElemsB.rightTop.x) != static_cast<int>(BlockId::Black) &&		// �E��
		stageManager_->GetMapchipData()->at(vElemsB.rightBottom.y).at(vElemsB.rightBottom.x) != static_cast<int>(BlockId::Black)) {	// �E��

		state = Boost;
	}
#pragma endregion
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