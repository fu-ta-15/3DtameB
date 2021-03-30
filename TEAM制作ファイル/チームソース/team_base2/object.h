//-----------------------------------------------------------------------------
//
// 敵の処理 ヘッダー [object.h]
// Author: Suzuki Fuut
//
//-----------------------------------------------------------------------------
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "game.h"
#include "player.h"
#include <time.h>

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
// オブジェクトのタイプ
//-----------------------------------------------------------------------------
typedef enum
{
	OBJECT_TYPE_NULL = 0,
	OBJECT_TYPE_1,
	OBJECT_TYPE_2,
	OBJECT_TYPE_3,
	OBJECT_TYPE_4,
	OBJECT_TYPE_5,
	OBJECT_TYPE_6,
	OBJECT_TYPE_MAX
}OBJECT_TYPE;





//-----------------------------------------------------------------------------
// オブジェクトの構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						// 位置
	D3DXVECTOR3 rot;						// 向き
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	LPD3DXMESH pMesh;						// メッシュへのポインタ
	LPD3DXBUFFER pBuffMat;					// マテリアルへのポインタ
	DWORD nNumMat;							// マテリアルの数
	LPDIRECT3DTEXTURE9 pTexture[10];		// テクスチャへのポインタ
	D3DXMATRIX mtxWorldMin, mtxWorldMax;
	D3DXVECTOR3 vtxMin, vtxMax;
	OBJECT_TYPE Type;

	int nIdx;								// 自分のID
	bool bUse;								// 使用中か
} Object;


//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitObject(int nStageNum);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
Object *GetObj(void);
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, OBJECT_TYPE type);

/* 追加 */
void SetTextObject(int nStageNum);

#endif

