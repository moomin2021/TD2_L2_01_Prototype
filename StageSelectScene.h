#pragma once
#include "Key.h"
#include "Util.h"
#include "StageManager.h"

class StageSelectScene {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static StageSelectScene* myInstance_;

#pragma region クラス宣言

	// --キーボード入力-- //
	Key* key_;

	// --ステージ管理-- //
	StageManager* stage_;

#pragma endregion

	// --画像の情報-- //
	Image stageSelectImage_[10];

	// --イージング先の画像の情報-- //
	Vector2 easeStartPos_[10];
	Vector2 easeEndPos_[10];

	// --時間計測に必要なデータ変数-- //
	int nowCount_;
	int startCount_;

	// --一個スクロールするのにかかる時間-- //
	const float maxScrollTime_;

	// --スクロールしてからの経過時間-- //
	float nowScrollTime_;

	// --現在選んでいるステージ-- //
	int selectStage_;

	// --ステージ画像の座標-- //

	//
	//Effect effect_{ static_cast<int>(EffectType::LTtoRB2) };

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static StageSelectScene* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --デストラクタ-- //
	~StageSelectScene();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	StageSelectScene();

	/// --メンバ関数END-- ///
};