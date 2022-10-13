#include "ResulrScene.h"

// --インスタンスにNULLを代入-- //
ResultScene* ResultScene::myInstance = nullptr;

// --インスタンス読み込み-- //
ResultScene* ResultScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new ResultScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --メモリ解放-- //
void ResultScene::Release() {
	// --メモリ解放-- //
	delete myInstance;

	// --NULLを代入-- //
	myInstance = nullptr;
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