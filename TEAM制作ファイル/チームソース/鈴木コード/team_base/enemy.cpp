#define _CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
//
// 敵の処理 [enemy.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "portal.h"
#include <stdio.h>

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MAX_OBJ				(30)
#define MAX_ENEMY_TYPE		(ENEMYTYPE_MAX)
#define MAX_STR				(128)
#define VECTOR_NUM			(3)			


//-----------------------------------------------------------------------------
// オブジェクト情報の構造体
//-----------------------------------------------------------------------------
typedef struct
{
	int nEnemyNum;										// モデルの数	
	int nEnemyIdx[MAX_ENEMY_TYPE];						// モデルの番号
	char cEnemyFileName[MAX_ENEMY_TYPE][MAX_STR];		// モデルのファイル名
	char cEnemyTextureName[MAX_ENEMY_TYPE][MAX_STR];		// テクスチャのファイル名
	float fEnemyPos[MAX_ENEMY_TYPE][VECTOR_NUM];			// モデルの位置(オフセット)
	float fEnemyRot[MAX_ENEMY_TYPE][VECTOR_NUM];			// モデルの向き
	int nType;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
} EnemyInfo;


//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void LoadXFileEnemy(const char* cXFileName, Model *model);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
Enemy g_aEnemy[ENEMY_AMOUNT_MAX];				// 敵の情報
int g_nEnemyAlive = 0;							// 敵の生存数

CharacterPartsInfo g_partsRobot;				// 読み込んだパーツ情報(ロボット)
KEY g_defKeyRobot[ENEMY_ROBOT_MODELPARTS];		// 

Model g_modelRobot[ENEMY_ROBOT_MODELPARTS];		// ロボットのモデル情報

bool g_bEliminated;								// 全滅したか
DWORD g_dwTimeTransition;						// 画面遷移時間計算

EnemyInfo g_ObjInfo;

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	//テキストから読み込み
	ReadCharacterInfo(&g_partsRobot, "data//TXT//motion_kogata.txt");


	//読み込んだ情報を使ってXファイル読み込み
	for (int nCntModel = 0; nCntModel < g_partsRobot.nModelNum; nCntModel++)
	{
		LoadXFileEnemy(&g_partsRobot.cModelFileName[nCntModel][0], &g_modelRobot[nCntModel]);
	}

	//各パーツの階層構造設定
	for (int nCntModel = 0; nCntModel < ENEMY_ROBOT_MODELPARTS; nCntModel++)
	{
		g_modelRobot[nCntModel].nNumModel = g_partsRobot.nModelNum;
		g_modelRobot[nCntModel].nIdxModelParent = g_partsRobot.nModelParent[nCntModel];
		g_modelRobot[nCntModel].pos = D3DXVECTOR3(g_partsRobot.fModelPos[nCntModel][0], g_partsRobot.fModelPos[nCntModel][1], g_partsRobot.fModelPos[nCntModel][2]);
		g_modelRobot[nCntModel].rot = D3DXVECTOR3(g_partsRobot.fModelRot[nCntModel][0], g_partsRobot.fModelRot[nCntModel][1], g_partsRobot.fModelRot[nCntModel][2]);
	}

	//初期キー
	for (int nCnt = 0; nCnt < ENEMY_ROBOT_MODELPARTS; nCnt++)
	{
		g_defKeyRobot[nCnt] = KeyPosRot(g_modelRobot[nCnt].pos.x, g_modelRobot[nCnt].pos.y, g_modelRobot[nCnt].pos.z, 0, 0, 0);
	}

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		//初期設定
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置の初期設定
		g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向きの初期設定
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].bInvincible = false;
		g_aEnemy[nCntEnemy].nLife = ENEMY_HP_MAX;
		g_aEnemy[nCntEnemy].nLifeMax = ENEMY_HP_MAX;
		g_aEnemy[nCntEnemy].bHit = false;
		g_aEnemy[nCntEnemy].bAttack = false;
		g_aEnemy[nCntEnemy].dwTimeAtk = NULL;
		g_aEnemy[nCntEnemy].dwTimeInv = NULL;
		g_aEnemy[nCntEnemy].nIdx = NULL;
	}
	g_nEnemyAlive = 0;
	g_dwTimeTransition = NULL;
	g_bEliminated = false;

	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 250.0f), ENEMYTYPE_ROBOT);
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitEnemy(void)
{
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateEnemy(void)
{
	DWORD dwCurrentTime = timeGetTime();	// 現在時間

	//使用中の敵を探す
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			Player *pPlayer = GetPlayer();	// プレイヤーの取得

			//移動量追加
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;

			//移動量減衰
			g_aEnemy[nCntEnemy].move.x = g_aEnemy[nCntEnemy].move.x * 0.2f;
			g_aEnemy[nCntEnemy].move.z = g_aEnemy[nCntEnemy].move.z * 0.2f;

			//重力
			g_aEnemy[nCntEnemy].move.y -= ENEMY_FALLSPEED;

			if (g_aEnemy[nCntEnemy].pos.y < 0) g_aEnemy[nCntEnemy].pos.y = 0;

			//体力なくなったら
			if (g_aEnemy[nCntEnemy].nLife <= 0)
			{
				//使用状況を切り替える
				g_aEnemy[nCntEnemy].bUse = false;

				//生存数を減算
				g_nEnemyAlive--;
			}

			//モーション管理
			if (g_aEnemy[nCntEnemy].move.x != 0.0f || g_aEnemy[nCntEnemy].move.z != 0.0f)
			{
				StartMotion(SELECTMOTION_ENEMY, MOTIONTYPE_WALK, nCntEnemy);
			}
			else
			{
				StartMotion(SELECTMOTION_ENEMY, MOTIONTYPE_NEUTRAL, nCntEnemy);
			}

			//プレイヤーとの距離
			float fDistanceToPlayer = sqrtf((pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x) * ((pPlayer->pos.x) - g_aEnemy[nCntEnemy].pos.x) + (pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z) * (pPlayer->pos.z - g_aEnemy[nCntEnemy].pos.z));

			//距離が検知範囲以内だったら
			if (fDistanceToPlayer <= ENEMY_DETECT_RADIUS)
			{
				//プレイヤーに向かう単位ベクトル
				D3DXVECTOR3 vecToPlayer = pPlayer->pos - g_aEnemy[nCntEnemy].pos;
				D3DXVec3Normalize(&vecToPlayer, &vecToPlayer);

				//移動を加算
				g_aEnemy[nCntEnemy].move += vecToPlayer * ENEMY_MOVESPEED;

				//プレイヤーへのラジアン角
				float fRadianToPlayer = atan2f(g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x, g_aEnemy[nCntEnemy].pos.z - pPlayer->pos.z);
				g_aEnemy[nCntEnemy].rot.y = fRadianToPlayer;
			}

			//距離が攻撃範囲内だったら
			if (fDistanceToPlayer <= ENEMY_ATTACK_RADIUS)
			{
				//すでに攻撃していない場合
				if (g_aEnemy[nCntEnemy].bAttack != true)
				{
					//プレイヤーの無敵時間じゃない場合
					if (pPlayer->bInvincible != true)
					{
						//現在時間取得（無敵時間計算）
						g_aEnemy[nCntEnemy].dwTimeAtk = timeGetTime();

						//現在時間取得（攻撃CT計算）
						pPlayer->dwTime = timeGetTime();

						//体力減少
						pPlayer->nLife--;

						//敵から自分に向かうベクトル
						D3DXVECTOR3 vecEnemyToPlayer = pPlayer->pos - g_aEnemy[nCntEnemy].pos;
						D3DXVec3Normalize(&vecEnemyToPlayer, &vecEnemyToPlayer);

						//ノックバック
						pPlayer->move += vecEnemyToPlayer * ENEMY_KNOCKBACK;
						pPlayer->move.y += 1.0f;

						//無敵になる
						pPlayer->bInvincible = true;

						//敵が攻撃クールタイムに入る
						g_aEnemy[nCntEnemy].bAttack = true;
					}
				}
			}

			//時間経過で攻撃CT解除
			if (dwCurrentTime - g_aEnemy[nCntEnemy].dwTimeAtk >= ENEMY_ATTACK_COOLTIME)
			{
				//CT解除
				g_aEnemy[nCntEnemy].bAttack = false;
			}
			
			//敵が全滅したら
			if (g_nEnemyAlive <= 0)
			{
				//ポータルを起動
				ActivatePortal(true, true);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();									// デバイス取得

	//ロボットタイプの敵描画
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true && g_aEnemy[nCntEnemy].type == ENEMYTYPE_ROBOT)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();									// デバイス取得
			D3DXMATRIX mtxRot, mtxTrans;												// 計算用マトリックス
			D3DMATERIAL9 matDef;														// 現在のマテリアル保存用
			D3DXMATERIAL *pMat;															// マテリアルデータへのポインタ
			D3DXMATERIAL *pMatAlt;														// 代えのマテリアル

			//プレイヤーのワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].mtxWorld);

			//プレイヤーの向き反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnemy].rot.y, g_aEnemy[nCntEnemy].rot.x, g_aEnemy[nCntEnemy].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxRot);

			//プレイヤーの位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, g_aEnemy[nCntEnemy].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].mtxWorld, &g_aEnemy[nCntEnemy].mtxWorld, &mtxTrans);

			//プレイヤーのワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].mtxWorld);

			//現在のマテリアル取得
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < ENEMY_ROBOT_MODELPARTS; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用マトリックス
				D3DXMATRIX mtxParent;					// 親のマトリックス

				//各パーツのワールドマトリックス初期化
				D3DXMatrixIdentity(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//各パーツの向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.y, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.x, g_aEnemy[nCntEnemy].aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxRotModel);

				//各パーツの位置を反映
				D3DXMatrixTranslation(&mtxTransModel, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.x, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.y, g_aEnemy[nCntEnemy].aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxTransModel);

				//各パーツの親のマトリックスを設定
				if (g_aEnemy[nCntEnemy].aModel[nCntModel].nIdxModelParent != -1)
				{
					mtxParent = g_aEnemy[nCntEnemy].aModel[g_aEnemy[nCntEnemy].aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{
					mtxParent = g_aEnemy[nCntEnemy].mtxWorld;	// プレイヤーのマトリックスを設定
				}

				//算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
				D3DXMatrixMultiply(&g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld, &mtxParent);

				//各パーツのワールドマトリックス設定
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnemy].aModel[nCntModel].mtxWorld);

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMatModel->GetBufferPointer();
				pMatAlt = (D3DXMATERIAL*)g_aEnemy[nCntEnemy].aModel[nCntModel].pBuffMatModel->GetBufferPointer();

				//無敵状態か見てモデルの色を変える
				if (g_aEnemy[nCntEnemy].bInvincible == true)
				{//無敵状態
					pMatAlt->MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f);
					for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].nNumMatModel; nCntMat++)
					{
						//マテリアル設定
						pDevice->SetMaterial(&pMatAlt[nCntMat].MatD3D);

						//テクスチャの設定
						pDevice->SetTexture(0, NULL);

						//モデルパーツの描画
						g_aEnemy[nCntEnemy].aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
					}
				}
				else if (g_aEnemy[nCntEnemy].bInvincible == false)
				{//通常状態
					pMat->MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0, 1.0f, 1.0f);
					for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnemy].aModel[nCntModel].nNumMatModel; nCntMat++)
					{
						//マテリアル設定
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						//テクスチャの設定
						pDevice->SetTexture(0, NULL);

						//モデルパーツの描画
						g_aEnemy[nCntEnemy].aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
					}
				}
			}
			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------------------------------------------------------
// プレイヤーの情報を取得
//-----------------------------------------------------------------------------
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//-----------------------------------------------------------------------------
// パーツ情報を取得
//-----------------------------------------------------------------------------
Model *GetEnemyModelParts(ENEMYTYPE type)
{
	switch (type)
	{
	case ENEMYTYPE_ROBOT:
		return &g_modelRobot[0];
		break;

	default:
		return NULL;
		break;
	}
}

//-----------------------------------------------------------------------------
// 敵を配置する
//-----------------------------------------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			//位置を指定
			g_aEnemy[nCntEnemy].pos = pos;

			//番号付け
			g_aEnemy[nCntEnemy].nIdx = nCntEnemy;

			//種類付け
			g_aEnemy[nCntEnemy].type = type;

			//パーツ情報を渡す
			switch (type)
			{
			case ENEMYTYPE_ROBOT:
				for (int nCntRobot = 0; nCntRobot < ENEMY_ROBOT_MODELPARTS; nCntRobot++)
				{
					g_aEnemy[nCntEnemy].aModel[nCntRobot] = g_modelRobot[nCntRobot];
				}
				break;

			default:
				break;
			}

			//生存数に加算
			g_nEnemyAlive++;

			//使用中に移行
			g_aEnemy[nCntEnemy].bUse = true;
			break;
		}
	}
}

void SetTextEnemy(void)
{
	// 外部ファイルへのポインタ
	FILE *pFile = fopen("data\\TXT\\enemy.txt", "r");	// ファイルオープン

	char *str;				// 文字列読み込み用
	int FileSize;			// ファイルのサイズ保存用
	bool EnemySet = false;	// 設置開始合図用
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
				fscanf(pFile, "%s %s", str, &g_ObjInfo.cEnemyFileName[nModelType][0]);
				// モデルのタイプを進める
				nModelType++;
			}
			// モデルの配置開始の合図
			if (strcmp(str, "MODEL_SET") == 0)
			{
				EnemySet = true;
			}

			while (EnemySet == true)
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
					//SetObject(g_ObjInfo.pos, g_ObjInfo.rot, (OBJECT_TYPE)g_ObjInfo.nType);
				}
				if (strcmp(str, "END_MODEL_SET") == 0)
				{// オブジェクト配置終了
					EnemySet = false;
				}
			}
		}
	}
	// メモリの開放
	free(str);
}


/* Xファイルからモデルを読み込む関数*/
void LoadXFileEnemy(const char* cXFileName, Model *model)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得

	//Xファイルの読み込み
	HRESULT hr = D3DXLoadMeshFromX(
		cXFileName,										// 読み込むファイル名
		D3DXMESH_SYSTEMMEM,								// 固定
		pDevice,										// デバイス
		NULL,											// NULL固定
		&model->pBuffMatModel,							// マテリアル
		NULL,											// NULL固定
		&model->nNumMatModel,							// マテリアル数
		&model->pMeshModel);							// メッシュ

	//マテリアル情報へのポインタ
	D3DXMATERIAL *pMat = (D3DXMATERIAL*)model->pBuffMatModel->GetBufferPointer();

	//テクスチャを取得
	for (int nCntMat = 0; nCntMat < (int)model->nNumMatModel; nCntMat++)
	{
		D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &model->pTexture[nCntMat]);
	}
}