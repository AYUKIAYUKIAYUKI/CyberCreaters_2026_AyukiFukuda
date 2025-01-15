//************************************************
//
//�p�[�e�B�N������(�e���v��)�A�w�b�_�t�@�C��[particle.h]
//Author�F���c����
//
//************************************************
#ifndef _PARTICLE_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PARTICLE_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�f�o�b�O�p*/
#define	TEXTURE_PARTICLE	"data\\TEX\\.png"

#define AMOUNT_POLYGON_PARTICLE	(128)	//�|���S����

#define RADIUS_PARTICLE	(50.0f)			//���a�p
#define REMAIN_TIME_PARTICLE	(60)	//�c������

#define MOVE_SPD_POS_PARTICLE	(5.0f)		//�ړ����x
#define CHANGE_SPD_RADIUS_PARTICLE	(1.0f)	//�k�����x

//�p�[�e�B�N���\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu�����i�[
	D3DXVECTOR3 move;	//�ړ������i�[
	D3DXCOLOR col;		//�F�����i�[
	float fRadius;		//���a���i�[
	int nRemain;		//�c�����Ԃ��i�[
	bool bUse;			//���ꂪ�g���Ă��邩����
}PARTICLE;

//�v���g�^�C�v�錾

/*����*/
void Init_Particle(void);

/*�I��*/
void Uninit_Particle(void);

/*�X�V*/
void Update_Particle(void);

/*�`��*/
void Draw_Particle(void);

/*�p�[�e�B�N���Ƀf�[�^��t�^*/
void Setinfo_Particle(D3DXVECTOR3 pos, D3DXCOLOR col);

#endif