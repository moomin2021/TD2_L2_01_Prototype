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

// --インスタンスにNULLを代入-- //
StageManager* StageManager::myInstance = nullptr;

// --インスタンス読み込み-- //
StageManager* StageManager::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance == nullptr) myInstance = new StageManager();

	// --インスタンスを返す-- //
	return myInstance;
}

// --メモリ解放-- //
void StageManager::Release() {
	// --メモリ解放-- //
	delete myInstance;

	// --NULLを代入-- //
	myInstance = nullptr;
}

// --コンストラクタ-- //
StageManager::StageManager() :
	// --1マスのサイズ-- //
	blockSize(64)
{

}

// --デストラクタ-- //
StageManager::~StageManager()
{
}

void StageManager::Initialize()
{
	// --障害物を削除-- //
	obstacles.clear();

	// --最大コイン数-- //
	maxCoin_ = 0;

	// --現在のコイン数-- //
	coin_ = 0;
}

void StageManager::Update()
{
}

void StageManager::Draw()
{
	DrawFormatString(500, 0, 0x000000, "コイン%d/%d", coin_, maxCoin_);

	// --障害物の描画
	for (int i = 0; i < obstacles.size(); i++) {
		obstacles[i].Draw();
	}
}

void StageManager::LoadCSV(string path)
{
	lineCounter = 0;

	// --読み込むCSVファイルを開く-- //
	ifstream ifs(path);

	// --読み込んだCSVファイルの1行を一時的に格納する変数-- //
	string line;

	// --[,]区切りで読み込んだデータ一時的に格納する変数-- //
	string tmp;

	// --Y軸のマス数をカウント
	size_t loopCount = 0;

	// --1行ずつ読み込む、読み込んだ1行をline変数に格納-- //
	while (getline(ifs, line)) {

		// --[,]区切りで読み込むためにistringstream型にする-- //
		istringstream line_stream(line);

		// --X軸のマス数をカウント
		int cellNumberX = 0;

		// --[,]区切りで読み込む、読み込んだ文字列をtmpに格納する-- //
		while (getline(line_stream, tmp, ',')) {
			// --形状を読み取る
			int blockType = stoi(tmp);

			// --読み取った数字が0以外なら障害物を生成する
			if (blockType != None) {
				Obstacle objTmp({ static_cast<float>(cellNumberX * blockSize + 32), static_cast<float>(loopCount * blockSize + 32) }, blockType);
				obstacles.push_back(objTmp);

				// --読みった数字がコインブロックだったら-- //
				if (blockType == CoinBlock) {
					// --最大コインに1追加-- //
					maxCoin_++;
				}

				// --読みった数字がコインだったら-- //
				else if (blockType == Coin) {
					// --最大コインに1追加-- //
					maxCoin_++;
				}
			}

			// --X軸のマス数をカウント
			cellNumberX++;
		}

		// --Y軸のマス数をカウント
		loopCount++;
	}

	// --障害物の初期化
	for (int i = 0; i < obstacles.size(); i++) {
		obstacles[i].Initialize();
	}

	lineCounter = loopCount;
}

int StageManager::GetLine() { return lineCounter; }

// --ブロックサイズを参照-- //
int StageManager::GetBlockSize() { return blockSize; }

// --コインの数に1追加-- //
void StageManager::AddCoin() { coin_++; }