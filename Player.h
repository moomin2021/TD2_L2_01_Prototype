#pragma once
#include "Key.h"
#include "Util.h"
#include "StageManager.h"

enum State {
	Normal,// -> �ʏ���
	Knock,// --> �m�b�N�o�b�N���
	Boost// ---> �u�[�X�g���
};

struct Vertex {
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightTop;
	Vector2 rightBottom;
};

class Player {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Player* myInstance;

	// --�N���X�錾-- //
	Key* key;
	StageManager* stageManager_ = nullptr;

	// --�����v���C���[�I�u�W�F�N�g-- //
	Object whiteObj;

	// --�����v���C���[�I�u�W�F�N�g-- //
	Object blackObj;

	// --�v���C���[�̏��-- //
	int state;

	// --���ړ����x�̊�b�l-- //
	const float defaultSpeedX;

	// --���ړ��̑��x-- //
	float speedX;

	// --�ړ��������-- //
	int direction;


	// Collision()
	Vertex vPosW;
	Vertex vPosB;
	Vertex vElemsW;
	Vertex vElemsB;

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

	// --�����I�u�W�F�N�g�̎Q��-- //
	Object GetWhiteObj();

	// --�����I�u�W�F�N�g�̎Q��-- //
	Object GetBlackObj();

	// --�v���C���[�̏�Ԃ�ύX-- //
	void SetState(int state);

private:
	// --�R���X�g���N�^-- //
	Player();

	void Coliision();

	/// --�����o�֐�END-- ///
};