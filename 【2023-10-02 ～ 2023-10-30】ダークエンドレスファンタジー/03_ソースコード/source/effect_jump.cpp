//************************************************
//
//ジャンプエフェクト処理[effect_jump.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "effect_jump.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Effect_Jump = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Effect_Jump = NULL;	//頂点バッファのポインタ
EFFECT_JUMP g_aEffect_Jump;	//ジャンプエフェクト構造体

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Effect_Jump()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_EFFECT_JUMP,
		&g_pTexture_Effect_Jump);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Effect_Jump,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Jump;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Jump->Lock(0, 0, (void**)&pVtx_Effect_Jump, 0);

	//頂点座標の初期設定
	pVtx_Effect_Jump[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Effect_Jump[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Effect_Jump[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Effect_Jump[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Effect_Jump[0].rhw = 1.0f;
	pVtx_Effect_Jump[1].rhw = 1.0f;
	pVtx_Effect_Jump[2].rhw = 1.0f;
	pVtx_Effect_Jump[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Effect_Jump[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Effect_Jump[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Effect_Jump[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Effect_Jump[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Effect_Jump[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Effect_Jump[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Effect_Jump[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Effect_Jump[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Jump->Unlock();

	//ジャンプエフェクト構造体の情報の初期化群
	g_aEffect_Jump.bUse = false;
	g_aEffect_Jump.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEffect_Jump.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEffect_Jump.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEffect_Jump.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aEffect_Jump.fRadius[nCnt] = 0.0f;
	}
	g_aEffect_Jump.fLength = 0.0f;
	g_aEffect_Jump.fAngle = 0.0f;
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Effect_Jump(void)
{
	//テクスチャの破棄
	if (g_pTexture_Effect_Jump != NULL)
	{
		g_pTexture_Effect_Jump->Release();
		g_pTexture_Effect_Jump = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Effect_Jump != NULL)
	{
		g_pVtxBuff_Effect_Jump->Release();
		g_pVtxBuff_Effect_Jump = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Effect_Jump(void)
{
	//位置更新
	Update_Pos_Effect_Jump();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Effect_Jump(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Effect_Jump, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Effect_Jump);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//ジャンプエフェクト構造体の情報を設定する関数
//************************************************
void SetInfo_Effect_Jump(D3DXVECTOR3 pos)
{
	g_aEffect_Jump.pos = pos;
	g_aEffect_Jump.move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_aEffect_Jump.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aEffect_Jump.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			g_aEffect_Jump.fRadius[nCnt] = RADIUS_EFFECT_JUMP_X;
			break;
		case 1:
			g_aEffect_Jump.fRadius[nCnt] = RADIUS_EFFECT_JUMP_Y;
			break;
		}
	}
	g_aEffect_Jump.fLength = sqrtf((g_aEffect_Jump.fRadius[0] * g_aEffect_Jump.fRadius[0]) + ((g_aEffect_Jump.fRadius[1]) * (g_aEffect_Jump.fRadius[1])));
	g_aEffect_Jump.fAngle = atan2f(g_aEffect_Jump.fRadius[0] * 2.0f, g_aEffect_Jump.fRadius[1] * 2.0f);
}

//************************************************
//ジャンプエフェクトの位置を設定する関数
//************************************************
void Update_Pos_Effect_Jump(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Jump;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Jump->Lock(0, 0, (void**)&pVtx_Effect_Jump, 0);

	//移動
	g_aEffect_Jump.pos += g_aEffect_Jump.move;

	//縮小
	g_aEffect_Jump.fLength += -3.0f;

	/*後で直せ*/
	pVtx_Effect_Jump[0].pos.x = g_aEffect_Jump.pos.x + sinf(g_aEffect_Jump.rot.z - (D3DX_PI - g_aEffect_Jump.fAngle)) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[0].pos.y = g_aEffect_Jump.pos.y + cosf(g_aEffect_Jump.rot.z - (D3DX_PI - g_aEffect_Jump.fAngle)) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[1].pos.x = g_aEffect_Jump.pos.x + sinf(g_aEffect_Jump.rot.z + (D3DX_PI - g_aEffect_Jump.fAngle)) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[1].pos.y = g_aEffect_Jump.pos.y + cosf(g_aEffect_Jump.rot.z + (D3DX_PI - g_aEffect_Jump.fAngle)) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[2].pos.x = g_aEffect_Jump.pos.x + sinf(g_aEffect_Jump.rot.z - g_aEffect_Jump.fAngle) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[2].pos.y = g_aEffect_Jump.pos.y + cosf(g_aEffect_Jump.rot.z - g_aEffect_Jump.fAngle) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[3].pos.x = g_aEffect_Jump.pos.x + sinf(g_aEffect_Jump.rot.z + g_aEffect_Jump.fAngle) * g_aEffect_Jump.fLength;
	pVtx_Effect_Jump[3].pos.y = g_aEffect_Jump.pos.y + cosf(g_aEffect_Jump.rot.z + g_aEffect_Jump.fAngle) * g_aEffect_Jump.fLength;

	//色変更
	g_aEffect_Jump.col.a -= 0.1f;

	pVtx_Effect_Jump[0].col = g_aEffect_Jump.col;
	pVtx_Effect_Jump[1].col = g_aEffect_Jump.col;
	pVtx_Effect_Jump[2].col = g_aEffect_Jump.col;
	pVtx_Effect_Jump[3].col = g_aEffect_Jump.col;

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Jump->Unlock();
}

//************************************************
//ジャンプエフェクト構造体のアドレスを渡す
//************************************************
EFFECT_JUMP* Getinfo_Effect_Jump(void)
{
	return &g_aEffect_Jump;
}