#include "StageSelectScene.h"
#include "DxLib.h"
#include "SceneManager.h"

// --�C���X�^���X��NULL����-- //
StageSelectScene* StageSelectScene::myInstance_ = nullptr;

// --�C���X�^���X�ǂݍ���-- //
StageSelectScene* StageSelectScene::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance_ == nullptr) myInstance_ = new StageSelectScene();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance_;
}

// --���������-- //
void StageSelectScene::Release() {
	// --���������-- //
	delete myInstance_;

	// --NULL����-- //
	myInstance_ = nullptr;
}

// --�R���X�g���N�^-- //
StageSelectScene::StageSelectScene() :
	// --��X�N���[������̂ɂ����鎞��-- //
	maxScrollTime_(0.5f)
{
#pragma region �N���X��`

	// --�L�[�{�[�h����
	key_ = Key::GetInstance();

	// --�X�e�[�W�Ǘ�-- //
	stage_ = StageManager::GetInstance();

#pragma endregion

	// --�X�e�[�W�Z���N�g�摜�̃n���h�����ꎞ�I�Ɋi�[����ϐ�-- //
	int handle[10];

	// --�X�e�[�W�Z���N�g�摜�ǂݍ���-- //
	LoadDivGraph("Resources/StageSelectImage.png", 10, 10, 1, 200, 200, handle);

	// --�摜�̏��-- //
	for (int i = 0; i < 10; i++) {
		stageSelectImage_[i] = { {320.0f, 400.0f + (i * 250.0f)}, 100.0f, 100.0f, handle[i] };
		easeStartPos_[i] = { 320.0f, 400.0f + (i * 250.0f) };
		easeEndPos_[i] = { 320.0f, 400.0f + (i * 250.0f) };
	}

	// --���Ԍv���ɕK�v�ȃf�[�^�ϐ�-- //
	nowCount_ = 0;
	startCount_ = 0;

	// --�X�N���[�����Ă���̌o�ߎ���-- //
	nowScrollTime_ = 0.0f;

	// --���ݑI��ł���X�e�[�W-- //
	selectStage_ = 1;
}

// --�f�X�g���N�^-- //
StageSelectScene::~StageSelectScene() {

}

// --����������-- //
void StageSelectScene::Initialize() {
	// --�摜�̏��-- //
	for (int i = 0; i < 10; i++) {
		stageSelectImage_[i].pos = {320.0f, 400.0f + (i * 250.0f)};
		easeStartPos_[i] = { 320.0f, 400.0f + (i * 250.0f) };
		easeEndPos_[i] = { 320.0f, 400.0f + (i * 250.0f) };
	}

	// --���Ԍv���ɕK�v�ȃf�[�^�ϐ�-- //
	nowCount_ = 0;
	startCount_ = 0;

	// --�X�N���[�����Ă���̌o�ߎ���-- //
	nowScrollTime_ = 0.0f;

	// --���ݑI��ł���X�e�[�W-- //
	selectStage_ = 1;

	float len[10];
	for (int i = 0; i < 10; i++) {
		len[i] = abs(400.0f - stageSelectImage_[i].pos.y);
		len[i] = Util::Clamp(len[i] / 600.0f, 1.0f, 0.0f);
		stageSelectImage_[i].radiusX = 100 * (1.0f - len[i]);
		stageSelectImage_[i].radiusY = 100 * (1.0f - len[i]);
	}
}

// --�X�V����-- //
void StageSelectScene::Update() {
	// --[SPACE]����������-- //
	if (key_->IsTrigger(KEY_INPUT_SPACE)) {
		//effect_.Activate();
		//Sleep(4 * 1000);
		stage_->SetCSV(selectStage_);
		SceneManager::SetScene(GAMESCENE);
	}

	// --[��]����������-- //
	if (key_->IsTrigger(KEY_INPUT_UP)) {
		// --�I��ł���X�e�[�W��1�ȊO�Ȃ�-- //
		if (selectStage_ > 1) {
			// --���݂̃J�E���g���擾-- //
			startCount_ = GetNowCount();

			for (int i = 0; i < 10; i++) {
				easeStartPos_[i] = stageSelectImage_[i].pos;
				easeEndPos_[i].y += 250.0f;
			}

			selectStage_--;
		}
	}

	// --[��]����������-- //
	else if (key_->IsTrigger(KEY_INPUT_DOWN)) {
		// --�I��ł���X�e�[�W��10�ȊO�Ȃ�-- //
		if (selectStage_ < 10) {
			// --���݂̃J�E���g���擾-- //
			startCount_ = GetNowCount();

			for (int i = 0; i < 10; i++) {
				easeStartPos_[i] = stageSelectImage_[i].pos;
				easeEndPos_[i].y -= 250.0f;
			}

			selectStage_++;
		}
	}

	// --�o�ߎ���timeRate[s]�̌v�Z
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

// --�`�揈��-- //
void StageSelectScene::Draw() {
	DrawFormatString(0, 20, 0x000000, "[SPACE]�������Ǝ��̃V�[����");
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