//=============================================================================
//
// ゲームの処理 [game.cpp]
// Author:Taiki Hayasaka, Sota Tomoe
//
//=============================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "meshwall.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "enemy.h"
#include "portal.h"
#include "collision.h"
#include "skybox.h"
#include "object.h"
#include "commandaction.h"
#include "boss.h"
#include "effect.h"
#include "gauge.h"

//=============================================================================
// グローバル変数
//=============================================================================
Stage g_stage;
int g_nCntFrame;

//=============================================================================
// ゲーム画面の初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	//モデルの初期化処理
	InitPlayer();

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//ポータルの初期化処理
	InitPortal();
	
	//コマンドアクション初期化処理
	InitCommand();

	//---ステージに依るもの----

	//ゲージ
	InitGauge();

	//敵の初期化処理
	InitEnemy();

	InitEffect();

	InitBoss();

	//オブジェクトの初期化処理
	InitObject();

	//メッシュフィールドの初期化処理
	InitMeshfield(g_stage.nStageNum);

	//壁(メッシュ)の初期化処理
	InitMeshwall();

	//壁の配置
	SetWall();
	
	//スカイボックスの処理
	InitSky();
	
	//-----------------------

	//コリジョン処理の初期化
	InitCollision();

	//モーションの初期化処理
	InitMotion();

	return S_OK;
}

//=============================================================================
// ゲーム画面の終了処理
//=============================================================================
void UninitGame(void)
{
	UninitGauge();

	//スカイボックスの終了処理
	UninitSky();

	//メッシュフィールドの終了処理
	UninitMeshfield();

	UninitBoss();

	UninitEffect();

	//敵の終了処理
	UninitEnemy();

	//オブジェクトの終了処理
	UninitObject();

	//壁(メッシュ)の終了処理
	UninitMeshwall();

	//コマンドアクション終了処理
	UninitCommand();

	//モデルの終了処理
	UninitPlayer();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//コリジョン終了処理	
	UninitCollision();

	//ポータルの終了処理
	UninitPortal();
}

//=============================================================================
// ゲーム画面の更新処理
//=============================================================================
void UpdateGame(void)
{
	g_nCntFrame++;
	CommandAction *pCmd = GetCAction();

	if (pCmd->bActive == true)
	{
		if (g_nCntFrame % 4 == 0)
		{
			//コリジョンの更新処理
			UpdateCollision();

			//メッシュフィールドの更新処理
			UpdateMeshfield();

			//壁(メッシュ)の更新処理
			UpdateMeshwall();

			//モーションの更新処理
			UpdateMotion();

			//モデルの更新処理
			UpdatePlayer();

			UpdateEffect();

			//敵の更新処理
			UpdateEnemy();

			UpdateBoss();

			//オブジェクトの更新処理
			UpdateObject();

			//ライトの更新処理
			UpdateLight();

			//ポータルの更新処理
			UpdatePortal();

			//スカイボックスの更新処理
			UpdateSky();

			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				g_stage.nStageNum += 1;
				SetFade(FADE_OUT, MODE_GAME);
			}
		}
		//カメラの更新処理
		UpdateCamera();

		//コマンドアクションの更新処理
		UpdateCommand();
	}
	else
	{
		//コリジョンの更新処理
		UpdateCollision();

		SetGeauge(GAUGE_TYPE_PORTAL, GAUGE_COVER_PORTAL, D3DXVECTOR3(100.0f, -500.0f, 0.0f), D3DXVECTOR2(1000.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		UpdateGauge();

		//メッシュフィールドの更新処理
		UpdateMeshfield();

		//壁(メッシュ)の更新処理
		UpdateMeshwall();

		UpdateEffect();

		//モデルの更新処理
		UpdatePlayer();

		//敵の更新処理
		UpdateEnemy();

		UpdateBoss();

		//オブジェクトの更新処理
		UpdateObject();

		//カメラの更新処理
		UpdateCamera();

		//モーションの更新処理
		UpdateMotion();

		//ライトの更新処理
		UpdateLight();

		//ポータルの更新処理
		UpdatePortal();

		//スカイボックスの更新処理
		UpdateSky();

		//コマンドアクションの更新処理
		UpdateCommand();

		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			g_stage.nStageNum += 1;
			SetFade(FADE_OUT, MODE_GAME);
		}
	}
}

//=============================================================================
// ゲーム画面の描画処理
//=============================================================================
void DrawGame(void)
{
	DrawGaugeCover();
	DrawGauge();
		//メッシュフィールドの描画処理
		DrawMeshfield();

		//壁(メッシュ)の描画処理
		DrawMeshwall();

		//モデルの描画処理
		DrawPlayer();

		//敵の描画処理
		DrawEnemy();

		DrawBoss();

		//オブジェクトの描画処理
		DrawObject();

		//スカイボックスの描画
		DrawSky();

		//ポータルの描画処理
		DrawPortal();


		DrawEffect();

		//コマンドアクション描画処理
		DrawCommand();



		//コリジョンの描画処理
		DrawCollision();
}

//=============================================================================
// ステージ番号を取得
//=============================================================================
Stage *GetStage(void)
{
	return &g_stage;
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