//************************************************
//
//�{������[bomb.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "bomb.h"
#include "attack_box.h"
#include "camera.h"
#include "player.h"
#include "stage.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Bomb[AMOUNT_TEX_BOMB] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Bomb = NULL;	//���_�o�b�t�@�̃|�C���^
BOMB g_aBomb[AMOUNT_POLYGON_BOMB];	//�{�����
BOMB_BOX g_aBomb_Box[BOMB_STATE_MAX];
int g_nCharge = 0;
static float g_F = 0;	//�ėp��������

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Bomb()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BOMB_1,
		&g_pTexture_Bomb[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BOMB_2,
		&g_pTexture_Bomb[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BOMB,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Bomb,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Bomb;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bomb->Lock(0, 0, (void**)&pVtx_Bomb, 0);

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		//���_���W�̏����ݒ�
		pVtx_Bomb[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bomb[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bomb[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bomb[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Bomb[0].rhw = 1.0f;
		pVtx_Bomb[1].rhw = 1.0f;
		pVtx_Bomb[2].rhw = 1.0f;
		pVtx_Bomb[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Bomb[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Bomb[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Bomb[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Bomb[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Bomb[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Bomb[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Bomb[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Bomb[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Bomb += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bomb->Unlock();

	//BOMB�\���̂̏��̏������Q
	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		g_aBomb[i].bUse = false;
		g_aBomb[i].nState = 0;
		g_aBomb[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomb[i].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomb[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomb[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBomb[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aBomb[i].LR = 0;
		g_aBomb[i].nCntTex = 0;
		g_aBomb[i].nCntPattern = 0;
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aBomb[i].fTexSpan[nCnt] = 0.0f;
			g_aBomb[i].fTexSpanY[nCnt] = 0.0f;
			g_aBomb[i].fRadius[nCnt] = 0.0f;
			g_aBomb[i].fLength[nCnt] = 0.0f;
			g_aBomb[i].fAngle[nCnt] = 0.0f;
		}
		g_aBomb[i].nCT = 0;
		g_aBomb[i].nCharge = 0;
	}

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aBomb_Box[i].fRadius_Hold[nCnt] = 0.0f;
			g_aBomb_Box[i].fLength_Hold[nCnt] = 0.0f;
			g_aBomb_Box[i].fAngle_Hold[nCnt] = 0.0f;
		}
	}

	g_nCharge = 0;

	g_F = 0;

	CalcSize_Bomb_Box();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Bomb(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		if (g_pTexture_Bomb[i] != NULL)
		{
			g_pTexture_Bomb[i]->Release();
			g_pTexture_Bomb[i] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Bomb != NULL)
	{
		g_pVtxBuff_Bomb->Release();
		g_pVtxBuff_Bomb = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Bomb(void)
{
	Update_Pos_Bomb();

	//�{���̃��L���X�g����
	if (g_nCharge > 0)
	{
		g_nCharge--;
	}

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		//�g�p���肪�o�Ă���
		if (g_aBomb[i].bUse)
		{
			if (g_aBomb[i].nState == BOMB_EXPLOSION &&
				g_aBomb[i].nCntTex == 0)
			{
				//����
				GiveInfo_Attack_Box(1);

				//�{�����L���X�g�ݒ�
				g_nCharge = 120;
			}
		}
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Bomb(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Bomb, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		//�e�N�X�`���̐ݒ�
		switch (g_aBomb[i].nState)
		{
		case 0:
			pDevice->SetTexture(0, g_pTexture_Bomb[0]);
			break;
		case 1:
			pDevice->SetTexture(0, g_pTexture_Bomb[1]);
			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

void CalcSize_Bomb_Box(void)
{
	for (int i = 0; i < BOMB_STATE_MAX; i++)
	{
		switch (i)
		{
		case 0:

			g_aBomb_Box[i].fRadius_Hold[0] = 30.0f;
			g_aBomb_Box[i].fRadius_Hold[1] = 30.0f;

			g_aBomb_Box[i].fLength_Hold[0] = sqrtf((g_aBomb_Box[i].fRadius_Hold[0] * g_aBomb_Box[i].fRadius_Hold[0]) +
				(g_aBomb_Box[i].fRadius_Hold[1] * g_aBomb_Box[i].fRadius_Hold[1]));
			g_aBomb_Box[i].fLength_Hold[1] = g_aBomb_Box[i].fLength_Hold[0];

			g_aBomb_Box[i].fAngle_Hold[0] = atan2f(g_aBomb_Box[i].fRadius_Hold[0] * 2.0f, g_aBomb_Box[i].fRadius_Hold[1] * 2.0f);
			g_aBomb_Box[i].fAngle_Hold[1] = g_aBomb_Box[i].fAngle_Hold[0];

			break;

		case 1:

			g_aBomb_Box[i].fRadius_Hold[0] = 170.0f;
			g_aBomb_Box[i].fRadius_Hold[1] = 170.0f;

			g_aBomb_Box[i].fLength_Hold[0] = sqrtf((g_aBomb_Box[i].fRadius_Hold[0] * g_aBomb_Box[i].fRadius_Hold[0]) +
				(g_aBomb_Box[i].fRadius_Hold[1] * g_aBomb_Box[i].fRadius_Hold[1]));
			g_aBomb_Box[i].fLength_Hold[1] = g_aBomb_Box[i].fLength_Hold[0];

			g_aBomb_Box[i].fAngle_Hold[0] = atan2f(g_aBomb_Box[i].fRadius_Hold[0] * 2.0f, g_aBomb_Box[i].fRadius_Hold[1] * 2.0f);
			g_aBomb_Box[i].fAngle_Hold[1] = g_aBomb_Box[i].fAngle_Hold[0];

			break;
		}
	}
}

//************************************************
//�{���\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Bomb(void)
{
	PLAYER* pPlayer = GetInfo_Player();

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		//���L���X�g�ς݂Ȃ�
		if (!g_aBomb[i].bUse && g_nCharge <= 0)
		{
			g_aBomb[i].bUse = true;
			g_aBomb[i].nState = BOMB_IDLE;
			g_aBomb[i].pos = pPlayer->pos;
			pPlayer->LR == 0 ? g_aBomb[i].move.x = 12.5f : g_aBomb[i].move.x = -12.5f;
			g_aBomb[i].move.y = -15.0f;
			g_aBomb[i].oldpos = g_aBomb[i].pos;
			for (int ii = 0; ii < 2; ii++)
			{
				g_aBomb[i].fRadius[ii] = g_aBomb_Box[i].fRadius_Hold[ii];
				g_aBomb[i].fLength[ii] = g_aBomb_Box[i].fLength_Hold[ii];
				g_aBomb[i].fAngle[ii] = g_aBomb_Box[i].fAngle_Hold[ii];
			}
			g_aBomb[i].nCT = 45;

			g_aBomb[i].fTexSpan[0] = 0.0f;
			g_aBomb[i].fTexSpan[1] = SPAN_CHANGE_TEX_BOMB;
			g_aBomb[i].fTexSpanY[0] = 0.0f;
			g_aBomb[i].fTexSpanY[1] = SPAN_CHANGE_TEX_BOMB;

			g_F = 1.0f;

			break;
		}
	}
}

//************************************************
//�{���̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Bomb(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Bomb;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bomb->Lock(0, 0, (void**)&pVtx_Bomb, 0);

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		if (g_aBomb[i].bUse)
		{
			//�ߋ��̈ʒu���L�^
			g_aBomb[i].oldpos = g_aBomb[i].pos;

			//�ړ�
			g_aBomb[i].pos += g_aBomb[i].move;

			//���ړ�����
			if (g_aBomb[i].nState != BOMB_EXPLOSION)
			{
				g_aBomb[i].move.x = g_aBomb[i].move.x * 0.98f;
			}
			else
			{
				g_aBomb[i].move.x = 0.0f;
			}

			//�d��
			g_aBomb[i].move.y = g_aBomb[i].move.y + 1.0f;

			//�A�j���[�V����
			Update_Tex_Bomb();

			//��Ԃɍ��킹�ă{�b�N�X����
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				g_aBomb[i].fLength[nCnt] = g_aBomb_Box[g_aBomb[i].nState].fLength_Hold[nCnt];
				g_aBomb[i].fAngle[nCnt] = g_aBomb_Box[g_aBomb[i].nState].fAngle_Hold[nCnt];
			}


			if (g_aBomb[i].nState == BOMB_EXPLOSION)
			{
				if (g_F > 1.0f)
				{
					g_F = 1.0f;
				}
			}


			//�n��
			HitDetection_Stage(0, 1, &g_aBomb[i].pos, &g_aBomb[i].oldpos, &g_aBomb[i].move, &g_aBomb[i].fRadius[0]);

			//�������ړ�
			ConvertInfo_Screen(&g_aBomb[i].pos);
		}
		//�g�p���ĂȂ��Ȃ�f�[�^�N���A
		else
		{
			g_aBomb[i].bUse = false;
			g_aBomb[i].nState = 0;
			g_aBomb[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBomb[i].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBomb[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBomb[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBomb[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			g_aBomb[i].LR = 0;
			g_aBomb[i].nCntTex = 0;
			g_aBomb[i].nCntPattern = 0;
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				g_aBomb[i].fTexSpan[nCnt] = 0.0f;
				g_aBomb[i].fTexSpanY[nCnt] = 0.0f;
				g_aBomb[i].fRadius[nCnt] = 0.0f;
				g_aBomb[i].fLength[nCnt] = 0.0f;
				g_aBomb[i].fAngle[nCnt] = 0.0f;
			}
			g_aBomb[i].nCT = 0;
			g_aBomb[i].nCharge = 0;
		}
			
		pVtx_Bomb[0].pos.x = g_aBomb[i].pos.x + sinf(g_aBomb[i].rot.z - (D3DX_PI - g_aBomb[i].fAngle[0])) * g_aBomb[i].fLength[0] * g_F;
		pVtx_Bomb[0].pos.y = g_aBomb[i].pos.y + cosf(g_aBomb[i].rot.z - (D3DX_PI - g_aBomb[i].fAngle[0])) * g_aBomb[i].fLength[0] * g_F;
		pVtx_Bomb[1].pos.x = g_aBomb[i].pos.x + sinf(g_aBomb[i].rot.z + (D3DX_PI - g_aBomb[i].fAngle[0])) * g_aBomb[i].fLength[0] * g_F;
		pVtx_Bomb[1].pos.y = g_aBomb[i].pos.y + cosf(g_aBomb[i].rot.z + (D3DX_PI - g_aBomb[i].fAngle[0])) * g_aBomb[i].fLength[0] * g_F;
		pVtx_Bomb[2].pos.x = g_aBomb[i].pos.x + sinf(g_aBomb[i].rot.z - g_aBomb[i].fAngle[1]) * g_aBomb[i].fLength[1] * g_F;
		pVtx_Bomb[2].pos.y = g_aBomb[i].pos.y + cosf(g_aBomb[i].rot.z - g_aBomb[i].fAngle[1]) * g_aBomb[i].fLength[1] * g_F;
		pVtx_Bomb[3].pos.x = g_aBomb[i].pos.x + sinf(g_aBomb[i].rot.z + g_aBomb[i].fAngle[1]) * g_aBomb[i].fLength[1] * g_F;
		pVtx_Bomb[3].pos.y = g_aBomb[i].pos.y + cosf(g_aBomb[i].rot.z + g_aBomb[i].fAngle[1]) * g_aBomb[i].fLength[1] * g_F;

		if (g_aBomb[i].nState == BOMB_IDLE)
		{
			pVtx_Bomb[0].pos.y += -40.0f;
			pVtx_Bomb[1].pos.y += -40.0f;
			pVtx_Bomb[2].pos.y += -40.0f;
			pVtx_Bomb[3].pos.y += -40.0f;

			g_F *= 1.03f;
		}

		if (g_aBomb[i].nState == BOMB_EXPLOSION)
		{
			pVtx_Bomb[0].pos.y += -40.0f;
			pVtx_Bomb[1].pos.y += -40.0f;
			pVtx_Bomb[2].pos.y += -40.0f;
			pVtx_Bomb[3].pos.y += -40.0f;

			g_F *= 0.96f;
		}

		pVtx_Bomb += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bomb->Unlock();
}

void Update_Tex_Bomb(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Bomb;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bomb->Lock(0, 0, (void**)&pVtx_Bomb, 0);

	for (int i = 0; i < AMOUNT_POLYGON_BOMB; i++)
	{
		if (g_aBomb[i].bUse)
		{
			//�e�N�X�`����ύX
			switch (g_aBomb[i].nState)
			{
			case BOMB_IDLE:
				g_aBomb[i].nCntTex++;
				if (g_aBomb[i].nCntTex > 0)
				{
					g_aBomb[i].nCntTex = 0;
					g_aBomb[i].nCntPattern++;
					g_aBomb[i].fTexSpan[0] += SPAN_CHANGE_TEX_BOMB;
					g_aBomb[i].fTexSpan[1] += SPAN_CHANGE_TEX_BOMB;

					if (g_aBomb[i].fTexSpan[0] >= 1.0f)
					{
						if (g_aBomb[i].fTexSpanY[1] >= SPAN_CHANGE_TEX_BOMB * 6.0f && g_aBomb[i].fTexSpan[1] >= SPAN_CHANGE_TEX_BOMB * 4.0f)
						{
							g_aBomb[i].nCntTex = 0;
							g_aBomb[i].fTexSpan[0] = 0.0f;
							g_aBomb[i].fTexSpan[1] = SPAN_CHANGE_TEX_EXPLOSION;

							g_aBomb[i].nState = BOMB_EXPLOSION;

							break;
						}

						g_aBomb[i].fTexSpan[0] = 0.0f;
						g_aBomb[i].fTexSpan[1] = SPAN_CHANGE_TEX_BOMB;

						g_aBomb[i].fTexSpanY[0] += SPAN_CHANGE_TEX_BOMB;
						g_aBomb[i].fTexSpanY[1] += SPAN_CHANGE_TEX_BOMB;
					}
				}
				break;
			case BOMB_EXPLOSION:
				g_aBomb[i].nCntTex++;
				g_aBomb[i].fTexSpan[0] += SPAN_CHANGE_TEX_EXPLOSION;
				g_aBomb[i].fTexSpan[1] += SPAN_CHANGE_TEX_EXPLOSION;
				g_aBomb[i].fTexSpanY[0] = 0.0f;
				g_aBomb[i].fTexSpanY[1] = SPAN_CHANGE_TEX_EXPLOSION;
				if (g_aBomb[i].nCntTex >= 30)
				{
					g_aBomb[i].fTexSpan[0] = 0.0f;
					g_aBomb[i].fTexSpan[1] = 0.0f;

					g_aBomb[i].fTexSpanY[0] = 0.0f;
					g_aBomb[i].fTexSpanY[1] = 0.0f;

					g_aBomb[i].bUse = false;
				}
				break;
			}

			pVtx_Bomb[0].tex = D3DXVECTOR2(g_aBomb[i].fTexSpan[0], 	g_aBomb[i].fTexSpanY[0]);
			pVtx_Bomb[1].tex = D3DXVECTOR2(g_aBomb[i].fTexSpan[1], 	g_aBomb[i].fTexSpanY[0]);
			pVtx_Bomb[2].tex = D3DXVECTOR2(g_aBomb[i].fTexSpan[0], 	g_aBomb[i].fTexSpanY[1]);
			pVtx_Bomb[3].tex = D3DXVECTOR2(g_aBomb[i].fTexSpan[1], 	g_aBomb[i].fTexSpanY[1]);
		}

		pVtx_Bomb += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bomb->Unlock();
}

//************************************************
//�{���\���̂̃A�h���X��n��
//************************************************
BOMB* GetInfo_Bomb(void)
{
	return &g_aBomb[0];
}

int* GetInfo_Bomb_aa(void)
{
	return &g_nCharge;
}