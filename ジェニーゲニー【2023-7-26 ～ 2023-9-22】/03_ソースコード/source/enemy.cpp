//************************************************
//
//�G(����)����[enemy.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "sound.h"
#include "block.h"
#include "effect_spawn.h"
#include "enemy.h"
#include "item.h"
#include "particle.h"
#include "player.h"
#include "score.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Enemy = NULL;	//�e�N�X�`���̃|�C���^��G����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Enemy = NULL;	//���_�o�b�t�@�̃|�C���^
ENEMY g_aEnemy[AMOUNT_POLYGON_ENEMY];	//�G�̊e���i�[
double g_aFileData[AMOUNT_POLYGON_ENEMY][AMOUNT_POLYGON_ENEMY] = {};	//�t�@�C������f�[�^���i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Enemy(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CLOUD_ENEMY,
		&g_pTexture_Enemy);

	//�G�e���̏�����
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		g_aEnemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�G�̈ʒu����������
		g_aEnemy[nCnt].fHalfSpanX = 0.0f;						//�G�̔���X��������
		g_aEnemy[nCnt].fHalfSpanY = 0.0f;						//�G�̔���Y��������
		g_aEnemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̈ړ�����������
		g_aEnemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�G�̌�������������
		g_aEnemy[nCnt].nColA = 0;								//�����x����
		g_aEnemy[nCnt].state = ENEMYSTATE_NORMAL;				//��������ʏ���
		g_aEnemy[nCnt].nCntState = 0;							//�J�E���g����������
		g_aEnemy[nCnt].nLife = 0;								//���C�t��������
		g_aEnemy[nCnt].bUse = false;							//�g�p����𖳂���
		g_aEnemy[nCnt].nCntSpawn = 0;							//���o�����邩
		g_aEnemy[nCnt].bUseEffect = false;						//�G�t�F�N�g�g�p����𖳂���
		g_aEnemy[nCnt].bFinishEffect = false;					//�G�t�F�N�g�I������
		g_aEnemy[nCnt].fLength = 0.0f;							//�Ίp���̒�����������
		g_aEnemy[nCnt].fAngle = 0.0f;							//�Ίp���̊p�x��������
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Enemy,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	//���_���W�̐ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
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
	g_pVtxBuff_Enemy->Unlock();

	//�t�@�C�����i�[�p��������
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_ENEMY; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_ENEMY)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData[nCnt1][nCnt2] = {};
	}

	//�G����ݒ肷��
	Setinfo_Enemy();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Enemy(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Enemy != NULL)
	{
		g_pTexture_Enemy->Release();
		g_pTexture_Enemy = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Enemy != NULL)
	{
		g_pVtxBuff_Enemy->Release();
		g_pVtxBuff_Enemy = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Enemy(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy;

	//�v���C���[���ւ̃|�C���^
	PLAYER* pPlayer;

	//�G���̎擾
	pPlayer = Getinfo_Player();	//�v���C���[���n�̐擪�A�h���X����������

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//�g�p����Ă��锻�肾������
		if (g_aEnemy[nCnt].bUse == true)
		{
			//���Ԍo�߂œo��
			if (g_aEnemy[nCnt].nCntSpawn > 0)
			{
				g_aEnemy[nCnt].nCntSpawn--;
			}
			else
			{
				//�G�t�F�N�g����x�̂ݏo������
				if (!g_aEnemy[nCnt].bUseEffect)
				{
					g_aEnemy[nCnt].bUseEffect = true;

					SetPos_Vtx_Effect_Spawn(nCnt, g_aEnemy[nCnt].pos, g_aEnemy[nCnt].move);
				}
				else
				{
					//��Ԃɍ��킹�ď�������
					switch (g_aEnemy[nCnt].state)
					{
						//�ʏ펞
					case ENEMYSTATE_NORMAL:

						/*�������Ȃ�*/

						break;

						//��e��
					case ENEMYSTATE_DAMAGE:

						//��Ԍp�����Ԃ����炷
						g_aEnemy[nCnt].nCntState--;

						//��Ԃ��I��鎞
						if (g_aEnemy[nCnt].nCntState <= 0)
						{
							//�Ԃ��Ȃ��Ă���̂�߂�
							pVtx_Enemy[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx_Enemy[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx_Enemy[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx_Enemy[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

							//�ʏ폈���ɕύX
							g_aEnemy[nCnt].state = ENEMYSTATE_NORMAL;
						}

						break;
					}

					//��]
					g_aEnemy[nCnt].rot.z += g_aEnemy[nCnt].move.z;

					//�ړ�
					g_aEnemy[nCnt].pos.x += g_aEnemy[nCnt].move.x;
					g_aEnemy[nCnt].pos.y += g_aEnemy[nCnt].move.y;

					//�v���C���[�����G���ԊO�ł��ꓖ��������
					if (pPlayer->pos.x <= g_aEnemy[nCnt].pos.x + g_aEnemy[nCnt].fHalfSpanX + HALFSPAN_X_PLAYER - 40.0f &&
						pPlayer->pos.x >= g_aEnemy[nCnt].pos.x - g_aEnemy[nCnt].fHalfSpanX - HALFSPAN_X_PLAYER + 20.0f &&
						pPlayer->pos.y >= g_aEnemy[nCnt].pos.y - g_aEnemy[nCnt].fHalfSpanY - HALFSPAN_Y_PLAYER + 20.0f &&
						pPlayer->pos.y <= g_aEnemy[nCnt].pos.y + g_aEnemy[nCnt].fHalfSpanY + HALFSPAN_Y_PLAYER - 40.0f &&
						pPlayer->state == PLAYERSTATE_NORMAL)
					{
						//�q�b�g����
						Hit_Player(1);
					}

					//���܂�ɂ������֍s���Ă��܂�����
					if (g_aEnemy[nCnt].pos.x <= -300.0f ||
						g_aEnemy[nCnt].pos.x >= 2300.0f)
					{
						//���ŏ���
						Disapper_Enemy(nCnt);
					}

					//�ړ��A��]�𔽉f
					pVtx_Enemy[0].pos.x = g_aEnemy[nCnt].pos.x + sinf(g_aEnemy[nCnt].rot.z - (D3DX_PI - g_aEnemy[nCnt].fAngle)) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[0].pos.y = g_aEnemy[nCnt].pos.y + cosf(g_aEnemy[nCnt].rot.z - (D3DX_PI - g_aEnemy[nCnt].fAngle)) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[1].pos.x = g_aEnemy[nCnt].pos.x + sinf(g_aEnemy[nCnt].rot.z + (D3DX_PI - g_aEnemy[nCnt].fAngle)) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[1].pos.y = g_aEnemy[nCnt].pos.y + cosf(g_aEnemy[nCnt].rot.z + (D3DX_PI - g_aEnemy[nCnt].fAngle)) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[2].pos.x = g_aEnemy[nCnt].pos.x + sinf(g_aEnemy[nCnt].rot.z - g_aEnemy[nCnt].fAngle) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[2].pos.y = g_aEnemy[nCnt].pos.y + cosf(g_aEnemy[nCnt].rot.z - g_aEnemy[nCnt].fAngle) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[3].pos.x = g_aEnemy[nCnt].pos.x + sinf(g_aEnemy[nCnt].rot.z + g_aEnemy[nCnt].fAngle) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[3].pos.y = g_aEnemy[nCnt].pos.y + cosf(g_aEnemy[nCnt].rot.z + g_aEnemy[nCnt].fAngle) * g_aEnemy[nCnt].fLength;
				}
			}
		}

		pVtx_Enemy += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Enemy->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Enemy(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Enemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//�G���g�p����Ă���ꍇ
		if (g_aEnemy[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexture_Enemy);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}
}

//************************************************
//�G���ݒ菈���֐�
//************************************************
void Setinfo_Enemy(void)
{
	//�f�[�^�𕪕ʂ���p
	int nLine = 0, nRow = 0;

	//�t�@�C���|�C���^��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(FILE_SET_ENEMY, "r");

	//�f�[�^�̈�s�ڂɂ�������������΂�
	while (fgetc(pFile) != '\n');

	//�t�@�C�����J����
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_ENEMY)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		g_aEnemy[nCnt].pos.x = (float)g_aFileData[0][nCnt];		//X�������W���擾
		g_aEnemy[nCnt].pos.y = (float)g_aFileData[1][nCnt];		//Y�������W���擾
		g_aEnemy[nCnt].fHalfSpanX = (float)g_aFileData[2][nCnt];	//����X�擾
		g_aEnemy[nCnt].fHalfSpanY = (float)g_aFileData[3][nCnt];	//����Y�擾
		g_aEnemy[nCnt].move.x = (float)g_aFileData[4][nCnt];		//X�ړ��ʂ��擾
		g_aEnemy[nCnt].move.y = (float)g_aFileData[5][nCnt];		//Y�ړ��ʂ��擾
		g_aEnemy[nCnt].move.z = (float)g_aFileData[6][nCnt];		//Z�ړ��ʂ��擾
		g_aEnemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//������������
		g_aEnemy[nCnt].nColA = 255;							//�����x����
		g_aEnemy[nCnt].state = ENEMYSTATE_NORMAL;			//�ʏ��Ԃ�ݒ�
		g_aEnemy[nCnt].nCntState = 255;						//�p�����Ԃ�0��
		g_aEnemy[nCnt].nLife = (int)g_aFileData[7][nCnt];		//���C�t���擾
		g_aEnemy[nCnt].bUse = true;							//���̓G�̎g�p������o��
		g_aEnemy[nCnt].nCntSpawn = (int)g_aFileData[8][nCnt];	//�o���܂łɗv���鎞�Ԃ��擾
		g_aEnemy[nCnt].bUseEffect = false;					//�G�t�F�N�g�g�p����͂܂�����
		g_aEnemy[nCnt].bFinishEffect = false;				//�G�t�F�N�g�I���J�n����͂܂�����
		g_aEnemy[nCnt].fLength = (float)g_aFileData[9][nCnt];		//�Ίp���擾
		g_aEnemy[nCnt].fAngle = (float)g_aFileData[10][nCnt];		//�p�x�擾

		//�|�C���^�����炷
		pVtx_Enemy += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Enemy->Unlock();
}

//************************************************
//�G(����)�ւ̖��������֐�
//************************************************
void Hit_Cloud_Enemy(int nCntEnemy, int nDamage)
{
	//���ʉ���炷
	PlaySound(SOUND_LABEL_SE_DAMAGE);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	//�����ɔ������C�t�����炷
	g_aEnemy[nCntEnemy].nLife -= nDamage;	//���̖ڂ̓G�ɁA�ǂꂾ���̃_���[�W��^����̂�

	//�G�����j
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//�X�R�A��100����
		Add_Score(100);

		//�A�C�e���h���b�v
		Setinfo_Item(g_aEnemy[nCntEnemy].pos, 1);

		//�p�[�e�B�N�����o��(�K��)
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			Setinfo_Particle(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.5f, 0.0f, 0.5f, 0.5f));
		}

		//�|�C���^���炵
		pVtx_Enemy += AMOUNT_VTX * nCntEnemy;

		//��ԕω����Ȃ��̂ł����ŒE�F
		pVtx_Enemy[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���̓G�̖{�̂̎g�p������
		g_aEnemy[nCntEnemy].bUse = false;
	}
	//�G���܂������Ă���
	else
	{
		//10�_�����܂���
		Add_Score(10);

		//�G���_���[�W��Ԃ�
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;

		//�_���[�W��Ԍp�����Ԑݒ�
		g_aEnemy[nCntEnemy].nCntState = AMOUNT_CNT_STATE_ENEMY;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Enemy->Unlock();
}

//************************************************
//�G���̐擪�A�h���X��n���֐�
//************************************************
ENEMY* Getinfo_Enemy(void)
{
	return &g_aEnemy[0];	//�G���̐擪�A�h���X��n��
}

//************************************************
//�g�����I�����G�̏��ŏ����֐�
//************************************************
void Disapper_Enemy(int nCntEnemy)
{
	g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(-1000.0f, -1000.0f, 0.0f);	//�G�̈ʒu����������
	g_aEnemy[nCntEnemy].fHalfSpanX = 0.0f;						//�G�̔���X��������
	g_aEnemy[nCntEnemy].fHalfSpanY = 0.0f;						//�G�̔���Y��������
	g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̈ړ�����������
	g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�G�̌�������������
	g_aEnemy[nCntEnemy].nColA = 0;								//�����x������
	g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;				//��������ʏ���
	g_aEnemy[nCntEnemy].nCntState = 0;							//�J�E���g����������
	g_aEnemy[nCntEnemy].nLife = 0;								//���C�t��������
	g_aEnemy[nCntEnemy].bUse = false;							//�g�p����𖳂���
	g_aEnemy[nCntEnemy].nCntSpawn = 0;							//���o�����邩
	g_aEnemy[nCntEnemy].bUseEffect = false;						//�G�t�F�N�g�g�p����𖳂���
	g_aEnemy[nCntEnemy].bFinishEffect = false;					//�G�t�F�N�g�I������𖳂���
	g_aEnemy[nCntEnemy].fLength = 0.0f;							//�Ίp���̒�����������
	g_aEnemy[nCntEnemy].fAngle = 0.0f;							//�Ίp���̊p�x��������
}