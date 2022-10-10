#pragma once
#include "Key.h"
#include "Util.h"

enum State {
	Normal,// -> 通常状態
	Knock,// --> ノックバック状態
	Boost// ---> ブースト状態
};

struct Vertex {
	size_t LeftTop;
	size_t LeftBottom;
	size_t RightTop;
	size_t RightBottom;
};

class Player {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static Player* myInstance;

	// --クラス宣言-- //
	Key* key;

	// --白いプレイヤーオブジェクト-- //
	Object whiteObj;

	// --黒いプレイヤーオブジェクト-- //
	Object blackObj;

	// --プレイヤーの状態-- //
	int state;

	// --横移動速度の基礎値-- //
	const float defaultSpeedX;

	// --横移動の速度-- //
	float speedX;

	// --移動する向き-- //
	int direction;

	// --縦移動の速度-- //
	float speedY;

	// --ブーストの時間[s]-- //
	float boostTime;

	// --ブーストの経過時間[s]-- //
	float boostTimer;

	// --ブーストが始まった時の時間-- //
	int boostStartTime;

	// Collision()
	Vertex vPos;

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

private:
	// --コンストラクタ-- //
	Player();

	void Coliision();

	/// --メンバ関数END-- ///
};