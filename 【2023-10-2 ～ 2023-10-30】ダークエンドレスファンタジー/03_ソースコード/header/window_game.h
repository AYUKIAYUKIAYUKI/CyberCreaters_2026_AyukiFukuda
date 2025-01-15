//************************************************
//
//�|�[�Y�E�B���h�E�����A�w�b�_�t�@�C��[window_game.h]
//Author�F���c����
//
//************************************************
#ifndef _WINDOW_GAME_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _WINDOW_GAME_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_WHTITE_PAUSE	"data\\TEX\\white.png"
#define	TEXTURE_WINDOW_GAME	"data\\TEX\\window.png"
#define	TEXTURE_TEXT_PAUSE	"data\\TEX\\pause.png"

#define AMOUNT_POLYGON_WINDOW_GAME	(3)	//�|�[�Y�E�B���h�E�̃|���S���ő吔
#define AMOUNT_TEX_WINDOW_GAME	(3)	//�|�[�Y�E�B���h�E�̃e�N�X�`������

#define RADIUS_TEXT_PAUSE_X	(250.0f)	//�|�[�Y�e�L�X�g�̉���
#define RADIUS_TEXT_PAUSE_Y	(80.0f)	//�|�[�Y�e�L�X�g�̏c��

//�|�[�Y�E�B���h�E���̗񋓌^
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}WINDOW_GAME;

//�v���g�^�C�v�錾

/*����*/
void Init_Window_Game(void);

/*�j��*/
void Uninit_Window_Game(void);

/*�X�V*/
void Update_Window_Game(void);

/*�`��*/
void Draw_Window_Game(void);

/*�|�[�Y�E�B���h�E�Ƀf�[�^��t�^*/
void SetInfo_Window_Game(void);

/*�|�[�Y�E�B���h�E�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Window_Game(void);

/*�|�[�Y�E�B���h�E�̃f�[�^���擾*/
WINDOW_GAME* GetInfo_Window_Game(void);

#endif