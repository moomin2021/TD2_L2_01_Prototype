#pragma once

class Camera {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Camera* myInstance;

	// --�X�N���[��-- //
	static float scrollY;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Camera* GetInstance();

	// --���������-- //
	static void Release();

	// --�f�X�g���N�^-- //
	~Camera();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�X�N���[���̒l�ɉ��Z-- //
	static void AddScroll(float value);

	// --�X�N���[���̒l���Q��-- //
	static float GetScroll();

private:
	// --�R���X�g���N�^-- //
	Camera();

	/// --�����o�֐�END-- ///
};