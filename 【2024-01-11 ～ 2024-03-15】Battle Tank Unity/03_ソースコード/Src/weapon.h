//************************************************
//
// ����\���A�w�b�_�t�@�C��[weapon.h]
// Author�F���c����
//
//************************************************
#ifndef _WEAPON_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _WEAPON_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*---�y�C���N���[�h�t�@�C���z---*/
#include "gameUI.h"

/*---�y�v���g�^�C�v�錾�z---*/
void InitWeapon(int joined);	// ����
void UninitWeapon(void);		// �I��
void UpdateWeapon(int joined);	// �X�V
void DrawWeapon(void);			// �`��

void RotatePFW3(int id, float pw);	// ���ԉ�]

#endif