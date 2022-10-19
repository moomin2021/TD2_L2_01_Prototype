#include "Camera.h"

// --インスタンスにNULLを代入-- //
Camera* Camera::myInstance_ = nullptr;

// --スクロール値-- //
float Camera::scrollY = 2400;

// --インスタンス読み込み-- //
Camera* Camera::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance_ == nullptr) myInstance_ = new Camera();

	// --インスタンスを返す-- //
	return myInstance_;
}

// --メモリ解放-- //
void Camera::Release() {
	// --メモリ解放-- //
	delete myInstance_;

	// --NULLを代入-- //
	myInstance_ = nullptr;
}

// --コンストラクタ-- //
Camera::Camera() {

}

// --デストラクタ-- //
Camera::~Camera() {

}

// --初期化処理-- //
void Camera::Initialize(int scrollY) {
	this->scrollY = scrollY;
}

// --更新処理-- //
void Camera::Update() {

}

// --スクロールの値に加算-- //
void Camera::AddScroll(float value) { scrollY += value; }

// --スクロールの値を参照-- //
float Camera::GetScroll() { return scrollY; }