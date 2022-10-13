#pragma once
#include "Util.h"

class Obstacle {
	/// --�����o�ϐ�-- ///
public:

private:
	// --���W
	Vector2 pos;

	// --�F
	int color;

	// --�`
	unsigned short int shape;

	// --X���̔��a
	float radiusX;

	// --Y���̕ό`
	float radiusY;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�R���X�g���N�^-- //
	Obstacle(Vector2 pos, int color, int shape);

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

	// --�F���Q��
	int GetColor();

	// --��Q����X���̔��a���Q��
	float GetRadiusX();

	// --��Q����Y���̔��a���Q��
	float GetRadiusY();

private:

	/// --�����o�֐�END-- ///
};