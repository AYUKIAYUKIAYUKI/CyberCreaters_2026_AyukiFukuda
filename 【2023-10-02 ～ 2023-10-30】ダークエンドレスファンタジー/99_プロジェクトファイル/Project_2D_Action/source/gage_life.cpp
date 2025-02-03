////************************************************
////
////���C�t�Q�[�W����[gage_life.cpp]
////Author�F���c����
////
////************************************************
//#include "main.h"
//#include "player.h"
//#include "gage_life.h"
//
////�O���[�o���ϐ�
//LPDIRECT3DTEXTURE9 g_pTexture_Gage_Life[AMOUNT_TEX_GAGE_LIFE] = {};	//�e�N�X�`���̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Gage_Life = NULL;	//���_�o�b�t�@�̃|�C���^
//GAGE_LIFE g_aGage_Life[AMOUNT_POLYGON_GAGE_LIFE];	//���C�t�Q�[�W���
//static int g_nHold;	//�ėp�����ۊǗp
//
////************************************************
////�|���S�������������֐�
////************************************************
//void Init_Gage_Life()
//{
//	//�f�o�C�X�ւ̃|�C���^
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//�f�o�C�X�ւ̎擾
//	pDevice = GetDevice();
//
//	//�e�N�X�`���̓Ǎ���
//	D3DXCreateTextureFromFile(pDevice,
//		TEXTURE_GAGE_LIFE,
//		&g_pTexture_Gage_Life[0]);
//
//	//�e�N�X�`���̓Ǎ���
//	D3DXCreateTextureFromFile(pDevice,
//		TEXTURE_GAGE_HEART,
//		&g_pTexture_Gage_Life[1]);
//
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_GAGE_LIFE,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuff_Gage_Life,
//		NULL);
//
//	//���_���ւ̃|�C���^
//	VERTEX_2D* pVtx_Gage_Life;
//
//	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
//	g_pVtxBuff_Gage_Life->Lock(0, 0, (void**)&pVtx_Gage_Life, 0);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		//���_���W�̏����ݒ�
//		pVtx_Gage_Life[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx_Gage_Life[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx_Gage_Life[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx_Gage_Life[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//������̊g�嗦(?)�̏����ݒ�
//		pVtx_Gage_Life[0].rhw = 1.0f;
//		pVtx_Gage_Life[1].rhw = 1.0f;
//		pVtx_Gage_Life[2].rhw = 1.0f;
//		pVtx_Gage_Life[3].rhw = 1.0f;
//
//		//���_�J���[�̏����ݒ�
//		pVtx_Gage_Life[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx_Gage_Life[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx_Gage_Life[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx_Gage_Life[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//�e�N�X�`�����W�̏����ݒ�
//		pVtx_Gage_Life[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx_Gage_Life[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx_Gage_Life[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx_Gage_Life[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx_Gage_Life += AMOUNT_VTX;
//	}
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuff_Gage_Life->Unlock();
//
//	//���C�t�Q�[�W�\���̂̏��̏������Q
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		g_aGage_Life[nCnt].nStyle = 0;
//		g_aGage_Life[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aGage_Life[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aGage_Life[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aGage_Life[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//		g_aGage_Life[nCnt].nCntTex = 0;
//		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
//		{
//			g_aGage_Life[nCnt].fTexSpan[nCnt2] = 0.0f;
//			g_aGage_Life[nCnt].fRadius[nCnt2] = 0.0f;
//			g_aGage_Life[nCnt].fLength[nCnt2] = 0.0f;
//			g_aGage_Life[nCnt].fAngle[nCnt2] = 0.0f;
//		}
//	}
//
//	g_nHold = AMOUNT_MAX_LIFE_PLAYER;
//
//	//���C�t�Q�[�W�\���̂ɏ���t�^
//	SetInfo_Gage_Life();
//}
//
////************************************************
////�|���S���I�������֐�
////************************************************
//void Uninit_Gage_Life(void)
//{
//	//�e�N�X�`���̔j��
//	for (int nCnt = 0; nCnt < AMOUNT_TEX_GAGE_LIFE; nCnt++)
//	{
//		if (g_pTexture_Gage_Life[nCnt] != NULL)
//		{
//			g_pTexture_Gage_Life[nCnt]->Release();
//			g_pTexture_Gage_Life[nCnt] = NULL;
//		}
//	}
//
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuff_Gage_Life != NULL)
//	{
//		g_pVtxBuff_Gage_Life->Release();
//		g_pVtxBuff_Gage_Life = NULL;
//	}
//}
//
////************************************************
////�|���S���X�V�����֐�
////************************************************
//void Update_Gage_Life(void)
//{
//	PLAYER* pPlayer = GetInfo_Player();
//
//	//�ړ��Ȃ�
//	Update_Pos_Gage_Life();
//
//	//�e�N�X�`���A�j���[�V����
//	Update_Tex_Gage_Life();
//
//	//�J���[�ύX
//	Update_Col_Gage_Life();
//
//	//�O��̃��C�t��ێ�
//	g_nHold = pPlayer->nLife;
//}
//
////************************************************
////�|���S���`�揈���֐�
////************************************************
//void Draw_Gage_Life(void)
//{
//	//�f�o�C�X�ւ̃|�C���^
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//�f�o�C�X�ւ̃|�C���^�擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuff_Gage_Life, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		//�e�N�X�`���̐ݒ�
//		pDevice->SetTexture(0, g_pTexture_Gage_Life[nCnt]);
//
//		//�|���S���̕`��
//		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
//	}
//}
//
////************************************************
////���C�t�Q�[�W�\���̂̏���ݒ肷��֐�
////************************************************
//void SetInfo_Gage_Life(void)
//{
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		g_aGage_Life[nCnt].nStyle = nCnt;
//		g_aGage_Life[nCnt].pos = D3DXVECTOR3(350.0f - (nCnt * SPAN_EACH_GAGE_LIFE_X), 1000.0f - (nCnt * SPAN_EACH_GAGE_LIFE_Y), 0.0f);
//		g_aGage_Life[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		switch (g_aGage_Life[nCnt].nStyle)
//		{
//		case GAGE_LIFE_STYLE_GAGE:
//			g_aGage_Life[nCnt].fTexSpan[0] = 0.0f;
//			g_aGage_Life[nCnt].fTexSpan[1] = SPAN_CHANGE_TEX_GAGE_LIFE;
//			g_aGage_Life[nCnt].fRadius[0] = RADIUS_GAGE_LIFE_X;	//���C�t�Q�[�W������
//			g_aGage_Life[nCnt].fRadius[1] = RADIUS_GAGE_LIFE_Y;	//���C�t�Q�[�W�c����
//			for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
//			{
//				g_aGage_Life[nCnt].fLength[nCnt2] = sqrtf((g_aGage_Life[nCnt].fRadius[0] * g_aGage_Life[nCnt].fRadius[0]) + (g_aGage_Life[nCnt].fRadius[1] * g_aGage_Life[nCnt].fRadius[1]));
//				g_aGage_Life[nCnt].fAngle[nCnt2] = atan2f(g_aGage_Life[nCnt].fRadius[0] * 2.0f, g_aGage_Life[nCnt].fRadius[1] * 2.0f);
//			}
//			break;
//		case GAGE_LIFE_STYLE_HEART:
//			g_aGage_Life[nCnt].fTexSpan[0] = 0.0f;
//			g_aGage_Life[nCnt].fTexSpan[1] = 1.0f;
//			g_aGage_Life[nCnt].fRadius[0] = RADIUS_GAGE_HEART_X;	//���C�t�n�[�g������
//			g_aGage_Life[nCnt].fRadius[1] = RADIUS_GAGE_HEART_Y;	//���C�t�n�[�g�c����
//			for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
//			{
//				g_aGage_Life[nCnt].fLength[nCnt2] = sqrtf((g_aGage_Life[nCnt].fRadius[0] * g_aGage_Life[nCnt].fRadius[0]) + (g_aGage_Life[nCnt].fRadius[1] * g_aGage_Life[nCnt].fRadius[1]));
//				g_aGage_Life[nCnt].fAngle[nCnt2] = atan2f(g_aGage_Life[nCnt].fRadius[0] * 2.0f, g_aGage_Life[nCnt].fRadius[1] * 2.0f);
//			}
//			break;
//		}
//	}
//}
//
////************************************************
////���C�t�Q�[�W�̈ʒu��ݒ肷��֐�
////************************************************
//void Update_Pos_Gage_Life(void)
//{
//	//���_���ւ̃|�C���^
//	VERTEX_2D* pVtx_Gage_Life;
//
//	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
//	g_pVtxBuff_Gage_Life->Lock(0, 0, (void**)&pVtx_Gage_Life, 0);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		//�F�̕ύX���Ԃɏ悶�Ă���������U��
//		if (g_aGage_Life[nCnt].nCntTex > 0)
//		{
//			//�K���Ɉʒu��ύX
//			int X = rand() % 25, Y = rand() % 25, RX = rand() % 2, RY = rand() % 2;
//			//�㉺���E�̈ړ��������_���ɔ��]
//			RX == 0 ? 0 : X *= -1;
//			RY == 0 ? 0 : Y *= -1;
//			g_aGage_Life[nCnt].pos = D3DXVECTOR3(350.0f - (nCnt * SPAN_EACH_GAGE_LIFE_X) + X, 1000.0f - (nCnt * SPAN_EACH_GAGE_LIFE_Y) + Y, 0.0f);
//		}
//		//���ԈȊO�͒�ʒu��
//		else
//		{
//			g_aGage_Life[nCnt].pos = D3DXVECTOR3(350.0f - (nCnt * SPAN_EACH_GAGE_LIFE_X), 1000.0f - (nCnt * SPAN_EACH_GAGE_LIFE_Y), 0.0f);
//		}
//
//		pVtx_Gage_Life[0].pos.x = g_aGage_Life[nCnt].pos.x + sinf(g_aGage_Life[nCnt].rot.z - (D3DX_PI - g_aGage_Life[nCnt].fAngle[0])) * g_aGage_Life[nCnt].fLength[0];
//		pVtx_Gage_Life[0].pos.y = g_aGage_Life[nCnt].pos.y + cosf(g_aGage_Life[nCnt].rot.z - (D3DX_PI - g_aGage_Life[nCnt].fAngle[0])) * g_aGage_Life[nCnt].fLength[0];
//		pVtx_Gage_Life[1].pos.x = g_aGage_Life[nCnt].pos.x + sinf(g_aGage_Life[nCnt].rot.z + (D3DX_PI - g_aGage_Life[nCnt].fAngle[0])) * g_aGage_Life[nCnt].fLength[0];
//		pVtx_Gage_Life[1].pos.y = g_aGage_Life[nCnt].pos.y + cosf(g_aGage_Life[nCnt].rot.z + (D3DX_PI - g_aGage_Life[nCnt].fAngle[0])) * g_aGage_Life[nCnt].fLength[0];
//		pVtx_Gage_Life[2].pos.x = g_aGage_Life[nCnt].pos.x + sinf(g_aGage_Life[nCnt].rot.z - g_aGage_Life[nCnt].fAngle[1]) * g_aGage_Life[nCnt].fLength[1];
//		pVtx_Gage_Life[2].pos.y = g_aGage_Life[nCnt].pos.y + cosf(g_aGage_Life[nCnt].rot.z - g_aGage_Life[nCnt].fAngle[1]) * g_aGage_Life[nCnt].fLength[1];
//		pVtx_Gage_Life[3].pos.x = g_aGage_Life[nCnt].pos.x + sinf(g_aGage_Life[nCnt].rot.z + g_aGage_Life[nCnt].fAngle[1]) * g_aGage_Life[nCnt].fLength[1];
//		pVtx_Gage_Life[3].pos.y = g_aGage_Life[nCnt].pos.y + cosf(g_aGage_Life[nCnt].rot.z + g_aGage_Life[nCnt].fAngle[1]) * g_aGage_Life[nCnt].fLength[1];
//
//		pVtx_Gage_Life += AMOUNT_VTX;
//	}
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuff_Gage_Life->Unlock();
//}
//
////************************************************
////�Q�[�W�̐F��ύX����֐�
////************************************************
//void Update_Col_Gage_Life(void)
//{
//	//���_���ւ̃|�C���^
//	VERTEX_2D* pVtx_Gage_Life;
//
//	PLAYER* pPlayer = GetInfo_Player();
//
//	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
//	g_pVtxBuff_Gage_Life->Lock(0, 0, (void**)&pVtx_Gage_Life, 0);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		//�̗͂ɕϓ��������
//		if (g_nHold != pPlayer->nLife)
//		{
//			//�ύX���Ԃ�t�^
//			g_aGage_Life[nCnt].nCntTex = 8;
//		}
//
//		//���Ԓ����������ɖ���
//		if (g_aGage_Life[nCnt].nCntTex > 0)
//		{
//			g_aGage_Life[nCnt].nCntTex--;
//
//			if (g_aGage_Life[nCnt].nCntTex < 4)
//			{
//				g_aGage_Life[nCnt].col.r = 0.0f;
//			}
//			g_aGage_Life[nCnt].col.g = 0.0f;
//			g_aGage_Life[nCnt].col.b = 0.0f;
//		}
//		//�I���Ɩ߂�
//		else
//		{
//			g_aGage_Life[nCnt].col.r = 1.0f;
//			g_aGage_Life[nCnt].col.g = 1.0f;
//			g_aGage_Life[nCnt].col.b = 1.0f;
//		}
//
//		pVtx_Gage_Life[0].col = g_aGage_Life[nCnt].col;
//		pVtx_Gage_Life[1].col = g_aGage_Life[nCnt].col;
//		pVtx_Gage_Life[2].col = g_aGage_Life[nCnt].col;
//		pVtx_Gage_Life[3].col = g_aGage_Life[nCnt].col;
//
//		pVtx_Gage_Life += AMOUNT_VTX;
//	}
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuff_Gage_Life->Unlock();
//}
//
////************************************************
////���C�t�Q�[�W�̃e�N�X�`���𓮂����֐�
////************************************************
//void Update_Tex_Gage_Life(void)
//{
//	//���_���ւ̃|�C���^
//	VERTEX_2D* pVtx_Gage_Life;
//
//	PLAYER* pPlayer = GetInfo_Player();
//
//	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
//	g_pVtxBuff_Gage_Life->Lock(0, 0, (void**)&pVtx_Gage_Life, 0);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		if (g_aGage_Life[nCnt].nStyle == GAGE_LIFE_STYLE_GAGE)
//		{
//			g_aGage_Life[nCnt].fTexSpan[0] = 1.0f - (SPAN_CHANGE_TEX_GAGE_LIFE * (pPlayer->nLife + 1));
//			g_aGage_Life[nCnt].fTexSpan[1] = 1.0f - (SPAN_CHANGE_TEX_GAGE_LIFE * pPlayer->nLife);
//		}
//
//		pVtx_Gage_Life[0].tex = D3DXVECTOR2(0.0f, g_aGage_Life[nCnt].fTexSpan[0]);
//		pVtx_Gage_Life[1].tex = D3DXVECTOR2(1.0f, g_aGage_Life[nCnt].fTexSpan[0]);
//		pVtx_Gage_Life[2].tex = D3DXVECTOR2(0.0f, g_aGage_Life[nCnt].fTexSpan[1]);
//		pVtx_Gage_Life[3].tex = D3DXVECTOR2(1.0f, g_aGage_Life[nCnt].fTexSpan[1]);
//
//		pVtx_Gage_Life += AMOUNT_VTX;
//	}
//
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuff_Gage_Life->Unlock();
//}
//
////************************************************
////���C�t�Q�[�W�\���̂̃A�h���X��n��
////************************************************
//GAGE_LIFE* GetInfo_Gage_Life(void)
//{
//	return &g_aGage_Life[0];
//}