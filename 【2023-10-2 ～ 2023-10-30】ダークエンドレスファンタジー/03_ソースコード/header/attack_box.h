//************************************************
//
//�U���{�b�N�X�����A�w�b�_�t�@�C��[attack_box.h]
//Author�F���c����
//
//************************************************
#ifndef _ATTACK_BOX_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ATTACK_BOX_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`
#define AMOUNT_POLYGON_ATTACK_BOX	(16)	//�v���C���[�U���{�b�N�X�̃|���S������

#define RADIUS_ATTACK_BOX_X	(100.0f)	//������
#define RADIUS_ATTACK_BOX_Y	(100.0f)	//�c����

//�U���{�b�N�X�̏��̍\���^
typedef struct
{
	int nMode;
	bool bUse;			//�g�p����
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//��]
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
	int nAppear;		//��������
	int nRemain;		//�c������
}ATTACK_BOX;

//�v���g�^�C�v�錾

/*����*/
void Init_Attack_Box(void);

/*�j��*/
void Uninit_Attack_Box(void);

/*�X�V*/
void Update_Attack_Box(void);

/*�U���{�b�N�X�Ƀf�[�^��t�^*/
void GiveInfo_Attack_Box(int nCnt);

/*�v���C���[�p�̍U���{�b�N�X�𒲐�*/
void Front_Player(int nCnt);

void Front_Bomb(int nCnt);

/*�U���{�b�N�X�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Attack_Box(void);

/*�U���{�b�N�X�̎c�����Ԃ�����*/
void Disapper_Attack_Box(void);

/*�����蔻��*/
void HitDetection_Attack_Box(int i);

/*�U���{�b�N�X�̃f�[�^���擾*/
ATTACK_BOX* GetInfo_Attack_Box(void);

/*�f�o�b�O�p�U���{�b�N�X�����`��*/
void Draw_Attack_Box_Debug(void);

#endif