#pragma once
#include "Particle.h"
#include <vector>

#define WWIDTH 640
#define WHEIGHT 768
#define PRADIUS 32

class Effect
{

public: // 関数
	Effect(int indexType);
	~Effect();

	void Activate();
	void Reset();

	void SceneChange();

private: // 変数

	// 1つめのパーティクル座標
	Vector2 startPos_{};

	int effectType_{ 0 };
	std::vector<Particle> particles_{};
	int activeCount_{ 0 };

	// effect開始時点でのpc内部の時間を記録
	int startTime_{ 0 };

	// effectを開始してからの経過時間を記録
	float elapsedTime_{ 0.0f };

	// 再生の有無
	bool isPlay_ = false;
};