//************************************************
//
//リザルトの順位表示処理[grade.cpp]
//Author：福田歩希
//
//************************************************
#include "grade.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Grade[AMOUNT_TEXTURE_GRADE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Grade = NULL;	//頂点バッファのポインタ
GRADE g_aGrade[AMOUNT_POLYGON_GRADE];	//メニュー用ポリゴンの情報を格納

//************************************************
//初期化処理関数
//************************************************
void Init_Grade(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの設定
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GRADE_1,
		&g_pTexture_Grade[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_GRADE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Grade,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Grade;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Grade->Lock(0, 0, (void**)&pVtx_Grade, 0);

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GRADE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Grade[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Grade[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Grade[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Grade[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Grade[0].rhw = 1.0f;
		pVtx_Grade[1].rhw = 1.0f;
		pVtx_Grade[2].rhw = 1.0f;
		pVtx_Grade[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Grade[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Grade[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Grade[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Grade[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Grade[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Grade[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Grade[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Grade[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Grade += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Grade->Unlock();

	//初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GRADE; nCnt++)
	{
		g_aGrade[nCnt].nStyle = 0;
		g_aGrade[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGrade[nCnt].fSpanX = 0.0f;
		g_aGrade[nCnt].fSpanY = 0.0f;
		g_aGrade[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGrade[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGrade[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//初回のみ頂点を展開
	Setinfo_Grade();
}

//************************************************
//終了処理関数
//************************************************
void Uninit_Grade(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_GRADE; nCnt++)
	{
		if (g_pTexture_Grade[nCnt] != NULL)
		{
			g_pTexture_Grade[nCnt]->Release();
			g_pTexture_Grade[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Grade != NULL)
	{
		g_pVtxBuff_Grade->Release();
		g_pVtxBuff_Grade = NULL;
	}
}

//************************************************
//更新処理関数
//************************************************
void Update_Grade(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Grade;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Grade->Lock(0, 0, (void**)&pVtx_Grade, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GRADE; nCnt++)
	{
		//移動、回転を反映
		pVtx_Grade[0].pos.x = g_aGrade[nCnt].pos.x - g_aGrade[nCnt].fSpanX;
		pVtx_Grade[0].pos.y = g_aGrade[nCnt].pos.y - g_aGrade[nCnt].fSpanY;
		pVtx_Grade[1].pos.x = g_aGrade[nCnt].pos.x + g_aGrade[nCnt].fSpanX;
		pVtx_Grade[1].pos.y = g_aGrade[nCnt].pos.y - g_aGrade[nCnt].fSpanY;
		pVtx_Grade[2].pos.x = g_aGrade[nCnt].pos.x - g_aGrade[nCnt].fSpanX;
		pVtx_Grade[2].pos.y = g_aGrade[nCnt].pos.y + g_aGrade[nCnt].fSpanY;
		pVtx_Grade[3].pos.x = g_aGrade[nCnt].pos.x + g_aGrade[nCnt].fSpanX;
		pVtx_Grade[3].pos.y = g_aGrade[nCnt].pos.y + g_aGrade[nCnt].fSpanY;

		pVtx_Grade[0].col = g_aGrade[nCnt].col;
		pVtx_Grade[1].col = g_aGrade[nCnt].col;
		pVtx_Grade[2].col = g_aGrade[nCnt].col;
		pVtx_Grade[3].col = g_aGrade[nCnt].col;

		pVtx_Grade += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Grade->Unlock();
}

//************************************************
//描画処理関数
//************************************************
void Draw_Grade(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Grade, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GRADE; nCnt++)
	{
		switch (g_aGrade[nCnt].nStyle)
		{
		case 0:

			pDevice->SetTexture(0, g_pTexture_Grade[0]);

			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ポリゴン情報を設定する関数
//************************************************
void Setinfo_Grade(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GRADE; nCnt++)
	{
		g_aGrade[nCnt].nStyle = nCnt;
		g_aGrade[nCnt].pos = D3DXVECTOR3(300.0f, 300.0f + (150.0f * nCnt), 0.0f);
		g_aGrade[nCnt].fSpanX = 50.0f;
		g_aGrade[nCnt].fSpanY = 50.0f;
		g_aGrade[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGrade[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGrade[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
	}
}