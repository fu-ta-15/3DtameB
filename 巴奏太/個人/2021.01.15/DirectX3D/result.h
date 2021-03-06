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
// RESULT構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
} RESULT;

//-----------------------------------------------------------------------------
//　プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

#endif