//************************************************
//
//タイトルロゴ処理[logo_title.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "logo_title.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Logo_Title = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Logo_Title = NULL;	//頂点バッファのポインタ
LOGO_TITLE g_aLogo_Title;	//タイトルロゴ情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Logo_Title()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_LOGO_TITLE,
		&g_pTexture_Logo_Title);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Logo_Title,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Logo_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Logo_Title->Lock(0, 0, (void**)&pVtx_Logo_Title, 0);

	//頂点座標の初期設定
	pVtx_Logo_Title[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Logo_Title[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Logo_Title[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Logo_Title[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Logo_Title[0].rhw = 1.0f;
	pVtx_Logo_Title[1].rhw = 1.0f;
	pVtx_Logo_Title[2].rhw = 1.0f;
	pVtx_Logo_Title[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Logo_Title[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Logo_Title[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Logo_Title[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Logo_Title[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Logo_Title[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Logo_Title[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Logo_Title[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Logo_Title[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Logo_Title->Unlock();

	//背景構造体の情報の初期化群
	g_aLogo_Title.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aLogo_Title.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aLogo_Title.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aLogo_Title.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aLogo_Title.fRadius[nCnt] = 0.0f;
	}
	g_aLogo_Title.fLength = 0.0f;
	g_aLogo_Title.fAngle = 0.0f;

	//背景構造体に情報を付与
	SetInfo_Logo_Title();

	//位置に基づきポリゴンを展開
	Update_Pos_Logo_Title();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Logo_Title(void)
{
	//テクスチャの破棄
	if (g_pTexture_Logo_Title != NULL)
	{
		g_pTexture_Logo_Title->Release();
		g_pTexture_Logo_Title = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Logo_Title != NULL)
	{
		g_pVtxBuff_Logo_Title->Release();
		g_pVtxBuff_Logo_Title = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Logo_Title(void)
{

}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Logo_Title(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Logo_Title, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Logo_Title);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//タイトルロゴ構造体の情報を設定する関数
//************************************************
void SetInfo_Logo_Title(void)
{
	g_aLogo_Title.pos = D3DXVECTOR3(990.0f, 250.0f, 0.0f);
	g_aLogo_Title.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aLogo_Title.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aLogo_Title.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aLogo_Title.fRadius[0] = RADIUS_LOGO_TITLE_X;	//背景横半幅
	g_aLogo_Title.fRadius[1] = RADIUS_LOGO_TITLE_Y;	//背景縦半幅
	g_aLogo_Title.fLength = sqrtf((g_aLogo_Title.fRadius[0] * g_aLogo_Title.fRadius[0]) + (g_aLogo_Title.fRadius[1] * g_aLogo_Title.fRadius[1]));
	g_aLogo_Title.fAngle = atan2f(g_aLogo_Title.fRadius[0] * 2.0f, g_aLogo_Title.fRadius[1] * 2.0f);
}

//************************************************
//タイトルロゴの位置を設定する関数
//************************************************
void Update_Pos_Logo_Title(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Logo_Title;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Logo_Title->Lock(0, 0, (void**)&pVtx_Logo_Title, 0);

	pVtx_Logo_Title[0].pos.x = g_aLogo_Title.pos.x + sinf(g_aLogo_Title.rot.z - (D3DX_PI - g_aLogo_Title.fAngle)) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[0].pos.y = g_aLogo_Title.pos.y + cosf(g_aLogo_Title.rot.z - (D3DX_PI - g_aLogo_Title.fAngle)) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[1].pos.x = g_aLogo_Title.pos.x + sinf(g_aLogo_Title.rot.z + (D3DX_PI - g_aLogo_Title.fAngle)) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[1].pos.y = g_aLogo_Title.pos.y + cosf(g_aLogo_Title.rot.z + (D3DX_PI - g_aLogo_Title.fAngle)) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[2].pos.x = g_aLogo_Title.pos.x + sinf(g_aLogo_Title.rot.z - g_aLogo_Title.fAngle) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[2].pos.y = g_aLogo_Title.pos.y + cosf(g_aLogo_Title.rot.z - g_aLogo_Title.fAngle) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[3].pos.x = g_aLogo_Title.pos.x + sinf(g_aLogo_Title.rot.z + g_aLogo_Title.fAngle) * g_aLogo_Title.fLength;
	pVtx_Logo_Title[3].pos.y = g_aLogo_Title.pos.y + cosf(g_aLogo_Title.rot.z + g_aLogo_Title.fAngle) * g_aLogo_Title.fLength;

	//頂点バッファをアンロックする
	g_pVtxBuff_Logo_Title->Unlock();
}

//************************************************
//タイトルロゴ構造体のアドレスを渡す
//************************************************
LOGO_TITLE* GetInfo_Logo_Title(void)
{
	return &g_aLogo_Title;
}