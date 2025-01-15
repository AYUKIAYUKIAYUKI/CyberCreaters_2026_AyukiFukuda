//************************************************
//
//�t���ς���������[leaves.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "block.h"
#include "leaves.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Leaves[AMOUNT_TEXTURE_LEAVES] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Leaves = NULL;	//���_�o�b�t�@�̃|�C���^
LEAVES g_aLeaves[AMOUNT_POLYGON_LEAVES];	//�t���ύ\���̂��i�[
float g_fLength_Leaves[2] = {};	//�t���ς̑Ίp�������i�[
float g_fAngle_Leaves[2] = {};	//�t���ς̊p�x�����i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Leaves(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LEAF_1,
		&g_pTexture_Leaves[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LEAF_2,
		&g_pTexture_Leaves[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LEAF_3,
		&g_pTexture_Leaves[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LEAF_4,
		&g_pTexture_Leaves[3]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LEAF_5,
		&g_pTexture_Leaves[4]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_LEAVES,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Leaves,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Leaves;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Leaves->Lock(0, 0, (void**)&pVtx_Leaves, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LEAVES; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Leaves[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Leaves[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Leaves[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Leaves[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Leaves[0].rhw = 1.0f;
		pVtx_Leaves[1].rhw = 1.0f;
		pVtx_Leaves[2].rhw = 1.0f;
		pVtx_Leaves[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Leaves[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Leaves[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Leaves[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Leaves[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Leaves[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Leaves[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Leaves[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Leaves[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Leaves += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Leaves->Unlock();

	//�t���ύ\���̂̏���������
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LEAVES; nCnt++)
	{
		g_aLeaves[nCnt].nStyle = 0;
		g_aLeaves[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaves[nCnt].fHalfSpanX = 0.0f;
		g_aLeaves[nCnt].fHalfSpanY = 0.0f;
		g_aLeaves[nCnt].nRute = 0;
		g_aLeaves[nCnt].nKeepTime = 0;
		g_aLeaves[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaves[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaves[nCnt].bUse = false;
		g_aLeaves[nCnt].nCntSpawn = 0;
		g_aLeaves[nCnt].fLength = 0.0f;
		g_aLeaves[nCnt].fAngle = 0.0f;
	}

	//�t���ςɕK�v�Ȓl�̌v�Z����x����
	SetSpan_Leaves();

	//���炩���ߖ��񃉃��_���ɏo�Ă���t���ς̏������߂�
	Setinfo_Leaves();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Leaves(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_LEAVES; nCnt++)
	{
		if (g_pTexture_Leaves[nCnt] != NULL)
		{
			g_pTexture_Leaves[nCnt]->Release();
			g_pTexture_Leaves[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Leaves != NULL)
	{
		g_pVtxBuff_Leaves->Release();
		g_pVtxBuff_Leaves = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Leaves(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Leaves;

	//�u���b�N���p�|�C���^
	BLOCK* pBlock;

	//�^�C�}�[���̃|�C���^
	bool* pInversion;
	bool* pReInversion;

	//�u���b�N�����擾
	pBlock = Getinfo_Block();

	//���]���̎擾
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Leaves->Lock(0, 0, (void**)&pVtx_Leaves, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LEAVES; nCnt++)
	{
		if (!g_aLeaves[nCnt].bUse)
		{
			if (g_aLeaves[nCnt].nCntSpawn > 0)
			{
				g_aLeaves[nCnt].nCntSpawn--;
			}
			else
			{
				g_aLeaves[nCnt].bUse = true;
			}
		}
		else
		{
			//��]�c?
			g_aLeaves[nCnt].rot.z += g_aLeaves[nCnt].move.z;

			//�ړ�����
			switch(g_aLeaves[nCnt].nRute)
			{
			case 0:

				g_aLeaves[nCnt].nKeepTime++;

				if (g_aLeaves[nCnt].nKeepTime >= 100)
				{
					g_aLeaves[nCnt].nKeepTime = 0;
				}

				g_aLeaves[nCnt].nKeepTime < 50 ?
					g_aLeaves[nCnt].move.x += 0.2f :
					g_aLeaves[nCnt].move.x -= 0.2f;

				break;

			case 1:

				g_aLeaves[nCnt].nKeepTime++;

				if (g_aLeaves[nCnt].nKeepTime >= 70)
				{
					g_aLeaves[nCnt].nKeepTime = 0;
				}

				g_aLeaves[nCnt].nKeepTime < 35 ?
					g_aLeaves[nCnt].move.x += 0.3f :
					g_aLeaves[nCnt].move.x -= 0.2f;

				g_aLeaves[nCnt].pos.y += g_aLeaves[nCnt].move.y * 0.5f;

				break;

			case 2:

				g_aLeaves[nCnt].nKeepTime++;

				if (g_aLeaves[nCnt].nKeepTime >= 6)
				{
					g_aLeaves[nCnt].nKeepTime = 0;
				}

				g_aLeaves[nCnt].nKeepTime < 3 ?
					g_aLeaves[nCnt].move.x += 0.2f :
					g_aLeaves[nCnt].move.x -= 0.0f;

				break;
			}

			//�ړ�
			if (*pInversion == false || *pReInversion == true)
			{
				g_aLeaves[nCnt].pos.x -= g_aLeaves[nCnt].move.x;

				if (*pReInversion == true)
				{
					g_aLeaves[nCnt].pos.x -= g_aLeaves[nCnt].move.x;
				}
			}
			else
			{
				g_aLeaves[nCnt].pos.x += g_aLeaves[nCnt].move.x;
			}

			g_aLeaves[nCnt].pos.y += g_aLeaves[nCnt].move.y;

			if (g_aLeaves[nCnt].pos.y > 1180)
			{
				Disappear_Leaves(nCnt);
			}

			//�ړ��A��]�𔽉f
			pVtx_Leaves[0].pos.x = g_aLeaves[nCnt].pos.x + sinf(g_aLeaves[nCnt].rot.z - (D3DX_PI - g_aLeaves[nCnt].fAngle)) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[0].pos.y = g_aLeaves[nCnt].pos.y + cosf(g_aLeaves[nCnt].rot.z - (D3DX_PI - g_aLeaves[nCnt].fAngle)) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[1].pos.x = g_aLeaves[nCnt].pos.x + sinf(g_aLeaves[nCnt].rot.z + (D3DX_PI - g_aLeaves[nCnt].fAngle)) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[1].pos.y = g_aLeaves[nCnt].pos.y + cosf(g_aLeaves[nCnt].rot.z + (D3DX_PI - g_aLeaves[nCnt].fAngle)) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[2].pos.x = g_aLeaves[nCnt].pos.x + sinf(g_aLeaves[nCnt].rot.z - g_aLeaves[nCnt].fAngle) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[2].pos.y = g_aLeaves[nCnt].pos.y + cosf(g_aLeaves[nCnt].rot.z - g_aLeaves[nCnt].fAngle) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[3].pos.x = g_aLeaves[nCnt].pos.x + sinf(g_aLeaves[nCnt].rot.z + g_aLeaves[nCnt].fAngle) * g_aLeaves[nCnt].fLength;
			pVtx_Leaves[3].pos.y = g_aLeaves[nCnt].pos.y + cosf(g_aLeaves[nCnt].rot.z + g_aLeaves[nCnt].fAngle) * g_aLeaves[nCnt].fLength;
		}

		pVtx_Leaves += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Leaves->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Leaves(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Leaves, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LEAVES; nCnt++)
	{
		switch (g_aLeaves[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Leaves[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Leaves[1]);

			break;

		case 2:

			pDevice->SetTexture(0, g_pTexture_Leaves[2]);

			break;

		case 3:

			pDevice->SetTexture(0, g_pTexture_Leaves[3]);

			break;

		case 4:

			pDevice->SetTexture(0, g_pTexture_Leaves[4]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�t���ςɕK�v�Ȓl����x�̂݌v�Z����֐�
//***********************************************
void SetSpan_Leaves(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			g_fLength_Leaves[nCnt] = sqrtf((HALFSPAN_X_TINYLEAF_1 * HALFSPAN_X_TINYLEAF_1) +
				(HALFSPAN_Y_LEAF_1 * HALFSPAN_Y_LEAF_1)) * 0.5f;

			g_fAngle_Leaves[nCnt] = atan2f((HALFSPAN_X_TINYLEAF_1 * 2), (HALFSPAN_Y_LEAF_1 * 2));

			break;

		case 1:

			g_fLength_Leaves[nCnt] = sqrtf((HALFSPAN_X_LEAF_1 * HALFSPAN_X_LEAF_1) +
				(HALFSPAN_Y_LEAF_1 * HALFSPAN_Y_LEAF_1)) * 0.5f;

			g_fAngle_Leaves[nCnt] = atan2f((HALFSPAN_X_LEAF_1 * 2.0f), (HALFSPAN_Y_LEAF_1 * 2.0f));

			break;
		}
	}
}

//************************************************
//�t���ς̏���ݒ肷��֐�
//***********************************************
void Setinfo_Leaves(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_LEAVES; nCnt++)
	{
		//�����_���ɗt�̎�ނ����߂�
		g_aLeaves[nCnt].nStyle = (int)rand() % 5;

		//�����_���ɏo�Ă���ʒu�����߂�
		g_aLeaves[nCnt].pos = D3DXVECTOR3(400.0f + (float)(90 * (rand() % 30)), -100.0f, 0.0f);

		g_aLeaves[nCnt].fHalfSpanY = HALFSPAN_Y_LEAF_1;

		//�����_���ɗ����������߂�
		g_aLeaves[nCnt].nRute = (int)rand() % 3;
		//g_aLeaves[nCnt].nRute = 1;

		g_aLeaves[nCnt].nKeepTime = 0;
		g_aLeaves[nCnt].move.x = 0.0f;
		g_aLeaves[nCnt].move.y = 6.0f;

		float fRandomSPD = 0.02f;

		//��]�̌����������_���Ɍ��߂�
		int nRondom = (int)rand() % 2;

		nRondom == 0 ?
			0 :
			fRandomSPD *= -1.0f;

		g_aLeaves[nCnt].move.z = fRandomSPD;
		g_aLeaves[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aLeaves[nCnt].bUse = false;

		//�o�Ă���܂łɂ����鎞�Ԃ����߂�
		g_aLeaves[nCnt].nCntSpawn = 30 + (30 * nCnt);

		if (nCnt % 2 == 1)
		{
			g_aLeaves[nCnt].nCntSpawn -= 20;
		}

		if (g_aLeaves[nCnt].nStyle == 0 || g_aLeaves[nCnt].nStyle == 3)
		{
			g_aLeaves[nCnt].fHalfSpanX = HALFSPAN_X_TINYLEAF_1;
			g_aLeaves[nCnt].fLength = g_fLength_Leaves[0];
			g_aLeaves[nCnt].fAngle = g_fAngle_Leaves[0];
		}
		else
		{
			g_aLeaves[nCnt].fHalfSpanX = HALFSPAN_X_LEAF_1;
			g_aLeaves[nCnt].fLength = g_fLength_Leaves[1];
			g_aLeaves[nCnt].fAngle = g_fAngle_Leaves[1];
		}
	}
}

//************************************************
//�t���ς̏����Đݒ肷��֐�
//***********************************************
void Disappear_Leaves(int nCnt)
{
	//�^�C�}�[���̃|�C���^
	bool* pInversion;
	bool* pReInversion;

	//���]���̎擾
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//�����_���ɗt�̎�ނ��Č���
	g_aLeaves[nCnt].nStyle = (int)rand() % 5;

	//�����_���ɏo�Ă���ʒu���Č���
	if (*pInversion == false || *pReInversion == true)
	{
		g_aLeaves[nCnt].pos = D3DXVECTOR3(400.0f + (float)(90 * (rand() % 30)), -100.0f, 0.0f);
	}
	else
	{
		g_aLeaves[nCnt].pos = D3DXVECTOR3(-600.0f + (float)(90 * (rand() % 30)), -100.0f, 0.0f);
	}

	//�����_���ɗ����������߂�
	g_aLeaves[nCnt].nRute = (int)rand() % 3;
	//g_aLeaves[nCnt].nRute = 1;

	g_aLeaves[nCnt].nKeepTime = 0;
	g_aLeaves[nCnt].move.x = 0.0f;
	g_aLeaves[nCnt].move.y = 6.0f;

	float fRandomSPD = 0.02f;

	//��]�̌����������_���ɍČ���
	int nRondom = (int)rand() % 2;

	nRondom == 0 ?
		0 :
		fRandomSPD *= -1.0f;

	g_aLeaves[nCnt].move.z = fRandomSPD;

	if (g_aLeaves[nCnt].nStyle == 0 || g_aLeaves[nCnt].nStyle == 3)
	{
		g_aLeaves[nCnt].fHalfSpanX = HALFSPAN_X_TINYLEAF_1;
		g_aLeaves[nCnt].fLength = g_fLength_Leaves[0];
		g_aLeaves[nCnt].fAngle = g_fAngle_Leaves[0];
	}
	else
	{
		g_aLeaves[nCnt].fHalfSpanX = HALFSPAN_X_LEAF_1;
		g_aLeaves[nCnt].fLength = g_fLength_Leaves[1];
		g_aLeaves[nCnt].fAngle = g_fAngle_Leaves[1];
	}
}