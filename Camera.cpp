#include "Camera.h"

// --インスタンスにNULLを代入-- //
Camera* Camera::myInstance = nullptr;

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

}

// --更新処理-- //
void Camera::Update() {

}