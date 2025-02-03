//************************************************
//
//�e[bullet.cpp]
//Author�F���c����
//
//************************************************
#include "bullet.h"

#include "input.h"
#include "sound.h"

#include "camera.h"
#include "collision.h"
#include "particle.h"
#include "player.h"
#include "effect.h"
#include "enemy.h"
#include "score.h"
#include "shadow.h"
#include "visible_sphere.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;	//�e�N�X�`���ւ̃|�C���^
Bullet g_aBullet[AMOUNT_BULLET];	//�e���
bool g_bZTest = false;	//Z�e�X�g�؂�ւ�
bool g_bATest = true;	//�A���t�@�e�X�g�؂�ւ�

//************************************************
//�e����
//************************************************
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e��񏉊��ݒ�
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		g_aBullet[i].bUse = false;
		g_aBullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[i].fPA = 0.0f;
		g_aBullet[i].fRadius = SPAN_BULLET;
		g_aBullet[i].nRemain = 0;
	}

	g_bZTest = false;	//Z�e�X�g�؂�ւ�
	g_bATest = true;	//�A���t�@�e�X�g�؂�ւ�

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\bullet01.png",
		&g_pTextureBullet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_BULLET, -SPAN_BULLET, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_BULLET, -SPAN_BULLET, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//************************************************
//�e�j��
//************************************************
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//************************************************
//�e�ݒ�
//************************************************
void SetInfoBullet(void)
{
	//Camera* pCamera = GetInfoCamera();
	Player* pPlayer = GetInfoPlayer();
	int nIdx = 0;

	for (int step = 0; step < 3; step++)
	{
		for (int i = 0; i < AMOUNT_BULLET; i++)
		{
			nIdx = i;

			if (g_aBullet[i].bUse) continue;

			g_aBullet[i].bUse = true;
			g_aBullet[i].pos = pPlayer->pos;
			//g_aBullet[i].rot = pCamera->rot;	//����
			g_aBullet[i].rot = pPlayer->rot;
			//g_aBullet[i].fPA = pCamera->fPA;	//��

			if (!pPlayer->bMUKIMUKI)
			{
				g_aBullet[i].nRemain = 5;
			}
			else
			{
				g_aBullet[i].nRemain = 20;
			}

			if (step == 0)
			{
				g_aBullet[nIdx].rot.y -= 0.1f;
			}

			if (step == 2)
			{
				g_aBullet[nIdx].rot.y += 0.1f;
			}

			//�����蔻��̉���
			//SetSizeVisible_Sphere(g_aBullet[i].fRadius, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), &g_aBullet[i].pos);

			/*�v���C���[�̐�[���甭�˂����悤�ɁA�����O�i�����Ă���*/
			g_aBullet[i].pos.x += sinf(g_aBullet[i].rot.y) * cosf(g_aBullet[i].fPA) * 15.0f;
			g_aBullet[i].pos.y += (sinf(g_aBullet[i].fPA) * 15.0f);
			g_aBullet[i].pos.z += cosf(g_aBullet[i].rot.y) * cosf(g_aBullet[i].fPA) * 15.0f;

			break;
		}
	}
}

//************************************************
//�e�X�V
//************************************************
void UpdateBullet(void)
{
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (g_aBullet[i].bUse)
		{
			//�ړ�
			g_aBullet[i].pos.x += sinf(g_aBullet[i].rot.y) * cosf(g_aBullet[i].fPA) * SPD_BULLET;
			g_aBullet[i].pos.y += sinf(g_aBullet[i].fPA) * SPD_BULLET;
			g_aBullet[i].pos.z += cosf(g_aBullet[i].rot.y) * cosf(g_aBullet[i].fPA) * SPD_BULLET;

			//�G�t�F�N�g����ɏo��
			SetInfoEffect(EffectStyleBullet, g_aBullet[i].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.9f));

			//���Ŕ�����s��
			DisappearBullet(i);
		}
	}

	//Z�e�X�g�؂�ւ�
	if (GetKeyboardTrigger(DIK_F2))
	{
		g_bZTest = !g_bZTest;
	}

	//�A���t�@�e�X�g�؂�ւ�
	if (GetKeyboardTrigger(DIK_F3))
	{
		g_bATest = !g_bATest;
	}
}

//************************************************
//�e����
//************************************************
void DisappearBullet(int nCnt)
{
	//�c�����Ԍ���
	g_aBullet[nCnt].nRemain--;

	//�c�����Ԃ������Ȃ�Ə���
	if (g_aBullet[nCnt].nRemain < 0)
	{
		g_aBullet[nCnt].bUse = false;

		//�����蔻������ɂ����ŏ������s��
		//DisappearVisible_Sphere(&g_aBullet[nCnt].pos);

		//�p�[�e�B�N�����o��
		for (int ii = 0; ii < 20; ii++)
		{
			SetInfoParticle(g_aBullet[nCnt].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.9f), 3.0f);
		}
	}
}

//************************************************
//�e�`��
//************************************************
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���C�g���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (g_bZTest)
	{
		//Z�ʒu�̔�r���@�̕ύX
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

		//Z�o�b�t�@�ɏ������܂Ȃ�
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	if (g_bATest)
	{
		//�A���t�@�e�X�g��L��
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	}

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (g_aBullet[i].bUse)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[i].mtxWorld);

			//�r���[�}�g���b�N�X�擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����̐��ʂɌ���������
			D3DXMatrixInverse(&g_aBullet[i].mtxWorld, NULL, &mtxView);	//�t�s������߂�

			g_aBullet[i].mtxWorld._41 = 0.0f;
			g_aBullet[i].mtxWorld._42 = 0.0f;
			g_aBullet[i].mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f1
			D3DXMatrixTranslation(&mtxTrans,
				g_aBullet[i].pos.x,
				g_aBullet[i].pos.y,
				g_aBullet[i].pos.z);

			//�ʒu�𔽉f2
			D3DXMatrixMultiply(&g_aBullet[i].mtxWorld,
				&g_aBullet[i].mtxWorld,
				&mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[i].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�r���{�[�h�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}

	//���C�g���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	if (g_bZTest)
	{
		//Z�ʒu�̔�r���@�̕ύX
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

		//Z�o�b�t�@�ɏ�������
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	if (g_bATest)
	{
		//�A���t�@�e�X�g�𖳌��ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//************************************************
//�e�̓����蔻��
//************************************************
void CollisionBullet(int nMode, int nCnt)
{
	Enemy* pEnemy = GetInfoEnemy();
	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (!g_aBullet[i].bUse) continue;

		switch (nMode)
		{
			//�G
		case CollisionModeEnemy:

			if (CollisionSphere(pEnemy[nCnt].pos, pEnemy[nCnt].fRadius, g_aBullet[i].pos, g_aBullet[i].fRadius))
			{
				//�_���[�W��Ԃ�
				if (pEnemy[nCnt].nState == EnemyStateDash || pEnemy[nCnt].nState == EnemyStateATK)
				{
					pEnemy[nCnt].nState = EnemyStateDamage;
					pEnemy[nCnt].nNowMotion = EnemyMotionStateNormal;
					pEnemy[nCnt].move.x = sinf(g_aBullet[i].rot.y) * 10.0f;
					pEnemy[nCnt].move.z = cosf(g_aBullet[i].rot.y) * 10.0f;
					pEnemy[nCnt].nLife--;
					pEnemy[nCnt].nCntState = 20;

					pPlayer->nEnegy += 10;

					Add_Score(13);

					PlaySound(SOUND_LABEL_HIT);

					g_aBullet[i].nRemain = 0;
				}
			}

			break;

			//��
		case CollisionModeWall:
			break;
		}
	}
}

//************************************************
//�e�����擾
//************************************************
Bullet* GetInfoBullet(void)
{
	return &g_aBullet[0];
}