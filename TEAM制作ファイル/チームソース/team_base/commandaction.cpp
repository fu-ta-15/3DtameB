//-----------------------------------------------------------------------------
//
// コマンドアクションの処理 [commandaction.cpp]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#include "commandaction.h"
#include "player.h"
#include "enemy.h"
#include "input.h"
#include <time.h>

//-----------------------------------------------------------------------------
//マクロ定義
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void SetCommandActionState(bool bActive);
void OnPlayerSccessAction(void);

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
CommandAction g_commandAct;						// コマンドアクションの情報
PWEAPON playerWeaponTest = PWEAPON_NAGINATA;		// プレイヤーの持っている武器 (後でplayer構造体の物を使う）
//D3DXVECTOR3 g_posButton[CA_BUTTON_NUM];			// ボタンを配置する位置

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT InitCommand(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得
	srand((unsigned)time(0));

	//初期化
	g_commandAct.nActionNum = CA_BUTTON_NUM_NAGINATA;	// 表示するボタンの数
	g_commandAct.nActionCounter = 0;					// カウンター初期化
	for (int nCntBtn = 0; nCntBtn < g_commandAct.nActionNum; nCntBtn++)
	{
		//ボタンの数によって位置を変える
		g_commandAct.buttonInfo.pos[nCntBtn] = D3DXVECTOR3(nCntBtn * CA_BUTTON_SPACE + CA_BUTTON_POS_X - CA_BUTTON_SPACE * (float)g_commandAct.nActionNum / 2, CA_BUTTON_POS_Y, 0.0f);
	}
	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++)
	{
		//順番をランダムで決定
		g_commandAct.nActionOrder[nCntBtn] = rand() % CA_BUTTON_TYPE;

		//押された順番を初期化
		g_commandAct.nActionOrderOut[nCntBtn] = 0;
	}

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command A00.png", &g_commandAct.buttonInfo.pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command B00.png", &g_commandAct.buttonInfo.pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command X00.png", &g_commandAct.buttonInfo.pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\command Y00.png", &g_commandAct.buttonInfo.pTexture[3]);

	//頂点バッファの生成 ボタン
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_AMOUNT * CA_BUTTON_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_commandAct.buttonInfo.pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVertexButton;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_commandAct.buttonInfo.pVtxBuff->Lock(0, 0, (void**)&pVertexButton, 0);

	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++, pVertexButton += 4)
	{
		//頂点座標 D3DXVECTOR3(X,Y, 0.0f);
		pVertexButton[0].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x, g_commandAct.buttonInfo.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);		 //TRIANGLESTRIPで四角
		pVertexButton[1].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x, g_commandAct.buttonInfo.pos[nCntBtn].y, 0.0f);
		pVertexButton[2].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_commandAct.buttonInfo.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);
		pVertexButton[3].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_commandAct.buttonInfo.pos[nCntBtn].y, 0.0f);

		//rhwの設定
		for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton[nCntVtx].rhw = 1.0f;

		//頂点カラーの設定
		for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//頂点情報の設定
		pVertexButton[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVertexButton[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVertexButton[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVertexButton[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}
	//頂点バッファをアンロックする
	g_commandAct.buttonInfo.pVtxBuff->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitCommand(void)
{
	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_TYPE; nCntBtn++)
	{
		//テクスチャの開放
		if (g_commandAct.buttonInfo.pTexture[nCntBtn] != NULL)
		{
			g_commandAct.buttonInfo.pTexture[nCntBtn]->Release();
			g_commandAct.buttonInfo.pTexture[nCntBtn] = NULL;
		}
	}
	//頂点バッファの開放
	if (g_commandAct.buttonInfo.pVtxBuff != NULL)
	{
		g_commandAct.buttonInfo.pVtxBuff->Release();
		g_commandAct.buttonInfo.pVtxBuff = NULL;
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateCommand(void)
{
	//プレイヤーの持ってる武器によってコマンドの数を変える
	switch (playerWeaponTest)
	{
	case PWEAPON_KATANA:
		g_commandAct.nActionNum = CA_BUTTON_NUM_KATANA;
		break;

	case PWEAPON_NAGINATA:
		g_commandAct.nActionNum = CA_BUTTON_NUM_NAGINATA;
		break;
	default:
		break;
	}

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVertexButton;
	g_commandAct.buttonInfo.pVtxBuff->Lock(0, 0, (void**)&pVertexButton, 0);

	for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++, pVertexButton += 4)
	{
		//頂点座標の更新
		pVertexButton[0].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x, g_commandAct.buttonInfo.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);		 //TRIANGLESTRIPで四角
		pVertexButton[1].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x, g_commandAct.buttonInfo.pos[nCntBtn].y, 0.0f);
		pVertexButton[2].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_commandAct.buttonInfo.pos[nCntBtn].y + CA_BUTTON_HEIGHT, 0.0f);
		pVertexButton[3].pos = D3DXVECTOR3(g_commandAct.buttonInfo.pos[nCntBtn].x + CA_BUTTON_WIDTH, g_commandAct.buttonInfo.pos[nCntBtn].y, 0.0f);
	}
	//頂点バッファをアンロックする
	g_commandAct.buttonInfo.pVtxBuff->Unlock();

	if (GetKeyboardTrigger(DIK_B) == true) SetCommandActionState(true);
	if (g_commandAct.nActionCounter >= g_commandAct.nActionNum) SetCommandActionState(false);

	//コマンド入力の部分
	if (g_commandAct.bActive == true)
	{
		VERTEX_2D *pVertexButton1;
		//頂点バッファロック
		g_commandAct.buttonInfo.pVtxBuff->Lock(0, 0, (void**)&pVertexButton1, 0);

		//入力
		if (GetKeyboardTrigger(DIK_1) == true)			// A
		{
			g_commandAct.nActionOrderOut[g_commandAct.nActionCounter] = 0;	// 入力したボタンを入れる
			pVertexButton1 += (g_commandAct.nActionCounter) * 4;			// 頂点のポインタをカウンタの場所までずらす
			g_commandAct.bPress = true;	// 入力フラグ入れる
		}
		else if (GetKeyboardTrigger(DIK_2) == true)		// B
		{
			g_commandAct.nActionOrderOut[g_commandAct.nActionCounter] = 1;
			pVertexButton1 += (g_commandAct.nActionCounter) * 4;
			g_commandAct.bPress = true;
		}
		else if (GetKeyboardTrigger(DIK_3) == true)		// X
		{
			g_commandAct.nActionOrderOut[g_commandAct.nActionCounter] = 2;
			pVertexButton1 += (g_commandAct.nActionCounter) * 4;
			g_commandAct.bPress = true;
		}
		else if (GetKeyboardTrigger(DIK_4) == true)		// Y
		{
			g_commandAct.nActionOrderOut[g_commandAct.nActionCounter] = 3;
			pVertexButton1 += (g_commandAct.nActionCounter) * 4;

			g_commandAct.bPress = true;
		}

		if (g_commandAct.nActionCounter >= 0 && g_commandAct.nActionCounter < g_commandAct.nActionNum && g_commandAct.bPress == true)
		{// カウンタが範囲内で指定キーが押された時
			if (g_commandAct.nActionOrder[g_commandAct.nActionCounter] == g_commandAct.nActionOrderOut[g_commandAct.nActionCounter])
			{//	入力のボタンと指示が一致していた場合
				for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton1[nCntVtx].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);	// 色変える

				g_commandAct.nActionNumCorrect++;	// 正解数にプラス

				g_commandAct.nActionCounter++;	// カウントアップ
				g_commandAct.bPress = false;	// 入力フラグ切る
			}
			else if (g_commandAct.nActionOrder[g_commandAct.nActionCounter] != g_commandAct.nActionOrderOut[g_commandAct.nActionCounter])
			{// 入力のボタンと指示が一致していなかった場合
				for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton1[nCntVtx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);	// 色変える

				g_commandAct.nActionCounter++;	// カウントアップ
				g_commandAct.bPress = false;	// 入力フラグ切る
			}
		}

		//アンロック
		g_commandAct.buttonInfo.pVtxBuff->Unlock();
	}
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawCommand(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイス取得

	if (g_commandAct.bActive == true)
	{
		for (int nCntBtn = 0; nCntBtn < g_commandAct.nActionNum; nCntBtn++)
		{
			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_commandAct.buttonInfo.pVtxBuff, 0, sizeof(VERTEX_2D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_commandAct.buttonInfo.pTexture[g_commandAct.nActionOrder[nCntBtn]]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBtn * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// コマンドアクションの情報を取得
//-----------------------------------------------------------------------------
CommandAction *GetCAction(void)
{
	return &g_commandAct;
}

/* コマンドアクションの状態を設定する */
void SetCommandActionState(bool bActive)
{
	if (bActive == true)
	{// 開始
		srand((unsigned)time(0));

		g_commandAct.bActive = true;		// 非アクティブ化
		g_commandAct.bPress = false;		// 入力フラグリセット
		g_commandAct.nActionCounter = 0;	// カウンターリセット
		g_commandAct.nActionNumCorrect = 0;	// 正答数リセット

		for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++)
		{//	ボタンの数だけ
			g_commandAct.nActionOrder[nCntBtn] = rand() % CA_BUTTON_TYPE;		// 押す順番ランダム設定
			g_commandAct.nActionOrderOut[nCntBtn] = 0;						// 押した順番リセット
		}

		//押すボタン数を設定
		if (playerWeaponTest == PWEAPON_KATANA) g_commandAct.nActionNum = CA_BUTTON_NUM_KATANA;
		else if (playerWeaponTest == PWEAPON_NAGINATA) g_commandAct.nActionNum = CA_BUTTON_NUM_NAGINATA;
	}
	else
	{//	終了
		OnPlayerSccessAction();

		g_commandAct.bActive = false;		// 非アクティブ化
		g_commandAct.bPress = false;		// 入力フラグリセット
		g_commandAct.nActionCounter = 0;	// カウンターリセット
		g_commandAct.nActionNum = 0;		// 押す数リセット
		g_commandAct.nActionNumCorrect = 0;	// 正答数リセット

		for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++)
		{//	ボタンの数だけ
			g_commandAct.nActionOrder[nCntBtn] = 0;		// 押す順番リセット
			g_commandAct.nActionOrderOut[nCntBtn] = 0;	// 押した順番リセット
		}


		//頂点バッファロック
		VERTEX_2D *pVertexButton;
		g_commandAct.buttonInfo.pVtxBuff->Lock(0, 0, (void**)&pVertexButton, 0);

		for (int nCntBtn = 0; nCntBtn < CA_BUTTON_NUM; nCntBtn++, pVertexButton += 4)
		{
			for (int nCntVtx = 0; nCntVtx < VERTEX_AMOUNT; nCntVtx++) pVertexButton[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}

		//アンロック
		g_commandAct.buttonInfo.pVtxBuff->Unlock();
	}
}

/* コマンドアクション成功後に呼ばれる */
void OnPlayerSccessAction(void)
{
	Player *pPlayer = GetPlayer();
	Enemy *pEnemy = GetEnemy();

	StartMotion(SELECTMOTION_PLAYER, MOTIONTYPE_ATTACK, NULL);

	for (int nCntEnemy = 0; nCntEnemy < ENEMY_AMOUNT_MAX; nCntEnemy++)
	{
		//敵との距離 高さを考えない
		float fDistanceToEnemy = sqrtf((pPlayer->pos.x - pEnemy[nCntEnemy].pos.x) * ((pPlayer->pos.x) - pEnemy[nCntEnemy].pos.x) + (pPlayer->pos.z - pEnemy[nCntEnemy].pos.z) * (pPlayer->pos.z - pEnemy[nCntEnemy].pos.z));

		//距離が検知範囲以内だったら
		if (fDistanceToEnemy <= CA_ATTACK_RADIUS)
		{
			//プレイヤーから敵への単位ベクトル
			D3DXVECTOR3 vecPtoE = pEnemy[nCntEnemy].pos - pPlayer->pos;
			D3DXVec3Normalize(&vecPtoE, &vecPtoE);

			//敵ノックバック
			pEnemy[nCntEnemy].move.x += vecPtoE.x * CA_ATTACK_KNOCKBACK;
			pEnemy[nCntEnemy].move.y += 10.0f;
			pEnemy[nCntEnemy].move.z += vecPtoE.z * CA_ATTACK_KNOCKBACK;
			
		}
	}
}

