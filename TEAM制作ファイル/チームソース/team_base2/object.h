//-----------------------------------------------------------------------------
//
// �G�̏��� �w�b�_�[ [object.h]
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
// �}�N����`
//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
// �I�u�W�F�N�g�̃^�C�v
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
// �I�u�W�F�N�g�̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						// �ʒu
	D3DXVECTOR3 rot;						// ����
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	LPD3DXMESH pMesh;						// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;					// �}�e���A���ւ̃|�C���^
	DWORD nNumMat;							// �}�e���A���̐�
	LPDIRECT3DTEXTURE9 pTexture[10];		// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxWorldMin, mtxWorldMax;
	D3DXVECTOR3 vtxMin, vtxMax;
	OBJECT_TYPE Type;

	int nIdx;								// ������ID
	bool bUse;								// �g�p����
} Object;


//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
void InitObject(int nStageNum);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
Object *GetObj(void);
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, OBJECT_TYPE type);

/* �ǉ� */
void SetTextObject(int nStageNum);

#endif

