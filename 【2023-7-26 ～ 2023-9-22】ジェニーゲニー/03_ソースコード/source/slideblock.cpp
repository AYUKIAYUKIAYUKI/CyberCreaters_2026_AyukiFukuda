//************************************************
//
//スライドブロック[slideblock.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "player.h"
#include "slideblock.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_SlideBlock[AMOUNT_TEXTURE_BLOCK] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_SlideBlock = NULL;	//頂点バッファのポインタ
SLIDEBLOCK g_aSlideBlock[AMOUNT_POLYGON_SLIDEBLOCK];	//スライドブロックの各情報
double g_aFileData_SlideBlock[AMOUNT_POLYGON_SLIDEBLOCK][AMOUNT_POLYGON_SLIDEBLOCK] = {};	//ファイルからデータを格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_SlideBlock(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_1_BLOCK,
		&g_pTexture_SlideBlock[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_2_BLOCK,
		&g_pTexture_SlideBlock[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_1_BLOCK,
		&g_pTexture_SlideBlock[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_2_BLOCK,
		&g_pTexture_SlideBlock[3]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_1_BLOCK,
		&g_pTexture_SlideBlock[4]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_2_BLOCK,
		&g_pTexture_SlideBlock[5]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SLIDEBLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_SlideBlock,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_SlideBlock->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SLIDEBLOCK; nCnt++)
	{
		//頂点座標の設定
		pVtx_Score[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Score[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx_Score[0].rhw = 1.0f;
		pVtx_Score[1].rhw = 1.0f;
		pVtx_Score[2].rhw = 1.0f;
		pVtx_Score[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx_Score[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Score[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Score[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Score[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設
		pVtx_Score[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Score[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Score[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Score[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Score += AMOUNT_VTX;
	}

	//スライドブロック各情報の初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SLIDEBLOCK; nCnt++)
	{
		g_aSlideBlock[nCnt].nStyle = BLOCKSTYLE_SHROT_1;
		g_aSlideBlock[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSlideBlock[nCnt].fHalfSpanX = 0.0f;
		g_aSlideBlock[nCnt].fHalfSpanY = 0.0f;
		g_aSlideBlock[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSlideBlock[nCnt].fStop = 0.0f;
		g_aSlideBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSlideBlock[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aSlideBlock[nCnt].fColChange = 0.0f;
		g_aSlideBlock[nCnt].bUse = false;
		g_aSlideBlock[nCnt].nCntSpawn = 0;
		g_aSlideBlock[nCnt].fLength = 0.0f;
		g_aSlideBlock[nCnt].fAngle = 0.0f;
	}

	//ファイル情報格納用を初期化
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_SLIDEBLOCK; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_BLOCK)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData_SlideBlock[nCnt1][nCnt2] = {};
	}

	//ブロック情報を設定する
	Setinfo_SlideBlock();

	//頂点バッファをアンロックする
	g_pVtxBuff_SlideBlock->Unlock();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_SlideBlock(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BLOCK; nCnt++)
	{
		if (g_pTexture_SlideBlock[nCnt] != NULL)
		{
			g_pTexture_SlideBlock[nCnt]->Release();
			g_pTexture_SlideBlock[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_SlideBlock != NULL)
	{
		g_pVtxBuff_SlideBlock->Release();
		g_pVtxBuff_SlideBlock = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_SlideBlock(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_SlideBlock;

	//プレイヤー情報へのポインタ
	PLAYER* pPlayer;

	//タイマー情報のポインタ
	bool* pInversion;
	bool* pReInversion;

	//プレイヤー情報の取得
	pPlayer = Getinfo_Player();	//プレイヤー情報系の先頭アドレスが代入される

	//反転情報の取得
	pInversion = Getinfo_Inversion_Timer();
	pReInversion = Getinfo_ReInversion_Timer();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_SlideBlock->Lock(0, 0, (void**)&pVtx_SlideBlock, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		if (g_aSlideBlock[nCnt].bUse == true)
		{
			//時間経過で登場
			if (g_aSlideBlock[nCnt].nCntSpawn > 0)
			{
				g_aSlideBlock[nCnt].nCntSpawn--;
			}
			else
			{
				//移動
				g_aSlideBlock[nCnt].pos.x += g_aSlideBlock[nCnt].move.x;
				//g_aSlideBlock[nCnt].pos.y += g_aSlideBlock[nCnt].move.y;
				
				//停止ラインを越えるまで
				if (g_aSlideBlock[nCnt].pos.y < g_aSlideBlock[nCnt].fStop ||
					g_aSlideBlock[nCnt].pos.y > g_aSlideBlock[nCnt].fStop)
				{
					g_aSlideBlock[nCnt].pos.y += g_aSlideBlock[nCnt].move.y;
				}
				//越えたら色変化
				else
				{
					if (g_aSlideBlock[nCnt].fColChange < 1.0f)
					{
						g_aSlideBlock[nCnt].col.g += g_aSlideBlock[nCnt].fColChange;
						g_aSlideBlock[nCnt].col.b += g_aSlideBlock[nCnt].fColChange;
					}
				}

				//反転判定が出ているとき
				if (*pInversion == true &&
					g_aSlideBlock[nCnt].move.x <= 7.0f &&
					*pReInversion == false)
				{
					g_aSlideBlock[nCnt].move.x += 0.1f;
				}
				else if (*pInversion == true &&
					g_aSlideBlock[nCnt].move.x >= -9.9f &&
					*pReInversion == true)
				{
					g_aSlideBlock[nCnt].move.x -= 0.1f;
				}

				//プレイヤーが無敵時間外でこれ当たった時
				if (pPlayer->pos.x <= g_aSlideBlock[nCnt].pos.x + g_aSlideBlock[nCnt].fHalfSpanX - 30.0f + HALFSPAN_X_PLAYER - 40.0f &&
					pPlayer->pos.x >= g_aSlideBlock[nCnt].pos.x - g_aSlideBlock[nCnt].fHalfSpanX + 30.0f - HALFSPAN_X_PLAYER + 20.0f &&
					pPlayer->pos.y >= g_aSlideBlock[nCnt].pos.y - g_aSlideBlock[nCnt].fHalfSpanY + 30.0f - HALFSPAN_Y_PLAYER + 20.0f &&
					pPlayer->pos.y <= g_aSlideBlock[nCnt].pos.y + g_aSlideBlock[nCnt].fHalfSpanY - 30.0f + HALFSPAN_Y_PLAYER - 40.0f &&
					pPlayer->state == PLAYERSTATE_NORMAL)
				{
					//ヒット処理
					Hit_Player(1);
				}

				//上下へ居なくなる物は
				if (g_aSlideBlock[nCnt].pos.y < -500.0f ||
					g_aSlideBlock[nCnt].pos.y > 1500.0f)
				{
					//消滅処理
					Disapper_SlideBlock(nCnt);
				}

				//移動、回転を反映
				pVtx_SlideBlock[0].pos.x = g_aSlideBlock[nCnt].pos.x + sinf(g_aSlideBlock[nCnt].rot.z - (D3DX_PI - g_aSlideBlock[nCnt].fAngle)) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[0].pos.y = g_aSlideBlock[nCnt].pos.y + cosf(g_aSlideBlock[nCnt].rot.z - (D3DX_PI - g_aSlideBlock[nCnt].fAngle)) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[1].pos.x = g_aSlideBlock[nCnt].pos.x + sinf(g_aSlideBlock[nCnt].rot.z + (D3DX_PI - g_aSlideBlock[nCnt].fAngle)) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[1].pos.y = g_aSlideBlock[nCnt].pos.y + cosf(g_aSlideBlock[nCnt].rot.z + (D3DX_PI - g_aSlideBlock[nCnt].fAngle)) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[2].pos.x = g_aSlideBlock[nCnt].pos.x + sinf(g_aSlideBlock[nCnt].rot.z - g_aSlideBlock[nCnt].fAngle) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[2].pos.y = g_aSlideBlock[nCnt].pos.y + cosf(g_aSlideBlock[nCnt].rot.z - g_aSlideBlock[nCnt].fAngle) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[3].pos.x = g_aSlideBlock[nCnt].pos.x + sinf(g_aSlideBlock[nCnt].rot.z + g_aSlideBlock[nCnt].fAngle) * g_aSlideBlock[nCnt].fLength;
				pVtx_SlideBlock[3].pos.y = g_aSlideBlock[nCnt].pos.y + cosf(g_aSlideBlock[nCnt].rot.z + g_aSlideBlock[nCnt].fAngle) * g_aSlideBlock[nCnt].fLength;

				//色変更の反映
				pVtx_SlideBlock[0].col = g_aSlideBlock[nCnt].col;
				pVtx_SlideBlock[1].col = g_aSlideBlock[nCnt].col;
				pVtx_SlideBlock[2].col = g_aSlideBlock[nCnt].col;
				pVtx_SlideBlock[3].col = g_aSlideBlock[nCnt].col;
			}
		}

		//ポインタをずらす
		pVtx_SlideBlock += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_SlideBlock->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_SlideBlock(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_SlideBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		//ブロックが使用されているなら
		if (g_aSlideBlock[nCnt].bUse == true)
		{
			switch (g_aSlideBlock[nCnt].nStyle)
			{
			case 0:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_SlideBlock[0]);

				break;

			case 1:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_SlideBlock[1]);

				break;

			case 2:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_SlideBlock[2]);

				break;

			case 3:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_SlideBlock[3]);

				break;

			case 4:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_SlideBlock[4]);

				break;

			case 5:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_SlideBlock[5]);

				break;
			}

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}
}

//************************************************
//ブロック位置設定処理関数
//************************************************
void Setinfo_SlideBlock(void)
{
	//データを分別する用
	int nLine = 0, nRow = 0;

	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(FILE_SET_SLIDEBLOCK, "r");

	//データの一行目にある説明文字を飛ばす
	while (fgetc(pFile) != '\n');

	//ファイルが開けた
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_SlideBlock[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_SLIDEBLOCK)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_SlideBlock;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_SlideBlock->Lock(0, 0, (void**)&pVtx_SlideBlock, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		//ブロックの使用判定が無い時
		if (g_aSlideBlock[nCnt].bUse == false)
		{
			g_aSlideBlock[nCnt].nStyle = (int)g_aFileData_SlideBlock[0][nCnt];
			g_aSlideBlock[nCnt].pos.x = (float)g_aFileData_SlideBlock[1][nCnt];
			g_aSlideBlock[nCnt].pos.y = (float)g_aFileData_SlideBlock[2][nCnt];
			g_aSlideBlock[nCnt].fHalfSpanX = (float)g_aFileData_SlideBlock[3][nCnt];
			g_aSlideBlock[nCnt].fHalfSpanY = (float)g_aFileData_SlideBlock[4][nCnt];
			g_aSlideBlock[nCnt].move.x = (float)g_aFileData_SlideBlock[5][nCnt];
			g_aSlideBlock[nCnt].move.y = (float)g_aFileData_SlideBlock[6][nCnt];
			g_aSlideBlock[nCnt].move.z = (float)g_aFileData_SlideBlock[7][nCnt];
			g_aSlideBlock[nCnt].fStop = (float)g_aFileData_SlideBlock[8][nCnt];
			g_aSlideBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aSlideBlock[nCnt].col = D3DXCOLOR(1.0f, 0.25f, 0.25f, 1.0f);
			g_aSlideBlock[nCnt].fColChange = (float)g_aFileData_SlideBlock[9][nCnt];
			g_aSlideBlock[nCnt].bUse = true;
			g_aSlideBlock[nCnt].nCntSpawn = (int)g_aFileData_SlideBlock[10][nCnt];
			g_aSlideBlock[nCnt].fLength = (float)g_aFileData_SlideBlock[11][nCnt];
			g_aSlideBlock[nCnt].fAngle = (float)g_aFileData_SlideBlock[12][nCnt];
		}

		pVtx_SlideBlock += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_SlideBlock->Unlock();
}

//************************************************
//スライドブロックの情報を引き渡す関数
//************************************************
SLIDEBLOCK* Getinfo_SlideBlock(void)
{
	return &g_aSlideBlock[0];
}

//************************************************
//使命を終えたスライドブロックの消滅処理関数
//************************************************
void Disapper_SlideBlock(int nCntSlideBlock)
{
	g_aSlideBlock[nCntSlideBlock].nStyle = BLOCKSTYLE_SHROT_1;
	g_aSlideBlock[nCntSlideBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aSlideBlock[nCntSlideBlock].fHalfSpanX = 0.0f;
	g_aSlideBlock[nCntSlideBlock].fHalfSpanY = 0.0f;
	g_aSlideBlock[nCntSlideBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aSlideBlock[nCntSlideBlock].fStop = 0.0f;
	g_aSlideBlock[nCntSlideBlock].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aSlideBlock[nCntSlideBlock].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aSlideBlock[nCntSlideBlock].fColChange = 0.0f;
	g_aSlideBlock[nCntSlideBlock].bUse = false;
	g_aSlideBlock[nCntSlideBlock].nCntSpawn = 0;
	g_aSlideBlock[nCntSlideBlock].fLength = 0.0f;
	g_aSlideBlock[nCntSlideBlock].fAngle = 0.0f;
}