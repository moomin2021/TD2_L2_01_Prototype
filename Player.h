#pragma once
#include "Key.h"
#include "Util.h"
#include "StageManager.h"

enum State {
	Normal,// -> 通常状態
	Knock,// --> ノックバック状態
	Boost// ---> ブースト状態
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
	/// --メンバ変数-- ///
public:
	// --白いプレイヤーオブジェクト-- //
	Object whiteObj;

	// --黒いプレイヤーオブジェクト-- //
	Object blackObj;

private:
	// --インスタンス-- //
	static Player* myInstance;

	// --クラス宣言-- //
	Key* key;
	StageManager* stageManager_ = nullptr;

	// --当たり判定が有効か
	bool isCollision;

	// --プレイヤーの状態-- //
	int state;

	// --横移動速度の基礎値-- //
	const float defaultSpeedX;

	// --横移動の速度-- //
	float speedX;

	// --移動する向き-- //
	int direction;

	// --縦移動速度の基礎値-- //
	const float defaultSpeedY;

	// --縦移動の速度-- //
	float speedY;

	// --ブーストの時間[s]-- //
	float boostTime;

	// --ブーストの経過時間[s]-- //
	float boostTimer;

	// --ブーストが始まった時の時間-- //
	int boostStartTime;

	// --ブースト時の初期スピード-- //
	const float defaultBoostSpeedY;

	// --ノックバック時の初期スピード-- //
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

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static Player* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --デストラクタ-- //
	~Player();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

	// --白いオブジェクトの参照-- //
	Object GetWhiteObj();

	// --黒いオブジェクトの参照-- //
	Object GetBlackObj();

	// --プレイヤーの状態を変更-- //
	void SetState(int state);

	// --通常状態に変更-- //
	void SetNormal();

	// --ノックバックに変更-- //
	void SetKnock();

	// --ブースト状態に変更-- //
	void SetBoost();

	// --当たり判定フラグを参照
	bool GetCollisionFlag();

	// --Y軸の速度を参照
	float GetSpeedY();

	// --X軸の速度を参照
	float GetSpeedX();

private:
	// --コンストラクタ-- //
	Player();

	//void Collision();

	/// --メンバ関数END-- ///
};