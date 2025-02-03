//************************************************
//
//�W�����v�G�t�F�N�g�����A�w�b�_�t�@�C��[effect_jump.h]
//Author�F���c����
//
//************************************************
#ifndef _EFFECT_JUMP_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _EFFECT_JUMP_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_EFFECT_JUMP	"data\\TEX\\effect_jump00.png"

#define RADIUS_EFFECT_JUMP_X	(100.0f)	//������
#define RADIUS_EFFECT_JUMP_Y	(20.0f)		//�c����

//�v���C���[���̗񋓌^
typedef struct
{
	bool bUse;			//�g�p
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	float fRadius[2];	//���a
	float fLength;		//�Ίp��
	float fAngle;		//�p�x
}EFFECT_JUMP;

//�v���g�^�C�v�錾

/*����*/
void Init_Effect_Jump(void);

/*�j��*/
void Uninit_Effect_Jump(void);

/*�X�V*/
void Update_Effect_Jump(void);

/*�`��*/
void Draw_Effect_Jump(void);

/*�W�����v�G�t�F�N�g�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Effect_Jump(void);

/*�W�����v�G�t�F�N�g�Ƀf�[�^��t�^*/
void SetInfo_Effect_Jump(D3DXVECTOR3 pos);

/*�W�����v�G�t�F�N�g�̃f�[�^���擾*/
EFFECT_JUMP* Getinfo_Effect_Jump(void);

#endif