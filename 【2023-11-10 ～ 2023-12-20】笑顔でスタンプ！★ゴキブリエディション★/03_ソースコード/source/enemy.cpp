//************************************************
//
//�G����[enemy.cpp]
//Author�F���c����
//
//************************************************
#include "enemy.h"

#include <assert.h>
#include "debugproc.h"
#include "sound.h"

#include "bullet.h"
#include "collision.h"
#include "model.h"
#include "particle.h"
#include "player.h"
#include "score.h"
#include "shadow.h"
#include "tutorialdesign.h"
#include "visible_sphere.h"

//�O���[�o���錾
LPD3DXMESH g_pMeshEnemy[AMOUNT_ENEMY_PARTS];	//���b�V���̃|�C���^
LPD3DXBUFFER g_pBuffMatEnemy[AMOUNT_ENEMY_PARTS];	//�}�e���A���̃|�C���^
DWORD g_dwNumMatEnemy[AMOUNT_ENEMY_PARTS];	//�}�e���A���̐�
Enemy g_aEnemy[AMOUNT_ENEMY] = {};
int g_nCastSpawn = 0;	//�G�X�|�[���Ԋu�Ǘ�

//************************************************
//�G����
//************************************************
void InitEnemy(void)
{
	//���f���p����������
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		g_pMeshEnemy[i] = NULL;	//���b�V�����̃|�C���^�����N���A
		g_pBuffMatEnemy[i] = NULL;	//�}�e���A�����̃|�C���^���N���A
		g_dwNumMatEnemy[i] = 0;	//�}�e���A���̐����N���A
	}

	//�G�p�̏���������
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		g_aEnemy[i].bUse = false;
		g_aEnemy[i].nState = EnemyStateNormal;
		g_aEnemy[i].bATK = false;
		g_aEnemy[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEnemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].fRadius = 0.0f;
		g_aEnemy[i].nLife = 0;
		g_aEnemy[i].nCntState = 0;
		/* �p�[�c���N���A */
		for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
		{
			g_aEnemy[i].aParts[j].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[i].aParts[j].posM = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[i].aParts[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[i].aParts[j].rotM = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[i].aParts[j].nIdxParent = 0;
		}
		/* ���[�V�������N���A */
		for (int j = 0; j < AMOUNT_ENEMY_MOTION; j++)
		{
			g_aEnemy[i].motion[j].nIdxKey = 0;
			g_aEnemy[i].motion[j].nLoop = 0;
			g_aEnemy[i].motion[j].nNumKey = 0;
			g_aEnemy[i].motion[j].nFrameCnt = 0;

			for (int k = 0; k < AMOUNT_ENEMY_KEY; k++)
			{
				g_aEnemy[i].motion[j].key[k].nFrame = 0;

				for (int l = 0; l < AMOUNT_ENEMY_PARTS; l++)
				{
					g_aEnemy[i].motion[j].key[j].parts[l].posGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					g_aEnemy[i].motion[j].key[j].parts[l].rotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}
		g_aEnemy[i].nNowMotion = EnemyMotionStateNormal;
		g_aEnemy[i].nOldMotion = EnemyMotionStateNormal;
	}

	//�G�X�|�[���Ԋu�N���A
	g_nCastSpawn = 0;

	//���f���p�[�c�̐ݒ�
	SetInfoPartsEnemy();

	//���[�V�����̐ݒ�
	SetInfoMotionEnemy();
}

//************************************************
//���f���p�[�c����ݒ�
//************************************************
void SetInfoPartsEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�p�[�c�p����ݒ�
	FILE* pFile = NULL;
	char sEnemyModel[64] = {};

	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		//�p�[�c�ԃI�t�Z�b�g�̓Ǎ���
		if (fopen_s(&pFile, "data\\txt\\enemymodelset.txt", "r") != 0) return;

		/* ���f���p�[�c�̑����ȏニ�[�v�ŏI�� */
		for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
		{
			fscanf_s(pFile, "%d", &g_aEnemy[i].aParts[j].nIdxParent);
			fscanf_s(pFile, "%f %f %f", &g_aEnemy[i].aParts[j].pos.x, &g_aEnemy[i].aParts[j].pos.y, &g_aEnemy[i].aParts[j].pos.z);
			fscanf_s(pFile, "%f %f %f", &g_aEnemy[i].aParts[j].rot.x, &g_aEnemy[i].aParts[j].rot.y, &g_aEnemy[i].aParts[j].rot.z);
		}

		fclose(pFile);

		/**********************************************************/

		//X�t�@�C���̓ǂݍ���
		if (fopen_s(&pFile, "data\\txt\\enemymodel.txt", "r") != 0) return;

		int j = 0;

		/* �t�@�C���̏I�[�ɒ������A���f���p�[�c�̑����ȏニ�[�v�ŏI�� */
		while (fscanf_s(pFile, "%s", &sEnemyModel[0], 64) != EOF || j < AMOUNT_ENEMY_PARTS)
		{
			D3DXLoadMeshFromX(&sEnemyModel[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatEnemy[j],
				NULL,
				&g_dwNumMatEnemy[j],
				&g_pMeshEnemy[j]);

			j++;
		}

		fclose(pFile);
	}
}

//************************************************
//���[�V��������ݒ�(�v���P)
//************************************************
void SetInfoMotionEnemy(void)
{
	//���[�V�����p����ݒ�
	FILE* pFile = NULL;
	char sEnemyMotion[128] = {};

	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_ENEMY; nCntEnemy++)
	{
		Enemy* thisEnemy = &g_aEnemy[nCntEnemy];

		if (fopen_s(&pFile, "data\\txt\\enemykeyset.txt", "r") == 0)
		{
			int i = 0;	/* nStyle�Ǘ� */

			/* �t�@�C���̏I�[�ɒ����܂Ń��[�v */
			while (fscanf_s(pFile, "%s", &sEnemyMotion[0], 128) != EOF)
			{
				if (strcmp(&sEnemyMotion[0], "LOOP") == 0)
				{
					fscanf_s(pFile, "%s %d", &sEnemyMotion[0], 64, &thisEnemy->motion[i].nLoop);
				}
				if (strcmp(&sEnemyMotion[0], "NUM_KEY") == 0)
				{
					fscanf_s(pFile, "%s %d", &sEnemyMotion[0], 64, &thisEnemy->motion[i].nNumKey);

					/* �L�[�����擾�����̂ŁA�L�[�����̃t���[�����擾 */
					for (int j = 0; j < thisEnemy->motion[i].nNumKey; fscanf_s(pFile, "%s", &sEnemyMotion[0], 128))
					{
						if (strcmp(&sEnemyMotion[0], "FRAME") == 0)
						{
							fscanf_s(pFile, "%s %d", &sEnemyMotion[0], 64, &thisEnemy->motion[i].key[j].nFrame);

							/* �t���[�������擾�����̂ŁA�p�[�c�����̖ړI�n���擾 */
							for (int k = 0; k < AMOUNT_ENEMY_PARTS; fscanf_s(pFile, "%s", &sEnemyMotion[0], 128))
							{
								if (strcmp(&sEnemyMotion[0], "POS") == 0)
								{
									fscanf_s(pFile, "%s %f %f %f", &sEnemyMotion[0], 64, &thisEnemy->motion[i].key[j].parts[k].posGoal.x, &thisEnemy->motion[i].key[j].parts[k].posGoal.y, &thisEnemy->motion[i].key[j].parts[k].posGoal.z);
									fscanf_s(pFile, "%s", &sEnemyMotion[0], 64);
									fscanf_s(pFile, "%s %f %f %f", &sEnemyMotion[0], 64, &thisEnemy->motion[i].key[j].parts[k].rotGoal.x, &thisEnemy->motion[i].key[j].parts[k].rotGoal.y, &thisEnemy->motion[i].key[j].parts[k].rotGoal.z);

									k++;
								}
							}

							j++;

							/* �S�ẴL�[��ǂݍ��ނƁA���̃��[�V������ǂݍ��� */
							if (j >= thisEnemy->motion[i].nNumKey)
							{
								i++;
							}
						}
					}
				}
			}

			fclose(pFile);
		}
	}
}

//************************************************
//�G�j��
//************************************************
void UninitEnemy(void)
{
	//�}�e���A���̔j��
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		if (g_pBuffMatEnemy[i] != NULL)
		{
			g_pBuffMatEnemy[i]->Release();
			g_pBuffMatEnemy[i] = NULL;
		}
	}

	//���b�V���̔j��
	for (int i = 0; i < AMOUNT_ENEMY_PARTS; i++)
	{
		if (g_pMeshEnemy[i] != NULL)
		{
			g_pMeshEnemy[i]->Release();
			g_pMeshEnemy[i] = NULL;
		}
	}
}

//************************************************
//�G�Z�b�g
//************************************************
void SetInfoEnemy(void)
{
	//�X�|�[���n�_�����_���ݒ�
	Model* pModel = GetInfoModel();
	D3DXVECTOR3 Spawn = {};
	int nIdx = 0;
	
	nIdx = rand() % 4;
	Spawn = pModel[nIdx].pos;

	//�G�̏���ݒ�
	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		if (g_aEnemy[i].bUse) continue;

		g_aEnemy[i].bUse = true;
		g_aEnemy[i].nState = EnemyStateNormal;
		g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEnemy[i].pos = D3DXVECTOR3(Spawn.x, 0.0f, Spawn.z);
		g_aEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].fRadius = 10.0f;
		g_aEnemy[i].nLife = 2;
		g_aEnemy[i].nCntState = 0;

		//�e���Z�b�g
		SetInfoShadow(10.0f, &g_aEnemy[i].pos);

		//�����蔻�������
		//SetSizeVisible_Sphere(g_aEnemy[i].fRadius, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), &g_aEnemy[i].pos);

		for (int j = 0; j < 10; j++)
		{
			SetInfoParticle(g_aEnemy[i].pos, D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.9f), 3.0f);
		}

		break;
	}
}

//************************************************
//�G�X�V
//************************************************
void UpdateEnemy(int mode)
{
	//�o������
	if (mode == MODE_TUTORIAL)
	{
		bool* pSpawn = GetInfoSpawnEnemy();

		if (*pSpawn)
		{
			for (int i = 0; i < AMOUNT_ENEMY; i++)
			{
				if (g_aEnemy[i].bUse)
				{
					break;
				}

				//1�C���o�Ă��Ȃ��Ƃ��̂�
				SpawnEnemy();
			}
		}
	}
	else
	{
		SpawnEnemy();
	}

	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		if (g_aEnemy[i].bUse)
		{
			//�e�Ƃ̓����蔻��
			if (g_aEnemy[i].nState != EnemyStateEscape)
			{
				CollisionBullet(CollisionModeEnemy, i);
			}

			//�X�e�[�^�X�ɉ����čs��
			StateEnemy(i, mode);

			//���[�V�����Đ�
			MotionEnemy(i);

			//�U�����肪�o�ē���Δ��萶��
			if (g_aEnemy[i].bATK)
			{
				SetInfoATK(i);
			}
		}
	}
}

//************************************************
//�G�o��
//************************************************
void SpawnEnemy(void)
{
	//�X�|�[���L���X�g
	g_nCastSpawn++;

	//�L���X�g������
	if (g_nCastSpawn >= 60)
	{
		g_nCastSpawn = 0;

		//�G�Z�b�g
		SetInfoEnemy();
	}
}

//************************************************
//�G���
//************************************************
void StateEnemy(int nCnt, int mode)
{
	bool* pStamp = GetInfoStampEnemy();

	Enemy* Enemy = &g_aEnemy[nCnt];
	Player* pPlayer = GetInfoPlayer();

	float fVecPlayer = atan2f(pPlayer->pos.x - Enemy->pos.x, pPlayer->pos.z - Enemy->pos.z);
	float fAntiVecPlayer = atan2f(-(pPlayer->pos.x - Enemy->pos.x), -(pPlayer->pos.z - Enemy->pos.z));

	switch (Enemy->nState)
	{
		//�ʏ�
	case EnemyStateNormal:

		if (Enemy->col.a != 1.0f)
		{
			Enemy->col.a = 1.0f;
		}

		switch (Enemy->nLife)
		{
		case 2:
			Enemy->nState = EnemyStateDash;
			Enemy->nNowMotion = EnemyMotionStateDash;
			break;
		case 1:
			Enemy->nState = EnemyStateEscape;
			Enemy->nNowMotion = EnemyMotionStateDash;
			break;
		default:
			Enemy->nState = EnemyStateDeath;
			break;
		}

		break;

		//�_�b�V��
	case EnemyStateDash:

		//�ǂꂮ�炢�߂Â��Ă����̂��v�Z
		if(CollisionSphere(Enemy->pos, Enemy->fRadius, pPlayer->pos, 20.0f))
		{
			Enemy->nState = EnemyStateATK;
			Enemy->nNowMotion = EnemyMotionStateATK;
		}
		else
		{
			//�v���C���[�̕����ɂ���Ă���
			Enemy->move =
			{
				sinf(fVecPlayer),
				0.0f,
				cosf(fVecPlayer)
			};

			if (mode == MODE_TUTORIAL)
			{
				Enemy->move *= 1.0f;
			}
			else
			{
				Enemy->move *= 3.0f;
			}
		}
		Enemy->rot.y = fAntiVecPlayer;

		//�ǂꂮ�炢�߂Â��ꂽ���v�Z
		if (pPlayer->bMUKIMUKI)
		{
			if (CollisionSphere(pPlayer->pos, 100.0f, Enemy->pos, Enemy->fRadius))
			{
				Enemy->nState = EnemyStateNormal;
				Enemy->nLife -= 1;
			}
		}

		break;

		//�U��
	case EnemyStateATK:

		//�ǂꂮ�炢�߂Â��Ă����̂��v�Z
		if (!CollisionSphere(Enemy->pos, Enemy->fRadius, pPlayer->pos, 30.0f))
		{
			//�v���C���[�ɏ�������Ă���
			Enemy->move =
			{
				sinf(fVecPlayer),
				0.0f,
				cosf(fVecPlayer)
			};

			if (mode == MODE_TUTORIAL)
			{
				Enemy->move *= 0.5;
			}
			else
			{
				Enemy->move *= 1.5f;
			}
		}
		Enemy->rot.y = fAntiVecPlayer;

		//�ǂꂮ�炢�߂Â��ꂽ���v�Z
		if (pPlayer->bMUKIMUKI)
		{
			if (CollisionSphere(pPlayer->pos, 15.0f, Enemy->pos, Enemy->fRadius))
			{
				Enemy->nState = EnemyStateNormal;
				Enemy->nLife -= 2;

				for (int i = 0; i < 30; i++)
				{
					SetInfoParticle(Enemy->pos, D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.9f), 7.0f);
				}
			}
		}

		break;

		//����
	case EnemyStateEscape:

		//�v���C���[���瓦����
		Enemy->move =
		{
			sinf(fAntiVecPlayer),
			0.0f,
			cosf(fAntiVecPlayer)
		};

		if (mode == MODE_TUTORIAL)
		{
			Enemy->move *= 0.5f;
		}
		else
		{
			Enemy->move *= 1.8f;
		}

		Enemy->rot.y = fVecPlayer;

		//�ǂꂮ�炢�߂Â��ꂽ���v�Z
		if (CollisionSphere(pPlayer->pos, 15.0f, Enemy->pos, Enemy->fRadius))
		{
			Enemy->nState = EnemyStateNormal;
			Enemy->nLife--;

			for (int i = 0; i < 30; i++)
			{
				SetInfoParticle(Enemy->pos, D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.9f), 7.0f);
			}

			if (pPlayer->bMUKIMUKI)
			{
				pPlayer->nEnegy += 35;
			}
		}

		break;

		//��e
	case EnemyStateDamage:

		//���G����
		if (Enemy->nCntState >= 0)
		{
			Enemy->nCntState--;
		}
		else
		{
			Enemy->nState = EnemyStateNormal;
		}

		Enemy->col.a *= -1.0f;

		break;

		//���S
	case EnemyStateDeath:

		//����
		DisappearEnemy(nCnt);
		Add_Score(666);

		if (mode == MODE_TUTORIAL)
		{
			*pStamp = true;
		}

		PlaySound(SOUND_LABEL_STAMP);

		break;

		//�A�N�Z�X�G���[
	default:
		assert(false);
		break;
	}

	g_aEnemy[nCnt].move *= 0.8f;	//�u���[�L
	g_aEnemy[nCnt].pos += g_aEnemy[nCnt].move;	//�ړ����x
}

//************************************************
//�G�U������
//************************************************
void SetInfoATK(int nCnt)
{
	Player* pPlayer = GetInfoPlayer();

	//�茳�ɍU��
	if (!pPlayer->bMUKIMUKI)
	{
		if (CollisionSphere(pPlayer->pos, 25.0f, g_aEnemy[nCnt].pos, g_aEnemy[nCnt].fRadius))
		{
			pPlayer->move =
			{
				sinf(g_aEnemy[nCnt].rot.y),
				0.0f,
				cosf(g_aEnemy[nCnt].rot.y),
			};

			pPlayer->move *= -30.0f;

			pPlayer->nState = PlayerStateDamage;
			pPlayer->nCntState = 20;

			pPlayer->nEnegy += 15;

			PlaySound(SOUND_LABEL_DAMAGE);
		}
	}

	g_aEnemy[nCnt].bATK = false;
}

//************************************************
//�G����
//************************************************
void DisappearEnemy(int nCnt)
{
	//�G�p�̏���������
	g_aEnemy[nCnt].bUse = false;
	g_aEnemy[nCnt].nState = EnemyStateNormal;
	g_aEnemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEnemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEnemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEnemy[nCnt].fRadius = 0.0f;
	g_aEnemy[nCnt].nLife = 0;
	g_aEnemy[nCnt].nCntState = 0;
	g_aEnemy[nCnt].nNowMotion = EnemyMotionStateNormal;
	g_aEnemy[nCnt].nOldMotion = EnemyMotionStateNormal;

	//�e�ɂ����ŏ������s��
	DisappearShadow(&g_aEnemy[nCnt].pos);

	//�����蔻������ɂ����ŏ������s��
	//DisappearVisible_Sphere(&g_aEnemy[nCnt].pos);
}

//************************************************
//�G���[�V�����Ǘ�
//************************************************
void MotionEnemy(int nCnt)
{
	EnemyMotionSet* Motion = &g_aEnemy[nCnt].motion[g_aEnemy[nCnt].nNowMotion];

	//���[�V�����ɕύX�����邩���m
	MotionChangeEnemy(nCnt);

	//�p�[�c�̈ړ����]
	MotionMoveEnemy(nCnt, Motion);

	//���[�V�����p�̌o�߃J�E���g
	MotionCountEnemy(nCnt, Motion);
}

//************************************************
//���[�V�����ύX
//************************************************
void MotionChangeEnemy(int nCnt)
{
	/* ���[�V�������ύX����Ă���� */
	if (g_aEnemy[nCnt].nOldMotion != g_aEnemy[nCnt].nNowMotion)
		{
		//�L�[�ƃt���[���J�E���g���Z�b�g
		g_aEnemy[nCnt].motion[g_aEnemy[nCnt].nOldMotion].nFrameCnt = 0;
		g_aEnemy[nCnt].motion[g_aEnemy[nCnt].nOldMotion].nIdxKey = 0;

		//�V�������[�V�������Đ��������Ƃ�ۑ�
		g_aEnemy[nCnt].nOldMotion = g_aEnemy[nCnt].nNowMotion;
	}
}

//************************************************
//���[�V�����p�ړ�
//************************************************
void MotionMoveEnemy(int nCnt, const EnemyMotionSet* Motion)
{
	/* �c�H(�p����) */
	//float fFrame = (float)(Motion->key[Motion->nIdxKey].nFrame);
	float fFrame = (float)(Motion->key[Motion->nIdxKey].nFrame - Motion->nFrameCnt);

	//�ڕW�ƌ��݂̍��𖄂߂Ă���
	for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
	{
		g_aEnemy[nCnt].aParts[j].posM += (Motion->key[Motion->nIdxKey].parts[j].posGoal - g_aEnemy[nCnt].aParts[j].posM) / fFrame;
		g_aEnemy[nCnt].aParts[j].rotM += (Motion->key[Motion->nIdxKey].parts[j].rotGoal - g_aEnemy[nCnt].aParts[j].rotM) / fFrame;
	}
}

//************************************************
//���[�V�����p�J�E���g
//************************************************
void MotionCountEnemy(int nCnt, EnemyMotionSet* Motion)
{
	Motion->nFrameCnt++;	/* �t���[����i�߂� */

	if (Motion->nFrameCnt >= Motion->key[Motion->nIdxKey].nFrame)	/* ���v�t���[�������o�߂� */
	{
		Motion->nFrameCnt = 0;
		Motion->nIdxKey++;		/* �L�[��i�߂� */

		//�U�����[�V�������̂��傤�ǂ����L�[�̃^�C�~���O�ōU������𐶐�
		if (g_aEnemy[nCnt].nState == EnemyStateATK && Motion->nIdxKey == 10 && !g_aEnemy[nCnt].bATK)
		{
			g_aEnemy[nCnt].bATK = true;
		}

		if (Motion->nIdxKey >= Motion->nNumKey)	/* ���v�L�[���o�߂� */
		{
			if (g_aEnemy[nCnt].nState == EnemyStateATK)
			{
				g_aEnemy[nCnt].nState = EnemyStateNormal;
				return;
			}

			if (Motion->nLoop == 1)
			{
				Motion->nIdxKey = 0;
				return;
			}

			g_aEnemy[nCnt].nNowMotion = EnemyMotionStateNormal;
		}
	}
}

//************************************************
//�G�`��
//************************************************
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	for (int i = 0; i < AMOUNT_ENEMY; i++)
	{
		if (g_aEnemy[i].bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEnemy[i].mtxWorld);

			//�����𔽉f1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_aEnemy[i].rot.y,
				g_aEnemy[i].rot.x,
				g_aEnemy[i].rot.z);

			//�����𔽉f2
			D3DXMatrixMultiply(&g_aEnemy[i].mtxWorld,
				&g_aEnemy[i].mtxWorld,
				&mtxRot);

			//�ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				g_aEnemy[i].pos.x,
				g_aEnemy[i].pos.y,
				g_aEnemy[i].pos.z);

			//�ʒu�𔽉f2
			D3DXMatrixMultiply(&g_aEnemy[i].mtxWorld,
				&g_aEnemy[i].mtxWorld,
				&mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[i].mtxWorld);

			for (int j = 0; j < AMOUNT_ENEMY_PARTS; j++)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aEnemy[i].aParts[j].mtxWorld);

				//���[�V���������̔��f
				D3DXVECTOR3 PartsRot =
				{
					g_aEnemy[i].aParts[j].rot.x + g_aEnemy[i].aParts[j].rotM.x,
					g_aEnemy[i].aParts[j].rot.y + g_aEnemy[i].aParts[j].rotM.y,
					g_aEnemy[i].aParts[j].rot.z + g_aEnemy[i].aParts[j].rotM.z
				};

				//�����𔽉f1
				D3DXMatrixRotationYawPitchRoll(&mtxRot,
					PartsRot.y,
					PartsRot.x,
					PartsRot.z);

				//�����𔽉f2
				D3DXMatrixMultiply(&g_aEnemy[i].aParts[j].mtxWorld,
					&g_aEnemy[i].aParts[j].mtxWorld,
					&mtxRot);

				//���[�V�����ʒu�̔��f
				D3DXVECTOR3 PartsPos =
				{
					g_aEnemy[i].aParts[j].pos.x + g_aEnemy[i].aParts[j].posM.x,
					g_aEnemy[i].aParts[j].pos.y + g_aEnemy[i].aParts[j].posM.y,
					g_aEnemy[i].aParts[j].pos.z + g_aEnemy[i].aParts[j].posM.z
				};

				//�ʒu�𔽉f1
				D3DXMatrixTranslation(&mtxTrans,
					PartsPos.x,
					PartsPos.y,
					PartsPos.z);

				//�ʒu�𔽉f
				D3DXMatrixMultiply(&g_aEnemy[i].aParts[j].mtxWorld,
					&g_aEnemy[i].aParts[j].mtxWorld,
					&mtxTrans);

				D3DXMATRIX mtxParent = {};

				//�e�̃��[���h�}�g���b�N�X���擾
				if (g_aEnemy[i].aParts[j].nIdxParent == -1)
				{
					mtxParent = g_aEnemy[i].mtxWorld;
				}
				else
				{
					mtxParent = g_aEnemy[i].aParts[g_aEnemy[i].aParts[j].nIdxParent].mtxWorld;
				}

				//�p�[�c���Ƃ̃��[���h�}�g���b�N�X���Z�o
				D3DXMatrixMultiply(&g_aEnemy[i].aParts[j].mtxWorld,
					&g_aEnemy[i].aParts[j].mtxWorld,
					&mtxParent);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[i].aParts[j].mtxWorld);

				//���݂̃}�e���A�����擾
				pDevice->GetMaterial(&matDef);

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatEnemy[j]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_dwNumMatEnemy[j]; nCntMat++)
				{
					//�F��ݒ�
					pMat[nCntMat].MatD3D.Diffuse.a = g_aEnemy[i].col.a;

					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�e�N�X�`���̐ݒ�
					pDevice->SetTexture(0, NULL);

					//���f���p�[�c�̕`��
					g_pMeshEnemy[j]->DrawSubset(nCntMat);
				}

				//�ۑ����Ă����}�e���A����߂�
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//************************************************
//�G�����擾
//************************************************
Enemy* GetInfoEnemy(void)
{
	return &g_aEnemy[0];
}