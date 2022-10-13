#include "Camera.h"

// --インスタンスにNULLを代入-- //
Camera* Camera::myInstance = nullptr;

// --スクロール値-- //
float Camera::scrollY = 2400;

// --インスタンス読み込み-- //
Camera* Camera::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new Camera();

	// --インスタンスを返す-- //
	return myInstance;
}

// --メモリ解放-- //
void Camera::Release() {
	// --メモリ解放-- //
	delete myInstance;

	// --NULLを代入-- //
	myInstance = nullptr;
}

// --コンストラクタ-- //
Camera::Camera() {

}

// --デストラクタ-- //
Camera::~Camera() {

}

// --初期化処理-- //
void Camera::Initialize() {
	scrollY = 2400;
}

// --更新処理-- //
void Camera::Update() {

}

// --スクロールの値に加算-- //
void Camera::AddScroll(float value) { scrollY += value; }

// --スクロールの値を参照-- //
float Camera::GetScroll() { return scrollY; }