#pragma once
#include "StageManager.h"
#include "Key.h"
#include "Player.h"
#include "Camera.h"
#include "Collision.h"

class GameScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static GameScene* myInstance_;
	

#pragma region クラス宣言

	// --キーボード入力-- //
	Key * key_;

	// --プレイヤー-- //
	Player* player_;

	// --カメラ-- //
	Camera* camera;

	// --当たり判定
	Collision* col;

	// --ステージマネージャー
	StageManager* stageManager;
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