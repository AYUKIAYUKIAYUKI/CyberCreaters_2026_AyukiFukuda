//************************************************
//
//�G�p�U���{�b�N�X�����A�w�b�_�t�@�C��[attack_box_enemy.h]
//Author�F���c����
//
//************************************************
#ifndef _ATTACK_BOX_ENEMY_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ATTACK_BOX_ENEMY_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

/*�摜�p�X�n*/
#define	TEXTURE_ENEMY_NONE "data\\TEX\\white.png"
#define	TEXTURE_ENEMY_04_BALL "data\\TEX\\e04_ball.png"
#define	TEXTURE_ENEMY_04_BALLEND "data\\TEX\\e04_ballend.png"

#define AMOUNT_TEX_BOX	(3)	//�e�N�X�`����

#define SPD_CHANGE_TEX_FIRE_ENEMY_04	(2)	//�ڂ����X���[�h�t�@�C�A�̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_FIRE_ENEMY_04	(6)	//�ڂ����X���[�h�t�@�C�A�̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_FIRE_ENEMY_04	(0.16666f)	//�ڂ����X���[�h�t�@�C�A�A�j���[�V�����p

#define SPD_CHANGE_TEX_FIREEND_ENEMY_04	(2)	//�ڂ����X���[�h�t�@�C�A�̃A�j���[�V�������x
#define AMOUNT_STYLE_TEX_FIREEND_ENEMY_04	(7)	//�ڂ����X���[�h�t�@�C�A�̃A�j���[�V�����p
#define SPAN_CHANGE_TEX_FIREEND_ENEMY_04	(0.14285f)	//�ڂ����X���[�h�t�@�C�A�A�j���[�V�����p
	
typedef enum
{
	BOX_MODE_NONE = 0,
	BOX_MODE_FIRE,
	BOX_MODE_FIRE_END,
	BOX_MODE_MAX,
}BOX_MODE;

//�G�U���{�b�N�X�̏��̍\���^
typedef struct
{
	int nMode;			//�{�b�N�X�����[�h
	bool bUse;			//�g�p����
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	float fX;			//�␳
	D3DXVECTOR3 rot;	//��]
	D3DXCOLOR col;		//�F
	int LR;				//����
	int nCntTex;		//�e�N�X�`���ύX
	int nCntPattern;	//�e�N�X�`���ύX
	float fTexSpan[2];	//�e�N�X�`����
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
	int nAppear;		//��������
	int nRemain;		//�c������
}ATTACK_BOX_ENEMY;

//�v���g�^�C�v�錾

/*����*/
void Init_Attack_Box_Enemy(void);

/*�j��*/
void Uninit_Attack_Box_Enemy(void);

/*�X�V*/
void Update_Attack_Box_Enemy(void);

/*�U���{�b�N�X�Ƀf�[�^��t�^*/
void GiveInfo_Attack_Box_Enemy(int i);

/*�G�p�̍U���{�b�N�X�𒲐�*/
void Front_Enemy(int i);

/*�U���{�b�N�X�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Attack_Box_Enemy(void);

/*�F*/
void Update_Col_Attack_Box_Enemy(int i);

/*�e�N�X�`���A�j���[�V��������*/
void Update_Tex_Attack_Box_Enemy(int i);

/*�U���{�b�N�X�̎c�����Ԃ�����*/
void Disapper_Attack_Box_Enemy(void);

/*�����蔻��*/
void HitDetection_Attack_Box_Enemy(int i);

/*�G�U���{�b�N�X�̃f�[�^���擾*/
ATTACK_BOX_ENEMY* GetInfo_Attack_Box_Enemy(void);

/*�f�o�b�O�p�U���{�b�N�X�����`��*/
void Draw_Attack_Box_Enemy_Debug(void);

#endif