#include "Obstacle.h"
#include "DxLib.h"
#include "Camera.h"

// --コンストラクタ
Obstacle::Obstacle(Vector2 pos, unsigned short int color, unsigned short int shape) {
	// --座標
	this->pos = pos;

	// --色
	this->color = 0;
	if (color == 1) this->color = 0xFFFFFF;
	else if (color == 2) this->color = 0x000000;

	// --形
	this->shape = shape;

	// --X軸の半径
	radiusX = 0.0f;

	// --Y軸の変形
	radiusY = 0.0f;
}

// --デストラクタ
Obstacle::~Obstacle() {

}

// --初期化処理
void Obstacle::Initialize() {
	// --形状によって半径を変える
	if (shape == 1) {
		radiusX = 160;
		radiusY = 96;
	}
}

// --更新処理
void Obstacle::Update() {

}

// --描画処理
void Obstacle::Draw() {
	DrawBoxAA(pos.x - radiusX, pos.y - radiusY - Camera::GetScroll(), pos.x + radiusX, pos.y + radiusY - Camera::GetScroll(), color, true);
}

// --障害物の座標を参照
Vector2 Obstacle::GetPos() { return pos; }

// --障害物のX軸の半径を参照
float Obstacle::GetRadiusX() { return radiusX; }

// --障害物のY軸の半径を参照
float Obstacle::GetRadiusY() { return radiusY; }

// --色を参照
int Obstacle::GetColor() { return color; }