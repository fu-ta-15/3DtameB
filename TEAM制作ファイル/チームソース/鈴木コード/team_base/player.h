//-----------------------------------------------------------------------------
//
// プレイヤーの処理 ヘッダー [player.h]
// Author: Souta Tomoe
//
//-----------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "motion.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define PLAYER_MOVESPEED (0.5f)													// プレイヤーの移動速度
#define PLAYER_MODEL_AMOUNT (11)
#define PLAYER_ATTACK_RADIUS (12.0f)											// プレイヤーの攻撃範囲
#define PlAYER_WIDTH (7.5f)
#define PLAYER_HEIGHT (50.0f)
#define PLAYER_INVINCIBLE_TIME (500)	// 攻撃された時の無敵時間
#define PLAYER_HEALTH (10)				// プレイヤーの体力

#define PLAYER_WEAPON_TYPE (2)			// プレイヤーの武器の種類
#define PLAYER_WEAPON_COLLISION_COMPONENTS (3)

//-----------------------------------------------------------------------------
// プレイヤーが持っている武器
//-----------------------------------------------------------------------------
typedef enum
{
	PWEAPON_KATANA,		// 刀
	PWEAPON_NAGINATA,	// 薙刀
	PWEAPON_MAX
} PWEAPON;

//-----------------------------------------------------------------------------
// ファイルから読んでくるキャラクターのモデル情報の構造体
//-----------------------------------------------------------------------------
typedef struct
{
	int nModelNum;						// モデルの数	
	int nModelIdx[20];					// モデルの番号
	int nModelParent[20];				// モデルの親
	char cModelFileName[20][256];		// モデルのファイル名
	float fModelPos[20][3];				// モデルの位置(オフセット)
	float fModelRot[20][3];				// モデルの向き

} CharacterPartsInfo;

//-----------------------------------------------------------------------------
// モデルの構造体
//-----------------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH pMeshModel;				// メッシュへのポインタ
	LPD3DXBUFFER pBuffMatModel;			// マテリアルへのポインタ
	DWORD nNumMatModel;					// マテリアルの数
	D3DXVECTOR3 pos;					// 位置(オフセット)
	D3DXVECTOR3 rot;					// 向き
	D3DXMATRIX mtxWorld;				// ワールドマトリックス
	int nIdxModelParent;				// 親モデルのインデックス
	LPDIRECT3DTEXTURE9 pTexture[10];	// texture
	int nNumModel;
} Model;

//-----------------------------------------------------------------------------
// プレイヤーの構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						// 位置
	D3DXVECTOR3 posOld;						// 前回の位置
	D3DXVECTOR3 move;						// 移動値
	D3DXVECTOR3 rot;						// 向き
	D3DXVECTOR3 rotDest;					// 目標の向き
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	Model aModel[PLAYER_MODEL_AMOUNT];		// モデル(パーツ)
	Model AltWeapon;						// 武器（パーツ）
	int nNumModel;							// モデル(パーツ)数

	bool bPlayMotion;						// モーション再生状態
	MOTION_INFO aMotionInfo[MOTION_MAX];	// モーション情報	 (モーションの最大数)
	MOTIONTYPE motionType;					// モーションタイプ
	bool bLoopMotion;						// ループの有無
	int nCurrentMotion;						// 現在のモーション
	int nNumMotion;							// モーション数
	int nNumKey;							// キー数
	int nKey;								// キーナンバー
	int nCounterMotion;						// モーションカウンター

	bool bBlendMotion;						// ブレンドするかどうか
	MOTIONTYPE motionTypeBlend;				// 次のモーション情報
	bool bLoopMotionBlend;					// 
	int nNumKeyBlend;						//
	int nKeyBlend;							//
	int nCounterMotionBlend;				//
	int nCounterBlend;
	int nFrameBlend;

	PWEAPON weapon;					// 現在持っている武器
	D3DXMATRIX mtxWeaponCol[PLAYER_WEAPON_COLLISION_COMPONENTS];	// 
	D3DXVECTOR3 posWeaponCol[PLAYER_WEAPON_COLLISION_COMPONENTS];	// 

	int nLifeMax;					// 最大体力
	int nLife;						// 体力
	bool bHit;						// 攻撃されている状態
	bool bInvincible;				// 無敵状態
	DWORD dwTime;					// 時間計算用
} Player;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
KEY *GetDefKey(void);
void ReadCharacterInfo(CharacterPartsInfo *characterInfo, char* fileName);
#endif