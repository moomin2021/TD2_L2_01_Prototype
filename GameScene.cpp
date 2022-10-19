#include "GameScene.h"
#include "DxLib.h"
#include "Camera.h"
#include "SceneManager.h"

// --�C���X�^���X��NULL����-- //
GameScene* GameScene::myInstance_ = nullptr;

// --�C���X�^���X�ǂݍ���-- //
GameScene* GameScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance_ == nullptr) myInstance_ = new GameScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance_;
}

// --���������-- //
void GameScene::Release() {
	// --���������-- //
	delete myInstance_;

	// --NULL����-- //
	myInstance_ = nullptr;
}

// --�R���X�g���N�^-- //
GameScene::GameScene() {
#pragma region �N���X��`

	// --�L�[�{�[�h����-- //
	key_ = Key::GetInstance();

	// --�v���C���[-- //
	player_ = Player::GetInstance();

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
	player_->Release();
	camera->Release();
}

// --����������-- //
void GameScene::Initialize() {
	stageManager->Initialize();
	stageManager->LoadCSV();
	camera->Initialize((stageManager->GetLineCount() * stageManager->blockSize_) - 800);
	// --�v���C���[-- //
	player_->Initialize();
}

// --�X�V����-- //
void GameScene::Update() {
	if (key_->IsTrigger(KEY_INPUT_R)) {
		stageManager->Initialize();
		stageManager->LoadCSV();
		player_->Initialize();
		camera->Initialize((stageManager->GetLineCount() * stageManager->blockSize_) - 800);
	}

	// --�Q�[���V�[����-- //
	if (key_->IsTrigger(KEY_INPUT_Q)) {
		SceneManager::SetScene(STAGESELECTSCENE);
	}

	// --�v���C���[-- //
	player_->Update();

	// --�����蔻��
	col->Update();
}

// --�`�揈��-- //
void GameScene::Draw() {
	for (int i = 0; i < 100; i++) {
		DrawLineAA(0, i * 64 - Camera::GetScroll() - 1280, 640, i * 64 - Camera::GetScroll() - 1280, 0xAAAAAA);
	}

	stageManager->Draw();
	player_->Draw();

	DrawFormatString(200, 0, 0x000000, "[R]�Ń��Z�b�g");
	DrawFormatString(200, 20, 0x000000, "[Q]�ŃX�e�[�W�Z���N�g��");
}