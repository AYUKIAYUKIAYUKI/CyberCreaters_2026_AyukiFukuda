//************************************************
//
// ���j�G�t�F�N�g[effect_burn.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "effect_burn.h"

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
#define MAX_EFFECT_BURN 256	// ���j�G�t�F�N�g�̍ő吔

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect_Burn = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureEffect_Burn = NULL;		// �e�N�X�`���ւ̃|�C���^
Effect_Burn g_Effect_Burn[MAX_EFFECT_BURN];			// ���j�G�t�F�N�g���

/*---�y�v���g�^�C�v�錾�z---*/

// ����
void ImportTexEffect_Burn(void);		// �e�N�X�`���擾
void CreateVtxBufferEffect_Burn(void);	// ���_���𐶐�

// �X�V
void SetVtxEffect_Burn(void);	// �W�J

void AnimationCnt_Burn(int id);		// ���j�F�e�N�X�`���J�E���g�p

TextureSize SetTexEffect_Burn(int id);	// �e�N�X�`���Ǘ��p

//************************************************
// ��������
//************************************************
void InitEffect_Burn(void)
{
	for (int i = 0; i < MAX_EFFECT_BURN; i++)
	{ // ���j�G�t�F�N�g��񃊃Z�b�g

		g_Effect_Burn[i].use = false;								// �g�p�t���O
		g_Effect_Burn[i].pPos = nullptr;							// �Ώۈʒu
		g_Effect_Burn[i].pos_moved = { 0.0f, 0.0f, 0.0f };			// �ϓ��ʒu
		g_Effect_Burn[i].pos = { 0.0f, 0.0f, 0.0f };				// �ʒu
		g_Effect_Burn[i].rot = { 0.0f, 0.0f, 0.0f };				// ����
		g_Effect_Burn[i].span = { 0.0f, 0.0f };						// �傫���p
		g_Effect_Burn[i].angle = 0.0f;									// �p�x
		g_Effect_Burn[i].length = 0.0f;							// �Ίp���p
		g_Effect_Burn[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
		g_Effect_Burn[i].remain = 0;								// ����

		g_Effect_Burn[i].anima.row = 0;			// �s
		g_Effect_Burn[i].anima.column = 0;		// ��
		g_Effect_Burn[i].anima.id_pattern = 0;	// ���݂̃p�^�[��
		g_Effect_Burn[i].anima.dur_cnt = 0;		// �p�^�[���J�ڊԊu
		g_Effect_Burn[i].anima.id_cnt = 0;		// �J�ڃJ�E���^�[
	}

	/*--------------------------------------------*/

	// �e�N�X�`�������擾
	ImportTexEffect_Burn();

	// ���_���𐶐�
	CreateVtxBufferEffect_Burn();
}

//************************************************
// �e�N�X�`������ǂݍ���
//************************************************
void ImportTexEffect_Burn(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	// �e�N�X�`���摜�̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\effect_ring.png",
		&g_pTextureEffect_Burn);
}

//************************************************
// ���_���𐶐�
//************************************************
void CreateVtxBufferEffect_Burn(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * MAX_EFFECT_BURN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect_Burn,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffEffect_Burn->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_EFFECT_BURN; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffEffect_Burn->Unlock();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// �I������
//************************************************
void UninitEffect_Burn(void)
{
	if (g_pTextureEffect_Burn != NULL)
	{ // �e�N�X�`���̔j��

		g_pTextureEffect_Burn->Release();
		g_pTextureEffect_Burn = NULL;
	}

	if (g_pVtxBuffEffect_Burn != NULL)
	{ // ���_�o�b�t�@�̔j��

		g_pVtxBuffEffect_Burn->Release();
		g_pVtxBuffEffect_Burn = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// �X�V����
//************************************************
void UpdateEffect_Burn(void)
{
	for (int i = 0; i < MAX_EFFECT_BURN; i++)
	{
		if (!g_Effect_Burn[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[

			continue;
		}

		g_Effect_Burn[i].remain--;

		if (g_Effect_Burn[i].remain < 4)
		{
			g_Effect_Burn[i].span *= 0.8f;
		}

		if (g_Effect_Burn[i].remain < 0)
		{
			DeleteEffect_Burn(i);
		}

		// �Y��Ɍ�����悤����������
		g_Effect_Burn[i].pos.y = 1.0f;
	}

	// �|���S����W�J
	SetVtxEffect_Burn();
}

//************************************************
// ���j�G�t�F�N�g�W�J
//************************************************
void SetVtxEffect_Burn(void)
{
	VERTEX_3D* pVtx;		// ���_���̃|�C���^
	TextureSize tex = {};	// �e�N�X�`���T�C�Y

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_EFFECT_BURN; i++)
	{ // ���_�ʒu�p�̏����Z�o

		if (!g_Effect_Burn[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[

			continue;
		}

		// �p�x���Z�o
		g_Effect_Burn[i].angle = atan2f(g_Effect_Burn[i].span.x, g_Effect_Burn[i].span.y);

		// �Ίp�����Z�o
		g_Effect_Burn[i].length = sqrtf(g_Effect_Burn[i].span.x * g_Effect_Burn[i].span.x + g_Effect_Burn[i].span.y * g_Effect_Burn[i].span.y);
	}

	/*--------------------------------------------*/

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffEffect_Burn->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_EFFECT_BURN; i++, pVtx += AMOUNT_VTX)
	{
		if (!g_Effect_Burn[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[

			continue;
		}

		// ���_�̓W�J
		pVtx[0].pos =
		{
			sinf(g_Effect_Burn[i].rot.z - (D3DX_PI - g_Effect_Burn[i].angle)) * g_Effect_Burn[i].length,
			0.0f,
			-cosf(g_Effect_Burn[i].rot.z - (D3DX_PI - g_Effect_Burn[i].angle)) * g_Effect_Burn[i].length
		};

		pVtx[1].pos =
		{
			sinf(g_Effect_Burn[i].rot.z + (D3DX_PI - g_Effect_Burn[i].angle)) * g_Effect_Burn[i].length,
			0.0f,
			-cosf(g_Effect_Burn[i].rot.z + (D3DX_PI - g_Effect_Burn[i].angle)) * g_Effect_Burn[i].length
		};

		pVtx[2].pos =
		{
			sinf(g_Effect_Burn[i].rot.z - g_Effect_Burn[i].angle) * g_Effect_Burn[i].length,
			0.0f,
			-cosf(g_Effect_Burn[i].rot.z - g_Effect_Burn[i].angle) * g_Effect_Burn[i].length
		};

		pVtx[3].pos =
		{
			sinf(g_Effect_Burn[i].rot.z + g_Effect_Burn[i].angle) * g_Effect_Burn[i].length,
			0.0f,
			-cosf(g_Effect_Burn[i].rot.z + g_Effect_Burn[i].angle) * g_Effect_Burn[i].length
		};

		// �J���[���f
		pVtx[0].col = g_Effect_Burn[i].col;
		pVtx[1].col = g_Effect_Burn[i].col;
		pVtx[2].col = g_Effect_Burn[i].col;
		pVtx[3].col = g_Effect_Burn[i].col;

		// �e�N�X�`���A�j���[�V�����Ǘ�
		tex = SetTexEffect_Burn(i);

		// �e�N�X�`���T�C�Y���f
		pVtx[0].tex = tex.size[0];
		pVtx[1].tex = tex.size[1];
		pVtx[2].tex = tex.size[2];
		pVtx[3].tex = tex.size[3];
	}

	g_pVtxBuffEffect_Burn->Unlock();
}

//************************************************
// �e�N�X�`���A�j���[�V�����Ǘ�
//************************************************
TextureSize SetTexEffect_Burn(int id)
{
	TextureSize tex = {};	// �e�N�X�`���T�C�Y�i�[

	// ���j�F5�� * 3�s�̃p�^�[���Ōv�Z
	float row = 1.0f / g_Effect_Burn[id].anima.row;			// 1������̍s�T�C�Y
	float column = 1.0f / g_Effect_Burn[id].anima.column;	// 1������̗�T�C�Y

	// ���j�F�e�N�X�`���J�E���g�p
	AnimationCnt_Burn(id);

	float x = 1.0f + (g_Effect_Burn[id].anima.id_pattern * 1.0f);
	float y = 1.0f;

	if (g_Effect_Burn[id].anima.id_pattern >= 5 &&
		g_Effect_Burn[id].anima.id_pattern < 10)
	{
		y = 2.0f;
	}
	else if (g_Effect_Burn[id].anima.id_pattern >= 10)
	{
		y = 3.0f;
	}

	tex = {
		D3DXVECTOR2(column * (x - 1.0f), row * (y - 1.0f)),
		D3DXVECTOR2(column * x, row * (y - 1.0f)),
		D3DXVECTOR2(column * (x - 1.0f), row * y),
		D3DXVECTOR2(column * x, row * y),
	};

	return tex;	// �e�N�X�`���T�C�Y��n��
}

//************************************************
// ���j�F�e�N�X�`���J�E���g�p
//************************************************
void AnimationCnt_Burn(int id)
{
	if (g_Effect_Burn[id].anima.id_cnt < g_Effect_Burn[id].anima.dur_cnt)
	{ // ����̊Ԋu�܂ŃJ�E���g

		g_Effect_Burn[id].anima.id_cnt++;
	}
	else
	{ // ����̊Ԋu�ɒB�����

		g_Effect_Burn[id].anima.id_cnt = 0;		// �J�E���g���Z�b�g
		g_Effect_Burn[id].anima.id_pattern++;	// �p�^�[����i�߂�

		if (g_Effect_Burn[id].anima.id_pattern >= 15)
		{ // 15�p�^�[���ɓ��B�Ń��Z�b�g�H

			g_Effect_Burn[id].anima.id_pattern = 0;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// �`�揈��
//************************************************
void DrawEffect_Burn(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans/*, mtxView*/;			// �v�Z�p�}�g���b�N�X

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
	pDevice->SetStreamSource(0, g_pVtxBuffEffect_Burn, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < MAX_EFFECT_BURN; i++)
	{
		if (!g_Effect_Burn[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Effect_Burn[i].mtx);

		//// �r���[�}�g���b�N�X�擾
		//pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//// �|���S�����J�����̐��ʂɌ���������
		//D3DXMatrixInverse(&g_Effect_Burn[i].mtx, NULL, &mtxView);	// �t�s������߂�

		g_Effect_Burn[i].mtx._41 = 0.0f;
		g_Effect_Burn[i].mtx._42 = 0.0f;
		g_Effect_Burn[i].mtx._43 = 0.0f;

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Effect_Burn[i].pos.x,
			g_Effect_Burn[i].pos.y,
			g_Effect_Burn[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Effect_Burn[i].mtx,
			&g_Effect_Burn[i].mtx,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Effect_Burn[i].mtx);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureEffect_Burn);

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
// ���j�G�t�F�N�g����
//************************************************
void CreateEffect_Burn(D3DXVECTOR3 pos , float rad)
{
	for (int i = 0; i < MAX_EFFECT_BURN; i++)
	{
		if (g_Effect_Burn[i].use)
		{ // �g�p���Ȃ�R���e�B�j���[
			continue;
		}

		g_Effect_Burn[i].use = true;
		g_Effect_Burn[i].pos = pos;	// �Ώۈʒu���擾

		g_Effect_Burn[i].span = { rad * 1.5f, rad * 1.5f };		// �傫���F�K��
		g_Effect_Burn[i].remain = -1;				// �����F����
		g_Effect_Burn[i].anima.row = 3;				// 3�s
		g_Effect_Burn[i].anima.column = 5;			// 5��
		g_Effect_Burn[i].anima.dur_cnt = 1;			// �J�ڊԊu�F�K��

		g_Effect_Burn[i].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	// �F
		g_Effect_Burn[i].remain = 25;

		break;	// �I��
	}
}

//************************************************
// ���j�G�t�F�N�g����
//************************************************
void DeleteEffect_Burn(int id)
{
	g_Effect_Burn[id].use = false;								// �g�p�t���O
	g_Effect_Burn[id].pPos = nullptr;							// �Ώۈʒu
	g_Effect_Burn[id].pos_moved = { 0.0f, 0.0f, 0.0f };			// �ϓ��ʒu
	g_Effect_Burn[id].pos = { 0.0f, 0.0f, 0.0f };				// �ʒu
	g_Effect_Burn[id].rot = { 0.0f, 0.0f, 0.0f };				// ����
	g_Effect_Burn[id].span = { 0.0f, 0.0f };					// �傫���p
	g_Effect_Burn[id].angle = 0.0f;								// �p�x
	g_Effect_Burn[id].length = 0.0f;							// �Ίp���p
	g_Effect_Burn[id].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	g_Effect_Burn[id].remain = 0;								// ����

	g_Effect_Burn[id].anima.row = 0;		// ���s��
	g_Effect_Burn[id].anima.column = 0;		// ����
	g_Effect_Burn[id].anima.id_pattern = 0;	// ���݂̃p�^�[��
	g_Effect_Burn[id].anima.dur_cnt = 0;	// �p�^�[���J�ڊԊu
	g_Effect_Burn[id].anima.id_cnt = 0;		// �J�ڃJ�E���^�[
}