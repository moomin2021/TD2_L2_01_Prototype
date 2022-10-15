#pragma once
#include "Key.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResulrScene.h"

enum Scene {
	TITLESCENE,
	STAGESELECTSCENE,
	GAMESCENE,
	RESULTSCENE
};

class SceneManager {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static SceneManager* myInstance_;

	// --シーンの初期化フラグ-- //
	static bool isSceneChange;

#pragma region クラスの宣言

	// --キーボード入力-- //
	Key* key;

	// --タイトルシーン-- //
	TitleScene* titleScene;
	
	// --ステージセレクトシーン-- //
	StageSelectScene* stageSelectScene;

	// --ゲームシーン-- //
	GameScene* gameScene;

	// --リザルトシーン-- //
	ResultScene* resultScene;

#pragma endregion

	// --現在のシーン-- //
	static int scene;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static SceneManager* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

	// --シーンの変更-- //
	static void SetScene(int scene);

private:
	// --コンストラクタ-- //
	SceneManager();

	// --デストラクタ-- //
	~SceneManager();

	/// --メンバ関数END-- ///
};