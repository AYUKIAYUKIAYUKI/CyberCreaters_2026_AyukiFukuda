#ifdef _DEBUG	// ��ԉ��܂�

//************************************************
//
// �G�l�~�[�z�u�A�w�b�_�t�@�C��[enemy_layout.h]
// Author�F���c����
//
//************************************************
#ifndef _ENEMY_LAYOUT_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ENEMY_LAYOUT_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*---�y�C���N���[�h�t�@�C���z---*/
#include "main.h"
#include "enemy.h"

/*---�y�v���g�^�C�v�錾�z---*/
void Init_EN(void);		// ����
void Uninit_EN(void);	// �I��
void Update_EN(void);	// �X�V
void Draw_EN(void);		// �`��

Enemy GetInfo_targetEN(void);	// �ǐՑΏۂ̎擾

#endif	// _ENEMY_LAYOUT_H_

#endif	// _DEBUG