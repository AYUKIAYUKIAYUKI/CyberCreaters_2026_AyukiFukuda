//===============================================================================
//
//  タイトル画面(title.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "title.h"
#include "title_select.h"
#include "title_anim.h"
#include "player_count.h"
#include "input.h"
#include "fade.h"

#include "sound.h"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
bool g_bRank;
//===============================================================================
//タイトル画面の初期化処理
//===============================================================================
void InitTitle(void)
{
	PlaySound(SOUND_LABEL_TITLE_BGM);
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title.jpg",
		&g_pTextureTitle);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);
	VERTEX_2D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	g_pVtxBuffTitle->Unlock();

	InitTitleAnim();
	InitTitleSelect();
	InitPlayerCount();
	g_bRank = false;
}

//===============================================================================
//タイトルの終了処理
//===============================================================================
void UninitTitle(void)
{
	StopSound();
	UninitTitleSelect();
	UninitTitleAnim();
	UninitPlayerCount();
	//テクスチャの破棄
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//===============================================================================
//タイトルの更新処理
//===============================================================================
void UpdateTitle(void)
{
	UpdateTitleSelect();
	UpdateTitleAnim();
	UpdatePlayerCount();

	if (g_bRank == true)
	{
		//フェードアウト処理
		SetFade(FADE_OUT, MODE_RANKING);//二つ目に移行先
	}
}

//===============================================================================
//タイトル描画
//===============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	DrawTitleSelect();
	DrawPlayerCount();
	DrawTitleAnim();
}

//===============================================================================
//ランキング画面遷移の判定処理
//===============================================================================
void MovetoRanking(void)
{
	g_bRank = true;
}