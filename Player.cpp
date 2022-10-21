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

#define UP -1
#define DOWN 1

// --�I�u�W�F�N�g�̕`��p�̊֐�-- //
void DrawBoxAA(BoxObj obj, unsigned int color, bool fillFlag) {
	DrawBoxAA(
		obj.pos.x - obj.radiusX, obj.pos.y - obj.radiusY,
		obj.pos.x + obj.radiusX, obj.pos.y + obj.radiusY,
		color, fillFlag);

	DrawLineAA(obj.pos.x - obj.radiusX, obj.pos.y - obj.radiusY, obj.pos.x + obj.radiusX, obj.pos.y - obj.radiusY, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x - obj.radiusX, obj.pos.y + obj.radiusY, obj.pos.x + obj.radiusX, obj.pos.y + obj.radiusY, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x - obj.radiusX, obj.pos.y - obj.radiusY, obj.pos.x - obj.radiusX, obj.pos.y + obj.radiusY, color ^ 0xFFFFFF, 3);
	DrawLineAA(obj.pos.x + obj.radiusX, obj.pos.y - obj.radiusY, obj.pos.x + obj.radiusX, obj.pos.y + obj.radiusY, color ^ 0xFFFFFF, 3);
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
#pragma region �v���C���[�̑��x�ϐ�
	// --Y����{���x-- //
	defSpeedY_(5.0f),

	// --Y���̍ō����x-- //
	maxSpeedY_(30.0f),

	// --Y���̍Œᑬ�x-- //
	minSpeedY_(5.0f),

	// --X���W�̍ō����W-- //
	maxPosX_(616.0f),

	// --X���W�̍Œ���W-- //
	minPosX_(24.0f),

	// --�ǃL�b�N�̑��x-- //
	wallKickSpeedX_(20.0f),

	// --��]��Ԃ̎���[s]-- //
	rotateTime_(0.5f),

	// --Y���̌����l-- //
	decelerationY_(0.2f),

	// --Y���̉����l-- //
	accelerationY_(5.0f)
#pragma endregion
{
#pragma region �N���X��`
	// --�L�[�{�[�h����-- //
	key_ = Key::GetInstance();

	// --�X�e�[�W�Ǘ�-- //
	stageManager_ = StageManager::GetInstance();
#pragma endregion

	// --�v���C���[�I�u�W�F�N�g-- //
	object_ = { {24.0f, 100.0f}, 24.0f, 24.0f };

	// --�v���C���[�̏��-- //
	state_ = NormalWallHit;

	// --���x-- //
	speedX_ = 0.0f;// -------> X��
	speedY_ = minSpeedY_;// -> Y��

	// --�󒆂ɂ��邩-- //
	isAir_ = false;

	// --�󒆃L�b�N���ł��邩-- //
	isAirKickActive_ = true;

	// --�ړ��������-- //
	directionX_ = LEFT;
	directionY_ = DOWN;

	// --�u�[�X�g�̌o�ߎ���[s]-- //
	rotateTimer_ = 0.0f;

	// --�u�[�X�g���n�܂������̎���-- //
	rotateStartTime_ = 0;
}

// --�f�X�g���N�^-- //
Player::~Player() {

}

// --����������-- //
void Player::Initialize() {
	// --�v���C���[�I�u�W�F�N�g-- //
	object_ = { {minPosX_, 100.0f}, 24.0f, 24.0f };

	// --�v���C���[�̏��-- //
	state_ = NormalWallHit;

	// --���x-- //
	speedX_ = 0.0f;
	speedY_ = defSpeedY_;

	// --�ړ��������-- //
	directionX_ = LEFT;
	directionY_ = DOWN;

	// --�u�[�X�g�̌o�ߎ���[s]-- //
	rotateTimer_ = 0.0f;

	// --�u�[�X�g���n�܂������̎���-- //
	rotateStartTime_ = 0;

	// --�󒆂ɂ��邩-- //
	isAir_ = false;

	// --�󒆃L�b�N���ł��邩-- //
	isAirKickActive_ = true;
}

// --�X�V����-- //
void Player::Update() {

#pragma region �ʏ��Ԃ��Ǔ`�����̏���
	if (state_ == NormalWallHit) {
		// --[SPACE]����������-- //
		if (key_->IsTrigger(KEY_INPUT_SPACE)) {
			// --���E�̌�����ς���-- //
			ChangeDireX();

			// --��Ԃ�ς���-- //
			state_ = NormalAir;// -> �ʏ��Ԃ���

			// --X���̑��x��ς���-- //
			speedX_ = wallKickSpeedX_;// --�ǃL�b�N�����Ƃ��̑��x-- //

			// --Y���̈ړ��������ゾ������-- //
			if (directionY_ == UP) {
				speedY_ -= accelerationY_;
			}

			// --Y���̈ړ�����������������-- //
			else if (directionY_ == DOWN) {
				speedY_ += accelerationY_;
			}
		}

		// --��������-- //
		if (directionY_ == DOWN) {
			speedY_ -= decelerationY_;
			speedY_ = Util::Clamp(speedY_, maxSpeedY_, minSpeedY_);
		}

		else if (directionY_ == UP) {
			speedY_ -= decelerationY_;
			if (speedY_ <= 0) {
				directionY_ = DOWN;
			}
		}
	}
#pragma endregion

#pragma region �ʏ��Ԃ��󒆂ɂ���
	else if (state_ == NormalAir) {
		
	}
#pragma endregion

#pragma region ��]��Ԃ��Ǔ`����
	else if (state_ == RotateWallHit) {
		// --[SPACE]����������-- //
		if (key_->IsTrigger(KEY_INPUT_SPACE)) {
			// --���E�̌�����ς���-- //
			ChangeDireX();

			// --��Ԃ�ς���-- //
			state_ = NormalAir;// -> �ʏ��Ԃ���

			// --X���̑��x��ς���-- //
			speedX_ = wallKickSpeedX_;// --�ǃL�b�N�����Ƃ��̑��x-- //
		}

		// --�u�[�X�g��ԂɂȂ��Ă���̌o�ߎ���-- //
		float nowTime = (GetNowCount() - rotateStartTime_) / 1000.0f;

		// --�w�肳��Ă���u�[�X�g���Ԃ��߂�����-- //
		if (rotateTime_ <= nowTime) {
			// --�u�[�X�g��Ԃ���ʏ��ԂɕύX-- //
			state_ = NormalWallHit;
		}
	}
#pragma endregion

#pragma region ��]��Ԃ��󒆂ɂ���
	else if (state_ == RotateAir) {
		// --�u�[�X�g��ԂɂȂ��Ă���̌o�ߎ���-- //
		float nowTime = (GetNowCount() - rotateStartTime_) / 1000.0f;

		// --�w�肳��Ă���u�[�X�g���Ԃ��߂�����-- //
		if (rotateTime_ <= nowTime) {
			// --�u�[�X�g��Ԃ���ʏ��ԂɕύX-- //
			state_ = NormalAir;
		}
	}
#pragma endregion

	// --�v���C���[��X���ɉ��Z-- //
	object_.pos.x += speedX_ * directionX_;

	// --�v���C���[�̈ړ����X�N���[��-- //
	Camera::AddScroll(speedY_ * directionY_);

	// --x���W���Œ���W�ȉ��ɂȂ�����-- //
	if (object_.pos.x < minPosX_) {
		// --x���W��ύX-- //
		object_.pos.x = minPosX_;

		// --��Ԃ�ύX-- //
		state_ = NormalWallHit;// -> �ʏ��Ԃ��Ǔ`����

		// --X���̑��x��ς���-- //
		speedX_ = 0.0f;// -> �����Ȃ��悤��
	}

	// --x���W���ō����W�ȏ�ɂȂ�����-- //
	else if (object_.pos.x > maxPosX_) {
		// --X���W��ύX-- //
		object_.pos.x = maxPosX_;

		// --��Ԃ�ύX-- //
		state_ = NormalWallHit;// -> �ʏ��Ԃ��Ǔ`����

		// --X���̑��x��ς���-- //
		speedX_ = 0.0f;// -> �����Ȃ��悤��
	}
}

// --�`�揈��-- //
void Player::Draw() {

	DrawBoxAA(object_, BLACK, true);

	DrawFormatString(0, 40, WHITE, "speedX_ : %f", speedX_);
	DrawFormatString(0, 60, WHITE, "speedY_ : %f", speedY_);
	DrawFormatString(0, 80, WHITE, "direX : %d", directionX_);
	DrawFormatString(0, 100, WHITE, "Pos : (%f, %f)", object_.pos.x, object_.pos.y);
	DrawFormatString(0, 120, WHITE, "Scroll : %f", Camera::GetScroll());

}

// --�I�u�W�F�N�g�̎Q��-- //
BoxObj Player::GetBoxObj() { return object_; }

// --�v���C���[�̏�Ԃ�ύX-- //
int Player::GetState() { return state_; }

// --�v���C���[�̏�Ԃ�ύX-- //
void Player::SetState(int state) { state_ = state; }
//
// --���S��ԂɕύX-- //
void Player::SetDeath() {
	SceneManager::SetScene(RESULTSCENE);
}

float& Player::GetSpeedX() { return speedX_; }
float& Player::GetSpeedY() { return speedY_; }

// --X���̌�����ς���-- //
void Player::ChangeDireX() {
	if (directionX_ == LEFT) directionX_ = RIGHT;
	else directionX_ = LEFT;
}

void Player::ChangeDireY() {
	if (directionY_ == UP) directionY_ = DOWN;
	else directionY_ = UP;
}

// --��]��Ԃɂ���-- //
void Player::SetRotate() {
	speedY_ = maxSpeedY_;

	state_ = RotateAir;
	rotateStartTime_ = GetNowCount();
}