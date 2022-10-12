#include "GameScene.h"
#include "DxLib.h"
#include "Camera.h"

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
#pragma region �N���X��`

	// --�L�[�{�[�h����-- //
	key = Key::GetInstance();

	// --�v���C���[-- //
	player = Player::GetInstance();

	// --�J����-- //
	camera = Camera::GetInstance();

	// --�����蔻��
	col = Collision::GetInstance();

#pragma endregion
}

// --�f�X�g���N�^-- //
GameScene::~GameScene() {
	// --���������-- //
	player->Release();
	camera->Release();
}

// --����������-- //
void GameScene::Initialize() {
	stageManager_ = StageManager::GetInstance();
	stageManager_->Init();
	stageManager_->LoadCSV("proto.csv");
	// --�v���C���[-- //
	player->Initialize();
}

// --�X�V����-- //
void GameScene::Update() {
	// --�v���C���[-- //
	player->Update();

	// --�����蔻��
	col->Update();
}

// --�`�揈��-- //
void GameScene::Draw() {
	stageManager_->Draw();
	player->Draw();

	for (int i = 0; i < 100; i++) {
		DrawLineAA(0, i * 64 - Camera::GetScroll() - 1280, 640, i * 64 - Camera::GetScroll() - 1280, 0xAAAAAA);
	}
}