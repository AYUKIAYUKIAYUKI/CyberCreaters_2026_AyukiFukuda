//************************************************
//
//�w�i�����A�w�b�_�t�@�C��[bg.h]
//Author�F���c����
//
//************************************************
#ifndef _BG_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BG_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�p*/
#define	TEXTURE_DEMO_BG	"data\\TEX\\02_game\\BG.png"

#define MOVE_SPD_TEX_BG	(0.0005f)	//�e�N�X�`���n�̈ړ����x

#define AMOUNT_POLYGON_BG	(1)	//�|���S����
#define AMOUNT_TEXTURE_BG	(1)	//�Ǎ��݃e�N�X�`����

typedef struct
{
	float texL;
	float texR;
	float moveSPD;
}BG;

//�v���g�^�C�v�錾
void Init_BG(void);
void Uninit_BG(void);
void Update_BG(void);
void Draw_BG(void);
void SetPos_Vtx_BG(void);

#endif