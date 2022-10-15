#include "ResulrScene.h"

// --インスタンスにNULLを代入-- //
ResultScene* ResultScene::myInstance_ = nullptr;

// --インスタンス読み込み-- //
ResultScene* ResultScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance_ == nullptr) myInstance_ = new ResultScene();

	// --インスタンスを返す-- //
	return myInstance_;
}

// --メモリ解放-- //
void ResultScene::Release() {
	// --メモリ解放-- //
	delete myInstance_;

	// --NULLを代入-- //
	myInstance_ = nullptr;
}

// --コンストラクタ-- //
ResultScene::ResultScene() {

}

// --デストラクタ-- //
ResultScene::~ResultScene() {

}

// --初期化処理-- //
void ResultScene::Initialize() {

}

// --更新処理-- //
void ResultScene::Update() {

}

// --描画処理-- //
void ResultScene::Draw() {

}