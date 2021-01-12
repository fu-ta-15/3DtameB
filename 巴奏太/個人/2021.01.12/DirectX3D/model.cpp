#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// モデルの処理 [model.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include <stdio.h>

//
// プロトタイプ宣言
//
void MoveModel(float fMoveAngleDegree, float fMoveSpeed);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshModel = NULL;													// メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatModel;													// マテリアル(材質)へのポインタ
DWORD g_nNumMatModel = 0;														// マテリアルの数
Model g_Model;																	// モデルの情報
D3DXVECTOR3 g_posModel;															// 位置
D3DXVECTOR3 g_rotModel;															// 向き
D3DXMATRIX g_mtxWorldModel;														// ワールドマトリックス
D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel;										// モデルの最大値、最小値
LPDIRECT3DTEXTURE9 g_apTextureModel[10] = { NULL };								// テクスチャへのポインタ
D3DXVECTOR3 g_RotDiff[2];														// test

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();														// デバイスの取得

	//Xファイルの読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\chair_wood00.x",			// 読み込むファイル名
		D3DXMESH_SYSTEMMEM,						// 固定
		pDevice,								// デバイス
		NULL,									// NULL固定
		&g_pBuffMatModel,						// マテリアル
		NULL,									// NULL固定
		&g_nNumMatModel,						// マテリアル数
		&g_pMeshModel);							// メッシュ

	//初期位置、向き
	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 初期位置
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 初期向き

	int nNumVtx;		// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;		// 頂点バッファへのポインタ

	//頂点数を取得
	nNumVtx = g_pMeshModel->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//頂点バッファをロック
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標代入
		
		//最大値最小値を抜き出す
		if (vtx.x > g_vtxMaxModel.x) g_vtxMaxModel.x = vtx.x;	// X最大値
		if (vtx.x < g_vtxMinModel.x) g_vtxMinModel.x = vtx.x;	// X最小値
		if (vtx.y > g_vtxMaxModel.y) g_vtxMaxModel.y = vtx.y;	// Y最大値
		if (vtx.y < g_vtxMinModel.y) g_vtxMinModel.y = vtx.y;	// Y最小値
		if (vtx.z > g_vtxMaxModel.z) g_vtxMaxModel.z = vtx.z;	// Z最大値
		if (vtx.z < g_vtxMinModel.z) g_vtxMinModel.z = vtx.z;	// Z最小値

		pVtxBuff += sizeFVF;		// 頂点フォーマットのサイズ分だけポインタを進める
	}

	//頂点バッファをアンロック
	g_pMeshModel->UnlockVertexBuffer();

	D3DXMATERIAL *pMat;	// マテリアルへのポインタ

	//マテリアル情報へのポインタ
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
		}
	}
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitModel(void)
{
	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateModel(void)
{
	Camera *pCamera = GetCamera();
	D3DXVECTOR3 RotDiff;

	//差分計算
	RotDiff.y = g_Model.rotDest.y - g_Model.rot.y;

	//テスト
	g_RotDiff[0].y = g_Model.rotDest.y - g_Model.rot.y;
	g_RotDiff[1].y = (D3DX_PI * 2) + g_RotDiff[0].y;

	//差分の一部を足していく
	//if (g_Model.rot.y < -D3DX_PI / 2 + pCamera->rot.y)
	//{
	//	if (g_Model.rotDest.y > 0)
	//	{
	//		g_Model.rot.y += -RotDiff2.y * 0.05f;
	//	}
	//	else
	//	{
	//		g_Model.rot.y += RotDiff.y * 0.05f;
	//	}
	//}
	//else if (g_Model.rot.y > D3DX_PI / 2 + pCamera->rot.y)
	//{
	//	if (g_Model.rotDest.y < 0)
	//	{
	//		g_Model.rot.y += ((D3DX_PI * 2) + RotDiff.y) * 0.05f;
	//	}
	//	else
	//	{
	//		g_Model.rot.y += RotDiff.y * 0.05f;
	//	}
	//}
	//else
	//{
	//	g_Model.rot.y += RotDiff.y * 0.05f;
	//}
	//g_Model.rot.y += RotDiff.y * 0.05f;

	//テスト1
	//if (g_RotDiff[0].y > g_RotDiff[1].y)
	//{
	//	g_Model.rot.y += g_RotDiff[1].y * 0.05f;
	//}
	//else
	//{
	//	g_Model.rot.y += g_RotDiff[0].y * 0.05f;
	//}

	//差分がD3DX_PI以上(半周以上)の場合、逆回転
	if (g_RotDiff[0].y > D3DX_PI)
	{
		g_Model.rot.y -= ((D3DX_PI * 2) - g_RotDiff[0].y) * MODEL_SMOOTHTURNSPEED;
	}
	else if (g_RotDiff[0].y < -D3DX_PI)
	{
		g_Model.rot.y += ((D3DX_PI * 2) + g_RotDiff[0].y) * MODEL_SMOOTHTURNSPEED;
	}
	else
	{
		g_Model.rot.y += g_RotDiff[0].y * MODEL_SMOOTHTURNSPEED;
	}

	//モデルの回転
	if (GetKeyboardPress(DIK_Q) == true)
	{// 左回転
		g_Model.rotDest.y -= MODEL_SMOOTHTURNSPEED;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{//	右回転
		g_Model.rotDest.y += MODEL_SMOOTHTURNSPEED;
	}

	/* モデルの移動 */
	if (GetKeyboardPress(DIK_UP) == true)
	{
		if (GetKeyboardPress(DIK_RIGHT) == true) MoveModel(45.0f, MODEL_MOVESPEED);				// 右前
		else if (GetKeyboardPress(DIK_LEFT) == true) MoveModel(-45.0f, MODEL_MOVESPEED);		// 左前
		else MoveModel(180.0f, MODEL_MOVESPEED);													// 前
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		if (GetKeyboardPress(DIK_RIGHT) == true) MoveModel(135.0f, MODEL_MOVESPEED);			// 右後ろ
		else if (GetKeyboardPress(DIK_LEFT) == true) MoveModel(-135.0f, MODEL_MOVESPEED);		// 左後ろ
		else MoveModel(0.0f, MODEL_MOVESPEED);												// 後ろ
	}
	else if (GetKeyboardPress(DIK_LEFT) == true) MoveModel(-90.0f, MODEL_MOVESPEED);			// 左
	else if (GetKeyboardPress(DIK_RIGHT) == true) MoveModel(90.0f, MODEL_MOVESPEED);			// 右

	/* 3.14超えたら±逆に */
	//モデル向き
	if (g_Model.rot.y > D3DX_PI)
	{
		g_Model.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rot.y += D3DX_PI * 2.0f;
	}
	//モデル目標向き
	if (g_Model.rotDest.y > D3DX_PI)
	{
		g_Model.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_Model.rotDest.y < -D3DX_PI)
	{
		g_Model.rotDest.y += D3DX_PI * 2.0f;
	}
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;												// 計算用マトリックス
	D3DMATERIAL9 matDef;														// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;															// マテリアルデータへのポインタ
	pDevice = GetDevice();														// デバイスの取得

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Model.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
	D3DXMatrixMultiply(&g_Model.mtxWorld, &g_Model.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Model.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

		//モデルパーツの描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

Model *GetModel(void)
{
	return &g_Model;
}

D3DXVECTOR3 *GetVariableTest(void)
{
	return &g_RotDiff[0];
}

void MoveModel(float fMoveAngleDegree, float fMoveSpeed)
{
	Camera *pCamera = GetCamera();	// カメラの情報取得

	g_Model.pos.x += sinf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_Model.pos.z += cosf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_Model.rotDest.y = (pCamera->rot.y - D3DXToRadian(fMoveAngleDegree) * fMoveSpeed) * -1 ;
}