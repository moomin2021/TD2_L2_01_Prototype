#include "StageSelectScene.h"
#include "DxLib.h"
#include "SceneManager.h"

// --インスタンスにNULLを代入-- //
StageSelectScene* StageSelectScene::myInstance_ = nullptr;

// --インスタンス読み込み-- //
StageSelectScene* StageSelectScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance_ == nullptr) myInstance_ = new StageSelectScene();

	// --インスタンスを返す-- //
	return myInstance_;
}

// --メモリ解放-- //
void StageSelectScene::Release() {
	// --メモリ解放-- //
	delete myInstance_;

	// --NULLを代入-- //
	myInstance_ = nullptr;
}

// --コンストラクタ-- //
StageSelectScene::StageSelectScene() {
#pragma region クラス定義

	// --キーボード入力
	key = Key::GetInstance();

#pragma endregion
}

// --デストラクタ-- //
StageSelectScene::~StageSelectScene() {

}

// --初期化処理-- //
void StageSelectScene::Initialize() {

}

// --更新処理-- //
void StageSelectScene::Update() {
	// --[SPACE]を押したら-- //
	if (key->IsTrigger(KEY_INPUT_SPACE)) {
		SceneManager::SetScene(GAMESCENE);
	}
}

// --描画処理-- //
void StageSelectScene::Draw() {
	DrawFormatString(0, 20, 0x000000, "[SPACE]を押すと次のシーンへ");
}