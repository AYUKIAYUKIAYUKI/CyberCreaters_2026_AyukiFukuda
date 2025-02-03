//************************************************
//
//�A�C�e�������A�w�b�_�t�@�C��[item.h]
//Author�F���c����
//
//************************************************
#ifndef _ITEM_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _ITEM_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_ITEM	"data\\TEX\\02_game\\item000.png"

#define AMOUNT_POLYGON_ITEM	(64)	//�|���S����

#define SPAN_X_ITEM	(50.0f)	//X�S��
#define SPAN_Y_ITEM	(50.0f)	//Y�S��
#define	HALFSPAN_X_ITEM	(25.0f)	//X����
#define HALFSPAN_Y_ITEM	(25.0f)	//Y����

#define REMAIN_TIME_ITEM	(60)	//�ҋ@����
#define FRASH_TIME_ITEM	(30)		//�_�Ŏ���

#define AMOUNT_ADD_LIFE	(30)	//�L���p�񕜗�

//�A�C�e���̎�ނ̗񋓌^
typedef enum
{
	ITEMSTYLE_TRACE = 0,	//�L���p�񕜃A�C�e��
	ITEMSTYLE_MAX,			//�A�C�e���̎�ޑ���
}ITEMSTYLE;

//�A�C�e���̏�ԕ����񋓌^
typedef enum
{
	ITEMSTATE_NORMAL = 0,	//�ʏ���
	ITEMSTATE_FLASHING,		//�_�ŏ��
	ITEMSTATE_DISAPPEAR,	//���ŏ��
	ITEMSTATE_MAX,			//��Ԃ̑���
}ITEMSTATE;

//�A�C�e���̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu�����i�[
	D3DXVECTOR3 move;	//�ړ��ʏ����i�[
	D3DCOLOR col;		//�F�����i�[
	int nRemain;		//�c������
	bool bUse;			//�g�p�󋵔���
	ITEMSTYLE style;	//�A�C�e���̎��
	ITEMSTATE state;	//�A�C�e���̏��
	float fColorA;		//�����x�ύX�p
	float fRadius;		//���a���i�[
}ITEM;

//�v���g�^�C�v�錾
void Init_Item(void);
void Uninit_Item(void);
void Update_Item(void);
void Draw_Item(void);
void Setinfo_Item(D3DXVECTOR3 pos, int nStyle);
void Disappear_Item(int nCntItem);

#endif