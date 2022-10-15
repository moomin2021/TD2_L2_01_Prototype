#pragma once
#include "Key.h"

class StageSelectScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static StageSelectScene* myInstance_;

#pragma region �N���X�錾

	// --�L�[�{�[�h����-- //
	Key* key;

#pragma endregion

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static StageSelectScene* GetInstance();

	// --���������-- //
	static void Release();

	// --�f�X�g���N�^-- //
	~StageSelectScene();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	StageSelectScene();

	/// --�����o�֐�END-- ///
};