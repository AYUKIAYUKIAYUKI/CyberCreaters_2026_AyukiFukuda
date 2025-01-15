//************************************************
//
//�G(�ړ�)�����A�w�b�_�t�@�C��[enemy_slide.h]
//Author�F���c����
//
//************************************************
#ifndef _ENEMY_SLIDE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ENEMY_SLIDE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include <stdio.h>
#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_ENEMY_SLIDE	"data\\TEX\\02_game\\enemy_slide.png"

/*�t�@�C���p�X�n*/
#define	FILE_SET_ENEMY_SLIDE	"data\\csv\\EnemyInfo_Slide.csv"

#define AMOUNT_POLYGON_ENEMY_SLIDE	(64)	//�G�̃|���S����

#define AMOUNT_DATA_ENEMY_SLIDE	(15)	//�G��̓�����̃f�[�^��

#define AMOUNT_CNT_STATE_ENEMY_SLIDE	(20)	//�G��ԕω��p������

//�G�̏�ԕ����񋓌^
typedef enum
{
	ENEMYSTATE_SLIDE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_SLIDE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_SLIDE_MAX,			//��Ԃ̑���
}ENEMYSTATE_SLIDE;

//�G�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�G�̈ʒu�����i�[
	float fHalfSpanX;	//�G�̔���X
	float fHalfSpanY;	//�G�̔���Y
	D3DXVECTOR3 move;	//�G�̈ړ������i�[
	int nRute;			//�ǂ̃��[�g��i�ނ̂�
	float fHoldmoveX;	//�ړ��ʂ�ێ�
	float fHoldmoveY;	//�ړ��ʂ�ێ�
	float fTurn1;		//�ړ�����߂�^�C�~���O1
	float fTurn2;		//�ړ�����߂�^�C�~���O2
	float fDecreaseSPD;	//�ړ��ʂ̌������x
	bool bTurning;		//�����]��
	D3DXVECTOR3 rot;	//�G�̌��������i�[
	int nColA;			//�����x����
	ENEMYSTATE_SLIDE state;	//��ԑJ��
	int nCntState;		//��ԕω����ԊǗ�
	int nLife;			//�G��HP
	bool bUse;			//�d�l����
	int nCntSpawn;		//���o�����邩
	bool bUseEffect;	//�G�t�F�N�g�̎g�p����
	bool bFinishEffect;	//�G�t�F�N�g�I������
	float fLength;		//�G�̑Ίp�����i�[
	float fAngle;		//�G�̑Ίp���̊p�x���i�[
}ENEMY_SLIDE;

//�v���g�^�C�v�錾
void Init_Enemy_Slide(void);
void Uninit_Enemy_Slide(void);
void Update_Enemy_Slide(void);
void Draw_Enemy_Slide(void);
void Setinfo_Enemy_Slide(void);
void Hit_Slide_Enemy(int nCntEnemy, int nDamage);
ENEMY_SLIDE* Getinfo_Enemy_Slide(void);
void Disapper_Enemy_Slide(int nCntEnemy);

#endif