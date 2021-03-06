//
//
// プレイヤーヘッダー [player.h]
//
//
//
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//
// マクロ定義
//
#define MAX_MODEL (14)		// モデル(パーツ)の最大数(総数)

//
// 構造体
//
//モーションの種類
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,		// ニュートラルモーション
	MOTIOBTYPE_MAX
}MOTIONTYPE;

// キーの構造体
typedef struct
{
	float fPosX;			// 位置X
	float fPosY;			// 位置Y
	float fPosZ;			// 位置Z
	float fRotX;			// 向きX
	float fRotY;			// 向きY
	float fRotZ;			// 向きZ
}KEY;

// キー情報の構造体
typedef struct
{
	int nFlame;				// 再生フレーム
	KEY aKey[MAX_MODEL];	// 各モデルのキー要素
}KEY_INFO;

// モーション情報の構造体
typedef struct
{
	bool bLoop;				// ループするかどうか
	int nNumKey;			// キーの総数
	KEY_INFO aKeyInfo[4];	// キー情報
}MOTION_INFO;

typedef struct
{
	LPD3DXMESH pMeshModel = NULL;		// メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMatModel = NULL;	// マテリアル(材質情報)へのポインタ
	DWORD nNumMatModel = NULL;			// マテリアルの数
	D3DXVECTOR3 pos;					// 位置
	D3DXVECTOR3 move;					// 移動量
	D3DXVECTOR3 rot;					// 向き
	D3DXVECTOR3 rotDest;				// 目的の向き
	D3DXMATRIX mtxWorld;				// ワールドマトリックス
	int nIdxModelParent;				// 親のインデックス
	D3DXVECTOR3 vtxMinModel;			// モデルの最小値
	D3DXVECTOR3 vtxMaxModel;			// モデルの最大値

} MODEL;

typedef struct
{
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動量
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 rotDest;		// 目的の向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	MODEL aModel[MAX_MODEL];	// モデル(パーツ)
	int nNumModel;				// モデル(パーツ)の数

	MOTION_INFO aMotionInfo[1];	// モーション情報
	int nNumMotion;				// モーション数
	MOTIONTYPE motionType;		// モーションタイプ
	bool bLoopMotion;			// ループするかどうか
	int nNumKey;				// キー数
	int nKey;					// キーNo.
	int nCounterMotion;			// モーションカウンター
} PLAYER;

typedef enum
{
	MODEL_LABEL_BODY = 0,	// 胴体
	MODEL_LABEL_HEAD,		// 頭部
	MODEL_LABEL_ARM_T_R,	// 右腕(肩〜肘)
	MODEL_LABEL_ARM_U_R,	// 右腕(肘〜手首)
	MODEL_LABEL_HAND_R,		// 右手
	MODEL_LABEL_ARM_T_L,	// 左腕(肩〜肘)
	MODEL_LABEL_ARM_U_L,	// 左腕(肘〜手首)
	MODEL_LABEL_HAND_L,		// 左手
	MODEL_LABEL_LEG_T_R,	// 右脚(腿)
	MODEL_LABEL_LEG_U_R,	// 右脚(脹脛)
	MODEL_LABEL_FOOT_R,		// 右足
	MODEL_LABEL_LEG_T_L,	// 左脚(腿)
	MODEL_LABEL_LEG_U_L,	// 左脚(脹脛)
	MODEL_LABEL_FOOT_L,		// 左足
	MODEL_LABEL_MAX,
} MODEL_LABEL;

//
// プロトタイプ宣言
//
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

#endif