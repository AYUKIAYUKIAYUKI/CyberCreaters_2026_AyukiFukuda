//************************************************
//
//���ނ珈��(�N�\�R�[�h����)[bush.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "bush.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Bush[AMOUNT_TEXTURE_BUSH] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Bush = NULL;	//���_�o�b�t�@�̃|�C���^
BUSH g_aBush[AMOUNT_POLYGON_BUSH];	//�O�i�|���S���p���\����
float g_fLength_Bush[2] = {};	//�Ίp�������i�[
float g_fAngle_Bush[2] = {};	//�p�x�����i�[
int g_nStartingSet_Bush = 0;	//�J��������ʓ��ɑ���u������

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Bush(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BUSH_1,
		&g_pTexture_Bush[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BUSH_2,
		&g_pTexture_Bush[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BUSH_3,
		&g_pTexture_Bush[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BUSH_4,
		&g_pTexture_Bush[3]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BUSH_5,
		&g_pTexture_Bush[4]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BUSH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Bush,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Bush;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bush->Lock(0, 0, (void**)&pVtx_Bush, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BUSH; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Bush[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bush[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bush[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bush[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Bush[0].rhw = 1.0f;
		pVtx_Bush[1].rhw = 1.0f;
		pVtx_Bush[2].rhw = 1.0f;
		pVtx_Bush[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Bush[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bush[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bush[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bush[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Bush[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Bush[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Bush[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Bush[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Bush += AMOUNT_VTX;
	}

	//���ނ珉����
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BUSH; nCnt++)
	{
		g_aBush[nCnt].nStyle = 0;
		g_aBush[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBush[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBush[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBush[nCnt].bUse = false;
		g_aBush[nCnt].nCntSpawn = 0;
		g_aBush[nCnt].fLength = 0.0f;
		g_aBush[nCnt].fAngle = 0.0f;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bush->Unlock();

	g_nStartingSet_Bush = 0;

	//�K�v�Ȓl�̌v�Z����x����
	SetSpan_Bush();

	//����Ɉ�x����ݒ肷��
	Setinfo_Vtx_Bush();

	////�ݒ肵���������ƂɈ�x�����W�J���Ă���
	//Update_Bush();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Bush(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BUSH; nCnt++)
	{
		if (g_pTexture_Bush[nCnt] != NULL)
		{
			g_pTexture_Bush[nCnt]->Release();
			g_pTexture_Bush[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Bush != NULL)
	{
		g_pVtxBuff_Bush->Release();
		g_pVtxBuff_Bush = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Bush(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Bush;

	//�^�C�}�[���̃|�C���^
	bool* pInversion;
	bool* pReInversion;

	//���]���̎擾
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bush->Lock(0, 0, (void**)&pVtx_Bush, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BUSH; nCnt++)
	{
		if (!g_aBush[nCnt].bUse)
		{
			if (g_aBush[nCnt].nCntSpawn > 0)
			{
				g_aBush[nCnt].nCntSpawn--;
			}
			else
			{
				g_aBush[nCnt].bUse = true;
			}
		}
		else
		{
			//�ړ�
			g_aBush[nCnt].pos.x += g_aBush[nCnt].move.x;
			g_aBush[nCnt].pos.y += g_aBush[nCnt].move.y;

			//���]���肪�o�Ă���Ƃ�
			if (*pInversion == true &&
				g_aBush[nCnt].move.x <= 8.0f &&
				*pReInversion == false)
			{
				g_aBush[nCnt].move.x += 0.1f;
			}
			else if (*pInversion == true &&
				g_aBush[nCnt].move.x >= -12.0f &&
				*pReInversion == true)
			{
				g_aBush[nCnt].move.x -= 0.1f;
			}

			if (g_aBush[nCnt].pos.x < -1000.0f ||
				g_aBush[nCnt].pos.x > 3000.0f)
			{
				Disappear_Bush(nCnt);
			}

			//�ړ��A��]�𔽉f
			pVtx_Bush[0].pos.x = g_aBush[nCnt].pos.x + sinf(g_aBush[nCnt].rot.z - (D3DX_PI - g_aBush[nCnt].fAngle)) * g_aBush[nCnt].fLength;
			pVtx_Bush[0].pos.y = g_aBush[nCnt].pos.y + cosf(g_aBush[nCnt].rot.z - (D3DX_PI - g_aBush[nCnt].fAngle)) * g_aBush[nCnt].fLength;
			pVtx_Bush[1].pos.x = g_aBush[nCnt].pos.x + sinf(g_aBush[nCnt].rot.z + (D3DX_PI - g_aBush[nCnt].fAngle)) * g_aBush[nCnt].fLength;
			pVtx_Bush[1].pos.y = g_aBush[nCnt].pos.y + cosf(g_aBush[nCnt].rot.z + (D3DX_PI - g_aBush[nCnt].fAngle)) * g_aBush[nCnt].fLength;
			pVtx_Bush[2].pos.x = g_aBush[nCnt].pos.x + sinf(g_aBush[nCnt].rot.z - g_aBush[nCnt].fAngle) * g_aBush[nCnt].fLength;
			pVtx_Bush[2].pos.y = g_aBush[nCnt].pos.y + cosf(g_aBush[nCnt].rot.z - g_aBush[nCnt].fAngle) * g_aBush[nCnt].fLength;
			pVtx_Bush[3].pos.x = g_aBush[nCnt].pos.x + sinf(g_aBush[nCnt].rot.z + g_aBush[nCnt].fAngle) * g_aBush[nCnt].fLength;
			pVtx_Bush[3].pos.y = g_aBush[nCnt].pos.y + cosf(g_aBush[nCnt].rot.z + g_aBush[nCnt].fAngle) * g_aBush[nCnt].fLength;
		}

		pVtx_Bush += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bush->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Bush(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Bush, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BUSH; nCnt++)
	{
		switch (g_aBush[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Bush[0]);

			break;

		case 1:

			pDevice->SetTexture(0, g_pTexture_Bush[1]);

			break;

		case 2:

			pDevice->SetTexture(0, g_pTexture_Bush[2]);

			break;

		case 3:

			pDevice->SetTexture(0, g_pTexture_Bush[3]);

			break;

		case 4:

			pDevice->SetTexture(0, g_pTexture_Bush[4]);

			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�K�v�Ȓl���v�Z����֐�
//***********************************************
void SetSpan_Bush(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			g_fLength_Bush[nCnt] = sqrtf((HALFSPAN_X_BUSH * HALFSPAN_X_BUSH) +
				(HALFSPAN_Y_BUSH * HALFSPAN_Y_BUSH)) * 0.5f;

			g_fAngle_Bush[nCnt] = atan2f(HALFSPAN_X_BUSH * 2.0f, HALFSPAN_X_BUSH * 2.0f);

			break;

		case 1:

			g_fLength_Bush[nCnt] = sqrtf((HALFSPAN_X_LONGBUSH * HALFSPAN_X_LONGBUSH) +
				(HALFSPAN_X_BUSH * HALFSPAN_X_BUSH)) * 0.5f;

			g_fAngle_Bush[nCnt] = atan2f(HALFSPAN_X_LONGBUSH * 2.0f, HALFSPAN_X_BUSH * 2.0f);

			break;
		}
	}
}

//************************************************
//�|���S������ݒ�֐�
//************************************************
void Setinfo_Vtx_Bush(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Bush;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bush->Lock(0, 0, (void**)&pVtx_Bush, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BUSH; nCnt++)
	{
		g_nStartingSet_Bush++;

		//�����_���Ɏ�ނ�ݒ�
		g_aBush[nCnt].nStyle = (int)rand() % 5;
		//g_aBush[nCnt].nStyle = 0;

		g_aBush[nCnt].move = D3DXVECTOR3(-6.0f, 0.0f, 0.0f);
		g_aBush[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBush[nCnt].bUse = false;

		if (g_nStartingSet_Bush >= 7)
		{
			g_aBush[nCnt].nCntSpawn = 60 * (nCnt - 7);
		}

		//int nRandom = (int)rand() % 2;

		//if (nRandom == 0)
		//{
		//	pVtx_Bush[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//	pVtx_Bush[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//	pVtx_Bush[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//	pVtx_Bush[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		//}
		////���]
		//else
		//{
		//	pVtx_Bush[0].tex = D3DXVECTOR2(1.0f, 0.0f);
		//	pVtx_Bush[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		//	pVtx_Bush[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		//	pVtx_Bush[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		//}

		if (g_nStartingSet_Bush < 7)
		{
			g_aBush[nCnt].nCntSpawn = 0;

			switch (g_aBush[nCnt].nStyle)
			{
			case 0:

				g_aBush[nCnt].pos = D3DXVECTOR3(2500.0f - (320.0f * (g_nStartingSet_Bush + 1)), 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[0];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

				break;

			case 1:

				g_aBush[nCnt].pos = D3DXVECTOR3(2500.0f - (320.0f * (g_nStartingSet_Bush + 1)), 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;

			case 2:

				g_aBush[nCnt].pos = D3DXVECTOR3(2500.0f - (320.0f * (g_nStartingSet_Bush + 1)), 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[0];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

				break;

			case 3:

				g_aBush[nCnt].pos = D3DXVECTOR3(2500.0f - (320.0f * (g_nStartingSet_Bush + 1)), 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;

			case 4:

				g_aBush[nCnt].pos = D3DXVECTOR3(2500.0f - (320.0f * (g_nStartingSet_Bush + 1)), 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;
			}
		}
		else
		{
			switch (g_aBush[nCnt].nStyle)
			{
			case 0:

				g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[0];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

				break;

			case 1:

				g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;

			case 2:

				g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[0];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

				break;

			case 3:

				g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;

			case 4:

				g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
				g_aBush[nCnt].fLength = g_fLength_Bush[1];
				g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

				break;
			}
		}

		pVtx_Bush += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bush->Unlock();
}

//************************************************
//�|���S���̏����Đݒ肷��֐�
//***********************************************
void Disappear_Bush(int nCnt)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Bush;

	//�^�C�}�[���̃|�C���^
	bool* pInversion;
	bool* pReInversion;

	//���]���̎擾
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bush->Lock(0, 0, (void**)&pVtx_Bush, 0);

	pVtx_Bush += AMOUNT_VTX * nCnt;

	//�����_���Ɏ�ނ��Č���
	g_aBush[nCnt].nStyle = (int)rand() % 5;

	g_aBush[nCnt].bUse = false;
	g_aBush[nCnt].nCntSpawn = 20;

	//int nRandom = (int)rand() % 2;

	//if (nRandom == 0)
	//{
	//	pVtx_Bush[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx_Bush[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx_Bush[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx_Bush[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//}
	////���]
	//else
	//{
	//	pVtx_Bush[0].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx_Bush[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx_Bush[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	//	pVtx_Bush[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	//}

	if (*pInversion == false || *pReInversion == true)
	{
		switch (g_aBush[nCnt].nStyle)
		{
		case 0:

			g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[0];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

			break;

		case 1:

			g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;

		case 2:

			g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[0];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

			break;

		case 3:

			g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;

		case 4:

			g_aBush[nCnt].pos = D3DXVECTOR3(2200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;
		}
	}
	else
	{
		switch (g_aBush[nCnt].nStyle)
		{
		case 0:

			g_aBush[nCnt].pos = D3DXVECTOR3(-200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[0];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

			break;

		case 1:

			g_aBush[nCnt].pos = D3DXVECTOR3(-200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;

		case 2:

			g_aBush[nCnt].pos = D3DXVECTOR3(-200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[0];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[0];

			break;

		case 3:

			g_aBush[nCnt].pos = D3DXVECTOR3(-200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;

		case 4:

			g_aBush[nCnt].pos = D3DXVECTOR3(-200.0f, 1140.0f, 0.0f);
			g_aBush[nCnt].fLength = g_fLength_Bush[1];
			g_aBush[nCnt].fAngle = g_fAngle_Bush[1];

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bush->Unlock();
}