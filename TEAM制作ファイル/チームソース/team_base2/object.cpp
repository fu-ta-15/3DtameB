//-----------------------------------------------------------------------------
//
// 敵の処理 [object.cpp]
// Author: Suzuki Fuut
//
//-----------------------------------------------------------------------------
#include "object.h"
#include "collision.h"
#include <stdio.h>


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MAX_OBJ				(30)
#define MAX_OBJ_TYPE		(OBJECT_TYPE_MAX)
#define MAX_STR				(128)
#define VECTOR_NUM			(3)			


//-----------------------------------------------------------------------------
// オブジェクト情報の構造体
//-----------------------------------------------------------------------------
typedef struct
{
	int nObjectNum;										// モデルの数	
	int nObjectIdx[MAX_OBJ_TYPE];						// モデルの番号
	char cObjectFileName[MAX_OBJ_TYPE][MAX_STR];		// モデルのファイル名
	char cObjectTextureName[MAX_OBJ_TYPE][MAX_STR];		// テクスチャのファイル名
	float fObjectPos[MAX_OBJ_TYPE][VECTOR_NUM];			// モデルの位置(オフセット)
	float fObjectRot[MAX_OBJ_TYPE][VECTOR_NUM];			// モデルの向き
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
} ObjectInfo;

// ポインタ
typedef struct
{
	int nObjectNum;				// モデルの数	
	int nObjectIdx;				// モデルの番号
	char cObjectFileName;		// モデルのファイル名
	char cObjectTextureName;	// テクスチャのファイル名
	float fObjectPos;			// モデルの位置(オフセット)
	float fObjectRot;			// モデルの向き
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
} pObjectInfo;


//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void LoadXFileObj(const char* cXFileName, int nCountModel);
void GetMinMaxVtx(int nIdx);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
Object g_Obj[MAX_OBJ];		// オブジェクトの情報
ObjectInfo g_ObjInfo;

// ポインタ
Object  * g_pObj;			// オブジェクトの情報
pObjectInfo  * g_pObjInfo;


//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitObject(int nStageNum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		//初期設定
		g_Obj[nCntObj].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置の初期設定
		g_Obj[nCntObj].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向きの初期設定
		g_Obj[nCntObj].bUse = false;
		g_Obj[nCntObj].Type = OBJECT_TYPE_NULL;
		g_Obj[nCntObj].nIdx = NULL;
	}

	// 初期設定   // ポインタ
	//g_pObj->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置の初期設定
	//g_pObj->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向きの初期設定
	//g_pObj->bUse = false;
	//g_pObj->Type = OBJECT_TYPE_NULL;
	//g_pObj->nIdx = NULL;

	
	// 外部ファイルからの設定
	SetTextObject(nStageNum);
}


//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitObject(void)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		//メッシュ破棄
		if (g_Obj[nCntObj].pMesh != NULL)
		{
			g_Obj[nCntObj].pMesh->Release();
			g_Obj[nCntObj].pMesh = NULL;
		}

		//マテリアル破棄
		if (g_Obj[nCntObj].pBuffMat != NULL)
		{
			g_Obj[nCntObj].pBuffMat->Release();
			g_Obj[nCntObj].pBuffMat = NULL;
		}
	}

	free(g_pObj);
}


//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateObject(void)
{
	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		if (g_Obj[nCntObj].bUse)
		{
			ColPlayerBoxThing(g_Obj[nCntObj].pos, g_Obj[nCntObj].vtxMax.x, g_Obj[nCntObj].vtxMax.z);
		}
	}
}


//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();					// デバイス取得

	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		if (g_Obj[nCntObj].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;						// 計算用マトリックス
			D3DMATERIAL9 matDef;								// 現在のマテリアル保存用
			D3DXMATERIAL *pMat;									// マテリアルデータへのポインタ
			
			//プレイヤーのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Obj[nCntObj].mtxWorld);

			//プレイヤーの向き反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Obj[nCntObj].rot.y, g_Obj[nCntObj].rot.x, g_Obj[nCntObj].rot.z);
			D3DXMatrixMultiply(&g_Obj[nCntObj].mtxWorld, &g_Obj[nCntObj].mtxWorld, &mtxRot);

			//プレイヤーの位置反映
			D3DXMatrixTranslation(&mtxTrans, g_Obj[nCntObj].pos.x, g_Obj[nCntObj].pos.y, g_Obj[nCntObj].pos.z);
			D3DXMatrixMultiply(&g_Obj[nCntObj].mtxWorld, &g_Obj[nCntObj].mtxWorld, &mtxTrans);

			//プレイヤーのワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Obj[nCntObj].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Obj[nCntObj].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Obj[nCntObj].nNumMat; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_Obj[nCntObj].pTexture[nCntMat]);

				//モデルパーツの描画
				g_Obj[nCntObj].pMesh->DrawSubset(nCntMat);
			}

			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}



//-----------------------------------------------------------------------------
// オブジェクトの情報
//-----------------------------------------------------------------------------
Object * GetObj(void)
{
	return &g_Obj[0];
}


//-----------------------------------------------------------------------------
// オブジェクトの設置
//-----------------------------------------------------------------------------
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, OBJECT_TYPE type)
{

	for (int nCntObj = 0; nCntObj < MAX_OBJ; nCntObj++)
	{
		if (g_Obj[nCntObj].bUse == false)
		{

			//位置を指定
			g_Obj[nCntObj].pos = pos;

			//向きを指定
			g_Obj[nCntObj].rot = rot;

			//番号付け
			g_Obj[nCntObj].nIdx = nCntObj;

			//Xファイルの読み込み
			LoadXFileObj(&g_ObjInfo.cObjectFileName[type][0], g_Obj[nCntObj].nIdx);

			//頂点の最大最小値を探す
			GetMinMaxVtx(nCntObj);

			//使用中に移行
			g_Obj[nCntObj].bUse = true;
			break;
		}
	}
}



//-----------------------------------------------------------------------------
// テキストでのオブジェクト配置
//-----------------------------------------------------------------------------
void SetTextObject(int nStageNum)
{
	char *aStr[128];

	if (nStageNum == 0) aStr[0] = "data\\TXT\\obj_wave1.txt";
	else if (nStageNum == 1) aStr[0] = "data\\TXT\\obj_wave2.txt";

	if (nStageNum != 2)
	{
		// 外部ファイルへのポインタ
		FILE *pFile = fopen(aStr[0], "r");	// ファイルオープン

		char *str;				// 文字列読み込み用
		int FileSize;			// ファイルのサイズ保存用
		bool ObjSet = false;	// 設置開始合図用
		int nModelType = 1;		// モデルのタイプを存用

		// ファイルの中の最後までの長さを取得
		fseek(pFile, 0, SEEK_END);
		FileSize = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		// メモリの確保
		str = (char*)malloc(sizeof(char) * FileSize);

		// メモリの初期化
		memset(str, NULL, sizeof(char) * FileSize);

		// オープンしたのか確認
		if (pFile == NULL)
		{// 開けなかったら
			printf("ファイルが開きませんでした。");
		}
		else
		{// 開けたら
			// 読み込み終了の文字列を読み込むまで
			while (strcmp(str, "END_SCRIPT") != 0)
			{
				// テキストファイルの読み込み
				fscanf(pFile, "%s", str);

				if (strcmp(str, "MODEL_NAME") == 0)
				{// モデル情報をタイプごとに保存
					// テキストファイルの読み込み
					fscanf(pFile, "%s %s", str, &g_ObjInfo.cObjectFileName[nModelType][0]);
					// モデルのタイプを進める
					nModelType++;
				}
				// モデルの配置開始の合図
				if (strcmp(str, "MODEL_SET") == 0)
				{
					ObjSet = true;
				}

				while (ObjSet == true)
				{
					// テキストファイルの読み込み
					fscanf(pFile, "%s", str);
					// モデル情報をタイプごとに保存
					if (strcmp(str, "TYPE") == 0) fscanf(pFile, "%s %d", str, &g_ObjInfo.nType);

					// 向きと位置を取得
					if (strcmp(str, "POS") == 0)
					{
						// "＝"を読み込む
						fscanf(pFile, "%s", str);
						// 数値を読み込む
						fscanf(pFile, "%f %f %f", &g_ObjInfo.pos.x, &g_ObjInfo.pos.y, &g_ObjInfo.pos.z);
					}
					if (strcmp(str, "ROT") == 0)
					{
						// "＝"を読み込む
						fscanf(pFile, "%s", str);
						// 数値を読み込む
						fscanf(pFile, "%f %f %f", &g_ObjInfo.rot.x, &g_ObjInfo.rot.y, &g_ObjInfo.rot.z);

					}
					if (strcmp(str, "SET") == 0)
					{// オブジェクトの設置
						SetObject(g_ObjInfo.pos, g_ObjInfo.rot, (OBJECT_TYPE)g_ObjInfo.nType);
					}
					if (strcmp(str, "END_MODEL_SET") == 0)
					{// オブジェクト配置終了
						ObjSet = false;
					}
				}
			}
		}
		// メモリの開放
		free(str);
	}
}

void LoadXFileObj(const char * cXFileName, int nCountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得

		//Xファイルの読み込み
		D3DXLoadMeshFromX(
			cXFileName,								// 読み込むファイル名
			D3DXMESH_SYSTEMMEM,						// 固定
			pDevice,								// デバイス
			NULL,									// NULL固定
			&g_Obj[nCountModel].pBuffMat,				// マテリアル
			NULL,									// NULL固定
			&g_Obj[nCountModel].nNumMat,				// マテリアル数
			&g_Obj[nCountModel].pMesh);					// メッシュ

		//マテリアル情報へのポインタ
		D3DXMATERIAL *pMat = (D3DXMATERIAL*)g_Obj[nCountModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Obj[nCountModel].nNumMat; nCntMat++)
		{
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_Obj[nCountModel].pTexture[nCntMat]);
		}
}

void GetMinMaxVtx(int nIdx)
{
	int nNumVtx;	// 頂点数
	DWORD sizeFVF;	// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;	// 頂点バッファへのポインタ

	//頂点数を取得
	nNumVtx = g_Obj[nIdx].pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_Obj[nIdx].pMesh->GetFVF());

	//頂点バッファをロック
	g_Obj[nIdx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標代入

		//最大値最小値を抜き出す
		if (vtx.x < g_Obj[nIdx].vtxMin.x) g_Obj[nIdx].vtxMin.x = vtx.x;	// X最小値
		if (vtx.y > g_Obj[nIdx].vtxMax.y) g_Obj[nIdx].vtxMax.y = vtx.y;	// Y最大値
		if (vtx.y < g_Obj[nIdx].vtxMin.y) g_Obj[nIdx].vtxMin.y = vtx.y;	// Y最小値
		if (vtx.z > g_Obj[nIdx].vtxMax.z) g_Obj[nIdx].vtxMax.z = vtx.z;	// Z最大値
		if (vtx.z < g_Obj[nIdx].vtxMin.z) g_Obj[nIdx].vtxMin.z = vtx.z;	// Z最小値
		if (vtx.x > g_Obj[nIdx].vtxMax.x) g_Obj[nIdx].vtxMax.x = vtx.x;	// X最大値

		pVtxBuff += sizeFVF;		// 頂点フォーマットのサイズ分だけポインタを進める
	}

	//頂点バッファをアンロック
	g_Obj[nIdx].pMesh->UnlockVertexBuffer();
}