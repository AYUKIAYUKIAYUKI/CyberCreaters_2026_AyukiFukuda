////************************************************
////
////���`�̓����蔻�������[visible_sphere.cpp]
////Author�F���c����
////
////************************************************
//#include "visible_sphere.h"
//
//#include "player.h"
//
////�}�N����`
//#define AMOUNT_SPHERE	(1024)	//�X�t�B�A�̍ő吔
//
//#define COLUMN_SPHERE	(11)	//��(���̕�)
//#define LINE_SPHERE	(11)	//�s(��������)
//
////�O���[�o���ϐ�
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSphere = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//LPDIRECT3DTEXTURE9 g_pTextureSphere = NULL;	//�e�N�X�`���ւ̃|�C���^
//LPDIRECT3DINDEXBUFFER9 g_pIdxBuffSphere = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
//Sphere g_aSphere[AMOUNT_SPHERE] = {};	//���C���
//static const float g_F = 1.0f;	//�萔1.0f
///* 1�|���S�������� */
//static const int g_nAmountVtx = (COLUMN_SPHERE * LINE_SPHERE);	//���_�̐�
//static const int g_nAmountPrimitive = (((COLUMN_SPHERE - 1) * (LINE_SPHERE - 1)) * 2) + ((LINE_SPHERE - 2) * 4);	//�ʂ̐�
//static const int g_nAmountIdx = g_nAmountPrimitive + 2;	//�C���f�b�N�X�̐�
//static const float g_COLUMN = g_F / (COLUMN_SPHERE - 1);	//���񕪂�1
//static const float g_LINE = g_F / (LINE_SPHERE - 1);	//���s����1
//static const float g_COLUMNr = (D3DX_PI * 2.0f) / (COLUMN_SPHERE - 1);	//���񕪂�1�̊p�x
//static const float g_LINEr = D3DX_PI / (LINE_SPHERE - 1);	//���s����1�̊p�x
//
////************************************************
////�X�t�B�A����
////************************************************
//void InitVisible_Sphere(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
//
//	for (int i = 0; i < AMOUNT_SPHERE; i++)
//	{
//		g_aSphere[i].bUse = false;
//		g_aSphere[i].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
//		g_aSphere[i].pPos = NULL;
//		g_aSphere[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//	}
//
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nAmountVtx * AMOUNT_SPHERE,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffSphere,
//		NULL);
//
//	//���_���̃|�C���^
//	VERTEX_3D* pVtx;
//
//	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
//	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int i = 0; i < g_nAmountVtx; i++)
//	{
//		//���_���W�̐ݒ�
//		pVtx[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//�@���x�N�g���̐ݒ�
//		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		//���_�J���[�̏����ݒ�
//		pVtx[i].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);
//
//		//�e�N�X�`�����W�̏����ݒ�
//		pVtx[i].tex = D3DXVECTOR2(0.0f, 0.0f);
//	}
//
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffSphere->Unlock();
//
//	//�C���f�b�N�X�o�b�t�@�̐���
//	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAmountIdx * AMOUNT_SPHERE,
//		D3DUSAGE_WRITEONLY,
//		D3DFMT_INDEX16,
//		D3DPOOL_MANAGED,
//		&g_pIdxBuffSphere,
//		NULL);
//
//	//�C���f�b�N�X�o�b�t�@�̃|�C���^
//	WORD* pIdx;
//
//	//�C���f�b�N�X�o�b�t�@�����b�N
//	g_pIdxBuffSphere->Lock(0, 0, (void**)&pIdx, 0);
//
//	int Z = 0;	//�s���J�E���g
//	while (1)	/* ���[�v�񐔂͏k�ރ��[�v�� */
//	{
//		//�s�̋N�_������W�J����
//		for (int X = 0; X < COLUMN_SPHERE; X++, pIdx += 2)	/* 2���_�Z�b�g�ŗ񂪂���Ă��� */
//		{
//			pIdx[0] = (WORD)(COLUMN_SPHERE + X + (Z * COLUMN_SPHERE));	/* �񐔎��̂��N�_�̃C���f�b�N�X�ɂȂ� */
//			pIdx[1] = (WORD)(X + (Z * COLUMN_SPHERE));
//		}
//
//		//�k�ރ��[�v���o���Ȃ��Ȃ�΃��[�v�𔲂���
//		if (Z >= LINE_SPHERE - 2) break;
//
//		pIdx[0] = (WORD)((COLUMN_SPHERE * (Z + 1)) - 1);	/* (�� * (�Y���s + 1)) - 1�ł��̍s�̉E��̊p */
//		pIdx[1] = (WORD)((Z + 2) * COLUMN_SPHERE);	/* (�Y���s + 2) * �񐔂ŋN�_�̂����1�s���� */
//
//		pIdx += 2;
//		Z++;	/* �s�̋N�_��1�i������ */
//	}
//
//	//�C���f�b�N�X�o�b�t�@���A�����b�N
//	g_pIdxBuffSphere->Unlock();
//}
//
////************************************************
////�X�t�B�A�W�J
////************************************************
//void SetSizeVisible_Sphere(const float fRadius, D3DXCOLOR col, D3DXVECTOR3* pPos)
//{
//	//���_���̃|�C���^
//	VERTEX_3D* pVtx;
//
//	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
//	g_pVtxBuffSphere->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int i = 0; i < AMOUNT_SPHERE; i++, pVtx += g_nAmountVtx)
//	{
//		if (g_aSphere[i].bUse) continue;
//
//		g_aSphere[i].bUse = true;
//
//		float fArg = 0.0f;	//��
//		float fAZ = -(D3DX_PI * 0.5f);	//��
//		for (int j = 0; j < g_nAmountVtx; j++, fArg += g_COLUMNr)
//		{
//			//�p�x�̒���
//			if (fArg >= (D3DX_PI * 2.0f))
//			{
//				fArg = 0.0f;
//				fAZ += g_LINEr;
//			}
//
//			//���_���W�̐ݒ�
//			pVtx[j].pos =
//			{
//				(fRadius * cosf(fArg) * cosf(fAZ)),
//				(fRadius * sinf(fAZ)),
//				(fRadius * sinf(fArg) * cosf(fAZ))
//			};
//
//			pVtx[j].col = col;
//		}
//
//		/* �Ώۂ̃��[���h���W�ɓ������� */
//		g_aSphere[i].pPos = pPos;
//
//		break;
//	}
//
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffSphere->Unlock();
//}
//
////************************************************
////�X�t�B�A�j��
////************************************************
//void UninitVisible_Sphere(void)
//{
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffSphere != NULL)
//	{
//		g_pVtxBuffSphere->Release();
//		g_pVtxBuffSphere = NULL;
//	}
//
//	//�C���f�b�N�X�o�b�t�@�̔j��
//	if (g_pIdxBuffSphere != NULL)
//	{
//		g_pIdxBuffSphere->Release();
//		g_pIdxBuffSphere = NULL;
//	}
//}
//
////************************************************
////�X�t�B�A�X�V(������)
////************************************************
//void UpdateVisible_Sphere(void)
//{
//	//�Ώە��̒��S��
//	for (int i = 0; i < AMOUNT_SPHERE; i++)
//	{
//		if (!g_aSphere[i].bUse) continue;
//
//		g_aSphere[i].pos = *g_aSphere[i].pPos;
//	}
//}
//
////************************************************
////�X�t�B�A����
////************************************************
//void DisappearVisible_Sphere(D3DXVECTOR3* pPos)
//{
//	for (int i = 0; i < AMOUNT_SPHERE; i++)
//	{
//		//�A�h���X����v����΂��̉e���폜
//		if (g_aSphere[i].pPos == pPos)
//		{
//			g_aSphere[i].bUse = false;
//			break;
//		}
//	}
//}
//
////************************************************
////�X�t�B�A�`��
////************************************************
//void DrawVisible_Sphere(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
//
//	//���C�g���I�t
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
//
//	for (int i = 0; i < AMOUNT_SPHERE; i++)
//	{
//		if (!g_aSphere[i].bUse) continue;
//
//		//���[���h�}�g���b�N�X�̏�����
//		D3DXMatrixIdentity(&g_aSphere[i].mtxWorld);
//
//		//�ʒu�𔽉f1
//		D3DXMatrixTranslation(&mtxTrans,
//			g_aSphere[i].pos.x,
//			g_aSphere[i].pos.y,
//			g_aSphere[i].pos.z);
//
//		//�ʒu�𔽉f2
//		D3DXMatrixMultiply(&g_aSphere[i].mtxWorld,
//			&g_aSphere[i].mtxWorld,
//			&mtxTrans);
//
//		//���[���h�}�g���b�N�X�̐ݒ�
//		pDevice->SetTransform(D3DTS_WORLD, &g_aSphere[i].mtxWorld);
//
//		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//		pDevice->SetStreamSource(0, g_pVtxBuffSphere, 0, sizeof(VERTEX_3D));
//
//		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//		pDevice->SetIndices(g_pIdxBuffSphere);
//
//		//���_�t�H�[�}�b�g�̐ݒ�
//		pDevice->SetFVF(FVF_VERTEX_3D);
//
//		//�X�t�B�A�̕`��
//		pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, i * g_nAmountVtx, 0, g_nAmountVtx,
//			0, g_nAmountPrimitive);
//	}
//
//	//���C�g���I��
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//}