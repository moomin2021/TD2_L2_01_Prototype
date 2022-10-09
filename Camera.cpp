#include "Camera.h"

// --�C���X�^���X��NULL����-- //
Camera* Camera::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
Camera* Camera::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new Camera();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --���������-- //
void Camera::Release() {
	// --���������-- //
	delete myInstance;

	// --NULL����-- //
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
Camera::Camera() {

}

// --�f�X�g���N�^-- //
Camera::~Camera() {

}

// --����������-- //
void Camera::Initialize() {

}

// --�X�V����-- //
void Camera::Update() {

}