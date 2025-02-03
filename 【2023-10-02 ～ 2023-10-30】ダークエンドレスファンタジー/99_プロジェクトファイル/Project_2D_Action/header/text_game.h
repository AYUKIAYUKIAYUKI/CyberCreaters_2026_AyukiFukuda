//************************************************
//
//�|�[�Y�e�L�X�g�����A�w�b�_�t�@�C��[text_game.h]
//Author�F���c����
//
//************************************************
#ifndef _TEXT_GAME_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TEXT_GAME_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_TEXT_GAME_1	"data\\TEX\\continue.png"
#define	TEXTURE_TEXT_GAME_2	"data\\TEX\\retry.png"
#define	TEXTURE_TEXT_GAME_3	"data\\TEX\\retire.png"

#define AMOUNT_POLYGON_TEXT_GAME	(3)	//�|�[�Y�e�L�X�g�̃|���S���ő吔
#define AMOUNT_TEX_TEXT_GAME	(3)	//�|�[�Y�e�L�X�g�̃e�N�X�`������

#define RADIUS_TEXT_GAME_X	(225.0f)	//������
#define RADIUS_TEXT_GAME_Y	(60.0f)	//�c����

//�|�[�Y�e�L�X�g���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}TEXT_GAME;

//�v���g�^�C�v�錾

/*����*/
void Init_Text_Game(void);

/*�j��*/
void Uninit_Text_Game(void);

/*�X�V*/
void Update_Text_Game(void);

/*�`��*/
void Draw_Text_Game(void);

/*�e�L�X�g�Ƀf�[�^��t�^*/
void SetInfo_Text_Game(void);

/*�e�L�X�g�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Text_Game(void);

/*�e�L�X�g�̃o�[�e�b�N�X�J���[���X�V*/
void Update_Col_Text_Game(void);

/*�e�L�X�g�̏����擾*/
TEXT_GAME* GetInfo_Text_Game(void);

#endif