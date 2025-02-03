//************************************************
//
// �X�R�A�\��[score.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "score.h"

// �V�X�e��
#include "sound.h"

// ������
#include "game.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

/*---�y�}�N����`�z---*/
#define AMOUNT_SCORE 8		// �X�R�A�\���̍ő吔

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;		// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;	// ���_�o�b�t�@�̃|�C���^
UI g_Score[AMOUNT_SCORE];						// �X�R�A�\���p���

int g_Score_old = 0;		// �ߋ��̃X�R�A
int g_CT_startScore = 0;	// �X�R�A�\�����o�ꂷ��܂ł̒x���p

/*---�y�v���g�^�C�v�錾�z---*/
void ImportTexScore(void);		// �e�N�X�`�����擾
void ImportInfoScore(void);		// �ݒ�����擾
void CreateVtxScore(void);		// ���_�o�b�t�@�̐���

void AnimationManager_Array(void);			// ���ʂȓ���
void AnimationManagerScore(void);			// �A�j���[�V�����Ǘ�
void PlayAnimationScore(int i, int type);	// �A�j���[�V�����Đ�
void StopAnimationScore(int i, int type);	// �A�j���[�V������~

void VibrationSmallScore(int i);	// �U���F��
void VibrationBigScore(int i);		// �U���F��
void ChangeRedScore(int i);			// �Ԃ�
void FadeAppearScore(int i);		// �o��
void LikeaGummyScore(int i);		// �u�j��
void AppealtoFrontScore(int i);		// �`���`��
void SlideUpScore(int i);			// ��X���C�h�C��
void SlideDownScore(int i);			// ��
void SlideLeftScore(int i);			// ��
void SlideRightScore(int i);		// �E
void DisSlideUpScore(int i);		// ��X���C�h�A�E�g
void DisSlideDownScore(int i);		// ��
void DisSlideLeftScore(int i);		// ��
void DisSlideRightScore(int i);		// �E

void SetVtxScore(void);		// �W�J
void DrawNormalScore(void);	// �ʏ�`��

//************************************************
// ��������
//************************************************
void InitScore(int joined)
{
	g_Score_old = 0;		// �ߋ��̃X�R�A
	g_CT_startScore = 0;	// �X�R�A�\�����o�ꂷ��܂ł̒x���p

	for (int i = 0; i < AMOUNT_SCORE; i++)
	{ // Score�\�����Z�b�g
		g_Score[i].use = false;
		g_Score[i].textype = -1;
		g_Score[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Score[i].move = { 0.0f, 0.0f, 0.0f };
		g_Score[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Score[i].span = { 0.0f, 0.0f };
		g_Score[i].angle = 0;
		g_Score[i].length = 0;
		g_Score[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // �A�j���[�V������񃊃Z�b�g
			g_Score[i].play[j].use = false;
			g_Score[i].play[j].dur = 0;
			g_Score[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Score[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Score[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Score[i].play[j].span = { 0.0f, 0.0f };
			g_Score[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// �e�N�X�`����ǂݍ���
	ImportTexScore();

	// �����擾����
	ImportInfoScore();

	// �ʏ풸�_�o�b�t�@�̐���
	CreateVtxScore();

	/**********************************/

	g_CT_startScore = 120 + (10 * joined);	// �X�R�A�\�����o�ꂷ��܂ł̒x���p

	/**********************************/
}

//************************************************
// �I������
//************************************************
void UninitScore(void)
{
	if (g_pTextureScore != NULL)
	{ // �e�N�X�`���̔j��
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	if (g_pVtxBuffScore != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//************************************************
// �X�V����
//************************************************
void UpdateScore(void)
{
	// ���ʂȂ��
	AnimationManager_Array();

	// �A�j���[�V�����Ǘ�
	AnimationManagerScore();

	// �ʏ�W�J
	SetVtxScore();
}

//************************************************
// �`�揈��
//************************************************
void DrawScore(void)
{
	// �ʏ�`��
	DrawNormalScore();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �e�N�X�`����ǂݍ���
//************************************************
void ImportTexScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\num.png",
		&g_pTextureScore);
}

//************************************************
// �ݒ����ǂݍ���
//************************************************
void ImportInfoScore(void)
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

	// Score����W�J����
	if (fopen_s(&pFile, "data\\TXT\\UI\\score.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�X�R�A�p�z�u���̓W�J�Ɏ��s");

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

			g_Score[i].use = true;
			g_Score[i].textype = textype;
			g_Score[i].pos = pos;
			g_Score[i].rot = rot;
			g_Score[i].span = span;
			g_Score[i].col = col;

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
void CreateVtxScore(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffScore->Unlock();
}

////************************************************
//// �A�j���[�V�����I��
////************************************************
//void SelectAnimationScore(void)
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
//			g_Score[i].play[ANIMATION_TYPE_VIBSMALL].use = true;
//			g_Score[i].play[ANIMATION_TYPE_VIBSMALL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_VIBBIG:
//
//			g_Score[i].play[ANIMATION_TYPE_VIBBIG].use = true;
//			g_Score[i].play[ANIMATION_TYPE_VIBBIG].dur = 15;
//
//			break;
//
//		case ANIMATION_TYPE_RED:
//
//			g_Score[i].play[ANIMATION_TYPE_RED].use = true;
//			g_Score[i].play[ANIMATION_TYPE_RED].dur = 20;
//
//			break;
//
//		case ANIMATION_TYPE_FADE:
//
//			g_Score[i].play[ANIMATION_TYPE_FADE].use = true;
//			g_Score[i].play[ANIMATION_TYPE_FADE].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_GUMMY:
//
//			g_Score[i].play[ANIMATION_TYPE_GUMMY].use = true;
//			g_Score[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_APPEAL:
//
//			g_Score[i].play[ANIMATION_TYPE_APPEAL].use = true;
//			g_Score[i].play[ANIMATION_TYPE_APPEAL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEUP:
//
//			g_Score[i].play[ANIMATION_TYPE_SLIDEUP].use = true;
//			g_Score[i].play[ANIMATION_TYPE_SLIDEUP].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEDOWN:
//
//			g_Score[i].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
//			g_Score[i].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDELEFT:
//
//			g_Score[i].play[ANIMATION_TYPE_SLIDELEFT].use = true;
//			g_Score[i].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDERIGHT:
//
//			g_Score[i].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
//			g_Score[i].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_DISUP:
//
//			g_Score[i].play[ANIMATION_TYPE_DISUP].use = true;
//			g_Score[i].play[ANIMATION_TYPE_DISUP].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISDOWN:
//
//			g_Score[i].play[ANIMATION_TYPE_DISDOWN].use = true;
//			g_Score[i].play[ANIMATION_TYPE_DISDOWN].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISLEFT:
//
//			g_Score[i].play[ANIMATION_TYPE_DISLEFT].use = true;
//			g_Score[i].play[ANIMATION_TYPE_DISLEFT].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISRIGHT:
//
//			g_Score[i].play[ANIMATION_TYPE_DISRIGHT].use = true;
//			g_Score[i].play[ANIMATION_TYPE_DISRIGHT].dur = 40;
//
//			break;
//		}
//	}
//}

//************************************************
// ���ʂȂ��
//************************************************
void AnimationManager_Array(void)
{
	g_CT_startScore > 0 ? g_CT_startScore-- : g_CT_startScore = 0;

	if (g_CT_startScore == 1)
	{
		g_Score[0].play[ANIMATION_TYPE_FADE].use = true;
		g_Score[0].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Score[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	for (int i = 0; i < AMOUNT_SCORE - 1; i++)
	{
		if (g_Score[i].play[ANIMATION_TYPE_FADE].dur == 50)
		{
			g_Score[i + 1].play[ANIMATION_TYPE_FADE].use = true;
			g_Score[i + 1].play[ANIMATION_TYPE_FADE].dur = 60;

			g_Score[i + 1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}
}

//************************************************
// �A�j���[�V�����Ǘ�
//************************************************
void AnimationManagerScore(void)
{
	for (int i = 0; i < AMOUNT_SCORE; i++)
	{
		if (!g_Score[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ǂ̃A�j���[�V�������Đ�����̂��I��
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Score[i].play[j].use)
			{
				// �Ή�����A�j���[�V�������Đ�����
				PlayAnimationScore(i, j);
			}
		}
	}
}

//************************************************
// ��ނɑΉ������A�j���[�V�����Đ�
//************************************************
void PlayAnimationScore(int id, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallScore(id);	// �U���F��

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigScore(id);	// �U���F��

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedScore(id);	// �Ԃ��Ȃ�

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearScore(id);	// �t�F�[�h

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyScore(id);	// �u�j��

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontScore(id);	// �o����

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpScore(id);	// ��X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownScore(id);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftScore(id);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightScore(id);	// �E�X���C�h�C��

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpScore(id);	// ��X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownScore(id);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftScore(id);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightScore(id);	// �E�X���C�h�A�E�g

		break;
	}
}

//************************************************
// �A�j���[�V������~
//************************************************
void StopAnimationScore(int id, int type)
{
	g_Score[id].play[type] =
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
void VibrationSmallScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// �U���F��
//************************************************
void VibrationBigScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// �Ԃ��Ȃ�
//************************************************
void ChangeRedScore(int id)
{
	if (g_Score[id].play[ANIMATION_TYPE_RED].dur > 10)
	{
		g_Score[id].play[ANIMATION_TYPE_RED].col.g += -0.1f;
		g_Score[id].play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		g_Score[id].play[ANIMATION_TYPE_RED].col.g += 0.1f;
		g_Score[id].play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_RED].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_RED);
	}
}

//************************************************
// �o��
//************************************************
void FadeAppearScore(int id)
{
	if (g_Score[id].play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		g_Score[id].play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		g_Score[id].play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - g_Score[id].play[ANIMATION_TYPE_FADE].dur));
	}

	if (g_Score[id].play[ANIMATION_TYPE_FADE].dur == 40)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_FADE].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// �u�j��
//************************************************
void LikeaGummyScore(int id)
{
	if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		g_Score[id].play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		g_Score[id].play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		g_Score[id].play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		g_Score[id].play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Score[id].play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Score[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Score[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_GUMMY].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// �`���`��
//************************************************
void AppealtoFrontScore(int id)
{
	if (g_Score[id].play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		g_Score[id].play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	g_Score[id].play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_APPEAL].dur))
	{
		g_Score[id].play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// ��X���C�h�C��
//************************************************
void SlideUpScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - g_Score[id].play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideDownScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - g_Score[id].play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideLeftScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - g_Score[id].play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// �E�X���C�h�C��
//************************************************
void SlideRightScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - g_Score[id].play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// ��X���C�h�A�E�g
//************************************************
void DisSlideUpScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / g_Score[id].play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_DISUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideDownScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / g_Score[id].play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideLeftScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / g_Score[id].play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// �E�X���C�h�A�E�g
//************************************************
void DisSlideRightScore(int id)
{
	g_Score[id].play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / g_Score[id].play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Score[id].play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationScore(id, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// ���_��W�J
//************************************************
void SetVtxScore(void)
{
	AnimationParam general[AMOUNT_SCORE] = {};	// �Đ��p�����܂Ƃ߂�

	for (int i = 0; i < AMOUNT_SCORE; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_Score[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// �Đ��p�̋^�������܂Ƃ߂�
			general[i].move += g_Score[i].play[j].move;
			general[i].pos += g_Score[i].play[j].pos;
			general[i].rot += g_Score[i].play[j].rot;
			general[i].span += g_Score[i].play[j].span;
			general[i].col += g_Score[i].play[j].col;
		}

		// �p�x���Z�o
		g_Score[i].angle = atan2f(g_Score[i].span.x + general[i].span.x, g_Score[i].span.y + general[i].span.y);

		// �Ίp�����Z�o
		g_Score[i].length = sqrtf((g_Score[i].span.x + general[i].span.x) * (g_Score[i].span.x + general[i].span.x) +
			(g_Score[i].span.y + general[i].span.y) * (g_Score[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;				// ���_���ւ̃|�C���^
	int* score = GetInfoScore();	// �X�R�A�擾
	int copy = *score;				// �X�R�A�R�s�[

	if (g_Score_old != *score)
	{ // �X�R�A�ɕϓ��������
		
		for (int i = 0; i < AMOUNT_SCORE; i++)
		{
			g_Score[i].play[ANIMATION_TYPE_GUMMY].use = true;
			g_Score[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
		}
	}

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_SCORE; i++, pVtx += AMOUNT_VTX)
	{ // ���_���W�̐ݒ�

		int value = copy % 10;
		copy /= 10;

		pVtx[0].pos =
		{
			g_Score[i].pos.x + general[i].pos.x + sinf((g_Score[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Score[i].angle)) * g_Score[i].length,
			g_Score[i].pos.y + general[i].pos.y + cosf((g_Score[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Score[i].angle)) * g_Score[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Score[i].pos.x + general[i].pos.x + sinf((g_Score[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Score[i].angle)) * g_Score[i].length,
			g_Score[i].pos.y + general[i].pos.y + cosf((g_Score[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Score[i].angle)) * g_Score[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Score[i].pos.x + general[i].pos.x + sinf((g_Score[i].rot.z + general[i].rot.z) - (g_Score[i].angle)) * g_Score[i].length,
			g_Score[i].pos.y + general[i].pos.y + cosf((g_Score[i].rot.z + general[i].rot.z) - (g_Score[i].angle)) * g_Score[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Score[i].pos.x + general[i].pos.x + sinf((g_Score[i].rot.z + general[i].rot.z) + (g_Score[i].angle)) * g_Score[i].length,
			g_Score[i].pos.y + general[i].pos.y + cosf((g_Score[i].rot.z + general[i].rot.z) + (g_Score[i].angle)) * g_Score[i].length,
			0.0f
		};

		// �F�̔��f
		pVtx[0].col = g_Score[i].col + general[i].col;
		pVtx[1].col = g_Score[i].col + general[i].col;
		pVtx[2].col = g_Score[i].col + general[i].col;
		pVtx[3].col = g_Score[i].col + general[i].col;

		// �e�N�X�`���̔��f
		pVtx[0].tex = { value * 0.1f, 0.0f };
		pVtx[1].tex = { (value + 1) * 0.1f, 0.0f };
		pVtx[2].tex = { value * 0.1f, 1.0f };
		pVtx[3].tex = { (value + 1) * 0.1f, 1.0f };
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

	g_Score_old = *score;
}

//************************************************
// �ʏ�`�揈��
//************************************************
void DrawNormalScore(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_SCORE; i++)
	{
		if (!g_Score[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		pDevice->SetTexture(0, g_pTextureScore);

		// �e�X�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}