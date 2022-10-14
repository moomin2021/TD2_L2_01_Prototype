#pragma once
#include "Util.h"

class Obstacle {
	/// --�����o�ϐ�-- ///
public:

private:
	// --���W
	Vector2 pos_;

	// --�u���b�N�̎��
	int blockType_;

	// --X���̔��a
	float radiusX_;

	// --Y���̕ό`
	float radiusY_;

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

	// --��Q���̍��W���Q��
	Vector2 GetPos();

	// --��Q����X���̔��a���Q��
	float GetRadiusX();

	// --��Q����Y���̔��a���Q��
	float GetRadiusY();

	// --�u���b�N�̎�ނ��Q��
	int GetBlockType();

private:

	/// --�����o�֐�END-- ///
};