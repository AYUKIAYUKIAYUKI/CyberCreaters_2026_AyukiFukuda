//************************************************
//
//アイテム処理[item.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "enemy.h"
#include "item.h"
#include "player.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Item = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Item = NULL;	//頂点バッファのポインタ
float g_fHoldRadius_Item = 0.0f;	//半径情報コピー用
ITEM g_aItem[AMOUNT_POLYGON_ITEM];	//アイテムの各情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Item(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Item;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ITEM,
		&g_pTexture_Item);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Item,
		NULL);

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Item->Lock(0, 0, (void**)&pVtx_Item, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ITEM; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Item[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Item[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Item[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Item[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Item[0].rhw = 1.0f;
		pVtx_Item[1].rhw = 1.0f;
		pVtx_Item[2].rhw = 1.0f;
		pVtx_Item[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Item[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Item[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Item[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Item[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx_Item[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Item[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Item[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Item[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Item += AMOUNT_VTX;	//頂点情報のポインタを4つ分進める
	}

	//半径情報コピー用変数初期化
	g_fHoldRadius_Item = 0.0f;

	//アイテム情報の初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ITEM; nCnt++)
	{
		g_aItem[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置情報を初期化
		g_aItem[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動情報を初期化
		g_aItem[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色情報を初期化
		g_aItem[nCnt].nRemain = 0;				//残存時間を初期化
		g_aItem[nCnt].bUse = false;				//使用状況判定を無くす
		g_aItem[nCnt].style = ITEMSTYLE_TRACE;	//アイテムの種類をトレースに
		g_aItem[nCnt].state = ITEMSTATE_NORMAL;	//アイテムの状態を通常に
		g_aItem[nCnt].fColorA = 1.0;			//透明度変更変数初期設定
		g_aItem[nCnt].fRadius = 0.0;			//半径格納変数初期化
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Item->Unlock();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Item(void)
{
	//テクスチャの破棄
	if (g_pTexture_Item != NULL)
	{
		g_pTexture_Item->Release();
		g_pTexture_Item = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Item != NULL)
	{
		g_pVtxBuff_Item->Release();
		g_pVtxBuff_Item = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Item(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Item;

	//プレイヤー情報へのポインタ
	PLAYER* pPlayer;

	//プレイヤー情報の取得
	pPlayer = Getinfo_Player();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Item->Lock(0, 0, (void**)&pVtx_Item, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ITEM; nCnt++)
	{
		//アイテムが使用されているとき
		if (g_aItem[nCnt].bUse)
		{
			//状態に応じて処理分け
			switch (g_aItem[nCnt].state)
			{
			case ITEMSTATE_NORMAL:

				g_aItem[nCnt].nRemain--;

				if (g_aItem[nCnt].nRemain <= 0)
				{
					g_aItem[nCnt].state = ITEMSTATE_FLASHING;	//点滅を開始

					g_aItem[nCnt].nRemain = FRASH_TIME_ITEM;	//お情けで僅かに残存延長
				}

				break;

			case ITEMSTATE_FLASHING:

				g_aItem[nCnt].nRemain--;

				//点滅
				g_aItem[nCnt].fColorA == 1.0f ? g_aItem[nCnt].fColorA = 0.0f : g_aItem[nCnt].fColorA = 1.0f;

				if (g_aItem[nCnt].nRemain <= 0)
				{
					g_aItem[nCnt].state = ITEMSTATE_DISAPPEAR;	//消滅致す
				}

				break;

			case ITEMSTATE_DISAPPEAR:

				Disappear_Item(nCnt);

				break;
			}

			//アイテムを吸い寄せる
			if (g_aItem[nCnt].state != ITEMSTATE_DISAPPEAR)
			{
				//アイテムの位置から自機の位置へのベクトル
				D3DXVECTOR3 CollisionVector = pPlayer->pos - g_aItem[nCnt].pos;

				////自機の位置とアイテムの位置の距離
				//float fDistance = sqrtf((CollisionVector.x * CollisionVector.x) + (CollisionVector.y * CollisionVector.y)) * 0.5f;

				////アイテムの持つ範囲内に入った時
				//if (fDistance < g_aItem[nCnt].fRadius)
				//{
					//吸い寄せ
					g_aItem[nCnt].pos += CollisionVector * 0.01f;

					//ブレ
					g_aItem[nCnt].move.x += sinf(g_aItem[nCnt].pos.x) * 0.035f;
					g_aItem[nCnt].move.y += cosf(g_aItem[nCnt].pos.y) * 0.035f;

					//ブレ反映
					g_aItem[nCnt].pos.x += g_aItem[nCnt].move.x;
					g_aItem[nCnt].pos.y += g_aItem[nCnt].move.y;
				//}
			}

			//アイテムに触れる
			if (pPlayer->pos.x >= g_aItem[nCnt].pos.x - HALFSPAN_X_ITEM - HALFSPAN_X_PLAYER &&
				pPlayer->pos.x <= g_aItem[nCnt].pos.x + HALFSPAN_X_ITEM + HALFSPAN_X_PLAYER &&
				pPlayer->pos.y <= g_aItem[nCnt].pos.y + HALFSPAN_Y_ITEM + HALFSPAN_Y_PLAYER &&
				pPlayer->pos.y >= g_aItem[nCnt].pos.y - HALFSPAN_Y_ITEM - HALFSPAN_Y_PLAYER)
			{
				//取得処理
				GetItem_Player(AMOUNT_ADD_LIFE);

				g_aItem[nCnt].state = ITEMSTATE_DISAPPEAR;
			}

			pVtx_Item[0].pos.x = g_aItem[nCnt].pos.x - HALFSPAN_X_ITEM;
			pVtx_Item[0].pos.y = g_aItem[nCnt].pos.y - HALFSPAN_Y_ITEM;
			pVtx_Item[1].pos.x = g_aItem[nCnt].pos.x + HALFSPAN_X_ITEM;
			pVtx_Item[1].pos.y = g_aItem[nCnt].pos.y - HALFSPAN_Y_ITEM;
			pVtx_Item[2].pos.x = g_aItem[nCnt].pos.x - HALFSPAN_X_ITEM;
			pVtx_Item[2].pos.y = g_aItem[nCnt].pos.y + HALFSPAN_Y_ITEM;
			pVtx_Item[3].pos.x = g_aItem[nCnt].pos.x + HALFSPAN_X_ITEM;
			pVtx_Item[3].pos.y = g_aItem[nCnt].pos.y + HALFSPAN_Y_ITEM;

			pVtx_Item[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aItem[nCnt].fColorA);
			pVtx_Item[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aItem[nCnt].fColorA);
			pVtx_Item[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aItem[nCnt].fColorA);
			pVtx_Item[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aItem[nCnt].fColorA);

			pVtx_Item += AMOUNT_VTX;
		}
		//使用されていないとき(バグ防止)
		else
		{
			g_aItem[nCnt].bUse = false;

			g_aItem[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			pVtx_Item[0].pos = g_aItem[nCnt].pos;
			pVtx_Item[1].pos = g_aItem[nCnt].pos;
			pVtx_Item[2].pos = g_aItem[nCnt].pos;
			pVtx_Item[3].pos = g_aItem[nCnt].pos;

			pVtx_Item += AMOUNT_VTX;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Item->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Item(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Item, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ITEM; nCnt++)
	{
		//アイテムが使用されている場合
		if (g_aItem[nCnt].bUse == true)
		{
			//敵の種類に応じてテクスチャを張り替え
			switch (g_aItem[nCnt].style)
			{
			case ITEMSTATE_NORMAL:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_Item);

				break;

			case 1:

				pDevice->SetTexture(0, g_pTexture_Item);

				break;
			}

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}

}

//************************************************
//アイテム設定処理関数
//************************************************
void Setinfo_Item(D3DXVECTOR3 pos, int nStyle)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Item;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Item->Lock(0, 0, (void**)&pVtx_Item, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ITEM; nCnt++)
	{
		//使用されていないアイテムを検知
		if (!g_aItem[nCnt].bUse)
		{
			g_aItem[nCnt].pos = pos;	//位置情報を代入
			g_aItem[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動情報を初期化
			g_aItem[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色を適当に設定
			g_aItem[nCnt].nRemain = REMAIN_TIME_ITEM;	//残存時間を適当に設定
			g_aItem[nCnt].bUse = true;	//使用判定を出す

			//アイテムの種類を振り分け
			switch (nStyle)
			{
			case ITEMSTYLE_TRACE:

				g_aItem[nCnt].style = ITEMSTYLE_TRACE;

				//吸い寄せ用の範囲をセット
				g_aItem[nCnt].fRadius = 600.0f;

				break;
			}

			g_aItem[nCnt].state = ITEMSTATE_NORMAL;	//アイテムの状態を通常に

			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Item->Unlock();
}

//************************************************
//アイテム消滅処理関数
//************************************************
void Disappear_Item(int nCntItem)
{
	g_aItem[nCntItem].pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);//位置情報を初期化
	g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動情報を初期化
	g_aItem[nCntItem].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色情報を初期化
	g_aItem[nCntItem].nRemain = 0;				//残存時間を初期化
	g_aItem[nCntItem].bUse = false;				//使用状況判定を無くす
	g_aItem[nCntItem].style = ITEMSTYLE_TRACE;	//アイテムの種類をトレースに
	g_aItem[nCntItem].state = ITEMSTATE_NORMAL;	//アイテムの状態を通常に
	g_aItem[nCntItem].fColorA = 1.0;			//透明度変更変数初期設定
	g_aItem[nCntItem].fRadius = 0.0;			//半径格納変数初期化
}