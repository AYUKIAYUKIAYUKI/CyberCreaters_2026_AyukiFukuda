//************************************************
//
// �{�X����[boss.cpp]
// Author�F�����h��
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "boss.h"
#include "boss_bullet.h"
#include "bullet.h"
#include "collision.h"
#include "explosion.h"
#include "object.h"
#include "player.h"
#include "player_count.h"
#include "visible_sph.h"
#include "shadow.h"
// ����
#include "game.h"
#include "input.h"
#include "sound.h"

#include <stdlib.h>
#include <time.h>

// ������
#include "enemy.h"
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif	// _DEBUG

// �}�N����`
#define MAX_DATA			(10)		// �����_���ŏo�����l�i�[�p
#define STAGE_SIZE			(2000.0f)	// �t�B�[���h�̑傫��

/*/ �O���[�o���ϐ� /*/
BOSSModel g_BossModel[AMOUNT_BOSS_PARTS];					// �{�X�p���f�����̂ЂȌ`
BossMotion g_BossMotion[NUM_MOTION];						// �{�X���[�V�������̂ЂȌ`
BOSS g_aBoss[MAX_BOSS];										// �{�X���
int g_nCntStop = 0;											// �����Ȃ������鎞��
int g_nCntRot = 0;											// �ǂ��������ɐi�ނ������߂�
int g_nCntPattern = 0;										// �s���p�^�[����ς��邽�߂̃t���[����
int g_nBulletType[MAX_DATA] = {};							// �{�X�̒e�̋���(�����O)
int g_nBulletNum[MAX_DATA] = {};							// �{�X�̒e�̋���(������)
int g_nAdjustTime = 0;										// �e�̋��������߂�^�C�~���O
int g_nSetBulletTime = 0;									// �ړ����ɒe�𔭎˂�����^�C�~���O
int g_nBulletTime = 0;										// �{�X����e�����Ă��Ȃ��Ƃ��̒e�𔭎˂�����^�C�~���O
int g_nMidBossActionChoice = 0;								// ���{�X�̋��������߂�^�C�~���O
int g_nbossActionPatterns = 0;								// ���{�X�̍s���p�^�[���i�[�p
int g_nMidBossBullet = 0;									// ���{�X���e�𔭎˂�����^�C�~���O
int g_nCntTeleport = 0;										// �e���|�[�g������^�C�~���O
int g_nTimeMidBossExplosion = 0;							// ���{�X�����񂾂��Ɣ���������^�C�~���O
int g_nTimeBigBossExplosion = 0;							// ��{�X�����񂾂��Ɣ���������^�C�~���O
int g_nTeleportLate = 0;									// �{�X���e���|�[�g������̎���
int g_nMidBossPhase = 0;									// ���{�X�̃t�F�[�Y
D3DXVECTOR3 g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���{�X�̈ړ���
D3DXVECTOR3 g_BigBossMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��{�X�̈ړ���
D3DXVECTOR3 g_TeleportPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���{�X�̃e���|�[�g��̍��W

float g_fStartHP = 0;										// �{�X�̏o������HP
float g_fRestHP = 0;										// �{�X�̎c��HP

bool g_bStateChange = false;								// ��{�X����ԕω��������ǂ���
bool g_bBigBossUse = false;									// ��{�X�������Ă��邩�ǂ���

int g_nCntPlayer = 0;										// �Q�[���̎Q���l��

/*---�y�v���g�^�C�v�錾�z---*/
void SetSizePartsRadBoss();			// �e�p�[�c�̔���T�C�Y���Z�b�g
void UpdatePartsRadBoss(int id);	// �e�p�[�c�̔�����X�V

//************************************************
// �{�X����
//************************************************
void InitBoss(void)
{

	//�O���[�o���ϐ��̏�����
	g_nCntStop = 0;									// �G�̃X�^������
	g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���{�X�̉��Z������ړ���
	g_BigBossMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��{�X�̉��Z������ړ���
	g_nCntRot = 0;									// �ǂ��������ɐi�ނ������߂�p�̕ϐ�
	g_fStartHP = 0.0f;								// �{�X�̏o������HP
	g_fRestHP = 0.0f;								// �{�X�̎c��HP	
	g_bStateChange = false;							// �{�X����ԕω��������ǂ���
	g_nCntPattern = 0;								// �s���p�^�[����ς��邽�߂̃t���[����
	g_nAdjustTime = 0;								// �{�X�̒e�̋��������߂�^�C�~���O
	g_nSetBulletTime = 0;							// �{�X�̈ړ����ɒe�𔭎˂�����^�C�~���O
	g_bBigBossUse = false;							// ��{�X�������Ă��邩�ǂ���
	g_nBulletTime = 0;								// �{�X����e���Ă��Ȃ��Ƃ��ɒe�𔭎˂�����^�C�~���O
	g_nCntPlayer = 0;								// �v���C�l��
	g_nMidBossActionChoice = 0;						// ���{�X�̋����𒊑I������^�C�~���O
	g_nbossActionPatterns = 0;						// ���{�X�̍s���p�^�[���i�[�p
	g_nMidBossBullet = 0;							// ���{�X���e�𔭎˂�����^�C�~���O
	g_nCntTeleport = 0;								// �e���|�[�g������^�C�~���O
	g_nTimeMidBossExplosion = 0;					// ���{�X�����񂾂��Ɣ��������鎞��
	g_nTimeBigBossExplosion = 0;					// ��{�X�����񂾂��Ɣ��������鎞��
	g_TeleportPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���{�X�̃e���|�[�g��̍��W
	g_nTeleportLate = 0;							// ���{�X���e���|�[�g������̎���
	g_nMidBossPhase = 0;							// ���{�X�̃t�F�[�Y

	// �v���C�l���̎擾
	g_nCntPlayer = ReturnSelectPlayerCount() + 1;

	for (int i = 0; i < MAX_DATA; i++)
	{
		g_nBulletType[i] = {};								// �{�X�̒e�̋���(�����O)
		g_nBulletNum[i] = {};								// �{�X�̒e�̋���(������)
	}

	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{ // �{�X�p���f�����̂ЂȌ`�̃��Z�b�g
		BOSSModel* pModel = &g_BossModel[i];

		// �X�^�C��
		pModel->style = 0;

		// ���f��
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;

		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // �}�e���A��
			pModel->pTex[j] = NULL;
		}

		// ���f�����W
		pModel->pos_offset = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �e�C���f�b�N�X
		pModel->IdxParent = -1;
	}

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_BOSS; i++)
	{ // �{�X���̃��Z�b�g
		BOSS* pBoss = &g_aBoss[i];

		// �g�p�t���O
		pBoss->use = false;

		// �p�����[�^
		pBoss->Param.style = 0;								//�ԍ�
		pBoss->Param.state = stateNormal_b;					//���
		pBoss->Param.dur = 0;								//HP���Ȃ��Ȃ��Ă���`�悳��Ȃ��Ȃ�܂ł̎���
		pBoss->Param.HP = 0;								//���C�t
		pBoss->Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		//pBoss->Param.Radius = 0.0f;							//�����蔻��̔��a
		pBoss->Param.motion_now = 0;						//���Đ����̃��[�V����
		pBoss->Param.motion_old = 0;						//1�O�ɍĐ�����Ă������[�V����
		//pBoss->Param.bMove = true;							//�ړ����Ă��邩�ǂ���

		// ���W
		pBoss->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBoss->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �F
		pBoss->col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		for (int j = 0; j < AMOUNT_BOSS_PARTS; j++)
		{ // �e�p�[�c�������Z�b�g
			BOSSModel* pModel = &pBoss->parts[j];

			// ���f��
			pModel->pMesh = NULL;
			pModel->pBuffMat = NULL;
			pModel->NumMat = 0;

			for (int k = 0; k < AMOUNT_MAT; k++)
			{ // �}�e���A��
				pModel->pTex[k] = NULL;
			}

			// ���f�����W
			pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �e�C���f�b�N�X
			pModel->IdxParent = -1;

			// ����p�������Z�b�g
			pBoss->rad[j] = 0.0f;
			pBoss->pos_sph[j] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pBoss->id_sph[j] = -1;
		}

		pBoss->id_shadow = -1;
	}

	/*--------------------------------------------*/

	// �{�X�p�̃��f�������擾
	ImportModelBoss();

	// �{�X�p�̃��[�V���������擾
	ImportMotionBoss();

	// �{�X�p�̃p�����[�^�����擾
	ImportParamBoss();

	/*---�y���[�V���������R�s�[(�C���\��)�z---*/
	for (int i = 0; i < MAX_BOSS; i++)
	{
		for (int j = 0; j < NUM_MOTION; j++)
		{
			if (g_BossMotion[j].amount_key == 0)
			{ // ���g�p�Ȃ�R���e�B�j���[
				continue;
			}

			// ���[�V���������R�s�[
			g_aBoss[i].motion[j] = g_BossMotion[j];
		}


	}

	for (int i = 0; i < MAX_BOSS; i++)
	{
		g_aBoss[i].Param.bMove = true;		// �ړ����Ă��邩�ǂ���
		g_fStartHP = g_aBoss[i].Param.HP;	// �o������HP��ۑ�����
	}

	// ���{�X�̋����̎Z�o
	g_nbossActionPatterns = rand() % NUM_ACT;

	/******************************/

	/*---�y�����I�ɓG��z�u(�����\��)�z---*/

	//DEBUG_GenerateEnemy();

	/******************************/
}

//************************************************
// ���f������ǂݍ���
//************************************************
void ImportModelBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int AmountModel = 0;		// ���f���̐����i�[
	int id_Model = 0;			// ���f���̎��ʗp

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�{�X���f�����̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &AmountModel);
		}

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%s", &FileString[0], 128);

			// �ǂݍ��񂾏����ЂȌ`�ɂ̂݃R�s�[����
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_BossModel[id_Model].pBuffMat,
				NULL,
				&g_BossModel[id_Model].NumMat,
				&g_BossModel[id_Model].pMesh);

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == AmountModel)
			{ // ���f�������ǂݎ��I���ƏI��
				break;
			}
		}
	}

	// �e���f���̃I�t�Z�b�g�����擾
	ImportOffsetBoss(pFile, AmountModel);

	// �e���f���̃e�N�X�`�������擾
	ImportTexBoss(AmountModel);

	// �t�@�C�������
	fclose(pFile);
}

//************************************************
// ���f���I�t�Z�b�g����ǂݍ���
//************************************************
void ImportOffsetBoss(FILE* pFile, int AmountModel)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	char FileString[128] = {};	// ���͂��i�[
	int Style = -1;				// ���̃p�[�c�̃X�^�C�����i�[
	int IdxParent = -1;			// �e�̃C���f�b�N�X���i�[
	D3DXVECTOR3 pos = {};		// �ʒu�̃I�t�Z�b�g���i�[
	D3DXVECTOR3 rot = {};		// �����̃I�t�Z�b�g���i�[
	int id_Model = 0;			// ���f���̎��ʗp

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // ���̃p�[�c�̃X�^�C�����擾	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &Style);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // �e�̃C���f�b�N�X���擾	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%d", &IdxParent);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu�̃I�t�Z�b�g���擾	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �����̃I�t�Z�b�g���擾	
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARTSSET") == 0)
		{
			// �ǂݍ��񂾏����ЂȌ`�ɂ̂݃R�s�[����
			g_BossModel[id_Model].style = Style;
			g_BossModel[id_Model].IdxParent = IdxParent;
			g_BossModel[id_Model].pos_offset = pos;
			g_BossModel[id_Model].rot_offset = rot;

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == AmountModel)
			{ // ���f�������ǂݎ��I���ƏI��
				break;
			}
		}
	}
}

//************************************************
// ���f���e�N�X�`������ǂݍ���
//************************************************
void ImportTexBoss(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int i = 0; i < AmountModel; i++)
	{
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_BossModel[i].pBuffMat->GetBufferPointer();

		// ���̃p�[�c�̎��}�e���A������
		for (int j = 0; j < (int)g_BossModel[i].NumMat; j++)
		{
			// �}�e���A���Ƀe�N�X�`�����ݒ肳��Ă���ΓǍ���
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_BossModel[i].pTex[j]);
			}
			else
			{
				g_BossModel[i].pTex[j] = NULL;
			}
		}
	}
}

//************************************************
// �G�̃p�����[�^���̓Ǎ���
//************************************************
void ImportParamBoss(void)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};		// ���͂��i�[
	int i = 0;						// �ėp����
	int appear = 0;					// �o���^�C�~���O���i�[
	int style = 0;					// �X�^�C�����i�[
	float hp = 0.0f;				// ���C�t���i�[
	//float radius = 0.0f;			// ���a���i�[(�����蔻��p)
	//float spd = 0;				// ���x���i�[
	D3DXVECTOR3 pos, rot, spd;		// �ʒu�ƌ������i�[

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_param.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�{�X�p�����[�^���̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (i >= MAX_BOSS)
		{ // �G�̍ő吔���z����Ƌ����I��
			break;
		}

		if (strcmp(&FileString[0], "APPEAR") == 0)
		{ // �o���^�C�~���O���擾
			fscanf_s(pFile, "%s %d", &FileString[0], 64, &appear);
		}

		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // �X�^�C�����擾
			fscanf_s(pFile, "%s %d", &FileString[0], 64, &style);
		}

		if (strcmp(&FileString[0], "HP") == 0)
		{ // ���C�t���擾
			fscanf_s(pFile, "%s %f", &FileString[0], 64, &hp);
		}

		if (strcmp(&FileString[0], "SPD") == 0)
		{ // ���x���擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &spd.x, &spd.y, &spd.z);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu���擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �������擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 64, &rot.x, &rot.y, &rot.z);
		}

		//if (strcmp(&FileString[0], "RADIUS") == 0)
		//{ // �����蔻����擾
		//	fscanf_s(pFile, "%s %f", &FileString[0], 64, &radius);
		//}

		if (strcmp(&FileString[0], "END_PARAMSET") == 0)
		{ // �擾�������𔽉f
			g_aBoss[i].Param =
			{
				appear, style, 0, 0, hp,spd,/*radius*/
			};

			g_aBoss[i].pos = pos;
			g_aBoss[i].rot = rot;

			i++;	// ���̔ԍ���
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{
			break;	// �I��
		}
	}

	// �G�̊e�p�[�c�̔���T�C�Y���G�ɐݒ�
	SetSizePartsRadBoss();
}

//************************************************
// �e�p�[�c�̔���T�C�Y��ݒ�
//************************************************
void SetSizePartsRadBoss(void)
{
	// ���ɉ����p�ӂ��Ă��Ȃ��̂ŁA�������ݒ�
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		g_aBoss[0].rad[i] = 20.0f;
	}

	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		g_aBoss[1].rad[i] = 40.0f;
	}

	g_aBoss[1].rad[15] = 125.0f;
}

////************************************************
//// �G�̏o���ݒ�
////************************************************
//void DEBUG_GenerateEnemy(void)
//{
//	/*---�y���݁A�����I�ɓG�̏��ݒ�(�C���\��)�z---*/
//	for (int i = 0; i < MAX_BOSS; i++)
//	{
//		// �p�����[�^
//		g_aBoss[i].Param.style = 0;
//		g_aBoss[i].Param.SPD = 0.1f + i * 0.1f;
//
//		g_aBoss[i].use = true;
//		g_aBoss[i].pos = D3DXVECTOR3(5.0f, 0.0f, 0.0f);
//
//		// �X�^�C���ԍ����ƍ�
//		VerifyStyleBOSS(i);
//
//		break;	// 1�̂̂�
//	}
//}

//************************************************
// �X�^�C���ԍ��̏ƍ�
//************************************************
void VerifyStyleBoss(int id)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		if (g_aBoss[id].Param.style == g_BossModel[i].style)
		{ // �e�{�X�̃X�^�C���ƑS�p�[�c�̃X�^�C�����ƍ�
			g_aBoss[id].parts[i] = g_BossModel[i];	//!< �ԍ��̈�v���Ă���p�[�c�̂ݗL����
		}
	}
}

//************************************************
// ���[�V��������ǂݍ���
//************************************************
void ImportMotionBoss(void)
{
	//�t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int i = 0, j = 0, k = 0;	// �ėp����
	int Loop = 0;				// ���[�v�t���O���i�[
	int AmountKey = 0;			// ���L�[�����擾
	int AmountFrame = 0;		// ���t���[�������擾
	D3DXVECTOR3 pos, rot;		// �ʒu�ƌ������i�[

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\BOSS\\boss_motion.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�{�X���[�V�������̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "LOOP") == 0)
		{ // ���[�v�t���O���擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &Loop);
		}

		if (strcmp(&FileString[0], "NUM_KEY") == 0)
		{ // ���L�[�����擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountKey);
		}

		if (strcmp(&FileString[0], "FRAME") == 0)
		{ // �t���[�������擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountFrame);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // ����ʒu���擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // ����������擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_KEY") == 0)
		{ // �p�[�c�������ۑ�
			g_BossMotion[i].key[j].dest[k].pos = pos;
			g_BossMotion[i].key[j].dest[k].rot = rot;

			k++;	// �p�[�c�ԍ���i�߂�
		}

		if (strcmp(&FileString[0], "END_KEYSET") == 0)
		{ // �L�[����ۑ�
			g_BossMotion[i].key[j].amount_frame = AmountFrame;

			k = 0;	// �p�[�c�ԍ������Z�b�g
			j++;	// �L�[�ԍ���i�߂�
		}

		if (strcmp(&FileString[0], "END_MOTIONSET") == 0)
		{ // ���[�V��������ۑ�
			g_BossMotion[i].loop = Loop;
			g_BossMotion[i].amount_key = AmountKey;

			j = 0;	// �L�[�ԍ������Z�b�g
			i++;	// ���[�V�����ԍ���i�߂�
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{ // �I��
			break;
		}
	}

}

//************************************************
// �{�X�j��
//************************************************
void UninitBoss(void)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_BossModel[i].pTex[j] != NULL)
			{ // �e�N�X�`���̔j��
				g_BossModel[i].pTex[j]->Release();
				g_BossModel[i].pTex[j] = NULL;
			}
		}

		if (g_BossModel[i].pMesh != NULL)
		{ // ���b�V���̔j��
			g_BossModel[i].pMesh->Release();
			g_BossModel[i].pMesh = NULL;
		}

		if (g_BossModel[i].pBuffMat != NULL)
		{ // �}�e���A���̔j��
			g_BossModel[i].pBuffMat->Release();
			g_BossModel[i].pBuffMat = NULL;
		}
	}
}

//************************************************
// �{�X�X�V
//************************************************
void UpdateBoss(void)
{
	for (int i = 0; i < MAX_BOSS; i++)
	{
		// �o��
		AppearBoss(i);

		if (!g_aBoss[i].use)
		{// �{�X���g�p����Ă��Ȃ��Ȃ�R���e�B�j���[
			continue;
		}

		if (g_aBoss[i].Param.style == BOSSTYPE_BIG && g_aBoss[i].use)
		{// �{�X�^�C�v����{�X�Ŏg���Ă�����J�E���g�𑝂₷
		}


		// �ߋ��̈ʒu���L�^
		g_aBoss[i].pos_old = g_aBoss[i].pos;

		// ��]
		RotateBoss(i);

		//�ړ�
		MoveBoss();

		/*---�y�V�����e�̒Ǐ]�z---*/
		TrackShadow(g_aBoss[i].id_shadow,
			g_aBoss[i].pos);

		// �e�p�[�c�̔�����X�V
		UpdatePartsRadBoss(i);

		//��e
		DamageBoss(i);

		// �{�X�ƌ����̓����蔻��
		CollisionBoss(i);

		// �{�X�ƃv���C���[�̓����蔻��
		CollisionPlayer(i);

		//�c��HP���Z�o����
		g_fRestHP = g_aBoss[i].Param.HP;

		//���S
		DeadBoss(i);

		// �t�F�[�Y�I����Ƀ{�X������
		DeleteOldBoss(i);

		// ���[�V����
		MotionBoss(i);

	}

	// �Ō�ɍs��v�Z
	CalcMtxBoss();
#ifdef _DEBUG

	PrintDebugProc("���{�X�̍��W : %f %f %f\n", g_aBoss[0].pos.x, g_aBoss[0].pos.y, g_aBoss[0].pos.z);
	PrintDebugProc("���{�X�̌��� : %f %f %f\n", g_aBoss[0].rot.x, g_aBoss[0].rot.y, g_aBoss[0].rot.z);
	PrintDebugProc("���{�X�̌�����ς���^�C�~���O : %d\n", g_nCntRot);
	PrintDebugProc("��{�X�̍��W : %f %f %f\n", g_aBoss[1].pos.x, g_aBoss[1].pos.y, g_aBoss[1].pos.z);
	PrintDebugProc("��{�X�̌��� : %f %f %f\n", g_aBoss[1].rot.x, g_aBoss[1].rot.y, g_aBoss[1].rot.z);
	PrintDebugProc("��{�X�̍s���p�^�[����ς���t���[���� : %d\n", g_nCntPattern);
	PrintDebugProc("���{�X�̍s���p�^�[���𒊑I�����邽�߂̃t���[���� : %d\n", g_nMidBossActionChoice);
	PrintDebugProc("���{�X�̍s���p�^�[�� : %d\n", g_nbossActionPatterns);
	PrintDebugProc("�e���|�[�g������^�C�~���O : %d\n", g_nCntTeleport);
#endif

#ifdef _DEBUG

	for (int i = 0; i < 2; i++)
	{
		BOSS* pBoss = &g_aBoss[i];
		char pStr[8];

		switch (pBoss->Param.state)
		{
		case stateNormal_b:
			snprintf(&pStr[0], 8, "�ʏ�");
			break;

		case stateMove_b:
			snprintf(&pStr[0], 8, "�ړ�");
			break;

		case stateAtk_b:
			snprintf(&pStr[0], 8, "�U��");
			break;

		case stateDamage_b:
			snprintf(&pStr[0], 8, "��e");
			break;

		case stateDead_b:
			snprintf(&pStr[0], 8, "���S");
			break;

		default:

			// �G���[
			assert(false && "�����ꂩ�̃G�l�~�[��ԂɃG���[");

			break;
		}

		PrintDebugProc("�y%dB�z\nstate : %s\n", i + 1, &pStr[0]);	// �X�e�[�^�X
		PrintDebugProc("HP : %f\n", pBoss->Param.HP);				// ���C�t
		PrintDebugProc("SPD : %f\n", pBoss->Param.SPD);				// ���x
	}
#endif
}

//************************************************
// �{�X�o��
//************************************************
void AppearBoss(int id)
{
	int* pPhase = GetInfoPhase();    // �t�F�[�Y�����擾

	if (id == 0)
	{
		if (*pPhase != 2)
		{ // ���{�X�t�F�[�Y�ȊO�̓��^�[��
			return;
		}
	}
	else if (id == 1)
	{
		if (*pPhase != 4)
		{ // ��{�X�t�F�[�Y�ȊO�̓��^�[��
			return;
		}
	}

	if (g_aBoss[id].Param.appear > 0)
	{ // �o���^�C�~���O���ݒ肳��Ă����
		g_aBoss[id].Param.appear--;

		if (g_aBoss[id].Param.appear <= 0)
		{ // �o���^�C�~���O���Ԃɓ��B��
			g_aBoss[id].use = true;

			// �X�^�C���ԍ����ƍ�
			VerifyStyleBoss(id);

			/*---�y�e�𐶐��z---*/
			g_aBoss[id].id_shadow = CreateShadow(40.0f);

#ifdef _DEBUG

			// ���̂Ƃ������蔻�������
			for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
			{
				switch (id)
				{
				case 0:

					if (i > 14)
					{
						continue;
					}

					break;

				case 1:

					if (i <= 14)
					{
						continue;
					}

					break;
				}

				g_aBoss[id].id_sph[i] = CreateVisibleSph(g_aBoss[id].rad[i], D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), &g_aBoss[id].pos_sph[i]);
			}

#endif
		}
	}
}

//************************************************
// �{�X��]
//************************************************
void RotateBoss(int id)
{
	// �u���[�L��
	float StopEnergy = 0.1f;

	// ��]�u���[�L
	if (g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y > D3DX_PI)
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y < -D3DX_PI)
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_aBoss[id].rot.y += ((g_aBoss[id].rot_goal.y - g_aBoss[id].rot.y) * StopEnergy);
	}
}

//************************************************
// �{�X�ړ�
//************************************************
void MoveBoss(void)
{
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{

		switch (g_aBoss[nCntBoss].Param.style)
		{
		case 0:
			MidBossBehavior(nCntBoss);	//���{�X�̋���
			break;
		case 1:
			BigBossBehavior(nCntBoss);	//��{�X�̋���
			break;
		default:
			break;
		}
	}
}

//************************************************
// ���{�X�̋���
//************************************************
void MidBossBehavior(int id)
{
	g_nTeleportLate = 0;

	if (g_aBoss[id].use && g_aBoss[id].Param.state != stateDamage_b && g_aBoss[id].Param.state != stateDead_b)
	{
		g_nMidBossActionChoice++;	// �J�E���g�𑝂₷

		g_aBoss[id].Param.state = stateMove_b;		// �ړ����

		//���������߂�
		g_aBoss[id].rot_goal.y = atan2f(-g_aBoss[id].Param.SPD.x - g_MidBossMove.x, -g_aBoss[id].Param.SPD.z - g_MidBossMove.z);

		if (g_nMidBossActionChoice >= MAX_CHANGEFRAME)
		{
			// �s���p�^�[���̍Ē��I
			g_nbossActionPatterns = rand() % NUM_ACT + 1;

			// �J�E���g��0�ɖ߂�
			g_nMidBossActionChoice = 0;

		}

		for (int nCntParts = 0; nCntParts < AMOUNT_BOSS_PARTS; nCntParts++)
		{
			// �X�e�[�W�O�̔���
			if (g_aBoss[id].pos.x + g_aBoss[id].rad[nCntParts] >= STAGE_SIZE)
			{// �X�e�[�W�̉E�[
				// �s���p�^�[���̍Ē��I
				g_nbossActionPatterns = 7;

				// �J�E���g��0�ɖ߂�
				g_nMidBossActionChoice = 0;

				g_aBoss[id].pos.x = STAGE_SIZE - g_aBoss[id].rad[nCntParts];

			}
			else if (g_aBoss[id].pos.x - g_aBoss[id].rad[nCntParts] <= -STAGE_SIZE)
			{// �X�e�[�W�̍��[
				// �s���p�^�[���̍Ē��I
				g_nbossActionPatterns = 8;

				// �J�E���g��0�ɖ߂�
				g_nMidBossActionChoice = 0;
			}

			if (g_aBoss[id].pos.z + g_aBoss[id].rad[nCntParts] >= STAGE_SIZE)
			{// �X�e�[�W�̉��[
				// �s���p�^�[���̍Ē��I
				g_nbossActionPatterns = 9;

				// �J�E���g��0�ɖ߂�
				g_nMidBossActionChoice = 0;

			}
			else if (g_aBoss[id].pos.z - g_aBoss[id].rad[nCntParts] <= -STAGE_SIZE)
			{// �X�e�[�W�̎�O�[
				// �s���p�^�[���̍Ē��I
				g_nbossActionPatterns = 10;

				// �J�E���g��0�ɖ߂�
				g_nMidBossActionChoice = 0;
			}

		}

		// �s���p�^�[��
		switch (g_nbossActionPatterns)
		{
		case 1:
			//********************************************************************
			// ���x�����߂�
			//********************************************************************
			g_MidBossMove = D3DXVECTOR3(MIDBOSSMOVE, 0.0f, 0.0f);
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;
		case 2:
			//********************************************************************
			// ���x�����߂�
			//********************************************************************
			g_MidBossMove = D3DXVECTOR3(-MIDBOSSMOVE, 0.0f, MIDBOSSMOVE);
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;
		case 3:
			//********************************************************************
			// ���x�����߂�
			//********************************************************************
			g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, -MIDBOSSMOVE);
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;
		case 4:
			//********************************************************************
			// ���x�����߂�
			//********************************************************************
			g_MidBossMove = D3DXVECTOR3(-MIDBOSSMOVE, 0.0f, -MIDBOSSMOVE);
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			break;
		case 5:
			g_aBoss[id].pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);	// �X�e�[�W�̐^��
			g_nCntTeleport++;
			if (g_nCntTeleport >= 30)
			{
				g_aBoss[id].Param.state = stateNormal_b;	// �ʏ��Ԃɂ���

				//********************************************************************
				// ���x�����߂�
				//********************************************************************
				g_nMidBossBullet++;
				if (g_nMidBossBullet % 20 == 0)
				{// 20�t���[����1��e�𔭎˂�����
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, -BULLETMOVEY, 5.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(5.0f, -BULLETMOVEY, 0.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-5.0f, -BULLETMOVEY, 0.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, -BULLETMOVEY, -5.0f), 100.0f);

					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(3.0f, -BULLETMOVEY, 3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(3.0f, -BULLETMOVEY, -3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-3.0f, -BULLETMOVEY, 3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-3.0f, -BULLETMOVEY, -3.0f), 100.0f);
				}
				else if (g_nMidBossBullet % 35 == 0)
				{// 35�t���[����1��e�𔭎˂�����
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(3.0f, -3.2f, 3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(3.0f, -3.2f, -3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-3.0f, -3.2f, 3.0f), 100.0f);
					SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_MIDBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-3.0f, -3.2f, -3.0f), 100.0f);

				}

				g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//g_nCntTeleport = 0;	// �e���|�[�g���Ă���̎��Ԃ����Z�b�g����

			}
			break;
		case 6:
			// �e���|�[�g�p�^�[��
			g_TeleportPos.x = rand() % DATA_RANGE - (float)DATA_ADJUST;
			g_TeleportPos.z = rand() % DATA_RANGE - (float)DATA_ADJUST;
			PlaySound(SOUND_LABEL_TELEPORT);

			g_aBoss[id].pos = D3DXVECTOR3(g_TeleportPos.x, 5.0f, g_TeleportPos.z);

			// �s���p�^�[���̍Ē��I
			g_nbossActionPatterns = rand() % NUM_ACT + 1;
			break;
		case 7:
			// �X�e�[�W�̉E�[�p
			g_MidBossMove = D3DXVECTOR3(-MIDBOSSMOVE, 0.0f, 0.0f);			// �������Ɉړ�����
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 8:
			// �X�e�[�W�̍��[�p
			g_MidBossMove = D3DXVECTOR3(MIDBOSSMOVE, 0.0f, 0.0f);			// �E�����Ɉړ�����
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 9:
			// �X�e�[�W�̉��[�p
			g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, -MIDBOSSMOVE);			// ��O�����Ɉړ�����
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 10:
			// �X�e�[�W�̎�O�[�p
			g_MidBossMove = D3DXVECTOR3(0.0f, 0.0f, MIDBOSSMOVE);			// �������Ɉړ�����
			g_aBoss[id].Param.SPD = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		}

		if (g_aBoss[id].Param.bMove)
		{
			//�ʒu�𓮂���
			g_aBoss[id].pos += g_MidBossMove * 1 + g_aBoss[id].Param.SPD;
		}
	}
}

//************************************************
// ��{�X�̋���
//************************************************
void BigBossBehavior(int id)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �e�̈ړ���
	int nLife = 0;	// �e�̎���


	BulletMove.x = rand() % 5 + (float)1;	// �e�̈ړ��ʂ��Z�o(X���W)
	BulletMove.z = rand() % 5 + (float)1;	// �e�̈ړ��ʂ��Z�o(Z���W)
	nLife = rand() % 50 + 100;		// �e�̎������Z�o

	if (g_aBoss[id].use)
	{ // �t���[�����̉��Z
		g_nCntPattern++;
	}

	if (g_fRestHP < g_fStartHP * 0.4f)
	{// ��{�X��HP��40%�����������
		g_bStateChange = true;
	}

	if (g_nCntPattern <= PATTERN_ZERO)
	{// �J�E���g�𑝂₵�Ă���500�t���[���܂�
		g_BigBossMove.x = 1.5f;			// X�����̈ړ��ʂ𒲐�����
		g_BigBossMove.z = 0.0f;			// Z�����̈ړ��ʂ�0�ɂ���
		g_aBoss[id].Param.SPD.z = 0.0f;	// �p�����[�^�[��Z�����̃X�s�[�h���Ȃ���
	}
	else if (g_nCntPattern <= PATTERN_ONE)
	{// �J�E���g�𑝂₵�Ă���1000�t���[���܂�
		g_BigBossMove.z = 1.0f;			// Z�����̈ړ��ʂ𒲐�����
		g_BigBossMove.x = 0.0f;			// X�����̈ړ��ʂ�0�ɂ���
		g_aBoss[id].Param.SPD.x = 0.0f;	// �p�����[�^�[��X�����̃X�s�[�h���Ȃ���
	}
	else if (g_nCntPattern <= PATTERN_TWO)
	{// �J�E���g�𑝂₵�Ă���1500�t���[���܂�
		g_BigBossMove.x = -1.0f;
		g_BigBossMove.z = 0.0f;
		g_aBoss[id].Param.SPD.z = 0.0f;
	}
	else if (g_nCntPattern <= PATTERN_THREE)
	{
		g_BigBossMove.x = -0.8f;
		g_BigBossMove.z = 0.8f;

	}
	else if (g_nCntPattern <= PATTERN_FOUR)
	{
		g_BigBossMove.x = -1.0f;
		g_BigBossMove.z = -0.5f;
	}
	else if (g_nCntPattern <= PATTERN_FIVE)
	{
		g_nBulletTime++;	//�t���[�������Z������

		if (g_nBulletTime % 50 == 0)
		{
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 8.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, -8.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(8.0f, 0.0f, 0.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-8.0f, 0.0f, 0.0f), 150.0f);
		}

		g_BigBossMove.x = 0.0f;
		g_BigBossMove.z = 0.0f;
		g_aBoss[id].Param.SPD.x = 0.0f;
		g_aBoss[id].Param.SPD.z = 0.0f;

	}
	else if (g_nCntPattern <= PATTERN_SIX)
	{
		g_BigBossMove.x = -1.0f;
		g_BigBossMove.z = -1.0f;
	}
	else if (g_nCntPattern <= PATTERN_SEVEN)
	{
		g_BigBossMove.x = 1.0f;
		g_BigBossMove.z = 0.0f;
		g_aBoss[id].Param.SPD.z = 0.0f;

	}
	else if (g_nCntPattern <= PATTERN_EIGHT)
	{
		g_nBulletTime++;	//�t���[�������Z������

		if (g_nBulletTime % 20 == 0)
		{
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(8.0f, 0.0f, 8.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(8.0f, 0.0f, -8.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(8.0f, 0.0f, -8.0f), 100.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-8.0f, 0.0f, -8.0f), 150.0f);
		}

		g_BigBossMove.x = 0.0f;
		g_BigBossMove.z = 0.0f;
		g_aBoss[id].Param.SPD.x = 0.0f;
		g_aBoss[id].Param.SPD.z = 0.0f;

	}
	else if (g_nCntPattern <= PATTERN_NINE)
	{
		g_BigBossMove.z = -1.5f;
	}
	if (g_nCntPattern > PATTERN_NINE)
	{// 1500�t���[���𒴂�����J�E���g��0�ɖ߂�
		g_nCntPattern = 0;
	}



	if (g_aBoss[id].use && g_aBoss[id].Param.state != stateDamage_b && g_aBoss[id].Param.state != stateDead_b)
	{
		g_nSetBulletTime++;

		if (g_nSetBulletTime % 100 == 0)
		{
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(BulletMove.x, 0.0f, BulletMove.z), (float)nLife);
		}
		g_aBoss[id].Param.state = stateMove_b;		// �ړ����

		//���������߂�
		g_aBoss[id].rot_goal.y = atan2f(-g_aBoss[id].Param.SPD.x - g_BigBossMove.x, -g_aBoss[id].Param.SPD.z - g_BigBossMove.z);

		//if (!g_bStateChange)
		//{//HP��40%�ȏ゠��Ƃ�
		if (g_aBoss[id].Param.bMove)
		{
			g_aBoss[id].pos += g_aBoss[id].Param.SPD + g_BigBossMove;
		}
		//}
		//else
		//{//HP��40%�ȉ������������
			//if (g_aBoss[id].Param.bMove)
			//{//�ړ����x�������グ��
			//	//�ʒu�𓮂���
			//	g_aBoss[id].pos += g_aBoss[id].Param.SPD * 2.0f;

			//}

		//}


		//if (g_aBoss[id].Param.style == BOSSTYPE_BIG)
		//{

		//}

	}


}

//************************************************
// �{�X�̓����蔻��
//************************************************
void HitBoss(int id)
{
	g_aBoss[id].Param.state = stateDamage_b;	// ������Ԃ�
	g_aBoss[id].Param.dur = STANTIME;			// �p�����Ԃ�t�^
	g_aBoss[id].Param.HP--;						// HP�����炷

}

//************************************************
// �{�X�̕�������
//************************************************
void DamageBoss(int id)
{

	if (g_aBoss[id].Param.state != stateDamage_b)
	{ // ������ԂłȂ���ΏI��
		return;
	}

	/*---�y�ȉ�������Ԏ��̂݁z---*/

	// �_��
	g_aBoss[id].col.a *= -1.0f;

	if (g_aBoss[id].Param.style == BOSSTYPE_BIG)
	{
		AdjustBullet(id);
	}

	switch (g_aBoss[id].Param.style)
	{
	case 0:
		if (CntDuration(&g_aBoss[id].Param.dur))
		{//�X�^�����Ԃ��߂�����
			g_aBoss[id].Param.state = stateNormal_b;	// �ʏ��Ԃ�
			g_aBoss[id].col.a = 1.0f;					// �ʏ�F��
			g_nCntRot++;

		}
		break;
	case 1:
		if (CntDuration(&g_aBoss[id].Param.dur))
		{//�X�^�����Ԃ��߂�����
			g_aBoss[id].Param.state = stateMove_b;	// �ړ���Ԃ�

		}
		break;
	}

}

//************************************************
// �{�X�̎��S����
//************************************************
void DeadBoss(int id)
{
	if (g_aBoss[id].Param.state == stateDamage_b && g_aBoss[id].Param.HP <= 0.0f)
	{ // ������Ԃő̗͂������Ƃ��̂�
		g_aBoss[id].Param.state = stateDead_b;	// ���S��Ԃ�
		g_aBoss[id].Param.dur = 180;			// �p�����ԕt�^
		g_aBoss[id].col.a = 0.5f;				// ��������
	}


	if (g_aBoss[id].Param.state != stateDead_b)
	{ // ���S��ԂłȂ���ΏI��
		return;
	}

	if (g_aBoss[id].Param.state == stateDead_b && g_aBoss[id].use)
	{
		switch (g_aBoss[id].Param.style)
		{
		case BOSSTYPE_MID:
			g_nTimeMidBossExplosion++;
			if (g_nTimeMidBossExplosion == MIDBOSS_LATE)
			{
				SetExplosion(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + 50.0f, g_aBoss[id].pos.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), 100.0f, 100.0f);
			}
			break;
		case BOSSTYPE_BIG:
			g_nTimeBigBossExplosion++;
			if (g_nTimeBigBossExplosion == BIGBOSS_LATE)
			{
				SetExplosion(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + 50.0f, g_aBoss[id].pos.z), D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f), 100.0f, 100.0f);
			}
			break;
		}
	}
	/*---�y�ȉ����S��Ԏ��̂݁z---*/

	if (CntDuration(&g_aBoss[id].Param.dur))
	{
		/*---�y�����Ɍ��ꂸ�A�������̗\������邽�߂���Łz---*/
		g_aBoss[id].use = false;	// �g�p�t���O

		/*---�y�e�������z---*/
		DeleteShadow(g_aBoss[id].id_shadow);

		g_aBoss[id].id_shadow = -1;	// ��ڂ��I�������l�����Z�b�g

#ifdef _DEBUG

		// ��������̂ݎז��Ȃ̂ŏ���
		for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
		{
			DeleteVisibleSph(g_aBoss[id].id_sph[i]);

			g_aBoss[id].id_sph[i] = -1;	// ��ڂ��I�������l�����Z�b�g
		}

#endif	// _DEBUG
	}

	if (g_aBoss[id].Param.style == BOSSTYPE_BIG && g_aBoss[id].Param.state == stateDead_b)
	{
		g_bBigBossUse = true;
	}
}



//************************************************
// �{�X�̕�������
//************************************************
void ResurrectBoss(int id)
{
	if (g_aBoss[id].Param.state == stateDead_b)
	{ // ���S��Ԃł����
		g_aBoss[id].Param.state = stateNormal_b;
		g_aBoss[id].Param.HP = 3;	//!< ���i�K�ł͓K���ɐݒ�
	}

}

//************************************************
// ���[�V�����Ǘ�����
//************************************************
void MotionBoss(int id)
{
	if (!g_aBoss[id].use)
	{ // ���g�p�Ȃ烊�^�[��
		return;
	}

	// �Đ����i�[�p
	int* pNow = &g_aBoss[id].Param.motion_now;			// ���݂̃��[�V�������
	int* pOld = &g_aBoss[id].Param.motion_old;			// �ߋ��̃��[�V�������
	BossMotion* pMotion = &g_aBoss[id].motion[*pNow];	// �e�G�l�~�[�̃��[�V�������

	switch (g_aBoss[id].Param.state)
	{
	case stateNormal_b: // �j���[�g�������[�V����
		if (g_aBoss[id].Param.style == BOSSTYPE_MID)
		{// ���{�X
			g_aBoss[id].Param.motion_now = motion_neutralMid;
		}
		else
		{// ��{�X
			g_aBoss[id].Param.motion_now = motion_neutralBig;
		}
		break;
	case stateMove_b:	// �ړ����[�V����
		if (g_aBoss[id].Param.style == BOSSTYPE_MID)
		{// ���{�X
			g_aBoss[id].Param.motion_now = motion_moveMid;
		}
		else
		{// ��{�X
			g_aBoss[id].Param.motion_now = motion_moveBig;
		}
		break;
	case stateAtk_b:	// �U�����[�V����
		if (g_aBoss[id].Param.style == BOSSTYPE_MID)
		{// ���{�X
			g_aBoss[id].Param.motion_now = motion_actionMid;
		}
		else
		{// ��{�X
			g_aBoss[id].Param.motion_now = motion_actionBig;
		}
		break;
	case stateDamage_b:	// ��e���[�V����
		if (g_aBoss[id].Param.style == BOSSTYPE_MID)
		{// ���{�X
			g_aBoss[id].Param.motion_now = motion_damageMid;
		}
		else
		{// ��{�X
			g_aBoss[id].Param.motion_now = motion_damageBig;
		}
		break;
	case stateDead_b:	// ���S���[�V����
		if (g_aBoss[id].Param.style == BOSSTYPE_MID)
		{// ���{�X
			g_aBoss[id].Param.motion_now = motion_deadMid;
		}
		else
		{// ��{�X
			g_aBoss[id].Param.motion_now = motion_deadBig;
		}
		break;
	case steteResurrect_b:	// �������[�V����
		break;

	}

	// �ύX�����m
	ChangeMotionBoss(id, pNow, pOld);

	// �p�[�c�̓���
	MoveMotionBoss(id, pMotion);

	// �t���[���J�E���g
	CntMotionBoss(id, pMotion);

}

//************************************************
// ���[�V�����ύX����
//************************************************
void ChangeMotionBoss(int id, int* pNow, int* pOld)
{
	if (*pOld == *pNow)
	{ // �ߋ��ƌ��݂̍Đ����[�V�����������Ȃ烊�^�[��
		return;
	}

	// �ߋ��̃��[�V�����̃L�[�ƃt���[�������Z�b�g
	g_aBoss[id].motion[*pOld].id_key = 0;
	g_aBoss[id].motion[*pOld].id_frame = 0;

	// �V�������[�V�����ֈڂ������Ƃ�ۑ�
	*pOld = *pNow;

}

//************************************************
// ���[�V�������쏈��
//************************************************
void MoveMotionBoss(int id, BossMotion* pMotion)
{
	int adjust = 0;	// �␳�p����

	// ���f���ƃ��[�V�����p�[�c�Ԃ̕s������␳����
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		if (g_aBoss[id].Param.style != g_BossModel[i].style)
		{ /*---�y���[�V�������̓��f���̎擾���Ɋւ�炸�Y���X�^�C�����\�����郂�f���Q��
					�匳�̐e�p�[�c��擪�Ƃ����A�Ԃł��邽�߁A�z��̕s������␳����K�v������z---*/
			adjust++;
		}
		else
		{
			break;	// �Y���X�^�C���ɓ��B�������_�ŏI��
		}
	}

	/*--------------------------------------------*/

	// �Đ����̃L�[�̑��t���[�������猻�݂̃t���[���ԍ�����������
	float dest = (float)(pMotion->key[pMotion->id_key].amount_frame - pMotion->id_frame);

	/*---�y�ЂȌ`�ɗp�ӂ���Ă���S�p�[�c�����z---*/
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		if (g_aBoss[id].parts[i].pMesh == NULL)
		{ // �p�[�c�����g�p�Ȃ�R���e�B�j���[
			continue;
		}

#ifdef _DEBUG

		assert((i - adjust) >= 0 && "���[�V�������␳�̔z��O�A�N�Z�X");

#endif // _DEBUG�F

		g_aBoss[id].parts[i].pos_moved += (pMotion->key[pMotion->id_key].dest[i - adjust].pos - g_aBoss[id].parts[i].pos_moved) / dest;
		g_aBoss[id].parts[i].rot_moved += (pMotion->key[pMotion->id_key].dest[i - adjust].rot - g_aBoss[id].parts[i].rot_moved) / dest;
	}
}

//************************************************
// ���[�V�����J�E���g�p
//************************************************
void CntMotionBoss(int id, BossMotion* pMotion)
{
	// �t���[���J�E���g
	pMotion->id_frame++;

	if (pMotion->id_frame >= pMotion->key[pMotion->id_key].amount_frame)
	{ // �Đ����̃L�[�̑��t���[�����o�߂�

		// �t���[���ԍ������Z�b�g��
		pMotion->id_frame = 0;

		// �L�[�J�E���g
		pMotion->id_key++;

		if (pMotion->id_key >= pMotion->amount_key)
		{ // �Đ����̃��[�V�����̑��L�[���o�߂�

			if (pMotion->loop == 1)
			{ // ���[�v�t���O���L��Ȃ�

				// �L�[�ԍ����Z�b�g�����^�[��
				pMotion->id_key = 0;
				return;
			}

			/*---�y����A�����I�ɑҋ@���[�V�����߂��z---*/
			g_aBoss[id].Param.motion_now = 0;
		}
	}

}

//************************************************
// �{�X�̒e�̋��������߂�
//************************************************
void AdjustBullet(int id)
{
	g_nAdjustTime++;	// �t���[�����̉��Z
	for (int nCntData = 0; nCntData < MAX_DATA; nCntData++)
	{
		if (g_nAdjustTime % 100 == 0)
		{
			g_nBulletType[nCntData] = rand() % 100 + 1;	//0�`10�܂ł̎��R���������_���Ő���

			if (g_nBulletType[nCntData] >= 0 && g_nBulletType[nCntData] < 10)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_ONE;
			}
			else if (g_nBulletType[nCntData] >= 10 && g_nBulletType[nCntData] < 20)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_TWO;
			}
			if (g_nBulletType[nCntData] >= 20 && g_nBulletType[nCntData] < 30)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_THREE;
			}
			if (g_nBulletType[nCntData] >= 30 && g_nBulletType[nCntData] < 40)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_FOUR;
			}
			if (g_nBulletType[nCntData] >= 40 && g_nBulletType[nCntData] < 50)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_FIVE;
			}
			if (g_nBulletType[nCntData] >= 50 && g_nBulletType[nCntData] < 60)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_SIX;
			}
			if (g_nBulletType[nCntData] >= 60 && g_nBulletType[nCntData] < 70)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_SEVEN;
			}
			if (g_nBulletType[nCntData] >= 70 && g_nBulletType[nCntData] < 80)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_EIGHT;
			}
			if (g_nBulletType[nCntData] >= 80 && g_nBulletType[nCntData] < 90)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_NINE;
			}
			if (g_nBulletType[nCntData] >= 90 && g_nBulletType[nCntData] < 100)
			{
				g_nBulletNum[nCntData] = BULLETPATTERN_TEN;
			}
		}

		switch (g_nBulletNum[nCntData])
		{
		case BULLETPATTERN_ONE:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 8.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 10.0f), 40.0f);
			break;
		case BULLETPATTERN_TWO:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(8.0f, 0.0f, 0.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 40.0f);
			break;
		case BULLETPATTERN_THREE:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 5.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-5.0f, 0.0f, 0.0f), 40.0f);
			break;
		case BULLETPATTERN_FOUR:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 5.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 10.0f), 40.0f);
			break;
		case BULLETPATTERN_FIVE:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(5.0f, 0.0f, 0.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 40.0f);
			break;
		case BULLETPATTERN_SIX:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 60.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 10.0f), 60.0f);
			break;
		case BULLETPATTERN_SEVEN:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(5.0f, 0.0f, 5.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(10.0f, 0.0f, 10.0f), 40.0f);
			break;
		case BULLETPATTERN_EIGHT:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, -10.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(0.0f, 0.0f, 10.0f), 40.0f);
			break;
		case BULLETPATTERN_NINE:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-10.0f, 0.0f, -10.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(10.0f, 0.0f, -10.0f), 40.0f);
			break;
		case BULLETPATTERN_TEN:
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-15.0f, 0.0f, -20.0f), 40.0f);
			SetBossBullet(D3DXVECTOR3(g_aBoss[id].pos.x, g_aBoss[id].pos.y + ADJUSTPOSY_BIGBOSS, g_aBoss[id].pos.z), D3DXVECTOR3(-15.0f, 0.0f, 20.0f), 40.0f);
			break;
		}

	}


}

//************************************************
// �{�X�p�̃��[���h�}�g���b�N�X���v�Z
//************************************************
void CalcMtxBoss(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	for (int enemy_id = 0; enemy_id < MAX_BOSS; enemy_id++)
	{
		if (!g_aBoss[enemy_id].use)
		{ // ���̔Ԃ̎g�p�t���O�������ŃR���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBoss[enemy_id].mtxWorld);

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aBoss[enemy_id].rot.y,
			g_aBoss[enemy_id].rot.x,
			g_aBoss[enemy_id].rot.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&g_aBoss[enemy_id].mtxWorld,
			&g_aBoss[enemy_id].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aBoss[enemy_id].pos.x,
			g_aBoss[enemy_id].pos.y,
			g_aBoss[enemy_id].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aBoss[enemy_id].mtxWorld,
			&g_aBoss[enemy_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < AMOUNT_BOSS_PARTS; Ps_id++)
		{
			if (g_aBoss[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // ����ۂȂ�R���e�B�j���[
				continue;
			}

			// ���̔ԃp�[�c�́u�e�p�[�c�v�̃C���f�b�N�X��ۑ�
			int IdxParent = g_aBoss[enemy_id].parts[Ps_id].IdxParent;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld);

			// ���[�V���������̔��f
			D3DXVECTOR3 PartsRot =
			{
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.x + g_aBoss[enemy_id].parts[Ps_id].rot_moved.x,
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.y + g_aBoss[enemy_id].parts[Ps_id].rot_moved.y,
				g_aBoss[enemy_id].parts[Ps_id].rot_offset.z + g_aBoss[enemy_id].parts[Ps_id].rot_moved.z
			};

			// �����𔽉f1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				PartsRot.y,
				PartsRot.x,
				PartsRot.z);

			// �����𔽉f2
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// ���[�V�����ʒu�̔��f
			D3DXVECTOR3 PartsPos =
			{
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.x + g_aBoss[enemy_id].parts[Ps_id].pos_moved.x,
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.y + g_aBoss[enemy_id].parts[Ps_id].pos_moved.y,
				g_aBoss[enemy_id].parts[Ps_id].pos_offset.z + g_aBoss[enemy_id].parts[Ps_id].pos_moved.z
			};

			// �ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				PartsPos.x,
				PartsPos.y,
				PartsPos.z);

			// �ʒu�𔽉f
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// �e�̃��[���h�}�g���b�N�X���擾
			if (IdxParent == -1)
			{ //���C���p�[�c�̂݃��[���h���W�ɒ���
				mtxParent = g_aBoss[enemy_id].mtxWorld;
			}
			else
			{ //���̑��p�[�c�͂��ꂼ��̐e�p�[�c�֕t��
				mtxParent = g_aBoss[enemy_id].parts[IdxParent].mtxWorld;
			}

			// �p�[�c���Ƃ̃��[���h�}�g���b�N�X���Z�o
			D3DXMatrixMultiply(&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&g_aBoss[enemy_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}
	}
}

//************************************************
// �{�X�`��
//************************************************
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int enemy_id = 0; enemy_id < MAX_BOSS; enemy_id++)
	{
		if (!g_aBoss[enemy_id].use)
		{ // ���̔Ԃ̎g�p�t���O�������ŃR���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[enemy_id].mtxWorld);

		for (int Ps_id = 0; Ps_id < AMOUNT_BOSS_PARTS; Ps_id++)
		{
			if (g_aBoss[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // ����ۂȂ�R���e�B�j���[
				continue;
			}

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBoss[enemy_id].parts[Ps_id].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aBoss[enemy_id].parts[Ps_id].pBuffMat->GetBufferPointer();

			for (int mat_id = 0; mat_id < (int)g_aBoss[enemy_id].parts[Ps_id].NumMat; mat_id++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[mat_id].MatD3D);

				// �e�N�X�`���̐ݒ�
				if (g_aBoss[enemy_id].parts[Ps_id].pTex[mat_id] != NULL)
				{
					pDevice->SetTexture(0, g_aBoss[enemy_id].parts[Ps_id].pTex[mat_id]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// ���f���p�[�c�̕`��
				g_aBoss[enemy_id].parts[Ps_id].pMesh->DrawSubset(mat_id);
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}

	}
}

//************************************************
// �{�X�����擾
//************************************************
BOSS* GetInfoBoss(void)
{
	return g_aBoss;
}

//************************************************
// �{�X�������Ă��邩�ǂ���
//************************************************
bool CheckBossUse(void)
{
	if (g_bBigBossUse)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//************************************************
// �{�X�ƌ����̓����蔻��
//************************************************
void CollisionBoss(int id)
{
	// �{�X�̃^�C�v�Ɍ��炸�I�u�W�F�N�g�Ƃ̏Փ˔�����s��
	Object* pObject = GetInfoObject();

	for (int nCntObject = 0; nCntObject < AMOUNT_OBJECT; nCntObject++, pObject++)
	{
		if (!pObject->use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
		{
			if (CollisionSphAABB(g_aBoss[id].pos_sph[i], g_aBoss[id].rad[i], pObject->model.aabb))
			{
				HitObject(nCntObject);	// �����ɏՓ˔���
			}
		}
	}
}

//************************************************
// �{�X�ƃv���C���[�̓����蔻��
//************************************************
void CollisionPlayer(int id)
{
	Player* pPlayer = GetInfoPlayer();

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (!g_aBoss[id].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (pPlayer[nCntPlayer].param.state == stateDamage_p ||
			pPlayer[nCntPlayer].param.state == stateDead_p)
		{ // �����F���S��ԂȂ�R���e�B�j���[
			continue;
		}

		for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
		{
			// �S�Ẵ��f�������肷��̂ŁA�X�^�C���s��v�̂��̂̓R���e�B�j���[
			switch (id)
			{
			case 0:

				if (i > 14)
				{
					continue;
				}

				break;

			case 1:

				if (i <= 14)
				{
					continue;
				}

				break;
			}

			if (CollisionSph(g_aBoss[id].pos_sph[i], g_aBoss[id].rad[i], pPlayer[nCntPlayer].pos, pPlayer[nCntPlayer].param.rad))
			{
				// ��e�̏���
				HitPlayer(nCntPlayer);
			}
		}
	}
}
//************************************************
// �t�F�[�Y���I������{�X�̏���
//************************************************
void DeleteOldBoss(int id)
{
	g_nMidBossPhase = *GetInfoPhase();

	if (g_nMidBossPhase != 3)
	{
		return;
	}

	if (g_aBoss[id].Param.style == BOSSTYPE_MID)
	{
#ifdef _DEBUG

		// ��������̂ݎז��Ȃ̂ŏ���
		for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
		{
			DeleteVisibleSph(g_aBoss[id].id_sph[i]);

			g_aBoss[id].id_sph[i] = -1;	// ��ڂ��I�������l�����Z�b�g
		}

#endif	// _DEBUG

		/*---�y�e�������z---*/
		DeleteShadow(g_aBoss[id].id_shadow);

		// �{�X�̏���
		g_aBoss[id].use = false;
	}

}

////////////////////////////////////////////////////////////////

//************************************************
// �̗͂ɂ�鐶������ - ���{�X
//************************************************
bool GetInfoHP_MidBoss(void)
{
	bool tf = false;

	if (g_aBoss[0].Param.HP <= 0)
	{
		tf = true;
	}

	return tf;
}

//************************************************
// �̗͂ɂ�鐶������ - ��{�X
//************************************************
bool GetInfoHP_BigBoss(void)
{
	bool tf = false;

	if (g_aBoss[1].Param.HP <= 0)
	{
		tf = true;
	}

	return tf;
}

////////////////////////////////////////////////////////////////

//************************************************
// �e�p�[�c�̔�����X�V
//************************************************
void UpdatePartsRadBoss(int id)
{
	for (int i = 0; i < AMOUNT_BOSS_PARTS; i++)
	{
		switch (id)
		{
		case 0:

			if (i > 14)
			{
				continue;
			}

			break;

		case 1:

			if (i <= 14)
			{
				continue;
			}

			break;
		}

		g_aBoss[id].pos_sph[i] =
		{
			g_aBoss[id].parts[i].mtxWorld._41,
			g_aBoss[id].parts[i].mtxWorld._42,
			g_aBoss[id].parts[i].mtxWorld._43
		};

		if (g_aBoss[id].pos_sph[i].x == 0.0f &&
			g_aBoss[id].pos_sph[i].z == 0.0f)
		{
			g_aBoss[id].pos_sph[i].y = -1000.0f;
		}

	}
}