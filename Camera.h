#pragma once

class Camera {
	/// --メンバ変数-- ///
public:

private:
	// --インスタンス-- //
	static Camera* myInstance;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static Camera* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --デストラクタ-- //
	~Camera();

	// --初期化処理-- //
	void Initialize();

	// --更新処理-- //
	void Update();

	// --描画処理-- //
	void Draw();

private:
	// --コンストラクタ-- //
	Camera();

	/// --メンバ関数END-- ///
};