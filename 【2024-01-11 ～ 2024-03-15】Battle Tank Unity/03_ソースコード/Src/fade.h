//===============================================================================
//
//  3D�`�[������(fade.h)
//								����F���n�O��
// 
//===============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
//�t�F�[�h�p�\����
typedef struct
{
	int nType;
	bool bUse;
	bool bFinish;
	MODE mode;
	bool bSoundUse[2];
}FADE;

//�t�F�[�h�ڍs��p�񋓌^
typedef enum
{
	FADE_IN = 0,
	FADE_OUT,
	FADE_MAX
}FADE_SET;

//�v���g�^�C�v�錾
void InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(int nType,MODE mode);
#endif 
