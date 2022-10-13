#include "StageSelectScene.h"
#include "DxLib.h"
#include "SceneManager.h"

// --インスタンスにNULLを代入-- //
StageSelectScene* StageSelectScene::myInstance = nullptr;

// --インスタンス読み込み-- //
StageSelectScene* StageSelectScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new StageSelectScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --メモリ解放-- //
void StageSelectScene::Release() {
	// --メモリ解放-- //
	delete myInstance;

	// --NULLを代入-- //
	myInstance = nullptr;
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