#include "ResulrScene.h"

// --�C���X�^���X��NULL����-- //
ResultScene* ResultScene::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
ResultScene* ResultScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new ResultScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --���������-- //
void ResultScene::Release() {
	// --���������-- //
	delete myInstance;

	// --NULL����-- //
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
ResultScene::ResultScene() {

}

// --�f�X�g���N�^-- //
ResultScene::~ResultScene() {

}

// --����������-- //
void ResultScene::Initialize() {

}

// --�X�V����-- //
void ResultScene::Update() {

}

// --�`�揈��-- //
void ResultScene::Draw() {

}