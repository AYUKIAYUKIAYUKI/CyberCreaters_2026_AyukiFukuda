//************************************************
//
// ���`�̓����蔻�������[visible_box.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "visible_box.h"

// ������
#include "player.h"
#include "debugproc.h"
#include "input.h"
#include "object.h"

/*---�y�}�N����`�z---*/
#define MAX_BOX	512	//�{�b�N�X�̍ő吔

/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBox = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffBox = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Box g_Box[MAX_BOX] = {};						// �{�b�N�X���
// 1�{�b�N�X������
static const int g_AmountVtx = 8;						// ���_�̐�
static const int g_AmountPrimitive = 12;				// �ӂ̐�
static const int g_AmountIdx = g_AmountPrimitive * 2;	// �C���f�b�N�X�̐�

/*---�y�v���g�^�C�v�錾�z---*/
void SetVtxVisibleBox(void);	// �{�b�N�X��W�J����

//************************************************
// �{�b�N�X����
//************************************************
void InitVisibleBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_BOX; i++)
	{
		g_Box[i].use = false;
		g_Box[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Box[i].aabb = nullptr;
		g_Box[i].col = { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	/*--------------------------------------------*/

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_AmountVtx * MAX_BOX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBox,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffBox->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_BOX; i++, pVtx += g_AmountVtx)
	{
		for (int j = 0; j < g_AmountVtx; j++)
		{
			// ���_���W�̐ݒ�
			pVtx[j].pos = { 0.0f, 0.0f, 0.0f };

			// �@���x�N�g���̐ݒ�
			pVtx[j].nor = { 0.0f, 0.0f, 0.0f };

			// ���_�J���[�̏����ݒ�
			pVtx[j].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̏����ݒ�
			pVtx[j].tex = { 0.0f, 0.0f };
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBox->Unlock();

	/*--------------------------------------------*/

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_AmountIdx * MAX_BOX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffBox,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBuffBox->Lock(0, 0, (void**)&pIdx, 0);

	for (int i = 0; i < MAX_BOX; i++)
	{
		// X���ɕ��s�Ȑ�������
		for (int j = 0; j < 8; j++, pIdx++)
		{
			pIdx[0] = (WORD)j;
		}

		// Y���ɕ��s�Ȑ�������
		for (int j = 0, k = 0; j < 4; j++, pIdx += 2)
		{
			if (j == 2) k += 2;	// 0,1,4,5�����C�̎n�_�ɂ��邽��3,4�̃C���f�b�N�X���΂�

			pIdx[0] = (WORD)(j + k);
			pIdx[1] = (WORD)(j + 2 + k);
		}

		// Z���ɕ��s�Ȑ�������
		for (int j = 0; j < 4; j++, pIdx += 2)
		{
			pIdx[0] = (WORD)(j);
			pIdx[1] = (WORD)(j + 4);
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffBox->Unlock();

	// �����I�ɔ���\��
	//CreateVisibleBox({ { 0.0f, 0.0f, 0.0f }, { 40.0f, 100.0f, 40.0f } }, { 0.0f, 1.0f, 1.0f, 1.0f }, &g_Box[0].aabb.pos);
}

//************************************************
// �{�b�N�X�W�J
//************************************************
int CreateVisibleBox(COLLISION_AABB* box, D3DXCOLOR col)
{
	VERTEX_3D* pVtx;	// ���_���̃|�C���^
	int id = -1;		// ���ʔԍ��i�[

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffBox->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_BOX; i++, pVtx += g_AmountVtx)
	{
		if (g_Box[i].use)
		{ // �g�p����Ă�����R���e�B�j���[
			continue;
		}

		g_Box[i].use = true;
		g_Box[i].aabb = box;	// ������̃A�h���X��n��

#if 0	// �Ώۂ̃��[���h���W�𑊎E�����_��W�J

		pVtx[0].pos = { box.min.x - pPos->x, box.max.y - pPos->y, box.min.z - pPos->z };
		pVtx[1].pos = { box.max.x - pPos->x, box.max.y - pPos->y, box.min.z - pPos->z };
		pVtx[2].pos = { box.min.x - pPos->x, box.min.y - pPos->y, box.min.z - pPos->z };
		pVtx[3].pos = { box.max.x - pPos->x, box.min.y - pPos->y, box.min.z - pPos->z };
		pVtx[4].pos = { box.min.x - pPos->x, box.max.y - pPos->y, box.max.z - pPos->z };
		pVtx[5].pos = { box.max.x - pPos->x, box.max.y - pPos->y, box.max.z - pPos->z };
		pVtx[6].pos = { box.min.x - pPos->x, box.min.y - pPos->y, box.max.z - pPos->z };
		pVtx[7].pos = { box.max.x - pPos->x, box.min.y - pPos->y, box.max.z - pPos->z };

#elif 0	// Y����␳���W�J

		pVtx[0].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[1].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[2].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[3].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[4].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[5].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[6].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[7].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };

#elif 1	// �ʏ�W�J

		pVtx[0].pos = { -g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[1].pos = { +g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[2].pos = { -g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[3].pos = { +g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[4].pos = { -g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[5].pos = { +g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[6].pos = { -g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[7].pos = { +g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };

#endif	// ���_�̓W�J���@����

		for (int j = 0; j < g_AmountVtx; j++)
		{
			pVtx[j].col = col;
		}

		break;
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBox->Unlock();

	return id;	// ���ʔԍ���Ԃ�
}

//************************************************
// �{�b�N�X�j��
//************************************************
void UninitVisibleBox(void)
{
	if (g_pVtxBuffBox != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffBox->Release();
		g_pVtxBuffBox = NULL;
	}

	if (g_pIdxBuffBox != NULL)
	{ // �C���f�b�N�X�o�b�t�@�̔j��
		g_pIdxBuffBox->Release();
		g_pIdxBuffBox = NULL;
	}
}

//************************************************
// �{�b�N�X�X�V
//************************************************
void UpdateVisibleBox(void)
{
	//�Ώە��̒��S��
	for (int i = 0; i < MAX_BOX; i++)
	{
		if (!g_Box[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �x�[�X�̔���ɓ���
		g_Box[i].pos = g_Box[i].aabb->pos;
	}

#if 0	// �����炩��I�u�W�F�N�g���񂵂Ĕ��̐��@��ύX���郄�c

	Object* obj = GetInfoObject();

	obj->rot.y += D3DX_PI / 100.0f;

	// ��]�𑱂��Ă���e�C�̐��l
	if (obj->rot.y >= D3DX_PI)
	{
		obj->rot.y = -D3DX_PI;
	}

	PrintDebugProc("\nobj1 rot y�F%f\n", obj->rot.y);

	// �T�C�Y���ς�葱����
	if (GetKeyboardPress(DIK_SPACE))
	{
		g_Box[0].aabb->vec.x = obj->model.aabb.vec.x;
		g_Box[0].aabb->vec.z = obj->model.aabb.vec.z;
	}
	else
	{
		g_Box[0].aabb->vec.x = obj->model.aabb.vec.x * cosf(obj->rot.y);
	}

#endif

	// �{�b�N�X��W�J
	SetVtxVisibleBox();

	// �s��v�Z
	CalcMtxVisibleBox();
}

//************************************************
// �{�b�N�X��W�J
//************************************************
void SetVtxVisibleBox(void)
{
	VERTEX_3D* pVtx;	// ���_���̃|�C���^

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffBox->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_BOX; i++, pVtx += g_AmountVtx)
	{
		if (!g_Box[i].use)
		{ // �g�p����Ă�����R���e�B�j���[
			continue;
		}

#if 0	// Y����␳���W�J

		pVtx[0].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[1].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[2].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[3].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[4].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[5].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) + g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[6].pos = { -g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[7].pos = { +g_Box[i].aabb->vec.x, (g_Box[i].aabb->pos.y + g_Box[i].aabb->vec.y) - g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
	
#elif 1	// �ʏ�W�J

		pVtx[0].pos = { -g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[1].pos = { +g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[2].pos = { -g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[3].pos = { +g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, -g_Box[i].aabb->vec.z };
		pVtx[4].pos = { -g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[5].pos = { +g_Box[i].aabb->vec.x, +g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[6].pos = { -g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };
		pVtx[7].pos = { +g_Box[i].aabb->vec.x, -g_Box[i].aabb->vec.y, +g_Box[i].aabb->vec.z };

#endif	// ���_�̓W�J���@����
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBox->Unlock();
}

//************************************************
// �{�b�N�X�p�̍s����v�Z
//************************************************
void CalcMtxVisibleBox(void)
{
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X

	for (int i = 0; i < MAX_BOX; i++)
	{
		if (!g_Box[i].use)
		{ //  ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Box[i].mtxWorld);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Box[i].pos.x,
			g_Box[i].pos.y,
			g_Box[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Box[i].mtxWorld,
			&g_Box[i].mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// �{�b�N�X�폜
//************************************************
void DeleteVisibleBox(int id)
{
	// �������Z�b�g
	g_Box[id].use = false;
	g_Box[id].pos = { 0.0f, 0.0f, 0.0f };
	g_Box[id].aabb = nullptr;
	g_Box[id].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//************************************************
// �{�b�N�X�`��
//************************************************
void DrawVisibleBox(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���C�g���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBox, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffBox);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < MAX_BOX; i++)
	{
		if (!g_Box[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Box[i].mtxWorld);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// �{�b�N�X�̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, i * g_AmountVtx, 0, g_AmountVtx,
			0, g_AmountPrimitive);
	}

	// ���C�g���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}