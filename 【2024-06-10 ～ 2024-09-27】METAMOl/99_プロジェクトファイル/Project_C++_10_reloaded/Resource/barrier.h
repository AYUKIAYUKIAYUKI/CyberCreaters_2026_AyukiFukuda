//============================================================================
// 
// �o���A�A�w�b�_�t�@�C�� [barrier.h]
// Author : ���c����
// 
//============================================================================

#ifndef _BARRIER_H_
#define _BARRIER_H_	// ��d�C���N���[�h�h�~

//****************************************************
// �C���N���[�h�t�@�C��
//****************************************************
#include "object_X.h"

//****************************************************
// �o���A�N���X
//****************************************************
class CBarrier : public CObject_X
{
public:

	CBarrier();		// �f�t�H���g�R���X�g���N�^
	~CBarrier();	// �f�X�g���N�^

	HRESULT Init() override;	// �����ݒ�
	void Uninit() override;		// �I������
	void Update() override;		// �X�V����
	void Draw() override;		// �`�揈��

	static CBarrier* Create(D3DXVECTOR3 Pos, D3DXVECTOR3 Rot);	// ����
};

#endif	// _BARRIER_H_