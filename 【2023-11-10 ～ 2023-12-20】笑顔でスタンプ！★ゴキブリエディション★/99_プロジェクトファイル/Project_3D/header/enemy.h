//************************************************
//
//�G�A�w�b�_�t�@�C��[enemy.h]
//Author�F���c����
//
//************************************************
#ifndef _ENEMY_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ENEMY_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`
#define AMOUNT_ENEMY (64)
#define AMOUNT_ENEMY_PARTS	(16)	//�G�l�~�[���f����
#define AMOUNT_ENEMY_MOTION	(3)	//�G�l�~�[�ő僂�[�V������
#define AMOUNT_ENEMY_KEY	(32)	//�G�l�~�[�ő�L�[��

//�G�̃X�e�[�^�X�ꗗ
typedef enum
{
	EnemyStateNormal = 0,
	EnemyStateDash,
	EnemyStateATK,
	EnemyStateEscape,
	EnemyStateDamage,
	EnemyStateDeath,
	EnemyStateMax
}EnemyState;

//�G�̃��[�V�����ꗗ
typedef enum
{
	EnemyMotionStateNormal = 0,
	EnemyMotionStateDash,
	EnemyMotionStateATK,
	EnemyMotionStateMax
}EnemyMotionState;

//�G�l�~�[���f���p�[�c�p
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posM;	//���[�V�������̈ʒu
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 rotM;	//���[�V�������̌���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nIdxParent;	//�e�p�[�c�̃C���f�b�N�X
}EnemyModel;

//�G�l�~�[�p�[�c�Ǘ�
typedef struct
{
	D3DXVECTOR3 posGoal;	/* ���̃p�[�c�̖ړI�ʒu */
	D3DXVECTOR3 rotGoal;	/* ���̃p�[�c�̖ړI���� */
}EnemyPartsSet;

//�G�l�~�[�L�[�Ǘ�
typedef struct
{
	int nFrame;	/* ���̃L�[�̃t���[���� */
	EnemyPartsSet parts[AMOUNT_ENEMY_PARTS];	/* �p�[�c���Ƃ̉��ړI�n */
}EnemyKeySet;

//�G�l�~�[���[�V�����Ǘ�
typedef struct
{
	int nLoop;	/* ���̃��[�V���������[�v���邩�ǂ��� */
	int nNumKey;	/* ���̃��[�V�����̃L�[�� */
	int nIdxKey;	/* �Đ����̃L�[�ԍ� */
	int nFrameCnt;	/* ���݂̃t���[���o�� */
	EnemyKeySet key[AMOUNT_ENEMY_KEY];	/* ���̃��[�V�����̃L�[�̍ő吔 */
}EnemyMotionSet;

//�G�\����
struct Enemy
{
	bool bUse;	//�g�p����
	int nState;	//���
	bool bATK;	//�U������
	D3DXCOLOR col;	//�F
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����(���z�̐i�s�����Ȃǂ�)
	float fRadius;		//���a
	int nLife;			//�̗�
	int nCntState;		//��Ԍp������
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	EnemyModel aParts[AMOUNT_ENEMY_PARTS];	//�p�[�c��
	EnemyMotionSet motion[EnemyStateMax];	//���[�V�����Ǘ��p
	int nNowMotion;	//�Đ����̃��[�V�����̎��
	int nOldMotion;	//�Đ����Ă����[�V�����̎��
	int nIdxShadow;
};

//�v���g�^�C�v�錾
void InitEnemy(void);	//����
void SetInfoPartsEnemy(void);	//���f���p�[�c�ݒ�
void SetInfoMotionEnemy(void);	//���[�V�����ݒ�
void UninitEnemy(void);	//�j��
void SetInfoEnemy(void);	//�ݒ�
void UpdateEnemy(int mode);	//�X�V
void SpawnEnemy(void);	//�o��
void StateEnemy(int nCnt, int mode);	//���
void SetInfoATK(int nCnt);	//�U������
void DisappearEnemy(int nCnt);	//����
void MotionEnemy(int nCnt);	//���[�V�����Ǘ�
void MotionChangeEnemy(int nCnt);	//���[�V�����ύX
void MotionMoveEnemy(int nCnt, const EnemyMotionSet* Motion);	//���[�V�����p�ړ�
void MotionCountEnemy(int  nCnt, EnemyMotionSet* Motion);	//���[�V�����p�J�E���g
void DrawEnemy(void);	//�`��
Enemy* GetInfoEnemy(void);	//�G�����擾

#endif