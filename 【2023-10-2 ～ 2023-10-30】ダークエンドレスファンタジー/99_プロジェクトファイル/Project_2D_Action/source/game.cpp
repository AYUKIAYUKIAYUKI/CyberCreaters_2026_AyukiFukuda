//************************************************
//
//ゲーム処理[game.cpp]
//Author：福田歩希
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

//グローバル変数
bool g_aPause;	//ポーズ判定
static int g_nChoose;	//何を選択しているか

//************************************************
//ゲーム初期化処理関数
//************************************************
void Init_Game()
{
	//フェード情報用
	FADE* pFade = GetInfo_Fade();

	//フェードイン開始
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
//ゲーム終了処理関数
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
//ゲーム更新処理関数
//************************************************
void Update_Game(void)
{
	/*ボツ*/
	//int* pScore = GetInfo_Score();
	//pScore[SCORE_OLD] = pScore[SCORE_NEW];
	//int* pS_A_CT = GetInfo_S_A_CT();

	//フェード情報用
	FADE* pFade = GetInfo_Fade();
	PLAYER* pPlayer = GetInfo_Player();
	TOWER* pTower = GetInfo_Tower();
	int* pTimer = GetInfo_Timer();

	//フェードイン後
	if (pFade->col.a <= 0.0f)
	{
		if (!g_aPause)
		{
			//※フェードイン後にタワーのライフが0になるか、制限時間経過で
			if (pTower->nLife <= 0 || *pTimer <= 0)
			{
				//フェードアウト開始
				pFade->bFadeIn = false;
				pFade->bFadeOut = true;

				g_nChoose = RESULT;

				//スコアを記録したりする
				Save_Score();
			}

			//ポーズ
			if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START) || GetJoypadTrigger(JOYKEY_BACK))
			{
				g_aPause = !g_aPause;
				PlaySound(SOUND_LABEL_CHOOSE);
				g_nChoose = CONTINUE;
			}
		}
		else
		{
			//項目切り替え
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

			//決定
			if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A) || GetJoypadTrigger(JOYKEY_START) || GetJoypadTrigger(JOYKEY_BACK))
			{
				if (g_nChoose != CONTINUE)
				{
					PlaySound(SOUND_LABEL_DEFINE);
					//フェードアウト開始
					pFade->bFadeIn = false;
					pFade->bFadeOut = true;
				}
				else
				{
					PlaySound(SOUND_LABEL_DEFINE);
					//ポーズ解除
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

	//フェードアウト後
	if (pFade->col.a >= 1.0f)
	{
		//選択項目に合わせてモード切り替えなど
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

	/*ボツ*/
	//if (pScore[SCORE_OLD] != pScore[SCORE_NEW])
	//{
	//	*pS_A_CT = 10;
	//}
}

//************************************************
//ゲーム描画処理関数
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
	/*デバッグ用…？*/
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
//ポーズメニュー選択項目を引き渡す
//************************************************
int* Getinfo_Choose_Pause_Menu(void)
{
	return &g_nChoose;
}

//************************************************
//スコアを記録したりする関数
//************************************************
void Save_Score(void)
{
	int nHold[SCORE_RANKING_STYLE_MAX];
	for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
	{
		nHold[i] = 0;
	}

	//まずは前回のスコアを取得
	FILE* pFile;
	pFile = fopen("data\\txt\\ranking.txt", "r");

	if (pFile != NULL)
	{
		for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
		{
			fscanf(pFile, "%d", &nHold[i]);
		}

		//ファイルを閉じる
		fclose(pFile);
	}

	//(今回スコアがハイスコアを越えているなら更新)
	int* pScore = GetInfo_Score();
	nHold[SCORE_RANKING_HIGH] < pScore[SCORE_NEW] ? nHold[SCORE_RANKING_HIGH] = pScore[SCORE_NEW] : 0;

	//ラストスコアを置き換える
	nHold[SCORE_RANKING_LAST] = pScore[SCORE_NEW];

	//変更されたスコアデータを書き込んで終了
	pFile = fopen("data\\txt\\ranking.txt", "w");

	if (pFile != NULL)
	{
		for (int i = 0; i < SCORE_RANKING_STYLE_MAX; i++)
		{
			fprintf(pFile, "%d\n", nHold[i]);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}