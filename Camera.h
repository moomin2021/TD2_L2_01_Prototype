#pragma once

class Camera {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static Camera* myInstance;

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

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	Camera();

	/// --�����o�֐�END-- ///
};