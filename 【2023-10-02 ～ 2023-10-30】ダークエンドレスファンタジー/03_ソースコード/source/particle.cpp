//************************************************
//
//�p�[�e�B�N������(�e���v��)[particle.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "camera.h"
#include "particle.h"
#include "player.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Particle[AMOUNT_TEX_PARTICLE] = {};	//�e�N�X�`���̃|�C���^
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
		TEXTURE_ATKED,
		&g_pTexture_Particle[PARTICLE_ATKED]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLOOD,
		&g_pTexture_Particle[PARTICLE_BLOOD]);

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
		g_aParticle[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCnt].nCntTex = 0;
		g_aParticle[nCnt].nCntPattern = 0;
		for (int i = 0; i < 2; i++)
		{
			g_aParticle[nCnt].fTexSpan[i] = 0;
			g_aParticle[nCnt].fRadius[i] = 0;
			g_aParticle[nCnt].fLength[i] = 0;
			g_aParticle[nCnt].fAngle[i] = 0;
		}
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
	for (int i = 0; i < AMOUNT_TEX_PARTICLE; i++)
	{
		if (g_pTexture_Particle[i] != NULL)
		{
			g_pTexture_Particle[i]->Release();
			g_pTexture_Particle[i] = NULL;
		}
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
	Update_Pos_Particle();
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

	for (int i = 0; i < AMOUNT_POLYGON_PARTICLE; i++)
	{
		//�e�N�X�`���̐ݒ�
		switch (g_aParticle[i].nStyle)
		{
		case PARTICLE_ATKED:
			pDevice->SetTexture(0, g_pTexture_Particle[PARTICLE_ATKED]);
			break;
		case PARTICLE_BLOOD:
			pDevice->SetTexture(0, g_pTexture_Particle[PARTICLE_BLOOD]);
			break;
		}

		////�A���t�@�u�����f�B���O�����Z�����ɐݒ�
		//pDevice->SetRenderState(D3DRS_BLENDOP,
		//	D3DBLENDOP_ADD);

		//pDevice->SetRenderState(D3DRS_SRCBLEND,
		//	D3DBLEND_SRCALPHA);

		//pDevice->SetRenderState(D3DRS_DESTBLEND,
		//	D3DBLEND_ONE);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	////�A���t�@�u�����f�B���O��߂��ݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP,
	//	D3DBLENDOP_ADD);

	//pDevice->SetRenderState(D3DRS_SRCBLEND,
	//	D3DBLEND_SRCALPHA);

	//pDevice->SetRenderState(D3DRS_DESTBLEND,
	//	D3DBLEND_INVSRCALPHA);
}

//************************************************
//�p�[�e�B�N���̏���ݒ肷��֐�
//************************************************
void Setinfo_Particle(int nStyle, D3DXVECTOR3 pos, D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		//�g�p����Ă��Ȃ��p�[�e�B�N�������m������
		if (!g_aParticle[nCnt].bUse)
		{
			float fRandomX = 0.0f, fRandomY = 0.0f;
			int nRondom = 0;

			g_aParticle[nCnt].nStyle = nStyle;
			switch (g_aParticle[nCnt].nStyle)
			{
			case PARTICLE_ATKED:
				g_aParticle[nCnt].pos = pos;
				g_aParticle[nCnt].pos.y -= 50.0f;	//����̃e�N�X�`���̈ʒu�ɍ����悤�ɕ␳
				fRandomX = (rand() % 314) * 0.01f;
				fRandomY = (rand() % 314) * 0.01f;
				nRondom = rand() % 2;
				nRondom == 0 ? 0 : fRandomX *= -1.0f, fRandomY *= -1.0f;
				g_aParticle[nCnt].move.x = sinf(D3DX_PI - fRandomX);
				g_aParticle[nCnt].move.y = cosf(D3DX_PI - fRandomY);
				g_aParticle[nCnt].pos += g_aParticle[nCnt].move * 15.0f;	//���炩���߈ړ��������Ƃɂ��Ă�����x���U
				g_aParticle[nCnt].col = col;
				g_aParticle[nCnt].fTexSpan[0] = 0.0f;
				g_aParticle[nCnt].fTexSpan[1] = SPAN_CHANGE_TEX_PARTICLE;
				g_aParticle[nCnt].fRadius[0] = 50.0f;
				g_aParticle[nCnt].fRadius[1] = 50.0f;
				g_aParticle[nCnt].fLength[0] = sqrtf((g_aParticle[nCnt].fRadius[0] * g_aParticle[nCnt].fRadius[0]) + (g_aParticle[nCnt].fRadius[1] * g_aParticle[nCnt].fRadius[1]));
				g_aParticle[nCnt].fLength[1] = g_aParticle[nCnt].fLength[0];
				g_aParticle[nCnt].fAngle[0] = atan2f(g_aParticle[nCnt].fRadius[0] * 2.0f, g_aParticle[nCnt].fRadius[1] * 2.0f);
				g_aParticle[nCnt].fAngle[1] = g_aParticle[nCnt].fAngle[0];
				g_aParticle[nCnt].nRemain = REMAIN_TIME_PARTICLE;
				g_aParticle[nCnt].bUse = true;
				break;
			case PARTICLE_BLOOD:
				g_aParticle[nCnt].pos = pos;
				g_aParticle[nCnt].pos.y -= 40.0f;	//�G�̃e�N�X�`���̈ʒu�ɍ����悤�ɕ␳
				fRandomX = (rand() % 314) * 0.01f;
				fRandomY = (rand() % 314) * 0.01f;
				nRondom = rand() % 2;
				nRondom == 0 ? 0 : fRandomX *= -1.0f, fRandomY *= -1.0f;
				g_aParticle[nCnt].move.x = sinf(D3DX_PI - fRandomX);
				g_aParticle[nCnt].move.y = cosf(D3DX_PI - fRandomY);
				g_aParticle[nCnt].pos += g_aParticle[nCnt].move * 5.0f;	//���炩���߈ړ��������Ƃɂ��Ă�����x���U
				g_aParticle[nCnt].col = col;
				g_aParticle[nCnt].fTexSpan[0] = 0.0f;
				g_aParticle[nCnt].fTexSpan[1] = SPAN_CHANGE_TEX_PARTICLE;
				g_aParticle[nCnt].fRadius[0] = 50.0f;
				g_aParticle[nCnt].fRadius[1] = 50.0f;
				g_aParticle[nCnt].fLength[0] = sqrtf((g_aParticle[nCnt].fRadius[0] * g_aParticle[nCnt].fRadius[0]) + (g_aParticle[nCnt].fRadius[1] * g_aParticle[nCnt].fRadius[1]));
				g_aParticle[nCnt].fLength[1] = g_aParticle[nCnt].fLength[0];
				g_aParticle[nCnt].fAngle[0] = atan2f(g_aParticle[nCnt].fRadius[0] * 2.0f, g_aParticle[nCnt].fRadius[1] * 2.0f);
				g_aParticle[nCnt].fAngle[1] = g_aParticle[nCnt].fAngle[0];
				g_aParticle[nCnt].nRemain = REMAIN_TIME_PARTICLE;
				g_aParticle[nCnt].bUse = true;
				break;
			}
			break;
		}
	}
}

//************************************************
//�p�[�e�B�N���̃o�[�e�b�N�X���X�V����֐�
//************************************************
void Update_Pos_Particle(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse)
		{
			//�ړ�
			g_aParticle[nCnt].pos += g_aParticle[nCnt].move;

			if (g_aParticle[nCnt].nStyle == PARTICLE_ATKED)
			{
				//����
				PLAYER* pPlayer = GetInfo_Player();
				pPlayer->LR == 0 ? g_aParticle[nCnt].pos.x += 1.5f : g_aParticle[nCnt].pos.x += -1.5f;
			}

			//�k��
			for (int q = 0; q < 2; q++)
			{
				g_aParticle[nCnt].fLength[q] *= CHANGE_SPD_RADIUS_PARTICLE;
				g_aParticle[nCnt].fLength[q] < 0 ? g_aParticle[nCnt].fLength[q] = 0.0f : 0;
			}

			//�A�j���[�V����
			Update_Tex_Particle(nCnt);

			//�X�N���[���ϊ�
			ConvertInfo_Screen(&g_aParticle[nCnt].pos);

			pVtx_Particle[0].pos.x = g_aParticle[nCnt].pos.x + sinf(g_aParticle[nCnt].rot.z - (D3DX_PI - g_aParticle[nCnt].fAngle[0])) * g_aParticle[nCnt].fLength[0];
			pVtx_Particle[0].pos.y = g_aParticle[nCnt].pos.y + cosf(g_aParticle[nCnt].rot.z - (D3DX_PI - g_aParticle[nCnt].fAngle[0])) * g_aParticle[nCnt].fLength[0];
			pVtx_Particle[1].pos.x = g_aParticle[nCnt].pos.x + sinf(g_aParticle[nCnt].rot.z + (D3DX_PI - g_aParticle[nCnt].fAngle[0])) * g_aParticle[nCnt].fLength[0];
			pVtx_Particle[1].pos.y = g_aParticle[nCnt].pos.y + cosf(g_aParticle[nCnt].rot.z + (D3DX_PI - g_aParticle[nCnt].fAngle[0])) * g_aParticle[nCnt].fLength[0];
			pVtx_Particle[2].pos.x = g_aParticle[nCnt].pos.x + sinf(g_aParticle[nCnt].rot.z - g_aParticle[nCnt].fAngle[1]) * g_aParticle[nCnt].fLength[1];
			pVtx_Particle[2].pos.y = g_aParticle[nCnt].pos.y + cosf(g_aParticle[nCnt].rot.z - g_aParticle[nCnt].fAngle[1]) * g_aParticle[nCnt].fLength[1];
			pVtx_Particle[3].pos.x = g_aParticle[nCnt].pos.x + sinf(g_aParticle[nCnt].rot.z + g_aParticle[nCnt].fAngle[1]) * g_aParticle[nCnt].fLength[1];
			pVtx_Particle[3].pos.y = g_aParticle[nCnt].pos.y + cosf(g_aParticle[nCnt].rot.z + g_aParticle[nCnt].fAngle[1]) * g_aParticle[nCnt].fLength[1];

			pVtx_Particle[0].col = g_aParticle[nCnt].col;
			pVtx_Particle[1].col = g_aParticle[nCnt].col;
			pVtx_Particle[2].col = g_aParticle[nCnt].col;
			pVtx_Particle[3].col = g_aParticle[nCnt].col;
		}

		pVtx_Particle += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle->Unlock();
}

//************************************************
//�p�[�e�B�N���̃e�N�X�`�����X�V����֐�
//************************************************
void Update_Tex_Particle(int nCnt)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle->Lock(0, 0, (void**)&pVtx_Particle, 0);

	pVtx_Particle += AMOUNT_VTX * nCnt;

	//�e�N�X�`����ύX
	g_aParticle[nCnt].nCntTex++;
	if (g_aParticle[nCnt].nCntTex > SPD_CHANGE_TEX_PARTICLE)
	{
		g_aParticle[nCnt].nCntTex = 0;
		g_aParticle[nCnt].nCntPattern++;
		g_aParticle[nCnt].fTexSpan[0] += SPAN_CHANGE_TEX_PARTICLE;
		g_aParticle[nCnt].fTexSpan[1] += SPAN_CHANGE_TEX_PARTICLE;
		if (g_aParticle[nCnt].nCntPattern >= AMOUNT_STYLE_TEX_PARTICLE)
		{
			g_aParticle[nCnt].nCntPattern = 0;
			g_aParticle[nCnt].fTexSpan[0] = 0;
			g_aParticle[nCnt].fTexSpan[1] = 0;
			g_aParticle[nCnt].bUse = false;
		}
	}

	pVtx_Particle[0].tex = D3DXVECTOR2(g_aParticle[nCnt].fTexSpan[0], 0.0f);
	pVtx_Particle[1].tex = D3DXVECTOR2(g_aParticle[nCnt].fTexSpan[1], 0.0f);
	pVtx_Particle[2].tex = D3DXVECTOR2(g_aParticle[nCnt].fTexSpan[0], 1.0f);
	pVtx_Particle[3].tex = D3DXVECTOR2(g_aParticle[nCnt].fTexSpan[1], 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle->Unlock();
}