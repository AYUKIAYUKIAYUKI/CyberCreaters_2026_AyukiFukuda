//************************************************
//
//�J����(�U)����[camera.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "camera.h"
#include "player.h"

D3DXVECTOR3 g_Camera_pos;

//************************************************
//�J�������W����������
//************************************************
void Init_Camera(void)
{
	//�ʒu��������
	g_Camera_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//************************************************
//�X�N���[������
//************************************************
void ConvertInfo_Screen(D3DXVECTOR3* real_pos)
{
	PLAYER* pPlayer = GetInfo_Player();

	//�v���C���[�̈ړ��ʂ��u���b�N�ɂ��Ă͂�
	real_pos->x -= pPlayer->move.x;
}