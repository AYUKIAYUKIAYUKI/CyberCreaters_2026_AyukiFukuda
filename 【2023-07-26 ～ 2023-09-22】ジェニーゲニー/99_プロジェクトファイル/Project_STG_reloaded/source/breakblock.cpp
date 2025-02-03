//************************************************
//
//�u���C�N�u���b�N[breakblock.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "sound.h"
#include "breakblock.h"
#include "particle.h"
#include "particle_block.h"
#include "player.h"
#include "timer.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_BreakBlock[AMOUNT_TEXTURE_BLOCK] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_BreakBlock = NULL;	//���_�o�b�t�@�̃|�C���^
BREAKBLOCK g_aBreakBlock[AMOUNT_POLYGON_BREAKBLOCK];	//�X���C�h�u���b�N�̊e���
double g_aFileData_BreakBlock[AMOUNT_POLYGON_BREAKBLOCK][AMOUNT_POLYGON_BREAKBLOCK] = {};	//�t�@�C������f�[�^���i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_BreakBlock(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_1_BLOCK,
		&g_pTexture_BreakBlock[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_2_BLOCK,
		&g_pTexture_BreakBlock[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_1_BLOCK,
		&g_pTexture_BreakBlock[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_2_BLOCK,
		&g_pTexture_BreakBlock[3]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_1_BLOCK,
		&g_pTexture_BreakBlock[4]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_2_BLOCK,
		&g_pTexture_BreakBlock[5]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BREAKBLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_BreakBlock,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Score;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_BreakBlock->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BREAKBLOCK; nCnt++)
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
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BREAKBLOCK; nCnt++)
	{
		g_aBreakBlock[nCnt].nStyle = BLOCKSTYLE_SHROT_1;
		g_aBreakBlock[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBreakBlock[nCnt].fHalfSpanX = 0.0f;
		g_aBreakBlock[nCnt].fHalfSpanY = 0.0f;
		g_aBreakBlock[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBreakBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBreakBlock[nCnt].bUse = false;
		g_aBreakBlock[nCnt].nCntSpawn = 0;
		g_aBreakBlock[nCnt].nLife = 0;
		g_aBreakBlock[nCnt].fLength = 0.0f;
		g_aBreakBlock[nCnt].fAngle = 0.0f;
	}

	//�t�@�C�����i�[�p��������
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_BREAKBLOCK; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_BLOCK)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData_BreakBlock[nCnt1][nCnt2] = {};
	}

	//�u���b�N����ݒ肷��
	Setinfo_BreakBlock();

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BreakBlock->Unlock();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_BreakBlock(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BLOCK; nCnt++)
	{
		if (g_pTexture_BreakBlock[nCnt] != NULL)
		{
			g_pTexture_BreakBlock[nCnt]->Release();
			g_pTexture_BreakBlock[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_BreakBlock != NULL)
	{
		g_pVtxBuff_BreakBlock->Release();
		g_pVtxBuff_BreakBlock = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************;
void Update_BreakBlock(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_BreakBlock;

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
	g_pVtxBuff_BreakBlock->Lock(0, 0, (void**)&pVtx_BreakBlock, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		if (g_aBreakBlock[nCnt].bUse)
		{
			//���Ԍo�߂œo��
			if (g_aBreakBlock[nCnt].nCntSpawn > 0)
			{
				g_aBreakBlock[nCnt].nCntSpawn--;
			}
			else
			{
				//�ړ�
				g_aBreakBlock[nCnt].pos.x += g_aBreakBlock[nCnt].move.x;
				g_aBreakBlock[nCnt].pos.y += g_aBreakBlock[nCnt].move.y;

				//���]���肪�o�Ă���Ƃ�
				if (*pInversion == true &&
					g_aBreakBlock[nCnt].move.x <= 7.0f &&
					*pReInversion == false)
				{
					g_aBreakBlock[nCnt].move.x += 0.1f;
				}
				else if (*pInversion == true &&
					g_aBreakBlock[nCnt].move.x >= -10.0f &&
					*pReInversion == true)
				{
					g_aBreakBlock[nCnt].move.x -= 0.1f;
				}

				switch (g_aBreakBlock[nCnt].nLife)
				{
				case BREAKBLOCKSTATE_LIFE3:

					//�F��ԐF�ɕύX
					g_aBreakBlock[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

					break;

				case BREAKBLOCKSTATE_LIFE2:

					//�F����F�ɕύX
					g_aBreakBlock[nCnt].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

					break;

				case BREAKBLOCKSTATE_LIFE1:

					//�F���I�����W�ɕύX
					g_aBreakBlock[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

					break;

				case BREAKBLOCKSTATE_BROKEN:

					g_aBreakBlock[nCnt].pos.x = -100.0f;

					g_aBreakBlock[nCnt].bUse = false;

					break;
				}

				//�v���C���[�����G���ԊO�ł��ꓖ��������
				if (pPlayer->pos.x <= g_aBreakBlock[nCnt].pos.x + g_aBreakBlock[nCnt].fHalfSpanX - 30.0f + HALFSPAN_X_PLAYER - 40.0f &&
					pPlayer->pos.x >= g_aBreakBlock[nCnt].pos.x - g_aBreakBlock[nCnt].fHalfSpanX + 30.0f - HALFSPAN_X_PLAYER + 20.0f &&
					pPlayer->pos.y >= g_aBreakBlock[nCnt].pos.y - g_aBreakBlock[nCnt].fHalfSpanY + 30.0f - HALFSPAN_Y_PLAYER + 20.0f &&
					pPlayer->pos.y <= g_aBreakBlock[nCnt].pos.y + g_aBreakBlock[nCnt].fHalfSpanY - 30.0f + HALFSPAN_Y_PLAYER - 40.0f &&
					pPlayer->state == PLAYERSTATE_NORMAL)
				{
					//�q�b�g����
					Hit_Player(1);
				}

				//�ړ��A��]�𔽉f
				pVtx_BreakBlock[0].pos.x = g_aBreakBlock[nCnt].pos.x + sinf(g_aBreakBlock[nCnt].rot.z - (D3DX_PI - g_aBreakBlock[nCnt].fAngle)) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[0].pos.y = g_aBreakBlock[nCnt].pos.y + cosf(g_aBreakBlock[nCnt].rot.z - (D3DX_PI - g_aBreakBlock[nCnt].fAngle)) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[1].pos.x = g_aBreakBlock[nCnt].pos.x + sinf(g_aBreakBlock[nCnt].rot.z + (D3DX_PI - g_aBreakBlock[nCnt].fAngle)) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[1].pos.y = g_aBreakBlock[nCnt].pos.y + cosf(g_aBreakBlock[nCnt].rot.z + (D3DX_PI - g_aBreakBlock[nCnt].fAngle)) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[2].pos.x = g_aBreakBlock[nCnt].pos.x + sinf(g_aBreakBlock[nCnt].rot.z - g_aBreakBlock[nCnt].fAngle) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[2].pos.y = g_aBreakBlock[nCnt].pos.y + cosf(g_aBreakBlock[nCnt].rot.z - g_aBreakBlock[nCnt].fAngle) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[3].pos.x = g_aBreakBlock[nCnt].pos.x + sinf(g_aBreakBlock[nCnt].rot.z + g_aBreakBlock[nCnt].fAngle) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[3].pos.y = g_aBreakBlock[nCnt].pos.y + cosf(g_aBreakBlock[nCnt].rot.z + g_aBreakBlock[nCnt].fAngle) * g_aBreakBlock[nCnt].fLength;

				//�F�ύX�̔��f
				pVtx_BreakBlock[0].col = g_aBreakBlock[nCnt].col;
				pVtx_BreakBlock[1].col = g_aBreakBlock[nCnt].col;
				pVtx_BreakBlock[2].col = g_aBreakBlock[nCnt].col;
				pVtx_BreakBlock[3].col = g_aBreakBlock[nCnt].col;
			}
		}

		//�|�C���^�����炷
		pVtx_BreakBlock += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BreakBlock->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_BreakBlock(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_BreakBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		//�u���b�N���g�p����Ă���Ȃ�
		if (g_aBreakBlock[nCnt].bUse == true)
		{
			switch (g_aBreakBlock[nCnt].nStyle)
			{
			case 0:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_BreakBlock[0]);

				break;

			case 1:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_BreakBlock[1]);

				break;

			case 2:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_BreakBlock[2]);

				break;

			case 3:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_BreakBlock[3]);

				break;

			case 4:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_BreakBlock[4]);

				break;

			case 5:

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTexture_BreakBlock[5]);

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
void Setinfo_BreakBlock(void)
{
	//�f�[�^�𕪕ʂ���p
	int nLine = 0, nRow = 0;

	//�t�@�C���|�C���^��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(FILE_SET_BREAKBLOCK, "r");

	//�f�[�^�̈�s�ڂɂ�������������΂�
	while (fgetc(pFile) != '\n');

	//�t�@�C�����J����
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_BreakBlock[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_BREAKBLOCK)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_BreakBlock;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_BreakBlock->Lock(0, 0, (void**)&pVtx_BreakBlock, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		//�u���b�N�̎g�p���肪������
		if (g_aBreakBlock[nCnt].bUse == false)
		{
			g_aBreakBlock[nCnt].nStyle = (int)g_aFileData_BreakBlock[0][nCnt];
			g_aBreakBlock[nCnt].pos.x = (float)g_aFileData_BreakBlock[1][nCnt];
			g_aBreakBlock[nCnt].pos.y = (float)g_aFileData_BreakBlock[2][nCnt];
			g_aBreakBlock[nCnt].fHalfSpanX = (float)g_aFileData_BreakBlock[3][nCnt];
			g_aBreakBlock[nCnt].fHalfSpanY = (float)g_aFileData_BreakBlock[4][nCnt];
			g_aBreakBlock[nCnt].move.x = (float)g_aFileData_BreakBlock[5][nCnt];
			g_aBreakBlock[nCnt].move.y = (float)g_aFileData_BreakBlock[6][nCnt];
			g_aBreakBlock[nCnt].move.z = (float)g_aFileData_BreakBlock[7][nCnt];
			g_aBreakBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBreakBlock[nCnt].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
			g_aBreakBlock[nCnt].bUse = true;
			g_aBreakBlock[nCnt].nCntSpawn = (int)g_aFileData_BreakBlock[8][nCnt];
			g_aBreakBlock[nCnt].nLife = (int)g_aFileData_BreakBlock[9][nCnt];
			g_aBreakBlock[nCnt].fLength = (float)g_aFileData_BreakBlock[10][nCnt];
			g_aBreakBlock[nCnt].fAngle = (float)g_aFileData_BreakBlock[11][nCnt];
		}

		pVtx_BreakBlock += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BreakBlock->Unlock();
}

//************************************************
//�u���C�N�u���b�N�ւ̖��������֐�
//************************************************
void Hit_BreakBlock(int nCntBreakBlock, int nDamage)
{
	//���ʉ���炷
	PlaySound(SOUND_LABEL_SE_DAMAGE);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_BreakBlock;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_BreakBlock->Lock(0, 0, (void**)&pVtx_BreakBlock, 0);

	//�����ɔ����ϋv�l�����炷
	g_aBreakBlock[nCntBreakBlock].nLife -= nDamage;

	//�j��
	if (g_aBreakBlock[nCntBreakBlock].nLife <= BREAKBLOCKSTATE_BROKEN)
	{
		/*����юU�点��\��*/
		//�p�[�e�B�N�����o��(�K��)
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			Setinfo_Particle_Block(g_aBreakBlock[nCntBreakBlock].pos, g_aBreakBlock[nCntBreakBlock].move);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_BreakBlock->Unlock();
}

//************************************************
//�u���C�N�u���b�N�̏��������n���֐�
//************************************************
BREAKBLOCK* Getinfo_BreakBlock(void)
{
	return &g_aBreakBlock[0];
}