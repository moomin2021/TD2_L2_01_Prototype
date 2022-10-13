#include "Obstacle.h"
#include "DxLib.h"
#include "Camera.h"

enum struct ShapeType {
	None,		// ����
	Default,	// �����������`
	Iphone,		// �c���������`
	LongWallet,	// ���������قǂ̉����������`
};

// --�R���X�g���N�^
Obstacle::Obstacle(Vector2 pos, int color, int shape) {
	// --���W
	this->pos = pos;

	// --�F
	this->color = 0;
	if (color == 1) this->color = 0xFFFFFF;
	else if (color == 2) this->color = 0x000000;

	// --�`
	this->shape = shape;

	// --X���̔��a
	radiusX = 0.0f;

	// --Y���̕ό`
	radiusY = 0.0f;
}

// --�f�X�g���N�^
Obstacle::~Obstacle() {

}

// --����������
void Obstacle::Initialize() {
	// --�`��ɂ���Ĕ��a��ς���
	if (shape == static_cast<int>(ShapeType::Default)) {
		radiusX = 160;
		radiusY = 96;
	}
	else if (shape == static_cast<int>(ShapeType::Iphone)) {
		radiusX = 96;
		radiusY = 160;
	}
	else if (shape == static_cast<int>(ShapeType::LongWallet)) {
		radiusX = 640;
		radiusY = 256;
	}
}

// --�X�V����
void Obstacle::Update() {

}

// --�`�揈��
void Obstacle::Draw() {
	DrawBoxAA(pos.x - radiusX, pos.y - radiusY - Camera::GetScroll(), pos.x + radiusX, pos.y + radiusY - Camera::GetScroll(), color, true);
}

// --��Q���̍��W���Q��
Vector2 Obstacle::GetPos() { return pos; }

// --��Q����X���̔��a���Q��
float Obstacle::GetRadiusX() { return radiusX; }

// --��Q����Y���̔��a���Q��
float Obstacle::GetRadiusY() { return radiusY; }

// --�F���Q��
int Obstacle::GetColor() { return color; }