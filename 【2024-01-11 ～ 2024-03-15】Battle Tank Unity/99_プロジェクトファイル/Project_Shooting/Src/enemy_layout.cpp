#ifdef _DEBUG	// ��ԉ��܂�

//************************************************
//
// �G�l�~�[�z�u�p[enemy_layout.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "enemy_layout.h"

// �V�X�e���n
#include "input.h"

// ������
#include "debugproc.h"
#include "enemy_camera.h"
#include <assert.h>

/*---�y�}�N����`�z---*/
#define MAX_EN 256		// �ő�z�u��
#define MAX_MODELEN 42	// �ő僂�f����

/*---�y�O���[�o���ϐ��z---*/
EnemyModel g_modelEN[MAX_MODELEN];	// �G�p���f��
Enemy g_EN[MAX_EN];					// �G�z�u�p���
Enemy g_tempEN;						// ���̓G�z�u��p

bool g_OW_EN = false;	// �z�u�F�㏑�����[�h�؂�ւ�
int g_selectEN = 0;		// �㏑�����̑I��ԍ�

/*---�y�v���g�^�C�v�錾�z---*/
void ClearInfo_modelEN(void);	// �G�p���f�����N���A
void ClearInfo_EN(void);		// �G�z�u�����N���A
void ClearInfo_tempEN(void);	// ���̓G�z�u�����N���A

void ImportInfo_modelEN(void);								// �G�p���f�����擾
void ImportOffset_modelEN(FILE* pFile, int AmountModel);	// �G�p���f���I�t�Z�b�g���擾
void ImportLayout_EN(void);									// �G�z�u�����擾
void VerifyStyle_EN(int id);								// �X�^�C�����ƍ�
void VerifyStyle_tempEN(void);								// ���z�G�̃X�^�C�����ƍ�

void Uninit_modelEN(void);	// �G�p���f���̔j��

int GetMaxEnabled(void);	// �g�p�����擾
void Delete_EN(void);		// ����
void SortArray_EN(void);	// �z��\�[�g
void ChangeSelect_EN(void);	// �Ώۂ�ύX
void ChangeStyle_EN(void);	// �X�^�C����ύX
void ChangeParam_EN(void);	// �p�����[�^��ύX
void Rotate_EN(void);		// ��]
void Translate_EN(void);	// �ړ�
void CalcMtx_EN(void);		// �G�̍s��v�Z
void CalcMtx_tempEN(void);	// ���z�G�̍s��v�Z
void Save_tempEN(void);		// ���z�G��ۑ�

void Draw_modelEN(void);	// �G�p���f���̕`��
void Draw_tempEN(void);		// ���z�̓G�p���f���̕`��

void ExportLayout_EN(void);	// �z�u����ۑ�
void PrintDebug_EN(void);	// �f�o�b�O�\��

//************************************************
// ����
//************************************************
void Init_EN(void)
{
	g_OW_EN = false;	// �z�u�F�㏑�����[�h�؂�ւ�
	g_selectEN = 0;		// �㏑�����̑I��ԍ�

	// �G�p���f�����N���A
	ClearInfo_modelEN();

	// �G�z�u�����N���A
	ClearInfo_EN();

	// ���̓G�z�u�����N���A
	ClearInfo_tempEN();

	// �G�p���f���̎擾
	ImportInfo_modelEN();

	// �G�z�u�����擾
	ImportLayout_EN();

	// ���z�G�̃X�^�C���ƍ�
	VerifyStyle_tempEN();
}

//************************************************
// �I��
//************************************************
void Uninit_EN(void)
{
	// �G�p���f����j��
	Uninit_modelEN();
}

//************************************************
// �X�V
//************************************************
void Update_EN(void)
{
	if (GetKeyboardTrigger(DIK_F3))
	{
		// �z�u����ۑ�
		ExportLayout_EN();
	}

	if (GetKeyboardTrigger(DIK_F5))
	{
		// �z�u�F�㏑�����[�h�ύX
		g_OW_EN = !g_OW_EN;
	}

	// ����
	Delete_EN();

	// �Ώۂ�ύX
	ChangeSelect_EN();

	// �X�^�C����ύX
	ChangeStyle_EN();

	// �p�����[�^��ύX
	ChangeParam_EN();

	// ��]
	Rotate_EN();

	// �ړ�
	Translate_EN();

	// �s��v�Z
	CalcMtx_EN();

	// ���z�̍s��v�Z
	CalcMtx_tempEN();

	// �ۑ�
	Save_tempEN();

	// �f�o�b�O�\��
	PrintDebug_EN();
}

//************************************************
// �`��
//************************************************
void Draw_EN(void)
{
	// �G�p���f���̕`��
	Draw_modelEN();

	// ���z�̓G�p���f���̕`��
	Draw_tempEN();
}

//************************************************
// �G�z�u���̎擾
//************************************************
Enemy GetInfo_targetEN(void)
{
	Enemy* pEN = nullptr;	// ���쎯�ʗp

	// ���[�h�ɉ����ĎQ�ƑΏۂ�ύX
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	return *pEN;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �G�p���f�����N���A
//************************************************
void ClearInfo_modelEN(void)
{
	EnemyModel* pModel = &g_modelEN[0];

	for (int i = 0; i < MAX_MODELEN; i++)
	{ // �G�l�~�[�p���f�����̂ЂȌ`�̃��Z�b�g

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
		pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �e�C���f�b�N�X
		pModel->IdxParent = -1;
	}
}

//************************************************
// �G�z�u�����N���A
//************************************************
void ClearInfo_EN(void)
{
	Enemy* pEnemy = &g_EN[0];

	for (int i = 0; i < MAX_EN; i++, pEnemy++)
	{
		// �g�p�t���O
		pEnemy->use = false;

		// �p�����[�^
		pEnemy->param =
		{
			0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, { 0.0f, 0.0f, 0.0f } ,0 ,0		// �����o�[���̓w�b�_�t�@�C�����m�F���ĉ�����
		};

		// ���W�n
		pEnemy->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �F
		pEnemy->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		for (int j = 0; j < MAX_MODELEN; j++)
		{ // �e�p�[�c�������Z�b�g
			EnemyModel* pModel = &pEnemy->parts[j];

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
		}

		// ���ʔԍ�
		pEnemy->id_shadow = 0;
		pEnemy->id_sph = 0;
	}
}

//************************************************
// ���̓G�z�u�����N���A
//************************************************
void ClearInfo_tempEN(void)
{
	// �g�p�t���O
	g_tempEN.use = false;

	// �p�����[�^
	g_tempEN.param =
	{
		0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, { 0.0f, 0.0f, 0.0f } ,0 ,0	// �����o�[���̓w�b�_�t�@�C�����m�F���ĉ�����
	};

	// ���W�n
	g_tempEN.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_tempEN.pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_tempEN.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_tempEN.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_tempEN.rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_tempEN.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �F
	g_tempEN.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int j = 0; j < MAX_MODELEN; j++)
	{ // �e�p�[�c�������Z�b�g
		EnemyModel* pModel = &g_tempEN.parts[j];

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
	}

	// ���ʔԍ�
	g_tempEN.id_shadow = 0;
	g_tempEN.id_sph = 0;
}

//************************************************
// �G�p���f�����擾
//************************************************
void ImportInfo_modelEN(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int AmountModel = 0;		// ���f���̐����i�[
	int id_Model = 0;			// ���f���̎��ʗp

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�G�l�~�[���f�����̓W�J�Ɏ��s");

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
		assert(AmountModel < MAX_MODELEN && "�G�l�~�[���f�����f����񂪍ő�ʂ��z���܂���");

#endif

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s %s", &FileString[0], 2, &FileString[0], 128);

			// �ǂݍ��񂾏����ЂȌ`�ɂ̂݃R�s�[����
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_modelEN[id_Model].pBuffMat,
				NULL,
				&g_modelEN[id_Model].NumMat,
				&g_modelEN[id_Model].pMesh);

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == AmountModel)
			{ // ���f�������ǂݎ��I���ƏI��
				break;
			}
		}
	}

	// �e���f���̃I�t�Z�b�g�����擾
	ImportOffset_modelEN(pFile, AmountModel);
}

//************************************************
// �G�p���f���I�t�Z�b�g���擾
//************************************************
void ImportOffset_modelEN(FILE* pFile, int AmountModel)
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
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &Style);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // �e�̃C���f�b�N�X���擾	
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
			g_modelEN[id_Model].style = Style;
			g_modelEN[id_Model].IdxParent = IdxParent;
			g_modelEN[id_Model].pos_offset = pos;
			g_modelEN[id_Model].rot_offset = rot;

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == AmountModel)
			{ // ���f�������ǂݎ��I���ƏI��
				break;
			}
		}
	}
}

//************************************************
// �z�u�����擾
//************************************************
void ImportLayout_EN(void)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int i = 0;					// �ėp����
	int phase = 0;				// �t�F�[�Y���i�[
	int appear = 0;				// �o���^�C�~���O���i�[
	int style = 0;				// �X�^�C�����i�[
	int hp = 0;					// ���C�t���i�[
	float spd = 0;				// ���x���i�[
	float rad = 0;				// ����T�C�Y���i�[
	D3DXVECTOR3 pos, rot;		// �ʒu�ƌ������i�[

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_param.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�G�l�~�[�p�����[�^���̓W�J�Ɏ��s");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "PHASE") == 0)
		{ // �o���t�F�[�Y���擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &phase);
		}

		if (strcmp(&FileString[0], "APPEAR") == 0)
		{ // �o���^�C�~���O���擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &appear);
		}

		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // �X�^�C�����擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &style);
		}

		if (strcmp(&FileString[0], "HP") == 0)
		{ // ���C�t���擾
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &hp);
		}

		if (strcmp(&FileString[0], "SPD") == 0)
		{ // ���x���擾
			fscanf_s(pFile, "%s %f", &FileString[0], 2, &spd);
		}

		if (strcmp(&FileString[0], "RAD") == 0)
		{ // ����T�C�Y���擾
			fscanf_s(pFile, "%s %f", &FileString[0], 2, &rad);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu���擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �������擾
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARAMSET") == 0)
		{ // �擾�������𔽉f

			g_EN[i].param =
			{
				phase, appear, style, 0, 0, -1, hp, spd, rad, { 0.0f, 0.0f, 0.0f }, 0, 0
			};
			g_EN[i].pos = pos;
			g_EN[i].rot = rot;

			g_EN[i].use = true;	// ����ɂ��`���ԂƂȂ�

			// �X�^�C���ԍ����ƍ�
			VerifyStyle_EN(i);

			i++;	// ���̔ԍ���

			if (i >= MAX_EN)
			{ // �G�̍ő吔���z����Ƌ����I��
				break;
			}
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{
			break;	// �I��
		}
	}
}

//************************************************
// �X�^�C���ԍ��̏ƍ�
//************************************************
void VerifyStyle_EN(int id)
{
	for (int i = 0; i < MAX_MODELEN; i++)
	{
		if (g_EN[id].param.style == g_modelEN[i].style)
		{ // �e�G�l�~�[�̃X�^�C���ƑS�p�[�c�̃X�^�C�����ƍ�

			g_EN[id].parts[i] = g_modelEN[i];	// �ԍ��̈�v���Ă���p�[�c�̂ݗL����
		}
		else
		{ // ����ȊO�̗]�v�Ȃ��͍̂폜

			// ���f��
			g_EN[id].parts[i].pMesh = NULL;
			g_EN[id].parts[i].pBuffMat = NULL;
			g_EN[id].parts[i].NumMat = 0;

			for (int j = 0; j < AMOUNT_MAT; j++)
			{ // �}�e���A��

				g_EN[id].parts[i].pTex[j] = NULL;
			}

			// ���f�����W
			g_EN[id].parts[i].pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_EN[id].parts[i].pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_EN[id].parts[i].rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_EN[id].parts[i].rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �e�C���f�b�N�X
			g_EN[id].parts[i].IdxParent = -1;
		}
	}
}

//************************************************
// ���z�G�̃X�^�C���ԍ��̏ƍ�
//************************************************
void VerifyStyle_tempEN(void)
{
	for (int i = 0; i < MAX_MODELEN; i++)
	{
		if (g_tempEN.param.style == g_modelEN[i].style)
		{ // �e�G�l�~�[�̃X�^�C���ƑS�p�[�c�̃X�^�C�����ƍ�

			g_tempEN.parts[i] = g_modelEN[i];	// �ԍ��̈�v���Ă���p�[�c�̂ݗL����
		}
		else
		{ // ����ȊO�̗]�v�Ȃ��͍̂폜

			// ���f��
			g_tempEN.parts[i].pMesh = NULL;
			g_tempEN.parts[i].pBuffMat = NULL;
			g_tempEN.parts[i].NumMat = 0;

			for (int j = 0; j < AMOUNT_MAT; j++)
			{ // �}�e���A��

				g_tempEN.parts[i].pTex[j] = NULL;
			}

			// ���f�����W
			g_tempEN.parts[i].pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_tempEN.parts[i].pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_tempEN.parts[i].rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_tempEN.parts[i].rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �e�C���f�b�N�X
			g_tempEN.parts[i].IdxParent = -1;
		}
	}
}

//************************************************
// �g�p�����擾
//************************************************
int GetMaxEnabled(void)
{
	int max = 0;	// �ő吔�i�[

	// �g�p����Ă��鑍�����擾
	for (int i = 0; i < MAX_EN; i++)
	{
		if (g_EN[i].use)
		{
			max++;
		}
	}

	return max;
}

//************************************************
// �G�̃��f������j��
//************************************************
void Uninit_modelEN(void)
{
	for (int i = 0; i < MAX_MODELEN; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_modelEN[i].pTex[j] != NULL)
			{ // �e�N�X�`���̔j��

				g_modelEN[i].pTex[j]->Release();
				g_modelEN[i].pTex[j] = NULL;
			}
		}

		if (g_modelEN[i].pMesh != NULL)
		{ // ���b�V���̔j��

			g_modelEN[i].pMesh->Release();
			g_modelEN[i].pMesh = NULL;
		}

		if (g_modelEN[i].pBuffMat != NULL)
		{ // �}�e���A���̔j��

			g_modelEN[i].pBuffMat->Release();
			g_modelEN[i].pBuffMat = NULL;
		}
	}
}

//************************************************
// ����
//************************************************
void Delete_EN(void)
{
	if (!g_OW_EN)
	{ // �㏑�����[�h�łȂ���΃��^�[��

		return;
	}

	if (GetKeyboardTrigger(DIK_BACK))
	{
		int max = GetMaxEnabled();	// �g�p�����擾

		if (max <= 0)
		{ // �����g�p����Ă��Ȃ���ΏI��

			return;
		}

		g_EN[g_selectEN].use = false;

		// �p�����[�^
		g_EN[g_selectEN].param =
		{
			0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, { 0.0f, 0.0f, 0.0f } ,0 ,0	// �����o�[���̓w�b�_�t�@�C�����m�F���ĉ�����
		};

		// ���W�n
		g_EN[g_selectEN].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EN[g_selectEN].pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EN[g_selectEN].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EN[g_selectEN].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EN[g_selectEN].rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EN[g_selectEN].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �F
		g_EN[g_selectEN].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		for (int i = 0; i < MAX_MODELEN; i++)
		{ // �e�p�[�c�������Z�b�g
			
			EnemyModel* pModel = &g_EN[g_selectEN].parts[i];

			// ���f��
			pModel->pMesh = NULL;
			pModel->pBuffMat = NULL;
			pModel->NumMat = 0;

			for (int j = 0; j < AMOUNT_MAT; j++)
			{ // �}�e���A��

				pModel->pTex[j] = NULL;
			}

			// ���f�����W
			pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �e�C���f�b�N�X
			pModel->IdxParent = -1;
		}

		// ���ʔԍ�
		g_EN[g_selectEN].id_shadow = 0;
		g_EN[g_selectEN].id_sph = 0;

		if (g_selectEN == max - 1)
		{ // �����\��̔Ԃ��ō��Ԃ̏ꍇ�A�I����1�߂��Ă���

			g_selectEN = max - 2;
		}
	}

	// �z��\�[�g
	SortArray_EN();
}

//************************************************
// �z��\�[�g
//************************************************
void SortArray_EN(void)
{
	for (int i = 0; i < MAX_EN - 1; i++)
	{
		if (!g_EN[i].use && g_EN[i + 1].use)
		{ // ���̔Ԃ����g�p�ŁA���̔Ԃ��g�p���̏ꍇ

			// ���𔽓]�����Ă���
			Enemy EN = g_EN[i];
			g_EN[i] = g_EN[i + 1];
			g_EN[i + 1] = EN;
		}
	}
}

//************************************************
// �Ώۂ�ύX
//************************************************
void ChangeSelect_EN(void)
{
	if (!g_OW_EN)
	{ // �㏑�����[�h�łȂ���΃��^�[��

		return;
	}

	int max = GetMaxEnabled();	// �g�p�����擾

	if (GetKeyboardTrigger(DIK_PERIOD))
	{
		g_selectEN < max - 1 ? g_selectEN++ : g_selectEN = 0;
	}
	else if (GetKeyboardTrigger(DIK_COMMA))
	{
		g_selectEN > 0 ? g_selectEN-- : g_selectEN = max - 1;
	}

	if (GetKeyboardPress(DIK_Z))
	{
		g_selectEN < max - 1 ? g_selectEN++ : g_selectEN = 0;
	}
	else if (GetKeyboardPress(DIK_X))
	{
		g_selectEN > 0 ? g_selectEN-- : g_selectEN = max - 1;
	}
}

//************************************************
// �X�^�C����ύX
//************************************************
void ChangeStyle_EN(void)
{
	Enemy* pEN = nullptr;	// ���쎯�ʗp

	// ���[�h�ɉ����đ���Ώۂ�ύX
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	int max = 3;	// �ő吔�i�[

	// �X�^�C���̕ύX
	if (GetKeyboardTrigger(DIK_RSHIFT))
	{
		pEN->param.style < max - 1 ? pEN->param.style++ : pEN->param.style = 0;

		g_OW_EN ? VerifyStyle_EN(g_selectEN) : VerifyStyle_tempEN();
	}
	else if (GetKeyboardTrigger(DIK_LSHIFT))
	{
		pEN->param.style > 0 ? pEN->param.style-- : pEN->param.style = max - 1;

		g_OW_EN ? VerifyStyle_EN(g_selectEN) : VerifyStyle_tempEN();
	}

	assert(pEN->param.style >= 0 && pEN->param.style < max && "�X�^�C���̕ύX���s");
}

//************************************************
// �p�����[�^��ύX
//************************************************
void ChangeParam_EN(void)
{
	Enemy* pEN = nullptr;	// ���쎯�ʗp

	// ���[�h�ɉ����đ���Ώۂ�ύX
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	// �t�F�[�Y��ύX
	if (GetKeyboardTrigger(DIK_1))
	{
		pEN->param.phase > 0 ? pEN->param.phase-- : pEN->param.phase = 4;
	}
	else if (GetKeyboardTrigger(DIK_2))
	{
		pEN->param.phase < 4 ? pEN->param.phase++ : pEN->param.phase = 0;
	}

	// �o��CT��ύX
	if (GetKeyboardTrigger(DIK_3))
	{
		if (pEN->param.appear > 0)
		{
			pEN->param.appear--;
		}
	}
	else if (GetKeyboardTrigger(DIK_4))
	{
		pEN->param.appear++;
	}

	// �o��CT��啝�ύX
	if (GetKeyboardPress(DIK_5))
	{
		if (pEN->param.appear > 0)
		{
			pEN->param.appear--;
		}
	}
	else if (GetKeyboardPress(DIK_6))
	{
		pEN->param.appear++;
	}

	// �̗͂�ύX
	if (GetKeyboardTrigger(DIK_7))
	{
		if (pEN->param.HP > 0)
		{
			pEN->param.HP--;
		}
	}
	else if (GetKeyboardTrigger(DIK_8))
	{
		pEN->param.HP++;
	}

	// ���x��ύX
	if (GetKeyboardTrigger(DIK_9))
	{
		if (pEN->param.SPD > 0.0f)
		{
			pEN->param.SPD -= 1.0f;
		}
	}
	else if (GetKeyboardTrigger(DIK_0))
	{
		pEN->param.SPD += 1.0f;
	}
}

//************************************************
// ��]
//************************************************
void Rotate_EN(void)
{
	Enemy* pEN = nullptr;	// ���쎯�ʗp

	// ���[�h�ɉ����đ���Ώۂ�ύX
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	// X���ɉ�]
	if (GetKeyboardPress(DIK_R))
	{
		pEN->rot.x += 0.05f;
	}
	else if (GetKeyboardPress(DIK_F))
	{
		pEN->rot.x -= 0.05f;
	}
	else if (GetKeyboardTrigger(DIK_V))
	{
		pEN->rot.x = 0.0f;
	}

	// Y���ɉ�]
	if (GetKeyboardPress(DIK_T))
	{
		pEN->rot.y += 0.05f;
	}
	else if (GetKeyboardPress(DIK_G))
	{
		pEN->rot.y -= 0.05f;
	}
	else if (GetKeyboardTrigger(DIK_B))
	{
		pEN->rot.y = 0.0f;
	}

	// Z���ɉ�]
	if (GetKeyboardPress(DIK_Y))
	{
		pEN->rot.z += 0.05f;
	}
	else if (GetKeyboardPress(DIK_H))
	{
		pEN->rot.z -= 0.05f;
	}
	else if (GetKeyboardTrigger(DIK_N))
	{
		pEN->rot.z = 0.0f;
	}

	// X���Ɉ��l
	if (GetKeyboardTrigger(DIK_U))
	{
		pEN->rot.x += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_J))
	{
		pEN->rot.x -= D3DX_PI * 0.025f;
	}

	// Y���Ɉ��l
	if (GetKeyboardTrigger(DIK_I))
	{
		pEN->rot.y += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_K))
	{
		pEN->rot.y -= D3DX_PI * 0.025f;
	}

	// Z���Ɉ��l
	if (GetKeyboardTrigger(DIK_O))
	{
		pEN->rot.z += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_L))
	{
		pEN->rot.z -= D3DX_PI * 0.025f;
	}
}

//************************************************
// �ړ�
//************************************************
void Translate_EN(void)
{
	Enemy* pEN = nullptr;				// ���쎯�ʗp
	bool move = false;					// �ړ��p
	float X = 0.0f;						// ���E�̈ړ�����
	float Z = 0.0f;						// �O��̈ړ�����
	const ENC* pENC = GetInfo_ENC();	// �J���������擾

	// ���[�h�ɉ����đ���Ώۂ�ύX
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	// ���E
	if (GetKeyboardPress(DIK_A))
	{
		X = -1.0f;
	}
	else if (GetKeyboardPress(DIK_D))
	{
		X = 1.0f;
	}

	// �O��
	if (GetKeyboardPress(DIK_W))
	{
		Z = 1.0f;
	}
	else if (GetKeyboardPress(DIK_S))
	{
		Z = -1.0f;
	}

	// �㉺
	if (GetKeyboardPress(DIK_LBRACKET))
	{
		pEN->pos.y += 5.0f;
	}
	else if (GetKeyboardPress(DIK_RBRACKET))
	{
		pEN->pos.y -= 5.0f;
	}
	else if (GetKeyboardTrigger(DIK_YEN))
	{
		pEN->pos.y = 0.0f;
	}

	// int�ւ̃L���X�g�𗘗p���ď���������؂�̂Ă邽�ߌx��������
#pragma warning(disable:4244)

	// �[������
	if (GetKeyboardTrigger(DIK_MINUS))
	{
		pEN->pos.x = (int)pEN->pos.x;
	}
	else if (GetKeyboardTrigger(DIK_CIRCUMFLEX))
	{
		pEN->pos.z = (int)pEN->pos.z;
	}

#pragma warning(default:4244)

	// ���E���l
	if (GetKeyboardTrigger(DIK_NUMPAD4))
	{
		X = -1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD6))
	{
		X = 1.0f;
	}

	// �O����l
	if (!GetKeyboardPress(DIK_LALT))
	{ /*---�y�f�o�b�O�\���̃X�N���[���Ƃ̌��ˍ����̂��߁z---*/

		if (GetKeyboardTrigger(DIK_NUMPAD8))
		{
			Z = 1.0f;
		}
		else if (GetKeyboardTrigger(DIK_NUMPAD5))
		{
			Z = -1.0f;
		}
	}

	// �㉺���l
	if (GetKeyboardTrigger(DIK_NUMPAD2))
	{
		pEN->pos.y += 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD0))
	{
		pEN->pos.y -= 1.0f;
	}

	if (X != 0.0f || Z != 0.0f)
	{ // ��������͂��Ă���Έړ����Ă��锻��
		move = true;
	}

	if (move)
	{
		// �ړ��ʂƖڕW���p��ݒ�
		pEN->pos.x += sinf(atan2f(X, Z) + pENC->rot.y) * 5.0f;
		pEN->pos.z += cosf(atan2f(X, Z) + pENC->rot.y) * 5.0f;
	}
}

//************************************************
// �G�z�u�p�̍s����v�Z
//************************************************
void CalcMtx_EN(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	for (int enemy_id = 0; enemy_id < MAX_EN; enemy_id++)
	{
		if (!g_EN[enemy_id].use)
		{ // ���̔Ԃ̎g�p�t���O�������ŃR���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_EN[enemy_id].mtxWorld);

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_EN[enemy_id].rot.y,
			g_EN[enemy_id].rot.x,
			g_EN[enemy_id].rot.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&g_EN[enemy_id].mtxWorld,
			&g_EN[enemy_id].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_EN[enemy_id].pos.x,
			g_EN[enemy_id].pos.y,
			g_EN[enemy_id].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_EN[enemy_id].mtxWorld,
			&g_EN[enemy_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < MAX_MODELEN; Ps_id++)
		{
			if (g_EN[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // ����ۂȂ�R���e�B�j���[
				continue;
			}

			// ���̔ԃp�[�c�́u�e�p�[�c�v�̃C���f�b�N�X��ۑ�
			int IdxParent = g_EN[enemy_id].parts[Ps_id].IdxParent;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_EN[enemy_id].parts[Ps_id].mtxWorld);

			// �����𔽉f1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_EN[enemy_id].parts[Ps_id].rot_offset.y,
				g_EN[enemy_id].parts[Ps_id].rot_offset.x,
				g_EN[enemy_id].parts[Ps_id].rot_offset.z);

			// �����𔽉f2
			D3DXMatrixMultiply(&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				g_EN[enemy_id].parts[Ps_id].pos_offset.x,
				g_EN[enemy_id].parts[Ps_id].pos_offset.y,
				g_EN[enemy_id].parts[Ps_id].pos_offset.z);

			// �ʒu�𔽉f
			D3DXMatrixMultiply(&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// �e�̃��[���h�}�g���b�N�X���擾
			if (IdxParent == -1)
			{ //���C���p�[�c�̂݃��[���h���W�ɒ���
				mtxParent = g_EN[enemy_id].mtxWorld;
			}
			else
			{ //���̑��p�[�c�͂��ꂼ��̐e�p�[�c�֕t��
				mtxParent = g_EN[enemy_id].parts[IdxParent].mtxWorld;
			}

			// �p�[�c���Ƃ̃��[���h�}�g���b�N�X���Z�o
			D3DXMatrixMultiply(&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}
	}
}

//************************************************
// ���z�G�̍s��v�Z
//************************************************
void CalcMtx_tempEN(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_tempEN.mtxWorld);

	// �����𔽉f1
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_tempEN.rot.y,
		g_tempEN.rot.x,
		g_tempEN.rot.z);

	// �����𔽉f2
	D3DXMatrixMultiply(&g_tempEN.mtxWorld,
		&g_tempEN.mtxWorld,
		&mtxRot);

	// �ʒu�𔽉f1
	D3DXMatrixTranslation(&mtxTrans,
		g_tempEN.pos.x,
		g_tempEN.pos.y,
		g_tempEN.pos.z);

	// �ʒu�𔽉f2
	D3DXMatrixMultiply(&g_tempEN.mtxWorld,
		&g_tempEN.mtxWorld,
		&mtxTrans);

	for (int Ps_id = 0; Ps_id < MAX_MODELEN; Ps_id++)
	{
		if (g_tempEN.parts[Ps_id].pMesh == NULL)
		{ // ����ۂȂ�R���e�B�j���[
			continue;
		}

		// ���̔ԃp�[�c�́u�e�p�[�c�v�̃C���f�b�N�X��ۑ�
		int IdxParent = g_tempEN.parts[Ps_id].IdxParent;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_tempEN.parts[Ps_id].mtxWorld);

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_tempEN.parts[Ps_id].rot_offset.y,
			g_tempEN.parts[Ps_id].rot_offset.x,
			g_tempEN.parts[Ps_id].rot_offset.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&g_tempEN.parts[Ps_id].mtxWorld,
			&g_tempEN.parts[Ps_id].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_tempEN.parts[Ps_id].pos_offset.x,
			g_tempEN.parts[Ps_id].pos_offset.y,
			g_tempEN.parts[Ps_id].pos_offset.z);

		// �ʒu�𔽉f
		D3DXMatrixMultiply(&g_tempEN.parts[Ps_id].mtxWorld,
			&g_tempEN.parts[Ps_id].mtxWorld,
			&mtxTrans);

		D3DXMATRIX mtxParent = {};

		// �e�̃��[���h�}�g���b�N�X���擾
		if (IdxParent == -1)
		{ //���C���p�[�c�̂݃��[���h���W�ɒ���
			mtxParent = g_tempEN.mtxWorld;
		}
		else
		{ //���̑��p�[�c�͂��ꂼ��̐e�p�[�c�֕t��
			mtxParent = g_tempEN.parts[IdxParent].mtxWorld;
		}

		// �p�[�c���Ƃ̃��[���h�}�g���b�N�X���Z�o
		D3DXMatrixMultiply(&g_tempEN.parts[Ps_id].mtxWorld,
			&g_tempEN.parts[Ps_id].mtxWorld,
			&mtxParent);
	}
}

//************************************************
// ���z�G��ۑ�
//************************************************
void Save_tempEN(void)
{
	if (g_OW_EN)
	{ // �z�u���[�h�łȂ���΃��^�[��

		return;
	}

	// ���z�G���A�ʏ�̓G�Ƃ��Ĕz�u
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		for (int i = 0; i < MAX_EN; i++)
		{
			if (g_EN[i].use)
			{ // �g�p����Ă���΃R���e�B�j���[
				continue;
			}

			g_EN[i] = g_tempEN;	// �V���ɏ���ۑ�

			g_EN[i].use = true;	// ���̃��f���̎g�p������o��

			break;
		}
	}
}

//************************************************
// �G�p���f���̕`��
//************************************************
void Draw_modelEN(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int id_enemy = 0; id_enemy < MAX_EN; id_enemy++)
	{
		if (!g_EN[id_enemy].use)
		{ // ���̔Ԃ̎g�p�t���O�������ŃR���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_EN[id_enemy].mtxWorld);

		for (int id_Ps = 0; id_Ps < MAX_MODELEN; id_Ps++)
		{
			if (g_EN[id_enemy].parts[id_Ps].pMesh == NULL)
			{ // �p�[�c�����g�p�Ȃ�R���e�B�j���[
				continue;
			}

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_EN[id_enemy].parts[id_Ps].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_EN[id_enemy].parts[id_Ps].pBuffMat->GetBufferPointer();

			for (int id_mat = 0; id_mat < (int)g_EN[id_enemy].parts[id_Ps].NumMat; id_mat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[id_mat].MatD3D);

				// �e�N�X�`���̐ݒ�
				if (g_EN[id_enemy].parts[id_Ps].pTex[id_mat] != NULL)
				{
					pDevice->SetTexture(0, g_EN[id_enemy].parts[id_Ps].pTex[id_mat]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// ���f���p�[�c�̕`��
				g_EN[id_enemy].parts[id_Ps].pMesh->DrawSubset(id_mat);
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//************************************************
// ���z�̓G�p���f���̕`��
//************************************************
void Draw_tempEN(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_tempEN.mtxWorld);

	for (int id_Ps = 0; id_Ps < MAX_MODELEN; id_Ps++)
	{
		if (g_tempEN.parts[id_Ps].pMesh == NULL)
		{ // �p�[�c�����g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_tempEN.parts[id_Ps].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_tempEN.parts[id_Ps].pBuffMat->GetBufferPointer();

		for (int id_mat = 0; id_mat < (int)g_tempEN.parts[id_Ps].NumMat; id_mat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[id_mat].MatD3D);

			// �e�N�X�`���̐ݒ�
			if (g_tempEN.parts[id_Ps].pTex[id_mat] != NULL)
			{
				pDevice->SetTexture(0, g_tempEN.parts[id_Ps].pTex[id_mat]);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			// ���f���p�[�c�̕`��
			g_tempEN.parts[id_Ps].pMesh->DrawSubset(id_mat);
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//************************************************
// �z�u����ۑ�
//************************************************
void ExportLayout_EN(void)
{
	FILE* pFile = NULL;
	D3DXVECTOR3 rot = {};	// �v�Z�p

	// �ۑ�����t�@�C�����w��A������΍쐬
	fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_param_export.txt", "w");
 
	for (int phase = 0; phase < 5; phase++)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �t�F�[�Y [ %d ]\n", phase);
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		for (int i = 0; i < MAX_EN; i++)
		{
			if (!g_EN[i].use)
			{ // ���g�p�Ȃ�R���e�B�j���[
				continue;
			}

			if (g_EN[i].param.phase != phase)
			{ // �t�F�[�Y���قȂ�΃R���e�B�j���[
				continue;
			}

			// �ʓx��x���ɕϊ�
			rot = (g_EN[i].rot * 180.0f) / D3DX_PI;

			fprintf(pFile, "PARAMSET\n");
			fprintf(pFile, "	PHASE = %d\n", g_EN[i].param.phase);
			fprintf(pFile, "	APPEAR = %d\n", g_EN[i].param.appear);
			fprintf(pFile, "	STYLE = %d\n", g_EN[i].param.style);
			fprintf(pFile, "	HP = %d\n", g_EN[i].param.HP);
			fprintf(pFile, "	SPD = %.1f\n", g_EN[i].param.SPD);

			if (g_EN[i].param.style == Dragonfly)
			{ // ��x�̂�

				fprintf(pFile, "	RAD = %.1f\n", 30.0f);
			}
			else
			{ // ����ȊO

				fprintf(pFile, "	RAD = %.1f\n", 40.0f);
			}

			fprintf(pFile, "	POS = %.1f %.1f %.1f\n", g_EN[i].pos.x, g_EN[i].pos.y, g_EN[i].pos.z);
			fprintf(pFile, "	ROT = %.1f %.1f %.1f\n", rot.x, rot.y, rot.z);
			fprintf(pFile, "END_PARAMSET\n\n");
		}
	}

	fprintf(pFile, "END_SCRIPT\n");

	// �t�@�C�������
	fclose(pFile);
}

//************************************************
// �f�o�b�O�\��
//************************************************
void PrintDebug_EN(void)
{
	Enemy* pEN = nullptr;	// ���쎯�ʗp

	// ���[�h�ɉ����ĎQ�ƑΏۂ�ύX
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	char Test[32] = {};	// �ėp������

	PrintDebugProc("\n�@�y�G�z�u���z\n");
	PrintDebugProc("����������������������������\n");
	g_OW_EN ? sprintf(Test, "�㏑��") : sprintf(Test, "�z�u");
	PrintDebugProc("�@�ҏW���[�h�F[ %s ] \n", &Test[0]);
	PrintDebugProc("����������������������������\n");
	PrintDebugProc("�@�㏑�����̑I��ԍ��F%d\n\n", g_selectEN);

	PrintDebugProc("�@�G�̎g�p���v���F%d\n\n", GetMaxEnabled());

	PrintDebugProc("�@�t�F�[�Y�F[ %d ] \n", pEN->param.phase);
	PrintDebugProc("�@�o��CT�F[ %d ] \n", pEN->param.appear);
	PrintDebugProc("�@�X�^�C���F[ %d ] \n", pEN->param.style);
	PrintDebugProc("�@�̗́F[ %d ] \n", pEN->param.HP);
	PrintDebugProc("�@���x�F[ %f ] \n", pEN->param.SPD);
	PrintDebugProc("�@�ʒu�F[ %f , %f , %f ] \n", pEN->pos.x, pEN->pos.y, pEN->pos.z);
	PrintDebugProc("�@�����F[ %f , %f , %f ] \n", pEN->rot.x, pEN->rot.y, pEN->rot.z);
	PrintDebugProc("����������������������������\n");
}

#endif	// _DEBUG