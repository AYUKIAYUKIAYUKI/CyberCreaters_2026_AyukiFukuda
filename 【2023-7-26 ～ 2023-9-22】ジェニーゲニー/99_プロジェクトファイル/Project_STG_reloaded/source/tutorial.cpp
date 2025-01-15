//************************************************
//
//�`���[�g���A��[tutorial.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "sound.h"
#include "tutorial.h"
#include "tutorial_fade.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Tutorial = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Tutorial = NULL;	//���_�o�b�t�@�̃|�C���^
TUTORIAL g_aTutorial[AMOUNT_POLYGON_TUTORIAL];
bool g_bStart_T = false;

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Tutorial(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_EXPLAIN_TUTORIAL,
		&g_pTexture_Tutorial);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Tutorial,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tutorial;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Tutorial->Lock(0, 0, (void**)&pVtx_Tutorial, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Tutorial[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Tutorial[0].rhw = 1.0f;
		pVtx_Tutorial[1].rhw = 1.0f;
		pVtx_Tutorial[2].rhw = 1.0f;
		pVtx_Tutorial[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Tutorial[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Tutorial[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Tutorial[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Tutorial[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Tutorial[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Tutorial[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Tutorial[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Tutorial[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Tutorial += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Tutorial->Unlock();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL; nCnt++)
	{
		g_aTutorial[nCnt].nStyle = 0;
		g_aTutorial[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTutorial[nCnt].fLength = 0.0f;
		g_aTutorial[nCnt].fAngle = 0.0f;
	}

	g_bStart_T = false;

	Setinfo_Tutorial();

	//���̂ق���
	Init_Tutorial_Fade();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Tutorial(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Tutorial != NULL)
	{
		g_pTexture_Tutorial->Release();
		g_pTexture_Tutorial = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Tutorial != NULL)
	{
		g_pVtxBuff_Tutorial->Release();
		g_pVtxBuff_Tutorial = NULL;
	}

	//���̂ق���
	Uninit_Tutorial_Fade();
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Tutorial(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tutorial;

	float* pFade_T;
	pFade_T = Getinfo_Tutorial_Fade();

	if (!g_bStart_T)
	{
		//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
		g_pVtxBuff_Tutorial->Lock(0, 0, (void**)&pVtx_Tutorial, 0);

		for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
		{
			//�ړ��A��]�𔽉f
			pVtx_Tutorial[0].pos.x = g_aTutorial[nCnt].pos.x + sinf(g_aTutorial[nCnt].rot.z - (D3DX_PI - g_aTutorial[nCnt].fAngle)) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[0].pos.y = g_aTutorial[nCnt].pos.y + cosf(g_aTutorial[nCnt].rot.z - (D3DX_PI - g_aTutorial[nCnt].fAngle)) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[1].pos.x = g_aTutorial[nCnt].pos.x + sinf(g_aTutorial[nCnt].rot.z + (D3DX_PI - g_aTutorial[nCnt].fAngle)) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[1].pos.y = g_aTutorial[nCnt].pos.y + cosf(g_aTutorial[nCnt].rot.z + (D3DX_PI - g_aTutorial[nCnt].fAngle)) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[2].pos.x = g_aTutorial[nCnt].pos.x + sinf(g_aTutorial[nCnt].rot.z - g_aTutorial[nCnt].fAngle) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[2].pos.y = g_aTutorial[nCnt].pos.y + cosf(g_aTutorial[nCnt].rot.z - g_aTutorial[nCnt].fAngle) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[3].pos.x = g_aTutorial[nCnt].pos.x + sinf(g_aTutorial[nCnt].rot.z + g_aTutorial[nCnt].fAngle) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[3].pos.y = g_aTutorial[nCnt].pos.y + cosf(g_aTutorial[nCnt].rot.z + g_aTutorial[nCnt].fAngle) * g_aTutorial[nCnt].fLength;
	
			pVtx_Tutorial[0].col = g_aTutorial[nCnt].col;
			pVtx_Tutorial[1].col = g_aTutorial[nCnt].col;
			pVtx_Tutorial[2].col = g_aTutorial[nCnt].col;
			pVtx_Tutorial[3].col = g_aTutorial[nCnt].col;
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuff_Tutorial->Unlock();

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true &&
			!g_bStart_T)
		{
			//���ʉ���炷
			PlaySound(SOUND_LABEL_SE_SELECT2);

			g_bStart_T = true;
		}
	}

	//���̂ق���
	Update_Tutorial_Fade();

	if (g_bStart_T)
	{
		if (*pFade_T > 1.1f)
		{
			Setinfo_Mode(MODE_GAME);	//�J�n
		}
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Tutorial(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Tutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Tutorial);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);

	//���̂ق���
	Draw_Tutorial_Fade();
}

//************************************************
//�|���S������ݒ肷��֐�
//************************************************
void Setinfo_Tutorial(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_FADE; nCnt++)
	{
		g_aTutorial[nCnt].nStyle = 0;
		g_aTutorial[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aTutorial[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTutorial[nCnt].fLength = sqrtf((990.0f * 990.0f) + (540.0f * 540.0f));
		g_aTutorial[nCnt].fAngle = atan2f(990.0f * 2.0f, 540.0f * 2.0f);
	}
}

//************************************************
//�J�n���𑗂�֐�
//************************************************
bool* Getinfo_Tutorial(void)
{
	return &g_bStart_T;
}