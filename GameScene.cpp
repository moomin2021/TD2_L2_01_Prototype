#include "GameScene.h"
#include "DxLib.h"
#include "Camera.h"

// --インスタンスにNULLを代入-- //
GameScene* GameScene::myInstance = nullptr;

// --インスタンス読み込み-- //
GameScene* GameScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new GameScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --メモリ解放-- //
void GameScene::Release() {
	// --メモリ解放-- //
	delete myInstance;

	// --NULLを代入-- //
	myInstance = nullptr;
}

// --コンストラクタ-- //
GameScene::GameScene() {
#pragma region クラス定義

	// --キーボード入力-- //
	key = Key::GetInstance();

	// --プレイヤー-- //
	player = Player::GetInstance();

	// --カメラ-- //
	camera = Camera::GetInstance();

	// --当たり判定
	col = Collision::GetInstance();

#pragma endregion
}

// --デストラクタ-- //
GameScene::~GameScene() {
	// --メモリ解放-- //
	player->Release();
	camera->Release();
}

// --初期化処理-- //
void GameScene::Initialize() {
	stageManager_ = StageManager::GetInstance();
	stageManager_->Init();
	stageManager_->LoadCSV("proto.csv");
	// --プレイヤー-- //
	player->Initialize();
}

// --更新処理-- //
void GameScene::Update() {
	// --プレイヤー-- //
	player->Update();

	// --当たり判定
	col->Update();
}

// --描画処理-- //
void GameScene::Draw() {
	stageManager_->Draw();
	player->Draw();

	for (int i = 0; i < 100; i++) {
		DrawLineAA(0, i * 64 - Camera::GetScroll() - 1280, 640, i * 64 - Camera::GetScroll() - 1280, 0xAAAAAA);
	}
}