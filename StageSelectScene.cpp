#include "StageSelectScene.h"
#include "DxLib.h"
#include "SceneManager.h"

// --�C���X�^���X��NULL����-- //
StageSelectScene* StageSelectScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
StageSelectScene* StageSelectScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new StageSelectScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --���������-- //
void StageSelectScene::Release() {
	// --���������-- //
	delete myInstance;

	// --NULL����-- //
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
StageSelectScene::StageSelectScene() {
#pragma region �N���X��`

	// --�L�[�{�[�h����
	key = Key::GetInstance();

#pragma endregion
}

// --�f�X�g���N�^-- //
StageSelectScene::~StageSelectScene() {

}

// --����������-- //
void StageSelectScene::Initialize() {

}

// --�X�V����-- //
void StageSelectScene::Update() {
	// --[SPACE]����������-- //
	if (key->IsTrigger(KEY_INPUT_SPACE)) {
		SceneManager::SetScene(GAMESCENE);
	}
}

// --�`�揈��-- //
void StageSelectScene::Draw() {
	DrawFormatString(0, 20, 0x000000, "[SPACE]�������Ǝ��̃V�[����");
}