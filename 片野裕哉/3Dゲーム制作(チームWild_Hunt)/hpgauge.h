//=========================================================================================================================
//
// HPゲージ [hpgauge.h]
// Author:Hiroya Katano
//
//=========================================================================================================================
#ifndef _HPGAUGE_H_
#define _HPGAUGE_H_
#include "main.h"

//=========================================================================================================================
// マクロ定義
//=========================================================================================================================
#define MAX_TYPE_HPGAUGE (3)

#define HPGAUGE_BASE_POINT_X (800.0f)				// ゲージの中心座標のX
#define HPGAUGE_BASE_POINT_Y (110.0f)				// ゲージの中心座標のY

#define DEFAULT_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))

#define GAUGE_SIZE (50)								//ゲージの大きさの倍率(基本 0 〜 100 で大丈夫かと)

#define GAUGE_BG_X (1029.0f / 100 * GAUGE_SIZE)
#define GAUGE_BG_Y (48.0f / 100 * GAUGE_SIZE)
#define GAUGE_X (1023.0f / 100 * GAUGE_SIZE)
#define GAUGE_Y (53.0f / 100 * GAUGE_SIZE)
#define GAUGE_FRAME_X (1080.0f / 100 * GAUGE_SIZE)
#define GAUGE_FRAME_Y (88.0f / 100 * GAUGE_SIZE)


//=========================================================================================================================
// プロトタイプ宣言
//=========================================================================================================================
HRESULT InitHPGauge(void);															// ポリゴンの初期化処理
void UninitHPGauge(void);															// ポリゴンの終了処理
void UpdateHPGauge(void);															// ポリゴンの更新処理
void DrawHPGauge(void);																// ポリゴンの描画処理
void ManageGauge(void);

#endif
