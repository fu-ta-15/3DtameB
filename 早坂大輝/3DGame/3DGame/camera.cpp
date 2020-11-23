//=============================================================================
//
// カメラの処理 [camera.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "camera.h"
#include "input.h"

//=============================================================================
// グローバル変数
//=============================================================================
Camera g_camera;	//カメラの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitCamera(void)
{
	//初期化
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -400.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCamera(void)
{
	//カメラ移動
	if (GetKeyboardPress(DIK_W) == true)	//Wを押した
	{
		//前移動
		g_camera.posV.x += sinf(g_camera.rot.y) * 3.0f;
		g_camera.posR.x += sinf(g_camera.rot.y) * 3.0f;
		g_camera.posV.z += cosf(g_camera.rot.y) * 3.0f;
		g_camera.posR.z += cosf(g_camera.rot.y) * 3.0f;
	}
	if (GetKeyboardPress(DIK_S) == true)	//Sを押した
	{
		//後移動
		g_camera.posV.x -= sinf(g_camera.rot.y) * 3.0f;
		g_camera.posR.x -= sinf(g_camera.rot.y) * 3.0f;
		g_camera.posV.z -= cosf(g_camera.rot.y) * 3.0f;
		g_camera.posR.z -= cosf(g_camera.rot.y) * 3.0f;
	}
	if (GetKeyboardPress(DIK_A) == true)	//Aを押した
	{
		//左移動
		g_camera.posV.x -= cosf(g_camera.rot.y) * 3.0f;
		g_camera.posR.x -= cosf(g_camera.rot.y) * 3.0f;
		g_camera.posV.z += sinf(g_camera.rot.y) * 3.0f;
		g_camera.posR.z += sinf(g_camera.rot.y) * 3.0f;
	}
	if (GetKeyboardPress(DIK_D) == true)	//Dを押した
	{
		//右移動
		g_camera.posV.x += cosf(g_camera.rot.y) * 3.0f;
		g_camera.posR.x += cosf(g_camera.rot.y) * 3.0f;
		g_camera.posV.z -= sinf(g_camera.rot.y) * 3.0f;
		g_camera.posR.z -= sinf(g_camera.rot.y) * 3.0f;
	}


	//視点操作
	if (GetKeyboardPress(DIK_Y) == true)	//Yを押した
	{
		//注視点 上
		g_camera.posV.y += 2.0f;
	}
	if (GetKeyboardPress(DIK_N) == true)	//Nを押した
	{
		//注視点 下
		g_camera.posV.y -= 2.0f;
	}

	if (GetKeyboardPress(DIK_Z) == true)	//Zを押した
	{
		g_camera.rot.y += 0.02f;

		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI*2.0f;
		}

		//左旋回
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * 400.0f;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * 400.0f;
		
	}
	if (GetKeyboardPress(DIK_C) == true)	//Cを押した
	{
		g_camera.rot.y -= 0.02f;

		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI*2.0f;
		}

		//右旋回
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * 400.0f;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * 400.0f;

	}


	//注視点操作
	if (GetKeyboardPress(DIK_T) == true)	//Tを押した
	{
		//注視点 上
		g_camera.posR.y += 2.0f;
	}
	if (GetKeyboardPress(DIK_B) == true)	//Bを押した
	{
		//注視点 下
		g_camera.posR.y -= 2.0f;
	}
	if (GetKeyboardPress(DIK_Q) == true)	//Qを押した
	{
		g_camera.rot.y -= 0.02f;

		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI*2.0f;
		}

		//左旋回
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * 400.0f;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * 400.0f;
	}
	if (GetKeyboardPress(DIK_E) == true)	//Eを押した
	{
		g_camera.rot.y += 0.02f;

		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI*2.0f;
		}

		//右旋回
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * 400.0f;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * 400.0f;
	}


	//リセット
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -400.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
}

//=============================================================================
// 設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),								//画角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,												//手前の描画
		1000.0f);											//奥の描画

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//=============================================================================
// デバイスの取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}