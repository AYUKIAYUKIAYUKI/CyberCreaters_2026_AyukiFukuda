//************************************************
//
//�G(����)�����A�w�b�_�t�@�C��[enemy.h]
//Author�F���c����
//
//************************************************
#ifndef _ENEMY_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ENEMY_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include <stdio.h>
#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_CLOUD_ENEMY	"data\\TEX\\02_game\\enemy000.png"

/*�t�@�C���p�X�n*/
#define	FILE_SET_ENEMY	"data\\csv\\EnemyInfo_Cloud.csv"

#define AMOUNT_POLYGON_ENEMY	(64)	//�G�̃|���S����

#define AMOUNT_DATA_ENEMY	(11)	//�G��̓�����̃f�[�^��

#define AMOUNT_CNT_STATE_ENEMY	(20)	//�G��ԕω��p������

//�G�̏�ԕ����񋓌^
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_MAX,			//��Ԃ̑���
}ENEMYSTATE;

//�G�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�G�̈ʒu�����i�[
	float fHalfSpanX;	//�G�̔���X
	float fHalfSpanY;	//�G�̔���Y
	D3DXVECTOR3 move;	//�G�̈ړ������i�[
	D3DXVECTOR3 rot;	//�G�̌��������i�[
	int nColA;			//�����x����
	ENEMYSTATE state;	//��ԑJ��
	int nCntState;		//��ԕω����ԊǗ�
	int nLife;			//�G��HP
	bool bUse;			//�d�l����
	int nCntSpawn;		//���o�����邩
	bool bUseEffect;	//�G�t�F�N�g�̎g�p����
	bool bFinishEffect;	//�G�t�F�N�g�I������
	float fLength;		//�G�̑Ίp�����i�[
	float fAngle;		//�G�̑Ίp���̊p�x���i�[
}ENEMY;

//�v���g�^�C�v�錾
void Init_Enemy(void);
void Uninit_Enemy(void);
void Update_Enemy(void);
void Draw_Enemy(void);
void Setinfo_Enemy(void);
void Hit_Cloud_Enemy(int nCntEnemy, int nDamage);
ENEMY* Getinfo_Enemy(void);
void Disapper_Enemy(int nCntEnemy);

#endif