//************************************************
//
//�e�̏����A�w�b�_�t�@�C��[bullet.h]
//Author�F���c����
//
//************************************************
#ifndef _BULLET_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _BULLET_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`n

/*�摜�p�X�n*/
#define	TEXTURE_COMET_BULLET	"data\\TEX\\02_game\\comet_effect.png"
#define	TEXTURE_REUNION_1_BULLET	"data\\TEX\\02_game\\bullet003.png"
#define	TEXTURE_REUNION_2_BULLET	"data\\TEX\\02_game\\bullet002.png"
#define	TEXTURE_KING_BULLET	"data\\TEX\\02_game\\knife000.png"

#define AMOUNT_POLYGON_BULLET	(128)	//�|���S����
#define AMOUNT_TEXTURE_BULLET	(4)		//�Ǎ��݃e�N�X�`����

#define SPAN_X_BULLET	(150.0f)	//���ϓI�Ȓe��X�S��
#define SPAN_Y_BULLET	(150.0f)	//���ϓI�Ȓe��Y�S��
#define	HALFSPAN_X_BULLET	(75.0f)	//���ϓI�Ȓe��X����
#define HALFSPAN_Y_BULLET	(75.0f)	//���ϓI�Ȓe��Y����

#define MOVE_SPD_POS_BULLET	(15.0f)	//���ϓI�Ȓe��
#define ROTATE_SPD_BULLET	(0.1f)	//���ϓI�Ȓe��]���x
#define REMAIN_TIME_BULLET	(60)	//���ϓI�Ȓe�̎c������
#define AMOUNT_DAMAGE_BULLET	(1)	//���ϓI�Ȓe�̎��_���[�W��

#define APPARENTSPAN_RADIUS_BULLET	(0.5f)	//�����ڂƎ��ۂ̓����蔻��𐮍�����W��

#define PER_ONE_TEX_X_COMET_BULLET	(0.2f)	//�e�N�X�`��1������̉���
#define PER_ONE_TEX_Y_COMET_BULLET	(0.5f)	//�c��
#define CHEANGE_SPD_TEX_COMET_BULLET	(3)	//�R���b�g�ω��L���X�g����

#define AMOUNT_USING_POLYGON_REUNION_BULLET	(2)	//�����j�I���ɔ��˂Ɏg���e��
#define ANGLE_REUNION_BULLET	(3.0f)			//�����j�I���̎ˏo�p�x
#define MOVE_ANGLE_REUNION_BULLET	(0.025f)	//�����j�I���̊p�x�ϓ���
#define REMAIN_REUNION_TIME_BULLET	(42)		//�����j�I���̎c������

#define HALFSPAN_KNIFE_X_BULLET	(75.0f)		//�i�C�tX����
#define HALFSPAN_KNIFE_Y_BULLET	(15.0f)		//�i�C�tY����
#define AMOUNT_KNIFE_DAMAGE_BULLET	(999)	//�i�C�t�_���[�W��

#define AMOUNT_DECREASE_CAPACITY_COMET_BULLET	(25)	//�e�L���p������
#define AMOUNT_DECREASE_CAPACITY_REUNION_BULLET	(30)
#define AMOUNT_DECREASE_CAPACITY_KING_BULLET	(200)

#define AMOUNT_ADD_SCORE_BULLET	(10)	//�X�R�A���Z��

#define DUMMY_POS_BULLET	(-100.0f)	//�_�~�[

//�e�̎�ޕ����񋓌^
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//�v���C���[�̒e
	BULLETTYPE_ENEMY,		//�G�̒e
	BULLETTYPE_NONE,		//�ǂ�ɂ��t�����Ȃ��e
	BULLETTYPE_MAX,			//��ނ̐�
}BULLETTYPE;

//�e�̎�ނ̗񋓌^
typedef enum
{
	BULLETSTYLE_COMET = 0,	//�ʏ�e
	BULLETSTYLE_REUNION,	//�����e
	BULLETSTYLE_KING,		//�ꌂ�K�E
	BULLETSTYLE_MAX,		//�e�̎�ޑ���
}BULLETSTYLE;

//�e������̗񋓌^
typedef enum
{
	BULLETRUTE_UP = 0,	//�㕪��
	BULLETRUTE_DOWN,	//������
	BULLETRUTE_NONE,	//���򖳂�
	BULLETRUTE_MAX,		//����̑���
}BULLETRUTE;

//�e�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu�����i�[
	D3DXVECTOR3 move;	//�ړ��ʂ��i�[
	D3DXVECTOR3 rot;	//�������i�[
	int nRemain;		//�e�̎c���ݒ�
	bool bUse;			//�g�p�󋵔���
	BULLETTYPE type;	//�e�����ɕt��������̂�
	BULLETSTYLE style;	//�e�̎��
	BULLETRUTE rute;	//�e���̕���
	float fLength;		//�e�̑Ίp��
	float fAngle;		//�e�̊p�x
	int nDamage;		//�e�̍U����
	int nPattern;		//�A�j���p�^�[��
	float fTexX;		//�e�N�X�`�����WX
	float fTexY;		//�e�N�X�`�����WY
}BULLET;

//�v���g�^�C�v�錾
void Init_Bullet(void);
void Uninit_Bullet(void);
void Update_Bullet(void);
void Draw_Bullet(void);
void Setinfo_Bullet(D3DXVECTOR3 pos, int nSetBulletStyle);
//void CalcNearlyVector_Bullet(int nCntBullet);
void Sort_BulletStyle(int nCnt);
void Updateinfo_Comet(int nCnt);
void Updateinfo_Reunion(int nCnt);
void Updateinfo_King(int nCnt);
void HitDetection_Cloud_Enemy(int nCnt);
void HitDetection_Glide_Enemy(int nCnt);
void HitDetection_Slide_Enemy(int nCnt);
void HitDetection_Block(int nCnt);
void HitDetection_SlideBlock(int nCnt);
void HitDetection_BreakBlock(int nCnt);
void HitDetection_Spiral_Enemy(int nCnt);

#endif