//************************************************
//
//UI�̌��̏����A�w�b�_�t�@�C��[back.h]
//Author�F���c����
//
//************************************************
#ifndef _BACK_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BACK_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_BACK	"data\\TEX\\black.png"

#define AMOUNT_POLYGON_BACK	(2)	//�|���S����

//UI�̌��̏��̗񋓌^
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}BACK;

//�v���g�^�C�v�錾

/*����*/
void Init_Back(void);

/*�j��*/
void Uninit_Back(void);

/*�X�V*/
void Update_Back(void);

/*�`��*/
void Draw_Back(void);

/*�|�[�Y�E�B���h�E�Ƀf�[�^��t�^*/
void SetInfo_Back(void);

/*�|�[�Y�E�B���h�E�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Back(void);

/*�|�[�Y�E�B���h�E�̃f�[�^���擾*/
BACK* GetInfo_Back(void);

#endif