//************************************************
//
// �I�u�W�F�N�g�A�w�b�_�t�@�C��[object.h]
// Author�F���c����
//
//************************************************
#ifndef _OBJECT_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _OBJECT_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

/*---�y�C���N���[�h�t�@�C���z---*/
#include "main.h"

/*---�y�}�N����`�z---*/
#define AMOUNT_OBJECT 512			// ���̍ő吔
#define AMOUNT_MODEL_OBJECT	33		// ���̕ێ��ł���ő僂�f���퐔

/*---�y�I�u�W�F�N�g�̏�ԕ��ށz---*/
typedef enum
{
	STATE_NORMAL_OBJECT = 0,	// �ʏ�
	STATE_DAMAGE_OBJECT,		// ��_��
	STATE_DEAD_OBJECT,			// ���S�H
	STATE_RESURRECT_OBJECT,		// ����
	STATE_OBJECT_MAX
} STATE_OBJECT;

/*---�y�I�u�W�F�N�g�p�����[�^�z---*/
typedef struct
{
	int state;	// ���
	int dur;	// �p������
	int HP;		// �̗�
	int DEF;	// �h���
} ObjectParam;

/*---�y�I�u�W�F�N�g���f���p�z---*/
typedef struct
{
	LPD3DXMESH pMesh;						// ���b�V�����̃|�C���^
	LPD3DXBUFFER pBuffMat;					// �}�e���A���̃|�C���^
	DWORD NumMat;							// �}�e���A���̐�
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// �e�N�X�`���̃|�C���^
	COLLISION_AABB aabb;					// ���̔���p
} ObjectModel;

/*---�y�I�u�W�F�N�g���p�z---*/
typedef struct
{
	bool use;				// �g�p����
	int type;				// ���f���̎�ފi�[
	ObjectParam param;		// �p�����[�^
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 size;		// �T�C�Y
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	ObjectModel model;		// ���f�����i�[
	int id_bar;				// �̗̓Q�[�W�̔ԍ��i�[�p
	int id_shadow;			// �ꉞ�e�̔ԍ��i�[�p
	int id_box;				// ���̎��ʔԍ�
} Object;

/*---�y�v���g�^�C�v�錾�z---*/
void InitObject(void);					// ����
void UninitObject(void);				// �j��
void UpdateObject(bool LayoutEdit);		// �X�V
void DrawObject(bool LayoutEdit);		// �`��

void HitObject(int id);				// ��e���̏���
Object* GetInfoObject(void);		// �I�u�W�F�N�g�̏����擾
Object* GetInfoGizmoObject(void);	// �M�Y�������擾

#endif