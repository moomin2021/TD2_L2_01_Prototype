#pragma once
#include <memory>
#include <string>
#include <array>
#include <vector>
#include "Obstacle.h"

enum struct BlockId
{
	None,   // 0
	White,  // 1
	Black   // 2
};

class StageManager {
	/// --�����o�ϐ�-- ///
public:
	// --��Q���N���X�錾-- //
	std::vector<Obstacle> obstacles;

	// --1�}�X�̃T�C�Y-- //
	const int blockSize;

	// csv�s��
	int lineCounter;

private:
	// --�C���X�^���X-- //
	static StageManager* myInstance;

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
	void LoadCSV(std::string path);

	// --�ǂݍ���CSV�̍s�����Q��-- //
	int GetLine();

	// --�u���b�N�T�C�Y���Q��-- //
	int GetBlockSize();

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