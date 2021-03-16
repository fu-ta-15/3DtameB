//=============================================================================
//
// カメラの処理 [camera.cpp]
// Author:Taiki Hayasaka, Sota Tomoe
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MOVE_CAMERA (4.0f)				// 移動量
#define CAMERA_DISTANCE (600.0f)		// 距離
#define CAMERA_MOUSE_SENSITIVITY (550)	// マウスの感度
#define CAMERA_ROT_LIMIT_UPPER
#define CAMERA_ROT_LIMIT_LOWER


//=============================================================================
// グローバル変数
//=============================================================================
Camera g_camera;					//カメラの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitCamera(void)
{
	//初期化
	g_camera.posV = D3DXVECTOR3(0.0f, 300.0f, -CAMERA_DISTANCE);
	g_camera.posVDest = g_camera.posV;
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = g_camera.posR;
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	Player *pPlayer = GetPlayer();

	//マウスの移動量を視点の回転に追加
	g_camera.rot.y += GetMouseVelocity().x / 550;
	g_camera.rot.z -= GetMouseVelocity().y / 550;

	if (g_camera.rot.z > D3DX_PI / 2.0f) g_camera.rot.z = D3DX_PI / 2.0f;
	else if (g_camera.rot.z < -D3DX_PI / 2.0f) g_camera.rot.z = -D3DX_PI / 2.0f;
	if (g_camera.rot.z > 0) g_camera.rot.z = 0.0f;	// 下に突き抜けないようにする

	//D3DXPI超えた時の対処
	if (g_camera.rot.x > D3DX_PI) g_camera.rot.x -= D3DX_PI * 2.0f;
	if (g_camera.rot.x < -D3DX_PI) g_camera.rot.x += D3DX_PI * 2.0f;
	if (g_camera.rot.y > D3DX_PI) g_camera.rot.y -= D3DX_PI * 2.0f;
	if (g_camera.rot.y < -D3DX_PI) g_camera.rot.y += D3DX_PI * 2.0f;
	if (g_camera.rot.z > D3DX_PI) g_camera.rot.z -= D3DX_PI * 2.0f;
	if (g_camera.rot.z < -D3DX_PI) g_camera.rot.z += D3DX_PI * 2.0f;

	//追従
	FollowCamera();
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
		100000.0f);											//奥の描画

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
// モデルの追従
//=============================================================================
void FollowCamera(void)
{
	Player *pPlayer = GetPlayer();

	g_camera.posR = pPlayer->pos;

	//----------------------縦回転バージョン(3次元極座標(球座標))---------------------------------
	//注視点をモデルに
	g_camera.posRDest.x = pPlayer->pos.x + sinf(pPlayer->rot.y + D3DX_PI) * 10;
	g_camera.posRDest.z = pPlayer->pos.z + cosf(pPlayer->rot.y + D3DX_PI) * 10;
	g_camera.posR.y = pPlayer->pos.y + 30.0f;

	//視点をモデルからカメラの向きに長さ分だけ
	g_camera.posV.x = pPlayer->pos.x - sinf(g_camera.rot.y) * cosf(g_camera.rot.z) * CAMERA_DISTANCE;
	g_camera.posV.z = pPlayer->pos.z - cosf(g_camera.rot.y) * cosf(g_camera.rot.z) * CAMERA_DISTANCE;
	g_camera.posV.y = pPlayer->pos.y - sinf(g_camera.rot.z) * CAMERA_DISTANCE;
	//---------------------------------------------------------------------
}

//=============================================================================
// デバイスの取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}