////************************************************
////
////���C�t�Q�[�W�����A�w�b�_�t�@�C��[bg.h]
////Author�F���c����
////
////************************************************
//#ifndef _GAGE_LIFE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
//#define _GAGE_LIFE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)
//
////�}�N����`
//
///*�摜�p�X�n*/
//#define	TEXTURE_GAGE_LIFE	"data\\TEX\\gage_life_f.png"
//#define	TEXTURE_GAGE_HEART	"data\\TEX\\heart.png"
//
//#define AMOUNT_POLYGON_GAGE_LIFE	(2)	//���C�t�Q�[�W�̃|���S���ő吔
//#define AMOUNT_TEX_GAGE_LIFE	(2)	//���C�t�Q�[�W�̃e�N�X�`������
//
//#define RADIUS_GAGE_LIFE_X	(200.0f)	//������
//#define RADIUS_GAGE_LIFE_Y	(35.0f)	//�c����
//
//#define RADIUS_GAGE_HEART_X	(70.0f)	//������
//#define RADIUS_GAGE_HEART_Y	(70.0f)	//�c����
//
//#define SPAN_EACH_GAGE_LIFE_X	(225.0f)	//�n�[�g�ƃQ�[�W�̈ʒu����
//#define SPAN_EACH_GAGE_LIFE_Y	(15.0f)	//�n�[�g�ƃQ�[�W�̈ʒu����
//
////#define SPD_CHANGE_TEX_GAGE_LIFE	(20)	//�A�j���[�V�������x
////#define AMOUNT_STYLE_TEX_GAGE_LIFE	(8)	//�A�j���[�V�����p
//#define SPAN_CHANGE_TEX_GAGE_LIFE	(0.125f)	//�A�j���[�V�����p
//
////���C�t�Q�[�W�̃p�[�c����
//typedef enum
//{
//	GAGE_LIFE_STYLE_GAGE = 0,
//	GAGE_LIFE_STYLE_HEART,
//	GAGE_LIFE_STYLE_MAX,
//}GAGE_LIFE_STYLE;
//
////���C�t�Q�[�W���̗񋓌^
//typedef struct
//{
//	int nStyle;			//���
//	D3DXVECTOR3 pos;	//�ʒu
//	D3DXVECTOR3 move;	//�ړ���
//	D3DXVECTOR3 rot;	//����
//	D3DXCOLOR col;		//�F
//	int nCntTex;		//�e�N�X�`���ύX
//	float fTexSpan[2];	//�e�N�X�`����
//	float fRadius[2];	//���a
//	float fLength[2];	//�Ίp��
//	float fAngle[2];	//�p�x
//}GAGE_LIFE;
//
////�v���g�^�C�v�錾
//
///*����*/
//void Init_Gage_Life(void);
//
///*�j��*/
//void Uninit_Gage_Life(void);
//
///*�X�V*/
//void Update_Gage_Life(void);
//
///*�`��*/
//void Draw_Gage_Life(void);
//
///*���C�t�Q�[�W�Ƀf�[�^��t�^*/
//void SetInfo_Gage_Life(void);
//
///*���C�t�Q�[�W�̃o�[�e�b�N�X���X�V*/
//void Update_Pos_Gage_Life(void);
//
///*�w�i�̃o�[�e�b�N�X�J���[���X�V*/
//void Update_Col_Gage_Life(void);
//
///*���C�t�Q�[�W�̃e�N�X�`���A�j���[�V��������*/
//void Update_Tex_Gage_Life(void);
//
///*���C�t�Q�[�W�̃f�[�^���擾*/
//GAGE_LIFE* GetInfo_Gage_Life(void);
//
//#endif