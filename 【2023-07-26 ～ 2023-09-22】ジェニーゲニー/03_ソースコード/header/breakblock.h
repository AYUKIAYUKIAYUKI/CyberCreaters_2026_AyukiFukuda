//************************************************
//
//�u���C�N�X���C�h�u���b�N�A�w�b�_�t�@�C��[breakblock.h]
//Author�F���c����
//
//************************************************
#ifndef _BREAKBLOCK_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BREAKBLOCK_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include <stdio.h>
#include "block.h"

//�}�N����`

/*�t�@�C���p�X�n*/
#define	FILE_SET_BREAKBLOCK	"data\\csv\\BreakBlockInfo.csv"

#define AMOUNT_POLYGON_BREAKBLOCK	(64)	//�X���C�h�u���b�N�̐�

#define AMOUNT_DATA_BREAKBLOCK	(12)	//�X���C�h�u���b�N1������̃f�[�^��

//�u���b�N�̎�ޕ����񋓌^
typedef enum
{
	BREAKBLOCKSTYLE_SHROT_1 = 0,
	BREAKBLOCKSTYLE_SHROT_2,
	BREAKBLOCKSTYLE_MIDDLE_1,
	BREAKBLOCKSTYLE_MIDDLE_2,
	BREAKBLOCKSTYLE_TALL_1,
	BREAKBLOCKSTYLE_TALL_2,
	BREAKBLOCKSTYLE_MAX,
}BREAKBLOCKSTYLE;

//�u���b�N�̏�ԕ���
typedef enum
{
	BREAKBLOCKSTATE_BROKEN = 0,
	BREAKBLOCKSTATE_LIFE1,
	BREAKBLOCKSTATE_LIFE2,
	BREAKBLOCKSTATE_LIFE3,
	BREAKBLOCKSTATE_MAX,
}BREAKBLOCKSTATE;

//�u���b�N�\����
typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu���
	float fHalfSpanX;	//����
	float fHalfSpanY;	//����
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�ǂ�ȐF
	bool bUse;			//�d�l����
	int nCntSpawn;		//���o�����邩
	int nLife;			//�����ŉ���H
	float fLength;		//�Ίp�����i�[
	float fAngle;		//�Ίp���̊p�x���i�[
}BREAKBLOCK;

//�v���g�^�C�v�錾
void Init_BreakBlock(void);
void Uninit_BreakBlock(void);
void Update_BreakBlock(void);
void Draw_BreakBlock(void);
void Setinfo_BreakBlock(void);
void Hit_BreakBlock(int nCntBreakBlock, int nDamage);
BREAKBLOCK* Getinfo_BreakBlock(void);

#endif