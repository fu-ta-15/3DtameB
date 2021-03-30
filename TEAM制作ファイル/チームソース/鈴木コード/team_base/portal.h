//-----------------------------------------------------------------------------
//
// ポータル処理 ヘッダー [portal.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _PORTAL_H_
#define _PORTAL_H_
#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define PORTAL_WIDTH (30)		// portal width
#define PORTAL_HEIGHT (30)		// portal height

//-----------------------------------------------------------------------------
// ポータルの構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	bool bActive;			// 使えるか
	bool bDraw;				// 描画するか
} Portal;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitPortal(void);
void UninitPortal(void);
void UpdatePortal(void);
void DrawPortal(void);
void ActivatePortal(bool bActive, bool bDraw);
Portal GetPortal(void);


#endif