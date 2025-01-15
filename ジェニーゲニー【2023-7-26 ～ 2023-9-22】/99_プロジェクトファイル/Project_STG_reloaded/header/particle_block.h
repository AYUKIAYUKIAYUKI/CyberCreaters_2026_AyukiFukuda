//************************************************
//
//�u���b�N�p�[�e�B�N�������A�w�b�_�t�@�C��[particle_Block.h]
//Author�F���c����
//
//************************************************
#ifndef _PARTICLE_BLOCK_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PARTICLE_BLOCK_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�f�o�b�O�p*/
#define	TEXTURE_PARTICLE_BLOCK	"data\\TEX\\02_game\\blocks_particle.png"

#define AMOUNT_POLYGON_PARTICLE_BLOCK	(256)	//�|���S����

#define RADIUS_PARTICLE_BLOCK	(50.0f)		//���a�p
#define REMAIN_TIME_PARTICLE_BLOCK	(60)	//�c������

#define MOVE_SPD_POS_PARTICLE_BLOCK	(2.5f)		//�ړ����x
#define CHANGE_SPD_RADIUS_PARTICLE_BLOCK	(1.0f)	//�k�����x

//�p�[�e�B�N���\����
typedef struct
{
	int nStyle;			//�ǂ̃u���b�N
	D3DXVECTOR3 pos;	//�ʒu�����i�[
	D3DXVECTOR3 move;	//�ړ������i�[
	D3DXVECTOR3 moveB;	//�u���b�N�ړ������i�[
	D3DXVECTOR3 rot;	//���������擾
	D3DXCOLOR col;		//�F�����i�[
	float fRadius;		//���a���i�[
	int nRemain;		//�c�����Ԃ��i�[
	bool bUse;			//���ꂪ�g���Ă��邩����
	float fAngle;		//�p�x�i�[
}PARTICLE_BLOCK;

//�v���g�^�C�v�錾
void Init_Particle_Block(void);
void Uninit_Particle_Block(void);
void Update_Particle_Block(void);
void Draw_Particle_Block(void);
void Setinfo_Particle_Block(D3DXVECTOR3 pos, D3DXVECTOR3 moveBlock);

#endif