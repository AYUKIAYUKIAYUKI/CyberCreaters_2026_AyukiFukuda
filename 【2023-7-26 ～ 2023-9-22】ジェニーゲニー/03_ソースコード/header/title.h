//************************************************
//
//�^�C�g���\�������A�w�b�_�t�@�C��[title.h]
//Author�F���c����
//
//************************************************3
#ifndef _TITLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _TITLE_H _	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include "main.h"

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_SKY_TITLE	"data\\TEX\\00_title\\BG_Sky000.jpg"
#define	TEXTURE_CLOUD1_TITLE	"data\\TEX\\00_title\\cloud000.png"
#define	TEXTURE_CLOUD2_TITLE	"data\\TEX\\00_title\\cloud001.png"
#define	TEXTURE_CLOUD3_TITLE	"data\\TEX\\00_title\\cloud002.png"
#define	TEXTURE_ROSES_TITLE	"data\\TEX\\00_title\\roses000.png"
#define	TEXTURE_GARLAND2_TITLE	"data\\TEX\\00_title\\garland001.png"
#define	TEXTURE_GARLAND1_TITLE	"data\\TEX\\00_title\\garland000.png"
#define	TEXTURE_GEAR_TITLE	"data\\TEX\\00_title\\gears000.png"
#define	TEXTURE_PENDANT_TITLE	"data\\TEX\\00_title\\pendant000.png"
#define	TEXTURE_BROOCH_TITLE	"data\\TEX\\00_title\\brooch000.png"
#define	TEXTURE_KANZASHI_TITLE	"data\\TEX\\00_title\\kanzashi000.png"
#define	TEXTURE_CURTAIN_TITLE	"data\\TEX\\00_title\\curtain000.png"
#define	TEXTURE_PIGEON1_TITLE	"data\\TEX\\00_title\\pigeon000.png"
#define	TEXTURE_PIGEON2_TITLE	"data\\TEX\\00_title\\pigeon001.png"
#define	TEXTURE_GEARBIG_TITLE	"data\\TEX\\00_title\\gear000.png"
#define	TEXTURE_GEARFRAME_TITLE	"data\\TEX\\00_title\\gear002.png"
#define	TEXTURE_GEARSMALL_TITLE	"data\\TEX\\00_title\\gear001.png"
#define	TEXTURE_LOGO_TITLE	"data\\TEX\\00_title\\logo000.png"
#define	TEXTURE_PRESS_TITLE	"data\\TEX\\00_title\\title_text000.png"
#define	TEXTURE_WHITE_TITLE	"data\\TEX\\00_title\\whitebese.png"
#define	TEXTURE_BLACK_TITLE	"data\\TEX\\00_title\\blackbase.png"

#define AMOUNT_POLYGON_TITLE	(30)	//�|���S����
#define AMOUNT_TEXTURE_TITLE	(30)	//�Ǎ��݃e�N�X�`����

#define AMOUNT_USING_TEX_BG_TITLE	(4)		//�w�i�Ɏg���Ă�e�N�X�`����
#define MOVE_SPD_TEX_BG_TITLE	(0.0005f)	//�w�i�̃e�N�X�`���ړ����x

#define SKIP_VTX_TO_WHITE_TITLE	(28)		//�z���C�g�x�[�X�|���S���֒��_�����炷�p
#define CHANGE_SPD_WHITE_COLORA_TITLE	(25)	//�z���C�g�x�[�X��colA�ύX���x

#define SKIP_VTX_TO_LOGO_TITLE	(26)		//���S�|���S���֒��_�����炷�p
#define HALF_X_LOGO_TITLE	(462.75f)		//���SX�S��
#define MOVE_SPD_POS_LOGO_TITLE	(2.5f)		//���S���_���W�ړ����x
#define MOVE_SPD_TEX_LOGO_TITLE	(0.002375f)	//���S�e�N�X�`���ړ����x

#define AMOUNT_USING_TEX_ROSES_TITLE	(2)	//�o���Ɏg���Ă�e�N�X�`����
#define SKIP_VTX_TO_ROSES_TITLE	(4)			//�o���|���S���֒��_�����炷�p
#define CHANGE_SPD_ROSES_COLORA_TITLE	(9)//�o����colA�ύX���x

#define SKIP_VTX_TO_CURTAIN_TITLE	(14)	//�J�[�e���|���S���֒��_�����炷�p
#define MOVE_SPD_POS_CURTAIN_TITLE	(45.0f)	//�J�[�e�����_���W�ړ����x

#define AMOUNT_USING_TEX_GARLAND1_TITLE	(2)	//�K�[�����h1�Ɏg���Ă�e�N�X�`����
#define SKIP_VTX_TO_GARLAND1_TITLE	(8)		//�K�[�����h1�|���S���֒��_�����炷�p
#define MOVE_SPD_POS_GARLAND1_TITLE	(75.0f)	//�K�[�����h1���_���W�ړ����x

#define SKIP_VTX_TO_KANZASHI_TITLE	(13)	//���񂴂��|���S���֒��_�����炷�p
#define MOVE_SPD_POS_KANZASHI_TITLE	(75.0f)	//���񂴂����_���W�ړ����x

#define SKIP_VTX_TO_BROOCH_TITLE	(12)	//�u���[�`�|���S���֒��_�����炷�p
#define MOVE_SPD_POS_BROOCH_TITLE	(75.0f)	//�u���[�`���_���W�ړ����x

#define SKIP_VTX_TO_GEAR_TITLE	(11)	//���ԃ|���S���֒��_�����炷�p
#define MOVE_SPD_POS_GEAR_TITLE	(45.0f)	//���Ԓ��_���W�ړ����x

#define SKIP_VTX_TO_PENDANT_TITLE	(10)	//�y���_���g�|���S���֒��_�����炷�p
#define MOVE_SPD_POS_PENDANT_TITLE	(30.0f)	//�y���_���g���_���W�ړ����x

#define AMOUNT_USING_TEX_GARLAND2_TITLE	(2)	//�K�[�����h2�Ɏg���Ă�e�N�X�`����
#define SKIP_VTX_TO_GARLAND2_TITLE	(6)		//�K�[�����h2�|���S���֒��_�����炷�p
#define MOVE_SPD_POS_GARLAND2_TITLE	(10.0f)	//�K�[�����h2���_���W�ړ����x

#define AMOUNT_USING_TEX_GEARS_TITLE	(8)		//���ԌQ�Ɏg���Ă�e�N�X�`����
#define AMOUNT_USING_TEX_GEARBIG_TITLE	(2)		//���ԑ�Ɏg���Ă�e�N�X�`����
#define AMOUNT_USING_TEX_GEARFRAME_TITLE	(4)	//���Ԙg�Ɏg���Ă�e�N�X�`����
#define AMOUNT_USING_TEX_GEARSMALL_TITLE	(2)	//���ԏ��Ɏg���Ă�e�N�X�`����
#define SKIP_VTX_TO_GEARS_TITLE	(18)			//���ԌQ�|���S���֒��_�����炷�p
#define MOVE_SPD_POS_GEARS_TITLE		(10.0f)	//���ԌQ���_���W�ړ����x
#define SPAN_GEARBIG_TITLE	(372.0f)			//���ԑ�S��
#define HALFSPAN_GEARBIG_TITLE	(186.0f)		//���ԑ唼��
#define SPAN_GEARFRAME_TITLE	(200.0f)		//���g��S��
#define HALFSPAN_GEARFRAME_TITLE	(100.0f)	//���g�唼��
#define SPAN_GEARSMALL_TITLE	(206.0f)		//������S��
#define HALFSPAN_GEARSMALL_TITLE	(103.0f)	//�����唼��
#define ROTATE_SPD_GEARS_TITLE	(0.005f)		//���ԌQ��]���x

#define AMOUNT_USING_TEX_PIGEONS_TITLE	(2)	//�U�n�g�Ɏg���Ă�e�N�X�`����
#define SKIP_VTX_TO_PIGEONS_TITLE	(16)	//�U�n�g�|���S���֒��_�����炷�p

#define SPAN_PIGEON1_X_TITLE	(336.0f)		//�U�n�g1X�S��
#define HALF_SPAN_PIGEON1_X_TITLE	(168.0f)	//�U�n�g1X����
#define SPAN_PIGEON1_Y_TITLE	(385.0f)		//�U�n�g1Y�S��

#define SPAN_PIGEON2_X_TITLE	(420.0f)		//�U�n�g2X�S��
#define HALF_SPAN_PIGEON2_X_TITLE	(210.0f)	//�U�n�g2X����
#define SPAN_PIGEON2_Y_TITLE	(386.0f)		//�U�n�g2Y�S��

#define MOVE_SPD_PIGEONS_1_TITLE	(6.0f)		//�U�n�g�Q�X���C�h�ړ����x

#define SKIP_VTX_TO_PRESS_TITLE	(27)		//�v���X�|���S���֒��_�����炷�p
#define CHANGE_SPD_PRESS_COLORA_TITLE	(3)	//�v���X��colA�ύX���x

#define SKIP_VTX_TO_FADEOUT_TITLE	(29)	//�t�@�[�h�A�E�g�|���S���֒��_�����炷�p

#define MOVE_SPD_PIGEONS_1_X	(2.0f)
#define MOVE_SPD_PIGEONS_1_Y	(2.0f)
#define MOVE_SPD_PIGEONS_1_Z	(0.01f)
#define MOVE_SPD_PIGEONS_2_X	(2.0f)
#define MOVE_SPD_PIGEONS_2_Y	(2.0f)
#define MOVE_SPD_PIGEONS_2_Z	(0.01f)

//�v���g�^�C�v�錾
void Init_Title(void);
void Uninit_Title(void);
void Update_Title(void);
void Draw_Title(void);
void SetPos_Vtx_Title(void);
void Flash_Animation_Title(void);
void BG_Animation_Title(void);
void TitleLogo_Animation_Title(void);
void Roses_Animation_Title(void);
void Curtain_Animation_Title(void);
void Garland1_Animation_Title(void);
void Kanzashi_Animation_Title(void);
void Brooch_Animation_Title(void);
void Gear_Animation_Title(void);
void Pendant_Animation_Title(void);
void Garland2_Animation_Title(void);
void Gears_Animation_Title(void);
void Gears_Rotate_Title(void);
void Pigeons_Animation_Title(void);
void Pigeons_Rotate_Title(void);
void Press_Animation_Title(void);
void Fadeout_Animation_Title(void);
//float Set_Volume_Title(void);
void Setinfo_TitleLogoEX_Title(void);
void TitleLogo_AnimationEX_Title(void);
bool* StartFadeout(void);

#endif