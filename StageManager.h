#pragma once
#include <memory>
#include <string>
#include <array>

enum struct BlockId
{
    None,   // 0
    Wall    // 1
};

class StageManager
{
public: // 静的関数
    static StageManager* GetInstance();

private: // 静的変数
    static const size_t blockSize_ = 32; // 定数

    static const size_t elemsX = 18; // 要素数
    static const size_t elemsY = 12; //

public: // 関数
    void LoadCSV(std::string path); // CSV読み込み

    void Init();
    void Update();
    void Draw();

private: // 関数
    void Reset();

private: // 変数
    std::array<std::array<size_t, elemsX>, elemsY> blocks_ = { 0 }; 

private: // シングルトン
    StageManager();
    ~StageManager();
    StageManager(const StageManager&) = delete;
    StageManager& operator=(const StageManager&) = delete;
};