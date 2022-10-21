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
StageSelectScene::StageSelectScene() :
	// --一個スクロールするのにかかる時間-- //
	maxScrollTime_(0.5f)
{
#pragma region クラス定義

	// --キーボード入力
	key_ = Key::GetInstance();

	// --ステージ管理-- //
	stage_ = StageManager::GetInstance();

#pragma endregion

	// --ステージセレクト画像のハンドルを一時的に格納する変数-- //
	int handle[10];

	// --ステージセレクト画像読み込み-- //
	LoadDivGraph("Resources/StageSelectImage.png", 10, 10, 1, 200, 200, handle);

	// --画像の情報-- //
	for (int i = 0; i < 10; i++) {
		stageSelectImage_[i] = { {320.0f, 400.0f + (i * 250.0f)}, 100.0f, 100.0f, handle[i] };
		easeStartPos_[i] = { 320.0f, 400.0f + (i * 250.0f) };
		easeEndPos_[i] = { 320.0f, 400.0f + (i * 250.0f) };
	}

	// --時間計測に必要なデータ変数-- //
	nowCount_ = 0;
	startCount_ = 0;

	// --スクロールしてからの経過時間-- //
	nowScrollTime_ = 0.0f;

	// --現在選んでいるステージ-- //
	selectStage_ = 1;
}

// --デストラクタ-- //
StageSelectScene::~StageSelectScene() {

}

// --初期化処理-- //
void StageSelectScene::Initialize() {
	// --画像の情報-- //
	for (int i = 0; i < 10; i++) {
		stageSelectImage_[i].pos = {320.0f, 400.0f + (i * 250.0f)};
		easeStartPos_[i] = { 320.0f, 400.0f + (i * 250.0f) };
		easeEndPos_[i] = { 320.0f, 400.0f + (i * 250.0f) };
	}

	// --時間計測に必要なデータ変数-- //
	nowCount_ = 0;
	startCount_ = 0;

	// --スクロールしてからの経過時間-- //
	nowScrollTime_ = 0.0f;

	// --現在選んでいるステージ-- //
	selectStage_ = 1;

	float len[10];
	for (int i = 0; i < 10; i++) {
		len[i] = abs(400.0f - stageSelectImage_[i].pos.y);
		len[i] = Util::Clamp(len[i] / 600.0f, 1.0f, 0.0f);
		stageSelectImage_[i].radiusX = 100 * (1.0f - len[i]);
		stageSelectImage_[i].radiusY = 100 * (1.0f - len[i]);
	}
}

// --更新処理-- //
void StageSelectScene::Update() {
	// --[SPACE]を押したら-- //
	if (key_->IsTrigger(KEY_INPUT_SPACE)) {
		//effect_.Activate();
		//Sleep(4 * 1000);
		stage_->SetCSV(selectStage_);
		SceneManager::SetScene(GAMESCENE);
	}

	// --[↑]を押したら-- //
	if (key_->IsTrigger(KEY_INPUT_UP)) {
		// --選んでいるステージが1以外なら-- //
		if (selectStage_ > 1) {
			// --現在のカウントを取得-- //
			startCount_ = GetNowCount();

			for (int i = 0; i < 10; i++) {
				easeStartPos_[i] = stageSelectImage_[i].pos;
				easeEndPos_[i].y += 250.0f;
			}

			selectStage_--;
		}
	}

	// --[↓]を押したら-- //
	else if (key_->IsTrigger(KEY_INPUT_DOWN)) {
		// --選んでいるステージが10以外なら-- //
		if (selectStage_ < 10) {
			// --現在のカウントを取得-- //
			startCount_ = GetNowCount();

			for (int i = 0; i < 10; i++) {
				easeStartPos_[i] = stageSelectImage_[i].pos;
				easeEndPos_[i].y -= 250.0f;
			}

			selectStage_++;
		}
	}

	// --経過時間timeRate[s]の計算
	nowCount_ = GetNowCount();
	nowScrollTime_ = nowCount_ - startCount_;
	nowScrollTime_ = nowScrollTime_ / 1000.0f;

	float timeRate = Util::Clamp(nowScrollTime_ / maxScrollTime_, 1.0f, 0.0f);

	for (int i = 0; i < 10; i++) {
		stageSelectImage_[i].pos.y = easeOutCubic(easeStartPos_[i], easeEndPos_[i], timeRate).y;
	}

	float len[10];
	for (int i = 0; i < 10; i++) {
		len[i] = abs(400.0f - stageSelectImage_[i].pos.y);
		len[i] = Util::Clamp(len[i] / 600.0f, 1.0f, 0.0f);
		stageSelectImage_[i].radiusX = 100 * (1.0f - len[i]);
		stageSelectImage_[i].radiusY = 100 * (1.0f - len[i]);
	}

	DrawFormatString(0, 80, 0x000000, "Pos : %f, %f", stageSelectImage_[0].pos.x, stageSelectImage_[0].pos.y);

	DrawFormatString(0, 100, 0x000000, "StartPos : %f, %f", easeStartPos_[0].x, easeStartPos_[0].y);
	DrawFormatString(0, 120, 0x000000, "EndPos : %f, %f", easeEndPos_[0].x, easeEndPos_[0].y);

	DrawFormatString(0, 140, 0x000000, "timeRate : %f", timeRate);
}

// --描画処理-- //
void StageSelectScene::Draw() {
	DrawFormatString(0, 20, 0x000000, "[SPACE]を押すと次のシーンへ");
	DrawFormatString(0, 40, 0x000000, "scrollTime : %f", nowScrollTime_);
	DrawFormatString(0, 60, 0x000000, "startCount : %d", startCount_);

	for (int i = 0; i < 10; i++) {
		DrawExtendGraph(
			stageSelectImage_[i].pos.x - stageSelectImage_[i].radiusX, stageSelectImage_[i].pos.y - stageSelectImage_[i].radiusY,
			stageSelectImage_[i].pos.x + stageSelectImage_[i].radiusX, stageSelectImage_[i].pos.y + stageSelectImage_[i].radiusY,
			stageSelectImage_[i].handle, false);
	}

	//effect_.SceneChange();
}