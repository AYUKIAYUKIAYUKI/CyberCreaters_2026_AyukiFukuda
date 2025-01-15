//************************************************
//
//�W�����v�G�t�F�N�g����[effect_jump.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "effect_jump.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Effect_Jump = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Effect_Jump = NULL;	//���_�o�b�t�@�̃|�C���^
EFFECT_JUMP g_aEffect_Jump;	//�W�����v�G�t�F�N�g�\����

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Effect_Jump()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_EFFECT_JUMP,
		&g_pTexture_Effect_Jump);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Effect_Jump,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Jump;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Jump->Lock(0, 0, (void**)&pVtx_Effect_Jump, 0);

	//���_���W�̏����ݒ�
	pVtx_Effect_Jump[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Effect_Jump[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Effect_Jump[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Effect_Jump[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Effect_Jump[0].rhw = 1.0f;
	pVtx_Effect_Jump[1].rhw = 1.0f;
	pVtx_Effect_Jump[2].rhw = 1.0f;
	pVtx_Effect_Jump[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Effect_Jump[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Effect_Jump[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Effect_Jump[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Effect_Jump[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Effect_Jump[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Effect_Jump[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Effect_Jump[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Effect_Jump[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Jump->Unlock();

	//�W�����v�G�t�F�N�g�\���̂̏��̏������Q
	g_aEffect_Jump.bUse = false;
	g_aEffect_Jump.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEffect_Jump.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEffect_Jump.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEffect_Jump.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aEffect_Jump.fRadius[nCnt] = 0.0f;
	}
	g_aEffect_Jump.fLength = 0.0f;
	g_aEffect_Jump.fAngle = 0.0f;
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Effect_Jump(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Effect_Jump != NULL)
	{
		g_pTexture_Effect_Jump->Release();
		g_pTexture_Effect_Jump = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Effect_Jump != NULL)
	{
		g_pVtxBuff_Effect_Jump->Release();
		g_pVtxBuff_Effect_Jump = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Effect_Jump(void)
{
	//�ʒu�X�V
	Update_Pos_Effect_Jump();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Effect_Jump(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Effect_Jump, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Effect_Jump);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//�W�����v�G�t�F�N�g�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Effect_Jump(D3DXVECTOR3 pos)
{
	g_aEffect_Jump.pos = pos;
	g_aEffect_Jump.move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_aEffect_Jump.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEffect_Jump.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			g_aEffect_Jump.fRadius[nCnt] = RADIUS_EFFECT_JUMP_X;
			break;
		case 1:
			g_aEffect_Jump.fRadius[nCnt] = RADIUS_EFFECT_JUMP_Y;
			break;
		}
	}
	g_aEffect_Jump.fLength = sqrtf((g_aEffect_Jump.fRadius[0] * g_aEffect_Jump.fRadius[0]) + ((g_aEffect_Jump.fRadius[1]) * (g_aEffect_Jump.fRadius[1])));
	g_aEffect_Jump.fAngle = atan2f(g_aEffect_Jump.fRadius[0] * 2.0f, g_aEffect_Jump.fRadius[1] * 2.0f);
}

//************************************************
//�W�����v�G�t�F�N�g�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Effect_Jump(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Jump;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Jump->Lock(0, 0, (void**)&pVtx_Effect_Jump, 0);

	//�ړ�
	g_aEffect_Jump.pos += g_aEffect_Jump.move;

	//�k��
	g_aEffect_Jump.fLength += -3.0f;

	/*��Œ���*/
	pVtx_Effect_Jump[0].pos.x = g_aEffect_Jump.pos.x + sinf(g_aEffect_Jump.rot.z - (D3DX_PI - g_aEffect_Jump.fAngle)) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[0].pos.y = g_aEffect_Jump.pos.y + cosf(g_aEffect_Jump.rot.z - (D3DX_PI - g_aEffect_Jump.fAngle)) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[1].pos.x = g_aEffect_Jump.pos.x + sinf(g_aEffect_Jump.rot.z + (D3DX_PI - g_aEffect_Jump.fAngle)) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[1].pos.y = g_aEffect_Jump.pos.y + cosf(g_aEffect_Jump.rot.z + (D3DX_PI - g_aEffect_Jump.fAngle)) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[2].pos.x = g_aEffect_Jump.pos.x + sinf(g_aEffect_Jump.rot.z - g_aEffect_Jump.fAngle) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[2].pos.y = g_aEffect_Jump.pos.y + cosf(g_aEffect_Jump.rot.z - g_aEffect_Jump.fAngle) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[3].pos.x = g_aEffect_Jump.pos.x + sinf(g_aEffect_Jump.rot.z + g_aEffect_Jump.fAngle) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[3].pos.y = g_aEffect_Jump.pos.y + cosf(g_aEffect_Jump.rot.z + g_aEffect_Jump.fAngle) * g_aEffect_Jump.fLength;

	//�F�ύX
	g_aEffect_Jump.col.a -= 0.1f;

	pVtx_Effect_Jump[0].col = g_aEffect_Jump.col;
	pVtx_Effect_Jump[1].col = g_aEffect_Jump.col;
	pVtx_Effect_Jump[2].col = g_aEffect_Jump.col;
	pVtx_Effect_Jump[3].col = g_aEffect_Jump.col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Jump->Unlock();
}

//************************************************
//�W�����v�G�t�F�N�g�\���̂̃A�h���X��n��
//************************************************
EFFECT_JUMP* Getinfo_Effect_Jump(void)
{
	return &g_aEffect_Jump;
}