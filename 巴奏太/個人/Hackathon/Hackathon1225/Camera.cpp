//-----------------------------------------------------------------------------
//
// カメラの処理 [Camera.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "camera.h"
#include "Input.h"
#include "Player.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define CAMERA_DISTANCE (200.0f)														// 視点と注視点までの距離
#define CAMERA_SPEED (0.05f)														// カメラの旋回速度

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
Camera g_camera;		// カメラの情報

						//-----------------------------------------------------------------------------
						// カメラの初期化処理
						//-----------------------------------------------------------------------------
void InitCamera(void)
{
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// カメラの向き
	g_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);				// 視点
	g_camera.posR = D3DXVECTOR3(g_camera.posV.x + sinf(g_camera.rot.x) * CAMERA_DISTANCE, 0.0f, g_camera.posV.z + cosf(g_camera.rot.z) * CAMERA_DISTANCE);					// 注視点
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					// 上向きベクトル
}

//-----------------------------------------------------------------------------
// カメラの終了処理
//-----------------------------------------------------------------------------
void UninitCamera(void)
{

}

//-----------------------------------------------------------------------------
// カメラの更新処理
//-----------------------------------------------------------------------------
void UpdateCamera(void)
{
	Player *pPlayer = GetPlayer();
	D3DXVECTOR3 Diff;

	//視点　左旋回
	if (GetkeyboardPress(DIK_Z) == true)
	{
		//視点の位置移動
		g_camera.rot.y += CAMERA_SPEED;

		//視点の固定、g_camera.rotの向きに
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_DISTANCE;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	}
	//視点　右旋回
	else if (GetkeyboardPress(DIK_C) == true)
	{
		g_camera.rot.y -= CAMERA_SPEED;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_DISTANCE;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	}

	//注視点をモデルに
	g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y) * -50;
	g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y) * -50;
	g_camera.posR.y = 50;

	//視点をモデルからカメラの向きに長さ分だけ
	g_camera.posV.x = pPlayer->pos.x - sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	g_camera.posV.z = pPlayer->pos.z - cosf(g_camera.rot.y) * CAMERA_DISTANCE;

	//差分計算
	Diff.x = g_camera.posRDest.x - g_camera.posR.x;
	Diff.z = g_camera.posRDest.z - g_camera.posR.z;

	g_camera.posR.x += Diff.x * 0.15f;
	g_camera.posR.z += Diff.z * 0.15f;

	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}

}

//-----------------------------------------------------------------------------
// カメラの設定
//-----------------------------------------------------------------------------
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//-----------------------------------------------------------------------------
// カメラの情報取得
//-----------------------------------------------------------------------------
Camera *GetCamera(void)
{
	return &g_camera;
}