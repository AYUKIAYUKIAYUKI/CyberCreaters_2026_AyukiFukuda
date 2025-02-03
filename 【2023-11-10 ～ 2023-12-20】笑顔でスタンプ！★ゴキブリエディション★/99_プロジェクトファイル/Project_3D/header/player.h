//************************************************
//
//�v���C���[�A�w�b�_�t�@�C��[player.h]
//Author�F���c����
//
//************************************************
#ifndef _PLAYER_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PLAYER_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`
#define AMOUNT_PLAYER_PARTS	(15)	//�v���C���[�ő僂�f����
#define AMOUNT_PLAYER_KEY	(32)	//�v���C���[�ő�L�[��
#define AMOUNT_CAPACITY (5000)	//�L���p�V�e�B
#define AMOUNT_USING_CAPACITY (500)	//�L���p����
#define AMOUNT_ENEGY (100)	//�����Q�[�W�}�b�N�X

//�v���C���[�̏��
typedef enum
{
	PlayerStateNormal = 0,
	PlayerStateMove,
	PlayerStateAtk,
	PlayerStateDamage,
	PlayerStateMax
}PlayerState;

//�v���C���[�̃��[�V�����ꗗ
typedef enum
{
	PlayerMotionStateNormal = 0,
	PlayerMotionStateMove,
	PlayerMotionStateAtk,
	PlayerMotionStateJump,
	PlayerMotionStateLand,
	PlayerMotionStateMax
}PlayerMotionState;

//�v���C���[���f���p�[�c�p
typedef struct
{
	LPD3DXMESH pMeshPlayer;	//���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMatPlayer;	//�}�e���A���̃|�C���^
	DWORD dwNumMatPlayer;	//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 pTexture;	//�e�N�X�`���̃|�C���^
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posM;	//���[�V�������̈ʒu
	D3DXVECTOR3 rot;	//����
	D3DXVECTOR3 rotM;	//���[�V�������̌���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nIdxParent;	//�e�p�[�c�̃C���f�b�N�X
}PlayerModel;

//�v���C���[�p�[�c�Ǘ�
typedef struct
{
	D3DXVECTOR3 posGoal;	/* ���̃p�[�c�̖ړI�ʒu */
	D3DXVECTOR3 rotGoal;	/* ���̃p�[�c�̖ړI���� */
}PlayerPartsSet;

//�v���C���[�L�[�Ǘ�
typedef struct
{
	int nFrame;	/* ���̃L�[�̃t���[���� */
	PlayerPartsSet parts[AMOUNT_PLAYER_PARTS];	/* �p�[�c���Ƃ̉��ړI�n */
}PlayerKeySet;

//�v���C���[���[�V�����Ǘ�
typedef struct 
{
	int nLoop;	/* ���̃��[�V���������[�v���邩�ǂ��� */
	int nNumKey;	/* ���̃��[�V�����̃L�[�� */
	int nIdxKey;	/* �Đ����̃L�[�ԍ� */
	int nFrameCnt;	/* ���݂̃t���[���o�� */
	PlayerKeySet key[AMOUNT_PLAYER_KEY];	/* ���̃��[�V�����̃L�[�̍ő吔 */
}PlayerMotionSet;

//�v���C���[�\����
typedef struct
{
	int nState;	//���
	D3DXCOLOR col;	//�F�ύX�p
	bool bATK;	//�U������
	bool bMUKIMUKI;	//���L���L�}�b�N�X���[�h
	int nCapacity;	//�X�v���[�L���p
	int nEnegy;	//�����Q�[�W
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�ߋ��̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//���݂̌���
	D3DXVECTOR3 rotGoal;	//�ڕW�̌���
	int nCntState;		//��Ԍp������
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	PlayerModel aParts[AMOUNT_PLAYER_PARTS];	//�v���C���[�̃p�[�c��
	PlayerMotionSet motion[PlayerStateMax];	//���[�V�����Ǘ��p
	int nNowMotion;	//�Đ����̃��[�V�����̎��
	int nOldMotion;	//�Đ����Ă����[�V�����̎��	
	COLLISION_AABB aabb;	//AABB
	int nIdxShadow;
}Player;

//�v���g�^�C�v�錾
void InitPlayer(int mode);	//����
void SetInfoParts(int mode);	//���f���p�[�c�ݒ�
void SetInfoMotion(int mode);	//���[�V�����ݒ�
void UninitPlayer(void);	//�j��
void UpdatePlayer(int mode);	//�X�V
bool MovePlayer(void);	//�ړ�
void MoveRotatePlayer(void);	//��]
bool JumpPlayer(void);	//�W�����v
bool LandPlayer(void);	//���n
void TakesDamagePlayer(void);	//��e
void UpdatePlayerAABB(D3DXVECTOR3 pos);	//AABB
void MotionPlayer(void);	//���[�V�����Ǘ�
void MotionChangePlayer(void);	//���[�V�����ύX
void MotionMovePlayer(const PlayerMotionSet* Motion);	//���[�V�����p�ړ�
void MotionCountPlayer(PlayerMotionSet* Motion);	//���[�V�����p�J�E���g
void DrawPlayer(void);	//�`��
Player* GetInfoPlayer(void);	//�v���C���[�����擾

void MUKIMUKI_Colorful(void);	//���L���L�J���t�����[�h

#endif