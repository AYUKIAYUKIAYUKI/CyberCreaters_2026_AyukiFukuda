//************************************************
//
//�E�B���h�E���U���g�����A�w�b�_�t�@�C��[window_result.h]
//Author�F���c����
//
//************************************************
#ifndef _WINDOW_RESULT_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _WINDOW_RESULT_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_WINDOW_RESULT1	"data\\TEX\\success.png"
#define	TEXTURE_WINDOW_RESULT2	"data\\TEX\\fail.png"

#define AMOUNT_TEX_WINDOW_RESULT	(2)	//�e�N�X�`����

#define RADIUS_WINDOW_RESULT_X	(600.0f)	//������
#define RADIUS_WINDOW_RESULT_Y	(200.0f)	//�c����

//�e�X�g���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
}WINDOW_RESULT;

//�v���g�^�C�v�錾

/*����*/
void Init_Window_Result(void);

/*�j��*/
void Uninit_Window_Result(void);

/*�X�V*/
void Update_Window_Result(void);

/*�`��*/
void Draw_Window_Result(void);

/*�E�B���h�E�Ƀf�[�^��t�^*/
void SetInfo_Window_Result(void);

/*�E�B���h�E�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Window_Result(void);

/*�E�B���h�E�̃f�[�^���擾*/
WINDOW_RESULT* GetInfo_Window_Result(void);

#endif