//===================================================================
//
// カメラの処理　[camera.cpp]
// Author: fukuyama syuya
//
//===================================================================
#include "main.h"
#include "camera.h"
#include "input.h"
#include "Player.h"

//=================================================================================================
//マクロ定義
//=================================================================================================
#define MAX_POINT (150.0f)			//カメラの位置

//=================================================================================================
//グローバル変数
//=================================================================================================
Camera g_camera;					//カメラの情報

//=================================================================================================
//初期化処理
//=================================================================================================
void InitCamera(void)
{
	//カメラの初期化
	g_camera.posV = D3DXVECTOR3(0.0f, MAX_POINT, - MAX_POINT);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=================================================================================================
//終了処理
//=================================================================================================
void UninitCamera(void)
{

}

//=================================================================================================
//更新処理
//=================================================================================================
void UpdateCamera(void)
{
	//モデルの取得
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	//カメラの追従
	g_camera.posR = pPlayer->pos;

	g_camera.posV.x = g_camera.posR.x;
	g_camera.posV.z = g_camera.posR.z - 200.0f;
	g_camera.posV.y = g_camera.posR.y + 200.0f;

	//カメラの上下左右移動
	if (GetKeyboardPress(DIK_W) == true)
	{
		g_camera.posV.x += sinf (g_camera.rot.y) * 1;
		g_camera.posR.z += cosf (g_camera.rot.y) * 1;
		g_camera.posR.x += sinf (g_camera.rot.y) * 1;
		g_camera.posV.z += cosf (g_camera.rot.y) * 1;
	}

	if (GetKeyboardPress(DIK_S) == true)
	{
		g_camera.posV.x -= sinf (g_camera.rot.y) * 1;
		g_camera.posR.z -= cosf (g_camera.rot.y) * 1;
		g_camera.posR.x -= sinf (g_camera.rot.y) * 1;
		g_camera.posV.z -= cosf (g_camera.rot.y) * 1;
	}

	if (GetKeyboardPress(DIK_A) == true)
	{
		g_camera.posV.x -= cosf (g_camera.rot.y) * 1;
		g_camera.posV.z -= sinf (g_camera.rot.y) * 1;
		g_camera.posR.x -= cosf (g_camera.rot.y) * 1;
		g_camera.posR.z -= sinf (g_camera.rot.y) * 1;
	}

	if (GetKeyboardPress(DIK_D) == true)
	{
		g_camera.posV.x += cosf(g_camera.rot.y) * 1;
		g_camera.posV.z += sinf(g_camera.rot.y) * 1;
		g_camera.posR.x += cosf(g_camera.rot.y) * 1;
		g_camera.posR.z += sinf(g_camera.rot.y) * 1;
	}

	//カメラの注視点の回転
	if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera.rot.y -= 0.06f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * MAX_POINT;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * MAX_POINT;
	}

	//カメラの逆回転
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera.rot.y += 0.06f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * MAX_POINT;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * MAX_POINT;
	}

	//カメラの視点の回転
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_camera.rot.y += 0.06f;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * MAX_POINT;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * MAX_POINT;
	}

	if (GetKeyboardPress(DIK_C) == true)
	{
		g_camera.rot.y -= 0.06f;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * MAX_POINT;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * MAX_POINT;
	}

	//注視点操作
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_camera.posR.z += cosf(g_camera.rot.y) * 1;
		g_camera.posV.z += sinf(g_camera.rot.y) * 1;
	}

	if (GetKeyboardPress(DIK_B) == true)
	{
		g_camera.posR.z -= cosf(g_camera.rot.y) * 1;
		g_camera.posV.z -= sinf(g_camera.rot.y) * 1;
	}

	//視点操作
	if (GetKeyboardPress(DIK_Y) == true)
	{

	}

	//自動回転
	/*g_camera.rot.y -= 0.007f;

	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * MAX_POINT;
	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * MAX_POINT;*/
}

//=================================================================================================
//設定処理
//=================================================================================================
void SetCamera(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//プロジェクションマトリックス
	D3DXMatrixIdentity(&g_camera.mtxPlojection);

	//プロジェクションを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxPlojection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxPlojection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxPlojection);

	//ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_camera.mtxPlojection, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxPlojection);
}

//=================================================================================================
//カメラの取得
//=================================================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}