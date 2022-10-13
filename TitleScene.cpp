#include "TitleScene.h"
#include "DxLib.h"
#include "SceneManager.h"

// --インスタンスにNULLを代入-- //
TitleScene* TitleScene::myInstance = nullptr;

// --インスタンス読み込み-- //
TitleScene* TitleScene::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new TitleScene();

	// --インスタンスを返す-- //
	return myInstance;
}

// --メモリ解放-- //
void TitleScene::Release() {
	// --メモリ解放-- //
	delete myInstance;

	// --NULLを代入-- //
	myInstance = nullptr;
}

// --コンストラクタ-- //
TitleScene::TitleScene() {
#pragma region クラス定義

	// --キーボードクラス-- //
	key = Key::GetInstance();

#pragma endregion
}

// --デストラクタ-- //
TitleScene::~TitleScene() {

}

// --初期化処理-- //
void TitleScene::Initialize() {

}

// --更新処理-- //
void TitleScene::Update() {
	// --[SPACE]を押したら-- //
	if (key->IsTrigger(KEY_INPUT_SPACE)) {
		// --ステージセレクトシーンに変更-- //
		SceneManager::SetScene(STAGESELECTSCENE);
	}
}

// --描画処理-- //
void TitleScene::Draw() {
	DrawFormatString(0, 20, 0x000000, "[SPACE]を押すと次のシーンへ");
}