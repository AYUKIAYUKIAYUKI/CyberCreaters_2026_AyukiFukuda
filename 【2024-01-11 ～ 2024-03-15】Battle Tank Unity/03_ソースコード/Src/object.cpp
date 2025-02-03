//************************************************
//
// �I�u�W�F�N�g[object.cpp]
// Author�F���c����
//
//************************************************

/*---�y�C���N���[�h�t�@�C���z---*/
#include "object.h"

// ������
#include "effect_smoke.h"
#include "item.h"
#include "object_bar.h"
#include "sound.h"

// �f�o�b�O�p
#ifdef _DEBUG
#include "debugproc.h"
#include "editcamera.h"
#include "input.h"
#include "visible_box.h"
#include <assert.h>
#endif	// _DEBUG

/*---�y�}�N����`�z---*/
#define OBJECT_EX 1	// �I�u�W�F�N�g���̊Ǘ�����

/*---�y�O���[�o���ϐ��z---*/
Object g_Object[AMOUNT_OBJECT];					// �I�u�W�F�N�g���p
Object g_PreObject;								// ���z�̃I�u�W�F�N�g���p
Object g_GizmoObject;							// �M�Y�����f���p
//Object g_StageObject;							// �X�e�[�W���f���p
ObjectModel g_ObjectModel[AMOUNT_MODEL_OBJECT];	// �I�u�W�F�N�g���f�����̌��^
D3DXVECTOR3 g_ObjectMove[AMOUNT_OBJECT];		// �U���p�ړ���
int g_MaxModel = 0;								// ���f������ސ��i�[
int g_MaxObject = 0;							// �������f�������i�[
bool g_TrackAA = true;							// �ړ����[�h����
bool g_Overwrite = false;						// �ҏW���[�h����
int g_obj_id = 0;								// �I�����Ă�������I�u�W�F�N�g����

/*---�y�v���g�^�C�v�錾�z---*/
void ClearObject(void);			// �I�u�W�F�N�g�����N���A
void ClearPreObject(void);		// ���z�̃I�u�W�F�N�g�����N���A
void ClearGizmoObject(void);	// �M�Y�����f�������N���A
//void ClearStageObject(void);	// �X�e�[�W���f�������N���A
void ClearObjectModel(void);	// �I�u�W�F�N�g���f�����̌��^���N���A

void ImportModelObject(void);			// �I�u�W�F�N�g���f���擾
void ImportModelBoxObject(int id,
	char* str);							// �o�E���f�B���O�{�b�N�X���`��
void ImportLayoutObject(FILE* pFile);	// ���f���z�u���擾
void ImportLayoutObjectEX(FILE* pFile);	// ���f���z�u���+���擾
void ImportTexObject(void);				// ���f���e�N�X�`����Ǎ���
void VerifyTypeObject(int id_Model);	// �I�u�W�F�N�g��ނ̏ƍ�
void AdjustAABBObject(int id_Model);	// AABB�T�C�Y�̒���
void ImportGizmoModelObject(void);		// �M�Y�����f���擾
//void ImportStageModelObject(void);	// �X�e�[�W���f���擾

void UninitGizmoObject(void);	// �M�Y�����f���̔j��
//void UninitStageObject(void);	// �X�e�[�W���f���̔j��

void UpdateAABB(int id);		// ������X�V
void DamageObject(int id);		// ��_�����ۂ�
void DeadObject(int id);		// ���銴��
void DeadDeleteObject(int id);	// �I�����Ŗ�������
void ResurrectObject(int id);	// ����

void UpdateEditObject(void);			// �G�f�B�b�g���[�h���̍X�V����
int GetInfoMaxObject(void);				// ���݂̔z�u���f�������擾
void DeleteObject(void);				// �����I�u�W�F�N�g������
void SortArrayObject(void);				// �����I�u�W�F�N�g���\�[�g
void ChangeTargetObject(void);			// �Ώۂ�ύX
void ChangeTypeObject(Object* pObject);	// ��ނ�ύX
void ChangeHPObject(Object* pObject);	// �̗͂�ύX
void ChangeDEFObject(Object* pObject);	// �h��͂�ύX
void VerifyTypePreObject(void);			// ���z�I�u�W�F�N�g��ނ̏ƍ�
void RotateObject(Object* pObject);		// �I�u�W�F�N�g�̉�]
void TranslateObject(Object* pObject);	// �I�u�W�F�N�g�̈ړ�
void SavePreObject(void);				// ���z�I�u�W�F�N�g��ۑ�
void TrackGizmoObject(Object* pObject);	// �M�Y�����f����Ǐ]
void CalcMtxObject(void);				// �����I�u�W�F�N�g�p�}�g���b�N�X�̌v�Z
void CalcMtxPreObject(int mode);		// ���z�I�u�W�F�N�g�p�}�g���b�N�X�̌v�Z
void ExportLayoutObject(void);			// ���f���z�u���ۑ�
void ExportLayoutObjectEX(void);		// ���f���z�u���+���ۑ�

void DrawPreObject(int mode);	// ���z�̃I�u�W�F�N�g�̕`��(�M�Y���܂�)

void PrintDebugObject(void);	// �f�o�b�O�\��
void PrintDebugObjectEX(void);	// �f�o�b�O�\��+��

//************************************************
// �I�u�W�F�N�g����
//************************************************
void InitObject(void)
{
	g_MaxModel = 0;			// ���f������ސ����Z�b�g
	g_MaxObject = 0;		// �������f�������Z�b�g
	g_TrackAA = true;		// �ړ����[�h�F���s
	g_Overwrite = false;	// �ҏW���[�h�F�ʏ�
	g_obj_id = 0;			// ���݂̑I���I�u�W�F�N�g

	// �I�u�W�F�N�g�����N���A
	ClearObject();

#ifdef _DEBUG

	// ���z�̃I�u�W�F�N�g�������Z�b�g
	ClearPreObject();

	// �M�Y���������Z�b�g
	ClearGizmoObject();

#endif // _DEBUG

	// �X�e�[�W���f���̃N���A
	//ClearStageObject();

	// �I�u�W�F�N�g���f�����̌��^���N���A
	ClearObjectModel();

	// �I�u�W�F�N�g�p�̃��f�������擾
	ImportModelObject();

#ifdef _DEBUG

	g_PreObject.model = g_ObjectModel[0];	//!< ���z�̃I�u�W�F�N�g���Ƀ��f������1�Z�b�g(�`��G���[���)

#endif // _DEBUG
}

//************************************************
// �I�u�W�F�N�g�j��
//************************************************
void UninitObject(void)
{
	for (int i = 0; i < AMOUNT_MODEL_OBJECT; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_ObjectModel[i].pTex[j] != NULL)
			{ // �e�N�X�`���̔j��
				g_ObjectModel[i].pTex[j]->Release();
				g_ObjectModel[i].pTex[j] = NULL;
			}
		}

		if (g_ObjectModel[i].pMesh != NULL)
		{ // ���b�V���̔j��
			g_ObjectModel[i].pMesh->Release();
			g_ObjectModel[i].pMesh = NULL;
		}

		if (g_ObjectModel[i].pBuffMat != NULL)
		{ // �}�e���A���̔j��
			g_ObjectModel[i].pBuffMat->Release();
			g_ObjectModel[i].pBuffMat = NULL;
		}
	}

	// �M�Y���j��
	UninitGizmoObject();
}

//************************************************
// �I�u�W�F�N�g�X�V
//************************************************
void UpdateObject(bool LayoutEdit)
{
#ifdef _DEBUG

	if (LayoutEdit)
	{ // �ҏW���[�h�łȂ���Ώ������s��Ȃ�
		UpdateEditObject();
	}

#endif	// _DEBUG

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (!g_Object[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ������X�V
		UpdateAABB(i);

		// ��_��
		DamageObject(i);

		// ���S�H
		DeadObject(i);

		// ����
		ResurrectObject(i);
	}

	// ���[�h�Ɋւ�炸�����I�u�W�F�N�g�͍Ō�ɍs��v�Z
	CalcMtxObject();
}

//************************************************
// �I�u�W�F�N�g�`��
//************************************************
void DrawObject(bool LayoutEdit)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int obj_id = 0; obj_id < AMOUNT_OBJECT; obj_id++)
	{
		if (!g_Object[obj_id].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Object[obj_id].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Object[obj_id].model.pBuffMat->GetBufferPointer();

		// ���̃p�[�c�̎��}�e���A������
		for (int mat_id = 0; mat_id < (int)g_Object[obj_id].model.NumMat; mat_id++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[mat_id].MatD3D);

			//�e�N�X�`���̐ݒ�
			if (g_Object[obj_id].model.pTex[mat_id] != NULL)
			{
				pDevice->SetTexture(0, g_Object[obj_id].model.pTex[mat_id]);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			// �I�u�W�F�N�g�p�[�c�̕`��
			g_Object[obj_id].model.pMesh->DrawSubset(mat_id);
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

	/*--------------------------------------------*/

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_StageObject.mtxWorld);

	//// ���݂̃}�e���A�����擾
	//pDevice->GetMaterial(&matDef);

	//// �}�e���A���f�[�^�ւ̃|�C���^���擾
	//pMat = (D3DXMATERIAL*)g_StageObject.model.pBuffMat->GetBufferPointer();

	//// �@���̐��K��
	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//// ���̃p�[�c�̎��}�e���A������
	//for (int mat_id = 0; mat_id < (int)g_StageObject.model.NumMat; mat_id++)
	//{
	//	// �}�e���A���̐ݒ�
	//	pDevice->SetMaterial(&pMat[mat_id].MatD3D);

	//	//�e�N�X�`���̐ݒ�
	//	if (g_StageObject.model.pTex[mat_id] != NULL)
	//	{
	//		pDevice->SetTexture(0, g_StageObject.model.pTex[mat_id]);
	//	}
	//	else
	//	{
	//		pDevice->SetTexture(0, NULL);
	//	}

	//	// �I�u�W�F�N�g�p�[�c�̕`��
	//	g_StageObject.model.pMesh->DrawSubset(mat_id);
	//}

	//// �@���̐��K��
	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	//// �ۑ����Ă����}�e���A����߂�
	//pDevice->SetMaterial(&matDef);

#ifdef _DEBUG

	if (LayoutEdit)
	{
		// ���z�I�u�W�F�N�g��`��
		if (!g_Overwrite)
		{
			DrawPreObject(0);
		}

		// �M�Y����`��
		DrawPreObject(1);
	}

#endif	// _DEBUG
}

//************************************************
// �I�u�W�F�N�g�̔�e
//************************************************
void HitObject(int id)
{
	if (g_Object[id].param.state == STATE_DAMAGE_OBJECT ||
		g_Object[id].param.state == STATE_DEAD_OBJECT)
	{ // ��e�H�F���S�H��ԂȂ��e���Ȃ�
		return;
	}

	// ��e��ԂłȂ���Δ�e
	g_Object[id].param.state = STATE_DAMAGE_OBJECT;	// ��e��Ԃ�

	g_Object[id].param.dur = 15;	// �p������
	g_Object[id].param.HP--;

	// �̗̓Q�[�W��\��
	EnableObject_Bar(g_Object[id].param.HP, g_Object[id].id_bar, g_Object[id].pos);
}

//************************************************
// �I�u�W�F�N�g�����擾
//************************************************
Object* GetInfoObject(void)
{
	return &g_Object[0];
}

//************************************************
// �M�Y�������擾
//************************************************
Object* GetInfoGizmoObject(void)
{
	return &g_GizmoObject;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �I�u�W�F�N�g�����N���A
//************************************************
void ClearObject(void)
{
	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{ // �I�u�W�F�N�g�̏��̃��Z�b�g
		g_Object[i].use = false;
		g_Object[i].type = 0;
		g_Object[i].param = {};
		g_Object[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Object[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Object[i].size = { 0.0f, 0.0f, 0.0f };
		g_Object[i].model.pMesh = NULL;
		g_Object[i].model.pBuffMat = NULL;
		g_Object[i].model.NumMat = 0;
		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // �e�N�X�`�����̃��Z�b�g
			g_Object[i].model.pTex[j] = NULL;
		}
		g_Object[i].model.aabb = {};
		g_Object[i].id_bar = 0;
		g_Object[i].id_shadow = 0;
		g_Object[i].id_box = 0;

		// �U���p�������Z�b�g
		g_ObjectMove[i] = { 0.0f, 0.0f, 0.0f };
	}
}

//************************************************
// ���z�̃I�u�W�F�N�g���N���A
//************************************************
void ClearPreObject(void)
{
	// ���z�̃I�u�W�F�N�g�̏��̃��Z�b�g
	g_PreObject.use = false;
	g_PreObject.type = 0;
	g_PreObject.param = {};
	g_PreObject.pos = { 0.0f, 0.0f, 0.0f };
	g_PreObject.rot = { 0.0f, 0.0f, 0.0f };
	g_PreObject.size = { 0.0f, 0.0f, 0.0f };
	g_PreObject.model.pMesh = NULL;
	g_PreObject.model.pBuffMat = NULL;
	g_PreObject.model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // �e�N�X�`���������Z�b�g
		g_PreObject.model.pTex[i] = NULL;
	}
	g_PreObject.model.aabb = {};
	g_PreObject.id_shadow = 0;
	g_PreObject.id_box = 0;
}

//************************************************
// �M�Y�����f�������N���A
//************************************************
void ClearGizmoObject(void)
{
	// �M�Y�����̃��Z�b�g
	g_GizmoObject.use = false;
	g_GizmoObject.type = 0;
	g_GizmoObject.param = {};
	g_GizmoObject.pos = { 0.0f, 0.0f, 0.0f };
	g_GizmoObject.rot = { 0.0f, 0.0f, 0.0f };
	g_GizmoObject.size = { 0.0f, 0.0f, 0.0f };
	g_GizmoObject.model.pMesh = NULL;
	g_GizmoObject.model.pBuffMat = NULL;
	g_GizmoObject.model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // �e�N�X�`���������Z�b�g
		g_GizmoObject.model.pTex[i] = NULL;
	}
	g_GizmoObject.model.aabb = {};
	g_GizmoObject.id_shadow = 0;
	g_GizmoObject.id_box = 0;
}

////************************************************
//// �X�e�[�W���f���̏����N���A
////************************************************
//void ClearStageObject(void)
//{
//	// �X�e�[�W���̃��Z�b�g
//	g_StageObject.use = false;
//	g_StageObject.type = 0;
//	g_StageObject.param = {};
//	g_StageObject.pos = { 0.0f, 0.0f, 0.0f };
//	g_StageObject.rot = { 0.0f, 0.0f, 0.0f };
//	g_StageObject.size = { 0.0f, 0.0f, 0.0f };
//	g_StageObject.model.pMesh = NULL;
//	g_StageObject.model.pBuffMat = NULL;
//	g_StageObject.model.NumMat = 0;
//	for (int i = 0; i < AMOUNT_MAT; i++)
//	{ // �e�N�X�`���������Z�b�g
//		g_StageObject.model.pTex[i] = NULL;
//	}
//	g_StageObject.model.aabb = {};
//	g_StageObject.id_shadow = 0;
//	g_StageObject.id_box = 0;
//}

//************************************************
// �I�u�W�F�N�g���f�����̌��^���N���A
//************************************************
void ClearObjectModel(void)
{
	for (int i = 0; i < AMOUNT_MODEL_OBJECT; i++)
	{ // �I�u�W�F�N�g�p���f�����̌��^�̃��Z�b�g
		g_ObjectModel[i].pMesh = NULL;
		g_ObjectModel[i].pBuffMat = NULL;
		g_ObjectModel[i].NumMat = 0;
		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // �e�N�X�`���̏��̃��Z�b�g
			g_ObjectModel[i].pTex[j] = NULL;
		}
		g_ObjectModel[i].aabb = {};
	}
}

//************************************************
// �I�u�W�F�N�g���f������ǂݍ���
//************************************************
void ImportModelObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	int id_Model = 0;			// ���f���̎��ʗp

	/*--------------------------------------------*/

#ifdef OBJECT_EX

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_import_EX.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�I�u�W�F�N�g���f�����+���̓W�J�Ɏ��s");

#endif	// _DEBUG

		return;
	}

#else

	// ���f������W�J����
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_import.txt", "r") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�I�u�W�F�N�g���f�����̓W�J�Ɏ��s");

#endif	// _DEBUG

		return;
	}

#endif	// OBJECT_EX

	/*--------------------------------------------*/

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%d", &g_MaxModel);
		}

#ifdef _DEBUG

		// �G���[
		assert(g_MaxModel < AMOUNT_MODEL_OBJECT && "�I�u�W�F�N�g���f����񂪍ő�ʂ��z���܂���");

#endif	// _DEBUG

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// �ǂݍ��ރ��f�������擾����
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%s", &FileString[0], 128);

			// ���f������o�E���f�B���O�{�b�N�X���`������
			ImportModelBoxObject(id_Model, &FileString[0]);

			// �ǂݍ��񂾏������^�ɂ̂݃R�s�[����
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ObjectModel[id_Model].pBuffMat,
				NULL,
				&g_ObjectModel[id_Model].NumMat,
				&g_ObjectModel[id_Model].pMesh);

			id_Model++; // �p�[�c��i�߂�

			if (id_Model == g_MaxModel)
			{ // �����f����ސ����ǂݎ��I���ƏI��
				break;
			}
		}
	}

	/*--------------------------------------------*/

	// �e���f���̃e�N�X�`�������擾
	ImportTexObject();

	/*--------------------------------------------*/

	// �e���f���̔z�u�����擾
#if OBJECT_EX 

	ImportLayoutObjectEX(pFile);

#else

	ImportLayoutObject(pFile);

#endif	// OBJECT_EX 

	// �t�@�C�������
	fclose(pFile);

	// �X�e�[�W���f����ǂݍ���
	//ImportStageModelObject();

	/*--------------------------------------------*/

#ifdef _DEBUG

	// �M�Y�����f����ǂݍ���
	ImportGizmoModelObject();

#endif
}

//************************************************
// �o�E���f�B���O�{�b�N�X���`��
//************************************************
void ImportModelBoxObject(int id, char* str)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	FILE* pFile = NULL;
	char FileString[128] = {};	// ���͂��i�[
	char* result = nullptr;		// �����������͂��i�[
	int i = 0;					// �ėp����
	D3DXVECTOR3 min = {};		// �ŏ��n�_�i�[
	D3DXVECTOR3 max = {};		// �ő�n�_�i�[
	D3DXVECTOR3 vec = {};		// �e���ւ̃x�N�g�����i�[

	// ��r�����p�ɐ��l�����Ă���
	min = { FLT_MAX, FLT_MAX, FLT_MAX };
	max = { FLT_MIN, FLT_MIN, FLT_MIN };

	// ���f�����̂��̂�W�J����
	if (fopen_s(&pFile, str, "r") != 0)
	{
		return;
	}

	// ���_����ǂݍ��ݎn�߂�Ƃ���܂ŃX�L�b�v
	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "Mesh") == 0)
		{
			i++;	// �S�~�����
		}

		if (i >= 2)
		{
			break;
		}
	}

	// ���l���r���Ă���
	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		int set = 0;						// �����Z�b�g�ŋ�؂邩�J�E���g
		int len = strlen(&FileString[0]);	// ������̒������擾

		for (i = 0; i < len; i++)
		{
			if (FileString[i] == ';')
			{ // �����񂪁A��؂蕶���u;�v���܂�ł��鐔���J�E���g
				set++;
			}
		}

		// ��؂蕶����3���o�����ꍇ�̂�
		if (set == 3)
		{
			i = 0;	// ���������Z�b�g

			// �����񂩂琔�l�𒊏o���Ă���
			result = strtok(FileString, ";");
			vec.x = (float)atof(result);

			while (result != NULL)
			{
				result = strtok(NULL, ";");

				// �������Ă������ŁA���o�����l��3�̂�
				switch (i)
				{
				case 0:
					vec.y = (float)atof(result);
					break;

				case 1:
					vec.z = (float)atof(result);
					break;
				}

				i++;
			}

			// �e���̍ő�E�ŏ��n�_���X�V
			if (min.x > vec.x)
			{
				min.x = vec.x;
			}

			if (min.y > vec.y)
			{
				min.y = vec.y;
			}

			if (min.z > vec.z)
			{
				min.z = vec.z;
			}

			if (max.x < vec.x)
			{
				max.x = vec.x;
			}

			if (max.y < vec.y)
			{
				max.y = vec.y;
			}

			if (max.z < vec.z)
			{
				max.z = vec.z;
			}
		}

		// ��؂蕶����4���o�����ꍇ�̂�
		if (set == 4)
		{
			// �e���̍ő�E�ŏ������Ԑ����̔��a��ۑ�
			vec =
			{
				(fabsf(min.x) + fabsf(max.x)) * 0.5f,
				(fabsf(min.y) + fabsf(max.y)) * 0.5f,
				(fabsf(min.z) + fabsf(max.z)) * 0.5f,
			};

			// �x�N�g���̏����R�s�[
			g_ObjectModel[id].aabb.vec = vec;

			break;	// ��r�����I��
		}
	}

	// �t�@�C�������
	fclose(pFile);
}

//************************************************
// ���f���e�N�X�`������ǂݍ���
//************************************************
void ImportTexObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	for (int i = 0; i < g_MaxModel; i++)
	{
		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_ObjectModel[i].pBuffMat->GetBufferPointer();

		// ���̃p�[�c�̎��}�e���A������
		for (int j = 0; j < (int)g_ObjectModel[i].NumMat; j++)
		{
			// �}�e���A���Ƀe�N�X�`�����ݒ肳��Ă���ΓǍ���
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_ObjectModel[i].pTex[j]);
			}
			else
			{
				g_ObjectModel[i].pTex[j] = NULL;
			}
		}
	}

	//D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_StageObject.model.pBuffMat->GetBufferPointer();

	//// ���̃p�[�c�̎��}�e���A������
	//for (int i = 0; i < (int)g_StageObject.model.NumMat; i++)
	//{
	//	// �}�e���A���Ƀe�N�X�`�����ݒ肳��Ă���ΓǍ���
	//	if (pMat[i].pTextureFilename != NULL)
	//	{
	//		D3DXCreateTextureFromFileA(pDevice,
	//			pMat[i].pTextureFilename,
	//			&g_StageObject.model.pTex[i]);
	//	}
	//	else
	//	{
	//		g_StageObject.model.pTex[i] = NULL;
	//	}
	//}
}

//************************************************
// ���f���z�u����ǂݍ���
//************************************************
void ImportLayoutObject(FILE* pFile)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	char FileString[128] = {};	// ���͂��i�[
	int Type = -1;				// ���f���̎�ފi�[
	D3DXVECTOR3 pos = {};		// �ʒu���i�[
	D3DXVECTOR3 rot = {};		// �����i�[
	int id_Model = 0;			// ���f���̎��ʗp

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "TYPE") == 0)
		{ // ���̃��f���̎�ނ��擾	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%d", &Type);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu���擾	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �������擾	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);

			// �x�����ʓx�ɕϊ�
			rot = (rot * D3DX_PI) / 180.0f;
		}

		if (strcmp(&FileString[0], "END_MODELSET") == 0)
		{
#ifdef _DEBUG

			// �G���[
			assert(Type != -1 && "�I�u�W�F�N�g���f���̎�ޏ��̓Ǎ��݂Ɏ��s");

#endif	// _DEBUG

			// �ǂݍ��񂾔z�u�����Y�����Ԃ̃I�u�W�F�N�g�փR�s�[����
			g_Object[id_Model].use = true;
			g_Object[id_Model].type = Type;
			g_Object[id_Model].param.state = 0;
			g_Object[id_Model].pos = pos;
			g_Object[id_Model].rot = rot;

			VerifyTypeObject(id_Model);	// ��ނ̏ƍ�

			AdjustAABBObject(id_Model);	// AABB�T�C�Y�̒���

#ifdef _DEBUG

			// ���̔���̉���
			g_Object[id_Model].id_box = CreateVisibleBox(&g_Object[id_Model].model.aabb, { 0.0f, 1.0f, 1.0f, 1.0f });

#endif // _DEBUG

			id_Model++; // �R�s�[�����玟��
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{ // �I��
			break;
		}
	}
}

//************************************************
// ���f���z�u���+����ǂݍ���
//************************************************
void ImportLayoutObjectEX(FILE* pFile)
{
	// �t�@�C���f�[�^�Ǎ��ݗp
	char FileString[128] = {};	// ���͂��i�[
	int Type = -1;				// ���f���̎�ފi�[
	int hp = 0;					// �̗͂��i�[
	int def = 0;				// �h��͂��i�[
	D3DXVECTOR3 pos = {};		// �ʒu���i�[
	D3DXVECTOR3 rot = {};		// �����i�[
	int id_Model = 0;			// ���f���̎��ʗp

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "TYPE") == 0)
		{ // ���̃��f���̎�ނ��擾	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%d", &Type);
		}

		if (strcmp(&FileString[0], "HP") == 0)
		{ // �̗͂��擾	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%d", &hp);
		}

		if (strcmp(&FileString[0], "DEF") == 0)
		{ // �h��͂��擾	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%d", &def);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // �ʒu���擾	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // �������擾	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);

			// �x�����ʓx�ɕϊ�
			rot = (rot * D3DX_PI) / 180.0f;
		}

		if (strcmp(&FileString[0], "END_MODELSET") == 0)
		{
#ifdef _DEBUG

			// �G���[
			assert(Type != -1 && "�I�u�W�F�N�g���f���̎�ޏ��̓Ǎ��݂Ɏ��s");

#endif	// _DEBUG

			// �ǂݍ��񂾔z�u�����Y�����Ԃ̃I�u�W�F�N�g�փR�s�[����
			g_Object[id_Model].use = true;
			g_Object[id_Model].type = Type;
			g_Object[id_Model].param.state = 0;
			g_Object[id_Model].param.HP = 7;
			g_Object[id_Model].param.DEF = def;
			g_Object[id_Model].pos = pos;
			g_Object[id_Model].rot = rot;

			VerifyTypeObject(id_Model);	// ��ނ̏ƍ�

			// �̗̓Q�[�W�̐���
			g_Object[id_Model].id_bar = CreateObject_Bar(g_Object[id_Model].param.HP);

			AdjustAABBObject(id_Model);	// AABB�T�C�Y�̒���

#ifdef _DEBUG

			// ���̔���̉���
			if (Type == 9 ||
				Type == 10)
			{
				g_Object[id_Model].id_box = CreateVisibleBox(&g_Object[id_Model].model.aabb, { 0.5f, 0.0f, 0.5f, 1.0f });
			}
			else
			{
				g_Object[id_Model].id_box = CreateVisibleBox(&g_Object[id_Model].model.aabb, { 0.0f, 1.0f, 1.0f, 1.0f });
			}

#endif // _DEBUG

			id_Model++; // �R�s�[�����玟��
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{ // �I��
			break;
		}
	}
}

//************************************************
// �I�u�W�F�N�g��ނ̏ƍ�
//************************************************
void VerifyTypeObject(int id_Model)
{
	for (int i = 0; i < g_MaxModel; i++)
	{
		if (g_Object[id_Model].type == i)
		{ // �e�I�u�W�F�N�g�̎�ނ��ƍ�
			g_Object[id_Model].model = g_ObjectModel[i];	//!< �ԍ��̈�v���Ă��郂�f�������R�s�[
		}
	}
}

//************************************************
// AABB�T�C�Y�̒���
//************************************************
void AdjustAABBObject(int id_Model)
{
	// ����̐���ł͏C�����܂�
	if (g_Object[id_Model].rot.y >= (D3DX_PI * 0.5f) * 0.5f &&
		g_Object[id_Model].rot.y <= (D3DX_PI * 1.5f) * 0.5f)
	{
		float copy = g_Object[id_Model].model.aabb.vec.x;
		g_Object[id_Model].model.aabb.vec.x = g_Object[id_Model].model.aabb.vec.z;
		g_Object[id_Model].model.aabb.vec.z = copy;
	}
	else if(g_Object[id_Model].rot.y <= (-D3DX_PI * 0.5f) * 0.5f &&
		g_Object[id_Model].rot.y >= (-D3DX_PI * 1.5f) * 0.5f)
	{
		float copy = g_Object[id_Model].model.aabb.vec.x;
		g_Object[id_Model].model.aabb.vec.x = g_Object[id_Model].model.aabb.vec.z;
		g_Object[id_Model].model.aabb.vec.z = copy;
	}
}

//************************************************
// �M�Y�����f������ǂݍ���
//************************************************
void ImportGizmoModelObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	D3DXLoadMeshFromX("data\\MODEL\\OBJECT\\Gizmo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_GizmoObject.model.pBuffMat,
		NULL,
		&g_GizmoObject.model.NumMat,
		&g_GizmoObject.model.pMesh);
}

////************************************************
//// �X�e�[�W���f������ǂݍ���
////************************************************
//void ImportStageModelObject(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
//
//	D3DXLoadMeshFromX("data\\MODEL\\OBJECT\\con_stage.x",
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&g_StageObject.model.pBuffMat,
//		NULL,
//		&g_StageObject.model.NumMat,
//		&g_StageObject.model.pMesh);
//
//	g_StageObject.use = true;
//	g_StageObject.pos = { 0.0f, 0.0f, 0.0f};
//}

//************************************************
// �M�Y�����f���̔j��
//************************************************
void UninitGizmoObject(void)
{
	if (g_GizmoObject.model.pMesh != NULL)
	{ // ���b�V���̔j��
		g_GizmoObject.model.pMesh->Release();
		g_GizmoObject.model.pMesh = NULL;
	}

	if (g_GizmoObject.model.pBuffMat != NULL)
	{ // �}�e���A���̔j��
		g_GizmoObject.model.pBuffMat->Release();
		g_GizmoObject.model.pBuffMat = NULL;
	}
}

////************************************************
//// �X�e�[�W���f���̔j��
////************************************************
//void UninitStageObject(void)
//{
//	for (int i = 0; i < AMOUNT_MAT; i++)
//	{
//		if (g_StageObject.model.pTex[i] != NULL)
//		{ // �e�N�X�`���̔j��
//			g_StageObject.model.pTex[i]->Release();
//			g_StageObject.model.pTex[i] = NULL;
//		}
//	}
//
//	if (g_StageObject.model.pMesh != NULL)
//	{ // ���b�V���̔j��
//		g_StageObject.model.pMesh->Release();
//		g_StageObject.model.pMesh = NULL;
//	}
//
//	if (g_StageObject.model.pBuffMat != NULL)
//	{ // �}�e���A���̔j��
//		g_StageObject.model.pBuffMat->Release();
//		g_StageObject.model.pBuffMat = NULL;
//	}
//}

//************************************************
// ������X�V
//************************************************
void UpdateAABB(int id)
{
	// �ʒu�𓯊�
	g_Object[id].model.aabb.pos = g_Object[id].pos;

	// Y����␳
	g_Object[id].model.aabb.pos.y += g_Object[id].model.aabb.vec.y;
}

//************************************************
// ��_�����ۂ�
//************************************************
void DamageObject(int id)
{
	if (g_Object[id].param.state != STATE_DAMAGE_OBJECT)
	{ // ��e��ԂłȂ����
		return;
	}

	// �k����
	int tf = rand() % 2;

	if (tf == 0)
	{
		g_ObjectMove[id].x += (float)(rand() % 5);
		g_ObjectMove[id].z += (float)(rand() % 5);
	}
	else
	{
		g_ObjectMove[id].x += -(float)(rand() % 5);
		g_ObjectMove[id].z += -(float)(rand() % 5);
	}

	// �U���ړ�����
	if (g_ObjectMove[id].x > 10.0f)
	{
		g_ObjectMove[id].x = 10.0f;
	}
	else if (g_ObjectMove[id].x < -10.0f)
	{
		g_ObjectMove[id].x = -10.0f;
	}

	if (g_ObjectMove[id].z > 10.0f)
	{
		g_ObjectMove[id].z = 10.0f;
	}
	else if (g_ObjectMove[id].z < -10.0f)
	{
		g_ObjectMove[id].z = -10.0f;
	}

	// �p�����Ԍ���
	g_Object[id].param.dur--;

	// ��(��)�G�t�F�N�g
	CreateEffect_Smoke(1, &g_Object[id].pos);

	if (g_Object[id].param.dur <= 0)
	{ // ���ԏI����

		// �k���Ă������̂����Z�b�g
		if (g_ObjectMove[id].x != 0.0f)
		{
			g_ObjectMove[id].x = 0.0f;
		}
		else if (g_ObjectMove[id].z != 0.0f)
		{
			g_ObjectMove[id].z = 0.0f;
		}

		if (g_Object[id].param.HP <= 0)
		{ // �̗͂����S�ɖ����Ȃ��Ă���ꍇ

			// ���S��ԂɕύX����
			g_Object[id].param.state = STATE_DEAD_OBJECT;

			PlaySound(SOUND_LABEL_EXPLOSION_1);

			// �����_���ȃA�C�e�����o��
			int stran = rand() % 4;
			CreateItem(stran, g_Object[id].pos);
		}
		else
		{
			// ��Ԃ�ʏ�ɖ߂�
			g_Object[id].param.state = STATE_NORMAL_OBJECT;
		}
	}
}

//************************************************
// ���銴��
//************************************************
void DeadObject(int id)
{
	if (g_Object[id].param.state != STATE_DEAD_OBJECT)
	{ // ���S��ԂłȂ����
		return;
	}

	// �k����
	int tf = rand() % 2;

	if (tf == 0)
	{
		g_ObjectMove[id].x += (float)(rand() % 5);
		g_ObjectMove[id].z += (float)(rand() % 5);
	}
	else
	{
		g_ObjectMove[id].x += -(float)(rand() % 5);
		g_ObjectMove[id].z += -(float)(rand() % 5);
	}

	// �U���ړ�����
	if (g_ObjectMove[id].x > 10.0f)
	{
		g_ObjectMove[id].x = 10.0f;
	}
	else if (g_ObjectMove[id].x < -10.0f)
	{
		g_ObjectMove[id].x = -10.0f;
	}

	if (g_ObjectMove[id].z > 10.0f)
	{
		g_ObjectMove[id].z = 10.0f;
	}
	else if (g_ObjectMove[id].z < -10.0f)
	{
		g_ObjectMove[id].z = -10.0f;
	}

	// ���~
	g_ObjectMove[id].y -= 3.0f;

	// ���G�t�F�N�g
	CreateEffect_Smoke(0, &g_Object[id].pos);
	CreateEffect_Smoke(1, &g_Object[id].pos);

	for (int i = 0; i < AMOUNT_MODEL_OBJECT; i++)
	{
		if (g_Object[id].type != i)
		{ // ���f������v���Ă��Ȃ���΃R���e�B�j���[
			continue;
		}

		if ((g_Object[id].pos.y + g_ObjectMove[id].y) + (g_ObjectModel[i].aabb.vec.y * 2.0f) < -5.0f)
		{ // ���f���̂Ă��؂񂪒n�ʂ̉��ɒ��ނ�

			// �g�p���Ȃ�
			DeadDeleteObject(id);
		}
	}
}

//************************************************
// �I�����łȂ�����
//************************************************
void DeadDeleteObject(int id)
{
#ifdef _DEBUG

	// ���̉���������
	DeleteVisibleBox(g_Object[id].id_box);

#endif // _DEBUG

	// �I�u�W�F�N�g�̏��̃��Z�b�g
	g_Object[id].use = false;
	g_Object[id].type = 0;
	g_Object[id].param = {};
	//g_Object[id].pos = { 0.0f, 0.0f, 0.0f };	// ���G�t�F�N�g�p�Ɉʒu�����́c
	g_Object[id].rot = { 0.0f, 0.0f, 0.0f };
	g_Object[id].size = { 0.0f, 0.0f, 0.0f };
	g_Object[id].model.pMesh = NULL;
	g_Object[id].model.pBuffMat = NULL;
	g_Object[id].model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // �e�N�X�`�����̃��Z�b�g
		g_ObjectModel[id].pTex[i] = NULL;
	}
	g_Object[id].model.aabb = {};
	g_Object[id].id_bar = 0;
	g_Object[id].id_shadow = 0;
	g_Object[id].id_box = 0;
}

//************************************************
// ����
//************************************************
void ResurrectObject(int id)
{
	// �����̖��Q�ƂɌx�����o��̂�}��
	g_Object[id];
}

//************************************************
// �G�f�B�b�g���[�h���̍X�V
//************************************************
void UpdateEditObject(void)
{
#ifdef _DEBUG

	Object* pObject = nullptr;	// ���z�E�����I�u�W�F�N�g���ʗp
	int Loop = 1;				// �ėp���[�v��

	// �ړ����[�h��ύX����
	if (GetKeyboardTrigger(DIK_F4))
	{
		g_TrackAA = !g_TrackAA;
	}

	// �ҏW���[�h��ύX����
	if (GetKeyboardTrigger(DIK_F5))
	{
		g_Overwrite = !g_Overwrite;
	}

	// ���݂̔z�u���f�������擾
	g_MaxObject = GetInfoMaxObject();

	if (GetKeyboardPress(DIK_SPACE))
	{ // �����ňړ����]�̑��x�㏸
		Loop = 4;
	}

	/*--------------------------------------------*/

	// ���[�h�ɉ����Ď擾����I�u�W�F�N�g�����ʂ���
	if (g_Overwrite)
	{
		pObject = &g_Object[g_obj_id];
	}
	else
	{
		pObject = &g_PreObject;
	}

	// �����̃I�u�W�F�N�g���폜
	DeleteObject();

	// �Ώۂ̕ύX
	ChangeTargetObject();

	// ��ނ�ύX
	ChangeTypeObject(pObject);

#if OBJECT_EX

	// �̗͂�ύX
	ChangeHPObject(pObject);

	// �h��͂�ύX
	ChangeDEFObject(pObject);

#endif	// OBJECT_EX

	// �g�����X�t�H�[��
	for (int i = 0; i < Loop; i++)
	{
		// �I�u�W�F�N�g�̉�]
		RotateObject(pObject);

		// �I�u�W�F�N�g�̈ړ�
		TranslateObject(pObject);
	}

	// ���z�I�u�W�F�N�g��ۑ�
	SavePreObject();

	// �M�Y�����f����Ǐ]
	TrackGizmoObject(pObject);

	// �Ō�ɍs��Z
	CalcMtxPreObject(0);	// ���z�I�u�W�F�N�g
	CalcMtxPreObject(1);	// �M�Y�����f��

	// ���f���̔z�u����ۑ�����
	if (GetKeyboardTrigger(DIK_F3))
	{
#if OBJECT_EX 

		ExportLayoutObjectEX();

#else

		ExportLayoutObject();

#endif	// OBJECT_EX 
	}


	// �f�o�b�O�\��
#if OBJECT_EX 

	PrintDebugObjectEX();

#else

	PrintDebugObject();

#endif	// OBJECT_EX 

#endif	// _DEBUG
}

//************************************************
// ���݂̔z�u���f�������擾
//************************************************
int GetInfoMaxObject(void)
{
	int value = 0;	// �J�E���g�p

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (g_Object[i].use)
		{ // �g�p����Ă���΃J�E���g
			value++;
		}
	}

	return value;
}

//************************************************
// �����I�u�W�F�N�g������
//************************************************
void DeleteObject(void)
{
#ifdef _DEBUG

	int i = g_obj_id;	// ���ʊȗ���

	if (g_Overwrite && GetKeyboardTrigger(DIK_BACK))
	{
		// ���̉���������
		DeleteVisibleBox(g_Object[i].id_box);

		// �I�u�W�F�N�g�̏��̃��Z�b�g
		g_Object[i].use = false;
		g_Object[i].type = 0;
		g_Object[i].param = {};
		g_Object[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Object[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Object[i].size = { 0.0f, 0.0f, 0.0f };
		g_Object[i].model.pMesh = NULL;
		g_Object[i].model.pBuffMat = NULL;
		g_Object[i].model.NumMat = 0;
		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // �e�N�X�`�����̃��Z�b�g
			g_Object[i].model.pTex[j] = NULL;
		}
		g_Object[i].model.aabb = {};
		g_Object[i].id_bar = 0;
		g_Object[i].id_shadow = 0;
		g_Object[i].id_box = 0;

		if (g_obj_id == g_MaxObject)
		{ // �����\��̔Ԃ��ō��Ԃ̏ꍇ�A�I����1�߂��Ă���
			g_obj_id = g_MaxObject - 1;
		}
	}

	// �z����\�[�g
	SortArrayObject();

#endif	// _DEBUG
}

//************************************************
// �����I�u�W�F�N�g���\�[�g
//************************************************
void SortArrayObject(void)
{
	for (int i = 0; i < AMOUNT_OBJECT - 1; i++)
	{
		if (!g_Object[i].use && g_Object[i + 1].use)
		{ // ���̔Ԃ����g�p�ŁA���̔Ԃ��g�p���̏ꍇ

			// ���𔽓]�����Ă���
			Object object = g_Object[i];
			g_Object[i] = g_Object[i + 1];
			g_Object[i + 1] = object;
		}
	}
}

//************************************************
// �Ώۂ�ύX
//************************************************
void ChangeTargetObject(void)
{
#ifdef _DEBUG

	if (g_Overwrite)
	{ // �㏑�����[�h���̂�
		if (GetKeyboardTrigger(DIK_PERIOD))
		{
			g_obj_id < g_MaxObject - 1 ? g_obj_id++ : g_obj_id = 0;
		}
		else if (GetKeyboardTrigger(DIK_COMMA))
		{
			g_obj_id > 0 ? g_obj_id-- : g_obj_id = g_MaxObject - 1;
		}

		if (GetKeyboardPress(DIK_Z))
		{
			g_obj_id < g_MaxObject - 1 ? g_obj_id++ : g_obj_id = 0;
		}
		else if (GetKeyboardPress(DIK_X))
		{
			g_obj_id > 0 ? g_obj_id-- : g_obj_id = g_MaxObject - 1;
		}
	}

#endif	// _DEBUG
}

//************************************************
// ��ނ�ύX
//************************************************
void ChangeTypeObject(Object* pObject)
{
#ifdef _DEBUG

	// ��ނ̕ύX
	if (GetKeyboardTrigger(DIK_RSHIFT))
	{
		pObject->type < g_MaxModel - 1 ? pObject->type++ : pObject->type = 0;

		g_Overwrite ? VerifyTypeObject(g_obj_id) : VerifyTypePreObject();
	}
	else if (GetKeyboardTrigger(DIK_LSHIFT))
	{
		pObject->type > 0 ? pObject->type-- : pObject->type = g_MaxModel - 1;

		g_Overwrite ? VerifyTypeObject(g_obj_id) : VerifyTypePreObject();
	}

	assert(pObject->type >= 0 && pObject->type < g_MaxModel && "�I�u�W�F�N�g���f���̎�ނ̕ύX���s");

#endif // _DEBUG
}

//************************************************
// �̗͂�ύX
//************************************************
void ChangeHPObject(Object* pObject)
{
#ifdef _DEBUG

	// �̗͂̕ύX
	if (GetKeyboardTrigger(DIK_Q) && pObject->param.HP > 0)
	{
		pObject->param.HP--;
	}
	else if (GetKeyboardTrigger(DIK_E))
	{
		pObject->param.HP++;
	}

#endif // _DEBUG
}

//************************************************
// �h��͂�ύX
//************************************************
void ChangeDEFObject(Object* pObject)
{
#ifdef _DEBUG

	// �h��͂̕ύX
	if (GetKeyboardTrigger(DIK_Z) && pObject->param.DEF > 0)
	{
		pObject->param.DEF--;
	}
	else if (GetKeyboardTrigger(DIK_C))
	{
		pObject->param.DEF++;
	}

#endif // _DEBUG
}

//************************************************
// ��ނ̏ƍ�(���z)
//************************************************
void VerifyTypePreObject(void)
{
	for (int i = 0; i < g_MaxModel; i++)
	{
		if (g_PreObject.type == i)
		{ // �e���z�I�u�W�F�N�g�̎�ނ��ƍ�
			g_PreObject.model = g_ObjectModel[i];	//!< �ԍ��̈�v���Ă��郂�f�������R�s�[
		}
	}
}

//************************************************
// �I�u�W�F�N�g�̉�]
//************************************************
void RotateObject(Object* pObject)
{
#ifdef _DEBUG

	// X���ɉ�]
	if (GetKeyboardPress(DIK_R))
	{
		pObject->rot.x += 0.01f;
	}
	else if (GetKeyboardPress(DIK_F))
	{
		pObject->rot.x -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_V))
	{
		pObject->rot.x = 0.0f;
	}

	// Y���ɉ�]
	if (GetKeyboardPress(DIK_T))
	{
		pObject->rot.y += 0.01f;
	}
	else if (GetKeyboardPress(DIK_G))
	{
		pObject->rot.y -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_B))
	{
		pObject->rot.y = 0.0f;
	}

	// Z���ɉ�]
	if (GetKeyboardPress(DIK_Y))
	{
		pObject->rot.z += 0.01f;
	}
	else if (GetKeyboardPress(DIK_H))
	{
		pObject->rot.z -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_N))
	{
		pObject->rot.z = 0.0f;
	}

	// X���Ɉ��l
	if (GetKeyboardTrigger(DIK_U))
	{
		pObject->rot.x += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_J))
	{
		pObject->rot.x -= D3DX_PI * 0.025f;
	}

	// Y���Ɉ��l
	if (GetKeyboardTrigger(DIK_I))
	{
		pObject->rot.y += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_K))
	{
		pObject->rot.y -= D3DX_PI * 0.025f;
	}

	// Z���Ɉ��l
	if (GetKeyboardTrigger(DIK_O))
	{
		pObject->rot.z += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_L))
	{
		pObject->rot.z -= D3DX_PI * 0.025f;
	}

#endif	// _DEBUG
}

//************************************************
// �I�u�W�F�N�g�̈ړ�
//************************************************
void TranslateObject(Object* pObject)
{
#ifdef _DEBUG

	bool move = false;
	float X = 0.0f;
	float Z = 0.0f;
	const EditCamera* pCamera = GetInfoEditCamera();

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
		pObject->pos.y += 1.0f;
	}
	else if (GetKeyboardPress(DIK_RBRACKET))
	{
		pObject->pos.y -= 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_YEN))
	{
		pObject->pos.y = 0.0f;
	}

	// int�ւ̃L���X�g�𗘗p���ď���������؂�̂Ă邽�ߌx��������
#pragma warning(disable:4244)

	// �[������
	if (GetKeyboardTrigger(DIK_MINUS))
	{
		pObject->pos.x = (int)pObject->pos.x;
	}
	else if (GetKeyboardTrigger(DIK_CIRCUMFLEX))
	{
		pObject->pos.z = (int)pObject->pos.z;
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
		pObject->pos.y += 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD0))
	{
		pObject->pos.y -= 1.0f;
	}

	if (X != 0.0f || Z != 0.0f)
	{ // ��������͂��Ă���Έړ����Ă��锻��
		move = true;
	}

	if (move)
	{
		// �ړ��ʂƖڕW���p��ݒ�
		if (g_TrackAA)
		{
			pObject->pos.x += sinf(atan2f(X, Z));
			pObject->pos.z += cosf(atan2f(X, Z));
		}
		else
		{
			pObject->pos.x += sinf(atan2f(X, Z) + pCamera->rot.y);
			pObject->pos.z += cosf(atan2f(X, Z) + pCamera->rot.y);
		}
	}

#endif	// _DEBUG
}

//************************************************
// ���z�I�u�W�F�N�g��ۑ�
//************************************************
void SavePreObject(void)
{
#ifdef _DEBUG

	// ���z�̃I�u�W�F�N�g���A�ʏ�I�u�W�F�N�g�Ƃ��Ĕz�u
	if (!g_Overwrite && GetKeyboardTrigger(DIK_RETURN))
	{
		for (int i = 0; i < AMOUNT_OBJECT; i++)
		{
			if (g_Object[i].use)
			{ // �g�p����Ă���΃R���e�B�j���[
				continue;
			}

			g_Object[i] = g_PreObject;	// �V���ɏ���ۑ�

			g_Object[i].use = true;		// ���̃��f���̎g�p������o��

			// ���̔��������
			g_Object[i].id_box = CreateVisibleBox(&g_Object[i].model.aabb, { 0.0f, 1.0f, 1.0f, 1.0f });

			break;
		}
	}

#endif // _DEBUG
}

//************************************************
// �M�Y�����f����Ǐ]
//************************************************
void TrackGizmoObject(Object* pObject)
{
#ifdef _DEBUG

	EditCamera* pEditCamera = GetInfoEditCamera();	// �ҏW�J�������擾

	// �����ʒu�ɃM�Y����t��
	g_GizmoObject.pos = pObject->pos;

	// ���������ɃM�Y����t��
	if (!g_TrackAA)
	{ // �������[�h���̂�
		g_GizmoObject.rot.y = pEditCamera->rot.y;
	}
	else
	{
		if (g_GizmoObject.rot.y != 0.0f)
		{
			g_GizmoObject.rot.y = 0.0f;
		}
	}

#endif	// _DEBUG
}

//************************************************
// �����I�u�W�F�N�g�p�}�g���b�N�X�̌v�Z
//************************************************
void CalcMtxObject(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	// �v�Z�p�}�g���b�N�X

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (!g_Object[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Object[i].mtxWorld);

		// �����𔽉f1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Object[i].rot.y,
			g_Object[i].rot.x,
			g_Object[i].rot.z);

		// �����𔽉f2
		D3DXMatrixMultiply(&g_Object[i].mtxWorld,
			&g_Object[i].mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Object[i].pos.x + g_ObjectMove[i].x,
			g_Object[i].pos.y + g_ObjectMove[i].y,
			g_Object[i].pos.z + g_ObjectMove[i].z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Object[i].mtxWorld,
			&g_Object[i].mtxWorld,
			&mtxTrans);
	}

	// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_StageObject.mtxWorld);

	////�X�P�[����ύX1
	//D3DXMatrixScaling(&mtxScale,
	//	g_StageObject.size.x + 18.0f,
	//	g_StageObject.size.y + 18.0f,
	//	g_StageObject.size.z + 18.0f);

	////�X�P�[����ύX2
	//D3DXMatrixMultiply(&g_StageObject.mtxWorld,
	//	&g_StageObject.mtxWorld,
	//	&mtxScale);

	//// �ʒu�𔽉f1
	//D3DXMatrixTranslation(&mtxTrans,
	//	g_StageObject.pos.x,
	//	g_StageObject.pos.y - 1992.5f,
	//	g_StageObject.pos.z);

	//// �ʒu�𔽉f2
	//D3DXMatrixMultiply(&g_StageObject.mtxWorld,
	//	&g_StageObject.mtxWorld,
	//	&mtxTrans);
}

//************************************************
// ���z�I�u�W�F�N�g�p�}�g���b�N�X�̌v�Z
//************************************************
void CalcMtxPreObject(int mode)
{
#ifdef _DEBUG

	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;		// �v�Z�p�}�g���b�N�X
	Object* pObject = nullptr;

	switch (mode)
	{
	case 0:

		// ���z�I�u�W�F�N�g
		pObject = &g_PreObject;

		break;

	case 1:

		// �M�Y�����f��
		pObject = &g_GizmoObject;

		break;

	default:

		// �G���[
		assert(false && "���z�I�u�W�F�N�g�̃}�g���b�N�X�v�Z�ُ�");

		break;
	}

	/*--------------------------------------------*/

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pObject->mtxWorld);

	if (mode == 1)
	{ // �M�Y�����[�h�̏ꍇ�Y�[�����ɍ��킹�Ċg�k
		EditCamera* pEditCamera = GetInfoEditCamera();	// �ҏW�J�������擾

		// �������擾
		float DistanceSize = (pEditCamera->distance * 0.005f);

		//�X�P�[����ύX1
		D3DXMatrixScaling(&mtxScale,
			pObject->size.x + DistanceSize,
			pObject->size.y + DistanceSize,
			pObject->size.z + DistanceSize);

		//�X�P�[����ύX2
		D3DXMatrixMultiply(&pObject->mtxWorld,
			&pObject->mtxWorld,
			&mtxScale);
	}

	// �����𔽉f1
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		pObject->rot.y,
		pObject->rot.x,
		pObject->rot.z);

	// �����𔽉f2
	D3DXMatrixMultiply(&pObject->mtxWorld,
		&pObject->mtxWorld,
		&mtxRot);

	// �ʒu�𔽉f1
	D3DXMatrixTranslation(&mtxTrans,
		pObject->pos.x,
		pObject->pos.y,
		pObject->pos.z);

	// �ʒu�𔽉f2
	D3DXMatrixMultiply(&pObject->mtxWorld,
		&pObject->mtxWorld,
		&mtxTrans);

#endif // _DEBUG
}

//************************************************
// ���z�̃I�u�W�F�N�g�`��
//************************************************
void DrawPreObject(int mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	Object* pObject = nullptr;

	switch (mode)
	{
	case 0:

		// ���z�I�u�W�F�N�g
		pObject = &g_PreObject;

		break;

	case 1:

		// �M�Y��
		pObject = &g_GizmoObject;

		//Z�ʒu�̔�r���@�̕ύX
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	// ��ɐ[�x�e�X�g�ɍ��i

		break;

	default:

#ifdef _DEBUG

		// �G���[
		assert(false && "���z�I�u�W�F�N�g�̕`�惂�[�h�ُ�");

#endif	// _DEBUG

		break;
	}

	/*--------------------------------------------*/

	D3DMATERIAL9 matDef;							// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;								// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &pObject->mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pObject->model.pBuffMat->GetBufferPointer();

	// ���̃p�[�c�̎��}�e���A������
	for (int i = 0; i < (int)pObject->model.NumMat; i++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//�e�N�X�`���̐ݒ�
		if (pObject->model.pTex[i] != NULL)
		{
			pDevice->SetTexture(0, pObject->model.pTex[i]);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		// �I�u�W�F�N�g�p�[�c�̕`��
		pObject->model.pMesh->DrawSubset(i);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	if (mode == 1)
	{ // �M�Y���`�惂�[�h�̏ꍇ
		//Z�ʒu�̔�r���@�̏C��
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}

//************************************************
// ���f���z�u����ۑ�����
//************************************************
void ExportLayoutObject(void)
{
	FILE* pFile = NULL;
	D3DXVECTOR3 rot = {};	// �v�Z�p

	// �ۑ�����t�@�C����p��
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_export.txt", "w") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�I�u�W�F�N�g���f���z�u�ۑ��p�̃t�@�C���̗p�ӂɎ��s");

#else

		return;

#endif	// _DEBUG
	}

	// �r���[���[�Ŏg���܂킵�₷���t�H�[�}�b�g�ŏ����o���Ă����c
	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# ���f���z�u���\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");

	// ���f���̎�ށA�ʒu�A�������A�u���������������o��
	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (!g_Object[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ʓx��x���ɕϊ�
		rot = (g_Object[i].rot * 180.0f) / D3DX_PI;

		fprintf(pFile, "MODELSET\n");
		fprintf(pFile, "	TYPE = %d\n", g_Object[i].type);
		fprintf(pFile, "	POS = %.1f %.1f %.1f\n", g_Object[i].pos.x, g_Object[i].pos.y, g_Object[i].pos.z);
		fprintf(pFile, "	ROT = %.1f %.1f %.1f\n", rot.x, rot.y, rot.z);
		fprintf(pFile, "END_MODELSET\n\n");
	}

	// �I��
	fprintf(pFile, "END_SCRIPT\n");

	// �t�@�C�������
	fclose(pFile);
}

//************************************************
// ���f���z�u���+����ۑ�����
//************************************************
void ExportLayoutObjectEX(void)
{
	FILE* pFile = NULL;
	D3DXVECTOR3 rot = {};	// �v�Z�p

	// �ۑ�����t�@�C����p��
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_export_EX.txt", "w") != 0)
	{
#ifdef _DEBUG

		// �G���[
		assert(false && "�I�u�W�F�N�g���f���z�u+���ۑ��p�̃t�@�C���̗p�ӂɎ��s");

#else

		return;

#endif	// _DEBUG
	}

	// �r���[���[�Ŏg���܂킵�₷���t�H�[�}�b�g�ŏ����o���Ă����c
	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# ���f���z�u���\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");

	// ���f���̎�ށA�ʒu�A�������A�u���������������o��
	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (!g_Object[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ʓx��x���ɕϊ�
		rot = (g_Object[i].rot * 180.0f) / D3DX_PI;

		fprintf(pFile, "MODELSET\n");
		fprintf(pFile, "	TYPE = %d\n", g_Object[i].type);
		fprintf(pFile, "	HP = %d\n", g_Object[i].param.HP);
		fprintf(pFile, "	DEF = %d\n", g_Object[i].param.DEF);
		fprintf(pFile, "	POS = %.1f %.1f %.1f\n", g_Object[i].pos.x, g_Object[i].pos.y, g_Object[i].pos.z);
		fprintf(pFile, "	ROT = %.1f %.1f %.1f\n", rot.x, rot.y, rot.z);
		fprintf(pFile, "END_MODELSET\n\n");
	}

	// �I��
	fprintf(pFile, "END_SCRIPT\n");

	// �t�@�C�������
	fclose(pFile);
}

//************************************************
// �I�u�W�F�N�g�̏����f�o�b�O�\��
//************************************************
void PrintDebugObject(void)
{
#ifdef _DEBUG

	char Test[32] = {};	// �ėp������

	PrintDebugProc("\n�@�y�I�u�W�F�N�g���z\n");
	PrintDebugProc("����������������������\n");

	g_TrackAA ? sprintf(Test, "�����s") : sprintf(Test, "�J����");

	PrintDebugProc("�@�ړ����[�h�F[ %s ]\n", &Test[0]);
	PrintDebugProc("����������������������\n");

	g_Overwrite ? sprintf(Test, "�㏑��") : sprintf(Test, "�ʏ�");

	PrintDebugProc("�@�ҏW���[�h�F[ %s ] \n", &Test[0]);
	PrintDebugProc("����������������������\n");

	PrintDebugProc("�@���f���̔z�u���F%d\n\n", g_MaxObject);

	if (!g_Overwrite)
	{
		PrintDebugProc("�@���f���̎�ށF%d\n\n", g_PreObject.type);
		PrintDebugProc("�@�ʒu�F%f %f %f\n", g_PreObject.pos.x, g_PreObject.pos.y, g_PreObject.pos.z);
		PrintDebugProc("�@�����F%f %f %f\n", g_PreObject.rot.x, g_PreObject.rot.y, g_PreObject.rot.z);
	}
	else
	{
		PrintDebugProc("�@���݂̑I���F(%d)�F%d\n\n", g_MaxObject, g_obj_id);
		PrintDebugProc("�@���f���̎�ށF%d\n\n", g_Object[g_obj_id].type);
		PrintDebugProc("�@�ʒu�F%f %f %f\n", g_Object[g_obj_id].pos.x, g_Object[g_obj_id].pos.y, g_Object[g_obj_id].pos.z);
		PrintDebugProc("�@�����F%f %f %f\n", g_Object[g_obj_id].rot.x, g_Object[g_obj_id].rot.y, g_Object[g_obj_id].rot.z);
	}

	PrintDebugProc("����������������������\n");

#endif	// _DEBUG
}

//************************************************
// �I�u�W�F�N�g�̏����f�o�b�O�\��+��
//************************************************
void PrintDebugObjectEX(void)
{
#ifdef _DEBUG

	char Test[32] = {};	// �ėp������

	PrintDebugProc("\n�@�y�I�u�W�F�N�g���+���z\n");
	PrintDebugProc("����������������������\n");

	g_TrackAA ? sprintf(Test, "�����s") : sprintf(Test, "�J����");

	PrintDebugProc("�@�ړ����[�h�F[ %s ]\n", &Test[0]);
	PrintDebugProc("����������������������\n");

	g_Overwrite ? sprintf(Test, "�㏑��") : sprintf(Test, "�ʏ�");

	PrintDebugProc("�@�ҏW���[�h�F[ %s ] \n", &Test[0]);
	PrintDebugProc("����������������������\n");

	PrintDebugProc("�@���f���̔z�u���F%d\n\n", g_MaxObject);

	if (!g_Overwrite)
	{
		PrintDebugProc("�@���f���̎�ށF%d\n\n", g_PreObject.type);
		PrintDebugProc("�@�̗́F%d\n", g_PreObject.param.HP);
		PrintDebugProc("�@�h��́F%d\n\n", g_PreObject.param.DEF);
		PrintDebugProc("�@�ʒu�F%f %f %f\n", g_PreObject.pos.x, g_PreObject.pos.y, g_PreObject.pos.z);
		PrintDebugProc("�@�����F%f %f %f\n", g_PreObject.rot.x, g_PreObject.rot.y, g_PreObject.rot.z);
	}
	else
	{
		PrintDebugProc("�@���݂̑I���F(%d)�F%d\n\n", g_MaxObject, g_obj_id);
		PrintDebugProc("�@���f���̎�ށF%d\n\n", g_Object[g_obj_id].type);
		PrintDebugProc("�@�̗́F%d\n", g_Object[g_obj_id].param.HP);
		PrintDebugProc("�@�h��́F%d\n\n", g_Object[g_obj_id].param.DEF);
		PrintDebugProc("�@�ʒu�F%f %f %f\n", g_Object[g_obj_id].pos.x, g_Object[g_obj_id].pos.y, g_Object[g_obj_id].pos.z);
		PrintDebugProc("�@�����F%f %f %f\n", g_Object[g_obj_id].rot.x, g_Object[g_obj_id].rot.y, g_Object[g_obj_id].rot.z);
	}

	PrintDebugProc("����������������������\n");

#endif	// _DEBUG
}

/*---�y�g���z---*/

//************************************************
// ��
//************************************************
//void ooooo(void)
//{
//	// ���f���̃^�C�v������̂Ƃ�
//
//	// �v���C���[�̒N����
//	
//	// ���͈͂ɋ߂Â��Ă���Ȃ�
//
//	// �e��⋋
//}