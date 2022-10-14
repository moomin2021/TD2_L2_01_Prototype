#include "Obstacle.h"
#include "DxLib.h"
#include "Camera.h"

enum struct ShapeType {
	None,		// 無効
	Default,	// 横向き長方形
	Iphone,		// 縦向き長方形
	LongWallet,	// 覆いつくすほどの横向き長方形
};

// --コンストラクタ-- //
Obstacle::Obstacle(Vector2 pos, int blockType) {
	// --座標
	pos_ = pos;

	// --ブロックの種類
	blockType_ = blockType;

	// --X軸の半径
	radiusX_ = 32.0f;

	// --Y軸の変形
	radiusY_ = 32.0f;
}

// --デストラクタ
Obstacle::~Obstacle() {

}

// --初期化処理
void Obstacle::Initialize() {
	
}

// --更新処理
void Obstacle::Update() {

}

// --描画処理
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

// --障害物の座標を参照
Vector2 Obstacle::GetPos() { return pos_; }

// --障害物のX軸の半径を参照
float Obstacle::GetRadiusX() { return radiusX_; }

// --障害物のY軸の半径を参照
float Obstacle::GetRadiusY() { return radiusY_; }

// --ブロックの種類を参照
int Obstacle::GetBlockType() { return blockType_; }