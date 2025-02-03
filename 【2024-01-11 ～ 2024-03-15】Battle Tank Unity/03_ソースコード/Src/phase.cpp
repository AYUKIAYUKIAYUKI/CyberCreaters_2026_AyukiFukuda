//************************************************
//
// �t�F�[�Y�\��[phase.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "phase.h"

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
#define AMOUNT_PHASE 16		// �t�F�[�Y�\���̍ő吔
#define AMOUNT_PHASENUM 4	// �����̍ő吔

/*---�y�e�N�X�`�����ށz---*/
typedef enum
{
	TEXTURE_TYPE_PHASE_ENEMYWOOD = 0,	// �G�̑����̕\���g
	TEXTURE_TYPE_PHASE_ENEMYMAX,		// �u�G�̑����v
	TEXTURE_TYPE_PHASE_WOOD,			// �t�F�[�Y�̕\���g
	TEXTURE_TYPE_PHASE_NOW,				// �u���݂̃t�F�[�Y�v
	TEXTURE_TYPE_PHASE_STONE,			// �ł����Δ�
	TEXTURE_TYPE_PHASE_NEXT,			// NEXT�̂��m�点
	TEXTURE_TYPE_PHASE_MIDBOSS,			// ���{�X�P��
	TEXTURE_TYPE_PHASE_BIGBOSS,			// ��{�X�P��
	TEXTURE_TYPE_PHASE_SCOREWOOD,		// �X�R�A�̕\���g
	TEXTURE_TYPE_PHASE_TIMEWOOD,		// �^�C�}�[�̕\���g
	TEXTURE_TYPE_PHASE_LIMIT,			// �u�c�莞�ԁv
	TEXTURE_TYPE_PHASE_COLON,			// �u�F�v
	TEXTURE_TYPE_PHASE_MAX
} TEXTURE_TYPE_PHASE;

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DTEXTURE9 g_pTexturePhase[TEXTURE_TYPE_PHASE_MAX] = {};	// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePhaseNum = NULL;						// �����p�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPhase = NULL;						// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPhaseNum = NULL;					// �����p���_�o�b�t�@�̃|�C���^
UI g_Phase[AMOUNT_PHASE];											// �t�F�[�Y�\���p���
UI g_PhaseNum[AMOUNT_PHASE];										// �����\���p���

int g_CT_startPhase_Enemy = 0;	// �G�̑����\�����o�ꂷ��܂ł̒x���p
int g_CT_startPhase_Now = 0;	// �t�F�[�Y�\�����o�ꂷ��܂ł̒x���p
bool g_change_phase = false;	// �t�F�[�Y�̕ϓ������m
int * g_pPhase = nullptr;		// �t�F�[�Y��񓯊��p
bool g_change_enemy = false;	// �o�������ς�����������o
bool g_change_score = false;	// �X�R�A���ς�����������o

/*---�y�v���g�^�C�v�錾�z---*/
void ImportTexPhase(void);		// �e�N�X�`�����擾
void ImportInfoPhase(void);		// �ݒ�����擾
void CreateVtxPhase(void);		// ���_�o�b�t�@�̐���
void SetInfoPhase_Enemy(void);	// �G�����p����ݒ�

void AnimationManagerPhase_Enemy(void);		// �G�̑����p�A�j���[�V�������ʊǗ�
void AnimationManagerPhase_Now(void);		// �t�F�[�Y�p�A�j���[�V�������ʊǗ�
void AnimationManagerPhase(void);			// �A�j���[�V�����Ǘ�
void PlayAnimationPhase(UI* p, int type);	// �A�j���[�V�����Đ�
void StopAnimationPhase(UI* p, int type);	// �A�j���[�V������~

void VibrationSmallPhase(UI* p);	// �U���F��
void VibrationBigPhase(UI* p);		// �U���F��
void ChangeRedPhase(UI* p);			// �Ԃ�
void FadeAppearPhase(UI* p);		// �o��
void LikeaGummyPhase(UI* p);		// �u�j��
void AppealtoFrontPhase(UI* p);		// �`���`��
void SlideUpPhase(UI* p);			// ��X���C�h�C��
void SlideDownPhase(UI* p);			// ��
void SlideLeftPhase(UI* p);			// ��
void SlideRightPhase(UI* p);		// �E
void DisSlideUpPhase(UI* p);		// ��X���C�h�A�E�g
void DisSlideDownPhase(UI* p);		// ��
void DisSlideLeftPhase(UI* p);		// ��
void DisSlideRightPhase(UI* p);		// �E

void SetVtxPhase(void);		// �W�J
void DrawNormalPhase(void);	// �ʏ�`��

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ImportTexPhaseNum(void);	// �e�N�X�`�����擾
void ImportInfoPhaseNum(void);	// �ݒ�����擾
void CreateVtxPhaseNum(void);	// ���_�o�b�t�@�̐���

void AnimationManagerPhaseNum(void);	// �A�j���[�V�����Ǘ�

void SetVtxPhaseNum(void);		// �W�J
void DrawNormalPhaseNum(void);	// �ʏ�`��

//************************************************
// ��������
//************************************************
void InitPhase(int joined)
{
	g_CT_startPhase_Enemy = 0;	// �G�̑����\�����o�ꂷ��܂ł̒x���p
	g_CT_startPhase_Now = 0;	// �t�F�[�Y�\�����o�ꂷ��܂ł̒x���p
	g_change_phase = false;		// �t�F�[�Y�̕ϓ������m
	g_pPhase = GetInfoPhase();	// �t�F�[�Y���𓯊��p
	g_change_enemy = false;		// �o�������ς�����������o
	g_change_score = false;		// �X�R�A���ς�����������o

#ifdef _DEBUG	// �t�F�[�Y���̃|�C���^�ɃA�h���X�����Ă邩�m�F (�������O�サ����o�O��)

	assert(g_pPhase != nullptr && "�t�F�[�Y�����p�̏����擾�ł��܂���ł���");

#endif

	for (int i = 0; i < AMOUNT_PHASE; i++)
	{ // Phase�\�����Z�b�g
		g_Phase[i].use = false;
		g_Phase[i].textype = -1;
		g_Phase[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Phase[i].move = { 0.0f, 0.0f, 0.0f };
		g_Phase[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Phase[i].span = { 0.0f, 0.0f };
		g_Phase[i].angle = 0;
		g_Phase[i].length = 0;
		g_Phase[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // �A�j���[�V������񃊃Z�b�g
			g_Phase[i].play[j].use = false;
			g_Phase[i].play[j].dur = 0;
			g_Phase[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Phase[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Phase[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Phase[i].play[j].span = { 0.0f, 0.0f };
			g_Phase[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// �e�N�X�`����ǂݍ���
	ImportTexPhase();

	// �����擾����
	ImportInfoPhase();

	// �ʏ풸�_�o�b�t�@�̐���
	CreateVtxPhase();

	/*--------------------------------------------*/

	for (int i = 0; i < AMOUNT_PHASENUM; i++)
	{ // �����p��񃊃Z�b�g
		g_PhaseNum[i].use = false;
		g_PhaseNum[i].textype = -1;
		g_PhaseNum[i].pos = { 0.0f, 0.0f, 0.0f };
		g_PhaseNum[i].move = { 0.0f, 0.0f, 0.0f };
		g_PhaseNum[i].rot = { 0.0f, 0.0f, 0.0f };
		g_PhaseNum[i].span = { 0.0f, 0.0f };
		g_PhaseNum[i].angle = 0;
		g_PhaseNum[i].length = 0;
		g_PhaseNum[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // �A�j���[�V������񃊃Z�b�g
			g_PhaseNum[i].play[j].use = false;
			g_PhaseNum[i].play[j].dur = 0;
			g_PhaseNum[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_PhaseNum[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_PhaseNum[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_PhaseNum[i].play[j].span = { 0.0f, 0.0f };
			g_PhaseNum[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// �e�N�X�`����ǂݍ���
	ImportTexPhaseNum();

	// �����擾����
	ImportInfoPhaseNum();

	// �ʏ풸�_�o�b�t�@�̐���
	CreateVtxPhaseNum();

	/*************************************/

	// ����ݒ�
	g_CT_startPhase_Enemy = 100 + (10 * joined);	// �G�̑����\�����o��܂ł̒x������
	g_CT_startPhase_Now = 150 + (10 * joined);		// �t�F�[�Y�\�����o��܂ł̒x������
	
	/*************************************/
}

//************************************************
// �I������
//************************************************
void UninitPhase(void)
{
	for (int i = 0; i < TEXTURE_TYPE_PHASE_MAX; i++)
	{ // �e�N�X�`���̔j��
		if (g_pTexturePhase[i] != NULL)
		{
			g_pTexturePhase[i]->Release();
			g_pTexturePhase[i] = NULL;
		}
	}

	if (g_pTexturePhaseNum != NULL)
	{ // �����e�N�X�`���̔j��
		g_pTexturePhaseNum->Release();
		g_pTexturePhaseNum = NULL;
	}

	if (g_pVtxBuffPhase != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffPhase->Release();
		g_pVtxBuffPhase = NULL;
	}

	if (g_pVtxBuffPhaseNum != NULL)
	{ // �������_�o�b�t�@�̔j��
		g_pVtxBuffPhaseNum->Release();
		g_pVtxBuffPhaseNum = NULL;
	}
}

//************************************************
// �X�V����
//************************************************
void UpdatePhase(void)
{
	// �G�����\���p�A�j���[�V�������ʊǗ�
	AnimationManagerPhase_Enemy();

	// �t�F�[�Y�\���p�A�j���[�V�������ʊǗ�
	AnimationManagerPhase_Now();

	if (g_change_score)
	{ // �X�R�A�ύX�ɍ��킹�ăA�j���[�V����
		g_Phase[TEXTURE_TYPE_PHASE_SCOREWOOD].play[ANIMATION_TYPE_VIBSMALL].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_SCOREWOOD].play[ANIMATION_TYPE_VIBSMALL].dur = 30;

		g_change_score = false;
	}

	// �A�j���[�V�����Ǘ�
	AnimationManagerPhase();

	// �����A�j���[�V�����Ǘ�
	AnimationManagerPhaseNum();

	// �ʏ�W�J
	SetVtxPhase();

	// �����ʏ�W�J
	SetVtxPhaseNum();
}

//************************************************
// �`�揈��
//************************************************
void DrawPhase(void)
{
	// �ʏ�`��
	DrawNormalPhase();

	// �����ʏ�`��
	DrawNormalPhaseNum();
}

//************************************************
// �t�F�[�Y�\���̏����擾
//************************************************
UI* GetInfoPhaseUI(void)
{
	return &g_Phase[0];
}

//************************************************
// �t�F�[�Y�̕ύX���m
//************************************************
bool* ChangePhasePlay(void)
{
	return &g_change_phase;
}

//************************************************
// �o�����̕ύX���m
//************************************************
bool* ChangeEnemyPlay(void)
{
	return &g_change_enemy;
}

//************************************************
// �X�R�A�̕ύX���m
//************************************************
bool* ChangeScorePlay(void)
{
	return &g_change_score;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �e�N�X�`����ǂݍ���
//************************************************
void ImportTexPhase(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ��ݗp
	const char* pFileName[TEXTURE_TYPE_PHASE_MAX] =
	{
		"data\\TEXTURE\\woody.png",
		"data\\TEXTURE\\amount_enemy.png",
		"data\\TEXTURE\\fewoody.png",
		"data\\TEXTURE\\phase_now.png",
		"data\\TEXTURE\\bigstone.png",
		"data\\TEXTURE\\NEXT.png",
		"data\\TEXTURE\\mid_phase.png",
		"data\\TEXTURE\\big_phase.png",
		"data\\TEXTURE\\woody.png",
		"data\\TEXTURE\\fewoody.png",
		"data\\TEXTURE\\timelimit.png",
		"data\\TEXTURE\\colon.png",
	};

	for (int i = 0; i < TEXTURE_TYPE_PHASE_MAX; i++)
	{ // �e�N�X�`���̐���

		if (pFileName[i] == NULL)
		{
			break;	// �摜�������Ȃ��Ă��I��
		}

		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTexturePhase[i]);
	}
}

//************************************************
// �ݒ����ǂݍ���
//************************************************
void ImportInfoPhase(void)
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

	// Phase����W�J����
	if (fopen_s(&pFile, "data\\TXT\\UI\\phase.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�t�F�[�Y�p���̓W�J�Ɏ��s");

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

			g_Phase[i].use = true;
			g_Phase[i].textype = textype;
			g_Phase[i].pos = pos;
			g_Phase[i].rot = rot;
			g_Phase[i].span = span;
			g_Phase[i].col = col;

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
void CreateVtxPhase(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_PHASE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPhase,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffPhase->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_PHASE; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffPhase->Unlock();
}

////************************************************
//// �A�j���[�V�����I��
////************************************************
//void SelectAnimationPhase(void)
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
//			g_Phase[i].play[ANIMATION_TYPE_VIBSMALL].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_VIBSMALL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_VIBBIG:
//
//			g_Phase[i].play[ANIMATION_TYPE_VIBBIG].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_VIBBIG].dur = 15;
//
//			break;
//
//		case ANIMATION_TYPE_RED:
//
//			g_Phase[i].play[ANIMATION_TYPE_RED].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_RED].dur = 20;
//
//			break;
//
//		case ANIMATION_TYPE_FADE:
//
//			g_Phase[i].play[ANIMATION_TYPE_FADE].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_FADE].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_GUMMY:
//
//			g_Phase[i].play[ANIMATION_TYPE_GUMMY].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_APPEAL:
//
//			g_Phase[i].play[ANIMATION_TYPE_APPEAL].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_APPEAL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEUP:
//
//			g_Phase[i].play[ANIMATION_TYPE_SLIDEUP].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_SLIDEUP].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEDOWN:
//
//			g_Phase[i].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDELEFT:
//
//			g_Phase[i].play[ANIMATION_TYPE_SLIDELEFT].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDERIGHT:
//
//			g_Phase[i].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_DISUP:
//
//			g_Phase[i].play[ANIMATION_TYPE_DISUP].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_DISUP].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISDOWN:
//
//			g_Phase[i].play[ANIMATION_TYPE_DISDOWN].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_DISDOWN].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISLEFT:
//
//			g_Phase[i].play[ANIMATION_TYPE_DISLEFT].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_DISLEFT].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISRIGHT:
//
//			g_Phase[i].play[ANIMATION_TYPE_DISRIGHT].use = true;
//			g_Phase[i].play[ANIMATION_TYPE_DISRIGHT].dur = 40;
//
//			break;
//		}
//	}
//}

//************************************************
// �G�����p����ݒ�
//************************************************
void SetInfoPhase_Enemy(void)
{
	g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
	g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;

	g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].col = { 1.0f, 1.0f, 1.0f, 1.0f };
}

//************************************************
// �G�����\���p�A�j���[�V�������ʊǗ�
//************************************************
void AnimationManagerPhase_Enemy(void)
{
	// �J�E���g����
	g_CT_startPhase_Enemy > 0 ? g_CT_startPhase_Enemy--: g_CT_startPhase_Enemy = 0;

	if (g_CT_startPhase_Enemy == 1)	// 0�ɂ���Ɩ����ɍĐ�
	{ // �x���o�ߌ�ɖؘg���o��
		SetInfoPhase_Enemy();

		g_Phase[TEXTURE_TYPE_PHASE_SCOREWOOD].play[ANIMATION_TYPE_SLIDELEFT].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_SCOREWOOD].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_SCOREWOOD].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	if (g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].play[ANIMATION_TYPE_SLIDERIGHT].dur == 35)
	{ // �ؘg���o��セ����ۂ��^�C�~���O�œo��

		g_Phase[TEXTURE_TYPE_PHASE_ENEMYMAX].play[ANIMATION_TYPE_FADE].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_ENEMYMAX].play[ANIMATION_TYPE_FADE].dur = 60;

		g_PhaseNum[1].play[ANIMATION_TYPE_FADE].use = true;
		g_PhaseNum[1].play[ANIMATION_TYPE_FADE].dur = 60;

		g_PhaseNum[2].play[ANIMATION_TYPE_FADE].use = true;
		g_PhaseNum[2].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_ENEMYMAX].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_PhaseNum[1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_PhaseNum[2].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	if (g_change_enemy)
	{ // �o�����̕ύX�ɍ��킹�ăA�j���[�V����

		g_Phase[TEXTURE_TYPE_PHASE_WOOD].play[ANIMATION_TYPE_VIBSMALL].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_WOOD].play[ANIMATION_TYPE_VIBSMALL].dur = 30;

		g_PhaseNum[1].play[ANIMATION_TYPE_GUMMY].use = true;
		g_PhaseNum[1].play[ANIMATION_TYPE_GUMMY].dur = 30;

		g_PhaseNum[2].play[ANIMATION_TYPE_GUMMY].use = true;
		g_PhaseNum[2].play[ANIMATION_TYPE_GUMMY].dur = 30;

		g_change_enemy = false;
	}
}

//************************************************
// �t�F�[�Y�\���A�j���[�V�������ʊǗ�
//************************************************
void AnimationManagerPhase_Now(void)
{
	// �J�E���g����
	g_CT_startPhase_Now > 0 ? g_CT_startPhase_Now-- : g_CT_startPhase_Now = 0;

	if (g_CT_startPhase_Now == 1)	// 0�ɂ���Ɩ����ɍĐ�
	{ // �x���o�ߌ�ɘg���o��

		g_Phase[TEXTURE_TYPE_PHASE_WOOD].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_WOOD].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_TIMEWOOD].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_TIMEWOOD].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_WOOD].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Phase[TEXTURE_TYPE_PHASE_TIMEWOOD].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	if (g_Phase[TEXTURE_TYPE_PHASE_WOOD].play[ANIMATION_TYPE_SLIDEDOWN].dur == 35)
	{ // �g���o��セ����ۂ��^�C�~���O�œo��

		g_Phase[TEXTURE_TYPE_PHASE_NOW].play[ANIMATION_TYPE_FADE].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_NOW].play[ANIMATION_TYPE_FADE].dur = 60;
		g_Phase[TEXTURE_TYPE_PHASE_LIMIT].play[ANIMATION_TYPE_FADE].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_LIMIT].play[ANIMATION_TYPE_FADE].dur = 60;
		g_Phase[TEXTURE_TYPE_PHASE_COLON].play[ANIMATION_TYPE_FADE].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_COLON].play[ANIMATION_TYPE_FADE].dur = 60;
		g_PhaseNum[0].play[ANIMATION_TYPE_FADE].use = true;
		g_PhaseNum[0].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_NOW].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Phase[TEXTURE_TYPE_PHASE_LIMIT].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_Phase[TEXTURE_TYPE_PHASE_COLON].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		g_PhaseNum[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	/*--------------------------------------------*/
	
	if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_SLIDELEFT].dur == 1)
	{ // ����\��������
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].dur = 60;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].dur == 1)
	{
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBSMALL].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_DISRIGHT].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_DISRIGHT].dur = 60;
	}

	if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_DISRIGHT].dur == 1)
	{
		g_Phase[TEXTURE_TYPE_PHASE_STONE].col = { 0.0f, 0.0f, 0.0f, 0.0f };

		// �G�̏o�����̐��������̃^�C�~���O�œ������Ƃ�
		g_PhaseNum[1].play[ANIMATION_TYPE_GUMMY].use = true;
		g_PhaseNum[1].play[ANIMATION_TYPE_GUMMY].dur = 30;
		g_PhaseNum[2].play[ANIMATION_TYPE_GUMMY].use = true;
		g_PhaseNum[2].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	/*--------------------------------------------*/
	
	// ���啶��������
	if (*g_pPhase == 2)
	{
		if (g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_SLIDELEFT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_GUMMY].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_GUMMY].dur = 30;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_DISRIGHT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_DISRIGHT].dur = 60;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_DISRIGHT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}
	else if (*g_pPhase == 4)
	{
		if (g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_SLIDELEFT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_GUMMY].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_GUMMY].dur = 30;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_DISRIGHT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_DISRIGHT].dur = 60;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_DISRIGHT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}
	else
	{
		if (g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_SLIDELEFT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_GUMMY].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_GUMMY].dur = 30;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBBIG].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_DISRIGHT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_DISRIGHT].dur = 60;
		}

		if (g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_DISRIGHT].dur == 1)
		{
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	/*--------------------------------------------*/

	if (g_change_phase)
	{ // �t�F�[�Y�̕ύX�ɍ��킹�ăA�j���[�V����

		// �ʏ�\��
		g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].play[ANIMATION_TYPE_VIBSMALL].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_ENEMYWOOD].play[ANIMATION_TYPE_VIBSMALL].dur = 30;

		g_PhaseNum[0].play[ANIMATION_TYPE_GUMMY].use = true;
		g_PhaseNum[0].play[ANIMATION_TYPE_GUMMY].dur = 30;

		// ����\��
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBSMALL].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_SLIDELEFT].use = true;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
		g_Phase[TEXTURE_TYPE_PHASE_STONE].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;

		g_Phase[TEXTURE_TYPE_PHASE_STONE].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		// ���啶��
		if (*g_pPhase == 2)
		{
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_SLIDELEFT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;

			g_Phase[TEXTURE_TYPE_PHASE_MIDBOSS].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
		else if (*g_pPhase == 4)
		{
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_SLIDELEFT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;

			g_Phase[TEXTURE_TYPE_PHASE_BIGBOSS].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
		else
		{
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_SLIDELEFT].use = true;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_VIBSMALL].dur = 60;
			g_Phase[TEXTURE_TYPE_PHASE_NEXT].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;

			g_Phase[TEXTURE_TYPE_PHASE_NEXT].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}

		g_change_phase = false;
	}
}

//************************************************
// �A�j���[�V�����Ǘ�
//************************************************
void AnimationManagerPhase(void)
{
	for (int i = 0; i < AMOUNT_PHASE; i++)
	{
		if (!g_Phase[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ǂ̃A�j���[�V�������Đ�����̂��I��
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Phase[i].play[j].use)
			{
				// �Ή�����A�j���[�V�������Đ�����
				PlayAnimationPhase(&g_Phase[i], j);
			}
		}
	}
}

//************************************************
// ��ނɑΉ������A�j���[�V�����Đ�
//************************************************
void PlayAnimationPhase(UI* p, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallPhase(p);	// �U���F��

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigPhase(p);	// �U���F��

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedPhase(p);	// �Ԃ��Ȃ�

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearPhase(p);	// �t�F�[�h

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyPhase(p);	// �u�j��

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontPhase(p);	// �o����

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpPhase(p);	// ��X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownPhase(p);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftPhase(p);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightPhase(p);	// �E�X���C�h�C��

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpPhase(p);	// ��X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownPhase(p);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftPhase(p);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightPhase(p);	// �E�X���C�h�A�E�g

		break;
	}
}

//************************************************
// �A�j���[�V������~
//************************************************
void StopAnimationPhase(UI* p, int type)
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
void VibrationSmallPhase(UI* p)
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
		StopAnimationPhase(p, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// �U���F��
//************************************************
void VibrationBigPhase(UI* p)
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
		StopAnimationPhase(p, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// �Ԃ��Ȃ�
//************************************************
void ChangeRedPhase(UI* p)
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
		StopAnimationPhase(p, ANIMATION_TYPE_RED);
	}
}

//************************************************
// �o��
//************************************************
void FadeAppearPhase(UI* p)
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
		StopAnimationPhase(p, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// �u�j��
//************************************************
void LikeaGummyPhase(UI* p)
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
		StopAnimationPhase(p, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// �`���`��
//************************************************
void AppealtoFrontPhase(UI* p)
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
		StopAnimationPhase(p, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// ��X���C�h�C��
//************************************************
void SlideUpPhase(UI* p)
{
	p->play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationPhase(p, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideDownPhase(UI* p)
{
	p->play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationPhase(p, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideLeftPhase(UI* p)
{
	p->play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationPhase(p, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// �E�X���C�h�C��
//************************************************
void SlideRightPhase(UI* p)
{
	p->play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - p->play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&p->play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationPhase(p, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// ��X���C�h�A�E�g
//************************************************
void DisSlideUpPhase(UI* p)
{
	p->play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / p->play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationPhase(p, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideDownPhase(UI* p)
{
	p->play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / p->play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationPhase(p, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideLeftPhase(UI* p)
{
	p->play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / p->play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationPhase(p, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// �E�X���C�h�A�E�g
//************************************************
void DisSlideRightPhase(UI* p)
{
	p->play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / p->play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&p->play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationPhase(p, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// ���_��W�J
//************************************************
void SetVtxPhase(void)
{
	AnimationParam general[AMOUNT_PHASE] = {};	// �Đ��p�����܂Ƃ߂�

	for (int i = 0; i < AMOUNT_PHASE; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_Phase[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// �Đ��p�̋^�������܂Ƃ߂�
			general[i].move += g_Phase[i].play[j].move;
			general[i].pos += g_Phase[i].play[j].pos;
			general[i].rot += g_Phase[i].play[j].rot;
			general[i].span += g_Phase[i].play[j].span;
			general[i].col += g_Phase[i].play[j].col;
		}

		// �p�x���Z�o
		g_Phase[i].angle = atan2f(g_Phase[i].span.x + general[i].span.x, g_Phase[i].span.y + general[i].span.y);

		// �Ίp�����Z�o
		g_Phase[i].length = sqrtf((g_Phase[i].span.x + general[i].span.x) * (g_Phase[i].span.x + general[i].span.x) +
			(g_Phase[i].span.y + general[i].span.y) * (g_Phase[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffPhase->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_PHASE; i++, pVtx += AMOUNT_VTX)
	{ // ���_���W�̐ݒ�

		pVtx[0].pos =
		{
			g_Phase[i].pos.x + general[i].pos.x + sinf((g_Phase[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Phase[i].angle)) * g_Phase[i].length,
			g_Phase[i].pos.y + general[i].pos.y + cosf((g_Phase[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Phase[i].angle)) * g_Phase[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Phase[i].pos.x + general[i].pos.x + sinf((g_Phase[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Phase[i].angle)) * g_Phase[i].length,
			g_Phase[i].pos.y + general[i].pos.y + cosf((g_Phase[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Phase[i].angle)) * g_Phase[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Phase[i].pos.x + general[i].pos.x + sinf((g_Phase[i].rot.z + general[i].rot.z) - (g_Phase[i].angle)) * g_Phase[i].length,
			g_Phase[i].pos.y + general[i].pos.y + cosf((g_Phase[i].rot.z + general[i].rot.z) - (g_Phase[i].angle)) * g_Phase[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Phase[i].pos.x + general[i].pos.x + sinf((g_Phase[i].rot.z + general[i].rot.z) + (g_Phase[i].angle)) * g_Phase[i].length,
			g_Phase[i].pos.y + general[i].pos.y + cosf((g_Phase[i].rot.z + general[i].rot.z) + (g_Phase[i].angle)) * g_Phase[i].length,
			0.0f
		};

		// �F�̔��f
		pVtx[0].col = g_Phase[i].col + general[i].col;
		pVtx[1].col = g_Phase[i].col + general[i].col;
		pVtx[2].col = g_Phase[i].col + general[i].col;
		pVtx[3].col = g_Phase[i].col + general[i].col;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPhase->Unlock();
}

//************************************************
// �ʏ�`�揈��
//************************************************
void DrawNormalPhase(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int textype = 0;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPhase, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_PHASE; i++)
	{
		if (!g_Phase[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		textype = g_Phase[i].textype;

		pDevice->SetTexture(0, g_pTexturePhase[textype]);

		// �e�X�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �e�N�X�`����ǂݍ���
//************************************************
void ImportTexPhaseNum(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ��ݗp
	const char* pFileName = "data\\TEXTURE\\num.png";

	D3DXCreateTextureFromFile(pDevice,
		pFileName,
		&g_pTexturePhaseNum);
}

//************************************************
// �ݒ����ǂݍ���
//************************************************
void ImportInfoPhaseNum(void)
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

	// Phase����W�J����
	if (fopen_s(&pFile, "data\\TXT\\UI\\phase_num.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�t�F�[�Y�p�������̓W�J�Ɏ��s");

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

			g_PhaseNum[i].use = true;
			g_PhaseNum[i].textype = textype;
			g_PhaseNum[i].pos = pos;
			g_PhaseNum[i].rot = rot;
			g_PhaseNum[i].span = span;
			g_PhaseNum[i].col = col;

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
void CreateVtxPhaseNum(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_PHASENUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPhaseNum,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffPhaseNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_PHASENUM; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffPhaseNum->Unlock();
}

//************************************************
// �A�j���[�V�����Ǘ�
//************************************************
void AnimationManagerPhaseNum(void)
{
	for (int i = 0; i < AMOUNT_PHASENUM; i++)
	{
		if (!g_PhaseNum[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ǂ̃A�j���[�V�������Đ�����̂��I��
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_PhaseNum[i].play[j].use)
			{
				// �Ή�����A�j���[�V�������Đ�����
				PlayAnimationPhase(&g_PhaseNum[i], j);
			}
		}
	}
}

//************************************************
// ���_��W�J
//************************************************
void SetVtxPhaseNum(void)
{
	AnimationParam general[AMOUNT_PHASENUM] = {};	// �Đ��p�����܂Ƃ߂�

	for (int i = 0; i < AMOUNT_PHASENUM; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_PhaseNum[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// �Đ��p�̋^�������܂Ƃ߂�
			general[i].move += g_PhaseNum[i].play[j].move;
			general[i].pos += g_PhaseNum[i].play[j].pos;
			general[i].rot += g_PhaseNum[i].play[j].rot;
			general[i].span += g_PhaseNum[i].play[j].span;
			general[i].col += g_PhaseNum[i].play[j].col;
		}

		// �p�x���Z�o
		g_PhaseNum[i].angle = atan2f(g_PhaseNum[i].span.x + general[i].span.x, g_PhaseNum[i].span.y + general[i].span.y);

		// �Ίp�����Z�o
		g_PhaseNum[i].length = sqrtf((g_PhaseNum[i].span.x + general[i].span.x) * (g_PhaseNum[i].span.x + general[i].span.x) +
			(g_PhaseNum[i].span.y + general[i].span.y) * (g_PhaseNum[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffPhaseNum->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_PHASENUM; i++, pVtx += AMOUNT_VTX)
	{ // ���_���W�̐ݒ�

		/*---�y���Ȃ薳���̂��鐔�l�̐ݒ�z---*/
		int value = 0;	// �e�N�X�`���p�̐��l���i�[

		if (i == 0)
		{
			value = *g_pPhase + 1;	// �t�F�[�Y�����擾
		}
		else if (i == 1)
		{
			value = GetInfoMaxEnemy();	// �G�̏o�������擾
			value /= 10;
		}
		else if (i == 2)
		{
			value = GetInfoMaxEnemy();	// �G�̏o�������擾
		}

		pVtx[0].pos =
		{
			g_PhaseNum[i].pos.x + general[i].pos.x + sinf((g_PhaseNum[i].rot.z + general[i].rot.z) - (D3DX_PI - g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			g_PhaseNum[i].pos.y + general[i].pos.y + cosf((g_PhaseNum[i].rot.z + general[i].rot.z) - (D3DX_PI - g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_PhaseNum[i].pos.x + general[i].pos.x + sinf((g_PhaseNum[i].rot.z + general[i].rot.z) + (D3DX_PI - g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			g_PhaseNum[i].pos.y + general[i].pos.y + cosf((g_PhaseNum[i].rot.z + general[i].rot.z) + (D3DX_PI - g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_PhaseNum[i].pos.x + general[i].pos.x + sinf((g_PhaseNum[i].rot.z + general[i].rot.z) - (g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			g_PhaseNum[i].pos.y + general[i].pos.y + cosf((g_PhaseNum[i].rot.z + general[i].rot.z) - (g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_PhaseNum[i].pos.x + general[i].pos.x + sinf((g_PhaseNum[i].rot.z + general[i].rot.z) + (g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			g_PhaseNum[i].pos.y + general[i].pos.y + cosf((g_PhaseNum[i].rot.z + general[i].rot.z) + (g_PhaseNum[i].angle)) * g_PhaseNum[i].length,
			0.0f
		};

		// �F�̔��f
		pVtx[0].col = g_PhaseNum[i].col + general[i].col;
		pVtx[1].col = g_PhaseNum[i].col + general[i].col;
		pVtx[2].col = g_PhaseNum[i].col + general[i].col;
		pVtx[3].col = g_PhaseNum[i].col + general[i].col;

		// ���l��؂�ւ�
		pVtx[0].tex = { value * 0.1f, 0.0f };
		pVtx[1].tex = { (value + 1) * 0.1f, 0.0f };
		pVtx[2].tex = { value * 0.1f, 1.0f };
		pVtx[3].tex = { (value + 1) * 0.1f, 1.0f };
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPhaseNum->Unlock();
}

//************************************************
// �ʏ�`�揈��
//************************************************
void DrawNormalPhaseNum(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPhaseNum, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_PHASENUM; i++)
	{
		if (!g_Phase[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		pDevice->SetTexture(0, g_pTexturePhaseNum);

		// �e�X�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}