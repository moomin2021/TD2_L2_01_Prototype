#pragma once
#include "Key.h"
#include "Util.h"
#include "StageManager.h"

enum State {
	NormalWallHit,// -> 通常状態で壁伝い中
	NormalAir,// -> 通常状態で空中にいる
	RotateWallHit,// -> 回転状態で壁伝い中
	RotateAir,// -> 回転状態で空中にいる
	Death// --死亡状態
};

class Player {
	/// --メンバ変数-- ///
public:
	// --オブジェクト-- //
	BoxObj object_;

private:
	// --インスタンス-- //
	static Player* myInstance_;

#pragma region クラス宣言
	// --キーボード入力-- //
	Key* key_;

	// --ステージ管理-- //
	StageManager* stageManager_;
#pragma endregion

	// --プレイヤーの状態-- //
	int state_;

#pragma region プレイヤーの速度変数
	// --実際に加算する速度変数-- //
	float speedX_;// -> X軸
	float speedY_;// -> Y軸
	const float defSpeedY_;// -> Y軸基本速度

	// --Y軸の最高速度-- //
	const float maxSpeedY_;

	// --Y軸の最低速度-- //
	const float minSpeedY_;

	// --壁キックの速度-- //
	const float wallKickSpeedX_;

	// --Y軸に減速速値-- //
	const float decelerationY_;

	// --Y軸の加速値-- //
	const float accelerationY_;
#pragma endregion

#pragma region ブースト時間変数
	// --ブーストの時間[s]-- //
	const float rotateTime_;

	// --ブーストの経過時間[s]-- //
	float rotateTimer_;

	// --ブーストが始まった時の時間-- //
	int rotateStartTime_;
#pragma endregion

	// --X座標の最高座標-- //
	const float maxPosX_;

	// --X座標の最低座標-- //
	const float minPosX_;

	// --空中にいるか-- //
	bool isAir_;

	// --空中キックができるか-- //
	bool isAirKickActive_;

	// --移動する向き-- //
	float directionX_;
	float directionY_;

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

	// --オブジェクトの参照-- //
	BoxObj GetBoxObj();

	// --プレイヤーの状態を参照-- //
	int GetState();

	// --プレイヤーの状態を変更-- //
	void SetState(int state);

	float& GetSpeedX();
	float& GetSpeedY();

	// --通常状態に変更-- //
	void SetNormal();

	// --ブースト状態に変更-- //
	void SetBoost();

	// --死亡状態に変更-- //
	void SetDeath();

	// --X軸の向きを変える-- //
	void ChangeDireX();
	void ChangeDireY();

	// --回転状態にする-- //
	void SetRotate();

private:
	// --コンストラクタ-- //
	Player();

	//void Collision();

	/// --メンバ関数END-- ///
};