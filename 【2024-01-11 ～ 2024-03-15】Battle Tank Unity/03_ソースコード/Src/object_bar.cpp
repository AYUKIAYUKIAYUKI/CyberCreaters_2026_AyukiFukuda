//************************************************
//
// �\�����̗̑̓Q�[�W[object_bar.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "object_bar.h"

// �V�X�e���n
#include "sound.h"

// ������
#include "game.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif // _DEBUG

/*---�y�}�N����`�z---*/
#define MAX_OBJECT_BAR 512	// �\�����̗̑̓Q�[�W�̍ő吔

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObject_Bar = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureObject_Bar = NULL;			// �e�N�X�`���ւ̃|�C���^
Object_Bar g_Object_Bar[MAX_OBJECT_BAR];				// �\�����̗̑̓Q�[�W���

/*---�y�v���g�^�C�v�錾�z---*/

// ����
void ImportTexObject_Bar(void);			// �e�N�X�`���擾
void CreateVtxBufferObject_Bar(void);	// ���_���𐶐�

// �X�V
void SetVtxObject_Bar(void);	// �W�J

void DeleteObject_Bar(int id);	// ����

//************************************************
// ��������
//************************************************
void InitObject_Bar(void)
{
	for (int i = 0; i < MAX_OBJECT_BAR; i++)
	{ // �\�����̗̑̓Q�[�W��񃊃Z�b�g

		g_Object_Bar[i].use = false;								// �g�p�t���O
		g_Object_Bar[i].dur = 0;									// ����
		g_Object_Bar[i].pos = { 0.0f, 0.0f, 0.0f };					// �ʒu
		g_Object_Bar[i].move = { 0.0f, 0.0f, 0.0f };				// �ړ���
		g_Object_Bar[i].rot = { 0.0f, 0.0f, 0.0f };					// ����
		g_Object_Bar[i].span = { 0.0f, 0.0f };						// �傫���p
		g_Object_Bar[i].HPspan = 0.0f;								// �̗͂̑傫������
		g_Object_Bar[i].angle = 0.0f;								// �p�x
		g_Object_Bar[i].length = 0.0f;								// �Ίp���p
		g_Object_Bar[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		g_Object_Bar[i].HPcol = 0.0f;								// �̗͂̐F����
	}

	/*--------------------------------------------*/

	// �e�N�X�`�������擾
	ImportTexObject_Bar();

	// ���_���𐶐�
	CreateVtxBufferObject_Bar();
}

//************************************************
// �e�N�X�`������ǂݍ���
//************************************************
void ImportTexObject_Bar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\bright.png",
		&g_pTextureObject_Bar);
}

//************************************************
// ���_���𐶐�
//************************************************
void CreateVtxBufferObject_Bar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * MAX_OBJECT_BAR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffObject_Bar,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffObject_Bar->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_OBJECT_BAR; i++, pVtx += AMOUNT_VTX)
	{ // ���_���̃��Z�b�g

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffObject_Bar->Unlock();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// �I������
//************************************************
void UninitObject_Bar(void)
{
	if (g_pTextureObject_Bar != NULL)
	{ // �e�N�X�`���̔j��

		g_pTextureObject_Bar->Release();
		g_pTextureObject_Bar = NULL;
	}

	if (g_pVtxBuffObject_Bar != NULL)
	{ // ���_�o�b�t�@�̔j��

		g_pVtxBuffObject_Bar->Release();
		g_pVtxBuffObject_Bar = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// �X�V����
//************************************************
void UpdateObject_Bar(void)
{
	for (int i = 0; i < MAX_OBJECT_BAR; i++)
	{
		if (g_Object_Bar[i].dur <= 0)
		{ // �p�����Ԃ�������΃R���e�B�j���[

			continue;
		}

		// �c�����ԍX�V
		CntDuration(&g_Object_Bar[i].dur);
	}

	// �|���S����W�J
	SetVtxObject_Bar();
}

//************************************************
// �\�����̗̑̓Q�[�W����
//************************************************
void DeleteObject_Bar(int id)
{
	g_Object_Bar[id].use = false;								// �g�p�t���O
	g_Object_Bar[id].dur = 0;									// ����
	g_Object_Bar[id].pos = { 0.0f, 0.0f, 0.0f };				// �ʒu
	g_Object_Bar[id].move = { 0.0f, 0.0f, 0.0f };				// �ړ���
	g_Object_Bar[id].rot = { 0.0f, 0.0f, 0.0f };				// ����
	g_Object_Bar[id].span = { 0.0f, 0.0f };						// �傫���p
	g_Object_Bar[id].HPspan = 0.0f;								// �̗͂̑傫������
	g_Object_Bar[id].angle = 0.0f;								// �p�x
	g_Object_Bar[id].length = 0.0f;								// �Ίp���p
	g_Object_Bar[id].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	g_Object_Bar[id].HPcol = 0.0f;								// �̗͂̐F����
}

//************************************************
// �\�����̗̑̓Q�[�W�W�J
//************************************************
void SetVtxObject_Bar(void)
{
	VERTEX_3D* pVtx;		// ���_���̃|�C���^
	TextureSize tex = {};	// �e�N�X�`���T�C�Y

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_OBJECT_BAR; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (g_Object_Bar[i].dur <= 0)
		{ // �p�����Ԃ�������΃R���e�B�j���[

			continue;
		}

		// �p�x���Z�o
		g_Object_Bar[i].angle = atan2f(g_Object_Bar[i].span.x, g_Object_Bar[i].span.y);

		// �Ίp�����Z�o
		g_Object_Bar[i].length = sqrtf(g_Object_Bar[i].span.x * g_Object_Bar[i].span.x + g_Object_Bar[i].span.y * g_Object_Bar[i].span.y);
	}

	/*--------------------------------------------*/

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffObject_Bar->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_OBJECT_BAR; i++, pVtx += AMOUNT_VTX)
	{
		if (g_Object_Bar[i].dur <= 0)
		{ // �p�����Ԃ�������΃R���e�B�j���[

			continue;
		}

		// ���_�̓W�J
		pVtx[0].pos =
		{
			sinf(g_Object_Bar[i].rot.z - (D3DX_PI - g_Object_Bar[i].angle)) * g_Object_Bar[i].length,
			-cosf(g_Object_Bar[i].rot.z - (D3DX_PI - g_Object_Bar[i].angle)) * g_Object_Bar[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			sinf(g_Object_Bar[i].rot.z + (D3DX_PI - g_Object_Bar[i].angle)) * g_Object_Bar[i].length,
			-cosf(g_Object_Bar[i].rot.z + (D3DX_PI - g_Object_Bar[i].angle)) * g_Object_Bar[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			sinf(g_Object_Bar[i].rot.z - g_Object_Bar[i].angle) * g_Object_Bar[i].length,
			-cosf(g_Object_Bar[i].rot.z - g_Object_Bar[i].angle) * g_Object_Bar[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			sinf(g_Object_Bar[i].rot.z + g_Object_Bar[i].angle) * g_Object_Bar[i].length,
			-cosf(g_Object_Bar[i].rot.z + g_Object_Bar[i].angle) * g_Object_Bar[i].length,
			0.0f
		};

		// �J���[���f
		pVtx[0].col = g_Object_Bar[i].col;
		pVtx[1].col = g_Object_Bar[i].col;
		pVtx[2].col = g_Object_Bar[i].col;
		pVtx[3].col = g_Object_Bar[i].col;
	}

	g_pVtxBuffObject_Bar->Unlock();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// �`�揈��
//************************************************
void DrawObject_Bar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans, mtxView;				// �v�Z�p�}�g���b�N�X

	// ���C�g���f�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �[�x�e�X�g�̔�r���@�̕ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// �[�x�o�b�t�@�ɕ`�悵�Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffObject_Bar, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < MAX_OBJECT_BAR; i++)
	{
		if (g_Object_Bar[i].dur <= 0)
		{ // �p�����Ԃ�������΃R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Object_Bar[i].mtx);

		// �r���[�}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// �|���S�����J�����̐��ʂɌ���������
		D3DXMatrixInverse(&g_Object_Bar[i].mtx, NULL, &mtxView);	// �t�s������߂�

		g_Object_Bar[i].mtx._41 = 0.0f;
		g_Object_Bar[i].mtx._42 = 0.0f;
		g_Object_Bar[i].mtx._43 = 0.0f;

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Object_Bar[i].pos.x,
			g_Object_Bar[i].pos.y,
			g_Object_Bar[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Object_Bar[i].mtx,
			&g_Object_Bar[i].mtx,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Object_Bar[i].mtx);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureObject_Bar);

		// �r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// ���C�g���f��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �[�x�e�X�g�̔�r���@�̕ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// �[�x�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// �\�����̗̑̓Q�[�W����
//************************************************
int CreateObject_Bar(int HP)
{
	int id = 0;	// ���ʔԍ��p

	for (int i = 0; i < MAX_OBJECT_BAR; i++)
	{
		if (g_Object_Bar[i].use)
		{ // �g�p���Ȃ�R���e�B�j���[
			continue;
		}

		g_Object_Bar[i].use = true;
		//g_Object_Bar[i].pPos = pPos;	// �Ώۈʒu��t�^

		g_Object_Bar[i].span = { 70.0f, 10.0f };		// �傫��
		g_Object_Bar[i].HPspan = 70.0f / (float)HP;	// �̗͂̑傫���������Z�o���Ă���

		g_Object_Bar[i].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);	// �F
		g_Object_Bar[i].HPcol = 1.0f / (float)HP;	// �̗͂̐F�������Z�o���Ă���

		id = i;	// ���ʔԍ��i�[

		break;	// �I��
	}

	return id;	// �ꉞ���ʔԍ���n��
}

//************************************************
// �\�����̗̑̓Q�[�W�X�V
//************************************************
void EnableObject_Bar(int HP, int id, D3DXVECTOR3 pos)
{
	// HP�ɉ����ăQ�[�W���k��
	g_Object_Bar[id].span.x = g_Object_Bar[id].HPspan * (float)HP;

	// �F���ύX���Ă���
	g_Object_Bar[id].col.g = g_Object_Bar[id].HPcol * (float)HP;
	g_Object_Bar[id].col.r = 1.5f - g_Object_Bar[id].col.g;

	// �\�����Ԃ�ݒ�
	g_Object_Bar[id].dur = 240;

	// �ʒu�𓯊�
	g_Object_Bar[id].pos = pos;
	g_Object_Bar[id].pos.y = 30.0f;
}