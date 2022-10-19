#pragma once
#include "Key.h"
#include "Util.h"
#include "StageManager.h"

enum State {
	Normal,// -> 通常状態
	Knock,// --> ノックバック状態
	Boost,// ---> ブースト状態
	Death// --死亡状態
};

enum struct XAxisState {
	Default,
	Boost
};

#ifdef _DEBUG
enum struct DirectionMode {
	Old,
	New
};
#endif

class Player {
	/// --メンバ変数-- ///
public:
	// --オブジェクト-- //
	BoxObj object_[2];

private:
	// --インスタンス-- //
	static Player* myInstance_;

	// --クラス宣言-- //
	Key* key_;
	StageManager* stageManager_ = nullptr;

	// --プレイヤーの状態-- //
	int state;
	bool xAxisState;
#ifdef _DEBUG
	bool debug_changeDirectionMode;
#endif
	bool isEaseDraw = false;

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

	//
	int easeStartTime = 0.0f;

	// --ブースト時の初期スピード-- //
	const float defaultBoostSpeedY;

	// --ノックバック時の初期スピード-- //
	const float defaultKnockSpeedY;

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

	// --オブジェクト1の参照-- //
	BoxObj GetPlayer1Obj();

	// --オブジェクト1の参照-- //
	BoxObj GetPlayer2Obj();

	// --プレイヤーの状態を変更-- //
	int GetState();

	// --通常状態に変更-- //
	void SetNormal();

	// --ノックバックに変更-- //
	void SetKnock();

	// --ブースト状態に変更-- //
	void SetBoost();

	// --死亡状態に変更-- //
	void SetDeath();

private:
	// --コンストラクタ-- //
	Player();

	//void Collision();

	/// --メンバ関数END-- ///
};