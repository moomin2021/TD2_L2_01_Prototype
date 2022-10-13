#pragma once
#include "Key.h"

class TitleScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static TitleScene* myInstance;

#pragma region �N���X��`

	// --�L�[�{�[�h�N���X-- //
	Key* key;

#pragma endregion

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static TitleScene* GetInstance();

	// --���������-- //
	static void Release();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	TitleScene();

	// --�f�X�g���N�^-- //
	~TitleScene();

	/// --�����o�֐�END-- ///
};