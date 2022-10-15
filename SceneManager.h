#pragma once
#include "Key.h"
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "ResulrScene.h"

enum Scene {
	TITLESCENE,
	STAGESELECTSCENE,
	GAMESCENE,
	RESULTSCENE
};

class SceneManager {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static SceneManager* myInstance_;

	// --�V�[���̏������t���O-- //
	static bool isSceneChange;

#pragma region �N���X�̐錾

	// --�L�[�{�[�h����-- //
	Key* key;

	// --�^�C�g���V�[��-- //
	TitleScene* titleScene;
	
	// --�X�e�[�W�Z���N�g�V�[��-- //
	StageSelectScene* stageSelectScene;

	// --�Q�[���V�[��-- //
	GameScene* gameScene;

	// --���U���g�V�[��-- //
	ResultScene* resultScene;

#pragma endregion

	// --���݂̃V�[��-- //
	static int scene;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static SceneManager* GetInstance();

	// --���������-- //
	static void Release();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

	// --�V�[���̕ύX-- //
	static void SetScene(int scene);

private:
	// --�R���X�g���N�^-- //
	SceneManager();

	// --�f�X�g���N�^-- //
	~SceneManager();

	/// --�����o�֐�END-- ///
};