#include "SceneManager.h"
#include "DxLib.h"

// --�C���X�^���X��NULL����-- //
SceneManager* SceneManager::myInstance_ = nullptr;

// --�V�[���̏�����-- //
int SceneManager::scene = TITLESCENE;

// --�V�[���ύX�t���O-- //
bool SceneManager::isSceneChange = false;

// --�C���X�^���X�ǂݍ���-- //
SceneManager* SceneManager::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance_ == nullptr) myInstance_ = new SceneManager();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance_;
}

// --���������-- //
void SceneManager::Release() {
	// --���������-- //
	delete myInstance_;

	// --NULL����-- //
	myInstance_ = nullptr;
}

// --�R���X�g���N�^-- //
SceneManager::SceneManager() {
#pragma region �N���X��`

	// --�L�[�{�[�h����-- //
	key_ = Key::GetInstance();

	// --�^�C�g���V�[��-- //
	titleScene = TitleScene::GetInstance();

	// --�X�e�[�W�Z���N�g�V�[��-- //
	stageSelectScene = StageSelectScene::GetInstance();

	// --�Q�[���V�[��-- //
	gameScene = GameScene::GetInstance();

	// --���U���g�V�[��-- //
	resultScene = ResultScene::GetInstance();

#pragma endregion
}

// --�f�X�g���N�^-- //
SceneManager::~SceneManager() {

}

// --����������-- //
void SceneManager::Initialize() {
	
}

// --�X�V����-- //
void SceneManager::Update() {
	// --�L�[�{�[�h���͂̍X�V����-- //
	key_->Update();

	// --�^�C�g���V�[���̍X�V����-- //
	if (scene == TITLESCENE) {
		titleScene->Update();
	}

	// --�X�e�[�W�Z���N�g�V�[���̍X�V����-- //
	else if (scene == STAGESELECTSCENE) {
		stageSelectScene->Update();
	}

	// --�Q�[���V�[���̍X�V����-- //
	else if (scene == GAMESCENE) {
		gameScene->Update();
	}

	// --���U���g�V�[���̍X�V����-- //
	else if (scene == RESULTSCENE) {
		resultScene->Update();
	}

	// --�V�[���ύX�����ꂽ��-- //
	if (isSceneChange == true) {
		// --�^�C�g���V�[����������-- //
		if (scene == TITLESCENE) {
			titleScene->Initialize();
		}

		// --�X�e�[�W�Z���N�g�V�[���Ȃ�-- //
		else if (scene == STAGESELECTSCENE) {
			stageSelectScene->Initialize();
		}

		// --�Q�[���V�[���Ȃ�-- //
		else if (scene == GAMESCENE) {
			gameScene->Initialize();
		}

		// --���U���g�V�[���Ȃ�-- //
		else if (scene == RESULTSCENE) {
			resultScene->Initialize();
		}

		// --�V�[���ύX�t���OOFF�ɂ���-- //
		isSceneChange = false;
	}
}

// --�`�揈��-- //
void SceneManager::Draw() {
	// --�^�C�g���V�[���̕`�揈��-- //
	if (scene == TITLESCENE) {
		titleScene->Draw();
	}

	// --�X�e�[�W�Z���N�g�V�[���̕`�揈��-- //
	else if (scene == STAGESELECTSCENE) {
		stageSelectScene->Draw();
	}

	// --�Q�[���V�[���̕`�揈��-- //
	else if (scene == GAMESCENE) {
		gameScene->Draw();
	}

	// --���U���g�V�[���̕`�揈��-- //
	else if (scene == RESULTSCENE) {
		resultScene->Draw();
	}

#pragma region ���݂̃V�[�����f�o�b�N�\��
	if (scene == TITLESCENE) DrawFormatString(0, 0, 0x000000, "�V�[�� : �^�C�g��");
	else if (scene == STAGESELECTSCENE) DrawFormatString(0, 0, 0x000000, "�V�[�� : �X�e�[�W�Z���N�g");
	else if (scene == GAMESCENE) DrawFormatString(0, 0, 0x000000, "�V�[�� : �Q�[��");
	else if (scene == RESULTSCENE) DrawFormatString(0, 0, 0x000000, "�V�[�� : ���U���g");
#pragma endregion
}

// --�V�[���̕ύX-- //
void SceneManager::SetScene(int selectScene) {
	// --�V�[����ύX-- //
	scene = selectScene;

	// --�V�[���ύX�t���O��ON��-- //
	isSceneChange = true;
}