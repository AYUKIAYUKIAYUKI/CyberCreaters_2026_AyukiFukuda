//************************************************
//
// �{�X�̒e[boss_bullet.cpp]
// Author�F�����h��
//
//************************************************

//include
#include "main.h"

#include "boss_bullet.h"
#include "collision.h"
#include "debugproc.h"
#include "object.h"
#include "player.h"
#include "shadow.h"
#include "visible_sph.h"

#include <stdlib.h>
#include <time.h>


//�O���[�o���ϐ��錾
BOSSBULLET g_aBossBullet[MAX_BOSSBULLET];				// �e�̏��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBossBullet = NULL;			// �e�N�X�`���ւ̃|�C���^
D3DXMATRIX g_mtxWorldBullet;							// ���[���h�}�g���b�N�X
int g_BulletType = 0;									// �e�̔��˂�����
//************************************************
// �{�X�̒e�̏���������
//************************************************
void InitBossBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();  //�f�o�C�X�ւ̃|�C���^

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cannon.png", &g_pTextureBossBullet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BOSSBULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBossBullet, NULL);

	VERTEX_3D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBossBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BOSSBULLET; nCntBullet++,pVtx += MAX_VARTEX)
	{
		g_aBossBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_aBossBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aBossBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
		g_aBossBullet[nCntBullet].fWidth = 0.0f;						// �e�̕�
		g_aBossBullet[nCntBullet].fHeight = 0.0f;						// �e�̍���
		g_aBossBullet[nCntBullet].fLife = 0.0f;							// �e�̎���
		g_aBossBullet[nCntBullet].id_sph = -1;							// �����蔻��̉����ԍ�
		g_aBossBullet[nCntBullet].rad = 0;								// ���̓����蔻��p�̃T�C�Y
		g_aBossBullet[nCntBullet].id_shadow = -1;						// �e�̎��ʔԍ�
		g_aBossBullet[nCntBullet].nBulletIndex = 0;						// �e�̔ԍ�
		g_aBossBullet[nCntBullet].bUse = false;							// �e���g�p���Ă��邩�ǂ���

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-MAX_BULLETSIZE, MAX_BULLETSIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_BULLETSIZE, MAX_BULLETSIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_BULLETSIZE, -MAX_BULLETSIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_BULLETSIZE, -MAX_BULLETSIZE, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBossBullet->Unlock();

	// �e��ϐ��̏�����
	g_BulletType = 0;
}

//************************************************
// �{�X�̒e�̏I������
//************************************************
void UninitBossBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBossBullet != NULL)
	{
		g_pTextureBossBullet->Release();
		g_pTextureBossBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBossBullet != NULL)
	{
		g_pVtxBuffBossBullet->Release();
		g_pVtxBuffBossBullet = NULL;
	}

}

//************************************************
// �{�X�̒e�̍X�V����
//************************************************
void UpdateBossBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BOSSBULLET; nCntBullet++)
	{
		if (!g_aBossBullet[nCntBullet].bUse)
		{// �e���g�p����Ă��Ȃ���΃R���e�B�j���[
			continue;
		}

		//********************************************************
		// �ȉ��̏����͒e���g�p����Ă���Ƃ��ɂ̂ݓK�p����܂�
		//********************************************************

		MoveBossBullet(nCntBullet);			// �e�̈ړ�

		/*---�y�V�����e�̒Ǐ]�z---*/
		TrackShadow(g_aBossBullet[nCntBullet].id_shadow, 
			g_aBossBullet[nCntBullet].pos);

		CheckUseBossBullet(nCntBullet);		// �e���g�p���Ă��邩�ǂ���

		CollisionBossBullet(nCntBullet);	// �{�X�̒e�ƌ����̓����蔻��

		BossBulletPlayerCollision(nCntBullet);	// �{�X�̒e�ƃv���C���[�̓����蔻��


	}
#ifdef _DEBUG

	PrintDebugProc("�e�̍��W : %f %f %f\n", g_aBossBullet[0].pos.x, g_aBossBullet[0].pos.y, g_aBossBullet[0].pos.z);
	PrintDebugProc("�e�̍��W : %f %f %f\n", g_aBossBullet[1].pos.x, g_aBossBullet[1].pos.y, g_aBossBullet[1].pos.z);
	PrintDebugProc("�e�̍��W : %f %f %f\n", g_aBossBullet[2].pos.x, g_aBossBullet[2].pos.y, g_aBossBullet[2].pos.z);
	PrintDebugProc("�e�̍��W : %f %f %f\n", g_aBossBullet[3].pos.x, g_aBossBullet[3].pos.y, g_aBossBullet[3].pos.z);
	//PrintDebugProc("�e�̍��W : %f %f %f\n", g_aBossBullet[10].pos.x, g_aBossBullet[10].pos.y, g_aBossBullet[10].pos.z);
#endif
}

//************************************************
// �{�X�̒e�̕`�揈��
//************************************************
void DrawBossBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans, mtxView;				// �v�Z�p�}�g���b�N�X

	// ���C�g���f�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBossBullet, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < MAX_BOSSBULLET; i++)
	{
		if (!g_aBossBullet[i].bUse)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBossBullet[i].mtxWorld);

		// �r���[�}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// �|���S�����J�����̐��ʂɌ���������
		D3DXMatrixInverse(&g_aBossBullet[i].mtxWorld, NULL, &mtxView);	// �t�s������߂�

		g_aBossBullet[i].mtxWorld._41 = 0.0f;
		g_aBossBullet[i].mtxWorld._42 = 0.0f;
		g_aBossBullet[i].mtxWorld._43 = 0.0f;

		// �ʒu�𔽉f1
		D3DXMatrixTranslation(&mtxTrans,
			g_aBossBullet[i].pos.x,
			g_aBossBullet[i].pos.y,
			g_aBossBullet[i].pos.z);

		// �ʒu�𔽉f2
		D3DXMatrixMultiply(&g_aBossBullet[i].mtxWorld,
			&g_aBossBullet[i].mtxWorld,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBossBullet[i].mtxWorld);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBossBullet);

		// �r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// ���C�g���f��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//************************************************
// �{�X�̒e�̈ړ�����
//************************************************
void MoveBossBullet(int id)
{
	g_aBossBullet[id].pos += g_aBossBullet[id].move;	// �e�̈ړ�
}

//************************************************
// �{�X�̒e���g�p���Ă��邩�ǂ���
//************************************************
void CheckUseBossBullet(int id)
{
	g_aBossBullet[id].fLife--;	// �e�̃��C�t�����炷

	if (g_aBossBullet[id].fLife <= 0.0f)
	{// ���C�t���Ȃ��Ȃ�����g�p���Ă��Ȃ���Ԃɂ���
		g_aBossBullet[id].bUse = false;
	}

	if (!g_aBossBullet[id].bUse)
	{
		// �������������
		DeleteVisibleSph(g_aBossBullet[id].id_sph);

		// �e������
		DeleteShadow(g_aBossBullet[id].id_shadow);

		// ��ڂ��I�������l�����Z�b�g
		g_aBossBullet[id].id_shadow = -1;
		g_aBossBullet[id].id_sph = -1;

	}
}

//************************************************
// �{�X�̒e�̐ݒ菈��
//************************************************
void  SetBossBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fLife)
{// �����̐���(�e�̔��ˈʒu/�e�̈ړ���/�e�̎���)

	VERTEX_3D* pVtx;  //���_���̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBossBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BOSSBULLET; nCntBullet++, pVtx += MAX_VARTEX)
	{
		if (!g_aBossBullet[nCntBullet].bUse)
		{
			g_aBossBullet[nCntBullet].pos = pos;						// �e�̔��ˈʒu
			g_aBossBullet[nCntBullet].move = move;						// �e�̈ړ���
			g_aBossBullet[nCntBullet].fLife = fLife;					// �e�̎���
			g_aBossBullet[nCntBullet].rad = MAX_BULLETSIZE * 2;			// �e�̓����蔻��̑傫��
			g_aBossBullet[nCntBullet].bUse = true;						// �g�p���Ă����Ԃɂ���

			/*---�y�e�𐶐��z---*/
			g_aBossBullet[nCntBullet].id_shadow = CreateShadow(20.0f);


#ifdef _DEBUG

			g_aBossBullet[nCntBullet].id_sph = CreateVisibleSph(20.0f, { 0.0f, 1.0f, 0.0f, 1.0f }, &g_aBossBullet[nCntBullet].pos);
#endif
			break;
		}
	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBossBullet->Unlock();

}

//************************************************
// �{�X�̒e�̏��̎擾
//************************************************
BOSSBULLET* GetBullet(void)
{
	return g_aBossBullet;
}

//************************************************
// �{�X�̒e�ƌ����̓����蔻��
//************************************************
void CollisionBossBullet(int id)
{
	// �e�̃^�C�v�Ɍ��炸�I�u�W�F�N�g�Ƃ̏Փ˔�����s��
	Object* pObject = GetInfoObject();

	for (int nCntObject = 0; nCntObject < AMOUNT_OBJECT; nCntObject++, pObject++)
	{
		if (!pObject->use)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (CollisionSphAABB(g_aBossBullet[id].pos, g_aBossBullet[id].rad, pObject->model.aabb))
		{
			g_aBossBullet[id].fLife = 0.0f;	// �e�̎�����0�ɂ���

			CheckUseBossBullet(id);	//�e�̎g�p����

			HitObject(nCntObject);	// �����ɏՓ˔���

		}

	}
}

//************************************************
// �{�X�̒e�ƃv���C���[�̓����蔻��
//************************************************
void BossBulletPlayerCollision(int id)
{
	Player* pPlayer = GetInfoPlayer();

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (!g_aBossBullet[id].bUse)
		{ // ���g�p�Ȃ�R���e�B�j���[
			continue;
		}

		if (CollisionSph(g_aBossBullet[id].pos, g_aBossBullet[id].rad, pPlayer[nCntPlayer].pos, pPlayer[nCntPlayer].param.rad))
		{
			g_aBossBullet[id].fLife = 0.0f;	// �e�̎�����0�ɂ���

			CheckUseBossBullet(id);	//�e�̎g�p����
		}

		if (pPlayer[nCntPlayer].param.state == stateDamage_p ||
			pPlayer[nCntPlayer].param.state == stateDead_p)
		{ // �����F���S��ԂȂ�R���e�B�j���[
			continue;
		}

		if (CollisionSph(g_aBossBullet[id].pos, g_aBossBullet[id].rad, pPlayer[nCntPlayer].pos, pPlayer[nCntPlayer].param.rad))
		{
			// ��e�̏���
			HitPlayer(nCntPlayer);

			g_aBossBullet[id].fLife = 0.0f;	// �e�̎�����0�ɂ���

			CheckUseBossBullet(id);	//�e�̎g�p����
		}

	}
}
