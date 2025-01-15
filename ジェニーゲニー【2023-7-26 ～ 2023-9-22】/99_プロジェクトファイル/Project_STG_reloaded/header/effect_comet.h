//************************************************
//
//�R���b�g�G�t�F�N�g�����A�w�b�_�t�@�C��[effect_comet.h]
//Author�F���c����
//
//************************************************
#ifndef _EFFECT_COMET_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _EFFECT_COMET_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_EFFECT_COMET	"data\\TEX\\02_game\\comet_explosion.png"

#define AMOUNT_POLYGON_EFFECT_COMET	(128)	//�|���S����

#define SPAN_X_EFFECT_COMET	(150.0f)	//X�S��
#define SPAN_Y_EFFECT_COMET	(150.0f)	//Y�S��
#define	HALFSPAN_X_EFFECT_COMET	(75.0f)	//X����
#define HALFSPAN_Y_EFFECT_COMET	(75.0f)	//Y����

#define ROTATE_SPD_EFFECT_COMET	(0.1f)	//�G�t�F�N�g��]���x

//�X�|�[���G�t�F�N�g�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu�����i�[
	D3DXVECTOR3 move;	//�ړ��ʂ��i�[
	D3DXVECTOR3 rot;	//���������i�[
	bool bUse;			//���ꂪ�g���Ă��邩����
	float fLength;		//�Ίp�����i�[
	float fAngle;		//�Ίp���̊p�x���i�[
	int nPattern;		//�A�j���[�V����
	float fTexX;		//�e�N�X�`�����WX
	float fTexY;		//�e�N�X�`�����WY
}COMET_EFFECT;

//�v���g�^�C�v�錾
void Init_Effect_Comet(void);
void Uninit_Effect_Comet(void);
void Update_Effect_Comet(void);
void Draw_Effect_Comet(void);
void SetPos_Vtx_Effect_Comet(D3DXVECTOR3 pos, float moveX);

#endif