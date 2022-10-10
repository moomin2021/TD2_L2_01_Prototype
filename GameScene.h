#pragma once
#include "StageManager.h"
#include "Key.h"
#include "Player.h"

class GameScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static GameScene* myInstance;
	StageManager* stageManager_ = nullptr;
	

#pragma region クラス宣言

	// --キーボード入力-- //
	Key * key;

	// --プレイヤー-- //
	Player* player;

#pragma endregion

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static GameScene* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --デストラクタ-- //
	~GameScene();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	GameScene();

	/// --メンバ関数END-- ///
};