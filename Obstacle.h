#pragma once
#include "Util.h"

class Obstacle {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�I�u�W�F�N�g-- //
	BoxObj object_;

	// --�u���b�N�̎��
	int blockType_;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�R���X�g���N�^-- //
	Obstacle(Vector2 pos, int blockType);

	// --�f�X�g���N�^-- //
	~Obstacle();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

	// --�I�u�W�F�N�g���Q��-- //
	BoxObj GetBoxObj();

	// --�u���b�N�̎�ނ��Q��
	int GetBlockType();

private:

	/// --�����o�֐�END-- ///
};