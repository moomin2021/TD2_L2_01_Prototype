#include "Key.h"
#include"DxLib.h"

// --�C���X�^���X��NULL����-- //
Key* Key::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
Key* Key::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new Key();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --���������-- //
void Key::Release() {
	// --���������-- //
	delete myInstance;

	// --NULL����-- //
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
Key::Key() {
	
}

// --�X�V����-- //
void Key::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldkeys[i] = keys[i];
	}

	// �ŐV�̃L�[�{�[�h�����擾
	GetHitKeyStateAll(keys);
}

// --�L�[�������ꂽ�u�Ԃ�-- //
bool Key::IsTrigger(char key) { return (keys[key] && !oldkeys[key]); }

// --�L�[��������Ă��邩-- //
bool Key::IsPress(char key) { return keys[key]; }

// --�L�[�������ꂽ�u�Ԃ�-- //
bool Key::IsRelease(char key) { return (!keys[key] && oldkeys[key]); }