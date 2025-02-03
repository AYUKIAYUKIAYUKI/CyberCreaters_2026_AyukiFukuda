//************************************************
//
//チュートリアル[tutorial.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"
#include "sound.h"
#include "tutorial.h"
#include "tutorial_fade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Tutorial = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Tutorial = NULL;	//頂点バッファのポインタ
TUTORIAL g_aTutorial[AMOUNT_POLYGON_TUTORIAL];
bool g_bStart_T = false;

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Tutorial(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_EXPLAIN_TUTORIAL,
		&g_pTexture_Tutorial);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Tutorial,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tutorial;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tutorial->Lock(0, 0, (void**)&pVtx_Tutorial, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Tutorial[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Tutorial[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Tutorial[0].rhw = 1.0f;
		pVtx_Tutorial[1].rhw = 1.0f;
		pVtx_Tutorial[2].rhw = 1.0f;
		pVtx_Tutorial[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Tutorial[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Tutorial[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Tutorial[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Tutorial[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx_Tutorial[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Tutorial[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Tutorial[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Tutorial[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Tutorial += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Tutorial->Unlock();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL; nCnt++)
	{
		g_aTutorial[nCnt].nStyle = 0;
		g_aTutorial[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTutorial[nCnt].fLength = 0.0f;
		g_aTutorial[nCnt].fAngle = 0.0f;
	}

	g_bStart_T = false;

	Setinfo_Tutorial();

	//そのほかの
	Init_Tutorial_Fade();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Tutorial(void)
{
	//テクスチャの破棄
	if (g_pTexture_Tutorial != NULL)
	{
		g_pTexture_Tutorial->Release();
		g_pTexture_Tutorial = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Tutorial != NULL)
	{
		g_pVtxBuff_Tutorial->Release();
		g_pVtxBuff_Tutorial = NULL;
	}

	//そのほかの
	Uninit_Tutorial_Fade();
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Tutorial(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tutorial;

	float* pFade_T;
	pFade_T = Getinfo_Tutorial_Fade();

	if (!g_bStart_T)
	{
		//頂点バッファをロックして頂点情報のポインタを取得
		g_pVtxBuff_Tutorial->Lock(0, 0, (void**)&pVtx_Tutorial, 0);

		for (int nCnt = 0; nCnt < AMOUNT_POLYGON_MENU; nCnt++)
		{
			//移動、回転を反映
			pVtx_Tutorial[0].pos.x = g_aTutorial[nCnt].pos.x + sinf(g_aTutorial[nCnt].rot.z - (D3DX_PI - g_aTutorial[nCnt].fAngle)) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[0].pos.y = g_aTutorial[nCnt].pos.y + cosf(g_aTutorial[nCnt].rot.z - (D3DX_PI - g_aTutorial[nCnt].fAngle)) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[1].pos.x = g_aTutorial[nCnt].pos.x + sinf(g_aTutorial[nCnt].rot.z + (D3DX_PI - g_aTutorial[nCnt].fAngle)) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[1].pos.y = g_aTutorial[nCnt].pos.y + cosf(g_aTutorial[nCnt].rot.z + (D3DX_PI - g_aTutorial[nCnt].fAngle)) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[2].pos.x = g_aTutorial[nCnt].pos.x + sinf(g_aTutorial[nCnt].rot.z - g_aTutorial[nCnt].fAngle) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[2].pos.y = g_aTutorial[nCnt].pos.y + cosf(g_aTutorial[nCnt].rot.z - g_aTutorial[nCnt].fAngle) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[3].pos.x = g_aTutorial[nCnt].pos.x + sinf(g_aTutorial[nCnt].rot.z + g_aTutorial[nCnt].fAngle) * g_aTutorial[nCnt].fLength;
			pVtx_Tutorial[3].pos.y = g_aTutorial[nCnt].pos.y + cosf(g_aTutorial[nCnt].rot.z + g_aTutorial[nCnt].fAngle) * g_aTutorial[nCnt].fLength;
	
			pVtx_Tutorial[0].col = g_aTutorial[nCnt].col;
			pVtx_Tutorial[1].col = g_aTutorial[nCnt].col;
			pVtx_Tutorial[2].col = g_aTutorial[nCnt].col;
			pVtx_Tutorial[3].col = g_aTutorial[nCnt].col;
		}

		//頂点バッファをアンロックする
		g_pVtxBuff_Tutorial->Unlock();

		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true &&
			!g_bStart_T)
		{
			//効果音を鳴らす
			PlaySound(SOUND_LABEL_SE_SELECT2);

			g_bStart_T = true;
		}
	}

	//そのほかの
	Update_Tutorial_Fade();

	if (g_bStart_T)
	{
		if (*pFade_T > 1.1f)
		{
			Setinfo_Mode(MODE_GAME);	//開始
		}
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Tutorial(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Tutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Tutorial);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);

	//そのほかの
	Draw_Tutorial_Fade();
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Tutorial(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_TUTORIAL_FADE; nCnt++)
	{
		g_aTutorial[nCnt].nStyle = 0;
		g_aTutorial[nCnt].pos = D3DXVECTOR3(990.0f, 540.0f, 0.0f);
		g_aTutorial[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTutorial[nCnt].fLength = sqrtf((990.0f * 990.0f) + (540.0f * 540.0f));
		g_aTutorial[nCnt].fAngle = atan2f(990.0f * 2.0f, 540.0f * 2.0f);
	}
}

//************************************************
//開始情報を送る関数
//************************************************
bool* Getinfo_Tutorial(void)
{
	return &g_bStart_T;
}