//************************************************
//
//�e�̃X�^�C���\�������A�w�b�_�t�@�C��)[style.h]
//Author�F���c����
//
//************************************************
#ifndef _STYLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _STYLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "bullet.h"

/*�}�N����`*/

/*�摜�p�X*/
#define	TEXTURE_REUNION_ODD_BULLET	""

#define AMOUNT_TEXTURE_STYLE	(6)		//�Ǎ��݃e�N�X�`����

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu�����i�[
	float fMoveZ;		//��]��
	D3DXVECTOR3 rot;	//�������i�[
	BULLETSTYLE style;	//�e�̎��
	float fLength;		//�e�̑Ίp��
	float fAngle;		//�e�̊p�x
	int nPattern;		//�A�j���p�^�[��
	float fTexX;		//�e�N�X�`�����WX
	float fTexY;		//�e�N�X�`�����WY
}BULLETSTYLE_INDICATE;

//�v���g�^�C�v�錾
void Init_Style(void);
void Uninit_Style(void);
void Update_Style(void);
void Draw_Style(void);

#endif