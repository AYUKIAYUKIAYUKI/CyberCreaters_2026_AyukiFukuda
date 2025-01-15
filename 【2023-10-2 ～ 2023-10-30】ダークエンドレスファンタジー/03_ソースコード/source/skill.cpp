//************************************************
//
//�X�L������[skill.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "bomb.h"
#include "skill.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Skill[AMOUNT_TEX_SKILL] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Skill = NULL;	//���_�o�b�t�@�̃|�C���^
SKILL g_aSkill[AMOUNT_POLYGON_SKILL];	//�X�L�����

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Skill()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SKILL,
		&g_pTexture_Skill[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SKILL_CHARGE,
		&g_pTexture_Skill[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SKILL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Skill,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Skill;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Skill->Lock(0, 0, (void**)&pVtx_Skill, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Skill[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Skill[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Skill[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Skill[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Skill[0].rhw = 1.0f;
		pVtx_Skill[1].rhw = 1.0f;
		pVtx_Skill[2].rhw = 1.0f;
		pVtx_Skill[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Skill[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Skill[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Skill[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Skill[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (nCnt == 1)
		{
			pVtx_Skill[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			pVtx_Skill[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			pVtx_Skill[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			pVtx_Skill[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		}

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Skill[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Skill[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Skill[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Skill[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Skill += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Skill->Unlock();

	//�X�L���\���̂̏��̏������Q
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		g_aSkill[nCnt].nStyle = 0;
		g_aSkill[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkill[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkill[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkill[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aSkill[nCnt].nCntTex = 0;
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aSkill[nCnt].fTexSpan[nCnt2] = 0.0f;
			g_aSkill[nCnt].fRadius[nCnt2] = 0.0f;
			g_aSkill[nCnt].fLength[nCnt2] = 0.0f;
			g_aSkill[nCnt].fAngle[nCnt2] = 0.0f;
		}
	}

	//�X�L���\���̂ɏ���t�^
	SetInfo_Skill();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Skill(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEX_SKILL; nCnt++)
	{
		if (g_pTexture_Skill[nCnt] != NULL)
		{
			g_pTexture_Skill[nCnt]->Release();
			g_pTexture_Skill[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Skill != NULL)
	{
		g_pVtxBuff_Skill->Release();
		g_pVtxBuff_Skill = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Skill(void)
{
	//�ړ��Ȃ�
	Update_Pos_Skill();

	//�e�N�X�`���A�j���[�V����
	//Update_Tex_Skill();

	//�J���[�ύX
	//Update_Col_Skill();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Skill(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Skill, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexture_Skill[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�X�L���\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Skill(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		g_aSkill[nCnt].nStyle = nCnt;
		g_aSkill[nCnt].pos = D3DXVECTOR3(1200.0, 100.0f, 0.0f);
		g_aSkill[nCnt].fRadius[0] = 60.0f;	//�X�L��������
		g_aSkill[nCnt].fRadius[1] = 60.0f;	//�X�L���c����
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aSkill[nCnt].fLength[nCnt2] = sqrtf((g_aSkill[nCnt].fRadius[0] * g_aSkill[nCnt].fRadius[0]) + (g_aSkill[nCnt].fRadius[1] * g_aSkill[nCnt].fRadius[1]));
			g_aSkill[nCnt].fAngle[nCnt2] = atan2f(g_aSkill[nCnt].fRadius[0] * 2.0f, g_aSkill[nCnt].fRadius[1] * 2.0f);
		}
	}
}

//************************************************
//�X�L���̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Skill(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Skill;

	BOMB* pBomb = GetInfo_Bomb();
	int* pII = GetInfo_Bomb_aa();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Skill->Lock(0, 0, (void**)&pVtx_Skill, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			pVtx_Skill[0].pos.x = g_aSkill[nCnt].pos.x + sinf(g_aSkill[nCnt].rot.z - (D3DX_PI - g_aSkill[nCnt].fAngle[0])) * g_aSkill[nCnt].fLength[0];
			pVtx_Skill[0].pos.y = g_aSkill[nCnt].pos.y + cosf(g_aSkill[nCnt].rot.z - (D3DX_PI - g_aSkill[nCnt].fAngle[0])) * g_aSkill[nCnt].fLength[0];
			pVtx_Skill[1].pos.x = g_aSkill[nCnt].pos.x + sinf(g_aSkill[nCnt].rot.z + (D3DX_PI - g_aSkill[nCnt].fAngle[0])) * g_aSkill[nCnt].fLength[0];
			pVtx_Skill[1].pos.y = g_aSkill[nCnt].pos.y + cosf(g_aSkill[nCnt].rot.z + (D3DX_PI - g_aSkill[nCnt].fAngle[0])) * g_aSkill[nCnt].fLength[0];
			pVtx_Skill[2].pos.x = g_aSkill[nCnt].pos.x + sinf(g_aSkill[nCnt].rot.z - g_aSkill[nCnt].fAngle[1]) * g_aSkill[nCnt].fLength[1];
			pVtx_Skill[2].pos.y = g_aSkill[nCnt].pos.y + cosf(g_aSkill[nCnt].rot.z - g_aSkill[nCnt].fAngle[1]) * g_aSkill[nCnt].fLength[1];
			pVtx_Skill[3].pos.x = g_aSkill[nCnt].pos.x + sinf(g_aSkill[nCnt].rot.z + g_aSkill[nCnt].fAngle[1]) * g_aSkill[nCnt].fLength[1];
			pVtx_Skill[3].pos.y = g_aSkill[nCnt].pos.y + cosf(g_aSkill[nCnt].rot.z + g_aSkill[nCnt].fAngle[1]) * g_aSkill[nCnt].fLength[1];
			break;
		case 1:

			if (pBomb[0].bUse || *pII > 0)
			{
				pVtx_Skill[0].pos.x = g_aSkill[nCnt].pos.x - 52.0f;
				pVtx_Skill[0].pos.y = g_aSkill[nCnt].pos.y - 52.0f;
				pVtx_Skill[1].pos.x = g_aSkill[nCnt].pos.x + 52.0f;
				pVtx_Skill[1].pos.y = g_aSkill[nCnt].pos.y - 52.0f;
				pVtx_Skill[2].pos.x = g_aSkill[nCnt].pos.x - 52.0f;
				pVtx_Skill[2].pos.y = g_aSkill[nCnt].pos.y + 52.0f;
				pVtx_Skill[3].pos.x = g_aSkill[nCnt].pos.x + 52.0f;
				pVtx_Skill[3].pos.y = g_aSkill[nCnt].pos.y + 52.0f;
			}
			else
			{
				pVtx_Skill[0].pos.x = g_aSkill[nCnt].pos.x - 0.0f;
				pVtx_Skill[0].pos.y = g_aSkill[nCnt].pos.y - 0.0f;
				pVtx_Skill[1].pos.x = g_aSkill[nCnt].pos.x + 0.0f;
				pVtx_Skill[1].pos.y = g_aSkill[nCnt].pos.y - 0.0f;
				pVtx_Skill[2].pos.x = g_aSkill[nCnt].pos.x - 0.0f;
				pVtx_Skill[2].pos.y = g_aSkill[nCnt].pos.y + 0.0f;
				pVtx_Skill[3].pos.x = g_aSkill[nCnt].pos.x + 0.0f;
				pVtx_Skill[3].pos.y = g_aSkill[nCnt].pos.y + 0.0f;
			}

			break;
		}

		pVtx_Skill += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Skill->Unlock();
}

//************************************************
//�Q�[�W�̐F��ύX����֐�
//************************************************
void Update_Col_Skill(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Skill;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Skill->Lock(0, 0, (void**)&pVtx_Skill, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		pVtx_Skill[0].col = g_aSkill[nCnt].col;
		pVtx_Skill[1].col = g_aSkill[nCnt].col;
		pVtx_Skill[2].col = g_aSkill[nCnt].col;
		pVtx_Skill[3].col = g_aSkill[nCnt].col;

		pVtx_Skill += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Skill->Unlock();
}

////************************************************
////�X�L���̃e�N�X�`���𓮂����֐�
////************************************************
//void Update_Tex_Skill(void)
//{
//	//���_���ւ̃|�C���^
//	VERTEX_2D* pVtx_Skill;
//
//	PLAYER* pPlayer = GetInfo_Player();
//
//	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
//	g_pVtxBuff_Skill->Lock(0, 0, (void**)&pVtx_Skill, 0);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
//	{
//		if (g_aSkill[nCnt].nStyle == SKILL_STYLE_GAGE)
//		{
//			g_aSkill[nCnt].fTexSpan[0] = 1.0f - (SPAN_CHANGE_TEX_SKILL * (pPlayer->nLife + 1));
//			g_aSkill[nCnt].fTexSpan[1] = 1.0f - (SPAN_CHANGE_TEX_SKILL * pPlayer->nLife);
//		}
//
//		pVtx_Skill[0].tex = D3DXVECTOR2(0.0f, g_aSkill[nCnt].fTexSpan[0]);
//		pVtx_Skill[1].tex = D3DXVECTOR2(1.0f, g_aSkill[nCnt].fTexSpan[0]);
//		pVtx_Skill[2].tex = D3DXVECTOR2(0.0f, g_aSkill[nCnt].fTexSpan[1]);
//		pVtx_Skill[3].tex = D3DXVECTOR2(1.0f, g_aSkill[nCnt].fTexSpan[1]);
//
//		pVtx_Skill += AMOUNT_VTX;
//	}
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuff_Skill->Unlock();
//}

//************************************************
//�X�L���\���̂̃A�h���X��n��
//************************************************
SKILL* GetInfo_Skill(void)
{
	return &g_aSkill[0];
}