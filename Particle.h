#pragma once
#include "Vector2.h"

enum class EffectType {
	None,
	LTtoRB,
	LTtoRB2
};

class Particle
{
private: // 静的変数
	static constexpr float shrinkSize_{ 2.0f };

public: // 関数
	Particle(Vector2 pos, float radius, int indexType);
	~Particle();

	// 基本
	void Activate();
	void Reset();

	//setter
	void SetRadius(float radius) { radius_ = radius; }

	// 種類
	void InOutBox();

private: // 変数

	// 座標
	Vector2 pos_{};

	int effectType_{ 0 };
	// 半径
	float radius_{0.0f};

	// effect開始時点でのpc内部の時間を記録
	int startTime_{ 0 };

	// effectを開始してからの経過時間を記録
	float elapsedTime_{ 0.0f };

	// 再生の有無
	bool isPlay_ = false;
};