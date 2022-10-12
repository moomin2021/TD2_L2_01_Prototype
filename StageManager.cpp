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

StageManager* StageManager::GetInstance()
{
	static StageManager instance;
	return &instance;
}

void StageManager::LoadCSV(string path)
{
	Reset();

	ifstream ifs(path);
	string line, tmp;
	size_t loopCount = 0;
	while (getline(ifs, line)) {
		istringstream line_stream(line); // ïœä∑

		for (size_t i = 0; i < elemsX_; i++) {
			getline(line_stream, tmp, ',');

			blocks_.at(loopCount).at(i).color_ = static_cast<int>(Sign(stoi(tmp)) * stoi(tmp) / 100) % 10;
			blocks_.at(loopCount).at(i).shape_ = stoi(tmp) % 100;

			if (blocks_.at(loopCount).at(i).color_ == static_cast<int>(BlockId::White) ||
				blocks_.at(loopCount).at(i).color_ == static_cast<int>(BlockId::Black)) {

				//Obstacle objTmp({ i * blockSize_ ,loopCount * blockSize_ }, { (i + 1) * blockSize_,(loopCount + 1) * blockSize_ });
				Obstacle objTmp({ static_cast<float>(i * blockSize_ + 32), static_cast<float>(loopCount * blockSize_ + 32) }, static_cast<unsigned short int>(blocks_.at(loopCount).at(i).color_), static_cast<unsigned short int>(blocks_.at(loopCount).at(i).shape_));
				obstacles_.push_back(objTmp);
			}
		}
		loopCount++;
	}

	// --è·äQï®ÇÃèâä˙âª
	for (int i = 0; i < obstacles_.size(); i++) {
		obstacles_[i].Initialize();
	}
}

void StageManager::Init()
{
	Reset();
	obstacles_.clear();
}

void StageManager::Update()
{
}

void StageManager::Draw()
{
	//size_t loopCount = 0;
	//for (size_t y = 0; y < blocks_.size(); y++) {
	//	for (size_t x = 0; x < blocks_[loopCount].size(); x++) {
	//		if (blocks_.at(y).at(x).color_ == static_cast<int>(BlockId::White)) {
	//			// äOòg
	//			DrawBox(blockSize_ * x, blockSize_ * y - Camera::GetScroll(),
	//				blockSize_ * (x + 1), blockSize_ * (y + 1) - Camera::GetScroll(),
	//				0x8d8d8d, true
	//			);

	//			// ì‡ë§
	//			DrawBox((blockSize_ * x) + 5, (blockSize_ * y) + 5 - Camera::GetScroll(),
	//				(blockSize_ * (x + 1)) - 5, (blockSize_ * (y + 1)) - 5 - Camera::GetScroll(),
	//				0xffffff, true
	//			);
	//		}
	//		else if (blocks_.at(y).at(x).color_ == static_cast<int>(BlockId::Black)) {
	//			// äOòg
	//			DrawBox(blockSize_ * x, blockSize_ * y + Camera::GetScroll(),
	//				blockSize_ * (x + 1), blockSize_ * (y + 1) - Camera::GetScroll(),
	//				0x8d8d8d, true
	//			);

	//			// ì‡ë§
	//			DrawBox((blockSize_ * x) + 5, (blockSize_ * y) + 5 + Camera::GetScroll(),
	//				(blockSize_ * (x + 1)) - 5, (blockSize_ * (y + 1)) - 5 - Camera::GetScroll(),
	//				0x000000, true
	//			);
	//		}
	//	}
	//	loopCount++;
	//}

	// --è·äQï®ÇÃï`âÊ
	for (int i = 0; i < obstacles_.size(); i++) {
		obstacles_[i].Draw();
	}
}

void StageManager::Reset()
{
	for (size_t i = 0; i < elemsY_; i++) {
		blocks_.at(i).fill({0,0});
	}
}

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
}