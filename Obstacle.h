#pragma once
#include "Util.h"

class Obstacle {
	/// --メンバ変数-- ///
public:

private:
	// --オブジェクト-- //
	BoxObj object_;

	// --ブロックの種類
	int blockType_;

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

	// --オブジェクトを参照-- //
	BoxObj GetBoxObj();

	// --ブロックの種類を参照
	int GetBlockType();

private:

	/// --メンバ関数END-- ///
};