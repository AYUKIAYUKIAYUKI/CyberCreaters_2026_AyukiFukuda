//************************************************
//
// �{�X�A�w�b�_�t�@�C��[boss.h]
// Author�F�����h��
//
//************************************************

#ifndef _BOSS_H_	// ���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BOSS_H_	// (��d�C���N���[�h�h�~�A�}�N����`����)

/*/ �C���N���[�h�t�@�C�� / */
#include "main.h"

/*/ �}�N����` /*/
#define MAX_BOSS					(2)		// �{�X�̐�
#define AMOUNT_BOSS_PARTS			(28)	// �{�X�ő僂�f����ސ�
#define SPD_STOPMOVE_BOSS			(0.9f)	// �u���[�L��
#define NUM_MOTION					(12)	// ���[�V�����̎�ސ�
#define STANTIME					(20)	// �{�X����e�����Ƃ��̃X�^������
#define ADJUSTPOSY_MIDBOSS			(100.0f)// �e�̔��ˈʒu(Y)�̒����p
#define ADJUSTPOSY_BIGBOSS			(30.0f)	// �e�̔��ˈʒu(Y)�̒����p
#define NUM_ACT						(6)		// ���{�X�̍s���p�^�[��
#define MAX_CHANGEFRAME				(500)	// ���{�X�̍s����ς���t���[����
#define BULLETMOVEY					(0.8f)	// ���{�X�̒e��Y���W�����ւ̈ړ���
#define MIDBOSSMOVE					(1.5f)	// ���{�X�̈ړ���
#define MIDBOSS_LATE				(60)	// ���{�X������ł��甚������܂ł̒x������
#define BIGBOSS_LATE				(40)	// ���{�X������ł��甚������܂ł̒x������

#define DATA_RANGE					(3800)	// rand�Ő������������l�͈̔�
#define DATA_ADJUST					(1900)	// ���̐������������邽�߂̒�����

//******************************************************************
// �{�X�̍s���p�^�[���t���[�����̃}�N����`
//******************************************************************
#define PATTERN_ZERO	(500)	// 1�p�^�[����
#define PATTERN_ONE		(1000)	// 2�p�^�[����
#define PATTERN_TWO		(1500)	// 3�p�^�[����
#define PATTERN_THREE	(2000)	// 4�p�^�[����
#define PATTERN_FOUR	(2500)	// 5�p�^�[����
#define PATTERN_FIVE	(3000)	// 6�p�^�[����
#define PATTERN_SIX		(3500)	// 7�p�^�[����
#define PATTERN_SEVEN	(4000)	// 8�p�^�[����
#define PATTERN_EIGHT	(4500)	// 9�p�^�[����
#define PATTERN_NINE	(5000)	// 10�p�^�[����

// �{�X�̎�ޕ���
typedef enum
{
	BOSSTYPE_MID = 0,	//���{�X
	BOSSTYPE_BIG,		//��{�X
	BOSSTYPE_MAX
}BOSSTYPE;

// �{�X��ԕ���
typedef enum
{
	stateNormal_b = 0,	// �ʏ�
	stateMove_b,		// �ړ�
	stateAtk_b,			// �U��
	stateDamage_b,		// ��e
	stateDead_b,		// ���S
	steteResurrect_b,	// ����
	Max_bossstate,
}BOSSState;

//���[�V������ޕ���
typedef enum
{
	motion_neutralMid = 0,		// �j���[�g�������[�V����(���{�X)
	motion_moveMid,				// �ړ����[�V����(���{�X)
	motion_actionMid,			// �U�����[�V����(���{�X)
	motion_jumpMid,				// �W�����v���[�V����(���{�X)
	motion_landingMid,			// ���n���[�V����(���{�X)
	motion_damageMid,			// ��e���[�V����(���{�X)
	motion_deadMid,				// ���S���[�V����(���{�X)
	motion_neutralBig,			// �j���[�g�������[�V����(��{�X)
	motion_moveBig,				// �ړ����[�V����(��{�X)
	motion_actionBig,			// �U�����[�V����(��{�X)
	motion_damageBig,			// ��e���[�V����(��{�X)
	motion_deadBig,				// ���S���[�V����(��{�X)
	motion_max,
}BossMotionType;

// �{�X�̒e�̋�������
typedef enum
{
	BULLETPATTERN_ZERO = 0,	// 0��ޖ�(rand�ł̐��l�ɑ΂���}�N����`�Ŏg���Ă���̂�BULLETPATTERN_ZERO�͕s�g�p)
	BULLETPATTERN_ONE,		// 1��ޖ�
	BULLETPATTERN_TWO,		// 2��ޖ�
	BULLETPATTERN_THREE,	// 3��ޖ�
	BULLETPATTERN_FOUR,		// 4��ޖ�
	BULLETPATTERN_FIVE,		// 5��ޖ�
	BULLETPATTERN_SIX,		// 6��ޖ�
	BULLETPATTERN_SEVEN,	// 7��ޖ�
	BULLETPATTERN_EIGHT,	// 8��ޖ�
	BULLETPATTERN_NINE,		// 9��ޖ�
	BULLETPATTERN_TEN,		// 10��ޖ�
	BULLETPATTERN_MAX
}BULLETPATTERN;

// �{�X�p�����[�^���
typedef struct
{
	int appear;			// �o���^�C�~���O
	int style;			// �X�^�C��
	int state;			// ���
	int dur;			// ��Ԍp��
	float HP;			// �̗�
	D3DXVECTOR3 SPD;	// ���x
	//float Radius;		// ���̔���ɕK�v�Ȕ��a
	int motion_now;		// �Đ����[�V����
	int motion_old;		// �ߋ����[�V����
	bool bMove;			// �ړ����Ă��邩�ǂ���

}BOSSParam;

// �{�X�p���f�����
typedef struct
{
	int style;								// �X�^�C��
	LPD3DXMESH pMesh;						// ���b�V���̃|�C���^
	LPD3DXBUFFER pBuffMat;					// �}�e���A���̃|�C���^
	DWORD NumMat;							// �}�e���A���̐�
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 pos_offset;					// �ʒu�I�t�Z�b�g
	D3DXVECTOR3 pos_moved;					// ���[�V�������ȂǕϓ��ʒu
	D3DXVECTOR3 rot_offset;					// �����I�t�Z�b�g
	D3DXVECTOR3 rot_moved;					// ���[�V�������ȂǕϓ�����
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	int IdxParent;							// �e�p�[�c�̃C���f�b�N�X
}BOSSModel;

// ���[�V�������̃p�[�c�ڕW����p
typedef struct
{
	D3DXVECTOR3 pos;	// �ڕW�ʒu�i�[
	D3DXVECTOR3 rot;	// �ڕW�����i�[
}BossMotionDest;

// ���[�V�������̃L�[�p
typedef struct
{
	int amount_frame;							// �L�[�P�ʂ̑��t���[����
	BossMotionDest dest[AMOUNT_BOSS_PARTS];		// �p�[�c�̓�����i�[
}BossMotionKey;

// �{�X���[�V�����p
typedef struct
{
	int loop;				// ���[�v�t���O
	int amount_key;			// ���[�V�����P�ʂ̑��L�[��
	int id_key;				// �Đ����̃L�[�ԍ����i�[
	int id_frame;			// �Đ����̃t���[���ԍ����i�[
	BossMotionKey key[16];	// �L�[�����i�[
}BossMotion;

// �{�X���
typedef struct
{
	bool use;								// �g�p���� 
	D3DXVECTOR3 pos;						// ���[���h�ʒu
	D3DXVECTOR3 pos_old;					// �ߋ��̈ʒu
	D3DXVECTOR3 move;						// �ړ���
	D3DXVECTOR3 rot;						// ���݂̌���
	D3DXVECTOR3 rot_goal;					// �ڕW�̌���
	D3DXCOLOR col;							// �F�ύX�p
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	BOSSModel parts[AMOUNT_BOSS_PARTS];		// �G�l�~�[�̃p�[�c��
	float rad[AMOUNT_BOSS_PARTS];			// �e�p�[�c�̔���T�C�Y
	D3DXVECTOR3 pos_sph[AMOUNT_BOSS_PARTS];	// �e�p�[�c�̔���ʒu
	int id_shadow;							// �e���ʔԍ��i�[
	int id_sph[AMOUNT_BOSS_PARTS];			// ���莯�ʔԍ��i�[
	BOSSTYPE type;							// �{�X�̎��
	BOSSState State;						// �{�X�̏��
	BOSSParam Param;						// �{�X�̃p�����[�^�[
	BossMotion motion[NUM_MOTION];			// ���[�V�������
}BOSS;

//�v���g�^�C�v�錾
void InitBoss(void);									// ����
void ImportModelBoss(void);								// ���f���擾
void ImportOffsetBoss(FILE* pFile, int AmountModel);	// ���f���I�t�Z�b�g�擾
void ImportTexBoss(int AmountModel);					// ���f���e�N�X�`����Ǎ���
void ImportMotionBoss(void);							// ���[�V�����擾
//void GenerateBOSS(void);								// �o���ݒ�
void AppearBoss(int id);								// �o��
void ImportParamBoss(void);								// �p�����[�^�擾
void VerifyStyleBoss(int id);							// �X�^�C���ԍ����ƍ�
void UninitBoss(void);									// �j��
void UpdateBoss(void);									// �X�V
void RotateBoss(int id);								// ��]
void MoveBoss(void);									// �ړ�
void CalcMtxBoss(void);									// �s��v�Z
void DrawBoss(void);									// �`��
BOSS* GetInfoBoss(void);								// �G�l�~�[�����擾
void SetBoss(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
	int nStyle, float fLife);							// �G�̃p�����[�^�[��ݒ肷��
void MidBossBehavior(int id);							// ���{�X�̋���
void BigBossBehavior(int id);							// ��{�X�̋���
void HitBoss(int id);									// �{�X�ƒe�̓����蔻��
void NeutralBoss(int id);								// �j���[�g�������
void DamageBoss(int id);								// ����
void DeadBoss(int id);									// ���S
void ResurrectBoss(int id);								// ����
void MotionBoss(int id);								// ���[�V�����Ǘ�
void ChangeMotionBoss(int id, int* pNow, int* pOld);		// ���[�V�����ύX���m
void MoveMotionBoss(int id, BossMotion* pMotion);		// ���[�V��������p
void CntMotionBoss(int id, BossMotion* pMotion);			// ���[�V�����J�E���g�p
void AdjustBullet(int id);								// �e�̋��������߂�
bool CheckBossUse(void);								// �{�X�������Ă��邩�ǂ���
void CollisionBoss(int id);								// �{�X�ƌ����̓����蔻��
void CollisionPlayer(int id);							// �{�X�ƃv���C���[�̓����蔻��
void DeleteOldBoss(int id);								// �t�F�[�Y���I�������{�X�̏���

//////////////////////////////////////////////////////////////////

bool GetInfoHP_MidBoss(void);	// �̗͂ɂ�鐶������ - ���{�X
bool GetInfoHP_BigBoss(void);	// �̗͂ɂ�鐶������ - ��{�X

#endif
