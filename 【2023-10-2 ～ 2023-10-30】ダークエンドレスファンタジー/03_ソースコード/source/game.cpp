//************************************************
//
//�Q�[������[game.cpp]
//Author�F���c����
//
//************************************************
#include "main.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "attack_box.h"
#include "attack_box_enemy.h"
#include "back.h"
#include "bg.h"
#include "bomb.h"
#include "colon.h"
#include "cursor_game.h"
#include "effect_jump.h"
#include "enemy.h"
//#include "gage_life.h"
#include "gauge_tower.h"
#include "particle.h"
#include "player.h"
#include "score.h"
#include "skill.h"
#include "stage.h"
#include "text_game.h"
#include "timer.h"
#include "tower.h"
#include "window_game.h"
#include "score_ranking.h"

//�O���[�o���ϐ�
bool g_aPause;	//�|�[�Y����
static int g_nChoose;	//����I�����Ă��邩

//************************************************
//�Q�[�������������֐�
//************************************************
void Init_Game()
{
	//�t�F�[�h���p
	FADE* pFade = GetInfo_Fade();

	//�t�F�[�h�C���J�n
	pFade->bFadeIn = true;
	pFade->bFadeOut = false;

	Init_Attack_Box();
	Init_Attack_Box_Enemy();
	Init_BG(BG_TYPE_GAME);
	Init_Bomb();
	Init_Cursor_Game();
	Init_Effect_Jump();
	Init_Enemy();
	//Init_Gage_Life();
	Init_Gauge_Tower();
	Init_Particle();
	Init_Player();
	Init_Score(SCORE_TYPE_GAME);
	Init_Skill();
	Init_Stage();
	Init_Text_Game();
	Init_Timer();
	Init_Back();
	Init_Colon();
	Init_Tower();
	Init_Window_Game();

	g_aPause = false;

	g_nChoose = CONTINUE;

	PlaySound(SOUND_LABEL_BATTLE);
}

//************************************************
//�Q�[���I�������֐�
//************************************************
void Uninit_Game(void)
{
	Uninit_Attack_Box();
	Uninit_Attack_Box_Enemy();
	Uninit_Back();
	Uninit_BG();
	Uninit_Bomb();
	Uninit_Colon();
	Uninit_Cursor_Game();
	Uninit_Effect_Jump();
	Uninit_Enemy();
	//Uninit_Gage_Life();
	Uninit_Gauge_Tower();
	Uninit_Particle();
	Uninit_Player();
	Uninit_Score();
	Uninit_Skill();
	Uninit_Stage();
	Uninit_Text_Game();
	Uninit_Timer();
	Uninit_Tower();
	Uninit_Window_Game();

	StopSound();
}

//************************************************
//�Q�[���X�V�����֐�
//************************************************
void Update_Game(void)
{
	/*�{�c*/
	//int* pScore = GetInfo_Score();
	//pScore[SCORE_OLD] = pScore[SCORE_NEW];
	//int* pS_A_CT = GetInfo_S_A_CT();

	//�t�F�[�h���p
	FADE* pFade = GetInfo_Fade();
	PLAYER* pPlayer = GetInfo_Player();
	TOWER* pTower = GetInfo_Tower();
	int* pTimer = GetInfo_Timer();

	//�t�F�[�h�C����
	if (pFade->col.a <= 0.0f)
	{
		if (!g_aPause)
		{
			//���t�F�[�h�C����Ƀ^���[�̃��C�t��0�ɂȂ邩�A�������Ԍo�߂�
			if (pTower->nLife <= 0 || *pTimer <= 0)
			{
				//�t�F�[�h�A�E�g�J�n
				pFade->bFadeIn = false;
				pFade->bFadeOut = true;

				g_nChoose = RESULT;

				//�X�R�A���L�^�����肷��
				Save_Score();
			}

			//�|�[�Y
			if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START) || GetJoypadTrigger(JOYKEY_BACK))
			{
				g_aPause = !g_aPause;
				PlaySound(SOUND_LABEL_CHOOSE);
				g_nChoose = CONTINUE;
			}
		}
		else
		{
			//���ڐ؂�ւ�
			if (GetKeyboardTrigger(DIK_UP) || GetJoypadTrigger(JOYKEY_UP))
			{
				g_nChoose <= CONTINUE ? g_nChoose = RETIRE : g_nChoose--;
				PlaySound(SOUND_LABEL_CHOOSE);
			}
			else if (GetKeyboardTrigger(DIK_DOWN) || GetJoypadTrigger(JOYKEY_DOWN))
			{
				g_nChoose >= RETIRE ? g_nChoose = CONTINUE : g_nChoose++;
				PlaySound(SOUND_LABEL_CHOOSE);
			}

			//����
			if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_START) || GetJoypadTrigger(JOYKEY_BACK))
			{
				if (g_nChoose != CONTINUE)
				{
					PlaySound(SOUND_LABEL_DEFINE);
					//�t�F�[�h�A�E�g�J�n
					pFade->bFadeIn = false;
					pFade->bFadeOut = true;
				}
				else
				{
					PlaySound(SOUND_LABEL_DEFINE);
					//�|�[�Y����
					g_aPause = !g_aPause;
				}
			}
		}
	}

	if (!g_aPause)
	{
		Update_Attack_Box();
		Update_Attack_Box_Enemy();
		Update_BG();
		Update_Bomb();
		Update_Effect_Jump();
		Update_Enemy();
		//Update_Gage_Life();
		Update_Gauge_Tower();
		Update_Particle();
		Update_Player();
		Update_Score();
		Update_Skill();
		Update_Stage();
		Update_Timer();
		Update_Tower();
	}
	else
	{
		Update_Cursor_Game();
		Update_Text_Game();
		Update_Window_Game();
	}

	//�t�F�[�h�A�E�g��
	if (pFade->col.a >= 1.0f)
	{
		//�I�����ڂɍ��킹�ă��[�h�؂�ւ��Ȃ�
		switch (g_nChoose)
		{
		case RETRY:
			Setinfo_Mode(MODE_GAME);
			break;
		case RETIRE:
			Setinfo_Mode(MODE_TITLE);
			break;
		case RESULT:
			Setinfo_Mode(MODE_RESULT);
			break;
		}
	}

	/*�{�c*/
	//if (pScore[SCORE_OLD] != pScore[SCORE_NEW])
	//{
	//	*pS_A_CT = 10;
	//}
}

//************************************************
//�Q�[���`�揈���֐�
//************************************************
void Draw_Game(void)
{
	Draw_BG();
	Draw_Effect_Jump();
	Draw_Tower();
	Draw_Player();
	Draw_Stage();
	Draw_Particle();
	Draw_Enemy();
	Draw_Bomb();
	/*�f�o�b�O�p�c�H*/
	Draw_Attack_Box_Debug();
	Draw_Attack_Box_Enemy_Debug();
	//Draw_Gage_Life();
	Draw_Gauge_Tower();
	Draw_Back();
	Draw_Colon();
	Draw_Score();
	Draw_Skill();
	Draw_Timer();
	if (g_aPause)
	{
		Draw_Window_Game();
		Draw_Cursor_Game();
		Draw_Text_Game();
	}
}

//************************************************
//�|�[�Y���j���[�I�����ڂ������n��
//************************************************
int* Getinfo_Choose_Pause_Menu(void)
{
	return &g_nChoose;
}

//************************************************
//�X�R�A���L�^�����肷��֐�
//************************************************
void Save_Score(void)
{
	int nHold[SCORE_RANKING_STYLE_MAX];
	for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
	{
		nHold[i] = 0;
	}

	//�܂��͑O��̃X�R�A���擾
	FILE* pFile;
	pFile = fopen("data\\txt\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
		{
			fscanf(pFile, "%d", &nHold[i]);
		}

		//�t�@�C�������
		fclose(pFile);
	}

	//(����X�R�A���n�C�X�R�A���z���Ă���Ȃ�X�V)
	int* pScore = GetInfo_Score();
	nHold[SCORE_RANKING_HIGH] < pScore[SCORE_NEW] ? nHold[SCORE_RANKING_HIGH] = pScore[SCORE_NEW] : 0;

	//���X�g�X�R�A��u��������
	nHold[SCORE_RANKING_LAST] = pScore[SCORE_NEW];

	//�ύX���ꂽ�X�R�A�f�[�^����������ŏI��
	pFile = fopen("data\\txt\\ranking.txt", "w");

	if (pFile != NULL)
	{
		for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
		{
			fprintf(pFile, "%d\n", nHold[i]);
		}

		//�t�@�C�������
		fclose(pFile);
	}
}