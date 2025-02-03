////************************************************
////
////ライフゲージ処理[gage_life.cpp]
////Author：福田歩希
////
////************************************************
//#include "main.h"
//#include "player.h"
//#include "gage_life.h"
//
////グローバル変数
//LPDIRECT3DTEXTURE9 g_pTexture_Gage_Life[AMOUNT_TEX_GAGE_LIFE] = {};	//テクスチャのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Gage_Life = NULL;	//頂点バッファのポインタ
//GAGE_LIFE g_aGage_Life[AMOUNT_POLYGON_GAGE_LIFE];	//ライフゲージ情報
//static int g_nHold;	//汎用整数保管用
//
////************************************************
////ポリゴン初期化処理関数
////************************************************
//void Init_Gage_Life()
//{
//	//デバイスへのポインタ
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//デバイスへの取得
//	pDevice = GetDevice();
//
//	//テクスチャの読込み
//	D3DXCreateTextureFromFile(pDevice,
//		TEXTURE_GAGE_LIFE,
//		&g_pTexture_Gage_Life[0]);
//
//	//テクスチャの読込み
//	D3DXCreateTextureFromFile(pDevice,
//		TEXTURE_GAGE_HEART,
//		&g_pTexture_Gage_Life[1]);
//
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_GAGE_LIFE,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuff_Gage_Life,
//		NULL);
//
//	//頂点情報へのポインタ
//	VERTEX_2D* pVtx_Gage_Life;
//
//	//頂点バッファをロックして頂点情報のポインタを取得
//	g_pVtxBuff_Gage_Life->Lock(0, 0, (void**)&pVtx_Gage_Life, 0);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		//頂点座標の初期設定
//		pVtx_Gage_Life[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx_Gage_Life[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx_Gage_Life[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx_Gage_Life[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//視錐台の拡大率(?)の初期設定
//		pVtx_Gage_Life[0].rhw = 1.0f;
//		pVtx_Gage_Life[1].rhw = 1.0f;
//		pVtx_Gage_Life[2].rhw = 1.0f;
//		pVtx_Gage_Life[3].rhw = 1.0f;
//
//		//頂点カラーの初期設定
//		pVtx_Gage_Life[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx_Gage_Life[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx_Gage_Life[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx_Gage_Life[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//テクスチャ座標の初期設定
//		pVtx_Gage_Life[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx_Gage_Life[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx_Gage_Life[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx_Gage_Life[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx_Gage_Life += AMOUNT_VTX;
//	}
//
//	//頂点バッファをアンロックする
//	g_pVtxBuff_Gage_Life->Unlock();
//
//	//ライフゲージ構造体の情報の初期化群
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		g_aGage_Life[nCnt].nStyle = 0;
//		g_aGage_Life[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aGage_Life[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aGage_Life[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aGage_Life[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//		g_aGage_Life[nCnt].nCntTex = 0;
//		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
//		{
//			g_aGage_Life[nCnt].fTexSpan[nCnt2] = 0.0f;
//			g_aGage_Life[nCnt].fRadius[nCnt2] = 0.0f;
//			g_aGage_Life[nCnt].fLength[nCnt2] = 0.0f;
//			g_aGage_Life[nCnt].fAngle[nCnt2] = 0.0f;
//		}
//	}
//
//	g_nHold = AMOUNT_MAX_LIFE_PLAYER;
//
//	//ライフゲージ構造体に情報を付与
//	SetInfo_Gage_Life();
//}
//
////************************************************
////ポリゴン終了処理関数
////************************************************
//void Uninit_Gage_Life(void)
//{
//	//テクスチャの破棄
//	for (int nCnt = 0; nCnt < AMOUNT_TEX_GAGE_LIFE; nCnt++)
//	{
//		if (g_pTexture_Gage_Life[nCnt] != NULL)
//		{
//			g_pTexture_Gage_Life[nCnt]->Release();
//			g_pTexture_Gage_Life[nCnt] = NULL;
//		}
//	}
//
//	//頂点バッファの破棄
//	if (g_pVtxBuff_Gage_Life != NULL)
//	{
//		g_pVtxBuff_Gage_Life->Release();
//		g_pVtxBuff_Gage_Life = NULL;
//	}
//}
//
////************************************************
////ポリゴン更新処理関数
////************************************************
//void Update_Gage_Life(void)
//{
//	PLAYER* pPlayer = GetInfo_Player();
//
//	//移動など
//	Update_Pos_Gage_Life();
//
//	//テクスチャアニメーション
//	Update_Tex_Gage_Life();
//
//	//カラー変更
//	Update_Col_Gage_Life();
//
//	//前回のライフを保持
//	g_nHold = pPlayer->nLife;
//}
//
////************************************************
////ポリゴン描画処理関数
////************************************************
//void Draw_Gage_Life(void)
//{
//	//デバイスへのポインタ
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//デバイスへのポインタ取得
//	pDevice = GetDevice();
//
//	//頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, g_pVtxBuff_Gage_Life, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		//テクスチャの設定
//		pDevice->SetTexture(0, g_pTexture_Gage_Life[nCnt]);
//
//		//ポリゴンの描画
//		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
//	}
//}
//
////************************************************
////ライフゲージ構造体の情報を設定する関数
////************************************************
//void SetInfo_Gage_Life(void)
//{
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		g_aGage_Life[nCnt].nStyle = nCnt;
//		g_aGage_Life[nCnt].pos = D3DXVECTOR3(350.0f - (nCnt * SPAN_EACH_GAGE_LIFE_X), 1000.0f - (nCnt * SPAN_EACH_GAGE_LIFE_Y), 0.0f);
//		g_aGage_Life[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		switch (g_aGage_Life[nCnt].nStyle)
//		{
//		case GAGE_LIFE_STYLE_GAGE:
//			g_aGage_Life[nCnt].fTexSpan[0] = 0.0f;
//			g_aGage_Life[nCnt].fTexSpan[1] = SPAN_CHANGE_TEX_GAGE_LIFE;
//			g_aGage_Life[nCnt].fRadius[0] = RADIUS_GAGE_LIFE_X;	//ライフゲージ横半幅
//			g_aGage_Life[nCnt].fRadius[1] = RADIUS_GAGE_LIFE_Y;	//ライフゲージ縦半幅
//			for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
//			{
//				g_aGage_Life[nCnt].fLength[nCnt2] = sqrtf((g_aGage_Life[nCnt].fRadius[0] * g_aGage_Life[nCnt].fRadius[0]) + (g_aGage_Life[nCnt].fRadius[1] * g_aGage_Life[nCnt].fRadius[1]));
//				g_aGage_Life[nCnt].fAngle[nCnt2] = atan2f(g_aGage_Life[nCnt].fRadius[0] * 2.0f, g_aGage_Life[nCnt].fRadius[1] * 2.0f);
//			}
//			break;
//		case GAGE_LIFE_STYLE_HEART:
//			g_aGage_Life[nCnt].fTexSpan[0] = 0.0f;
//			g_aGage_Life[nCnt].fTexSpan[1] = 1.0f;
//			g_aGage_Life[nCnt].fRadius[0] = RADIUS_GAGE_HEART_X;	//ライフハート横半幅
//			g_aGage_Life[nCnt].fRadius[1] = RADIUS_GAGE_HEART_Y;	//ライフハート縦半幅
//			for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
//			{
//				g_aGage_Life[nCnt].fLength[nCnt2] = sqrtf((g_aGage_Life[nCnt].fRadius[0] * g_aGage_Life[nCnt].fRadius[0]) + (g_aGage_Life[nCnt].fRadius[1] * g_aGage_Life[nCnt].fRadius[1]));
//				g_aGage_Life[nCnt].fAngle[nCnt2] = atan2f(g_aGage_Life[nCnt].fRadius[0] * 2.0f, g_aGage_Life[nCnt].fRadius[1] * 2.0f);
//			}
//			break;
//		}
//	}
//}
//
////************************************************
////ライフゲージの位置を設定する関数
////************************************************
//void Update_Pos_Gage_Life(void)
//{
//	//頂点情報へのポインタ
//	VERTEX_2D* pVtx_Gage_Life;
//
//	//頂点バッファをロックして頂点情報のポインタを取得
//	g_pVtxBuff_Gage_Life->Lock(0, 0, (void**)&pVtx_Gage_Life, 0);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		//色の変更期間に乗じてこちらも微振動
//		if (g_aGage_Life[nCnt].nCntTex > 0)
//		{
//			//適当に位置を変更
//			int X = rand() % 25, Y = rand() % 25, RX = rand() % 2, RY = rand() % 2;
//			//上下左右の移動もランダムに反転
//			RX == 0 ? 0 : X *= -1;
//			RY == 0 ? 0 : Y *= -1;
//			g_aGage_Life[nCnt].pos = D3DXVECTOR3(350.0f - (nCnt * SPAN_EACH_GAGE_LIFE_X) + X, 1000.0f - (nCnt * SPAN_EACH_GAGE_LIFE_Y) + Y, 0.0f);
//		}
//		//期間以外は定位置に
//		else
//		{
//			g_aGage_Life[nCnt].pos = D3DXVECTOR3(350.0f - (nCnt * SPAN_EACH_GAGE_LIFE_X), 1000.0f - (nCnt * SPAN_EACH_GAGE_LIFE_Y), 0.0f);
//		}
//
//		pVtx_Gage_Life[0].pos.x = g_aGage_Life[nCnt].pos.x + sinf(g_aGage_Life[nCnt].rot.z - (D3DX_PI - g_aGage_Life[nCnt].fAngle[0])) * g_aGage_Life[nCnt].fLength[0];
//		pVtx_Gage_Life[0].pos.y = g_aGage_Life[nCnt].pos.y + cosf(g_aGage_Life[nCnt].rot.z - (D3DX_PI - g_aGage_Life[nCnt].fAngle[0])) * g_aGage_Life[nCnt].fLength[0];
//		pVtx_Gage_Life[1].pos.x = g_aGage_Life[nCnt].pos.x + sinf(g_aGage_Life[nCnt].rot.z + (D3DX_PI - g_aGage_Life[nCnt].fAngle[0])) * g_aGage_Life[nCnt].fLength[0];
//		pVtx_Gage_Life[1].pos.y = g_aGage_Life[nCnt].pos.y + cosf(g_aGage_Life[nCnt].rot.z + (D3DX_PI - g_aGage_Life[nCnt].fAngle[0])) * g_aGage_Life[nCnt].fLength[0];
//		pVtx_Gage_Life[2].pos.x = g_aGage_Life[nCnt].pos.x + sinf(g_aGage_Life[nCnt].rot.z - g_aGage_Life[nCnt].fAngle[1]) * g_aGage_Life[nCnt].fLength[1];
//		pVtx_Gage_Life[2].pos.y = g_aGage_Life[nCnt].pos.y + cosf(g_aGage_Life[nCnt].rot.z - g_aGage_Life[nCnt].fAngle[1]) * g_aGage_Life[nCnt].fLength[1];
//		pVtx_Gage_Life[3].pos.x = g_aGage_Life[nCnt].pos.x + sinf(g_aGage_Life[nCnt].rot.z + g_aGage_Life[nCnt].fAngle[1]) * g_aGage_Life[nCnt].fLength[1];
//		pVtx_Gage_Life[3].pos.y = g_aGage_Life[nCnt].pos.y + cosf(g_aGage_Life[nCnt].rot.z + g_aGage_Life[nCnt].fAngle[1]) * g_aGage_Life[nCnt].fLength[1];
//
//		pVtx_Gage_Life += AMOUNT_VTX;
//	}
//
//	//頂点バッファをアンロックする
//	g_pVtxBuff_Gage_Life->Unlock();
//}
//
////************************************************
////ゲージの色を変更する関数
////************************************************
//void Update_Col_Gage_Life(void)
//{
//	//頂点情報へのポインタ
//	VERTEX_2D* pVtx_Gage_Life;
//
//	PLAYER* pPlayer = GetInfo_Player();
//
//	//頂点バッファをロックして頂点情報のポインタを取得
//	g_pVtxBuff_Gage_Life->Lock(0, 0, (void**)&pVtx_Gage_Life, 0);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		//体力に変動があると
//		if (g_nHold != pPlayer->nLife)
//		{
//			//変更期間を付与
//			g_aGage_Life[nCnt].nCntTex = 8;
//		}
//
//		//期間中いい感じに明滅
//		if (g_aGage_Life[nCnt].nCntTex > 0)
//		{
//			g_aGage_Life[nCnt].nCntTex--;
//
//			if (g_aGage_Life[nCnt].nCntTex < 4)
//			{
//				g_aGage_Life[nCnt].col.r = 0.0f;
//			}
//			g_aGage_Life[nCnt].col.g = 0.0f;
//			g_aGage_Life[nCnt].col.b = 0.0f;
//		}
//		//終わると戻る
//		else
//		{
//			g_aGage_Life[nCnt].col.r = 1.0f;
//			g_aGage_Life[nCnt].col.g = 1.0f;
//			g_aGage_Life[nCnt].col.b = 1.0f;
//		}
//
//		pVtx_Gage_Life[0].col = g_aGage_Life[nCnt].col;
//		pVtx_Gage_Life[1].col = g_aGage_Life[nCnt].col;
//		pVtx_Gage_Life[2].col = g_aGage_Life[nCnt].col;
//		pVtx_Gage_Life[3].col = g_aGage_Life[nCnt].col;
//
//		pVtx_Gage_Life += AMOUNT_VTX;
//	}
//
//	//頂点バッファをアンロックする
//	g_pVtxBuff_Gage_Life->Unlock();
//}
//
////************************************************
////ライフゲージのテクスチャを動かす関数
////************************************************
//void Update_Tex_Gage_Life(void)
//{
//	//頂点情報へのポインタ
//	VERTEX_2D* pVtx_Gage_Life;
//
//	PLAYER* pPlayer = GetInfo_Player();
//
//	//頂点バッファをロックして頂点情報のポインタを取得
//	g_pVtxBuff_Gage_Life->Lock(0, 0, (void**)&pVtx_Gage_Life, 0);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_GAGE_LIFE; nCnt++)
//	{
//		if (g_aGage_Life[nCnt].nStyle == GAGE_LIFE_STYLE_GAGE)
//		{
//			g_aGage_Life[nCnt].fTexSpan[0] = 1.0f - (SPAN_CHANGE_TEX_GAGE_LIFE * (pPlayer->nLife + 1));
//			g_aGage_Life[nCnt].fTexSpan[1] = 1.0f - (SPAN_CHANGE_TEX_GAGE_LIFE * pPlayer->nLife);
//		}
//
//		pVtx_Gage_Life[0].tex = D3DXVECTOR2(0.0f, g_aGage_Life[nCnt].fTexSpan[0]);
//		pVtx_Gage_Life[1].tex = D3DXVECTOR2(1.0f, g_aGage_Life[nCnt].fTexSpan[0]);
//		pVtx_Gage_Life[2].tex = D3DXVECTOR2(0.0f, g_aGage_Life[nCnt].fTexSpan[1]);
//		pVtx_Gage_Life[3].tex = D3DXVECTOR2(1.0f, g_aGage_Life[nCnt].fTexSpan[1]);
//
//		pVtx_Gage_Life += AMOUNT_VTX;
//	}
//
//	//頂点バッファをアンロックする
//	g_pVtxBuff_Gage_Life->Unlock();
//}
//
////************************************************
////ライフゲージ構造体のアドレスを渡す
////************************************************
//GAGE_LIFE* GetInfo_Gage_Life(void)
//{
//	return &g_aGage_Life[0];
//}