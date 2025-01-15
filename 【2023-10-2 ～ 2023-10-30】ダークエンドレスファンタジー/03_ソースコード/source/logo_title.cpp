//************************************************
//
//�^�C�g�����S����[logo_title.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "logo_title.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Logo_Title = NULL;	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Logo_Title = NULL;	//���_�o�b�t�@�̃|�C���^
LOGO_TITLE g_aLogo_Title;	//�^�C�g�����S���

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Logo_Title()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LOGO_TITLE,
		&g_pTexture_Logo_Title);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Logo_Title,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Logo_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Logo_Title->Lock(0, 0, (void**)&pVtx_Logo_Title, 0);

	//���_���W�̏����ݒ�
	pVtx_Logo_Title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Logo_Title[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Logo_Title[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Logo_Title[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//������̊g�嗦(?)�̏����ݒ�
	pVtx_Logo_Title[0].rhw = 1.0f;
	pVtx_Logo_Title[1].rhw = 1.0f;
	pVtx_Logo_Title[2].rhw = 1.0f;
	pVtx_Logo_Title[3].rhw = 1.0f;

	//���_�J���[�̏����ݒ�
	pVtx_Logo_Title[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Logo_Title[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Logo_Title[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Logo_Title[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̏����ݒ�
	pVtx_Logo_Title[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Logo_Title[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Logo_Title[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Logo_Title[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Logo_Title->Unlock();

	//�w�i�\���̂̏��̏������Q
	g_aLogo_Title.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aLogo_Title.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aLogo_Title.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aLogo_Title.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aLogo_Title.fRadius[nCnt] = 0.0f;
	}
	g_aLogo_Title.fLength = 0.0f;
	g_aLogo_Title.fAngle = 0.0f;

	//�w�i�\���̂ɏ���t�^
	SetInfo_Logo_Title();

	//�ʒu�Ɋ�Â��|���S����W�J
	Update_Pos_Logo_Title();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Logo_Title(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexture_Logo_Title != NULL)
	{
		g_pTexture_Logo_Title->Release();
		g_pTexture_Logo_Title = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Logo_Title != NULL)
	{
		g_pVtxBuff_Logo_Title->Release();
		g_pVtxBuff_Logo_Title = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Logo_Title(void)
{

}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Logo_Title(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Logo_Title, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexture_Logo_Title);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//�^�C�g�����S�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Logo_Title(void)
{
	g_aLogo_Title.pos = D3DXVECTOR3(990.0f, 250.0f, 0.0f);
	g_aLogo_Title.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aLogo_Title.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aLogo_Title.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aLogo_Title.fRadius[0] = RADIUS_LOGO_TITLE_X;	//�w�i������
	g_aLogo_Title.fRadius[1] = RADIUS_LOGO_TITLE_Y;	//�w�i�c����
	g_aLogo_Title.fLength = sqrtf((g_aLogo_Title.fRadius[0] * g_aLogo_Title.fRadius[0]) + (g_aLogo_Title.fRadius[1] * g_aLogo_Title.fRadius[1]));
	g_aLogo_Title.fAngle = atan2f(g_aLogo_Title.fRadius[0] * 2.0f, g_aLogo_Title.fRadius[1] * 2.0f);
}

//************************************************
//�^�C�g�����S�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Logo_Title(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Logo_Title;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Logo_Title->Lock(0, 0, (void**)&pVtx_Logo_Title, 0);

	pVtx_Logo_Title[0].pos.x = g_aLogo_Title.pos.x + sinf(g_aLogo_Title.rot.z - (D3DX_PI - g_aLogo_Title.fAngle)) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[0].pos.y = g_aLogo_Title.pos.y + cosf(g_aLogo_Title.rot.z - (D3DX_PI - g_aLogo_Title.fAngle)) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[1].pos.x = g_aLogo_Title.pos.x + sinf(g_aLogo_Title.rot.z + (D3DX_PI - g_aLogo_Title.fAngle)) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[1].pos.y = g_aLogo_Title.pos.y + cosf(g_aLogo_Title.rot.z + (D3DX_PI - g_aLogo_Title.fAngle)) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[2].pos.x = g_aLogo_Title.pos.x + sinf(g_aLogo_Title.rot.z - g_aLogo_Title.fAngle) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[2].pos.y = g_aLogo_Title.pos.y + cosf(g_aLogo_Title.rot.z - g_aLogo_Title.fAngle) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[3].pos.x = g_aLogo_Title.pos.x + sinf(g_aLogo_Title.rot.z + g_aLogo_Title.fAngle) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[3].pos.y = g_aLogo_Title.pos.y + cosf(g_aLogo_Title.rot.z + g_aLogo_Title.fAngle) * g_aLogo_Title.fLength;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Logo_Title->Unlock();
}

//************************************************
//�^�C�g�����S�\���̂̃A�h���X��n��
//************************************************
LOGO_TITLE* GetInfo_Logo_Title(void)
{
	return &g_aLogo_Title;
}