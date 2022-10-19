#include "StageManager.h"
#include <fstream>
#include <array>
#include <sstream>
#include <DxLib.h>
#include <algorithm>
#include "Util.h"

namespace {
	using namespace std;
}

// --�C���X�^���X��NULL����-- //
StageManager* StageManager::myInstance_ = nullptr;

// --�C���X�^���X�ǂݍ���-- //
StageManager* StageManager::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance_ == nullptr) myInstance_ = new StageManager();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance_;
}

// --���������-- //
void StageManager::Release() {
	// --���������-- //
	delete myInstance_;

	// --NULL����-- //
	myInstance_ = nullptr;
}

// --�R���X�g���N�^-- //
StageManager::StageManager() :
	// --1�}�X�̃T�C�Y-- //
	blockSize_(64)
{
	// --CSV�̍s��-- //
	lineCounter_ = 0;
}

// --�f�X�g���N�^-- //
StageManager::~StageManager()
{
}

void StageManager::Initialize()
{
	// --��Q�����폜-- //
	obstacles_.clear();

	// --�ő�R�C����-- //
	maxCoin_ = 0;

	// --���݂̃R�C����-- //
	coin_ = 0;

	// --CSV�̍s��-- //
	lineCounter_ = 0;
}

void StageManager::Update()
{
}

void StageManager::Draw()
{
	DrawFormatString(500, 0, 0x000000, "�R�C��%d/%d", coin_, maxCoin_);

	// --��Q���̕`��
	for (int i = 0; i < obstacles_.size(); i++) {
		obstacles_[i].Draw();
	}
}

void StageManager::LoadCSV()
{
	lineCounter_ = 0;

	// --�ǂݍ���CSV�t�@�C�����J��-- //
	ifstream ifs(path_);

	// --�ǂݍ���CSV�t�@�C����1�s���ꎞ�I�Ɋi�[����ϐ�-- //
	string line;

	// --[,]��؂�œǂݍ��񂾃f�[�^�ꎞ�I�Ɋi�[����ϐ�-- //
	string tmp;

	// --Y���̃}�X�����J�E���g
	size_t loopCount = 0;

	// --1�s���ǂݍ��ށA�ǂݍ���1�s��line�ϐ��Ɋi�[-- //
	while (getline(ifs, line)) {

		// --[,]��؂�œǂݍ��ނ��߂�istringstream�^�ɂ���-- //
		istringstream line_stream(line);

		// --X���̃}�X�����J�E���g
		int cellNumberX = 0;

		// --[,]��؂�œǂݍ��ށA�ǂݍ��񂾕������tmp�Ɋi�[����-- //
		while (getline(line_stream, tmp, ',')) {
			// --�`���ǂݎ��
			int blockType = stoi(tmp);

			// --�ǂݎ����������0�ȊO�Ȃ��Q���𐶐�����
			if (blockType != None) {
				Obstacle objTmp({ static_cast<float>(cellNumberX * blockSize_ + 32), static_cast<float>(loopCount * blockSize_ + 32) }, blockType);
				obstacles_.push_back(objTmp);

				// --�ǂ݂����������R�C���u���b�N��������-- //
				if (blockType == CoinBlock) {
					// --�ő�R�C����1�ǉ�-- //
					maxCoin_++;
				}

				// --�ǂ݂����������R�C����������-- //
				else if (blockType == Coin) {
					// --�ő�R�C����1�ǉ�-- //
					maxCoin_++;
				}
			}

			// --X���̃}�X�����J�E���g
			cellNumberX++;
		}

		// --Y���̃}�X�����J�E���g
		loopCount++;
	}

	// --��Q���̏�����
	for (int i = 0; i < obstacles_.size(); i++) {
		obstacles_[i].Initialize();
	}

	lineCounter_ = loopCount;
}

int StageManager::GetLineCount() { return lineCounter_; }

// --�u���b�N�T�C�Y���Q��-- //
int StageManager::GetBlockSize() { return blockSize_; }

// --�R�C���̐���1�ǉ�-- //
void StageManager::AddCoin() { coin_++; }

// --�ǂݍ��ރt�@�C�����Z�b�g����-- //
void StageManager::SetCSV(int num) {
	if (num == 1) {
		path_ = "csv/check_progress_gimic1.csv";
	}else if (num == 2) {
		path_ = "csv/check_progress_gimic2.csv";
	}
	else if (num == 3) {
		path_ = "csv/check_progress_gimic3.csv";
	}
}