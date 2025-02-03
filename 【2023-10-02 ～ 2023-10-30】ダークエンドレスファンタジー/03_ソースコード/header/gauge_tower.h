//************************************************
//
//���ΏۃQ�[�W�����A�w�b�_�t�@�C��[gauge_tower.h]
//Author�F���c����
//
//************************************************
#ifndef _GAUGE_TOWER_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _GAUGE_TOWER_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_GAUGE_TOWER	"data\\TEX\\gage_life_f.png"
#define	TEXTURE_GAUGE_HEART	"data\\TEX\\heart.png"

#define AMOUNT_POLYGON_GAUGE_TOWER	(2)	//���C�t�Q�[�W�̃|���S���ő吔
#define AMOUNT_TEX_GAUGE_TOWER	(2)	//���C�t�Q�[�W�̃e�N�X�`������

#define RADIUS_GAUGE_TOWER_X	(200.0f)	//������
#define RADIUS_GAUGE_TOWER_Y	(35.0f)	//�c����

#define RADIUS_GAUGE_HEART_X	(70.0f)	//������
#define RADIUS_GAUGE_HEART_Y	(70.0f)	//�c����

#define SPAN_EACH_GAUGE_TOWER_X	(225.0f)	//�n�[�g�ƃQ�[�W�̈ʒu����
#define SPAN_EACH_GAUGE_TOWER_Y	(15.0f)	//�n�[�g�ƃQ�[�W�̈ʒu����

#define SPAN_CHANGE_TEX_GAUGE_TOWER	(0.125f)	//�A�j���[�V�����p

//���ΏۃQ�[�W�̃p�[�c����
typedef enum
{
	GAUGE_TOWER_STYLE_GAUGE = 0,
	GAUGE_TOWER_STYLE_HEART,
	GAUGE_TOWER_STYLE_MAX,
}GAUGE_TOWER_STYLE;

//���C�t�Q�[�W���̗񋓌^
typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	int nCntTex;		//�e�N�X�`���ύX
	float fTexSpan[2];	//�e�N�X�`����
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
}GAUGE_TOWER;

//�v���g�^�C�v�錾

/*����*/
void Init_Gauge_Tower(void);

/*�j��*/
void Uninit_Gauge_Tower(void);

/*�X�V*/
void Update_Gauge_Tower(void);

/*�`��*/
void Draw_Gauge_Tower(void);

/*���ΏۃQ�[�W�Ƀf�[�^��t�^*/
void SetInfo_Gauge_Tower(void);

/*���ΏۃQ�[�W�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Gauge_Tower(void);

/*���ΏۃQ�[�W�̃o�[�e�b�N�X�J���[���X�V*/
void Update_Col_Gauge_Tower(void);

/*���ΏۃQ�[�W�̃e�N�X�`���A�j���[�V��������*/
void Update_Tex_Gauge_Tower(void);

/*���ΏۃQ�[�W�̃f�[�^���擾*/
GAUGE_TOWER* GetInfo_Gauge_Tower(void);

#endif