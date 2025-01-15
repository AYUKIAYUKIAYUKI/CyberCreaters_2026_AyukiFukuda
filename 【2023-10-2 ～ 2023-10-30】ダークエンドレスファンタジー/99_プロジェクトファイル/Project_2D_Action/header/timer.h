//************************************************
//
//�������ԏ����A�w�b�_�t�@�C��[timer.h]
//Author�F���c����
//
//************************************************
#ifndef _TIMER_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TIMER_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_TIMER	"data\\TEX\\number.png"

#define AMOUNT_POLYGON_TIMER	(4)	//�|���S����

//�^�C�}�[�\���p�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ�
	D3DXVECTOR3 rot;	//��]
	D3DXCOLOR col;		//�F
	int nCntTex;		//�e�N�X�`���ύX
	int nCntPattern;	//�e�N�X�`���ύX
	float fTexSpan[2];	//�e�N�X�`����
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
}TIMER;

//�v���g�^�C�v�錾

/*����*/
void Init_Timer(void);

/*�j��*/
void Uninit_Timer(void);

/*�X�V*/
void Update_Timer(void);

/*�`��*/
void Draw_Timer(void);

/*�^�C�}�[�Ƀf�[�^��t�^*/
void SetInfo_Timer(void);

/*�^�C�}�[�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Timer(void);

/*�^�C�}�[�̃e�N�X�`�����X�V*/
void Update_Tex_Timer(void);

/*�^�C�}�[����e�N�X�`�������v�Z*/
void Calc_Tex_Timer(void);

/*�^�C�}�[�\���p�̃A�h���X���擾*/
TIMER* GetInfo_TIMER(void);

/*�^�C�}�[�̃A�h���X���擾*/
int* GetInfo_Timer(void);

#endif