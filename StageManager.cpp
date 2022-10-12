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
	obstacles_.clear();
}

void StageManager::Update()
{
}

void StageManager::Draw()
{
	// --��Q���̕`��
	for (int i = 0; i < obstacles_.size(); i++) {
		obstacles_[i].Draw();
	}
}

void StageManager::LoadCSV(string path)
{

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

		while (getline(line_stream, tmp, ',')) {
			// --�F��ǂݎ��
			int color = static_cast<int>(Sign(stoi(tmp)) * stoi(tmp) / 100) % 10;
			
			// --�`���ǂݎ��
			int shape = stoi(tmp) % 100;

			// --�ǂݎ����������0�ȊO�Ȃ��Q���𐶐�����
			if (stoi(tmp) != 0) {
				Obstacle objTmp({ static_cast<float>(cellNumberX * blockSize + 32), static_cast<float>(loopCount * blockSize + 32) }, color, shape);
				obstacles_.push_back(objTmp);
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
}