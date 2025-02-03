//************************************************
//
// �e[bullet.cpp]
// Author�F���c����
//
//************************************************

/*/ �C���N���[�h�t�@�C�� /*/
#include "bullet.h"
// ����
#include "input.h"
#include "sound.h"
// ������
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "effect.h"
#include "effect_burn.h"
#include "effect_sand.h"
#include "effect_smoke.h"
#include "enemy.h"
#include "explosion.h"
#include "game.h"
#include "item.h"
#include "object.h"
#include "player.h"
#include "shadow.h"
// �f�o�b�O��
#ifdef _DEBUG
#include "debugproc.h"
#include "visible_sph.h"
#endif	// _DEBUG

/*---�y�}�N����`�z---*/
#define RPG_UP	(6.0f)
#define GRAVITY	(0.5f)
#define RPG_SPEED	(9.0f)
#define RPG_INCSPEED	(0.35f)
#define RPG_DEFSPEED	(0.1f)
//������RPG�̓����蔻��f�J�����Ă�
//#define RPG_EXRADIUS	(5.0f)
/*---�y�O���[�o���ϐ��z---*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			// �e�N�X�`���ւ̃|�C���^
Bullet g_Bullet[AMOUNT_BULLET];						// �e���

/*---�y�v���g�^�C�v�錾�z---*/
void SubBullet(float rotY, D3DXVECTOR3 pos);	// �g���FSTG
void WideRangeCollision(int id);				// �g������FRPG
void WideRangeDelete(int id);					// �g�����ŁFRPG

//************************************************
// �e����
//************************************************
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{ // �e��񃊃Z�b�g
		g_Bullet[i].use = false;							// �g�p�t���O
		g_Bullet[i].type = -1;								// �^�C�v
		g_Bullet[i].style = -1;								// �X�^�C��
		g_Bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_Bullet[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ̏�����
		g_Bullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_Bullet[i].rad = 0;								// ���a
		g_Bullet[i].id_shadow = -1;							// �e�̎��ʔԍ�
		g_Bullet[i].id_sph = -1;							// ��������̎��ʔԍ�
		g_Bullet[i].RPG_Speed = 0.0f;						//���P�����̒e��
		g_Bullet[i].RPGBulletSpeed = 0.0f;					//�e�̉���
		g_Bullet[i].startRPGfall = false;					//�������J�n����܂ł̃C���^�[�o��
		g_Bullet[i].RPGammofallcount = 0;					//���P�����̗�������^�C�~���O���߂�p
		g_Bullet[i].ShotRPG = false;						//���˂������ǂ���
	}

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cannon.png",
		&g_pTextureBullet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BULLET; i++, pVtx += AMOUNT_VTX)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_BULLET, -SPAN_BULLET, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_BULLET, -SPAN_BULLET, 0.0f);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//************************************************
// �e�j��
//************************************************
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{ // �e�N�X�`���̔j��
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	if (g_pVtxBuffBullet != NULL)
	{ // ���_�o�b�t�@�̔j��
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//************************************************
// �e����
//************************************************
void CreateBullet(int type, int id)
{
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (g_Bullet[i].use)
		{ // �g�p���Ȃ�R���e�B�j���[
			continue;
		}

		Camera* pCamera = GetInfoCamera();	// �J�����ւ̃|�C���^
		Player* pPlayer = GetInfoPlayer();	// �v���C���[�ւ̃|�C���^

		g_Bullet[i].type = type;	// �e�Ƀ^�C�v��ݒ�
		g_Bullet[i].use = true;		// �g�p����

		// �������J�����̕�����
		g_Bullet[i].rot = pCamera[id].rot;

		// ���펯�ʔԍ��i�[
		int weapon = pPlayer[id].param.weapon;

		// ����ɉ����ē���ύX
		switch (weapon)
		{
			// �e
		case styleGun:
			PlaySound(SOUND_LABEL_NOMALGUNSHOT);
			g_Bullet[i].style = styleGun;	// �X�^�C�����f

			g_Bullet[i].pos =
			{
				pPlayer[id].offset_atk[weapon].mtx._41,
				pPlayer[id].offset_atk[weapon].mtx._42,
				pPlayer[id].offset_atk[weapon].mtx._43,
			};

			g_Bullet[i].rad = 4.0f;		// �傫���F�K��
			g_Bullet[i].remain = 20;	// ����

			break;

			// RPG
		case styleRPG:
			PlaySound(SOUND_LABEL_ROCKETLAUNCERSHOT);
			g_Bullet[i].move.y = RPG_UP;
			g_Bullet[i].style = styleRPG;	// �X�^�C�����f

			g_Bullet[i].pos =
			{
				pPlayer[id].offset_atk[weapon].mtx._41,
				pPlayer[id].offset_atk[weapon].mtx._42,
				pPlayer[id].offset_atk[weapon].mtx._43,
			};

			g_Bullet[i].rad = 10.0f;	// �傫���F�K��
			g_Bullet[i].remain = 1000;	// ����

			break;

			// �K�g�����O
		case styleGut:
			PlaySound(SOUND_LABEL_MACHINEGUNSHOT);
			g_Bullet[i].style = styleGut;	// �X�^�C�����f

			g_Bullet[i].pos =
			{
				pPlayer[id].offset_atk[weapon].mtx._41,
				pPlayer[id].offset_atk[weapon].mtx._42,
				pPlayer[id].offset_atk[weapon].mtx._43,
			};

			g_Bullet[i].rad = 3.0f;		// �傫���F�K��
			g_Bullet[i].remain = 10;	// ����

			break;

			// �U�e�e
		case styleShot:
			PlaySound(SOUND_LABEL_SHOTGUNSHOT);
			g_Bullet[i].style = styleShot;	// �X�^�C�����f

			g_Bullet[i].pos =
			{
				pPlayer[id].offset_atk[weapon].mtx._41,
				pPlayer[id].offset_atk[weapon].mtx._42,
				pPlayer[id].offset_atk[weapon].mtx._43,
			};

			g_Bullet[i].rad = 7.5f;		// �傫���F�K��
			g_Bullet[i].remain = 5;	// ����

			SubBullet(g_Bullet[i].rot.y, g_Bullet[i].pos);	// �g���ˌ��F2WAY

			break;
		}

		// �e�𐶐�
		g_Bullet[i].id_shadow = CreateShadow(5.0f);

#ifdef _DEBUG

		// �����蔻�������
		g_Bullet[i].id_sph = CreateVisibleSph(g_Bullet[i].rad, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), &g_Bullet[i].pos);

#endif	// _DEBUG 

		break;
	}
}

//************************************************
// �e�X�V
//************************************************
void UpdateBullet(void)
{
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (!g_Bullet[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// �ړ�
		MoveBullet(i);

		/*---�y�V�����e�̒Ǐ]�z---*/
		TrackShadow(g_Bullet[i].id_shadow,
			g_Bullet[i].pos);

		// �G�t�F�N�g���o��
		//SetEffect(g_Bullet[i].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.5f, 3.0f);

		// �����蔻����s��
		CollisionBullet(i);

		// ���Ŕ�����s��
		DeleteBullet(i);

		if (g_Bullet[i].style == styleRPG && g_Bullet[i].remain == -99)
		{
			// �g������
			WideRangeCollision(i);
		}
	}

	// ���_��W�J
	SetVtxBullet();
}

//************************************************
// ���_����W�J
//************************************************
void SetVtxBullet(void)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx;

	// ���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BULLET; i++, pVtx += AMOUNT_VTX)
	{
		if (!g_Bullet[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-g_Bullet[i].rad, g_Bullet[i].rad, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Bullet[i].rad, g_Bullet[i].rad, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_Bullet[i].rad, -g_Bullet[i].rad, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Bullet[i].rad, -g_Bullet[i].rad, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//************************************************
// �e�ړ�
//************************************************
void MoveBullet(int id)
{
	if (g_Bullet[id].style == styleGun)
	{ // �ʏ�e

		// �ړ�
		g_Bullet[id].pos.x += sinf(g_Bullet[id].rot.y) * 15.0f;
		g_Bullet[id].pos.z += cosf(g_Bullet[id].rot.y) * 15.0f;
	}
	else if (g_Bullet[id].style == styleRPG)
	{ // RPG�e

		//RPG�ɂ̂ݏd�͂�K�p
		g_Bullet[id].move.y -= GRAVITY;
		g_Bullet[id].pos.y += g_Bullet[id].move.y;

		// ���ʂȏ���t�^
		g_Bullet[id].RPG_Speed = RPG_SPEED;
		g_Bullet[id].RPGBulletSpeed += RPG_INCSPEED;
		g_Bullet[id].RPG_Speed += g_Bullet[id].RPGBulletSpeed;

		// �ړ�
		g_Bullet[id].pos.x += sinf(g_Bullet[id].rot.y) * cosf(g_Bullet[id].rot.x) * g_Bullet[id].RPG_Speed;

		g_Bullet[id].pos.z += cosf(g_Bullet[id].rot.y) * cosf(g_Bullet[id].rot.x) * g_Bullet[id].RPG_Speed;
	}
	else if (g_Bullet[id].style == styleGut)
	{ // �~�j�K���e

		// �ړ�
		g_Bullet[id].pos.x += sinf(g_Bullet[id].rot.y) * 30.0f;
		g_Bullet[id].pos.z += cosf(g_Bullet[id].rot.y) * 30.0f;
	}
	else if (g_Bullet[id].style == styleShot)
	{ // �U�e�e�e

		// �ړ�
		g_Bullet[id].pos.x += sinf(g_Bullet[id].rot.y) * 30.0f;
		g_Bullet[id].pos.z += cosf(g_Bullet[id].rot.y) * 30.0f;
	}
}

//************************************************
// �e����
//************************************************
void DeleteBullet(int id)
{
	if (CntDuration(&g_Bullet[id].remain) ||
		g_Bullet[id].pos.y - g_Bullet[id].rad <= 0.0f)
	{ // �c�����Ԃ������Ȃ邩�n�ʂɒ��e�����

		/*---�y���P�����̂݁z---*/
		if (g_Bullet[id].style == styleRPG)
		{
			g_Bullet[id].remain = -99;	// �g���˓�

			return;
		}

		// ����
		SetExplosion(g_Bullet[id].pos, { 0.0f ,0.0f ,0.0f ,0.0f }, g_Bullet[id].rad * 5.0f, g_Bullet[id].rad * 5.0f);

		// ����
		g_Bullet[id].use = false;							// �g�p�t���O
		g_Bullet[id].type = -1;								// �^�C�v���Z�b�g
		g_Bullet[id].style = -1;							// �X�^�C�����Z�b�g
		g_Bullet[id].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_Bullet[id].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ̏�����
		g_Bullet[id].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_Bullet[id].rad = 0;								// ���a
		g_Bullet[id].RPG_Speed = 0.0f;						//���P�����̒e��
		g_Bullet[id].RPGBulletSpeed = 0.0f;					//�e�̉���
		g_Bullet[id].startRPGfall = false;					//�������J�n����܂ł̃C���^�[�o��
		g_Bullet[id].RPGammofallcount = 0;					//���P�����̗�������^�C�~���O���߂�p
		g_Bullet[id].ShotRPG = false;						//���˂������ǂ���

		// �e������
		DeleteShadow(g_Bullet[id].id_shadow);

#ifdef _DEBUG

		// �������������
		DeleteVisibleSph(g_Bullet[id].id_sph);

#endif	// _DEBUG

		// ��ڂ��I�������l�����Z�b�g
		g_Bullet[id].id_shadow = -1;
		g_Bullet[id].id_sph = -1;
	}
}

//************************************************
// �e�`��
//************************************************
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans, mtxView;				// �v�Z�p�}�g���b�N�X

	// ���C�g���f�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//// �[�x�e�X�g�̔�r���@�̕ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//// �[�x�o�b�t�@�ɕ`�悵�Ȃ�
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (!g_Bullet[i].use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Bullet[i].mtxWorld);

		// �r���[�}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// �|���S�����J�����̐��ʂɌ���������
		D3DXMatrixInverse(&g_Bullet[i].mtxWorld, NULL, &mtxView);	// �t�s������߂�

		g_Bullet[i].mtxWorld._41 = 0.0f;
		g_Bullet[i].mtxWorld._42 = 0.0f;
		g_Bullet[i].mtxWorld._43 = 0.0f;

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_Bullet[i].pos.x,
			g_Bullet[i].pos.y,
			g_Bullet[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_Bullet[i].mtxWorld,
			&g_Bullet[i].mtxWorld,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[i].mtxWorld);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet);

		// �r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// ���C�g���f��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//// �[�x�e�X�g�̔�r���@�̕ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//// �[�x�o�b�t�@�ɏ�������
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//************************************************
// �e�̓����蔻��
//************************************************
void CollisionBullet(int id)
{
	// �e�̃^�C�v�Ɍ��炸�I�u�W�F�N�g�Ƃ̏Փ˔�����s��
	Object* pObject = GetInfoObject();

	for (int i = 0; i < AMOUNT_OBJECT; i++, pObject++)
	{
		if (!pObject->use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (CollisionSphAABB(g_Bullet[id].pos, g_Bullet[id].rad, pObject->model.aabb))
		{
			g_Bullet[id].remain = 0;	// �e�͏���

			HitObject(i);	// �����ɏՓ˔���
		}
	}

	// switch����ł͐錾���s���Ȃ�����if�Ő���@�����ʂɉ\�݂����ł����A����͂������̂܂܂����܂��c
	if (g_Bullet[id].type == bulletPlayer)
	{ // �e���v���C���[�^�C�v�Ȃ�
		Enemy* pEnemy = GetInfoEnemy();
		BOSS* pBoss = GetInfoBoss();

		for (int j = 0; j < AMOUNT_ENEMY; j++, pEnemy++)
		{ // �G�l�~�[�Ƃ̔�����s��
			if (!pEnemy->use)
			{ // ���g�p�Ȃ�R���e�B�j���[
				continue;
			}

			if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pEnemy->pos, pEnemy->param.rad))
			{ // �G�Ƀq�b�g�����

				g_Bullet[id].remain = 0;	// �g�p���Ԃ𖳂���

				// �G�ɔ�e����t�^
				if (pEnemy->param.state != stateRotate_e &&
					pEnemy->param.state != stateDamage_e &&
					pEnemy->param.state != stateDead_e)
				{ // ��]�F�����F���S��ԂłȂ��Ƃ��̂�
					HitEnemy(j);

					if (pEnemy->param.style == Dragonfly)
					{ // ��x�̂ݓ��ʂɃm�b�N�o�b�N��^����
						pEnemy->move.x *= -1.0f;
						pEnemy->move.z *= -1.0f;
					}
				}
			}
		}

		for (int i = 0; i < MAX_BOSS; i++, pBoss++)
		{//�{�X�Ƃ̔�����s��
			if (!pBoss->use)
			{//���g�p�Ȃ�R���e�B�j���[
				continue;
			}

			for (int j = 0; j < AMOUNT_BOSS_PARTS; j++)
			{
				if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pBoss->pos_sph[j], pBoss->rad[j]))
				{//�{�X�ɓ������

					g_Bullet[id].remain = 0;	// �g�p���Ԃ𖳂���

					// �G�ɔ�e����t�^
					if (pBoss->Param.state != stateDamage_b &&
						pBoss->Param.state != stateDead_b)
					{// ������ԂƎ��S��ԂłȂ��Ƃ��̂�
						HitBoss(i);
					}
				}
			}
		}
	}
	//else if (g_Bullet[id].type == bulletEnemy)
	//{ // �e���G�l�~�[�^�C�v�Ȃ�

	//}
	//else if (g_Bullet[id].type == bulletBoss)
	//{// �e���{�X�^�C�v�Ȃ�
	//	Player* pPlayer = GetInfoPlayer(); // �v���C���[�̏����擾����

	//	for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++, pPlayer++)
	//	{
	//		if (!pPlayer->use)
	//		{//�v���C���[������ł�����R���e�B�j���[
	//			continue;
	//		}

	//		if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pPlayer->pos, pPlayer->param.rad))
	//		{
	//			DamagePlayer(nCntPlayer);
	//		}
	//	}
	//}
}

//************************************************
// �e�����擾
//************************************************
Bullet* GetInfoBullet(void)
{
	return &g_Bullet[0];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// �g���FSTG
//************************************************
void SubBullet(float rotY, D3DXVECTOR3 pos)
{
	for (int way = 0; way < 2; way++)
	{
		for (int i = 0; i < AMOUNT_BULLET; i++)
		{
			if (g_Bullet[i].use)
			{ // �g�p���Ȃ�R���e�B�j���[
				continue;
			}

			g_Bullet[i].type = 0;		// �e�Ƀ^�C�v��ݒ�
			g_Bullet[i].use = true;		// �g�p����

			// �������J�����̕�����
			if (way == 0)
			{
				g_Bullet[i].rot.y = rotY + 0.45f;
			}
			else
			{
				g_Bullet[i].rot.y = rotY - 0.45f;
			}

			g_Bullet[i].style = styleShot;	// �X�^�C�����w��

			g_Bullet[i].pos = pos;	// �ʒu�͂��̎��_�̂��̂��Q��

			g_Bullet[i].rad = 7.5f;		// �傫���F�K��
			g_Bullet[i].remain = 5;	// ����

				// �e�𐶐�
			g_Bullet[i].id_shadow = CreateShadow(5.0f);

#ifdef _DEBUG

			// �����蔻�������
			g_Bullet[i].id_sph = CreateVisibleSph(g_Bullet[i].rad, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), &g_Bullet[i].pos);

#endif	// _DEBUG 

			break;
		}
	}
}

//************************************************
// �g������FRPG
//************************************************
void WideRangeCollision(int id)
{
	g_Bullet[id].rad = 175.0f;	// �g���˓�

		// �e�̃^�C�v�Ɍ��炸�I�u�W�F�N�g�Ƃ̏Փ˔�����s��
	Object* pObject = GetInfoObject();

	for (int i = 0; i < AMOUNT_OBJECT; i++, pObject++)
	{
		if (!pObject->use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (CollisionSphAABB(g_Bullet[id].pos, g_Bullet[id].rad, pObject->model.aabb))
		{
			HitObject(i);	// �����ɏՓ˔���
		}
	}

	Enemy* pEnemy = GetInfoEnemy();
	BOSS* pBoss = GetInfoBoss();

	for (int i = 0; i < AMOUNT_ENEMY; i++, pEnemy++)
	{ // �G�l�~�[�Ƃ̔�����s��
		if (!pEnemy->use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pEnemy->pos, pEnemy->param.rad))
		{ // �G�Ƀq�b�g�����

			// �G�ɔ�e����t�^
			if (pEnemy->param.state != stateRotate_e &&
				pEnemy->param.state != stateDamage_e &&
				pEnemy->param.state != stateDead_e)
			{ // ��]�F�����F���S��ԂłȂ��Ƃ��̂�
				HitEnemy(i);

				if (pEnemy->param.style == Dragonfly)
				{ // ��x�̂ݓ��ʂɃm�b�N�o�b�N��^����
					pEnemy->move.x *= -1.0f;
					pEnemy->move.z *= -1.0f;
				}
			}
		}
	}

	for (int i = 0; i < MAX_BOSS; i++, pBoss++)
	{//�{�X�Ƃ̔�����s��
		if (!pBoss->use)
		{//���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		for (int j = 0; j < AMOUNT_BOSS_PARTS; j++)
		{
			if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pBoss->pos_sph[j], pBoss->rad[j]))
			{//�{�X�ɓ������

				// �G�ɔ�e����t�^
				if (pBoss->Param.state != stateDamage_b &&
					pBoss->Param.state != stateDead_b)
				{// ������ԂƎ��S��ԂłȂ��Ƃ��̂�
					HitBoss(i);
				}
			}
		}
	}

	// ����
	WideRangeDelete(id);
}

//************************************************
// �g�����ŁFRPG
//************************************************
void WideRangeDelete(int id)
{
	// �͈͏o��
	CreateEffect_Burn(g_Bullet[id].pos, g_Bullet[id].rad);

	// ���G�t�F�N�g
	for (int i = 0; i < 7; i++)
	{
		CreateEffect_Smoke(0, &g_Bullet[id].pos);
		CreateEffect_Smoke(1, &g_Bullet[id].pos);
	}

	// ����
	SetExplosion(g_Bullet[id].pos, { 0.0f, 0.0f, 0.0f, 0.0f }, 35.0f, 35.0f);

	// ����
	g_Bullet[id].use = false;							// �g�p�t���O
	g_Bullet[id].type = -1;								// �^�C�v���Z�b�g
	g_Bullet[id].style = -1;							// �X�^�C�����Z�b�g
	//g_Bullet[id].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	g_Bullet[id].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ̏�����
	g_Bullet[id].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	g_Bullet[id].rad = 0;								// ���a
	g_Bullet[id].RPG_Speed = 0.0f;						//���P�����̒e��
	g_Bullet[id].RPGBulletSpeed = 0.0f;					//�e�̉���
	g_Bullet[id].startRPGfall = false;					//�������J�n����܂ł̃C���^�[�o��
	g_Bullet[id].RPGammofallcount = 0;					//���P�����̗�������^�C�~���O���߂�p
	g_Bullet[id].ShotRPG = false;						//���˂������ǂ���

	// �e������
	DeleteShadow(g_Bullet[id].id_shadow);

#ifdef _DEBUG

	// �������������
	DeleteVisibleSph(g_Bullet[id].id_sph);

#endif	// _DEBUG

	// ��ڂ��I�������l�����Z�b�g
	g_Bullet[id].id_shadow = -1;
	g_Bullet[id].id_sph = -1;
}