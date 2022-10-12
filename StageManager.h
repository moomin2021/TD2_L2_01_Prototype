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

struct Block
{
	size_t color_;
	size_t shape_;
};

//struct Obstacle
//{
//	Vector2 start_;
//	Vector2 end_;
//
//	Obstacle(Vector2 start, Vector2 end)
//		:start_(start), end_(end)
//	{
//	}
//
//	void ChangeSize(Vector2 start, Vector2 end)
//	{
//		start_ = start;
//		end_ = end;
//	}
//};

class StageManager
{
public: // �ÓI�֐�
	static StageManager* GetInstance();

public: // �ÓI�ϐ�
	static const size_t blockSize_ = 64; // �萔
	static const size_t elemsX_ = 10; // �v�f��
	static const size_t elemsY_ = 50; //

public: // �֐�
	void LoadCSV(std::string path); // CSV�ǂݍ���

	void Init();
	void Update();
	void Draw();

	std::array<std::array<Block, elemsX_>, elemsY_>* GetMapchipData() { return &blocks_; }
private: // �֐�
	void Reset();

private: // �ϐ�
	std::array<std::array<Block, elemsX_>, elemsY_> blocks_ = { 0 };

public:
	std::vector<Obstacle> obstacles_;

private: // �V���O���g��
	StageManager();
	~StageManager();
	StageManager(const StageManager&) = delete;
	StageManager& operator=(const StageManager&) = delete;
};