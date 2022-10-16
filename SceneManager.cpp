#include "SceneManager.h"
#include "DxLib.h"

// --インスタンスにNULLを代入-- //
SceneManager* SceneManager::myInstance_ = nullptr;

// --シーンの初期化-- //
int SceneManager::scene = TITLESCENE;

// --シーン変更フラグ-- //
bool SceneManager::isSceneChange = false;

// --インスタンス読み込み-- //
SceneManager* SceneManager::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance_ == nullptr) myInstance_ = new SceneManager();

	// --インスタンスを返す-- //
	return myInstance_;
}

// --メモリ解放-- //
void SceneManager::Release() {
	// --メモリ解放-- //
	delete myInstance_;

	// --NULLを代入-- //
	myInstance_ = nullptr;
}

// --コンストラクタ-- //
SceneManager::SceneManager() {
#pragma region クラス定義

	// --キーボード入力-- //
	key_ = Key::GetInstance();

	// --タイトルシーン-- //
	titleScene = TitleScene::GetInstance();

	// --ステージセレクトシーン-- //
	stageSelectScene = StageSelectScene::GetInstance();

	// --ゲームシーン-- //
	gameScene = GameScene::GetInstance();

	// --リザルトシーン-- //
	resultScene = ResultScene::GetInstance();

#pragma endregion
}

// --デストラクタ-- //
SceneManager::~SceneManager() {

}

// --初期化処理-- //
void SceneManager::Initialize() {
	
}

// --更新処理-- //
void SceneManager::Update() {
	// --キーボード入力の更新処理-- //
	key_->Update();

	// --タイトルシーンの更新処理-- //
	if (scene == TITLESCENE) {
		titleScene->Update();
	}

	// --ステージセレクトシーンの更新処理-- //
	else if (scene == STAGESELECTSCENE) {
		stageSelectScene->Update();
	}

	// --ゲームシーンの更新処理-- //
	else if (scene == GAMESCENE) {
		gameScene->Update();
	}

	// --リザルトシーンの更新処理-- //
	else if (scene == RESULTSCENE) {
		resultScene->Update();
	}

	// --シーン変更がされたら-- //
	if (isSceneChange == true) {
		// --タイトルシーンだったら-- //
		if (scene == TITLESCENE) {
			titleScene->Initialize();
		}

		// --ステージセレクトシーンなら-- //
		else if (scene == STAGESELECTSCENE) {
			stageSelectScene->Initialize();
		}

		// --ゲームシーンなら-- //
		else if (scene == GAMESCENE) {
			gameScene->Initialize();
		}

		// --リザルトシーンなら-- //
		else if (scene == RESULTSCENE) {
			resultScene->Initialize();
		}

		// --シーン変更フラグOFFにする-- //
		isSceneChange = false;
	}
}

// --描画処理-- //
void SceneManager::Draw() {
	// --タイトルシーンの描画処理-- //
	if (scene == TITLESCENE) {
		titleScene->Draw();
	}

	// --ステージセレクトシーンの描画処理-- //
	else if (scene == STAGESELECTSCENE) {
		stageSelectScene->Draw();
	}

	// --ゲームシーンの描画処理-- //
	else if (scene == GAMESCENE) {
		gameScene->Draw();
	}

	// --リザルトシーンの描画処理-- //
	else if (scene == RESULTSCENE) {
		resultScene->Draw();
	}

#pragma region 現在のシーンをデバック表示
	if (scene == TITLESCENE) DrawFormatString(0, 0, 0x000000, "シーン : タイトル");
	else if (scene == STAGESELECTSCENE) DrawFormatString(0, 0, 0x000000, "シーン : ステージセレクト");
	else if (scene == GAMESCENE) DrawFormatString(0, 0, 0x000000, "シーン : ゲーム");
	else if (scene == RESULTSCENE) DrawFormatString(0, 0, 0x000000, "シーン : リザルト");
#pragma endregion
}

// --シーンの変更-- //
void SceneManager::SetScene(int selectScene) {
	// --シーンを変更-- //
	scene = selectScene;

	// --シーン変更フラグをONに-- //
	isSceneChange = true;
}