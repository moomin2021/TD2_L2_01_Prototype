#include "GameScene.h"

// --�C���X�^���X��NULL����-- //
GameScene* GameScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
GameScene* GameScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new GameScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --���������-- //
void GameScene::Release() {
	// --���������-- //
	delete myInstance;

	// --NULL����-- //
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
GameScene::GameScene() {

}

// --�f�X�g���N�^-- //
GameScene::~GameScene() {

}

// --����������-- //
void GameScene::Initialize() {
	stageManager_ = StageManager::GetInstance();
	stageManager_->Init();
	stageManager_->LoadCSV("proto.csv");
}

// --�X�V����-- //
void GameScene::Update() {

}

// --�`�揈��-- //
void GameScene::Draw() {
	stageManager_->Draw();
}