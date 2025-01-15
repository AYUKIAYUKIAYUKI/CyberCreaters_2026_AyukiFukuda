//************************************************
//
//�W�F�j�[�Q�j�[�A�w�b�_�t�@�C��[main.h]
//Author�F���c����
//
//************************************************
#ifndef _MAIN_H_	//���̃}�N����`���ߋ��ɂ���Ă��Ȃ�������1�x�̂݉��̏�����ʂ�
#define _MAIN_H_	//(��d�C���N���[�h�h�~�A�}�N����`����)

#include <windows.h>
#include <Mmsystem.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	//���̂�̃r���h���x���p�}�N��
#include <dinput.h>
#include "Xinput.h"
#include "xaudio2.h"
#include "title.h"
#include "tutorial.h"
#include "ranking.h"
#include "menu.h"
#include "game.h"
#include "result.h"

//���C�u�����̃����N
#pragma	comment(lib,"d3d9.lib")		//�`�揈���p
#pragma	comment(lib,"d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma	comment(lib,"dxguid.lib")	//DirectX�̃R�[�|�l���g�g�p�̂���
#pragma comment(lib,"Winmm.lib")	//�V�X�e�����Ԏ擾�p
#pragma comment(lib,"dinput8.lib")	//���͏����p
#pragma comment(lib,"xinput.lib")	//�R���g���[�����͗p

//�}�N����`
#define SCREEN_WIDTH	(1980)	//�E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080)	//�E�C���h�E�̍���

#define FVF_VERTEX_2D	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_�t�H�[�}�b�g

#define AMOUNT_VTX	(4)				//���ϓI�ȃ|���S��1������̒��_��
#define AMOUNT_COMBINEPOLYGON	(2)	//���ϓI�ȃ|���S���̑g�ݍ��킹����

#define SCREENCENTER_X	(990.0f)	//X���S
#define SCREENCENTER_Y	(540.0f)	//Y���S

#define SPAN_OUTSIDE_BORDER	(20.0f)	//��ʂ̉��̒���

//���[�h���ʂ̗񋓌^
typedef enum
{
	MODE_TITLE = 0, //�^�C�g�����[�h
	MODE_MENU,		//���j���[���[�h
	MODE_TUTORIAL,	//�`���[�g���A�����[�h
	MODE_RANKING,	//�����L���O���[�h
	MODE_GAME,		//�Q�[�����[�h
	MODE_RESULT,	//���U���g���[�h
	MODE_MAX,		//���[�h�̑���
}MODE;

//�|���S���p�\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ω��p�W��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W�p
}VERTEX_2D;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void Setinfo_Mode(MODE mode);
MODE Getinfo_Mode(void);
bool* Getinfo_End(void);
int* Getinfo_HoldLastScore(void);

#endif