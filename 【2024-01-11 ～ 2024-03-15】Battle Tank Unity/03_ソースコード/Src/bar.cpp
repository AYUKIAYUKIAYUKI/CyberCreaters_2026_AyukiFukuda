//************************************************
//
// �Q�[�W�\��[bar.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "bar.h"

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
#define AMOUNT_BAR 8	// ����\���̃Q�[�W

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DTEXTURE9 g_pTextureBar = NULL;		// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBar = NULL;	// ���_�o�b�t�@�̃|�C���^
UI g_Bar[AMOUNT_BAR];							// �Q�[�W�\���p���

int g_CT_startBar = 0;					// ����Q�[�W���o�ꂷ��܂ł̒x���p
int g_Magazine_old[MAX_PLAYER] = {};	// �ߋ��̒e��

/*---�y�v���g�^�C�v�錾�z---*/
void ImportTexBar(void);		// �e�N�X�`�����擾
void ImportInfoBar(int joined);	// �ݒ�����擾
void CreateVtxBar(void);		// ���_�o�b�t�@�̐���

void AnimationManagerBar_First(void);	// �A�j���[�V�������ʊǗ�
void AnimationManagerBar(void);			// �A�j���[�V�����Ǘ�
void PlayAnimationBar(int i, int type);	// �A�j���[�V�����Đ�
void StopAnimationBar(int i, int type);	// �A�j���[�V������~

void VibrationSmallBar(int i);	// �U���F��
void VibrationBigBar(int i);	// �U���F��
void ChangeRedBar(int i);		// �Ԃ�
void FadeAppearBar(int i);		// �o��
void LikeaGummyBar(int i);		// �u�j��
void AppealtoFrontBar(int i);	// �`���`��
void SlideUpBar(int i);			// ��X���C�h�C��
void SlideDownBar(int i);		// ��
void SlideLeftBar(int i);		// ��
void SlideRightBar(int i);		// �E
void DisSlideUpBar(int i);		// ��X���C�h�A�E�g
void DisSlideDownBar(int i);	// ��
void DisSlideLeftBar(int i);	// ��
void DisSlideRightBar(int i);	// �E

void SetVtxBar(void);		// �W�J
void DrawNormalBar(void);	// �ʏ�`��

//************************************************
// ��������
//************************************************
void InitBar(int joined)
{
	g_CT_startBar = 0;	// ����\�����o�ꂷ��܂ł̒x���p

	for (int i = 0; i < AMOUNT_BAR; i++)
	{ // �Q�[�W�\�����Z�b�g
		g_Bar[i].use = false;
		g_Bar[i].textype = -1;
		g_Bar[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Bar[i].move = { 0.0f, 0.0f, 0.0f };
		g_Bar[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Bar[i].span = { 0.0f, 0.0f };
		g_Bar[i].angle = 0;
		g_Bar[i].length = 0;
		g_Bar[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // �A�j���[�V������񃊃Z�b�g
			g_Bar[i].play[j].use = false;
			g_Bar[i].play[j].dur = 0;
			g_Bar[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Bar[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Bar[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Bar[i].play[j].span = { 0.0f, 0.0f };
			g_Bar[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}
	}

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_Magazine_old[i] = 0;
	}

	// �e�N�X�`����ǂݍ���
	ImportTexBar();

	// �����擾����
	ImportInfoBar(joined);

	// �ʏ풸�_�o�b�t�@�̐���
	CreateVtxBar();

	/**********************************/

	g_CT_startBar = 30;	// �Q�[�W���o�ꂷ��܂ł̒x���p

	/**********************************/
}

//************************************************
// �I������
//************************************************
void UninitBar(void)
{
	if (g_pTextureBar != NULL)
	{ // �e�N�X�`���̔j��
		g_pTextureBar->Release();
		g_pTextureBar = NULL;
	}

	if (g_pVtxBuffBar != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffBar->Release();
		g_pVtxBuffBar = NULL;
	}
}

//************************************************
// �X�V����
//************************************************
void UpdateBar(void)
{
	// �A�j���[�V�������ʊǗ�
	AnimationManagerBar_First();

	// �A�j���[�V�����Ǘ�
	AnimationManagerBar();

	// �ʏ�W�J
	SetVtxBar();
}

//************************************************
// �`�揈��
//************************************************
void DrawBar(void)
{
	// �ʏ�`��
	DrawNormalBar();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �e�N�X�`����ǂݍ���
//************************************************
void ImportTexBar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ��ݗp
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\num.png",
		&g_pTextureBar);
}

//************************************************
// �ݒ����ǂݍ���
//************************************************
void ImportInfoBar(int joined)
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

	// Bar����W�J����
	if (fopen_s(&pFile, "data\\TXT\\UI\\bar.txt", "r") != 0)
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

			g_Bar[i].use = true;
			g_Bar[i].textype = textype;
			g_Bar[i].pos = pos;
			g_Bar[i].rot = rot;
			g_Bar[i].span = span;
			g_Bar[i].col = col;

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
void CreateVtxBar(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_BAR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBar,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffBar->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BAR; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffBar->Unlock();
}

//************************************************
// �A�j���[�V�������ʊǗ�
//************************************************
void AnimationManagerBar_First(void)
{
	//g_CT_startBar > 0 ? g_CT_startBar-- : g_CT_startBar = 0;

	//if (g_CT_startBar == 1)
	//{
	//	g_Bar[0].play[ANIMATION_TYPE_FADE].use = true;
	//	g_Bar[0].play[ANIMATION_TYPE_FADE].dur = 60;

	//	g_Bar[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	//}
}

//************************************************
// �A�j���[�V�����Ǘ�
//************************************************
void AnimationManagerBar(void)
{
	for (int i = 0; i < AMOUNT_BAR; i++)
	{
		if (!g_Bar[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ǂ̃A�j���[�V�������Đ�����̂��I��
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Bar[i].play[j].use)
			{
				// �Ή�����A�j���[�V�������Đ�����
				PlayAnimationBar(i, j);
			}
		}
	}
}
//************************************************
// ��ނɑΉ������A�j���[�V�����Đ�
//************************************************
void PlayAnimationBar(int id, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallBar(id);	// �U���F��

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigBar(id);	// �U���F��

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedBar(id);	// �Ԃ��Ȃ�

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearBar(id);	// �t�F�[�h

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyBar(id);	// �u�j��

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontBar(id);	// �o����

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpBar(id);	// ��X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownBar(id);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftBar(id);	// ���X���C�h�C��

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightBar(id);	// �E�X���C�h�C��

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpBar(id);	// ��X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownBar(id);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftBar(id);	// ���X���C�h�A�E�g

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightBar(id);	// �E�X���C�h�A�E�g

		break;
	}
}

//************************************************
// �A�j���[�V������~
//************************************************
void StopAnimationBar(int id, int type)
{
	g_Bar[id].play[type] =
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
void VibrationSmallBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// �U���F��
//************************************************
void VibrationBigBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// �Ԃ��Ȃ�
//************************************************
void ChangeRedBar(int id)
{
	if (g_Bar[id].play[ANIMATION_TYPE_RED].dur > 10)
	{
		g_Bar[id].play[ANIMATION_TYPE_RED].col.g += -0.1f;
		g_Bar[id].play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		g_Bar[id].play[ANIMATION_TYPE_RED].col.g += 0.1f;
		g_Bar[id].play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_RED].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_RED);
	}
}

//************************************************
// �o��
//************************************************
void FadeAppearBar(int id)
{
	if (g_Bar[id].play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		g_Bar[id].play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		g_Bar[id].play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - g_Bar[id].play[ANIMATION_TYPE_FADE].dur));
	}

	if (g_Bar[id].play[ANIMATION_TYPE_FADE].dur == 40)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_FADE].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// �u�j��
//************************************************
void LikeaGummyBar(int id)
{
	if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Bar[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Bar[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_GUMMY].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// �`���`��
//************************************************
void AppealtoFrontBar(int id)
{
	if (g_Bar[id].play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		g_Bar[id].play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	g_Bar[id].play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_APPEAL].dur))
	{
		g_Bar[id].play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// ��X���C�h�C��
//************************************************
void SlideUpBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - g_Bar[id].play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideDownBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - g_Bar[id].play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// ���X���C�h�C��
//************************************************
void SlideLeftBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - g_Bar[id].play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// �E�X���C�h�C��
//************************************************
void SlideRightBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - g_Bar[id].play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// ��X���C�h�A�E�g
//************************************************
void DisSlideUpBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / g_Bar[id].play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_DISUP].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideDownBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / g_Bar[id].play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// ���X���C�h�A�E�g
//************************************************
void DisSlideLeftBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / g_Bar[id].play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// �E�X���C�h�A�E�g
//************************************************
void DisSlideRightBar(int id)
{
	g_Bar[id].play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / g_Bar[id].play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Bar[id].play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// �A�j���[�V�������~
		StopAnimationBar(id, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// ���_��W�J
//************************************************
void SetVtxBar(void)
{
	AnimationParam general[AMOUNT_BAR] = {};	// �Đ��p�����܂Ƃ߂�

	for (int i = 0; i < AMOUNT_BAR; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_Bar[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// �Đ��p�̋^�������܂Ƃ߂�
			general[i].move += g_Bar[i].play[j].move;
			general[i].pos += g_Bar[i].play[j].pos;
			general[i].rot += g_Bar[i].play[j].rot;
			general[i].span += g_Bar[i].play[j].span;
			general[i].col += g_Bar[i].play[j].col;
		}

		// �p�x���Z�o
		g_Bar[i].angle = atan2f(g_Bar[i].span.x + general[i].span.x, g_Bar[i].span.y + general[i].span.y);

		// �Ίp�����Z�o
		g_Bar[i].length = sqrtf((g_Bar[i].span.x + general[i].span.x) * (g_Bar[i].span.x + general[i].span.x) +
			(g_Bar[i].span.y + general[i].span.y) * (g_Bar[i].span.y + general[i].span.y));
	}

	/*--------------------------------------------*/

	Player* pPlayer = GetInfoPlayer();

	/*---�y���Ȃ薳���̂��鐔�l�̐ݒ�z---*/
	int value[AMOUNT_BAR] = {};
	int P_id = 0;

	for (int i = 0; i < AMOUNT_BAR; i++)
	{
		if (i % 2 == 0 && i != 0)
		{ // 2��Ɉ�x�v���C���[�p���l���㏸ 

			P_id++;
		}

		value[i] = pPlayer[P_id].PFW.magazine;	// �e�N�X�`���p�̐��l���i�[

		//PrintDebugProc("�� %d P_id %d\n", value[i], P_id);
	}

	for (int i = 0; i < AMOUNT_BAR / 2; i++)
	{
		// �����𐮍�����
		value[(i * 2)] /= 10;
	}

	for (int i = 0; i < AMOUNT_BAR; i++)
	{
		//PrintDebugProc("�� %d\n", value[i]);
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuffBar->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BAR; i++, pVtx += AMOUNT_VTX)
	{ // ���_���W�̐ݒ�

		pVtx[0].pos =
		{
			g_Bar[i].pos.x + general[i].pos.x + sinf((g_Bar[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Bar[i].angle)) * g_Bar[i].length,
			g_Bar[i].pos.y + general[i].pos.y + cosf((g_Bar[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Bar[i].angle)) * g_Bar[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Bar[i].pos.x + general[i].pos.x + sinf((g_Bar[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Bar[i].angle)) * g_Bar[i].length,
			g_Bar[i].pos.y + general[i].pos.y + cosf((g_Bar[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Bar[i].angle)) * g_Bar[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Bar[i].pos.x + general[i].pos.x + sinf((g_Bar[i].rot.z + general[i].rot.z) - (g_Bar[i].angle)) * g_Bar[i].length,
			g_Bar[i].pos.y + general[i].pos.y + cosf((g_Bar[i].rot.z + general[i].rot.z) - (g_Bar[i].angle)) * g_Bar[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Bar[i].pos.x + general[i].pos.x + sinf((g_Bar[i].rot.z + general[i].rot.z) + (g_Bar[i].angle)) * g_Bar[i].length,
			g_Bar[i].pos.y + general[i].pos.y + cosf((g_Bar[i].rot.z + general[i].rot.z) + (g_Bar[i].angle)) * g_Bar[i].length,
			0.0f
		};

		// �F�̔��f
		pVtx[0].col = g_Bar[i].col + general[i].col;
		pVtx[1].col = g_Bar[i].col + general[i].col;
		pVtx[2].col = g_Bar[i].col + general[i].col;
		pVtx[3].col = g_Bar[i].col + general[i].col;

		// ���l��؂�ւ�
		pVtx[0].tex = { value[i] * 0.1f, 0.0f };
		pVtx[1].tex = { (value[i] + 1) * 0.1f, 0.0f };
		pVtx[2].tex = { value[i] * 0.1f, 1.0f };
		pVtx[3].tex = { (value[i] + 1) * 0.1f, 1.0f };
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBar->Unlock();

#if 0

	for (int i = 0; i < MAX_PLAYER; i++)
	{ // �ߋ��̃��C�t���L�^

		if (!pPlayer[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[

			continue;
		}

		// �ߋ��̃��C�t�ƌ��݂̃��C�t���قȂ�΃A�j���[�V����
		if (g_Magazine_old[i] != pPlayer[i].PFW.magazine)
		{
			g_Bar[i].play[ANIMATION_TYPE_GUMMY].use = true;
			g_Bar[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
		}

		// �e�̐����L�^
		g_Magazine_old[i] = pPlayer[i].PFW.magazine;
	}

#endif
}

//************************************************
// �ʏ�`�揈��
//************************************************
void DrawNormalBar(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBar, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_BAR; i++)
	{
		if (!g_Bar[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		pDevice->SetTexture(0, g_pTextureBar);

		// �e�X�g�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}