//-----------------------------------------------------------------------------
//
// ゲームの処理 [game.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "game.h"
#include "fade.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "model.h"
#include "player.h"
#include "polygon.h"
#include "meshfield.h"
#include "bullet.h"
#include "wall.h"
#include "billboard.h"
#include "shadow.h"

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ゲームの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitGame(void)
{
	//ライトの初期化処理
	InitLight();

	//カメラの初期化処理
	InitCamera();

	//モデルの初期化処理
	//InitModel();

	//プレイヤーの初期化処理
	InitPlayer();

	//ポリゴンの初期化処理
	//InitPolygon();

	//地面の初期化処理
	InitMeshfield();

	//弾の初期化処理
	InitBullet();

	//壁の初期化処理
	InitWall();

	//ビルボードの初期化処理
	InitBillboard();

	//影の初期化処理
	InitShadow();

	return S_OK;
}

//-----------------------------------------------------------------------------
// ゲームの終了処理
//-----------------------------------------------------------------------------
void UninitGame(void)
{
	//影の終了処理
	UninitShadow();

	//ビルボードの終了処理
	UninitBillboard();

	//壁の終了処理
	UninitWall();

	//弾の終了処理
	UninitBullet();

	//地面の終了処理
	UninitMeshfield();

	//ポリゴンの終了処理
	//UninitPolygon();

	//プレイヤーの終了処理
	UninitPlayer();

	//モデルの終了処理
	//UninitModel();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();
}

//-----------------------------------------------------------------------------
// ゲームの更新処理
//-----------------------------------------------------------------------------
void UpdateGame(void)
{
	//ライトの更新処理
	UpdateLight();

	//カメラの更新処理
	UpdateCamera();

	//モデルの更新処理
	//UpdateModel();

	//プレイヤーの更新処理
	UpdatePlayer();

	//ポリゴンの更新処理
	//UpdatePolygon();

	//地面の更新処理
	UpdateMeshfield();

	//弾の更新処理
	UpdateBullet();

	//壁の更新処理
	UpdateWall();

	//ビルボードの更新処理
	UpdateBillboard();

	//影の更新処理
	UpdateShadow();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}
}

//-----------------------------------------------------------------------------
// ゲームの描画処理
//-----------------------------------------------------------------------------
void DrawGame(void)
{
	//カメラの設定
	SetCamera();

	//モデルの描画処理
	//DrawModel();

	//プレイヤーの描画処理
	DrawPlayer();

	//ポリゴンの描画処理
	//DrawPolygon();

	//地面の描画処理
	DrawMeshfield();

	//弾の描画処理
	DrawBullet();

	//壁の描画処理
	DrawWall();

	//ビルボードの描画処理
	DrawBillboard();

	//影の描画処理
	DrawShadow();
}

//-----------------------------------------------------------------------------
// ポーズセット
//-----------------------------------------------------------------------------
void SetPause(bool bPause)
{

}