//************************************************
//
//���ΏۃQ�[�W����[gauge_tower.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "gauge_tower.h"
#include "tower.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Gauge_Tower[AMOUNT_TEX_GAUGE_TOWER] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Gauge_Tower = NULL;	//���_�o�b�t�@�̃|�C���^
GAUGE_TOWER g_aGauge_Tower[AMOUNT_POLYGON_GAUGE_TOWER];	//���ΏۃQ�[�W���
static int g_nHold;	//�ėp�����ۊǗp

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Gauge_Tower()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAUGE_TOWER,
		&g_pTexture_Gauge_Tower[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GAUGE_HEART,
		&g_pTexture_Gauge_Tower[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_GAUGE_TOWER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Gauge_Tower,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Gauge_Tower;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Gauge_Tower->Lock(0, 0, (void**)&pVtx_Gauge_Tower, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Gauge_Tower[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Gauge_Tower[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Gauge_Tower[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Gauge_Tower[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Gauge_Tower[0].rhw = 1.0f;
		pVtx_Gauge_Tower[1].rhw = 1.0f;
		pVtx_Gauge_Tower[2].rhw = 1.0f;
		pVtx_Gauge_Tower[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Gauge_Tower[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Gauge_Tower[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Gauge_Tower[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Gauge_Tower[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Gauge_Tower[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Gauge_Tower[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Gauge_Tower[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Gauge_Tower[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Gauge_Tower += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Gauge_Tower->Unlock();

	//���ΏۃQ�[�W�\���̂̏��̏������Q
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		g_aGauge_Tower[nCnt].nStyle = 0;
		g_aGauge_Tower[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge_Tower[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge_Tower[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGauge_Tower[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aGauge_Tower[nCnt].nCntTex = 0;
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aGauge_Tower[nCnt].fTexSpan[nCnt2] = 0.0f;
			g_aGauge_Tower[nCnt].fRadius[nCnt2] = 0.0f;
			g_aGauge_Tower[nCnt].fLength[nCnt2] = 0.0f;
			g_aGauge_Tower[nCnt].fAngle[nCnt2] = 0.0f;
		}
	}

	g_nHold = AMOUNT_MAX_LIFE_TOWER;

	//���ΏۃQ�[�W�\���̂ɏ���t�^
	SetInfo_Gauge_Tower();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Gauge_Tower(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEX_GAUGE_TOWER; nCnt++)
	{
		if (g_pTexture_Gauge_Tower[nCnt] != NULL)
		{
			g_pTexture_Gauge_Tower[nCnt]->Release();
			g_pTexture_Gauge_Tower[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Gauge_Tower != NULL)
	{
		g_pVtxBuff_Gauge_Tower->Release();
		g_pVtxBuff_Gauge_Tower = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Gauge_Tower(void)
{
	TOWER* pTower = GetInfo_Tower();

	//�ړ��Ȃ�
	Update_Pos_Gauge_Tower();

	//�e�N�X�`���A�j���[�V����
	Update_Tex_Gauge_Tower();

	//�J���[�ύX
	Update_Col_Gauge_Tower();

	//�O��̎��Ώۂ�ێ�
	g_nHold = pTower->nLife;
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Gauge_Tower(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Gauge_Tower, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexture_Gauge_Tower[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//���ΏۃQ�[�W�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Gauge_Tower(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		g_aGauge_Tower[nCnt].nStyle = nCnt;
		g_aGauge_Tower[nCnt].pos = D3DXVECTOR3(800.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_X), 110.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_Y), 0.0f);
		g_aGauge_Tower[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		switch (g_aGauge_Tower[nCnt].nStyle)
		{
		case GAUGE_TOWER_STYLE_GAUGE:
			g_aGauge_Tower[nCnt].fTexSpan[0] = 0.0f;
			g_aGauge_Tower[nCnt].fTexSpan[1] = SPAN_CHANGE_TEX_GAUGE_TOWER;
			g_aGauge_Tower[nCnt].fRadius[0] = RADIUS_GAUGE_TOWER_X;	//���ΏۃQ�[�W������
			g_aGauge_Tower[nCnt].fRadius[1] = RADIUS_GAUGE_TOWER_Y;	//���ΏۃQ�[�W�c����
			for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
			{
				g_aGauge_Tower[nCnt].fLength[nCnt2] = sqrtf((g_aGauge_Tower[nCnt].fRadius[0] * g_aGauge_Tower[nCnt].fRadius[0]) + (g_aGauge_Tower[nCnt].fRadius[1] * g_aGauge_Tower[nCnt].fRadius[1]));
				g_aGauge_Tower[nCnt].fAngle[nCnt2] = atan2f(g_aGauge_Tower[nCnt].fRadius[0] * 2.0f, g_aGauge_Tower[nCnt].fRadius[1] * 2.0f);
			}
			break;
		case GAUGE_TOWER_STYLE_HEART:
			g_aGauge_Tower[nCnt].fTexSpan[0] = 0.0f;
			g_aGauge_Tower[nCnt].fTexSpan[1] = 1.0f;
			g_aGauge_Tower[nCnt].fRadius[0] = RADIUS_GAUGE_HEART_X;	//���Ώۃn�[�g������
			g_aGauge_Tower[nCnt].fRadius[1] = RADIUS_GAUGE_HEART_Y;	//���Ώۃn�[�g�c����
			for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
			{
				g_aGauge_Tower[nCnt].fLength[nCnt2] = sqrtf((g_aGauge_Tower[nCnt].fRadius[0] * g_aGauge_Tower[nCnt].fRadius[0]) + (g_aGauge_Tower[nCnt].fRadius[1] * g_aGauge_Tower[nCnt].fRadius[1]));
				g_aGauge_Tower[nCnt].fAngle[nCnt2] = atan2f(g_aGauge_Tower[nCnt].fRadius[0] * 2.0f, g_aGauge_Tower[nCnt].fRadius[1] * 2.0f);
			}
			break;
		}
	}
}

//************************************************
//���ΏۃQ�[�W�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Gauge_Tower(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Gauge_Tower;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Gauge_Tower->Lock(0, 0, (void**)&pVtx_Gauge_Tower, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		//�F�̕ύX���Ԃɏ悶�Ă���������U��
		if (g_aGauge_Tower[nCnt].nCntTex > 0)
		{
			//�K���Ɉʒu��ύX
			int X = rand() % 25, Y = rand() % 25, RX = rand() % 2, RY = rand() % 2;
			//�㉺���E�̈ړ��������_���ɔ��]
			RX == 0 ? 0 : X *= -1;
			RY == 0 ? 0 : Y *= -1;
			g_aGauge_Tower[nCnt].pos = D3DXVECTOR3(800.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_X) + X, 110.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_Y) + Y, 0.0f);
		}
		//���ԈȊO�͒�ʒu��
		else
		{
			g_aGauge_Tower[nCnt].pos = D3DXVECTOR3(800.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_X), 110.0f - (nCnt * SPAN_EACH_GAUGE_TOWER_Y), 0.0f);
		}

		pVtx_Gauge_Tower[0].pos.x = g_aGauge_Tower[nCnt].pos.x + sinf(g_aGauge_Tower[nCnt].rot.z - (D3DX_PI - g_aGauge_Tower[nCnt].fAngle[0])) * g_aGauge_Tower[nCnt].fLength[0];
		pVtx_Gauge_Tower[0].pos.y = g_aGauge_Tower[nCnt].pos.y + cosf(g_aGauge_Tower[nCnt].rot.z - (D3DX_PI - g_aGauge_Tower[nCnt].fAngle[0])) * g_aGauge_Tower[nCnt].fLength[0];
		pVtx_Gauge_Tower[1].pos.x = g_aGauge_Tower[nCnt].pos.x + sinf(g_aGauge_Tower[nCnt].rot.z + (D3DX_PI - g_aGauge_Tower[nCnt].fAngle[0])) * g_aGauge_Tower[nCnt].fLength[0];
		pVtx_Gauge_Tower[1].pos.y = g_aGauge_Tower[nCnt].pos.y + cosf(g_aGauge_Tower[nCnt].rot.z + (D3DX_PI - g_aGauge_Tower[nCnt].fAngle[0])) * g_aGauge_Tower[nCnt].fLength[0];
		pVtx_Gauge_Tower[2].pos.x = g_aGauge_Tower[nCnt].pos.x + sinf(g_aGauge_Tower[nCnt].rot.z - g_aGauge_Tower[nCnt].fAngle[1]) * g_aGauge_Tower[nCnt].fLength[1];
		pVtx_Gauge_Tower[2].pos.y = g_aGauge_Tower[nCnt].pos.y + cosf(g_aGauge_Tower[nCnt].rot.z - g_aGauge_Tower[nCnt].fAngle[1]) * g_aGauge_Tower[nCnt].fLength[1];
		pVtx_Gauge_Tower[3].pos.x = g_aGauge_Tower[nCnt].pos.x + sinf(g_aGauge_Tower[nCnt].rot.z + g_aGauge_Tower[nCnt].fAngle[1]) * g_aGauge_Tower[nCnt].fLength[1];
		pVtx_Gauge_Tower[3].pos.y = g_aGauge_Tower[nCnt].pos.y + cosf(g_aGauge_Tower[nCnt].rot.z + g_aGauge_Tower[nCnt].fAngle[1]) * g_aGauge_Tower[nCnt].fLength[1];

		pVtx_Gauge_Tower += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Gauge_Tower->Unlock();
}

//************************************************
//�Q�[�W�̐F��ύX����֐�
//************************************************
void Update_Col_Gauge_Tower(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Gauge_Tower;

	TOWER* pTower = GetInfo_Tower();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Gauge_Tower->Lock(0, 0, (void**)&pVtx_Gauge_Tower, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		//�̗͂ɕϓ��������
		if (g_nHold != pTower->nLife)
		{
			//�ύX���Ԃ�t�^
			g_aGauge_Tower[nCnt].nCntTex = 8;
		}

		//���Ԓ����������ɖ���
		if (g_aGauge_Tower[nCnt].nCntTex > 0)
		{
			g_aGauge_Tower[nCnt].nCntTex--;

			if (g_aGauge_Tower[nCnt].nCntTex < 4)
			{
				g_aGauge_Tower[nCnt].col.r = 0.0f;
			}
			g_aGauge_Tower[nCnt].col.g = 0.0f;
			g_aGauge_Tower[nCnt].col.b = 0.0f;
		}
		//�I���Ɩ߂�
		else
		{
			g_aGauge_Tower[nCnt].col.r = 1.0f;
			g_aGauge_Tower[nCnt].col.g = 1.0f;
			g_aGauge_Tower[nCnt].col.b = 1.0f;
		}

		pVtx_Gauge_Tower[0].col = g_aGauge_Tower[nCnt].col;
		pVtx_Gauge_Tower[1].col = g_aGauge_Tower[nCnt].col;
		pVtx_Gauge_Tower[2].col = g_aGauge_Tower[nCnt].col;
		pVtx_Gauge_Tower[3].col = g_aGauge_Tower[nCnt].col;

		pVtx_Gauge_Tower += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Gauge_Tower->Unlock();
}

//************************************************
//���ΏۃQ�[�W�̃e�N�X�`���𓮂����֐�
//************************************************
void Update_Tex_Gauge_Tower(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Gauge_Tower;

	TOWER* pTower = GetInfo_Tower();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Gauge_Tower->Lock(0, 0, (void**)&pVtx_Gauge_Tower, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAUGE_TOWER; nCnt++)
	{
		if (g_aGauge_Tower[nCnt].nStyle == GAUGE_TOWER_STYLE_GAUGE)
		{
			g_aGauge_Tower[nCnt].fTexSpan[0] = 1.0f - (SPAN_CHANGE_TEX_GAUGE_TOWER * (pTower->nLife + 1));
			g_aGauge_Tower[nCnt].fTexSpan[1] = 1.0f - (SPAN_CHANGE_TEX_GAUGE_TOWER * pTower->nLife);
		}

		pVtx_Gauge_Tower[0].tex = D3DXVECTOR2(0.0f, g_aGauge_Tower[nCnt].fTexSpan[0]);
		pVtx_Gauge_Tower[1].tex = D3DXVECTOR2(1.0f, g_aGauge_Tower[nCnt].fTexSpan[0]);
		pVtx_Gauge_Tower[2].tex = D3DXVECTOR2(0.0f, g_aGauge_Tower[nCnt].fTexSpan[1]);
		pVtx_Gauge_Tower[3].tex = D3DXVECTOR2(1.0f, g_aGauge_Tower[nCnt].fTexSpan[1]);

		pVtx_Gauge_Tower += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Gauge_Tower->Unlock();
}

//************************************************
//���ΏۃQ�[�W�\���̂̃A�h���X��n��
//************************************************
GAUGE_TOWER* GetInfo_Gauge_Tower(void)
{
	return &g_aGauge_Tower[0];
}