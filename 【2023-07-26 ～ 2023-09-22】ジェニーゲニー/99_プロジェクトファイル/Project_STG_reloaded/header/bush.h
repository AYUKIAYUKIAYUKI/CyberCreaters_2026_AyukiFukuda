//************************************************
//
//���ނ珈���A�w�b�_�t�@�C��[bush.h]
//Author�F���c����
//
//************************************************
#ifndef _BUSH_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BUSH_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_BUSH_1	"data\\TEX\\02_game\\bush000.png"
#define	TEXTURE_BUSH_2	"data\\TEX\\02_game\\bush001.png"
#define	TEXTURE_BUSH_3	"data\\TEX\\02_game\\bush002.png"
#define	TEXTURE_BUSH_4	"data\\TEX\\02_game\\bush003.png"
#define	TEXTURE_BUSH_5	"data\\TEX\\02_game\\bush004.png"

#define AMOUNT_POLYGON_BUSH	(16)	//�|���S����
#define AMOUNT_TEXTURE_BUSH	(5)	//�Ǎ��݃e�N�X�`����

#define HALFSPAN_X_BUSH	(300.0f)		//���ނ牡����
#define HALFSPAN_X_LONGBUSH	(450.0f)	//�������ނ牡����
#define HALFSPAN_Y_BUSH	(300.0f)		//���ނ�c����

//���ނ�p�\����
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
}BUSH;

//�v���g�^�C�v�錾
void Init_Bush(void);
void Uninit_Bush(void);
void Update_Bush(void);
void Draw_Bush(void);
void SetSpan_Bush(void);
void Setinfo_Vtx_Bush(void);
void Disappear_Bush(int nCnt);

#endif