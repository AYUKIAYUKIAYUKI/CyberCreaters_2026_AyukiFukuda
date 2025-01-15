//************************************************
//
//2D�A�N�V�������C������[main.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "fade.h"
#include "title.h"
#include "menu.h"
#include "ranking.h"
#include "game.h"
#include "result.h"

/*�f�o�b�O�p*/
#include "player.h"
#include "tower.h"

/*��邱��*/

//�}�N����`
#define CLASS_NAME	"WindowClass"		//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME	"�_�[�N�G���h���X�t�@���^�W�["		//�E�C���h�E�̖��O
#define MAX_WORD	(512)				//�\���������̍ő�

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
/*DirectX�`��p*/
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindiw);	//����������
void UnInit(void);	//�I������
void Update(void);	//�X�V����
void Draw(void);	//�`�揈��
void DrawFPS(void);	//FPS�\������

//�O���[�o���ϐ����`
LPDIRECT3D9 g_pD3D = NULL;				//Direct3D�I�u�W�F�N�g�̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3D�f�o�C�X�̃|�C���^
MODE g_mode;							//���݂̃��[�h������
bool g_bExit = false;						//�I������
int g_nMode = 0;

/*�f�o�b�O�\���p*/
LPD3DXFONT g_pFont = NULL;	//�t�H���g�̃|�C���^
int g_nCountFPS = 0;		//FPS�J�E���^

//�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//************************************************
//���C���֐�
//************************************************
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DWORD dwCurrentTime;	//���ݎ����p
	DWORD dwExecLastTime;	//�Ō�ɏ�����������
	DWORD dwFrameCount;		//�t���[���J�E���g�i�[
	DWORD dwFPSLastTime;	//�Ō��FPS���v�����������i�[

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						//�E�C���h�E�̃X�^�C��
		WindowProc,						//�E�C���h�E�v���V�[�W��
		0,								//������0�ɂ���
		0,								//������0�ɂ���
		hInstance,						//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW),			//�N���C�A���g�̈�̔w�i�F
		NULL,							//���j���[�o�[
		CLASS_NAME,						//�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	//�t�@�C���̃A�C�R��
	};

	HWND hWnd;	//�E�C���h�E�n���h��(���ʎq)
	MSG msg;	//���b�Z�[�W���i�[����ϐ�

	//��ʃT�C�Y�̍\����
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,		//�g���E�C���h�E�̃X�^�C��
		CLASS_NAME,					//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,				//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		//�E�C���h�E�̃X�^�C��
		CW_USEDEFAULT,				//�E�C���h�E�̍����X���W
		CW_USEDEFAULT,				//�E�C���h�E�̍����Y���W
		(rect.right - rect.left),	//�E�C���h�E�̍���̕�
		(rect.bottom - rect.top),	//�E�C���h�E�̍���̍���
		NULL,						//�e�E�C���h�E�̃n���h��
		NULL,						//���j���[�o�[�܂��͎q�E�C���h�EID
		hInstance,					//�C���X�^���X�n���h��
		NULL);						//�E�C���h�E�쐬�f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{

		//���������������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	//������
	dwCurrentTime = 0;
	dwFrameCount = 0;

	//���ݎ������擾
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, SW_MAXIMIZE);	//�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);				//�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			//Windows�̏���
			if (msg.message == WM_QUIT)
			{
				//WM_QUIT�̃��b�Z�[�W���󂯎��ƁA���b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);	//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	//�E�C���h�E�v���V�[�W���փ��b�Z�[�W��n�o
			}
		}
		else
		{
			//���ݎ������擾
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPS���v���������Ԃ�ۑ�
				dwFPSLastTime = dwCurrentTime;

				//�t���[���J�E���g���N���A
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				//���ݎ�����ۑ�
				dwExecLastTime = dwCurrentTime;

				Draw();		//�`�揈��

				Update();	//�X�V����

				//�I�����I������Ă����狭���I��
				if (g_bExit)
				{
					break;
				}

				//�t���[���J�E���g�����Z
				dwFrameCount++;
			}
		}
	}

	//�I������
	UnInit();

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//************************************************
//�E�C���h�E�v���V�[�W��
//************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*�錾*/
	int nID;			//�Ԃ�l�󂯎M
	switch (uMsg)
	{
	case WM_CREATE:	//�E�C���h�E�����̃��b�Z�[�W�𑗂�

		break;

	case WM_DESTROY:	//�E�C���h�E�j���̃��b�Z�[�W�𑗂�

		PostQuitMessage(0);	//�uWM_QUIT�v�Ƃ������b�Z�[�W�𑗂�

		break;

	case WM_KEYDOWN:	//�L�[��������Ă��郁�b�Z�[�W�𑗂�

		switch (wParam)
		{
		case VK_ESCAPE:	//ESC�L�[����������

			//���b�Z�[�W�{�b�N�X��\��
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	//�uWM_DESTROY�Ƃ������b�Z�[�W�𑗂�v
			}

			break;
		}

		break;

	case WM_COMMAND:

		break;

	case WM_LBUTTONDOWN:

		SetFocus(hWnd);

		break;

	case WM_CLOSE:

		//���b�Z�[�W�{�b�N�X��\��
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	//�uWM_DESTROY�Ƃ������b�Z�[�W�𑗂�v
		}
		else
		{
			return 0;
		}

		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//����̏�����Ԃ�
}

//************************************************
//�����������֐�
//************************************************
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindiw)
{
	D3DDISPLAYMODE d3ddm;			//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));	//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;						//�Q�[���T�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						//�Q�[���T�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindiw;									//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���1
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3D�f�o�C�X�̐���2
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3D�f�o�C�X�̐���3
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�H(�R�s�y)
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�R���g���[���̏���������
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 25, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Termina", &g_pFont);

	g_mode = MODE_TITLE;

	//�T�E���h�̏���������
	InitSound(hWnd);

	//���[�h�̏���ݒ�
	Init_Fade();
	Setinfo_Mode(g_mode);

	return S_OK;
}

//************************************************
//�I�������֐�
//************************************************
void UnInit(void)
{
	//����\��߂�(�����Uninit���ň�ԏ��)
	timeEndPeriod(1);

	//�����Q�̏�����
	Uninit_Fade();
	Uninit_Title();
	Uninit_Menu();
	//Uninit_Tutorial();
	Uninit_Ranking();
	Uninit_Game();
	Uninit_Result();

	//�L�[�{�[�h�̏I������
	UnInitKeyboard();

	//�R���g���[���̏I������
	UninitJoypad();

	//�T�E���h�̏I������
	UninitSound();

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//�f�o�b�O�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
}

//************************************************
//�X�V�����֐�
//************************************************
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�R���g���[���̍X�V����
	UpdateJoypad();

	//���[�h�ɍ��킹�ĉ�ʍX�V����
	Update_Fade();
	switch (g_mode)
	{
		//�^�C�g�����[�h�̎�
	case MODE_TITLE:

		Update_Title();

		break;

		//���j���[���[�h�̎�
	case MODE_MENU:

		Update_Menu();

		break;

		//�`���[�g���A�����[�h�̎�
	case MODE_TUTORIAL:

		//Update_Tutorial();

		break;

		//�����L���O���[�h�̎�
	case MODE_RANKING:

		Update_Ranking();

		break;

		//�Q�[�����[�h�̎�
	case MODE_GAME:

		Update_Game();

		break;

		//���U���g���[�h�̎�
	case MODE_RESULT:

		Update_Result();

		break;
	}
}

//************************************************
//�`�揈���֐�
//************************************************
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@�ƂȂ񂩃o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//���[�h�ɍ��킹�ĉ�ʕ`�揈��
		switch (g_mode)
		{
			//�^�C�g�����[�h�̎�
		case MODE_TITLE:

			Draw_Title();

			break;

			//���j���[���[�h�̎�
		case MODE_MENU:

			Draw_Menu();

			break;

			//�`���[�g���A�����[�h�̎�
		case MODE_TUTORIAL:

			//Draw_Tutorial();

			break;

			//�����L���O���[�h�̎�
		case MODE_RANKING:

			Draw_Ranking();

			break;

			//�Q�[�����[�h�̎�
		case MODE_GAME:

			Draw_Game();

			break;

			//���U���g���[�h�̎�
		case MODE_RESULT:

			Draw_Result();

			break;
		}
		Draw_Fade();

#ifdef _DEBUG
		
		//FPS�cetc�̕`��
		DrawFPS();
		
#endif // DEBUG

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//************************************************
//FPS�\�������֐�
//************************************************
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[MAX_WORD];

	PLAYER* pPlayer = GetInfo_Player();
	TOWER* pTower = GetInfo_Tower();
	char aStrpos[16][MAX_WORD];
	snprintf(&aStrpos[0][0], MAX_WORD, "%.1f", pPlayer->BGpos.x);
	snprintf(&aStrpos[1][0], MAX_WORD, "%.1f", pPlayer->BGpos.y);
	snprintf(&aStrpos[2][0], MAX_WORD, "%.1f", pPlayer->BGpos.z);
	snprintf(&aStrpos[3][0], MAX_WORD, "%.1f", pPlayer->pos.x);
	snprintf(&aStrpos[4][0], MAX_WORD, "%.1f", pPlayer->pos.y);
	snprintf(&aStrpos[5][0], MAX_WORD, "%.1f", pPlayer->pos.z);
	snprintf(&aStrpos[6][0], MAX_WORD, "%.1f", pPlayer->lastland.x);
	snprintf(&aStrpos[7][0], MAX_WORD, "%.1f", pPlayer->lastland.y);
	snprintf(&aStrpos[8][0], MAX_WORD, "%.1f", pPlayer->lastland.z);

	//������ɑ��
	wsprintf(&aStr[0], "FPS�F%d\n\n[A/D]�F�ړ�\n[SPACE]�F�W�����v �c��񐔁F%d\n[I]�F�U�� �R���{�P�\�F%d �i�F%d\n[P]�F�|�[�Y\n\n[8]�F�^���[�����C�t1����\n���݂̃^���[���C�t(%d)\n\n�����W(%sf,%sf,%sf)\n������(%sf,%sf,%sf)\n���n�_(%sf,%sf,%sf)"
		, g_nCountFPS, pPlayer->nJumpTimes, pPlayer->nCntAfterATK, pPlayer->nLastATK - 6, pTower->nLife, &aStrpos[0][0], &aStrpos[1][0], &aStrpos[2][0], &aStrpos[3][0], &aStrpos[4][0], &aStrpos[5][0], &aStrpos[6][0], &aStrpos[7][0], &aStrpos[8][0]);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//************************************************
//���[�h�ύX�����֐�
//************************************************
void Setinfo_Mode(MODE mode)
{
	//�܂��͌��݂̃��[�h�̏I������
	switch (g_mode)
	{
		//�^�C�g�����[�h�̎�
	case MODE_TITLE:

		Uninit_Title();

		break;

		//���j���[���[�h�̎�
	case MODE_MENU:

		Uninit_Menu();

		break;

		//�`���[�g���A�����[�h�̎�
	case MODE_TUTORIAL:

		//Uninit_Tutorial();

		break;

		//�����L���O���[�h�̎�
	case MODE_RANKING:

		Init_Ranking();

		break;

		//�Q�[�����[�h�̎�
	case MODE_GAME:

		Uninit_Game();

		break;

		//���U���g���[�h�̎�
	case MODE_RESULT:

		Uninit_Result();

		break;
	}

	//���ɕύX��̃��[�h��������
	switch (mode)
	{
		//�^�C�g�����[�h�̎�
	case MODE_TITLE:

		Init_Title();

		break;

		//���j���[���[�h�̎�
	case MODE_MENU:

		Init_Menu();

		break;

		//�`���[�g���A�����[�h�̎�
	case MODE_TUTORIAL:

		//Init_Tutorial();

		break;

		//�����L���O���[�h�̎�
	case MODE_RANKING:

		Init_Ranking();

		break;

		//�Q�[�����[�h�̎�
	case MODE_GAME:

		Init_Game();

		break;

		//���U���g���[�h�̎�
	case MODE_RESULT:

		Init_Result();

		break;
	}

	g_mode = mode;	//���݂̃��[�h���㏑��
}

//************************************************
//�Q�[���I������
//************************************************
bool* Getinfo_End(void)
{
	return &g_bExit;	//���݂̃��[�h�������n��
}