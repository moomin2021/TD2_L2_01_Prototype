#pragma once
#include "StageManager.h"
#include "Key.h"
#include "Player.h"
#include "Camera.h"

class GameScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static GameScene* myInstance;
	

#pragma region �N���X�錾

	// --�L�[�{�[�h����-- //
	Key * key;

	// --�v���C���[-- //
	Player* player;

	// --�J����-- //
	Camera* camera;

	// 
	StageManager* stageManager_ = nullptr;
#pragma endregion

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static GameScene* GetInstance();

	// --���������-- //
	static void Release();

	// --�f�X�g���N�^-- //
	~GameScene();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	GameScene();

	/// --�����o�֐�END-- ///
};