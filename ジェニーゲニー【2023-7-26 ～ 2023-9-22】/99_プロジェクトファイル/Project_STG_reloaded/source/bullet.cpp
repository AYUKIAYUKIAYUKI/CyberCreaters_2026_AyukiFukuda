//************************************************
//
//�e�̏���[bullet.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "sound.h"
#include "block.h"
#include "breakblock.h"
#include "bullet.h"
#include "effect_bullet.h"
#include "effect_comet.h"
#include "enemy.h"
#include "enemy_glide.h"
#include "enemy_slide.h"
#include "enemy_spiral.h"
#include "particle.h"
#include "player.h"
#include "score.h"
#include "slideblock.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Bullet[AMOUNT_TEXTURE_BULLET] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Bullet = NULL;	//���_�o�b�t�@�̃|�C���^
BULLET g_aBullet[AMOUNT_POLYGON_BULLET];	//�e�̊e���
int g_nChangeRute_Bullet = 0;	//��������p
D3DXVECTOR3 g_NowVector_Bullet[AMOUNT_POLYGON_ENEMY] = {};	//�e����G�ւ̃x�N�g���i�[
float g_fRadius_Bullet = 0.0f;	//�e�̔��a���i�[
float g_fRadius_EnemyCore_Bullet = 0.0f;	//�G�̖{�̂̔��a���i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Bullet(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Bullet;

	//�G���ւ̃|�C���^
	ENEMY* pEnemy;

	//�G���̎擾
	pEnemy = Getinfo_Enemy();	//�G���n�̐擪�A�h���X����������

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_COMET_BULLET,
		&g_pTexture_Bullet[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_REUNION_1_BULLET,
		&g_pTexture_Bullet[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_REUNION_2_BULLET,
		&g_pTexture_Bullet[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_KING_BULLET,
		&g_pTexture_Bullet[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BULLET,
	D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Bullet,
		NULL);

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bullet->Lock(0, 0, (void**)&pVtx_Bullet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BULLET; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Bullet[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bullet[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bullet[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bullet[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Bullet[0].rhw = 1.0f;
		pVtx_Bullet[1].rhw = 1.0f;
		pVtx_Bullet[2].rhw = 1.0f;
		pVtx_Bullet[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Bullet += AMOUNT_VTX;	//���_���̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bullet->Unlock();

	//�e���̏�����
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BULLET; nCnt++)
	{
		g_aBullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu����������
		g_aBullet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ�������
		g_aBullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//������������
		g_aBullet[nCnt].nRemain = REMAIN_TIME_BULLET;			//�e�̎c�����Ԃ����߂�
		g_aBullet[nCnt].bUse = false;							//�e�̎g�p����𖳂���
		g_aBullet[nCnt].type = BULLETTYPE_NONE;					//�e�̕��ނ𖳂���
		g_aBullet[nCnt].style = BULLETSTYLE_COMET;				//�e�̎�ނ�ʏ�e�ɕύX
		g_aBullet[nCnt].rute = BULLETRUTE_NONE;					//�e���̕����������
		g_aBullet[nCnt].fLength = 0.0f;							//�e�̑Ίp�����i�[
		g_aBullet[nCnt].fAngle = 0.0f;							//�e�̊p�x���i�[
		g_aBullet[nCnt].nDamage = 0;							//�e�̍U���͂�������
		g_aBullet[nCnt].nPattern = 0;							//�p�^�[���J�E���g
		g_aBullet[nCnt].fTexX = 0.0f;							//�e�N�X�`�����W��������
		g_aBullet[nCnt].fTexY = 0.0f;							//�e�N�X�`�����W��������
	}

	//�������򏉊���
	g_nChangeRute_Bullet = 0;

	//���ϓI�Ȓe�̔��a�̒������Z�o����
	g_fRadius_Bullet = sqrtf(HALFSPAN_X_BULLET * HALFSPAN_X_BULLET +
		HALFSPAN_Y_BULLET * HALFSPAN_Y_BULLET) * APPARENTSPAN_RADIUS_BULLET;

	//�G(����)�̔��a�̒������Z�o����
	g_fRadius_EnemyCore_Bullet = sqrtf(pEnemy[0].fHalfSpanX * pEnemy[0].fHalfSpanX +
		pEnemy[0].fHalfSpanY * pEnemy[0].fHalfSpanY) * APPARENTSPAN_RADIUS_BULLET;
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Bullet(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BULLET; nCnt++)
	{
		if (g_pTexture_Bullet[nCnt] != NULL)
		{
			g_pTexture_Bullet[nCnt]->Release();
			g_pTexture_Bullet[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Bullet != NULL)
	{
		g_pVtxBuff_Bullet->Release();
		g_pVtxBuff_Bullet = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Bullet(void)
{	
	//�e���̂��߂̃��[�v
	for (int nCnt = 0; nCnt< AMOUNT_POLYGON_BULLET; nCnt++)
	{
		//�v���C���[�̒e�̏���
		if (g_aBullet[nCnt].bUse && g_aBullet[nCnt].type == BULLETTYPE_PLAYER)
		{
			//�e�̎�ނɂ���ď����ω�
			Sort_BulletStyle(nCnt);

			//�e����ʂ̊O�֏o���Ƃ�
			if (g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET <= 0.0f ||
				g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET >= SCREEN_WIDTH)
			{
				//����̒e�̎g�p����𖳂���
				g_aBullet[nCnt].bUse = false;
			}

			//�����蔻��V���[�Y
			HitDetection_Cloud_Enemy(nCnt);
			HitDetection_Glide_Enemy(nCnt);
			HitDetection_Slide_Enemy(nCnt);
			HitDetection_Spiral_Enemy(nCnt);
			HitDetection_Block(nCnt);
			HitDetection_SlideBlock(nCnt);
			HitDetection_BreakBlock(nCnt);
		}
		//�G�̒e�̏���
		else if (g_aBullet[nCnt].bUse == true && g_aBullet[nCnt].type == BULLETTYPE_ENEMY)
		{

		}
		/*�e�̎g�p���������ꂽ�Ƃ��c��������W���������ցc(�o�O�h�~)*/
		else
		{
			g_aBullet[nCnt].pos.x = DUMMY_POS_BULLET;
		}
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Bullet(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Bullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BULLET; nCnt++)
	{
		//�e���g�p����Ă���ԍ������m
		if (g_aBullet[nCnt].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			switch (g_aBullet[nCnt].style)
			{
			case BULLETSTYLE_COMET:

				pDevice->SetTexture(0, g_pTexture_Bullet[0]);

				break;

			case BULLETSTYLE_REUNION:

				if (g_aBullet[nCnt].rute == BULLETRUTE_UP)
				{
					pDevice->SetTexture(0, g_pTexture_Bullet[1]);
				}
				else if (g_aBullet[nCnt].rute == BULLETRUTE_DOWN)
				{
					pDevice->SetTexture(0, g_pTexture_Bullet[2]);
				}

				break;

			case BULLETSTYLE_KING:

				pDevice->SetTexture(0, g_pTexture_Bullet[3]);

				break;
			}
		
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}
}

//************************************************
//�v���C���[�̒e�۔��ˏ����֐�
//************************************************
void Setinfo_Bullet(D3DXVECTOR3 pos, int nSetBulletStyle)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Bullet;

	//�v���C���[���ւ̃|�C���^
	PLAYER* pPlayer;

	//�v���C���[���̎擾
	pPlayer = Getinfo_Player();	//�v���C���[���n�̐擪�A�h���X����������
	
	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bullet->Lock(0, 0, (void**)&pVtx_Bullet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BULLET; nCnt++)
	{
		//�g�p����Ă��Ȃ��e�̔ԍ������m������
		if (g_aBullet[nCnt].bUse == false)
		{
			//�X�^�C���ԍ��ɉ����e�̎�ޑI��
			switch (nSetBulletStyle)
			{
			case 0:

				g_aBullet[nCnt].style = BULLETSTYLE_COMET;

				break;

			case 1:

				g_aBullet[nCnt].style = BULLETSTYLE_REUNION;

				break;

			case 2:

				g_aBullet[nCnt].style = BULLETSTYLE_KING;

				break;
			}

			//�e�̎�ނɂ���ď�񂪕ω�
			switch (g_aBullet[nCnt].style)
			{
			case BULLETSTYLE_COMET:

				if (pPlayer->nCapacity >= AMOUNT_DECREASE_CAPACITY_COMET_BULLET)
				{
					//�v���C���[�̒��S�ʒu��e�̒��S�ʒu�ɐݒ�
					g_aBullet[nCnt].pos = pos;

					//���傢�v���C���[�̉E�ɏo��
					g_aBullet[nCnt].pos.x += HALFSPAN_X_PLAYER;

					//���S�����Ƃɒe�̒��_���W��W�J
					pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET;
					pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET;
					pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET;
					pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET;
					pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET;
					pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET;
					pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET;
					pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET;

					//�ړ��ʂ�ݒ�
					g_aBullet[nCnt].move = D3DXVECTOR3(MOVE_SPD_POS_BULLET, 0.0f, 0.0f);

					//��]�����������_����
					int i = rand() % 2;
					i == 0 ? g_aBullet[nCnt].move.z = ROTATE_SPD_BULLET : g_aBullet[nCnt].move.z = -ROTATE_SPD_BULLET;

					g_aBullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//������������
					g_aBullet[nCnt].nRemain = REMAIN_TIME_BULLET;	//�e�̎c�����Ԃ����߂�
					g_aBullet[nCnt].bUse = true;					//�e�̎g�p������o��
					g_aBullet[nCnt].type = BULLETTYPE_PLAYER;		//���̎����˂����e���v���C���[�̂��̂Ƃ���
					g_aBullet[nCnt].rute = BULLETRUTE_NONE;			//�e���̕���𖳂��ɃZ�b�g
					
					//�Ίp���̒�����ݒ�
					g_aBullet[nCnt].fLength = sqrtf(SPAN_X_BULLET * SPAN_X_BULLET +
						SPAN_Y_BULLET * SPAN_Y_BULLET) * 0.5f;

					//�Ίp���̊p�x��ݒ�
					g_aBullet[nCnt].fAngle = atan2f(SPAN_Y_BULLET, SPAN_Y_BULLET);

					g_aBullet[nCnt].nDamage = AMOUNT_DAMAGE_BULLET;	//�U���͂��Z�b�g
					g_aBullet[nCnt].nPattern = 0;					//�p�^�[���J�E���g
					g_aBullet[nCnt].fTexX = 0.0f;					//�e�N�X�`�����W��������
					g_aBullet[nCnt].fTexY = 0.0f;					//�e�N�X�`�����W��������

					//�F��ʏ�F��
					pVtx_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					//�e�N�X�`������肢���ƒ���
					pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx_Bullet[1].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET, 0.0f);
					pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f, PER_ONE_TEX_Y_COMET_BULLET);
					pVtx_Bullet[3].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET, PER_ONE_TEX_Y_COMET_BULLET);

					pPlayer->nCapacity -= AMOUNT_DECREASE_CAPACITY_COMET_BULLET;	//�L���p������

					//���ʉ���炷
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}

				break;

			case BULLETSTYLE_REUNION:

				if (pPlayer->nCapacity >= AMOUNT_DECREASE_CAPACITY_REUNION_BULLET)
				{
					g_nChangeRute_Bullet++;

					g_aBullet[nCnt].pos = pos;	//�v���C���[�̒��S�ʒu��e�̒��S�ʒu�ɐݒ�

					//���S�����Ƃɒe�̒��_���W��W�J
					pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET * 0.5f;
					pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET * 0.5f;
					pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET * 0.5f;
					pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET * 0.5f;
					pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET * 0.5f;
					pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET * 0.5f;
					pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET * 0.5f;
					pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET * 0.5f;

					//�ړ��ʂ�ݒ�
					g_aBullet[nCnt].move = D3DXVECTOR3(MOVE_SPD_POS_BULLET, MOVE_SPD_POS_BULLET, 0.0f);

					g_aBullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//������������
					g_aBullet[nCnt].nRemain = REMAIN_REUNION_TIME_BULLET;	//�����j�I���p�̎c�����Ԃ����߂�
					g_aBullet[nCnt].bUse = true;				//�e�̎g�p������o��
					g_aBullet[nCnt].type = BULLETTYPE_PLAYER;	//���̎����˂����e���v���C���[�̂��̂Ƃ���

					switch (g_nChangeRute_Bullet)
					{
					case 1:

						g_aBullet[nCnt].rute = BULLETRUTE_UP;	//�e���̕������ɃZ�b�g

						//�F��ʏ�F��
						pVtx_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//�e�N�X�`����ʏ��
						pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
						pVtx_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
						pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
						pVtx_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

						break;

					case 2:

						g_aBullet[nCnt].rute = BULLETRUTE_DOWN;	//�e���̕�������ɃZ�b�g

						//�F��ʏ�F��
						pVtx_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//�e�N�X�`����ʏ��
						pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
						pVtx_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
						pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
						pVtx_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

						break;
					}

					//�Ίp���̒�����ݒ�
					g_aBullet[nCnt].fLength = sqrtf(SPAN_X_BULLET * SPAN_X_BULLET +
						SPAN_Y_BULLET * SPAN_Y_BULLET) * 0.5f;

					//�Ίp���̊p�x��ݒ�
					g_aBullet[nCnt].fAngle = atan2f(SPAN_Y_BULLET, SPAN_Y_BULLET);

					g_aBullet[nCnt].nDamage = AMOUNT_DAMAGE_BULLET;			//�U���͂��Z�b�g
					g_aBullet[nCnt].nPattern = 0;							//�p�^�[���J�E���g
					g_aBullet[nCnt].fTexX = 0.0f;							//�e�N�X�`�����W��������
					g_aBullet[nCnt].fTexY = 0.0f;							//�e�N�X�`�����W��������

					if (g_nChangeRute_Bullet < AMOUNT_USING_POLYGON_REUNION_BULLET)
					{
						//���̎�ނ̒e���o���Ƃ������ꔭ�����ŏo��
						Setinfo_Bullet(pos, nSetBulletStyle);

						//�e������J�E���g�̑��������Z�b�g
						g_nChangeRute_Bullet = 0;
					}

					pPlayer->nCapacity -= AMOUNT_DECREASE_CAPACITY_REUNION_BULLET;	//�L���p������

					//���ʉ���炷
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}

				break;

			case BULLETSTYLE_KING:

				if (pPlayer->nCapacity >= AMOUNT_DECREASE_CAPACITY_KING_BULLET)
				{
					g_aBullet[nCnt].pos = pos;	//�v���C���[�̒��S�ʒu��e�̒��S�ʒu�ɐݒ�

					//���S�����Ƃɒe�̒��_���W��W�J
					pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_KNIFE_X_BULLET;
					pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_KNIFE_Y_BULLET;
					pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_KNIFE_X_BULLET;
					pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_KNIFE_Y_BULLET;
					pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_KNIFE_X_BULLET;
					pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_KNIFE_Y_BULLET;
					pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_KNIFE_X_BULLET;
					pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_KNIFE_Y_BULLET;

					//�ړ��ʂ�ݒ�
					g_aBullet[nCnt].move = D3DXVECTOR3(MOVE_SPD_POS_BULLET, MOVE_SPD_POS_BULLET, 0.0f);

					g_aBullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//������������
					g_aBullet[nCnt].nRemain = REMAIN_TIME_BULLET;	//�e�̎c�����Ԃ����߂�
					g_aBullet[nCnt].bUse = true;					//�e�̎g�p������o��
					g_aBullet[nCnt].type = BULLETTYPE_PLAYER;		//���̎����˂����e���v���C���[�̂��̂Ƃ���
					g_aBullet[nCnt].rute = BULLETRUTE_NONE;			//�e���̕���𖳂��ɃZ�b�g
			
					//�Ίp���̒�����ݒ�
					g_aBullet[nCnt].fLength = 0.0f;

					//�Ίp���̊p�x��ݒ�
					g_aBullet[nCnt].fAngle = 0.0f;

					g_aBullet[nCnt].nDamage = AMOUNT_KNIFE_DAMAGE_BULLET;	//�i�C�t�p�U���͂��Z�b�g
					g_aBullet[nCnt].nPattern = 0;					//�p�^�[���J�E���g
					g_aBullet[nCnt].fTexX = 0.0f;					//�e�N�X�`�����W��������
					g_aBullet[nCnt].fTexY = 0.0f;					//�e�N�X�`�����W��������

					//�F��ʏ�F��
					pVtx_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					//�e�N�X�`����ʏ��
					pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
					pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

					pPlayer->nCapacity -= AMOUNT_DECREASE_CAPACITY_KING_BULLET;	//�L���p������

					//���ʉ���炷
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}

				break;
			}

			break;
		}

		pVtx_Bullet += AMOUNT_VTX;	//���_���̃|�C���^��4���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bullet->Unlock();
}

//************************************************
//�e�ƓG�ōł��Z�������̂��̂��o���֐�
//************************************************
//void CalcNearlyVector_Bullet(int nCnt)
//{
//	//�G���ւ̃|�C���^
//	ENEMY* pEnemy;
//
//	//�G���̎擾
//	pEnemy = Getinfo_Enemy();	//�G���n�̐擪�A�h���X����������
//
//	float fMinDistance = FLT_MAX;
//	float fDistance;
//	int nEnemyNearest = 0;
//
//	//�G�̐����A��������
//	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_POLYGON_ENEMY; nCntEnemy++)
//	{
//		//�g�p����Ă���S�Ă̓G�ւ̋������擾
//		if (pEnemy[nCntEnemy].bUse == true)
//		{
//			g_NowVector_Bullet[nCntEnemy] = pEnemy[nCntEnemy].pos - g_aBullet[nCnt].pos;
//
//			fDistance = g_NowVector_Bullet[nCntEnemy].x * g_NowVector_Bullet[nCntEnemy].x + g_NowVector_Bullet[nCntEnemy].y * g_NowVector_Bullet[nCntEnemy].y;
//
//			if (fMinDistance > fDistance)
//			{
//				fMinDistance = fDistance;
//				nEnemyNearest = nCntEnemy;
//			}
//		}
//	}
//
//	g_aBullet[nCnt].nTarget = nEnemyNearest;
//}

//************************************************
//�e�������ʊ֐�
//************************************************
void Sort_BulletStyle(int nCnt)
{
	switch (g_aBullet[nCnt].style)
	{
	case BULLETSTYLE_COMET:

		Updateinfo_Comet(nCnt);

		break;

	case BULLETSTYLE_REUNION:

		Updateinfo_Reunion(nCnt);

		break;

	case BULLETSTYLE_KING:

		Updateinfo_King(nCnt);

		break;
	}
}

//************************************************
//�ʏ�e�����֐�
//************************************************
void Updateinfo_Comet(int nCnt)
{
	//�|�C���^
	VERTEX_2D* pVtx_Bullet;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bullet->Lock(0, 0, (void**)&pVtx_Bullet, 0);

	//���̏��Ԃ̃��c�ɃX�L�b�v
	pVtx_Bullet += AMOUNT_VTX * nCnt;

	//�e�̎c�����Ԃ����炷
	g_aBullet[nCnt].nRemain--;

	//�c�����Ԃ�0
	if (g_aBullet[nCnt].nRemain <= 0)
	{
		SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, 0.0f);

		g_aBullet[nCnt].pos = D3DXVECTOR3(-1000.0f, -1000.0f, 0.0f);

		//����̒e�̎g�p����𖳂���
		g_aBullet[nCnt].bUse = false;
	}

	//�ړ�
	g_aBullet[nCnt].pos.x += g_aBullet[nCnt].move.x;

	//�e���G�t�F�N�g
	Setinfo_Effect_Bullet(g_aBullet[nCnt].pos, g_aBullet[nCnt].move, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	//��]
	g_aBullet[nCnt].rot.z += g_aBullet[nCnt].move.z;

	//�Ō�ɒe�̈ړ��ʂɍ��킹�Ē��_���X�V
	pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x + sinf(g_aBullet[nCnt].rot.z - (D3DX_PI - g_aBullet[nCnt].fAngle)) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y + cosf(g_aBullet[nCnt].rot.z - (D3DX_PI - g_aBullet[nCnt].fAngle)) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + sinf(g_aBullet[nCnt].rot.z + (D3DX_PI - g_aBullet[nCnt].fAngle)) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y + cosf(g_aBullet[nCnt].rot.z + (D3DX_PI - g_aBullet[nCnt].fAngle)) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x + sinf(g_aBullet[nCnt].rot.z - g_aBullet[nCnt].fAngle) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + cosf(g_aBullet[nCnt].rot.z - g_aBullet[nCnt].fAngle) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + sinf(g_aBullet[nCnt].rot.z + g_aBullet[nCnt].fAngle) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + cosf(g_aBullet[nCnt].rot.z + g_aBullet[nCnt].fAngle) * g_aBullet[nCnt].fLength;

	//�e�N�X�`������肢���ƒ���
	pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f + g_aBullet[nCnt].fTexX, 0.0f + g_aBullet[nCnt].fTexY);
	pVtx_Bullet[1].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET + g_aBullet[nCnt].fTexX, 0.0f + g_aBullet[nCnt].fTexY);
	pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f + g_aBullet[nCnt].fTexX, PER_ONE_TEX_Y_COMET_BULLET + g_aBullet[nCnt].fTexY);
	pVtx_Bullet[3].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET + g_aBullet[nCnt].fTexX, PER_ONE_TEX_Y_COMET_BULLET + g_aBullet[nCnt].fTexY);

	//�e�N�X�`���ω��x��
	g_aBullet[nCnt].nPattern++;

	//�e�N�X�`�����ω�
	if (g_aBullet[nCnt].nPattern > CHEANGE_SPD_TEX_COMET_BULLET)
	{
		g_aBullet[nCnt].fTexX += PER_ONE_TEX_X_COMET_BULLET;

		if (g_aBullet[nCnt].fTexX >= 1.0f)
		{
			g_aBullet[nCnt].fTexX = 0.0f;

			g_aBullet[nCnt].fTexY += PER_ONE_TEX_Y_COMET_BULLET;

			if (g_aBullet[nCnt].fTexY >= 1.0f)
			{
				g_aBullet[nCnt].fTexY = 0.0f;
			}
		}

		g_aBullet[nCnt].nPattern = 0;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bullet->Unlock();
}

//************************************************
//�����e�����֐�
//************************************************
void Updateinfo_Reunion(int nCnt)
{
	//�|�C���^
	VERTEX_2D* pVtx_Bullet;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bullet->Lock(0, 0, (void**)&pVtx_Bullet, 0);

	//���̏��Ԃ̃��c�ɃX�L�b�v
	pVtx_Bullet += AMOUNT_VTX * nCnt;

	//�ړ��ʕω�
	g_aBullet[nCnt].move.x = sinf(D3DX_PI * g_aBullet[nCnt].fAngle);
	g_aBullet[nCnt].move.y = cosf(D3DX_PI * g_aBullet[nCnt].fAngle);

	switch (g_aBullet[nCnt].rute)
	{
	case BULLETRUTE_UP:

		//�e�̊p�x���ϓ�
		g_aBullet[nCnt].fAngle += MOVE_ANGLE_REUNION_BULLET;

		g_aBullet[nCnt].pos.x -= g_aBullet[nCnt].move.x * MOVE_SPD_POS_BULLET;
		g_aBullet[nCnt].pos.y += g_aBullet[nCnt].move.y * MOVE_SPD_POS_BULLET;

		break;

	case BULLETRUTE_DOWN:

		//�e�̊p�x���ϓ�
		g_aBullet[nCnt].fAngle += MOVE_ANGLE_REUNION_BULLET;

		g_aBullet[nCnt].pos.x -= g_aBullet[nCnt].move.x * MOVE_SPD_POS_BULLET;
		g_aBullet[nCnt].pos.y -= g_aBullet[nCnt].move.y * MOVE_SPD_POS_BULLET;

		break;
	}

	//�e�̎c�����Ԃ����炷
	g_aBullet[nCnt].nRemain--;

	//�c�����Ԃ�0
	if (g_aBullet[nCnt].nRemain <= 0)
	{
		//����̒e�̎g�p����𖳂���
		g_aBullet[nCnt].bUse = false;
	}

	//�Ō�ɒe�̈ړ��ʂɍ��킹�Ē��_���X�V
	pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET * 0.5f;
	pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET * 0.5f;
	pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET * 0.5f;
	pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET * 0.5f;
	pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET * 0.5f;
	pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET * 0.5f;
	pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET * 0.5f;
	pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET * 0.5f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bullet->Unlock();
}

//************************************************
//�ꌂ�K�E�e�����֐�
//************************************************
void Updateinfo_King(int nCnt)
{
	//�|�C���^
	VERTEX_2D* pVtx_Bullet;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Bullet->Lock(0, 0, (void**)&pVtx_Bullet, 0);

	//���̏��Ԃ̃��c�ɃX�L�b�v
	pVtx_Bullet += AMOUNT_VTX * nCnt;

	//���S�ʒu�ʒu���ړ���
	g_aBullet[nCnt].pos.x += g_aBullet[nCnt].move.x;

	//�e�̎c�����Ԃ����炷
	g_aBullet[nCnt].nRemain--;

	//�c�����Ԃ�0
	if (g_aBullet[nCnt].nRemain <= 0)
	{
		//����̒e�̎g�p����𖳂���
		g_aBullet[nCnt].bUse = false;
	}

	//�Ō�ɒe�̈ړ��ʂɍ��킹�Ē��_���X�V
	pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_KNIFE_X_BULLET;
	pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_KNIFE_Y_BULLET;
	pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_KNIFE_X_BULLET;
	pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_KNIFE_Y_BULLET;
	pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_KNIFE_X_BULLET;
	pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_KNIFE_Y_BULLET;
	pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_KNIFE_X_BULLET;
	pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_KNIFE_Y_BULLET;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Bullet->Unlock();
}

//************************************************
//�G(����)�ւ̓����蔻�菈���֐�
//************************************************
void HitDetection_Cloud_Enemy(int nCnt)
{
	ENEMY* pEnemy;

	pEnemy = Getinfo_Enemy();

	//�G(����)�̐����A�����蔻�菈������
	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_POLYGON_ENEMY; nCntEnemy++)
	{
		//�G���g�p����Ă��鎞
		if (pEnemy[nCntEnemy].bUse == true && pEnemy[nCntEnemy].nCntSpawn <= 0)
		{
			//�e���~�`�̎�
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//�e�̈ʒu����G�̈ʒu�ւ̃x�N�g�����i�[
				D3DXVECTOR3 CollisionVector = pEnemy[nCntEnemy].pos - g_aBullet[nCnt].pos;

				//�e�̈ʒu�ƓG�̈ʒu�̋���
				float fDistance = sqrtf(CollisionVector.x * CollisionVector.x + CollisionVector.y * CollisionVector.y);

				//�G�̖{�̂̎������蔻����ɒe����������
				if (fDistance < g_fRadius_Bullet + g_fRadius_EnemyCore_Bullet)
				{
					//�e�̎g�p������
					g_aBullet[nCnt].bUse = false;

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//���ŃG�t�F�N�g
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pEnemy[nCntEnemy].move.x);
					}

					//�_���[�W�ʂ𑗂�
					if (pEnemy[nCntEnemy].state != ENEMYSTATE_DAMAGE)
					{
						Hit_Cloud_Enemy(nCntEnemy, g_aBullet[nCnt].nDamage);
					}
				}
			}
			//�i�C�t�̎�
			else
			{
				if (g_aBullet[nCnt].pos.x <= pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].fHalfSpanX + HALFSPAN_KNIFE_X_BULLET &&
					g_aBullet[nCnt].pos.x >= pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].fHalfSpanX - HALFSPAN_KNIFE_X_BULLET &&
					g_aBullet[nCnt].pos.y >= pEnemy[nCntEnemy].pos.y - pEnemy[nCntEnemy].fHalfSpanY - HALFSPAN_KNIFE_Y_BULLET &&
					g_aBullet[nCnt].pos.y <= pEnemy[nCntEnemy].pos.y + pEnemy[nCntEnemy].fHalfSpanY + HALFSPAN_KNIFE_Y_BULLET)
				{
					//�e�̎g�p������
					g_aBullet[nCnt].bUse = false;

					//�_���[�W�ʂ𑗂�
					Hit_Cloud_Enemy(nCntEnemy, g_aBullet[nCnt].nDamage);

					//10�_�����܂���
					Add_Score(AMOUNT_ADD_SCORE_BULLET);
				}
			}
		}
	}
}

//************************************************
//�G(����)�ւ̓����蔻�菈���֐�
//************************************************
void HitDetection_Glide_Enemy(int nCnt)
{
	ENEMY_GLIDE* pEnemy_Glide;

	pEnemy_Glide = Getinfo_Enemy_Glide();

	//�G(����)�̐����A�����蔻�菈������
	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_POLYGON_ENEMY_GLIDE; nCntEnemy++)
	{
		//�G���g�p����Ă��鎞
		if (pEnemy_Glide[nCntEnemy].bUse == true && pEnemy_Glide[nCntEnemy].nCntSpawn <= 0)
		{
			//�e�ƓG���~�`�̎�
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//�e�̈ʒu����G�̈ʒu�ւ̃x�N�g�����i�[
				D3DXVECTOR3 CollisionVector = pEnemy_Glide[nCntEnemy].pos - g_aBullet[nCnt].pos;

				//�e�̈ʒu�ƓG�̈ʒu�̋���
				float fDistance = sqrtf(CollisionVector.x * CollisionVector.x + CollisionVector.y * CollisionVector.y);

				//�G�̖{�̂̎������蔻����ɒe����������
				if (fDistance < g_fRadius_Bullet + g_fRadius_EnemyCore_Bullet)
				{
					//�e�̎g�p������
					g_aBullet[nCnt].bUse = false;

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//���ŃG�t�F�N�g
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pEnemy_Glide[nCntEnemy].move.x);
					}

					//���̎��̓G�̔ԍ��ƃ_���[�W�ʂ𑗂�(�G�̎�ނɉ����ĕύX�\��)
					if (pEnemy_Glide[nCntEnemy].state != ENEMYSTATE_DAMAGE)
					{
						Hit_Glide_Enemy(nCntEnemy, g_aBullet[nCnt].nDamage);
					}
				}
			}
		}
	}
}

//************************************************
//�G(�ړ�)�ւ̓����蔻�菈���֐�
//************************************************
void HitDetection_Slide_Enemy(int nCnt)
{
	ENEMY_SLIDE* pEnemy_Slide;

	pEnemy_Slide = Getinfo_Enemy_Slide();

	//�G(�ړ�)�̐����A�����蔻�菈������
	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_POLYGON_ENEMY_SLIDE; nCntEnemy++)
	{
		//�G���g�p����Ă��鎞
		if (pEnemy_Slide[nCntEnemy].bUse == true && pEnemy_Slide[nCntEnemy].nCntSpawn <= 0)
		{
			//�e�ƓG���~�`�̎�
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//�G�̖{�̂̎������蔻����ɒe����������
				if (g_aBullet[nCnt].pos.x <= pEnemy_Slide[nCntEnemy].pos.x + pEnemy_Slide[nCntEnemy].fHalfSpanX + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.x >= pEnemy_Slide[nCntEnemy].pos.x - pEnemy_Slide[nCntEnemy].fHalfSpanX - g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y <= pEnemy_Slide[nCntEnemy].pos.y + pEnemy_Slide[nCntEnemy].fHalfSpanY + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y >= pEnemy_Slide[nCntEnemy].pos.y - pEnemy_Slide[nCntEnemy].fHalfSpanY - g_fRadius_Bullet)
				{
					//�e�̎g�p������
					g_aBullet[nCnt].bUse = false;

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//���ŃG�t�F�N�g
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pEnemy_Slide[nCntEnemy].move.x);
					}

					//�_���[�W�ʂ𑗂�
					if (pEnemy_Slide[nCntEnemy].state != ENEMYSTATE_DAMAGE)
					{
						Hit_Slide_Enemy(nCntEnemy, g_aBullet[nCnt].nDamage);
					}
				}
			}
		}
	}
}

//************************************************
//�G(�ђ�)�ւ̓����蔻�菈���֐�
//************************************************
void HitDetection_Spiral_Enemy(int nCnt)
{
	ENEMY_SPIRAL* pEnemy_Spiral;

	pEnemy_Spiral = Getinfo_Enemy_Spiral();

	//�G(�ړ�)�̐����A�����蔻�菈������
	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_POLYGON_ENEMY_SPIRAL; nCntEnemy++)
	{
		//�G���g�p����Ă��鎞
		if (pEnemy_Spiral[nCntEnemy].bUse == true && pEnemy_Spiral[nCntEnemy].nCntSpawn <= 0)
		{
			//�e�ƓG���~�`�̎�
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//�G�̖{�̂̎������蔻����ɒe����������
				if (g_aBullet[nCnt].pos.x <= pEnemy_Spiral[nCntEnemy].pos.x + pEnemy_Spiral[nCntEnemy].fHalfSpanX + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.x >= pEnemy_Spiral[nCntEnemy].pos.x - pEnemy_Spiral[nCntEnemy].fHalfSpanX - g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y <= pEnemy_Spiral[nCntEnemy].pos.y + pEnemy_Spiral[nCntEnemy].fHalfSpanY + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y >= pEnemy_Spiral[nCntEnemy].pos.y - pEnemy_Spiral[nCntEnemy].fHalfSpanY - g_fRadius_Bullet)
				{
					//�e�̎g�p������
					g_aBullet[nCnt].bUse = false;

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//���ŃG�t�F�N�g
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pEnemy_Spiral[nCntEnemy].move.x);
					}

					//�_���[�W�ʂ𑗂�
					if (pEnemy_Spiral[nCntEnemy].state != ENEMYSTATE_DAMAGE)
					{
						Hit_Spiral_Enemy(nCntEnemy, g_aBullet[nCnt].nDamage);
					}
				}
			}
		}
	}
}

//************************************************
//�u���b�N�ւ̓����蔻�菈���֐�
//************************************************
void HitDetection_Block(int nCnt)
{
	BLOCK* pBlock;

	pBlock = Getinfo_Block();

	//�u���b�N�̐��������蔻�����
	for (int nCntBlock = 0; nCntBlock < AMOUNT_POLYGON_BLOCK; nCntBlock++)
	{
		//�u���b�N�̎g�p����Ă��鎞
		if (pBlock[nCntBlock].bUse && pBlock[nCntBlock].nCntSpawn <= 0)
		{
			//�e���~�`�̎�
			if (g_aBullet[nCnt].pos.x <= pBlock[nCntBlock].pos.x + pBlock[nCntBlock].fHalfSpanX + g_fRadius_Bullet &&
				g_aBullet[nCnt].pos.x >= pBlock[nCntBlock].pos.x - pBlock[nCntBlock].fHalfSpanX - g_fRadius_Bullet &&
				g_aBullet[nCnt].pos.y <= pBlock[nCntBlock].pos.y + pBlock[nCntBlock].fHalfSpanY + g_fRadius_Bullet &&
				g_aBullet[nCnt].pos.y >= pBlock[nCntBlock].pos.y - pBlock[nCntBlock].fHalfSpanY - g_fRadius_Bullet)
			{
				//�e�̎g�p������
				g_aBullet[nCnt].bUse = false;

				if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
				{
					//���ŃG�t�F�N�g
					SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pBlock[nCntBlock].move.x);
				}
			}
		}
	}
}

//************************************************
//�X���C�h�u���b�N�ւ̓����蔻�菈���֐�
//************************************************
void HitDetection_SlideBlock(int nCnt)
{
	SLIDEBLOCK* pSlideBlock;

	pSlideBlock = Getinfo_SlideBlock();

	//�X���C�h�u���b�N�̐��������蔻�����
	for (int nCntSlideBlock = 0; nCntSlideBlock < AMOUNT_POLYGON_SLIDEBLOCK; nCntSlideBlock++)
	{
		//�X���C�h�u���b�N���g�p����Ă��鎞
		if (pSlideBlock[nCntSlideBlock].bUse && pSlideBlock[nCntSlideBlock].nCntSpawn <= 0)
		{
			//�e���~�`�̎�
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//�u���b�N�ɓ�������
				if (g_aBullet[nCnt].pos.x <= pSlideBlock[nCntSlideBlock].pos.x + pSlideBlock[nCntSlideBlock].fHalfSpanX + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.x >= pSlideBlock[nCntSlideBlock].pos.x - pSlideBlock[nCntSlideBlock].fHalfSpanX - g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y <= pSlideBlock[nCntSlideBlock].pos.y + pSlideBlock[nCntSlideBlock].fHalfSpanY + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y >= pSlideBlock[nCntSlideBlock].pos.y - pSlideBlock[nCntSlideBlock].fHalfSpanY - g_fRadius_Bullet)
				{
					//�e�̎g�p������
					g_aBullet[nCnt].bUse = false;

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//���ŃG�t�F�N�g
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pSlideBlock[nCntSlideBlock].move.x);
					}
				}
			}
		}
	}
}

//************************************************
//�u���C�N�u���b�N�ւ̓����蔻�菈���֐�
//************************************************
void HitDetection_BreakBlock(int nCnt)
{
	BREAKBLOCK* pBreakBlock;

	pBreakBlock = Getinfo_BreakBlock();

	//�u���C�N�u���b�N�̐��������蔻�����
	for (int nCntBreakBlock = 0; nCntBreakBlock < AMOUNT_POLYGON_BREAKBLOCK; nCntBreakBlock++)
	{
		//�u���C�N�u���b�N�̎g�p����Ă��鎞
		if (pBreakBlock[nCntBreakBlock].bUse && pBreakBlock[nCntBreakBlock].nCntSpawn <= 0)
		{
			//�e���~�`�̎�
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//�u���b�N�ɓ�������
				if (g_aBullet[nCnt].pos.x <= pBreakBlock[nCntBreakBlock].pos.x + pBreakBlock[nCntBreakBlock].fHalfSpanX + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.x >= pBreakBlock[nCntBreakBlock].pos.x - pBreakBlock[nCntBreakBlock].fHalfSpanX - g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y <= pBreakBlock[nCntBreakBlock].pos.y + pBreakBlock[nCntBreakBlock].fHalfSpanY + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y >= pBreakBlock[nCntBreakBlock].pos.y - pBreakBlock[nCntBreakBlock].fHalfSpanY - g_fRadius_Bullet)
				{
					//�e�̎g�p������
					g_aBullet[nCnt].bUse = false;

					Hit_BreakBlock(nCntBreakBlock, g_aBullet[nCnt].nDamage);

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//���ŃG�t�F�N�g
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pBreakBlock[nCntBreakBlock].move.x);
					}
				}
			}
		}
	}
}