////************************************************
////
////��`�̓����蔻�������[visible_rect.cpp]
////Author�F���c����
////
////************************************************
//#include "visible_rect.h"
//
//#include "player.h"
//
////�}�N����`
//#define AMOUNT_RECT	(128)	//���N�g�̍ő吔
//
////�O���[�o���ϐ�
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//LPDIRECT3DINDEXBUFFER9 g_pIdxBuffRect = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
//Rect g_aRect[AMOUNT_RECT] = {};	//���N�g���
///* 1���N�g������ */
//static const int g_nAmountVtx = 8;	//���_�̐�
//static const int g_nAmountPrimitive = 12;	//�ӂ̐�
//static const int g_nAmountIdx = g_nAmountPrimitive * 2;	//�C���f�b�N�X�̐�
//
////************************************************
////���N�g����
////************************************************
//void InitVisible_Rect(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
//
//	for (int i = 0; i < AMOUNT_RECT; i++)
//	{
//		g_aRect[i].bUse = false;
//		g_aRect[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aRect[i].pPos = NULL;
//		g_aRect[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//	}
//
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nAmountVtx * AMOUNT_RECT,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffRect,
//		NULL);
//
//	//���_���̃|�C���^
//	VERTEX_3D* pVtx;
//
//	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
//	g_pVtxBuffRect->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int i = 0; i < g_nAmountVtx * AMOUNT_RECT; i++)
//	{
//		//���_���W�̐ݒ�
//		pVtx[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//�@���x�N�g���̐ݒ�
//		pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//���_�J���[�̏����ݒ�
//		pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//�e�N�X�`�����W�̏����ݒ�
//		pVtx[i].tex = D3DXVECTOR2(0.0f, 0.0f);
//	}
//
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffRect->Unlock();
//
//	//�C���f�b�N�X�o�b�t�@�̐���
//	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nAmountIdx * AMOUNT_RECT,
//		D3DUSAGE_WRITEONLY,
//		D3DFMT_INDEX16,
//		D3DPOOL_MANAGED,
//		&g_pIdxBuffRect,
//		NULL);
//
//	//�C���f�b�N�X�o�b�t�@�̃|�C���^
//	WORD* pIdx;
//
//	//�C���f�b�N�X�o�b�t�@�����b�N
//	g_pIdxBuffRect->Lock(0, 0, (void**)&pIdx, 0);
//
//	for (int i = 0; i < AMOUNT_RECT; i++)
//	{
//		/* X���ɕ��s�Ȑ������� */
//		for (int j = 0; j < 8; j++, pIdx++)
//		{
//			pIdx[0] = (WORD)j;
//		}
//
//		/* Y���ɕ��s�Ȑ������� */
//		for (int j = 0, k = 0; j < 4; j++, pIdx += 2)
//		{
//			if (j == 2) k += 2;	/* 0,1,4,5�����C�̎n�_�ɂ��邽��3,4�̃C���f�b�N�X���΂� */
//
//			pIdx[0] = (WORD)(j + k);
//			pIdx[1] = (WORD)(j + 2 + k);
//		}
//
//		/* Z���ɕ��s�Ȑ������� */
//		for (int j = 0; j < 4; j++, pIdx += 2)
//		{
//			pIdx[0] = (WORD)(j);
//			pIdx[1] = (WORD)(j + 4);
//		}
//	}
//
//	//�C���f�b�N�X�o�b�t�@���A�����b�N
//	g_pIdxBuffRect->Unlock();
//}
//
////************************************************
////���N�g�W�J
////************************************************
//void SetSizeVisible_Rect(const COLLISION_AABB obj, D3DXCOLOR col, D3DXVECTOR3* pPos)
//{
//	//���_���̃|�C���^
//	VERTEX_3D* pVtx;
//
//	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
//	g_pVtxBuffRect->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int i = 0; i < AMOUNT_RECT; i++, pVtx += g_nAmountVtx)
//	{
//		if (g_aRect[i].bUse) continue;
//
//		g_aRect[i].bUse = true;
//
//		/* �Ώۂ̃��[���h���W�𑊎E�����_��W�J���� */
//		pVtx[0].pos = { obj.min.x - pPos->x, obj.max.y - pPos->y, obj.min.z - pPos->z };
//		pVtx[1].pos = { obj.max.x - pPos->x, obj.max.y - pPos->y, obj.min.z - pPos->z };
//		pVtx[2].pos = { obj.min.x - pPos->x, obj.min.y - pPos->y, obj.min.z - pPos->z };
//		pVtx[3].pos = { obj.max.x - pPos->x, obj.min.y - pPos->y, obj.min.z - pPos->z };
//		pVtx[4].pos = { obj.min.x - pPos->x, obj.max.y - pPos->y, obj.max.z - pPos->z };
//		pVtx[5].pos = { obj.max.x - pPos->x, obj.max.y - pPos->y, obj.max.z - pPos->z };
//		pVtx[6].pos = { obj.min.x - pPos->x, obj.min.y - pPos->y, obj.max.z - pPos->z };
//		pVtx[7].pos = { obj.max.x - pPos->x, obj.min.y - pPos->y, obj.max.z - pPos->z };
//
//		for (int j = 0; j < g_nAmountVtx; j++)
//		{
//			pVtx[j].col = col;
//		}
//
//		/* �Ώۂ̃��[���h���W�ɓ������� */
//		g_aRect[i].pPos = pPos;
//
//		break;
//	}
//
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffRect->Unlock();
//}
//
////************************************************
////���N�g�j��
////************************************************
//void UninitVisible_Rect(void)
//{
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffRect != NULL)
//	{
//		g_pVtxBuffRect->Release();
//		g_pVtxBuffRect = NULL;
//	}
//
//	//�C���f�b�N�X�o�b�t�@�̔j��
//	if (g_pIdxBuffRect != NULL)
//	{
//		g_pIdxBuffRect->Release();
//		g_pIdxBuffRect = NULL;
//	}
//}
//
////************************************************
////���N�g�X�V
////************************************************
//void UpdateVisible_Rect(void)
//{
//	//�Ώە��̒��S��
//	for (int i = 0; i < AMOUNT_RECT; i++)
//	{
//		if (!g_aRect[i].bUse) continue;
//
//		g_aRect[i].pos = *g_aRect[i].pPos;
//	}
//
//	///* ���𑾂����邽��3�������ɏ��������炷 */
//	//g_aRect[1].pos.x += 0.15f;
//	//g_aRect[2].pos.x += -0.15f;
//
//	//g_aRect[3].pos.y += 0.15f;
//	//g_aRect[4].pos.y += -0.15f;
//
//	//g_aRect[5].pos.z += 0.15f;
//	//g_aRect[6].pos.z += -0.15f;
//}
//
////************************************************
////���N�g�`��
////************************************************
//void DrawVisible_Rect(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
//
//	//���C�g���I�t
//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
//
//	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
//
//	for (int i = 0; i < AMOUNT_RECT; i++)
//	{
//		if (!g_aRect[i].bUse) continue;
//
//		//���[���h�}�g���b�N�X�̏�����
//		D3DXMatrixIdentity(&g_aRect[i].mtxWorld);
//
//		//�ʒu�𔽉f1
//		D3DXMatrixTranslation(&mtxTrans,
//			g_aRect[i].pos.x,
//			g_aRect[i].pos.y,
//			g_aRect[i].pos.z);
//
//		//�ʒu�𔽉f2
//		D3DXMatrixMultiply(&g_aRect[i].mtxWorld,
//			&g_aRect[i].mtxWorld,
//			&mtxTrans);
//
//		//���[���h�}�g���b�N�X�̐ݒ�
//		pDevice->SetTransform(D3DTS_WORLD, &g_aRect[i].mtxWorld);
//
//		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//		pDevice->SetStreamSource(0, g_pVtxBuffRect, 0, sizeof(VERTEX_3D));
//
//		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//		pDevice->SetIndices(g_pIdxBuffRect);
//
//		//���_�t�H�[�}�b�g�̐ݒ�
//		pDevice->SetFVF(FVF_VERTEX_3D);
//
//		//�e�N�X�`���̐ݒ�
//		//pDevice->SetTexture(0, NULL);
//
//		//���N�g�̕`��
//		pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, i * g_nAmountVtx, 0, g_nAmountVtx,
//			0, g_nAmountPrimitive);
//	}
//
//	//���C�g���I��
//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
//}