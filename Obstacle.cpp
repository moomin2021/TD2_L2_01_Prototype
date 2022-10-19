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
	// --�I�u�W�F�N�g-- //
	object_ = { pos, 32.0f, 32.0f };

	// --�u���b�N�̎��
	blockType_ = blockType;
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
		DrawBoxAA(object_.pos.x - object_.radiusX, object_.pos.y - object_.radiusY - Camera::GetScroll(), object_.pos.x + object_.radiusX, object_.pos.y + object_.radiusY - Camera::GetScroll(), 0x000000, true);
		DrawBoxAA(object_.pos.x - object_.radiusX, object_.pos.y - object_.radiusY - Camera::GetScroll(), object_.pos.x + object_.radiusX, object_.pos.y + object_.radiusY - Camera::GetScroll(), 0xFFFFFF, false);
	}

	else if (blockType_ == 2) {
		DrawBoxAA(object_.pos.x - object_.radiusX, object_.pos.y - object_.radiusY - Camera::GetScroll(), object_.pos.x + object_.radiusX, object_.pos.y + object_.radiusY - Camera::GetScroll(), 0x000000, true);
		DrawBoxAA(object_.pos.x - object_.radiusX, object_.pos.y - object_.radiusY - Camera::GetScroll(), object_.pos.x + object_.radiusX, object_.pos.y + object_.radiusY - Camera::GetScroll(), 0xFFFFFF, false);
		DrawCircleAA(object_.pos.x, object_.pos.y - Camera::GetScroll(), object_.radiusX - 5, 50, 0xFFFF00, true);
		DrawCircleAA(object_.pos.x, object_.pos.y - Camera::GetScroll(), object_.radiusX - 5, 50, 0x000000, false);
	}

	else if (blockType_ == 3) {
		DrawCircleAA(object_.pos.x, object_.pos.y - Camera::GetScroll(), object_.radiusX - 5, 50, 0xFFFF00, true);
		DrawCircleAA(object_.pos.x, object_.pos.y - Camera::GetScroll(), object_.radiusX - 5, 50, 0x000000, false);
	}

	else if (blockType_ == 4) {
		DrawBoxAA(object_.pos.x - object_.radiusX, object_.pos.y - object_.radiusY - Camera::GetScroll(), object_.pos.x + object_.radiusX, object_.pos.y + object_.radiusY - Camera::GetScroll(), 0x000000, true);
		DrawBoxAA(object_.pos.x - object_.radiusX, object_.pos.y - object_.radiusY - Camera::GetScroll(), object_.pos.x + object_.radiusX, object_.pos.y + object_.radiusY - Camera::GetScroll(), 0xFFFFFF, false);
	}
}

// --�I�u�W�F�N�g���Q��-- //
BoxObj Obstacle::GetBoxObj() {
	return object_;
}

// --�u���b�N�̎�ނ��Q��
int Obstacle::GetBlockType() {
	return blockType_;
}