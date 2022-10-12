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
	obstacles_.clear();
}

void StageManager::Update()
{
}

void StageManager::Draw()
{
	// --障害物の描画
	for (int i = 0; i < obstacles_.size(); i++) {
		obstacles_[i].Draw();
	}
}

void StageManager::LoadCSV(string path)
{

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

		while (getline(line_stream, tmp, ',')) {
			// --色を読み取る
			int color = static_cast<int>(Sign(stoi(tmp)) * stoi(tmp) / 100) % 10;
			
			// --形状を読み取る
			int shape = stoi(tmp) % 100;

			// --読み取った数字が0以外なら障害物を生成する
			if (stoi(tmp) != 0) {
				Obstacle objTmp({ static_cast<float>(cellNumberX * blockSize + 32), static_cast<float>(loopCount * blockSize + 32) }, color, shape);
				obstacles_.push_back(objTmp);
			}

			// --X軸のマス数をカウント
			cellNumberX++;
		}

		// --Y軸のマス数をカウント
		loopCount++;
	}

	// --障害物の初期化
	for (int i = 0; i < obstacles_.size(); i++) {
		obstacles_[i].Initialize();
	}
}