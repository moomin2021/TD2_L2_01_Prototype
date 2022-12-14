#include "Key.h"
#include"DxLib.h"

// --インスタンスにNULLを代入-- //
Key* Key::myInstance_ = nullptr;

// --インスタンス読み込み-- //
Key* Key::GetInstance() {
	// --インスタンスが無かったら生成する-- //
	if (myInstance_ == nullptr) myInstance_ = new Key();

	// --インスタンスを返す-- //
	return myInstance_;
}

// --メモリ解放-- //
void Key::Release() {
	// --メモリ解放-- //
	delete myInstance_;

	// --NULLを代入-- //
	myInstance_ = nullptr;
}

// --コンストラクタ-- //
Key::Key() {
	
}

// --更新処理-- //
void Key::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldkeys[i] = keys[i];
	}

	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}

// --キーが押された瞬間か-- //
bool Key::IsTrigger(int key_) { return (keys[key_] && !oldkeys[key_]); }

// --キーが押されているか-- //
bool Key::IsPress(int key_) { return keys[key_]; }

// --キーが離された瞬間か-- //
bool Key::IsRelease(int key_) { return (!keys[key_] && oldkeys[key_]); }