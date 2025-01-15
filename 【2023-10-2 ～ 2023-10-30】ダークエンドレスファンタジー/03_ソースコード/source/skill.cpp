//************************************************
//
//スキル処理[skill.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "bomb.h"
#include "skill.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Skill[AMOUNT_TEX_SKILL] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Skill = NULL;	//頂点バッファのポインタ
SKILL g_aSkill[AMOUNT_POLYGON_SKILL];	//スキル情報

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Skill()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SKILL,
		&g_pTexture_Skill[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_SKILL_CHARGE,
		&g_pTexture_Skill[1]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_SKILL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Skill,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Skill;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Skill->Lock(0, 0, (void**)&pVtx_Skill, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Skill[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Skill[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Skill[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Skill[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Skill[0].rhw = 1.0f;
		pVtx_Skill[1].rhw = 1.0f;
		pVtx_Skill[2].rhw = 1.0f;
		pVtx_Skill[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Skill[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Skill[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Skill[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Skill[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (nCnt == 1)
		{
			pVtx_Skill[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			pVtx_Skill[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			pVtx_Skill[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
			pVtx_Skill[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		}

		//テクスチャ座標の初期設定
		pVtx_Skill[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Skill[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Skill[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Skill[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Skill += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Skill->Unlock();

	//スキル構造体の情報の初期化群
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		g_aSkill[nCnt].nStyle = 0;
		g_aSkill[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkill[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkill[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aSkill[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aSkill[nCnt].nCntTex = 0;
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aSkill[nCnt].fTexSpan[nCnt2] = 0.0f;
			g_aSkill[nCnt].fRadius[nCnt2] = 0.0f;
			g_aSkill[nCnt].fLength[nCnt2] = 0.0f;
			g_aSkill[nCnt].fAngle[nCnt2] = 0.0f;
		}
	}

	//スキル構造体に情報を付与
	SetInfo_Skill();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Skill(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEX_SKILL; nCnt++)
	{
		if (g_pTexture_Skill[nCnt] != NULL)
		{
			g_pTexture_Skill[nCnt]->Release();
			g_pTexture_Skill[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Skill != NULL)
	{
		g_pVtxBuff_Skill->Release();
		g_pVtxBuff_Skill = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Skill(void)
{
	//移動など
	Update_Pos_Skill();

	//テクスチャアニメーション
	//Update_Tex_Skill();

	//カラー変更
	//Update_Col_Skill();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Skill(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Skill, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexture_Skill[nCnt]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//スキル構造体の情報を設定する関数
//************************************************
void SetInfo_Skill(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		g_aSkill[nCnt].nStyle = nCnt;
		g_aSkill[nCnt].pos = D3DXVECTOR3(1200.0, 100.0f, 0.0f);
		g_aSkill[nCnt].fRadius[0] = 60.0f;	//スキル横半幅
		g_aSkill[nCnt].fRadius[1] = 60.0f;	//スキル縦半幅
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aSkill[nCnt].fLength[nCnt2] = sqrtf((g_aSkill[nCnt].fRadius[0] * g_aSkill[nCnt].fRadius[0]) + (g_aSkill[nCnt].fRadius[1] * g_aSkill[nCnt].fRadius[1]));
			g_aSkill[nCnt].fAngle[nCnt2] = atan2f(g_aSkill[nCnt].fRadius[0] * 2.0f, g_aSkill[nCnt].fRadius[1] * 2.0f);
		}
	}
}

//************************************************
//スキルの位置を設定する関数
//************************************************
void Update_Pos_Skill(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Skill;

	BOMB* pBomb = GetInfo_Bomb();
	int* pII = GetInfo_Bomb_aa();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Skill->Lock(0, 0, (void**)&pVtx_Skill, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			pVtx_Skill[0].pos.x = g_aSkill[nCnt].pos.x + sinf(g_aSkill[nCnt].rot.z - (D3DX_PI - g_aSkill[nCnt].fAngle[0])) * g_aSkill[nCnt].fLength[0];
			pVtx_Skill[0].pos.y = g_aSkill[nCnt].pos.y + cosf(g_aSkill[nCnt].rot.z - (D3DX_PI - g_aSkill[nCnt].fAngle[0])) * g_aSkill[nCnt].fLength[0];
			pVtx_Skill[1].pos.x = g_aSkill[nCnt].pos.x + sinf(g_aSkill[nCnt].rot.z + (D3DX_PI - g_aSkill[nCnt].fAngle[0])) * g_aSkill[nCnt].fLength[0];
			pVtx_Skill[1].pos.y = g_aSkill[nCnt].pos.y + cosf(g_aSkill[nCnt].rot.z + (D3DX_PI - g_aSkill[nCnt].fAngle[0])) * g_aSkill[nCnt].fLength[0];
			pVtx_Skill[2].pos.x = g_aSkill[nCnt].pos.x + sinf(g_aSkill[nCnt].rot.z - g_aSkill[nCnt].fAngle[1]) * g_aSkill[nCnt].fLength[1];
			pVtx_Skill[2].pos.y = g_aSkill[nCnt].pos.y + cosf(g_aSkill[nCnt].rot.z - g_aSkill[nCnt].fAngle[1]) * g_aSkill[nCnt].fLength[1];
			pVtx_Skill[3].pos.x = g_aSkill[nCnt].pos.x + sinf(g_aSkill[nCnt].rot.z + g_aSkill[nCnt].fAngle[1]) * g_aSkill[nCnt].fLength[1];
			pVtx_Skill[3].pos.y = g_aSkill[nCnt].pos.y + cosf(g_aSkill[nCnt].rot.z + g_aSkill[nCnt].fAngle[1]) * g_aSkill[nCnt].fLength[1];
			break;
		case 1:

			if (pBomb[0].bUse || *pII > 0)
			{
				pVtx_Skill[0].pos.x = g_aSkill[nCnt].pos.x - 52.0f;
				pVtx_Skill[0].pos.y = g_aSkill[nCnt].pos.y - 52.0f;
				pVtx_Skill[1].pos.x = g_aSkill[nCnt].pos.x + 52.0f;
				pVtx_Skill[1].pos.y = g_aSkill[nCnt].pos.y - 52.0f;
				pVtx_Skill[2].pos.x = g_aSkill[nCnt].pos.x - 52.0f;
				pVtx_Skill[2].pos.y = g_aSkill[nCnt].pos.y + 52.0f;
				pVtx_Skill[3].pos.x = g_aSkill[nCnt].pos.x + 52.0f;
				pVtx_Skill[3].pos.y = g_aSkill[nCnt].pos.y + 52.0f;
			}
			else
			{
				pVtx_Skill[0].pos.x = g_aSkill[nCnt].pos.x - 0.0f;
				pVtx_Skill[0].pos.y = g_aSkill[nCnt].pos.y - 0.0f;
				pVtx_Skill[1].pos.x = g_aSkill[nCnt].pos.x + 0.0f;
				pVtx_Skill[1].pos.y = g_aSkill[nCnt].pos.y - 0.0f;
				pVtx_Skill[2].pos.x = g_aSkill[nCnt].pos.x - 0.0f;
				pVtx_Skill[2].pos.y = g_aSkill[nCnt].pos.y + 0.0f;
				pVtx_Skill[3].pos.x = g_aSkill[nCnt].pos.x + 0.0f;
				pVtx_Skill[3].pos.y = g_aSkill[nCnt].pos.y + 0.0f;
			}

			break;
		}

		pVtx_Skill += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Skill->Unlock();
}

//************************************************
//ゲージの色を変更する関数
//************************************************
void Update_Col_Skill(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Skill;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Skill->Lock(0, 0, (void**)&pVtx_Skill, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
	{
		pVtx_Skill[0].col = g_aSkill[nCnt].col;
		pVtx_Skill[1].col = g_aSkill[nCnt].col;
		pVtx_Skill[2].col = g_aSkill[nCnt].col;
		pVtx_Skill[3].col = g_aSkill[nCnt].col;

		pVtx_Skill += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Skill->Unlock();
}

////************************************************
////スキルのテクスチャを動かす関数
////************************************************
//void Update_Tex_Skill(void)
//{
//	//頂点情報へのポインタ
//	VERTEX_2D* pVtx_Skill;
//
//	PLAYER* pPlayer = GetInfo_Player();
//
//	//頂点バッファをロックして頂点情報のポインタを取得
//	g_pVtxBuff_Skill->Lock(0, 0, (void**)&pVtx_Skill, 0);
//
//	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_SKILL; nCnt++)
//	{
//		if (g_aSkill[nCnt].nStyle == SKILL_STYLE_GAGE)
//		{
//			g_aSkill[nCnt].fTexSpan[0] = 1.0f - (SPAN_CHANGE_TEX_SKILL * (pPlayer->nLife + 1));
//			g_aSkill[nCnt].fTexSpan[1] = 1.0f - (SPAN_CHANGE_TEX_SKILL * pPlayer->nLife);
//		}
//
//		pVtx_Skill[0].tex = D3DXVECTOR2(0.0f, g_aSkill[nCnt].fTexSpan[0]);
//		pVtx_Skill[1].tex = D3DXVECTOR2(1.0f, g_aSkill[nCnt].fTexSpan[0]);
//		pVtx_Skill[2].tex = D3DXVECTOR2(0.0f, g_aSkill[nCnt].fTexSpan[1]);
//		pVtx_Skill[3].tex = D3DXVECTOR2(1.0f, g_aSkill[nCnt].fTexSpan[1]);
//
//		pVtx_Skill += AMOUNT_VTX;
//	}
//
//	//頂点バッファをアンロックする
//	g_pVtxBuff_Skill->Unlock();
//}

//************************************************
//スキル構造体のアドレスを渡す
//************************************************
SKILL* GetInfo_Skill(void)
{
	return &g_aSkill[0];
}