//************************************************
//
//ゲーム動作処理[game.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"
#include "main.h"
#include "sound.h"
#include "bg.h"
#include "block.h"
#include "breakblock.h"
#include "bullet.h"
#include "bush.h"
#include "effect_bullet.h"
#include "effect_comet.h"
#include "effect_spawn.h"
#include "enemy.h"
#include "enemy_glide.h"
#include "enemy_slide.h"
#include "enemy_spiral.h"
#include "fg.h"
#include "guage.h"
#include "guagebar.h"
#include "item.h"
#include "leaves.h"
#include "life.h"
#include "particle.h"
#include "particle_block.h"
#include "pause.h"
#include "player.h"
#include "score.h"
#include "slideblock.h"
#include "style.h"
#include "timer.h"
#include "window_bullet.h"
#include "wreath.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Game = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Game = NULL;	//頂点バッファのポインタ
int g_nColorA_Fade_Gmae = 255;	//フェード用アルファ値格納
bool g_bStart_Game = false;
int g_nFreeze_Game = 0;		//ゲームを止める
bool g_bStop_Gmae = false;	//ポーズ画面用

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Game(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_GAME,
		&g_pTexture_Game);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_GAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Game,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Game->Lock(0, 0, (void**)&pVtx_Game, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAME; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Game[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Game[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Game[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Game[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Game[0].rhw = 1.0f;
		pVtx_Game[1].rhw = 1.0f;
		pVtx_Game[2].rhw = 1.0f;
		pVtx_Game[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Game[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Game[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Game[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Game[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Game[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Game[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Game[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Game[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Game += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Game->Unlock();

	//ポリゴンの初期化処理
	Init_BG();
	Init_Block();
	Init_BreakBlock();
	Init_Bullet();
	Init_Bush();
	Init_Effect_Bullet();
	Init_Effect_Comet();
	Init_Effect_Spawn();
	Init_Enemy();
	Init_Enemy_Glide();
	Init_Enemy_Slide();
	Init_Enemy_Spiral();
	Init_FG();
	Init_Guage();
	Init_GuageBar();
	Init_Item();
	Init_Leaves();
	Init_Life();
	Init_Particle();
	Init_Particle_Block();
	Init_Pause();
	Init_Player();
	Init_Score();
	Init_SlideBlock();
	Init_Style();
	Init_Timer();
	Init_Window_Bullet();
	Init_Wreath();

	//フェード初期設定
	g_nColorA_Fade_Gmae = 255;

	g_bStart_Game = false;

	//死後硬直初期化
	g_nFreeze_Game = 0;

	//ポーズ初期化
	g_bStop_Gmae = false;

	//初回のみポリゴンを展開
	SetPos_Vtx_Game();

	PlaySound(SOUND_LABEL_BGM001);
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Game(void)
{
	//ポリゴンの終了処理
	Uninit_BG();
	Uninit_Block();
	Uninit_BreakBlock();
	Uninit_Bullet();
	Uninit_Bush();
	Uninit_Effect_Bullet();
	Uninit_Effect_Comet();
	Uninit_Effect_Spawn();
	Uninit_Enemy();
	Uninit_Enemy_Glide();
	Uninit_Enemy_Slide();
	Uninit_Enemy_Spiral();
	Uninit_FG();
	Uninit_Guage();
	Uninit_GuageBar();
	Uninit_Item();
	Uninit_Leaves();
	Uninit_Life();
	Uninit_Particle();
	Uninit_Particle_Block();
	Uninit_Pause();
	Uninit_Player();
	Uninit_Score();
	Uninit_SlideBlock();
	Uninit_Style();
	Uninit_Timer();
	Uninit_Window_Bullet();
	Uninit_Wreath();

	//BGMを止める
	StopSound();
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Game(void)
{
	if (g_nColorA_Fade_Gmae > 0 && !g_bStart_Game)
	{
		//フェードインアニメーション
		Fadein_Animation_Game();

		//フェード中も地味に動いてて欲しい素材の皆さん
		Update_BG();
		Update_Bush();
		Update_FG();
		Update_Leaves();
	}
	else
	{
		//プレイヤー情報へのポインタ
		PLAYER* pPlayer;

		//制限時間情報へのポインタ
		int* pTimer;

		//プレイヤー情報の取得
		pPlayer = Getinfo_Player();	//プレイヤー情報系の先頭アドレスが代入される

		//残り時間の取得
		pTimer = Getinfo_Timer();	//アドレス代入

		//プレイヤーが生きているときポーズ可能
		if (!g_bStop_Gmae && GetKeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_START) == true
			|| GetJoypadTrigger(JOYKEY_BACK) == true && pPlayer->nCntState != PLAYERSTATE_DEATH)
		{
			g_bStop_Gmae = true;

			//効果音を鳴らす
			PlaySound(SOUND_LABEL_SE_PAUSE);

			//ポーズ処理もう一度
			//Init_Pause();
		}
		else if (g_bStop_Gmae)
		{
			Update_Pause();
		}

		//通常時
		if (!g_bStop_Gmae)
		{
			//プレイヤーが死ぬか、タイマーが0で
			if (pPlayer->state == PLAYERSTATE_DEATH || *pTimer <= 0)
			{
				//遅延カウント
				g_nFreeze_Game++;
			}
			//ゲーム通常進行時の処理
			else
			{
				//ポリゴンの更新処理
				Update_BG();
				Update_Block();
				Update_BreakBlock();
				Update_Bullet();
				Update_Bush();
				Update_Effect_Bullet();
				Update_Effect_Comet();
				Update_Effect_Spawn();
				Update_Enemy();
				Update_Enemy_Glide();
				Update_Enemy_Slide();
				Update_Enemy_Spiral();
				Update_FG();
				Update_Guage();
				Update_Item();
				Update_Leaves();
				Update_Particle();
				Update_Particle_Block();
				Update_Score();
				Update_SlideBlock();
				Update_Style();
			}

			//0になるのを見せるため
			Update_Timer();

			//ライフが空になる表示のため
			Update_Life(pPlayer->nLife);

			//死亡時の見た目に変更するため
			Update_Player();

			//遅延終了
			if (g_nFreeze_Game >= AMOUNT_CNT_FINISH_GAME)
			{
				Fadeout_Animation_Game();

				if (g_nColorA_Fade_Gmae >= 255)
				{
					Setinfo_Mode(MODE_RANKING);	//ランキングモードに設定
				}
			}
		}
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Game(void)
{
	Draw_BG();
	Draw_Block();
	Draw_SlideBlock();
	Draw_BreakBlock();
	Draw_Effect_Bullet();
	Draw_Effect_Comet();
	Draw_Effect_Spawn();
	Draw_Enemy();
	Draw_Enemy_Glide();
	Draw_Enemy_Slide();
	Draw_Enemy_Spiral();
	Draw_Bullet();
	Draw_Item();
	Draw_Particle();
	Draw_Particle_Block();
	Draw_Player();

	Draw_Leaves();

	Draw_Bush();
	Draw_FG();

	//レイヤー遵守
	Draw_Wreath();
	Draw_Guage();
	Draw_GuageBar();
	Draw_Style();
	Draw_Window_Bullet();
	Draw_Life();
	
	//ポーズされているとき画面覆う
	if (g_bStop_Gmae)
	{
		Draw_Pause();
	}

	//ポーズ表示よりも優先表示
	Draw_Score();
	Draw_Timer();

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Game, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Game);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//頂点を展開する関数
//************************************************
void SetPos_Vtx_Game(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Game->Lock(0, 0, (void**)&pVtx_Game, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAME; nCnt++)
	{
		pVtx_Game[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Game[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx_Game[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx_Game[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		pVtx_Game[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
		pVtx_Game[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
		pVtx_Game[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
		pVtx_Game[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);

		pVtx_Game += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Game->Unlock();
}

//************************************************
//フェードイン関数
//************************************************
void Fadein_Animation_Game(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Game->Lock(0, 0, (void**)&pVtx_Game, 0);

	g_nColorA_Fade_Gmae -= CHANGE_SPD_FADE_COLORA_GAME;

	//色変わりすぎ防止
	if (g_nColorA_Fade_Gmae <= 0)
	{
		g_bStart_Game = true;

		g_nColorA_Fade_Gmae = 0;
	}

	//色変更
	pVtx_Game[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);

	//頂点バッファをアンロックする
	g_pVtxBuff_Game->Unlock();
}

//************************************************
//フェードアウト関数
//************************************************
void Fadeout_Animation_Game(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Game;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Game->Lock(0, 0, (void**)&pVtx_Game, 0);

	g_nColorA_Fade_Gmae += CHANGE_SPD_FADE_COLORA_GAME;

	//色変わりすぎ防止
	if (g_nColorA_Fade_Gmae >= 255)
	{
		g_nColorA_Fade_Gmae = 255;
	}

	//色変更
	pVtx_Game[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);
	pVtx_Game[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fade_Gmae);

	//頂点バッファをアンロックする
	g_pVtxBuff_Game->Unlock();
}

//************************************************
//ポーズのcppにboolのアドレス渡すだけの関数
//************************************************
bool* Getinfo_Pause(void)
{
	return &g_bStop_Gmae;	//ポーズの判定する変数のアドレスを渡す
}