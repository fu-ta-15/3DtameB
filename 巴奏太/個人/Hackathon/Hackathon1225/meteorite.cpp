////////////////////////////////////////////////////////////////////////////////
//
//Contents	: メテオライトの処理 [meteorite.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/12/25
//
////////////////////////////////////////////////////////////////////////////////
#include "meteorite.h"
#include "Input.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_MODEL (8)

////////////////////////////////////////////////////////////////////////////////
//モデルの構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	LPD3DXMESH pMesh;			//メッシュへのポインタ
	LPD3DXBUFFER pBufferMat;	//マテリアルへのポインタ
	DWORD nNumMat;				//マテリアルの数
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	int nIdxModelParent;		//親モデルのインデックス
} MODEL;

////////////////////////////////////////////////////////////////////////////////
//プレイヤーの構造体
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 rot;			//向き
	D3DXMATRIX mtxWorld;		//ワールドマトリックス
	MODEL aModel[MAX_MODEL];	//モデル(パーツ)
	int nNumModel;				//モデル(パーツ)数
} METEORITE;

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
METEORITE g_Meteorite;	//隕石

						////////////////////////////////////////////////////////////////////////////////
						//初期化処理
						////////////////////////////////////////////////////////////////////////////////
void InitMeteorite(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/Model/inseki0.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[0].pBufferMat, NULL, &g_Meteorite.aModel[0].nNumMat, &g_Meteorite.aModel[0].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki1.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[1].pBufferMat, NULL, &g_Meteorite.aModel[1].nNumMat, &g_Meteorite.aModel[1].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[2].pBufferMat, NULL, &g_Meteorite.aModel[2].nNumMat, &g_Meteorite.aModel[2].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki3.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[3].pBufferMat, NULL, &g_Meteorite.aModel[3].nNumMat, &g_Meteorite.aModel[3].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki4.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[4].pBufferMat, NULL, &g_Meteorite.aModel[4].nNumMat, &g_Meteorite.aModel[4].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki5.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[5].pBufferMat, NULL, &g_Meteorite.aModel[5].nNumMat, &g_Meteorite.aModel[5].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki6.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[6].pBufferMat, NULL, &g_Meteorite.aModel[6].nNumMat, &g_Meteorite.aModel[6].pMesh);
	D3DXLoadMeshFromX("data/Model/inseki7.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Meteorite.aModel[7].pBufferMat, NULL, &g_Meteorite.aModel[7].nNumMat, &g_Meteorite.aModel[7].pMesh);

	g_Meteorite.nNumModel = MAX_MODEL;

	//各パーツの階層構造設定
	g_Meteorite.aModel[0].nIdxModelParent = -1;						//親モデルのインデックスを設定
	g_Meteorite.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置(オフセット)の初期設定
	g_Meteorite.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Meteorite.aModel[1].nIdxModelParent = -1;						//親モデルのインデックスを設定
	g_Meteorite.aModel[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置(オフセット)の初期設定
	g_Meteorite.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Meteorite.aModel[2].nIdxModelParent = -1;						//親モデルのインデックスを設定
	g_Meteorite.aModel[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置(オフセット)の初期設定
	g_Meteorite.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Meteorite.aModel[3].nIdxModelParent = -1;						//親モデルのインデックスを設定
	g_Meteorite.aModel[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置(オフセット)の初期設定
	g_Meteorite.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Meteorite.aModel[4].nIdxModelParent = -1;						//親モデルのインデックスを設定
	g_Meteorite.aModel[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置(オフセット)の初期設定
	g_Meteorite.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Meteorite.aModel[5].nIdxModelParent = -1;						//親モデルのインデックスを設定
	g_Meteorite.aModel[5].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置(オフセット)の初期設定
	g_Meteorite.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Meteorite.aModel[6].nIdxModelParent = -1;						//親モデルのインデックスを設定
	g_Meteorite.aModel[6].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置(オフセット)の初期設定
	g_Meteorite.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Meteorite.aModel[7].nIdxModelParent = -1;						//親モデルのインデックスを設定
	g_Meteorite.aModel[7].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置(オフセット)の初期設定
	g_Meteorite.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Meteorite.aModel[8].nIdxModelParent = -1;						//親モデルのインデックスを設定
	g_Meteorite.aModel[8].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置(オフセット)の初期設定
	g_Meteorite.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Meteorite.aModel[9].nIdxModelParent = -1;						//親モデルのインデックスを設定
	g_Meteorite.aModel[9].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置(オフセット)の初期設定
	g_Meteorite.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期設定
	g_Meteorite.pos = D3DXVECTOR3(0.0f, 0.0f, 200.0f);				//プレイヤーの位置の初期設定
	g_Meteorite.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//プレイヤーの向きの初期設定

}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitMeteorite(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_Meteorite.aModel[nCntModel].pMesh != NULL)
		{
			g_Meteorite.aModel[nCntModel].pMesh->Release();	//破棄
			g_Meteorite.aModel[nCntModel].pMesh = NULL;		//初期化
		}

		if (g_Meteorite.aModel[nCntModel].pBufferMat != NULL)
		{
			g_Meteorite.aModel[nCntModel].pBufferMat->Release();	//破棄
			g_Meteorite.aModel[nCntModel].pBufferMat = NULL;		//初期化
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateMeteorite(void)
{
	static bool bBakusan = false;

	if (GetkeyboardTrigger(DIK_RETURN) == true)
	{
		bBakusan = true;
	}

	if (bBakusan == true)
	{
		g_Meteorite.aModel[0].pos.x -= 10;
		g_Meteorite.aModel[0].pos.y += 10;
		g_Meteorite.aModel[0].pos.z += 10;
		g_Meteorite.aModel[1].pos.x += 10;
		g_Meteorite.aModel[1].pos.y += 10;
		g_Meteorite.aModel[1].pos.z += 10;
		g_Meteorite.aModel[2].pos.x += 10;
		g_Meteorite.aModel[2].pos.y -= 10;
		g_Meteorite.aModel[2].pos.z -= 10;
		g_Meteorite.aModel[3].pos.x -= 10;
		g_Meteorite.aModel[3].pos.y += 10;
		g_Meteorite.aModel[3].pos.z -= 10;
		g_Meteorite.aModel[4].pos.x -= 10;
		g_Meteorite.aModel[4].pos.y -= 10;
		g_Meteorite.aModel[4].pos.z += 10;
		g_Meteorite.aModel[5].pos.x += 10;
		g_Meteorite.aModel[5].pos.y -= 10;
		g_Meteorite.aModel[5].pos.z += 10;
		g_Meteorite.aModel[6].pos.x -= 10;
		g_Meteorite.aModel[6].pos.y -= 10;
		g_Meteorite.aModel[6].pos.z -= 10;
		g_Meteorite.aModel[7].pos.x += 10;
		g_Meteorite.aModel[7].pos.y += 10;
		g_Meteorite.aModel[7].pos.z -= 10;
	}
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawMeteorite(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

												//プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Meteorite.mtxWorld);

	//プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Meteorite.rot.y, g_Meteorite.rot.x, g_Meteorite.rot.z);
	D3DXMatrixMultiply(&g_Meteorite.mtxWorld, &g_Meteorite.mtxWorld, &mtxRot);

	//プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Meteorite.pos.x, g_Meteorite.pos.y, g_Meteorite.pos.z);
	D3DXMatrixMultiply(&g_Meteorite.mtxWorld, &g_Meteorite.mtxWorld, &mtxTrans);

	//プレイヤーのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Meteorite.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Meteorite.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用マトリックス
		D3DXMATRIX mtxParent;					//親のマトリックス

												//各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Meteorite.aModel[nCntModel].mtxWorld);

		//各パーツの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Meteorite.aModel[nCntModel].rot.y, g_Meteorite.aModel[nCntModel].rot.x, g_Meteorite.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Meteorite.aModel[nCntModel].mtxWorld, &g_Meteorite.aModel[nCntModel].mtxWorld, &mtxRot);

		//各パーツの位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Meteorite.aModel[nCntModel].pos.x, g_Meteorite.aModel[nCntModel].pos.y, g_Meteorite.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Meteorite.aModel[nCntModel].mtxWorld, &g_Meteorite.aModel[nCntModel].mtxWorld, &mtxTrans);

		//各パーツの親のマトリックスを設定
		if (g_Meteorite.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Meteorite.aModel[g_Meteorite.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Meteorite.mtxWorld;	//プレイヤーのマトリックスを設定
		}

		//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_Meteorite.aModel[nCntModel].mtxWorld, &g_Meteorite.aModel[nCntModel].mtxWorld, &mtxParent);

		//各パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Meteorite.aModel[nCntModel].mtxWorld);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL *)g_Meteorite.aModel[nCntModel].pBufferMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Meteorite.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//モデル(パーツ)の描画
			g_Meteorite.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}