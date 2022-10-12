#pragma once
#include "Key.h"
#include "Util.h"
#include "StageManager.h"

enum State {
	Normal,// -> �ʏ���
	Knock,// --> �m�b�N�o�b�N���
	Boost// ---> �u�[�X�g���
};

struct Vertex {
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightTop;
	Vector2 rightBottom;

	const bool operator==(const Vertex& vtx) const
	{
		return (leftTop.x == vtx.leftTop.x && leftTop.y == vtx.leftTop.y &&
			leftBottom.x == vtx.leftBottom.x && leftBottom.y == vtx.leftBottom.y &&
			rightTop.x == vtx.rightTop.x && rightTop.y == vtx.rightTop.y &&
			rightBottom.x == vtx.rightBottom.x && rightBottom.y == rightBottom.y);
	}

	const bool operator<(const Vertex& vtx) const
	{
		return (leftTop.x < vtx.leftTop.x && leftTop.y < vtx.leftTop.y &&
			leftBottom.x < vtx.leftBottom.x && leftBottom.y < vtx.leftBottom.y &&
			rightTop.x < vtx.rightTop.x && rightTop.y < vtx.rightTop.y &&
			rightBottom.x < vtx.rightBottom.x && rightBottom.y < rightBottom.y);
	}

	const bool operator<=(const Vertex& vtx) const
	{
		return (leftTop.x <= vtx.leftTop.x&& leftTop.y <= vtx.leftTop.y&&
			leftBottom.x <= vtx.leftBottom.x&& leftBottom.y <= vtx.leftBottom.y&&
			rightTop.x <= vtx.rightTop.x&& rightTop.y <= vtx.rightTop.y&&
			rightBottom.x <= vtx.rightBottom.x&& rightBottom.y <= rightBottom.y);
	}

	const bool operator>(const Vertex& vtx) const
	{
		return (leftTop.x > vtx.leftTop.x&& leftTop.y > vtx.leftTop.y&&
			leftBottom.x > vtx.leftBottom.x&& leftBottom.y > vtx.leftBottom.y&&
			rightTop.x > vtx.rightTop.x&& rightTop.y > vtx.rightTop.y&&
			rightBottom.x > vtx.rightBottom.x&& rightBottom.y > rightBottom.y);
	}

	const bool operator>=(const Vertex& vtx) const
	{
		return (leftTop.x >= vtx.leftTop.x && leftTop.y >= vtx.leftTop.y &&
			leftBottom.x >= vtx.leftBottom.x && leftBottom.y >= vtx.leftBottom.y &&
			rightTop.x >= vtx.rightTop.x && rightTop.y >= vtx.rightTop.y &&
			rightBottom.x >= vtx.rightBottom.x && rightBottom.y >= rightBottom.y);
	}
};

class Player {
	/// --�����o�ϐ�-- ///
public:
	// --�����v���C���[�I�u�W�F�N�g-- //
	Object whiteObj;

	// --�����v���C���[�I�u�W�F�N�g-- //
	Object blackObj;

private:
	// --�C���X�^���X-- //
	static Player* myInstance;

	// --�N���X�錾-- //
	Key* key;
	StageManager* stageManager_ = nullptr;

	// --�����蔻�肪�L����
	bool isCollision;

	// --�v���C���[�̏��-- //
	int state;

	// --���ړ����x�̊�b�l-- //
	const float defaultSpeedX;

	// --���ړ��̑��x-- //
	float speedX;

	// --�ړ��������-- //
	int direction;

	// --�c�ړ����x�̊�b�l-- //
	const float defaultSpeedY;

	// --�c�ړ��̑��x-- //
	float speedY;

	// --�u�[�X�g�̎���[s]-- //
	float boostTime;

	// --�u�[�X�g�̌o�ߎ���[s]-- //
	float boostTimer;

	// --�u�[�X�g���n�܂������̎���-- //
	int boostStartTime;

	// --�u�[�X�g���̏����X�s�[�h-- //
	const float defaultBoostSpeedY;

	// --�m�b�N�o�b�N���̏����X�s�[�h-- //
	const float defaultKnockSpeedY;

	// Collision()
	Vertex vPosW;
	Vertex vPosB;
	Vertex vElemsW;
	Vertex vElemsB;

	const Vertex minVElems_ = {};
	const Vertex maxVElems_ =
	{
		{StageManager::elemsX_ - 1, StageManager::elemsY_ - 1},
		{StageManager::elemsX_ - 1, StageManager::elemsY_ - 1},
		{StageManager::elemsX_ - 1, StageManager::elemsY_ - 1},
		{StageManager::elemsX_ - 1, StageManager::elemsY_ - 1}
	};

	/// --�����o�ϐ�END-- ///
	/// --------------- ///
	/// --�����o�֐�-- ///
public:
	// --�C���X�^���X�擾-- //
	static Player* GetInstance();

	// --���������-- //
	static void Release();

	// --�f�X�g���N�^-- //
	~Player();

	// --����������-- //
	void Initialize();

	// --�X�V����-- //
	void Update();

	// --�`�揈��-- //
	void Draw();

	// --�����I�u�W�F�N�g�̎Q��-- //
	Object GetWhiteObj();

	// --�����I�u�W�F�N�g�̎Q��-- //
	Object GetBlackObj();

	// --�v���C���[�̏�Ԃ�ύX-- //
	void SetState(int state);

	// --�ʏ��ԂɕύX-- //
	void SetNormal();

	// --�m�b�N�o�b�N�ɕύX-- //
	void SetKnock();

	// --�u�[�X�g��ԂɕύX-- //
	void SetBoost();

	// --�����蔻��t���O���Q��
	bool GetCollisionFlag();

	// --Y���̑��x���Q��
	float GetSpeedY();

	// --X���̑��x���Q��
	float GetSpeedX();

private:
	// --�R���X�g���N�^-- //
	Player();

	//void Collision();

	/// --�����o�֐�END-- ///
};