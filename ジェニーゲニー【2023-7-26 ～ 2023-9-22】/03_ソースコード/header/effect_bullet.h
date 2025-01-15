//************************************************
//
//�e���G�t�F�N�g�����A�w�b�_�t�@�C��[effect_bullet.h]
//Author�F���c����
//
//************************************************
#ifndef _EFFECT_BULLET_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _EFFECT_BULLET_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_EFFECT_BULLET	"data\\TEX\\02_game\\effect0001.png"

#define AMOUNT_POLYGON_EFFECT_BULLET	(512)	//�|���S����

#define RADIUS_EFFECT_BULLET	(15.0f)		//���a�p
#define REMAIN_TIME_EFFECT_BULLET	(15)	//�c������(���Ƃ������Ȃ�)

#define CHANGE_SPD_RADIUS_EFFECT_BULLET	(1.0f)	//�k�ޑ��x(���ڂݕ��ς��)

//�e�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu�����i�[
	D3DXVECTOR3 move;	//�N�\�R�[�h��
	D3DXCOLOR col;
	float fRadius;		//���a���i�[
	int nRemain;		//�e�̎c���ݒ�
	bool bUse;			//�g�p�󋵔���
}EFFECT_BULLET;

//�v���g�^�C�v�錾
void Init_Effect_Bullet(void);
void Uninit_Effect_Bullet(void);
void Update_Effect_Bullet(void);
void Draw_Effect_Bullet(void);
void Setinfo_Effect_Bullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col);

#endif