#pragma once
#include "Vector2.h"

enum class EffectType {
	None,
	LTtoRB,
	LTtoRB2
};

class Particle
{
private: // �ÓI�ϐ�
	static constexpr float shrinkSize_{ 2.0f };

public: // �֐�
	Particle(Vector2 pos, float radius, int indexType);
	~Particle();

	// ��{
	void Activate();
	void Reset();

	//setter
	void SetRadius(float radius) { radius_ = radius; }

	// ���
	void InOutBox();

private: // �ϐ�

	// ���W
	Vector2 pos_{};

	int effectType_{ 0 };
	// ���a
	float radius_{0.0f};

	// effect�J�n���_�ł�pc�����̎��Ԃ��L�^
	int startTime_{ 0 };

	// effect���J�n���Ă���̌o�ߎ��Ԃ��L�^
	float elapsedTime_{ 0.0f };

	// �Đ��̗L��
	bool isPlay_ = false;
};