#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// 衝突判定の処理 [collision.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "collision.h"
#include "player.h"
#include "enemy.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define BOX_VERTICES (8)

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void ColPlayerEnemy(void);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
VCollision g_aVCollision[MAX_VISIBLE_COLLISION];								// 可視化コリジョンの情報

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitCollision(void)
{
#ifdef _DEBUG

#endif // !_DEBUG
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitCollision(void)
{
	for (int nCntCollision = 0; nCntCollision < MAX_VISIBLE_COLLISION; nCntCollision++)
	{
		//メッシュ破棄
		if (g_aVCollision[nCntCollision].pMesh != NULL)
		{
			g_aVCollision[nCntCollision].pMesh->Release();
			g_aVCollision[nCntCollision].pMesh = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateCollision(void)
{
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();
	
	DWORD currentTime = timeGetTime();	// 現在の時間

	//敵とプレイヤーの攻撃判定
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (pEnemy[nCntEnemy].bUse == true)
		{
			//手の位置と敵の位置で判定
			D3DXVECTOR3 spherePos = D3DXVECTOR3(pPlayer->aModel[3].mtxWorld._41, pPlayer->aModel[3].mtxWorld._42, pPlayer->aModel[3].mtxWorld._43);	// 球の場所 (プレイヤーの右手の位置)
			
			//敵位置
			D3DXVECTOR3 enemyPosFix = D3DXVECTOR3(pEnemy[nCntEnemy].pos.x, pEnemy[nCntEnemy].pos.y + (pEnemy[nCntEnemy].fHeight / 2), pEnemy[nCntEnemy].pos.z);

			//判定
			pEnemy[nCntEnemy].bHit = CollisionBoxSphere(&enemyPosFix, &spherePos, pEnemy[nCntEnemy].fWidth, pEnemy[nCntEnemy].fHeight, pEnemy[nCntEnemy].fDepth, PLAYER_ATTACK_RADIUS);

			//判定がtrueの場合
			if (pEnemy[nCntEnemy].bHit == true)
			{
				//プレイヤーが攻撃状態の場合
				if (pPlayer->motionType == MOTIONTYPE_ATTACK)
				{
					//プレイヤーが無敵状態じゃない場合
					if (pEnemy[nCntEnemy].bInvincible != true)
					{
						//現在時間取得
						pEnemy[nCntEnemy].dwTimeInv = timeGetTime();

						//体力減少
						pEnemy[nCntEnemy].nLife--;

						//プレイヤーから敵へのベクトル
						D3DXVECTOR3 vecPtoE = pEnemy[nCntEnemy].pos - pPlayer->pos;
						vecPtoE = D3DXVECTOR3(vecPtoE.x, 10.0f, vecPtoE.z);
						D3DXVec3Normalize(&vecPtoE, &vecPtoE);

						//ノックバック
						pEnemy[nCntEnemy].move += vecPtoE * ENEMY_KNOCKBACK;

						//無敵時間に
						pEnemy[nCntEnemy].bInvincible = true;
					}
				}
			}
			//攻撃された時から時間経過したら無敵解除
			if (currentTime - pEnemy[nCntEnemy].dwTimeInv >= ENEMY_INVINCIBLE_TIME)
			{
				pEnemy[nCntEnemy].bInvincible = false;
			}
		}
	}

	ColPlayerEnemy();
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawCollision(void)
{
#ifdef _DEBUG
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntCollision = 0; nCntCollision < MAX_VISIBLE_COLLISION; nCntCollision++)
	{
		if (g_aVCollision[nCntCollision].bUse == true)
		{
			D3DXMATRIX mtxTrans, mtxRot;	// 計算用マトリックス
			D3DMATERIAL9 matDef;			// マテリアル保存

			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_aVCollision[nCntCollision].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aVCollision[nCntCollision].rot.y, g_aVCollision[nCntCollision].rot.x, g_aVCollision[nCntCollision].rot.z);
			D3DXMatrixMultiply(&g_aVCollision[nCntCollision].mtxWorld, &g_aVCollision[nCntCollision].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aVCollision[nCntCollision].pos.x, g_aVCollision[nCntCollision].pos.y, g_aVCollision[nCntCollision].pos.z);
			D3DXMatrixMultiply(&g_aVCollision[nCntCollision].mtxWorld, &g_aVCollision[nCntCollision].mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aVCollision[nCntCollision].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルの設定
			pDevice->SetMaterial(&g_aVCollision[nCntCollision].mat);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//モデルパーツの描画
			g_aVCollision[nCntCollision].pMesh->DrawSubset(0);

			//マテリアルをもとに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
#endif
}

//-----------------------------------------------------------------------------
// 可視コリジョンの構造体を取得
//-----------------------------------------------------------------------------
VCollision *GetVCol(void)
{
	return &g_aVCollision[0];
}

//-----------------------------------------------------------------------------
// 可視化用のスフィアを設置
//-----------------------------------------------------------------------------
void SetSphere(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fRadius, int nSlices, int nIdx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイス

	for (int nCntCollision = 0; nCntCollision < MAX_VISIBLE_COLLISION; nCntCollision++)
	{
		if (g_aVCollision[nCntCollision].bUse == false)
		{
			//スフィアのメッシュ生成
			D3DXCreateSphere(pDevice, fRadius, nSlices, nSlices, &g_aVCollision[nCntCollision].pMesh, NULL);

			//位置の設定
			g_aVCollision[nCntCollision].pos = pos;

			//向きの設定
			g_aVCollision[nCntCollision].rot = rot;

			//色の設定
			g_aVCollision[nCntCollision].mat.Diffuse = col;

			//番号付け
			g_aVCollision[nCntCollision].nIdx = nIdx;

			//使用中に移行
			g_aVCollision[nCntCollision].bUse = true;
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// 可視化用のボックスを配置
//-----------------------------------------------------------------------------
void SetBox(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fWidth, float fHeight, float fDepth, int nIdx)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイス

	for (int nCntCollision = 0; nCntCollision < MAX_VISIBLE_COLLISION; nCntCollision++)
	{
		if (g_aVCollision[nCntCollision].bUse == false)
		{
			//スフィアのメッシュ生成
			D3DXCreateBox(pDevice, fWidth, fHeight * 2, fDepth, &g_aVCollision[nCntCollision].pMesh, NULL);

			//位置の設定
			g_aVCollision[nCntCollision].pos = pos;

			//向きの設定
			g_aVCollision[nCntCollision].rot = rot;

			//色の設定
			g_aVCollision[nCntCollision].mat.Diffuse = col;

			//番号付け
			g_aVCollision[nCntCollision].nIdx = nIdx;

			//使用中に移行
			g_aVCollision[nCntCollision].bUse = true;
			break;
		}
	}
}

//-----------------------------------------------------------------------------
// 可視化コリジョンの移動反映
//-----------------------------------------------------------------------------
void MoveVCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pRot, int nIdx)
{
	for (int nCntCollision = 0; nCntCollision < MAX_VISIBLE_COLLISION; nCntCollision++)
	{
		if (g_aVCollision[nCntCollision].bUse == true && g_aVCollision[nCntCollision].nIdx == nIdx)
		{
			g_aVCollision[nCntCollision].pos = *pPos;

			g_aVCollision[nCntCollision].rot = *pRot;
		}
	}
}

//-----------------------------------------------------------------------------
// 箱と箱の当たり判定 (縦を考えない)
//-----------------------------------------------------------------------------
bool CollisionBoxBox(D3DXVECTOR3 *pPosA, D3DXVECTOR3 *pPosB, float fWidthA, float fDepthA, float fWidthB, float fDepthB)
{
	//右から
	if (pPosA->x - fWidthA < pPosB->x + fWidthB && pPosA->x - fWidthA > pPosB->x - fWidthB &&
		pPosA->z + fDepthA > pPosB->z - fDepthB && pPosA->z - fDepthA < pPosB->z + fDepthB)
	{
		return true;
	}
	//左から
	if (pPosA->x + fWidthA > pPosB->x - fWidthB && pPosA->x + fWidthA < pPosB->x + fWidthB &&
		pPosA->z + fDepthA > pPosB->z - fDepthB && pPosA->z - fDepthA < pPosB->z + fDepthB)
	{
		return true;
	}
	//奥から
	if (pPosA->z - fDepthA < pPosB->z + fDepthB && pPosA->z - fDepthA > pPosB->z - fDepthB &&
		pPosA->x + fWidthA > pPosB->x - fWidthB && pPosA->x - fWidthA < pPosB->x + fWidthB)
	{
		return true;
	}
	//手前から
	if (pPosA->z + fDepthA > pPosB->z - fDepthB && pPosA->z + fDepthA < pPosB->z + fDepthB &&
		pPosA->x + fWidthA > pPosB->x - fWidthB && pPosA->x - fWidthA < pPosB->x + fWidthB)
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// 箱と球の当たり判定
//-----------------------------------------------------------------------------
bool CollisionBoxSphere(D3DXVECTOR3 *pBoxPos, D3DXVECTOR3 *pSpherePos, float fBoxWidth, float fBoxHeight, float fBoxDepth, float fSphereRadius)
{
	D3DXVECTOR3 vtxPos[BOX_VERTICES];	// 箱の頂点

	//各頂点の位置設定
	vtxPos[0] = D3DXVECTOR3(pBoxPos->x + (fBoxWidth / 2), pBoxPos->y + fBoxHeight, pBoxPos->z - (fBoxDepth / 2));	// 右手前上
	vtxPos[1] = D3DXVECTOR3(pBoxPos->x + (fBoxWidth / 2), pBoxPos->y + fBoxHeight, pBoxPos->z + (fBoxDepth / 2));	// 右奥上
	vtxPos[2] = D3DXVECTOR3(pBoxPos->x - (fBoxWidth / 2), pBoxPos->y + fBoxHeight, pBoxPos->z - (fBoxDepth / 2));	// 左手前上
	vtxPos[3] = D3DXVECTOR3(pBoxPos->x - (fBoxWidth / 2), pBoxPos->y + fBoxHeight, pBoxPos->z + (fBoxDepth / 2));	// 左奥上
	vtxPos[4] = D3DXVECTOR3(pBoxPos->x + (fBoxWidth / 2), pBoxPos->y, pBoxPos->z - (fBoxDepth / 2));				// 右手前下
	vtxPos[5] = D3DXVECTOR3(pBoxPos->x + (fBoxWidth / 2), pBoxPos->y, pBoxPos->z + (fBoxDepth / 2));				// 右奥下
	vtxPos[6] = D3DXVECTOR3(pBoxPos->x - (fBoxWidth / 2), pBoxPos->y, pBoxPos->z - (fBoxDepth / 2));				// 左手前下
	vtxPos[7] = D3DXVECTOR3(pBoxPos->x - (fBoxWidth / 2), pBoxPos->y, pBoxPos->z + (fBoxDepth / 2));				// 左奥下
	
	for (int nCntVtx = 0; nCntVtx < BOX_VERTICES; nCntVtx++)
	{
		//各頂点から球への距離が半径以内だったらあたってる
		if (sqrtf((vtxPos[nCntVtx].x - pSpherePos->x) * ((vtxPos[nCntVtx].x) - pSpherePos->x) + (vtxPos[nCntVtx].y - pSpherePos->y) * (vtxPos[nCntVtx].y - pSpherePos->y) + (vtxPos[nCntVtx].z - pSpherePos->z) * (vtxPos[nCntVtx].z - pSpherePos->z)) <= fSphereRadius)
		{
 			return true;
		}
	}

	//長方形領域に入っていたら
	if (pSpherePos->x < pBoxPos->x + (fBoxWidth / 2) + fSphereRadius &&
		pSpherePos->x > pBoxPos->x - (fBoxWidth / 2) - fSphereRadius &&
		pSpherePos->z < pBoxPos->z + (fBoxDepth / 2) &&
		pSpherePos->z > pBoxPos->z - (fBoxDepth / 2) &&
		pSpherePos->y < pBoxPos->y + fBoxHeight &&
		pSpherePos->y > pBoxPos->y - fBoxHeight)
	{
		return true;
	}
	if (pSpherePos->x < pBoxPos->x + (fBoxWidth / 2) &&
		pSpherePos->x > pBoxPos->x - (fBoxWidth / 2) &&
		pSpherePos->z < pBoxPos->z + (fBoxDepth / 2) + fSphereRadius &&
		pSpherePos->z > pBoxPos->z - (fBoxDepth / 2) - fSphereRadius &&
		pSpherePos->y < pBoxPos->y + fBoxHeight &&
		pSpherePos->y > pBoxPos->y - fBoxHeight)
	{
		return true;
	}
	if (pSpherePos->x < pBoxPos->x + (fBoxWidth / 2) &&
		pSpherePos->x > pBoxPos->x - (fBoxWidth / 2) &&
		pSpherePos->z < pBoxPos->z + (fBoxDepth / 2) &&
		pSpherePos->z > pBoxPos->z - (fBoxDepth / 2) &&
		pSpherePos->y < pBoxPos->y + fBoxHeight + fSphereRadius &&
		pSpherePos->y > pBoxPos->y - fBoxHeight - fSphereRadius)
	{
		return true;
	}

	return false;
}

/* プレイヤーと敵の衝突 */
void ColPlayerEnemy(void)
{
	Enemy *pEnemy = GetEnemy();
	Player *pPlayer = GetPlayer();

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (pEnemy[nCntEnemy].bUse == true)
		{
			// 正方形 対 矩形 当たり判定 2d 判定後めり込み戻す
			//奥から
			if (pPlayer->pos.z - PlAYER_WIDTH < pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].fDepth && pPlayer->pos.z - PlAYER_WIDTH > pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].fDepth &&
				pPlayer->pos.x + PlAYER_WIDTH > pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].fWidth && pPlayer->pos.x - PlAYER_WIDTH < pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].fWidth)
			{
				if (pPlayer->posOld.z + PlAYER_WIDTH > pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].fDepth &&
					pPlayer->posOld.x + PlAYER_WIDTH > pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].fWidth && pPlayer->posOld.x - PlAYER_WIDTH < pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].fWidth)
				{
					pPlayer->pos.z = pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].fDepth + PlAYER_WIDTH;
				}
			}
			//手前から
			if (pPlayer->pos.z + PlAYER_WIDTH > pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].fDepth && pPlayer->pos.z + PlAYER_WIDTH < pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].fDepth &&
				pPlayer->pos.x + PlAYER_WIDTH > pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].fWidth && pPlayer->pos.x - PlAYER_WIDTH < pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].fDepth)
			{
				if (pPlayer->posOld.z - PlAYER_WIDTH < pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].fDepth &&
					pPlayer->posOld.x + PlAYER_WIDTH > pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].fWidth && pPlayer->posOld.x - PlAYER_WIDTH < pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].fWidth)
				{
					pPlayer->pos.z = pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].fDepth - PlAYER_WIDTH;
				}
			}
			//左から
			if (pPlayer->pos.x + PlAYER_WIDTH > pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].fWidth && pPlayer->pos.x - PlAYER_WIDTH < pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].fWidth &&
				pPlayer->pos.z - PlAYER_WIDTH < pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].fDepth && pPlayer->pos.z + PlAYER_WIDTH > pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].fDepth)
			{
				if (pPlayer->posOld.x <= pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].fWidth &&
					pPlayer->posOld.z - PlAYER_WIDTH <= pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].fDepth && pPlayer->posOld.z + PlAYER_WIDTH >= pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].fDepth)
				{
					pPlayer->pos.x = pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].fWidth - PlAYER_WIDTH;
				}
			}
			//右から
			if (pPlayer->pos.x + PlAYER_WIDTH > pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].fWidth && pPlayer->pos.x - PlAYER_WIDTH < pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].fWidth &&
				pPlayer->pos.z - PlAYER_WIDTH < pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].fDepth && pPlayer->pos.z + PlAYER_WIDTH > pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].fDepth)
			{
				if (pPlayer->posOld.x + PlAYER_WIDTH >= pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].fWidth &&
					pPlayer->posOld.z - PlAYER_WIDTH <= pEnemy[nCntEnemy].pos.z + pEnemy[nCntEnemy].fDepth && pPlayer->posOld.z + PlAYER_WIDTH >= pEnemy[nCntEnemy].pos.z - pEnemy[nCntEnemy].fDepth)
				{
					pPlayer->pos.x = pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].fWidth + PlAYER_WIDTH;
				}
			}
		}
	}

}