//************************************************
//
//�X�|�[���G�t�F�N�g����[effect_spawn.cpp]
//Author�F���c����
//
//************************************************
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "effect_spawn.h"
#include "enemy.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Effect_Spawn = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Effect_Spawn = NULL;	//���_�o�b�t�@�̃|�C���^
SPAWN_EFFECT g_aEffect_Spwan[AMOUNT_POLYGON_EFFECT_SPAWN];	//�X�|�[���G�t�F�N�g���i�[

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Effect_Spawn(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GENERATOR_EFFECT_SPAWN,
		&g_pTexture_Effect_Spawn);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_EFFECT_SPAWN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Effect_Spawn,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Spawn;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Spawn->Lock(0, 0, (void**)&pVtx_Effect_Spawn, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_SPAWN; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Effect_Spawn[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Spawn[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Spawn[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Spawn[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Effect_Spawn[0].rhw = 1.0f;
		pVtx_Effect_Spawn[1].rhw = 1.0f;
		pVtx_Effect_Spawn[2].rhw = 1.0f;
		pVtx_Effect_Spawn[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Effect_Spawn[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Spawn[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Spawn[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Spawn[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Effect_Spawn[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Effect_Spawn[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Effect_Spawn[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Effect_Spawn[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Effect_Spawn += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Spawn->Unlock();

	//�X�|�[���G�t�F�N�g��񏉊��ݒ�
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_SPAWN; nCnt++)
	{
		g_aEffect_Spwan[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu������
		g_aEffect_Spwan[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʏ�����
		g_aEffect_Spwan[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����������
		g_aEffect_Spwan[nCnt].bUse = false;							//�g�p����𖳂���
		g_aEffect_Spwan[nCnt].fLength = 0.0f;						//�Ίp������������
		g_aEffect_Spwan[nCnt].fAngle = 0.0f;						//�p�x����������
		g_aEffect_Spwan[nCnt].nColorA = 0;							//�����x������
	}
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Effect_Spawn(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Effect_Spawn != NULL)
	{
		g_pTexture_Effect_Spawn->Release();
		g_pTexture_Effect_Spawn = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Effect_Spawn != NULL)
	{
		g_pVtxBuff_Effect_Spawn->Release();
		g_pVtxBuff_Effect_Spawn = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Effect_Spawn(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Spawn;

	//�G(����)���ւ̃|�C���^
	ENEMY* pEnemy;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Spawn->Lock(0, 0, (void**)&pVtx_Effect_Spawn, 0);

	//�G�����擾
	pEnemy = Getinfo_Enemy();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_SPAWN; nCnt++)
	{
		//���̎g�p���肪���鎞
		if (g_aEffect_Spwan[nCnt].bUse)
		{
			//�ړ�
			g_aEffect_Spwan[nCnt].pos += g_aEffect_Spwan[nCnt].move;

			//��]
			g_aEffect_Spwan[nCnt].rot += D3DXVECTOR3(0.0f, 0.0f, ROTATE_SPD_EFFECT_SPAWN);

			pVtx_Effect_Spawn[0].pos.x = g_aEffect_Spwan[nCnt].pos.x + sinf(g_aEffect_Spwan[nCnt].rot.z - (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[0].pos.y = g_aEffect_Spwan[nCnt].pos.y + cosf(g_aEffect_Spwan[nCnt].rot.z - (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[1].pos.x = g_aEffect_Spwan[nCnt].pos.x + sinf(g_aEffect_Spwan[nCnt].rot.z + (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[1].pos.y = g_aEffect_Spwan[nCnt].pos.y + cosf(g_aEffect_Spwan[nCnt].rot.z + (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[2].pos.x = g_aEffect_Spwan[nCnt].pos.x + sinf(g_aEffect_Spwan[nCnt].rot.z - g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[2].pos.y = g_aEffect_Spwan[nCnt].pos.y + cosf(g_aEffect_Spwan[nCnt].rot.z - g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[3].pos.x = g_aEffect_Spwan[nCnt].pos.x + sinf(g_aEffect_Spwan[nCnt].rot.z + g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[3].pos.y = g_aEffect_Spwan[nCnt].pos.y + cosf(g_aEffect_Spwan[nCnt].rot.z + g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
		
			//�J���[�����O
			if (!pEnemy[nCnt].bFinishEffect)
			{
				//�L����
				g_aEffect_Spwan[nCnt].fLength++;

				g_aEffect_Spwan[nCnt].nColorA += CHANGE_SPD_COLORA_EFFECT_SPAWN;

				if (g_aEffect_Spwan[nCnt].nColorA >= 255)
				{
					g_aEffect_Spwan[nCnt].nColorA = 255;

					//�����n�߂�
					pEnemy[nCnt].bFinishEffect = true;
				}
			}
			else
			{
				//�k��
				g_aEffect_Spwan[nCnt].fLength--;

				g_aEffect_Spwan[nCnt].nColorA -= CHANGE_SPD_COLORA_EFFECT_SPAWN;

				if (g_aEffect_Spwan[nCnt].nColorA <= 0)
				{
					g_aEffect_Spwan[nCnt].nColorA = 0;

					g_aEffect_Spwan[nCnt].bUse = false;
				}
			}

			pVtx_Effect_Spawn[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aEffect_Spwan[nCnt].nColorA);
			pVtx_Effect_Spawn[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aEffect_Spwan[nCnt].nColorA);
			pVtx_Effect_Spawn[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aEffect_Spwan[nCnt].nColorA);
			pVtx_Effect_Spawn[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aEffect_Spwan[nCnt].nColorA);
		}
		//�o�O�h�~
		else
		{
			g_aEffect_Spwan[nCnt].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

			pVtx_Effect_Spawn[0].pos = g_aEffect_Spwan[nCnt].pos;
			pVtx_Effect_Spawn[1].pos = g_aEffect_Spwan[nCnt].pos;
			pVtx_Effect_Spawn[2].pos = g_aEffect_Spwan[nCnt].pos;
			pVtx_Effect_Spawn[3].pos = g_aEffect_Spwan[nCnt].pos;
		}

		pVtx_Effect_Spawn += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Spawn->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Effect_Spawn(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Effect_Spawn, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Effect_Spawn);

	//�|���S���̕`��
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_SPAWN; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//���_��W�J����֐�
//************************************************
void SetPos_Vtx_Effect_Spawn(int nCntEnemy, D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Effect_Spawn;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Effect_Spawn->Lock(0, 0, (void**)&pVtx_Effect_Spawn, 0);

	//�g�p����Ă��Ȃ��ԍ������m
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_SPAWN; nCnt++)
	{
		//���̎g�p���肪������
		if (g_aEffect_Spwan[nCntEnemy].bUse == false)
		{
			//�G�̈ʒu��
			g_aEffect_Spwan[nCntEnemy].pos = pos;

			//�G�̈ړ��ʂ��R�s�[
			g_aEffect_Spwan[nCntEnemy].move = move;

			//�����̌�����ݒ�
			g_aEffect_Spwan[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//���S�����Ƃɒ��_���W�̐ݒ�
			pVtx_Effect_Spawn[0].pos.x = g_aEffect_Spwan[nCntEnemy].pos.x + sinf(g_aEffect_Spwan[nCntEnemy].rot.z - (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[0].pos.y = g_aEffect_Spwan[nCntEnemy].pos.y + cosf(g_aEffect_Spwan[nCntEnemy].rot.z - (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[1].pos.x = g_aEffect_Spwan[nCntEnemy].pos.x + sinf(g_aEffect_Spwan[nCntEnemy].rot.z + (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[1].pos.y = g_aEffect_Spwan[nCntEnemy].pos.y + cosf(g_aEffect_Spwan[nCntEnemy].rot.z + (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[2].pos.x = g_aEffect_Spwan[nCntEnemy].pos.x + sinf(g_aEffect_Spwan[nCntEnemy].rot.z - g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[2].pos.y = g_aEffect_Spwan[nCntEnemy].pos.y + cosf(g_aEffect_Spwan[nCntEnemy].rot.z - g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[3].pos.x = g_aEffect_Spwan[nCntEnemy].pos.x + sinf(g_aEffect_Spwan[nCntEnemy].rot.z + g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[3].pos.y = g_aEffect_Spwan[nCntEnemy].pos.y + cosf(g_aEffect_Spwan[nCntEnemy].rot.z + g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;

			g_aEffect_Spwan[nCntEnemy].bUse = true;	//���̂�̎g�p������o��

			//�Ίp���̒�����ݒ�
			g_aEffect_Spwan[nCntEnemy].fLength = sqrtf(SPAN_X_EFFECT_SPAWN * SPAN_X_EFFECT_SPAWN +
				SPAN_Y_EFFECT_SPAWN * SPAN_Y_EFFECT_SPAWN) * 0.5f;

			//�Ίp���̊p�x��ݒ�
			g_aEffect_Spwan[nCntEnemy].fAngle = atan2f(SPAN_X_EFFECT_SPAWN, SPAN_Y_EFFECT_SPAWN);

			//�����x�����ݒ�
			g_aEffect_Spwan[nCntEnemy].nColorA = 30;

			////�����x�ύX����
			//pEnemy[nCntEnemy].bFinishEffect = false;

			break;
		}

		pVtx_Effect_Spawn += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Effect_Spawn->Unlock();
}

////************************************************
////�G�t�F�N�g���ŊJ�n����������n���֐�
////************************************************
//bool* Getinfo_Disappear_Effect(int nCnt)
//{
//	return &g_aEffect_Spwan[nCnt].bChangeColorA;
//}