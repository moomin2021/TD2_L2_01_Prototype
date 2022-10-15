#include "ResulrScene.h"
#include "DxLib.h"
#include "SceneManager.h"

// --�C���X�^���X��NULL����-- //
ResultScene* ResultScene::myInstance_ = nullptr;

// --�C���X�^���X�ǂݍ���-- //
ResultScene* ResultScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance_ == nullptr) myInstance_ = new ResultScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance_;
}

// --���������-- //
void ResultScene::Release() {
	// --���������-- //
	delete myInstance_;

	// --NULL����-- //
	myInstance_ = nullptr;
}

// --�R���X�g���N�^-- //
ResultScene::ResultScene() {
#pragma region �N���X��`

	// --�L�[�{�[�h�N���X-- //
	key = Key::GetInstance();

#pragma endregion
}

// --�f�X�g���N�^-- //
ResultScene::~ResultScene() {

}

// --����������-- //
void ResultScene::Initialize() {

}

// --�X�V����-- //
void ResultScene::Update() {
	// --[SPACE]����������-- //
	if (key->IsTrigger(KEY_INPUT_SPACE)) {
		// --�X�e�[�W�Z���N�g�V�[���ɕύX-- //
		SceneManager::SetScene(STAGESELECTSCENE);
	}
}

// --�`�揈��-- //
void ResultScene::Draw() {
	DrawFormatString(0, 20, 0x000000, "[SPACE]�������Ǝ��̃V�[����");
}