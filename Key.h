#pragma once
class Key
{
	/// --メンバ変数-- ///
public:

private:
	char keys[256] = {};
	char oldkeys[256] = {};

	// --インスタンス-- //
	static Key* myInstance_;

	/// --メンバ変数END-- ///
	/// --------------- ///
	/// --メンバ関数-- ///
public:
	// --インスタンス取得-- //
	static Key* GetInstance();

	// --メモリ解放-- //
	static void Release();

	// --更新処理-- //
	void Update();

	/// <summary>
	/// キーが押された瞬間か
	/// </summary>
	bool IsTrigger(char key);
	/// <summary>
	/// キーが押されているか
	/// </summary>
	bool IsPress(char key);
	/// <summary>
	/// キーが離された瞬間か
	/// </summary>
	bool IsRelease(char key);

private:
	// --コンストラクタ-- //
	Key();

	/// --メンバ関数END-- ///
};