//************************************************
//
//�t���ς����������A�w�b�_�t�@�C��[leaves.h]
//Author�F���c����
//
//************************************************
#ifndef _LEAVES_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _LEAVES_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_LEAF_1	"data\\TEX\\02_game\\leaf000.png"
#define	TEXTURE_LEAF_2	"data\\TEX\\02_game\\leaf001.png"
#define	TEXTURE_LEAF_3	"data\\TEX\\02_game\\leaf002.png"
#define	TEXTURE_LEAF_4	"data\\TEX\\02_game\\leaf003.png"
#define	TEXTURE_LEAF_5	"data\\TEX\\02_game\\leaf004.png"

#define AMOUNT_POLYGON_LEAVES	(16)//�|���S����
#define AMOUNT_TEXTURE_LEAVES	(5)	//�Ǎ��݃e�N�X�`����

#define HALFSPAN_X_TINYLEAF_1	(20)	//�ׂ��t���ς̉���
#define HALFSPAN_X_LEAF_1	(40)	//���ʂ̗t���ς̉���
#define HALFSPAN_Y_LEAF_1	(40)	//�t���ϋ��ʂ̏c��

//�t���ύ\����
typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu�����i�[
	float fHalfSpanX;	//����
	float fHalfSpanY;	//�c��
	int nRute;			//�ǂ�������
	int nKeepTime;		//���̓����������������
	D3DXVECTOR3 move;	//�ړ������i�[
	D3DXVECTOR3 rot;	//���������i�[
	bool bUse;			//�d�l����
	int nCntSpawn;		//���o�����邩
	float fLength;		//�Ίp�����i�[
	float fAngle;		//�Ίp���̊p�x���i�[
}LEAVES;


//�v���g�^�C�v�錾
void Init_Leaves(void);
void Uninit_Leaves(void);
void Update_Leaves(void);
void Draw_Leaves(void);
void SetSpan_Leaves(void);
void Setinfo_Leaves(void);
void Disappear_Leaves(int nCnt);

#endif