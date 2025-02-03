//************************************************
//
//���C�g[light.cpp]
//Author�F���c����
//
//************************************************
#include "light.h"

#include "input.h"

//�}�N����`
#define AMOUNT_LIGHT	(3)	//���C�g�̐�

//�O���[�o���ϐ�
D3DLIGHT9 g_aLight[AMOUNT_LIGHT] = {};	//���C�g���
int g_nLightType = 0;	//���C�g����

//************************************************
//���C�g����
//************************************************
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���C�g�̏���������
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	//���C�g���ʔԍ�
	g_nLightType = 0;

	for (int i = 0; i < AMOUNT_LIGHT; i++)
	{
		D3DXVECTOR3 vecDir;	//�ݒ�p�����x�N�g��

		//���C�g�̎�ނ�ݒ�
		g_aLight[i].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		g_aLight[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�̕�����ݒ�
		switch (i)
		{
		case 0:
			vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
			break;
		case 1:
			vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(0.8f, 0.1f, 0.4f);
			break;
		}
		D3DXVec3Normalize(&vecDir, &vecDir);	//�x�N�g�����擾����
		g_aLight[i].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(i, &g_aLight[i]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(i, TRUE);
	}
}

//************************************************
//���C�g�j��
//************************************************
void UninitLight(void)
{

}

//************************************************
//���C�g�X�V
//************************************************
void UpdateLight(void)
{
	//���C�g�ԍ��ύX
	ChangeLightType();

	//�ړ�
	MoveLight();

	//���Z�b�g
	ResetLight();

	//�ړ��Ȃǔ��f
	SetLight();
}

//************************************************
//���C�g�ԍ��ύX
//************************************************
void ChangeLightType(void)
{
	//���C�g�ԍ��ύX
	if (GetKeyboardTrigger(DIK_0))
	{
		g_nLightType < 2 ? g_nLightType++ : g_nLightType = 0;
	}
}

//************************************************
//���C�g�ړ�
//************************************************
void MoveLight(void)
{
	//X�����ύX
	if (GetKeyboardPress(DIK_1))
	{
		g_aLight[g_nLightType].Direction.x += 0.1f;
	}
	else if (GetKeyboardPress(DIK_2))
	{
		g_aLight[g_nLightType].Direction.x -= 0.1f;
	}

	//Y�����ύX
	if (GetKeyboardPress(DIK_3))
	{
		g_aLight[g_nLightType].Direction.x += 0.1f;
	}
	else if (GetKeyboardPress(DIK_4))
	{
		g_aLight[g_nLightType].Direction.x -= 0.1f;
	}

	//Z�����ύX
	if (GetKeyboardPress(DIK_5))
	{
		g_aLight[g_nLightType].Direction.z += 0.1f;
	}
	else if (GetKeyboardPress(DIK_6))
	{
		g_aLight[g_nLightType].Direction.z -= 0.1f;
	}
}

//************************************************
//���C�g���Z�b�g
//************************************************
void ResetLight(void)
{
	//���C�g���Z�b�g
	if (GetKeyboardTrigger(DIK_R))
	{
		switch (g_nLightType)
		{
		case 0:
			g_aLight[g_nLightType].Direction = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
			break;
		case 1:
			g_aLight[g_nLightType].Direction = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
			break;
		case 2:
			g_aLight[g_nLightType].Direction = D3DXVECTOR3(0.8f, 0.1f, 0.4f);
			break;
		}
	}
}

//************************************************
//���C�g���f
//************************************************
void SetLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�ύX���f
	for (int i = 0; i < AMOUNT_LIGHT; i++)
	{
		D3DXVECTOR3 vecDir = g_aLight[i].Direction;	//�ݒ�p�����x�N�g��
		D3DXVec3Normalize(&vecDir, &vecDir);	//�x�N�g�����擾����
		g_aLight[i].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(i, &g_aLight[i]);
	}
}

//************************************************
//���C�g�����擾
//************************************************
D3DLIGHT9* GetInfoLight(void)
{
	return &g_aLight[0];
}

//************************************************
//���C�g�ԍ������擾
//************************************************
int GetInfoLightType(void)
{
	return g_nLightType;
}