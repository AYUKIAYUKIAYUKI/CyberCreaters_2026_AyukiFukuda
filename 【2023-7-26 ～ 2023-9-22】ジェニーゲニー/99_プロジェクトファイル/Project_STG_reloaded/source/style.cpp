//************************************************
//
//弾のスタイル表示処理[style.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "player.h"
#include "style.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Style[AMOUNT_TEXTURE_STYLE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Style = NULL;	//頂点バッファのポインタ
int g_nChoosingBulletStyle_Style = 0;	//選択している弾の種類
BULLETSTYLE_INDICATE g_aBlletStyle;	//弾表示の構造体

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Style()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_COMET_BULLET,
		&g_pTexture_Style[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_REUNION_ODD_BULLET,
		&g_pTexture_Style[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_KING_BULLET,
		&g_pTexture_Style[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Style,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Style;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Style->Lock(0, 0, (void**)&pVtx_Style, 0);

	//頂点座標の初期設定
	pVtx_Style[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Style[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Style[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Style[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Style[0].rhw = 1.0f;
	pVtx_Style[1].rhw = 1.0f;
	pVtx_Style[2].rhw = 1.0f;
	pVtx_Style[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Style[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Style[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Style[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Style[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の初期設定
	pVtx_Style[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Style[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Style[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Style[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//現在の弾の種類をデフォルトに設定
	g_nChoosingBulletStyle_Style = 0;

	//弾表示の構造体を初期化
	g_aBlletStyle.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aBlletStyle.fMoveZ = 0.0f;
	g_aBlletStyle.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aBlletStyle.style = BULLETSTYLE_COMET;
	g_aBlletStyle.fLength = 0.0f;
	g_aBlletStyle.fAngle = 0.0f;
	g_aBlletStyle.nPattern = 0;
	g_aBlletStyle.fTexX = 0.0f;
	g_aBlletStyle.fTexY = 0.0f;
	
	//頂点バッファをアンロックする
	g_pVtxBuff_Style->Unlock();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Style(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_STYLE; nCnt++)
	{
		if (g_pTexture_Style[nCnt] != NULL)
		{
			g_pTexture_Style[nCnt]->Release();
			g_pTexture_Style[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Style != NULL)
	{
		g_pVtxBuff_Style->Release();
		g_pVtxBuff_Style = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Style(void)
{
	//現在選択している弾の種類を代入する
	g_nChoosingBulletStyle_Style = *Getinfo_BulletStyle();

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Style;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Style->Lock(0, 0, (void**)&pVtx_Style, 0);

	switch (g_nChoosingBulletStyle_Style)
	{
	case BULLETSTYLE_COMET:

		//回転
		g_aBlletStyle.rot.z += g_aBlletStyle.fMoveZ;

		/*デバッグ用*/
		g_aBlletStyle.pos.x = 140.0f;
		g_aBlletStyle.pos.y = 935.0f;
		g_aBlletStyle.fMoveZ = 0.05f;
		g_aBlletStyle.fLength = sqrtf(SPAN_X_BULLET * SPAN_X_BULLET + SPAN_Y_BULLET * SPAN_Y_BULLET) * 0.5f;
		g_aBlletStyle.fAngle = atan2f(SPAN_X_BULLET, SPAN_Y_BULLET);

		//最後に弾の移動量に合わせて頂点も更新
		pVtx_Style[0].pos.x = g_aBlletStyle.pos.x + sinf(g_aBlletStyle.rot.z - (D3DX_PI - g_aBlletStyle.fAngle)) * g_aBlletStyle.fLength;
		pVtx_Style[0].pos.y = g_aBlletStyle.pos.y + cosf(g_aBlletStyle.rot.z - (D3DX_PI - g_aBlletStyle.fAngle)) * g_aBlletStyle.fLength;
		pVtx_Style[1].pos.x = g_aBlletStyle.pos.x + sinf(g_aBlletStyle.rot.z + (D3DX_PI - g_aBlletStyle.fAngle)) * g_aBlletStyle.fLength;
		pVtx_Style[1].pos.y = g_aBlletStyle.pos.y + cosf(g_aBlletStyle.rot.z + (D3DX_PI - g_aBlletStyle.fAngle)) * g_aBlletStyle.fLength;
		pVtx_Style[2].pos.x = g_aBlletStyle.pos.x + sinf(g_aBlletStyle.rot.z - g_aBlletStyle.fAngle) * g_aBlletStyle.fLength;
		pVtx_Style[2].pos.y = g_aBlletStyle.pos.y + cosf(g_aBlletStyle.rot.z - g_aBlletStyle.fAngle) * g_aBlletStyle.fLength;
		pVtx_Style[3].pos.x = g_aBlletStyle.pos.x + sinf(g_aBlletStyle.rot.z + g_aBlletStyle.fAngle) * g_aBlletStyle.fLength;
		pVtx_Style[3].pos.y = g_aBlletStyle.pos.y + cosf(g_aBlletStyle.rot.z + g_aBlletStyle.fAngle) * g_aBlletStyle.fLength;

		//テクスチャを上手いこと調整
		pVtx_Style[0].tex = D3DXVECTOR2(0.0f + g_aBlletStyle.fTexX, 0.0f + g_aBlletStyle.fTexY);
		pVtx_Style[1].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET + g_aBlletStyle.fTexX, 0.0f + g_aBlletStyle.fTexY);
		pVtx_Style[2].tex = D3DXVECTOR2(0.0f + g_aBlletStyle.fTexX, PER_ONE_TEX_Y_COMET_BULLET + g_aBlletStyle.fTexY);
		pVtx_Style[3].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET + g_aBlletStyle.fTexX, PER_ONE_TEX_Y_COMET_BULLET + g_aBlletStyle.fTexY);

		//テクスチャ変化遅延
		g_aBlletStyle.nPattern++;

		//テクスチャが変化
		if (g_aBlletStyle.nPattern > CHEANGE_SPD_TEX_COMET_BULLET)
		{
			g_aBlletStyle.fTexX += PER_ONE_TEX_X_COMET_BULLET;

			if (g_aBlletStyle.fTexX >= 1.0f)
			{
				g_aBlletStyle.fTexX = 0.0f;

				g_aBlletStyle.fTexY += PER_ONE_TEX_Y_COMET_BULLET;

				if (g_aBlletStyle.fTexY >= 1.0f)
				{
					g_aBlletStyle.fTexY = 0.0f;
				}
			}

			g_aBlletStyle.nPattern = 0;
		}

		break;

	case BULLETSTYLE_REUNION:

		break;

	case BULLETSTYLE_KING:

		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Style->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Style(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Style, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	switch (g_nChoosingBulletStyle_Style)
	{
	case BULLETSTYLE_COMET:

		pDevice->SetTexture(0, g_pTexture_Style[0]);

		break;

	case BULLETSTYLE_REUNION:

		pDevice->SetTexture(0, g_pTexture_Style[1]);

		break;

	case BULLETSTYLE_KING:

		pDevice->SetTexture(0, g_pTexture_Style[2]);

		break;
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}