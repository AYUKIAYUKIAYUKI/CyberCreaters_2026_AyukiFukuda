//************************************************
//
//�t�F�[�h�����A�w�b�_�t�@�C��[fade.h]
//Author�F���c����
//
//************************************************
#ifndef _FADE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _FADE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

/*�摜�p�X�n*/
#define	TEXTURE_FADE	"data\\TEX\\black.png"

#define RADIUS_FADE_X	(990.0f)	//������
#define RADIUS_FADE_Y	(540.0f)	//�c����

#define SPD_CHANGE_COL_FADE (0.05f)	//�t�F�[�h���x

//�t�F�[�h���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
	bool bFadeIn;
	bool bFadeOut;
}FADE;

//�v���g�^�C�v�錾
void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetInfoFade(void);
void UpdatePosFade(void);
void UpdateColFade(void);
FADE* GetInfoFade(void);

#endif