//===================================================================
//
// プレイヤーの処理　[player.h]
// Author: fukuyama syuya
//
//===================================================================

#ifndef PLAYER_H_
#define PLAYER_H_

#include "main.h"

//===========================================================================================================
// マクロ定義
//===========================================================================================================
#define MAX_MODEL (15)					//モデルの最大数

//===================================================================
//モデルの構造体
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;									//モデルの位置
	D3DXVECTOR3 posDest;								//目的のモデルの位置
	D3DXVECTOR3 rot;									//モデルの向き
	D3DXVECTOR3 rotDest;								//目的のモデルの向き
	D3DXMATRIX mtxWorld;							//ワールドマトリックス
	LPD3DXMESH pMeshModel = NULL;						//メッシュへのポインタ
	LPD3DXBUFFER pBuffMatModel = NULL;					//マテリアルへのポインタ
	DWORD nNumMatModel = 1;								//マテリアルの数
	D3DXVECTOR3 VtxMinModel, g_VtxMaxModel;				//モデルの最小値・最大値
	LPDIRECT3DTEXTURE9 apTextureModel[256] = {};		//テクスチャへのポインタ
	int nIdxModelParent;								//親のインデックス
}Model;

//===================================================================
//プレイヤーの構造体
//===================================================================
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 posDest;				//目的のモデルの位置
	D3DXVECTOR3 rot;					//向き
	D3DXVECTOR3 rotDest;				//目的のモデルの向き
	D3DXMATRIX mtxWorld;				//ワールドマトリックス
	Model aModel[MAX_MODEL];			//モデル(パーツ)
	int nNumModel;						//パーツ数
}PLAYER;

typedef enum
{
	MODEL_LABEL_BODY = 0,	// 胴体
	MODEL_LABEL_HEAD,		// 頭部
	MODEL_LABEL_ARM_T_R,	// 右腕(肩～肘)
	MODEL_LABEL_ARM_U_R,	// 右腕(肘～手首)
	MODEL_LABEL_HAND_R,		// 右手
	MODEL_LABEL_ARM_T_L,	// 左腕(肩～肘)
	MODEL_LABEL_ARM_U_L,	// 左腕(肘～手首)
	MODEL_LABEL_HAND_L,		// 左手
	MODEL_LABEL_LEG_T_R,	// 右脚(腿)
	MODEL_LABEL_LEG_U_R,	// 右脚(脹脛)
	MODEL_LABEL_FOOT_R,		// 右足
	MODEL_LABEL_LEG_T_L,	// 左脚(腿)
	MODEL_LABEL_LEG_U_L,	// 左脚(脹脛)
	MODEL_LABEL_FOOT_L,		// 左足
	MODEL_LABEL_BODYSEC,	// 腰 
	MODEL_LABEL_MAX,
} MODEL_LABEL;

//===========================================================================================================
// プロトタイプ宣言
//===========================================================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

#endif

