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

class StageManager
{
public: // �ÓI�֐�
    static StageManager* GetInstance();

private: // �ÓI�ϐ�
    static const size_t blockSize_ = 64; // �萔

    static const size_t elemsX = 10; // �v�f��
    static const size_t elemsY = 12; //

public: // �֐�
    void LoadCSV(std::string path); // CSV�ǂݍ���

    void Init();
    void Update();
    void Draw();

private: // �֐�
    void Reset();

private: // �ϐ�
    std::array<std::array<size_t, elemsX>, elemsY> blocks_ = { 0 }; 

private: // �V���O���g��
    StageManager();
    ~StageManager();
    StageManager(const StageManager&) = delete;
    StageManager& operator=(const StageManager&) = delete;
};