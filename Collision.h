#pragma once
#include "Player.h"
#include "StageManager.h"
#include "Util.h"

struct Box {
	Vector2 pos;

	float radiusX;
	float radiusY;
};

class Collision {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static Collision* myInstance_;

	Player* player;

	StageManager* stage;

	Box oldPlayerObj[2];

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static Collision* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --デストラクタ-- //
	~Collision();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

private:
	// --コンストラクタ-- //
	Collision();

	/// --メンバ関数END-- ///
};