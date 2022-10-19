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

	// --�X�e�[�W�}�l�[�W���[-- //
	stageManager = StageManager::GetInstance();

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
	stageManager->Initialize();
	stageManager->LoadCSV("proto.csv");
	camera->Initialize((stageManager->GetLine() * stageManager->blockSize) - 800);
	// --�v���C���[-- //
	player->Initialize();

	effect_.Activate();
}

// --�X�V����-- //
void GameScene::Update() {
	if (key->IsTrigger(KEY_INPUT_R)) {
		stageManager->Initialize();
		stageManager->LoadCSV("proto.csv");
		player->Initialize();
		camera->Initialize((stageManager->GetLine() * stageManager->blockSize) - 800);
	}

	// --�v���C���[-- //
	player->Update();

	// --�����蔻��
	col->Update();
}

// --�`�揈��-- //
void GameScene::Draw() {
	for (int i = 0; i < 100; i++) {
		DrawLineAA(0, i * 64 - Camera::GetScroll() - 1280, 640, i * 64 - Camera::GetScroll() - 1280, 0xAAAAAA);
	}

	stageManager->Draw();
	player->Draw();

	effect_.SceneChange();

	DrawFormatString(200, 0, 0x000000, "[R]�Ń��Z�b�g");
}