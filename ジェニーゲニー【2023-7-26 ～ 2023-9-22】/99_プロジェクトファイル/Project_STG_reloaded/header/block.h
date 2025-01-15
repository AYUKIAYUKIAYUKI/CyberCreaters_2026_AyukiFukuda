//************************************************
//
//�u���b�N�A�w�b�_�t�@�C��[block.h]
//Author�F���c����
//
//************************************************
#ifndef _BLOCK_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BLOCK_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include <stdio.h>

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_SHROT_1_BLOCK	"data\\TEX\\02_game\\block_short000.png"
#define	TEXTURE_SHROT_2_BLOCK	"data\\TEX\\02_game\\block_short001.png"
#define	TEXTURE_MIDDLE_1_BLOCK	"data\\TEX\\02_game\\block_MIDDLE000.png"
#define	TEXTURE_MIDDLE_2_BLOCK	"data\\TEX\\02_game\\block_MIDDLE001.png"
#define	TEXTURE_TALL_1_BLOCK	"data\\TEX\\02_game\\block_tall000.png"
#define	TEXTURE_TALL_2_BLOCK	"data\\TEX\\02_game\\block_tall001.png"

/*�t�@�C���p�X�n*/
#define	FILE_SET_BLOCK	"data\\csv\\BlockInfo.csv"

#define AMOUNT_POLYGON_BLOCK	(64)	//�u���b�N�̐�
#define AMOUNT_TEXTURE_BLOCK	(6)		//�Ǎ��݃e�N�X�`����

#define AMOUNT_DATA_BLOCK	(11)	//�u���b�N1������̃f�[�^��

//�u���b�N�̎�ޕ����񋓌^
typedef enum
{
	BLOCKSTYLE_SHROT_1 = 0,
	BLOCKSTYLE_SHROT_2,
	BLOCKSTYLE_MIDDLE_1,
	BLOCKSTYLE_MIDDLE_2,
	BLOCKSTYLE_TALL_1,
	BLOCKSTYLE_TALL_2,
	BLOCKSTYLE_MAX,
}BLOCKSTYLE;

//�u���b�N�\����
typedef struct
{
	int nStyle;			//�u���b�N�̎��
	D3DXVECTOR3 pos;	//�u���b�N�̈ʒu�����i�[
	float fHalfSpanX;	//�u���b�N�̉���
	float fHalfSpanY;	//�u���b�N�̉���
	D3DXVECTOR3 move;	//�u���b�N�̈ړ������i�[
	D3DXVECTOR3 rot;	//�u���b�N�̌��������i�[
	bool bUse;			//�d�l����
	int nCntSpawn;		//���o�����邩
	float fLength;		//�Ίp�����i�[
	float fAngle;		//�Ίp���̊p�x���i�[
}BLOCK;

//�v���g�^�C�v�錾
void Init_Block(void);
void Uninit_Block(void);
void Update_Block(void);
void Draw_Block(void);
void Setinfo_Block(void);
BLOCK* Getinfo_Block(void);

#endif