//************************************************
//
// �t�F�[�Y�\���A�w�b�_�t�@�C��[phase.h]
// Author�F���c����
//
//************************************************
#ifndef _PHASE_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PHASE_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*---�y�C���N���[�h�t�@�C���z---*/
#include "gameUI.h"

/*---�y�v���g�^�C�v�錾�z---*/
void InitPhase(int joined);	// ����
void UninitPhase(void);		// �I��
void UpdatePhase(void);		// �X�V
void DrawPhase(void);		// �`��

UI* GetInfoPhaseUI(void);		// �t�F�[�Y�\���̎擾
bool* ChangePhasePlay(void);	// �t�F�[�Y�̕ύX�����o
bool* ChangeEnemyPlay(void);	// �o�����̕ύX�����o
bool* ChangeScorePlay(void);	// �X�R�A�̕ύX�����o

#endif