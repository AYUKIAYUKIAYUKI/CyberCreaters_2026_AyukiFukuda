//************************************************
//
//ブロック[block.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "block.h"
#include "player.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Block[AMOUNT_TEXTURE_BLOCK] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Block = NULL;	//頂点バッファのポインタ
BLOCK g_aBlock[AMOUNT_POLYGON_BLOCK];	//ブロックの各情報
double g_aFileData_Block[AMOUNT_POLYGON_BLOCK][AMOUNT_POLYGON_BLOCK] = {};	//ファイルからデータを格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Block(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_1_BLOCK,
		&g_pTexture_Block[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_2_BLOCK,
		&g_pTexture_Block[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_1_BLOCK,
		&g_pTexture_Block[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_2_BLOCK,
		&g_pTexture_Block[3]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_1_BLOCK,
		&g_pTexture_Block[4]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_2_BLOCK,
		&g_pTexture_Block[5]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BLOCK, 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Block,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Block->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
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
		pVtx_Score[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Score[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設
		pVtx_Score[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Score[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Score[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Score[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Score += AMOUNT_VTX;
	}

	//ブロック各情報の初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		g_aBlock[nCnt].nStyle = BLOCKSTYLE_SHROT_1;
		g_aBlock[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCnt].fHalfSpanX = 0.0f;
		g_aBlock[nCnt].fHalfSpanY = 0.0f;
		g_aBlock[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCnt].bUse = false;
		g_aBlock[nCnt].nCntSpawn = 0;
		g_aBlock[nCnt].fLength = 0.0f;
		g_aBlock[nCnt].fAngle = 0.0f;
	}

	//ファイル情報格納用を初期化
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_BLOCK; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_BLOCK)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData_Block[nCnt1][nCnt2] = {};
	}

	//ブロック情報を設定する
	Setinfo_Block();

	//頂点バッファをアンロックする
	g_pVtxBuff_Block->Unlock();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Block(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BLOCK; nCnt++)
	{
		if (g_pTexture_Block[nCnt] != NULL)
		{
			g_pTexture_Block[nCnt]->Release();
			g_pTexture_Block[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Block != NULL)
	{
		g_pVtxBuff_Block->Release();
		g_pVtxBuff_Block = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Block(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Block;

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
	g_pVtxBuff_Block->Lock(0, 0, (void**)&pVtx_Block, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		if (g_aBlock[nCnt].bUse == true)
		{
			//時間経過で登場
			if (g_aBlock[nCnt].nCntSpawn > 0)
			{
				g_aBlock[nCnt].nCntSpawn--;
			}
			else
			{
				//移動
				g_aBlock[nCnt].pos.x += g_aBlock[nCnt].move.x;
				g_aBlock[nCnt].pos.y += g_aBlock[nCnt].move.y;

				//反転判定が出ているとき
				if (*pInversion == true &&
					g_aBlock[nCnt].move.x <= 7.0f &&
					*pReInversion == false)
				{
					g_aBlock[nCnt].move.x += 0.1f;
				}
				else if (*pInversion == true &&
					g_aBlock[nCnt].move.x >= -10.0f &&
					*pReInversion == true)
				{
					g_aBlock[nCnt].move.x -= 0.1f;
				}

				//プレイヤーが無敵時間外でこれ当たった時
				if (pPlayer->pos.x <= g_aBlock[nCnt].pos.x + g_aBlock[nCnt].fHalfSpanX - 30.0f + HALFSPAN_X_PLAYER - 40.0f &&
					pPlayer->pos.x >= g_aBlock[nCnt].pos.x - g_aBlock[nCnt].fHalfSpanX + 30.0f - HALFSPAN_X_PLAYER + 20.0f &&
					pPlayer->pos.y >= g_aBlock[nCnt].pos.y - g_aBlock[nCnt].fHalfSpanY + 30.0f - HALFSPAN_Y_PLAYER + 20.0f &&
					pPlayer->pos.y <= g_aBlock[nCnt].pos.y + g_aBlock[nCnt].fHalfSpanY - 30.0f + HALFSPAN_Y_PLAYER - 40.0f &&
					pPlayer->state == PLAYERSTATE_NORMAL)
				{
					//ヒット処理
					Hit_Player(1);
				}

				//移動、回転を反映
				pVtx_Block[0].pos.x = g_aBlock[nCnt].pos.x + sinf(g_aBlock[nCnt].rot.z - (D3DX_PI - g_aBlock[nCnt].fAngle)) * g_aBlock[nCnt].fLength;
				pVtx_Block[0].pos.y = g_aBlock[nCnt].pos.y + cosf(g_aBlock[nCnt].rot.z - (D3DX_PI - g_aBlock[nCnt].fAngle)) * g_aBlock[nCnt].fLength;
				pVtx_Block[1].pos.x = g_aBlock[nCnt].pos.x + sinf(g_aBlock[nCnt].rot.z + (D3DX_PI - g_aBlock[nCnt].fAngle)) * g_aBlock[nCnt].fLength;
				pVtx_Block[1].pos.y = g_aBlock[nCnt].pos.y + cosf(g_aBlock[nCnt].rot.z + (D3DX_PI - g_aBlock[nCnt].fAngle)) * g_aBlock[nCnt].fLength;
				pVtx_Block[2].pos.x = g_aBlock[nCnt].pos.x + sinf(g_aBlock[nCnt].rot.z - g_aBlock[nCnt].fAngle) * g_aBlock[nCnt].fLength;
				pVtx_Block[2].pos.y = g_aBlock[nCnt].pos.y + cosf(g_aBlock[nCnt].rot.z - g_aBlock[nCnt].fAngle) * g_aBlock[nCnt].fLength;
				pVtx_Block[3].pos.x = g_aBlock[nCnt].pos.x + sinf(g_aBlock[nCnt].rot.z + g_aBlock[nCnt].fAngle) * g_aBlock[nCnt].fLength;
				pVtx_Block[3].pos.y = g_aBlock[nCnt].pos.y + cosf(g_aBlock[nCnt].rot.z + g_aBlock[nCnt].fAngle) * g_aBlock[nCnt].fLength;
			}
		}
	
		//ポインタをずらす
		pVtx_Block += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Block->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Block(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Block, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		//ブロックが使用されているなら
		if (g_aBlock[nCnt].bUse == true)
		{
			switch (g_aBlock[nCnt].nStyle)
			{
			case 0:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_Block[0]);

				break;

			case 1:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_Block[1]);

				break;

			case 2:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_Block[2]);

				break;

			case 3:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_Block[3]);

				break;

			case 4:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_Block[4]);

				break;

			case 5:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_Block[5]);

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
void Setinfo_Block(void)
{
	//データを分別する用
	int nLine = 0, nRow = 0;

	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(FILE_SET_BLOCK, "r");

	//データの一行目にある説明文字を飛ばす
	while (fgetc(pFile) != '\n');

	//ファイルが開けた
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_Block[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_BLOCK)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Block;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Block->Lock(0, 0, (void**)&pVtx_Block, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		//ブロックの使用判定が無い時
		if (g_aBlock[nCnt].bUse == false)
		{
			g_aBlock[nCnt].nStyle = (int)g_aFileData_Block[0][nCnt];
			g_aBlock[nCnt].pos.x = (float)g_aFileData_Block[1][nCnt];
			g_aBlock[nCnt].pos.y = (float)g_aFileData_Block[2][nCnt];
			g_aBlock[nCnt].fHalfSpanX = (float)g_aFileData_Block[3][nCnt];
			g_aBlock[nCnt].fHalfSpanY = (float)g_aFileData_Block[4][nCnt];
			g_aBlock[nCnt].move.x = (float)g_aFileData_Block[5][nCnt];
			g_aBlock[nCnt].move.y = (float)g_aFileData_Block[6][nCnt];
			g_aBlock[nCnt].move.z = (float)g_aFileData_Block[7][nCnt];
			g_aBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBlock[nCnt].bUse = true;
			g_aBlock[nCnt].nCntSpawn = (int)g_aFileData_Block[8][nCnt];
			g_aBlock[nCnt].fLength = (float)g_aFileData_Block[9][nCnt];
			g_aBlock[nCnt].fAngle = (float)g_aFileData_Block[10][nCnt];
			//float uno = g_aFileData_Block[10][nCnt];
			//g_aBlock[nCnt].fAngle = atan2((g_aBlock[nCnt].fHalfSpanX * 2), (g_aBlock[nCnt].fHalfSpanY * 2));
		}

		pVtx_Block += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Block->Unlock();
}

//************************************************
//ブロックの情報を引き渡す関数
//************************************************
BLOCK* Getinfo_Block(void)
{
	return &g_aBlock[0];
}