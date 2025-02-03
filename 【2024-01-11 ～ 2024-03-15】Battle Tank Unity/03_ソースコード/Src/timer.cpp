//************************************************
//
// �^�C�}�[�\��[timer.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "timer.h"

// �V�X�e��
#include "sound.h"

// ������
#include "enemy.h"
#include "game.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

/*---�y�}�N����`�z---*/
#define AMOUNT_SCORE 4		// �^�C�}�[�\���̍ő吔

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;		// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;	// ���_�o�b�t�@�̃|�C���^
UI g_Timer[AMOUNT_SCORE];						// �^�C�}�[�\���p���

int g_CT_startTimer = 0;	// �^�C�}�[���o�ꂷ��܂ł̒x������

/*---�y�v���g�^�C�v�錾�z---*/
void ImportTexTimer(void);		// �e�N�X�`�����擾
void ImportInfoTimer(void);		// �ݒ�����擾
void CreateVtxTimer(void);		// ���_�o�b�t�@�̐���

void AnimationManager_ArrayTime(void);		// ���ʂȓ���
void AnimationManagerTimer(void);			// �A�j���[�V�����Ǘ�
void PlayAnimationTimer(int i, int type);	// �A�j���[�V�����Đ�
void StopAnimationTimer(int i, int type);	// �A�j���[�V������~

void VibrationSmallTimer(int i);	// �U���F��
void VibrationBigTimer(int i);		// �U���F��
void ChangeRedTimer(int i);			// �Ԃ�
void FadeAppearTimer(int i);		// �o��
void LikeaGummyTimer(int i);		// �u�j��
void AppealtoFrontTimer(int i);		// �`���`��
void SlideUpTimer(int i);			// ��X���C�h�C��
void SlideDownTimer(int i);			// ��
void SlideLeftTimer(int i);			// ��
void SlideRightTimer(int i);		// �E
void DisSlideUpTimer(int i);		// ��X���C�h�A�E�g
void DisSlideDownTimer(int i);		// ��
void DisSlideLeftTimer(int i);		// ��
void DisSlideRightTimer(int i);		// �E

void SetVtxTimer(void);		// �W�J
void DrawNormalTimer(void);	// �ʏ�`��

//************************************************
// ��������
//************************************************
void InitTimer(int joined)
{
	for (int i = 0; i < AMOUNT_SCORE; i++)
	{ // Timer�\�����Z�b�g
		g_Timer[i].use = false;
		g_Timer[i].textype = -1;
		g_Timer[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Timer[i].move = { 0.0f, 0.0f, 0.0f };
		g_Timer[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Timer[i].span = { 0.0f, 0.0f };
		g_Timer[i].angle = 0;
		g_Timer[i].length = 0;
		g_Timer[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // �A�j���[�V������񃊃Z�b�g
			g_Timer[i].play[j].use = false;
			g_Timer[i].play[j].dur = 0;
			g_Timer[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Timer[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Timer[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Timer[i].play[j].span = { 0.0f, 0.0f };
			g_Timer[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// �e�N�X�`����ǂݍ���
	ImportTexTimer();

	// �����擾����
	ImportInfoTimer();

	// �ʏ풸�_�o�b�t�@�̐���
	CreateVtxTimer();

	/**********************************/

	g_CT_startTimer = 160 + (10 * joined);	// �^�C�}�[�\�����o�ꂷ��܂ł̒x���p

	/**********************************/
}

//************************************************
// �I������
//************************************************
void UninitTimer(void)
{
	if (g_pTextureTimer != NULL)
	{ // �e�N�X�`���̔j��
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

	if (g_pVtxBuffTimer != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//************************************************
// �X�V����
//************************************************
void UpdateTimer(void)
{
	// ���ʂȂ��
	AnimationManager_ArrayTime();

	// �A�j���[�V�����Ǘ�
	AnimationManagerTimer();

	// �ʏ�W�J
	SetVtxTimer();
}

//************************************************
// �`�揈��
//************************************************
void DrawTimer(void)
{
	// �ʏ�`��
	DrawNormalTimer();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �e�N�X�`����ǂݍ���
//************************************************
void ImportTexTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\num.png",
		&g_pTextureTimer);
}

//************************************************
// �ݒ����ǂݍ���
//************************************************
void ImportInfoTimer(void)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char str[128] = {};		// ���͂��i�[
	int i = 0;				// �ėp����
	int textype = 0;		// �e�N�X�`�������擾
	D3DXVECTOR3 pos = {};	// �ʒu���i�[
	D3DXVECTOR3 rot = {};	// �������i�[
	D3DXVECTOR2 span = {};	// �傫�����i�[
	D3DXCOLOR col = {};		// �F���i�[

	// Timer����W�J����
	if (fopen_s(&pFile, "data\\TXT\\UI\\timer.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�^�C�}�[�p�z�u���̓W�J�Ɏ��s");

#endif	// _DEBUG�F�t�@�C���W�J�̍���
	}

	while (fscanf_s(pFile, "%s", &str[0], 128) != EOF)
	{
		if (strcmp(&str[0], "TEXTYPE") == 0)
		{ // �e�N�X�`���^�C�v���擾
			fscanf_s(pFile, "%s %d", &str[0], 2, &textype);
		}

		if (strcmp(&str[0], "POS") == 0)
		{ // �ʒu���擾
			fscanf_s(pFile, "%s %f %f %f", &str[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&str[0], "ROT") == 0)
		{ // �������擾
			fscanf_s(pFile, "%s %f %f %f", &str[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&str[0], "SPAN") == 0)
		{ // �傫�����擾
			fscanf_s(pFile, "%s %f %f", &str[0], 2, &span.x, &span.y);
		}

		if (strcmp(&str[0], "COL") == 0)
		{ // �F���擾
			fscanf_s(pFile, "%s %f %f %f %f", &str[0], 2, &col.r, &col.g, &col.b, &col.a);
		}

		if (strcmp(&str[0], "END_PARAMSET") == 0)
		{ // �擾�������𔽉f

			g_Timer[i].use = true;
			g_Timer[i].textype = textype;
			g_Timer[i].pos = pos;
			g_Timer[i].rot = rot;
			g_Timer[i].span = span;
			g_Timer[i].col = col;

			i++;	// ���̔ԍ���
		}

		if (strcmp(&str[0], "END_SCRIPT") == 0)
		{
			break;	// �I��
		}
	}

	// �t�@�C�������
	fclose(pFile);
}

//************************************************
// ���_�o�b�t�@�̐���
//************************************************
void CreateVtxTimer(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SCORE; i++, pVtx += AMOUNT_VTX)
	{
		// ���_���W�̏����ݒ�
		pVtx[0].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[1].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[2].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[3].pos = { 0.0f, 0.0f, 0.0f };

		// ���Z���̏����ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = { 0.0f, 0.0f };
		pVtx[1].tex = { 1.0f, 0.0f };
		pVtx[2].tex = { 0.0f, 1.0f };
		pVtx[3].tex = { 1.0f, 1.0f };
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}

////************************************************
//// �A�j���[�V�����I��
////************************************************
//void SelectAnimationTimer(void)
//{
//	int i = g_select;	// ���ʊȗ���
//
//	// �Đ�����A�j���[�V������ύX����
//	if (GetKeyboardTrigger(DIK_1))
//	{
//		g_animaType > 0 ? g_animaType-- : g_animaType = ANIMATION_TYPE_MAX - 1;
//	}
//	else if (GetKeyboardTrigger(DIK_2))
//	{
//		g_animaType < ANIMATION_TYPE_MAX - 1 ? g_animaType++ : g_animaType = 0;
//	}
//
//	// �Ή�����A�j���[�V�������Đ�
//	if (GetKeyboardTrigger(DIK_3))
//	{
//		switch (g_animaType)
//		{
//		case ANIMATION_TYPE_VIBSMALL:
//
//			g_Timer[i].play[ANIMATION_TYPE_VIBSMALL].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_VIBSMALL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_VIBBIG:
//
//			g_Timer[i].play[ANIMATION_TYPE_VIBBIG].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_VIBBIG].dur = 15;
//
//			break;
//
//		case ANIMATION_TYPE_RED:
//
//			g_Timer[i].play[ANIMATION_TYPE_RED].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_RED].dur = 20;
//
//			break;
//
//		case ANIMATION_TYPE_FADE:
//
//			g_Timer[i].play[ANIMATION_TYPE_FADE].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_FADE].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_GUMMY:
//
//			g_Timer[i].play[ANIMATION_TYPE_GUMMY].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_APPEAL:
//
//			g_Timer[i].play[ANIMATION_TYPE_APPEAL].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_APPEAL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEUP:
//
//			g_Timer[i].play[ANIMATION_TYPE_SLIDEUP].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_SLIDEUP].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEDOWN:
//
//			g_Timer[i].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDELEFT:
//
//			g_Timer[i].play[ANIMATION_TYPE_SLIDELEFT].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDERIGHT:
//
//			g_Timer[i].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_DISUP:
//
//			g_Timer[i].play[ANIMATION_TYPE_DISUP].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_DISUP].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISDOWN:
//
//			g_Timer[i].play[ANIMATION_TYPE_DISDOWN].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_DISDOWN].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISLEFT:
//
//			g_Timer[i].play[ANIMATION_TYPE_DISLEFT].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_DISLEFT].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISRIGHT:
//
//			g_Timer[i].play[ANIMATION_TYPE_DISRIGHT].use = true;
//			g_Timer[i].play[ANIMATION_TYPE_DISRIGHT].dur = 40;
//
//			break;
//		}
//	}
//}

//************************************************
// ���ʂȂ��
//************************************************
void AnimationManager_ArrayTime(void)
{
	g_CT_startTimer > 0 ? g_CT_startTimer-- : g_CT_startTimer = 0;

	if (g_CT_startTimer == 1)
	{
		g_Timer[0].play[ANIMATION_TYPE_FADE].use = true;
		g_Timer[0].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Timer[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	for (int i = 0; i < AMOUNT_SCORE - 1; i++)
	{
		if (g_Timer[i].play[ANIMATION_TYPE_FADE].dur == 50)
		{
			g_Timer[i + 1].play[ANIMATION_TYPE_FADE].use = true;
			g_Timer[i + 1].play[ANIMATION_TYPE_FADE].dur = 60;

			g_Timer[i + 1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}
}

//************************************************
// �A�j���[�V�����Ǘ�
//************************************************
void AnimationManagerTimer(void)
{
	for (int i = 0; i < AMOUNT_SCORE; i++)
	{
		if (!g_Timer[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ǂ̃A�j���[�V�������Đ�����̂��I��
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Timer[i].play[j].use)
			{
				// �Ή�����A�j���[�V�������Đ�����
				PlayAnimationTimer(i, j);
			}
		}
	}
}

//************************************************
// ��ނɑΉ������A�j���[�V�����Đ�
//************************************************
void PlayAnimationTimer(int id, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallTimer(id);	// �U���F��

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigTimer(id);	// �U���F��

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedTimer(id);	// �Ԃ��Ȃ�

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearTimer(id);	// �t�F�[�h

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyTimer(id);	// �u�j��

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontTimer(id);	// �o����

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpTimer(id);	// ��X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownTimer(id);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftTimer(id);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightTimer(id);	// �E�X���C�h�C��

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpTimer(id);	// ��X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownTimer(id);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftTimer(id);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightTimer(id);	// �E�X���C�h�A�E�g

		break;
	}
}

//************************************************
// �A�j���[�V������~
//************************************************
void StopAnimationTimer(int id, int type)
{
	g_Timer[id].play[type] =
	{
		false,
		0,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
	};
}

//************************************************
// �U���F��
//************************************************
void VibrationSmallTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// �U���F��
//************************************************
void VibrationBigTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// �Ԃ��Ȃ�
//************************************************
void ChangeRedTimer(int id)
{
	if (g_Timer[id].play[ANIMATION_TYPE_RED].dur > 10)
	{
		g_Timer[id].play[ANIMATION_TYPE_RED].col.g += -0.1f;
		g_Timer[id].play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		g_Timer[id].play[ANIMATION_TYPE_RED].col.g += 0.1f;
		g_Timer[id].play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_RED].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_RED);
	}
}

//************************************************
// �o��
//************************************************
void FadeAppearTimer(int id)
{
	if (g_Timer[id].play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		g_Timer[id].play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		g_Timer[id].play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - g_Timer[id].play[ANIMATION_TYPE_FADE].dur));
	}

	if (g_Timer[id].play[ANIMATION_TYPE_FADE].dur == 40)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_FADE].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// �u�j��
//************************************************
void LikeaGummyTimer(int id)
{
	if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Timer[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Timer[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_GUMMY].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// �`���`��
//************************************************
void AppealtoFrontTimer(int id)
{
	if (g_Timer[id].play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		g_Timer[id].play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	g_Timer[id].play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_APPEAL].dur))
	{
		g_Timer[id].play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// ��X���C�h�C��
//************************************************
void SlideUpTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - g_Timer[id].play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideDownTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - g_Timer[id].play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideLeftTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - g_Timer[id].play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// �E�X���C�h�C��
//************************************************
void SlideRightTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - g_Timer[id].play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// ��X���C�h�A�E�g
//************************************************
void DisSlideUpTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / g_Timer[id].play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_DISUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideDownTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / g_Timer[id].play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideLeftTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / g_Timer[id].play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// �E�X���C�h�A�E�g
//************************************************
void DisSlideRightTimer(int id)
{
	g_Timer[id].play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / g_Timer[id].play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Timer[id].play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationTimer(id, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// ���_��W�J
//************************************************
void SetVtxTimer(void)
{
	AnimationParam general[AMOUNT_SCORE] = {};	// �Đ��p�����܂Ƃ߂�

	for (int i = 0; i < AMOUNT_SCORE; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_Timer[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// �Đ��p�̋^�������܂Ƃ߂�
			general[i].move += g_Timer[i].play[j].move;
			general[i].pos += g_Timer[i].play[j].pos;
			general[i].rot += g_Timer[i].play[j].rot;
			general[i].span += g_Timer[i].play[j].span;
			general[i].col += g_Timer[i].play[j].col;
		}

		// �p�x���Z�o
		g_Timer[i].angle = atan2f(g_Timer[i].span.x + general[i].span.x, g_Timer[i].span.y + general[i].span.y);

		// �Ίp�����Z�o
		g_Timer[i].length = sqrtf((g_Timer[i].span.x + general[i].span.x) * (g_Timer[i].span.x + general[i].span.x) +
			(g_Timer[i].span.y + general[i].span.y) * (g_Timer[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;						// ���_���ւ̃|�C���^
	int phaseTimer = GetInfoPhaseTimer();	// �t�F�[�Y�^�C�}�[���擾

	// 60�i���Ɋ��Z
	int dev = phaseTimer / 60;
	phaseTimer += (40 * dev);

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SCORE; i++, pVtx += AMOUNT_VTX)
	{ // ���_���W�̐ݒ�

		int value = phaseTimer % 10;
		phaseTimer /= 10;

		pVtx[0].pos =
		{
			g_Timer[i].pos.x + general[i].pos.x + sinf((g_Timer[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Timer[i].angle)) * g_Timer[i].length,
			g_Timer[i].pos.y + general[i].pos.y + cosf((g_Timer[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Timer[i].angle)) * g_Timer[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Timer[i].pos.x + general[i].pos.x + sinf((g_Timer[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Timer[i].angle)) * g_Timer[i].length,
			g_Timer[i].pos.y + general[i].pos.y + cosf((g_Timer[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Timer[i].angle)) * g_Timer[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Timer[i].pos.x + general[i].pos.x + sinf((g_Timer[i].rot.z + general[i].rot.z) - (g_Timer[i].angle)) * g_Timer[i].length,
			g_Timer[i].pos.y + general[i].pos.y + cosf((g_Timer[i].rot.z + general[i].rot.z) - (g_Timer[i].angle)) * g_Timer[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Timer[i].pos.x + general[i].pos.x + sinf((g_Timer[i].rot.z + general[i].rot.z) + (g_Timer[i].angle)) * g_Timer[i].length,
			g_Timer[i].pos.y + general[i].pos.y + cosf((g_Timer[i].rot.z + general[i].rot.z) + (g_Timer[i].angle)) * g_Timer[i].length,
			0.0f
		};

		// �F�̔��f
		pVtx[0].col = g_Timer[i].col + general[i].col;
		pVtx[1].col = g_Timer[i].col + general[i].col;
		pVtx[2].col = g_Timer[i].col + general[i].col;
		pVtx[3].col = g_Timer[i].col + general[i].col;

		// �e�N�X�`���̔��f
		pVtx[0].tex = { value * 0.1f, 0.0f };
		pVtx[1].tex = { (value + 1) * 0.1f, 0.0f };
		pVtx[2].tex = { value * 0.1f, 1.0f };
		pVtx[3].tex = { (value + 1) * 0.1f, 1.0f };
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}

//************************************************
// �ʏ�`�揈��
//************************************************
void DrawNormalTimer(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_SCORE; i++)
	{
		if (!g_Timer[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		pDevice->SetTexture(0, g_pTextureTimer);

		// �e�X�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}