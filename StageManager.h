#pragma once
#include <memory>
#include <string>
#include <array>
#include <vector>
#include "Obstacle.h"

enum BlockId
{
	None,   // -> �Ȃɂ��Ȃ�
	Coin,// -> �R�C��
	BoundBlock,// -> �o�E���h�u���b�N
	DeathBlock// -> �f�X�u���b�N
};

class StageManager {
	/// --�����o�ϐ�-- ///
public:
	// --�}�b�v-- //
	std::vector<int[10]> map_;

	// --�I�u�W�F�N�g-- //
	std::vector<Obstacle> obstacles_;

	// --1�}�X�̃T�C�Y-- //
	const int blockSize_;

	// csv�s��
	int lineCounter_;

private:
	// --�C���X�^���X-- //
	static StageManager* myInstance_;

	// --�ő�R�C����-- //
	int maxCoin_ = 0;

	// --���݂̃R�C����-- //
	int coin_ = 0;

	// --�ǂݍ���CSV�̃p�X-- //
	std::string path_;

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static StageManager* GetInstance();

	// --���������-- //
	static void Release();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

	// --CSV��ǂݍ���-- //
	void LoadCSV();

	// --�ǂݍ���CSV�̍s�����Q��-- //
	int GetLineCount();

	// --�u���b�N�T�C�Y���Q��-- //
	int GetBlockSize();

	// --�R�C���̐���1�ǉ�-- //
	void AddCoin();

	// --�ǂݍ��ރt�@�C�����Z�b�g����-- //
	void SetCSV(int num);

private:

	 // --�R���X�g���N�^-- //
	StageManager();

	// --�f�X�g���N�^-- //
	~StageManager();

	// --�R�s�[�R���X�g���N�^�֎~-- //
	StageManager(const StageManager&) = delete;

	// --�R�s�[������Z�q�֎~-- //
	StageManager& operator=(const StageManager&) = delete;

	/// --�����o�֐�END-- ///
};