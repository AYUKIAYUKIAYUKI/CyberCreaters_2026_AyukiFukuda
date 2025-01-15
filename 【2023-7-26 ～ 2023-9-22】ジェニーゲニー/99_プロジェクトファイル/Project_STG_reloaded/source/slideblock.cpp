//************************************************
//
//�X���C�h�u���b�N[slideblock.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "player.h"
#include "slideblock.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_SlideBlock[AMOUNT_TEXTURE_BLOCK] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_SlideBlock = NULL;	//���_�o�b�t�@�̃|�C���^
SLIDEBLOCK g_aSlideBlock[AMOUNT_POLYGON_SLIDEBLOCK];	//�X���C�h�u���b�N�̊e���
double g_aFileData_SlideBlock[AMOUNT_POLYGON_SLIDEBLOCK][AMOUNT_POLYGON_SLIDEBLOCK] = {};	//�t�@�C������f�[�^���i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_SlideBlock(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_1_BLOCK,
		&g_pTexture_SlideBlock[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_2_BLOCK,
		&g_pTexture_SlideBlock[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_1_BLOCK,
		&g_pTexture_SlideBlock[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_2_BLOCK,
		&g_pTexture_SlideBlock[3]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_1_BLOCK,
		&g_pTexture_SlideBlock[4]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_2_BLOCK,
		&g_pTexture_SlideBlock[5]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SLIDEBLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_SlideBlock,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_SlideBlock->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SLIDEBLOCK; nCnt++)
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
		pVtx_Score[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Score[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Score[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Score[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐�
		pVtx_Score[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Score[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Score[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Score[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Score += AMOUNT_VTX;
	}

	//�X���C�h�u���b�N�e���̏�����
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SLIDEBLOCK; nCnt++)
	{
		g_aSlideBlock[nCnt].nStyle = BLOCKSTYLE_SHROT_1;
		g_aSlideBlock[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSlideBlock[nCnt].fHalfSpanX = 0.0f;
		g_aSlideBlock[nCnt].fHalfSpanY = 0.0f;
		g_aSlideBlock[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSlideBlock[nCnt].fStop = 0.0f;
		g_aSlideBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSlideBlock[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aSlideBlock[nCnt].fColChange = 0.0f;
		g_aSlideBlock[nCnt].bUse = false;
		g_aSlideBlock[nCnt].nCntSpawn = 0;
		g_aSlideBlock[nCnt].fLength = 0.0f;
		g_aSlideBlock[nCnt].fAngle = 0.0f;
	}

	//�t�@�C�����i�[�p��������
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_SLIDEBLOCK; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_BLOCK)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData_SlideBlock[nCnt1][nCnt2] = {};
	}

	//�u���b�N����ݒ肷��
	Setinfo_SlideBlock();

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_SlideBlock->Unlock();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_SlideBlock(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BLOCK; nCnt++)
	{
		if (g_pTexture_SlideBlock[nCnt] != NULL)
		{
			g_pTexture_SlideBlock[nCnt]->Release();
			g_pTexture_SlideBlock[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_SlideBlock != NULL)
	{
		g_pVtxBuff_SlideBlock->Release();
		g_pVtxBuff_SlideBlock = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_SlideBlock(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_SlideBlock;

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
	g_pVtxBuff_SlideBlock->Lock(0, 0, (void**)&pVtx_SlideBlock, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		if (g_aSlideBlock[nCnt].bUse == true)
		{
			//���Ԍo�߂œo��
			if (g_aSlideBlock[nCnt].nCntSpawn > 0)
			{
				g_aSlideBlock[nCnt].nCntSpawn--;
			}
			else
			{
				//�ړ�
				g_aSlideBlock[nCnt].pos.x += g_aSlideBlock[nCnt].move.x;
				//g_aSlideBlock[nCnt].pos.y += g_aSlideBlock[nCnt].move.y;
				
				//��~���C�����z����܂�
				if (g_aSlideBlock[nCnt].pos.y < g_aSlideBlock[nCnt].fStop ||
					g_aSlideBlock[nCnt].pos.y > g_aSlideBlock[nCnt].fStop)
				{
					g_aSlideBlock[nCnt].pos.y += g_aSlideBlock[nCnt].move.y;
				}
				//�z������F�ω�
				else
				{
					if (g_aSlideBlock[nCnt].fColChange < 1.0f)
					{
						g_aSlideBlock[nCnt].col.g += g_aSlideBlock[nCnt].fColChange;
						g_aSlideBlock[nCnt].col.b += g_aSlideBlock[nCnt].fColChange;
					}
				}

				//���]���肪�o�Ă���Ƃ�
				if (*pInversion == true &&
					g_aSlideBlock[nCnt].move.x <= 7.0f &&
					*pReInversion == false)
				{
					g_aSlideBlock[nCnt].move.x += 0.1f;
				}
				else if (*pInversion == true &&
					g_aSlideBlock[nCnt].move.x >= -9.9f &&
					*pReInversion == true)
				{
					g_aSlideBlock[nCnt].move.x -= 0.1f;
				}

				//�v���C���[�����G���ԊO�ł��ꓖ��������
				if (pPlayer->pos.x <= g_aSlideBlock[nCnt].pos.x + g_aSlideBlock[nCnt].fHalfSpanX - 30.0f + HALFSPAN_X_PLAYER - 40.0f &&
					pPlayer->pos.x >= g_aSlideBlock[nCnt].pos.x - g_aSlideBlock[nCnt].fHalfSpanX + 30.0f - HALFSPAN_X_PLAYER + 20.0f &&
					pPlayer->pos.y >= g_aSlideBlock[nCnt].pos.y - g_aSlideBlock[nCnt].fHalfSpanY + 30.0f - HALFSPAN_Y_PLAYER + 20.0f &&
					pPlayer->pos.y <= g_aSlideBlock[nCnt].pos.y + g_aSlideBlock[nCnt].fHalfSpanY - 30.0f + HALFSPAN_Y_PLAYER - 40.0f &&
					pPlayer->state == PLAYERSTATE_NORMAL)
				{
					//�q�b�g����
					Hit_Player(1);
				}

				//�㉺�֋��Ȃ��Ȃ镨��
				if (g_aSlideBlock[nCnt].pos.y < -500.0f ||
					g_aSlideBlock[nCnt].pos.y > 1500.0f)
				{
					//���ŏ���
					Disapper_SlideBlock(nCnt);
				}

				//�ړ��A��]�𔽉f
				pVtx_SlideBlock[0].pos.x = g_aSlideBlock[nCnt].pos.x + sinf(g_aSlideBlock[nCnt].rot.z - (D3DX_PI - g_aSlideBlock[nCnt].fAngle)) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[0].pos.y = g_aSlideBlock[nCnt].pos.y + cosf(g_aSlideBlock[nCnt].rot.z - (D3DX_PI - g_aSlideBlock[nCnt].fAngle)) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[1].pos.x = g_aSlideBlock[nCnt].pos.x + sinf(g_aSlideBlock[nCnt].rot.z + (D3DX_PI - g_aSlideBlock[nCnt].fAngle)) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[1].pos.y = g_aSlideBlock[nCnt].pos.y + cosf(g_aSlideBlock[nCnt].rot.z + (D3DX_PI - g_aSlideBlock[nCnt].fAngle)) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[2].pos.x = g_aSlideBlock[nCnt].pos.x + sinf(g_aSlideBlock[nCnt].rot.z - g_aSlideBlock[nCnt].fAngle) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[2].pos.y = g_aSlideBlock[nCnt].pos.y + cosf(g_aSlideBlock[nCnt].rot.z - g_aSlideBlock[nCnt].fAngle) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[3].pos.x = g_aSlideBlock[nCnt].pos.x + sinf(g_aSlideBlock[nCnt].rot.z + g_aSlideBlock[nCnt].fAngle) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[3].pos.y = g_aSlideBlock[nCnt].pos.y + cosf(g_aSlideBlock[nCnt].rot.z + g_aSlideBlock[nCnt].fAngle) * g_aSlideBlock[nCnt].fLength;

				//�F�ύX�̔��f
				pVtx_SlideBlock[0].col = g_aSlideBlock[nCnt].col;
				pVtx_SlideBlock[1].col = g_aSlideBlock[nCnt].col;
				pVtx_SlideBlock[2].col = g_aSlideBlock[nCnt].col;
				pVtx_SlideBlock[3].col = g_aSlideBlock[nCnt].col;
			}
		}

		//�|�C���^�����炷
		pVtx_SlideBlock += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_SlideBlock->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_SlideBlock(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_SlideBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		//�u���b�N���g�p����Ă���Ȃ�
		if (g_aSlideBlock[nCnt].bUse == true)
		{
			switch (g_aSlideBlock[nCnt].nStyle)
			{
			case 0:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_SlideBlock[0]);

				break;

			case 1:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_SlideBlock[1]);

				break;

			case 2:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_SlideBlock[2]);

				break;

			case 3:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_SlideBlock[3]);

				break;

			case 4:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_SlideBlock[4]);

				break;

			case 5:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_SlideBlock[5]);

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
void Setinfo_SlideBlock(void)
{
	//�f�[�^�𕪕ʂ���p
	int nLine = 0, nRow = 0;

	//�t�@�C���|�C���^��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(FILE_SET_SLIDEBLOCK, "r");

	//�f�[�^�̈�s�ڂɂ�������������΂�
	while (fgetc(pFile) != '\n');

	//�t�@�C�����J����
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_SlideBlock[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_SLIDEBLOCK)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_SlideBlock;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_SlideBlock->Lock(0, 0, (void**)&pVtx_SlideBlock, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		//�u���b�N�̎g�p���肪������
		if (g_aSlideBlock[nCnt].bUse == false)
		{
			g_aSlideBlock[nCnt].nStyle = (int)g_aFileData_SlideBlock[0][nCnt];
			g_aSlideBlock[nCnt].pos.x = (float)g_aFileData_SlideBlock[1][nCnt];
			g_aSlideBlock[nCnt].pos.y = (float)g_aFileData_SlideBlock[2][nCnt];
			g_aSlideBlock[nCnt].fHalfSpanX = (float)g_aFileData_SlideBlock[3][nCnt];
			g_aSlideBlock[nCnt].fHalfSpanY = (float)g_aFileData_SlideBlock[4][nCnt];
			g_aSlideBlock[nCnt].move.x = (float)g_aFileData_SlideBlock[5][nCnt];
			g_aSlideBlock[nCnt].move.y = (float)g_aFileData_SlideBlock[6][nCnt];
			g_aSlideBlock[nCnt].move.z = (float)g_aFileData_SlideBlock[7][nCnt];
			g_aSlideBlock[nCnt].fStop = (float)g_aFileData_SlideBlock[8][nCnt];
			g_aSlideBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSlideBlock[nCnt].col = D3DXCOLOR(1.0f, 0.25f, 0.25f, 1.0f);
			g_aSlideBlock[nCnt].fColChange = (float)g_aFileData_SlideBlock[9][nCnt];
			g_aSlideBlock[nCnt].bUse = true;
			g_aSlideBlock[nCnt].nCntSpawn = (int)g_aFileData_SlideBlock[10][nCnt];
			g_aSlideBlock[nCnt].fLength = (float)g_aFileData_SlideBlock[11][nCnt];
			g_aSlideBlock[nCnt].fAngle = (float)g_aFileData_SlideBlock[12][nCnt];
		}

		pVtx_SlideBlock += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_SlideBlock->Unlock();
}

//************************************************
//�X���C�h�u���b�N�̏��������n���֐�
//************************************************
SLIDEBLOCK* Getinfo_SlideBlock(void)
{
	return &g_aSlideBlock[0];
}

//************************************************
//�g�����I�����X���C�h�u���b�N�̏��ŏ����֐�
//************************************************
void Disapper_SlideBlock(int nCntSlideBlock)
{
	g_aSlideBlock[nCntSlideBlock].nStyle = BLOCKSTYLE_SHROT_1;
	g_aSlideBlock[nCntSlideBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aSlideBlock[nCntSlideBlock].fHalfSpanX = 0.0f;
	g_aSlideBlock[nCntSlideBlock].fHalfSpanY = 0.0f;
	g_aSlideBlock[nCntSlideBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aSlideBlock[nCntSlideBlock].fStop = 0.0f;
	g_aSlideBlock[nCntSlideBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aSlideBlock[nCntSlideBlock].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aSlideBlock[nCntSlideBlock].fColChange = 0.0f;
	g_aSlideBlock[nCntSlideBlock].bUse = false;
	g_aSlideBlock[nCntSlideBlock].nCntSpawn = 0;
	g_aSlideBlock[nCntSlideBlock].fLength = 0.0f;
	g_aSlideBlock[nCntSlideBlock].fAngle = 0.0f;
}