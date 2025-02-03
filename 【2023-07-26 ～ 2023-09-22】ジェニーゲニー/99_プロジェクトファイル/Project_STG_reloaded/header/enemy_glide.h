//************************************************
//
//�G(����)�����A�w�b�_�t�@�C��[enemy_glide.h]
//Author�F���c����
//
//************************************************
#ifndef _ENEMY_GLIDE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ENEMY_GLIDE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include <stdio.h>
#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_ENEMY_GLIDE	"data\\TEX\\02_game\\enemy_glide.png"

/*�t�@�C���p�X�n*/
#define	FILE_SET_ENEMY_GLIDE	"data\\csv\\EnemyInfo_Glide.csv"

#define AMOUNT_POLYGON_ENEMY_GLIDE	(64)	//�G�̃|���S����

#define AMOUNT_DATA_ENEMY_GLIDE	(15)	//�G��̓�����̃f�[�^��

#define AMOUNT_CNT_STATE_ENEMY_GLIDE	(20)	//�G��ԕω��p������

//�G�̏�ԕ����񋓌^
typedef enum
{
	ENEMYSTATE_GLIDE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_GLIDE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_GLIDE_MAX,			//��Ԃ̑���
}ENEMYSTATE_GLIDE;

//�G�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�G�̈ʒu�����i�[
	float fHalfSpanX;	//�G�̔���X
	float fHalfSpanY;	//�G�̔���Y
	D3DXVECTOR3 move;	//�G�̈ړ������i�[
	D3DXVECTOR3 rot;	//�G�̌��������i�[
	int nColA;			//�����x����
	ENEMYSTATE_GLIDE state;	//��ԑJ��
	int nCntState;		//��ԕω����ԊǗ�
	int nLife;			//�G��HP
	bool bUse;			//�d�l����
	int nCntSpawn;		//���o�����邩
	int nCntChange;		//���i�H�ύX���邩
	bool bUseEffect;	//�G�t�F�N�g�̎g�p����
	bool bFinishEffect;	//�G�t�F�N�g�I������
	float fDirection;	//���p
	float fTurningSPD;	//���񑬓x
	float fSizeCircle;	//�~����
	float fLength;		//�G�̑Ίp�����i�[
	float fAngle;		//�G�̑Ίp���̊p�x���i�[
}ENEMY_GLIDE;

//�v���g�^�C�v�錾
void Init_Enemy_Glide(void);
void Uninit_Enemy_Glide(void);
void Update_Enemy_Glide(void);
void Draw_Enemy_Glide(void);
void Setinfo_Enemy_Glide(void);
void Hit_Glide_Enemy(int nCntEnemy, int nDamage);
ENEMY_GLIDE* Getinfo_Enemy_Glide(void);
void Disapper_Enemy_Glide(int nCntEnemy);

#endif