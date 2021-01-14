//=================================================================================================================
//
// プレイヤーの処理　〔player.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "polygon.h"
#include "input.h"
#include "player.h"
#include "camera.h"
#include "bullet.h"

//=================================================================================================================
//	モデル構造体
//=================================================================================================================
typedef struct
{
	LPD3DXMESH g_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER g_pBuffMat = NULL;			//マテリアル(材質情報)へのポインタ
	DWORD g_nNumMat = 0;					//マテリアルの数
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	//int nNumMo
}Model;

//=================================================================================================================
//	プレイヤーの構造体
//=================================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
}Player;

//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexturePlayer[1] = {};		//テクスチャへのポインタ
Player g_Player;									//モデルの情報
Model g_Model;										//モデルの情報
D3DXVECTOR3 g_VtxMinPlayer;							//モデルの最小値
D3DXVECTOR3 g_VtxMaxPlayer;							//モデルの最大値

//*****************************************************************************************************************
//	モデルの初期化処理
//*****************************************************************************************************************
void InitModel(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//初期化
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期設定
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定

	//Xファイルの読み込み
	D3DXLoadMeshFromX("date\\MODEL\\torii00.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&g_pBuffMatPlayer, NULL,
		&g_nNumMatPlayer, &g_pMeshPlayer);

	D3DXMATERIAL *pMat;		//マテリアルへのポインタ
	int nNumVtx;			//頂点数
	DWORD sizeFVF;			//頂点フォーマットのサイズ
	BYTE *pVtxBuff;			//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());


	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//このファイル名を使用してテクスチャを読み込む
		}
	}


	//頂点バッファロック
	g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY,(void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++);
	{
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

		//すべての頂点を比較してモデルの最大最小を抜き出す

		pVtxBuff += sizeFVF;	//頂点フォーマットのサイズ分のポインタ
	}
	//頂点バッファをアンロック
	g_pMeshPlayer->UnlockVertexBuffer();
}

//*****************************************************************************************************************
//	モデルの終了処理
//*****************************************************************************************************************
void UninitModel(void)
{
	//メッシュの破壊
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破壊
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//*****************************************************************************************************************
//	ポリゴンの更新処理
//*****************************************************************************************************************
void UpdateModel(void)
{
	//モデルを動かす
	ControlModel();

	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		SetBullet(D3DXVECTOR3(g_Player.pos.x + 0.0f, g_Player.pos.y + 0.0f, g_Player.pos.y + 0.0f),
			D3DXVECTOR3(sinf(g_Player.rot.y) * 2.0f, 0.0f, cosf(g_Player.rot.y)* 2.0f));
	}
}

//*****************************************************************************************************************
//	ポリゴンの描画処理
//*****************************************************************************************************************
void DrawModel(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデル(パーツ)の描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//*****************************************************************************************************************
//	設定処理
//*****************************************************************************************************************
void ControlModel(void)
{	
	Camera *pCamera; 
	pCamera = GetCamera();

	//レフトキーが押されたとき
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Player.pos.x = g_Player.pos.x - cosf(pCamera->rot.y) * SPEED;
		g_Player.pos.z = g_Player.pos.z + sinf(pCamera->rot.y) * SPEED;

		g_Player.rot.y = (pCamera->rot.y) - D3DX_PI / 2.0f;
		
	}

	//ライトキーが押されたら
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Player.pos.x = g_Player.pos.x + cosf(pCamera->rot.y) * SPEED;
		g_Player.pos.z = g_Player.pos.z - sinf(pCamera->rot.y) * SPEED;
		g_Player.rot.y = (pCamera->rot.y) + D3DX_PI / 2.0f;

	}

	//ダウンキーが押されたら
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Player.pos.x = g_Player.pos.x - sinf(pCamera->rot.y) * SPEED;
		g_Player.pos.z = g_Player.pos.z - cosf(pCamera->rot.y) * SPEED;

		g_Player.rot.y = (pCamera->rot.y) - D3DX_PI;
	}

	//アップキーが押されたら	
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Player.pos.x = g_Player.pos.x + sinf(pCamera->rot.y) * SPEED;
		g_Player.pos.z = g_Player.pos.z + cosf(pCamera->rot.y) * SPEED;

		g_Player.rot.y = (pCamera->rot.y);
	}

}
//*****************************************************************************************************************
//	プレイヤーの情報
//*****************************************************************************************************************
Model *GetModel(void)
{
	return &g_Model;
}
