//=================================================================================================================
//
// カメラの処理　〔camera.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
Camera g_camera;
D3DXVECTOR3 g_Difference;

//*****************************************************************************************************************
//	カメラの初期化処理
//*****************************************************************************************************************
void InitCamera(void)
{
	//初期化
	g_camera.posV = D3DXVECTOR3(0.0f, 300.0f, -550.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の視点
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の注視点
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//ほぼいじらない
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//カメラの向き
}

//*****************************************************************************************************************
//	カメラの終了処理
//*****************************************************************************************************************
void UninitCamera(void)
{
}

//*****************************************************************************************************************
//	カメラの更新処理
//*****************************************************************************************************************
void UpdateCamera(void)
{
	Model *pModel;
	pModel = GetModel();

	g_camera.posRDest = pModel->pos;

	g_camera.posV.x = pModel->pos.x + sinf(g_camera.rot.y) * LONG;
	g_camera.posV.z = pModel->pos.z - cosf(g_camera.rot.y) * LONG;
	g_camera.posV.y = pModel->pos.y + 500.0f;

	g_Difference.x = g_camera.posRDest.x - g_camera.posR.x;
	g_Difference.z = g_camera.posRDest.z - g_camera.posR.z;

	g_camera.posR.x += g_Difference.x * 0.1f;
	g_camera.posR.z += g_Difference.z * 0.1f;

	//カメラ
	ControlCamera();

}

//*****************************************************************************************************************
//	設定処理
//*****************************************************************************************************************
void SetCamera(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスを作成(  、画角、　、手前の位置、奥の位置）
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

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
//*****************************************************************************************************************
//	設定処理
//*****************************************************************************************************************
void ControlCamera(void)
{
	//Aキーが押されたとき
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_camera.posR.x = g_camera.posR.x - sinf(g_camera.rot.y) * SPEED;
		g_camera.posR.z = g_camera.posR.z + cosf(g_camera.rot.y) * SPEED;

		g_camera.posV.x = g_camera.posV.x - sinf(g_camera.rot.y) * SPEED;
		g_camera.posV.z = g_camera.posV.z + cosf(g_camera.rot.y) * SPEED;
	}

	//Dキーが押されたら
	if (GetKeyboardPress(DIK_D) == true)
	{
		g_camera.posR.x = g_camera.posR.x + sinf(g_camera.rot.y) * SPEED;
		g_camera.posR.z = g_camera.posR.z - cosf(g_camera.rot.y) * SPEED;

		g_camera.posV.x = g_camera.posV.x + sinf(g_camera.rot.y) * SPEED;
		g_camera.posV.z = g_camera.posV.z - cosf(g_camera.rot.y) * SPEED;
	}

	//Sキーが押されたら
	if (GetKeyboardPress(DIK_S) == true)
	{
		g_camera.posR.x = g_camera.posR.x - sinf(g_camera.rot.y) * SPEED;
		g_camera.posR.z = g_camera.posR.z - cosf(g_camera.rot.y) * SPEED;

		g_camera.posV.x = g_camera.posV.x - sinf(g_camera.rot.y) * SPEED;
		g_camera.posV.z = g_camera.posV.z - cosf(g_camera.rot.y) * SPEED;
	}

	//Wキーが押されたら
	if (GetKeyboardPress(DIK_W) == true)
	{
		g_camera.posR.x = g_camera.posR.x + sinf(g_camera.rot.y) * SPEED;
		g_camera.posR.z = g_camera.posR.z + cosf(g_camera.rot.y) * SPEED;

		g_camera.posV.x = g_camera.posV.x + sinf(g_camera.rot.y) * SPEED;
		g_camera.posV.z = g_camera.posV.z + cosf(g_camera.rot.y) * SPEED;
	}

	//*******************************************
	// 注視点 (R)
	//*******************************************

		//Qキーが押されたら
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera.rot.y += 0.01f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * LONG;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * LONG;
	}

	//Eキーが押されたら
	if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera.rot.y -= 0.01f;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * LONG;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * LONG;
	}

	//Tキーが押されたら
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_camera.posR.z -= sinf(D3DX_PI) * SPEED;
		g_camera.posR.y += cosf(D3DX_PI) * SPEED;
	}

	//Bキーが押されたら
	if (GetKeyboardPress(DIK_B) == true)
	{
		g_camera.posR.z += sinf(D3DX_PI) * SPEED;
		g_camera.posR.y -= cosf(D3DX_PI) * SPEED;
	}

	//*******************************************
	// 視点(V)
	//*******************************************

		//Zキーが押されたら
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_camera.rot.y += 0.01f;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * LONG;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * LONG;
	}

	//Cキーが押されたら
	if (GetKeyboardPress(DIK_C) == true)
	{
		g_camera.rot.y -= 0.01f;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * LONG;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * LONG;
	}

	//Yキーが押されたら
	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_camera.posV.z += sinf(D3DX_PI) * SPEED;
		g_camera.posV.y -= cosf(D3DX_PI) * SPEED;
	}

	//Nキーが押されたら
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_camera.posV.z -= sinf(D3DX_PI) * SPEED;
		g_camera.posV.y += cosf(D3DX_PI) * SPEED;
	}

}

//*****************************************************************************************************************
//	カメラ
//*****************************************************************************************************************
Camera *GetCamera(void)
{
	return &g_camera;
}