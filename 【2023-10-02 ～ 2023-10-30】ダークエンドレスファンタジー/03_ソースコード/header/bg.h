//************************************************
//
//�w�i�����A�w�b�_�t�@�C��[bg.h]
//Author�F���c����
//
//************************************************
#ifndef _BG_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BG_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_BG_1	"data\\TEX\\BG_0.png"
#define	TEXTURE_BG_2	"data\\TEX\\BG_1.png"
#define	TEXTURE_BG_3	"data\\TEX\\BG_2.png"
#define	TEXTURE_BG_4	"data\\TEX\\BG_3.png"
#define	TEXTURE_BG_5	"data\\TEX\\BG_4.png"
#define	TEXTURE_BG_6	"data\\TEX\\BG_5.png"
#define	TEXTURE_BG_7	"data\\TEX\\BG_6.png"
#define	TEXTURE_BG_8	"data\\TEX\\BG_7.png"
#define	TEXTURE_BG_9	"data\\TEX\\BG_8.png"
#define	TEXTURE_BG_10	"data\\TEX\\BG_EX.png"

#define AMOUNT_POLYGON_BG	(9)	//�w�i�̃|���S���ő吔
#define AMOUNT_TEX_BG	(9)	//�w�i�̃e�N�X�`������

#define RADIUS_BG_X	(1080.0f)	//������
#define RADIUS_BG_Y	(540.0f)	//�c����

#define RADIUS_CLOUD_X	(100.0f)	//������
#define RADIUS_CLOUD_Y	(75.0f)	//�c����

//�w�i�p���[�h����
typedef enum
{
	BG_TYPE_TITLE = 0,
	BG_TYPE_GAME,
	BG_TYPE_MAX,
}BG_TYPE;

//�w�i���̗񋓌^
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
	int nLayer;			//
	float fTex[2];		//
}BG;

//�v���g�^�C�v�錾

/*����*/
void Init_BG(int nMode);

/*�j��*/
void Uninit_BG(void);

/*�X�V*/
void Update_BG(void);

/*�`��*/
void Draw_BG(void);

/*�w�i�Ƀf�[�^��t�^*/
void SetInfo_BG(void);

/*�w�i�̃o�[�e�b�N�X���X�V*/
void Update_Pos_BG(void);

/*�w�i�̃o�[�e�b�N�X�J���[���X�V*/
void Update_Col_BG(void);

/*�w�i�̃e�N�X�`���A�j���[�V��������*/
void Update_Tex_BG(void);

/*�w�i�̃f�[�^���擾*/
BG* GetInfo_BG(void);

#endif