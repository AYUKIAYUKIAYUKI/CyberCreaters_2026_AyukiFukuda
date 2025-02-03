//************************************************
//
//�G����[enemy.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "attack_box_enemy.h"
#include "camera.h"
#include "enemy.h"
#include "particle.h"
#include "player.h"
#include "score.h"
#include "stage.h"
#include "tower.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexture_Enemy[AMOUNT_TEX_ENEMY] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Enemy = NULL;	//���_�o�b�t�@�̃|�C���^
ENEMY g_aEnemy[AMOUNT_POLYGON_ENEMY];	//�G���
ENEMY_BOX g_aEnemy_Box[ENEMY_MAX][AMOUNT_POLYGON_ENEMY];	//�G�{�b�N�X���
int g_nCTspawn;	//���W�F�l�L���X�g�^�C��

//************************************************
//�|���S�������������֐�
//************************************************
void Init_Enemy()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_00_MOVE,
		&g_pTexture_Enemy[0]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_00_ATK,
		&g_pTexture_Enemy[1]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_00_HURT,
		&g_pTexture_Enemy[2]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_00_DEATH,
		&g_pTexture_Enemy[3]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_01_IDLE,
		&g_pTexture_Enemy[4]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_01_MOVE,
		&g_pTexture_Enemy[5]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_01_ATK,
		&g_pTexture_Enemy[6]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_01_HURT,
		&g_pTexture_Enemy[7]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_01_DEATH,
		&g_pTexture_Enemy[8]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_02_IDLE,
		&g_pTexture_Enemy[9]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_02_MOVE,
		&g_pTexture_Enemy[10]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_02_ATK,
		&g_pTexture_Enemy[11]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_02_HURT,
		&g_pTexture_Enemy[12]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_02_DEATH,
		&g_pTexture_Enemy[13]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_03_IDLE,
		&g_pTexture_Enemy[14]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_03_MOVE,
		&g_pTexture_Enemy[15]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_03_ATK,
		&g_pTexture_Enemy[16]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_03_HURT,
		&g_pTexture_Enemy[17]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_03_DEATH,
		&g_pTexture_Enemy[18]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_IDLE,
		&g_pTexture_Enemy[19]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_MOVE,
		&g_pTexture_Enemy[20]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_ATK,
		&g_pTexture_Enemy[21]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_HURT,
		&g_pTexture_Enemy[22]);

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_DEATH,
		&g_pTexture_Enemy[23]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Enemy,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy;

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		//���_���W�̏����ݒ�
		pVtx_Enemy[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Enemy[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Enemy[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Enemy[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//������̊g�嗦(?)�̏����ݒ�
		pVtx_Enemy[0].rhw = 1.0f;
		pVtx_Enemy[1].rhw = 1.0f;
		pVtx_Enemy[2].rhw = 1.0f;
		pVtx_Enemy[3].rhw = 1.0f;

		//���_�J���[�̏����ݒ�
		pVtx_Enemy[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Enemy[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Enemy[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Enemy[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx_Enemy[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Enemy[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Enemy[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Enemy[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Enemy += AMOUNT_VTX;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Enemy->Unlock();

	//�G�\���̂̏��̏������Q
	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		g_aEnemy[i].bUse = false;
		g_aEnemy[i].nStyle = 0;
		g_aEnemy[i].nState = 0;
		g_aEnemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEnemy[i].LR = 0;
		g_aEnemy[i].nCntTex = 0;
		g_aEnemy[i].nCntPattern = 0;
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aEnemy[i].fTexSpan[nCnt] = 0.0f;
			g_aEnemy[i].fRadius[nCnt] = 0.0f;
			g_aEnemy[i].fLength[nCnt] = 0.0f;
			g_aEnemy[i].fAngle[nCnt] = 0.0f;
		}
		g_aEnemy[i].fDisappear = 1.0f;
		g_aEnemy[i].nLife = 0;
		g_aEnemy[i].nCT = 0;
		g_aEnemy[i].bLockonP = false;
	}

	//�G�{�b�N�X�̏�����
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
		{
			for (int nCntHold = 0; nCntHold < 2; nCntHold++)
			{
				g_aEnemy_Box[i][nCnt].fRadius_Hold[nCntHold];
				g_aEnemy_Box[i][nCnt].fLength_Hold[nCntHold];
				g_aEnemy_Box[i][nCnt].fAngle_Hold[nCntHold];
			}
		}
	}

	g_nCTspawn = AMOUN_RESPAWN_CT;

	//�G�p�����ڃ{�b�N�X�̐���
	CalcSize_Enemy_Box();
}

//************************************************
//�|���S���I�������֐�
//************************************************
void Uninit_Enemy(void)
{
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < AMOUNT_TEX_ENEMY; nCnt++)
	{
		if (g_pTexture_Enemy[nCnt] != NULL)
		{
			g_pTexture_Enemy[nCnt]->Release();
			g_pTexture_Enemy[nCnt] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuff_Enemy != NULL)
	{
		g_pVtxBuff_Enemy->Release();
		g_pVtxBuff_Enemy = NULL;
	}
}

//************************************************
//�|���S���X�V�����֐�
//************************************************
void Update_Enemy(void)
{
	//�t���[���J�E���g
	g_nCTspawn++;

	//��莞�Ԍo�߂ŐV���ȓG���o��������
	if (g_nCTspawn >= AMOUN_RESPAWN_CT)
	{
		SetInfo_Enemy();
		g_nCTspawn = 0;
	}

	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		if (g_aEnemy[i].bUse)
		{
			//�ړ�����
			Update_Pos_Enemy(i);

			//���ŏ���
			Disapper_Enemy(i);
		}
	}
}

//************************************************
//�|���S���`�揈���֐�
//************************************************
void Draw_Enemy(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�ւ̃|�C���^�擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuff_Enemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		//�G�̎�ނɂ���đI��
		switch (g_aEnemy[i].nStyle)
		{
		case ENEMY_00:
			//�G�̏�Ԃɂ���Ă���ɑI��
			switch (g_aEnemy[i].nState)
			{
			case ENEMY_00_STATE_MOVE:
				pDevice->SetTexture(0, g_pTexture_Enemy[0]);
				break;
			case ENEMY_00_STATE_ATK:
				pDevice->SetTexture(0, g_pTexture_Enemy[1]);
				break;
			case ENEMY_00_STATE_HURT:
				pDevice->SetTexture(0, g_pTexture_Enemy[2]);
				break;
			case ENEMY_00_STATE_DEATH:
				pDevice->SetTexture(0, g_pTexture_Enemy[3]);
				break;
			}
			break;
		case ENEMY_01:
			switch (g_aEnemy[i].nState)
			{
			case ENEMY_01_STATE_IDLE:
				pDevice->SetTexture(0, g_pTexture_Enemy[4]);
				break;
			case ENEMY_01_STATE_MOVE:
				pDevice->SetTexture(0, g_pTexture_Enemy[5]);
				break;
			case ENEMY_01_STATE_ATK:
				pDevice->SetTexture(0, g_pTexture_Enemy[6]);
				break;
			case ENEMY_01_STATE_HURT:
				pDevice->SetTexture(0, g_pTexture_Enemy[7]);
				break;
			case ENEMY_01_STATE_DEATH:
				pDevice->SetTexture(0, g_pTexture_Enemy[8]);
				break;
			}
			break;
		case ENEMY_02:
			switch (g_aEnemy[i].nState)
			{
			case ENEMY_02_STATE_IDLE:
				pDevice->SetTexture(0, g_pTexture_Enemy[9]);
				break;
			case ENEMY_02_STATE_MOVE:
				pDevice->SetTexture(0, g_pTexture_Enemy[10]);
				break;
			case ENEMY_02_STATE_ATK:
				pDevice->SetTexture(0, g_pTexture_Enemy[11]);
				break;
			case ENEMY_02_STATE_HURT:
				pDevice->SetTexture(0, g_pTexture_Enemy[12]);
				break;
			case ENEMY_02_STATE_DEATH:
				pDevice->SetTexture(0, g_pTexture_Enemy[13]);
				break;
			}
			break;
		case ENEMY_03:
			switch (g_aEnemy[i].nState)
			{
			case ENEMY_03_STATE_IDLE:
				pDevice->SetTexture(0, g_pTexture_Enemy[14]);
				break;
			case ENEMY_03_STATE_MOVE:
				pDevice->SetTexture(0, g_pTexture_Enemy[15]);
				break;
			case ENEMY_03_STATE_ATK:
				pDevice->SetTexture(0, g_pTexture_Enemy[16]);
				break;
			case ENEMY_03_STATE_HURT:
				pDevice->SetTexture(0, g_pTexture_Enemy[17]);
				break;
			case ENEMY_03_STATE_DEATH:
				pDevice->SetTexture(0, g_pTexture_Enemy[18]);
				break;
			}
			break;
		case ENEMY_04:
			switch (g_aEnemy[i].nState)
			{
			case ENEMY_04_STATE_IDLE:
				pDevice->SetTexture(0, g_pTexture_Enemy[19]);
				break;
			case ENEMY_04_STATE_MOVE:
				pDevice->SetTexture(0, g_pTexture_Enemy[20]);
				break;
			case ENEMY_04_STATE_ATK:
				pDevice->SetTexture(0, g_pTexture_Enemy[21]);
				break;
			case ENEMY_04_STATE_HURT:
				pDevice->SetTexture(0, g_pTexture_Enemy[22]);
				break;
			case ENEMY_04_STATE_DEATH:
				pDevice->SetTexture(0, g_pTexture_Enemy[23]);
				break;
			}
			break;
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//�G�̒��_�T�C�Y���Z�o�֐�
//************************************************
void CalcSize_Enemy_Box(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		switch (i)
		{
		case ENEMY_00:
			for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
			{
				switch (nCnt)
				{
				case ENEMY_00_STATE_MOVE:
					//�Ίp���̒���
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((175.0f * 175.0f) +
						(175.0f * 175.0f));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = g_aEnemy_Box[i][nCnt].fLength_Hold[0];

					//�Ίp���̊p�x
					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(175.0f * 2.0f, 175.0f * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = g_aEnemy_Box[i][nCnt].fAngle_Hold[0];
					break;
				case ENEMY_00_STATE_ATK:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((175.0f * 175.0f) +
						(175.0f * 175.0f));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = g_aEnemy_Box[i][nCnt].fLength_Hold[0];

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(175.0f * 2.0f, 175.0f * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = g_aEnemy_Box[i][nCnt].fAngle_Hold[0];
					break;
				case ENEMY_00_STATE_HURT:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((175.0f * 175.0f) +
						(175.0f * 175.0f));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = g_aEnemy_Box[i][nCnt].fLength_Hold[0];

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(175.0f * 2.0f, 175.0f * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = g_aEnemy_Box[i][nCnt].fAngle_Hold[0];
					break;
				case ENEMY_00_STATE_DEATH:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((175.0f * 175.0f) +
						(175.0f * 175.0f));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = g_aEnemy_Box[i][nCnt].fLength_Hold[0];

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(175.0f * 2.0f, 175.0f * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = g_aEnemy_Box[i][nCnt].fAngle_Hold[0];
					break;
				}
			}
			break;
		case ENEMY_01:
			for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
			{
				switch (nCnt)
				{
				case ENEMY_01_STATE_IDLE:
					//�Ίp���̒���
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((200.0f * 200.0f) +
						((50.0f * 2.0f) * (50.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(200.0f * 200.0f);

					//�Ίp���̊p�x
					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(200.0f * 2.0f, (50.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(200.0f * 2.0f, 0.0f);
					break;
				case ENEMY_01_STATE_MOVE:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((200.0f * 200.0f) +
						((50.0f * 2.0f) * (50.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(200.0f * 200.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(200.0f * 2.0f, (50.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(200.0f * 2.0f, 0.0f);
					break;
				case ENEMY_01_STATE_ATK:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((200.0f * 200.0f) +
						((50.0f * 2.0f) * (50.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(200.0f * 200.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(200.0f * 2.0f, (50.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(200.0f * 2.0f, 0.0f);
					break;
				case ENEMY_01_STATE_HURT:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((200.0f * 200.0f) +
						((50.0f * 2.0f) * (50.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(200.0f * 200.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(200.0f * 2.0f, (50.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(200.0f * 2.0f, 0.0f);
					break;
				case ENEMY_01_STATE_DEATH:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((200.0f * 200.0f) +
						((50.0f * 2.0f) * (50.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(200.0f * 200.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(200.0f * 2.0f, (50.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(200.0f * 2.0f, 0.0f);
					break;
				}
			}
			break;
		case ENEMY_02:
			for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
			{
				switch (nCnt)
				{
				case ENEMY_02_STATE_IDLE:
					//�Ίp���̒���
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((150.0f * 150.0f) +
						((40.0f * 2.0f) * (40.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(150.0f * 150.0f);

					//�Ίp���̊p�x
					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(150.0f * 2.0f, (40.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(150.0f * 2.0f, 0.0f);
					break;
				case ENEMY_02_STATE_MOVE:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((150.0f * 150.0f) +
						((40.0f * 2.0f) * (40.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(150.0f * 150.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(150.0f * 2.0f, (40.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(150.0f * 2.0f, 0.0f);
					break;
				case ENEMY_02_STATE_ATK:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((150.0f * 150.0f) +
						((40.0f * 2.0f) * (40.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(150.0f * 150.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(150.0f * 2.0f, (40.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(150.0f * 2.0f, 0.0f);
					break;
				case ENEMY_02_STATE_HURT:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((150.0f * 150.0f) +
						((40.0f * 2.0f) * (40.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(150.0f * 150.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(150.0f * 2.0f, (40.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(150.0f * 2.0f, 0.0f);
					break;
				case ENEMY_02_STATE_DEATH:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((150.0f * 150.0f) +
						((40.0f * 2.0f) * (40.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(150.0f * 150.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(150.0f * 2.0f, (40.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(150.0f * 2.0f, 0.0f);
					break;
				}
			}
			break;
		case ENEMY_03:
			for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
			{
				switch (nCnt)
				{
				case ENEMY_03_STATE_IDLE:
					//�Ίp���̒���
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((160.0f * 160.0f) +
						((60.0f * 2.0f) * (60.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(160.0f * 160.0f);

					//�Ίp���̊p�x
					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(160.0f * 2.0f, (60.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(160.0f * 2.0f, 0.0f);
					break;
				case ENEMY_03_STATE_MOVE:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((160.0f * 160.0f) +
						((60.0f * 2.0f) * (60.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(160.0f * 160.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(160.0f * 2.0f, (60.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(160.0f * 2.0f, 0.0f);
					break;
				case ENEMY_03_STATE_ATK:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((160.0f * 160.0f) +
						((60.0f * 2.0f) * (60.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(160.0f * 160.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(160.0f * 2.0f, (60.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(160.0f * 2.0f, 0.0f);
					break;
				case ENEMY_03_STATE_HURT:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((160.0f * 160.0f) +
						((60.0f * 2.0f) * (60.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(160.0f * 160.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(160.0f * 2.0f, (60.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(160.0f * 2.0f, 0.0f);
					break;
				case ENEMY_03_STATE_DEATH:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((160.0f * 160.0f) +
						((60.0f * 2.0f) * (60.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(160.0f * 160.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(160.0f * 2.0f, (60.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(160.0f * 2.0f, 0.0f);
					break;
				}
			}
			break;
		case ENEMY_04:
			for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
			{
				switch (nCnt)
				{
				case ENEMY_04_STATE_IDLE:
					//�Ίp���̒���
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((100.0f * 100.0f) +
						((55.0f * 2.0f) * (55.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(100.0f * 100.0f);

					//�Ίp���̊p�x
					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(100.0f * 2.0f, (55.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(100.0f * 2.0f, 0.0f);
					break;
				case ENEMY_04_STATE_MOVE:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((100.0f * 100.0f) +
						((55.0f * 2.0f) * (55.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(100.0f * 100.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(100.0f * 2.0f, (55.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(100.0f * 2.0f, 0.0f);
					break;
				case ENEMY_04_STATE_ATK:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((100.0f * 100.0f) +
						((55.0f * 2.0f) * (55.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(100.0f * 100.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(100.0f * 2.0f, (55.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(100.0f * 2.0f, 0.0f);
					break;
				case ENEMY_04_STATE_HURT:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((100.0f * 100.0f) +
						((55.0f * 2.0f) * (55.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(100.0f * 100.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(100.0f * 2.0f, (55.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(100.0f * 2.0f, 0.0f);
					break;
				case ENEMY_04_STATE_DEATH:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((100.0f * 100.0f) +
						((55.0f * 2.0f) * (55.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(100.0f * 100.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(100.0f * 2.0f, (55.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(100.0f * 2.0f, 0.0f);
					break;
				}
			}
			break;
		}
	}
}

//************************************************
//�G�\���̂̏���ݒ肷��֐�
//************************************************
void SetInfo_Enemy(void)
{
	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		//�󂫂�����
		if (!g_aEnemy[i].bUse)
		{
			TOWER* pTower = GetInfo_Tower();
			int R = 0, YR = 0;
			float fReverse = 0.0f;

			//�Œ�
			g_aEnemy[i].bUse = true;

			//��ނ͂Ȃɂ��ȁH
			int nStyle = rand() % 10;

			//�}�W�œK���ɐU��킯
			if (nStyle == 0 || nStyle == 5)
			{
				g_aEnemy[i].nStyle = ENEMY_00;
			}
			else if (nStyle == 1 || nStyle == 6)
			{
				g_aEnemy[i].nStyle = ENEMY_01;
			}
			else if (nStyle == 2 || nStyle == 7)
			{
				g_aEnemy[i].nStyle = ENEMY_02;
			}
			else if (nStyle == 3 || nStyle == 8)
			{
				g_aEnemy[i].nStyle = ENEMY_03;
			}
			else if (nStyle == 4)
			{
				g_aEnemy[i].nStyle = ENEMY_04;
			}

			//�o���������ނɍ��킹�Đݒ蕪��
			switch (g_aEnemy[i].nStyle)
			{
			case ENEMY_00:

				//�����_���A��������ނɂ���Ă�����x�Еz�͍��ʉ�
				R = rand() % 2;
				YR = rand() % 10;
				fReverse = 1.0f;
				R == 1 ? 0 : fReverse *= -1.0f;
				g_aEnemy[i].pos = D3DXVECTOR3(pTower->pos.x + (2100.0f * fReverse), -210 + (150.0f * (float)YR), 0.0f);
				g_aEnemy[i].oldpos = g_aEnemy[i].pos;

				//���������͈ʒu���猈��
				g_aEnemy[i].LR = R;

				//�e�N�X�`�����͎�ނɈˑ�
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_00;

				//�����蔻��͂قړ����ɒ���
				g_aEnemy[i].fRadius[0] = RADIUS_ENEMY_X;
				g_aEnemy[i].fRadius[1] = RADIUS_ENEMY_Y;

				//�����ڃ{�b�N�X����ނɈˑ�
				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[ENEMY_00][ENEMY_00_STATE_MOVE].fLength_Hold[nCnt];
					g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[ENEMY_00][ENEMY_00_STATE_MOVE].fAngle_Hold[nCnt];
				}

				//���C�t����ނɍ��킹�Ė���Œ�
				g_aEnemy[i].nLife = AMOUNT_MAX_LIFE_ENEMY_00;

				/****************�ȉ����̃t�H�[�}�b�g�ŕ���**************/
				break;
			case ENEMY_01:

				R = rand() % 2;
				YR = rand() % 10;
				fReverse = 1.0f;
				R == 1 ? 0 : fReverse *= -1.0f;
				g_aEnemy[i].pos = D3DXVECTOR3(pTower->pos.x + ((990.0f + (YR * 100.0f)) * fReverse), -100.0f, 0.0f);
				g_aEnemy[i].oldpos = g_aEnemy[i].pos;

				g_aEnemy[i].LR = R;

				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_01;

				g_aEnemy[i].fRadius[0] = 40.0f;
				g_aEnemy[i].fRadius[1] = 40.0f;

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[ENEMY_01][ENEMY_01_STATE_IDLE].fLength_Hold[nCnt];
					g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[ENEMY_01][ENEMY_01_STATE_IDLE].fAngle_Hold[nCnt];
				}

				g_aEnemy[i].nLife = AMOUNT_MAX_LIFE_ENEMY_01;

				break;
			case ENEMY_02:

				R = rand() % 2;
				YR = rand() % 10;
				fReverse = 1.0f;
				R == 1 ? 0 : fReverse *= -1.0f;
				g_aEnemy[i].pos = D3DXVECTOR3(pTower->pos.x + ((990.0f + (YR * 100.0f)) * fReverse), -100.0f, 0.0f);
				g_aEnemy[i].oldpos = g_aEnemy[i].pos;

				g_aEnemy[i].LR = R;

				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_02;

				g_aEnemy[i].fRadius[0] = 30.0f;
				g_aEnemy[i].fRadius[1] = 30.0f;

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[ENEMY_02][ENEMY_02_STATE_IDLE].fLength_Hold[nCnt];
					g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[ENEMY_02][ENEMY_02_STATE_IDLE].fAngle_Hold[nCnt];
				}

				g_aEnemy[i].nLife = AMOUNT_MAX_LIFE_ENEMY_02;

				break;
			case ENEMY_03:

				R = rand() % 2;
				YR = rand() % 10;
				fReverse = 1.0f;
				R == 1 ? 0 : fReverse *= -1.0f;
				g_aEnemy[i].pos = D3DXVECTOR3(pTower->pos.x + ((990.0f + (YR * 30.0f)) * fReverse), -100.0f, 0.0f);
				g_aEnemy[i].oldpos = g_aEnemy[i].pos;

				g_aEnemy[i].LR = R;

				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_03;

				g_aEnemy[i].fRadius[0] = 40.0f;
				g_aEnemy[i].fRadius[1] = 50.0f;

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[ENEMY_03][ENEMY_03_STATE_IDLE].fLength_Hold[nCnt];
					g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[ENEMY_03][ENEMY_03_STATE_IDLE].fAngle_Hold[nCnt];
				}

				g_aEnemy[i].nLife = AMOUNT_MAX_LIFE_ENEMY_03;

				break;
			case ENEMY_04:

				R = rand() % 2;
				YR = rand() % 10;
				fReverse = 1.0f;
				R == 1 ? 0 : fReverse *= -1.0f;
				g_aEnemy[i].pos = D3DXVECTOR3(pTower->pos.x + ((990.0f + (YR * 30.0f)) * fReverse), -100.0f, 0.0f);
				g_aEnemy[i].oldpos = g_aEnemy[i].pos;

				g_aEnemy[i].LR = R;

				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_04;

				g_aEnemy[i].fRadius[0] = 40.0f;
				g_aEnemy[i].fRadius[1] = 40.0f;

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[ENEMY_04][ENEMY_04_STATE_IDLE].fLength_Hold[nCnt];
					g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[ENEMY_04][ENEMY_04_STATE_IDLE].fAngle_Hold[nCnt];
				}

				g_aEnemy[i].nLife = AMOUNT_MAX_LIFE_ENEMY_04;

				break;
			}

			//1�̏o���������烋�[�v�I��
			break;
		}
	}
}

//************************************************
//�G�̈ʒu��ݒ肷��֐�
//************************************************
void Update_Pos_Enemy(int i)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy;

	TOWER* pTower = GetInfo_Tower();

	//�O��̈ʒu��ێ�
	g_aEnemy[i].oldpos = g_aEnemy[i].pos;

	//�d��
	if (g_aEnemy[i].nStyle != ENEMY_00 && g_aEnemy[i].nStyle != ENEMY_03)
	{
		//�G�͂ӂ���
		g_aEnemy[i].move.y = g_aEnemy[i].move.y + (MOVE_SPD_GRAVITY_Y * 0.25f);
	}
	else if (g_aEnemy[i].nStyle == ENEMY_03)
	{
		g_aEnemy[i].move.y = g_aEnemy[i].move.y + (MOVE_SPD_GRAVITY_Y * 0.1f);
	}

	//�ړ��ʐݒ�
	switch (g_aEnemy[i].nStyle)
	{
	case ENEMY_00:

		//��e���̓m�b�N�o�b�N��D�悷�邽�߈ړ��ʂ̌Œ���X���[
		if (g_aEnemy[i].nState != ENEMY_00_STATE_HURT)
		{
			g_aEnemy[i].nCT > 0 ? g_aEnemy[i].nCT-- : 0;

			//�^���[�ւ̌������o��
			D3DXVECTOR3 Vector = pTower->pos - g_aEnemy[i].pos;

			//�^���[�ւ̕��������m
			if (Vector.x > 0)
			{
				//������x�߂Â��Ǝ~�܂�
				Vector.x < pTower->fRadius[0] * 1.5f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = 3.0f, g_aEnemy[i].LR = 0;
			}
			else if (Vector.x < 0)
			{
				Vector.x > -pTower->fRadius[0] * 1.5f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = -3.0f, g_aEnemy[i].LR = 1;
			}

			if (g_aEnemy[i].pos.y < pTower->pos.y - 100.0f)
			{
				g_aEnemy[i].move.y = 0.75f;
			}
			else if (g_aEnemy[i].pos.y > pTower->pos.y - 80.0f)
			{
				g_aEnemy[i].move.y = -0.75f;
			}

			//�v�Z�p�ɕϊ�
			Vector.x < 0.0f ? Vector.x *= -1.0f : 0;
			Vector.y < 0.0f ? Vector.y *= -1.0f : 0;

			//�^���[�ɋ߂Â��Ă��āA�U����ԂłȂ�HP������A�L���X�g�^�C���������ς݂ł���
			if (Vector.x < pTower->fRadius[1] &&
				Vector.y < pTower->fRadius[1] &&
				g_aEnemy[i].nState != ENEMY_00_STATE_ATK &&
				g_aEnemy[i].nLife > 0 && g_aEnemy[i].nCT <= 0)
			{
				//�����ڃ{�b�N�X��������
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern = 0;
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_ATK_ENEMY_00;
				//�U����ԂɕύX
				g_aEnemy[i].nState = ENEMY_00_STATE_ATK;
			}
		}
		//���S��
		else if (g_aEnemy[i].nState == ENEMY_00_STATE_DEATH)
		{
			g_aEnemy[i].move.x = 0.0f;
			g_aEnemy[i].move.y = 2.0f;
		}

		break;
	case ENEMY_01:

		//��e���̓m�b�N�o�b�N��D�悷�邽�߈ړ��ʂ̌Œ���X���[
		if (g_aEnemy[i].nState != ENEMY_01_STATE_HURT && g_aEnemy[i].nState != ENEMY_01_STATE_DEATH)
		{
			g_aEnemy[i].nCT > 0 ? g_aEnemy[i].nCT-- : 0;

			//�^���[�ւ̌������o��
			D3DXVECTOR3 Vector = pTower->pos - g_aEnemy[i].pos;

			//�^���[�ւ̕��������m
			if (Vector.x > 0)
			{
				//������x�߂Â��Ǝ~�܂�
				Vector.x < pTower->fRadius[0] * 1.5f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = 3.0f, g_aEnemy[i].LR = 0;
			}
			else if (Vector.x < 0)
			{
				Vector.x > -pTower->fRadius[0] * 1.5f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = -3.0f, g_aEnemy[i].LR = 1;
			}

			//�U�����͑ҋ@��ړ��̕��ʂ𖳎�
			if (g_aEnemy[i].nState != ENEMY_01_STATE_ATK)
			{
				if (g_aEnemy[i].move.x == 0.0f)
				{
					//����܂őҋ@����Ȃ��Ƃ��̓{�b�N�X������
					if (g_aEnemy[i].nState != ENEMY_01_STATE_IDLE)
					{
						//�����ڃ{�b�N�X��������
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_01;
					}
					//�ړ��ʖ����ŌŒ�
					g_aEnemy[i].nState = ENEMY_01_STATE_IDLE;
				}
				else
				{
					//����܂ňړ�����Ȃ��Ƃ��̓{�b�N�X������
					if (g_aEnemy[i].nState != ENEMY_01_STATE_MOVE)
					{
						//�����ڃ{�b�N�X��������
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_01;
					}
					g_aEnemy[i].nState = ENEMY_01_STATE_MOVE;
				}
			}

			//�v�Z�p�ɕϊ�
			Vector.x < 0.0f ? Vector.x *= -1.0f : 0;

			//�^���[�ɋ߂Â��Ă��āA�U����ԂłȂ�HP������A�L���X�g�^�C���������ς݂ł���
			if (Vector.x < pTower->fRadius[1] &&
				g_aEnemy[i].nState != ENEMY_01_STATE_ATK &&
				g_aEnemy[i].nLife > 0 && g_aEnemy[i].nCT <= 0)
			{
				//�����ڃ{�b�N�X��������
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern = 0;
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_ATK_ENEMY_01;
				//�U����ԂɕύX
				g_aEnemy[i].nState = ENEMY_01_STATE_ATK;
			}
		}
		//���S��
		else if (g_aEnemy[i].nState == ENEMY_01_STATE_DEATH)
		{
			g_aEnemy[i].move.x = 0.0f;
			g_aEnemy[i].move.y = 2.0f;
		}

		break;
	case ENEMY_02:

		//��e���̓m�b�N�o�b�N��D�悷�邽�߈ړ��ʂ̌Œ���X���[
		if (g_aEnemy[i].nState != ENEMY_02_STATE_HURT && g_aEnemy[i].nState != ENEMY_02_STATE_DEATH)
		{
			g_aEnemy[i].nCT > 0 ? g_aEnemy[i].nCT-- : 0;

			//�^���[�ւ̌������o��
			D3DXVECTOR3 Vector = pTower->pos - g_aEnemy[i].pos;

			//�^���[�ւ̕��������m
			if (Vector.x > 0)
			{
				//������x�߂Â��Ǝ~�܂�
				Vector.x < pTower->fRadius[0] * 1.4f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = 6.0f, g_aEnemy[i].LR = 0;
			}
			else if (Vector.x < 0)
			{
				Vector.x > -pTower->fRadius[0] * 1.4f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = -6.0f, g_aEnemy[i].LR = 1;
			}

			//�U�����͑ҋ@��ړ��̕��ʂ𖳎�
			if (g_aEnemy[i].nState != ENEMY_02_STATE_ATK)
			{
				if (g_aEnemy[i].move.x == 0.0f)
				{
					//����܂őҋ@����Ȃ��Ƃ��̓{�b�N�X������
					if (g_aEnemy[i].nState != ENEMY_02_STATE_IDLE)
					{
						//�����ڃ{�b�N�X��������
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_02;
					}
					//�ړ��ʖ����ŌŒ�
					g_aEnemy[i].nState = ENEMY_02_STATE_IDLE;
				}
				else
				{
					//����܂ňړ�����Ȃ��Ƃ��̓{�b�N�X������
					if (g_aEnemy[i].nState != ENEMY_02_STATE_MOVE)
					{
						//�����ڃ{�b�N�X��������
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_02;
					}
					g_aEnemy[i].nState = ENEMY_02_STATE_MOVE;
				}
			}

			//�v�Z�p�ɕϊ�
			Vector.x < 0.0f ? Vector.x *= -1.0f : 0;

			//�^���[�ɋ߂Â��Ă��āA�U����ԂłȂ�HP������A�L���X�g�^�C���������ς݂ł���
			if (Vector.x < pTower->fRadius[1] &&
				g_aEnemy[i].nState != ENEMY_02_STATE_ATK &&
				g_aEnemy[i].nLife > 0 && g_aEnemy[i].nCT <= 0)
			{
				//�����ڃ{�b�N�X��������
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern = 0;
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_ATK_ENEMY_02;
				//�U����ԂɕύX
				g_aEnemy[i].nState = ENEMY_02_STATE_ATK;
			}
		}
		//���S��
		else if (g_aEnemy[i].nState == ENEMY_02_STATE_DEATH)
		{
			g_aEnemy[i].move.x = 0.0f;
			g_aEnemy[i].move.y = 2.0f;
		}

		break;
	case ENEMY_03:

		//��e���̓m�b�N�o�b�N��D�悷�邽�߈ړ��ʂ̌Œ���X���[
		if (g_aEnemy[i].nState != ENEMY_03_STATE_HURT && g_aEnemy[i].nState != ENEMY_03_STATE_DEATH)
		{
			g_aEnemy[i].nCT > 0 ? g_aEnemy[i].nCT-- : 0;

			//�^���[�ւ̌������o��
			D3DXVECTOR3 Vector = pTower->pos - g_aEnemy[i].pos;

			//�^���[�ւ̕��������m
			if (Vector.x > 0)
			{
				//������x�߂Â��Ǝ~�܂�
				Vector.x < pTower->fRadius[0] * 2.25f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = 2.0f, g_aEnemy[i].LR = 0;
			}
			else if (Vector.x < 0)
			{
				Vector.x > -pTower->fRadius[0] * 2.25f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = -2.0f, g_aEnemy[i].LR = 1;
			}

			//�U�����͑ҋ@��ړ��̕��ʂ𖳎�
			if (g_aEnemy[i].nState != ENEMY_03_STATE_ATK)
			{
				if (g_aEnemy[i].move.x == 0.0f)
				{
					//����܂őҋ@����Ȃ��Ƃ��̓{�b�N�X������
					if (g_aEnemy[i].nState != ENEMY_03_STATE_IDLE)
					{
						//�����ڃ{�b�N�X��������
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_03;
					}
					//�ړ��ʖ����ŌŒ�
					g_aEnemy[i].nState = ENEMY_03_STATE_IDLE;
				}
				else
				{
					//����܂ňړ�����Ȃ��Ƃ��̓{�b�N�X������
					if (g_aEnemy[i].nState != ENEMY_03_STATE_MOVE)
					{
						//�����ڃ{�b�N�X��������
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_03;
					}
					g_aEnemy[i].nState = ENEMY_03_STATE_MOVE;
				}
			}

			//�v�Z�p�ɕϊ�
			Vector.x < 0.0f ? Vector.x *= -1.0f : 0;

			//�^���[�ɋ߂Â��Ă��āA�U����ԂłȂ�HP������A�L���X�g�^�C���������ς݂ł���
			if (Vector.x < pTower->fRadius[1] * 1.75f &&
				g_aEnemy[i].nState != ENEMY_03_STATE_ATK &&
				g_aEnemy[i].nLife > 0 && g_aEnemy[i].nCT <= 0)
			{
				//�����ڃ{�b�N�X��������
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern = 0;
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_ATK_ENEMY_03;
				//�U����ԂɕύX
				g_aEnemy[i].nState = ENEMY_03_STATE_ATK;
			}
		}
		//���S��
		else if (g_aEnemy[i].nState == ENEMY_03_STATE_DEATH)
		{
			g_aEnemy[i].move.x = 0.0f;
			g_aEnemy[i].move.y = 2.0f;
		}

		break;
	case ENEMY_04:

		//��e���̓m�b�N�o�b�N��D�悷�邽�߈ړ��ʂ̌Œ���X���[
		if (g_aEnemy[i].nState != ENEMY_04_STATE_HURT && g_aEnemy[i].nState != ENEMY_04_STATE_DEATH)
		{
			g_aEnemy[i].nCT > 0 ? g_aEnemy[i].nCT-- : 0;

			//�^���[�ւ̌������o��
			D3DXVECTOR3 Vector = pTower->pos - g_aEnemy[i].pos;

			//�^���[�ւ̕��������m
			if (Vector.x > 0)
			{
				//������x�߂Â��Ǝ~�܂�
				Vector.x < pTower->fRadius[0] * 4.0f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = 4.0f, g_aEnemy[i].LR = 0;
			}
			else if (Vector.x < 0)
			{
				Vector.x > -pTower->fRadius[0] * 4.0f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = -4.0f, g_aEnemy[i].LR = 1;
			}

			//�U�����͑ҋ@��ړ��̕��ʂ𖳎�
			if (g_aEnemy[i].nState != ENEMY_04_STATE_ATK)
			{
				if (g_aEnemy[i].move.x == 0.0f)
				{
					//����܂őҋ@����Ȃ��Ƃ��̓{�b�N�X������
					if (g_aEnemy[i].nState != ENEMY_04_STATE_IDLE)
					{
						//�����ڃ{�b�N�X��������
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_04;
					}
					//�ړ��ʖ����ŌŒ�
					g_aEnemy[i].nState = ENEMY_04_STATE_IDLE;
				}
				else
				{
					//����܂ňړ�����Ȃ��Ƃ��̓{�b�N�X������
					if (g_aEnemy[i].nState != ENEMY_04_STATE_MOVE)
					{
						//�����ڃ{�b�N�X��������
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_04;
					}
					g_aEnemy[i].nState = ENEMY_04_STATE_MOVE;
				}
			}

			//�v�Z�p�ɕϊ�
			Vector.x < 0.0f ? Vector.x *= -1.0f : 0;

			//�^���[�ɋ߂Â��Ă��āA�U����ԂłȂ�HP������A�L���X�g�^�C���������ς݂ł���
			if (Vector.x < pTower->fRadius[1] * 3.0f &&
				g_aEnemy[i].nState != ENEMY_04_STATE_ATK &&
				g_aEnemy[i].nLife > 0 && g_aEnemy[i].nCT <= 0)
			{
				//�����ڃ{�b�N�X��������
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern = 0;
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_ATK_ENEMY_04;
				//�U����ԂɕύX
				g_aEnemy[i].nState = ENEMY_04_STATE_ATK;
			}
		}
		//���S��
		else if (g_aEnemy[i].nState == ENEMY_04_STATE_DEATH)
		{
			g_aEnemy[i].move.x = 0.0f;
			g_aEnemy[i].move.y = 2.0f;
		}

		break;
	}

	//�ړ�
	g_aEnemy[i].pos += g_aEnemy[i].move;

	//�������̈ʒu�𒲐�����
	Adjust_Pos_Enemy(i);

	//�e�N�X�`���A�j���[�V����
	Update_Tex_Enemy(i);

	//������
	g_aEnemy[i].nLife <= 0 ? g_aEnemy[i].fDisappear *= 0.97f : 0;

	//��Ԃɍ��킹�ă{�b�N�X����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[g_aEnemy[i].nStyle][g_aEnemy[i].nState].fLength_Hold[nCnt] * g_aEnemy[i].fDisappear;
		g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[g_aEnemy[i].nStyle][g_aEnemy[i].nState].fAngle_Hold[nCnt];
	}

	//�n�`�Ƃ̓����蔻��
	if (g_aEnemy[i].nStyle != ENEMY_00)
	{
		HitDetection_Stage(i, HIT_TYPE_ENEMY, &g_aEnemy[i].pos, &g_aEnemy[i].oldpos, &g_aEnemy[i].move, &g_aEnemy[i].fRadius[0]);
	}

	//�������ړ�
	ConvertInfo_Screen(&g_aEnemy[i].pos);

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	pVtx_Enemy += AMOUNT_VTX * i;

	/*�f�o�b�O�p�����蔻�����*/
	//g_aEnemy[i].fLength[0] = sqrtf((RADIUS_ENEMY_X * RADIUS_ENEMY_X) + (RADIUS_ENEMY_Y * RADIUS_ENEMY_Y));
	//g_aEnemy[i].fLength[1] = g_aEnemy[i].fLength[0];
	//g_aEnemy[i].fAngle[0] = atan2f(RADIUS_ENEMY_X * 2.0f, RADIUS_ENEMY_Y * 2.0f);
	//g_aEnemy[i].fAngle[1] = g_aEnemy[i].fAngle[0];

	pVtx_Enemy[0].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z - (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
	pVtx_Enemy[0].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z - (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
	pVtx_Enemy[1].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z + (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
	pVtx_Enemy[1].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z + (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
	pVtx_Enemy[2].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z - g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
	pVtx_Enemy[2].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z - g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
	pVtx_Enemy[3].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z + g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
	pVtx_Enemy[3].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z + g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Enemy->Unlock();
}

//************************************************
//�G��|�����Ƃ��̏��ŏ����֐�
//************************************************
void Disapper_Enemy(int i)
{
	//HP��0�Ŕ�e��Ԃ��I��肻���ȂƂ�
	switch (g_aEnemy[i].nStyle)
	{
	case ENEMY_00:
		if (g_aEnemy[i].nLife <= 0 && g_aEnemy[i].nState == ENEMY_00_STATE_HURT &&
			g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_00 - 1)
		{
			//�����ڃ{�b�N�X������
			g_aEnemy[i].nCntTex = 0;
			g_aEnemy[i].nCntPattern = 0;
			g_aEnemy[i].fTexSpan[0] = 0.0f;
			g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_DEATH_ENEMY_00;

			//���S��Ԃ�
			g_aEnemy[i].nState = ENEMY_00_STATE_DEATH;

			PlaySound(SOUND_LABEL_SLAY);
		}
		break;
	case ENEMY_01:
		if (g_aEnemy[i].nLife <= 0 && g_aEnemy[i].nState == ENEMY_01_STATE_HURT &&
			g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_01 - 1)
		{
			//�����ڃ{�b�N�X������
			g_aEnemy[i].nCntTex = 0;
			g_aEnemy[i].nCntPattern = 0;
			g_aEnemy[i].fTexSpan[0] = 0.0f;
			g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_DEATH_ENEMY_01;

			//���S��Ԃ�
			g_aEnemy[i].nState = ENEMY_01_STATE_DEATH;

			PlaySound(SOUND_LABEL_SLAY);
		}
		break;
	case ENEMY_02:
		if (g_aEnemy[i].nLife <= 0 && g_aEnemy[i].nState == ENEMY_02_STATE_HURT &&
			g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_02 - 1)
		{
			//�����ڃ{�b�N�X������
			g_aEnemy[i].nCntTex = 0;
			g_aEnemy[i].nCntPattern = 0;
			g_aEnemy[i].fTexSpan[0] = 0.0f;
			g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_DEATH_ENEMY_02;

			//���S��Ԃ�
			g_aEnemy[i].nState = ENEMY_02_STATE_DEATH;

			PlaySound(SOUND_LABEL_SLAY);
		}
		break;
	case ENEMY_03:
		if (g_aEnemy[i].nLife <= 0 && g_aEnemy[i].nState == ENEMY_03_STATE_HURT &&
			g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_03 - 1)
		{
			//�����ڃ{�b�N�X������
			g_aEnemy[i].nCntTex = 0;
			g_aEnemy[i].nCntPattern = 0;
			g_aEnemy[i].fTexSpan[0] = 0.0f;
			g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_DEATH_ENEMY_03;

			//���S��Ԃ�
			g_aEnemy[i].nState = ENEMY_03_STATE_DEATH;

			PlaySound(SOUND_LABEL_SLAY);
		}
		break;
	case ENEMY_04:
		if (g_aEnemy[i].nLife <= 0 && g_aEnemy[i].nState == ENEMY_04_STATE_HURT &&
			g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_04 - 1)
		{
			//�����ڃ{�b�N�X������
			g_aEnemy[i].nCntTex = 0;
			g_aEnemy[i].nCntPattern = 0;
			g_aEnemy[i].fTexSpan[0] = 0.0f;
			g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_DEATH_ENEMY_04;

			//���S��Ԃ�
			g_aEnemy[i].nState = ENEMY_04_STATE_DEATH;

			PlaySound(SOUND_LABEL_SLAY);
		}
		break;
	}

	if (g_aEnemy[i].nState == -1)
	{
		//�����N���A
		g_aEnemy[i].bUse = false;
		g_aEnemy[i].nStyle = 0;
		g_aEnemy[i].nState = 0;
		g_aEnemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEnemy[i].LR = 0;
		g_aEnemy[i].nCntTex = 0;
		g_aEnemy[i].nCntPattern = 0;
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aEnemy[i].fTexSpan[nCnt] = 0.0f;
			g_aEnemy[i].fRadius[nCnt] = 0.0f;
			g_aEnemy[i].fLength[nCnt] = 0.0f;
			g_aEnemy[i].fAngle[nCnt] = 0.0f;
		}
		g_aEnemy[i].fDisappear = 1.0f;
		g_aEnemy[i].nLife = 0;
		g_aEnemy[i].bLockonP = false;

		//���_���ւ̃|�C���^
		VERTEX_2D* pVtx_Enemy;

		//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
		g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

		pVtx_Enemy += AMOUNT_VTX * i;

		pVtx_Enemy[0].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z - (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
		pVtx_Enemy[0].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z - (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
		pVtx_Enemy[1].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z + (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
		pVtx_Enemy[1].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z + (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
		pVtx_Enemy[2].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z - g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
		pVtx_Enemy[2].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z - g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
		pVtx_Enemy[3].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z + g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
		pVtx_Enemy[3].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z + g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuff_Enemy->Unlock();
	}
}

//************************************************
//�ʒu�ł��낢�뒲������֐�
//************************************************
void Adjust_Pos_Enemy(int i)
{
	//��������Ǝ��S
	if (g_aEnemy[i].pos.y >= SCREEN_HEIGHT + 100.0f)
	{
		g_aEnemy[i].nLife > 0 ? g_aEnemy[i].nLife = 0, PlaySound(SOUND_LABEL_FALL) : 0;

		switch (g_aEnemy[i].nStyle)
		{
		case ENEMY_00:
			//���ȂȂ�
			break;
		case ENEMY_01:
			g_aEnemy[i].nState = ENEMY_01_STATE_DEATH;
			break;
		case ENEMY_02:
			g_aEnemy[i].nState = ENEMY_02_STATE_DEATH;
			break;
		case ENEMY_03:
			g_aEnemy[i].nState = ENEMY_03_STATE_DEATH;
			break;
		case ENEMY_04:
			g_aEnemy[i].nState = ENEMY_04_STATE_DEATH;
			break;
		}
	}
}

//************************************************
//�G�̃e�N�X�`���𓮂����֐�
//************************************************
void Update_Tex_Enemy(int i)
{
	//���_���ւ̃|�C���^
	VERTEX_2D* pVtx_Enemy;

	//�e�N�X�`����ύX
	switch (g_aEnemy[i].nStyle)
	{
	case ENEMY_00:
		switch (g_aEnemy[i].nState)
		{
		case ENEMY_00_STATE_MOVE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_MOVE_ENEMY_00)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_MOVE_ENEMY_00;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_MOVE_ENEMY_00;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_MOVE_ENEMY_00)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_00;
				}
			}
			break;
		case ENEMY_00_STATE_ATK:

			//�e�N�X�`���̃^�C�~���O�ɍ��킹�čU���{�b�N�X����
			if (g_aEnemy[i].nCntTex == 0 && g_aEnemy[i].nCntPattern == 6)
			{
				//�G�̔ԍ����M
				GiveInfo_Attack_Box_Enemy(i);
			}

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_ATK_ENEMY_00)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_ATK_ENEMY_00;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_ATK_ENEMY_00;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_ATK_ENEMY_00)
				{
					g_aEnemy[i].nState = ENEMY_00_STATE_MOVE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_00;
				}
			}
			break;
		case ENEMY_00_STATE_HURT:
			//�p�[�e�B�N�����΂�
			g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Setinfo_Particle(PARTICLE_BLOOD, g_aEnemy[i].pos, g_aEnemy[i].col);

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_HURT_ENEMY_00)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_HURT_ENEMY_00;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_HURT_ENEMY_00;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_00)
				{
					g_aEnemy[i].nState = ENEMY_00_STATE_MOVE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_00;

					//CT��ݒ�
					AMOUNT_CT_ATK_ENEMY_00;
				}
			}
			break;
		case ENEMY_00_STATE_DEATH:
			
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_DEATH_ENEMY_00)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_DEATH_ENEMY_00;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_DEATH_ENEMY_00;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_DEATH_ENEMY_00)
				{
					//�N���A
					g_aEnemy[i].nState = -1;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = 0;

					//�X�R�A���Z
					int* pScore = GetInfo_Score();
					pScore[SCORE_NEW] += 10;
				}
			}
			break;
		}
		break;
	case ENEMY_01:
		switch (g_aEnemy[i].nState)
		{
		case ENEMY_01_STATE_IDLE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_IDLE_ENEMY_01)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_IDLE_ENEMY_01;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_IDLE_ENEMY_01;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_IDLE_ENEMY_01)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_01;
				}
			}
			break;
		case ENEMY_01_STATE_MOVE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_MOVE_ENEMY_01)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_MOVE_ENEMY_01;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_MOVE_ENEMY_01;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_MOVE_ENEMY_01)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_01;
				}
			}
			break;
		case ENEMY_01_STATE_ATK:

			//�e�N�X�`���̃^�C�~���O�ɍ��킹�čU���{�b�N�X����
			if (g_aEnemy[i].nCntTex == 0 && g_aEnemy[i].nCntPattern == 6)
			{
				//�G�̔ԍ����M
				GiveInfo_Attack_Box_Enemy(i);
			}

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_ATK_ENEMY_01)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_ATK_ENEMY_01;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_ATK_ENEMY_01;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_ATK_ENEMY_01)
				{
					g_aEnemy[i].nState = ENEMY_01_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_01;
				}
			}
			break;
		case ENEMY_01_STATE_HURT:
			//�p�[�e�B�N�����΂�
			g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Setinfo_Particle(PARTICLE_BLOOD, g_aEnemy[i].pos, g_aEnemy[i].col);

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_HURT_ENEMY_01)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_HURT_ENEMY_01;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_HURT_ENEMY_01;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_01)
				{
					g_aEnemy[i].nState = ENEMY_01_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_01;

					//CT��ݒ�
					AMOUNT_CT_ATK_ENEMY_01;
				}
			}
			break;
		case ENEMY_01_STATE_DEATH:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_DEATH_ENEMY_01)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_DEATH_ENEMY_01;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_DEATH_ENEMY_01;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_DEATH_ENEMY_01)
				{
					//�N���A
					g_aEnemy[i].nState = -1;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = 0;

					//�X�R�A���Z
					int* pScore = GetInfo_Score();
					pScore[SCORE_NEW] += 5;
				}
			}
			break;
		}
		break;
	case ENEMY_02:
		switch (g_aEnemy[i].nState)
		{
		case ENEMY_02_STATE_IDLE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_IDLE_ENEMY_02)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_IDLE_ENEMY_02;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_IDLE_ENEMY_02;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_IDLE_ENEMY_02)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_02;
				}
			}
			break;
		case ENEMY_02_STATE_MOVE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_MOVE_ENEMY_02)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_MOVE_ENEMY_02;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_MOVE_ENEMY_02;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_MOVE_ENEMY_02)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_02;
				}
			}
			break;
		case ENEMY_02_STATE_ATK:

			//�e�N�X�`���̃^�C�~���O�ɍ��킹�čU���{�b�N�X����
			if (g_aEnemy[i].nCntTex == 0 && g_aEnemy[i].nCntPattern == 6)
			{
				//�G�̔ԍ����M
				GiveInfo_Attack_Box_Enemy(i);
			}

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_ATK_ENEMY_02)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_ATK_ENEMY_02;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_ATK_ENEMY_02;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_ATK_ENEMY_02)
				{
					g_aEnemy[i].nState = ENEMY_02_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_02;
				}
			}
			break;
		case ENEMY_02_STATE_HURT:
			//�p�[�e�B�N�����΂�
			g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Setinfo_Particle(PARTICLE_BLOOD, g_aEnemy[i].pos, g_aEnemy[i].col);

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_HURT_ENEMY_02)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_HURT_ENEMY_02;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_HURT_ENEMY_02;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_02)
				{
					g_aEnemy[i].nState = ENEMY_02_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_02;

					//CT��ݒ�
					AMOUNT_CT_ATK_ENEMY_02;
				}
			}
			break;
		case ENEMY_02_STATE_DEATH:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_DEATH_ENEMY_02)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_DEATH_ENEMY_02;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_DEATH_ENEMY_02;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_DEATH_ENEMY_02)
				{
					//�N���A
					g_aEnemy[i].nState = -1;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = 0;

					//�X�R�A���Z
					int* pScore = GetInfo_Score();
					pScore[SCORE_NEW] += 10;
				}
			}
			break;
		}
		break;
	case ENEMY_03:
		switch (g_aEnemy[i].nState)
		{
		case ENEMY_03_STATE_IDLE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_IDLE_ENEMY_03)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_IDLE_ENEMY_03;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_IDLE_ENEMY_03;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_IDLE_ENEMY_03)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_03;
				}
			}
			break;
		case ENEMY_03_STATE_MOVE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_MOVE_ENEMY_03)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_MOVE_ENEMY_03;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_MOVE_ENEMY_03;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_MOVE_ENEMY_03)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_03;
				}
			}
			break;
		case ENEMY_03_STATE_ATK:

			//�e�N�X�`���̃^�C�~���O�ɍ��킹�čU���{�b�N�X����
			if (g_aEnemy[i].nCntTex == 0 && g_aEnemy[i].nCntPattern == 6)
			{
				//�G�̔ԍ����M
				GiveInfo_Attack_Box_Enemy(i);
			}

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_ATK_ENEMY_03)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_ATK_ENEMY_03;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_ATK_ENEMY_03;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_ATK_ENEMY_03)
				{
					g_aEnemy[i].nState = ENEMY_03_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_03;
				}
			}
			break;
		case ENEMY_03_STATE_HURT:
			//�p�[�e�B�N�����΂�
			g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Setinfo_Particle(PARTICLE_BLOOD, g_aEnemy[i].pos, g_aEnemy[i].col);

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_HURT_ENEMY_03)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_HURT_ENEMY_03;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_HURT_ENEMY_03;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_03)
				{
					g_aEnemy[i].nState = ENEMY_03_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_03;

					//CT��ݒ�
					AMOUNT_CT_ATK_ENEMY_03;
				}
			}
			break;
		case ENEMY_03_STATE_DEATH:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_DEATH_ENEMY_03)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_DEATH_ENEMY_03;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_DEATH_ENEMY_03;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_DEATH_ENEMY_03)
				{
					//�N���A
					g_aEnemy[i].nState = -1;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = 0;

					//�X�R�A���Z
					int* pScore = GetInfo_Score();
					pScore[SCORE_NEW] += 15;
				}
			}
			break;
		}
		break;
	case ENEMY_04:
		switch (g_aEnemy[i].nState)
		{
		case ENEMY_04_STATE_IDLE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_IDLE_ENEMY_04)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_IDLE_ENEMY_04;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_IDLE_ENEMY_04;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_IDLE_ENEMY_04)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_04;
				}
			}
			break;
		case ENEMY_04_STATE_MOVE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_MOVE_ENEMY_04)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_MOVE_ENEMY_04;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_MOVE_ENEMY_04;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_MOVE_ENEMY_04)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_04;
				}
			}
			break;
		case ENEMY_04_STATE_ATK:

			//�e�N�X�`���̃^�C�~���O�ɍ��킹�čU���{�b�N�X����
			if (g_aEnemy[i].nCntTex == 0 && g_aEnemy[i].nCntPattern == 6)
			{
				//�G�̔ԍ����M
				GiveInfo_Attack_Box_Enemy(i);
			}

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_ATK_ENEMY_04)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_ATK_ENEMY_04;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_ATK_ENEMY_04;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_ATK_ENEMY_04)
				{
					g_aEnemy[i].nState = ENEMY_04_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_04;
				}
			}
			break;
		case ENEMY_04_STATE_HURT:
			//�p�[�e�B�N�����΂�
			g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Setinfo_Particle(PARTICLE_BLOOD, g_aEnemy[i].pos, g_aEnemy[i].col);

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_HURT_ENEMY_04)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_HURT_ENEMY_04;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_HURT_ENEMY_04;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_04)
				{
					g_aEnemy[i].nState = ENEMY_04_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_04;

					//CT��ݒ�
					AMOUNT_CT_ATK_ENEMY_04;
				}
			}
			break;
		case ENEMY_04_STATE_DEATH:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_DEATH_ENEMY_04)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_DEATH_ENEMY_04;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_DEATH_ENEMY_04;
				//1���[�v�ŏI��
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_DEATH_ENEMY_04)
				{
					//�N���A
					g_aEnemy[i].nState = -1;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = 0;

					//�X�R�A���Z
					int* pScore = GetInfo_Score();
					pScore[SCORE_NEW] += 20;
				}
			}
			break;
		}
		break;
	}

	//���_�o�b�t�@�����b�N���Ē��_���̃|�C���^���擾
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	pVtx_Enemy += AMOUNT_VTX * i;

	if (g_aEnemy[i].LR == 0)
	{
		pVtx_Enemy[0].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[0], 0.0f);
		pVtx_Enemy[1].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[1], 0.0f);
		pVtx_Enemy[2].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[0], 1.0f);
		pVtx_Enemy[3].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[1], 1.0f);
	}
	else
	{
		pVtx_Enemy[0].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[1], 0.0f);
		pVtx_Enemy[1].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[0], 0.0f);
		pVtx_Enemy[2].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[1], 1.0f);
		pVtx_Enemy[3].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[0], 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuff_Enemy->Unlock();
}

//************************************************
//�G�\���̂̃A�h���X��n��
//************************************************
ENEMY* GetInfo_Enemy(void)
{
	return &g_aEnemy[0];
}