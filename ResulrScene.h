#pragma once

class ResultScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static ResultScene* myInstance_;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static ResultScene* GetInstance();

	// --���������-- //
	static void Release();

	// --�f�X�g���N�^-- //
	~ResultScene();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	ResultScene();

	/// --�����o�֐�END-- ///
};