//************************************************
//
//�p�[�e�B�N������[particle.cpp]
//Author�F���c����
//
//************************************************
#include "particle.h"

//�}�N����`
#define AMOUNT_PARTICLE	(1024)	//�p�[�e�B�N���̐�
#define SPAN_PARTICLE	(3.0f)	//�p�[�e�B�N���̑傫��

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;	//�e�N�X�`���ւ̃|�C���^
Particle g_aParticle[AMOUNT_PARTICLE] = {};	//�p�[�e�B�N�����

//************************************************
//�p�[�e�B�N������
//************************************************
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�p�[�e�B�N����񏉊���
	for (int i = 0; i < AMOUNT_PARTICLE; i++)
	{
		g_aParticle[i].bUse = false;
		g_aParticle[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aParticle[i].fSize = 0.0f;
		g_aParticle[i].fDecrease = 0.0f;
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\shadow000.jpg",
		&g_pTextureParticle);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_PARTICLE; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();
}

//************************************************
//�p�[�e�B�N���j��
//************************************************
void UninitParticle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//************************************************
//�p�[�e�B�N���ݒ�
//************************************************
void SetInfoParticle(D3DXVECTOR3 pos, D3DXCOLOR col, float fSize)
{
	for (int i = 0; i < AMOUNT_PARTICLE; i++)
	{
		if (!g_aParticle[i].bUse)
		{
			g_aParticle[i].bUse = true;
			g_aParticle[i].pos = pos;
			g_aParticle[i].rot.y = (float)(rand() % 100);	/*�p�[�e�B�N����΂�������K����*/
			g_aParticle[i].col = col;
			g_aParticle[i].fSize = fSize;
			g_aParticle[i].fDecrease = 0.1f;

			//�T�C�Y�Z�b�g
			SetSizeParticle(i);

			break;
		}
	}
}

//************************************************
//�p�[�e�B�N���T�C�Y�Z�b�g
//************************************************
void SetSizeParticle(int nCnt)
{
	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//�T�C�Y�ύX
	pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCnt].fSize, g_aParticle[nCnt].fSize, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCnt].fSize, g_aParticle[nCnt].fSize, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCnt].fSize, -g_aParticle[nCnt].fSize, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCnt].fSize, -g_aParticle[nCnt].fSize, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();
}

//************************************************
//�p�[�e�B�N���X�V
//************************************************
void UpdateParticle(void)
{
	for (int i = 0; i < AMOUNT_PARTICLE; i++)
	{
		if (g_aParticle[i].bUse)
		{
			//�ړ�
			g_aParticle[i].pos.x += sinf(D3DX_PI - g_aParticle[i].rot.y);
			g_aParticle[i].pos.z -= cosf(D3DX_PI - g_aParticle[i].rot.y);

			//�J���[�����O
			SetColParticle(i);

			//���ŏ���
			DisappearParticle(i);
		}
	}
}

//************************************************
//�p�[�e�B�N���J���[�����O
//************************************************
void SetColParticle(int nCnt)
{
	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	g_aParticle[nCnt].col.a -= 0.05f;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//�J���[�����O
	pVtx[0].col = g_aParticle[nCnt].col;
	pVtx[1].col = g_aParticle[nCnt].col;
	pVtx[2].col = g_aParticle[nCnt].col;
	pVtx[3].col = g_aParticle[nCnt].col;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();
}

//************************************************
//�p�[�e�B�N������
//************************************************
void DisappearParticle(int nCnt)
{
	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//���������x
	g_aParticle[nCnt].fDecrease += 0.01f;

	//�|���S�����W�J�\�ȃT�C�Y������Ƃ�
	if (pVtx[0].pos.x <= 0.0f)
	{
		//�k��
		pVtx[0].pos.x += g_aParticle[nCnt].fDecrease;
		pVtx[0].pos.y -= g_aParticle[nCnt].fDecrease;
		pVtx[1].pos.x -= g_aParticle[nCnt].fDecrease;
		pVtx[1].pos.y -= g_aParticle[nCnt].fDecrease;
		pVtx[2].pos.x += g_aParticle[nCnt].fDecrease;
		pVtx[2].pos.y += g_aParticle[nCnt].fDecrease;
		pVtx[3].pos.x -= g_aParticle[nCnt].fDecrease;
		pVtx[3].pos.y += g_aParticle[nCnt].fDecrease;
	}
	//�|���S�������������Ƃ�
	else
	{
		g_aParticle[nCnt].bUse = false;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffParticle->Unlock();
}

//************************************************
//�p�[�e�B�N���`��
//************************************************
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���C�g���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�ʒu�̔�r���@�̕ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;

	for (int i = 0; i < AMOUNT_PARTICLE; i++)
	{
		if (g_aParticle[i].bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aParticle[i].mtxWorld);

			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����̐��ʂɌ���������
			D3DXMatrixInverse(&g_aParticle[i].mtxWorld, NULL, &mtxView);	//�t�s������߂�

			g_aParticle[i].mtxWorld._41 = 0.0f;
			g_aParticle[i].mtxWorld._42 = 0.0f;
			g_aParticle[i].mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				g_aParticle[i].pos.x,
				g_aParticle[i].pos.y,
				g_aParticle[i].pos.z);

			//�ʒu�𔽉f2
			D3DXMatrixMultiply(&g_aParticle[i].mtxWorld,
				&g_aParticle[i].mtxWorld,
				&mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aParticle[i].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureParticle);

			//�p�[�e�B�N���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}

	//���C�g���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�ʒu�̔�r���@�̕ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�u�����f�B���O��߂��ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}