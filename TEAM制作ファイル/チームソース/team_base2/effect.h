//##################################################################################################################################################################//
//
// �G�t�F�N�g�w�b�_�t�@�C�� [effect.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//=====================================================================================================================================================================//
// �}�N����`
//=====================================================================================================================================================================//

typedef enum
{
	EFFECT_TYPE_NORMAL = 0,
	EFFECT_TYPE_PORTAL,
	EFFECT_TYPE_NOT,

	EFFECT_TYPE_MAX
}EFFECT_TYPE;


//=====================================================================================================================================================================//
// �e�̍\����
//=====================================================================================================================================================================//
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 posdest;			// �ʒu
	D3DXVECTOR3 rot;
	D3DXVECTOR3 oldpos;				// �ߋ��̈ʒu
	D3DXVECTOR3 move;				// �ړ���
	D3DXCOLOR color;				// �F
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	EFFECT_TYPE type;
	float EffectSizeW;				// �e�̃T�C�Y
	float EffectSizeH;				// �e�̃T�C�Y
	float fRadius;					// ���a
	float fAngle;					// �p�x
	int nLife;						// ����
	int nCnt;
	int nFrame;
	int nIdx;						// ���o����
	bool bUse;						// �g�p���Ă��邩�ǂ���
}Effect;

//=====================================================================================================================================================================//
//�v���g�^�C�v�錾
//=====================================================================================================================================================================//
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void EffectOn(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float movex, float movez,float movey,int nIdx,int nLife);

void EffectPortalOn(void);
void SetEffectPortal(D3DXVECTOR3 pos,D3DXVECTOR3 posDest, D3DXCOLOR col, D3DXVECTOR3 move, D3DXVECTOR3 posdicetance, int nIdx, int nLife, int nFrame);

Effect *GetEffect(void);
#endif 

