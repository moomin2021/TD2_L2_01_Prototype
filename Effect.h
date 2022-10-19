#pragma once
#include "Particle.h"
#include <vector>

#define WWIDTH 640
#define WHEIGHT 768
#define PRADIUS 32

class Effect
{

public: // �֐�
	Effect(int indexType);
	~Effect();

	void Activate();
	void Reset();

	void SceneChange();

private: // �ϐ�

	// 1�߂̃p�[�e�B�N�����W
	Vector2 startPos_{};

	int effectType_{ 0 };
	std::vector<Particle> particles_{};
	int activeCount_{ 0 };

	// effect�J�n���_�ł�pc�����̎��Ԃ��L�^
	int startTime_{ 0 };

	// effect���J�n���Ă���̌o�ߎ��Ԃ��L�^
	float elapsedTime_{ 0.0f };

	// �Đ��̗L��
	bool isPlay_ = false;
};