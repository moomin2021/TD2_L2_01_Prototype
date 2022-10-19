#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"

// --�C���X�^���X��NULL����-- //
TitleScene* TitleScene::myInstance_ = nullptr;

// --�C���X�^���X�ǂݍ���-- //
TitleScene* TitleScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance_ == nullptr) myInstance_ = new TitleScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance_;
}

// --���������-- //
void TitleScene::Release() {
	// --���������-- //
	delete myInstance_;

	// --NULL����-- //
	myInstance_ = nullptr;
}

// --�R���X�g���N�^-- //
TitleScene::TitleScene() {
#pragma region �N���X��`

	// --�L�[�{�[�h�N���X-- //
	key_ = Key::GetInstance();

#pragma endregion
}

// --�f�X�g���N�^-- //
TitleScene::~TitleScene() {

}

// --����������-- //
void TitleScene::Initialize() {

}

// --�X�V����-- //
void TitleScene::Update() {
	// --[SPACE]����������-- //
	if (key_->IsTrigger(KEY_INPUT_SPACE)) {
		// --�X�e�[�W�Z���N�g�V�[���ɕύX-- //
		SceneManager::SetScene(STAGESELECTSCENE);
	}
}

// --�`�揈��-- //
void TitleScene::Draw() {
	DrawFormatString(0, 20, 0x000000, "[SPACE]�������Ǝ��̃V�[����");
}