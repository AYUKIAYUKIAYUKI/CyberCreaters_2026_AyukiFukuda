//************************************************
//
//���Ώۏ����A�w�b�_�t�@�C��[tower.h]
//Author�F���c����
//
//************************************************
#ifndef _TOWER_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TOWER_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_TOWER	"data\\TEX\\tower.png"

#define AMOUNT_TEX_TOWER	(1)	//���Ώۂ̃e�N�X�`������

#define RADIUS_TOWER_X	(100.0f)	//������
#define RADIUS_TOWER_Y	(150.0f)	//�c����

#define AMOUNT_MAX_LIFE_TOWER	(7)	//���Ώۂ̃��C�t�ő�

#define SPD_CHANGE_TEX_TOWER	(3)	//�A�j���[�V�������x
#define AMOUNT_STYLE_TEX_TOWER	(11)	//�A�j���[�V�����p
#define SPAN_CHANGE_TEX_TOWER	(0.09090f)	//�A�j���[�V�����p

//���Ώۂ̏��̍\���^
typedef struct
{
	int nState;			//���Ώۂ̏��
	D3DXVECTOR3 pos;	//�^���ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//��]
	D3DXCOLOR col;		//�F
	int nCntTex;		//�e�N�X�`���ύX
	int nCntPattern;	//�e�N�X�`���ύX
	float fTexSpan[2];	//�e�N�X�`����
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
	int nLife;			//���C�t
	int nCT;			//�L���X�g�^�C��
}TOWER;

//�v���g�^�C�v�錾

/*����*/
void Init_Tower(void);

/*�j��*/
void Uninit_Tower(void);

/*�X�V*/
void Update_Tower(void);

/*�`��*/
void Draw_Tower(void);

/*���ΏۂɃf�[�^��t�^*/
void SetInfo_Tower(void);

/*���Ώۂ̃o�[�e�b�N�X���X�V*/
void Update_Pos_Tower(void);

/*���Ώۂ̃o�[�e�b�N�X�J���[���X�V*/
void Update_Col_Tower(void);

/*�e�N�X�`���A�j���[�V��������*/
void Update_Tex_Tower(void);

/*���Ώۂ̃f�[�^���擾*/
TOWER* GetInfo_Tower(void);

#endif