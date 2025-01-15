//************************************************
//
//�p�[�e�B�N������(�e���v��)[particle.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "particle.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Particle = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Particle = NULL;	//���_�o�b�t�@�̃|�C���^
PARTICLE g_aParticle[AMOUNT_POLYGON_PARTICLE];	//�p�[�e�B�N���p�����i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Particle()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PARTICLE,
		&g_pTexture_Particle);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Particle,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Particle[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Particle[0].rhw = 1.0f;
		pVtx_Particle[1].rhw = 1.0f;
		pVtx_Particle[2].rhw = 1.0f;
		pVtx_Particle[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Particle[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Particle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Particle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Particle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Particle[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Particle += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle->Unlock();

	//�\���̂̒��g��������
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCnt].fRadius = 0.0f;
		g_aParticle[nCnt].nRemain = 0;
		g_aParticle[nCnt].bUse = false;
	}
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Particle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Particle != NULL)
	{
		g_pTexture_Particle->Release();
		g_pTexture_Particle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Particle != NULL)
	{
		g_pVtxBuff_Particle->Release();
		g_pVtxBuff_Particle = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Particle(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse)
		{
			//�k��
			g_aParticle[nCnt].fRadius -= CHANGE_SPD_RADIUS_PARTICLE;

			//���Ԃ�̖h�~
			if (g_aParticle[nCnt].fRadius <= 0)
			{
				g_aParticle[nCnt].fRadius = 0.0f;
			}

			g_aParticle[nCnt].pos += g_aParticle[nCnt].move * MOVE_SPD_POS_PARTICLE;

			//���_��W�J����
			pVtx_Particle[0].pos.x = g_aParticle[nCnt].pos.x - g_aParticle[nCnt].fRadius;
			pVtx_Particle[0].pos.y = g_aParticle[nCnt].pos.y - g_aParticle[nCnt].fRadius;
			pVtx_Particle[1].pos.x = g_aParticle[nCnt].pos.x + g_aParticle[nCnt].fRadius;
			pVtx_Particle[1].pos.y = g_aParticle[nCnt].pos.y - g_aParticle[nCnt].fRadius;
			pVtx_Particle[2].pos.x = g_aParticle[nCnt].pos.x - g_aParticle[nCnt].fRadius;
			pVtx_Particle[2].pos.y = g_aParticle[nCnt].pos.y + g_aParticle[nCnt].fRadius;
			pVtx_Particle[3].pos.x = g_aParticle[nCnt].pos.x + g_aParticle[nCnt].fRadius;
			pVtx_Particle[3].pos.y = g_aParticle[nCnt].pos.y + g_aParticle[nCnt].fRadius;

			//�F���f
			pVtx_Particle[0].col = g_aParticle[nCnt].col;
			pVtx_Particle[1].col = g_aParticle[nCnt].col;
			pVtx_Particle[2].col = g_aParticle[nCnt].col;
			pVtx_Particle[3].col = g_aParticle[nCnt].col;

			g_aParticle[nCnt].nRemain--;

			//�c�����Ԃ������Ȃ����Ƃ�
			if (g_aParticle[nCnt].nRemain <= 0)
			{
				pVtx_Particle[0].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle[1].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle[2].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

				pVtx_Particle[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Particle[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Particle[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Particle[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				g_aParticle[nCnt].bUse = false;	//�g�p����𖳂���
			}
		}

		pVtx_Particle += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Particle(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Particle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Particle);

	//�|���S���̕`��
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�p�[�e�B�N���̏���ݒ肷��֐�
//************************************************
void Setinfo_Particle(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		//�g�p����Ă��Ȃ��p�[�e�B�N�������m������
		if (!g_aParticle[nCnt].bUse)
		{
			g_aParticle[nCnt].pos = pos;	//�ʒu��K���ɐݒ�

			//������ۂ��v�Z(�v���P�c)
			float fRandomX = (rand() % 314) * 0.01f;
			float fRandomY = (rand() % 314) * 0.01f;

			int nRondom = rand() % 2;

			nRondom == 0 ? 0 : fRandomX *= -1.0f, fRandomY *= -1.0f;

			g_aParticle[nCnt].move.x = sinf(D3DX_PI - fRandomX);	//�ړ��ʂ�K���ɐݒ�
			g_aParticle[nCnt].move.y = cosf(D3DX_PI - fRandomY);	//�ړ��ʂ�K���ɐݒ�
			g_aParticle[nCnt].col = col;	//�F�����킹�Đݒ�
			g_aParticle[nCnt].fRadius = RADIUS_PARTICLE;		//���a��K���ɐݒ�
			g_aParticle[nCnt].nRemain = REMAIN_TIME_PARTICLE;	//�c�����Ԃ�K���ɐݒ�
			g_aParticle[nCnt].bUse = true;	//�g�p������o��

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle->Unlock();
}