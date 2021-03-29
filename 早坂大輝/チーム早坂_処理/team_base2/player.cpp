#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// プレイヤーの処理 [player.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "player.h"
#include "camera.h"
#include "input.h"
#include "meshfield.h"
#include "fade.h"
#include "result.h"
#include "motion.h"


#include <stdio.h>
#include <time.h>

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define PLAYER_SMOOTHTURN_SPEED (0.1f)											// 滑らかに振り向く速度
#define READROW (1028)	// ファイル読み込みで読む最大数

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void MovePlayer(float fMoveAngleDegree, float fMoveSpeed);
HRESULT LoadXFile(const char* cXFileName, int nCountModel);
void PlayerSmoothTurn(void);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
Player g_player;													// プレイヤーの情報
D3DXVECTOR3 g_MotionKey[4][10];										// モーションのキー
KEY g_playerDefaultKey[10];
CharacterPartsInfo g_ModelInfo;										// 読み込んだモデルの情報

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	//プレイヤーの初期設定
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置の初期設定
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向きの初期設定
	g_player.bHit = false;
	g_player.bInvincible = false;
	g_player.dwTime = NULL;
	g_player.nLife = PLAYER_HEALTH;
	g_player.nLifeMax = PLAYER_HEALTH;

	//テキスト読み込み
	ReadCharacterInfo(&g_ModelInfo, "data\\TXT\\model_character.txt");

	//読み込んだ情報を使ってXファイル読み込み
	for (int nCntModel = 0; nCntModel < g_ModelInfo.nModelNum; nCntModel++)
	{
		LoadXFile(&g_ModelInfo.cModelFileName[nCntModel][0], nCntModel);
	}

	//モデルのパーツ数
	g_player.nNumModel = g_ModelInfo.nModelNum;

	//各パーツの階層構造設定
	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		g_player.aModel[nCntModel].nIdxModelParent = g_ModelInfo.nModelParent[nCntModel];
		g_player.aModel[nCntModel].pos = D3DXVECTOR3(g_ModelInfo.fModelPos[nCntModel][0], g_ModelInfo.fModelPos[nCntModel][1], g_ModelInfo.fModelPos[nCntModel][2]);
		g_player.aModel[nCntModel].rot = D3DXVECTOR3(g_ModelInfo.fModelRot[nCntModel][0], g_ModelInfo.fModelRot[nCntModel][1], g_ModelInfo.fModelRot[nCntModel][2]);
	}

	//初期キー
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		g_playerDefaultKey[nCnt] = KeyPosRot(g_player.aModel[nCnt].pos.x, g_player.aModel[nCnt].pos.y, g_player.aModel[nCnt].pos.z, 0, 0, 0);
	}
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < 2; nCntModel++)
	{
		//メッシュの破棄
		if (g_player.aModel[nCntModel].pMeshModel != NULL)
		{
			g_player.aModel[nCntModel].pMeshModel->Release();
			g_player.aModel[nCntModel].pMeshModel = NULL;
		}

		//マテリアルの破棄
		if (g_player.aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_player.aModel[nCntModel].pBuffMatModel->Release();
			g_player.aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{
	DWORD dwCurrentTime = timeGetTime();	// 現在時間

	//位置保存
	g_player.posOld = g_player.pos;

	//移動量追加
	g_player.pos += g_player.move;

	//移動量減衰
	g_player.move.x += (0 - g_player.move.x) * 0.2f;
	g_player.move.z += (0 - g_player.move.z) * 0.2f;

	//重力
	g_player.move.y -= 0.2f;

	//移動制限
	if (g_player.pos.x > FIELD_MAXSIZE) g_player.pos.x = FIELD_MAXSIZE;
	if (g_player.pos.x < -FIELD_MAXSIZE) g_player.pos.x = -FIELD_MAXSIZE;
	if (g_player.pos.z > FIELD_MAXSIZE) g_player.pos.z = FIELD_MAXSIZE;
	if (g_player.pos.z < -FIELD_MAXSIZE) g_player.pos.z = -FIELD_MAXSIZE;
	if (g_player.pos.y <= 0.0f)
	{
		g_player.move.y = 0.0f;
		g_player.pos.y = 0.0f;
	}

	/* モデルの移動 */
	if (GetKeyboardPress(DIK_W) == true)
	{
		if (GetKeyboardPress(DIK_D) == true) MovePlayer(45.0f, PLAYER_MOVESPEED);			// 右前
		else if (GetKeyboardPress(DIK_A) == true) MovePlayer(-45.0f, PLAYER_MOVESPEED);		// 左前
		else MovePlayer(0.0f, PLAYER_MOVESPEED);												// 前
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{
		if (GetKeyboardPress(DIK_D) == true) MovePlayer(135.0f, PLAYER_MOVESPEED);			// 右後ろ
		else if (GetKeyboardPress(DIK_A) == true) MovePlayer(-135.0f, PLAYER_MOVESPEED);		// 左後ろ
		else MovePlayer(-180.0f, PLAYER_MOVESPEED);												// 後ろ
	}
	else if (GetKeyboardPress(DIK_A) == true) MovePlayer(-90.0f, PLAYER_MOVESPEED);			// 左
	else if (GetKeyboardPress(DIK_D) == true) MovePlayer(90.0f, PLAYER_MOVESPEED);			// 右

	/* プレイヤーの振り向きを滑らかにする */
	PlayerSmoothTurn();

	//行動にモーションつける
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_ATTACK, NULL);
	}
	else if (GetKeyboardPress(DIK_W) ||
		GetKeyboardPress(DIK_S) ||
		GetKeyboardPress(DIK_A) ||
		GetKeyboardPress(DIK_D) == true)
	{
		StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_WALK, NULL);
	}
	else
	{
		StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_NEUTRAL, NULL);
	}

	//攻撃中は移動０にする
	if (g_player.motionType == MOTIONTYPE_ATTACK)
	{
		g_player.move = D3DXVECTOR3(0, 0, 0);
	}

	//時間経過で無敵時間解除
	if (dwCurrentTime - g_player.dwTime >= PLAYER_INVINCIBLE_TIME)
	{
		//無敵解除
		g_player.bInvincible = false;
	}


	if (GetKeyboardPress(DIK_H) == true) g_player.move.y += 1.0f;
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();									// デバイス取得
	D3DXMATRIX mtxRot, mtxTrans;												// 計算用マトリックス
	D3DMATERIAL9 matDef;														// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;															// マテリアルデータへのポインタ
	D3DXMATERIAL *pMatAlt;														// 代えのマテリアル

	//プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//プレイヤーの向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//プレイヤーの位置反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//プレイヤーのワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用マトリックス
		D3DXMATRIX mtxParent;					// 親のマトリックス

		//各パーツのワールドマトリックス初期化
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
			mtxParent = g_player.mtxWorld;	// プレイヤーのマトリックスを設定
		}

		//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxParent);

		//各パーツのワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();
		pMatAlt = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		//無敵状態か見てモデルの色を変える
		if (g_player.bInvincible == true)
		{//無敵状態
			pMatAlt->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMatAlt[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);

				//モデルパーツの描画
				g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
			}
		}
		else if (g_player.bInvincible == false)
		{//通常状態
			pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);
			for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, NULL);

				//モデルパーツの描画
				g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
			}
		}
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

}

//-----------------------------------------------------------------------------
// プレイヤーの情報を取得
//-----------------------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_player;
}
//-----------------------------------------------------------------------------
// モデルの初期状態を取得
//-----------------------------------------------------------------------------
KEY *GetDefKey(void)
{
	return &g_playerDefaultKey[0];
}

/* モデルを移動させる関数 */
void MovePlayer(float fMoveAngleDegree, float fMoveSpeed)
{
	Camera *pCamera = GetCamera();	// カメラの情報取得

	g_player.move.x += sinf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_player.move.z += cosf(pCamera->rot.y + D3DXToRadian(fMoveAngleDegree)) * fMoveSpeed;
	g_player.rotDest.y = pCamera->rot.y + D3DXToRadian(fMoveAngleDegree) + D3DX_PI;
}

/* Xファイルからモデルを読み込む関数*/
HRESULT LoadXFile(const char* cXFileName, int nCountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得
	HRESULT hres;

	//Xファイルの読み込み
	hres = D3DXLoadMeshFromX(
		cXFileName,										// 読み込むファイル名
		D3DXMESH_SYSTEMMEM,								// 固定
		pDevice,										// デバイス
		NULL,											// NULL固定
		&g_player.aModel[nCountModel].pBuffMatModel,		// マテリアル
		NULL,											// NULL固定
		&g_player.aModel[nCountModel].nNumMatModel,		// マテリアル数
		&g_player.aModel[nCountModel].pMeshModel);		// メッシュ

	return hres;
}

/* キャラの回転を滑らかにする関数 */
void PlayerSmoothTurn(void)
{
	D3DXVECTOR3 RotDiff;

	//差分計算
	RotDiff.y = g_player.rotDest.y - g_player.rot.y;

	//差分がD3DX_PI以上(半周以上)の場合、逆回転
	if (RotDiff.y > D3DX_PI)
	{
		g_player.rot.y -= ((D3DX_PI * 2) - RotDiff.y) * PLAYER_SMOOTHTURN_SPEED;
	}
	else if (RotDiff.y < -D3DX_PI)
	{
		g_player.rot.y += ((D3DX_PI * 2) + RotDiff.y) * PLAYER_SMOOTHTURN_SPEED;
	}
	else
	{
		g_player.rot.y += RotDiff.y * PLAYER_SMOOTHTURN_SPEED;
	}

	// 回転の修正 (3.14超えたら±逆に)
	if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	if (g_player.rotDest.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}
}

/* キャラクターのモデル情報を読み込む関数 */
void ReadCharacterInfo(CharacterPartsInfo *characterInfo, char* fileName)
{
	FILE *pFile;
	char cCharRead[READROW][128];
	char cEqual[2];

	int nCountModelNum = 0;
	int nCountModelIdx = 0;
	int nCountModelParent = 0;
	int nCountModelPos = 0;
	int nCountModelRot = 0;

	pFile = fopen(fileName, "r");
	if (pFile != NULL)
	{
		//1028行探す
		for (int nCntRow = 0; nCntRow < READROW; nCntRow++)
		{
			//文字列読み込み
			fscanf(pFile, "%s", &cCharRead[nCntRow][0]);

			//SCRIPTの文字列を見つけたら
			if (strcmp(&cCharRead[nCntRow][0], "SCRIPT") == 0)
			{
				for (int nCntRow = 0; nCntRow < READROW; nCntRow++)
				{
					//次の文字列読み込み
					fscanf(pFile, "%s", &cCharRead[nCntRow][0]);

					if (strcmp(&cCharRead[nCntRow][0], "NUM_MODEL") == 0)
					{
						//次の文字列
						fscanf(pFile, "%s", &cEqual[0]);

						//イコール見つかったら
						if (strcmp(&cEqual[0], "=") == 0)
						{
							//イコールの次の整数を変数に入れる
							fscanf(pFile, "%d", &characterInfo->nModelNum);
						}
					}

					if (strcmp(&cCharRead[nCntRow][0], "MODEL_FILENAME") == 0)
					{
						//次の文字列
						fscanf(pFile, "%s", &cEqual[0]);

						//イコール見つけたら
						if (strcmp(&cEqual[0], "=") == 0)
						{
							//イコールの次の文字列を配列に入れる
							fscanf(pFile, "%s", &characterInfo->cModelFileName[nCountModelNum][0]);

							//カウントアップ
							nCountModelNum++;
						}
					}

					if (strcmp(&cCharRead[nCntRow][0], "CHARACTERSET") == 0)
					{
						for (int nCntCSET = 0; nCntCSET < READROW; nCntCSET++)
						{
							fscanf(pFile, "%s", &cCharRead[nCntCSET][0]);

							//PARTSSET見つけた
							if (strcmp(&cCharRead[nCntCSET][0], "PARTSSET") == 0)
							{
								for (int nCntPSET = 0; nCntCSET < READROW; nCntCSET++)
								{
									fscanf(pFile, "%s", &cCharRead[nCntCSET][0]);

									//INDEX
									if (strcmp(&cCharRead[nCntCSET][0], "INDEX") == 0)
									{
										//次の文字列
										fscanf(pFile, "%s", &cEqual[0]);

										//イコール見つけたら
										if (strcmp(&cEqual[0], "=") == 0)
										{
											fscanf(pFile, "%d", &characterInfo->nModelIdx[nCountModelIdx]);

											nCountModelIdx++;
										}
									}

									//PARENT
									if (strcmp(&cCharRead[nCntCSET][0], "PARENT") == 0)
									{
										//次の文字列
										fscanf(pFile, "%s", &cEqual[0]);

										//イコール見つけたら
										if (strcmp(&cEqual[0], "=") == 0)
										{
											fscanf(pFile, "%d", &characterInfo->nModelParent[nCountModelParent]);

											nCountModelParent++;
										}
									}

									//POS
									if (strcmp(&cCharRead[nCntCSET][0], "POS") == 0)
									{
										//次の文字列
										fscanf(pFile, "%s", &cEqual[0]);

										//イコール見つけたら
										if (strcmp(&cEqual[0], "=") == 0)
										{
											for (int nCntVector3 = 0; nCntVector3 < 3; nCntVector3++)
											{
												fscanf(pFile, "%f", &characterInfo->fModelPos[nCountModelPos][nCntVector3]);
											}
											nCountModelPos++;
										}
									}

									//ROT
									if (strcmp(&cCharRead[nCntCSET][0], "ROT") == 0)
									{
										//次の文字列
										fscanf(pFile, "%s", &cEqual[0]);

										//イコール見つけたら
										if (strcmp(&cEqual[0], "=") == 0)
										{
											for (int nCntVector3 = 0; nCntVector3 < 3; nCntVector3++)
											{
												fscanf(pFile, "%f", &characterInfo->fModelRot[nCountModelRot][nCntVector3]);
											}
											nCountModelRot++;
										}
									}

									//END_PARTSSET見つけたらループ抜ける
									if (strcmp(&cCharRead[nCntCSET][0], "END_PARTSSET") == 0)
									{
										break;
									}
								}
							}

							//END_CHARACTERSET見つけたらループ抜ける
							if (strcmp(&cCharRead[nCntCSET][0], "END_CHARACTERSET") == 0)
							{
								break;
							}
						}
					}
				}
				break;
			}
		}
	}
}