//************************************************
//
//�|�[�Y�J�[�\�������A�w�b�_�t�@�C��[cursor_game.h]
//Author�F���c����
//
//************************************************
#ifndef _CURSOR_GAME_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _CURSOR_GAME_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_CURSOR_GAME_1	"data\\TEX\\dain.png"

#define RADIUS_CURSOR_GAME_X	(50.0f)	//������
#define RADIUS_CURSOR_GAME_Y	(50.0f)	//�c����

//�|�[�Y�J�[�\�����̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}CURSOR_GAME;

//�v���g�^�C�v�錾

/*����*/
void Init_Cursor_Game(void);

/*�j��*/
void Uninit_Cursor_Game(void);

/*�X�V*/
void Update_Cursor_Game(void);

/*�`��*/
void Draw_Cursor_Game(void);

/*�J�[�\���Ƀf�[�^��t�^*/
void SetInfo_Cursor_Game(void);

/*�J�[�\���̃o�[�e�b�N�X���X�V*/
void Update_Pos_Cursor_Game(void);

/*�J�[�\���̏����擾*/
CURSOR_GAME* GetInfo_Cursor_Game(void);

#endif