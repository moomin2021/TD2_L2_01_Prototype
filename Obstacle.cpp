#include "Obstacle.h"
#include "DxLib.h"
#include "Camera.h"
#include "StageManager.h"

enum struct ShapeType {
	None,		// 無効
	Default,	// 横向き長方形
	Iphone,		// 縦向き長方形
	LongWallet,	// 覆いつくすほどの横向き長方形
};

// --コンストラクタ-- //
Obstacle::Obstacle(Vector2 pos, int blockType) {
	// --オブジェクト-- //
	object_ = { pos, 32.0f, 32.0f };

	// --ブロックの種類
	blockType_ = blockType;
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

	if (blockType_ == BoundBlock) {
		DrawBoxAA(object_.pos.x - object_.radiusX, object_.pos.y - object_.radiusY - Camera::GetScroll(), object_.pos.x + object_.radiusX, object_.pos.y + object_.radiusY - Camera::GetScroll(), 0x000000, true);
		DrawBoxAA(object_.pos.x - object_.radiusX, object_.pos.y - object_.radiusY - Camera::GetScroll(), object_.pos.x + object_.radiusX, object_.pos.y + object_.radiusY - Camera::GetScroll(), 0xFFFFFF, false);
	}

	else if (blockType_ == DeathBlock) {
		DrawBoxAA(object_.pos.x - object_.radiusX, object_.pos.y - object_.radiusY - Camera::GetScroll(), object_.pos.x + object_.radiusX, object_.pos.y + object_.radiusY - Camera::GetScroll(), 0xFF0000, true);
		DrawBoxAA(object_.pos.x - object_.radiusX, object_.pos.y - object_.radiusY - Camera::GetScroll(), object_.pos.x + object_.radiusX, object_.pos.y + object_.radiusY - Camera::GetScroll(), 0xFFFFFF, false);
	}

	else if (blockType_ == Coin) {
		DrawCircleAA(object_.pos.x, object_.pos.y - Camera::GetScroll(), object_.radiusX - 5, 50, 0xFFFF00, true);
		DrawCircleAA(object_.pos.x, object_.pos.y - Camera::GetScroll(), object_.radiusX - 5, 50, 0x000000, false);
	}
}

// --オブジェクトを参照-- //
BoxObj Obstacle::GetBoxObj() {
	return object_;
}

// --ブロックの種類を参照
int Obstacle::GetBlockType() {
	return blockType_;
}