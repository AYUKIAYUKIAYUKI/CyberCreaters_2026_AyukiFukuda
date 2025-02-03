//************************************************
//
//�J����[camera.cpp]
//Author�F���c����
//
//************************************************
#include "camera.h"

#include "debugproc.h"
#include "input.h"

#include "player.h"

//�O���[�o���ϐ�
Camera g_Camera;	//�J�������
static const float g_UP = 80.0f;	/* (���_ - �����_�Ԃɏo���鋅�`�O�����̂��̂�y���W��ύX���鐔�l) */

//************************************************
//�J��������
//************************************************
void InitCamera(void)
{
	//�J�������̏����Z�b�g
	g_Camera.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.rotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.fPA = 0.0f;
	g_Camera.fPAGoal = 0.0f;
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.fDistance = 150.0f;
	g_Camera.bTrack = false;
}

//************************************************
//�J�����j��
//************************************************
void UninitCamera(void)
{
	/* ���i�K�ł͖��� */
}

//************************************************
//�J�����X�V
//************************************************
void UpdateCamera(int mode)
{
	//�ǔ��Ώە��ύX
	if (mode != MODE_TITLE)
	{
		//if (GetKeyboardPress(DIK_F1) || GetPressTriggerButtonL()) g_Camera.bTrack = true;
		//else g_Camera.bTrack = false;
	}

	//�E�X�e�B�b�N�Ŏ��_�ύX (��)
	if (GetJoyStickR())
	{
		const XINPUT_GAMEPAD GamePad = GetGamePad();

		g_Camera.fPAGoal += (float)(GamePad.sThumbRY * 0.000001);
		g_Camera.rotGoal.y += (float)(GamePad.sThumbRX * 0.000001);
	}
	//�L�[�{�[�h�Ŏ��_�ύX
	else
	{
		//���E
		if (GetKeyboardPress(DIK_RIGHT)) g_Camera.rotGoal.y += 0.05f;
		else if (GetKeyboardPress(DIK_LEFT)) g_Camera.rotGoal.y -= 0.05f;

		//�㉺
		if (GetKeyboardPress(DIK_UP)) g_Camera.fPAGoal += 0.025f;
		else if (GetKeyboardPress(DIK_DOWN)) g_Camera.fPAGoal -= 0.025f;
	}

	//�u���[�L
	g_Camera.rotGoal *= 0.8f;
	g_Camera.fPAGoal *= 0.8f;

	//�ړ�
	g_Camera.rot += g_Camera.rotGoal * 0.5f;
	g_Camera.fPA += g_Camera.fPAGoal * 0.5f;

	//��]�͈�
	if (g_Camera.rot.y > D3DX_PI) g_Camera.rot.y = -D3DX_PI;
	if (g_Camera.rot.y < -D3DX_PI) g_Camera.rot.y = D3DX_PI;

	//�Ίp�͈�
	if (g_Camera.fPA > D3DX_PI * 0.45f) g_Camera.fPA = D3DX_PI * 0.45f;
	if (g_Camera.fPA < -D3DX_PI * 0.45f) g_Camera.fPA = -D3DX_PI * 0.45f;

	//�Ώە��̍��W
	D3DXVECTOR3 target;
	const Player* pPlayer = GetInfoPlayer();	//�v���C���[���Q��
	target = pPlayer->pos;

	//���_���Z�o
	CalcPosV(target);

	//�����_���Z�o
	CalcPosR(target);

	PrintDebugProc("�J�����̍��W( %f %f %f )\n", g_Camera.posV.x, g_Camera.posV.y, g_Camera.posV.z);
}


//************************************************
//���_���Z�o
//************************************************
void CalcPosV(const D3DXVECTOR3 target)
{
	/* ���Ȃ�Ƃ�����\�� */

	static float fA[2] = {};	/* �X�R�[�v�����Ƃ��A���_�������_�ɐڋ߂��邽�߂̌W��������c */

	g_Camera.bTrack ? fA[1] = g_Camera.fDistance * 1.8f : fA[1] = 0.0f;	/* �܂����ꂮ�炢 */

	//�ړ�
	fA[0] += (fA[1] - fA[0]) * 0.3f;

	//���_�͑Ώە��̌����
	g_Camera.posV =
	{
		target.x - (sinf(g_Camera.rot.y) * cosf(g_Camera.fPA) * (g_Camera.fDistance - fA[0])),
		target.y - (sinf(g_Camera.fPA) * (g_Camera.fDistance - fA[0])),
		target.z - (cosf(g_Camera.rot.y) * cosf(g_Camera.fPA) * (g_Camera.fDistance - fA[0]))
	};
}

//************************************************
//�����_���Z�o
//************************************************
void CalcPosR(const D3DXVECTOR3 target)
{
	//�����_��Ώە��̑O����
	g_Camera.posR =
	{
		target.x + (sinf(g_Camera.rot.y) * cosf(g_Camera.fPA) * g_Camera.fDistance),
		target.y + (sinf(g_Camera.fPA) * g_Camera.fDistance),
		target.z + (cosf(g_Camera.rot.y) * cosf(g_Camera.fPA) * g_Camera.fDistance)
	};
}

//************************************************
//�J�����ݒ�
//************************************************
void SetInfoCamera(int mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&g_Camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	D3DXVECTOR3 posV = g_Camera.posV;

	if (mode == MODE_TITLE)
	{
		posV.y += 110.0f;
	}
	else
	{
		if (!g_Camera.bTrack) posV.y += g_UP;
	}

	//�r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
		&posV,
		&g_Camera.posR,
		&g_Camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW,
		&g_Camera.mtxView);
}

//************************************************
//�J���������擾
//************************************************
Camera* GetInfoCamera(void)
{
	return &g_Camera;
}