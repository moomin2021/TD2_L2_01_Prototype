#include "GameScene.h"
#include "DxLib.h"
#include "Camera.h"
#include "SceneManager.h"

// --インスタンスにNULLを代入-- //
GameScene* GameScene::myInstance_ = nullptr;

// --インスタンス読み込み-- //
GameScene* GameScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance_ == nullptr) myInstance_ = new GameScene();

	// --インスタンスを返す-- //
	return myInstance_;
}

// --メモリ解放-- //
void GameScene::Release() {
	// --メモリ解放-- //
	delete myInstance_;

	// --NULLを代入-- //
	myInstance_ = nullptr;
}

// --コンストラクタ-- //
GameScene::GameScene() {
#pragma region クラス定義

	// --キーボード入力-- //
	key_ = Key::GetInstance();

	// --プレイヤー-- //
	player_ = Player::GetInstance();

	// --カメラ-- //
	camera = Camera::GetInstance();

	// --当たり判定
	col = Collision::GetInstance();

	// --ステージマネージャー-- //
	stageManager = StageManager::GetInstance();

#pragma endregion
}

// --デストラクタ-- //
GameScene::~GameScene() {
	// --メモリ解放-- //
	player_->Release();
	camera->Release();
}

// --初期化処理-- //
void GameScene::Initialize() {
	stageManager->Initialize();
	stageManager->LoadCSV();
	camera->Initialize((stageManager->GetLineCount() * stageManager->blockSize_) - 800);
	// --プレイヤー-- //
	player_->Initialize();
}

// --更新処理-- //
void GameScene::Update() {
	if (key_->IsTrigger(KEY_INPUT_R)) {
		stageManager->Initialize();
		stageManager->LoadCSV();
		player_->Initialize();
		camera->Initialize((stageManager->GetLineCount() * stageManager->blockSize_) - 800);
	}

	// --ゲームシーンへ-- //
	if (key_->IsTrigger(KEY_INPUT_Q)) {
		SceneManager::SetScene(STAGESELECTSCENE);
	}

	// --プレイヤー-- //
	player_->Update();

	// --当たり判定
	col->Update();
}

// --描画処理-- //
void GameScene::Draw() {
	for (int i = 0; i < 100; i++) {
		DrawLineAA(0, i * 64 - Camera::GetScroll() - 1280, 640, i * 64 - Camera::GetScroll() - 1280, 0xAAAAAA);
	}

	stageManager->Draw();
	player_->Draw();

	DrawFormatString(200, 0, 0x000000, "[R]でリセット");
	DrawFormatString(200, 20, 0x000000, "[Q]でステージセレクトへ");
}