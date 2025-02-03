//************************************************
//
// ���^�̔���������A�w�b�_�t�@�C��[visible_box.h]
// Author�F���c����
//
//************************************************
#ifndef _VISIBLE_BOX_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _VISIBLE_BOX_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*---�y�C���N���[�h�t�@�C���z---*/
#include "main.h"

/*---�y�{�b�N�X�\���́z-- - */
typedef struct
{
	bool use;				// �g�p����
	D3DXVECTOR3 pos;		// �ʒu
	COLLISION_AABB* aabb;	// ��������i�[
	D3DXCOLOR col;			// �\���J���[
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
} Box;

/*---�y�v���g�^�C�v�錾�z---*/
void InitVisibleBox(void);				// ����
int CreateVisibleBox(COLLISION_AABB* obj,
	D3DXCOLOR col);						// ����
void UninitVisibleBox(void);			// �j��
void UpdateVisibleBox(void);			// �X�V
void DeleteVisibleBox(int id);			// ����
void CalcMtxVisibleBox(void);			// �s��v�Z
void DrawVisibleBox(void);				// �`��

#endif