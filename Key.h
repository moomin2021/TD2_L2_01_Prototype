#pragma once
class Key
{
	/// --�����o�ϐ�-- ///
public:

private:
	char keys[256] = {};
	char oldkeys[256] = {};

	// --�C���X�^���X-- //
	static Key* myInstance_;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Key* GetInstance();

	// --���������-- //
	static void Release();

	// --�X�V����-- //
	void Update();

	/// <summary>
	/// �L�[�������ꂽ�u�Ԃ�
	/// </summary>
	bool IsTrigger(int key_);
	/// <summary>
	/// �L�[��������Ă��邩
	/// </summary>
	bool IsPress(int key_);
	/// <summary>
	/// �L�[�������ꂽ�u�Ԃ�
	/// </summary>
	bool IsRelease(int key_);

private:
	// --�R���X�g���N�^-- //
	Key();

	/// --�����o�֐�END-- ///
};