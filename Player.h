#pragma once
#include "Key.h"
#include "Vector2.h"

struct Object {
	// --���W-- //
	Vector2 pos;

	// --���a-- //
	float radius;
};

class Player {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Player* myInstance;

	// --�N���X�錾-- //
	Key* key;

	// --�����v���C���[�I�u�W�F�N�g-- //
	Object whiteObj;

	// --�����v���C���[�I�u�W�F�N�g-- //
	Object blackObj;

	// --���ړ����x�̊�b�l-- //
	const float defaultSpeedX;

	// --���ړ��̑��x-- //
	float speedX;

	// --�ړ��������-- //
	int direction;

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

private:
	// --�R���X�g���N�^-- //
	Player();

	/// --�����o�֐�END-- ///
};