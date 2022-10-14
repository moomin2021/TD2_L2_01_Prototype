#include "Obstacle.h"
#include "DxLib.h"
#include "Camera.h"

enum struct ShapeType {
	None,		// ����
	Default,	// �����������`
	Iphone,		// �c���������`
	LongWallet,	// ���������قǂ̉����������`
};

// --�R���X�g���N�^-- //
Obstacle::Obstacle(Vector2 pos, int blockType) {
	// --���W
	pos_ = pos;

	// --�u���b�N�̎��
	blockType_ = blockType;

	// --X���̔��a
	radiusX_ = 32.0f;

	// --Y���̕ό`
	radiusY_ = 32.0f;
}

// --�f�X�g���N�^
Obstacle::~Obstacle() {

}

// --����������
void Obstacle::Initialize() {
	
}

// --�X�V����
void Obstacle::Update() {

}

// --�`�揈��
void Obstacle::Draw() {

	if (blockType_ == 1) {
		DrawBoxAA(pos_.x - radiusX_, pos_.y - radiusY_ - Camera::GetScroll(), pos_.x + radiusX_, pos_.y + radiusY_ - Camera::GetScroll(), 0x000000, true);
		DrawBoxAA(pos_.x - radiusX_, pos_.y - radiusY_ - Camera::GetScroll(), pos_.x + radiusX_, pos_.y + radiusY_ - Camera::GetScroll(), 0xFFFFFF, false);
	}

	else if (blockType_ == 2) {
		DrawBoxAA(pos_.x - radiusX_, pos_.y - radiusY_ - Camera::GetScroll(), pos_.x + radiusX_, pos_.y + radiusY_ - Camera::GetScroll(), 0x000000, true);
		DrawBoxAA(pos_.x - radiusX_, pos_.y - radiusY_ - Camera::GetScroll(), pos_.x + radiusX_, pos_.y + radiusY_ - Camera::GetScroll(), 0xFFFFFF, false);
		DrawCircleAA(pos_.x, pos_.y - Camera::GetScroll(), radiusX_ - 5, 50, 0xFFFF00, true);
		DrawCircleAA(pos_.x, pos_.y - Camera::GetScroll(), radiusX_ - 5, 50, 0x000000, false);
	}

	else if (blockType_ == 3) {
		DrawCircleAA(pos_.x, pos_.y - Camera::GetScroll(), radiusX_ - 5, 50, 0xFFFF00, true);
		DrawCircleAA(pos_.x, pos_.y - Camera::GetScroll(), radiusX_ - 5, 50, 0x000000, false);
	}
}

// --��Q���̍��W���Q��
Vector2 Obstacle::GetPos() { return pos_; }

// --��Q����X���̔��a���Q��
float Obstacle::GetRadiusX() { return radiusX_; }

// --��Q����Y���̔��a���Q��
float Obstacle::GetRadiusY() { return radiusY_; }

// --�u���b�N�̎�ނ��Q��
int Obstacle::GetBlockType() { return blockType_; }