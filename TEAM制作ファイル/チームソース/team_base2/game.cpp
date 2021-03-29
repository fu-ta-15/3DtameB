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
#include "boss_attack.h"
#include "effect.h"
#include "bullet.h"

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
	g_stage.nStageNum = 0;

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
	
	InitEffect();

	InitBullet();

	//---ステージに依るもの----

	//敵の初期化処理
	InitEnemy();

	InitBoss();
	InitBossATK();

	//オブジェクトの初期化処理
	InitObject(g_stage.nStageNum);

	//メッシュフィールドの初期化処理
	InitMeshfield(g_stage.nStageNum);

	//壁(メッシュ)の初期化処理
	InitMeshwall();

	//壁の配置
	//if (g_stage.nStageNum == 1) SetWall();
	
	//スカイボックスの処理
	InitSky();
	
	//-----------------------

	//コリジョン処理の初期化
	InitCollision();

	//モーションの初期化処理
	InitMotion();

	//
	if (g_stage.nStageNum == 2) SetBoss(D3DXVECTOR3(0.0f, 0.0f, 100.0f), ENEMYTYPE_BOSS);

	return S_OK;
}

//=============================================================================
// ゲーム画面の終了処理
//=============================================================================
void UninitGame(void)
{
	UninitMotion();

	//コリジョン終了処理	
	UninitCollision();

	//スカイボックスの終了処理
	UninitSky();

	//壁(メッシュ)の終了処理
	UninitMeshwall();

	//メッシュフィールドの終了処理
	UninitMeshfield();

	//オブジェクトの終了処理
	UninitObject();

	UninitBossATK();

	UninitBoss();

	//敵の終了処理
	UninitEnemy();

	UninitBullet();

	UninitEffect();

	//コマンドアクション終了処理
	UninitCommand();

	UninitPortal();

	//ライトの終了処理
	UninitLight();

	//カメラの終了処理
	UninitCamera();

	UninitPlayer();
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
		//コマンドアクションの更新処理
		UpdateCommand();

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

			//敵の更新処理
			UpdateEnemy();

			UpdateBoss();
			UpdateBossATK();

			UpdateEffect();

			UpdateBullet();

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


	}
	else
	{
		//コマンドアクションの更新処理
		UpdateCommand();

		//コリジョンの更新処理
		UpdateCollision();

		//メッシュフィールドの更新処理
		UpdateMeshfield();

		//壁(メッシュ)の更新処理
		UpdateMeshwall();

		//モデルの更新処理
		UpdatePlayer();

		//敵の更新処理
		UpdateEnemy();

		UpdateBoss();
		UpdateBossATK();

		UpdateEffect();

		UpdateBullet();

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


		//メッシュフィールドの描画処理
		DrawMeshfield();

		//壁(メッシュ)の描画処理
		DrawMeshwall();

		//モデルの描画処理
		DrawPlayer();

		//敵の描画処理
		DrawEnemy();

		DrawBoss();
		DrawBossATK();

		DrawEffect();

		DrawBullet();

		//オブジェクトの描画処理
		DrawObject();

		//スカイボックスの描画
		DrawSky();

		//ポータルの描画処理
		DrawPortal();

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