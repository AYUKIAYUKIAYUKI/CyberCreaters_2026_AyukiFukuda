//************************************************
//
// ���C�t�\��[life.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "life.h"

// �V�X�e��
#include "sound.h"

// ������
#include "player.h"
#include "game.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

/*---�y�}�N����`�z---*/
#define AMOUNT_LIFE 8		// ���C�t�\���̍ő吔
#define AMOUNT_LIFENUM	4	// �����̍ő吔

/*---�y�e�N�X�`�����ށz---*/
typedef enum
{
	TEXTURE_TYPE_LIFE_SIRCLE = 0,	// �\���g
	TEXTURE_TYPE_LIFE_HEART,		// �n�[�g
	TEXTURE_TYPE_LIFE_MAX
} TEXTURE_TYPE_LIFE;

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DTEXTURE9 g_pTextureLife[TEXTURE_TYPE_LIFE_MAX] = {};	// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureLifeNum = NULL;					// �����e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;					// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLifeNum = NULL;				// �������_�o�b�t�@�̃|�C���^
UI g_Life[AMOUNT_LIFE];											// ���C�t�\���p���
UI g_LifeNum[AMOUNT_LIFENUM];									// �����\���p���

int g_CT_startLife = 0;				// ���C�t�\�����o�ꂷ��܂ł̒x���p
int g_CT_vibHeart = 0;				// �n�[�g���L�����������Ԃ��Ǘ�
int g_Life_old[MAX_PLAYER] = {};	// �ߋ��̃��C�t

/*---�y�v���g�^�C�v�錾�z---*/
void ImportTexLife(void);			// �e�N�X�`�����擾
void ImportInfoLife(int joined);	// �ݒ�����擾
void CreateVtxLife(void);			// ���_�o�b�t�@�̐���

void AnimationManagerLife_Second(void);		// ���C�t�\���p�A�j���[�V�������ʊǗ�
void AnimationManagerLife(void);			// �A�j���[�V�����Ǘ�
void PlayAnimationLife(UI* p, int type);	// �A�j���[�V�����Đ�
void StopAnimationLife(UI* p, int type);	// �A�j���[�V������~

void VibrationSmallLife(UI* p);	// �U���F��
void VibrationBigLife(UI* p);	// �U���F��
void ChangeRedLife(UI* p);		// �Ԃ�
void FadeAppearLife(UI* p);		// �o��
void LikeaGummyLife(UI* p);		// �u�j��
void AppealtoFrontLife(UI* p);	// �`���`��
void SlideUpLife(UI* p);		// ��X���C�h�C��
void SlideDownLife(UI* p);		// ��
void SlideLeftLife(UI* p);		// ��
void SlideRightLife(UI* p);		// �E
void DisSlideUpLife(UI* p);		// ��X���C�h�A�E�g
void DisSlideDownLife(UI* p);	// ��
void DisSlideLeftLife(UI* p);	// ��
void DisSlideRightLife(UI* p);	// �E

void SetVtxLife(void);		// �W�J
void DrawNormalLife(void);	// �ʏ�`��

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ImportTexLifeNum(void);		// �e�N�X�`�����擾
void ImportInfoLifeNum(int joined);	// �ݒ�����擾
void CreateVtxLifeNum(void);		// ���_�o�b�t�@�̐���

void AnimationManagerLifeNum_EX(void);	// �����p�A�j���[�V�������ʊǗ�
void AnimationManagerLifeNum(void);		// �����A�j���[�V�����Ǘ�

void SetVtxLifeNum(void);		// �W�J
void DrawNormalLifeNum(void);	// �ʏ�`��

//************************************************
// ��������
//************************************************
void InitLife(int joined)
{
	g_CT_startLife = 0;	// ���C�t�\�����o�ꂷ��܂ł̒x���p
	g_CT_vibHeart = 0;	// �n�[�g���L�����������Ԃ��Ǘ�

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_Life_old[i] = 0;	// ���C�t�̏������Z�b�g
	}

	for (int i = 0; i < AMOUNT_LIFE; i++)
	{ // Life�\�����Z�b�g
		g_Life[i].use = false;
		g_Life[i].textype = -1;
		g_Life[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Life[i].move = { 0.0f, 0.0f, 0.0f };
		g_Life[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Life[i].span = { 0.0f, 0.0f };
		g_Life[i].angle = 0;
		g_Life[i].length = 0;
		g_Life[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // �A�j���[�V������񃊃Z�b�g
			g_Life[i].play[j].use = false;
			g_Life[i].play[j].dur = 0;
			g_Life[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Life[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Life[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Life[i].play[j].span = { 0.0f, 0.0f };
			g_Life[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// �e�N�X�`����ǂݍ���
	ImportTexLife();

	// �����擾����
	ImportInfoLife(joined);

	// �ʏ풸�_�o�b�t�@�̐���
	CreateVtxLife();

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_LIFENUM; i++)
	{ // �����p��񃊃Z�b�g
		g_LifeNum[i].use = false;
		g_LifeNum[i].textype = -1;
		g_LifeNum[i].pos = { 0.0f, 0.0f, 0.0f };
		g_LifeNum[i].move = { 0.0f, 0.0f, 0.0f };
		g_LifeNum[i].rot = { 0.0f, 0.0f, 0.0f };
		g_LifeNum[i].span = { 0.0f, 0.0f };
		g_LifeNum[i].angle = 0;
		g_LifeNum[i].length = 0;
		g_LifeNum[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // �A�j���[�V������񃊃Z�b�g
			g_LifeNum[i].play[j].use = false;
			g_LifeNum[i].play[j].dur = 0;
			g_LifeNum[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_LifeNum[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_LifeNum[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_LifeNum[i].play[j].span = { 0.0f, 0.0f };
			g_LifeNum[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// �e�N�X�`����ǂݍ���
	ImportTexLifeNum();

	// �����擾����
	ImportInfoLifeNum(joined);

	// �ʏ풸�_�o�b�t�@�̐���
	CreateVtxLifeNum();

	/**********************************/

	g_CT_startLife = 40;	// ���C�t�\�����o�ꂷ��܂ł̒x���p
	g_CT_vibHeart = 180;	// �n�[�g���L������������

	/**********************************/
}

//************************************************
// �I������
//************************************************
void UninitLife(void)
{
	for (int i = 0; i < TEXTURE_TYPE_LIFE_MAX; i++)
	{
		if (g_pTextureLife[i] != NULL)
		{ // �e�N�X�`���̔j��
			g_pTextureLife[i]->Release();
			g_pTextureLife[i] = NULL;
		}
	}

	if (g_pVtxBuffLife != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//************************************************
// �X�V����
//************************************************
void UpdateLife(void)
{
	// ���C�t�p���ʃA�j���[�V����
	AnimationManagerLife_Second();

	// �A�j���[�V�����Ǘ�
	AnimationManagerLife();

	// �����p���ʃA�j���[�V����
	AnimationManagerLifeNum_EX();

	// �����A�j���[�V�����Ǘ�
	AnimationManagerLifeNum();

	// �ʏ�W�J
	SetVtxLife();

	// �����ʏ�W�J
	SetVtxLifeNum();
}

//************************************************
// �`�揈��
//************************************************
void DrawLife(void)
{
	// �ʏ�`��
	DrawNormalLife();

	// �����ʏ�`��
	DrawNormalLifeNum();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �e�N�X�`����ǂݍ���
//************************************************
void ImportTexLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ��ݗp
	const char* pFileName[TEXTURE_TYPE_LIFE_MAX] =
	{
		"data\\TEXTURE\\lifecircle.png",
		"data\\TEXTURE\\heart.png",
	};

	for (int i = 0; i < TEXTURE_TYPE_LIFE_MAX; i++)
	{ // �e�N�X�`���̐���

		if (pFileName[i] == NULL)
		{
			break;	// �摜�������Ȃ��Ă��I��
		}

		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureLife[i]);
	}
}

//************************************************
// �ݒ����ǂݍ���
//************************************************
void ImportInfoLife(int joined)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char str[128] = {};		// ���͂��i�[
	int set = 0;			// ���l�p��
	int i = 0;				// �ėp����
	int textype = 0;		// �e�N�X�`�������擾
	D3DXVECTOR3 pos = {};	// �ʒu���i�[
	D3DXVECTOR3 rot = {};	// �������i�[
	D3DXVECTOR2 span = {};	// �傫�����i�[
	D3DXCOLOR col = {};		// �F���i�[

	// Life����W�J����
	if (fopen_s(&pFile, "data\\TXT\\UI\\life.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "���C�t�p�z�u���̓W�J�Ɏ��s");

#endif	// _DEBUG�F�t�@�C���W�J�̍���
	}

	while (fscanf_s(pFile, "%s", &str[0], 128) != EOF)
	{
		if (strcmp(&str[0], "SET") == 0)
		{ // �Q���l�����擾
			fscanf_s(pFile, "%s %d", &str[0], 2, &set);
		}

		if (set != joined)
		{ // �Ή�����Z�b�g�݂̂��擾
			continue;
		}

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

			g_Life[i].use = true;
			g_Life[i].textype = textype;
			g_Life[i].pos = pos;
			g_Life[i].rot = rot;
			g_Life[i].span = span;
			g_Life[i].col = col;

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
void CreateVtxLife(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_LIFE; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffLife->Unlock();
}

////************************************************
//// �A�j���[�V�����I��
////************************************************
//void SelectAnimationLife(void)
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
//			g_Life[i].play[ANIMATION_TYPE_VIBSMALL].use = true;
//			g_Life[i].play[ANIMATION_TYPE_VIBSMALL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_VIBBIG:
//
//			g_Life[i].play[ANIMATION_TYPE_VIBBIG].use = true;
//			g_Life[i].play[ANIMATION_TYPE_VIBBIG].dur = 15;
//
//			break;
//
//		case ANIMATION_TYPE_RED:
//
//			g_Life[i].play[ANIMATION_TYPE_RED].use = true;
//			g_Life[i].play[ANIMATION_TYPE_RED].dur = 20;
//
//			break;
//
//		case ANIMATION_TYPE_FADE:
//
//			g_Life[i].play[ANIMATION_TYPE_FADE].use = true;
//			g_Life[i].play[ANIMATION_TYPE_FADE].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_GUMMY:
//
//			g_Life[i].play[ANIMATION_TYPE_GUMMY].use = true;
//			g_Life[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_APPEAL:
//
//			g_Life[i].play[ANIMATION_TYPE_APPEAL].use = true;
//			g_Life[i].play[ANIMATION_TYPE_APPEAL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEUP:
//
//			g_Life[i].play[ANIMATION_TYPE_SLIDEUP].use = true;
//			g_Life[i].play[ANIMATION_TYPE_SLIDEUP].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEDOWN:
//
//			g_Life[i].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
//			g_Life[i].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDELEFT:
//
//			g_Life[i].play[ANIMATION_TYPE_SLIDELEFT].use = true;
//			g_Life[i].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDERIGHT:
//
//			g_Life[i].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
//			g_Life[i].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_DISUP:
//
//			g_Life[i].play[ANIMATION_TYPE_DISUP].use = true;
//			g_Life[i].play[ANIMATION_TYPE_DISUP].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISDOWN:
//
//			g_Life[i].play[ANIMATION_TYPE_DISDOWN].use = true;
//			g_Life[i].play[ANIMATION_TYPE_DISDOWN].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISLEFT:
//
//			g_Life[i].play[ANIMATION_TYPE_DISLEFT].use = true;
//			g_Life[i].play[ANIMATION_TYPE_DISLEFT].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISRIGHT:
//
//			g_Life[i].play[ANIMATION_TYPE_DISRIGHT].use = true;
//			g_Life[i].play[ANIMATION_TYPE_DISRIGHT].dur = 40;
//
//			break;
//		}
//	}
//}

//************************************************
// �A�j���[�V�������ʊǗ�
//************************************************
void AnimationManagerLife_Second(void)
{
	g_CT_startLife > 0 ? g_CT_startLife-- : g_CT_startLife = 0;

	if (g_CT_startLife == 1)
	{
		g_Life[0].play[ANIMATION_TYPE_FADE].use = true;
		g_Life[0].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Life[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	for (int i = 0; i < AMOUNT_LIFE - 1; i++)
	{
		if (!g_Life[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (g_Life[i].play[ANIMATION_TYPE_FADE].dur == 50)
		{
			g_Life[i + 1].play[ANIMATION_TYPE_FADE].use = true;
			g_Life[i + 1].play[ANIMATION_TYPE_FADE].dur = 60;

			g_Life[i + 1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}

	/*--------------------------------------------*/

#if 0	// ����I�ɃL��������

	g_CT_vibHeart > 0 ? g_CT_vibHeart-- : g_CT_vibHeart = 0;

	if (g_CT_vibHeart == 1)
	{ // ����I�ɃL��������

		g_Life[TEXTURE_TYPE_LIFE_HEART].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Life[TEXTURE_TYPE_LIFE_HEART].play[ANIMATION_TYPE_GUMMY].dur = 30;

		g_CT_vibHeart = 180;
	}

#endif
}

//************************************************
// �A�j���[�V�����Ǘ�
//************************************************
void AnimationManagerLife(void)
{
	for (int i = 0; i < AMOUNT_LIFE; i++)
	{
		if (!g_Life[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ǂ̃A�j���[�V�������Đ�����̂��I��
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Life[i].play[j].use)
			{
				// �Ή�����A�j���[�V�������Đ�����
				PlayAnimationLife(&g_Life[i], j);
			}
		}
	}
}

//************************************************
// ��ނɑΉ������A�j���[�V�����Đ�
//************************************************
void PlayAnimationLife(UI *p, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallLife(p);	// �U���F��

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigLife(p);	// �U���F��

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedLife(p);	// �Ԃ��Ȃ�

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearLife(p);	// �t�F�[�h

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyLife(p);	// �u�j��

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontLife(p);	// �o����

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpLife(p);	// ��X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownLife(p);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftLife(p);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightLife(p);	// �E�X���C�h�C��

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpLife(p);	// ��X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownLife(p);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftLife(p);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightLife(p);	// �E�X���C�h�A�E�g

		break;
	}
}

//************************************************
// �A�j���[�V������~
//************************************************
void StopAnimationLife(UI *p, int type)
{
	p->play[type] =
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
void VibrationSmallLife(UI *p)
{
	p->play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&p->play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// �U���F��
//************************************************
void VibrationBigLife(UI *p)
{
	p->play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&p->play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// �Ԃ��Ȃ�
//************************************************
void ChangeRedLife(UI *p)
{
	if (p->play[ANIMATION_TYPE_RED].dur > 10)
	{
		p->play[ANIMATION_TYPE_RED].col.g += -0.1f;
		p->play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		p->play[ANIMATION_TYPE_RED].col.g += 0.1f;
		p->play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&p->play[ANIMATION_TYPE_RED].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_RED);
	}
}

//************************************************
// �o��
//************************************************
void FadeAppearLife(UI *p)
{
	if (p->play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		p->play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		p->play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - p->play[ANIMATION_TYPE_FADE].dur));
	}

	if (p->play[ANIMATION_TYPE_FADE].dur == 40)
	{
		p->play[ANIMATION_TYPE_GUMMY].use = true;
		p->play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&p->play[ANIMATION_TYPE_FADE].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// �u�j��
//************************************************
void LikeaGummyLife(UI *p)
{
	if (p->play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		p->play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (p->play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		p->play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		p->play[ANIMATION_TYPE_GUMMY].span.x += 2;

		p->play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (p->play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		p->play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		p->play[ANIMATION_TYPE_GUMMY].span.x += 2;

		p->play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (p->play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		p->play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		p->play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (p->play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		p->play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		p->play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		p->play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (p->play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		p->play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		p->play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		p->play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&p->play[ANIMATION_TYPE_GUMMY].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// �`���`��
//************************************************
void AppealtoFrontLife(UI *p)
{
	if (p->play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		p->play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	p->play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&p->play[ANIMATION_TYPE_APPEAL].dur))
	{
		p->play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// ��X���C�h�C��
//************************************************
void SlideUpLife(UI *p)
{
	p->play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideDownLife(UI *p)
{
	p->play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideLeftLife(UI *p)
{
	p->play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// �E�X���C�h�C��
//************************************************
void SlideRightLife(UI *p)
{
	p->play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// ��X���C�h�A�E�g
//************************************************
void DisSlideUpLife(UI *p)
{
	p->play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / p->play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideDownLife(UI *p)
{
	p->play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / p->play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideLeftLife(UI *p)
{
	p->play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / p->play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// �E�X���C�h�A�E�g
//************************************************
void DisSlideRightLife(UI *p)
{
	p->play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / p->play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationLife(p, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// ���_��W�J
//************************************************
void SetVtxLife(void)
{
	AnimationParam general[AMOUNT_LIFE] = {};	// �Đ��p�����܂Ƃ߂�

	for (int i = 0; i < AMOUNT_LIFE; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_Life[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// �Đ��p�̋^�������܂Ƃ߂�
			general[i].move += g_Life[i].play[j].move;
			general[i].pos += g_Life[i].play[j].pos;
			general[i].rot += g_Life[i].play[j].rot;
			general[i].span += g_Life[i].play[j].span;
			general[i].col += g_Life[i].play[j].col;
		}

		// �p�x���Z�o
		g_Life[i].angle = atan2f(g_Life[i].span.x + general[i].span.x, g_Life[i].span.y + general[i].span.y);

		// �Ίp�����Z�o
		g_Life[i].length = sqrtf((g_Life[i].span.x + general[i].span.x) * (g_Life[i].span.x + general[i].span.x) +
			(g_Life[i].span.y + general[i].span.y) * (g_Life[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_LIFE; i++, pVtx += AMOUNT_VTX)
	{ // ���_���W�̐ݒ�
		pVtx[0].pos =
		{
			g_Life[i].pos.x + general[i].pos.x + sinf((g_Life[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Life[i].angle)) * g_Life[i].length,
			g_Life[i].pos.y + general[i].pos.y + cosf((g_Life[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Life[i].angle)) * g_Life[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Life[i].pos.x + general[i].pos.x + sinf((g_Life[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Life[i].angle)) * g_Life[i].length,
			g_Life[i].pos.y + general[i].pos.y + cosf((g_Life[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Life[i].angle)) * g_Life[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Life[i].pos.x + general[i].pos.x + sinf((g_Life[i].rot.z + general[i].rot.z) - (g_Life[i].angle)) * g_Life[i].length,
			g_Life[i].pos.y + general[i].pos.y + cosf((g_Life[i].rot.z + general[i].rot.z) - (g_Life[i].angle)) * g_Life[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Life[i].pos.x + general[i].pos.x + sinf((g_Life[i].rot.z + general[i].rot.z) + (g_Life[i].angle)) * g_Life[i].length,
			g_Life[i].pos.y + general[i].pos.y + cosf((g_Life[i].rot.z + general[i].rot.z) + (g_Life[i].angle)) * g_Life[i].length,
			0.0f
		};

		// �F�̔��f
		pVtx[0].col = g_Life[i].col + general[i].col;
		pVtx[1].col = g_Life[i].col + general[i].col;
		pVtx[2].col = g_Life[i].col + general[i].col;
		pVtx[3].col = g_Life[i].col + general[i].col;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//************************************************
// �ʏ�`�揈��
//************************************************
void DrawNormalLife(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int textype = 0;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_LIFE; i++)
	{
		if (!g_Life[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		textype = g_Life[i].textype;

		pDevice->SetTexture(0, g_pTextureLife[textype]);

		// �e�X�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �e�N�X�`����ǂݍ���
//************************************************
void ImportTexLifeNum(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ��ݗp
	const char* pFileName = "data\\TEXTURE\\num.png";

	D3DXCreateTextureFromFile(pDevice,
		pFileName,
		&g_pTextureLifeNum);
}

//************************************************
// �ݒ����ǂݍ���
//************************************************
void ImportInfoLifeNum(int joined)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char str[128] = {};		// ���͂��i�[
	int set = 0;			// ���l�p��
	int i = 0;				// �ėp����
	int textype = 0;		// �e�N�X�`�������擾
	D3DXVECTOR3 pos = {};	// �ʒu���i�[
	D3DXVECTOR3 rot = {};	// �������i�[
	D3DXVECTOR2 span = {};	// �傫�����i�[
	D3DXCOLOR col = {};		// �F���i�[

	// Life����W�J����
	if (fopen_s(&pFile, "data\\TXT\\UI\\life_num.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "���C�t�p�������̓W�J�Ɏ��s");

#endif	// _DEBUG�F�t�@�C���W�J�̍���
	}

	while (fscanf_s(pFile, "%s", &str[0], 128) != EOF)
	{
		if (strcmp(&str[0], "SET") == 0)
		{ // �Q���l�����擾
			fscanf_s(pFile, "%s %d", &str[0], 2, &set);
		}

		if (set != joined)
		{ // �Ή�����Z�b�g�݂̂��擾
			continue;
		}

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

			g_LifeNum[i].use = true;
			g_LifeNum[i].textype = textype;
			g_LifeNum[i].pos = pos;
			g_LifeNum[i].rot = rot;
			g_LifeNum[i].span = span;
			g_LifeNum[i].col = col;

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
void CreateVtxLifeNum(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_LIFENUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLifeNum,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffLifeNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_LIFENUM; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffLifeNum->Unlock();
}

//************************************************
// �A�j���[�V�������ʊǗ�
//************************************************
void AnimationManagerLifeNum_EX(void)
{
	if (g_CT_startLife == 1)
	{
		g_LifeNum[0].play[ANIMATION_TYPE_FADE].use = true;
		g_LifeNum[0].play[ANIMATION_TYPE_FADE].dur = 70;

		g_LifeNum[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	for (int i = 0; i < AMOUNT_LIFENUM - 1; i++)
	{
		if (!g_LifeNum[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (g_LifeNum[i].play[ANIMATION_TYPE_FADE].dur == 50)
		{
			g_LifeNum[i + 1].play[ANIMATION_TYPE_FADE].use = true;
			g_LifeNum[i + 1].play[ANIMATION_TYPE_FADE].dur = 70;

			g_LifeNum[i + 1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}
}

//************************************************
// �A�j���[�V�����Ǘ�
//************************************************
void AnimationManagerLifeNum(void)
{
	for (int i = 0; i < AMOUNT_LIFENUM; i++)
	{
		if (!g_LifeNum[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ǂ̃A�j���[�V�������Đ�����̂��I��
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_LifeNum[i].play[j].use)
			{
				// �Ή�����A�j���[�V�������Đ�����
				PlayAnimationLife(&g_LifeNum[i], j);
			}
		}
	}
}

//************************************************
// ���_��W�J
//************************************************
void SetVtxLifeNum(void)
{
	AnimationParam general[AMOUNT_LIFENUM] = {};	// �Đ��p�����܂Ƃ߂�

	for (int i = 0; i < AMOUNT_LIFENUM; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_LifeNum[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// �Đ��p�̋^�������܂Ƃ߂�
			general[i].move += g_LifeNum[i].play[j].move;
			general[i].pos += g_LifeNum[i].play[j].pos;
			general[i].rot += g_LifeNum[i].play[j].rot;
			general[i].span += g_LifeNum[i].play[j].span;
			general[i].col += g_LifeNum[i].play[j].col;
		}

		// �p�x���Z�o
		g_LifeNum[i].angle = atan2f(g_LifeNum[i].span.x + general[i].span.x, g_LifeNum[i].span.y + general[i].span.y);

		// �Ίp�����Z�o
		g_LifeNum[i].length = sqrtf((g_LifeNum[i].span.x + general[i].span.x) * (g_LifeNum[i].span.x + general[i].span.x) +
			(g_LifeNum[i].span.y + general[i].span.y) * (g_LifeNum[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// ���_���ւ̃|�C���^
	Player* pPlayer = GetInfoPlayer();

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffLifeNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_LIFENUM; i++, pVtx += AMOUNT_VTX)
	{ // ���_���W�̐ݒ�

		/*---�y���Ȃ薳���̂��鐔�l�̐ݒ�z---*/
		int value = pPlayer[i].param.HP;	// �e�N�X�`���p�̐��l���i�[

		pVtx[0].pos =
		{
			g_LifeNum[i].pos.x + general[i].pos.x + sinf((g_LifeNum[i].rot.z + general[i].rot.z) - (D3DX_PI - g_LifeNum[i].angle)) * g_LifeNum[i].length,
			g_LifeNum[i].pos.y + general[i].pos.y + cosf((g_LifeNum[i].rot.z + general[i].rot.z) - (D3DX_PI - g_LifeNum[i].angle)) * g_LifeNum[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_LifeNum[i].pos.x + general[i].pos.x + sinf((g_LifeNum[i].rot.z + general[i].rot.z) + (D3DX_PI - g_LifeNum[i].angle)) * g_LifeNum[i].length,
			g_LifeNum[i].pos.y + general[i].pos.y + cosf((g_LifeNum[i].rot.z + general[i].rot.z) + (D3DX_PI - g_LifeNum[i].angle)) * g_LifeNum[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_LifeNum[i].pos.x + general[i].pos.x + sinf((g_LifeNum[i].rot.z + general[i].rot.z) - (g_LifeNum[i].angle)) * g_LifeNum[i].length,
			g_LifeNum[i].pos.y + general[i].pos.y + cosf((g_LifeNum[i].rot.z + general[i].rot.z) - (g_LifeNum[i].angle)) * g_LifeNum[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_LifeNum[i].pos.x + general[i].pos.x + sinf((g_LifeNum[i].rot.z + general[i].rot.z) + (g_LifeNum[i].angle)) * g_LifeNum[i].length,
			g_LifeNum[i].pos.y + general[i].pos.y + cosf((g_LifeNum[i].rot.z + general[i].rot.z) + (g_LifeNum[i].angle)) * g_LifeNum[i].length,
			0.0f
		};

		// �F�̔��f
		pVtx[0].col = g_LifeNum[i].col + general[i].col;
		pVtx[1].col = g_LifeNum[i].col + general[i].col;
		pVtx[2].col = g_LifeNum[i].col + general[i].col;
		pVtx[3].col = g_LifeNum[i].col + general[i].col;

		// ���l��؂�ւ�
		pVtx[0].tex = { value * 0.1f, 0.0f };
		pVtx[1].tex = { (value + 1) * 0.1f, 0.0f };
		pVtx[2].tex = { value * 0.1f, 1.0f };
		pVtx[3].tex = { (value + 1) * 0.1f, 1.0f };
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLifeNum->Unlock();

	for (int i = 0; i < MAX_PLAYER; i++)
	{ // �ߋ��̃��C�t���L�^

		if (!pPlayer[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[

			continue;
		}

		// �ߋ��̃��C�t�ƌ��݂̃��C�t���قȂ�΃A�j���[�V����
		if (g_Life_old[i] != pPlayer[i].param.HP)
		{
			if (g_Life_old[i] > pPlayer[i].param.HP)
			{ // �Ⴂ�ꍇ

				// �g
				g_Life[i * 2].play[ANIMATION_TYPE_VIBSMALL].use = true;
				g_Life[i * 2].play[ANIMATION_TYPE_RED].use = true;
				g_Life[i * 2].play[ANIMATION_TYPE_VIBSMALL].dur = 20;
				g_Life[i * 2].play[ANIMATION_TYPE_RED].dur = 20;
				
				// �n�[�g
				g_Life[i * 2 + 1].play[ANIMATION_TYPE_VIBSMALL].use = true;
				g_Life[i * 2 + 1].play[ANIMATION_TYPE_VIBSMALL].dur = 30;

				// ����
				g_LifeNum[i].play[ANIMATION_TYPE_GUMMY].use = true;
				g_LifeNum[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
			}
			else
			{ // �����ꍇ

				// �n�[�g
				g_Life[i * 2 + 1].play[ANIMATION_TYPE_GUMMY].use = true;
				g_Life[i * 2 + 1].play[ANIMATION_TYPE_GUMMY].dur = 30;
			
				// ����
				g_LifeNum[i].play[ANIMATION_TYPE_GUMMY].use = true;
				g_LifeNum[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
			}
		}

		g_Life_old[i] = pPlayer[i].param.HP;
	}
}

//************************************************
// �ʏ�`�揈��
//************************************************
void DrawNormalLifeNum(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLifeNum, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_LIFENUM; i++)
	{
		if (!g_Life[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		pDevice->SetTexture(0, g_pTextureLifeNum);

		// �e�X�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}