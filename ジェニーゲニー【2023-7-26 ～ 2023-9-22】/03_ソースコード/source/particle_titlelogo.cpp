//************************************************
//
//�^�C�g�����S�p�[�e�B�N������[particle_titlelogo.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "title.h"
#include "particle_titlelogo.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Particle_Titlelogo = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Particle_Titlelogo = NULL;	//���_�o�b�t�@�̃|�C���^
PARTICLE_TITLELOGO g_aParticle_Titlelogo[AMOUNT_POLYGON_PARTICLE_TITLELOGO];	//�p�[�e�B�N���p�����i�[
float g_fcol = 0.5f;

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Particle_Titlelogo()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PARTICLE_TITLELOGO,
		&g_pTexture_Particle_Titlelogo);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PARTICLE_TITLELOGO,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Particle_Titlelogo,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle_Titlelogo;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle_Titlelogo->Lock(0, 0, (void**)&pVtx_Particle_Titlelogo, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_TITLELOGO; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Particle_Titlelogo[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle_Titlelogo[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle_Titlelogo[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle_Titlelogo[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Particle_Titlelogo[0].rhw = 1.0f;
		pVtx_Particle_Titlelogo[1].rhw = 1.0f;
		pVtx_Particle_Titlelogo[2].rhw = 1.0f;
		pVtx_Particle_Titlelogo[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Particle_Titlelogo[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle_Titlelogo[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle_Titlelogo[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle_Titlelogo[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Particle_Titlelogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Particle_Titlelogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Particle_Titlelogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Particle_Titlelogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Particle_Titlelogo += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle_Titlelogo->Unlock();

	//�\���̂̒��g��������
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_TITLELOGO; nCnt++)
	{
		g_aParticle_Titlelogo[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Titlelogo[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Titlelogo[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle_Titlelogo[nCnt].fRadius = 0.0f;
		g_aParticle_Titlelogo[nCnt].nRemain = 0;
		g_aParticle_Titlelogo[nCnt].bUse = false;
	}

	g_fcol = 0.5f;
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Particle_Titlelogo(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Particle_Titlelogo != NULL)
	{
		g_pTexture_Particle_Titlelogo->Release();
		g_pTexture_Particle_Titlelogo = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Particle_Titlelogo != NULL)
	{
		g_pVtxBuff_Particle_Titlelogo->Release();
		g_pVtxBuff_Particle_Titlelogo = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Particle_Titlelogo(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle_Titlelogo;

	bool* pStartFadeout;
	pStartFadeout = StartFadeout();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle_Titlelogo->Lock(0, 0, (void**)&pVtx_Particle_Titlelogo, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_TITLELOGO; nCnt++)
	{
		if (g_aParticle_Titlelogo[nCnt].bUse)
		{
			//�k��
			g_aParticle_Titlelogo[nCnt].fRadius -= CHANGE_SPD_RADIUS_PARTICLE_TITLELOGO;

			//���Ԃ�̖h�~
			if (g_aParticle_Titlelogo[nCnt].fRadius <= 0)
			{
				g_aParticle_Titlelogo[nCnt].fRadius = 0.0f;
			}

			g_aParticle_Titlelogo[nCnt].pos += g_aParticle_Titlelogo[nCnt].move * MOVE_SPD_POS_PARTICLE_TITLELOGO;

			//���_��W�J����
			pVtx_Particle_Titlelogo[0].pos.x = g_aParticle_Titlelogo[nCnt].pos.x - g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[0].pos.y = g_aParticle_Titlelogo[nCnt].pos.y - g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[1].pos.x = g_aParticle_Titlelogo[nCnt].pos.x + g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[1].pos.y = g_aParticle_Titlelogo[nCnt].pos.y - g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[2].pos.x = g_aParticle_Titlelogo[nCnt].pos.x - g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[2].pos.y = g_aParticle_Titlelogo[nCnt].pos.y + g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[3].pos.x = g_aParticle_Titlelogo[nCnt].pos.x + g_aParticle_Titlelogo[nCnt].fRadius;
			pVtx_Particle_Titlelogo[3].pos.y = g_aParticle_Titlelogo[nCnt].pos.y + g_aParticle_Titlelogo[nCnt].fRadius;

			if (*pStartFadeout == true)
			{
				if (g_fcol > 0.0f)
				{
					g_fcol -= 0.1f;
				}

				pVtx_Particle_Titlelogo[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcol);
				pVtx_Particle_Titlelogo[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcol);
				pVtx_Particle_Titlelogo[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcol);
				pVtx_Particle_Titlelogo[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_fcol);
			}

			g_aParticle_Titlelogo[nCnt].nRemain--;

			//�c�����Ԃ������Ȃ����Ƃ�
			if (g_aParticle_Titlelogo[nCnt].nRemain <= 0)
			{
				pVtx_Particle_Titlelogo[0].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Titlelogo[1].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Titlelogo[2].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Titlelogo[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

				g_aParticle_Titlelogo[nCnt].bUse = false;	//�g�p����𖳂���
			}
		}

		pVtx_Particle_Titlelogo += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle_Titlelogo->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Particle_Titlelogo(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Particle_Titlelogo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Particle_Titlelogo);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_ONE);

	//�|���S���̕`��
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_TITLELOGO; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//�A���t�@�u�����f�B���O��߂��ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_INVSRCALPHA);
}

//************************************************
//�p�[�e�B�N���̏���ݒ肷��֐�
//************************************************
void Setinfo_Particle_Titlelogo(D3DXVECTOR3 pos)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle_Titlelogo;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle_Titlelogo->Lock(0, 0, (void**)&pVtx_Particle_Titlelogo, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_TITLELOGO; nCnt++)
	{
		//�g�p����Ă��Ȃ��p�[�e�B�N�������m������
		if (!g_aParticle_Titlelogo[nCnt].bUse)
		{
			g_aParticle_Titlelogo[nCnt].pos = pos;	//�ʒu��K���ɐݒ�

			//������ۂ��v�Z(�v���P�c)
			float fRandomX = (rand() % 314) * 0.01f;
			float fRandomY = (rand() % 314) * 0.01f;

			int nRondom = rand() % 2;

			nRondom == 0 ? 0 : fRandomX *= -1.0f, fRandomY *= -1.0f;

			g_aParticle_Titlelogo[nCnt].move.x = sinf(D3DX_PI - fRandomX);	//�ړ��ʂ�K���ɐݒ�
			g_aParticle_Titlelogo[nCnt].move.y = cosf(D3DX_PI - fRandomY);	//�ړ��ʂ�K���ɐݒ�
			g_aParticle_Titlelogo[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);	//�F��K���ɐݒ�
			g_aParticle_Titlelogo[nCnt].fRadius = RADIUS_PARTICLE_TITLELOGO;		//���a��K���ɐݒ�
			g_aParticle_Titlelogo[nCnt].nRemain = REMAIN_TIME_PARTICLE_TITLELOGO;	//�c�����Ԃ�K���ɐݒ�
			g_aParticle_Titlelogo[nCnt].bUse = true;	//�g�p������o��

			break;
		}

		pVtx_Particle_Titlelogo += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle_Titlelogo->Unlock();
}