//************************************************
//
//�u���b�N�p�[�e�B�N������[particle_block.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "particle_block.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Particle_Block = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Particle_Block = NULL;	//���_�o�b�t�@�̃|�C���^
PARTICLE_BLOCK g_aParticle_Block[AMOUNT_POLYGON_PARTICLE_BLOCK];	//�p�[�e�B�N���p�����i�[
float g_fLength_Particle_Block = 0.0f;	//�Ίp�������i�[
float g_fAngle_Particle_Block = 0.0f;	//�p�x�����i�[
int g_nCntPos = 0;

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Particle_Block()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PARTICLE_BLOCK,
		&g_pTexture_Particle_Block);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PARTICLE_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Particle_Block,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle_Block->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_BLOCK; nCnt++)
	{
		//���_���W�̏����ݒ�
		pVtx_Particle[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Particle[0].rhw = 1.0f;
		pVtx_Particle[1].rhw = 1.0f;
		pVtx_Particle[2].rhw = 1.0f;
		pVtx_Particle[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Particle[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Particle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Particle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Particle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Particle[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Particle += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle_Block->Unlock();

	//�\���̂̒��g��������
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_BLOCK; nCnt++)
	{
		g_aParticle_Block[nCnt].nStyle = 0;
		g_aParticle_Block[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Block[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Block[nCnt].moveB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Block[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Block[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle_Block[nCnt].fRadius = 0.0f;
		g_aParticle_Block[nCnt].nRemain = 0;
		g_aParticle_Block[nCnt].bUse = false;
		g_aParticle_Block[nCnt].fAngle = 0.0f;
	}

	//�p�x����ݒ�
	g_fAngle_Particle_Block = atan2f(RADIUS_PARTICLE_BLOCK * 2.0f, RADIUS_PARTICLE_BLOCK * 2.0f);

	g_nCntPos = 0;
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Particle_Block(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Particle_Block != NULL)
	{
		g_pTexture_Particle_Block->Release();
		g_pTexture_Particle_Block = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Particle_Block != NULL)
	{
		g_pVtxBuff_Particle_Block->Release();
		g_pVtxBuff_Particle_Block = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Particle_Block(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle_Block;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle_Block->Lock(0, 0, (void**)&pVtx_Particle_Block, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_BLOCK; nCnt++)
	{
		if (g_aParticle_Block[nCnt].bUse)
		{
			//�k��
			g_aParticle_Block[nCnt].fRadius -= CHANGE_SPD_RADIUS_PARTICLE_BLOCK;

			//���Ԃ�̖h�~
			if (g_aParticle_Block[nCnt].fRadius <= 0)
			{
				g_aParticle_Block[nCnt].fRadius = 0.0f;
			}

			//�ړ�
			g_aParticle_Block[nCnt].pos.x += g_aParticle_Block[nCnt].move.x * MOVE_SPD_POS_PARTICLE_BLOCK;
			g_aParticle_Block[nCnt].pos.y += g_aParticle_Block[nCnt].move.y * MOVE_SPD_POS_PARTICLE_BLOCK;

			//����Ƃ͕ʂɃu���b�N�̓����𓯊�
			g_aParticle_Block[nCnt].pos += g_aParticle_Block[nCnt].moveB;

			//��]
			g_aParticle_Block[nCnt].rot.z += g_aParticle_Block[nCnt].move.z;

			//���_��W�J����
			pVtx_Particle_Block[0].pos.x = g_aParticle_Block[nCnt].pos.x + sinf(g_aParticle_Block[nCnt].rot.z - (D3DX_PI - g_aParticle_Block[nCnt].fAngle)) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[0].pos.y = g_aParticle_Block[nCnt].pos.y + cosf(g_aParticle_Block[nCnt].rot.z - (D3DX_PI - g_aParticle_Block[nCnt].fAngle)) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[1].pos.x = g_aParticle_Block[nCnt].pos.x + sinf(g_aParticle_Block[nCnt].rot.z + (D3DX_PI - g_aParticle_Block[nCnt].fAngle)) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[1].pos.y = g_aParticle_Block[nCnt].pos.y + cosf(g_aParticle_Block[nCnt].rot.z + (D3DX_PI - g_aParticle_Block[nCnt].fAngle)) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[2].pos.x = g_aParticle_Block[nCnt].pos.x + sinf(g_aParticle_Block[nCnt].rot.z - g_aParticle_Block[nCnt].fAngle) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[2].pos.y = g_aParticle_Block[nCnt].pos.y + cosf(g_aParticle_Block[nCnt].rot.z - g_aParticle_Block[nCnt].fAngle) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[3].pos.x = g_aParticle_Block[nCnt].pos.x + sinf(g_aParticle_Block[nCnt].rot.z + g_aParticle_Block[nCnt].fAngle) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[3].pos.y = g_aParticle_Block[nCnt].pos.y + cosf(g_aParticle_Block[nCnt].rot.z + g_aParticle_Block[nCnt].fAngle) * g_aParticle_Block[nCnt].fRadius;

			g_aParticle_Block[nCnt].nRemain--;

			//�c�����Ԃ������Ȃ����Ƃ�
			if (g_aParticle_Block[nCnt].nRemain <= 0)
			{
				pVtx_Particle_Block[0].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Block[1].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Block[2].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Block[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

				g_aParticle_Block[nCnt].bUse = false;	//�g�p����𖳂���
			}

			pVtx_Particle_Block[0].col = g_aParticle_Block[nCnt].col;
			pVtx_Particle_Block[1].col = g_aParticle_Block[nCnt].col;
			pVtx_Particle_Block[2].col = g_aParticle_Block[nCnt].col;
			pVtx_Particle_Block[3].col = g_aParticle_Block[nCnt].col;

			//�u���b�N�̎�ޕς��Ă��������ǋC����������
			pVtx_Particle_Block[0].tex.x = 0.0f;
			pVtx_Particle_Block[1].tex.x = 0.333f;
			pVtx_Particle_Block[2].tex.x = 0.0f;
			pVtx_Particle_Block[3].tex.x = 0.333f;
		}

		pVtx_Particle_Block += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle_Block->Unlock();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Particle_Block(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Particle_Block, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Particle_Block);

	//�|���S���̕`��
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_BLOCK; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�p�[�e�B�N���̏���ݒ肷��֐�
//************************************************
void Setinfo_Particle_Block(D3DXVECTOR3 pos, D3DXVECTOR3 moveBlock)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Particle;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Particle_Block->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_BLOCK; nCnt++)
	{
		//�g�p����Ă��Ȃ��p�[�e�B�N�������m������
		if (!g_aParticle_Block[nCnt].bUse)
		{
			g_aParticle_Block[nCnt].nStyle = 0;
			g_aParticle_Block[nCnt].pos = pos;	//�ʒu��K���ɐݒ�

			switch (g_nCntPos)
			{
			case 0:

				g_aParticle_Block[nCnt].pos.y -= 100.0f;

				break;

			case 2:

				g_aParticle_Block[nCnt].pos.y += 100.0f;

				g_nCntPos = -1;

				break;
			}

			g_nCntPos++;

			//������ۂ��v�Z(�v���P�c)
			float fRandomX = (rand() % 314) * 0.01f;
			float fRandomY = (rand() % 314) * 0.01f;

			int nRondom = rand() % 2;

			nRondom == 0 ?
				0 :
				fRandomX *= -1.0f, fRandomY *= -1.0f;

			g_aParticle_Block[nCnt].move.x = sinf(D3DX_PI - fRandomX);			//�ړ��ʂ�K���ɐݒ�
			g_aParticle_Block[nCnt].move.y = cosf(D3DX_PI - fRandomY);			//�ړ��ʂ�K���ɐݒ�
			g_aParticle_Block[nCnt].move.z = (float)fRandomX * 0.1f;			//��]�ʂ�K���ɐݒ�
			g_aParticle_Block[nCnt].moveB = moveBlock;							//�u���b�N�̈ړ��ʂɓ���
			g_aParticle_Block[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���������i�[
			g_aParticle_Block[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);	//�F��K���ɐݒ�
			g_aParticle_Block[nCnt].fRadius = RADIUS_PARTICLE_BLOCK;			//���a��K���ɐݒ�
			g_aParticle_Block[nCnt].nRemain = REMAIN_TIME_PARTICLE_BLOCK;		//�c�����Ԃ�K���ɐݒ�
			g_aParticle_Block[nCnt].bUse = true;								//�g�p������o��
			g_aParticle_Block[nCnt].fAngle = g_fAngle_Particle_Block;			//�p�x���i�[

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Particle_Block->Unlock();
}