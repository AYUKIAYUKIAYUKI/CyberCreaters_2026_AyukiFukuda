//************************************************
//
//守護対象処理[tower.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "stage.h"
#include "tower.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Tower[AMOUNT_TEX_PLAYER] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Tower = NULL;	//頂点バッファのポインタ
TOWER g_aTower;	//守護対象情報
static float g_F;	//汎用浮動小数

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Tower()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TOWER,
		&g_pTexture_Tower[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Tower,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tower;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tower->Lock(0, 0, (void**)&pVtx_Tower, 0);

	//頂点座標の初期設定
	pVtx_Tower[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Tower[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Tower[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Tower[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Tower[0].rhw = 1.0f;
	pVtx_Tower[1].rhw = 1.0f;
	pVtx_Tower[2].rhw = 1.0f;
	pVtx_Tower[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Tower[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Tower[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Tower[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Tower[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Tower[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Tower[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Tower[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Tower[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Tower->Unlock();

	//守護対象構造体の情報の初期化群
	g_aTower.nState = 0;
	g_aTower.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aTower.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aTower.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aTower.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aTower.nCntTex = 0;
	g_aTower.nCntPattern = 0;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aTower.fTexSpan[nCnt] = 0.0f;
		g_aTower.fRadius[nCnt] = 0.0f;
		g_aTower.fLength[nCnt] = 0.0f;
		g_aTower.fAngle[nCnt] = 0.0f;
	}
	g_aTower.nLife = 0;
	g_aTower.nCT = 0;

	g_F = 0.5f;

	//守護対象構造体に情報を付与
	SetInfo_Tower();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Tower(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEX_PLAYER; nCnt++)
	{
		if (g_pTexture_Tower[nCnt] != NULL)
		{
			g_pTexture_Tower[nCnt]->Release();
			g_pTexture_Tower[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Tower != NULL)
	{
		g_pVtxBuff_Tower->Release();
		g_pVtxBuff_Tower = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Tower(void)
{
	/*デバッグ用ダメージ*/
	if (GetKeyboardTrigger(DIK_8))
	{
		//ライフを減らす
		g_aTower.nLife--;
	}

	//設置
	Update_Pos_Tower();

	//色変更
	Update_Col_Tower();

	//アニメーション
	Update_Tex_Tower();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Tower(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Tower, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Tower[0]);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//守護対象構造体の情報を設定する関数
//************************************************
void SetInfo_Tower(void)
{
	g_aTower.pos = D3DXVECTOR3(SCREEN_HALFWIDTH, 690.0f, 0.0f);
	g_aTower.fTexSpan[0] = 0.0f;
	g_aTower.fTexSpan[1] = SPAN_CHANGE_TEX_TOWER;
	g_aTower.fRadius[0] = RADIUS_TOWER_X;
	g_aTower.fRadius[1] = RADIUS_TOWER_Y;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			g_aTower.fLength[nCnt] = sqrtf((RADIUS_TOWER_X * RADIUS_TOWER_X) +
				((RADIUS_TOWER_Y * 2.0f) * (RADIUS_TOWER_Y * 2.0f)));
			g_aTower.fAngle[nCnt] = atan2f(RADIUS_TOWER_X * 2.0f, (RADIUS_TOWER_Y * 2.0f) * 2.0f);
			break;
		case 1:
			g_aTower.fLength[nCnt] = sqrtf((RADIUS_TOWER_X * RADIUS_TOWER_X));
			g_aTower.fAngle[nCnt] = atan2f(RADIUS_TOWER_X * 2.0f, 0.0f);
			break;
		}
	}
	g_aTower.nLife = AMOUNT_MAX_LIFE_TOWER;
}

//************************************************
//守護対象の位置を設定する関数
//************************************************
void Update_Pos_Tower(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tower;

	//座標変更
	g_aTower.pos += g_aTower.move;

	ConvertInfo_Screen(&g_aTower.pos);

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tower->Lock(0, 0, (void**)&pVtx_Tower, 0);

	pVtx_Tower[0].pos.x = g_aTower.pos.x + sinf(g_aTower.rot.z - (D3DX_PI - g_aTower.fAngle[0])) * g_aTower.fLength[0];
	pVtx_Tower[0].pos.y = g_aTower.pos.y + cosf(g_aTower.rot.z - (D3DX_PI - g_aTower.fAngle[0])) * g_aTower.fLength[0];
	pVtx_Tower[1].pos.x = g_aTower.pos.x + sinf(g_aTower.rot.z + (D3DX_PI - g_aTower.fAngle[0])) * g_aTower.fLength[0];
	pVtx_Tower[1].pos.y = g_aTower.pos.y + cosf(g_aTower.rot.z + (D3DX_PI - g_aTower.fAngle[0])) * g_aTower.fLength[0];
	pVtx_Tower[2].pos.x = g_aTower.pos.x + sinf(g_aTower.rot.z - g_aTower.fAngle[1]) * g_aTower.fLength[1];
	pVtx_Tower[2].pos.y = g_aTower.pos.y + cosf(g_aTower.rot.z - g_aTower.fAngle[1]) * g_aTower.fLength[1];
	pVtx_Tower[3].pos.x = g_aTower.pos.x + sinf(g_aTower.rot.z + g_aTower.fAngle[1]) * g_aTower.fLength[1];
	pVtx_Tower[3].pos.y = g_aTower.pos.y + cosf(g_aTower.rot.z + g_aTower.fAngle[1]) * g_aTower.fLength[1];

	//頂点バッファをアンロックする
	g_pVtxBuff_Tower->Unlock();
}

//************************************************
//守護対象の色を変更する関数
//************************************************
void Update_Col_Tower(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tower;

	if (g_aTower.nCT > 0)
	{
		g_aTower.nCT--;

		g_aTower.col.r = 0.5f;
		g_aTower.col.g = 0.5f;

		//明滅用1
		g_aTower.col.a -= g_F;
		if (g_aTower.col.a < 0.0f || g_aTower.col.a > 1.0f)
		{
			g_F *= -1.0f;
		}
	}
	else
	{
		g_aTower.col.r = 1.0f;
		g_aTower.col.g = 1.0f;
		g_aTower.col.a = 1.0f;
	}

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tower->Lock(0, 0, (void**)&pVtx_Tower, 0);

	pVtx_Tower[0].col = g_aTower.col;
	pVtx_Tower[1].col = g_aTower.col;
	pVtx_Tower[2].col = g_aTower.col;
	pVtx_Tower[3].col = g_aTower.col;

	//頂点バッファをアンロックする
	g_pVtxBuff_Tower->Unlock();
}

//************************************************
//守護対象のテクスチャを動かす関数
//************************************************
void Update_Tex_Tower(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Tower;

	//テクスチャを変更
	g_aTower.nCntTex++;
	if (g_aTower.nCntTex > SPD_CHANGE_TEX_TOWER)
	{
		g_aTower.nCntTex = 0;
		g_aTower.nCntPattern++;
		g_aTower.fTexSpan[0] += SPAN_CHANGE_TEX_TOWER;
		g_aTower.fTexSpan[1] += SPAN_CHANGE_TEX_TOWER;
		if (g_aTower.nCntPattern >= AMOUNT_STYLE_TEX_TOWER)
		{
			g_aTower.nCntPattern = 0;
			g_aTower.fTexSpan[0] = 0;
			g_aTower.fTexSpan[1] = SPAN_CHANGE_TEX_TOWER;
		}
	}

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Tower->Lock(0, 0, (void**)&pVtx_Tower, 0);

	pVtx_Tower[0].tex = D3DXVECTOR2(g_aTower.fTexSpan[0], 0.0f);
	pVtx_Tower[1].tex = D3DXVECTOR2(g_aTower.fTexSpan[1], 0.0f);
	pVtx_Tower[2].tex = D3DXVECTOR2(g_aTower.fTexSpan[0], 1.0f);
	pVtx_Tower[3].tex = D3DXVECTOR2(g_aTower.fTexSpan[1], 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Tower->Unlock();
}

//************************************************
//守護対象の構造体のアドレスを渡す
//************************************************
TOWER* GetInfo_Tower(void)
{
	return &g_aTower;
}