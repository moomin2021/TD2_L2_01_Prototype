#pragma once
#include "Key.h"
#include "Util.h"
#include "StageManager.h"

class StageSelectScene {
	/// --�����o�ϐ�-- ///
public:

private:
	// --�C���X�^���X-- //
	static StageSelectScene* myInstance_;

#pragma region �N���X�錾

	// --�L�[�{�[�h����-- //
	Key* key_;

	// --�X�e�[�W�Ǘ�-- //
	StageManager* stage_;

#pragma endregion

	// --�摜�̏��-- //
	Image stageSelectImage_[10];

	// --�C�[�W���O��̉摜�̏��-- //
	Vector2 easeStartPos_[10];
	Vector2 easeEndPos_[10];

	// --���Ԍv���ɕK�v�ȃf�[�^�ϐ�-- //
	int nowCount_;
	int startCount_;

	// --��X�N���[������̂ɂ����鎞��-- //
	const float maxScrollTime_;

	// --�X�N���[�����Ă���̌o�ߎ���-- //
	float nowScrollTime_;

	// --���ݑI��ł���X�e�[�W-- //
	int selectStage_;

	// --�X�e�[�W�摜�̍��W-- //

	//
	//Effect effect_{ static_cast<int>(EffectType::LTtoRB2) };

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static StageSelectScene* GetInstance();

	// --���������-- //
	static void Release();

	// --�f�X�g���N�^-- //
	~StageSelectScene();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

private:
	// --�R���X�g���N�^-- //
	StageSelectScene();

	/// --�����o�֐�END-- ///
};