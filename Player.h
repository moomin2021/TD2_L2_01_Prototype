#pragma once
#include "Key.h"
#include "Util.h"
#include "StageManager.h"

enum State {
	Normal,// -> �ʏ���
	Knock,// --> �m�b�N�o�b�N���
	Boost,// ---> �u�[�X�g���
	Death// --���S���
};

enum struct XAxisState {
	Default,
	Boost
};

#ifdef _DEBUG
enum struct DirectionMode {
	Old,
	New
};
#endif

class Player {
	/// --�����o�ϐ�-- ///
public:
	// --�I�u�W�F�N�g-- //
	BoxObj object_[2];

private:
	// --�C���X�^���X-- //
	static Player* myInstance_;

	// --�N���X�錾-- //
	Key* key_;
	StageManager* stageManager_ = nullptr;

	// --�v���C���[�̏��-- //
	int state;
	bool xAxisState;
#ifdef _DEBUG
	bool debug_changeDirectionMode;
#endif
	bool isEaseDraw = false;

	// --���ړ����x�̊�b�l-- //
	const float defaultSpeedX;

	// --���ړ��̑��x-- //
	float speedX;

	// --�ړ��������-- //
	int direction;

	// --�c�ړ����x�̊�b�l-- //
	const float defaultSpeedY;

	// --�c�ړ��̑��x-- //
	float speedY;

	// --�u�[�X�g�̎���[s]-- //
	float boostTime;

	// --�u�[�X�g�̌o�ߎ���[s]-- //
	float boostTimer;

	// --�u�[�X�g���n�܂������̎���-- //
	int boostStartTime;

	//
	int easeStartTime = 0.0f;

	// --�u�[�X�g���̏����X�s�[�h-- //
	const float defaultBoostSpeedY;

	// --�m�b�N�o�b�N���̏����X�s�[�h-- //
	const float defaultKnockSpeedY;

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

	// --�I�u�W�F�N�g1�̎Q��-- //
	BoxObj GetPlayer1Obj();

	// --�I�u�W�F�N�g1�̎Q��-- //
	BoxObj GetPlayer2Obj();

	// --�v���C���[�̏�Ԃ�ύX-- //
	int GetState();

	// --�ʏ��ԂɕύX-- //
	void SetNormal();

	// --�m�b�N�o�b�N�ɕύX-- //
	void SetKnock();

	// --�u�[�X�g��ԂɕύX-- //
	void SetBoost();

	// --���S��ԂɕύX-- //
	void SetDeath();

private:
	// --�R���X�g���N�^-- //
	Player();

	//void Collision();

	/// --�����o�֐�END-- ///
};