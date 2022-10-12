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
	/// --メンバ変数-- ///
public:
	// --障害物クラス宣言-- //
	std::vector<Obstacle> obstacles_;

	// --1マスのサイズ-- //
	const int blockSize;

private:
	// --インスタンス-- //
	static StageManager* myInstance;

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