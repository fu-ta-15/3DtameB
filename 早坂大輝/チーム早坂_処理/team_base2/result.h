//-----------------------------------------------------------------------------
//
// リザルトの処理 ヘッダー [result.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define RESULT_WAITTIME (1500)	// 遷移までの待機時間
//-----------------------------------------------------------------------------
// RESULT構造体
//-----------------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9  pVtxBuff;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 pTexture[2];			// リザルトのテクスチャへのポインタ
	D3DXVECTOR3 pos;						// 位置
	bool bGameOver;							// ゲームオーバーかクリアか
} RESULT;

//-----------------------------------------------------------------------------
//　プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
RESULT *GetResult(void);

#endif