//************************************************
//
//�|�[�Y��ʁA�w�b�_�t�@�C��[pause.h]
//Author�F���c����
//
//************************************************
#ifndef _PAUSE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PAUSE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_WHITE_PAUSE	"data\\TEX\\01_menu\\blackbase.png"

//�v���g�^�C�v�錾
void Init_Pause(void);
void Uninit_Pause(void);
void Update_Pause(void);
void Draw_Pause(void);
bool* Getinfo_Return_Pause(void);

#endif