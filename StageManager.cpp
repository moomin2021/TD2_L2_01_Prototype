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
StageManager* StageManager::myInstance = nullptr;

// --�C���X�^���X�ǂݍ���-- //
StageManager* StageManager::GetInstance() {
	// --�C���X�^���X�����������琶������-- //
	if (myInstance == nullptr) myInstance = new StageManager();

	// --�C���X�^���X��Ԃ�-- //
	return myInstance;
}

// --���������-- //
void StageManager::Release() {
	// --���������-- //
	delete myInstance;

	// --NULL����-- //
	myInstance = nullptr;
}

// --�R���X�g���N�^-- //
StageManager::StageManager() :
	// --1�}�X�̃T�C�Y-- //
	blockSize(64)
{

}

// --�f�X�g���N�^-- //
StageManager::~StageManager()
{
}

void StageManager::Initialize()
{
	// --��Q�����폜-- //
	obstacles.clear();

	// --�ő�R�C����-- //
	maxCoin_ = 0;

	// --���݂̃R�C����-- //
	coin_ = 0;
}

void StageManager::Update()
{
}

void StageManager::Draw()
{
	DrawFormatString(500, 0, 0x000000, "�R�C��%d/%d", coin_, maxCoin_);

	// --��Q���̕`��
	for (int i = 0; i < obstacles.size(); i++) {
		obstacles[i].Draw();
	}
}

void StageManager::LoadCSV(string path)
{
	lineCounter = 0;

	// --�ǂݍ���CSV�t�@�C�����J��-- //
	ifstream ifs(path);

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
				Obstacle objTmp({ static_cast<float>(cellNumberX * blockSize + 32), static_cast<float>(loopCount * blockSize + 32) }, blockType);
				obstacles.push_back(objTmp);

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
	for (int i = 0; i < obstacles.size(); i++) {
		obstacles[i].Initialize();
	}

	lineCounter = loopCount;
}

int StageManager::GetLine() { return lineCounter; }

// --�u���b�N�T�C�Y���Q��-- //
int StageManager::GetBlockSize() { return blockSize; }

// --�R�C���̐���1�ǉ�-- //
void StageManager::AddCoin() { coin_++; }