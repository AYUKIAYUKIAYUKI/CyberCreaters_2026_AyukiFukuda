//************************************************
//
// ���j�G�t�F�N�g�A�w�b�_�t�@�C��[effect_burn.h]
// Author�F���c����
//
//************************************************
#ifndef _EFFECT_BURN_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _EFFECT_BURN_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*---�y�C���N���[�h�t�@�C���z---*/
#include "main.h"

// �����O�G�t�F�N�g�p���
typedef struct
{
	bool use;				// �g�p�t���O
	D3DXVECTOR3* pPos;		// �Ώۈʒu
	D3DXVECTOR3 pos_moved;	// �ϓ��ʒu
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR2 span;		// �傫���p
	float angle;			// �p�x
	float length;			// �Ίp���p
	D3DXCOLOR col;			// �F
	int remain;				// ����
	TextureAnimation anima;	// �A�j���[�V�����p
	D3DXMATRIX mtx;			// �s��p
} Effect_Burn;

/*---�y�v���g�^�C�v�錾�z---*/
void InitEffect_Burn(void);		// ����
void UninitEffect_Burn(void);	// �I��
void UpdateEffect_Burn(void);	// �X�V
void DrawEffect_Burn(void);		// �`��

void CreateEffect_Burn(D3DXVECTOR3 pos, float rad);	// ����
void DeleteEffect_Burn(int id);	// ����

#endif