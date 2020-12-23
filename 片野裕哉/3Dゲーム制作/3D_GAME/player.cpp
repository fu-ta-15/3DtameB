//=========================================================================================================================
//
// プレイヤー [player.cpp]
// Author:Katano Hiroya
//
//=========================================================================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"

//
// マクロ定義
//
#define MODEL_SPD (2.0f)	// プレイヤーの移動量
#define SPD_DECAY (0.4f)	// 移動量の減衰係数

//
// グローバル変数
//
PLAYER g_player;								// プレイヤー
char *g_aModelFile[MODEL_LABEL_MAX] =
{
	"data\\MODEL\\Katano_Model\\00_body_0.x",		// 胴体
	"data\\MODEL\\Katano_Model\\01_head_2.x",		// 頭部
	"data\\MODEL\\Katano_Model\\02_armR_T_0.x",		// 右腕(肩～肘)
	"data\\MODEL\\Katano_Model\\03_armR_U_0.x",		// 右腕(肘～手首)
	"data\\MODEL\\Katano_Model\\04_handR_0.x",		// 右手
	"data\\MODEL\\Katano_Model\\05_armL_T_0.x",		// 左腕(肩～肘)
	"data\\MODEL\\Katano_Model\\06_armL_U_0.x",		// 左腕(肘～手首)
	"data\\MODEL\\Katano_Model\\07_handL_0.x",		// 左手
	"data\\MODEL\\Katano_Model\\08_legR_T_1.x",		// 右脚(腿)
	"data\\MODEL\\Katano_Model\\09_legR_U_0.x",		// 右脚(脹脛)
	"data\\MODEL\\Katano_Model\\10_footR_0.x",		// 右足
	"data\\MODEL\\Katano_Model\\11_legL_T_1.x",		// 左脚(腿)
	"data\\MODEL\\Katano_Model\\12_legL_U_0.x",		// 左脚(脹脛)
	"data\\MODEL\\Katano_Model\\13_footL_0.x",		// 左足
};		// モデルのファイル一覧
LPDIRECT3DTEXTURE9 g_apTextureModel[256] = {};	// テクスチャへのポインタ

//
// 初期化処理
//
void InitPlayer(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(
			g_aModelFile[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[nCntModel].pBuffMatModel,
			NULL,
			&g_player.aModel[nCntModel].nNumMatModel,
			&g_player.aModel[nCntModel].pMeshModel);

		int nNumvtx = 0;			// 頂点数
		DWORD sizeFVF = NULL;		// 頂点フォーマットのサイズ
		BYTE *pVtxBuff = NULL;		// 頂点バッファのポインタ

		D3DXMATERIAL *pMat;	// マテリアルへのポインタ

		g_player.aModel[nCntModel].vtxMinModel = D3DXVECTOR3(65535.0f, 65535.0f, 65535.0f);
		g_player.aModel[nCntModel].vtxMaxModel = D3DXVECTOR3(-65535.0f, -65535.0f, -65535.0f);

		// 頂点数を取得
		nNumvtx = g_player.aModel[nCntModel].pMeshModel->GetNumVertices();

		// 頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCntModel].pMeshModel->GetFVF());

		// 頂点バッファをロック
		g_player.aModel[nCntModel].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVex = 0; nCntVex < nNumvtx; nCntVex++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		// 頂点座標の代入

			// ↓全ての頂点数を比較してプレイヤーの最小値・最大値を抜き出す
			if (g_player.aModel[nCntModel].vtxMinModel.x > vtx.x)
			{
				g_player.aModel[nCntModel].vtxMinModel.x = vtx.x;
			}

			if (g_player.aModel[nCntModel].vtxMinModel.y > vtx.y)
			{
				g_player.aModel[nCntModel].vtxMinModel.y = vtx.y;
			}

			if (g_player.aModel[nCntModel].vtxMinModel.z > vtx.z)
			{
				g_player.aModel[nCntModel].vtxMinModel.z = vtx.z;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.x < vtx.x)
			{
				g_player.aModel[nCntModel].vtxMaxModel.x = vtx.x;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.y < vtx.y)
			{
				g_player.aModel[nCntModel].vtxMaxModel.y = vtx.y;
			}

			if (g_player.aModel[nCntModel].vtxMaxModel.z < vtx.z)
			{
				g_player.aModel[nCntModel].vtxMaxModel.z = vtx.z;
			}
			// ↑全ての頂点数を比較してプレイヤーの最小値・最大値を抜き出す

			pVtxBuff += sizeFVF;		// 頂点フォーマットのサイズ分ポインタを進める
		}

		g_player.aModel[nCntModel].pMeshModel->UnlockVertexBuffer();

		// マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// ↓このファイル名を使用してテクスチャを読み込む
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
			}// ↑このファイル名を使用してテクスチャを読み込む
		}

		g_player.nNumModel++;
	}

	// 全パーツの階層構造設定
	g_player.aModel[0].nIdxModelParent = -1;						// 親のインデックスを設定
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);			// 位置の初期設定
	g_player.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[0].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[1].nIdxModelParent = 0;							// 親のインデックスを設定
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 27.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[1].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[2].nIdxModelParent = 0;							// 親のインデックスを設定
	g_player.aModel[2].pos = D3DXVECTOR3(-8.5f, 23.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[2].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[3].nIdxModelParent = 2;							// 親のインデックスを設定
	g_player.aModel[3].pos = D3DXVECTOR3(-11.0f, 0.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[3].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[3].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[4].nIdxModelParent = 3;							// 親のインデックスを設定
	g_player.aModel[4].pos = D3DXVECTOR3(-11.5f, 0.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[4].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[4].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[5].nIdxModelParent = 0;							// 親のインデックスを設定
	g_player.aModel[5].pos = D3DXVECTOR3(8.5f, 23.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[5].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[5].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[6].nIdxModelParent = 5;							// 親のインデックスを設定
	g_player.aModel[6].pos = D3DXVECTOR3(11.0f, 0.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[6].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[6].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[7].nIdxModelParent = 6;							// 親のインデックスを設定
	g_player.aModel[7].pos = D3DXVECTOR3(11.5f, 0.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[7].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[7].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[8].nIdxModelParent = 0;							// 親のインデックスを設定
	g_player.aModel[8].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[8].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[8].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[9].nIdxModelParent = 8;							// 親のインデックスを設定
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -14.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[9].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[9].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[10].nIdxModelParent = 9;							// 親のインデックスを設定
	g_player.aModel[10].pos = D3DXVECTOR3(0.0f, -16.5f, 0.0f);		// 位置の初期設定
	g_player.aModel[10].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[10].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[11].nIdxModelParent = 0;							// 親のインデックスを設定
	g_player.aModel[11].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[11].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[11].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[12].nIdxModelParent = 11;							// 親のインデックスを設定
	g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -14.0f, 0.0f);		// 位置の初期設定
	g_player.aModel[12].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[12].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.aModel[13].nIdxModelParent = 12;							// 親のインデックスを設定
	g_player.aModel[13].pos = D3DXVECTOR3(0.0f, -16.5f, 0.0f);		// 位置の初期設定
	g_player.aModel[13].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動量の初期設定
	g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向きの初期設定
	g_player.aModel[13].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 目的の向きの初期設定

	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置の初期設定
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 移動量の初期設定
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向きの初期設定
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 目的の向きの初期設定
}


//
// 終了処理
//
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		// メッシュの破棄
		if (g_player.aModel[nCntModel].pMeshModel != NULL)
		{
			g_player.aModel[nCntModel].pMeshModel->Release();
			g_player.aModel[nCntModel].pMeshModel = NULL;
		}

		// マテリアルの破棄
		if (g_player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_player.aModel[nCntModel].pBuffMatModel->Release();
			g_player.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}


//
// 更新処理
//
void UpdatePlayer(void)
{
	Camera *pCamera = GetCamera();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_player.rotDest.y = (-D3DX_PI + pCamera->rot.y);

		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y -= D3DX_PI * 2.0f;
		}
		if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y += D3DX_PI * 2.0f;
		}
		g_player.move.x += sinf(pCamera->rot.y) * MODEL_SPD;
		g_player.move.z += cosf(pCamera->rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_player.rotDest.y = (pCamera->rot.y);
		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y -= D3DX_PI * 2.0f;
		}
		if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y += D3DX_PI * 2.0f;
		}

		g_player.move.x -= sinf(pCamera->rot.y) * MODEL_SPD;
		g_player.move.z -= cosf(pCamera->rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_player.rotDest.y = (D3DX_PI / 2 + pCamera->rot.y);
		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y -= D3DX_PI * 2.0f;
		}
		if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y += D3DX_PI * 2.0f;
		}

		g_player.move.x -= cosf(pCamera->rot.y) * MODEL_SPD;
		g_player.move.z += sinf(pCamera->rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_player.rotDest.y = (-D3DX_PI / 2 + pCamera->rot.y);
		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y -= D3DX_PI * 2.0f;
		}
		if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y += D3DX_PI * 2.0f;
		}

		g_player.move.x += cosf(pCamera->rot.y) * MODEL_SPD;
		g_player.move.z -= sinf(pCamera->rot.y) * MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_player.rotDest.y -= 0.2f;
		if (g_player.rotDest.y < -D3DX_PI)
		{
			g_player.rotDest.y += D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{
		g_player.rotDest.y += 0.2f;
		if (g_player.rotDest.y > D3DX_PI)
		{
			g_player.rotDest.y -= D3DX_PI * 2.0f;
		}
	}

	if (GetKeyboardPress(DIK_I) == true)
	{
		g_player.move.y += MODEL_SPD;
	}

	if (GetKeyboardPress(DIK_K) == true)
	{
		g_player.move.y -= MODEL_SPD;
	}




	if ((g_player.rotDest.y - g_player.rot.y) > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if ((g_player.rotDest.y - g_player.rot.y) < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}

	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}

	g_player.move.x += (0.0f - g_player.move.x) * SPD_DECAY;
	g_player.move.z += (0.0f - g_player.move.z) * SPD_DECAY;
	g_player.move.y += (0.0f - g_player.move.y) * SPD_DECAY;

	g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;
	g_player.pos.y += g_player.move.y;
}


//
// 描画処理
//
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	// プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// プレイヤーの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);

	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// プレイヤーのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;			// 計算用マトリックス
		D3DXMATRIX mtxParent;							// 親のマトリックス

		// 各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		// プレイヤーの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRot);

		// プレイヤーの位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTrans);

		// 各パーツの親のマトリックスを設定
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;
		}

		// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
							&g_player.aModel[nCntModel].mtxWorld,
							&mtxParent);

		// 各パーツのワールドマトリックスを設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL *)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{// モデル(パーツ)の描画
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

			// プレイヤー(パーツ)の描画
			g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}

	}
	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}


//
// プレイヤーの取得
//
PLAYER *GetPlayer(void)
{
	return &g_player;
}
