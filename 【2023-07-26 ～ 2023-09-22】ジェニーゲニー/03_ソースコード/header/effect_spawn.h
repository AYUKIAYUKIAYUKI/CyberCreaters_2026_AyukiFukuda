//************************************************
//
//�X�|�[���G�t�F�N�g�����A�w�b�_�t�@�C��[effect_spawn.h]
//Author�F���c����
//
//************************************************
#ifndef _EFFECT_SPAWN_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _EFFECT_SPAWN_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_GENERATOR_EFFECT_SPAWN	"data\\TEX\\02_game\\generator000.png"

#define AMOUNT_POLYGON_EFFECT_SPAWN	(64)	//�|���S����

#define SPAN_X_EFFECT_SPAWN	(100.0f)	//X�S��
#define SPAN_Y_EFFECT_SPAWN	(100.0f)	//Y�S��
#define	HALFSPAN_X_EFFECT_SPAWN	(50.0f)	//X����
#define HALFSPAN_Y_EFFECT_SPAWN	(50.0f)	//Y����

#define ROTATE_SPD_EFFECT_SPAWN	(0.05f)	//�G�t�F�N�g��]���x

#define CHANGE_SPD_COLORA_EFFECT_SPAWN	(10)	//�G�t�F�N�g��colA�ύX���x

//�X�|�[���G�t�F�N�g�\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu�����i�[
	D3DXVECTOR3 move;	//�ړ��ʏ����i�[
	D3DXVECTOR3 rot;	//���������i�[
	bool bUse;			//���ꂪ�g���Ă��邩����
	float fLength;		//�Ίp�����i�[
	float fAngle;		//�Ίp���̊p�x���i�[
	int nColorA;		//�����x�ύX�p
}SPAWN_EFFECT;

//�v���g�^�C�v�錾
void Init_Effect_Spawn(void);
void Uninit_Effect_Spawn(void);
void Update_Effect_Spawn(void);
void Draw_Effect_Spawn(void);
void SetPos_Vtx_Effect_Spawn(int nCntEnemy, D3DXVECTOR3 pos, D3DXVECTOR3 move);

#endif