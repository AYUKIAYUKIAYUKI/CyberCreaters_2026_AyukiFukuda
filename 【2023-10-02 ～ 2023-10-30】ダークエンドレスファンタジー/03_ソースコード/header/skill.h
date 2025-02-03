//************************************************
//
//�X�L�������A�w�b�_�t�@�C��[skill.h]
//Author�F���c����
//
//************************************************
#ifndef _SKILL_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _SKILL_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X�n*/
#define	TEXTURE_SKILL	"data\\TEX\\skillicon01.png"
#define	TEXTURE_SKILL_CHARGE	"data\\TEX\\black.png"

#define AMOUNT_POLYGON_SKILL	(2)	//���C�t�Q�[�W�̃|���S���ő吔
#define AMOUNT_TEX_SKILL	(2)	//���C�t�Q�[�W�̃e�N�X�`������

//���C�t�Q�[�W���̗񋓌^
typedef struct
{
	int nStyle;			//���
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//����
	D3DXCOLOR col;		//�F
	int nCntTex;		//�e�N�X�`���ύX
	float fTexSpan[2];	//�e�N�X�`����
	float fRadius[2];	//���a
	float fLength[2];	//�Ίp��
	float fAngle[2];	//�p�x
}SKILL;

//�v���g�^�C�v�錾

/*����*/
void Init_Skill(void);

/*�j��*/
void Uninit_Skill(void);

/*�X�V*/
void Update_Skill(void);

/*�`��*/
void Draw_Skill(void);

/*�Ƀf�[�^��t�^*/
void SetInfo_Skill(void);

/*�̃o�[�e�b�N�X���X�V*/
void Update_Pos_Skill(void);

/*�̃o�[�e�b�N�X�J���[���X�V*/
void Update_Col_Skill(void);

/*�̃e�N�X�`���A�j���[�V��������*/
//void Update_Tex_Skill(void);

/*�̃f�[�^���擾*/
SKILL* GetInfo_Skill(void);

#endif