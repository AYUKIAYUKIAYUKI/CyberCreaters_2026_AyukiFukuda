//************************************************
//
//タイトル表示処理[title.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"
#include "sound.h"
#include "title.h"
#include "line_titleh.h"
#include "particle_titlelogo.h"

/*なぜヘッダーに置けない？*/
//歯車回転用構造体
typedef struct
{
	D3DXVECTOR3 pos;	//中心点情報を格納
	D3DXVECTOR3 rot;	//向き情報を格納
	float fLength;		//対角線を格納
	float fAngle;		//対角線の角度を格納
}GEARS_ROTATE_TITLE;

/*なぜヘッダーに置けない？*/
//偽ハト回転用(?)構造体
typedef struct
{
	D3DXVECTOR3 pos;	//中心点情報を格納
	D3DXVECTOR3 move;	//移動情報を格納
	D3DXVECTOR3 rot;	//向き情報を格納
	float fLength;		//対角線を格納
	float fAngle;		//対角線の角度を格納
	float fMoveSPD1;
	float fMoveSPD2;
	float fMoveSPD3;
	int nCntStop;
}PIGEONS_ROTATE_TITLE;

typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	float fSpanX;		//サイズ
	float fSpanY;		//サイズ
	D3DXVECTOR3 move;	//移動情報
	D3DXVECTOR3 rot;	//向き情報
	D3DXCOLOR col;		//色
	float fLength;		//対角線
	float fAngle;		//角度
	bool bfirst;
	int nCntfirst;
	bool bsecond;
	int nCntsecond;
	float fHoldX;
	float fHoldY;
	float fHoldZ;
	bool bthird;
	int nCntthird;
	bool bTurnX;
	bool bTurnY;
	bool bTurnZ;
	int nCntStop;
}LOGO_EX;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Title[AMOUNT_TEXTURE_TITLE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Title = NULL;	//頂点バッファのポインタ
int g_nColorA_Flash_Title = 0;	//閃光色変更用
float g_fPosX_TitleLogo = 0.0f;	//タイトルロゴ座標用
float g_fTexU_TitleLogo = 0.0f;	//タイトルロゴテクスチャ用
int g_nColorA_Roses_Title = 0;	//バラ色変更用
float g_fPosY_Curtain_Title[AMOUNT_USING_TEX_ROSES_TITLE] = {};		//カーテン座標用
float g_fPosX_Garland1_Title[AMOUNT_USING_TEX_GARLAND1_TITLE] = {};	//ガーランド1座標用
float g_fPosY_Kanzashi_Title = 0.0f;	//かんざし座標用
float g_fPosY_Brooch_Title = 0.0f;		//ブローチ座標用
float g_fPosY_Gear_Title = 0.0f;		//歯車座標用
float g_fPosY_Pendant_Title = 0.0f;		//ペンダント座標用
float g_fPosY_Garland2_Title = 0.0f;	//ガーランド2座標用
GEARS_ROTATE_TITLE g_aGears_Title[AMOUNT_USING_TEX_GEARS_TITLE];		//歯車群回転用
PIGEONS_ROTATE_TITLE g_aPigeons_Title[AMOUNT_USING_TEX_PIGEONS_TITLE];	//偽ハト回転用(?)
int g_nColorA_Press_Title = 0;	//入力勧告色変更用
bool g_bChangeColor_Press_Title = false;	//入力勧告色変更開始判定用
int g_nColorA_Fadeout_Title = 0;	//フェードアウト用アルファ値格納
bool g_bStartFadeout_Title = false;	//フェードアウト開始判定用
bool g_bStartRotate = false;		//回転開始判定
bool g_bTurn_1 = false;
bool g_bTurn_2 = false;
int g_nCntBright = 0;
//float g_fVolume_BGM_Title = 0.0f;
LOGO_EX g_aLogoEX;

//************************************************
//初期化処理関数
//************************************************
void Init_Title(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SKY_TITLE,
		&g_pTexture_Title[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CLOUD1_TITLE,
		&g_pTexture_Title[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CLOUD2_TITLE,
		&g_pTexture_Title[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CLOUD3_TITLE,
		&g_pTexture_Title[3]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ROSES_TITLE,
		&g_pTexture_Title[4]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ROSES_TITLE,
		&g_pTexture_Title[5]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GARLAND2_TITLE,
		&g_pTexture_Title[6]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GARLAND2_TITLE,
		&g_pTexture_Title[7]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GARLAND1_TITLE,
		&g_pTexture_Title[8]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GARLAND1_TITLE,
		&g_pTexture_Title[9]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PENDANT_TITLE,
		&g_pTexture_Title[10]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEAR_TITLE,
		&g_pTexture_Title[11]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BROOCH_TITLE,
		&g_pTexture_Title[12]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_KANZASHI_TITLE,
		&g_pTexture_Title[13]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CURTAIN_TITLE,
		&g_pTexture_Title[14]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CURTAIN_TITLE,
		&g_pTexture_Title[15]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PIGEON1_TITLE,
		&g_pTexture_Title[16]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PIGEON2_TITLE,
		&g_pTexture_Title[17]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARBIG_TITLE,
		&g_pTexture_Title[18]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARBIG_TITLE,
		&g_pTexture_Title[19]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARFRAME_TITLE,
		&g_pTexture_Title[20]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARFRAME_TITLE,
		&g_pTexture_Title[21]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARFRAME_TITLE,
		&g_pTexture_Title[22]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARFRAME_TITLE,
		&g_pTexture_Title[23]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARSMALL_TITLE,
		&g_pTexture_Title[24]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GEARSMALL_TITLE,
		&g_pTexture_Title[25]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LOGO_TITLE,
		&g_pTexture_Title[26]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PRESS_TITLE,
		&g_pTexture_Title[27]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_WHITE_TITLE,
		&g_pTexture_Title[28]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_BLACK_TITLE,
		&g_pTexture_Title[29]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Title,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	//初期位置設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TITLE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Title[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Title[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Title[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Title[0].rhw = 1.0f;
		pVtx_Title[1].rhw = 1.0f;
		pVtx_Title[2].rhw = 1.0f;
		pVtx_Title[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Title[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Title[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Title[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Title[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//ポインタをずらす
		pVtx_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();

	//閃光初期色
	g_nColorA_Flash_Title = 255;

	//タイトルロゴ初期座標
	g_fPosX_TitleLogo = 0.0f;

	//タイトルロゴ初期テクスチャサイズ
	g_fTexU_TitleLogo = 0.5f;

	//バラ初期色
	g_nColorA_Roses_Title = 0;

	//カーテン初期座標
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_ROSES_TITLE; nCnt++)
	{
		g_fPosY_Curtain_Title[nCnt] = {};
	}

	//ガーランド1初期座標
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GARLAND1_TITLE; nCnt++)
	{
		g_fPosX_Garland1_Title[nCnt] = {};
	}

	//かんざし初期座標
	g_fPosY_Kanzashi_Title = 0.0f;

	//ブローチ初期座標
	g_fPosY_Brooch_Title = 0.0f;

	//歯車初期座標
	g_fPosY_Gear_Title = 0.0f;

	//ペンダント初期座標
	g_fPosY_Pendant_Title = 0.0f;

	//ガーランド2初期座標
	g_fPosY_Garland2_Title = 0.0f;

	//歯車群初期設定
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GEARS_TITLE; nCnt++)
	{
		//回転させる為に中心点を設定
		switch (nCnt)
		{
		case 0:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(-151.0f - HALFSPAN_GEARBIG_TITLE, 855.0f + HALFSPAN_GEARBIG_TITLE, 0.0);

			break;

		case 1:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH + 151.0f + HALFSPAN_GEARBIG_TITLE, 855.0f + HALFSPAN_GEARBIG_TITLE, 0.0);

			break;

		case 2:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(-200.0f - HALFSPAN_GEARFRAME_TITLE, 800.0f + HALFSPAN_GEARFRAME_TITLE, 0.0f);

			break;

		case 3:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(275.0f - HALFSPAN_GEARFRAME_TITLE, SCREEN_HEIGHT + 200.0f + HALFSPAN_GEARFRAME_TITLE, 0.0f);

			break;

		case 4:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH + 200.0f + HALFSPAN_GEARFRAME_TITLE, 800.0f + HALFSPAN_GEARFRAME_TITLE, 0.0f);

			break;

		case 5:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 275.0f + HALFSPAN_GEARFRAME_TITLE, SCREEN_HEIGHT + 200.0f + HALFSPAN_GEARFRAME_TITLE, 0.0f);

			break;

		case 6:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(137.0f - HALFSPAN_GEARSMALL_TITLE, SCREEN_HEIGHT + 206.0f - HALFSPAN_GEARSMALL_TITLE, 0.0f);

			break;

		case 7:

			g_aGears_Title[nCnt].pos = D3DXVECTOR3(SCREEN_WIDTH - 137.0f + HALFSPAN_GEARSMALL_TITLE, SCREEN_HEIGHT + 206.0f - HALFSPAN_GEARSMALL_TITLE, 0.0f);

			break;
		}

		g_aGears_Title[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0);

		switch(nCnt)
		{
		case 0:

			g_aGears_Title[nCnt].fLength = sqrtf(SPAN_GEARBIG_TITLE * SPAN_GEARBIG_TITLE + SPAN_GEARBIG_TITLE * SPAN_GEARBIG_TITLE) * 0.5f;
			g_aGears_Title[nCnt].fAngle = atan2f(SPAN_GEARBIG_TITLE, SPAN_GEARBIG_TITLE);

			for (int nCopy = nCnt + 1; nCopy < nCnt + AMOUNT_USING_TEX_GEARBIG_TITLE; nCopy++)
			{
				//同じ形のものに代入
				g_aGears_Title[nCopy].fLength = g_aGears_Title[nCnt].fLength;
				g_aGears_Title[nCopy].fAngle = g_aGears_Title[nCnt].fAngle;
			}

			break;

		case AMOUNT_USING_TEX_GEARBIG_TITLE:

			g_aGears_Title[nCnt].fLength = sqrtf(SPAN_GEARFRAME_TITLE * SPAN_GEARFRAME_TITLE + SPAN_GEARFRAME_TITLE * SPAN_GEARFRAME_TITLE) * 0.5f;
			g_aGears_Title[nCnt].fAngle = atan2f(SPAN_GEARFRAME_TITLE, SPAN_GEARFRAME_TITLE);

			for (int nCopy = nCnt + 1; nCopy < nCnt + AMOUNT_USING_TEX_GEARFRAME_TITLE; nCopy++)
			{
				//同じ形のものに代入
				g_aGears_Title[nCopy].fLength = g_aGears_Title[nCnt].fLength;
				g_aGears_Title[nCopy].fAngle = g_aGears_Title[nCnt].fAngle;
			}

			break;

		case AMOUNT_USING_TEX_GEARBIG_TITLE + AMOUNT_USING_TEX_GEARFRAME_TITLE:

			g_aGears_Title[nCnt].fLength = sqrtf(SPAN_GEARSMALL_TITLE * SPAN_GEARSMALL_TITLE + SPAN_GEARSMALL_TITLE * SPAN_GEARSMALL_TITLE) * 0.5f;
			g_aGears_Title[nCnt].fAngle = atan2f(SPAN_GEARSMALL_TITLE, SPAN_GEARSMALL_TITLE);

			for (int nCopy = nCnt + 1; nCopy < nCnt + AMOUNT_USING_TEX_GEARSMALL_TITLE; nCopy++)
			{
				//同じ形のものに代入
				g_aGears_Title[nCopy].fLength = g_aGears_Title[nCnt].fLength;
				g_aGears_Title[nCopy].fAngle = g_aGears_Title[nCnt].fAngle;
			}

			break;
		}
	}

	//偽ハト初期設定
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_PIGEONS_TITLE; nCnt++)
	{
		//回転させる為に中心点を設定
		switch (nCnt)
		{
		case 0:

			g_aPigeons_Title[nCnt].pos = D3DXVECTOR3(0.0f - HALF_SPAN_PIGEON1_X_TITLE, 850.0f, 0.0f);

			break;

		case 1:

			g_aPigeons_Title[nCnt].pos = D3DXVECTOR3(1980.0f + HALF_SPAN_PIGEON2_X_TITLE, 800.0f, 0.0f);

			break;
		}

		g_aPigeons_Title[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0);
		g_aPigeons_Title[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0);

		switch (nCnt)
		{
		case 0:

			g_aPigeons_Title[nCnt].fLength = sqrtf(SPAN_PIGEON1_X_TITLE * SPAN_PIGEON1_X_TITLE + SPAN_PIGEON1_Y_TITLE * SPAN_PIGEON1_Y_TITLE) * 0.5f;
			g_aPigeons_Title[nCnt].fAngle = atan2f(SPAN_PIGEON1_X_TITLE, SPAN_PIGEON1_Y_TITLE);

			g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_1_X;
			g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_1_Y;
			g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_1_Z;
			
			break;

		case 1:

			g_aPigeons_Title[nCnt].fLength = sqrtf(SPAN_PIGEON2_X_TITLE * SPAN_PIGEON2_X_TITLE + SPAN_PIGEON2_Y_TITLE * SPAN_PIGEON2_Y_TITLE) * 0.5f;
			g_aPigeons_Title[nCnt].fAngle = atan2f(SPAN_PIGEON2_X_TITLE, SPAN_PIGEON2_Y_TITLE);

			g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_2_X;
			g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_2_Y;
			g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_2_Z;

			break;
		}

		g_aPigeons_Title[nCnt].nCntStop = 0 + (30 * nCnt);
	}

	//入力勧告初期色
	g_nColorA_Press_Title = 0;

	//フェードアウト初期色
	g_nColorA_Fadeout_Title = 0;

	g_bStartFadeout_Title = false;

	g_bStartRotate = false;

	g_bTurn_1 = false;
	g_bTurn_2 = false;

	g_nCntBright = 0;

	//タイトルロゴ情報を初期化
	g_aLogoEX.nStyle = 0;	//種類
	g_aLogoEX.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	g_aLogoEX.fSpanX = 0.0f;	//サイズ
	g_aLogoEX.fSpanY = 0.0f;	//サイズ
	g_aLogoEX.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動情報
	g_aLogoEX.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き情報
	g_aLogoEX.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//色
	g_aLogoEX.fLength = 0.0f;	//対角線
	g_aLogoEX.fAngle = 0.0f;	//角度
	g_aLogoEX.bfirst = false;
	g_aLogoEX.nCntfirst = 0;
	g_aLogoEX.bsecond = false;
	g_aLogoEX.nCntsecond = 0;
	g_aLogoEX.fHoldX = 0.0f;
	g_aLogoEX.fHoldY = 0.0f;
	g_aLogoEX.fHoldZ = 0.0f;
	g_aLogoEX.bthird = false;
	g_aLogoEX.nCntthird = 0;
	g_aLogoEX.bTurnX = false;
	g_aLogoEX.bTurnY = false;
	g_aLogoEX.bTurnZ = false;
	g_aLogoEX.nCntStop = 0;

	//初回に一度ポリゴンを展開する
	SetPos_Vtx_Title();

	//タイトルロゴ情報を設定
	Setinfo_TitleLogoEX_Title();

	//BGMをかける
	PlaySound(SOUND_LABEL_BGM000);

	//初期化
	Init_Line_title();
	Init_Particle_Titlelogo();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Title(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TITLE; nCnt++)
	{
		if (g_pTexture_Title[nCnt] != NULL)
		{
			g_pTexture_Title[nCnt]->Release();
			g_pTexture_Title[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Title != NULL)
	{
		g_pVtxBuff_Title->Release();
		g_pVtxBuff_Title = NULL;
	}

	//BGMを止める
	StopSound();

	//終了
	Uninit_Line_title();
	Uninit_Particle_Titlelogo();
}

//************************************************
//更新処理関数
//************************************************
void Update_Title(void)
{
	//背景動き続ける
	BG_Animation_Title();

	//歯車群回り続ける
	Gears_Rotate_Title();

	if (g_nColorA_Flash_Title > 0)
	{
		//閃光アニメーション
		Flash_Animation_Title();
	}
	else
	{
		if (g_nColorA_Roses_Title < 255)
		{
			//バラアニメーション
			Roses_Animation_Title();
		}
		else
		{
			if (g_fPosY_Curtain_Title[1] < 275.0f)
			{
				//カーテンアニメーション
				Curtain_Animation_Title();
			}
			else
			{
				
				if (g_fPosX_Garland1_Title[1] < 729.0f)
				{
					//ガーランド1アニメーション
					Garland1_Animation_Title();
				}
				else
				{
					if (g_fPosY_Kanzashi_Title < 595.0f)
					{
						//かんざしアニメーション
						Kanzashi_Animation_Title();
					}
					else
					{
						if (g_fPosY_Brooch_Title < 585.0f)
						{
							//ブローチアニメーション
							Brooch_Animation_Title();
						}
						else
						{
							if (g_fPosY_Gear_Title < 447.0f)
							{
								//歯車アニメーション
								Gear_Animation_Title();
							}
							else
							{
								if (g_fPosY_Pendant_Title < 327.0f)
								{
									//ペンダントアニメーション
									Pendant_Animation_Title();
								}
								else
								{	
									if (g_fPosY_Garland2_Title < 519.0f)
									{
										//ガーランド2アニメーション
										Garland2_Animation_Title();
									}
								}
							}
						}
					}
				}
			}
		}

		if (g_aGears_Title[6].pos.y > 939.0f + HALFSPAN_GEARSMALL_TITLE)
		{
			//歯車群アニメーション
			Gears_Animation_Title();
		}
		else
		{
			if (g_aPigeons_Title[0].pos.x < 300.0f && !g_bStartRotate)
			{
				//偽ハトアニメーション
				Pigeons_Animation_Title();
			}
			else
			{
				//偽ハト可動
				Pigeons_Rotate_Title();
			}
		}

		if (g_fPosX_TitleLogo < SCREEN_WIDTH - (SCREENCENTER_X + HALF_X_LOGO_TITLE))
		{
			//タイトルロゴアニメーション
			TitleLogo_Animation_Title();
			//TitleLogo_AnimationEX_Title();
		}
		else
		{
			//キラキラ
			if (g_nCntBright > 10)
			{
				g_nCntBright = 0;

				Setinfo_Particle_Titlelogo(D3DXVECTOR3(463.0f + (float)(rand() % 924), 100.0f + (float)(rand() % 640), 0.0f));
			}
			else
			{
				g_nCntBright++;
			}

			//入力勧告アニメーション
			Press_Animation_Title();

			if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_START) == true
				|| GetJoypadTrigger(JOYKEY_A) == true && !g_bStartFadeout_Title)
			{
				g_bStartFadeout_Title = true;
			}
		}
	}

	//更新
	Update_Line_title();
	Update_Particle_Titlelogo();

	if (g_bStartFadeout_Title && g_nColorA_Fadeout_Title < 255)
	{
		//フェードアウト
		Fadeout_Animation_Title();
	}
	else if (g_nColorA_Fadeout_Title >= 255)
	{
		/*これは各アニメーションのバッファのアンロック後に行われるべきである、メモリ破壊*/

		Setinfo_Mode(MODE_MENU);	//メニューモードへ
	}

	///***********デバッグ用コマンド→ゲームへスキップ*********/
	//if (GetKeyboardTrigger(DIK_0) == true)
	//{
	//	Setinfo_Mode(MODE_GAME);	//ゲームモードへ
	//}
}

//************************************************
//描画処理関数
//************************************************
void Draw_Title(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Title, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_TITLE; nCnt++)
	{
		pDevice->SetTexture(0, g_pTexture_Title[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	//更新
	//Draw_Line_title();
	Draw_Particle_Titlelogo();
}

//************************************************
//頂点を展開する関数
//************************************************
void SetPos_Vtx_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	//各ポリゴン展開
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TITLE; nCnt++)
	{
		if (nCnt == 0 || nCnt == 1 || nCnt == 2 || nCnt == 3 || nCnt == SKIP_VTX_TO_WHITE_TITLE)
		{
			pVtx_Title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		else if (nCnt == SKIP_VTX_TO_ROSES_TITLE)
		{
			pVtx_Title[0].pos = D3DXVECTOR3(-45.0f, -58.0f, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(363.0f, -58.0f, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(-45.0f, 435.0f, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(363.0f, 435.0f, 0.0f);

			pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);

			pVtx_Title[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_Title[1].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx_Title[2].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_Title[3].tex = D3DXVECTOR2(0.0f, 0.0f);
		}
		else if (nCnt == SKIP_VTX_TO_ROSES_TITLE + 1)
		{
			pVtx_Title[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 363.0f, -58.0f, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH + 45.0f, -58.0f, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 363.0f, 435.0f, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH + 45.0f, 435.0f, 0.0f);

			pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
			pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);

			pVtx_Title[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx_Title[1].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_Title[2].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Title[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}
		else if (nCnt == SKIP_VTX_TO_GARLAND2_TITLE + 1)
		{
			pVtx_Title[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_Title[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Title[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_Title[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
		else if (nCnt == SKIP_VTX_TO_GARLAND1_TITLE + 1)
		{
			pVtx_Title[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_Title[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Title[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_Title[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
		else if (nCnt == SKIP_VTX_TO_CURTAIN_TITLE + 1)
		{
			pVtx_Title[0].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx_Title[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx_Title[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx_Title[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		}
		else if(nCnt == SKIP_VTX_TO_PRESS_TITLE)
		{
			pVtx_Title[0].pos = D3DXVECTOR3(715.0f, 850.0f, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(1245.0f, 850.0f, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(715.0f, 916.0f, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(1245.0f, 916.0f, 0.0f);

			pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
			pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
			pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
			pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
		}
		else if (nCnt == SKIP_VTX_TO_FADEOUT_TITLE)
		{
			pVtx_Title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

			pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
			pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
			pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
			pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
		}

		pVtx_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//閃光アニメーション関数
//************************************************
void Flash_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_WHITE_TITLE;

	g_nColorA_Flash_Title -= CHANGE_SPD_WHITE_COLORA_TITLE;

	//色変わりすぎ防止
	if (g_nColorA_Flash_Title <= 0)
	{
		g_nColorA_Flash_Title = 0;
	}

	//色変更
	pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Flash_Title);
	pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Flash_Title);
	pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Flash_Title);
	pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Flash_Title);

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//背景アニメーション関数
//************************************************
void BG_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	//テクスチャ位置変更
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_BG_TITLE; nCnt++)
	{
		//テクスチャ座標の更新
		pVtx_Title[0].tex.x += MOVE_SPD_TEX_BG_TITLE * (nCnt + 1);
		pVtx_Title[1].tex.x += MOVE_SPD_TEX_BG_TITLE * (nCnt + 1);
		pVtx_Title[2].tex.x += MOVE_SPD_TEX_BG_TITLE * (nCnt + 1);
		pVtx_Title[3].tex.x += MOVE_SPD_TEX_BG_TITLE * (nCnt + 1);

		pVtx_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//タイトルロゴアニメーション関数
//************************************************
void TitleLogo_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_LOGO_TITLE;

	g_fPosX_TitleLogo += MOVE_SPD_POS_LOGO_TITLE * 3.0f;

	//ポリゴン伸縮しすぎ防止
	if (SCREENCENTER_X + g_fPosX_TitleLogo >= SCREEN_WIDTH - HALF_X_LOGO_TITLE)
	{
		g_fPosX_TitleLogo = SCREEN_WIDTH - (SCREENCENTER_X + HALF_X_LOGO_TITLE);
	}

	//頂点座標の移動
	pVtx_Title[0].pos = D3DXVECTOR3(SCREENCENTER_X - g_fPosX_TitleLogo, 100.0f, 0.0f);
	pVtx_Title[1].pos = D3DXVECTOR3(SCREENCENTER_X + g_fPosX_TitleLogo, 100.0f, 0.0f);
	pVtx_Title[2].pos = D3DXVECTOR3(SCREENCENTER_X - g_fPosX_TitleLogo, 740.0f, 0.0f);
	pVtx_Title[3].pos = D3DXVECTOR3(SCREENCENTER_X + g_fPosX_TitleLogo, 740.0f, 0.0f);

	//ロゴ展開にパーティクル
	//Setinfo_Particle_Titlelogo(D3DXVECTOR3(SCREENCENTER_X - g_fPosX_TitleLogo, 100.0f, 0.0f));

	g_fTexU_TitleLogo -= MOVE_SPD_TEX_LOGO_TITLE * 3.0f;

	//テクスチャ伸縮しすぎ防止
	if (g_fTexU_TitleLogo <= 0.0f)
	{
		g_fTexU_TitleLogo = 0.0f;
	}

	//テクスチャのサイズ変更
	pVtx_Title[0].tex = D3DXVECTOR2(0.0f + g_fTexU_TitleLogo, 0.0f);
	pVtx_Title[1].tex = D3DXVECTOR2(1.0f - g_fTexU_TitleLogo, 0.0f);
	pVtx_Title[2].tex = D3DXVECTOR2(0.0f + g_fTexU_TitleLogo, 1.0f);
	pVtx_Title[3].tex = D3DXVECTOR2(1.0f - g_fTexU_TitleLogo, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//バラアニメーション関数
//************************************************
void Roses_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_ROSES_TITLE;

	g_nColorA_Roses_Title += CHANGE_SPD_ROSES_COLORA_TITLE;

	//色変わりすぎ防止
	if (g_nColorA_Roses_Title >= 255)
	{
		g_nColorA_Roses_Title = 255;
	}

	//色変更
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_ROSES_TITLE; nCnt++)
	{
		pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
		pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
		pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);
		pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Roses_Title);

		pVtx_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//カーテンアニメーション関数
//************************************************
void Curtain_Animation_Title(void)
{
	int nCntCurtain = 0;	//カーテン番号

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_CURTAIN_TITLE;

	g_fPosY_Curtain_Title[nCntCurtain] += MOVE_SPD_POS_CURTAIN_TITLE;

	//ポリゴン伸縮しすぎ防止
	if (g_fPosY_Curtain_Title[nCntCurtain] >= 275.0f)
	{
		g_fPosY_Curtain_Title[nCntCurtain] = 275.0f;

		nCntCurtain++;
	}

	switch (nCntCurtain)
	{
	case 0:

		//頂点座標の移動
		pVtx_Title[0].pos = D3DXVECTOR3(-76.0f, -363.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[1].pos = D3DXVECTOR3(281.0f, -363.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[2].pos = D3DXVECTOR3(-76.0f, 0.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[3].pos = D3DXVECTOR3(281.0f, 0.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);

		break;

	case 1:

		pVtx_Title += AMOUNT_VTX;

		g_fPosY_Curtain_Title[nCntCurtain] += MOVE_SPD_POS_CURTAIN_TITLE;

		//ポリゴン伸縮しすぎ防止
		if (g_fPosY_Curtain_Title[nCntCurtain] >= 275.0f)
		{
			g_fPosY_Curtain_Title[nCntCurtain] = 275.0f;
		}

		pVtx_Title[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 281.0f, -363.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH + 76.0f, -363.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 281.0f, 0.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);
		pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH + 76.0f, 0.0f + g_fPosY_Curtain_Title[nCntCurtain], 0.0f);

		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//ガーランド1アニメーション関数
//************************************************
void Garland1_Animation_Title(void)
{
	int nCntGarland1 = 0;	//ガーランド1番号

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_GARLAND1_TITLE;

	g_fPosX_Garland1_Title[nCntGarland1] += MOVE_SPD_POS_GARLAND1_TITLE;

	//ポリゴン伸縮しすぎ防止
	if (g_fPosX_Garland1_Title[nCntGarland1] >= 729.0f)
	{
		g_fPosX_Garland1_Title[nCntGarland1] = 729.0f;

		nCntGarland1++;

		g_fPosX_Garland1_Title[nCntGarland1] += MOVE_SPD_POS_GARLAND1_TITLE;

		pVtx_Title += AMOUNT_VTX;

		//ポリゴン伸縮しすぎ防止
		if (g_fPosX_Garland1_Title[nCntGarland1] >= 729.0f)
		{
			g_fPosX_Garland1_Title[nCntGarland1] = 729.0f;
		}
	}

	switch (nCntGarland1)
	{
	case 0:

		//頂点座標の移動
		pVtx_Title[0].pos = D3DXVECTOR3(-560.0f + g_fPosX_Garland1_Title[nCntGarland1], -206.0f, 0.0f);
		pVtx_Title[1].pos = D3DXVECTOR3(0.0f + g_fPosX_Garland1_Title[nCntGarland1], -206.0f, 0.0f);
		pVtx_Title[2].pos = D3DXVECTOR3(-560.0f + g_fPosX_Garland1_Title[nCntGarland1], 227.0f, 0.0f);
		pVtx_Title[3].pos = D3DXVECTOR3(0.0f + g_fPosX_Garland1_Title[nCntGarland1], 227.0f, 0.0f);

		break;

	case 1:

		pVtx_Title[0].pos = D3DXVECTOR3(SCREEN_WIDTH - g_fPosX_Garland1_Title[nCntGarland1], -206.0f, 0.0f);
		pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH + 560.0f - g_fPosX_Garland1_Title[nCntGarland1], -206.0f, 0.0f);
		pVtx_Title[2].pos = D3DXVECTOR3(SCREEN_WIDTH - g_fPosX_Garland1_Title[nCntGarland1], 227.0f, 0.0f);
		pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH + 560.0f - g_fPosX_Garland1_Title[nCntGarland1], 227.0f, 0.0f);

		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//かんざしアニメーション関数
//************************************************
void Kanzashi_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_KANZASHI_TITLE;

	g_fPosY_Kanzashi_Title += MOVE_SPD_POS_KANZASHI_TITLE;

	//ポリゴン伸縮しすぎ防止
	if (g_fPosY_Kanzashi_Title >= 595.0f)
	{
		g_fPosY_Kanzashi_Title = 595.0f;
	}

	//頂点座標の移動
	pVtx_Title[0].pos = D3DXVECTOR3(-69.0f, -489.0f + g_fPosY_Kanzashi_Title, 0.0f);
	pVtx_Title[1].pos = D3DXVECTOR3(219.0f, -489.0f + g_fPosY_Kanzashi_Title, 0.0f);
	pVtx_Title[2].pos = D3DXVECTOR3(-69.0f, 0.0f + g_fPosY_Kanzashi_Title, 0.0f);
	pVtx_Title[3].pos = D3DXVECTOR3(219.0f, 0.0f + g_fPosY_Kanzashi_Title, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//ブローチアニメーション関数
//************************************************
void Brooch_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_BROOCH_TITLE;

	g_fPosY_Brooch_Title += MOVE_SPD_POS_BROOCH_TITLE;

	//ポリゴン伸縮しすぎ防止
	if (g_fPosY_Brooch_Title >= 585.0f)
	{
		g_fPosY_Brooch_Title = 585.0f;
	}

	//頂点座標の移動
	pVtx_Title[0].pos = D3DXVECTOR3(1803.0f, -551.0f + g_fPosY_Brooch_Title, 0.0f);
	pVtx_Title[1].pos = D3DXVECTOR3(1934.0f, -551.0f + g_fPosY_Brooch_Title, 0.0f);
	pVtx_Title[2].pos = D3DXVECTOR3(1803.0f, 0.0f + g_fPosY_Brooch_Title, 0.0f);
	pVtx_Title[3].pos = D3DXVECTOR3(1934.0f, 0.0f + g_fPosY_Brooch_Title, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//歯車アニメーション関数
//************************************************
void Gear_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_GEAR_TITLE;

	g_fPosY_Gear_Title += MOVE_SPD_POS_GEAR_TITLE;

	//ポリゴン伸縮しすぎ防止
	if (g_fPosY_Gear_Title >= 447.0f)
	{
		g_fPosY_Gear_Title = 447.0f;
	}

	//頂点座標の移動
	pVtx_Title[0].pos = D3DXVECTOR3(110.0f, -390.0f + g_fPosY_Gear_Title, 0.0f);
	pVtx_Title[1].pos = D3DXVECTOR3(287.0f, -390.0f + g_fPosY_Gear_Title, 0.0f);
	pVtx_Title[2].pos = D3DXVECTOR3(110.0f, 0.0f + g_fPosY_Gear_Title, 0.0f);
	pVtx_Title[3].pos = D3DXVECTOR3(287.0f, 0.0f + g_fPosY_Gear_Title, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//ペンダントアニメーション関数
//************************************************
void Pendant_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_PENDANT_TITLE;

	g_fPosY_Pendant_Title += MOVE_SPD_POS_PENDANT_TITLE;

	//ポリゴン伸縮しすぎ防止
	if (g_fPosY_Pendant_Title >= 327.0f)
	{
		g_fPosY_Pendant_Title = 327.0f;
	}

	//頂点座標の移動
	pVtx_Title[0].pos = D3DXVECTOR3(1690.0f, -189.0f + g_fPosY_Pendant_Title, 0.0f);
	pVtx_Title[1].pos = D3DXVECTOR3(1804.0f, -189.0f + g_fPosY_Pendant_Title, 0.0f);
	pVtx_Title[2].pos = D3DXVECTOR3(1690.0f, 0.0f + g_fPosY_Pendant_Title, 0.0f);
	pVtx_Title[3].pos = D3DXVECTOR3(1804.0f, 0.0f + g_fPosY_Pendant_Title, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//ガーランド2アニメーション関数
//************************************************
void Garland2_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_GARLAND2_TITLE;

	g_fPosY_Garland2_Title += MOVE_SPD_POS_GARLAND2_TITLE;

	//ポリゴン伸縮しすぎ防止
	if (g_fPosY_Garland2_Title >= 519.0f)
	{
		g_fPosY_Garland2_Title = 519.0f;
	}

	//頂点座標の移動
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			pVtx_Title[0].pos = D3DXVECTOR3(75.0f, -521.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(312.0f, -521.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(75.0f, 0.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(312.0f, 0.0f + g_fPosY_Garland2_Title, 0.0f);

			break;

		case 1:

			pVtx_Title[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 342.0f, -521.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[1].pos = D3DXVECTOR3(SCREEN_WIDTH - 105.0f, -521.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 342.0f, 0.0f + g_fPosY_Garland2_Title, 0.0f);
			pVtx_Title[3].pos = D3DXVECTOR3(SCREEN_WIDTH - 105.0f, 0.0f + g_fPosY_Garland2_Title, 0.0f);

			break;
		}

		pVtx_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//歯車群アニメーション関数
//************************************************
void Gears_Animation_Title(void)
{
	int nCntGears = 0;	//歯車番号
	bool bStartRotateFrame = false;
	bool bStartRotateSmall = false;

	//歯車大の中心点を移動する
	for (int nCntBig = 0; nCntBig < AMOUNT_USING_TEX_GEARBIG_TITLE; nCntBig++)
	{
		switch (nCntBig)
		{
		case 0:

			g_aGears_Title[nCntBig].pos.x += MOVE_SPD_POS_GEARS_TITLE;

			break;

		case 1:

			g_aGears_Title[nCntBig].pos.x -= MOVE_SPD_POS_GEARS_TITLE;

			break;
		}
	}

	//歯車大移動後、歯車枠移動開始
	if (g_aGears_Title[nCntGears].pos.x >= 218.0f - HALFSPAN_GEARBIG_TITLE)
	{
		//対応パーツ回数ループ、歯車番号も進める
		for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GEARBIG_TITLE; nCnt++)
		{
			switch (nCntGears)
			{
			case 0:

				g_aGears_Title[nCntGears].pos.x = 218.0f - HALFSPAN_GEARBIG_TITLE;

				break;

			case 1:

				g_aGears_Title[nCntGears].pos.x = SCREEN_WIDTH - 218.0f + HALFSPAN_GEARBIG_TITLE;

				break;
			}

			nCntGears++;
		}

		if (!bStartRotateFrame)
		{
			bStartRotateFrame = true;
		}
	}

	//歯車枠の中心点を移動する
	if (bStartRotateFrame)
	{
		for (int nCntFrame = 0; nCntFrame < AMOUNT_USING_TEX_GEARFRAME_TITLE; nCntFrame++)
		{
			switch (nCntFrame)
			{
			case 0:

				g_aGears_Title[nCntFrame + AMOUNT_USING_TEX_GEARBIG_TITLE].pos.x += MOVE_SPD_POS_GEARS_TITLE;

				break;

			case 2:

				g_aGears_Title[nCntFrame + AMOUNT_USING_TEX_GEARBIG_TITLE].pos.x -= MOVE_SPD_POS_GEARS_TITLE;

				break;

			default:

				g_aGears_Title[nCntFrame + AMOUNT_USING_TEX_GEARBIG_TITLE].pos.y -= MOVE_SPD_POS_GEARS_TITLE;

				break;
			}
		}
	}

	//歯車枠移動後、歯車小移動開始
	if (g_aGears_Title[nCntGears].pos.x >= 137.0f - HALFSPAN_GEARFRAME_TITLE)
	{
		//対応パーツ回数ループ、歯車番号も進める
		for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GEARFRAME_TITLE; nCnt++)
		{
			switch (nCntGears)
			{
			case 2:

				g_aGears_Title[nCntGears].pos.x = 137.0f - HALFSPAN_GEARFRAME_TITLE;

				break;

			case 3:

				g_aGears_Title[nCntGears].pos.y = 934.0f + HALFSPAN_GEARFRAME_TITLE;

				break;

			case 4:

				g_aGears_Title[nCntGears].pos.x = SCREEN_WIDTH - 137.0f + HALFSPAN_GEARFRAME_TITLE;

				break;

			case 5:

				g_aGears_Title[nCntGears].pos.y = 934.0f + HALFSPAN_GEARFRAME_TITLE;

				break;
			}

			nCntGears++;
		}

		if (!bStartRotateSmall)
		{
			bStartRotateSmall = true;
		}
	}

	//歯車枠の中心点を移動する
	if (bStartRotateSmall)
	{
		for (int nCntSmall = 0; nCntSmall < AMOUNT_USING_TEX_GEARSMALL_TITLE; nCntSmall++)
		{
			switch (nCntSmall)
			{
			case 0:

				g_aGears_Title[nCntSmall + AMOUNT_USING_TEX_GEARBIG_TITLE + AMOUNT_USING_TEX_GEARFRAME_TITLE].pos.y -= MOVE_SPD_POS_GEARS_TITLE;

				break;

			case 1:

				g_aGears_Title[nCntSmall + AMOUNT_USING_TEX_GEARBIG_TITLE + AMOUNT_USING_TEX_GEARFRAME_TITLE].pos.y -= MOVE_SPD_POS_GEARS_TITLE;

				break;
			}
		}
	}

	//歯車小移動後
	if (g_aGears_Title[nCntGears].pos.y <= 939.0f + HALFSPAN_GEARSMALL_TITLE)
	{
		//対応パーツ回数ループ、歯車番号も進める
		for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GEARFRAME_TITLE; nCnt++)
		{
			switch (nCntGears)
			{
			case 6:

				g_aGears_Title[nCntGears].pos.y = 939.0f + HALFSPAN_GEARSMALL_TITLE;

				break;

			case 7:

				g_aGears_Title[nCntGears].pos.y = 939.0f + HALFSPAN_GEARSMALL_TITLE;

				break;
			}

			nCntGears++;
		}
	}
}

//************************************************
//歯車群回転関数
//************************************************
void Gears_Rotate_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_GEARS_TITLE;

	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_GEARS_TITLE; nCnt++)
	{
		pVtx_Title[0].pos.x = g_aGears_Title[nCnt].pos.x + sinf(g_aGears_Title[nCnt].rot.z - (D3DX_PI - g_aGears_Title[nCnt].fAngle)) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[0].pos.y = g_aGears_Title[nCnt].pos.y + cosf(g_aGears_Title[nCnt].rot.z - (D3DX_PI - g_aGears_Title[nCnt].fAngle)) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[1].pos.x = g_aGears_Title[nCnt].pos.x + sinf(g_aGears_Title[nCnt].rot.z + (D3DX_PI - g_aGears_Title[nCnt].fAngle)) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[1].pos.y = g_aGears_Title[nCnt].pos.y + cosf(g_aGears_Title[nCnt].rot.z + (D3DX_PI - g_aGears_Title[nCnt].fAngle)) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[2].pos.x = g_aGears_Title[nCnt].pos.x + sinf(g_aGears_Title[nCnt].rot.z - g_aGears_Title[nCnt].fAngle) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[2].pos.y = g_aGears_Title[nCnt].pos.y + cosf(g_aGears_Title[nCnt].rot.z - g_aGears_Title[nCnt].fAngle) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[3].pos.x = g_aGears_Title[nCnt].pos.x + sinf(g_aGears_Title[nCnt].rot.z + g_aGears_Title[nCnt].fAngle) * g_aGears_Title[nCnt].fLength;
		pVtx_Title[3].pos.y = g_aGears_Title[nCnt].pos.y + cosf(g_aGears_Title[nCnt].rot.z + g_aGears_Title[nCnt].fAngle) * g_aGears_Title[nCnt].fLength;

		switch (nCnt)
		{
		case 0:

			g_aGears_Title[nCnt].rot.z += ROTATE_SPD_GEARS_TITLE;

			break;

		case 1:

			g_aGears_Title[nCnt].rot.z -= ROTATE_SPD_GEARS_TITLE;

			break;

		case 2:

			g_aGears_Title[nCnt].rot.z -= ROTATE_SPD_GEARS_TITLE * 1.5f;

			break;

		case 3:

			g_aGears_Title[nCnt].rot.z += ROTATE_SPD_GEARS_TITLE * 1.5f;

			break;

		case 4:

			g_aGears_Title[nCnt].rot.z += ROTATE_SPD_GEARS_TITLE * 1.5f;

			break;

		case 5:

			g_aGears_Title[nCnt].rot.z -= ROTATE_SPD_GEARS_TITLE * 1.5f;

			break;

		case 6:

			g_aGears_Title[nCnt].rot.z += ROTATE_SPD_GEARS_TITLE * 2.0f;

			break;

		case 7:

			g_aGears_Title[nCnt].rot.z -= ROTATE_SPD_GEARS_TITLE * 2.0f;

			break;
		}

		pVtx_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//偽ハトアニメーション関数
//************************************************
void Pigeons_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_PIGEONS_TITLE;

	//偽ハトの中心点を移動する
	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_PIGEONS_TITLE; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			g_aPigeons_Title[nCnt].pos.x += MOVE_SPD_PIGEONS_1_TITLE;

			break;

		case 1:

			g_aPigeons_Title[nCnt].pos.x -= MOVE_SPD_PIGEONS_1_TITLE;

			break;
		}

		pVtx_Title[0].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z - (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[0].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z - (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[1].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z + (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[1].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z + (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[2].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z - g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[2].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z - g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[3].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z + g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[3].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z + g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;

		pVtx_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();

	//偽ハト1移動後
	if (g_aPigeons_Title[0].pos.x >= 300.0f)
	{
		g_aPigeons_Title[0].pos.x = 300.0f;	
	
		g_bStartRotate = true;
	}

	//偽ハト2移動後
	if (g_aPigeons_Title[1].pos.x <= 1680.0f)
	{
		g_aPigeons_Title[1].pos.x = 1680.0f;
	}
}

//************************************************
//偽ハト回転関数
//************************************************
void Pigeons_Rotate_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_PIGEONS_TITLE;

	for (int nCnt = 0; nCnt < AMOUNT_USING_TEX_PIGEONS_TITLE; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			if (g_aPigeons_Title[nCnt].nCntStop > 0)
			{
				g_aPigeons_Title[nCnt].nCntStop--;
			}
			else
			{
				g_aPigeons_Title[nCnt].fMoveSPD1 *= 0.9935f;
				g_aPigeons_Title[nCnt].fMoveSPD2 *= 0.9935f;
				g_aPigeons_Title[nCnt].fMoveSPD3 *= 0.9935f;

				if (g_aPigeons_Title[nCnt].rot.z < 0.5f && !g_bTurn_1)
				{
					//移動
					g_aPigeons_Title[nCnt].pos.x -= g_aPigeons_Title[nCnt].fMoveSPD1;
					g_aPigeons_Title[nCnt].pos.y -= g_aPigeons_Title[nCnt].fMoveSPD2;

					//回転
					g_aPigeons_Title[nCnt].rot.z += g_aPigeons_Title[nCnt].fMoveSPD3;
				}
				else if (g_aPigeons_Title[nCnt].rot.z >= 0.5f && !g_bTurn_1)
				{
					g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_1_X;
					g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_1_Y;
					g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_1_Z;

					g_bTurn_1 = true;

					g_aPigeons_Title[nCnt].nCntStop = 10 + (rand() % 20);
				}

				if (g_aPigeons_Title[nCnt].rot.z > -0.5f && g_bTurn_1)
				{
					//移動
					g_aPigeons_Title[nCnt].pos.x += g_aPigeons_Title[nCnt].fMoveSPD1;
					g_aPigeons_Title[nCnt].pos.y += g_aPigeons_Title[nCnt].fMoveSPD2;

					//回転
					g_aPigeons_Title[nCnt].rot.z -= g_aPigeons_Title[nCnt].fMoveSPD3;
				}
				else if (g_aPigeons_Title[nCnt].rot.z <= -0.5f && g_bTurn_1)
				{
					g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_1_X;
					g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_1_Y;
					g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_1_Z;

					g_bTurn_1 = false;

					g_aPigeons_Title[nCnt].nCntStop = 10 + (rand() % 20);
				}
			}

			break;

		case 1:

			if (g_aPigeons_Title[nCnt].nCntStop > 0)
			{
				g_aPigeons_Title[nCnt].nCntStop--;
			}
			else
			{
				g_aPigeons_Title[nCnt].fMoveSPD1 *= 0.9935f;
				g_aPigeons_Title[nCnt].fMoveSPD2 *= 0.9935f;
				g_aPigeons_Title[nCnt].fMoveSPD3 *= 0.9935f;

				if (g_aPigeons_Title[nCnt].rot.z < 0.5f && !g_bTurn_2)
				{
					//移動
					g_aPigeons_Title[nCnt].pos.x -= g_aPigeons_Title[nCnt].fMoveSPD1;
					g_aPigeons_Title[nCnt].pos.y += g_aPigeons_Title[nCnt].fMoveSPD2;

					//回転
					g_aPigeons_Title[nCnt].rot.z += g_aPigeons_Title[nCnt].fMoveSPD3;
				}
				else if (g_aPigeons_Title[nCnt].rot.z >= 0.5f && !g_bTurn_2)
				{
					g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_1_X;
					g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_1_Y;
					g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_1_Z;

					g_bTurn_2 = true;

					g_aPigeons_Title[nCnt].nCntStop = 10 + (rand() % 20);
				}

				if (g_aPigeons_Title[nCnt].rot.z > -0.5f && g_bTurn_2)
				{
					//移動
					g_aPigeons_Title[nCnt].pos.x += g_aPigeons_Title[nCnt].fMoveSPD1;
					g_aPigeons_Title[nCnt].pos.y -= g_aPigeons_Title[nCnt].fMoveSPD2;

					//回転
					g_aPigeons_Title[nCnt].rot.z -= g_aPigeons_Title[nCnt].fMoveSPD3;
				}
				else if (g_aPigeons_Title[nCnt].rot.z <= -0.5f && g_bTurn_2)
				{
					g_aPigeons_Title[nCnt].fMoveSPD1 = MOVE_SPD_PIGEONS_1_X;
					g_aPigeons_Title[nCnt].fMoveSPD2 = MOVE_SPD_PIGEONS_1_Y;
					g_aPigeons_Title[nCnt].fMoveSPD3 = MOVE_SPD_PIGEONS_1_Z;

					g_bTurn_2 = false;

					g_aPigeons_Title[nCnt].nCntStop = 10 + (rand() % 20);
				}
			}

			break;
		}

		pVtx_Title[0].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z - (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[0].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z - (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[1].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z + (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[1].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z + (D3DX_PI - g_aPigeons_Title[nCnt].fAngle)) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[2].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z - g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[2].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z - g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[3].pos.x = g_aPigeons_Title[nCnt].pos.x + sinf(g_aPigeons_Title[nCnt].rot.z + g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;
		pVtx_Title[3].pos.y = g_aPigeons_Title[nCnt].pos.y + cosf(g_aPigeons_Title[nCnt].rot.z + g_aPigeons_Title[nCnt].fAngle) * g_aPigeons_Title[nCnt].fLength;

		pVtx_Title += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//入力勧告アニメーション関数
//************************************************
void Press_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_PRESS_TITLE;

	//色変わりまくる
	if (g_nColorA_Press_Title < 255 && !g_bChangeColor_Press_Title)
	{
		g_nColorA_Press_Title += CHANGE_SPD_PRESS_COLORA_TITLE;
	}
	
	if (g_nColorA_Press_Title >= 255)
	{
		g_nColorA_Press_Title = 255;

		g_bChangeColor_Press_Title = true;
	}

	if (g_nColorA_Press_Title > 100 && g_bChangeColor_Press_Title)
	{
		g_nColorA_Press_Title -= CHANGE_SPD_PRESS_COLORA_TITLE;
	}
	else
	{
		g_bChangeColor_Press_Title = false;
	}

	//色変更
	pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
	pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
	pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);
	pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Press_Title);

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//************************************************
//フェードアウト関数
//************************************************
void Fadeout_Animation_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_FADEOUT_TITLE;

	g_nColorA_Fadeout_Title += 25;

	//色変わりすぎ防止
	if (g_nColorA_Fadeout_Title >= 255)
	{
		g_nColorA_Fadeout_Title = 255;
	}

	//色変更
	pVtx_Title[0].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
	pVtx_Title[1].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
	pVtx_Title[2].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);
	pVtx_Title[3].col = D3DCOLOR_RGBA(255, 255, 255, g_nColorA_Fadeout_Title);

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

////************************************************
////音量関数
////************************************************
//float Set_Volume_Title(void)
//{
//	//音量を引き渡す
//	return g_fVolume_BGM_Title;
//}

//************************************************
//タイトルロゴ設定関数
//************************************************
void Setinfo_TitleLogoEX_Title(void)
{
	//タイトルロゴ情報を設定
	g_aLogoEX.nStyle = 0;	//種類
	g_aLogoEX.pos = D3DXVECTOR3(990.0f, -800.0f, 0.0f);	//位置
	g_aLogoEX.fSpanX = 462.75f;	//サイズ
	g_aLogoEX.fSpanY = 320.0f;	//サイズ
	g_aLogoEX.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動情報
	g_aLogoEX.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き情報
	g_aLogoEX.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色
	g_aLogoEX.fLength = sqrtf((g_aLogoEX.fSpanX * g_aLogoEX.fSpanX) + (g_aLogoEX.fSpanY * g_aLogoEX.fSpanY));	//対角線
	g_aLogoEX.fAngle = atan2f(g_aLogoEX.fSpanX * 2.0f, g_aLogoEX.fSpanY * 2.0f);	//角度
	g_aLogoEX.bfirst = false;
}

//************************************************
//タイトルロゴアニメーション関数
//************************************************
void TitleLogo_AnimationEX_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Title->Lock(0, 0, (void**)&pVtx_Title, 0);

	pVtx_Title += AMOUNT_VTX * SKIP_VTX_TO_LOGO_TITLE;

	//第一落下
	if (g_aLogoEX.pos.y < 720.0f - g_aLogoEX.fSpanY && !g_aLogoEX.bfirst)
	{
		g_aLogoEX.move.y += 0.1f;
		g_aLogoEX.move.z += -0.00002f;

		//移動
		g_aLogoEX.pos.y += g_aLogoEX.move.y;

		//回転
		g_aLogoEX.rot.z += g_aLogoEX.move.z;
	}
	else if (!g_aLogoEX.bfirst)
	{
		g_aLogoEX.move.x = -10.0f;
		g_aLogoEX.move.y = -15.0f;
		g_aLogoEX.move.z = 0.0f;

		g_aLogoEX.bfirst = true;
	}

	//跳ねて、
	if (g_aLogoEX.nCntfirst < 30 && g_aLogoEX.bfirst && !g_aLogoEX.bsecond)
	{
		g_aLogoEX.nCntfirst++;

		g_aLogoEX.move.x += 0.25f;
		g_aLogoEX.move.y += 0.8f;
		g_aLogoEX.move.z += 0.0001f;

		//移動
		g_aLogoEX.pos += g_aLogoEX.move;

		//回転
		g_aLogoEX.rot.z += g_aLogoEX.move.z;
	}
	else if (g_aLogoEX.bfirst && !g_aLogoEX.bsecond)
	{
		g_aLogoEX.move.x = 1.0f;
		g_aLogoEX.move.y = 1.0f;
		g_aLogoEX.move.z = 0.0f;

		g_aLogoEX.bsecond = true;
	}

	//揺れる
	if (g_aLogoEX.nCntsecond < 45 && g_aLogoEX.bsecond && !g_aLogoEX.bthird)
	{
		g_aLogoEX.nCntsecond++;

		g_aLogoEX.move.x += 0.1f;
		g_aLogoEX.move.y += 0.001f;
g_aLogoEX.move.z += 0.0002f;

//移動
g_aLogoEX.pos.x += g_aLogoEX.move.x;
g_aLogoEX.pos.y += g_aLogoEX.move.y;

//回転
g_aLogoEX.rot.z += g_aLogoEX.move.z;
	}
	else if (g_aLogoEX.bsecond && !g_aLogoEX.bthird)
	{
	g_aLogoEX.fHoldX = 0.2f;
	//g_aLogoEX.fHoldY = 0.15f;
	g_aLogoEX.fHoldZ = 0.000335f;

	g_aLogoEX.bthird = true;
	}

	//揺れる(恒常)
	if (g_aLogoEX.bthird)
	{
		if (g_aLogoEX.nCntStop > 0)
		{
			g_aLogoEX.nCntStop--;
		}
		else
		{
			if (!g_aLogoEX.bTurnX)
			{
				g_aLogoEX.move.x += g_aLogoEX.fHoldX;
				g_aLogoEX.move.z += g_aLogoEX.fHoldZ;
			}
			else
			{
				g_aLogoEX.move.x -= g_aLogoEX.fHoldX;
				g_aLogoEX.move.z -= g_aLogoEX.fHoldZ;
			}

			//if (!g_aLogoEX.bTurnY)
			//{
			//	g_aLogoEX.move.y += g_aLogoEX.fHoldY;
			//}
			//else
			//{
			//	g_aLogoEX.move.y -= g_aLogoEX.fHoldY;
			//}

			//移動
			g_aLogoEX.pos.x += g_aLogoEX.move.x;
			//g_aLogoEX.pos.y += g_aLogoEX.move.y;

			if (g_aLogoEX.pos.x < 915.0f)
			{
				g_aLogoEX.nCntStop = 1;
			}
			else if (g_aLogoEX.pos.x > 1075.0f)
			{
				g_aLogoEX.nCntStop = 1;
			}

			if (g_aLogoEX.pos.x > 990.0f)
			{
				g_aLogoEX.bTurnX = true;
			}
			else if (g_aLogoEX.pos.x < 990.0f)
			{
				g_aLogoEX.bTurnX = false;
			}

			//if (g_aLogoEX.pos.y > 370.0f)
			//{
			//	g_aLogoEX.bTurnY = true;
			//}
			//else if (g_aLogoEX.pos.y < 370.0f)
			//{
			//	g_aLogoEX.bTurnY = false;
			//}

			//回転
			g_aLogoEX.rot.z += g_aLogoEX.move.z;
		}
	}

	//移動、回転を反映
	pVtx_Title[0].pos.x = g_aLogoEX.pos.x + sinf(g_aLogoEX.rot.z - (D3DX_PI - g_aLogoEX.fAngle)) * g_aLogoEX.fLength;
	pVtx_Title[0].pos.y = g_aLogoEX.pos.y + cosf(g_aLogoEX.rot.z - (D3DX_PI - g_aLogoEX.fAngle)) * g_aLogoEX.fLength;
	pVtx_Title[1].pos.x = g_aLogoEX.pos.x + sinf(g_aLogoEX.rot.z + (D3DX_PI - g_aLogoEX.fAngle)) * g_aLogoEX.fLength;
	pVtx_Title[1].pos.y = g_aLogoEX.pos.y + cosf(g_aLogoEX.rot.z + (D3DX_PI - g_aLogoEX.fAngle)) * g_aLogoEX.fLength;
	pVtx_Title[2].pos.x = g_aLogoEX.pos.x + sinf(g_aLogoEX.rot.z - g_aLogoEX.fAngle) * g_aLogoEX.fLength;
	pVtx_Title[2].pos.y = g_aLogoEX.pos.y + cosf(g_aLogoEX.rot.z - g_aLogoEX.fAngle) * g_aLogoEX.fLength;
	pVtx_Title[3].pos.x = g_aLogoEX.pos.x + sinf(g_aLogoEX.rot.z + g_aLogoEX.fAngle) * g_aLogoEX.fLength;
	pVtx_Title[3].pos.y = g_aLogoEX.pos.y + cosf(g_aLogoEX.rot.z + g_aLogoEX.fAngle) * g_aLogoEX.fLength;

	//頂点バッファをアンロックする
	g_pVtxBuff_Title->Unlock();
}

//******************
//フェードアウト関数
//******************
bool* StartFadeout(void)
{
	return &g_bStartFadeout_Title;
}