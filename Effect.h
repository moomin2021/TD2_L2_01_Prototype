#pragma once
class Effect
{
public:
	Effect();
	~Effect();

private:
	// effect�J�n���_�ł�pc�����̎��Ԃ��L�^
	int startTime = 0;

	// effect���J�n���Ă���̌o�ߎ��Ԃ��L�^
	float elapsedTime = 0;

	// effect�̍Đ����x
	float speed = 1;
};