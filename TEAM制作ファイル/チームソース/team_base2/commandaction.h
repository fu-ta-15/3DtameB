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

#define CA_ATTACK_RADIUS (150.0f)
#define CA_ATTACK_KNOCKBACK_KATANA (10.0f)
#define CA_ATTACK_KNOCKBACK_NAGINATA (20.0f)
#define CA_ATTACK_DAMAGE (3)

#define CA_TIMEREMAIN_OBJ (2)			// 残り時間で使うオブジェクト数
#define CA_TIMEREMAIN_WIDTH (600)		// 残り時間のバー幅
#define CA_TIMEREMAIN_HEIGHT (15)		// 残り時間のバー高さ
#define CA_TIMEREMAIN_TIMELIMIT (3000)	// 入力の制限時間(ミリ秒)

#define CA_USEPOWER_MAX (2)
#define CA_CIRCLE_RADIUS (150.0f)	// circle radius

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
// 残り時間バーの構造体
//-----------------------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff[CA_TIMEREMAIN_OBJ];	// 頂点バッファ
	LPDIRECT3DTEXTURE9 pTexture[CA_TIMEREMAIN_OBJ];			// テクスチャ
	D3DXVECTOR3 pos[CA_TIMEREMAIN_OBJ];						// 位置
	DWORD dwStartTime;										// 開始時間
	DWORD dwCurrentTime;									// 現在時間
	DWORD dwRemainTime;										// 残り時間
} TimeRemain;

//-----------------------------------------------------------------------------
// 範囲サークルの構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXMATRIX	mtxWorld;				// worldmtx
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	// 頂点バッファ
	LPDIRECT3DTEXTURE9 pTexture;		// テクスチャ
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 rot;					// rot
} ActionCircle;

//-----------------------------------------------------------------------------
// コマンドアクション構造体
//-----------------------------------------------------------------------------
typedef struct
{
	CAButton buttonInfo;				// ボタンの情報
	TimeRemain remainTimeInfo;			// 残り時間の情報
	ActionCircle actionCircle;			// 範囲サークルの情報
	int nActionOrder[CA_BUTTON_NUM];	// ボタンを押す順番
	int nActionOrderOut[CA_BUTTON_NUM];	// 実際に押された順番
	int nActionNum;						// ボタンを押す数
	int nActionNumCorrect;				// 押したボタンが正解した数
	int nActionCounter;					// カウンター
	bool bPress;						// 入力のフラグ管理
	bool bActive;						// アクティブかどうか
	bool bUsable;
	int nUsePower;
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


