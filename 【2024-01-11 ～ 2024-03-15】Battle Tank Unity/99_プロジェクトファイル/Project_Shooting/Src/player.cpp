//************************************************
//
// �v���C���[����[player.cpp]
// Author�F���c����, kasai keisuke
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "player.h"

// �V�X�e���n
#include "input.h"
#include "sound.h"

// ������
#include "bullet.h"
#include "camera.h"
#include "collision.h"
#include "effect_heart.h"
#include "effect_sand.h"
#include "effect_smoke.h"
#include "effect_soul.h"
#include "game.h"
#include "object.h"
#include "player_count.h"
#include "shadow.h"
#include "weapon.h"

// �f�o�b�O��
#ifdef _DEBUG
#include "debugproc.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*---�y�O���[�o���ϐ��z---*/
PlayerModel g_PlayerModel[AMOUNT_PLAYER_PARTS];	// �v���C���[�p���f��
PlayerMotion g_PlayerMotion[8];					// �v���C���[�p���[�V����
Player g_Player[MAX_PLAYER];					// �v���C���[���
int g_nNumPlayer = 0;							// �v���C�l���i�[�p
/*---�y�L�[�{�[�h�Ńf�o�b�O���삷��v���C���[�����ʁz---*/
int g_P_id = -1;

/*---�y�v���g�^�C�v�錾�z---*/
void ClearInfoPlayerModel(void);	// �v���C���[�p���f���̃N���A
void ClearInfoPlayerMotion(void);	// �v���C���[�p���[�V�����̃N���A
void ClearInfoPlayer(void);			// �v���C���[���̃N���A

//************************************************
// �v���C���[����
//************************************************
void InitPlayer(int joined)
{
	// �O���[�o���ϐ��̏�����
	g_P_id = -1;		// �f�o�b�O����v���C���[��ύX
	g_nNumPlayer = 0;	// �Q���l���i�[�p

	//�v���C�l���̎擾
	g_nNumPlayer = ReturnSelectPlayerCount() + 1;

	// �v���C���[�p���f���̃N���A
	ClearInfoPlayerModel();

	// �v���C���[�p���[�V�����̃N���A
	ClearInfoPlayerMotion();

	// �v���C���[���̃N���A
	ClearInfoPlayer();

	// �v���C���[�p�̃��f�������擾
	ImportModelPlayer();

	// �v���C���[�p�̃��[�V���������擾
	ImportMotionPlayer();
		
	// �v���C���[����
	CreatePlayer(joined);

	// �X�|�[���n�_��ݒ�
	SetSpawnPlayer(joined);
}

//************************************************
// �v���C���[����
//************************************************
void CreatePlayer(int joined)
{
	for (int i = 0; i < joined; i++)
	{
		// ���[�V���������R�s�[
		for (int j = 0; j < 8; j++)
		{
			if (g_PlayerMotion[j].amount_key == 0)
			{ // ���g�p�Ȃ�R���e�B�j���[
				continue;
			}

			g_Player[i].motion[j] = g_PlayerMotion[j];
		}

		g_Player[i].use = true;						// �g�p
		g_Player[i].param.style = i;				// �X�^�C���ԍ�
		g_Player[i].param.state = stateNormal_p;	// ���
		g_Player[i].param.HP = 3;					// �̗�
		g_Player[i].param.SPD = 10.0f;				// ���x
		g_Player[i].param.rad = 30.0f;				// ����T�C�Y
		g_Player[i].param.motion_now = styleGun;	// ����
		g_Player[i].param.motion_now = 0;
		g_Player[i].param.motion_old = 0;
		g_Player[i].param.weapon = styleGun;		// ����
		g_Player[i].PFW.magazine = 20;				// �e��


		// �X�^�C���ԍ����ƍ�
		VerifyStylePlayer(i);

		/*---�y�e�𐶐��z---*/
		g_Player[i].id_shadow = CreateShadow(40.0f);

#ifdef _DEBUG

		// �����蔻�������
		CreateVisibleSph(g_Player[i].param.rad, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), &g_Player[i].pos);

#endif
	}
}

//************************************************
// �X�|�[���n�_�ݒ�
//************************************************
void SetSpawnPlayer(int joined)
{
	switch (joined)
	{
	case 1:

		g_Player[0].pos = { 0.0f, 0.0f, 0.0f };

		break;

	case 2:

		g_Player[0].pos = { -100.0f, 0.0f, 0.0f };
		g_Player[1].pos = { 100.0f, 0.0f, 0.0f };

		break;

	case 3:

		g_Player[0].pos = { -100.0f, 0.0f, 100.0f };
		g_Player[1].pos = { 100.0f, 0.0f, 100.0f };
		g_Player[2].pos = { -100.0f, 0.0f, -100.0f };

		break;

	case 4:

		g_Player[0].pos = { -100.0f, 0.0f, 100.0f };
		g_Player[1].pos = { 100.0f, 0.0f, 100.0f };
		g_Player[2].pos = { -100.0f, 0.0f, -100.0f };
		g_Player[3].pos = { 100.0f, 0.0f, -100.0f };

		break;
	}
}

//************************************************
// ���f������ǂݍ���
//************************************************
void ImportModelPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int AmountModel = 0;		// ���f���̐����i�[
	int id_Model = 0;			// ���f���̎��ʗp

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\PLAYER\\player_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�v���C���[���f�����̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountModel);
		}

#ifdef _DEBUG

		// �G���[
		assert(AmountModel < AMOUNT_PLAYER_PARTS && "�v���C���[���f�����f����񂪍ő�ʂ��z���܂���");

#endif	// _DEBUG

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s %s", &FileString[0], 2, &FileString[0], 128);

			// �ǂݍ��񂾏����ЂȌ`�ɂ̂݃R�s�[����
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_PlayerModel[id_Model].pBuffMat,
				NULL,
				&g_PlayerModel[id_Model].NumMat,
				&g_PlayerModel[id_Model].pMesh);

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == AmountModel)
			{ // ���f�������ǂݎ��I���ƏI��
				break;
			}
		}
	}

	// �e���f���̃I�t�Z�b�g�����擾
	ImportOffsetPlayer(pFile, AmountModel);

	// �e���f���̃e�N�X�`�������擾
	ImportTexPlayer(AmountModel);

	// �t�@�C�������
	fclose(pFile);
}

//************************************************
// ���f���I�t�Z�b�g����ǂݍ���
//************************************************
void ImportOffsetPlayer(FILE* pFile, int AmountModel)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	char FileString[128] = {};	// ���͂��i�[
	int style = -1;				// ���̃p�[�c�̃X�^�C�����i�[
	int weapon = -1;			// ���̃p�[�c�̕���X�^�C�����i�[
	int IdxParent = -1;			// �e�̃C���f�b�N�X���i�[
	D3DXVECTOR3 pos = {};		// �ʒu�̃I�t�Z�b�g���i�[
	D3DXVECTOR3 rot = {};		// �����̃I�t�Z�b�g���i�[
	int id_Model = 0;			// ���f���̎��ʗp

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // ���̃p�[�c�̃X�^�C�����擾	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &style);
		}

		if (strcmp(&FileString[0], "WEAPON") == 0)
		{ // ���̃p�[�c�̃X�^�C�����擾	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &weapon);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // �e�p�[�c�ƂȂ���̂̔Ԃ��擾	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &IdxParent);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu�̃I�t�Z�b�g���擾	
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �����̃I�t�Z�b�g���擾	
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARTSSET") == 0)
		{
			// �ǂݍ��񂾏����ЂȌ`�ɂ̂݃R�s�[����
			g_PlayerModel[id_Model].style = style;
			g_PlayerModel[id_Model].weapon = weapon;
			g_PlayerModel[id_Model].IdxParent = IdxParent;
			g_PlayerModel[id_Model].pos_offset = pos;
			g_PlayerModel[id_Model].rot_offset = rot;

			weapon = -1;	// ����X�^�C�������Z�b�g
			id_Model++;		// �p�[�c��i�߂�

			if (id_Model == AmountModel)
			{ // ���f�������ǂݎ��I���ƏI��
				break;
			}
		}
	}

	// �U���ʒu�̃I�t�Z�b�g�����擾
	ImportOffsetAtkPlayer(pFile);
}

//************************************************
// (������) �U���ʒu�̃I�t�Z�b�g����ǂݍ���
//************************************************
void ImportOffsetAtkPlayer(FILE* pFile)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	char FileString[128] = {};	// ���͂��i�[
	int i = 0;					// �ėp����
	D3DXVECTOR3 pos = {};		// �ʒu�̃I�t�Z�b�g���i�[

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{ 
		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu�̃I�t�Z�b�g�𔽉f

			// �ʒu���擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
			
			for (int j = 0; j < MAX_PLAYER; j++)
			{ // (�������) �S�Ẵv���C���[�ɔ��f
				g_Player[j].offset_atk[i].pos = pos;
			}

			i++;	// ���̔Ԃ�
		}

		if (i >= Max_itemstyle)
		{ // ����̍ő吔�ɓ��B����ƏI��
			break;
		}
	}
}

//************************************************
// ���f���e�N�X�`������ǂݍ���
//************************************************
void ImportTexPlayer(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int i = 0; i < AmountModel; i++)
	{
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_PlayerModel[i].pBuffMat->GetBufferPointer();

		// ���̃p�[�c�̎��}�e���A������
		for (int j = 0; j < (int)g_PlayerModel[i].NumMat; j++)
		{
			// �}�e���A���Ƀe�N�X�`�����ݒ肳��Ă���ΓǍ���
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_PlayerModel[i].pTex[j]);
			}
			else
			{
				g_PlayerModel[i].pTex[j] = NULL;
			}
		}
	};
}

//************************************************
// �X�^�C���ԍ��̏ƍ�
//************************************************
void VerifyStylePlayer(int id)
{
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		// �e�v���C���[�̃X�^�C���ԍ��Ɗe�p�[�c�̃X�^�C���ԍ����ƍ�
		if (g_PlayerModel[i].style == g_Player[id].param.style || g_PlayerModel[i].style == 99)
		{ // �X�^�C���ԍ��̈�v���Ă���p�[�c�y�у��j�p�[�c��L��������
			g_Player[id].parts[i] = g_PlayerModel[i];
		}
	}
}

//************************************************
// ���[�V��������ǂݍ���
//************************************************
void ImportMotionPlayer(void)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int i = 0, j = 0, k = 0;	// �ėp����
	int loop = 0;				// ���[�v�t���O���i�[
	int amountKey = 0;			// ���L�[�����擾
	int amountFrame = 0;		// ���t���[�������擾
	D3DXVECTOR3 pos, rot;		// �ʒu�ƌ������i�[

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\PLAYER\\player_motion.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�v���C���[���[�V�������̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "LOOP") == 0)
		{ // ���[�v�t���O���擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &loop);
		}

		if (strcmp(&FileString[0], "NUM_KEY") == 0)
		{ // ���L�[�����擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &amountKey);
		}

		if (strcmp(&FileString[0], "FRAME") == 0)
		{ // �t���[�������擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &amountFrame);
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
			g_PlayerMotion[i].key[j].dest[k].pos = pos;
			g_PlayerMotion[i].key[j].dest[k].rot = rot;

			k++;	// �p�[�c�ԍ���i�߂�
		}

		if (strcmp(&FileString[0], "END_KEYSET") == 0)
		{ // �L�[����ۑ�
			g_PlayerMotion[i].key[j].amount_frame = amountFrame;

			k = 0;	// �p�[�c�ԍ������Z�b�g
			j++;	// �L�[�ԍ���i�߂�
		}

		if (strcmp(&FileString[0], "END_MOTIONSET") == 0)
		{ // ���[�V��������ۑ�
			g_PlayerMotion[i].loop = loop;
			g_PlayerMotion[i].amount_key = amountKey;

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
// �v���C���[�j��
//************************************************
void UninitPlayer(void)
{
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_PlayerModel[i].pTex[j] != NULL)
			{ // �e�N�X�`���̔j��

				g_PlayerModel[i].pTex[j]->Release();
				g_PlayerModel[i].pTex[j] = NULL;
			}
		}

		if (g_PlayerModel[i].pMesh != NULL)
		{ // ���b�V���̔j��

			g_PlayerModel[i].pMesh->Release();
			g_PlayerModel[i].pMesh = NULL;
		}

		if (g_PlayerModel[i].pBuffMat != NULL)
		{ // �}�e���A���̔j��

			g_PlayerModel[i].pBuffMat->Release();
			g_PlayerModel[i].pBuffMat = NULL;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �v���C���[�X�V
//************************************************
void UpdatePlayer(int joined)
{
	for (int i = 0; i < joined; i++)
	{
		// �ߋ��̈ʒu���L�^
		g_Player[i].pos_old = g_Player[i].pos;

		// ��]
		RotatePlayer(i);

		// �C������
		AdjustTurret(i);

		// �ړ�
		MovePlayer(i);

		// �ړ����f
		TranslatePlayer(i);

		/*---�y�V�����e�̒Ǐ]�z---*/
		TrackShadow(g_Player[i].id_shadow,
			g_Player[i].pos);

		// �U��
		AtkPlayer(i);

		// �U���̔���
		//RecoilPlayer(i);

		// ����
		DamagePlayer(i);

		// ���S����
		DeadPlayer(i);

		// ��������
		ResurrectPlayer(i);

		// ���[�V����
		MotionPlayer(i);
	}

	// �Ō�ɍs��v�Z
	CalcMtxPlayer();

#ifdef _DEBUG

	// �f�o�b�O�\��
	//PrintDebugPlayer();

#endif	// _DEBUG
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �v���C���[��]
//************************************************
void RotatePlayer(int id)
{
	// �u���[�L��
	float StopEnergy = 0.1f;

	if (!g_Player[id].use)
	{ // ���g�p�Ȃ烊�^�[��
		return;
	}

	// ��]�u���[�L
	if (g_Player[id].rot_goal.y - g_Player[id].rot.y > D3DX_PI)
	{
		g_Player[id].rot.y += ((g_Player[id].rot_goal.y - g_Player[id].rot.y) * StopEnergy + (D3DX_PI * 1.8f));
	}
	else if (g_Player[id].rot_goal.y - g_Player[id].rot.y < -D3DX_PI)
	{
		g_Player[id].rot.y += ((g_Player[id].rot_goal.y - g_Player[id].rot.y) * StopEnergy + (D3DX_PI * -1.8f));
	}
	else
	{
		g_Player[id].rot.y += ((g_Player[id].rot_goal.y - g_Player[id].rot.y) * StopEnergy);
	}
}

//************************************************
// �C�������_�����֌�����
//************************************************
void AdjustTurret(int id)
{
	// �J���������擾
	Camera* pCamera = GetInfoCamera();

	if (!g_Player[id].use)
	{ // ���g�p�Ȃ烊�^�[��
		return;
	}

	for (int j = 0; j < AMOUNT_PLAYER_PARTS; j++)
	{ // �����̕ύX���l�����A�`��̂Ȃ��p�[�c�ɂ�����^����

		// ���̔ԃp�[�c�́u�e�p�[�c�v�̃C���f�b�N�X��ۑ�
		int IdxParent = g_Player[id].parts[j].IdxParent;

#if OFFSET_VERIFY

		if (g_Player[id].parts[j].IdxParent == -1)
		{ // ���̔Ԃ̃p�[�c���y��p�[�c�ł���Ȃ�X�L�b�v
			continue;
		}

#else

		if (IdxParent != 0)
		{ // ���̔Ԃ̃p�[�c�̐e�̃��f����ނ��y��p�[�c�łȂ��Ȃ�X�L�b�v
			continue;
		}

#endif	// OFFSET_VERIFY

		// ���������_���ʕ�����
		g_Player[id].parts[j].rot_moved.y = pCamera[id].rot.y;
	}
}

//************************************************
// �v���C���[�ړ�
//************************************************
void MovePlayer(int id)
{
#ifdef _DEBUG

	if (id == g_P_id)
	{ // �f�o�b�O�I�����Ă���v���C���[�̔Ԃ��΂�
		DEBUG_MovePlayer();
		return;
	}

#endif	// _DEBUG

	if (!g_Player[id].use)
	{ // ���g�p�Ȃ烊�^�[��
		return;
	}

	if (g_Player[id].param.state != stateDead_p &&
		g_Player[id].param.motion_now != 3)
	{ // ��e���[�V�������F���S��ԂłȂ��Ƃ�

		// �J���������擾
		const Camera* pCamera = GetInfoCamera();

		if (GetJoyStickL(id))
		{ // ���X�e�B�b�N�ňړ�
			const XINPUT_GAMEPAD GamePad = GetGamePad(id);

			// �ړ��ʂƖړI�̌�����t�^
			g_Player[id].move.x += sinf(atan2f((float)(GamePad.sThumbLX * 0.00001), (float)(GamePad.sThumbLY * 0.00001)) + pCamera[id].rot.y);
			g_Player[id].move.z += cosf(atan2f((float)(GamePad.sThumbLX * 0.00001), (float)(GamePad.sThumbLY * 0.00001)) + pCamera[id].rot.y);
			g_Player[id].rot_goal.y = atan2f((float)(GamePad.sThumbLX * -0.000001), (float)(GamePad.sThumbLY * -0.000001)) + pCamera[id].rot.y;

			if (g_Player[id].param.state != stateDamage_p &&
				g_Player[id].param.state != stateDead_p)
			{ // �����F���S��ԂłȂ����

				// �ړ���Ԃ�
				g_Player[id].param.state = stateMove_p;

				// �ړ����[�V�������Đ�
				g_Player[id].param.motion_now = 1;
			}

			// ���G�t�F�N�g
			SetEffectSand(g_Player[id].pos, 0, 30.0f, id);
			SetEffectSand(g_Player[id].pos, 1, 30.0f, id);
		}
		else
		{ // �ړ����Ă��Ȃ��Ƃ�

			if (g_Player[id].param.state != stateDamage_p)
			{ // ������ԂłȂ����

				// �ʏ��Ԃ�
				g_Player[id].param.state = stateNormal_p;

				// �ʏ탂�[�V�������Đ�
				g_Player[id].param.motion_now = 0;
			}
		}
	}

	g_Player[id].move *= SPD_STOPMOVE_PLAYER;	// �u���[�L

	// ������x�ړ��ʂ����Ȃ���0�����Ă���
	if (g_Player[id].move.x < EPSILON && g_Player[id].move.x > -EPSILON)
	{
		g_Player[id].move.x = 0.0f;
	}

	if (g_Player[id].move.z < EPSILON && g_Player[id].move.z > -EPSILON)
	{
		g_Player[id].move.z = 0.0f;
	}
}

//************************************************
// �f�o�b�O�ړ�
//************************************************
void DEBUG_MovePlayer(void)
{
	if (g_Player[g_P_id].param.state != stateDead_p &&
		g_Player[g_P_id].param.motion_now != 3)
	{ // ��e���[�V�������F���S��ԂłȂ��Ƃ�

		// �J���������擾
		const Camera* pCamera = GetInfoCamera();

		// �f�o�b�O���̓L�[�{�[�h���͂ňړ��\
		float X = 0.0f;
		float Z = 0.0f;
		bool move = false;

		if (GetKeyboardTrigger(DIK_1))
		{
			g_P_id = 0;
		}
		else if (GetKeyboardTrigger(DIK_2))
		{
			g_P_id = 1;
		}
		else if (GetKeyboardTrigger(DIK_3))
		{
			g_P_id = 2;
		}
		else if (GetKeyboardTrigger(DIK_4))
		{
			g_P_id = 3;
		}

		if (GetKeyboardPress(DIK_A))
		{
			X = -1.0f;
		}
		else if (GetKeyboardPress(DIK_D))
		{
			X = 1.0f;
		}

		if (GetKeyboardPress(DIK_W))
		{
			Z = 1.0f;
		}
		else if (GetKeyboardPress(DIK_S))
		{
			Z = -1.0f;
		}

		if (X != 0.0f || Z != 0.0f)
		{ // ��������͂��Ă���Έړ����Ă��锻��
			move = true;
		}

		if (move)
		{
			// �ړ��ʂƖڕW������ݒ�
			g_Player[g_P_id].move.x += sinf(atan2f(X, Z) + pCamera[g_P_id].rot.y);
			g_Player[g_P_id].move.z += cosf(atan2f(X, Z) + pCamera[g_P_id].rot.y);
			g_Player[g_P_id].rot_goal.y = atan2f(-X, -Z) + pCamera[g_P_id].rot.y;

			if (g_Player[g_P_id].param.state != stateDamage_p &&
				g_Player[g_P_id].param.state != stateDead_p)
			{ // �����F���S��ԂłȂ����

				// �ړ���Ԃ�
				g_Player[g_P_id].param.state = stateMove_p;

				// �ړ����[�V�������Đ�
				g_Player[g_P_id].param.motion_now = 1;
			}

			// ���G�t�F�N�g
			SetEffectSand(g_Player[g_P_id].pos, 0, 30.0f, g_P_id);
			SetEffectSand(g_Player[g_P_id].pos, 1, 30.0f, g_P_id);
		}
		else
		{ // �ړ����Ă��Ȃ��Ƃ�

			if (g_Player[g_P_id].param.state != stateDamage_p)
			{ // ������ԂłȂ����

				// �ʏ��Ԃ�
				g_Player[g_P_id].param.state = stateNormal_p;

				// �ʏ탂�[�V�������Đ�
				g_Player[g_P_id].param.motion_now = 0;
			}
		}
	}

	g_Player[g_P_id].move *= SPD_STOPMOVE_PLAYER;	// �u���[�L
}

//************************************************
// �ړ��𔽉f
//************************************************
void TranslatePlayer(int id)
{
	g_Player[id].pos += g_Player[id].move * SPD_MOVE_PLAYER;	// �ړ�

	if (g_Player[id].param.state == stateDamage_p)
	{ // ������Ԃ̂ݓ��ʂɉ���
		g_Player[id].pos += g_Player[id].move * SPD_MOVE_PLAYER;
	}

	// �I�u�W�F�N�g�Ƃ̓����蔻������s���A�ړ���␳
	HitObjectPlayer(id);

	// �X�e�[�W�̒[���z���Ă�����␳
	if (g_Player[id].pos.x + g_Player[id].param.rad >= 2000.0f)
	{
		g_Player[id].pos.x = 2000.0f - g_Player[id].param.rad;
	}
	else if (g_Player[id].pos.x - g_Player[id].param.rad <= -2000.0f)
	{
		g_Player[id].pos.x = -2000.0f + g_Player[id].param.rad;
	}

	if (g_Player[id].pos.z + g_Player[id].param.rad >= 2000.0f)
	{
		g_Player[id].pos.z = 2000.0f - g_Player[id].param.rad;
	}
	else if (g_Player[id].pos.z - g_Player[id].param.rad <= -2000.0f)
	{
		g_Player[id].pos.z = -2000.0f + g_Player[id].param.rad;
	}
}

//************************************************
// �ǂƂ̓����蔻��
//************************************************
void HitObjectPlayer(int id)
{
	Object* pObject = GetInfoObject();

	for (int i = 0; i < AMOUNT_OBJECT; i++, pObject++)
	{
		if (pObject->param.HP <= 0)
		{ // �j�󂳂�Ă���΃R���e�B�j���[
			continue;
		}

		if (pObject->type == 9 ||
			pObject->type == 10)
		{ // ���̃��f�������H�̏ꍇ�̓R���e�B�j���[
			continue;
		}

		// �����蔻������s�A�ړ���␳
		CollisionVecSphAABB(id, g_Player[id].pos, g_Player[id].param.rad, pObject->model.aabb);
	}
}

//************************************************
// �v���C���[�̍U��
//************************************************
void AtkPlayer(int id)
{
	if (!g_Player[id].use)
	{ // ���g�p�Ȃ烊�^�[��
		return;
	}

	if (g_Player[id].param.state == stateDead_p ||
		g_Player[id].param.HP <= 0)
	{ // ���S��ԂȂ烊�^�[��
		return;
	}	

	// ���킲�Ƃ̓�����s��
	switch (g_Player[id].param.weapon)
	{
	case styleGun:

		if (!g_Player[id].PFW.empty)
		{ // �c�e�������

			// �U���{�^�������Ŕ��ˏ���
			if (GetPressTriggerButtonR(id))
			{
				g_Player[id].PFW.CT_input++;	// �L���X�g
			}
			else
			{
				// �����łȂ���΁A���ˏo�����悤�ɂ���
				g_Player[id].PFW.CT_input = 14;
			}

			if (g_Player[id].PFW.CT_input >= 15)
			{ // ���˃L���X�g������

				CreateBullet(bulletPlayer, id);	// �e�𐶐�
				
				RotatePFW3(id, -0.1f);	// ���ԉ�]

				g_Player[id].PFW.magazine--;	// �e������

				if (g_Player[id].PFW.magazine <= 0)
				{ // �c�e�������Ȃ��

					g_Player[id].PFW.empty = true;	// �����[�h�ɓ���
				}

				g_Player[id].PFW.CT_input = 0;	// �L���X�g�����Z�b�g
			}
		}
		else
		{ // �c�e���������

			g_Player[id].PFW.CT_reload++;	// �����[�h�J�n

			RotatePFW3(id, 0.1f);	// ���ԉ�]

			if (g_Player[id].PFW.CT_reload >= 80)
			{ // �����[�h������

				g_Player[id].PFW.magazine = 20;	// ���U 
				g_Player[id].PFW.CT_reload = 0;	// �����[�h���Z�b�g
				g_Player[id].PFW.empty = false;	// ����۔��������
				PlaySound(SOUND_LABEL_PICK_WEAPON);
			}
		}

		break;

	case styleRPG:

		if (!g_Player[id].PFW.empty)
		{ // �c�e�������

				if (g_Player[id].PFW.CT_recoil > 0)
			{ // �����̊��Ԃ������

				g_Player[id].PFW.CT_recoil--;	// �������Ԃ�����
			}
			else
			{ // �������Ԃ��Ȃ����

				// �U���{�^�������Ŕ��ˏ���
				if (GetTriggerTriggerButtonR(id))
				{
					CreateBullet(bulletPlayer, id);	// �e�𐶐�

					RotatePFW3(id, -0.4f);	// ���ԉ�]

					g_Player[id].PFW.magazine--;	// �c�e����

					if (g_Player[id].PFW.magazine <= 0)
					{
						g_Player[id].PFW.empty = true;
					}

					g_Player[id].PFW.CT_recoil = 80;	// ��������
				}
			}
		}
		else
		{ // �c�e���������

			g_Player[id].PFW.CT_reload++;	// �����[�h�J�n

			RotatePFW3(id, 0.01f);	// ���ԉ�]

			if (g_Player[id].PFW.CT_reload >= 100)
			{ // �����[�h������

				g_Player[id].PFW.magazine = 3;	// ���U 
				g_Player[id].PFW.CT_reload = 0;	// �����[�h���Z�b�g
				g_Player[id].PFW.CT_recoil = 0;	// �������Z�b�g
				g_Player[id].PFW.empty = false;	// ����۔��������
				PlaySound(SOUND_LABEL_PICK_WEAPON);
			}
		}

		break;

	case styleGut:

		if (!g_Player[id].PFW.empty)
		{ // �c�e�������

			// �U���{�^�������Ŕ��ˏ���
			if (GetPressTriggerButtonR(id))
			{
				g_Player[id].PFW.CT_input++;	// �L���X�g
			}
			else
			{
				// �����łȂ���΁A���ˏo�����悤�ɂ���
				g_Player[id].PFW.CT_input = 7;
			}

			if (g_Player[id].PFW.CT_input >= 8)
			{ // ���˃L���X�g������

				CreateBullet(bulletPlayer, id);	// �e�𐶐�

				RotatePFW3(id, -0.15f);	// ���ԉ�]

				g_Player[id].PFW.magazine--;	// �e������

				if (g_Player[id].PFW.magazine <= 0)
				{ // �c�e�������Ȃ��

					g_Player[id].PFW.empty = true;	// �����[�h�ɓ���
				}

				g_Player[id].PFW.CT_input = 0;	// �L���X�g�����Z�b�g
			}
		}
		else
		{ // �c�e���������

			g_Player[id].PFW.CT_reload++;	// �����[�h�J�n

			RotatePFW3(id, 0.01f);	// ���ԉ�]

			if (g_Player[id].PFW.CT_reload >= GUTRELOAD)
			{ // �����[�h������

				g_Player[id].PFW.magazine = 40;	// ���U 
				g_Player[id].PFW.CT_reload = 0;	// �����[�h���Z�b�g
				g_Player[id].PFW.CT_recoil = 0;	// �������Z�b�g
				g_Player[id].PFW.empty = false;	// ����۔��������
				PlaySound(SOUND_LABEL_PICK_WEAPON);
			}
		}

		break;

	case styleShot:

		if (!g_Player[id].PFW.empty)
		{ // �c�e�������

			if (g_Player[id].PFW.CT_recoil > 0)
			{ // �����̊��Ԃ������

				g_Player[id].PFW.CT_recoil--;	// �������Ԃ�����
			}
			else
			{ // �������Ԃ��Ȃ����

				// �U���{�^�������Ŕ��ˏ���
				if (GetTriggerTriggerButtonR(id))
				{
					CreateBullet(bulletPlayer, id);	// �e�𐶐�

					RotatePFW3(id, -0.4f);	// ���ԉ�]

					g_Player[id].PFW.magazine--;	// �c�e����

					if (g_Player[id].PFW.magazine <= 0)
					{
						g_Player[id].PFW.empty = true;
					}

					g_Player[id].PFW.CT_recoil = 20;	// ��������
				}
			}
		}
		else
		{ // �c�e���������

			g_Player[id].PFW.CT_reload++;	// �����[�h�J�n

			RotatePFW3(id, 0.01f);	// ���ԉ�]

			if (g_Player[id].PFW.CT_reload >= 100)
			{ // �����[�h������

				g_Player[id].PFW.magazine = 7;	// ���U 
				g_Player[id].PFW.CT_reload = 0;	// �����[�h���Z�b�g
				g_Player[id].PFW.empty = false;	// ����۔��������
				PlaySound(SOUND_LABEL_PICK_WEAPON);
			}
		}

		break;
	}

#ifdef _DEBUG

	/*---�y�f�o�b�O�\���z---*/
	PrintDebugProc("\n����������������������������\n");
	PrintDebugProc("�c�e���F%d\n", g_Player[id].PFW.magazine);
	PrintDebugProc("����CT�F%d\n", g_Player[id].PFW.CT_input);
	PrintDebugProc("�����[�hCT�F%d\n", g_Player[id].PFW.CT_reload);
	const char* unko = nullptr;
	g_Player[id].PFW.empty ? unko = "[ empty ]" : unko = "�I�E�P�C";
	PrintDebugProc("�󔻒�F%s\n", unko);
	PrintDebugProc("����������������������������\n\n");

	if (GetKeyboardPress(DIK_SPACE))
	{
		CreateBullet(bulletPlayer, id);
	}

#endif	// _DEBUG
}

//************************************************
// �v���C���[�̔�e��
//************************************************
void HitPlayer(int id)
{
	// ��e��ԂłȂ���Δ�e
	g_Player[id].param.state = stateDamage_p;	// ������Ԃ�
	g_Player[id].param.motion_now = 3;			// ��e���[�V����
	g_Player[id].motion[3].id_frame = 0;		// �t���[�������Z�b�g
	g_Player[id].motion[3].id_key = 0;			// �L�[�����Z�b�g
	g_Player[id].param.dur = 100;				// �p������
	g_Player[id].param.HP--;

	// ��ʂ̐U��
	VibCamera(id);

	// ��e�G�t�F�N�g
	if (g_Player[id].param.HP > 0)
	{
		PlaySound(SOUND_LABEL_PLAYERHIT);
		CreateEffect_Heart(&g_Player[id].pos);
	}
	else
	{
		PlaySound(SOUND_LABEL_PLAYERDEAD);
		CreateEffect_Soul(&g_Player[id].pos);
	}
}

//************************************************
// �v���C���[����
//************************************************
void DamagePlayer(int id)
{
	if (g_Player[id].param.state != stateDamage_p)
	{ // ������ԂłȂ���ΏI��
		return;
	}

	/*---�y�ȉ�������Ԏ��̂݁z---*/

	// �_��
	//g_Player[id].col.a *= -1.0f;

	if(CntDuration(&g_Player[id].param.dur))
	{
		//g_Player[id].col.a = 1.0f;					// �ʏ�F��
		g_Player[id].param.state = stateNormal_p;	// �ʏ��Ԃ�
	}
}

//************************************************
// �v���C���[���S����
//************************************************
void DeadPlayer(int id)
{
	if (g_Player[id].param.HP <= 0 &&
		g_Player[id].param.state != stateDead_p)
	{ // ���C�t�������Ȃ�A���S��ԂŖ����ꍇ
		int* score = GetInfoScore();
		*score -= 100;
		/*---�y���������Ȃ̂ŕ����������[�V�����z---*/
		g_Player[id].motion[3].id_frame = 0;	// �t���[�������Z�b�g
		g_Player[id].motion[3].id_key = 0;		// �L�[�����Z�b�g

		g_Player[id].param.state = stateDead_p;	// ���S��Ԃ�
		g_Player[id].param.dur = 360;			// �K���ɃN�[���^�C��
	}

	if (g_Player[id].param.state == stateDead_p)
	{
		g_Player[id].param.dur--;	// �K���Ɍ���

		// �������o��
		if (g_Player[id].param.dur % 5 == 0)
		{
			CreateEffect_Smoke(0, &g_Player[id].pos);
		}
	}
}

//************************************************
// �v���C���[��������
//************************************************
void ResurrectPlayer(int id)
{
	if (g_Player[id].param.state == stateDead_p &&
		g_Player[id].param.dur <= 0)
	{ // ���S��ԂŁA���̌p�����Ԃ������Ȃ��

		g_Player[id].param.state = stateNormal_p;
		g_Player[id].param.HP = 3;
	}
}

//************************************************
// �v���C���[�̃��[�V�����Ǘ�
//************************************************
void MotionPlayer(int id)
{
	if (!g_Player[id].use)
	{ // ���g�p�Ȃ烊�^�[��
		return;
	}

	if (g_Player[id].param.state == stateDead_p)
	{ // ���S��ԂȂ烊�^�[��
		return;
	}

	// �Đ����i�[�p
	int* pNow = &g_Player[id].param.motion_now;				// ���݂̃��[�V�������
	int* pOld = &g_Player[id].param.motion_old;				// �ߋ��̃��[�V�������
	PlayerMotion* pMotion = &g_Player[id].motion[*pNow];	// �e�v���C���[�̃��[�V�������

	// �ύX�����m
	ChangeMotionPlayer(id, pNow, pOld);

	// �p�[�c�̓���
	MoveMotionPlayer(id, pMotion);

	// �t���[���J�E���g
	CntMotionPlayer(id, pMotion);
}

//************************************************
// �v���C���[�̃��[�V�����ύX���m
//************************************************
void ChangeMotionPlayer(int id, int* pNow, int* pOld)
{
	if (*pOld == *pNow)
	{ // �ߋ��ƌ��݂̍Đ����[�V�����������Ȃ烊�^�[��
		return;
	}

	// �ߋ��̃��[�V�����̃L�[�ƃt���[�������Z�b�g
	g_Player[id].motion[*pOld].id_key = 0;
	g_Player[id].motion[*pOld].id_frame = 0;

	// �V�������[�V�����ֈڂ������Ƃ�ۑ�
	*pOld = *pNow;
}

//************************************************
// �v���C���[�̃��[�V��������p
//************************************************
void MoveMotionPlayer(int id, PlayerMotion* pMotion)
{
	// �Đ����̃L�[�̑��t���[�������猻�݂̃t���[���ԍ�����������
	float dest = (float)(pMotion->key[pMotion->id_key].amount_frame - pMotion->id_frame);

	/*---�y���삪�K�v�ȓy��p�[�c�̂݃��[�V�����𔽉f�z---*/
	g_Player[id].parts[0].pos_moved += (pMotion->key[pMotion->id_key].dest[0].pos - g_Player[id].parts[0].pos_moved) / dest;
	g_Player[id].parts[0].rot_moved += (pMotion->key[pMotion->id_key].dest[0].rot - g_Player[id].parts[0].rot_moved) / dest;
}

//************************************************
// �v���C���[�̃��[�V�����J�E���g�p
//************************************************
void CntMotionPlayer(int id, PlayerMotion* pMotion)
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
			g_Player[id].param.motion_now = 0;
		}
	}
}

//************************************************
// �v���C���[�p�̃��[���h�}�g���b�N�X���v�Z
//************************************************
void CalcMtxPlayer(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	
	// ����for���̍ő吔���Q���l���ɕύX���Ă��܂�(����)
	for (int P_id = 0; P_id < g_nNumPlayer; P_id++)
	{
		if (!g_Player[P_id].use)
		{ // ���̔Ԏg�p�t���O�����ŃR���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player[P_id].mtxWorld);

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Player[P_id].rot.y,
			g_Player[P_id].rot.x,
			g_Player[P_id].rot.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&g_Player[P_id].mtxWorld,
			&g_Player[P_id].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Player[P_id].pos.x,
			g_Player[P_id].pos.y,
			g_Player[P_id].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Player[P_id].mtxWorld,
			&g_Player[P_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < AMOUNT_PLAYER_PARTS; Ps_id++)
		{
			if (g_Player[P_id].parts[Ps_id].pMesh == NULL)
			{ // ���g�p�Ȃ�R���e�B�j���[
				continue;
			}

			// ���̔ԃp�[�c�́u�e�p�[�c�v�̃C���f�b�N�X��ۑ�
			int IdxParent = g_Player[P_id].parts[Ps_id].IdxParent;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player[P_id].parts[Ps_id].mtxWorld);

			// ���[�V���������̔��f
			D3DXVECTOR3 PartsRot =
			{
				g_Player[P_id].parts[Ps_id].rot_offset.x + g_Player[P_id].parts[Ps_id].rot_moved.x,
				g_Player[P_id].parts[Ps_id].rot_offset.y + g_Player[P_id].parts[Ps_id].rot_moved.y,
				g_Player[P_id].parts[Ps_id].rot_offset.z + g_Player[P_id].parts[Ps_id].rot_moved.z
			};

			if (IdxParent == 0)
			{ // ���̔Ԃ̐e�p�[�c���u�y��p�[�c�v�ł���΁A�ړ������ւ̉�]��ł�����(�C������Ɏ��_��������������)
				PartsRot -= g_Player[P_id].rot;
			}

			// �����𔽉f1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				PartsRot.y,
				PartsRot.x,
				PartsRot.z);

			// �����𔽉f2
			D3DXMatrixMultiply(&g_Player[P_id].parts[Ps_id].mtxWorld,
				&g_Player[P_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// ���[�V�����ʒu�̔��f
			D3DXVECTOR3 PartsPos =
			{
				g_Player[P_id].parts[Ps_id].pos_offset.x + g_Player[P_id].parts[Ps_id].pos_moved.x,
				g_Player[P_id].parts[Ps_id].pos_offset.y + g_Player[P_id].parts[Ps_id].pos_moved.y,
				g_Player[P_id].parts[Ps_id].pos_offset.z + g_Player[P_id].parts[Ps_id].pos_moved.z
			};

			// �ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				PartsPos.x,
				PartsPos.y,
				PartsPos.z);

			// �ʒu�𔽉f
			D3DXMatrixMultiply(&g_Player[P_id].parts[Ps_id].mtxWorld,
				&g_Player[P_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// �e�̃��[���h�}�g���b�N�X���擾
			if (IdxParent == -1)
			{ // �y��p�[�c�̂݃��[���h���W�ɒ���
				mtxParent = g_Player[P_id].mtxWorld;
			}
			else if (IdxParent == 99)
			{ // ���j�p�[�c�͊e�v���C���[�̑̂̃p�[�c�ɕt��
				mtxParent = g_Player[P_id].parts[P_id + 1].mtxWorld;
			}
			else
			{ // �̂̃p�[�c�͓y��ɕt��
				mtxParent = g_Player[P_id].parts[IdxParent].mtxWorld;
			}

			// �p�[�c���Ƃ̃��[���h�}�g���b�N�X���Z�o
			D3DXMatrixMultiply(&g_Player[P_id].parts[Ps_id].mtxWorld,
				&g_Player[P_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}

		// (���Ȃ薳���̂���) �U���ʒu�̐ݒ� (��)
		for (int weapon_id = 0; weapon_id < Max_itemstyle; weapon_id++)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player[P_id].offset_atk[weapon_id].mtx);

			// �ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				g_Player[P_id].offset_atk[weapon_id].pos.x,
				g_Player[P_id].offset_atk[weapon_id].pos.y,
				g_Player[P_id].offset_atk[weapon_id].pos.z);

			// �ʒu�𔽉f
			D3DXMatrixMultiply(&g_Player[P_id].offset_atk[weapon_id].mtx,
				&g_Player[P_id].offset_atk[weapon_id].mtx,
				&mtxTrans);

			// �t������ł��낤����̃}�g���b�N�X�Ƌ����ɂ������킹��c
			D3DXMatrixMultiply(&g_Player[P_id].offset_atk[weapon_id].mtx,
				&g_Player[P_id].offset_atk[weapon_id].mtx,
				&g_Player[P_id].parts[weapon_id + 5].mtxWorld);
		}
	}
}

//************************************************
// �v���C���[�`��
//************************************************
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	// ����for���̍ő吔���Q���l���ɕύX���Ă��܂�(����)
	for (int id_P = 0; id_P < g_nNumPlayer; id_P++)
	{
		if (!g_Player[id_P].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player[id_P].mtxWorld);

		for (int id_Ps = 0; id_Ps < AMOUNT_PLAYER_PARTS; id_Ps++)
		{
			if (g_Player[id_P].parts[id_Ps].pMesh == NULL)
			{ // ����ۂȂ�R���e�B�j���[
				continue;
			}

			if (g_Player[id_P].param.state == stateDead_p)
			{ // ���S��Ԃ̂Ƃ�

				if (id_Ps != 9)
				{ // ��ȊO�̃p�[�c��`�悵�Ȃ�
					continue;
				}
			}
			else
			{ // ������Ԃ̎�

				if (id_Ps == 9)
				{ // ���`�悵�Ȃ�
					continue;
				}
			}

			if (g_Player[id_P].parts[id_Ps].style == 99 &&
				g_Player[id_P].parts[id_Ps].IdxParent == 99 &&
				g_Player[id_P].param.weapon != g_PlayerModel[id_Ps].weapon)
			{ // ���j�p�[�c�̏ꍇ�A����̎��ʂ��X�^�C�����قȂ�ƃR���e�B�j���[
				continue;
			}

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player[id_P].parts[id_Ps].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player[id_P].parts[id_Ps].pBuffMat->GetBufferPointer();

			for (int id_mat = 0; id_mat < (int)g_Player[id_P].parts[id_Ps].NumMat; id_mat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[id_mat].MatD3D);

				// �e�N�X�`���̐ݒ�
				if (g_Player[id_P].parts[id_Ps].pTex[id_mat] != NULL)
				{
					pDevice->SetTexture(0, g_Player[id_P].parts[id_Ps].pTex[id_mat]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// ���f���p�[�c�̕`��
				g_Player[id_P].parts[id_Ps].pMesh->DrawSubset(id_mat);
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//************************************************
// �g�U����ύX
//************************************************
void ChangeDiffuseColPlayer(int player_id, int parts_id, int mat_id, D3DXMATERIAL * pMat)
{
	if (parts_id == 0)
	{ // �v���C���[�{�̂̃L���^�s���p�[�c�̐F��ς���c�H
		switch (player_id)
		{
			// ��
		case 0:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			break;

			// ��
		case 1:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			break;

			// ��
		case 2:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			break
				;
			// ��
		case 3:
			pMat[mat_id].MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
			break;
		}
	}
}

//************************************************
// �v���C���[�����擾
//************************************************
Player* GetInfoPlayer(void)
{
	return &g_Player[0];
}

//************************************************
// �f�o�b�O�\��
//************************************************
void PrintDebugPlayer(void)
{
#ifdef _DEBUG

	Player* pPlayer;
	char pStr[8];

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		pPlayer = &g_Player[i];

		switch (pPlayer->param.state)
		{
		case stateNormal_p:
			snprintf(&pStr[0], 8, "�ʏ�");
			break;

		case stateMove_p:
			snprintf(&pStr[0], 8, "�ړ�");
			break;

		case stateAtk_p:
			snprintf(&pStr[0], 8, "�U��");
			break;

		case stateDamage_p:
			snprintf(&pStr[0], 8, "��e");
			break;

		case stateDead_p:
			snprintf(&pStr[0], 8, "���S");
			break;

		default:

			// �G���[
			assert(false && "�����ꂩ�̃v���C���[��ԂɃG���[");

			break;
		}

		PrintDebugProc("�y%dP�z\nstate : %s\n", i, &pStr[0]);	// �X�e�[�^�X
		PrintDebugProc("HP : %d\n", pPlayer->param.HP);			// �̗�
		PrintDebugProc("SPD : %f\n", pPlayer->param.SPD);		// ���x
	}

#endif	// _DEBUG
}

//************************************************
// �U�����̔���
//************************************************
//void RecoilPlayer(int id)
//{
//
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �v���C���[�p���f���̃N���A
//************************************************
void ClearInfoPlayerModel(void)
{
	PlayerModel* pModel = &g_PlayerModel[0];
	
	for (int i = 0; i < AMOUNT_PLAYER_PARTS; i++, pModel++)
	{
		pModel->style = 0;
		pModel->weapon = 0;
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;
		pModel->pos_offset = { 0.0f, 0.0f, 0.0f };
		pModel->pos_moved = { 0.0f, 0.0f, 0.0f };
		pModel->rot_offset = { 0.0f, 0.0f, 0.0f };
		pModel->rot_moved = { 0.0f, 0.0f, 0.0f };

		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			pModel->pTex[j] = NULL;
		}

		pModel->IdxParent = 0;
	}
}

//************************************************
// �v���C���[�p���[�V�����̃N���A
//************************************************
void ClearInfoPlayerMotion(void)
{
	PlayerMotion* pMotion = &g_PlayerMotion[0];

	for (int i = 0; i < 8; i++, pMotion++)
	{
		pMotion->loop = 0;
		pMotion->amount_key = 0;
		pMotion->id_key = 0;
		pMotion->id_frame = 0;

		for (int j = 0; j < 16; j++)
		{
			pMotion->key[j].amount_frame = 0;

			for (int k = 0; k < AMOUNT_PLAYER_PARTS; k++)
			{
				pMotion->key[j].dest[k].pos = { 0.0f, 0.0f, 0.0f };
				pMotion->key[j].dest[k].rot = { 0.0f, 0.0f, 0.0f };
			}
		}
	}
}

//************************************************
// �v���C���[���̃N���A
//************************************************
void ClearInfoPlayer(void)
{
	Player* pPlayer = &g_Player[0];

	for (int i = 0; i < MAX_PLAYER; i++)
	{
		pPlayer->use = false;
		pPlayer->param = { 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 0 };	// �����o�[���̓w�b�_�t�@�C�����m�F���ĉ�����
		pPlayer->PFW = { 0, 0, 0, 0, true };	// �����o�[(ry
		pPlayer->pos = { 0.0f, 0.0f, 0.0f };
		pPlayer->pos_old = { 0.0f, 0.0f, 0.0f };
		pPlayer->move = { 0.0f, 0.0f, 0.0f };
		pPlayer->rot = { 0.0f, 0.0f, 0.0f };
		pPlayer->rot_goal = { 0.0f, 0.0f, 0.0f };
		pPlayer->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		for (int j = 0; j < Max_itemstyle; j++)
		{
			pPlayer->offset_atk[j].pos = { 0.0f, 0.0f, 0.0f };
		}

		for (int j = 0; j < AMOUNT_PLAYER_PARTS; j++)
		{
			pPlayer->parts[j].style = 0;
			pPlayer->parts[j].weapon = 0;
			pPlayer->parts[j].pMesh = NULL;
			pPlayer->parts[j].pBuffMat = NULL;
			pPlayer->parts[j].NumMat = 0;
			pPlayer->parts[j].pos_offset = { 0.0f, 0.0f, 0.0f };
			pPlayer->parts[j].pos_moved = { 0.0f, 0.0f, 0.0f };
			pPlayer->parts[j].rot_offset = { 0.0f, 0.0f, 0.0f };
			pPlayer->parts[j].rot_moved = { 0.0f, 0.0f, 0.0f };

			for (int k = 0; k < AMOUNT_MAT; k++)
			{
				pPlayer->parts[j].pTex[k] = NULL;
			}

			pPlayer->parts[j].IdxParent = 0;
		}

		pPlayer->id_shadow = 0;
		pPlayer->id_sph = 0;
	}
}