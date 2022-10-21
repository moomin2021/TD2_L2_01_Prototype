#pragma once
#include "Player.h"
#include "StageManager.h"
#include "Util.h"

class Collision {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Collision* myInstance_;

	Player* player_;

	StageManager* stage_;

	BoxObj oldObj_;

	// --�����蔻����Ƃ邩-- //
	bool isCollision_ = true;

	// --�u���b�N�̃T�C�Y-- //
	float blockSize_ = 64.0f;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Collision* GetInstance();

	// --���������-- //
	static void Release();

	// --�f�X�g���N�^-- //
	~Collision();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

private:
	// --�R���X�g���N�^-- //
	Collision();

	/// --�����o�֐�END-- ///
};