//=================================================================================================================
//
// メッシュフィールドの処理　〔polygon.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "meshfield.h"
#include "input.h"

//=================================================================================================================
// グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//インデックスバッファ
D3DXVECTOR3 g_posMeshfield;			//位置
D3DXVECTOR3 g_rotMeshfield;			//向き
D3DXMATRIX g_mtxWorldMeshfield;		//ワールドマトリックス


//*****************************************************************************************************************
//	メッシュフィールドの初期化処理
//*****************************************************************************************************************
HRESULT InitMeshfield(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "date\\TEXTURE\\floor01.jpg", &g_pTextureMeshfield);

	g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL)))
	{
		return E_FAIL;
	}
	 
	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	//インデックス情報へのポインタ
	WORD *pId;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//インデックスバッファをロックし番号がデータへのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pId, 0);

	//番号データの設定
	pId[0] = 3;
	pId[1] = 0;
	pId[2] = 4;
	pId[3] = 1;
	pId[4] = 5;
	pId[5] = 2;
	pId[6] = 2;
	pId[7] = 6;
	pId[8] = 6;
	pId[9] = 3;
	pId[10] = 7;
	pId[11] = 4;
	pId[12] = 8;
	pId[13] = 5;


	//インデックスバッファをアンロックする
	g_pIdxBuffMeshField->Unlock();


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);


	//頂点座標の設定 (XYZ)
	pVtx[0].pos = D3DXVECTOR3(g_posMeshfield.x - 200.0f, 0.0f, g_posMeshfield.z + 200.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, g_posMeshfield.z + 200.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posMeshfield.x + 200.0f, 0.0f, g_posMeshfield.z + 200.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posMeshfield.x - 200.0f, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f,  0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_posMeshfield.x + 200.0f, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_posMeshfield.x - 200.0f, 0.0f, g_posMeshfield.z - 200.0f);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, g_posMeshfield.z - 200.0f);
	pVtx[8].pos = D3DXVECTOR3(g_posMeshfield.x + 200.0f, 0.0f, g_posMeshfield.z - 200.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャー座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffMeshfield->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	メッシュフィールドの終了処理
//*****************************************************************************************************************
void UninitMeshfield(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}
}

//*****************************************************************************************************************
//	メッシュフィールドの更新処理
//*****************************************************************************************************************
void UpdateMeshfield(void)
{
}

//*****************************************************************************************************************
//	メッシュフィールドの描画処理
//*****************************************************************************************************************
void DrawMeshfield(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshfield);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		9,
		0,
		12);
}
