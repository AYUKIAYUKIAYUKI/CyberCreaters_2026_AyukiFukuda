//************************************************
//
//�t�F�[�h�����A�w�b�_�t�@�C��[fade.h]
//Author�F���c����
//
//************************************************
#ifndef _FADE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _FADE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_FADE	"data\\TEX\\black.png"

#define RADIUS_FADE_X	(990.0f)	//������
#define RADIUS_FADE_Y	(540.0f)	//�c����

#define SPD_CHANGE_COL_FADE (0.05f)	//�t�F�[�h���x

//�t�F�[�h���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
	bool bFadeIn;
	bool bFadeOut;
}FADE;

//�v���g�^�C�v�錾

/*����*/
void Init_Fade(void);

/*�j��*/
void Uninit_Fade(void);

/*�X�V*/
void Update_Fade(void);

/*�`��*/
void Draw_Fade(void);

/*�t�F�[�h�Ƀf�[�^��t�^*/
void SetInfo_Fade(void);

/*�t�F�[�h�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Fade(void);

/*�t�F�[�h�̃o�[�e�b�N�X�J���[���X�V*/
void Update_Col_Fade(void);

/*�t�F�[�h�̃f�[�^���擾*/
FADE* GetInfo_Fade(void);

#endif