//************************************************
//
// �����[�h�\��[reload.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "reload.h"

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
#define AMOUNT_RELOAD 4	// �����[�h�\���̍ő吔

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DTEXTURE9 g_pTextureReload = {};			// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReload = NULL;	// ���_�o�b�t�@�̃|�C���^
UI g_Reload[AMOUNT_RELOAD];							// �����[�h�\���p���

int g_CT_startReload = 0;	// �����[�h�\�����o�ꂷ��܂ł̒x���p

/*---�y�v���g�^�C�v�錾�z---*/
void ImportTexReload(void);			// �e�N�X�`�����擾
void ImportInfoReload(int joined);	// �ݒ�����擾
void CreateVtxReload(void);			// ���_�o�b�t�@�̐���

void AnimationManagerReload_EX(void);		// �A�j���[�V�������ʊǗ�
void AnimationManagerReload(void);			// �A�j���[�V�����Ǘ�
void PlayAnimationReload(int i, int type);	// �A�j���[�V�����Đ�
void StopAnimationReload(int i, int type);	// �A�j���[�V������~

void VibrationSmallReload(int i);	// �U���F��
void VibrationBigReload(int i);		// �U���F��
void ChangeRedReload(int i);		// �Ԃ�
void FadeAppearReload(int i);		// �o��
void LikeaGummyReload(int i);		// �u�j��
void AppealtoFrontReload(int i);	// �`���`��
void SlideUpReload(int i);			// ��X���C�h�C��
void SlideDownReload(int i);		// ��
void SlideLeftReload(int i);		// ��
void SlideRightReload(int i);		// �E
void DisSlideUpReload(int i);		// ��X���C�h�A�E�g
void DisSlideDownReload(int i);		// ��
void DisSlideLeftReload(int i);		// ��
void DisSlideRightReload(int i);	// �E

void SetVtxReload(void);		// �W�J
void DrawNormalReload(void);	// �ʏ�`��

//************************************************
// ��������
//************************************************
void InitReload(int joined)
{
	g_CT_startReload = 0;	// �����[�h�\�����o�ꂷ��܂ł̒x���p

	for (int i = 0; i < AMOUNT_RELOAD; i++)
	{ // Reload�\�����Z�b�g
		g_Reload[i].use = false;
		g_Reload[i].textype = -1;
		g_Reload[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Reload[i].move = { 0.0f, 0.0f, 0.0f };
		g_Reload[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Reload[i].span = { 0.0f, 0.0f };
		g_Reload[i].angle = 0;
		g_Reload[i].length = 0;
		g_Reload[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // �A�j���[�V������񃊃Z�b�g
			g_Reload[i].play[j].use = false;
			g_Reload[i].play[j].dur = 0;
			g_Reload[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Reload[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Reload[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Reload[i].play[j].span = { 0.0f, 0.0f };
			g_Reload[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	// �e�N�X�`����ǂݍ���
	ImportTexReload();

	// �����擾����
	ImportInfoReload(joined);

	// �ʏ풸�_�o�b�t�@�̐���
	CreateVtxReload();

	/**********************************/

	g_CT_startReload = 30;	// �����[�h�\�����o�ꂷ��܂ł̒x���p

	/**********************************/
}

//************************************************
// �I������
//************************************************
void UninitReload(void)
{
	if (g_pTextureReload != NULL)
	{ // �e�N�X�`���̔j��
		g_pTextureReload->Release();
		g_pTextureReload = NULL;
	}

	if (g_pVtxBuffReload != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffReload->Release();
		g_pVtxBuffReload = NULL;
	}
}

//************************************************
// �X�V����
//************************************************
void UpdateReload(void)
{
	// �A�j���[�V�������ʊǗ�
	AnimationManagerReload_EX();

	// �A�j���[�V�����Ǘ�
	AnimationManagerReload();

	// �ʏ�W�J
	SetVtxReload();
}

//************************************************
// �`�揈��
//************************************************
void DrawReload(void)
{
	// �ʏ�`��
	DrawNormalReload();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �e�N�X�`����ǂݍ���
//************************************************
void ImportTexReload(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ��ݗp
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\rere.png",
		&g_pTextureReload);
}

//************************************************
// �ݒ����ǂݍ���
//************************************************
void ImportInfoReload(int joined)
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

	// Reload����W�J����
	if (fopen_s(&pFile, "data\\TXT\\UI\\reload.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�����[�h�p�z�u���̓W�J�Ɏ��s");

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

			g_Reload[i].use = true;
			g_Reload[i].textype = textype;
			g_Reload[i].pos = pos;
			g_Reload[i].rot = rot;
			g_Reload[i].span = span;
			g_Reload[i].col = col;

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
void CreateVtxReload(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_RELOAD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReload,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffReload->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_RELOAD; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffReload->Unlock();
}

//************************************************
// �A�j���[�V�������ʊǗ�
//************************************************
void AnimationManagerReload_EX(void)
{
	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < AMOUNT_RELOAD; i++)
	{
		if (!g_Reload[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (pPlayer[i].PFW.empty)
		{
			g_Reload[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
		else
		{
			g_Reload[i].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}
}

//************************************************
// �A�j���[�V�����Ǘ�
//************************************************
void AnimationManagerReload(void)
{
	for (int i = 0; i < AMOUNT_RELOAD; i++)
	{
		if (!g_Reload[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ǂ̃A�j���[�V�������Đ�����̂��I��
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Reload[i].play[j].use)
			{
				// �Ή�����A�j���[�V�������Đ�����
				PlayAnimationReload(i, j);
			}
		}
	}
}

//************************************************
// ��ނɑΉ������A�j���[�V�����Đ�
//************************************************
void PlayAnimationReload(int id, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallReload(id);	// �U���F��

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigReload(id);	// �U���F��

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedReload(id);	// �Ԃ��Ȃ�

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearReload(id);	// �t�F�[�h

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyReload(id);	// �u�j��

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontReload(id);	// �o����

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpReload(id);	// ��X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownReload(id);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftReload(id);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightReload(id);	// �E�X���C�h�C��

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpReload(id);	// ��X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownReload(id);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftReload(id);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightReload(id);	// �E�X���C�h�A�E�g

		break;
	}
}

//************************************************
// �A�j���[�V������~
//************************************************
void StopAnimationReload(int id, int type)
{
	g_Reload[id].play[type] =
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
void VibrationSmallReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// �U���F��
//************************************************
void VibrationBigReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// �Ԃ��Ȃ�
//************************************************
void ChangeRedReload(int id)
{
	if (g_Reload[id].play[ANIMATION_TYPE_RED].dur > 10)
	{
		g_Reload[id].play[ANIMATION_TYPE_RED].col.g += -0.1f;
		g_Reload[id].play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		g_Reload[id].play[ANIMATION_TYPE_RED].col.g += 0.1f;
		g_Reload[id].play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_RED].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_RED);
	}
}

//************************************************
// �o��
//************************************************
void FadeAppearReload(int id)
{
	if (g_Reload[id].play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		g_Reload[id].play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		g_Reload[id].play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - g_Reload[id].play[ANIMATION_TYPE_FADE].dur));
	}

	if (g_Reload[id].play[ANIMATION_TYPE_FADE].dur == 40)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_FADE].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// �u�j��
//************************************************
void LikeaGummyReload(int id)
{
	if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Reload[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Reload[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_GUMMY].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// �`���`��
//************************************************
void AppealtoFrontReload(int id)
{
	if (g_Reload[id].play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		g_Reload[id].play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	g_Reload[id].play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_APPEAL].dur))
	{
		g_Reload[id].play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// ��X���C�h�C��
//************************************************
void SlideUpReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - g_Reload[id].play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideDownReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - g_Reload[id].play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideLeftReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - g_Reload[id].play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// �E�X���C�h�C��
//************************************************
void SlideRightReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - g_Reload[id].play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// ��X���C�h�A�E�g
//************************************************
void DisSlideUpReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / g_Reload[id].play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_DISUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideDownReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / g_Reload[id].play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideLeftReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / g_Reload[id].play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// �E�X���C�h�A�E�g
//************************************************
void DisSlideRightReload(int id)
{
	g_Reload[id].play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / g_Reload[id].play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Reload[id].play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationReload(id, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// ���_��W�J
//************************************************
void SetVtxReload(void)
{
	AnimationParam general[AMOUNT_RELOAD] = {};	// �Đ��p�����܂Ƃ߂�

	for (int i = 0; i < AMOUNT_RELOAD; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_Reload[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// �Đ��p�̋^�������܂Ƃ߂�
			general[i].move += g_Reload[i].play[j].move;
			general[i].pos += g_Reload[i].play[j].pos;
			general[i].rot += g_Reload[i].play[j].rot;
			general[i].span += g_Reload[i].play[j].span;
			general[i].col += g_Reload[i].play[j].col;
		}

		// �p�x���Z�o
		g_Reload[i].angle = atan2f(g_Reload[i].span.x + general[i].span.x, g_Reload[i].span.y + general[i].span.y);

		// �Ίp�����Z�o
		g_Reload[i].length = sqrtf((g_Reload[i].span.x + general[i].span.x) * (g_Reload[i].span.x + general[i].span.x) +
			(g_Reload[i].span.y + general[i].span.y) * (g_Reload[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffReload->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_RELOAD; i++, pVtx += AMOUNT_VTX)
	{ // ���_���W�̐ݒ�

		pVtx[0].pos =
		{
			g_Reload[i].pos.x + general[i].pos.x + sinf((g_Reload[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Reload[i].angle)) * g_Reload[i].length,
			g_Reload[i].pos.y + general[i].pos.y + cosf((g_Reload[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Reload[i].angle)) * g_Reload[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Reload[i].pos.x + general[i].pos.x + sinf((g_Reload[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Reload[i].angle)) * g_Reload[i].length,
			g_Reload[i].pos.y + general[i].pos.y + cosf((g_Reload[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Reload[i].angle)) * g_Reload[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Reload[i].pos.x + general[i].pos.x + sinf((g_Reload[i].rot.z + general[i].rot.z) - (g_Reload[i].angle)) * g_Reload[i].length,
			g_Reload[i].pos.y + general[i].pos.y + cosf((g_Reload[i].rot.z + general[i].rot.z) - (g_Reload[i].angle)) * g_Reload[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Reload[i].pos.x + general[i].pos.x + sinf((g_Reload[i].rot.z + general[i].rot.z) + (g_Reload[i].angle)) * g_Reload[i].length,
			g_Reload[i].pos.y + general[i].pos.y + cosf((g_Reload[i].rot.z + general[i].rot.z) + (g_Reload[i].angle)) * g_Reload[i].length,
			0.0f
		};

		// �F�̔��f
		pVtx[0].col = g_Reload[i].col + general[i].col;
		pVtx[1].col = g_Reload[i].col + general[i].col;
		pVtx[2].col = g_Reload[i].col + general[i].col;
		pVtx[3].col = g_Reload[i].col + general[i].col;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffReload->Unlock();
}

//************************************************
// �ʏ�`�揈��
//************************************************
void DrawNormalReload(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffReload, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_RELOAD; i++)
	{
		if (!g_Reload[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		pDevice->SetTexture(0, g_pTextureReload);

		// �e�X�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}