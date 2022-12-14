#pragma once
#include "Player.h"
#include "StageManager.h"
#include "Util.h"

class Collision {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static Collision* myInstance_;

	Player* player_;

	StageManager* stage_;

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