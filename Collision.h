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