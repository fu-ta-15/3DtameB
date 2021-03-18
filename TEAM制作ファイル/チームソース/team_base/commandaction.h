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
#define CA_BUTTON_NUM (4)
#define CA_BUTTON_WIDTH (50.0f)
#define CA_BUTTON_HEIGHT (50.0f)

//-----------------------------------------------------------------------------
// ボタン構造体
//-----------------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	LPDIRECT3DTEXTURE9 pTexture[CA_BUTTON_NUM];
	D3DXVECTOR3 pos[CA_BUTTON_NUM];
} CAButton;

//-----------------------------------------------------------------------------
//プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitCommand(void);
void UninitCommand(void);
void UpdateCommand(void);
void DrawCommand(void);

#endif


