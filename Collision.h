#pragma once
#include "Player.h"
#include "StageManager.h"
#include "Util.h"

struct Box {
	Vector2 pos;

	float radiusX;
	float radiusY;
};

class Collision {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Collision* myInstance_;

	Player* player_;

	StageManager* stage_;

	Box oldPlayerObj_[2];

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