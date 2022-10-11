#pragma once
#include <memory>
#include <string>
#include <array>

enum struct BlockId
{
	None,   // 0
	White,  // 1
	Black   // 2
};

struct Block
{
	size_t color_;
	size_t shape_;
};

class StageManager
{
public: // 静的関数
	static StageManager* GetInstance();

public: // 静的変数
	static const size_t blockSize_ = 64; // 定数

private: // 静的変数
	static const size_t elemsX_ = 10; // 要素数
	static const size_t elemsY_ = 50; //

public: // 関数
	void LoadCSV(std::string path); // CSV読み込み

	void Init();
	void Update();
	void Draw();

	std::array<std::array<Block, elemsX_>, elemsY_>* GetMapchipData() { return &blocks_; }
private: // 関数
	void Reset();

private: // 変数
	std::array<std::array<Block, elemsX_>, elemsY_> blocks_ = { 0 };

private: // シングルトン
	StageManager();
	~StageManager();
	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;
};