//==========================================================
//
//�Q�[����ʂ̕`�揈��[game.h]
//Author:kasai keisuke
//
//==========================================================

#ifndef _GAME_H_
#define _GAME_H_

//include
#include "main.h"

//�}�N����`
#define MAX_LATE	(240)		// �ő�x������

//�G�̃p�����[�^�[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�o���ʒu
	D3DXVECTOR3 rot;	//�o������
	int nStyle;			//�^�C�v
	int nCntAppear;		//�o������
	int nLife;			//���C�t
}EnemyInfo;

//�v���g�^�C�v�錾
void InitGame(void);		//�Q�[����ʂ̏���������
void UninitGame(void);		//�Q�[����ʂ̏I������
void UpdateGame(void);		//�Q�[����ʂ̍X�V����
void DrawGame(void);		//�Q�[����ʂ̕`�揈��
void SetEnablePause(bool bPause);	// �|�[�Y�̗L�������ݒ�
bool CheckGameEnd(void);			//�{�X�����񂾂��Ƃ̒x������

bool GetLayoutEdit(void);	// �ҏW���[�h�̃t���O�擾
bool GetLayout_EN(void);	// �G�ҏW���[�h�̃t���O�擾
int* GetInfoScore(void);	// �X�R�A�����擾
bool CntDuration(int* dur);	// ��Ԍp���J�E���g�p

bool* GetInfoEndGame(void); // �C���Q�[���I���t���O�擾

#endif