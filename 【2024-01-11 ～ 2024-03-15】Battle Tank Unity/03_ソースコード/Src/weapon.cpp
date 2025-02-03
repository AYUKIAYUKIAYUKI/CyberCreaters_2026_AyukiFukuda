//************************************************
//
// ����\��[weapon.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "weapon.h"

// �V�X�e��
#include "sound.h"

// ������
#include "game.h"
#include "player.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

/*---�y�}�N����`�z---*/
#define AMOUNT_WEAPON 32	// ����\���̍ő吔

/*---�y�e�N�X�`�����ށz---*/
typedef enum
{
	TEXTURE_TYPE_WEAPON_PFW1 = 0,	// ���n
	TEXTURE_TYPE_WEAPON_PFW2,		// ��
	TEXTURE_TYPE_WEAPON_PFW3,		// ����
	TEXTURE_TYPE_WEAPON_GUN,		// �e
	TEXTURE_TYPE_WEAPON_RPG,		// RPG
	TEXTURE_TYPE_WEAPON_GUT,		// �~�j�K��
	TEXTURE_TYPE_WEAPON_SHOT,		// �U�e�e
	TEXTURE_TYPE_WEAPON_MAX
} TEXTURE_TYPE_WEAPON;

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DTEXTURE9 g_pTextureWeapon[TEXTURE_TYPE_WEAPON_MAX] = {};	// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWeapon = NULL;					// ���_�o�b�t�@�̃|�C���^
UI g_Weapon[AMOUNT_WEAPON];											// ����\���p���
float g_RotZ_Goal[AMOUNT_WEAPON] = {};								// ���ʂ�

int g_CT_startWeapon = 0;	// ����\�����o�ꂷ��܂ł̒x���p

/*---�y�v���g�^�C�v�錾�z---*/
void ImportTexWeapon(void);			// �e�N�X�`�����擾
void ImportInfoWeapon(int joined);	// �ݒ�����擾
void CreateVtxWeapon(void);			// ���_�o�b�t�@�̐���

void ChangePFW4(int id, int tex);			// ����ύX
void AnimationManagerWeapon_First(void);	// �A�j���[�V�������ʊǗ�
void AnimationManagerWeapon(void);			// �A�j���[�V�����Ǘ�
void PlayAnimationWeapon(int i, int type);	// �A�j���[�V�����Đ�
void StopAnimationWeapon(int i, int type);	// �A�j���[�V������~

void VibrationSmallWeapon(int i);	// �U���F��
void VibrationBigWeapon(int i);		// �U���F��
void ChangeRedWeapon(int i);		// �Ԃ�
void FadeAppearWeapon(int i);		// �o��
void LikeaGummyWeapon(int i);		// �u�j��
void AppealtoFrontWeapon(int i);	// �`���`��
void SlideUpWeapon(int i);			// ��X���C�h�C��
void SlideDownWeapon(int i);		// ��
void SlideLeftWeapon(int i);		// ��
void SlideRightWeapon(int i);		// �E
void DisSlideUpWeapon(int i);		// ��X���C�h�A�E�g
void DisSlideDownWeapon(int i);		// ��
void DisSlideLeftWeapon(int i);		// ��
void DisSlideRightWeapon(int i);	// �E

void SetVtxWeapon(void);		// �W�J
void DrawNormalWeapon(void);	// �ʏ�`��

//************************************************
// ��������
//************************************************
void InitWeapon(int joined)
{
	g_CT_startWeapon = 0;	// ����\�����o�ꂷ��܂ł̒x���p

	for (int i = 0; i < AMOUNT_WEAPON; i++)
	{ // Weapon�\�����Z�b�g
		g_Weapon[i].use = false;
		g_Weapon[i].textype = -1;
		g_Weapon[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Weapon[i].move = { 0.0f, 0.0f, 0.0f };
		g_Weapon[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Weapon[i].span = { 0.0f, 0.0f };
		g_Weapon[i].angle = 0;
		g_Weapon[i].length = 0;
		g_Weapon[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // �A�j���[�V������񃊃Z�b�g
			g_Weapon[i].play[j].use = false;
			g_Weapon[i].play[j].dur = 0;
			g_Weapon[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Weapon[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Weapon[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Weapon[i].play[j].span = { 0.0f, 0.0f };
			g_Weapon[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}

		g_RotZ_Goal[i] = 0.0f;
	}

	// �e�N�X�`����ǂݍ���
	ImportTexWeapon();

	// �����擾����
	ImportInfoWeapon(joined);

	// �ʏ풸�_�o�b�t�@�̐���
	CreateVtxWeapon();

	/**********************************/

	g_CT_startWeapon = 30;	// ����\�����o�ꂷ��܂ł̒x���p

	/**********************************/
}

//************************************************
// �I������
//************************************************
void UninitWeapon(void)
{
	for (int i = 0; i < TEXTURE_TYPE_WEAPON_MAX; i++)
	{
		if (g_pTextureWeapon[i] != NULL)
		{ // �e�N�X�`���̔j��
			g_pTextureWeapon[i]->Release();
			g_pTextureWeapon[i] = NULL;
		}
	}

	if (g_pVtxBuffWeapon != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffWeapon->Release();
		g_pVtxBuffWeapon = NULL;
	}
}

//************************************************
// �X�V����
//************************************************
void UpdateWeapon(int joined)
{
	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < joined; i++)
	{
		// ����e�N�X�`�����f
		ChangePFW4(i, pPlayer[i].param.weapon);
	}

	// �A�j���[�V�������ʊǗ�
	AnimationManagerWeapon_First();

	// �A�j���[�V�����Ǘ�
	AnimationManagerWeapon();

	// �ʏ�W�J
	SetVtxWeapon();
}

//************************************************
// �`�揈��
//************************************************
void DrawWeapon(void)
{
	// �ʏ�`��
	DrawNormalWeapon();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �e�N�X�`����ǂݍ���
//************************************************
void ImportTexWeapon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ��ݗp
	const char* pFileName[TEXTURE_TYPE_WEAPON_MAX] =
	{
		"data\\TEXTURE\\PFW1.png",
		"data\\TEXTURE\\PFW2.png",
		"data\\TEXTURE\\PFW3.png",
		"data\\TEXTURE\\gun.png",
		"data\\TEXTURE\\rpg.png",
		"data\\TEXTURE\\gut.png",
		"data\\TEXTURE\\shot.png",
	};

	for (int i = 0; i < TEXTURE_TYPE_WEAPON_MAX; i++)
	{ // �e�N�X�`���̐���

		if (pFileName[i] == NULL)
		{
			break;	// �摜�������Ȃ��Ă��I��
		}

		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureWeapon[i]);
	}
}

//************************************************
// �ݒ����ǂݍ���
//************************************************
void ImportInfoWeapon(int joined)
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

	// Weapon����W�J����
	if (fopen_s(&pFile, "data\\TXT\\UI\\weapon.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "����p�z�u���̓W�J�Ɏ��s");

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

			g_Weapon[i].use = true;
			g_Weapon[i].textype = textype;
			g_Weapon[i].pos = pos;
			g_Weapon[i].rot = rot;
			g_Weapon[i].span = span;
			g_Weapon[i].col = col;

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
void CreateVtxWeapon(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_WEAPON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWeapon,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffWeapon->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_WEAPON; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffWeapon->Unlock();
}

////************************************************
//// �A�j���[�V�����I��
////************************************************
//void SelectAnimationWeapon(void)
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
//			g_Weapon[i].play[ANIMATION_TYPE_VIBSMALL].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_VIBSMALL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_VIBBIG:
//
//			g_Weapon[i].play[ANIMATION_TYPE_VIBBIG].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_VIBBIG].dur = 15;
//
//			break;
//
//		case ANIMATION_TYPE_RED:
//
//			g_Weapon[i].play[ANIMATION_TYPE_RED].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_RED].dur = 20;
//
//			break;
//
//		case ANIMATION_TYPE_FADE:
//
//			g_Weapon[i].play[ANIMATION_TYPE_FADE].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_FADE].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_GUMMY:
//
//			g_Weapon[i].play[ANIMATION_TYPE_GUMMY].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_APPEAL:
//
//			g_Weapon[i].play[ANIMATION_TYPE_APPEAL].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_APPEAL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEUP:
//
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDEUP].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDEUP].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEDOWN:
//
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDELEFT:
//
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDELEFT].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDERIGHT:
//
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_DISUP:
//
//			g_Weapon[i].play[ANIMATION_TYPE_DISUP].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_DISUP].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISDOWN:
//
//			g_Weapon[i].play[ANIMATION_TYPE_DISDOWN].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_DISDOWN].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISLEFT:
//
//			g_Weapon[i].play[ANIMATION_TYPE_DISLEFT].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_DISLEFT].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISRIGHT:
//
//			g_Weapon[i].play[ANIMATION_TYPE_DISRIGHT].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_DISRIGHT].dur = 40;
//
//			break;
//		}
//	}
//}

//************************************************
// ����ύX
//************************************************
void ChangePFW4(int id, int tex)
{
	if (g_Weapon[4 + (id * 4) - 1].textype - 3 != tex)
	{ // �قȂ�w�肪����Ă���Ƃ��̂�

		// �e�N�X�`���w��
		g_Weapon[4 + (id * 4) - 1].textype = tex + 3;

		// �A�j���[�V����
		g_Weapon[4 + (id * 4) - 1].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Weapon[4 + (id * 4) - 1].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}
}

//************************************************
// �A�j���[�V�������ʊǗ�
//************************************************
void AnimationManagerWeapon_First(void)
{
	g_CT_startWeapon > 0 ? g_CT_startWeapon-- : g_CT_startWeapon = 0;

	if (g_CT_startWeapon == 1)
	{
		g_Weapon[0].play[ANIMATION_TYPE_FADE].use = true;
		g_Weapon[0].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Weapon[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	for (int i = 0; i < AMOUNT_WEAPON - 1; i++)
	{
		if (!g_Weapon[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (g_Weapon[i].play[ANIMATION_TYPE_FADE].dur == 55)
		{
			g_Weapon[i + 1].play[ANIMATION_TYPE_FADE].use = true;
			g_Weapon[i + 1].play[ANIMATION_TYPE_FADE].dur = 60;

			g_Weapon[i + 1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}

	for (int i = 0; i < AMOUNT_WEAPON - 2; i++)
	{
		if (!g_Weapon[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (g_Weapon[i + 1].play[ANIMATION_TYPE_FADE].dur == 55)
		{
			g_Weapon[i + 2].play[ANIMATION_TYPE_FADE].use = true;
			g_Weapon[i + 2].play[ANIMATION_TYPE_FADE].dur = 60;

			g_Weapon[i + 2].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}
}

//************************************************
// �A�j���[�V�����Ǘ�
//************************************************
void AnimationManagerWeapon(void)
{
	for (int i = 0; i < AMOUNT_WEAPON; i++)
	{
		if (!g_Weapon[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ǂ̃A�j���[�V�������Đ�����̂��I��
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Weapon[i].play[j].use)
			{
				// �Ή�����A�j���[�V�������Đ�����
				PlayAnimationWeapon(i, j);
			}
		}
	}
}

//************************************************
// ��ނɑΉ������A�j���[�V�����Đ�
//************************************************
void PlayAnimationWeapon(int id, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallWeapon(id);	// �U���F��

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigWeapon(id);	// �U���F��

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedWeapon(id);	// �Ԃ��Ȃ�

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearWeapon(id);	// �t�F�[�h

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyWeapon(id);	// �u�j��

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontWeapon(id);	// �o����

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpWeapon(id);	// ��X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownWeapon(id);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftWeapon(id);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightWeapon(id);	// �E�X���C�h�C��

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpWeapon(id);	// ��X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownWeapon(id);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftWeapon(id);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightWeapon(id);	// �E�X���C�h�A�E�g

		break;
	}
}

//************************************************
// �A�j���[�V������~
//************************************************
void StopAnimationWeapon(int id, int type)
{
	g_Weapon[id].play[type] =
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
void VibrationSmallWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// �U���F��
//************************************************
void VibrationBigWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// �Ԃ��Ȃ�
//************************************************
void ChangeRedWeapon(int id)
{
	if (g_Weapon[id].play[ANIMATION_TYPE_RED].dur > 10)
	{
		g_Weapon[id].play[ANIMATION_TYPE_RED].col.g += -0.1f;
		g_Weapon[id].play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		g_Weapon[id].play[ANIMATION_TYPE_RED].col.g += 0.1f;
		g_Weapon[id].play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_RED].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_RED);
	}
}

//************************************************
// �o��
//************************************************
void FadeAppearWeapon(int id)
{
	if (g_Weapon[id].play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		g_Weapon[id].play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		g_Weapon[id].play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - g_Weapon[id].play[ANIMATION_TYPE_FADE].dur));
	}

	if (g_Weapon[id].play[ANIMATION_TYPE_FADE].dur == 40)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_FADE].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// �u�j��
//************************************************
void LikeaGummyWeapon(int id)
{
	if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// �`���`��
//************************************************
void AppealtoFrontWeapon(int id)
{
	if (g_Weapon[id].play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		g_Weapon[id].play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	g_Weapon[id].play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_APPEAL].dur))
	{
		g_Weapon[id].play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// ��X���C�h�C��
//************************************************
void SlideUpWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - g_Weapon[id].play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideDownWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - g_Weapon[id].play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideLeftWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - g_Weapon[id].play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// �E�X���C�h�C��
//************************************************
void SlideRightWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - g_Weapon[id].play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// ��X���C�h�A�E�g
//************************************************
void DisSlideUpWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / g_Weapon[id].play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_DISUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideDownWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / g_Weapon[id].play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideLeftWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / g_Weapon[id].play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// �E�X���C�h�A�E�g
//************************************************
void DisSlideRightWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / g_Weapon[id].play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationWeapon(id, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// ���_��W�J
//************************************************
void SetVtxWeapon(void)
{
	AnimationParam general[AMOUNT_WEAPON] = {};	// �Đ��p�����܂Ƃ߂�

	for (int i = 0; i < AMOUNT_WEAPON; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_Weapon[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// �Đ��p�̋^�������܂Ƃ߂�
			general[i].move += g_Weapon[i].play[j].move;
			general[i].pos += g_Weapon[i].play[j].pos;
			general[i].rot += g_Weapon[i].play[j].rot;
			general[i].span += g_Weapon[i].play[j].span;
			general[i].col += g_Weapon[i].play[j].col;
		}

		// �p�x���Z�o
		g_Weapon[i].angle = atan2f(g_Weapon[i].span.x + general[i].span.x, g_Weapon[i].span.y + general[i].span.y);

		// �Ίp�����Z�o
		g_Weapon[i].length = sqrtf((g_Weapon[i].span.x + general[i].span.x) * (g_Weapon[i].span.x + general[i].span.x) +
			(g_Weapon[i].span.y + general[i].span.y) * (g_Weapon[i].span.y + general[i].span.y));

		// ��]�ʂɊ���
		if (g_RotZ_Goal[i] != 0.0f)
		{ // ���Ȃ��Ƃ���]�̌����݂��������

			g_RotZ_Goal[i] *= 0.9f;
			g_Weapon[i].rot.z += g_RotZ_Goal[i];
		}
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffWeapon->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_WEAPON; i++, pVtx += AMOUNT_VTX)
	{ // ���_���W�̐ݒ�
		pVtx[0].pos =
		{
			g_Weapon[i].pos.x + general[i].pos.x + sinf((g_Weapon[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Weapon[i].angle)) * g_Weapon[i].length,
			g_Weapon[i].pos.y + general[i].pos.y + cosf((g_Weapon[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Weapon[i].angle)) * g_Weapon[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Weapon[i].pos.x + general[i].pos.x + sinf((g_Weapon[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Weapon[i].angle)) * g_Weapon[i].length,
			g_Weapon[i].pos.y + general[i].pos.y + cosf((g_Weapon[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Weapon[i].angle)) * g_Weapon[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Weapon[i].pos.x + general[i].pos.x + sinf((g_Weapon[i].rot.z + general[i].rot.z) - (g_Weapon[i].angle)) * g_Weapon[i].length,
			g_Weapon[i].pos.y + general[i].pos.y + cosf((g_Weapon[i].rot.z + general[i].rot.z) - (g_Weapon[i].angle)) * g_Weapon[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Weapon[i].pos.x + general[i].pos.x + sinf((g_Weapon[i].rot.z + general[i].rot.z) + (g_Weapon[i].angle)) * g_Weapon[i].length,
			g_Weapon[i].pos.y + general[i].pos.y + cosf((g_Weapon[i].rot.z + general[i].rot.z) + (g_Weapon[i].angle)) * g_Weapon[i].length,
			0.0f
		};

		// �F�̔��f
		pVtx[0].col = g_Weapon[i].col + general[i].col;
		pVtx[1].col = g_Weapon[i].col + general[i].col;
		pVtx[2].col = g_Weapon[i].col + general[i].col;
		pVtx[3].col = g_Weapon[i].col + general[i].col;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWeapon->Unlock();
}

//************************************************
// �ʏ�`�揈��
//************************************************
void DrawNormalWeapon(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int textype = 0;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffWeapon, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_WEAPON; i++)
	{
		if (!g_Weapon[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		textype = g_Weapon[i].textype;

		pDevice->SetTexture(0, g_pTextureWeapon[textype]);

		// �e�X�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// ���ԉ�]
//************************************************
void RotatePFW3(int id, float pw)
{
	g_RotZ_Goal[3 + (id * 4) - 1] += pw;
}