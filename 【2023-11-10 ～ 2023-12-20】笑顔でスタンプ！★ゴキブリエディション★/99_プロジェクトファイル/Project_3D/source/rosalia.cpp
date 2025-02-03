//************************************************
//
//���U���A����[rosalia.cpp]
//Author�F���c����
//
//************************************************
#include "rosalia.h"

#include "sound.h"

#include "player.h"
#include "shadow.h"

//�}�N����`
#define AMOUNT_ROSALIA	(1)	//���U���A�̐�
#define SPAN_ROZALIA	(5.0f)	//�T�C�Y

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRosalia = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRosalia = NULL;	//�e�N�X�`���ւ̃|�C���^
Rosalia g_aRosalia[AMOUNT_ROSALIA] = {};

//************************************************
//���U���A����
//************************************************
void InitRosalia(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���U���A��񏉊���
	for (int i = 0; i < AMOUNT_ROSALIA; i++)
	{
		g_aRosalia[i].pos = D3DXVECTOR3(0.0f, 10.0f, 90.0f);
		g_aRosalia[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\Rozalia.png",
		&g_pTextureRosalia);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_ROSALIA,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRosalia,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffRosalia->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_ROSALIA; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRosalia->Unlock();

	//����̂݁A�T�C�Y�Z�b�g
	SetSizeRosalia();
}

//************************************************
//���U���A�j��
//************************************************
void UninitRosalia(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRosalia != NULL)
	{
		g_pTextureRosalia->Release();
		g_pTextureRosalia = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRosalia != NULL)
	{
		g_pVtxBuffRosalia->Release();
		g_pVtxBuffRosalia = NULL;
	}
}

//************************************************
//���U���A�X�V
//************************************************
void UpdateRosalia(void)
{
	////�����v�Z
	//Player* pPlayer = GetInfoPlayer();
	//D3DXVECTOR3 Vector = pPlayer[0].pos - g_aRosalia[0].pos;
	//float fDistance = sqrtf((Vector.x * Vector.x) + (Vector.z * Vector.z)) * 0.5f;

	////���ʏ����擾
	//float* pVol = GetInfoSoundVol();

	////����Ă���Ə���
	//pVol[SOUND_LABEL_ROSALIA] = 0.0f;

	////���͈͓��ŉ��ʕύX
	//if (fDistance < 100.0f)
	//{
	//	//���������̊����ŋ߂Â��Ɖ��ʑ���
	//	pVol[SOUND_LABEL_ROSALIA] = (100.0f - fDistance) / 100;
	//}

	////�Őڋ߂Ŕ���
	//if (pVol[SOUND_LABEL_ROSALIA] >= 0.9f)
	//{
	//	pVol[SOUND_LABEL_ROSALIA] = 1000.0f;
	//}

	////���ʂ𔽉f
	//SetInfoSoundVol(SOUND_LABEL_ROSALIA);
}

//************************************************
//���U���A�T�C�Y�Z�b�g
//************************************************
void SetSizeRosalia(void)
{
	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffRosalia->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_ROSALIA; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-SPAN_ROZALIA, SPAN_ROZALIA * 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_ROZALIA, SPAN_ROZALIA * 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_ROZALIA, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_ROZALIA, 0.0f, 0.0f);

		pVtx += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRosalia->Unlock();
}

//************************************************
//���U���A�`��
//************************************************
void DrawRosalia(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���C�g���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;

	for (int i = 0; i < AMOUNT_ROSALIA; i++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aRosalia[i].mtxWorld);

		//�r���[�}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����̐��ʂɌ���������
		D3DXMatrixInverse(&g_aRosalia[i].mtxWorld, NULL, &mtxView);	//�t�s������߂�

		g_aRosalia[i].mtxWorld._41 = 0.0f;
		g_aRosalia[i].mtxWorld._42 = 0.0f;
		g_aRosalia[i].mtxWorld._43 = 0.0f;

		//�ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aRosalia[i].pos.x,
			g_aRosalia[i].pos.y,
			g_aRosalia[i].pos.z);

		//�ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aRosalia[i].mtxWorld,
			&g_aRosalia[i].mtxWorld,
			&mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aRosalia[i].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffRosalia, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRosalia);

		//���U���A�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//���C�g���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}