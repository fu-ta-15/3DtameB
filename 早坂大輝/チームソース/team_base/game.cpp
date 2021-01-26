//=============================================================================
//
// ゲームの処理 [game.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "meshwall.h"
#include "player.h"
#include "input.h"

//=============================================================================
// ゲーム画面の初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	//メッシュフィールドの初期化処理
	InitMeshfield();

	//壁(メッシュ)の初期化処理
	InitMeshwall();

	//モデルの初期化処理
	InitPlayer();

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//------------------------------------

	//壁の配置
	SetWall();

	//------------------------------------
	return S_OK;
}

//=============================================================================
// ゲーム画面の終了処理
//=============================================================================
void UninitGame(void)
{
	//メッシュフィールドの終了処理
	UninitMeshfield();

	//壁(メッシュ)の終了処理
	UninitMeshwall();

	//モデルの終了処理
	UninitPlayer();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();
}

//=============================================================================
// ゲーム画面の更新処理
//=============================================================================
void UpdateGame(void)
{
	//メッシュフィールドの更新処理
	UpdateMeshfield();

	//壁(メッシュ)の更新処理
	UpdateMeshwall();

	//モデルの更新処理
	UpdatePlayer();

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();
}

//=============================================================================
// ゲーム画面の描画処理
//=============================================================================
void DrawGame(void)
{
	//メッシュフィールドの描画処理
	DrawMeshfield();

	//壁(メッシュ)の描画処理
	DrawMeshwall();

	//モデルの描画処理
	DrawPlayer();
}

//=============================================================================
// 壁の配置
//=============================================================================
void SetWall(void)
{
	SetMeshwall(D3DXVECTOR3(0.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f, 50.0f);
	SetMeshwall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 400.0f, 50.0f);
	SetMeshwall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f), 400.0f, 50.0f);
	SetMeshwall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 400.0f, 50.0f);
}