//************************************************
//
//ブロックパーティクル処理[particle_block.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "particle_block.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Particle_Block = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Particle_Block = NULL;	//頂点バッファのポインタ
PARTICLE_BLOCK g_aParticle_Block[AMOUNT_POLYGON_PARTICLE_BLOCK];	//パーティクル用情報を格納
float g_fLength_Particle_Block = 0.0f;	//対角線情報を格納
float g_fAngle_Particle_Block = 0.0f;	//角度情報を格納
int g_nCntPos = 0;

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Particle_Block()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PARTICLE_BLOCK,
		&g_pTexture_Particle_Block);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_PARTICLE_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Particle_Block,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle_Block->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_BLOCK; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Particle[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Particle[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Particle[0].rhw = 1.0f;
		pVtx_Particle[1].rhw = 1.0f;
		pVtx_Particle[2].rhw = 1.0f;
		pVtx_Particle[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Particle[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Particle[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Particle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Particle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Particle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Particle[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Particle += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle_Block->Unlock();

	//構造体の中身を初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_BLOCK; nCnt++)
	{
		g_aParticle_Block[nCnt].nStyle = 0;
		g_aParticle_Block[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Block[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Block[nCnt].moveB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Block[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle_Block[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle_Block[nCnt].fRadius = 0.0f;
		g_aParticle_Block[nCnt].nRemain = 0;
		g_aParticle_Block[nCnt].bUse = false;
		g_aParticle_Block[nCnt].fAngle = 0.0f;
	}

	//角度情報を設定
	g_fAngle_Particle_Block = atan2f(RADIUS_PARTICLE_BLOCK * 2.0f, RADIUS_PARTICLE_BLOCK * 2.0f);

	g_nCntPos = 0;
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Particle_Block(void)
{
	//テクスチャの破棄
	if (g_pTexture_Particle_Block != NULL)
	{
		g_pTexture_Particle_Block->Release();
		g_pTexture_Particle_Block = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Particle_Block != NULL)
	{
		g_pVtxBuff_Particle_Block->Release();
		g_pVtxBuff_Particle_Block = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Particle_Block(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle_Block;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle_Block->Lock(0, 0, (void**)&pVtx_Particle_Block, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_BLOCK; nCnt++)
	{
		if (g_aParticle_Block[nCnt].bUse)
		{
			//縮む
			g_aParticle_Block[nCnt].fRadius -= CHANGE_SPD_RADIUS_PARTICLE_BLOCK;

			//裏返るの防止
			if (g_aParticle_Block[nCnt].fRadius <= 0)
			{
				g_aParticle_Block[nCnt].fRadius = 0.0f;
			}

			//移動
			g_aParticle_Block[nCnt].pos.x += g_aParticle_Block[nCnt].move.x * MOVE_SPD_POS_PARTICLE_BLOCK;
			g_aParticle_Block[nCnt].pos.y += g_aParticle_Block[nCnt].move.y * MOVE_SPD_POS_PARTICLE_BLOCK;

			//それとは別にブロックの動きを同期
			g_aParticle_Block[nCnt].pos += g_aParticle_Block[nCnt].moveB;

			//回転
			g_aParticle_Block[nCnt].rot.z += g_aParticle_Block[nCnt].move.z;

			//頂点を展開する
			pVtx_Particle_Block[0].pos.x = g_aParticle_Block[nCnt].pos.x + sinf(g_aParticle_Block[nCnt].rot.z - (D3DX_PI - g_aParticle_Block[nCnt].fAngle)) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[0].pos.y = g_aParticle_Block[nCnt].pos.y + cosf(g_aParticle_Block[nCnt].rot.z - (D3DX_PI - g_aParticle_Block[nCnt].fAngle)) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[1].pos.x = g_aParticle_Block[nCnt].pos.x + sinf(g_aParticle_Block[nCnt].rot.z + (D3DX_PI - g_aParticle_Block[nCnt].fAngle)) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[1].pos.y = g_aParticle_Block[nCnt].pos.y + cosf(g_aParticle_Block[nCnt].rot.z + (D3DX_PI - g_aParticle_Block[nCnt].fAngle)) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[2].pos.x = g_aParticle_Block[nCnt].pos.x + sinf(g_aParticle_Block[nCnt].rot.z - g_aParticle_Block[nCnt].fAngle) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[2].pos.y = g_aParticle_Block[nCnt].pos.y + cosf(g_aParticle_Block[nCnt].rot.z - g_aParticle_Block[nCnt].fAngle) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[3].pos.x = g_aParticle_Block[nCnt].pos.x + sinf(g_aParticle_Block[nCnt].rot.z + g_aParticle_Block[nCnt].fAngle) * g_aParticle_Block[nCnt].fRadius;
			pVtx_Particle_Block[3].pos.y = g_aParticle_Block[nCnt].pos.y + cosf(g_aParticle_Block[nCnt].rot.z + g_aParticle_Block[nCnt].fAngle) * g_aParticle_Block[nCnt].fRadius;

			g_aParticle_Block[nCnt].nRemain--;

			//残存時間が無くなったとき
			if (g_aParticle_Block[nCnt].nRemain <= 0)
			{
				pVtx_Particle_Block[0].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Block[1].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Block[2].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
				pVtx_Particle_Block[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

				g_aParticle_Block[nCnt].bUse = false;	//使用判定を無くす
			}

			pVtx_Particle_Block[0].col = g_aParticle_Block[nCnt].col;
			pVtx_Particle_Block[1].col = g_aParticle_Block[nCnt].col;
			pVtx_Particle_Block[2].col = g_aParticle_Block[nCnt].col;
			pVtx_Particle_Block[3].col = g_aParticle_Block[nCnt].col;

			//ブロックの種類変えてもいいけど気が向いたら
			pVtx_Particle_Block[0].tex.x = 0.0f;
			pVtx_Particle_Block[1].tex.x = 0.333f;
			pVtx_Particle_Block[2].tex.x = 0.0f;
			pVtx_Particle_Block[3].tex.x = 0.333f;
		}

		pVtx_Particle_Block += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle_Block->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Particle_Block(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Particle_Block, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Particle_Block);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_BLOCK; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//パーティクルの情報を設定する関数
//************************************************
void Setinfo_Particle_Block(D3DXVECTOR3 pos, D3DXVECTOR3 moveBlock)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Particle;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Particle_Block->Lock(0, 0, (void**)&pVtx_Particle, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_PARTICLE_BLOCK; nCnt++)
	{
		//使用されていないパーティクルを検知した時
		if (!g_aParticle_Block[nCnt].bUse)
		{
			g_aParticle_Block[nCnt].nStyle = 0;
			g_aParticle_Block[nCnt].pos = pos;	//位置を適当に設定

			switch (g_nCntPos)
			{
			case 0:

				g_aParticle_Block[nCnt].pos.y -= 100.0f;

				break;

			case 2:

				g_aParticle_Block[nCnt].pos.y += 100.0f;

				g_nCntPos = -1;

				break;
			}

			g_nCntPos++;

			//それっぽく計算(要改善…)
			float fRandomX = (rand() % 314) * 0.01f;
			float fRandomY = (rand() % 314) * 0.01f;

			int nRondom = rand() % 2;

			nRondom == 0 ?
				0 :
				fRandomX *= -1.0f, fRandomY *= -1.0f;

			g_aParticle_Block[nCnt].move.x = sinf(D3DX_PI - fRandomX);			//移動量を適当に設定
			g_aParticle_Block[nCnt].move.y = cosf(D3DX_PI - fRandomY);			//移動量を適当に設定
			g_aParticle_Block[nCnt].move.z = (float)fRandomX * 0.1f;			//回転量を適当に設定
			g_aParticle_Block[nCnt].moveB = moveBlock;							//ブロックの移動量に同期
			g_aParticle_Block[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き情報を格納
			g_aParticle_Block[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);	//色を適当に設定
			g_aParticle_Block[nCnt].fRadius = RADIUS_PARTICLE_BLOCK;			//半径を適当に設定
			g_aParticle_Block[nCnt].nRemain = REMAIN_TIME_PARTICLE_BLOCK;		//残存時間を適当に設定
			g_aParticle_Block[nCnt].bUse = true;								//使用判定を出す
			g_aParticle_Block[nCnt].fAngle = g_fAngle_Particle_Block;			//角度を格納

			break;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Particle_Block->Unlock();
}