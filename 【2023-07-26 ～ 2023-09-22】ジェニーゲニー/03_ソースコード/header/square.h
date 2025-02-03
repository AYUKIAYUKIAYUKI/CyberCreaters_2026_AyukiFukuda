//************************************************
//
//���j���[�̎l�p�����A�w�b�_�t�@�C��[square.h]
//Author�F���c����
//
//************************************************
#ifndef _SQUARE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SQUARE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_SUQUARE_SMALL	"data\\TEX\\01_menu\\square000.png"
#define	TEXTURE_SUQUARE_MIDDLE	"data\\TEX\\01_menu\\square001.png"

#define AMOUNT_POLYGON_SQUARE	(16)	//�|���S����
#define AMOUNT_TEXTURE_SQUARE	(2)		//�Ǎ��݃e�N�X�`����

#define HALFSPAN_SMALL_SQUARE	(100.0f)
#define HALFSPAN_MIDDLE_SQUARE	(200.0f)

typedef struct
{
	int nStyle;			//���
	int nRute;			//�O��
	D3DXVECTOR3 pos;	//�ʒu
	float fSpan;		//�T�C�Y
	D3DXVECTOR3 move;	//�ړ����
	D3DXVECTOR3 rot;	//�������
	D3DXCOLOR col;		//�F
	int nCntSpawn;		//�o���^�C�~���O
}SQUARE;

//�v���g�^�C�v�錾
void Init_Square(void);
void Uninit_Square(void);
void Update_Square(void);
void Draw_Square(void);
void Setinfo_Square(void);
void Disappear_Square(int nCnt);

#endif