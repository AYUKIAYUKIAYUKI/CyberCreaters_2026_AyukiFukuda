//************************************************
//
//�v���C���[[player.cpp]
//Author�F���c����
//
//************************************************
#include "player.h"

#include "debugproc.h"
#include "input.h"
#include "sound.h"

#include "bullet.h"
#include "camera.h"
#include "model.h"
#include "shadow.h"
#include "visible_rect.h"
#include "wall.h"

//�}�N����`
#define SPD_STOPMOVE_PLAYER	(0.9f)	//�u���[�L��
#define SPD_MOVE_PLAYER	(0.2f)	//�ړ����x
#define EPSILON	(0.1f)	//臒l

//�O���[�o���ϐ�
Player g_Player;	//�v���C���[���
int g_nMUKIMUKI_Colorful_CT = 0;	//���L���L�J���t���L���X�g
bool g_bOnceRosalia = false;
int g_nDecrease = 0;
//D3DXCOLOR coldef[AMOUNT_PLAYER_PARTS][8];
//bool g_bDef = false;

//�p�[�c�Z�b�g
static const char* g_sFileNameParts[2] =
{
	"data\\txt\\danceP.txt",
	"data\\txt\\playermodelset.txt"
};

//���[�V�����Z�b�g
static const char* g_sFileNameMotion[2] =
{
	"data\\txt\\dance.txt",
	"data\\txt\\playerkeyset.txt"
};

//************************************************
//�v���C���[����
//************************************************
void InitPlayer(int mode)
{
	g_nMUKIMUKI_Colorful_CT = 0;
	g_bOnceRosalia = false;
	g_nDecrease = 0;
	//g_bDef = false;

	//for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		coldef[i][j] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//	}
	//}

	//�v���C���[�̏����Z�b�g
	g_Player.nState = PlayerStateNormal;
	g_Player.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_Player.bATK = false;
	g_Player.bMUKIMUKI = false;
	g_Player.nCapacity = AMOUNT_CAPACITY;
	g_Player.nEnegy = 0;
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nCntState = 0;
	/* �p�[�c���N���A */
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		g_Player.aParts[i].pMeshPlayer = NULL;	//���b�V�����̃|�C���^�����N���A
		g_Player.aParts[i].pBuffMatPlayer = NULL;	//�}�e���A�����̃|�C���^���N���A
		g_Player.aParts[i].dwNumMatPlayer = 0;	//�}�e���A���̐����N���A
		g_Player.aParts[i].pTexture = NULL;	//�e�N�X�`�����̃|�C���^���N���A
		g_Player.aParts[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aParts[i].posM = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aParts[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aParts[i].rotM = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Player.aParts[i].nIdxParent = 0;
	}
	/* ���[�V�������N���A */
	for (int i = 0; i < PlayerStateMax; i++)
	{
		g_Player.motion[i].nIdxKey = 0;
		g_Player.motion[i].nLoop = 0;
		g_Player.motion[i].nNumKey = 0;
		g_Player.motion[i].nFrameCnt = 0;

		for (int j = 0; j < AMOUNT_PLAYER_KEY; j++)
		{
			g_Player.motion[i].key[j].nFrame = 0;

			for (int k = 0; k < AMOUNT_PLAYER_PARTS; k++)
			{
				g_Player.motion[i].key[j].parts[k].posGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_Player.motion[i].key[j].parts[k].rotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}
	g_Player.nNowMotion = PlayerMotionStateNormal;
	g_Player.nOldMotion = PlayerMotionStateNormal;
	/* AABB���N���A */
	g_Player.aabb.min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aabb.max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e��ݒ�
	SetInfoShadow(20.0f, &g_Player.pos);

	//���f���p�[�c�̐ݒ�
	SetInfoParts(mode);

	//���[�V�����̐ݒ�
	SetInfoMotion(mode);

	//�����蔻�������
	if (mode != MODE_TITLE)
	{
		UpdatePlayerAABB(g_Player.pos);
		//SetSizeVisible_Rect(g_Player.aabb, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), &g_Player.pos);
	}
}

//************************************************
//���f���p�[�c����ݒ�
//************************************************
void SetInfoParts(int mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�p�[�c�p����ݒ�
	FILE* pFile = NULL;
	char sPlayerModel[64] = {};
	int ReadMode = 0;

	if (mode == MODE_TITLE)
	{
		ReadMode = 0;
	}
	else
	{
		ReadMode = 1;
	}

	//�p�[�c�ԃI�t�Z�b�g�̓Ǎ���
	if (fopen_s(&pFile, g_sFileNameParts[ReadMode], "r") != 0) return;

	/* ���f���p�[�c�̑����ȏニ�[�v�ŏI�� */
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		fscanf_s(pFile, "%f %f %f", &g_Player.aParts[i].pos.x, &g_Player.aParts[i].pos.y, &g_Player.aParts[i].pos.z);
		fscanf_s(pFile, "%f %f %f", &g_Player.aParts[i].rot.x, &g_Player.aParts[i].rot.y, &g_Player.aParts[i].rot.z);
		fscanf_s(pFile, "%d", &g_Player.aParts[i].nIdxParent);

		//g_Player.aParts[i].pos.y *= 50.0f;
	}

	fclose(pFile);

	/**********************************************************/

	//X�t�@�C���̓ǂݍ���
	if (fopen_s(&pFile, "data\\txt\\playermodel.txt", "r") != 0) return;

	int i = 0;

	/* �t�@�C���̏I�[�ɒ������A���f���p�[�c�̑����ȏニ�[�v�ŏI�� */
	while (fscanf_s(pFile, "%s", &sPlayerModel[0], 64) != EOF || i < AMOUNT_PLAYER_PARTS)
	{
		D3DXLoadMeshFromX(&sPlayerModel[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aParts[i].pBuffMatPlayer,
			NULL,
			&g_Player.aParts[i].dwNumMatPlayer,
			&g_Player.aParts[i].pMeshPlayer);

		i++;
	}

	fclose(pFile);

	/**********************************************************/

	for (int j = 0; j < AMOUNT_PLAYER_PARTS; j++)
	{
		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_Player.aParts[j].pBuffMatPlayer->GetBufferPointer();

		//���̃p�[�c�̎��}�e���A������
		for (int k = 0; k < (int)g_Player.aParts[j].dwNumMatPlayer; k++)
		{
			//coldef[j][k] = pMat[k].MatD3D.Diffuse;

			//�}�e���A���Ƀe�N�X�`�����ݒ肳��Ă���ΓǍ���
			if (pMat[k].pTextureFilename != NULL)
			{
				char* sFileName = pMat[k].pTextureFilename;

				D3DXCreateTextureFromFileA(pDevice,
					sFileName,
					&g_Player.aParts[j].pTexture);
			}
			else
			{
				g_Player.aParts[j].pTexture = NULL;
			}
		}
	}
}

//************************************************
//���[�V��������ݒ�(�v���P)
//************************************************
void SetInfoMotion(int mode)
{
	//���[�V�����p����ݒ�
	FILE* pFile = NULL;
	char sPlayerMotion[128] = {};
	int ReadMode = 0;

	if (mode == MODE_TITLE)
	{
		ReadMode = 0;
	}
	else
	{
		ReadMode = 1;
	}

	if (fopen_s(&pFile, g_sFileNameMotion[ReadMode], "r") == 0)
	{
		int i = 0;	/* nStyle�Ǘ� */

		/* �t�@�C���̏I�[�ɒ����܂Ń��[�v */
		while (fscanf_s(pFile, "%s", &sPlayerMotion[0], 128) != EOF)
		{
			if (strcmp(&sPlayerMotion[0], "LOOP") == 0)
			{
				fscanf_s(pFile, "%s %d", &sPlayerMotion[0], 64, &g_Player.motion[i].nLoop);
			}
			if (strcmp(&sPlayerMotion[0], "NUM_KEY") == 0)
			{
				fscanf_s(pFile, "%s %d", &sPlayerMotion[0], 64, &g_Player.motion[i].nNumKey);

				/* �L�[�����擾�����̂ŁA�L�[�����̃t���[�����擾 */
  				for (int j = 0; j < g_Player.motion[i].nNumKey; fscanf_s(pFile, "%s", &sPlayerMotion[0], 128))
				{
					if (strcmp(&sPlayerMotion[0], "FRAME") == 0)
					{
						fscanf_s(pFile, "%s %d", &sPlayerMotion[0], 64, &g_Player.motion[i].key[j].nFrame);

						/* �t���[�������擾�����̂ŁA�p�[�c�����̖ړI�n���擾 */
						for (int k = 0; k < AMOUNT_PLAYER_PARTS; fscanf_s(pFile, "%s", &sPlayerMotion[0], 128))
						{
							if (strcmp(&sPlayerMotion[0], "POS") == 0)
							{
								fscanf_s(pFile, "%s %f %f %f", &sPlayerMotion[0], 64, &g_Player.motion[i].key[j].parts[k].posGoal.x, &g_Player.motion[i].key[j].parts[k].posGoal.y, &g_Player.motion[i].key[j].parts[k].posGoal.z);
								fscanf_s(pFile, "%s", &sPlayerMotion[0], 64);
								fscanf_s(pFile, "%s %f %f %f", &sPlayerMotion[0], 64, &g_Player.motion[i].key[j].parts[k].rotGoal.x, &g_Player.motion[i].key[j].parts[k].rotGoal.y, &g_Player.motion[i].key[j].parts[k].rotGoal.z);

								k++;
							}
						}

						j++;

						/* �S�ẴL�[��ǂݍ��ނƁA���̃��[�V������ǂݍ��� */
						if (j >= g_Player.motion[i].nNumKey)
						{
							i++;

							if(ReadMode == 0)
							{
								if (i > 1) break;
							}
							else if (ReadMode == 1)
							{
								if (i > PlayerMotionStateMax) break;
							}
						}
					}
				}
			}
		}
	}

	if (pFile != NULL)
	{
		fclose(pFile);
	}
}

//************************************************
//�v���C���[�j��
//************************************************
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		if (g_Player.aParts[i].pTexture != NULL)
		{
			g_Player.aParts[i].pTexture->Release();
			g_Player.aParts[i].pTexture = NULL;
		}
	}

	//�}�e���A���̔j��
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		if (g_Player.aParts[i].pBuffMatPlayer != NULL)
		{
			g_Player.aParts[i].pBuffMatPlayer->Release();
			g_Player.aParts[i].pBuffMatPlayer = NULL;
		}
	}

	//���b�V���̔j��
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		if (g_Player.aParts[i].pMeshPlayer != NULL)
		{
			g_Player.aParts[i].pMeshPlayer->Release();
			g_Player.aParts[i].pMeshPlayer = NULL;
		}
	}
}

//************************************************
//�v���C���[�X�V
//************************************************
void UpdatePlayer(int mode)
{
	if (mode != MODE_TITLE)
	{
		g_Player.bATK = false;

		if (g_Player.bMUKIMUKI)
		{
			//g_bDef = false;

			//���L���L�J���t��
			MUKIMUKI_Colorful();

			if (!g_bOnceRosalia)
			{
				g_bOnceRosalia = true;
				PlaySound(SOUND_LABEL_ROSALIA);
			}

			SetVibration(1, 65535);

			g_nDecrease++;

			if (g_nDecrease >= 2)
			{
				g_nDecrease = 0;
				g_Player.nEnegy--;
			}

			if (g_Player.nEnegy <= 0)
			{
				g_Player.bMUKIMUKI = false;
			}
		}
		else
		{
			if (g_Player.nState != PlayerStateDamage)
			{
				//�f�t�H���g�J���[��
				//g_bDef = true;
			}

			if (g_bOnceRosalia)
			{
				g_bOnceRosalia = false;
				StopSound(SOUND_LABEL_ROSALIA);
			}
		}

		//��e�m�F�̏���
		if (g_Player.nState == PlayerStateDamage) TakesDamagePlayer();

		//�ߋ��̈ʒu���L�^
		g_Player.posOld = g_Player.pos;

		//�L���p��
		if (g_Player.nCapacity < AMOUNT_CAPACITY)
		{
			if (!g_Player.bMUKIMUKI)
			{
				g_Player.nCapacity++;
				g_Player.nCapacity *= 1.075f;
			}
			else
			{
				g_Player.nCapacity++;
				g_Player.nCapacity *= 1.15f;
			}
		}

		if (g_Player.nEnegy >= AMOUNT_ENEGY)
		{
			g_Player.bMUKIMUKI = true;
		}

		//�e����
		if (GetKeyboardPress(DIK_SPACE) || GetPressTriggerButtonR())
		{
			if (g_Player.nCapacity >= AMOUNT_USING_CAPACITY)
			{
				/* 1,�v���C���[�̌������J�������ʕ����� */
				//const Camera* pCamera = GetInfoCamera();
				//g_Player.rotGoal.y = pCamera->rot.y;

				/* 2.�e�ۂ𔭎� */
				SetInfoBullet();

				if (mode == MODE_GAME)
				{
					if (!g_Player.bMUKIMUKI)
					{
						g_Player.nCapacity -= AMOUNT_USING_CAPACITY;
					}
					else
					{
						g_Player.nCapacity -= AMOUNT_USING_CAPACITY * 0.8;
					}
				}

				PlaySound(SOUND_LABEL_ATK);
			}

			//�U��������o��
			g_Player.bATK = true;
		}

		//�U�����Ă��āA��e���Ă��Ȃ���΂����ōU�����[�V����
		if (g_Player.bATK && g_Player.nState != PlayerStateDamage)
		{
			g_Player.nState = PlayerStateAtk;
			g_Player.nNowMotion = PlayerMotionStateAtk;
		}
		//�U�����Ă��Ȃ��āA��e���Ă��Ȃ���΂����Œʏ탂�[�V������
		else if (!g_Player.bATK && g_Player.nState != PlayerStateDamage)
		{
			g_Player.nState = PlayerStateNormal;
			g_Player.nNowMotion = PlayerMotionStateNormal;
		}

		//�ړ�
		if (MovePlayer() && g_Player.nState != PlayerStateAtk)
		{
			//��e���Ă��Ȃ���΂������ňړ����[�V����
			if (g_Player.nState != PlayerStateDamage)
			{
				g_Player.nNowMotion = PlayerMotionStateMove;
			}
		}

		//��]
		MoveRotatePlayer();

		////�W�����v
		//if (g_Player.nState != PlayerStateJump && JumpPlayer())
		//{
		//	g_Player.nState = PlayerStateJump;
		//	g_Player.nNowMotion = PlayerStateJump;
		//}

		////���n
		//if (g_Player.nState == PlayerStateJump && LandPlayer())
		//{
		//	g_Player.nState = PlayerStateNormal;
		//	g_Player.nNowMotion = PlayerStateLand;
		//}

		//AABB�X�V
		UpdatePlayerAABB(g_Player.pos);

		//�����蔻��
		CollisionWall();
		//CollisionModel();

		/* �U�����[�V�����Đ� */
		if (GetKeyboardTrigger(DIK_M))
		{
			if (g_Player.nNowMotion != PlayerStateAtk)
			{
				g_Player.nState = PlayerStateAtk;
				g_Player.nNowMotion = PlayerMotionStateAtk;
			}
		}

		PrintDebugProc("�v���C���[�̍��W�F( %f, %f, %f, )\n", g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);	
		PrintDebugProc("�v���C���[�̈ړ��ʁF( %f, %f, %f, )\n", g_Player.move.x, g_Player.move.y, g_Player.move.z);
	}

	//���[�V�����Đ�
	MotionPlayer();
}

//************************************************
//�v���C���[�ړ�
//************************************************
bool MovePlayer(void)
{
	bool bMove = false;

	//�J�����̌����ɑ΂��Đi�s�������\���ɕς���
	Camera* pCamera = GetInfoCamera();

	float X = 0.0f;
	float Z = 0.0f;

	if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT))
	{
		X = -1.0f;
	}
	if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT))
	{
		X = 1.0f;
	}
	if (GetKeyboardPress(DIK_W) || GetJoypadPress(JOYKEY_UP))
	{
		Z = 1.0f;
	}
	if (GetKeyboardPress(DIK_S) || GetJoypadPress(JOYKEY_DOWN))
	{
		Z = -1.0f;
	}

	//��������͂��Ă���Έړ����Ă��锻��
	if (X != 0.0f || Z != 0.0f)
	{
		bMove = true;
	}

	if (bMove)
	{
		//�ړ��ʂƖڕW���p��ݒ�
		if (!g_Player.bATK)
		{
			g_Player.move.x += sinf(atan2f(X, Z) + pCamera->rot.y);
			g_Player.move.z += cosf(atan2f(X, Z) + pCamera->rot.y);
		}

		if (g_Player.bMUKIMUKI)
		{
			g_Player.move.x += sinf(atan2f(X, Z) + pCamera->rot.y);
			g_Player.move.z += cosf(atan2f(X, Z) + pCamera->rot.y);
		}

		if (g_Player.nState != PlayerStateDamage)
		{
			g_Player.rotGoal.y = atan2f(X, Z) + pCamera->rot.y;
		}
	}

	g_Player.move *= SPD_STOPMOVE_PLAYER;	//�u���[�L

	//������x�ړ��ʂ����Ȃ���0�����Ă���
	if (g_Player.move.x < EPSILON && g_Player.move.x > -EPSILON) g_Player.move.x = 0.0f;
	if (g_Player.move.y < EPSILON && g_Player.move.y > -EPSILON) g_Player.move.y = 0.0f;
	if (g_Player.move.z < EPSILON && g_Player.move.z > -EPSILON) g_Player.move.z = 0.0f;

	g_Player.pos += g_Player.move * SPD_MOVE_PLAYER;	//�ړ�

	//�W�����v���Ă�Ȃ�d��
	//if (g_Player.nState == PlayerStateJump) g_Player.move.y = g_Player.move.y - 3.0f;

	return bMove;
}

//************************************************
//�v���C���[��]
//************************************************
void MoveRotatePlayer(void)
{
	////�v���C���[����]
	//if (GetKeyboardPress(DIK_Z))
	//{
	//	g_Player.rotGoal.y -= 0.1f;

	//	if (g_Player.rotGoal.y <= -D3DX_PI) g_Player.rotGoal.y = D3DX_PI;
	//}
	//else if (GetKeyboardPress(DIK_C))
	//{
	//	g_Player.rotGoal.y += 0.1f;

	//	if (g_Player.rotGoal.y >= D3DX_PI) g_Player.rotGoal.y = -D3DX_PI;
	//}

	//�u���[�L��
	float StopEnergy = 0.1f;

	//��̗}�~��
	//float fStop = 1.0f;
	//if (g_Player.bATK)
	//{
	//	fStop = 0.2f;
	//}

	//��]�u���[�L
	if (g_Player.rotGoal.y - g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y += ((g_Player.rotGoal.y - g_Player.rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_Player.rotGoal.y - g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += ((g_Player.rotGoal.y - g_Player.rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_Player.rot.y += ((g_Player.rotGoal.y - g_Player.rot.y) * StopEnergy);
	}
}

//************************************************
//�v���C���[�W�����v
//************************************************
bool JumpPlayer(void)
{
	bool bJump = false;

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		g_Player.move.y += 200.0f;

		bJump = true;
	}

	return bJump;
}

//************************************************
//�v���C���[���n
//************************************************
bool LandPlayer(void)
{
	bool bLand = false;

	if (g_Player.pos.y < 0.0f)
	{
		g_Player.pos.y = 0.0f;
		g_Player.move.y = 0.0f;

		bLand = true;
	}

	return bLand;
}

//************************************************
//�v���C���[��e
//************************************************
void TakesDamagePlayer(void)
{
	//���G����
	if (g_Player.nCntState > 0)
	{
		g_Player.nCntState--;
		g_Player.nCapacity = 0;
		g_Player.col.a *= -1.0f;
		g_Player.rot.y++;
		g_Player.nNowMotion = PlayerMotionStateJump;
	}
	//��������Ƃ�
	else
	{
		g_Player.nState = PlayerStateNormal;
		g_Player.col.a = 1.0f;
	}
}

//************************************************
//�v���C���[AABB�X�V
//************************************************
void UpdatePlayerAABB(D3DXVECTOR3 pos)
{
	g_Player.aabb.min =
	{
		pos.x - 15.0f,
		pos.y,
		pos.z - 15.0f
	};

	g_Player.aabb.max =
	{
		pos.x + 15.0f,
		pos.y + 70.0f,
		pos.z + 15.0f
	};
}

//************************************************
//�v���C���[���[�V�����Ǘ�
//************************************************
void MotionPlayer(void)
{
	PlayerMotionSet* Motion = &g_Player.motion[g_Player.nNowMotion];

	//���[�V�����ɕύX�����邩���m
	MotionChangePlayer();

	//�p�[�c�̈ړ����]
	MotionMovePlayer(Motion);

	//���[�V�����p�̌o�߃J�E���g
	MotionCountPlayer(Motion);
}

//************************************************
//���[�V�����ύX
//************************************************
void MotionChangePlayer(void)
{
	/* ���[�V�������ύX����Ă���� */
	if (g_Player.nOldMotion != g_Player.nNowMotion)
	{
		//�L�[�ƃt���[���J�E���g���Z�b�g
		g_Player.motion[g_Player.nOldMotion].nFrameCnt = 0;
		g_Player.motion[g_Player.nOldMotion].nIdxKey = 0;

		//�V�������[�V�������Đ��������Ƃ�ۑ�
		g_Player.nOldMotion = g_Player.nNowMotion;
	}
}

//************************************************
//���[�V�����p�ړ�
//************************************************
void MotionMovePlayer(const PlayerMotionSet* Motion)
{
	/* �c�H(�p����) */
	//float fFrame = (float)(Motion->key[Motion->nIdxKey].nFrame);
	float fFrame = (float)(Motion->key[Motion->nIdxKey].nFrame - Motion->nFrameCnt);

	//�ڕW�ƌ��݂̍��𖄂߂Ă���
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		g_Player.aParts[i].posM += (Motion->key[Motion->nIdxKey].parts[i].posGoal - g_Player.aParts[i].posM) / fFrame;
		g_Player.aParts[i].rotM += (Motion->key[Motion->nIdxKey].parts[i].rotGoal - g_Player.aParts[i].rotM) / fFrame;
	}
}

//************************************************
//���[�V�����p�J�E���g
//************************************************
void MotionCountPlayer(PlayerMotionSet* Motion)
{
	Motion->nFrameCnt++;	/* �t���[����i�߂� */

	if (Motion->nFrameCnt >= Motion->key[Motion->nIdxKey].nFrame)	/* ���v�t���[�������o�߂� */
	{
		if (g_Player.nNowMotion == PlayerMotionStateAtk && Motion->nIdxKey > 5)
		{
			Motion->nFrameCnt = 0;
			Motion->nIdxKey = 4;
		}

		Motion->nFrameCnt = 0;
		Motion->nIdxKey++;		/* �L�[��i�߂� */

		if (Motion->nIdxKey >= Motion->nNumKey)	/* ���v�L�[���o�߂� */
		{
			if (Motion->nLoop == 1)
			{
				Motion->nIdxKey = 0;
				return;
			}

			g_Player.nNowMotion = PlayerMotionStateNormal;
		}
	}
}

//************************************************
//�v���C���[�`��
//************************************************
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;	//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�����𔽉f1
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_Player.rot.y,
		g_Player.rot.x,
		g_Player.rot.z);

	//�����𔽉f2
	D3DXMatrixMultiply(&g_Player.mtxWorld,
		&g_Player.mtxWorld,
		&mtxRot);

	//�ʒu�𔽉f1
	D3DXMatrixTranslation(&mtxTrans,
		g_Player.pos.x,
		g_Player.pos.y,
		g_Player.pos.z);

	//�ʒu�𔽉f2
	D3DXMatrixMultiply(&g_Player.mtxWorld,
		&g_Player.mtxWorld,
		&mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aParts[i].mtxWorld);

		//���[�V���������̔��f
		D3DXVECTOR3 PartsRot =
		{
			g_Player.aParts[i].rot.x + g_Player.aParts[i].rotM.x,
			g_Player.aParts[i].rot.y + g_Player.aParts[i].rotM.y,
			g_Player.aParts[i].rot.z + g_Player.aParts[i].rotM.z
		};

		//�����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			PartsRot.y,
			PartsRot.x,
			PartsRot.z);

		//�����𔽉f2
		D3DXMatrixMultiply(&g_Player.aParts[i].mtxWorld,
			&g_Player.aParts[i].mtxWorld,
			&mtxRot);

		//���[�V�����ʒu�̔��f
		D3DXVECTOR3 PartsPos =
		{
			g_Player.aParts[i].pos.x + g_Player.aParts[i].posM.x,
			g_Player.aParts[i].pos.y + g_Player.aParts[i].posM.y,
			g_Player.aParts[i].pos.z + g_Player.aParts[i].posM.z
		};

		//�ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			PartsPos.x,
			PartsPos.y,
			PartsPos.z);

		//�ʒu�𔽉f
		D3DXMatrixMultiply(&g_Player.aParts[i].mtxWorld,
			&g_Player.aParts[i].mtxWorld,
			&mtxTrans);

		D3DXMATRIX mtxParent = {};

		//�e�̃��[���h�}�g���b�N�X���擾
		if (g_Player.aParts[i].nIdxParent == -1)
		{
			mtxParent = g_Player.mtxWorld;
		}
		else
		{
			mtxParent = g_Player.aParts[g_Player.aParts[i].nIdxParent].mtxWorld;
		}

		//�p�[�c���Ƃ̃��[���h�}�g���b�N�X���Z�o
		D3DXMatrixMultiply(&g_Player.aParts[i].mtxWorld,
			&g_Player.aParts[i].mtxWorld,
			&mtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aParts[i].mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aParts[i].pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aParts[i].dwNumMatPlayer; nCntMat++)
		{
			//�J���`�F��
			if (g_Player.bMUKIMUKI)
			{
				pMat[nCntMat].MatD3D.Diffuse = g_Player.col;
			}

			//if (g_bDef)
			//{
			//	pMat[nCntMat].MatD3D.Diffuse = coldef[i][nCntMat];
			//}

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			if (g_Player.aParts[i].pTexture != NULL)
			{
				pDevice->SetTexture(0, g_Player.aParts[i].pTexture);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			//���f���p�[�c�̕`��
			g_Player.aParts[i].pMeshPlayer->DrawSubset(nCntMat);
		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//************************************************
//�v���C���[�����擾
//************************************************
Player* GetInfoPlayer(void)
{
	return &g_Player;
}

//************************************************
//���L���L�J���t�����[�h
//************************************************
void MUKIMUKI_Colorful(void)
{
	g_nMUKIMUKI_Colorful_CT++;

	switch (g_nMUKIMUKI_Colorful_CT)
	{
	case 0:
		g_Player.col = { 1.0f, 0.0f, 0.0f, 1.0f };
		break;

	case 1:
		g_Player.col = { 0.0f, 1.0f, 0.0f, 1.0f };
		break;

	case 2:
		g_Player.col = { 0.0f, 0.0f, 1.0f, 1.0f };
		break;

	case 3:
		g_Player.col = { 1.0f, 1.0f, 0.0f, 1.0f };
		break;

	case 4:
		g_Player.col = { 1.0f, 0.0f, 1.0f, 1.0f };
		break;

	case 5:
		g_Player.col = { 0.0f, 1.0f, 1.0f, 1.0f };
		g_nMUKIMUKI_Colorful_CT = -1;
		break;
	}
}