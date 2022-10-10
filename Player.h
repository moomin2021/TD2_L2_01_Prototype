#pragma once
#include "Key.h"
#include "Vector2.h"

struct Object {
	// --座標-- //
	Vector2 pos;

	// --半径-- //
	float radius;
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

	// --横移動速度の基礎値-- //
	const float defaultSpeedX;

	// --横移動の速度-- //
	float speedX;

	// --移動する向き-- //
	int direction;


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

private:
	// --コンストラクタ-- //
	Player();

	void Coliision();

	/// --メンバ関数END-- ///
};