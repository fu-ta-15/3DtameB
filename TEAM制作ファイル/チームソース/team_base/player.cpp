//=============================================================================
//
// プレイヤーの処理 [model.cpp]
// Author:Taiki Hayasaka
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MOVE_MODEL	(1.0f)
#define MOVE_BULLET (5.0f)
#define HIT_WALL	(390.0f)
#define MAX_TEX		(10)

#define VTX_MINP	(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))		// 仮頂点最小値
#define	VTX_MAXP	(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))	// 仮頂点最大値

//=============================================================================
// グローバル変数
//=============================================================================
LPD3DXMESH g_pMeshModel = NULL;						//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;				//マテリアル(材質情報)へのポインタ
DWORD g_nNumMatModel = 0;							//マテリアルの数
D3DXVECTOR3 g_vtxMinPlayer, g_vtxMaxPlayer;			//モデルの最小、最大
LPDIRECT3DTEXTURE9 g_apTextureModel[MAX_TEX] = {};	//テクスチャへのポインタ
Player g_player;									//モデル情報

D3DXVECTOR3 aCollisionPos[2];						//当たり判定ライン

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//プレイヤーの構造体の初期化
	g_player.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.boost = 200.0f;
	g_player.nNumModel = MAX_USE_MODEL;

	//変数初期化
	g_vtxMinPlayer = VTX_MINP;
	g_vtxMaxPlayer = VTX_MAXP;

	aCollisionPos[0] = D3DXVECTOR3(-200, 0, 200);
	aCollisionPos[1] = D3DXVECTOR3(200, 0, 200);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/healdrone.x",	//仮
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMat,
		NULL,
		&g_player.aModel[0].nNumMat,
		&g_player.aModel[0].pMesh);

	//各パーツの階層構造の設定
	g_player.aModel[0].nIdxModelParent = -1;	//親のインデックスを設定
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);	//位置
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

													//変数宣言
	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ
	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		//マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		//頂点数を取得
		nNumVtx = g_player.aModel[nCntModel].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[nCntModel].pMesh->GetFVF());

		//頂点バッファをロック
		g_player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		//頂点情報の抜き出し
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//全ての頂点を比較しモデルの最小値、最大値を抜き出す
			// 各座標の最大値の比較
			if (g_vtxMaxPlayer.x < vtx.x)
			{
				g_vtxMaxPlayer.x = vtx.x;
			}
			if (g_vtxMaxPlayer.y < vtx.y)
			{
				g_vtxMaxPlayer.y = vtx.y;
			}
			if (g_vtxMaxPlayer.z < vtx.z)
			{
				g_vtxMaxPlayer.z = vtx.z;
			}

			// 各座標の最小値の比較
			if (g_vtxMinPlayer.x > vtx.x)
			{
				g_vtxMinPlayer.x = vtx.x;
			}
			if (g_vtxMinPlayer.y > vtx.y)
			{
				g_vtxMinPlayer.y = vtx.y;
			}
			if (g_vtxMinPlayer.z > vtx.z)
			{
				g_vtxMinPlayer.z = vtx.z;
			}

			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//テクスチャ
		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntMat].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャの読み込み
//				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_apTextureModel[nCntMat]);
			}
		}

		//頂点バッファをアンロック
		g_player.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_USE_MODEL; nCntModel++)
	{
		//メッシュの破棄
		if (g_player.aModel[nCntModel].pMesh != NULL)
		{
			g_player.aModel[nCntModel].pMesh->Release();
			g_player.aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.aModel[nCntModel].pBuffMat->Release();
			g_player.aModel[nCntModel].pBuffMat = NULL;
		}
	}

	//テクスチャの開放
	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		if (g_apTextureModel[nCntMat] != NULL)
		{
			g_apTextureModel[nCntMat]->Release();
			g_apTextureModel[nCntMat] = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	//位置の更新
	g_player.pos.x += g_player.move.x;
	g_player.pos.y += g_player.move.y;
	g_player.pos.z += g_player.move.z;

	//移動量の減衰
	g_player.move.x += (0.0f - g_player.move.x) * 0.2f;
	g_player.move.y += (0.0f - g_player.move.y) * 0.2f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.2f;


	//重力
	if (g_player.pos.y > 0.0f)
	{
		g_player.move.y -= 0.5f;
	}

	//地面めり込み戻す
	if (g_player.pos.y < 0.0f)
	{
		g_player.pos.y = 0.0f;
	}


	// モデルの移動
	if (GetKeyboardPress(DIK_W) == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{// 左上方向
			g_player.move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * MOVE_MODEL;
			g_player.move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// 右上方向
			g_player.move.x += cosf(pCamera->rot.y - D3DX_PI / 4) * MOVE_MODEL;
			g_player.move.z -= sinf(pCamera->rot.y - D3DX_PI / 4) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y - (D3DX_PI * 3 / 4);
		}
		else
		{// 上方向
			g_player.move.x += sinf(pCamera->rot.y) * MOVE_MODEL;
			g_player.move.z += cosf(pCamera->rot.y) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{// 左下方向
			g_player.move.x += cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * MOVE_MODEL;
			g_player.move.z -= sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / 4;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{// 右下方向
			g_player.move.x -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * MOVE_MODEL;
			g_player.move.z += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y + D3DX_PI / -4;
		}
		else
		{// 下方向
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI) * MOVE_MODEL;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI) * MOVE_MODEL;
			g_player.rotDest.y = pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{// 左方向
		g_player.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL;
		g_player.move.z += sinf(pCamera->rot.y) * MOVE_MODEL;
		g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{// 右方向
		g_player.move.x += cosf(pCamera->rot.y) * MOVE_MODEL;
		g_player.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL;
		g_player.rotDest.y = pCamera->rot.y + (D3DX_PI / -2);
	}


	//モデルの向き
	if (GetKeyboardPress(DIK_LSHIFT) == true)	//左シフトを押した
	{
		g_player.rotDest.y -= D3DX_PI / 18;

	}
	if (GetKeyboardPress(DIK_RSHIFT) == true)	//右シフトを押した
	{
		g_player.rotDest.y += D3DX_PI / 18;
	}

	// 目的の回転角の上限
	if (g_player.rotDest.y - g_player.rot.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}

	// 向きの更新
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	// 現在の回転角の上限
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}


	//壁の設定
	if (g_player.pos.x < -HIT_WALL)
	{
		//左端
		g_player.pos.x = -HIT_WALL;
	}
	if (g_player.pos.x > HIT_WALL)
	{
		//右端
		g_player.pos.x = HIT_WALL;
	}
	if (g_player.pos.z > HIT_WALL)
	{
		//奥
		g_player.pos.z = HIT_WALL;
	}
	if (g_player.pos.z < -HIT_WALL)
	{
		//手前
		g_player.pos.z = -HIT_WALL;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

								//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用マトリックス
		D3DXMATRIX mtxParent;					//親のマトリックス

												//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		//各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		//各パーツの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//各パーツの位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//各パーツの親のマトリックスを設定
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;	//プレイヤーのマトリックスを設定
		}

		//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld,
			&g_player.aModel[nCntModel].mtxWorld,
			&mtxParent);

		//各パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureModel[nCntMat]);

			//モデルの描画
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// モデルの位置情報の取得
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}