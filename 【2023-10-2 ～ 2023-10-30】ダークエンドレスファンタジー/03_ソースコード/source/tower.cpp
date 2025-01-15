//************************************************
//
//���Ώۏ���[tower.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "stage.h"
#include "tower.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Tower[AMOUNT_TEX_PLAYER] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Tower = NULL;	//���_�o�b�t�@�̃|�C���^
TOWER g_aTower;	//���Ώۏ��
static float g_F;	//�ėp��������

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Tower()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TOWER,
		&g_pTexture_Tower[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Tower,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tower;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Tower->Lock(0, 0, (void**)&pVtx_Tower, 0);

	//���_���W�̏����ݒ�
	pVtx_Tower[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Tower[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Tower[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Tower[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Tower[0].rhw = 1.0f;
	pVtx_Tower[1].rhw = 1.0f;
	pVtx_Tower[2].rhw = 1.0f;
	pVtx_Tower[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Tower[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Tower[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Tower[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Tower[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Tower[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Tower[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Tower[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Tower[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Tower->Unlock();

	//���Ώۍ\���̂̏��̏������Q
	g_aTower.nState = 0;
	g_aTower.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aTower.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aTower.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aTower.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aTower.nCntTex = 0;
	g_aTower.nCntPattern = 0;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aTower.fTexSpan[nCnt] = 0.0f;
		g_aTower.fRadius[nCnt] = 0.0f;
		g_aTower.fLength[nCnt] = 0.0f;
		g_aTower.fAngle[nCnt] = 0.0f;
	}
	g_aTower.nLife = 0;
	g_aTower.nCT = 0;

	g_F = 0.5f;

	//���Ώۍ\���̂ɏ���t�^
	SetInfo_Tower();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Tower(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEX_PLAYER; nCnt++)
	{
		if (g_pTexture_Tower[nCnt] != NULL)
		{
			g_pTexture_Tower[nCnt]->Release();
			g_pTexture_Tower[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Tower != NULL)
	{
		g_pVtxBuff_Tower->Release();
		g_pVtxBuff_Tower = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Tower(void)
{
	/*�f�o�b�O�p�_���[�W*/
	if (GetKeyboardTrigger(DIK_8))
	{
		//���C�t�����炷
		g_aTower.nLife--;
	}

	//�ݒu
	Update_Pos_Tower();

	//�F�ύX
	Update_Col_Tower();

	//�A�j���[�V����
	Update_Tex_Tower();
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Tower(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Tower, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Tower[0]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//���Ώۍ\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Tower(void)
{
	g_aTower.pos = D3DXVECTOR3(SCREEN_HALFWIDTH, 690.0f, 0.0f);
	g_aTower.fTexSpan[0] = 0.0f;
	g_aTower.fTexSpan[1] = SPAN_CHANGE_TEX_TOWER;
	g_aTower.fRadius[0] = RADIUS_TOWER_X;
	g_aTower.fRadius[1] = RADIUS_TOWER_Y;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			g_aTower.fLength[nCnt] = sqrtf((RADIUS_TOWER_X * RADIUS_TOWER_X) +
				((RADIUS_TOWER_Y * 2.0f) * (RADIUS_TOWER_Y * 2.0f)));
			g_aTower.fAngle[nCnt] = atan2f(RADIUS_TOWER_X * 2.0f, (RADIUS_TOWER_Y * 2.0f) * 2.0f);
			break;
		case 1:
			g_aTower.fLength[nCnt] = sqrtf((RADIUS_TOWER_X * RADIUS_TOWER_X));
			g_aTower.fAngle[nCnt] = atan2f(RADIUS_TOWER_X * 2.0f, 0.0f);
			break;
		}
	}
	g_aTower.nLife = AMOUNT_MAX_LIFE_TOWER;
}

//************************************************
//���Ώۂ̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Tower(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tower;

	//���W�ύX
	g_aTower.pos += g_aTower.move;

	ConvertInfo_Screen(&g_aTower.pos);

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Tower->Lock(0, 0, (void**)&pVtx_Tower, 0);

	pVtx_Tower[0].pos.x = g_aTower.pos.x + sinf(g_aTower.rot.z - (D3DX_PI - g_aTower.fAngle[0])) * g_aTower.fLength[0];
	pVtx_Tower[0].pos.y = g_aTower.pos.y + cosf(g_aTower.rot.z - (D3DX_PI - g_aTower.fAngle[0])) * g_aTower.fLength[0];
	pVtx_Tower[1].pos.x = g_aTower.pos.x + sinf(g_aTower.rot.z + (D3DX_PI - g_aTower.fAngle[0])) * g_aTower.fLength[0];
	pVtx_Tower[1].pos.y = g_aTower.pos.y + cosf(g_aTower.rot.z + (D3DX_PI - g_aTower.fAngle[0])) * g_aTower.fLength[0];
	pVtx_Tower[2].pos.x = g_aTower.pos.x + sinf(g_aTower.rot.z - g_aTower.fAngle[1]) * g_aTower.fLength[1];
	pVtx_Tower[2].pos.y = g_aTower.pos.y + cosf(g_aTower.rot.z - g_aTower.fAngle[1]) * g_aTower.fLength[1];
	pVtx_Tower[3].pos.x = g_aTower.pos.x + sinf(g_aTower.rot.z + g_aTower.fAngle[1]) * g_aTower.fLength[1];
	pVtx_Tower[3].pos.y = g_aTower.pos.y + cosf(g_aTower.rot.z + g_aTower.fAngle[1]) * g_aTower.fLength[1];

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Tower->Unlock();
}

//************************************************
//���Ώۂ̐F��ύX����֐�
//************************************************
void Update_Col_Tower(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tower;

	if (g_aTower.nCT > 0)
	{
		g_aTower.nCT--;

		g_aTower.col.r = 0.5f;
		g_aTower.col.g = 0.5f;

		//���ŗp1
		g_aTower.col.a -= g_F;
		if (g_aTower.col.a < 0.0f || g_aTower.col.a > 1.0f)
		{
			g_F *= -1.0f;
		}
	}
	else
	{
		g_aTower.col.r = 1.0f;
		g_aTower.col.g = 1.0f;
		g_aTower.col.a = 1.0f;
	}

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Tower->Lock(0, 0, (void**)&pVtx_Tower, 0);

	pVtx_Tower[0].col = g_aTower.col;
	pVtx_Tower[1].col = g_aTower.col;
	pVtx_Tower[2].col = g_aTower.col;
	pVtx_Tower[3].col = g_aTower.col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Tower->Unlock();
}

//************************************************
//���Ώۂ̃e�N�X�`���𓮂����֐�
//************************************************
void Update_Tex_Tower(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Tower;

	//�e�N�X�`����ύX
	g_aTower.nCntTex++;
	if (g_aTower.nCntTex > SPD_CHANGE_TEX_TOWER)
	{
		g_aTower.nCntTex = 0;
		g_aTower.nCntPattern++;
		g_aTower.fTexSpan[0] += SPAN_CHANGE_TEX_TOWER;
		g_aTower.fTexSpan[1] += SPAN_CHANGE_TEX_TOWER;
		if (g_aTower.nCntPattern >= AMOUNT_STYLE_TEX_TOWER)
		{
			g_aTower.nCntPattern = 0;
			g_aTower.fTexSpan[0] = 0;
			g_aTower.fTexSpan[1] = SPAN_CHANGE_TEX_TOWER;
		}
	}

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Tower->Lock(0, 0, (void**)&pVtx_Tower, 0);

	pVtx_Tower[0].tex = D3DXVECTOR2(g_aTower.fTexSpan[0], 0.0f);
	pVtx_Tower[1].tex = D3DXVECTOR2(g_aTower.fTexSpan[1], 0.0f);
	pVtx_Tower[2].tex = D3DXVECTOR2(g_aTower.fTexSpan[0], 1.0f);
	pVtx_Tower[3].tex = D3DXVECTOR2(g_aTower.fTexSpan[1], 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Tower->Unlock();
}

//************************************************
//���Ώۂ̍\���̂̃A�h���X��n��
//************************************************
TOWER* GetInfo_Tower(void)
{
	return &g_aTower;
}