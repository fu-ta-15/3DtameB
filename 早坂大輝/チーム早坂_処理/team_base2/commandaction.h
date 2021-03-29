//-----------------------------------------------------------------------------
//
// コマンドアクション ヘッダー [commandaction.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _COMMANDACTION_H_
#define _COMMANDACTION_H_
#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define CA_BUTTON_NUM_KATANA (4)
#define CA_BUTTON_NUM_NAGINATA (5)
#define CA_BUTTON_NUM (5)
#define CA_BUTTON_TYPE (4)
#define CA_BUTTON_WIDTH (50.0f)
#define CA_BUTTON_HEIGHT (50.0f)
#define CA_BUTTON_SPACE (75.0f)
#define CA_BUTTON_POS_X (SCREEN_WIDTH / 2)
#define CA_BUTTON_POS_Y (SCREEN_WIDTH / 2)
#define CA_ATTACK_RADIUS (500.0f)
#define CA_ATTACK_KNOCKBACK (50.0f)

//-----------------------------------------------------------------------------
// ボタン構造体
//-----------------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;				// 頂点バッファ
	LPDIRECT3DTEXTURE9 pTexture[CA_BUTTON_TYPE];	// テクスチャ
	D3DXVECTOR3 pos[CA_BUTTON_NUM];					// 位置
} CAButton;

//-----------------------------------------------------------------------------
// コマンドアクション構造体
//-----------------------------------------------------------------------------
typedef struct
{
	CAButton buttonInfo;				// ボタンの情報
	int nActionOrder[CA_BUTTON_NUM];	// ボタンを押す順番
	int nActionOrderOut[CA_BUTTON_NUM];	// 実際に押された順番
	int nActionNum;						// ボタンを押す数
	int nActionNumCorrect;				// 押したボタンが正解した数
	int nActionCounter;					// カウンター
	bool bPress;						// 入力のフラグ管理
	bool bActive;						// アクティブかどうか
	int nTest;
} CommandAction;

//-----------------------------------------------------------------------------
//プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitCommand(void);
void UninitCommand(void);
void UpdateCommand(void);
void DrawCommand(void);
CommandAction *GetCAction(void);

#endif


