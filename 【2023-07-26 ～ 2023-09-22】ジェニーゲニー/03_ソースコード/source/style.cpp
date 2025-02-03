//************************************************
//
//�e�̃X�^�C���\������[style.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "player.h"
#include "style.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Style[AMOUNT_TEXTURE_STYLE] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Style = NULL;	//���_�o�b�t�@�̃|�C���^
int g_nChoosingBulletStyle_Style = 0;	//�I�����Ă���e�̎��
BULLETSTYLE_INDICATE g_aBlletStyle;	//�e�\���̍\����

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Style()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_COMET_BULLET,
		&g_pTexture_Style[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_REUNION_ODD_BULLET,
		&g_pTexture_Style[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_KING_BULLET,
		&g_pTexture_Style[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Style,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Style;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Style->Lock(0, 0, (void**)&pVtx_Style, 0);

	//���_���W�̏����ݒ�
	pVtx_Style[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Style[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Style[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Style[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Style[0].rhw = 1.0f;
	pVtx_Style[1].rhw = 1.0f;
	pVtx_Style[2].rhw = 1.0f;
	pVtx_Style[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Style[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Style[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Style[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Style[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Style[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Style[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Style[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Style[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���݂̒e�̎�ނ��f�t�H���g�ɐݒ�
	g_nChoosingBulletStyle_Style = 0;

	//�e�\���̍\���̂�������
	g_aBlletStyle.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aBlletStyle.fMoveZ = 0.0f;
	g_aBlletStyle.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aBlletStyle.style = BULLETSTYLE_COMET;
	g_aBlletStyle.fLength = 0.0f;
	g_aBlletStyle.fAngle = 0.0f;
	g_aBlletStyle.nPattern = 0;
	g_aBlletStyle.fTexX = 0.0f;
	g_aBlletStyle.fTexY = 0.0f;
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Style->Unlock();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Style(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_STYLE; nCnt++)
	{
		if (g_pTexture_Style[nCnt] != NULL)
		{
			g_pTexture_Style[nCnt]->Release();
			g_pTexture_Style[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Style != NULL)
	{
		g_pVtxBuff_Style->Release();
		g_pVtxBuff_Style = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Style(void)
{
	//���ݑI�����Ă���e�̎�ނ�������
	g_nChoosingBulletStyle_Style = *Getinfo_BulletStyle();

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Style;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Style->Lock(0, 0, (void**)&pVtx_Style, 0);

	switch (g_nChoosingBulletStyle_Style)
	{
	case BULLETSTYLE_COMET:

		//��]
		g_aBlletStyle.rot.z += g_aBlletStyle.fMoveZ;

		/*�f�o�b�O�p*/
		g_aBlletStyle.pos.x = 140.0f;
		g_aBlletStyle.pos.y = 935.0f;
		g_aBlletStyle.fMoveZ = 0.05f;
		g_aBlletStyle.fLength = sqrtf(SPAN_X_BULLET * SPAN_X_BULLET + SPAN_Y_BULLET * SPAN_Y_BULLET) * 0.5f;
		g_aBlletStyle.fAngle = atan2f(SPAN_X_BULLET, SPAN_Y_BULLET);

		//�Ō�ɒe�̈ړ��ʂɍ��킹�Ē��_���X�V
		pVtx_Style[0].pos.x = g_aBlletStyle.pos.x + sinf(g_aBlletStyle.rot.z - (D3DX_PI - g_aBlletStyle.fAngle)) * g_aBlletStyle.fLength;
		pVtx_Style[0].pos.y = g_aBlletStyle.pos.y + cosf(g_aBlletStyle.rot.z - (D3DX_PI - g_aBlletStyle.fAngle)) * g_aBlletStyle.fLength;
		pVtx_Style[1].pos.x = g_aBlletStyle.pos.x + sinf(g_aBlletStyle.rot.z + (D3DX_PI - g_aBlletStyle.fAngle)) * g_aBlletStyle.fLength;
		pVtx_Style[1].pos.y = g_aBlletStyle.pos.y + cosf(g_aBlletStyle.rot.z + (D3DX_PI - g_aBlletStyle.fAngle)) * g_aBlletStyle.fLength;
		pVtx_Style[2].pos.x = g_aBlletStyle.pos.x + sinf(g_aBlletStyle.rot.z - g_aBlletStyle.fAngle) * g_aBlletStyle.fLength;
		pVtx_Style[2].pos.y = g_aBlletStyle.pos.y + cosf(g_aBlletStyle.rot.z - g_aBlletStyle.fAngle) * g_aBlletStyle.fLength;
		pVtx_Style[3].pos.x = g_aBlletStyle.pos.x + sinf(g_aBlletStyle.rot.z + g_aBlletStyle.fAngle) * g_aBlletStyle.fLength;
		pVtx_Style[3].pos.y = g_aBlletStyle.pos.y + cosf(g_aBlletStyle.rot.z + g_aBlletStyle.fAngle) * g_aBlletStyle.fLength;

		//�e�N�X�`������肢���ƒ���
		pVtx_Style[0].tex = D3DXVECTOR2(0.0f + g_aBlletStyle.fTexX, 0.0f + g_aBlletStyle.fTexY);
		pVtx_Style[1].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET + g_aBlletStyle.fTexX, 0.0f + g_aBlletStyle.fTexY);
		pVtx_Style[2].tex = D3DXVECTOR2(0.0f + g_aBlletStyle.fTexX, PER_ONE_TEX_Y_COMET_BULLET + g_aBlletStyle.fTexY);
		pVtx_Style[3].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET + g_aBlletStyle.fTexX, PER_ONE_TEX_Y_COMET_BULLET + g_aBlletStyle.fTexY);

		//�e�N�X�`���ω��x��
		g_aBlletStyle.nPattern++;

		//�e�N�X�`�����ω�
		if (g_aBlletStyle.nPattern > CHEANGE_SPD_TEX_COMET_BULLET)
		{
			g_aBlletStyle.fTexX += PER_ONE_TEX_X_COMET_BULLET;

			if (g_aBlletStyle.fTexX >= 1.0f)
			{
				g_aBlletStyle.fTexX = 0.0f;

				g_aBlletStyle.fTexY += PER_ONE_TEX_Y_COMET_BULLET;

				if (g_aBlletStyle.fTexY >= 1.0f)
				{
					g_aBlletStyle.fTexY = 0.0f;
				}
			}

			g_aBlletStyle.nPattern = 0;
		}

		break;

	case BULLETSTYLE_REUNION:

		break;

	case BULLETSTYLE_KING:

		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Style->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Style(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Style, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	switch (g_nChoosingBulletStyle_Style)
	{
	case BULLETSTYLE_COMET:

		pDevice->SetTexture(0, g_pTexture_Style[0]);

		break;

	case BULLETSTYLE_REUNION:

		pDevice->SetTexture(0, g_pTexture_Style[1]);

		break;

	case BULLETSTYLE_KING:

		pDevice->SetTexture(0, g_pTexture_Style[2]);

		break;
	}

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}