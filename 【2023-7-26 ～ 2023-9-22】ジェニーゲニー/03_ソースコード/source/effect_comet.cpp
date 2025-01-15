//************************************************
//
//�R���b�g�G�t�F�N�g����[effect_comet.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "effect_comet.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Effect_Comet = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Effect_Comet = NULL;	//���_�o�b�t�@�̃|�C���^
COMET_EFFECT g_aEffect_Comet[AMOUNT_POLYGON_EFFECT_COMET];	//�R���b�g�G�t�F�N�g���i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Effect_Comet(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_EFFECT_COMET,
		&g_pTexture_Effect_Comet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_EFFECT_COMET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Effect_Comet,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Comet;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Comet->Lock(0, 0, (void**)&pVtx_Effect_Comet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_COMET; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Effect_Comet[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Comet[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Comet[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Comet[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Effect_Comet[0].rhw = 1.0f;
		pVtx_Effect_Comet[1].rhw = 1.0f;
		pVtx_Effect_Comet[2].rhw = 1.0f;
		pVtx_Effect_Comet[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Effect_Comet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Comet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Comet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Comet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Effect_Comet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Effect_Comet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Effect_Comet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Effect_Comet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Effect_Comet += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Comet->Unlock();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_COMET; nCnt++)
	{
		g_aEffect_Comet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect_Comet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect_Comet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect_Comet[nCnt].bUse = false;
		g_aEffect_Comet[nCnt].fLength = 0.0f;
		g_aEffect_Comet[nCnt].fAngle = 0.0f;
		g_aEffect_Comet[nCnt].nPattern = 0;
		g_aEffect_Comet[nCnt].fTexX = 0.0f;
		g_aEffect_Comet[nCnt].fTexY = 0.0f;
	}
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Effect_Comet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Effect_Comet != NULL)
	{
		g_pTexture_Effect_Comet->Release();
		g_pTexture_Effect_Comet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Effect_Comet != NULL)
	{
		g_pVtxBuff_Effect_Comet->Release();
		g_pVtxBuff_Effect_Comet = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Effect_Comet(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Comet;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Comet->Lock(0, 0, (void**)&pVtx_Effect_Comet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_COMET; nCnt++)
	{
		if (g_aEffect_Comet[nCnt].bUse)
		{
			//��]
			g_aEffect_Comet[nCnt].rot.z += ROTATE_SPD_EFFECT_COMET;

			//(�G��ǂȂǂɓ��������ꍇ�ړ��ʂ𓯊�)
			g_aEffect_Comet[nCnt].pos.x += g_aEffect_Comet[nCnt].move.x;

			pVtx_Effect_Comet[0].tex = D3DXVECTOR2(0.0f + g_aEffect_Comet[nCnt].fTexX, 0.0f + g_aEffect_Comet[nCnt].fTexY);
			pVtx_Effect_Comet[1].tex = D3DXVECTOR2(0.2f + g_aEffect_Comet[nCnt].fTexX, 0.0f + g_aEffect_Comet[nCnt].fTexY);
			pVtx_Effect_Comet[2].tex = D3DXVECTOR2(0.0f + g_aEffect_Comet[nCnt].fTexX, 0.5f + g_aEffect_Comet[nCnt].fTexY);
			pVtx_Effect_Comet[3].tex = D3DXVECTOR2(0.2f + g_aEffect_Comet[nCnt].fTexX, 0.5f + g_aEffect_Comet[nCnt].fTexY);

			//�e�N�X�`�����ω�
			g_aEffect_Comet[nCnt].nPattern++;

			if (g_aEffect_Comet[nCnt].nPattern > 1)
			{
				g_aEffect_Comet[nCnt].fTexX += 0.2f;

				if (g_aEffect_Comet[nCnt].fTexX >= 1.0f)
				{
					g_aEffect_Comet[nCnt].fTexX = 0.0f;

					g_aEffect_Comet[nCnt].fTexY += 0.5f;

					if (g_aEffect_Comet[nCnt].fTexY >= 1.0f)
					{
						//����
						g_aEffect_Comet[nCnt].pos = D3DXVECTOR3(-1000.0f, -1000.0f, 0.0f);

						g_aEffect_Comet[nCnt].bUse = false;
					}
				}

				g_aEffect_Comet[nCnt].nPattern = 0;
			}

			//�Ō�ɔ��f
			pVtx_Effect_Comet[0].pos.x = g_aEffect_Comet[nCnt].pos.x + sinf(g_aEffect_Comet[nCnt].rot.z - (D3DX_PI - g_aEffect_Comet[nCnt].fAngle)) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[0].pos.y = g_aEffect_Comet[nCnt].pos.y + cosf(g_aEffect_Comet[nCnt].rot.z - (D3DX_PI - g_aEffect_Comet[nCnt].fAngle)) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[1].pos.x = g_aEffect_Comet[nCnt].pos.x + sinf(g_aEffect_Comet[nCnt].rot.z + (D3DX_PI - g_aEffect_Comet[nCnt].fAngle)) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[1].pos.y = g_aEffect_Comet[nCnt].pos.y + cosf(g_aEffect_Comet[nCnt].rot.z + (D3DX_PI - g_aEffect_Comet[nCnt].fAngle)) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[2].pos.x = g_aEffect_Comet[nCnt].pos.x + sinf(g_aEffect_Comet[nCnt].rot.z - g_aEffect_Comet[nCnt].fAngle) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[2].pos.y = g_aEffect_Comet[nCnt].pos.y + cosf(g_aEffect_Comet[nCnt].rot.z - g_aEffect_Comet[nCnt].fAngle) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[3].pos.x = g_aEffect_Comet[nCnt].pos.x + sinf(g_aEffect_Comet[nCnt].rot.z + g_aEffect_Comet[nCnt].fAngle) * g_aEffect_Comet[nCnt].fLength;
			pVtx_Effect_Comet[3].pos.y = g_aEffect_Comet[nCnt].pos.y + cosf(g_aEffect_Comet[nCnt].rot.z + g_aEffect_Comet[nCnt].fAngle) * g_aEffect_Comet[nCnt].fLength;
		}

		pVtx_Effect_Comet += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Comet->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Effect_Comet(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Effect_Comet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Effect_Comet);

	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP,
		D3DBLENDOP_ADD);

	pDevice->SetRenderState(D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA);

	pDevice->SetRenderState(D3DRS_DESTBLEND,
		D3DBLEND_ONE);

	//�|���S���̕`��
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_COMET; nCnt++)
	{
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
//���_��W�J����֐�
//************************************************
void SetPos_Vtx_Effect_Comet(D3DXVECTOR3 pos, float moveX)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Comet;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Comet->Lock(0, 0, (void**)&pVtx_Effect_Comet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_COMET; nCnt++)
	{
		if (!g_aEffect_Comet[nCnt].bUse)
		{
			g_aEffect_Comet[nCnt].pos = pos;
			g_aEffect_Comet[nCnt].move.x = moveX;
			g_aEffect_Comet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEffect_Comet[nCnt].bUse = true;

			g_aEffect_Comet[nCnt].fLength = sqrtf(SPAN_X_EFFECT_COMET * SPAN_X_EFFECT_COMET +
				SPAN_Y_EFFECT_COMET * SPAN_Y_EFFECT_COMET) * 0.5f;

			g_aEffect_Comet[nCnt].fAngle = atan2f(SPAN_X_EFFECT_COMET, SPAN_Y_EFFECT_COMET);

			g_aEffect_Comet[nCnt].nPattern = 0;
			g_aEffect_Comet[nCnt].fTexX = 0.0f;
			g_aEffect_Comet[nCnt].fTexY = 0.0f;

			break;
		}

		pVtx_Effect_Comet += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Comet->Unlock();
}