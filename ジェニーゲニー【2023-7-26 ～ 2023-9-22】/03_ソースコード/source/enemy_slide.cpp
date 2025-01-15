//************************************************
//
//�G(�ړ�)����[enemy_slide.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "sound.h"
#include "block.h"
#include "effect_spawn.h"
#include "enemy_slide.h"
#include "item.h"
#include "particle.h"
#include "player.h"
#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Enemy_Slide = NULL;	//�e�N�X�`���̃|�C���^��G����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Enemy_Slide = NULL;	//���_�o�b�t�@�̃|�C���^
ENEMY_SLIDE g_aEnemy_Slide[AMOUNT_POLYGON_ENEMY_SLIDE];	//�G�̊e���i�[
double g_aFileData_Enemy_Slide[AMOUNT_POLYGON_ENEMY_SLIDE][AMOUNT_POLYGON_ENEMY_SLIDE] = {};	//�t�@�C������f�[�^���i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Enemy_Slide(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_SLIDE,
		&g_pTexture_Enemy_Slide);

	//�G�e���̏�����
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_SLIDE; nCnt++)
	{
		g_aEnemy_Slide[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̈ʒu����������
		g_aEnemy_Slide[nCnt].fHalfSpanX = 0.0f;						//�G�̔���X��������
		g_aEnemy_Slide[nCnt].fHalfSpanY = 0.0f;						//�G�̔���Y��������
		g_aEnemy_Slide[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̈ړ�����������
		g_aEnemy_Slide[nCnt].nRute = 0;								//���[�g���򏉊���
		g_aEnemy_Slide[nCnt].fHoldmoveX = 0.0f;						//�ړ��ʕێ���������
		g_aEnemy_Slide[nCnt].fHoldmoveY = 0.0f;						//�ړ��ʕێ���������
		g_aEnemy_Slide[nCnt].fTurn1 = 0.0f;							//�ړ�����߂�^�C�~���O1
		g_aEnemy_Slide[nCnt].fTurn2 = 0.0f;							//�ړ�����߂�^�C�~���O2
		g_aEnemy_Slide[nCnt].fDecreaseSPD = 0.0f;					//�ړ��ʂ̌������x
		//g_aEnemy_Slide[nCnt].bCharge = false;						//���ߊ���
		g_aEnemy_Slide[nCnt].bTurning = false;						//�����]��
		g_aEnemy_Slide[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̌�������������
		g_aEnemy_Slide[nCnt].nColA = 0;								//�����x����
		g_aEnemy_Slide[nCnt].state = ENEMYSTATE_SLIDE_NORMAL;		//��������ʏ���
		g_aEnemy_Slide[nCnt].nCntState = 0;							//�J�E���g����������
		g_aEnemy_Slide[nCnt].nLife = 0;								//���C�t��������
		g_aEnemy_Slide[nCnt].bUse = false;							//�g�p����𖳂���
		g_aEnemy_Slide[nCnt].nCntSpawn = 0;							//���o�����邩
		g_aEnemy_Slide[nCnt].bUseEffect = false;					//�G�t�F�N�g�g�p����𖳂���
		g_aEnemy_Slide[nCnt].bFinishEffect = false;					//�G�t�F�N�g�I������
		g_aEnemy_Slide[nCnt].fLength = 0.0f;						//�Ίp���̒�����������
		g_aEnemy_Slide[nCnt].fAngle = 0.0f;							//�Ίp���̊p�x��������
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ENEMY_SLIDE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Enemy_Slide,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy_Slide->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	//���_���W�̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_SLIDE; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Enemy[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Enemy[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Enemy[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Enemy[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Enemy[0].rhw = 1.0f;
		pVtx_Enemy[1].rhw = 1.0f;
		pVtx_Enemy[2].rhw = 1.0f;
		pVtx_Enemy[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Enemy[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Enemy[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Enemy[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Enemy[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Enemy[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�|�C���^�����炷
		pVtx_Enemy += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Enemy_Slide->Unlock();

	//�t�@�C�����i�[�p��������
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_ENEMY_SLIDE; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_ENEMY_SLIDE)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData_Enemy_Slide[nCnt1][nCnt2] = {};
	}

	//�G����ݒ肷��
	Setinfo_Enemy_Slide();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Enemy_Slide(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Enemy_Slide != NULL)
	{
		g_pTexture_Enemy_Slide->Release();
		g_pTexture_Enemy_Slide = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Enemy_Slide != NULL)
	{
		g_pVtxBuff_Enemy_Slide->Release();
		g_pVtxBuff_Enemy_Slide = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Enemy_Slide(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy_Slide;

	//�v���C���[���ւ̃|�C���^
	PLAYER* pPlayer;

	//�G���̎擾
	pPlayer = Getinfo_Player();	//�v���C���[���n�̐擪�A�h���X����������

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy_Slide->Lock(0, 0, (void**)&pVtx_Enemy_Slide, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_SLIDE; nCnt++)
	{
		//�g�p����Ă��锻�肾������
		if (g_aEnemy_Slide[nCnt].bUse == true)
		{
			//���Ԍo�߂œo��
			if (g_aEnemy_Slide[nCnt].nCntSpawn > 0)
			{
				g_aEnemy_Slide[nCnt].nCntSpawn--;
			}
			else
			{
				//��Ԃɍ��킹�ď�������
				switch (g_aEnemy_Slide[nCnt].state)
				{
					//�ʏ펞
				case ENEMYSTATE_SLIDE_NORMAL:

					/*�������Ȃ�*/

					break;

					//��e��
				case ENEMYSTATE_SLIDE_DAMAGE:

					//��Ԍp�����Ԃ����炷
					g_aEnemy_Slide[nCnt].nCntState--;

					//��Ԃ��I��鎞
					if (g_aEnemy_Slide[nCnt].nCntState <= 0)
					{
						//�Ԃ��Ȃ��Ă���̂�߂�
						pVtx_Enemy_Slide[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Enemy_Slide[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Enemy_Slide[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Enemy_Slide[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//�ʏ폈���ɕύX
						g_aEnemy_Slide[nCnt].state = ENEMYSTATE_SLIDE_NORMAL;
					}

					break;
				}

				//��]
				g_aEnemy_Slide[nCnt].rot.z += g_aEnemy_Slide[nCnt].move.z;

				//�ړ�
				g_aEnemy_Slide[nCnt].pos.x += g_aEnemy_Slide[nCnt].move.x;
				g_aEnemy_Slide[nCnt].pos.y += g_aEnemy_Slide[nCnt].move.y;

				//���[�g�ɍ����Ĉړ��ω�
				switch (g_aEnemy_Slide[nCnt].nRute)
				{
					//�ォ�牺
				case 0:

					//�K��l���z���Ă���Ԃ����ړ��ʂ𑝌�
					if (g_aEnemy_Slide[nCnt].pos.y < g_aEnemy_Slide[nCnt].fTurn1)
					{
						g_aEnemy_Slide[nCnt].move.y += g_aEnemy_Slide[nCnt].fDecreaseSPD;
					}
					
					if (g_aEnemy_Slide[nCnt].pos.y > g_aEnemy_Slide[nCnt].fTurn2)
					{
						g_aEnemy_Slide[nCnt].move.y -= g_aEnemy_Slide[nCnt].fDecreaseSPD;
					}

					break;

					//�������
				case 1:

					//�K��l���z���Ă���Ԃ����ړ��ʂ𑝌�
					if (g_aEnemy_Slide[nCnt].pos.y > g_aEnemy_Slide[nCnt].fTurn1)
					{
						g_aEnemy_Slide[nCnt].move.y -= g_aEnemy_Slide[nCnt].fDecreaseSPD;
					}

					if (g_aEnemy_Slide[nCnt].pos.y < g_aEnemy_Slide[nCnt].fTurn2)
					{
						g_aEnemy_Slide[nCnt].move.y += g_aEnemy_Slide[nCnt].fDecreaseSPD;
					}

					break;
				}

				//�v���C���[�����G���ԊO�ł��ꓖ��������
				if (pPlayer->pos.x <= g_aEnemy_Slide[nCnt].pos.x + g_aEnemy_Slide[nCnt].fHalfSpanX + HALFSPAN_X_PLAYER - 40.0f &&
					pPlayer->pos.x >= g_aEnemy_Slide[nCnt].pos.x - g_aEnemy_Slide[nCnt].fHalfSpanX - HALFSPAN_X_PLAYER + 20.0f &&
					pPlayer->pos.y >= g_aEnemy_Slide[nCnt].pos.y - g_aEnemy_Slide[nCnt].fHalfSpanY - HALFSPAN_Y_PLAYER + 20.0f &&
					pPlayer->pos.y <= g_aEnemy_Slide[nCnt].pos.y + g_aEnemy_Slide[nCnt].fHalfSpanY + HALFSPAN_Y_PLAYER - 40.0f &&
					pPlayer->state == PLAYERSTATE_NORMAL)
				{
					//�q�b�g����
					Hit_Player(1);
				}

				//�ړ��A��]�𔽉f
				pVtx_Enemy_Slide[0].pos.x = g_aEnemy_Slide[nCnt].pos.x + sinf(g_aEnemy_Slide[nCnt].rot.z - (D3DX_PI - g_aEnemy_Slide[nCnt].fAngle)) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[0].pos.y = g_aEnemy_Slide[nCnt].pos.y + cosf(g_aEnemy_Slide[nCnt].rot.z - (D3DX_PI - g_aEnemy_Slide[nCnt].fAngle)) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[1].pos.x = g_aEnemy_Slide[nCnt].pos.x + sinf(g_aEnemy_Slide[nCnt].rot.z + (D3DX_PI - g_aEnemy_Slide[nCnt].fAngle)) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[1].pos.y = g_aEnemy_Slide[nCnt].pos.y + cosf(g_aEnemy_Slide[nCnt].rot.z + (D3DX_PI - g_aEnemy_Slide[nCnt].fAngle)) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[2].pos.x = g_aEnemy_Slide[nCnt].pos.x + sinf(g_aEnemy_Slide[nCnt].rot.z - g_aEnemy_Slide[nCnt].fAngle) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[2].pos.y = g_aEnemy_Slide[nCnt].pos.y + cosf(g_aEnemy_Slide[nCnt].rot.z - g_aEnemy_Slide[nCnt].fAngle) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[3].pos.x = g_aEnemy_Slide[nCnt].pos.x + sinf(g_aEnemy_Slide[nCnt].rot.z + g_aEnemy_Slide[nCnt].fAngle) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[3].pos.y = g_aEnemy_Slide[nCnt].pos.y + cosf(g_aEnemy_Slide[nCnt].rot.z + g_aEnemy_Slide[nCnt].fAngle) * g_aEnemy_Slide[nCnt].fLength;
			}
		}

		pVtx_Enemy_Slide += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Enemy_Slide->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Enemy_Slide(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Enemy_Slide, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_SLIDE; nCnt++)
	{
		//�G���g�p����Ă���ꍇ
		if (g_aEnemy_Slide[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexture_Enemy_Slide);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}
}

//************************************************
//�G���ݒ菈���֐�
//************************************************
void Setinfo_Enemy_Slide(void)
{
	//�f�[�^�𕪕ʂ���p
	int nLine = 0, nRow = 0;

	//�t�@�C���|�C���^��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(FILE_SET_ENEMY_SLIDE, "r");

	//�f�[�^�̈�s�ڂɂ�������������΂�
	while (fgetc(pFile) != '\n');

	//�t�@�C�����J����
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_Enemy_Slide[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_ENEMY_SLIDE)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy_Slide;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy_Slide->Lock(0, 0, (void**)&pVtx_Enemy_Slide, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		g_aEnemy_Slide[nCnt].pos.x = (float)g_aFileData_Enemy_Slide[0][nCnt];		//X�������W���擾
		g_aEnemy_Slide[nCnt].pos.y = (float)g_aFileData_Enemy_Slide[1][nCnt];		//Y�������W���擾
		g_aEnemy_Slide[nCnt].fHalfSpanX = (float)g_aFileData_Enemy_Slide[2][nCnt];	//����X�擾
		g_aEnemy_Slide[nCnt].fHalfSpanY = (float)g_aFileData_Enemy_Slide[3][nCnt];	//����Y�擾
		g_aEnemy_Slide[nCnt].move.x = (float)g_aFileData_Enemy_Slide[4][nCnt];		//X�ړ��ʂ��擾
		g_aEnemy_Slide[nCnt].move.y = (float)g_aFileData_Enemy_Slide[5][nCnt];		//Y�ړ��ʂ��擾
		g_aEnemy_Slide[nCnt].move.z = (float)g_aFileData_Enemy_Slide[6][nCnt];		//Z�ړ��ʂ��擾
		g_aEnemy_Slide[nCnt].nRute = (int)g_aFileData_Enemy_Slide[7][nCnt];			//���[�g����
		g_aEnemy_Slide[nCnt].fHoldmoveX = g_aEnemy_Slide[nCnt].move.x;				//�ړ��ʕێ���������
		g_aEnemy_Slide[nCnt].fHoldmoveY = g_aEnemy_Slide[nCnt].move.y;				//�ړ��ʕێ���������
		g_aEnemy_Slide[nCnt].fTurn1 = (float)g_aFileData_Enemy_Slide[8][nCnt];		//�ړ�����߂�^�C�~���O1
		g_aEnemy_Slide[nCnt].fTurn2 = (float)g_aFileData_Enemy_Slide[9][nCnt];		//�ړ�����߂�^�C�~���O2
		g_aEnemy_Slide[nCnt].fDecreaseSPD = (float)g_aFileData_Enemy_Slide[10][nCnt];//�ړ��ʂ̌������x
		g_aEnemy_Slide[nCnt].bTurning = false;						//�����]��
		g_aEnemy_Slide[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//������������
		g_aEnemy_Slide[nCnt].nColA = 255;							//�����x����
		g_aEnemy_Slide[nCnt].state = ENEMYSTATE_SLIDE_NORMAL;		//�ʏ��Ԃ�ݒ�
		g_aEnemy_Slide[nCnt].nCntState = 255;						//�p�����Ԃ�0��
		g_aEnemy_Slide[nCnt].nLife = (int)g_aFileData_Enemy_Slide[11][nCnt];		//���C�t���擾
		g_aEnemy_Slide[nCnt].bUse = true;							//���̓G�̎g�p������o��
		g_aEnemy_Slide[nCnt].nCntSpawn = (int)g_aFileData_Enemy_Slide[12][nCnt];	//�o���܂łɗv���鎞�Ԃ��擾
		g_aEnemy_Slide[nCnt].bUseEffect = false;					//�G�t�F�N�g�g�p����͂܂�����
		g_aEnemy_Slide[nCnt].bFinishEffect = false;					//�G�t�F�N�g�I���J�n����͂܂�����
		g_aEnemy_Slide[nCnt].fLength = (float)g_aFileData_Enemy_Slide[13][nCnt];		//�Ίp���擾
		g_aEnemy_Slide[nCnt].fAngle = (float)g_aFileData_Enemy_Slide[14][nCnt];			//�p�x�擾

		//�|�C���^�����炷
		pVtx_Enemy_Slide += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Enemy_Slide->Unlock();
}

//************************************************
//�G(�ړ�)�ւ̖��������֐�
//************************************************
void Hit_Slide_Enemy(int nCntEnemy, int nDamage)
{
	//���ʉ���炷
	PlaySound(SOUND_LABEL_SE_DAMAGE);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy_Slide;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy_Slide->Lock(0, 0, (void**)&pVtx_Enemy_Slide, 0);

	//�����ɔ������C�t�����炷
	g_aEnemy_Slide[nCntEnemy].nLife -= nDamage;	//���̖ڂ̓G�ɁA�ǂꂾ���̃_���[�W��^����̂�

	//�G�����j
	if (g_aEnemy_Slide[nCntEnemy].nLife <= 0)
	{
		//�X�R�A��100����
		Add_Score(100);

		//�A�C�e���h���b�v
		Setinfo_Item(g_aEnemy_Slide[nCntEnemy].pos, 1);

		//�p�[�e�B�N�����o��(�K��)
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			Setinfo_Particle(g_aEnemy_Slide[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}

		//�|�C���^���炵
		pVtx_Enemy_Slide += AMOUNT_VTX * nCntEnemy;

		//��ԕω����Ȃ��̂ł����ŒE�F
		pVtx_Enemy_Slide[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy_Slide[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy_Slide[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy_Slide[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���̓G�̖{�̂̎g�p������
		g_aEnemy_Slide[nCntEnemy].bUse = false;
	}
	//�G���܂������Ă���
	else
	{
		//10�_�����܂���
		Add_Score(10);

		//�G���_���[�W��Ԃ�
		g_aEnemy_Slide[nCntEnemy].state = ENEMYSTATE_SLIDE_DAMAGE;

		//�_���[�W��Ԍp�����Ԑݒ�
		g_aEnemy_Slide[nCntEnemy].nCntState = AMOUNT_CNT_STATE_ENEMY_SLIDE;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Enemy_Slide->Unlock();
}

//************************************************
//�G���̐擪�A�h���X��n���֐�
//************************************************
ENEMY_SLIDE* Getinfo_Enemy_Slide(void)
{
	return &g_aEnemy_Slide[0];	//�G���̐擪�A�h���X��n��
}

//************************************************
//�g�����I�����G�̏��ŏ����֐�
//************************************************
void Disapper_Enemy_Slide(int nCntEnemy)
{
	g_aEnemy_Slide[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̈ʒu����������
	g_aEnemy_Slide[nCntEnemy].fHalfSpanX = 0.0f;					//�G�̔���X��������
	g_aEnemy_Slide[nCntEnemy].fHalfSpanY = 0.0f;					//�G�̔���Y��������
	g_aEnemy_Slide[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̈ړ�����������
	g_aEnemy_Slide[nCntEnemy].nRute = 0;							//���[�g���򏉊���
	g_aEnemy_Slide[nCntEnemy].fHoldmoveX = 0.0f;					//�ړ��ʕێ���������
	g_aEnemy_Slide[nCntEnemy].fHoldmoveY = 0.0f;					//�ړ��ʕێ���������
	g_aEnemy_Slide[nCntEnemy].fTurn1 = 0.0f;						//�ړ�����߂�^�C�~���O1
	g_aEnemy_Slide[nCntEnemy].fTurn2 = 0.0f;						//�ړ�����߂�^�C�~���O2
	g_aEnemy_Slide[nCntEnemy].fDecreaseSPD = 0.0f;					//�ړ��ʂ̌������x
	//g_aEnemy_Slide[nCntEnemy].bCharge = false;					//���ߊ���
	g_aEnemy_Slide[nCntEnemy].bTurning = false;						//�����]��
	g_aEnemy_Slide[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̌�������������
	g_aEnemy_Slide[nCntEnemy].nColA = 0;							//�����x������
	g_aEnemy_Slide[nCntEnemy].state = ENEMYSTATE_SLIDE_NORMAL;		//��������ʏ���
	g_aEnemy_Slide[nCntEnemy].nCntState = 0;						//�J�E���g����������
	g_aEnemy_Slide[nCntEnemy].nLife = 0;							//���C�t��������
	g_aEnemy_Slide[nCntEnemy].bUse = false;							//�g�p����𖳂���
	g_aEnemy_Slide[nCntEnemy].nCntSpawn = 0;						//���o�����邩
	g_aEnemy_Slide[nCntEnemy].bUseEffect = false;					//�G�t�F�N�g�g�p����𖳂���
	g_aEnemy_Slide[nCntEnemy].bFinishEffect = false;				//�G�t�F�N�g�I������𖳂���
	g_aEnemy_Slide[nCntEnemy].fLength = 0.0f;						//�Ίp���̒�����������
	g_aEnemy_Slide[nCntEnemy].fAngle = 0.0f;						//�Ίp���̊p�x��������
}