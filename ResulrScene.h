#pragma once
#include "Key.h"

class ResultScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static ResultScene* myInstance_;

#pragma region クラス定義

	// --キーボードクラス-- //
	Key* key_;

#pragma endregion

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static ResultScene* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --デストラクタ-- //
	~ResultScene();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	ResultScene();

	/// --メンバ関数END-- ///
};