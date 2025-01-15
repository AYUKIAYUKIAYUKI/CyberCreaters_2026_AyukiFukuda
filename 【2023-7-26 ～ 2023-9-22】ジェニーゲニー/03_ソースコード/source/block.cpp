//************************************************
//
//�u���b�N[block.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "block.h"
#include "player.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Block[AMOUNT_TEXTURE_BLOCK] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Block = NULL;	//���_�o�b�t�@�̃|�C���^
BLOCK g_aBlock[AMOUNT_POLYGON_BLOCK];	//�u���b�N�̊e���
double g_aFileData_Block[AMOUNT_POLYGON_BLOCK][AMOUNT_POLYGON_BLOCK] = {};	//�t�@�C������f�[�^���i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Block(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_1_BLOCK,
		&g_pTexture_Block[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_2_BLOCK,
		&g_pTexture_Block[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_1_BLOCK,
		&g_pTexture_Block[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_2_BLOCK,
		&g_pTexture_Block[3]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_1_BLOCK,
		&g_pTexture_Block[4]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_2_BLOCK,
		&g_pTexture_Block[5]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BLOCK, 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Block,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Block->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx_Score[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx_Score[0].rhw = 1.0f;
		pVtx_Score[1].rhw = 1.0f;
		pVtx_Score[2].rhw = 1.0f;
		pVtx_Score[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx_Score[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐�
		pVtx_Score[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Score[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Score[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Score[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Score += AMOUNT_VTX;
	}

	//�u���b�N�e���̏�����
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		g_aBlock[nCnt].nStyle = BLOCKSTYLE_SHROT_1;
		g_aBlock[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCnt].fHalfSpanX = 0.0f;
		g_aBlock[nCnt].fHalfSpanY = 0.0f;
		g_aBlock[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCnt].bUse = false;
		g_aBlock[nCnt].nCntSpawn = 0;
		g_aBlock[nCnt].fLength = 0.0f;
		g_aBlock[nCnt].fAngle = 0.0f;
	}

	//�t�@�C�����i�[�p��������
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_BLOCK; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_BLOCK)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData_Block[nCnt1][nCnt2] = {};
	}

	//�u���b�N����ݒ肷��
	Setinfo_Block();

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Block->Unlock();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Block(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BLOCK; nCnt++)
	{
		if (g_pTexture_Block[nCnt] != NULL)
		{
			g_pTexture_Block[nCnt]->Release();
			g_pTexture_Block[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Block != NULL)
	{
		g_pVtxBuff_Block->Release();
		g_pVtxBuff_Block = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Block(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Block;

	//�v���C���[���ւ̃|�C���^
	PLAYER* pPlayer;

	//�^�C�}�[���̃|�C���^
	bool* pInversion;
	bool* pReInversion;

	//�v���C���[���̎擾
	pPlayer = Getinfo_Player();	//�v���C���[���n�̐擪�A�h���X����������

	//���]���̎擾
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Block->Lock(0, 0, (void**)&pVtx_Block, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		if (g_aBlock[nCnt].bUse == true)
		{
			//���Ԍo�߂œo��
			if (g_aBlock[nCnt].nCntSpawn > 0)
			{
				g_aBlock[nCnt].nCntSpawn--;
			}
			else
			{
				//�ړ�
				g_aBlock[nCnt].pos.x += g_aBlock[nCnt].move.x;
				g_aBlock[nCnt].pos.y += g_aBlock[nCnt].move.y;

				//���]���肪�o�Ă���Ƃ�
				if (*pInversion == true &&
					g_aBlock[nCnt].move.x <= 7.0f &&
					*pReInversion == false)
				{
					g_aBlock[nCnt].move.x += 0.1f;
				}
				else if (*pInversion == true &&
					g_aBlock[nCnt].move.x >= -10.0f &&
					*pReInversion == true)
				{
					g_aBlock[nCnt].move.x -= 0.1f;
				}

				//�v���C���[�����G���ԊO�ł��ꓖ��������
				if (pPlayer->pos.x <= g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fHalfSpanX - 30.0f + HALFSPAN_X_PLAYER - 40.0f &&
					pPlayer->pos.x >= g_aBlock[nCnt].pos.x - g_aBlock[nCnt].fHalfSpanX + 30.0f - HALFSPAN_X_PLAYER + 20.0f &&
					pPlayer->pos.y >= g_aBlock[nCnt].pos.y - g_aBlock[nCnt].fHalfSpanY + 30.0f - HALFSPAN_Y_PLAYER + 20.0f &&
					pPlayer->pos.y <= g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHalfSpanY - 30.0f + HALFSPAN_Y_PLAYER - 40.0f &&
					pPlayer->state == PLAYERSTATE_NORMAL)
				{
					//�q�b�g����
					Hit_Player(1);
				}

				//�ړ��A��]�𔽉f
				pVtx_Block[0].pos.x = g_aBlock[nCnt].pos.x + sinf(g_aBlock[nCnt].rot.z - (D3DX_PI - g_aBlock[nCnt].fAngle)) * g_aBlock[nCnt].fLength;
				pVtx_Block[0].pos.y = g_aBlock[nCnt].pos.y + cosf(g_aBlock[nCnt].rot.z - (D3DX_PI - g_aBlock[nCnt].fAngle)) * g_aBlock[nCnt].fLength;
				pVtx_Block[1].pos.x = g_aBlock[nCnt].pos.x + sinf(g_aBlock[nCnt].rot.z + (D3DX_PI - g_aBlock[nCnt].fAngle)) * g_aBlock[nCnt].fLength;
				pVtx_Block[1].pos.y = g_aBlock[nCnt].pos.y + cosf(g_aBlock[nCnt].rot.z + (D3DX_PI - g_aBlock[nCnt].fAngle)) * g_aBlock[nCnt].fLength;
				pVtx_Block[2].pos.x = g_aBlock[nCnt].pos.x + sinf(g_aBlock[nCnt].rot.z - g_aBlock[nCnt].fAngle) * g_aBlock[nCnt].fLength;
				pVtx_Block[2].pos.y = g_aBlock[nCnt].pos.y + cosf(g_aBlock[nCnt].rot.z - g_aBlock[nCnt].fAngle) * g_aBlock[nCnt].fLength;
				pVtx_Block[3].pos.x = g_aBlock[nCnt].pos.x + sinf(g_aBlock[nCnt].rot.z + g_aBlock[nCnt].fAngle) * g_aBlock[nCnt].fLength;
				pVtx_Block[3].pos.y = g_aBlock[nCnt].pos.y + cosf(g_aBlock[nCnt].rot.z + g_aBlock[nCnt].fAngle) * g_aBlock[nCnt].fLength;
			}
		}
	
		//�|�C���^�����炷
		pVtx_Block += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Block->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Block(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Block, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		//�u���b�N���g�p����Ă���Ȃ�
		if (g_aBlock[nCnt].bUse == true)
		{
			switch (g_aBlock[nCnt].nStyle)
			{
			case 0:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_Block[0]);

				break;

			case 1:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_Block[1]);

				break;

			case 2:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_Block[2]);

				break;

			case 3:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_Block[3]);

				break;

			case 4:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_Block[4]);

				break;

			case 5:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_Block[5]);

				break;
			}

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}
}

//************************************************
//�u���b�N�ʒu�ݒ菈���֐�
//************************************************
void Setinfo_Block(void)
{
	//�f�[�^�𕪕ʂ���p
	int nLine = 0, nRow = 0;

	//�t�@�C���|�C���^��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(FILE_SET_BLOCK, "r");

	//�f�[�^�̈�s�ڂɂ�������������΂�
	while (fgetc(pFile) != '\n');

	//�t�@�C�����J����
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_Block[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_BLOCK)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Block;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Block->Lock(0, 0, (void**)&pVtx_Block, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		//�u���b�N�̎g�p���肪������
		if (g_aBlock[nCnt].bUse == false)
		{
			g_aBlock[nCnt].nStyle = (int)g_aFileData_Block[0][nCnt];
			g_aBlock[nCnt].pos.x = (float)g_aFileData_Block[1][nCnt];
			g_aBlock[nCnt].pos.y = (float)g_aFileData_Block[2][nCnt];
			g_aBlock[nCnt].fHalfSpanX = (float)g_aFileData_Block[3][nCnt];
			g_aBlock[nCnt].fHalfSpanY = (float)g_aFileData_Block[4][nCnt];
			g_aBlock[nCnt].move.x = (float)g_aFileData_Block[5][nCnt];
			g_aBlock[nCnt].move.y = (float)g_aFileData_Block[6][nCnt];
			g_aBlock[nCnt].move.z = (float)g_aFileData_Block[7][nCnt];
			g_aBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBlock[nCnt].bUse = true;
			g_aBlock[nCnt].nCntSpawn = (int)g_aFileData_Block[8][nCnt];
			g_aBlock[nCnt].fLength = (float)g_aFileData_Block[9][nCnt];
			g_aBlock[nCnt].fAngle = (float)g_aFileData_Block[10][nCnt];
			//float uno = g_aFileData_Block[10][nCnt];
			//g_aBlock[nCnt].fAngle = atan2((g_aBlock[nCnt].fHalfSpanX * 2), (g_aBlock[nCnt].fHalfSpanY * 2));
		}

		pVtx_Block += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Block->Unlock();
}

//************************************************
//�u���b�N�̏��������n���֐�
//************************************************
BLOCK* Getinfo_Block(void)
{
	return &g_aBlock[0];
}