#pragma once
#include "Util.h"

class Obstacle {
	/// --メンバ変数-- ///
public:

private:
	// --座標
	Vector2 pos_;

	// --ブロックの種類
	int blockType_;

	// --X軸の半径
	float radiusX_;

	// --Y軸の変形
	float radiusY_;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --コンストラクタ-- //
	Obstacle(Vector2 pos, int blockType);

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

	// --障害物のX軸の半径を参照
	float GetRadiusX();

	// --障害物のY軸の半径を参照
	float GetRadiusY();

	// --ブロックの種類を参照
	int GetBlockType();

private:

	/// --メンバ関数END-- ///
};