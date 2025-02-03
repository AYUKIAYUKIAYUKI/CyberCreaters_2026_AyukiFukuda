//************************************************
//
// ���G�t�F�N�g[effect_soul.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "effect_soul.h"

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
#define MAX_EFFECT_SOUL 256	// ���G�t�F�N�g�̍ő吔

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect_Soul = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEffect_Soul = NULL;		// �e�N�X�`���ւ̃|�C���^
Effect_Soul g_Effect_Soul[MAX_EFFECT_SOUL];				// ���G�t�F�N�g���

/*---�y�v���g�^�C�v�錾�z---*/

// ����
void ImportTexEffect_Soul(void);		// �e�N�X�`���擾
void CreateVtxBufferEffect_Soul(void);	// ���_���𐶐�

// �X�V
void SetVtxEffect_Soul(void);	// �W�J

void AnimationManager_Soul(int id);	// �A�j���[�V��������Ǘ��p
void AnimationPlay_Soul(int id);	// ���F�A�j���[�V��������p

TextureSize SetTexEffect_Soul(void);	// �e�N�X�`���Ǘ��p

void DeleteEffect_Soul(int id);	// ����

//************************************************
// ��������
//************************************************
void InitEffect_Soul(void)
{
	for (int i = 0; i < MAX_EFFECT_SOUL; i++)
	{ // ���G�t�F�N�g��񃊃Z�b�g

		g_Effect_Soul[i].use = false;								// �g�p�t���O
		g_Effect_Soul[i].pPos = nullptr;							// �Ώۈʒu
		g_Effect_Soul[i].pos_moved = { 0.0f, 0.0f, 0.0f };			// �ϓ��ʒu
		g_Effect_Soul[i].pos = { 0.0f, 0.0f, 0.0f };				// �ʒu
		g_Effect_Soul[i].rot = { 0.0f, 0.0f, 0.0f };				// ����
		g_Effect_Soul[i].span = { 0.0f, 0.0f };						// �傫���p
		g_Effect_Soul[i].angle = 0.0f;								// �p�x
		g_Effect_Soul[i].length = 0.0f;								// �Ίp���p
		g_Effect_Soul[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		g_Effect_Soul[i].remain = 0;								// ����

		g_Effect_Soul[i].anima.row = 0;			// �s
		g_Effect_Soul[i].anima.column = 0;		// ��
		g_Effect_Soul[i].anima.id_pattern = 0;	// ���݂̃p�^�[��
		g_Effect_Soul[i].anima.dur_cnt = 0;		// �p�^�[���J�ڊԊu
		g_Effect_Soul[i].anima.id_cnt = 0;		// �J�ڃJ�E���^�[
	}

	/*--------------------------------------------*/

	// �e�N�X�`�������擾
	ImportTexEffect_Soul();

	// ���_���𐶐�
	CreateVtxBufferEffect_Soul();
}

//************************************************
// �e�N�X�`������ǂݍ���
//************************************************
void ImportTexEffect_Soul(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\soul.png",
		&g_pTextureEffect_Soul);
}

//************************************************
// ���_���𐶐�
//************************************************
void CreateVtxBufferEffect_Soul(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * MAX_EFFECT_SOUL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect_Soul,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffEffect_Soul->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_EFFECT_SOUL; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffEffect_Soul->Unlock();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// �I������
//************************************************
void UninitEffect_Soul(void)
{
	if (g_pTextureEffect_Soul != NULL)
	{ // �e�N�X�`���̔j��

		g_pTextureEffect_Soul->Release();
		g_pTextureEffect_Soul = NULL;
	}

	if (g_pVtxBuffEffect_Soul != NULL)
	{ // ���_�o�b�t�@�̔j��

		g_pVtxBuffEffect_Soul->Release();
		g_pVtxBuffEffect_Soul = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// �X�V����
//************************************************
void UpdateEffect_Soul(void)
{
	for (int i = 0; i < MAX_EFFECT_SOUL; i++)
	{
		if (!g_Effect_Soul[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[

			continue;
		}

		// �A�j���[�V��������p
		AnimationManager_Soul(i);

		// �Ώۈʒu�ɕϓ��ʒu�����Z
		g_Effect_Soul[i].pos = *g_Effect_Soul[i].pPos + g_Effect_Soul[i].pos_moved;

		if (g_Effect_Soul[i].remain != -1)
		{ // �����������łȂ����

			if (CntDuration(&g_Effect_Soul[i].remain))
			{ // ���ԏI����

				// ����
				DeleteEffect_Soul(i);
			}
		}
	}

	// �|���S����W�J
	SetVtxEffect_Soul();
}

//************************************************
// �A�j���[�V��������Ǘ��p
//************************************************
void AnimationManager_Soul(int id)
{
	// ���̍Đ�
	AnimationPlay_Soul(id);
}

//************************************************
// ���F�A�j���[�V��������p
//************************************************
void AnimationPlay_Soul(int id)
{
	// �ȉ��A�㏸�A���ł���悤�ɒ���
	g_Effect_Soul[id].pos_moved.y += 1.15f - (1.0f - g_Effect_Soul[id].col.a) * 2.0f;
	g_Effect_Soul[id].span = g_Effect_Soul[id].span - (g_Effect_Soul[id].span * 0.01f);
	g_Effect_Soul[id].col.a -= 0.0025f;
}

//************************************************
// ���G�t�F�N�g����
//************************************************
void DeleteEffect_Soul(int id)
{
	g_Effect_Soul[id].use = false;								// �g�p�t���O
	g_Effect_Soul[id].pPos = nullptr;							// �Ώۈʒu
	g_Effect_Soul[id].pos_moved = { 0.0f, 0.0f, 0.0f };			// �ϓ��ʒu
	g_Effect_Soul[id].pos = { 0.0f, 0.0f, 0.0f };				// �ʒu
	g_Effect_Soul[id].rot = { 0.0f, 0.0f, 0.0f };				// ����
	g_Effect_Soul[id].span = { 0.0f, 0.0f };					// �傫���p
	g_Effect_Soul[id].angle = 0.0f;								// �p�x
	g_Effect_Soul[id].length = 0.0f;							// �Ίp���p
	g_Effect_Soul[id].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	g_Effect_Soul[id].remain = 0;								// ����

	g_Effect_Soul[id].anima.row = 0;		// ���s��
	g_Effect_Soul[id].anima.column = 0;		// ����
	g_Effect_Soul[id].anima.id_pattern = 0;	// ���݂̃p�^�[��
	g_Effect_Soul[id].anima.dur_cnt = 0;	// �p�^�[���J�ڊԊu
	g_Effect_Soul[id].anima.id_cnt = 0;		// �J�ڃJ�E���^�[
}

//************************************************
// ���G�t�F�N�g�W�J
//************************************************
void SetVtxEffect_Soul(void)
{
	VERTEX_3D* pVtx;		// ���_���̃|�C���^
	TextureSize tex = {};	// �e�N�X�`���T�C�Y

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_EFFECT_SOUL; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_Effect_Soul[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[

			continue;
		}

		// �p�x���Z�o
		g_Effect_Soul[i].angle = atan2f(g_Effect_Soul[i].span.x, g_Effect_Soul[i].span.y);

		// �Ίp�����Z�o
		g_Effect_Soul[i].length = sqrtf(g_Effect_Soul[i].span.x * g_Effect_Soul[i].span.x + g_Effect_Soul[i].span.y * g_Effect_Soul[i].span.y);
	}

	/*--------------------------------------------*/

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffEffect_Soul->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_EFFECT_SOUL; i++, pVtx += AMOUNT_VTX)
	{
		if (!g_Effect_Soul[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[

			continue;
		}

		// ���_�̓W�J
		pVtx[0].pos =
		{
			sinf(g_Effect_Soul[i].rot.z - (D3DX_PI - g_Effect_Soul[i].angle)) * g_Effect_Soul[i].length,
			-cosf(g_Effect_Soul[i].rot.z - (D3DX_PI - g_Effect_Soul[i].angle)) * g_Effect_Soul[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			sinf(g_Effect_Soul[i].rot.z + (D3DX_PI - g_Effect_Soul[i].angle)) * g_Effect_Soul[i].length,
			-cosf(g_Effect_Soul[i].rot.z + (D3DX_PI - g_Effect_Soul[i].angle)) * g_Effect_Soul[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			sinf(g_Effect_Soul[i].rot.z - g_Effect_Soul[i].angle) * g_Effect_Soul[i].length,
			-cosf(g_Effect_Soul[i].rot.z - g_Effect_Soul[i].angle) * g_Effect_Soul[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			sinf(g_Effect_Soul[i].rot.z + g_Effect_Soul[i].angle) * g_Effect_Soul[i].length,
			-cosf(g_Effect_Soul[i].rot.z + g_Effect_Soul[i].angle) * g_Effect_Soul[i].length,
			0.0f
		};

		// �J���[���f
		pVtx[0].col = g_Effect_Soul[i].col;
		pVtx[1].col = g_Effect_Soul[i].col;
		pVtx[2].col = g_Effect_Soul[i].col;
		pVtx[3].col = g_Effect_Soul[i].col;

#if 0	// (�e�N�X�`���A�j���[�V��������)

		// �e�N�X�`���A�j���[�V�����Ǘ�
		tex = SetTexEffect_Soul(i);

		// �e�N�X�`���T�C�Y���f
		pVtx[0].tex = tex.size[0];
		pVtx[1].tex = tex.size[1];
		pVtx[2].tex = tex.size[2];
		pVtx[3].tex = tex.size[3];

#endif
	}

	g_pVtxBuffEffect_Soul->Unlock();
}

//************************************************
// �e�N�X�`���A�j���[�V�����Ǘ�
//************************************************
TextureSize SetTexEffect_Soul(void)
{
	TextureSize tex = {};	// �e�N�X�`���T�C�Y�i�[

	// ���F�Œ�
	tex = {
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(1.0f, 0.0f),
		D3DXVECTOR2(0.0f, 1.0f),
		D3DXVECTOR2(1.0f, 1.0f),
	};

	return tex;	// �e�N�X�`���T�C�Y��n��
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// �`�揈��
//************************************************
void DrawEffect_Soul(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans, mtxView;				// �v�Z�p�}�g���b�N�X

	// ���C�g���f�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//// �[�x�e�X�g�̔�r���@�̕ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//// �[�x�o�b�t�@�ɕ`�悵�Ȃ�
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect_Soul, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < MAX_EFFECT_SOUL; i++)
	{
		if (!g_Effect_Soul[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Effect_Soul[i].mtx);

		// �r���[�}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// �|���S�����J�����̐��ʂɌ���������
		D3DXMatrixInverse(&g_Effect_Soul[i].mtx, NULL, &mtxView);	// �t�s������߂�

		g_Effect_Soul[i].mtx._41 = 0.0f;
		g_Effect_Soul[i].mtx._42 = 0.0f;
		g_Effect_Soul[i].mtx._43 = 0.0f;

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Effect_Soul[i].pos.x,
			g_Effect_Soul[i].pos.y,
			g_Effect_Soul[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Effect_Soul[i].mtx,
			&g_Effect_Soul[i].mtx,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Effect_Soul[i].mtx);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureEffect_Soul);

		// �r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// ���C�g���f��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//// �[�x�e�X�g�̔�r���@�̕ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//// �[�x�o�b�t�@�ɏ�������
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// ���G�t�F�N�g����
//************************************************
int CreateEffect_Soul(D3DXVECTOR3* pPos)
{
	int id = 0;	// ���ʔԍ��p

	for (int i = 0; i < MAX_EFFECT_SOUL; i++)
	{
		if (g_Effect_Soul[i].use)
		{ // �g�p���Ȃ�R���e�B�j���[
			continue;
		}

		g_Effect_Soul[i].use = true;
		g_Effect_Soul[i].pPos = pPos;	// �Ώۈʒu���擾

		g_Effect_Soul[i].span = { 10.0f, 25.0f };	// �傫���F�K��
		g_Effect_Soul[i].remain = 220;				// �����F�K��

		id = i;	// ���ʔԍ��i�[

		break;	// �I��
	}

	return id;	// �ꉞ���ʔԍ���n��
}