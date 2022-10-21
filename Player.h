#pragma once
#include "Key.h"
#include "Util.h"
#include "StageManager.h"

enum State {
	NormalWallHit,// -> �ʏ��ԂŕǓ`����
	NormalAir,// -> �ʏ��Ԃŋ󒆂ɂ���
	RotateWallHit,// -> ��]��ԂŕǓ`����
	RotateAir,// -> ��]��Ԃŋ󒆂ɂ���
	Death// --���S���
};

class Player {
	/// --�����o�ϐ�-- ///
public:
	// --�I�u�W�F�N�g-- //
	BoxObj object_;

private:
	// --�C���X�^���X-- //
	static Player* myInstance_;

#pragma region �N���X�錾
	// --�L�[�{�[�h����-- //
	Key* key_;

	// --�X�e�[�W�Ǘ�-- //
	StageManager* stageManager_;
#pragma endregion

	// --�v���C���[�̏��-- //
	int state_;

#pragma region �v���C���[�̑��x�ϐ�
	// --���ۂɉ��Z���鑬�x�ϐ�-- //
	float speedX_;// -> X��
	float speedY_;// -> Y��
	const float defSpeedY_;// -> Y����{���x

	// --Y���̍ō����x-- //
	const float maxSpeedY_;

	// --Y���̍Œᑬ�x-- //
	const float minSpeedY_;

	// --�ǃL�b�N�̑��x-- //
	const float wallKickSpeedX_;

	// --Y���Ɍ������l-- //
	const float decelerationY_;

	// --Y���̉����l-- //
	const float accelerationY_;
#pragma endregion

#pragma region �u�[�X�g���ԕϐ�
	// --�u�[�X�g�̎���[s]-- //
	const float rotateTime_;

	// --�u�[�X�g�̌o�ߎ���[s]-- //
	float rotateTimer_;

	// --�u�[�X�g���n�܂������̎���-- //
	int rotateStartTime_;
#pragma endregion

	// --X���W�̍ō����W-- //
	const float maxPosX_;

	// --X���W�̍Œ���W-- //
	const float minPosX_;

	// --�󒆂ɂ��邩-- //
	bool isAir_;

	// --�󒆃L�b�N���ł��邩-- //
	bool isAirKickActive_;

	// --�ړ��������-- //
	float directionX_;
	float directionY_;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Player* GetInstance();

	// --���������-- //
	static void Release();

	// --�f�X�g���N�^-- //
	~Player();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

	// --�I�u�W�F�N�g�̎Q��-- //
	BoxObj GetBoxObj();

	// --�v���C���[�̏�Ԃ��Q��-- //
	int GetState();

	// --�v���C���[�̏�Ԃ�ύX-- //
	void SetState(int state);

	float& GetSpeedX();
	float& GetSpeedY();

	// --�ʏ��ԂɕύX-- //
	void SetNormal();

	// --�u�[�X�g��ԂɕύX-- //
	void SetBoost();

	// --���S��ԂɕύX-- //
	void SetDeath();

	// --X���̌�����ς���-- //
	void ChangeDireX();
	void ChangeDireY();

	// --��]��Ԃɂ���-- //
	void SetRotate();

private:
	// --�R���X�g���N�^-- //
	Player();

	//void Collision();

	/// --�����o�֐�END-- ///
};