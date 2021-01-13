#include "Model.h"
#include "Input.h"
#include "Player.h"
#include "Fade.h"
#include "Xinput.h"
#include "ClearAndOver.h"
#include "ModelBillBoard.h"
#include "Sound.h"
// macro
#define STAGEMODEL_POS_1 (-500.0f)
#define STAGEMODEL_POS_2 (0.0f)
#define STAGEMODEL_POS_3 (500.0f)
#define STAGEMODEL_Y (50.0f)
#define STAGEMODEL_Z (1000.0f)
#define EARTH_POS_Z (-200.f)			// earth position
#define HIT_SUCCESS_DISTANCE (200.0f)	// “–‚½‚è”»’è hit detection

LPD3DXMESH g_pMeshModel[STAGEMODEL_NUM_ALL] = {};
LPD3DXBUFFER g_pBuffMatModel[STAGEMODEL_NUM_ALL] = {};
LPDIRECT3DTEXTURE9 g_apTextureModel[4] = { NULL };
DWORD g_nNumMatModel = 0;
D3DXMATRIX g_mtxWorldModel;
MODEL *pModel;
int nCntTimeCreate;
void InitModel(void)
{
	nCntTimeCreate = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pModel = (MODEL*)malloc(STAGEMODEL_NUM_ALL * sizeof(MODEL));

	for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_RED; nCntModel++)
	{
		D3DXLoadMeshFromX("data/Model/meteorite000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel[nCntModel], NULL, &g_nNumMatModel, &g_pMeshModel[nCntModel]);

		pModel[nCntModel].pos = D3DXVECTOR3(STAGEMODEL_POS_1, STAGEMODEL_Y, STAGEMODEL_Z);
		pModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel[nCntModel].modelType = MODELTYPE_RED;
		pModel[nCntModel].fMoveSpeed = 0.f;
		pModel[nCntModel].bUse = false;

	}
	for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_BLUE; nCntModel++)
	{
		D3DXLoadMeshFromX("data/Model/meteorite001.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel[nCntModel + 50], NULL, &g_nNumMatModel, &g_pMeshModel[nCntModel + 50]);

		pModel[nCntModel + 50].pos = D3DXVECTOR3(STAGEMODEL_POS_2, STAGEMODEL_Y, STAGEMODEL_Z);
		pModel[nCntModel + 50].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel[nCntModel + 50].modelType = MODELTYPE_BLUE;
		pModel[nCntModel + 50].fMoveSpeed = 0.f;
		pModel[nCntModel + 50].bUse = false;
	}
	for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_YELLOW; nCntModel++)
	{
		D3DXLoadMeshFromX("data/Model/meteorite002.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel[nCntModel + 100], NULL, &g_nNumMatModel, &g_pMeshModel[nCntModel + 100]);

		pModel[nCntModel + 100].pos = D3DXVECTOR3(STAGEMODEL_POS_3, STAGEMODEL_Y, STAGEMODEL_Z);
		pModel[nCntModel + 100].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel[nCntModel + 100].modelType = MODELTYPE_YELLOW;
		pModel[nCntModel + 100].fMoveSpeed = 0.0f;
		pModel[nCntModel + 100].bUse = false;
	}
	for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_GREEN; nCntModel++)
	{
		D3DXLoadMeshFromX("data/Model/meteorite003.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel[nCntModel + 150], NULL, &g_nNumMatModel, &g_pMeshModel[nCntModel + 150]);

		pModel[nCntModel + 150].pos = D3DXVECTOR3(0.0f, STAGEMODEL_Y, STAGEMODEL_Z);
		pModel[nCntModel + 150].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel[nCntModel + 150].modelType = MODELTYPE_GREEN;
		pModel[nCntModel + 150].fMoveSpeed = 0.0f;
		pModel[nCntModel + 150].bUse = false;
	}

}

void UninitModel(void)
{
	for (int nCnt = 0; nCnt < STAGEMODEL_NUM_ALL; nCnt++)
	{
		if (g_pMeshModel[nCnt] != NULL)
			g_pMeshModel[nCnt] = NULL;
		if (g_pBuffMatModel[nCnt] != NULL)
			g_pBuffMatModel[nCnt] = NULL;
	}
}

void UpdateModel(void)
{
	nCntTimeCreate++;
	GAMEPAD *pPad = GetGamePad();
	Player *pPlayer = GetPlayer();

	if (nCntTimeCreate % 50 == 0)
	{
		nCntTimeCreate = 0;
		int nCntColor = rand() % 4;
		int nCntPos = rand() % 3;
		//int nCntRotx = rand() % 628 + 1;
		//int nCntRoty = rand() % 628 + 1;
		//int nCntRotz = rand() % 628 + 1;
		switch (nCntColor)
		{
		case 0:
			for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_RED; nCntModel++)
			{
				if (pModel[nCntModel].bUse == false)
				{
					pModel[nCntModel].bUse = true;
					switch (nCntPos)
					{
					case 0:
						pModel[nCntModel].pos = D3DXVECTOR3(STAGEMODEL_POS_1, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					case 1:
						pModel[nCntModel].pos = D3DXVECTOR3(STAGEMODEL_POS_2, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					case 2:
						pModel[nCntModel].pos = D3DXVECTOR3(STAGEMODEL_POS_3, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					}
					break;
				}
			}
			break;
		case 1:
			for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_BLUE; nCntModel++)
			{
				if (pModel[nCntModel + 50].bUse == false)
				{
					pModel[nCntModel + 50].bUse = true;
					switch (nCntPos)
					{
					case 0:
						pModel[nCntModel + 50].pos = D3DXVECTOR3(STAGEMODEL_POS_1, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel + 50].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					case 1:
						pModel[nCntModel + 50].pos = D3DXVECTOR3(STAGEMODEL_POS_2, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel + 50].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					case 2:
						pModel[nCntModel + 50].pos = D3DXVECTOR3(STAGEMODEL_POS_3, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel + 50].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					}
					break;
				}
			}
			break;
		case 2:
			for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_YELLOW; nCntModel++)
			{
				if (pModel[nCntModel + 100].bUse == false)
				{
					pModel[nCntModel + 100].bUse = true;
					switch (nCntPos)
					{
					case 0:
						pModel[nCntModel + 100].pos = D3DXVECTOR3(STAGEMODEL_POS_1, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel + 100].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					case 1:
						pModel[nCntModel + 100].pos = D3DXVECTOR3(STAGEMODEL_POS_2, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel + 100].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					case 2:
						pModel[nCntModel + 100].pos = D3DXVECTOR3(STAGEMODEL_POS_3, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel + 100].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					}
					break;
				}
			} 
			break;
		case 3:
			for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_GREEN; nCntModel++)
			{
				if (pModel[nCntModel + 150].bUse == false)
				{
					pModel[nCntModel + 150].bUse = true;
					switch (nCntPos)
					{
					case 0:
						pModel[nCntModel + 150].pos = D3DXVECTOR3(STAGEMODEL_POS_1, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel + 150].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					case 1:
						pModel[nCntModel + 150].pos = D3DXVECTOR3(STAGEMODEL_POS_2, STAGEMODEL_Y, STAGEMODEL_Z);
						//[nCntModel + 150].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					case 2:
						pModel[nCntModel + 150].pos = D3DXVECTOR3(STAGEMODEL_POS_3, STAGEMODEL_Y, STAGEMODEL_Z);
						//pModel[nCntModel + 150].rot = D3DXVECTOR3(nCntRotx / 100.0f, nCntRoty / 100.0f, nCntRotz / 100.0f);
						break;
					}
					break;
				}
			}
			break;
		}
	}

	for (int nCntModel = 0; nCntModel < STAGEMODEL_NUM_ALL; nCntModel++)
	{
		if (pModel[nCntModel].bUse == true)
		{
			D3DXVECTOR3 Dest;
			Dest.x = sinf(atan2f(0.0f - pModel[nCntModel].pos.x, EARTH_POS_Z - pModel[nCntModel].pos.z));
			Dest.z = cosf(atan2f(0.0f - pModel[nCntModel].pos.x, EARTH_POS_Z - pModel[nCntModel].pos.z));

			//ˆÚ“®—Ê’Ç‰Á
			pModel[nCntModel].pos += D3DXVECTOR3(Dest.x, 0.0f, Dest.z) * 2;
			
			// player destroys a meteorite
			if (GetkeyboardTrigger(DIK_A) == true || pPad->bB == true)
			{
				// if meteorite is within reach
				if (pModel[nCntModel].pos.z <= HIT_SUCCESS_DISTANCE)
				{			
					// if meteorite type is matched
					if (pModel[nCntModel].modelType == MODELTYPE_RED)
					{
						// score increase
						pPlayer->nScore += 400;
						PlaySound(SOUND_LABEL_SE_BREAK);
						// delete meteorite
						pModel[nCntModel].bUse = false;

						// destroy motion
						pPlayer->bMotionStart = true;

						break;
					}
					else
					{
						// score decrease
						pPlayer->nScore -= 200;
					}
				}
			}
			else if (GetkeyboardTrigger(DIK_S) == true || pPad->bX == true)
			{
				// if meteorite is within reach
				if (pModel[nCntModel].pos.z <= HIT_SUCCESS_DISTANCE)
				{					
					// if meteorite type is matched
					if (pModel[nCntModel].modelType == MODELTYPE_BLUE)
					{
						// score increase
						pPlayer->nScore += 300;
						PlaySound(SOUND_LABEL_SE_BREAK);
						// delete meteorite
						pModel[nCntModel].bUse = false;

						// destroy motion
						pPlayer->bMotionStart = true;
						
						break;
					}
					else
					{
						// score decrease
						pPlayer->nScore -= 150;

						
					}
				}
			}
			else if (GetkeyboardTrigger(DIK_D) == true || pPad->bY == true)
			{
				// if meteorite is within reach
				if (pModel[nCntModel].pos.z <= HIT_SUCCESS_DISTANCE)
				{
	
					// if meteorite type is matched
					if (pModel[nCntModel].modelType == MODELTYPE_YELLOW)
					{
						// score increase
						pPlayer->nScore += 200;
						PlaySound(SOUND_LABEL_SE_BREAK);
						// delete meteorite
						pModel[nCntModel].bUse = false;

						// destroy motion
						pPlayer->bMotionStart = true;
						break;
					}
					else
					{
						// score decrease
						pPlayer->nScore -= 100;

						
					}
				}
			}
			else if (GetkeyboardTrigger(DIK_F) == true || pPad->bA == true)
			{
				// if meteorite is within reach
				if (pModel[nCntModel].pos.z <= HIT_SUCCESS_DISTANCE)
				{
					// if meteorite type is matched
					if (pModel[nCntModel].modelType == MODELTYPE_GREEN)
					{
						// score increase
						pPlayer->nScore += 100;
						PlaySound(SOUND_LABEL_SE_BREAK);
						// delete meteorite
						pModel[nCntModel].bUse = false;

						// destroy motion
						pPlayer->bMotionStart = true;
						break;
					}
					else
					{
						// score decrease
						pPlayer->nScore -= 50;

				
					}
				}
			}
			// meteorite hits the player
			if (pModel[nCntModel].pos.z < -10.0f)
			{
				// play beep sound
				PlaySound(SOUND_LABEL_SE_DAMAGE);

				// damage to player
				if (pPlayer->nHp > 0)
				{
					if (pPlayer->bHit == false)
					{
						pPlayer->bHit = true;
						pPlayer->nHp--;
					}
				}
				else
				{
					OAC *pOAC = GetOAC();
					pOAC[0].bUse = true;
					SetFade(FADE_OUT, MODE_OAC);
				}
				// bUse false
				pModel[nCntModel].bUse = false;
				pModel[nCntModel].pos = D3DXVECTOR3(0.0f, STAGEMODEL_Y, STAGEMODEL_Z);
			}
		}
	}
	if (pPad->bY == true) pPad->bY = false;
	if (pPad->bX == true) pPad->bX = false;
	if (pPad->bA == true) pPad->bA = false;
	if (pPad->bB == true) pPad->bB = false;
	if (pPad->bStart == true) pPad->bStart = false;
}

void DrawModel(void)
{
	for (int nCnt = 0; nCnt < STAGEMODEL_NUM_ALL; nCnt++)
	{
		if (pModel[nCnt].bUse == true)
		{
			LPDIRECT3DDEVICE9 pDevice = GetDevice();
			D3DXMATRIX mtxRot, mtxTrans;
			D3DMATERIAL9 matDef;
			D3DXMATERIAL *pMat;
			D3DXMatrixIdentity(&g_mtxWorldModel);
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pModel[nCnt].rot.y, pModel[nCnt].rot.x, pModel[nCnt].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);
			D3DXMatrixTranslation(&mtxTrans, pModel[nCnt].pos.x, pModel[nCnt].pos.y, pModel[nCnt].pos.z); //¢ŠEmatrix‘S‘Ì@ˆÚ“®‚µ‚½‚¢‹——£‚Æ‚¢‚¤matrix‚Ì‡ŽZ
			D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans); //¢ŠEmatrix‚ÌˆÚ“®
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel); //set the world into Map
			pDevice->GetMaterial(&matDef);
			pMat = (D3DXMATERIAL*)g_pBuffMatModel[nCnt]->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
			{
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				pDevice->SetTexture(0, NULL);
				g_pMeshModel[nCnt]->DrawSubset(nCntMat);
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

MODEL *GetModel(void)
{
	return &pModel[0];
}