#include "StageManager.h"
#include <fstream>
#include <array>
#include <sstream>
#include <DxLib.h>
#include <algorithm>

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
        istringstream line_stream(line); // •ÏŠ·

        for (size_t i = 0; i < elemsX; i++) {
            getline(line_stream, tmp, ',');

            blocks_.at(loopCount).at(i) = stoi(tmp);
        }
        loopCount++;
    }
}

void StageManager::Init()
{
    Reset();
}

void StageManager::Update()
{
}

void StageManager::Draw()
{
    size_t loopCount = 0;
    for (size_t y = 0; y < blocks_.size(); y++) {
        for (size_t x = 0; x < blocks_[loopCount].size(); x++) {
            if (blocks_.at(y).at(x) == static_cast<int>(BlockId::White)) {
                // ŠO˜g
                DrawBox(blockSize_ * x, blockSize_ * y,
                        blockSize_ * (x + 1), blockSize_ * (y + 1),
                        0x8d8d8d, true
                );

                // “à‘¤
                DrawBox((blockSize_ * x) + 5, (blockSize_ * y) + 5,
                        (blockSize_ * (x + 1)) - 5, (blockSize_ * (y + 1)) - 5,
                        0xffffff, true
                );
            }
            else if (blocks_.at(y).at(x) == static_cast<int>(BlockId::Black)) {
                // ŠO˜g
                DrawBox(blockSize_ * x, blockSize_ * y,
                        blockSize_ * (x + 1), blockSize_ * (y + 1),
                        0x8d8d8d, true
                );

                // “à‘¤
                DrawBox((blockSize_ * x) + 5, (blockSize_ * y) + 5,
                        (blockSize_ * (x + 1)) - 5, (blockSize_ * (y + 1)) - 5,
                        0x000000, true
                );
            }
        }
        loopCount++;
    }
}

void StageManager::Reset()
{
    for (size_t i = 0; i < elemsY; i++) {
        blocks_.at(i).fill(0);
    }
}

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
}