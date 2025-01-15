//************************************************
//
//�������ԏ���[timer.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "input.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Timer = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Timer = NULL;	//���_�o�b�t�@�̃|�C���^
TIMER g_aTimer[AMOUNT_POLYGON_TIMER];	//�^�C�}�[�\���p
int g_nTimer = 0;	//�^�C�}�[
int g_nFrameCnt = 0;	//�t���[���J�E���g

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Timer(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TIMER,
		&g_pTexture_Timer);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Timer,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Timer;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Timer->Lock(0, 0, (void**)&pVtx_Timer, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TIMER; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Timer[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Timer[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Timer[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Timer[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Timer[0].rhw = 1.0f;
		pVtx_Timer[1].rhw = 1.0f;
		pVtx_Timer[2].rhw = 1.0f;
		pVtx_Timer[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Timer[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Timer[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Timer[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Timer[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Timer[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Timer[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Timer[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Timer[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Timer += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Timer->Unlock();

	//�^�C�}�[�\���p�N���A
	for (int i = 0; i < AMOUNT_POLYGON_TIMER; i++)
	{
		g_aTimer[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTimer[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTimer[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTimer[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aTimer[i].nCntTex = 0;
		g_aTimer[i].nCntPattern = 0;
		for (int ii = 0; ii < AMOUNT_POLYGON_TIMER; ii++)
		{
			g_aTimer[i].fTexSpan[ii] = 0.0f;
			g_aTimer[i].fRadius[ii] = 0.0f;
			g_aTimer[i].fLength[ii] = 0.0f;
			g_aTimer[i].fAngle[ii] = 0.0f;
		}
	}

	//�^�C�}�[�N���A
	g_nTimer = 0;

	//�t���[���N���A
	g_nFrameCnt = 0;

	//�^�C�}�[�ɏ���t�^
	SetInfo_Timer();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Timer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Timer != NULL)
	{
		g_pTexture_Timer->Release();
		g_pTexture_Timer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Timer != NULL)
	{
		g_pVtxBuff_Timer->Release();
		g_pVtxBuff_Timer = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Timer(void)
{
	//60�t���[���o�߂�1�b���炷
	g_nFrameCnt++;
	if (g_nFrameCnt >= 60)
	{
		g_nFrameCnt = 0;
		g_nTimer--;
	}

	//�W�J
	Update_Pos_Timer();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Timer(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Timer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TIMER; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexture_Timer);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�^�C�}�[�\���p�Ƀf�[�^��t�^����֐�
//************************************************
void SetInfo_Timer(void)
{
	//�^�C�}�[�Z�b�g
	g_nTimer = 90;

	for (int i = 0; i < AMOUNT_POLYGON_TIMER; i++)
	{
		g_aTimer[i].pos = D3DXVECTOR3(100.0f + (55.0f * i), 100.0f, 0.0f);
		if (i > 1)
		{
			g_aTimer[i].pos.x += 40.0f;
		}
		g_aTimer[i].fTexSpan[0] = 0.0f;
		g_aTimer[i].fTexSpan[1] = 0.1f;
		g_aTimer[i].fRadius[0] = 25.0f;
		g_aTimer[i].fRadius[1] = 45.0f;
		g_aTimer[i].fLength[0] = sqrtf((g_aTimer[i].fRadius[0] * g_aTimer[i].fRadius[0]) + (g_aTimer[i].fRadius[1] * g_aTimer[i].fRadius[1]));
		g_aTimer[i].fLength[1] = g_aTimer[i].fLength[0];
		g_aTimer[i].fAngle[0] = atan2f(g_aTimer[i].fRadius[0] * 2.0f, g_aTimer[i].fRadius[1] * 2.0f);
		g_aTimer[i].fAngle[1] = g_aTimer[i].fAngle[0];
	}
}

//************************************************
//�^�C�}�[�\���p�Ƀo�[�e�b�N�X���X�V�֐�
//************************************************
void Update_Pos_Timer(void)
{
	//�e�N�X�`�����X�V
	Update_Tex_Timer();

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Timer;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Timer->Lock(0, 0, (void**)&pVtx_Timer, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TIMER; i++)
	{
		pVtx_Timer[0].pos.x = g_aTimer[i].pos.x + sinf(g_aTimer[i].rot.z - (D3DX_PI - g_aTimer[i].fAngle[0])) * g_aTimer[i].fLength[0];
		pVtx_Timer[0].pos.y = g_aTimer[i].pos.y + cosf(g_aTimer[i].rot.z - (D3DX_PI - g_aTimer[i].fAngle[0])) * g_aTimer[i].fLength[0];
		pVtx_Timer[1].pos.x = g_aTimer[i].pos.x + sinf(g_aTimer[i].rot.z + (D3DX_PI - g_aTimer[i].fAngle[0])) * g_aTimer[i].fLength[0];
		pVtx_Timer[1].pos.y = g_aTimer[i].pos.y + cosf(g_aTimer[i].rot.z + (D3DX_PI - g_aTimer[i].fAngle[0])) * g_aTimer[i].fLength[0];
		pVtx_Timer[2].pos.x = g_aTimer[i].pos.x + sinf(g_aTimer[i].rot.z - g_aTimer[i].fAngle[1]) * g_aTimer[i].fLength[1];
		pVtx_Timer[2].pos.y = g_aTimer[i].pos.y + cosf(g_aTimer[i].rot.z - g_aTimer[i].fAngle[1]) * g_aTimer[i].fLength[1];
		pVtx_Timer[3].pos.x = g_aTimer[i].pos.x + sinf(g_aTimer[i].rot.z + g_aTimer[i].fAngle[1]) * g_aTimer[i].fLength[1];
		pVtx_Timer[3].pos.y = g_aTimer[i].pos.y + cosf(g_aTimer[i].rot.z + g_aTimer[i].fAngle[1]) * g_aTimer[i].fLength[1];

		pVtx_Timer += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Timer->Unlock();
}

//************************************************
//�^�C�}�[�\���p�Ƀe�N�X�`�����X�V�֐�
//************************************************
void Update_Tex_Timer(void)
{
	//�e�N�X�`���̕����^�C������Z�o
	Calc_Tex_Timer();

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Timer;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Timer->Lock(0, 0, (void**)&pVtx_Timer, 0);

	for (int i = 0; i < AMOUNT_POLYGON_TIMER; i++)
	{
		pVtx_Timer[0].tex = D3DXVECTOR2(g_aTimer[i].fTexSpan[0], 0.0f);
		pVtx_Timer[1].tex = D3DXVECTOR2(g_aTimer[i].fTexSpan[1], 0.0f);
		pVtx_Timer[2].tex = D3DXVECTOR2(g_aTimer[i].fTexSpan[0], 1.0f);
		pVtx_Timer[3].tex = D3DXVECTOR2(g_aTimer[i].fTexSpan[1], 1.0f);

		pVtx_Timer += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Timer->Unlock();
}

//************************************************
//�^�C�}�[����Ƀe�N�X�`�������v�Z�֐�
//************************************************
void Calc_Tex_Timer(void)
{
	//���Ԃ��擾
	int nHold = g_nTimer;

	//���ƕb�𕪂���
	int nMinute = nHold / 60;
	nHold += (40 * nMinute);

	//�v�Z����
	for (int i = 0; i < AMOUNT_POLYGON_TIMER; i++)
	{
		//1�̈ʂ̐��l�𔲂��o��
		int nNumber = nHold % 10;

		//�����o���������畝���Z�b�g
		g_aTimer[(AMOUNT_POLYGON_TIMER - 1) - i].fTexSpan[0] = 0.0f + (0.1f * nNumber);
		g_aTimer[(AMOUNT_POLYGON_TIMER - 1) - i].fTexSpan[1] = 0.1f + (0.1f * nNumber);

		//�X�R�A�̌������炷
		nHold /= 10;
	}
}

//************************************************
//�^�C�}�[�\���p�̃A�h���X��n��
//************************************************
TIMER* GetInfo_TIMER(void)
{
	return &g_aTimer[0];
}

//************************************************
//�^�C�}�[�̃A�h���X��n��
//************************************************
int* GetInfo_Timer(void)
{
	return &g_nTimer;
}