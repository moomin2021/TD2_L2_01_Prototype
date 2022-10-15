#include "Camera.h"

// --�C���X�^���X��NULL����-- //
Camera* Camera::myInstance_ = nullptr;

// --�X�N���[���l-- //
float Camera::scrollY = 2400;

// --�C���X�^���X�ǂݍ���-- //
Camera* Camera::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance_ == nullptr) myInstance_ = new Camera();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance_;
}

// --���������-- //
void Camera::Release() {
	// --���������-- //
	delete myInstance_;

	// --NULL����-- //
	myInstance_ = nullptr;
}

// --�R���X�g���N�^-- //
Camera::Camera() {

}

// --�f�X�g���N�^-- //
Camera::~Camera() {

}

// --����������-- //
void Camera::Initialize(int scrollY) {
	this->scrollY = scrollY;
}

// --�X�V����-- //
void Camera::Update() {

}

// --�X�N���[���̒l�ɉ��Z-- //
void Camera::AddScroll(float value) { scrollY += value; }

// --�X�N���[���̒l���Q��-- //
float Camera::GetScroll() { return scrollY; }