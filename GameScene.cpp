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

	// --ステージマネージャー-- //
	stageManager = StageManager::GetInstance();

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
	stageManager->Initialize();
	stageManager->LoadCSV("proto.csv");
	camera->Initialize((stageManager->GetLine() * stageManager->blockSize) - 800);
	// --プレイヤー-- //
	player->Initialize();

	effect_.Activate();
}

// --更新処理-- //
void GameScene::Update() {
	if (key->IsTrigger(KEY_INPUT_R)) {
		stageManager->Initialize();
		stageManager->LoadCSV("proto.csv");
		player->Initialize();
		camera->Initialize((stageManager->GetLine() * stageManager->blockSize) - 800);
	}

	// --プレイヤー-- //
	player->Update();

	// --当たり判定
	col->Update();
}

// --描画処理-- //
void GameScene::Draw() {
	for (int i = 0; i < 100; i++) {
		DrawLineAA(0, i * 64 - Camera::GetScroll() - 1280, 640, i * 64 - Camera::GetScroll() - 1280, 0xAAAAAA);
	}

	stageManager->Draw();
	player->Draw();

	effect_.SceneChange();

	DrawFormatString(200, 0, 0x000000, "[R]でリセット");
}