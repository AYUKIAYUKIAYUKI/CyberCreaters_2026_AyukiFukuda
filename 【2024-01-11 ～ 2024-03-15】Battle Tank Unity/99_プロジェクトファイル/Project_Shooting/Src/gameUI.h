//************************************************
//
// �Q�[��UI�\���p���A�w�b�_�t�@�C��[ui.h]
// Author�F���c����
//
//************************************************
#ifndef _Phase_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _Phase_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*---�y�C���N���[�h�t�@�C���z---*/
#include "main.h"

/*---�y�A�j���[�V�������ށz---*/
typedef enum
{
	ANIMATION_TYPE_VIBSMALL = 0,	// �U���F��
	ANIMATION_TYPE_VIBBIG,			// �U���F��
	ANIMATION_TYPE_RED,				// �Ԃ��Ȃ�
	ANIMATION_TYPE_FADE,			// �o��
	ANIMATION_TYPE_GUMMY,			// �u�j��
	ANIMATION_TYPE_APPEAL,			// �`���`��
	ANIMATION_TYPE_SLIDEUP,			// ��X���C�h�C��
	ANIMATION_TYPE_SLIDEDOWN,		// ��
	ANIMATION_TYPE_SLIDELEFT,		// ��
	ANIMATION_TYPE_SLIDERIGHT,		// �E
	ANIMATION_TYPE_DISUP,			// ��X���C�h�A�E�g
	ANIMATION_TYPE_DISDOWN,			// ��
	ANIMATION_TYPE_DISLEFT,			// ��
	ANIMATION_TYPE_DISRIGHT,		// �E
	ANIMATION_TYPE_MAX
} ANIMATION_TYPE;

/*---�y�A�j���[�V��������p�z---*/
typedef struct
{
	bool use;			// �g�p
	int dur;			// �A�j���[�V�����p������
	D3DXVECTOR3 move;	// ���S���W
	D3DXVECTOR3 pos;	// �ړ���
	D3DXVECTOR3 rot;	// ��]��
	D3DXVECTOR2 span;	// �傫��
	D3DXCOLOR col;		// �F
} AnimationParam;

/*---�yUI�\���p�z---*/
typedef struct
{
	bool use;									// �g�p
	int textype;								// �e�N�X�`������
	D3DXVECTOR3 pos;							// ���S���W
	D3DXVECTOR3 move;							// �ړ���
	D3DXVECTOR3 rot;							// ��]��
	D3DXVECTOR2 span;							// �傫��
	float angle;								// ���_�p�x
	float length;								// ���_����
	D3DXCOLOR col;								// �F
	AnimationParam play[ANIMATION_TYPE_MAX];	// �A�j���[�V�������̏��
	D3DXMATRIX mtx;								// �}�g���b�N�X
} UI;

#endif