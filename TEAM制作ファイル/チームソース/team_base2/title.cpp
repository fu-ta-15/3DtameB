//=================================================================================================================
//
// タイトルの処理　〔title.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "title.h"
#include "input.h"
#include "player.h"
#include "fade.h"
#include "meshfield.h"
#include "Dinput.h"
#include "sound.h"

//=================================================================================================================
// マクロ定義
//=================================================================================================================

//=================================================================================================================
//　グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexResult[MAX_TITLE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
int g_nPatternAnim;
int g_nCounterAnim;
float g_TitleMove;		// ロゴの変数
int g_CntMove;			// ロゴの変数
bool g_bPush;			// プッシュが押されたか
int g_nCntPush;			// プッシュボタンの変数
int g_nCntEnter;		// プッシュボタンの変数
bool g_bEnter;			// プッシュが押されたか

//*****************************************************************************************************************
// タイトルの初期化処理
//*****************************************************************************************************************
HRESULT InitTitle(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//初期化
	g_nPatternAnim = 0;
	g_nCounterAnim = 0;
	g_TitleMove = 2.0f;
	g_CntMove = 0;
	g_nCntPush = 0;
	g_nCntEnter = 40;
	g_bPush = true;
	g_bEnter = false;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG031.jpg", &g_apTexResult[TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Titil logo02.png", &g_apTexResult[TITLE_LOGO]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER01.png", &g_apTexResult[TITLE_PUSH]);

	////メッシュフィールドの初期化処理
	//InitMeshfield(g_stage.nStageNum);


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{
		if (nCntTitle == TITLE_BG)
		{
			//頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			//頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		}
		else if (nCntTitle == TITLE_LOGO)
		{
			//頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

		else if (nCntTitle == TITLE_PUSH)
		{
			//頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(625, 1000, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(625, 850, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1325, 1000, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1325, 850, 0.0f);

			//頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		}

		//rhwの設定（（（（（（（2Dでしか使わない））））））
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//テクスチャー座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGM004);	//タイトル時のサウンド

	return S_OK;
}

//*****************************************************************************************************************
// タイトルの終了処理
//*****************************************************************************************************************
void UninitTitle(void)
{

	//頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//テクスチャの開放
		if (g_apTexResult[nCntTitle] != NULL)
		{
			g_apTexResult[nCntTitle]->Release();
			g_apTexResult[nCntTitle] = NULL;
		}
	}
}

//*****************************************************************************************************************
//　タイトルの更新処理
//*****************************************************************************************************************
void UpdateTitle(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//エンターキーが押された場合
	if (GetKeyboardTrigger(DIK_RETURN) == true ||
		GetKeypadTrigger(D_BUUTON_A) ||
		GetKeypadTrigger(D_BUUTON_START))
	{
		g_bEnter = true;	//エンターが押された

		StopSound();	//サウンドを止める 
		SetFade(FADE_OUT, MODE_GAME);	//ゲーム画面に飛ぶ＆フェードアウト
	}
	if (g_bEnter == true)
	{
		g_nCntEnter = 5;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{
		if (nCntTitle == TITLE_LOGO)
		{
			//頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(300.0f, 0.0f + g_TitleMove * g_CntMove, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(300.0f, -270.0f + g_TitleMove * g_CntMove, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1500.0f, 0.0f + g_TitleMove * g_CntMove, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1500.0f, -270.0f + g_TitleMove * g_CntMove, 0.0f);

			if (g_TitleMove * g_CntMove <= 530)
			{
				g_CntMove++;
			}
		}

		//プッシュエンターの点滅処理
		if (nCntTitle == TITLE_PUSH)
		{
			g_nCntPush++;

			if (g_nCntPush >= g_nCntEnter)
			{
				if (g_bPush == true)
				{
					//頂点カラー
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					g_bPush = false;
				}
				else if (g_bPush == false)
				{
					//頂点カラー
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

					g_bPush = true;
				}
				g_nCntPush = 0;

			}
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}


//*****************************************************************************************************************
// タイトルの描画処理
//*****************************************************************************************************************
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexResult[nCntTitle]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}
}
