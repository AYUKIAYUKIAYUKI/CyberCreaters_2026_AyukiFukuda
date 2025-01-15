//************************************************
//
//���@�����A�w�b�_�t�@�C��[player.h]
//Author�F���c����
//
//************************************************
#ifndef _PLEYER_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _PLEYER_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

//�}�N����`

/*�摜�p�X*/
#define	TEXTURE_CHARACTER_PLAYER	"data\\TEX\\02_game\\player000.png"

#define POS_X_SPAWN_PLAYER	(300.0f)	//�X�|�[���n�_X���W
#define POS_Y_SPAWN_PLAYER	(540.0f)	//�X�|�[���n�_Y���W

#define SPAN_X_PLAYER	(180.0f)	//X�S��
#define SPAN_Y_PLAYER	(150.0f)	//Y�S��
#define HALFSPAN_X_PLAYER	(90.0f)	//X����
#define HALFSPAN_Y_PLAYER	(75.0f)	//Y����

#define MOVE_SPD_POS_PLAYER	(1.0f)			//�ړ����x
#define ATTENUATION_SPD_POS_PLAYER	(0.1f)	//�ړ��ʂ̌������x
#define AMOUNT_CNT_CAST_VULKAN_PLAYER	(3)	//�o���J���L���X�g�J�E���g
#define AMOUNT_LIFE_PLAYER	(5)				//���C�t��
#define AMOUNT_CNT_STATE_PLAYER	(60)		//��ԕω��p������
#define AMOUNT_CAPACITY_PLAYER	(300)		//�L���p��
#define AMOUNT_CNT_CAPACITY_PLAYER	(3)		//�L���p�񕜃L���X�g����

#define PUSHBACK_WALL_PLAYER	(0.1f)	//�ǂ̔�����

//�G�̏�ԕ����񋓌^
typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//�ʏ���
	PLAYERSTATE_DAMAGE,		//�_���[�W���
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_MAX,		//��Ԃ̑���
}PLAYERSTATE;

//�v���C���[���̗񋓌^
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu���i�[
	D3DXVECTOR3 move;	//�ړ��ʊi�[
	PLAYERSTATE state;	//��ԋ��
	int nCntState;		//��ԕω����ԊǗ�
	int nLife;			//���C�t���i�[
	int nCapacity;		//�L���p�V�e�B���i�[
}PLAYER;

//�v���g�^�C�v�錾
void Init_Player(void);
void Uninit_Player(void);
void Update_Player(void);
void Draw_Player(void);
PLAYER* Getinfo_Player(void);
void Hit_Player(int nDamage);
void GetItem_Player(int nIncreaseCapacity);
int* Getinfo_BulletStyle(void);
void Animation_Player(void);

#endif