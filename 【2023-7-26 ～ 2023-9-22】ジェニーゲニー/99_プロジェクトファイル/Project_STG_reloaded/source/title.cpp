//************************************************
//
//�^�C�g���\������[title.cpp]
//Author�F���c����
//
//************************************************
#include "input.h"
#include "sound.h"
#include "title.h"
#include "line_titleh.h"
#include "particle_titlelogo.h"

/*�Ȃ��w�b�_�[�ɒu���Ȃ��H*/
//���ԉ�]�p�\����
typedef struct
{
	D3DXVECTOR3 pos;	//���S�_�����i�[
	D3DXVECTOR3 rot;	//���������i�[
	float fLength;		//�Ίp�����i�[
	float fAngle;		//�Ίp���̊p�x���i�[
}GEARS_ROTATE_TITLE;

/*�Ȃ��w�b�_�[�ɒu���Ȃ��H*/
//�U�n�g��]�p(?)�\����
typedef struct
{
	D3DXVECTOR3 pos;	//���S�_�����i�[
	D3DXVECTOR3 move;	//�ړ������i�[
	D3DXVECTOR3 rot;	//���������i�[
	float fLength;		//�Ίp�����i�[
	float fAngle;		//�Ίp���̊p�x���i�[
	float fMoveSPD1;
	float fMoveSPD2;
	float fMoveSPD3;
	int nCntStop;
}PIGEONS_ROTATE_TITLE;

typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	float fSpanX;		//�T�C�Y
	float fSpanY;		//�T�C�Y
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
	bool bfirst;
	int nCntfirst;
	bool bsecond;
	int nCntsecond;
	float fHoldX;
	float fHoldY;
	float fHoldZ;
	bool bthird;
	int nCntthird;
	bool bTurnX;
	bool bTurnY;
	bool bTurnZ;
	int nCntStop;
}LOGO_EX;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Title[AMOUNT_TEXTURE_TITLE] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Title = NULL;	//���_�o�b�t�@�̃|�C���^
int g_nColorA_Flash_Title = 0;	//�M���F�ύX�p
float g_fPosX_TitleLogo = 0.0f;	//�^�C�g�����S���W�p
float g_fTexU_TitleLogo = 0.0f;	//�^�C�g�����S�e�N�X�`���p
int g_nColorA_Roses_Title = 0;	//�o���F�ύX�p
float g_fPosY_Curtain_Title[AMOUNT_USING_TEX_ROSES_TITLE] = {};		//�J�[�e�����W�p
float g_fPosX_Garland1_Title[AMOUNT_USING_TEX_GARLAND1_TITLE] = {};	//�K�[�����h1���W�p
float g_fPosY_Kanzashi_Title = 0.0f;	//���񂴂����W�p
float g_fPosY_Brooch_Title = 0.0f;		//�u���[�`���W�p
float g_fPosY_Gear_Title = 0.0f;		//���ԍ��W�p
float g_fPosY_Pendant_Title = 0.0f;		//�y���_���g���W�p
float g_fPosY_Garland2_Title = 0.0f;	//�K�[�����h2���W�p
GEARS_ROTATE_TITLE g_aGears_Title[AMOUNT_USING_TEX_GEARS_TITLE];		//���ԌQ��]�p
PIGEONS_ROTATE_TITLE g_aPigeons_Title[AMOUNT_USING_TEX_PIGEONS_TITLE];	//�U�n�g��]�p(?)
int g_nColorA_Press_Title = 0;	//���͊����F�ύX�p
bool g_bChangeColor_Press_Title = false;	//���͊����F�ύX�J�n����p
int g_nColorA_Fadeout_Title = 0;	//�t�F�[�h�A�E�g�p�A���t�@�l�i�[
bool g_bStartFadeout_Title = false;	//�t�F�[�h�A�E�g�J�n����p
bool g_bStartRotate = false;		//��]�J�n����
bool g_bTurn_1 = false;
bool g_bTurn_2 = false;
int g_nCntBright = 0;
//float g_fVolume_BGM_Title = 0.0f;
LOGO_EX g_aLogoEX;

//************************************************
//�����������֐�
//************************************************
void Init_Title(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SKY_TITLE,
		&g_pTexture_Title[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CLOUD1_TITLE,
		&g_pTexture_Title[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CLOUD2_TITLE,
		&g_pTexture_Title[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CLOUD3_TITLE,
		&g_pTexture_Title[3]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ROSES_TITLE,
		&g_pTexture_Title[4]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ROSES_TITLE,
		&g_pTexture_Title[5]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GARLAND2_TITLE,
		&g_pTexture_Title[6]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GARLAND2_TITLE,
		&g_pTexture_Title[7]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GARLAND1_TITLE,
		&g_pTexture_Title[8]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GARLAND1_TITLE,
		&g_pTexture_Title[9]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PENDANT_TITLE,
		&g_pTexture_Title[10]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEAR_TITLE,
		&g_pTexture_Title[11]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BROOCH_TITLE,
		&g_pTexture_Title[12]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_KANZASHI_TITLE,
		&g_pTexture_Title[13]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CURTAIN_TITLE,
		&g_pTexture_Title[14]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CURTAIN_TITLE,
		&g_pTexture_Title[15]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PIGEON1_TITLE,
		&g_pTexture_Title[16]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PIGEON2_TITLE,
		&g_pTexture_Title[17]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARBIG_TITLE,
		&g_pTexture_Title[18]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARBIG_TITLE,
		&g_pTexture_Title[19]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARFRAME_TITLE,
		&g_pTexture_Title[20]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARFRAME_TITLE,
		&g_pTexture_Title[21]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARFRAME_TITLE,
		&g_pTexture_Title[22]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARFRAME_TITLE,
		&g_pTexture_Title[23]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARSMALL_TITLE,
		&g_pTexture_Title[24]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARSMALL_TITLE,
		&g_pTexture_Title[25]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LOGO_TITLE,
		&g_pTexture_Title[26]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PRESS_TITLE,
		&g_pTexture_Title[27]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WHITE_TITLE,
		&g_pTexture_Title[28]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_TITLE,
		&g_pTexture_Title[29]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Title,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	//�����ʒu�ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TITLE; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Title[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Title[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Title[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Title[0].rhw = 1.0f;
		pVtx_Title[1].rhw = 1.0f;
		pVtx_Title[2].rhw = 1.0f;
		pVtx_Title[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Title[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Title[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Title[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Title[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�|�C���^�����炷
		pVtx_Title += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();

	//�M�������F
	g_nColorA_Flash_Title = 255;

	//�^�C�g�����S�������W
	g_fPosX_TitleLogo = 0.0f;

	//�^�C�g�����S�����e�N�X�`���T�C�Y
	g_fTexU_TitleLogo = 0.5f;

	//�o�������F
	g_nColorA_Roses_Title = 0;

	//�J�[�e���������W
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_ROSES_TITLE; nCnt++)
	{
		g_fPosY_Curtain_Title[nCnt] = {};
	}

	//�K�[�����h1�������W
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GARLAND1_TITLE; nCnt++)
	{
		g_fPosX_Garland1_Title[nCnt] = {};
	}

	//���񂴂��������W
	g_fPosY_Kanzashi_Title = 0.0f;

	//�u���[�`�������W
	g_fPosY_Brooch_Title = 0.0f;

	//���ԏ������W
	g_fPosY_Gear_Title = 0.0f;

	//�y���_���g�������W
	g_fPosY_Pendant_Title = 0.0f;

	//�K�[�����h2�������W
	g_fPosY_Garland2_Title = 0.0f;

	//���ԌQ�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GEARS_TITLE; nCnt++)
	{
		//��]������ׂɒ��S�_��ݒ�
		switch (nCnt)
		{
		case 0:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(-151.0f - HALFSPAN_GEARBIG_TITLE, 855.0f + HALFSPAN_GEARBIG_TITLE, 0.0);

			break;

		case 1:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH + 151.0f + HALFSPAN_GEARBIG_TITLE, 855.0f + HALFSPAN_GEARBIG_TITLE, 0.0);

			break;

		case 2:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(-200.0f - HALFSPAN_GEARFRAME_TITLE, 800.0f + HALFSPAN_GEARFRAME_TITLE, 0.0f);

			break;

		case 3:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(275.0f - HALFSPAN_GEARFRAME_TITLE, SCREEN_HEIGHT + 200.0f + HALFSPAN_GEARFRAME_TITLE, 0.0f);

			break;

		case 4:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH + 200.0f + HALFSPAN_GEARFRAME_TITLE, 800.0f + HALFSPAN_GEARFRAME_TITLE, 0.0f);

			break;

		case 5:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 275.0f + HALFSPAN_GEARFRAME_TITLE, SCREEN_HEIGHT + 200.0f + HALFSPAN_GEARFRAME_TITLE, 0.0f);

			break;

		case 6:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(137.0f - HALFSPAN_GEARSMALL_TITLE, SCREEN_HEIGHT + 206.0f - HALFSPAN_GEARSMALL_TITLE, 0.0f);

			break;

		case 7:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 137.0f + HALFSPAN_GEARSMALL_TITLE, SCREEN_HEIGHT + 206.0f - HALFSPAN_GEARSMALL_TITLE, 0.0f);

			break;
		}

		g_aGears_Title[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0);

		switch(nCnt)
		{
		case 0:

			g_aGears_Title[nCnt].fLength = sqrtf(SPAN_GEARBIG_TITLE * SPAN_GEARBIG_TITLE + SPAN_GEARBIG_TITLE * SPAN_GEARBIG_TITLE) * 0.5f;
			g_aGears_Title[nCnt].fAngle = atan2f(SPAN_GEARBIG_TITLE, SPAN_GEARBIG_TITLE);

			for (int nCopy = nCnt + 1; nCopy < nCnt + AMOUNT_USING_TEX_GEARBIG_TITLE; nCopy++)
			{
				//�����`�̂��̂ɑ��
				g_aGears_Title[nCopy].fLength = g_aGears_Title[nCnt].fLength;
				g_aGears_Title[nCopy].fAngle = g_aGears_Title[nCnt].fAngle;
			}

			break;

		case AMOUNT_USING_TEX_GEARBIG_TITLE:

			g_aGears_Title[nCnt].fLength = sqrtf(SPAN_GEARFRAME_TITLE * SPAN_GEARFRAME_TITLE + SPAN_GEARFRAME_TITLE * SPAN_GEARFRAME_TITLE) * 0.5f;
			g_aGears_Title[nCnt].fAngle = atan2f(SPAN_GEARFRAME_TITLE, SPAN_GEARFRAME_TITLE);

			for (int nCopy = nCnt + 1; nCopy < nCnt + AMOUNT_USING_TEX_GEARFRAME_TITLE; nCopy++)
			{
				//�����`�̂��̂ɑ��
				g_aGears_Title[nCopy].fLength = g_aGears_Title[nCnt].fLength;
				g_aGears_Title[nCopy].fAngle = g_aGears_Title[nCnt].fAngle;
			}

			break;

		case AMOUNT_USING_TEX_GEARBIG_TITLE + AMOUNT_USING_TEX_GEARFRAME_TITLE:

			g_aGears_Title[nCnt].fLength = sqrtf(SPAN_GEARSMALL_TITLE * SPAN_GEARSMALL_TITLE + SPAN_GEARSMALL_TITLE * SPAN_GEARSMALL_TITLE) * 0.5f;
			g_aGears_Title[nCnt].fAngle = atan2f(SPAN_GEARSMALL_TITLE, SPAN_GEARSMALL_TITLE);

			for (int nCopy = nCnt + 1; nCopy < nCnt + AMOUNT_USING_TEX_GEARSMALL_TITLE; nCopy++)
			{
				//�����`�̂��̂ɑ��
				g_aGears_Title[nCopy].fLength = g_aGears_Title[nCnt].fLength;
				g_aGears_Title[nCopy].fAngle = g_aGears_Title[nCnt].fAngle;
			}

			break;
		}
	}

	//�U�n�g�����ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_PIGEONS_TITLE; nCnt++)
	{
		//��]������ׂɒ��S�_��ݒ�
		switch (nCnt)
		{
		case 0:

			g_aPigeons_Title[nCnt].pos = D3DXVECTOR3(0.0f - HALF_SPAN_PIGEON1_X_TITLE, 850.0f, 0.0f);

			break;

		case 1:

			g_aPigeons_Title[nCnt].pos = D3DXVECTOR3(1980.0f + HALF_SPAN_PIGEON2_X_TITLE, 800.0f, 0.0f);

			break;
		}

		g_aPigeons_Title[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0);
		g_aPigeons_Title[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0);

		switch (nCnt)
		{
		case 0:

			g_aPigeons_Title[nCnt].fLength = sqrtf(SPAN_PIGEON1_X_TITLE * SPAN_PIGEON1_X_TITLE + SPAN_PIGEON1_Y_TITLE * SPAN_PIGEON1_Y_TITLE) * 0.5f;
			g_aPigeons_Title[nCnt].fAngle = atan2f(SPAN_PIGEON1_X_TITLE, SPAN_PIGEON1_Y_TITLE);

			g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_1_X;
			g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_1_Y;
			g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_1_Z;
			
			break;

		case 1:

			g_aPigeons_Title[nCnt].fLength = sqrtf(SPAN_PIGEON2_X_TITLE * SPAN_PIGEON2_X_TITLE + SPAN_PIGEON2_Y_TITLE * SPAN_PIGEON2_Y_TITLE) * 0.5f;
			g_aPigeons_Title[nCnt].fAngle = atan2f(SPAN_PIGEON2_X_TITLE, SPAN_PIGEON2_Y_TITLE);

			g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_2_X;
			g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_2_Y;
			g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_2_Z;

			break;
		}

		g_aPigeons_Title[nCnt].nCntStop = 0 + (30 * nCnt);
	}

	//���͊��������F
	g_nColorA_Press_Title = 0;

	//�t�F�[�h�A�E�g�����F
	g_nColorA_Fadeout_Title = 0;

	g_bStartFadeout_Title = false;

	g_bStartRotate = false;

	g_bTurn_1 = false;
	g_bTurn_2 = false;

	g_nCntBright = 0;

	//�^�C�g�����S����������
	g_aLogoEX.nStyle = 0;	//���
	g_aLogoEX.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	g_aLogoEX.fSpanX = 0.0f;	//�T�C�Y
	g_aLogoEX.fSpanY = 0.0f;	//�T�C�Y
	g_aLogoEX.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ����
	g_aLogoEX.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������
	g_aLogoEX.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F
	g_aLogoEX.fLength = 0.0f;	//�Ίp��
	g_aLogoEX.fAngle = 0.0f;	//�p�x
	g_aLogoEX.bfirst = false;
	g_aLogoEX.nCntfirst = 0;
	g_aLogoEX.bsecond = false;
	g_aLogoEX.nCntsecond = 0;
	g_aLogoEX.fHoldX = 0.0f;
	g_aLogoEX.fHoldY = 0.0f;
	g_aLogoEX.fHoldZ = 0.0f;
	g_aLogoEX.bthird = false;
	g_aLogoEX.nCntthird = 0;
	g_aLogoEX.bTurnX = false;
	g_aLogoEX.bTurnY = false;
	g_aLogoEX.bTurnZ = false;
	g_aLogoEX.nCntStop = 0;

	//����Ɉ�x�|���S����W�J����
	SetPos_Vtx_Title();

	//�^�C�g�����S����ݒ�
	Setinfo_TitleLogoEX_Title();

	//BGM��������
	PlaySound(SOUND_LABEL_BGM000);

	//������
	Init_Line_title();
	Init_Particle_Titlelogo();
}

//************************************************
//�I�������֐�
//************************************************
void Uninit_Title(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TITLE; nCnt++)
	{
		if (g_pTexture_Title[nCnt] != NULL)
		{
			g_pTexture_Title[nCnt]->Release();
			g_pTexture_Title[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Title != NULL)
	{
		g_pVtxBuff_Title->Release();
		g_pVtxBuff_Title = NULL;
	}

	//BGM���~�߂�
	StopSound();

	//�I��
	Uninit_Line_title();
	Uninit_Particle_Titlelogo();
}

//************************************************
//�X�V�����֐�
//************************************************
void Update_Title(void)
{
	//�w�i����������
	BG_Animation_Title();

	//���ԌQ��葱����
	Gears_Rotate_Title();

	if (g_nColorA_Flash_Title > 0)
	{
		//�M���A�j���[�V����
		Flash_Animation_Title();
	}
	else
	{
		if (g_nColorA_Roses_Title < 255)
		{
			//�o���A�j���[�V����
			Roses_Animation_Title();
		}
		else
		{
			if (g_fPosY_Curtain_Title[1] < 275.0f)
			{
				//�J�[�e���A�j���[�V����
				Curtain_Animation_Title();
			}
			else
			{
				
				if (g_fPosX_Garland1_Title[1] < 729.0f)
				{
					//�K�[�����h1�A�j���[�V����
					Garland1_Animation_Title();
				}
				else
				{
					if (g_fPosY_Kanzashi_Title < 595.0f)
					{
						//���񂴂��A�j���[�V����
						Kanzashi_Animation_Title();
					}
					else
					{
						if (g_fPosY_Brooch_Title < 585.0f)
						{
							//�u���[�`�A�j���[�V����
							Brooch_Animation_Title();
						}
						else
						{
							if (g_fPosY_Gear_Title < 447.0f)
							{
								//���ԃA�j���[�V����
								Gear_Animation_Title();
							}
							else
							{
								if (g_fPosY_Pendant_Title < 327.0f)
								{
									//�y���_���g�A�j���[�V����
									Pendant_Animation_Title();
								}
								else
								{	
									if (g_fPosY_Garland2_Title < 519.0f)
									{
										//�K�[�����h2�A�j���[�V����
										Garland2_Animation_Title();
									}
								}
							}
						}
					}
				}
			}
		}

		if (g_aGears_Title[6].pos.y > 939.0f + HALFSPAN_GEARSMALL_TITLE)
		{
			//���ԌQ�A�j���[�V����
			Gears_Animation_Title();
		}
		else
		{
			if (g_aPigeons_Title[0].pos.x < 300.0f && !g_bStartRotate)
			{
				//�U�n�g�A�j���[�V����
				Pigeons_Animation_Title();
			}
			else
			{
				//�U�n�g��
				Pigeons_Rotate_Title();
			}
		}

		if (g_fPosX_TitleLogo < SCREEN_WIDTH - (SCREENCENTER_X + HALF_X_LOGO_TITLE))
		{
			//�^�C�g�����S�A�j���[�V����
			TitleLogo_Animation_Title();
			//TitleLogo_AnimationEX_Title();
		}
		else
		{
			//�L���L��
			if (g_nCntBright > 10)
			{
				g_nCntBright = 0;

				Setinfo_Particle_Titlelogo(D3DXVECTOR3(463.0f + (float)(rand() % 924), 100.0f + (float)(rand() % 640), 0.0f));
			}
			else
			{
				g_nCntBright++;
			}

			//���͊����A�j���[�V����
			Press_Animation_Title();

			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true
				|| GetJoypadTrigger(JOYKEY_A) == true && !g_bStartFadeout_Title)
			{
				g_bStartFadeout_Title = true;
			}
		}
	}

	//�X�V
	Update_Line_title();
	Update_Particle_Titlelogo();

	if (g_bStartFadeout_Title && g_nColorA_Fadeout_Title < 255)
	{
		//�t�F�[�h�A�E�g
		Fadeout_Animation_Title();
	}
	else if (g_nColorA_Fadeout_Title >= 255)
	{
		/*����͊e�A�j���[�V�����̃o�b�t�@�̃A�����b�N��ɍs����ׂ��ł���A�������j��*/

		Setinfo_Mode(MODE_MENU);	//���j���[���[�h��
	}

	///***********�f�o�b�O�p�R�}���h���Q�[���փX�L�b�v*********/
	//if (GetKeyboardTrigger(DIK_0) == true)
	//{
	//	Setinfo_Mode(MODE_GAME);	//�Q�[�����[�h��
	//}
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw_Title(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Title, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TITLE; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Title[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//�X�V
	//Draw_Line_title();
	Draw_Particle_Titlelogo();
}

//************************************************
//���_��W�J����֐�
//************************************************
void SetPos_Vtx_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	//�e�|���S���W�J
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TITLE; nCnt++)
	{
		if (nCnt == 0 || nCnt == 1 || nCnt == 2 || nCnt == 3 || nCnt == SKIP_VTX_TO_WHITE_TITLE)
		{
			pVtx_Title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (nCnt == SKIP_VTX_TO_ROSES_TITLE)
		{
			pVtx_Title[0].pos = D3DXVECTOR3(-45.0f, -58.0f, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(363.0f, -58.0f, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(-45.0f, 435.0f, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(363.0f, 435.0f, 0.0f);

			pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);

			pVtx_Title[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_Title[1].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx_Title[2].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_Title[3].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
		else if (nCnt == SKIP_VTX_TO_ROSES_TITLE + 1)
		{
			pVtx_Title[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 363.0f, -58.0f, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH + 45.0f, -58.0f, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 363.0f, 435.0f, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH + 45.0f, 435.0f, 0.0f);

			pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);

			pVtx_Title[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx_Title[1].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_Title[2].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Title[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}
		else if (nCnt == SKIP_VTX_TO_GARLAND2_TITLE + 1)
		{
			pVtx_Title[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_Title[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Title[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_Title[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
		else if (nCnt == SKIP_VTX_TO_GARLAND1_TITLE + 1)
		{
			pVtx_Title[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_Title[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Title[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_Title[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
		else if (nCnt == SKIP_VTX_TO_CURTAIN_TITLE + 1)
		{
			pVtx_Title[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_Title[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Title[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_Title[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
		else if(nCnt == SKIP_VTX_TO_PRESS_TITLE)
		{
			pVtx_Title[0].pos = D3DXVECTOR3(715.0f, 850.0f, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(1245.0f, 850.0f, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(715.0f, 916.0f, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(1245.0f, 916.0f, 0.0f);

			pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
			pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
			pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
			pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
		}
		else if (nCnt == SKIP_VTX_TO_FADEOUT_TITLE)
		{
			pVtx_Title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

			pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
			pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
			pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
			pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
		}

		pVtx_Title += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�M���A�j���[�V�����֐�
//************************************************
void Flash_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_WHITE_TITLE;

	g_nColorA_Flash_Title -= CHANGE_SPD_WHITE_COLORA_TITLE;

	//�F�ς�肷���h�~
	if (g_nColorA_Flash_Title <= 0)
	{
		g_nColorA_Flash_Title = 0;
	}

	//�F�ύX
	pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Flash_Title);
	pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Flash_Title);
	pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Flash_Title);
	pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Flash_Title);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�w�i�A�j���[�V�����֐�
//************************************************
void BG_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	//�e�N�X�`���ʒu�ύX
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_BG_TITLE; nCnt++)
	{
		//�e�N�X�`�����W�̍X�V
		pVtx_Title[0].tex.x += MOVE_SPD_TEX_BG_TITLE * (nCnt + 1);
		pVtx_Title[1].tex.x += MOVE_SPD_TEX_BG_TITLE * (nCnt + 1);
		pVtx_Title[2].tex.x += MOVE_SPD_TEX_BG_TITLE * (nCnt + 1);
		pVtx_Title[3].tex.x += MOVE_SPD_TEX_BG_TITLE * (nCnt + 1);

		pVtx_Title += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�^�C�g�����S�A�j���[�V�����֐�
//************************************************
void TitleLogo_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_LOGO_TITLE;

	g_fPosX_TitleLogo += MOVE_SPD_POS_LOGO_TITLE * 3.0f;

	//�|���S���L�k�������h�~
	if (SCREENCENTER_X + g_fPosX_TitleLogo >= SCREEN_WIDTH - HALF_X_LOGO_TITLE)
	{
		g_fPosX_TitleLogo = SCREEN_WIDTH - (SCREENCENTER_X + HALF_X_LOGO_TITLE);
	}

	//���_���W�̈ړ�
	pVtx_Title[0].pos = D3DXVECTOR3(SCREENCENTER_X - g_fPosX_TitleLogo, 100.0f, 0.0f);
	pVtx_Title[1].pos = D3DXVECTOR3(SCREENCENTER_X + g_fPosX_TitleLogo, 100.0f, 0.0f);
	pVtx_Title[2].pos = D3DXVECTOR3(SCREENCENTER_X - g_fPosX_TitleLogo, 740.0f, 0.0f);
	pVtx_Title[3].pos = D3DXVECTOR3(SCREENCENTER_X + g_fPosX_TitleLogo, 740.0f, 0.0f);

	//���S�W�J�Ƀp�[�e�B�N��
	//Setinfo_Particle_Titlelogo(D3DXVECTOR3(SCREENCENTER_X - g_fPosX_TitleLogo, 100.0f, 0.0f));

	g_fTexU_TitleLogo -= MOVE_SPD_TEX_LOGO_TITLE * 3.0f;

	//�e�N�X�`���L�k�������h�~
	if (g_fTexU_TitleLogo <= 0.0f)
	{
		g_fTexU_TitleLogo = 0.0f;
	}

	//�e�N�X�`���̃T�C�Y�ύX
	pVtx_Title[0].tex = D3DXVECTOR2(0.0f + g_fTexU_TitleLogo, 0.0f);
	pVtx_Title[1].tex = D3DXVECTOR2(1.0f - g_fTexU_TitleLogo, 0.0f);
	pVtx_Title[2].tex = D3DXVECTOR2(0.0f + g_fTexU_TitleLogo, 1.0f);
	pVtx_Title[3].tex = D3DXVECTOR2(1.0f - g_fTexU_TitleLogo, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�o���A�j���[�V�����֐�
//************************************************
void Roses_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_ROSES_TITLE;

	g_nColorA_Roses_Title += CHANGE_SPD_ROSES_COLORA_TITLE;

	//�F�ς�肷���h�~
	if (g_nColorA_Roses_Title >= 255)
	{
		g_nColorA_Roses_Title = 255;
	}

	//�F�ύX
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_ROSES_TITLE; nCnt++)
	{
		pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
		pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
		pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
		pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);

		pVtx_Title += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�J�[�e���A�j���[�V�����֐�
//************************************************
void Curtain_Animation_Title(void)
{
	int nCntCurtain = 0;	//�J�[�e���ԍ�

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_CURTAIN_TITLE;

	g_fPosY_Curtain_Title[nCntCurtain] += MOVE_SPD_POS_CURTAIN_TITLE;

	//�|���S���L�k�������h�~
	if (g_fPosY_Curtain_Title[nCntCurtain] >= 275.0f)
	{
		g_fPosY_Curtain_Title[nCntCurtain] = 275.0f;

		nCntCurtain++;
	}

	switch (nCntCurtain)
	{
	case 0:

		//���_���W�̈ړ�
		pVtx_Title[0].pos = D3DXVECTOR3(-76.0f, -363.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[1].pos = D3DXVECTOR3(281.0f, -363.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[2].pos = D3DXVECTOR3(-76.0f, 0.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[3].pos = D3DXVECTOR3(281.0f, 0.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);

		break;

	case 1:

		pVtx_Title += AMOUNT_VTX;

		g_fPosY_Curtain_Title[nCntCurtain] += MOVE_SPD_POS_CURTAIN_TITLE;

		//�|���S���L�k�������h�~
		if (g_fPosY_Curtain_Title[nCntCurtain] >= 275.0f)
		{
			g_fPosY_Curtain_Title[nCntCurtain] = 275.0f;
		}

		pVtx_Title[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 281.0f, -363.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH + 76.0f, -363.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 281.0f, 0.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH + 76.0f, 0.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);

		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�K�[�����h1�A�j���[�V�����֐�
//************************************************
void Garland1_Animation_Title(void)
{
	int nCntGarland1 = 0;	//�K�[�����h1�ԍ�

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_GARLAND1_TITLE;

	g_fPosX_Garland1_Title[nCntGarland1] += MOVE_SPD_POS_GARLAND1_TITLE;

	//�|���S���L�k�������h�~
	if (g_fPosX_Garland1_Title[nCntGarland1] >= 729.0f)
	{
		g_fPosX_Garland1_Title[nCntGarland1] = 729.0f;

		nCntGarland1++;

		g_fPosX_Garland1_Title[nCntGarland1] += MOVE_SPD_POS_GARLAND1_TITLE;

		pVtx_Title += AMOUNT_VTX;

		//�|���S���L�k�������h�~
		if (g_fPosX_Garland1_Title[nCntGarland1] >= 729.0f)
		{
			g_fPosX_Garland1_Title[nCntGarland1] = 729.0f;
		}
	}

	switch (nCntGarland1)
	{
	case 0:

		//���_���W�̈ړ�
		pVtx_Title[0].pos = D3DXVECTOR3(-560.0f + g_fPosX_Garland1_Title[nCntGarland1], -206.0f, 0.0f);
		pVtx_Title[1].pos = D3DXVECTOR3(0.0f + g_fPosX_Garland1_Title[nCntGarland1], -206.0f, 0.0f);
		pVtx_Title[2].pos = D3DXVECTOR3(-560.0f + g_fPosX_Garland1_Title[nCntGarland1], 227.0f, 0.0f);
		pVtx_Title[3].pos = D3DXVECTOR3(0.0f + g_fPosX_Garland1_Title[nCntGarland1], 227.0f, 0.0f);

		break;

	case 1:

		pVtx_Title[0].pos = D3DXVECTOR3(SCREEN_WIDTH - g_fPosX_Garland1_Title[nCntGarland1], -206.0f, 0.0f);
		pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH + 560.0f - g_fPosX_Garland1_Title[nCntGarland1], -206.0f, 0.0f);
		pVtx_Title[2].pos = D3DXVECTOR3(SCREEN_WIDTH - g_fPosX_Garland1_Title[nCntGarland1], 227.0f, 0.0f);
		pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH + 560.0f - g_fPosX_Garland1_Title[nCntGarland1], 227.0f, 0.0f);

		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//���񂴂��A�j���[�V�����֐�
//************************************************
void Kanzashi_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_KANZASHI_TITLE;

	g_fPosY_Kanzashi_Title += MOVE_SPD_POS_KANZASHI_TITLE;

	//�|���S���L�k�������h�~
	if (g_fPosY_Kanzashi_Title >= 595.0f)
	{
		g_fPosY_Kanzashi_Title = 595.0f;
	}

	//���_���W�̈ړ�
	pVtx_Title[0].pos = D3DXVECTOR3(-69.0f, -489.0f + g_fPosY_Kanzashi_Title, 0.0f);
	pVtx_Title[1].pos = D3DXVECTOR3(219.0f, -489.0f + g_fPosY_Kanzashi_Title, 0.0f);
	pVtx_Title[2].pos = D3DXVECTOR3(-69.0f, 0.0f + g_fPosY_Kanzashi_Title, 0.0f);
	pVtx_Title[3].pos = D3DXVECTOR3(219.0f, 0.0f + g_fPosY_Kanzashi_Title, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�u���[�`�A�j���[�V�����֐�
//************************************************
void Brooch_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_BROOCH_TITLE;

	g_fPosY_Brooch_Title += MOVE_SPD_POS_BROOCH_TITLE;

	//�|���S���L�k�������h�~
	if (g_fPosY_Brooch_Title >= 585.0f)
	{
		g_fPosY_Brooch_Title = 585.0f;
	}

	//���_���W�̈ړ�
	pVtx_Title[0].pos = D3DXVECTOR3(1803.0f, -551.0f + g_fPosY_Brooch_Title, 0.0f);
	pVtx_Title[1].pos = D3DXVECTOR3(1934.0f, -551.0f + g_fPosY_Brooch_Title, 0.0f);
	pVtx_Title[2].pos = D3DXVECTOR3(1803.0f, 0.0f + g_fPosY_Brooch_Title, 0.0f);
	pVtx_Title[3].pos = D3DXVECTOR3(1934.0f, 0.0f + g_fPosY_Brooch_Title, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//���ԃA�j���[�V�����֐�
//************************************************
void Gear_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_GEAR_TITLE;

	g_fPosY_Gear_Title += MOVE_SPD_POS_GEAR_TITLE;

	//�|���S���L�k�������h�~
	if (g_fPosY_Gear_Title >= 447.0f)
	{
		g_fPosY_Gear_Title = 447.0f;
	}

	//���_���W�̈ړ�
	pVtx_Title[0].pos = D3DXVECTOR3(110.0f, -390.0f + g_fPosY_Gear_Title, 0.0f);
	pVtx_Title[1].pos = D3DXVECTOR3(287.0f, -390.0f + g_fPosY_Gear_Title, 0.0f);
	pVtx_Title[2].pos = D3DXVECTOR3(110.0f, 0.0f + g_fPosY_Gear_Title, 0.0f);
	pVtx_Title[3].pos = D3DXVECTOR3(287.0f, 0.0f + g_fPosY_Gear_Title, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�y���_���g�A�j���[�V�����֐�
//************************************************
void Pendant_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_PENDANT_TITLE;

	g_fPosY_Pendant_Title += MOVE_SPD_POS_PENDANT_TITLE;

	//�|���S���L�k�������h�~
	if (g_fPosY_Pendant_Title >= 327.0f)
	{
		g_fPosY_Pendant_Title = 327.0f;
	}

	//���_���W�̈ړ�
	pVtx_Title[0].pos = D3DXVECTOR3(1690.0f, -189.0f + g_fPosY_Pendant_Title, 0.0f);
	pVtx_Title[1].pos = D3DXVECTOR3(1804.0f, -189.0f + g_fPosY_Pendant_Title, 0.0f);
	pVtx_Title[2].pos = D3DXVECTOR3(1690.0f, 0.0f + g_fPosY_Pendant_Title, 0.0f);
	pVtx_Title[3].pos = D3DXVECTOR3(1804.0f, 0.0f + g_fPosY_Pendant_Title, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�K�[�����h2�A�j���[�V�����֐�
//************************************************
void Garland2_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_GARLAND2_TITLE;

	g_fPosY_Garland2_Title += MOVE_SPD_POS_GARLAND2_TITLE;

	//�|���S���L�k�������h�~
	if (g_fPosY_Garland2_Title >= 519.0f)
	{
		g_fPosY_Garland2_Title = 519.0f;
	}

	//���_���W�̈ړ�
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			pVtx_Title[0].pos = D3DXVECTOR3(75.0f, -521.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(312.0f, -521.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(75.0f, 0.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(312.0f, 0.0f + g_fPosY_Garland2_Title, 0.0f);

			break;

		case 1:

			pVtx_Title[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 342.0f, -521.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 105.0f, -521.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 342.0f, 0.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 105.0f, 0.0f + g_fPosY_Garland2_Title, 0.0f);

			break;
		}

		pVtx_Title += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//���ԌQ�A�j���[�V�����֐�
//************************************************
void Gears_Animation_Title(void)
{
	int nCntGears = 0;	//���Ԕԍ�
	bool bStartRotateFrame = false;
	bool bStartRotateSmall = false;

	//���ԑ�̒��S�_���ړ�����
	for (int nCntBig = 0; nCntBig < AMOUNT_USING_TEX_GEARBIG_TITLE; nCntBig++)
	{
		switch (nCntBig)
		{
		case 0:

			g_aGears_Title[nCntBig].pos.x += MOVE_SPD_POS_GEARS_TITLE;

			break;

		case 1:

			g_aGears_Title[nCntBig].pos.x -= MOVE_SPD_POS_GEARS_TITLE;

			break;
		}
	}

	//���ԑ�ړ���A���Ԙg�ړ��J�n
	if (g_aGears_Title[nCntGears].pos.x >= 218.0f - HALFSPAN_GEARBIG_TITLE)
	{
		//�Ή��p�[�c�񐔃��[�v�A���Ԕԍ����i�߂�
		for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GEARBIG_TITLE; nCnt++)
		{
			switch (nCntGears)
			{
			case 0:

				g_aGears_Title[nCntGears].pos.x = 218.0f - HALFSPAN_GEARBIG_TITLE;

				break;

			case 1:

				g_aGears_Title[nCntGears].pos.x = SCREEN_WIDTH - 218.0f + HALFSPAN_GEARBIG_TITLE;

				break;
			}

			nCntGears++;
		}

		if (!bStartRotateFrame)
		{
			bStartRotateFrame = true;
		}
	}

	//���Ԙg�̒��S�_���ړ�����
	if (bStartRotateFrame)
	{
		for (int nCntFrame = 0; nCntFrame < AMOUNT_USING_TEX_GEARFRAME_TITLE; nCntFrame++)
		{
			switch (nCntFrame)
			{
			case 0:

				g_aGears_Title[nCntFrame + AMOUNT_USING_TEX_GEARBIG_TITLE].pos.x += MOVE_SPD_POS_GEARS_TITLE;

				break;

			case 2:

				g_aGears_Title[nCntFrame + AMOUNT_USING_TEX_GEARBIG_TITLE].pos.x -= MOVE_SPD_POS_GEARS_TITLE;

				break;

			default:

				g_aGears_Title[nCntFrame + AMOUNT_USING_TEX_GEARBIG_TITLE].pos.y -= MOVE_SPD_POS_GEARS_TITLE;

				break;
			}
		}
	}

	//���Ԙg�ړ���A���ԏ��ړ��J�n
	if (g_aGears_Title[nCntGears].pos.x >= 137.0f - HALFSPAN_GEARFRAME_TITLE)
	{
		//�Ή��p�[�c�񐔃��[�v�A���Ԕԍ����i�߂�
		for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GEARFRAME_TITLE; nCnt++)
		{
			switch (nCntGears)
			{
			case 2:

				g_aGears_Title[nCntGears].pos.x = 137.0f - HALFSPAN_GEARFRAME_TITLE;

				break;

			case 3:

				g_aGears_Title[nCntGears].pos.y = 934.0f + HALFSPAN_GEARFRAME_TITLE;

				break;

			case 4:

				g_aGears_Title[nCntGears].pos.x = SCREEN_WIDTH - 137.0f + HALFSPAN_GEARFRAME_TITLE;

				break;

			case 5:

				g_aGears_Title[nCntGears].pos.y = 934.0f + HALFSPAN_GEARFRAME_TITLE;

				break;
			}

			nCntGears++;
		}

		if (!bStartRotateSmall)
		{
			bStartRotateSmall = true;
		}
	}

	//���Ԙg�̒��S�_���ړ�����
	if (bStartRotateSmall)
	{
		for (int nCntSmall = 0; nCntSmall < AMOUNT_USING_TEX_GEARSMALL_TITLE; nCntSmall++)
		{
			switch (nCntSmall)
			{
			case 0:

				g_aGears_Title[nCntSmall + AMOUNT_USING_TEX_GEARBIG_TITLE + AMOUNT_USING_TEX_GEARFRAME_TITLE].pos.y -= MOVE_SPD_POS_GEARS_TITLE;

				break;

			case 1:

				g_aGears_Title[nCntSmall + AMOUNT_USING_TEX_GEARBIG_TITLE + AMOUNT_USING_TEX_GEARFRAME_TITLE].pos.y -= MOVE_SPD_POS_GEARS_TITLE;

				break;
			}
		}
	}

	//���ԏ��ړ���
	if (g_aGears_Title[nCntGears].pos.y <= 939.0f + HALFSPAN_GEARSMALL_TITLE)
	{
		//�Ή��p�[�c�񐔃��[�v�A���Ԕԍ����i�߂�
		for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GEARFRAME_TITLE; nCnt++)
		{
			switch (nCntGears)
			{
			case 6:

				g_aGears_Title[nCntGears].pos.y = 939.0f + HALFSPAN_GEARSMALL_TITLE;

				break;

			case 7:

				g_aGears_Title[nCntGears].pos.y = 939.0f + HALFSPAN_GEARSMALL_TITLE;

				break;
			}

			nCntGears++;
		}
	}
}

//************************************************
//���ԌQ��]�֐�
//************************************************
void Gears_Rotate_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_GEARS_TITLE;

	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GEARS_TITLE; nCnt++)
	{
		pVtx_Title[0].pos.x = g_aGears_Title[nCnt].pos.x + sinf(g_aGears_Title[nCnt].rot.z - (D3DX_PI - g_aGears_Title[nCnt].fAngle)) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[0].pos.y = g_aGears_Title[nCnt].pos.y + cosf(g_aGears_Title[nCnt].rot.z - (D3DX_PI - g_aGears_Title[nCnt].fAngle)) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[1].pos.x = g_aGears_Title[nCnt].pos.x + sinf(g_aGears_Title[nCnt].rot.z + (D3DX_PI - g_aGears_Title[nCnt].fAngle)) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[1].pos.y = g_aGears_Title[nCnt].pos.y + cosf(g_aGears_Title[nCnt].rot.z + (D3DX_PI - g_aGears_Title[nCnt].fAngle)) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[2].pos.x = g_aGears_Title[nCnt].pos.x + sinf(g_aGears_Title[nCnt].rot.z - g_aGears_Title[nCnt].fAngle) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[2].pos.y = g_aGears_Title[nCnt].pos.y + cosf(g_aGears_Title[nCnt].rot.z - g_aGears_Title[nCnt].fAngle) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[3].pos.x = g_aGears_Title[nCnt].pos.x + sinf(g_aGears_Title[nCnt].rot.z + g_aGears_Title[nCnt].fAngle) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[3].pos.y = g_aGears_Title[nCnt].pos.y + cosf(g_aGears_Title[nCnt].rot.z + g_aGears_Title[nCnt].fAngle) * g_aGears_Title[nCnt].fLength;

		switch (nCnt)
		{
		case 0:

			g_aGears_Title[nCnt].rot.z += ROTATE_SPD_GEARS_TITLE;

			break;

		case 1:

			g_aGears_Title[nCnt].rot.z -= ROTATE_SPD_GEARS_TITLE;

			break;

		case 2:

			g_aGears_Title[nCnt].rot.z -= ROTATE_SPD_GEARS_TITLE * 1.5f;

			break;

		case 3:

			g_aGears_Title[nCnt].rot.z += ROTATE_SPD_GEARS_TITLE * 1.5f;

			break;

		case 4:

			g_aGears_Title[nCnt].rot.z += ROTATE_SPD_GEARS_TITLE * 1.5f;

			break;

		case 5:

			g_aGears_Title[nCnt].rot.z -= ROTATE_SPD_GEARS_TITLE * 1.5f;

			break;

		case 6:

			g_aGears_Title[nCnt].rot.z += ROTATE_SPD_GEARS_TITLE * 2.0f;

			break;

		case 7:

			g_aGears_Title[nCnt].rot.z -= ROTATE_SPD_GEARS_TITLE * 2.0f;

			break;
		}

		pVtx_Title += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�U�n�g�A�j���[�V�����֐�
//************************************************
void Pigeons_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_PIGEONS_TITLE;

	//�U�n�g�̒��S�_���ړ�����
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_PIGEONS_TITLE; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			g_aPigeons_Title[nCnt].pos.x += MOVE_SPD_PIGEONS_1_TITLE;

			break;

		case 1:

			g_aPigeons_Title[nCnt].pos.x -= MOVE_SPD_PIGEONS_1_TITLE;

			break;
		}

		pVtx_Title[0].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z - (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[0].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z - (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[1].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z + (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[1].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z + (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[2].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z - g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[2].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z - g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[3].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z + g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[3].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z + g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;

		pVtx_Title += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();

	//�U�n�g1�ړ���
	if (g_aPigeons_Title[0].pos.x >= 300.0f)
	{
		g_aPigeons_Title[0].pos.x = 300.0f;	
	
		g_bStartRotate = true;
	}

	//�U�n�g2�ړ���
	if (g_aPigeons_Title[1].pos.x <= 1680.0f)
	{
		g_aPigeons_Title[1].pos.x = 1680.0f;
	}
}

//************************************************
//�U�n�g��]�֐�
//************************************************
void Pigeons_Rotate_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_PIGEONS_TITLE;

	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_PIGEONS_TITLE; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			if (g_aPigeons_Title[nCnt].nCntStop > 0)
			{
				g_aPigeons_Title[nCnt].nCntStop--;
			}
			else
			{
				g_aPigeons_Title[nCnt].fMoveSPD1 *= 0.9935f;
				g_aPigeons_Title[nCnt].fMoveSPD2 *= 0.9935f;
				g_aPigeons_Title[nCnt].fMoveSPD3 *= 0.9935f;

				if (g_aPigeons_Title[nCnt].rot.z < 0.5f && !g_bTurn_1)
				{
					//�ړ�
					g_aPigeons_Title[nCnt].pos.x -= g_aPigeons_Title[nCnt].fMoveSPD1;
					g_aPigeons_Title[nCnt].pos.y -= g_aPigeons_Title[nCnt].fMoveSPD2;

					//��]
					g_aPigeons_Title[nCnt].rot.z += g_aPigeons_Title[nCnt].fMoveSPD3;
				}
				else if (g_aPigeons_Title[nCnt].rot.z >= 0.5f && !g_bTurn_1)
				{
					g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_1_X;
					g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_1_Y;
					g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_1_Z;

					g_bTurn_1 = true;

					g_aPigeons_Title[nCnt].nCntStop = 10 + (rand() % 20);
				}

				if (g_aPigeons_Title[nCnt].rot.z > -0.5f && g_bTurn_1)
				{
					//�ړ�
					g_aPigeons_Title[nCnt].pos.x += g_aPigeons_Title[nCnt].fMoveSPD1;
					g_aPigeons_Title[nCnt].pos.y += g_aPigeons_Title[nCnt].fMoveSPD2;

					//��]
					g_aPigeons_Title[nCnt].rot.z -= g_aPigeons_Title[nCnt].fMoveSPD3;
				}
				else if (g_aPigeons_Title[nCnt].rot.z <= -0.5f && g_bTurn_1)
				{
					g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_1_X;
					g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_1_Y;
					g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_1_Z;

					g_bTurn_1 = false;

					g_aPigeons_Title[nCnt].nCntStop = 10 + (rand() % 20);
				}
			}

			break;

		case 1:

			if (g_aPigeons_Title[nCnt].nCntStop > 0)
			{
				g_aPigeons_Title[nCnt].nCntStop--;
			}
			else
			{
				g_aPigeons_Title[nCnt].fMoveSPD1 *= 0.9935f;
				g_aPigeons_Title[nCnt].fMoveSPD2 *= 0.9935f;
				g_aPigeons_Title[nCnt].fMoveSPD3 *= 0.9935f;

				if (g_aPigeons_Title[nCnt].rot.z < 0.5f && !g_bTurn_2)
				{
					//�ړ�
					g_aPigeons_Title[nCnt].pos.x -= g_aPigeons_Title[nCnt].fMoveSPD1;
					g_aPigeons_Title[nCnt].pos.y += g_aPigeons_Title[nCnt].fMoveSPD2;

					//��]
					g_aPigeons_Title[nCnt].rot.z += g_aPigeons_Title[nCnt].fMoveSPD3;
				}
				else if (g_aPigeons_Title[nCnt].rot.z >= 0.5f && !g_bTurn_2)
				{
					g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_1_X;
					g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_1_Y;
					g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_1_Z;

					g_bTurn_2 = true;

					g_aPigeons_Title[nCnt].nCntStop = 10 + (rand() % 20);
				}

				if (g_aPigeons_Title[nCnt].rot.z > -0.5f && g_bTurn_2)
				{
					//�ړ�
					g_aPigeons_Title[nCnt].pos.x += g_aPigeons_Title[nCnt].fMoveSPD1;
					g_aPigeons_Title[nCnt].pos.y -= g_aPigeons_Title[nCnt].fMoveSPD2;

					//��]
					g_aPigeons_Title[nCnt].rot.z -= g_aPigeons_Title[nCnt].fMoveSPD3;
				}
				else if (g_aPigeons_Title[nCnt].rot.z <= -0.5f && g_bTurn_2)
				{
					g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_1_X;
					g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_1_Y;
					g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_1_Z;

					g_bTurn_2 = false;

					g_aPigeons_Title[nCnt].nCntStop = 10 + (rand() % 20);
				}
			}

			break;
		}

		pVtx_Title[0].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z - (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[0].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z - (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[1].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z + (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[1].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z + (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[2].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z - g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[2].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z - g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[3].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z + g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[3].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z + g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;

		pVtx_Title += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//���͊����A�j���[�V�����֐�
//************************************************
void Press_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_PRESS_TITLE;

	//�F�ς��܂���
	if (g_nColorA_Press_Title < 255 && !g_bChangeColor_Press_Title)
	{
		g_nColorA_Press_Title += CHANGE_SPD_PRESS_COLORA_TITLE;
	}
	
	if (g_nColorA_Press_Title >= 255)
	{
		g_nColorA_Press_Title = 255;

		g_bChangeColor_Press_Title = true;
	}

	if (g_nColorA_Press_Title > 100 && g_bChangeColor_Press_Title)
	{
		g_nColorA_Press_Title -= CHANGE_SPD_PRESS_COLORA_TITLE;
	}
	else
	{
		g_bChangeColor_Press_Title = false;
	}

	//�F�ύX
	pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
	pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
	pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
	pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//�t�F�[�h�A�E�g�֐�
//************************************************
void Fadeout_Animation_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_FADEOUT_TITLE;

	g_nColorA_Fadeout_Title += 25;

	//�F�ς�肷���h�~
	if (g_nColorA_Fadeout_Title >= 255)
	{
		g_nColorA_Fadeout_Title = 255;
	}

	//�F�ύX
	pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
	pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
	pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
	pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

////************************************************
////���ʊ֐�
////************************************************
//float Set_Volume_Title(void)
//{
//	//���ʂ������n��
//	return g_fVolume_BGM_Title;
//}

//************************************************
//�^�C�g�����S�ݒ�֐�
//************************************************
void Setinfo_TitleLogoEX_Title(void)
{
	//�^�C�g�����S����ݒ�
	g_aLogoEX.nStyle = 0;	//���
	g_aLogoEX.pos = D3DXVECTOR3(990.0f, -800.0f, 0.0f);	//�ʒu
	g_aLogoEX.fSpanX = 462.75f;	//�T�C�Y
	g_aLogoEX.fSpanY = 320.0f;	//�T�C�Y
	g_aLogoEX.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ����
	g_aLogoEX.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�������
	g_aLogoEX.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	g_aLogoEX.fLength = sqrtf((g_aLogoEX.fSpanX * g_aLogoEX.fSpanX) + (g_aLogoEX.fSpanY * g_aLogoEX.fSpanY));	//�Ίp��
	g_aLogoEX.fAngle = atan2f(g_aLogoEX.fSpanX * 2.0f, g_aLogoEX.fSpanY * 2.0f);	//�p�x
	g_aLogoEX.bfirst = false;
}

//************************************************
//�^�C�g�����S�A�j���[�V�����֐�
//************************************************
void TitleLogo_AnimationEX_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_LOGO_TITLE;

	//��ꗎ��
	if (g_aLogoEX.pos.y < 720.0f - g_aLogoEX.fSpanY && !g_aLogoEX.bfirst)
	{
		g_aLogoEX.move.y += 0.1f;
		g_aLogoEX.move.z += -0.00002f;

		//�ړ�
		g_aLogoEX.pos.y += g_aLogoEX.move.y;

		//��]
		g_aLogoEX.rot.z += g_aLogoEX.move.z;
	}
	else if (!g_aLogoEX.bfirst)
	{
		g_aLogoEX.move.x = -10.0f;
		g_aLogoEX.move.y = -15.0f;
		g_aLogoEX.move.z = 0.0f;

		g_aLogoEX.bfirst = true;
	}

	//���˂āA
	if (g_aLogoEX.nCntfirst < 30 && g_aLogoEX.bfirst && !g_aLogoEX.bsecond)
	{
		g_aLogoEX.nCntfirst++;

		g_aLogoEX.move.x += 0.25f;
		g_aLogoEX.move.y += 0.8f;
		g_aLogoEX.move.z += 0.0001f;

		//�ړ�
		g_aLogoEX.pos += g_aLogoEX.move;

		//��]
		g_aLogoEX.rot.z += g_aLogoEX.move.z;
	}
	else if (g_aLogoEX.bfirst && !g_aLogoEX.bsecond)
	{
		g_aLogoEX.move.x = 1.0f;
		g_aLogoEX.move.y = 1.0f;
		g_aLogoEX.move.z = 0.0f;

		g_aLogoEX.bsecond = true;
	}

	//�h���
	if (g_aLogoEX.nCntsecond < 45 && g_aLogoEX.bsecond && !g_aLogoEX.bthird)
	{
		g_aLogoEX.nCntsecond++;

		g_aLogoEX.move.x += 0.1f;
		g_aLogoEX.move.y += 0.001f;
g_aLogoEX.move.z += 0.0002f;

//�ړ�
g_aLogoEX.pos.x += g_aLogoEX.move.x;
g_aLogoEX.pos.y += g_aLogoEX.move.y;

//��]
g_aLogoEX.rot.z += g_aLogoEX.move.z;
	}
	else if (g_aLogoEX.bsecond && !g_aLogoEX.bthird)
	{
	g_aLogoEX.fHoldX = 0.2f;
	//g_aLogoEX.fHoldY = 0.15f;
	g_aLogoEX.fHoldZ = 0.000335f;

	g_aLogoEX.bthird = true;
	}

	//�h���(�P��)
	if (g_aLogoEX.bthird)
	{
		if (g_aLogoEX.nCntStop > 0)
		{
			g_aLogoEX.nCntStop--;
		}
		else
		{
			if (!g_aLogoEX.bTurnX)
			{
				g_aLogoEX.move.x += g_aLogoEX.fHoldX;
				g_aLogoEX.move.z += g_aLogoEX.fHoldZ;
			}
			else
			{
				g_aLogoEX.move.x -= g_aLogoEX.fHoldX;
				g_aLogoEX.move.z -= g_aLogoEX.fHoldZ;
			}

			//if (!g_aLogoEX.bTurnY)
			//{
			//	g_aLogoEX.move.y += g_aLogoEX.fHoldY;
			//}
			//else
			//{
			//	g_aLogoEX.move.y -= g_aLogoEX.fHoldY;
			//}

			//�ړ�
			g_aLogoEX.pos.x += g_aLogoEX.move.x;
			//g_aLogoEX.pos.y += g_aLogoEX.move.y;

			if (g_aLogoEX.pos.x < 915.0f)
			{
				g_aLogoEX.nCntStop = 1;
			}
			else if (g_aLogoEX.pos.x > 1075.0f)
			{
				g_aLogoEX.nCntStop = 1;
			}

			if (g_aLogoEX.pos.x > 990.0f)
			{
				g_aLogoEX.bTurnX = true;
			}
			else if (g_aLogoEX.pos.x < 990.0f)
			{
				g_aLogoEX.bTurnX = false;
			}

			//if (g_aLogoEX.pos.y > 370.0f)
			//{
			//	g_aLogoEX.bTurnY = true;
			//}
			//else if (g_aLogoEX.pos.y < 370.0f)
			//{
			//	g_aLogoEX.bTurnY = false;
			//}

			//��]
			g_aLogoEX.rot.z += g_aLogoEX.move.z;
		}
	}

	//�ړ��A��]�𔽉f
	pVtx_Title[0].pos.x = g_aLogoEX.pos.x + sinf(g_aLogoEX.rot.z - (D3DX_PI - g_aLogoEX.fAngle)) * g_aLogoEX.fLength;
	pVtx_Title[0].pos.y = g_aLogoEX.pos.y + cosf(g_aLogoEX.rot.z - (D3DX_PI - g_aLogoEX.fAngle)) * g_aLogoEX.fLength;
	pVtx_Title[1].pos.x = g_aLogoEX.pos.x + sinf(g_aLogoEX.rot.z + (D3DX_PI - g_aLogoEX.fAngle)) * g_aLogoEX.fLength;
	pVtx_Title[1].pos.y = g_aLogoEX.pos.y + cosf(g_aLogoEX.rot.z + (D3DX_PI - g_aLogoEX.fAngle)) * g_aLogoEX.fLength;
	pVtx_Title[2].pos.x = g_aLogoEX.pos.x + sinf(g_aLogoEX.rot.z - g_aLogoEX.fAngle) * g_aLogoEX.fLength;
	pVtx_Title[2].pos.y = g_aLogoEX.pos.y + cosf(g_aLogoEX.rot.z - g_aLogoEX.fAngle) * g_aLogoEX.fLength;
	pVtx_Title[3].pos.x = g_aLogoEX.pos.x + sinf(g_aLogoEX.rot.z + g_aLogoEX.fAngle) * g_aLogoEX.fLength;
	pVtx_Title[3].pos.y = g_aLogoEX.pos.y + cosf(g_aLogoEX.rot.z + g_aLogoEX.fAngle) * g_aLogoEX.fLength;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Title->Unlock();
}

//******************
//�t�F�[�h�A�E�g�֐�
//******************
bool* StartFadeout(void)
{
	return &g_bStartFadeout_Title;
}