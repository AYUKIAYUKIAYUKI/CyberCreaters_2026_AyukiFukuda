//************************************************
//
// �\�����̗̑̓Q�[�W�A�w�b�_�t�@�C��[object_bar.h]
// Author�F���c����
//
//************************************************
#ifndef _OBJECT_BAR_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _OBJECT_BAR_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*---�y�C���N���[�h�t�@�C���z---*/
#include "main.h"

/*---�y�\�����̗̑̓Q�[�W�̍\���́z---*/
typedef struct
{
	bool use;			// �g�p
	int dur;			// �p������
	D3DXVECTOR3 pos;	// ���S���W
	D3DXVECTOR3 move;	// �ړ���
	D3DXVECTOR3 rot;	// ��]��
	D3DXVECTOR2 span;	// �傫��
	float HPspan;		// �̗͂̃T�C�Y����
	float angle;		// ���_�p�x
	float length;		// ���_����
	D3DXCOLOR col;		// �F
	float HPcol;		// �̗͂̐F����
	D3DXMATRIX mtx;		// �}�g���b�N�X
} Object_Bar;

//�v���g�^�C�v�錾
void InitObject_Bar(void);		// ����
void UninitObject_Bar(void);	// �j��
void UpdateObject_Bar(void);	// �X�V
void DrawObject_Bar(void);		// �`��

int CreateObject_Bar(int HP);							// ����
void EnableObject_Bar(int HP, int id, D3DXVECTOR3 pos);	// �\��

#endif