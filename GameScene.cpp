#include "GameScene.h"

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

}

// --デストラクタ-- //
GameScene::~GameScene() {

}

// --初期化処理-- //
void GameScene::Initialize() {
	stageManager_ = StageManager::GetInstance();
	stageManager_->Init();
	stageManager_->LoadCSV("proto.csv");
}

// --更新処理-- //
void GameScene::Update() {

}

// --描画処理-- //
void GameScene::Draw() {
	stageManager_->Draw();
}