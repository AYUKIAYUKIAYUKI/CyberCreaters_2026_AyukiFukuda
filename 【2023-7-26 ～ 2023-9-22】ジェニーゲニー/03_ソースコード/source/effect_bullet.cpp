//************************************************
//
//�e���G�t�F�N�g����[effect_bullet.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "effect_bullet.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Effect_Bullet = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Effect_Bullet = NULL;	//���_�o�b�t�@�̃|�C���^
EFFECT_BULLET g_aEffect_Bullet[AMOUNT_POLYGON_EFFECT_BULLET];	//�e���G�t�F�N�g�����i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Effect_Bullet()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_EFFECT_BULLET,
		&g_pTexture_Effect_Bullet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_EFFECT_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Effect_Bullet,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Bullet;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Bullet->Lock(0, 0, (void**)&pVtx_Effect_Bullet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_BULLET; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Effect_Bullet[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Bullet[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Bullet[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Bullet[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Effect_Bullet[0].rhw = 1.0f;
		pVtx_Effect_Bullet[1].rhw = 1.0f;
		pVtx_Effect_Bullet[2].rhw = 1.0f;
		pVtx_Effect_Bullet[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Effect_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Effect_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Effect_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Effect_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Effect_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Effect_Bullet += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Bullet->Unlock();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_BULLET; nCnt++)
	{
		g_aEffect_Bullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu��������
		g_aEffect_Bullet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect_Bullet[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect_Bullet[nCnt].fRadius = 0.0f;							//���a��������
		g_aEffect_Bullet[nCnt].nRemain = 0;								//�c�����Ԃ�������
		g_aEffect_Bullet[nCnt].bUse = false;							//�g�p����𖳂���
	}
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Effect_Bullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Effect_Bullet != NULL)
	{
		g_pTexture_Effect_Bullet->Release();
		g_pTexture_Effect_Bullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Effect_Bullet != NULL)
	{
		g_pVtxBuff_Effect_Bullet->Release();
		g_pVtxBuff_Effect_Bullet = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Effect_Bullet(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Bullet;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Bullet->Lock(0, 0, (void**)&pVtx_Effect_Bullet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_BULLET; nCnt++)
	{
		//�G�t�F�N�g���g�p����Ă�Ƃ�
		if (g_aEffect_Bullet[nCnt].bUse)
		{
			//�ړ�
			g_aEffect_Bullet[nCnt].pos += g_aEffect_Bullet[nCnt].move * 0.75f;
			g_aEffect_Bullet[nCnt].pos.x -= 5.0f;

			//�k��
			g_aEffect_Bullet[nCnt].fRadius -= CHANGE_SPD_RADIUS_EFFECT_BULLET;

			//���Ԃ�̖h�~
			if (g_aEffect_Bullet[nCnt].fRadius <= 0)
			{
				g_aEffect_Bullet[nCnt].fRadius = 0.0f;
			}

			pVtx_Effect_Bullet[0].pos.x = g_aEffect_Bullet[nCnt].pos.x - g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[0].pos.y = g_aEffect_Bullet[nCnt].pos.y - g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[1].pos.x = g_aEffect_Bullet[nCnt].pos.x + g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[1].pos.y = g_aEffect_Bullet[nCnt].pos.y - g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[2].pos.x = g_aEffect_Bullet[nCnt].pos.x - g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[2].pos.y = g_aEffect_Bullet[nCnt].pos.y + g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[3].pos.x = g_aEffect_Bullet[nCnt].pos.x + g_aEffect_Bullet[nCnt].fRadius;
			pVtx_Effect_Bullet[3].pos.y = g_aEffect_Bullet[nCnt].pos.y + g_aEffect_Bullet[nCnt].fRadius;

			pVtx_Effect_Bullet[0].col = g_aEffect_Bullet[nCnt].col;
			pVtx_Effect_Bullet[1].col = g_aEffect_Bullet[nCnt].col;
			pVtx_Effect_Bullet[2].col = g_aEffect_Bullet[nCnt].col;
			pVtx_Effect_Bullet[3].col = g_aEffect_Bullet[nCnt].col;

			//�c�����Ԍ���
			g_aEffect_Bullet[nCnt].nRemain--;

			//������
			if (g_aEffect_Bullet[nCnt].nRemain <= 0)
			{
				pVtx_Effect_Bullet[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
				pVtx_Effect_Bullet[1].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
				pVtx_Effect_Bullet[2].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
				pVtx_Effect_Bullet[3].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);

				pVtx_Effect_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Effect_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Effect_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx_Effect_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				g_aEffect_Bullet[nCnt].bUse = false;
			}
		}

		pVtx_Effect_Bullet += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Bullet->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Effect_Bullet(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Effect_Bullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Effect_Bullet);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_ONE);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_BULLET; nCnt++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//�A���t�@�u�����f�B���O��߂��ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_INVSRCALPHA);
}

//************************************************
//�G�t�F�N�g�̏���ݒ肷��֐�
//************************************************
void Setinfo_Effect_Bullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Bullet;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Bullet->Lock(0, 0, (void**)&pVtx_Effect_Bullet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_BULLET; nCnt++)
	{
		//�g���Ă��Ȃ���
		if (!g_aEffect_Bullet[nCnt].bUse)
		{
			g_aEffect_Bullet[nCnt].pos = pos;	//�ʒu����
			g_aEffect_Bullet[nCnt].move = move;	//�N�\�R�[�h��
			g_aEffect_Bullet[nCnt].col = col;	
			g_aEffect_Bullet[nCnt].fRadius = RADIUS_EFFECT_BULLET;	//�K���ɔ��a�𒲐�
			g_aEffect_Bullet[nCnt].nRemain = REMAIN_TIME_EFFECT_BULLET;	//�K���Ɏc�����Ԃ𒲐�
			g_aEffect_Bullet[nCnt].bUse = true;	//�g�p������o��

			break;
		}

		pVtx_Effect_Bullet += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Bullet->Unlock();
}