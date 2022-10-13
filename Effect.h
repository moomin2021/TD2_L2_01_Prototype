#pragma once
class Effect
{
public:
	Effect();
	~Effect();

private:
	// effect開始時点でのpc内部の時間を記録
	int startTime = 0;

	// effectを開始してからの経過時間を記録
	float elapsedTime = 0;

	// effectの再生速度
	float speed = 1;
};