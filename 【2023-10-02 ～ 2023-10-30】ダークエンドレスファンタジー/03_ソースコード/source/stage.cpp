//************************************************
//
//�X�e�[�W�I�u�W�F�N�g����(�r��n)[stege.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "stage.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Stage[AMOUNT_TEX_STAGE] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Stage = NULL;	//���_�o�b�t�@�̃|�C���^
STAGE g_aStage[AMOUNT_POLYGON_STAGE];	//�X�e�[�W�\����
double g_aFileData_Satge_Object[AMOUNT_POLYGON_STAGE][AMOUNT_POLYGON_STAGE] = {};	//�O���̏����i�[
double g_aInfo_Satge_Object[AMOUNT_POLYGON_STAGE][AMOUNT_POLYGON_STAGE] = {};	//�I�u�W�F�N�g�̏����i�[
double g_aPosInfo_Satge_Object[AMOUNT_POLYGON_STAGE][AMOUNT_POLYGON_STAGE] = {};	//�ʒu�̏����i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Stage()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_STAGE_OBJECT_BLOCK,
		&g_pTexture_Stage[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_STAGE_OBJECT_LEFT,
		&g_pTexture_Stage[1]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_STAGE_OBJECT_RIGHT,
		&g_pTexture_Stage[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_STAGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Stage,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Stage;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Stage->Lock(0, 0, (void**)&pVtx_Stage, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Stage[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Stage[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Stage[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Stage[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Stage[0].rhw = 1.0f;
		pVtx_Stage[1].rhw = 1.0f;
		pVtx_Stage[2].rhw = 1.0f;
		pVtx_Stage[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Stage[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Stage[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Stage[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Stage[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Stage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Stage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Stage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Stage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Stage += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Stage->Unlock();

	//�X�e�[�W�\���̂̏��̏������Q
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		g_aStage[nCnt].nStyle = STAGE_OBJECT_STYLE_NONE;
		g_aStage[nCnt].bUse = false;
		g_aStage[nCnt].pos = D3DXVECTOR3(0.0f, -1000.0f, 0.0f);
		g_aStage[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aStage[nCnt].fRadius[nCnt2] = 0.0f;
			g_aStage[nCnt].fLength[nCnt2] = 0.0f;
			g_aStage[nCnt].fAngle[nCnt2] = 0.0f;
		}
	}

	//�I�u�W�F�N�g���i�[�p������
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_STAGE; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_STAGE)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aInfo_Satge_Object[nCnt1][nCnt2] = {};
	}

	//�ʒu���i�[�p������
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_STAGE; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_STAGE)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aPosInfo_Satge_Object[nCnt1][nCnt2] = {};
	}

	/*�v�C��*/
	////�X�e�[�W�\���̗p�̏����擾
	//ReadInfo_Stage();

	////�X�e�[�W�\���̗p�̈ʒu���擾
	//ReadPosInfo_Stage();

	//�ǂݎ���������X�e�[�W�\���̓��ɑ��(��)
	ReadInfo_Stage_Old();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Stage(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEX_STAGE; nCnt++)
	{
		if (g_pTexture_Stage[nCnt] != NULL)
		{
			g_pTexture_Stage[nCnt]->Release();
			g_pTexture_Stage[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Stage != NULL)
	{
		g_pVtxBuff_Stage->Release();
		g_pVtxBuff_Stage = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Stage(void)
{
	//�X�e�[�W�I�u�W�F�N�g��W�J
	Update_Pos_Stage();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Stage(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Stage, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		switch (g_aStage[nCnt].nStyle)
		{
		case STAGE_OBJECT_STYLE_BLOCK:
			pDevice->SetTexture(0, g_pTexture_Stage[0]);
			break;
		case STAGE_OBJECT_STYLE_LEFT:
			pDevice->SetTexture(0, g_pTexture_Stage[1]);
			break;
		case STAGE_OBJECT_STYLE_RIGHT:
			pDevice->SetTexture(0, g_pTexture_Stage[2]);
			break;
		case STAGE_OBJECT_STYLE_LEFT_J:
			pDevice->SetTexture(0, g_pTexture_Stage[1]);
			break;
		case STAGE_OBJECT_STYLE_RIGHT_J:
			pDevice->SetTexture(0, g_pTexture_Stage[2]);
			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�X�e�[�W�\���̂̏���ݒ肷��֐�(��)
//************************************************
void ReadInfo_Stage_Old(void)
{
	//�f�[�^�𕪕ʂ���p
	int nLine = 0, nRow = 0, nMaxLine = 0;

	//�t�@�C���|�C���^��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(DATA_STAGE_OBJECT_OLD, "r");

	//�t�@�C���̃w�b�_�[������؂�̂āA�f�[�^�����񂠂�̂��J�E���g
	while (fgetc(pFile) != '\n');

	//�t�@�C�����J����
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_Satge_Object[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= 17)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//�ǂݎ�����f�[�^����
	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		g_aStage[nCnt].nStyle = (int)g_aFileData_Satge_Object[0][nCnt];
		g_aStage[nCnt].pos.x = (float)g_aFileData_Satge_Object[1][nCnt];
		g_aStage[nCnt].pos.y = (float)g_aFileData_Satge_Object[2][nCnt];
		g_aStage[nCnt].move.x = (float)g_aFileData_Satge_Object[3][nCnt];
		g_aStage[nCnt].move.y = (float)g_aFileData_Satge_Object[4][nCnt];
		g_aStage[nCnt].move.z = (float)g_aFileData_Satge_Object[5][nCnt];
		g_aStage[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, (float)g_aFileData_Satge_Object[6][nCnt]);
		g_aStage[nCnt].col = D3DXCOLOR((float)g_aFileData_Satge_Object[7][nCnt],
			(float)g_aFileData_Satge_Object[8][nCnt],
			(float)g_aFileData_Satge_Object[9][nCnt],
			(float)g_aFileData_Satge_Object[10][nCnt]);
		/*�v�C���]�[��*/
		g_aStage[nCnt].fRadius[0] = (float)g_aFileData_Satge_Object[11][nCnt];	//������
		g_aStage[nCnt].fRadius[1] = (float)g_aFileData_Satge_Object[12][nCnt];	//�c����
		g_aStage[nCnt].fLength[0] = (float)g_aFileData_Satge_Object[13][nCnt];
		g_aStage[nCnt].fLength[1] = (float)g_aFileData_Satge_Object[14][nCnt];
		g_aStage[nCnt].fAngle[0] = (float)g_aFileData_Satge_Object[15][nCnt];
		g_aStage[nCnt].fAngle[1] = (float)g_aFileData_Satge_Object[16][nCnt];
	}
}

//************************************************
//�X�e�[�W�\���̂̏���ǂݎ��֐�
//************************************************
void ReadInfo_Stage(void)
{
	//�f�[�^�𕪕ʂ���p
	int nLine = 0, nRow = STAGE_OBJECT_STYLE_BLOCK;

	//�t�@�C���|�C���^��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(DATA_STAGE_OBJECT, "r");

	//�t�@�C���̃w�b�_�[������؂�̂�
	while (fgetc(pFile) != '\n');

	//�t�@�C�����J����
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aInfo_Satge_Object[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= 14)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}
}

//************************************************
//�X�e�[�W�\���̂̈ʒu��ǂݎ��֐�
//************************************************
void ReadPosInfo_Stage(void)
{
	//�f�[�^�𕪕ʂ���p
	int nCnt = 0, nLine = 0, nRow = 0;

	//�t�@�C���|�C���^��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(POS_STAGE_OBJECT, "r");

	//�t�@�C�����J����
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aPosInfo_Satge_Object[nLine][nRow]) != EOF)
		{
			//��ނƈʒu���̂ݐ�s���đ��
			g_aStage[nCnt].nStyle = (int)g_aPosInfo_Satge_Object[nLine][nRow];

			if (g_aStage[nCnt].nStyle != STAGE_OBJECT_STYLE_NONE)
			{
				g_aStage[nCnt].pos.x = (nLine * 70.0f) + 1000.0f;
				g_aStage[nCnt].pos.y = (nRow * 70.0f) + 105.0f;
			}
			else
			{
				g_aStage[nCnt].pos.x = 0.0f;
				g_aStage[nCnt].pos.y = 0.0f;
			}

			nLine++;

			if (nLine >= 26)
			{
				nLine = 0;
				nRow++;
			}

			nCnt++;
		}

		fclose(pFile);
	}
}

//************************************************
//�X�e�[�W�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Stage(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		switch (g_aStage[nCnt].nStyle)
		{
		case STAGE_OBJECT_STYLE_BLOCK:
			g_aStage[nCnt].move.x = (float)g_aInfo_Satge_Object[0][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].move.y = (float)g_aInfo_Satge_Object[1][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].move.z = (float)g_aInfo_Satge_Object[2][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, (float)g_aInfo_Satge_Object[3][STAGE_OBJECT_STYLE_BLOCK]);
			g_aStage[nCnt].col = D3DXCOLOR((float)g_aInfo_Satge_Object[4][STAGE_OBJECT_STYLE_BLOCK],
				(float)g_aInfo_Satge_Object[5][STAGE_OBJECT_STYLE_BLOCK],
				(float)g_aInfo_Satge_Object[6][STAGE_OBJECT_STYLE_BLOCK],
				(float)g_aInfo_Satge_Object[7][STAGE_OBJECT_STYLE_BLOCK]);
			/*�v�C���]�[��*/
			g_aStage[nCnt].fRadius[0] = (float)g_aInfo_Satge_Object[8][STAGE_OBJECT_STYLE_BLOCK];	//������
			g_aStage[nCnt].fRadius[1] = (float)g_aInfo_Satge_Object[9][STAGE_OBJECT_STYLE_BLOCK];	//�c����
			g_aStage[nCnt].fLength[0] = (float)g_aInfo_Satge_Object[10][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].fLength[1] = (float)g_aInfo_Satge_Object[11][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].fAngle[0] = (float)g_aInfo_Satge_Object[12][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].fAngle[1] = (float)g_aInfo_Satge_Object[13][STAGE_OBJECT_STYLE_BLOCK];
			break;
		}
	}
}

//************************************************
//�X�e�[�W�I�u�W�F�N�g�̃|���S����W�J����֐�
//************************************************
void Update_Pos_Stage(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Stage;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Stage->Lock(0, 0, (void**)&pVtx_Stage, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		ConvertInfo_Screen(&g_aStage[nCnt].pos);

		pVtx_Stage[0].pos.x = g_aStage[nCnt].pos.x + sinf(g_aStage[nCnt].rot.z - (D3DX_PI - g_aStage[nCnt].fAngle[0])) * g_aStage[nCnt].fLength[0];
		pVtx_Stage[0].pos.y = g_aStage[nCnt].pos.y + cosf(g_aStage[nCnt].rot.z - (D3DX_PI - g_aStage[nCnt].fAngle[0])) * g_aStage[nCnt].fLength[0] - 5.0f;
		pVtx_Stage[1].pos.x = g_aStage[nCnt].pos.x + sinf(g_aStage[nCnt].rot.z + (D3DX_PI - g_aStage[nCnt].fAngle[0])) * g_aStage[nCnt].fLength[0];
		pVtx_Stage[1].pos.y = g_aStage[nCnt].pos.y + cosf(g_aStage[nCnt].rot.z + (D3DX_PI - g_aStage[nCnt].fAngle[0])) * g_aStage[nCnt].fLength[0] - 5.0f;
		pVtx_Stage[2].pos.x = g_aStage[nCnt].pos.x + sinf(g_aStage[nCnt].rot.z - g_aStage[nCnt].fAngle[1]) * g_aStage[nCnt].fLength[1];
		pVtx_Stage[2].pos.y = g_aStage[nCnt].pos.y + cosf(g_aStage[nCnt].rot.z - g_aStage[nCnt].fAngle[1]) * g_aStage[nCnt].fLength[1];
		pVtx_Stage[3].pos.x = g_aStage[nCnt].pos.x + sinf(g_aStage[nCnt].rot.z + g_aStage[nCnt].fAngle[1]) * g_aStage[nCnt].fLength[1];
		pVtx_Stage[3].pos.y = g_aStage[nCnt].pos.y + cosf(g_aStage[nCnt].rot.z + g_aStage[nCnt].fAngle[1]) * g_aStage[nCnt].fLength[1];

		pVtx_Stage += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Stage->Unlock();
}

//************************************************
//�����蔻��֐�
//************************************************
bool HitDetection_Stage(int nEnemy,int nType, D3DXVECTOR3* pos, D3DXVECTOR3* oldpos, D3DXVECTOR3* move, float fRadius[2])
{
	ENEMY* pEnemy = GetInfo_Enemy();
	PLAYER* pPlayer = GetInfo_Player();

	//���n�����������
	pPlayer->bLanding = false;

	//���ꉽ�H
	bool b = false;

	/*�����蔻��́A���̍��W�ōs��*/
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		//���̃I�u�W�F�N�g�̎������͈͂�
		if (pos->x - fRadius[0] < g_aStage[nCnt].pos.x + g_aStage[nCnt].fRadius[0] &&
			pos->x + fRadius[0] > g_aStage[nCnt].pos.x - g_aStage[nCnt].fRadius[0])
		{
			//���ցA������
			if (oldpos->y > g_aStage[nCnt].pos.y &&	//�ߋ��̍��W�����̃I�u�W�F�N�g���Ꮚ�ł���
				move->y < 0.0f &&	//�㏸��
				pos->y - (fRadius[1] * 2.0f) < g_aStage[nCnt].pos.y + g_aStage[nCnt].fRadius[1])	//���݂̍��W�����̃I�u�W�F�N�g��荂���ł���
			{
				//�ʒu���I�u�W�F�N�g�̉��[�ɖ߂�
				pos->y = (fRadius[1] * 2.0f) + g_aStage[nCnt].pos.y + g_aStage[nCnt].fRadius[1];
				//�v���C���[�̂Ƃ��̂ݓ��ʂȏ������{��
				if (nType == HIT_TYPE_PLAYER)
				{
					pPlayer->BGpos.y = (fRadius[1] * 2.0f) + g_aStage[nCnt].pos.y + g_aStage[nCnt].fRadius[1];
				}

				//�c�����̈ړ��ʂ𖳂���(�o�O�h�~)
				move->y = 0.0f;
			}

			//���ցA������
			if (oldpos->y < g_aStage[nCnt].pos.y &&	//�ߋ��̍��W�����̃I�u�W�F�N�g��荂���ł���
				move->y > 0.0f &&	//���~��
				pos->y > g_aStage[nCnt].pos.y - g_aStage[nCnt].fRadius[1])	//���݂̍��W�����̃I�u�W�F�N�g���Ꮚ�ł�
			{
				//�v���C���[�̂Ƃ��̂ݓ��ʂȏ������{��
				if (nType == HIT_TYPE_PLAYER)
				{
					//��e���͂�������ŗD��
					if (pPlayer->nState != PLAYER_STATE_HURT1 &&
						pPlayer->nState != PLAYER_STATE_HURT2)
					{
						//�W�����v��Ȃ璅�n��Ԃ�
						if (pPlayer->nState == PLAYER_STATE_JUMP)
						{
							pPlayer->nState = PLAYER_STATE_LAND;
							pPlayer->nCntTex = 0;
							pPlayer->nCntPattern = 0;
							pPlayer->fTexSpan[0] = 0;
							pPlayer->fTexSpan[1] = SPAN_CHANGE_TEX_LAND_PLAYER;
						}
						//���̂ɂ���Ă͗D�悳���邪�A��{���̑��͑ҋ@��Ԃ�
						else if (pPlayer->nState != PLAYER_STATE_IDLE &&
							pPlayer->nState != PLAYER_STATE_LAND &&
							pPlayer->nState != PLAYER_STATE_RUN &&
							pPlayer->nState != PLAYER_STATE_LIGHT1 &&
							pPlayer->nState != PLAYER_STATE_LIGHT2 &&
							pPlayer->nState != PLAYER_STATE_LIGHT3 &&
							pPlayer->nState != PLAYER_STATE_HEAVY1 &&
							pPlayer->nState != PLAYER_STATE_HEAVY2 &&
							pPlayer->nState != PLAYER_STATE_HEAVY3)
						{
							pPlayer->nState = PLAYER_STATE_IDLE;
							pPlayer->nCntTex = 0;
							pPlayer->nCntPattern = 0;
							pPlayer->fTexSpan[0] = 0;
							pPlayer->fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
						}
					}

					//�W�����v�񐔕���
					pPlayer->nJumpTimes = AMOUNT_ABLE_JUMPS;

					//�Ō�ɒ��n���Ă����ʒu���L�^
					pPlayer->lastland.x = g_aStage[nCnt].pos.x;
					pPlayer->lastland.y = g_aStage[nCnt].pos.y - g_aStage[nCnt].fRadius[1];
				}

				//�ʒu���I�u�W�F�N�g�̏�[�ɖ߂�
				pos->y = g_aStage[nCnt].pos.y - g_aStage[nCnt].fRadius[1];
				//�v���C���[�̂Ƃ��̂ݓ��ʂȏ������{��
				if (nType == HIT_TYPE_PLAYER)
				{
					pPlayer->BGpos.y = g_aStage[nCnt].pos.y - g_aStage[nCnt].fRadius[1];
				}

				//�c�����̈ړ��ʂ𖳂���(�o�O�h�~)
				move->y = 0.0f;

				//�X�ɁA���̃u���b�N����J�R�������ꍇ�A�n�ʂ�����^�C�v�̓G��K���W�����v������
				if (nType == HIT_TYPE_ENEMY)
				{
					if (g_aStage[nCnt].nStyle == STAGE_OBJECT_STYLE_LEFT_J ||
						g_aStage[nCnt].nStyle == STAGE_OBJECT_STYLE_RIGHT_J)
					{
						switch (pEnemy[nEnemy].nStyle)
						{
						case ENEMY_01:
							pEnemy[nEnemy].move.y = -20.0f;
							break;
						case ENEMY_02:
							pEnemy[nEnemy].move.y = -18.0f;
							break;
						case ENEMY_03:
							pEnemy[nEnemy].move.y = -14.0f;
							break;
						case ENEMY_04:
							pEnemy[nEnemy].move.y = -20.0f;
							break;
						}
					}
				}
			}
		}

		//���̃I�u�W�F�N�g�̎��c���͈͓���
		if (pos->y - (fRadius[1] * 2.0f) < g_aStage[nCnt].pos.y + g_aStage[nCnt].fRadius[1] &&
			pos->y > g_aStage[nCnt].pos.y - g_aStage[nCnt].fRadius[1])
		{
			//���ցA������
			if (oldpos->x > g_aStage[nCnt].pos.x &&	//�ߋ��̍��W�����̃I�u�W�F�N�g���E���ł���
				move->x < 0.0f &&	//���ֈړ���
				pos->x - fRadius[0] < g_aStage[nCnt].pos.x + g_aStage[nCnt].fRadius[0])	//���݂̍��W�����̃I�u�W�F�N�g��荶���ł���
			{
				//�ʒu���I�u�W�F�N�g�̉E�[�ɖ߂�
				pos->x = g_aStage[nCnt].pos.x + g_aStage[nCnt].fRadius[0] + fRadius[0];

				//�������̈ړ��ʂ𖳂���(�o�O�h�~)
				move->x = 0.0f;
			}

			//���ցA������
			if (oldpos->x < g_aStage[nCnt].pos.x &&	//�ߋ��̍��W�����̃I�u�W�F�N�g��荶���ł���
				move->x > 0.0f &&	//�E�ֈړ���
				pos->x + fRadius[0] > g_aStage[nCnt].pos.x - g_aStage[nCnt].fRadius[0])	//���݂̍��W�����̃I�u�W�F�N�g���E���ł���
			{
				//�ʒu���I�u�W�F�N�g�̍��[�ɖ߂�
				pos->x = g_aStage[nCnt].pos.x - g_aStage[nCnt].fRadius[0] - fRadius[0];

				//�������̈ړ��ʂ𖳂���(�o�O�h�~)
				move->x = 0.0f;
			}
		}
	}

	return b;
}

//************************************************
//�X�e�[�W�\���̂̃A�h���X��n��
//************************************************
STAGE* GetInfo_Stage(void)
{
	return &g_aStage[0];
}