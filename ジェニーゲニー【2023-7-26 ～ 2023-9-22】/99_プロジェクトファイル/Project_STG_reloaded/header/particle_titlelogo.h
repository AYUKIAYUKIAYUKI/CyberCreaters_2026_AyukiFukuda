//************************************************
//
//�^�C�g�����S�p�[�e�B�N�������A�w�b�_�t�@�C��[particle_titlelogo.h]
//Author�F���c����
//
//************************************************
#ifndef _PARTICLE_TITLELOGO_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PARTICLE_TITLELOGO_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�f�o�b�O�p*/
#define	TEXTURE_PARTICLE_TITLELOGO	"data\\TEX\\02_game\\effect0001.png"

#define AMOUNT_POLYGON_PARTICLE_TITLELOGO	(8)	//�|���S����

#define RADIUS_PARTICLE_TITLELOGO	(20.0f)		//���a�p
#define REMAIN_TIME_PARTICLE_TITLELOGO	(180)	//�c������


#define MOVE_SPD_POS_PARTICLE_TITLELOGO	(1.0f)			//�ړ����x
#define CHANGE_SPD_RADIUS_PARTICLE_TITLELOGO	(0.25f)	//�k�����x

//�p�[�e�B�N���\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu�����i�[
	D3DXVECTOR3 move;	//�ړ������i�[
	D3DXCOLOR col;		//�F�����i�[
	float fRadius;		//���a���i�[
	int nRemain;		//�c�����Ԃ��i�[
	bool bUse;			//���ꂪ�g���Ă��邩����
}PARTICLE_TITLELOGO;

//�v���g�^�C�v�錾
void Init_Particle_Titlelogo(void);
void Uninit_Particle_Titlelogo(void);
void Update_Particle_Titlelogo(void);
void Draw_Particle_Titlelogo(void);
void Setinfo_Particle_Titlelogo(D3DXVECTOR3 pos);

#endif