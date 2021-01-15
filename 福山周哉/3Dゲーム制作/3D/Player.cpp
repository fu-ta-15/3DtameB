//===================================================================
//
// プレイヤーの処理　[player.cpp]
// Author: fukuyama syuya
//
//===================================================================

#include "Player.h"
#include "input.h"
#include "camera.h"

//===========================================================================================================
// グローバル変数
//===========================================================================================================
PLAYER g_Player;											//モデルの情報

char *g_aModelFile[MODEL_LABEL_MAX] =
{
	"data\\MODEL\\DANB_MODEL\\body1.x",		// 胴体
	"data\\MODEL\\DANB_MODEL\\danbo.x",		// 頭部
	"data\\MODEL\\DANB_MODEL\\armR1.x",		// 右腕(肩～肘)
	"data\\MODEL\\DANB_MODEL\\armR.x",		// 右腕(肘～手首)
	"data\\MODEL\\DANB_MODEL\\handR.x",		// 右手
	"data\\MODEL\\DANB_MODEL\\armL1.x",		// 左腕(肩～肘)
	"data\\MODEL\\DANB_MODEL\\armL.x",		// 左腕(肘～手首)
	"data\\MODEL\\DANB_MODEL\\handL.x",		// 左手
	"data\\MODEL\\DANB_MODEL\\legR.x",		// 右脚(腿)
	"data\\MODEL\\DANB_MODEL\\legR.x",		// 右脚(脹脛)
	"data\\MODEL\\DANB_MODEL\\footR.x",		// 右足
	"data\\MODEL\\DANB_MODEL\\legR.x",		// 左脚(腿)
	"data\\MODEL\\DANB_MODEL\\legR.x",		// 左脚(脹脛)
	"data\\MODEL\\DANB_MODEL\\footR.x",		// 左足
	"data\\MODEL\\DANB_MODEL\\body2.x"		// 腰
};		// モデルのファイル一覧

//===========================================================================================================
// 初期化
//===========================================================================================================
void InitPlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//Xファイルの読み込み
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		D3DXLoadMeshFromX(g_aModelFile[nCntModel], D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[nCntModel].pBuffMatModel, NULL, &g_Player.aModel[nCntModel].nNumMatModel, &g_Player.aModel[nCntModel].pMeshModel);

		D3DXMATERIAL *pMat;				//マテリアルへのポインタ

		//マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_Player.aModel[nCntModel].apTextureModel[nCntMat]);
			}
		}

		int nNumVtx;					//頂点数

		DWORD sizeFVF;					//頂点フォーマットのサイズ

		BYTE *pVtxBuff;					//頂点バッファへのポインタ

										//頂点数を取得
		nNumVtx = g_Player.aModel[nCntModel].pMeshModel->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMeshModel->GetFVF());

		//頂点バッファのロック
		g_Player.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;				//頂点座標の代入



			pVtxBuff += sizeFVF;									//頂点フォーマットのサイズ分ポインタを進める
		}

		//頂点バッファのアンロック
		g_Player.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();

		g_Player.nNumModel++;
	}
	//各パーツの階層構造の設定
	g_Player.aModel[0].nIdxModelParent = -1;

	//位置と向きの初期設定
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0, 16.0, 0.0);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	//各パーツの階層構造の設定
	g_Player.aModel[1].nIdxModelParent = 0;

	//位置と向きの初期設定
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0, 23.0, 0.0);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	//各パーツの階層構造の設定
	g_Player.aModel[2].nIdxModelParent = 0;

	//位置と向きの初期設定
	g_Player.aModel[2].pos = D3DXVECTOR3(-7.0, 18.0, 0.0);
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[3].nIdxModelParent = 2;

	//位置と向きの初期設定
	g_Player.aModel[3].pos = D3DXVECTOR3(-5.0, 0.0, 0.0);
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[4].nIdxModelParent = 3;

	//位置と向きの初期設定
	g_Player.aModel[4].pos = D3DXVECTOR3(-8.0, 0.0, 0.0);
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[5].nIdxModelParent = 0;

	//位置と向きの初期設定
	g_Player.aModel[5].pos = D3DXVECTOR3(7.0, 18.0, 0.0);
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[6].nIdxModelParent = 5;

	//位置と向きの初期設定
	g_Player.aModel[6].pos = D3DXVECTOR3(5.0, 0.0, 0.0);
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[7].nIdxModelParent = 6;

	//位置と向きの初期設定
	g_Player.aModel[7].pos = D3DXVECTOR3(8.0, 0.0, 0.0);
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[8].nIdxModelParent = 0;

	//位置と向きの初期設定
	g_Player.aModel[8].pos = D3DXVECTOR3(-4.0, 8.0, 0.0);
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[9].nIdxModelParent = 8;

	//位置と向きの初期設定
	g_Player.aModel[9].pos = D3DXVECTOR3(0.0, -7.3, 0.0);
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[10].nIdxModelParent = 9;

	//位置と向きの初期設定
	g_Player.aModel[10].pos = D3DXVECTOR3(0.0, -10.0, 0.0);
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[11].nIdxModelParent = 0;

	//位置と向きの初期設定
	g_Player.aModel[11].pos = D3DXVECTOR3(4.0, 8.0, 0.0);
	g_Player.aModel[11].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[12].nIdxModelParent = 11;

	//位置と向きの初期設定
	g_Player.aModel[12].pos = D3DXVECTOR3(0.0, -7.3, 0.0);
	g_Player.aModel[12].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[13].nIdxModelParent = 12;

	//位置と向きの初期設定
	g_Player.aModel[13].pos = D3DXVECTOR3(0.0, -10.0, 0.0);
	g_Player.aModel[13].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	g_Player.aModel[14].nIdxModelParent = 0;

	//位置と向きの初期設定
	g_Player.aModel[14].pos = D3DXVECTOR3(0.0, 7.0, 0.0);
	g_Player.aModel[14].rot = D3DXVECTOR3(0.0, 0.0, 0.0);

	//モデルの初期化
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===========================================================================================================
// 終了
//===========================================================================================================
void UninitPlayer(void)
{
	//頂点バッファの開放
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_Player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMatModel->Release();
			g_Player.aModel[nCntModel].pBuffMatModel = NULL;
		}

		//テクスチャの開放
		if (g_Player.aModel[nCntModel].nNumMatModel != NULL)
		{
			g_Player.aModel[nCntModel].pMeshModel->Release();
			g_Player.aModel[nCntModel].pMeshModel = NULL;
		}
	}
}

//===========================================================================================================
// 更新処理
//===========================================================================================================
void UpdatePlayer(void)
{
	Camera *pCamera;

	pCamera = GetCamera();

	//モデルの移動
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Player.pos.x += sinf(pCamera->rot.y) * 1;
		g_Player.pos.z += cosf(pCamera->rot.y) * 1;

		g_Player.rotDest.y = D3DX_PI + pCamera->rot.y;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Player.pos.z -= cosf(pCamera->rot.y) * 1;
		g_Player.pos.x -= sinf(pCamera->rot.y) * 1;

		g_Player.rotDest.y = 0.0f + pCamera->rot.y;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Player.pos.x -= cosf(pCamera->rot.y) * 1;
		g_Player.pos.z += sinf(pCamera->rot.y) * 1;

		g_Player.rotDest.y = D3DX_PI / 2 + pCamera->rot.y;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Player.pos.x += cosf(pCamera->rot.y) * 1;
		g_Player.pos.z -= sinf(pCamera->rot.y) * 1;

		g_Player.rotDest.y = -D3DX_PI / 2 + pCamera->rot.y;
	}

	g_Player.rot.y = g_Player.rotDest.y;

	//モデルの向き
}

//===========================================================================================================
// 描画処理
//===========================================================================================================
void DrawPlayer(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;				//計算用デバイス
	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータのポインタ

	pDevice = GetDevice();						//デバイスの取得

	// プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// プレイヤーのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// プレイヤーのマテリアルデータへのポインタを取得
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;				//計算用マトリックス
		D3DXMATRIX mtxParent;								//親のマトリックス

		// モデルのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		// モデルの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRot);

		// モデルの位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTrans);

		//親のマトリックスを設定
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Player.mtxWorld;
		}

		//算出したモデルのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
						   &g_Player.aModel[nCntModel].mtxWorld,
			               &mtxParent);

		// モデルのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			
			//テクスチャの設定
			pDevice->SetTexture(0, g_Player.aModel[nCntModel].apTextureModel[nCntMat]);

			//モデルパーツの描画
			g_Player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
//===========================================================================================================
// モデルの取得
//===========================================================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}