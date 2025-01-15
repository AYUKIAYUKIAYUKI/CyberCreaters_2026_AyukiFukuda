//************************************************
//
//ブレイクブロック[breakblock.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "sound.h"
#include "breakblock.h"
#include "particle.h"
#include "particle_block.h"
#include "player.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_BreakBlock[AMOUNT_TEXTURE_BLOCK] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_BreakBlock = NULL;	//頂点バッファのポインタ
BREAKBLOCK g_aBreakBlock[AMOUNT_POLYGON_BREAKBLOCK];	//スライドブロックの各情報
double g_aFileData_BreakBlock[AMOUNT_POLYGON_BREAKBLOCK][AMOUNT_POLYGON_BREAKBLOCK] = {};	//ファイルからデータを格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_BreakBlock(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_1_BLOCK,
		&g_pTexture_BreakBlock[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SHROT_2_BLOCK,
		&g_pTexture_BreakBlock[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_1_BLOCK,
		&g_pTexture_BreakBlock[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_MIDDLE_2_BLOCK,
		&g_pTexture_BreakBlock[3]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_1_BLOCK,
		&g_pTexture_BreakBlock[4]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_TALL_2_BLOCK,
		&g_pTexture_BreakBlock[5]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BREAKBLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_BreakBlock,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Score;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_BreakBlock->Lock(0, 0, (void**)&pVtx_Score, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BREAKBLOCK; nCnt++)
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
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BREAKBLOCK; nCnt++)
	{
		g_aBreakBlock[nCnt].nStyle = BLOCKSTYLE_SHROT_1;
		g_aBreakBlock[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBreakBlock[nCnt].fHalfSpanX = 0.0f;
		g_aBreakBlock[nCnt].fHalfSpanY = 0.0f;
		g_aBreakBlock[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBreakBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBreakBlock[nCnt].bUse = false;
		g_aBreakBlock[nCnt].nCntSpawn = 0;
		g_aBreakBlock[nCnt].nLife = 0;
		g_aBreakBlock[nCnt].fLength = 0.0f;
		g_aBreakBlock[nCnt].fAngle = 0.0f;
	}

	//ファイル情報格納用を初期化
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_BREAKBLOCK; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_BLOCK)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData_BreakBlock[nCnt1][nCnt2] = {};
	}

	//ブロック情報を設定する
	Setinfo_BreakBlock();

	//頂点バッファをアンロックする
	g_pVtxBuff_BreakBlock->Unlock();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_BreakBlock(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BLOCK; nCnt++)
	{
		if (g_pTexture_BreakBlock[nCnt] != NULL)
		{
			g_pTexture_BreakBlock[nCnt]->Release();
			g_pTexture_BreakBlock[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_BreakBlock != NULL)
	{
		g_pVtxBuff_BreakBlock->Release();
		g_pVtxBuff_BreakBlock = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************;
void Update_BreakBlock(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_BreakBlock;

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
	g_pVtxBuff_BreakBlock->Lock(0, 0, (void**)&pVtx_BreakBlock, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		if (g_aBreakBlock[nCnt].bUse)
		{
			//時間経過で登場
			if (g_aBreakBlock[nCnt].nCntSpawn > 0)
			{
				g_aBreakBlock[nCnt].nCntSpawn--;
			}
			else
			{
				//移動
				g_aBreakBlock[nCnt].pos.x += g_aBreakBlock[nCnt].move.x;
				g_aBreakBlock[nCnt].pos.y += g_aBreakBlock[nCnt].move.y;

				//反転判定が出ているとき
				if (*pInversion == true &&
					g_aBreakBlock[nCnt].move.x <= 7.0f &&
					*pReInversion == false)
				{
					g_aBreakBlock[nCnt].move.x += 0.1f;
				}
				else if (*pInversion == true &&
					g_aBreakBlock[nCnt].move.x >= -10.0f &&
					*pReInversion == true)
				{
					g_aBreakBlock[nCnt].move.x -= 0.1f;
				}

				switch (g_aBreakBlock[nCnt].nLife)
				{
				case BREAKBLOCKSTATE_LIFE3:

					//色を赤色に変更
					g_aBreakBlock[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

					break;

				case BREAKBLOCKSTATE_LIFE2:

					//色を朱色に変更
					g_aBreakBlock[nCnt].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

					break;

				case BREAKBLOCKSTATE_LIFE1:

					//色をオレンジに変更
					g_aBreakBlock[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

					break;

				case BREAKBLOCKSTATE_BROKEN:

					g_aBreakBlock[nCnt].pos.x = -100.0f;

					g_aBreakBlock[nCnt].bUse = false;

					break;
				}

				//プレイヤーが無敵時間外でこれ当たった時
				if (pPlayer->pos.x <= g_aBreakBlock[nCnt].pos.x + g_aBreakBlock[nCnt].fHalfSpanX - 30.0f + HALFSPAN_X_PLAYER - 40.0f &&
					pPlayer->pos.x >= g_aBreakBlock[nCnt].pos.x - g_aBreakBlock[nCnt].fHalfSpanX + 30.0f - HALFSPAN_X_PLAYER + 20.0f &&
					pPlayer->pos.y >= g_aBreakBlock[nCnt].pos.y - g_aBreakBlock[nCnt].fHalfSpanY + 30.0f - HALFSPAN_Y_PLAYER + 20.0f &&
					pPlayer->pos.y <= g_aBreakBlock[nCnt].pos.y + g_aBreakBlock[nCnt].fHalfSpanY - 30.0f + HALFSPAN_Y_PLAYER - 40.0f &&
					pPlayer->state == PLAYERSTATE_NORMAL)
				{
					//ヒット処理
					Hit_Player(1);
				}

				//移動、回転を反映
				pVtx_BreakBlock[0].pos.x = g_aBreakBlock[nCnt].pos.x + sinf(g_aBreakBlock[nCnt].rot.z - (D3DX_PI - g_aBreakBlock[nCnt].fAngle)) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[0].pos.y = g_aBreakBlock[nCnt].pos.y + cosf(g_aBreakBlock[nCnt].rot.z - (D3DX_PI - g_aBreakBlock[nCnt].fAngle)) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[1].pos.x = g_aBreakBlock[nCnt].pos.x + sinf(g_aBreakBlock[nCnt].rot.z + (D3DX_PI - g_aBreakBlock[nCnt].fAngle)) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[1].pos.y = g_aBreakBlock[nCnt].pos.y + cosf(g_aBreakBlock[nCnt].rot.z + (D3DX_PI - g_aBreakBlock[nCnt].fAngle)) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[2].pos.x = g_aBreakBlock[nCnt].pos.x + sinf(g_aBreakBlock[nCnt].rot.z - g_aBreakBlock[nCnt].fAngle) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[2].pos.y = g_aBreakBlock[nCnt].pos.y + cosf(g_aBreakBlock[nCnt].rot.z - g_aBreakBlock[nCnt].fAngle) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[3].pos.x = g_aBreakBlock[nCnt].pos.x + sinf(g_aBreakBlock[nCnt].rot.z + g_aBreakBlock[nCnt].fAngle) * g_aBreakBlock[nCnt].fLength;
				pVtx_BreakBlock[3].pos.y = g_aBreakBlock[nCnt].pos.y + cosf(g_aBreakBlock[nCnt].rot.z + g_aBreakBlock[nCnt].fAngle) * g_aBreakBlock[nCnt].fLength;

				//色変更の反映
				pVtx_BreakBlock[0].col = g_aBreakBlock[nCnt].col;
				pVtx_BreakBlock[1].col = g_aBreakBlock[nCnt].col;
				pVtx_BreakBlock[2].col = g_aBreakBlock[nCnt].col;
				pVtx_BreakBlock[3].col = g_aBreakBlock[nCnt].col;
			}
		}

		//ポインタをずらす
		pVtx_BreakBlock += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_BreakBlock->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_BreakBlock(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_BreakBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BLOCK; nCnt++)
	{
		//ブロックが使用されているなら
		if (g_aBreakBlock[nCnt].bUse == true)
		{
			switch (g_aBreakBlock[nCnt].nStyle)
			{
			case 0:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_BreakBlock[0]);

				break;

			case 1:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_BreakBlock[1]);

				break;

			case 2:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_BreakBlock[2]);

				break;

			case 3:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_BreakBlock[3]);

				break;

			case 4:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_BreakBlock[4]);

				break;

			case 5:

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTexture_BreakBlock[5]);

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
void Setinfo_BreakBlock(void)
{
	//データを分別する用
	int nLine = 0, nRow = 0;

	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(FILE_SET_BREAKBLOCK, "r");

	//データの一行目にある説明文字を飛ばす
	while (fgetc(pFile) != '\n');

	//ファイルが開けた
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_BreakBlock[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_BREAKBLOCK)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_BreakBlock;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_BreakBlock->Lock(0, 0, (void**)&pVtx_BreakBlock, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		//ブロックの使用判定が無い時
		if (g_aBreakBlock[nCnt].bUse == false)
		{
			g_aBreakBlock[nCnt].nStyle = (int)g_aFileData_BreakBlock[0][nCnt];
			g_aBreakBlock[nCnt].pos.x = (float)g_aFileData_BreakBlock[1][nCnt];
			g_aBreakBlock[nCnt].pos.y = (float)g_aFileData_BreakBlock[2][nCnt];
			g_aBreakBlock[nCnt].fHalfSpanX = (float)g_aFileData_BreakBlock[3][nCnt];
			g_aBreakBlock[nCnt].fHalfSpanY = (float)g_aFileData_BreakBlock[4][nCnt];
			g_aBreakBlock[nCnt].move.x = (float)g_aFileData_BreakBlock[5][nCnt];
			g_aBreakBlock[nCnt].move.y = (float)g_aFileData_BreakBlock[6][nCnt];
			g_aBreakBlock[nCnt].move.z = (float)g_aFileData_BreakBlock[7][nCnt];
			g_aBreakBlock[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBreakBlock[nCnt].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
			g_aBreakBlock[nCnt].bUse = true;
			g_aBreakBlock[nCnt].nCntSpawn = (int)g_aFileData_BreakBlock[8][nCnt];
			g_aBreakBlock[nCnt].nLife = (int)g_aFileData_BreakBlock[9][nCnt];
			g_aBreakBlock[nCnt].fLength = (float)g_aFileData_BreakBlock[10][nCnt];
			g_aBreakBlock[nCnt].fAngle = (float)g_aFileData_BreakBlock[11][nCnt];
		}

		pVtx_BreakBlock += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_BreakBlock->Unlock();
}

//************************************************
//ブレイクブロックへの命中処理関数
//************************************************
void Hit_BreakBlock(int nCntBreakBlock, int nDamage)
{
	//効果音を鳴らす
	PlaySound(SOUND_LABEL_SE_DAMAGE);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_BreakBlock;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_BreakBlock->Lock(0, 0, (void**)&pVtx_BreakBlock, 0);

	//命中に伴い耐久値を減らす
	g_aBreakBlock[nCntBreakBlock].nLife -= nDamage;

	//破壊
	if (g_aBreakBlock[nCntBreakBlock].nLife <= BREAKBLOCKSTATE_BROKEN)
	{
		/*岩を飛び散らせる予定*/
		//パーティクルを出す(適量)
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			Setinfo_Particle_Block(g_aBreakBlock[nCntBreakBlock].pos, g_aBreakBlock[nCntBreakBlock].move);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_BreakBlock->Unlock();
}

//************************************************
//ブレイクブロックの情報を引き渡す関数
//************************************************
BREAKBLOCK* Getinfo_BreakBlock(void)
{
	return &g_aBreakBlock[0];
}