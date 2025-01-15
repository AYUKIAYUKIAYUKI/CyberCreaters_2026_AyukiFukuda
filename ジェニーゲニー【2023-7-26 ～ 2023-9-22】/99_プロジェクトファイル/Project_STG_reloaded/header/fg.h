//************************************************
//
//�O�i�����A�w�b�_�t�@�C��[fg.h]
//Author�F���c����
//
//************************************************
#ifndef _FG_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _FG_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_IVY_1	"data\\TEX\\02_game\\ivy000.png"
#define	TEXTURE_IVY_2	"data\\TEX\\02_game\\ivy002.png"
#define	TEXTURE_IVY_3	"data\\TEX\\02_game\\ivy003.png"
//#define	TEXTURE_BUSH_1	"data\\TEX\\02_game\\bush000.png"

#define AMOUNT_POLYGON_FG	(8)	//�|���S����
#define AMOUNT_TEXTURE_FG	(3)	//�Ǎ��݃e�N�X�`����

#define HALFSPAN_X_IVY	(300.0f)		//�c�^������
#define HALFSPAN_X_LONGIVY	(600.0f)	//�����c�^������
#define HALFSPAN_Y_IVY	(300.0f)		//�c�^�c����
#define HALFSPAN_Y_LONGIVY	(150.0f)	//�����c�^�c����

//#define HALFSPAN_X_BUSH	(300.0f)		//���ނ牡����
//#define HALFSPAN_X_LONGBUSH	(450.0f)	//�������ނ牡����
//#define HALFSPAN_Y_BUSH	(300.0f)		//���ނ�c����

//�O�i�|���S���p�\����
typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	bool bUse;			//�d�l����
	int nCntSpawn;		//���o�����邩
	float fLength;		//�Ίp�����i�[
	float fAngle;		//�Ίp���̊p�x���i�[
}FG_OBJECT;

//�v���g�^�C�v�錾
void Init_FG(void);
void Uninit_FG(void);
void Update_FG(void);
void Draw_FG(void);
void SetSpan_FG(void);
void Setinfo_Vtx_FG(void);
void Disappear_FG(int nCnt);

#endif