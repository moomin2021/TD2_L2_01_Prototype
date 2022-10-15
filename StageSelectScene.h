#pragma once
#include "Key.h"

class StageSelectScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static StageSelectScene* myInstance_;

#pragma region クラス宣言

	// --キーボード入力-- //
	Key* key;

#pragma endregion

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static StageSelectScene* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --デストラクタ-- //
	~StageSelectScene();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	StageSelectScene();

	/// --メンバ関数END-- ///
};