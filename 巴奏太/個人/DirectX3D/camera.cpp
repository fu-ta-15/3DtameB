//-----------------------------------------------------------------------------
//
// カメラの処理 [camera.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "camera.h"
#include "input.h"
#include "model.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define CAMERA_DISTANCE (50.0f)													// 視点と注視点までの距離
#define CAMERA_SPEED (0.1f)														// カメラの旋回速度

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
	g_camera.posV = D3DXVECTOR3(0.0f, 150.0f, -100.0f);				// 視点
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
	Model *pModel;
	pModel = GetModel();

	//注視点をモデルに
	g_camera.posR = pModel->pos;

	//視点をモデルからカメラの向きに長さ分だけ
	g_camera.posV.x = pModel->pos.x - sinf(g_camera.rot.y) * 100;
	g_camera.posV.z = pModel->pos.z - cosf(g_camera.rot.y) * 100;

	////前進
	//if (GetKeyboardPress(DIK_W) == true)
	//{
	//	//視点の位置移動、g_camera.rotの向きに
	//	g_camera.posV.x += sinf(g_camera.rot.y);
	//	g_camera.posV.z += cosf(g_camera.rot.y);

	//	//注視点の位置固定、g_camera.rotの向きに
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////後退
	//if (GetKeyboardPress(DIK_S) == true)
	//{
	//	g_camera.posV.x -= sinf(g_camera.rot.y);
	//	g_camera.posV.z -= cosf(g_camera.rot.y);
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////右
	//if (GetKeyboardPress(DIK_D) == true)
	//{
	//	g_camera.posV.x += sinf(g_camera.rot.y + D3DXToRadian(90));
	//	g_camera.posV.z += cosf(g_camera.rot.y + D3DXToRadian(90));
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////左
	//if (GetKeyboardPress(DIK_A) == true)
	//{
	//	g_camera.posV.x -= sinf(g_camera.rot.y + D3DXToRadian(90));
	//	g_camera.posV.z -= cosf(g_camera.rot.y + D3DXToRadian(90));
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}

	////注視点　右旋回
	//if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_camera.rot.y += CAMERA_SPEED;
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////注視点　左旋回
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	//向きの移動
	//	g_camera.rot.y -= CAMERA_SPEED;

	//	//注視点の位置固定、g_camera.rotの向きに
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////注視点　上昇
	//else if (GetKeyboardPress(DIK_T) == true)
	//{
	//	g_camera.posR.y += CAMERA_SPEED * 10;
	//}
	////注視点　下降
	//else if (GetKeyboardPress(DIK_B) == true)
	//{
	//	g_camera.posR.y -= CAMERA_SPEED * 10;
	//}

	////視点　左旋回
	//if (GetKeyboardPress(DIK_Z) == true)
	//{
	//	//視点の位置移動
	//	g_camera.rot.y += CAMERA_SPEED;

	//	//視点の固定、g_camera.rotの向きに
	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////視点　右旋回
	//else if (GetKeyboardPress(DIK_C) == true)
	//{
	//	g_camera.rot.y -= CAMERA_SPEED;

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_DISTANCE;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_DISTANCE;
	//}
	////視点　上昇
	//else if (GetKeyboardPress(DIK_Y) == true)
	//{
	//	g_camera.posV.y += CAMERA_SPEED * 10;
	//}
	////視点　下降
	//else if (GetKeyboardPress(DIK_N) == true)
	//{
	//	g_camera.posV.y -= CAMERA_SPEED * 10;
	//}

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