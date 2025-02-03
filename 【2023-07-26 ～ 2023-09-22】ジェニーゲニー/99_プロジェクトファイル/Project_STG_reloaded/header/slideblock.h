//************************************************
//
//�X���C�h�u���b�N�A�w�b�_�t�@�C��[slideblock.h]
//Author�F���c����
//
//************************************************
#ifndef _SLIDEBLOCK_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SLIDEBLOCK_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include <stdio.h>
#include "block.h"

//�}�N����`

/*�t�@�C���p�X�n*/
#define	FILE_SET_SLIDEBLOCK	"data\\csv\\SlideBlockInfo.csv"

#define AMOUNT_POLYGON_SLIDEBLOCK	(64)	//�X���C�h�u���b�N�̐�

#define AMOUNT_DATA_SLIDEBLOCK	(13)	//�X���C�h�u���b�N1������̃f�[�^��

//�u���b�N�̎�ޕ����񋓌^
typedef enum
{
	SLIDEBLOCKSTYLE_SHROT_1 = 0,
	SLIDEBLOCKSTYLE_SHROT_2,
	SLIDEBLOCKSTYLE_MIDDLE_1,
	SLIDEBLOCKSTYLE_MIDDLE_2,
	SLIDEBLOCKSTYLE_TALL_1,
	SLIDEBLOCKSTYLE_TALL_2,
	SLIDEBLOCKSTYLE_MAX,
}SLIDEBLOCKSTYLE;

//�u���b�N�\����
typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu���
	float fHalfSpanX;	//����
	float fHalfSpanY;	//����
	D3DXVECTOR3 move;	//�ړ����
	float fStop;		//�X���C�h��~
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�ǂ�ȐF
	float fColChange;	//�ؗ���
	bool bUse;			//�d�l����
	int nCntSpawn;		//���o�����邩
	float fLength;		//�Ίp�����i�[
	float fAngle;		//�Ίp���̊p�x���i�[
}SLIDEBLOCK;

//�v���g�^�C�v�錾
void Init_SlideBlock(void);
void Uninit_SlideBlock(void);
void Update_SlideBlock(void);
void Draw_SlideBlock(void);
void Setinfo_SlideBlock(void);
SLIDEBLOCK* Getinfo_SlideBlock(void);
void Disapper_SlideBlock(int nCntSlideBlock);

#endif