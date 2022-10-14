#pragma once
#include <memory>
#include <string>
#include <array>
#include <vector>
#include "Obstacle.h"

enum BlockId
{
	None,   // 0
	Block,
	CoinBlock,
	Coin
};

class StageManager {
	/// --メンバ変数-- ///
public:
	// --障害物クラス宣言-- //
	std::vector<Obstacle> obstacles;

	// --1マスのサイズ-- //
	const int blockSize;

	// csv行数
	int lineCounter;

private:
	// --インスタンス-- //
	static StageManager* myInstance;

	// --最大コイン数-- //
	int maxCoin_ = 0;

	// --現在のコイン数-- //
	int coin_ = 0;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static StageManager* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

	// --CSVを読み込む-- //
	void LoadCSV(std::string path);

	// --読み込んだCSVの行数を参照-- //
	int GetLine();

	// --ブロックサイズを参照-- //
	int GetBlockSize();

	// --コインの数に1追加-- //
	void AddCoin();

private:

	 // --コンストラクタ-- //
	StageManager();

	// --デストラクタ-- //
	~StageManager();

	// --コピーコンストラクタ禁止-- //
	StageManager(const StageManager&) = delete;

	// --コピー代入演算子禁止-- //
	StageManager& operator=(const StageManager&) = delete;

	/// --メンバ関数END-- ///
};