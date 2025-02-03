//************************************************
//
//�������ԏ���[timer.cpp]	(���K�V�[)
//Author�F���c����
//
//************************************************
#include "timer.h"

#include "fade.h"
#include "input.h"
#include "sound.h"

//�^�C�}�[�֘A�\����
typedef struct
{
	int nTime;			//���ۂ̎c�莞��
	int nHold;			//�c�莞�ԏ��R�s�[
	int nCntDecrease;	//�c�莞�Ԃ����炷�t���[���J�E���g
	int nCntWait;		//�����Ⴎ����̃��c(�A�j���[�V����)
	int nCntInversion;	//���]���鎞�ԃJ�E���g
	int nCntReInversion;//�Ĕ��]���鎞�ԃJ�E���g
	bool bInversion;	//���]����
	bool bReInversion;	//�Ĕ��]����
}TIMER;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Timer[AMOUNT_TEXTURE_TIMER] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Timer = NULL;	//���_�o�b�t�@�̃|�C���^
float g_fMoveX_Timer = 0.0f;	//�����|���S���ړ���
int g_nTimer[AMOUNT_POLYGON_TIMER] = {};	//��ʕ\���p�U�蕪��
TIMER g_Timer;	//�^�C�}�[�֘A���

static const float g_AdjustY = 15.0f;

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
		TEXTURE_BLACK_TIMER,
		&g_pTexture_Timer[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NUMBER_TIMER,
		&g_pTexture_Timer[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NUMBER_SUB_TIMER,
		&g_pTexture_Timer[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CLOCK_TIMER,
		&g_pTexture_Timer[3]);

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

	//�ړ��ʂ����Z�b�g
	g_fMoveX_Timer = 0.0f;

	//�U�蕪�������Z�b�g
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TIMER; nCnt++)
	{
		g_nTimer[nCnt] = 0;
	}

	//�^�C�}�[�n��񏉊��ݒ�
	g_Timer.nTime = REMAIN_TIMER;
	g_Timer.nHold = 0;
	g_Timer.nCntDecrease = AMOUNT_CNT_MAX_TIMER - 1;
	g_Timer.nCntWait = 0;
	g_Timer.nCntInversion = 0;
	g_Timer.nCntReInversion = 0;
	g_Timer.bInversion = false;
	g_Timer.bReInversion = false;

	//���_�̓W�J�ƁA�������Ԃ̐ݒ�
	SetPos_Vtx_Timer();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Timer(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TIMER; nCnt++)
	{
		if (g_pTexture_Timer[nCnt] != NULL)
		{
			g_pTexture_Timer[nCnt]->Release();
			g_pTexture_Timer[nCnt] = NULL;
		}
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
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Timer;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Timer->Lock(0, 0, (void**)&pVtx_Timer, 0);

	//�c�莞�Ԍ����p�J�E���g
	g_Timer.nCntDecrease++;

	pVtx_Timer += AMOUNT_VTX * 6;

	if (g_Timer.nTime > 0)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			//�K���ɐ����𓮂���
			if (g_Timer.nCntWait < 5)
			{
				g_Timer.nCntWait++;
			}
			else
			{
				g_nTimer[6 - nCnt] = rand() % 10;
			}

			//�U�蕪�����x�[�X�Ƀe�N�X�`�����W��ύX
			pVtx_Timer[0].tex.x = MOVE_SPAN_TEX_TIMER * g_nTimer[6 - nCnt];
			pVtx_Timer[1].tex.x = MOVE_SPAN_TEX_TIMER * (g_nTimer[6 - nCnt] + 1);
			pVtx_Timer[2].tex.x = MOVE_SPAN_TEX_TIMER * g_nTimer[6 - nCnt];
			pVtx_Timer[3].tex.x = MOVE_SPAN_TEX_TIMER * (g_nTimer[6 - nCnt] + 1);

			pVtx_Timer -= AMOUNT_VTX;
		}
	}

	//�v�Z�p�ɁA���̎��Ԃ��擾
	g_Timer.nHold = g_Timer.nTime;

	int nMinute = g_Timer.nHold / 60;

	//���Ԃ𕪂Ƃ��ɕϊ�����
	g_Timer.nHold += (40 * nMinute);

	//�����ƂɐU�蕪����
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//�z���4 - nCnt�Ԗڂ�1�̈ʂ̐��l��U�蕪����
		g_nTimer[4 - nCnt] = g_Timer.nHold % 10;

		//�ʂ�������
		g_Timer.nHold /= 10;

		//�U�蕪�����x�[�X�Ƀe�N�X�`�����W��ύX
		pVtx_Timer[0].tex.x = MOVE_SPAN_TEX_TIMER * g_nTimer[4 - nCnt];
		pVtx_Timer[1].tex.x = MOVE_SPAN_TEX_TIMER * (g_nTimer[4 - nCnt] + 1);
		pVtx_Timer[2].tex.x = MOVE_SPAN_TEX_TIMER * g_nTimer[4 - nCnt];
		pVtx_Timer[3].tex.x = MOVE_SPAN_TEX_TIMER * (g_nTimer[4 - nCnt] + 1);

		pVtx_Timer -= AMOUNT_VTX;
	}

	//�t���[���J�E���g�����ɒB�����
	if (g_Timer.nCntDecrease >= AMOUNT_CNT_MAX_TIMER && g_Timer.nTime > 0)
	{
		//1�b����
		g_Timer.nTime--;

		g_Timer.nCntDecrease = 0;

		//���Ԍo�߂ŃX�N���[�����]
		if (g_Timer.nCntInversion < INVERSION_TIMER)
		{
			g_Timer.nCntInversion++;
		}
		else
		{
			g_Timer.bInversion = true;
		}

		//���Ԍo�߂ŃX�N���[���Ĕ��]
		if (g_Timer.nCntReInversion < REINVERSION_TIMER)
		{
			g_Timer.nCntReInversion++;
		}
		else
		{
			g_Timer.bReInversion = true;
		}
	}

	if (GetKeyboardTrigger(DIK_9) == true)
	{
		//�U�E���[���h
		g_Timer.nTime = 0;
	}

	//���Ԑ؂�
	if (g_Timer.nTime <= 0)
	{
		//�t�F�[�h���p
		FADE* pFade = GetInfoFade();

		//�t�F�[�h�A�E�g�J�n
		pFade->bFadeIn = false;
		pFade->bFadeOut = true;
	}
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
		if (nCnt == 0)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexture_Timer[0]);
		}
		else if (nCnt >= 1 && nCnt <= 6)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexture_Timer[1]);
		}
		else if (nCnt == 7 || nCnt == 8)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexture_Timer[2]);
		}
		else
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexture_Timer[3]);
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�����Ƃ��z�u�p�����֐�
//************************************************
void SetPos_Vtx_Timer(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Timer;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Timer->Lock(0, 0, (void**)&pVtx_Timer, 0);

	//�����_�����̕ӂɔz�u
	pVtx_Timer[0].pos = D3DXVECTOR3(0.0f, 20.0f + g_AdjustY, 0.0f);
	pVtx_Timer[1].pos = D3DXVECTOR3(365.0f, 20.0f + g_AdjustY, 0.0f);
	pVtx_Timer[2].pos = D3DXVECTOR3(0.0f, 100.0f + g_AdjustY, 0.0f);
	pVtx_Timer[3].pos = D3DXVECTOR3(340.0f, 100.0f + g_AdjustY, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx_Timer[0].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Timer[1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Timer[2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
	pVtx_Timer[3].col = D3DCOLOR_RGBA(255, 255, 255, 150);

	//������
	pVtx_Timer += AMOUNT_VTX;

	//������
	for (int nCnt = 0, nCntNumber = 0; nCnt < AMOUNT_USING_POLYGON_NUMBER_TIMER; nCnt++, nCntNumber++)
	{
		//���Ԃ����̕ӂɔz�u
		pVtx_Timer[0].pos = D3DXVECTOR3(85.0f + g_fMoveX_Timer, 40.0f + g_AdjustY, 0.0f);
		pVtx_Timer[1].pos = D3DXVECTOR3(145.0f + g_fMoveX_Timer, 40.0f + g_AdjustY, 0.0f);
		pVtx_Timer[2].pos = D3DXVECTOR3(85.0f + g_fMoveX_Timer, 80.0f + g_AdjustY, 0.0f);
		pVtx_Timer[3].pos = D3DXVECTOR3(145.0f + g_fMoveX_Timer, 80.0f + g_AdjustY, 0.0f);

		//����E�ɂ����
		g_fMoveX_Timer += DISTANCESPAN_POLYGON_TIMER;

		//�Ȃ�2���1�񑽂߂ɕ������
		if (nCntNumber % 2 == 1)
		{
			g_fMoveX_Timer += MORE_DISTANCESPAN_POLYGON_TIMER;
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx_Timer[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Timer[1].tex = D3DXVECTOR2(TEX_U_RIGHT_TIMER, 0.0f);
		pVtx_Timer[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Timer[3].tex = D3DXVECTOR2(TEX_U_RIGHT_TIMER, 1.0f);

		pVtx_Timer += AMOUNT_VTX;
	}

	g_fMoveX_Timer = 0;

	//�L����
	for (int nCnt = 0, nCntNumber = 0; nCnt < AMOUNT_USING_POLYGON_SYMBOL_TIMER; nCnt++, nCntNumber++)
	{
		//�L�������̕ӂɔz�u
		pVtx_Timer[0].pos = D3DXVECTOR3(142.5f + g_fMoveX_Timer, 45.0f + g_AdjustY, 0.0f);
		pVtx_Timer[1].pos = D3DXVECTOR3(192.5f + g_fMoveX_Timer, 45.0f + g_AdjustY, 0.0f);
		pVtx_Timer[2].pos = D3DXVECTOR3(142.5f + g_fMoveX_Timer, 80.0f + g_AdjustY, 0.0f);
		pVtx_Timer[3].pos = D3DXVECTOR3(192.5f + g_fMoveX_Timer, 80.0f + g_AdjustY, 0.0f);

		//����E�ɂ����
		g_fMoveX_Timer += DISTANCESPAN_POLYGON_SYMBOL_TIMER;

		if (nCnt == 0)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx_Timer[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Timer[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx_Timer[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx_Timer[3].tex = D3DXVECTOR2(0.5f, 1.0f);
		}
		else
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx_Timer[0].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx_Timer[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_Timer[2].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx_Timer[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		pVtx_Timer += AMOUNT_VTX;
	}

	//���v�����̕ӂɔz�u
	pVtx_Timer[0].pos = D3DXVECTOR3(25.0f, 35.0f + g_AdjustY, 0.0f);
	pVtx_Timer[1].pos = D3DXVECTOR3(75.0f, 35.0f + g_AdjustY, 0.0f);
	pVtx_Timer[2].pos = D3DXVECTOR3(25.0f, 85.0f + g_AdjustY, 0.0f);
	pVtx_Timer[3].pos = D3DXVECTOR3(75.0f, 85.0f + g_AdjustY, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Timer->Unlock();
}

//************************************************
//�������ԏ��̃A�h���X��n���֐�
//************************************************
int* Getinfo_Timer(void)
{
	return &g_Timer.nTime;	//�c�莞�ԏ��������n��
}

//************************************************
//���]����̃A�h���X��n���֐�
//************************************************
bool* Getinfo_Inversion_Timer(void)
{
	return &g_Timer.bInversion;
}

//************************************************
//�Ĕ��]����̃A�h���X��n���֐�
//************************************************
bool* Getinfo_ReInversion_Timer(void)
{
	return &g_Timer.bReInversion;
}