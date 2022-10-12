#pragma once
#include "Util.h"

class Obstacle {
	/// --メンバ変数-- ///
public:

private:
	// --座標
	Vector2 pos;

	// --色
	int color;

	// --形
	unsigned short int shape;

	// --X軸の半径
	float radiusX;

	// --Y軸の変形
	float radiusY;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --コンストラクタ-- //
	Obstacle(Vector2 pos, int color, int shape);

	// --デストラクタ-- //
	~Obstacle();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

	// --障害物の座標を参照
	Vector2 GetPos();

	// --色を参照
	int GetColor();

	// --障害物のX軸の半径を参照
	float GetRadiusX();

	// --障害物のY軸の半径を参照
	float GetRadiusY();

private:

	/// --メンバ関数END-- ///
};