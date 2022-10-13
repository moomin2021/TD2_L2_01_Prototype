#pragma once
#include "Key.h"

class TitleScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static TitleScene* myInstance;

#pragma region クラス定義

	// --キーボードクラス-- //
	Key* key;

#pragma endregion

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static TitleScene* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	TitleScene();

	// --デストラクタ-- //
	~TitleScene();

	/// --メンバ関数END-- ///
};