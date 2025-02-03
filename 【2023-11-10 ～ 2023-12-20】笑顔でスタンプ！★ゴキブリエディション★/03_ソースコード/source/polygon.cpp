////************************************************
////
////�|���S������[polygon.cpp]
////Author�F���c����
////
////************************************************
//#include "polygon.h"
//
////�}�N����`
//#define AMOUNT_POLYGON	(1)
//
////�O���[�o���ϐ�
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;	//�e�N�X�`���ւ̃|�C���^
//Polygon g_aPolygon[AMOUNT_POLYGON] = {};
//
////************************************************
////�|���S������
////************************************************
//void InitPolygon(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
//
//	//�|���S����񏉊���
//	for (int i = 0; i < AMOUNT_POLYGON; i++)
//	{
//		g_aPolygon[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aPolygon[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	}
//
//	//�e�N�X�`���̓Ǎ���
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\texture\\dain.png",
//		&g_pTexturePolygon);
//
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_POLYGON,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_3D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffPolygon,
//		NULL);
//
//	//���_���̃|�C���^
//	VERTEX_3D* pVtx;
//
//	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
//	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int i = 0; i < AMOUNT_POLYGON; i++)
//	{
//		//���_���W�̐ݒ�
//		pVtx[0].pos = D3DXVECTOR3(-25.0f, 0.0f, 25.0f);
//		pVtx[1].pos = D3DXVECTOR3(25.0f, 0.0f, 25.0f);
//		pVtx[2].pos = D3DXVECTOR3(-25.0f, 0.0f, -25.0f);
//		pVtx[3].pos = D3DXVECTOR3(25.0f, 0.0f, -25.0f);
//
//		//�@���x�N�g���̐ݒ�
//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		//���_�J���[�̏����ݒ�
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//�e�N�X�`�����W�̏����ݒ�
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += AMOUNT_VTX;
//	}
//
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffPolygon->Unlock();
//}
//
////************************************************
////�|���S���j��
////************************************************
//void UninitPolygon(void)
//{
//	//�e�N�X�`���̔j��
//	if (g_pTexturePolygon != NULL)
//	{
//		g_pTexturePolygon->Release();
//		g_pTexturePolygon = NULL;
//	}
//
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffPolygon != NULL)
//	{
//		g_pVtxBuffPolygon->Release();
//		g_pVtxBuffPolygon = NULL;
//	}
//}
//
////************************************************
////�|���S���X�V
////************************************************
//void UpdatePolygon(void)
//{
//	
//}
//
////************************************************
////�|���S���`��
////************************************************
//void DrawPolygon(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
//
//	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
//	
//	for (int i = 0; i < AMOUNT_POLYGON; i++)
//	{
//		//���[���h�}�g���b�N�X�̏�����
//		D3DXMatrixIdentity(&g_aPolygon[i].mtxWorld);
//
//		//�����𔽉f1
//		D3DXMatrixRotationYawPitchRoll(&mtxRot,
//			g_aPolygon[i].rot.y,
//			g_aPolygon[i].rot.x,
//			g_aPolygon[i].rot.z);
//
//		//�����𔽉f2
//		D3DXMatrixMultiply(&g_aPolygon[i].mtxWorld,
//			&g_aPolygon[i].mtxWorld,
//			&mtxRot);
//
//		//�ʒu�𔽉f1
//		D3DXMatrixTranslation(&mtxTrans,
//			g_aPolygon[i].pos.x,
//			g_aPolygon[i].pos.y,
//			g_aPolygon[i].pos.z);
//
//		//�ʒu�𔽉f2
//		D3DXMatrixMultiply(&g_aPolygon[i].mtxWorld,
//			&g_aPolygon[i].mtxWorld,
//			&mtxTrans);
//
//		//���[���h�}�g���b�N�X�̐ݒ�
//		pDevice->SetTransform(D3DTS_WORLD, &g_aPolygon[i].mtxWorld);
//
//		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//		pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));
//
//		//���_�t�H�[�}�b�g�̐ݒ�
//		pDevice->SetFVF(FVF_VERTEX_3D);
//
//		//�e�N�X�`���̐ݒ�
//		pDevice->SetTexture(0, g_pTexturePolygon);
//
//		//�|���S���̕`��
//		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
//	}
//}