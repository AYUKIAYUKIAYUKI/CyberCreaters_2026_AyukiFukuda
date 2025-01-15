//************************************************
//
//�G(�ђ�)�����A�w�b�_�t�@�C��[enemy_spiral.h]
//Author�F���c����
//
//************************************************
#ifndef _ENEMY_SPIRAL_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ENEMY_SPIRAL_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include <stdio.h>
#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_ENEMY_SPIRAL	"data\\TEX\\02_game\\enemy_spiral.png"

/*�t�@�C���p�X�n*/
#define	FILE_SET_ENEMY_SPIRAL	"data\\csv\\EnemyInfo_Spiral.csv"

#define AMOUNT_POLYGON_ENEMY_SPIRAL	(64)	//�G�̃|���S����

#define AMOUNT_DATA_ENEMY_SPIRAL	(13)	//�G��̓�����̃f�[�^��

#define AMOUNT_CNT_STATE_ENEMY_SPIRAL	(20)	//�G��ԕω��p������

//�G�̏�ԕ����񋓌^
typedef enum
{
	ENEMYSTATE_SPIRAL_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_SPIRAL_DAMAGE,		//�_���[�W���
	ENEMYSTATE_SPIRAL_MAX,			//��Ԃ̑���
}ENEMYSTATE_SPIRAL;

//�G�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�G�̈ʒu�����i�[
	float fHalfSpanX;	//�G�̔���X
	float fHalfSpanY;	//�G�̔���Y
	D3DXVECTOR3 move;	//�G�̈ړ������i�[
	float fHoldmoveX;	//�ړ��ʂ�ێ�
	float fHoldmoveY;	//�ړ��ʂ�ێ�
	float fStop;		//�ړ�����߂�^�C�~���O1
	bool bReMove;
	float fDecreaseSPD;	//�ړ��ʂ̌������x
	D3DXVECTOR3 rot;	//�G�̌��������i�[
	int nColA;			//�����x����
	ENEMYSTATE_SPIRAL state;	//��ԑJ��
	int nCntState;		//��ԕω����ԊǗ�
	int nLife;			//�G��HP
	bool bUse;			//�g�p����
	int nCntSpawn;		//���o�����邩
	float fLength;		//�G�̑Ίp�����i�[
	float fAngle;		//�G�̑Ίp���̊p�x���i�[
}ENEMY_SPIRAL;

//�v���g�^�C�v�錾
void Init_Enemy_Spiral(void);
void Uninit_Enemy_Spiral(void);
void Update_Enemy_Spiral(void);
void Draw_Enemy_Spiral(void);
void Setinfo_Enemy_Spiral(void);
void Hit_Spiral_Enemy(int nCntEnemy, int nDamage);
ENEMY_SPIRAL* Getinfo_Enemy_Spiral(void);
void Disapper_Enemy_Spiral(int nCntEnemy);

#endif