//************************************************
//
//�G�t�F�N�g����[effect.cpp]
//Author�F���c����
//
//************************************************
#include "effect.h"

//�}�N����`
#define AMOUNT_EFFECT	(1024)	//�G�t�F�N�g�̐�
#define SPAN_EFFECT	(4.0f)	//�G�t�F�N�g�̑傫��

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;	//�e�N�X�`���ւ̃|�C���^
Effect g_aEffect[AMOUNT_EFFECT] = {};	//�G�t�F�N�g���

//************************************************
//�G�t�F�N�g����
//************************************************
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�G�t�F�N�g��񏉊���
	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		g_aEffect[i].bUse = false;
		g_aEffect[i].nStyle = 0;
		g_aEffect[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect[i].fDecrease = 0.0f;
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\shadow000.jpg",
		&g_pTextureEffect);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	g_pVtxBuffEffect->Unlock();
}

//************************************************
//�G�t�F�N�g�j��
//************************************************
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//************************************************
//�G�t�F�N�g�ݒ�
//************************************************
void SetInfoEffect(int nStyle, D3DXVECTOR3 pos, D3DXCOLOR col)
{
	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		if (!g_aEffect[i].bUse)
		{
			g_aEffect[i].bUse = true;
			g_aEffect[i].nStyle = nStyle;
			g_aEffect[i].pos = pos;
			g_aEffect[i].col = col;
			g_aEffect[i].fDecrease = 0.1f;

			//��ނɍ��킹�ăT�C�Y���Z�b�g
			SetSizeEffect(i);

			break;
		}
	}
}

//************************************************
//�G�t�F�N�g�T�C�Y�Z�b�g
//************************************************
void SetSizeEffect(int nCnt)
{
	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//�T�C�Y�ύX
	switch (g_aEffect[nCnt].nStyle)
	{
	case EffectStyleBullet:
		pVtx[0].pos = D3DXVECTOR3(-SPAN_EFFECT, SPAN_EFFECT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_EFFECT, SPAN_EFFECT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_EFFECT, -SPAN_EFFECT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_EFFECT, -SPAN_EFFECT, 0.0f);
		break;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//************************************************
//�G�t�F�N�g�X�V
//************************************************
void UpdateEffect(void)
{
	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		if (g_aEffect[i].bUse)
		{
			//�J���[�����O
			SetColEffect(i);

			//���ŏ���
			DisappearEffect(i);
		}
	}
}

//************************************************
//�G�t�F�N�g�J���[�����O
//************************************************
void SetColEffect(int nCnt)
{
	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//����
	g_aEffect[nCnt].col.a -= 0.01f;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//�F�ύX
	pVtx[0].col = g_aEffect[nCnt].col;
	pVtx[1].col = g_aEffect[nCnt].col;
	pVtx[2].col = g_aEffect[nCnt].col;
	pVtx[3].col = g_aEffect[nCnt].col;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//************************************************
//�G�t�F�N�g����
//************************************************
void DisappearEffect(int nCnt)
{
	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += AMOUNT_VTX * nCnt;

	//���������x
	g_aEffect[nCnt].fDecrease += 0.0025f;

	//�|���S�����W�J�\�ȃT�C�Y������Ƃ�
	if (pVtx[0].pos.x <= 0.0f)
	{
		//�k��
		pVtx[0].pos.x += g_aEffect[nCnt].fDecrease;
		pVtx[0].pos.y -= g_aEffect[nCnt].fDecrease;
		pVtx[1].pos.x -= g_aEffect[nCnt].fDecrease;
		pVtx[1].pos.y -= g_aEffect[nCnt].fDecrease;
		pVtx[2].pos.x += g_aEffect[nCnt].fDecrease;
		pVtx[2].pos.y += g_aEffect[nCnt].fDecrease;
		pVtx[3].pos.x -= g_aEffect[nCnt].fDecrease;
		pVtx[3].pos.y += g_aEffect[nCnt].fDecrease;
	}
	//�|���S�������������Ƃ�
	else
	{
		g_aEffect[nCnt].bUse = false;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//************************************************
//�G�t�F�N�g�`��
//************************************************
void DrawEffect(void)
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

	for (int i = 0; i < AMOUNT_EFFECT; i++)
	{
		if (g_aEffect[i].bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[i].mtxWorld);

			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����̐��ʂɌ���������
			D3DXMatrixInverse(&g_aEffect[i].mtxWorld, NULL, &mtxView);	//�t�s������߂�

			g_aEffect[i].mtxWorld._41 = 0.0f;
			g_aEffect[i].mtxWorld._42 = 0.0f;
			g_aEffect[i].mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				g_aEffect[i].pos.x,
				g_aEffect[i].pos.y,
				g_aEffect[i].pos.z);

			//�ʒu�𔽉f2
			D3DXMatrixMultiply(&g_aEffect[i].mtxWorld,
				&g_aEffect[i].mtxWorld,
				&mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[i].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			//�G�t�F�N�g�̕`��
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
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
}