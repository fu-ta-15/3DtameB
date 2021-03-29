//-----------------------------------------------------------------------------
//
// ボスの攻撃処理 [boss_attack.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "boss_attack.h"
#include "collision.h"
#include "player.h"
#include "game.h"
#include "input.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void UpdateFloor(void);
void AttackDetail(void);
bool CheckFloor(D3DXVECTOR3 checkPos, int nIdx);
void InitializeFloor(int nIdx);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureBossATK = NULL;			// ポリゴンのテクスチャへのポインタ																// ポータルの情報
AttackFloor g_bossAttack[BOSS_ATTACK_MAX];				// ボスの攻撃床の情報

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT InitBossATK(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data//TEXTURE//circle.png", &g_pTextureBossATK);

	//頂点バッファ生成
	for (int nCntBATK = 0; nCntBATK < BOSS_ATTACK_MAX; nCntBATK++)
	{
		VERTEX_3D *pVertex;

		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX_AMOUNT * BOSS_ATTACK_OBJ,					//サイズ
			D3DUSAGE_WRITEONLY,									//
			FVF_VERTEX_3D,										//フォーマット
			D3DPOOL_MANAGED,									//
			&g_bossAttack[nCntBATK].pVtx,						//頂点バッファへのポインタ
			NULL);

		//頂点バッファをロックし頂点情報へのポインタを取得
		g_bossAttack[nCntBATK].pVtx->Lock(0, 0, (void**)&pVertex, 0);

		for (int nCntFloor = 0; nCntFloor < BOSS_ATTACK_OBJ; nCntFloor++, pVertex += 4)
		{
			//床情報の初期化
			InitializeFloor(nCntBATK);

			//頂点座標設定
			pVertex[0].pos = D3DXVECTOR3(-BOSS_ATTACK_RADIUS, 0.0f, -BOSS_ATTACK_RADIUS);
			pVertex[1].pos = D3DXVECTOR3(-BOSS_ATTACK_RADIUS, 0.0f, BOSS_ATTACK_RADIUS);
			pVertex[2].pos = D3DXVECTOR3(BOSS_ATTACK_RADIUS, 0.0f, -BOSS_ATTACK_RADIUS);
			pVertex[3].pos = D3DXVECTOR3(BOSS_ATTACK_RADIUS, 0.0f, BOSS_ATTACK_RADIUS);

			//法線ベクトルの設定
			for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertex[nCntVtx].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//頂点カラーの設定
			if (nCntFloor == 0)
			{
				for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertex[nCntVtx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{
				for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertex[nCntVtx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);
			}

			//テクスチャ座標の設定
			pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		//頂点バッファをアンロックする
		g_bossAttack[nCntBATK].pVtx->Unlock();
	}

	//BeginBossAttack(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitBossATK(void)
{
	//テクスチャの破棄
	if (g_pTextureBossATK != NULL)
	{
		g_pTextureBossATK->Release();
		g_pTextureBossATK = NULL;
	}

	//頂点バッファの破棄
	for (int nCntBATK = 0; nCntBATK < BOSS_ATTACK_MAX; nCntBATK++)
	{
		if (g_bossAttack[nCntBATK].pVtx != NULL)
		{
			g_bossAttack[nCntBATK].pVtx->Release();
			g_bossAttack[nCntBATK].pVtx = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateBossATK(void)
{
	Player *pPlayer = GetPlayer();

	UpdateFloor();	// 床の状態更新

	if (GetKeyboardTrigger(DIK_V)) BeginBossAttack(pPlayer->pos);	// テスト用 Vでボスの攻撃プレイヤーに来る
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawBossATK(void)
{
	for (int nCntBATK = 0; nCntBATK < BOSS_ATTACK_MAX; nCntBATK++)
	{
		if (g_bossAttack[nCntBATK].bDraw == true)
		{
			LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ
			D3DXMATRIX mtxView;					// ビューマトリックス取得
			D3DXMATRIX mtxTrans, mtxRot;		// 計算用マトリックス

			//デバイス取得
			pDevice = GetDevice();

			//減算合成の設定
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ソース（描画元）の合成方法の設定
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	//デスティネーション（描画先）の合成方法の設定

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_bossAttack[nCntBATK].mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_bossAttack[nCntBATK].rot.y, g_bossAttack[nCntBATK].rot.x, g_bossAttack[nCntBATK].rot.z);
			D3DXMatrixMultiply(&g_bossAttack[nCntBATK].mtxWorld, &g_bossAttack[nCntBATK].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_bossAttack[nCntBATK].pos.x, g_bossAttack[nCntBATK].pos.y, g_bossAttack[nCntBATK].pos.z);
			D3DXMatrixMultiply(&g_bossAttack[nCntBATK].mtxWorld, &g_bossAttack[nCntBATK].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_bossAttack[nCntBATK].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_bossAttack[nCntBATK].pVtx, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			for (int nCntFloor = 0; nCntFloor < BOSS_ATTACK_OBJ; nCntFloor++)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureBossATK);

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFloor * 4, 2);
			}

			//通常合成に戻す
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		}
	}
}

//-----------------------------------------------------------------------------
// 攻撃処理の開始
//-----------------------------------------------------------------------------
void BeginBossAttack(D3DXVECTOR3 pos)
{
	for (int nCntBATK = 0; nCntBATK < BOSS_ATTACK_MAX; nCntBATK++)
	{
		if (!g_bossAttack[nCntBATK].bDraw)
		{//	描画していない物
			g_bossAttack[nCntBATK].pos = D3DXVECTOR3(pos.x, 0.0f, pos.z);		// pos set
			g_bossAttack[nCntBATK].bDraw = true;								// start draw

			break;
		}
	}
}

/* 攻撃内容 */
void AttackDetail(void)
{
	Player *pPlayer = GetPlayer();

	pPlayer->move.y += 5.0f;	// 上に飛ばす
}

/* 床の状態更新 */
void UpdateFloor(void)
{
	Player *pPlayer = GetPlayer();
	VERTEX_3D *pVertex;

	for (int nCntBATK = 0; nCntBATK < BOSS_ATTACK_MAX; nCntBATK++)
	{
		if (g_bossAttack[nCntBATK].bDraw)
		{//	描画中の物
			//0%~100%まで徐々に加算、100%で攻撃フラグを有効に
			if (g_bossAttack[nCntBATK].bDraw && g_bossAttack[nCntBATK].fFloorRatio <= 1.0f) g_bossAttack[nCntBATK].fFloorRatio += 0.01f;
			if (g_bossAttack[nCntBATK].fFloorRatio >= 1.0f)
			{
				g_bossAttack[nCntBATK].bAttackFlag = true;
				if (CheckFloor(pPlayer->pos, nCntBATK)) AttackDetail();	// 対象が範囲内か確認、入ってた場合攻撃処理
				InitializeFloor(nCntBATK);	// 床の初期化
			}

			//頂点バッファをロックし頂点情報へのポインタを取得
			g_bossAttack[nCntBATK].pVtx->Lock(0, 0, (void**)&pVertex, 0);

			pVertex += 4;	// 2枚目に行く

			pVertex[0].pos = D3DXVECTOR3(-BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio, 0.0f, -BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio);
			pVertex[1].pos = D3DXVECTOR3(-BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio, 0.0f, BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio);
			pVertex[2].pos = D3DXVECTOR3(BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio, 0.0f, -BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio);
			pVertex[3].pos = D3DXVECTOR3(BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio, 0.0f, BOSS_ATTACK_RADIUS * g_bossAttack[nCntBATK].fFloorRatio);

			g_bossAttack[nCntBATK].pVtx->Unlock();
		}
	}
}

/* 赤床の範囲内に対象が居たかチェック */
bool CheckFloor(D3DXVECTOR3 checkPos, int nIdx)
{
	//対象の位置と床の中心の距離 XZ軸
	float fDistance = sqrtf((g_bossAttack[nIdx].pos.x - checkPos.x) * ((g_bossAttack[nIdx].pos.x) - checkPos.x) + (g_bossAttack[nIdx].pos.z - checkPos.z) * (g_bossAttack[nIdx].pos.z - checkPos.z));

	if (fDistance <= BOSS_ATTACK_RADIUS)
	{//	入ってる
		return true;
	}
	else
	{//	入ってない
		return false;
	}
}

/* 床の情報を初期化する */
void InitializeFloor(int nIdx)
{
	g_bossAttack[nIdx].bAttackFlag = false;
	g_bossAttack[nIdx].bDraw = false;
	g_bossAttack[nIdx].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_bossAttack[nIdx].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_bossAttack[nIdx].fFloorRatio = 0.0f;
}