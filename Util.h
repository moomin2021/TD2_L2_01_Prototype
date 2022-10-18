#pragma once
#include "Vector2.h"

struct BoxObj {
	// --���W-- //
	Vector2 pos;

	// --���a-- //
	float radiusX;// -> X��
	float radiusY;// -> Y��
};

struct Image {
	// --���W-- //
	Vector2 pos;

	// --X���̔��a-- //
	float radiusX;

	// --Y���̔��a-- //
	float radiusY;

	// --�摜�̃n���h��-- //
	int handle;
};

double Sign(double a);

namespace Util {

	const float PI = 3.141592654f;

	// --�������玩��֐�-- //

	/// <summary>
	/// ���ꂽ�l���ő�l�������Ă�����ő�l��Ԃ��A�ŏ��l��������Ă�����ŏ��l��Ԃ��B
	/// �ǂ���ɂ����Ă͂܂�Ȃ��ꍇ�́A�l�����̂܂ܕԂ�
	/// </summary>
	/// <param name="value"> �l </param>
	/// <param name="max"> �ő�l </param>
	/// <param name="min"> �ŏ��l </param>
	/// <returns></returns>
	int Clamp(int value, int max, int min);

	/// <summary>
	/// ���ꂽ�l���ő�l�������Ă�����ő�l��Ԃ��A�ŏ��l��������Ă�����ŏ��l��Ԃ��B
	/// �ǂ���ɂ����Ă͂܂�Ȃ��ꍇ�́A�l�����̂܂ܕԂ�
	/// </summary>
	/// <param name="value"> �l </param>
	/// <param name="max"> �ő�l </param>
	/// <param name="min"> �ŏ��l </param>
	/// <returns></returns>
	float Clamp(float value, float max, float min);

	/// <summary>
	/// �ʓx�@�̒l��x���@�ɂ��ĕԂ�
	/// </summary>
	/// <param name="radian"> �ʓx�@�̒l </param>
	/// <returns></returns>
	float Radian2Degree(float radian);

	/// <summary>
	/// �x���@�̒l���ʓx�@�ɂ��ĕԂ�
	/// </summary>
	/// <param name="degree"> �x���@�̒l </param>
	/// <returns></returns>
	float Degree2Radian(float degree);

} // namespace MathUtility