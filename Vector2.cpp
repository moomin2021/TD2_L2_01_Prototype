#include "Vector2.h"
#include <cmath>    // sqrt

// �����Ȃ��̃R���X�g���N�^
Vector2::Vector2() : x(0), y(0) {}

// ����2�̃R���X�g���N�^
Vector2::Vector2(float x, float y) : x(x), y(y) {}

// �x�N�g���̒��������߂�
float Vector2::length() const
{
    return sqrt((x * x) + (y * y));
}

// �x�N�g���̐��K��
Vector2& Vector2::normalize()
{
    float len = length();
    if (len != 0)
    {
        return *this /= len;
    }
    return *this;
}

// ���ς����߂�
float Vector2::dot(const Vector2& v) const
{
    return x * v.x + y * v.y;
}

// �O�ς����߂�
float Vector2::cross(const Vector2& v) const
{
    return x * v.y - y * v.x;
}

// �P�����Z�q+���g����悤�ɂ���
Vector2 Vector2::operator+() const
{
    return *this;
}

// �P�����Z�q-���g����悤�ɂ���
Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

// +=���g�p�ł���悤�ɂ���
Vector2& Vector2::operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;
    return *this;
}

// -=���g�p�ł���悤�ɂ���
Vector2& Vector2::operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

// �x�N�g����s�{�ɂ���
Vector2& Vector2::operator*=(float s)
{
    x *= s;
    y *= s;
    return *this;
}

// �x�N�g����1/s�{�ɂ���
Vector2& Vector2::operator/=(float s)
{
    x /= s;
    y /= s;
    return *this;
}

// Vector2 �N���X�ɑ����Ȃ��֐��R
// �񍀉��Z�q
const Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
    Vector2 temp(v1);
    return temp += v2;
}

// �x�N�g���̈����Z���ł���悤�ɂ���
const Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
    Vector2 temp(v1);
    return temp -= v2;
}

// �x�N�g����s�{���v�Z�ł���悤�ɂ���
const Vector2 operator*(const Vector2& v, float s)
{
    Vector2 temp(v);
    return temp *= s;
}

// �x�N�g����s�{���v�Z�ł���悤�ɂ���
const Vector2 operator*(float s, const Vector2& v)
{
    return v * s;
}

// �x�N�g����1/s�{���v�Z�ł���悤�ɂ���
const Vector2 operator/(const Vector2& v, float s)
{
    Vector2 temp(v);
    return temp /= s;
}