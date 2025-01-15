//************************************************
//
//スポーンエフェクト処理[effect_spawn.cpp]
//Author：福田歩希
//
//************************************************
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "effect_spawn.h"
#include "enemy.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Effect_Spawn = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Effect_Spawn = NULL;	//頂点バッファのポインタ
SPAWN_EFFECT g_aEffect_Spwan[AMOUNT_POLYGON_EFFECT_SPAWN];	//スポーンエフェクト情報格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Effect_Spawn(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_GENERATOR_EFFECT_SPAWN,
		&g_pTexture_Effect_Spawn);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_EFFECT_SPAWN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Effect_Spawn,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Spawn;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Spawn->Lock(0, 0, (void**)&pVtx_Effect_Spawn, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_SPAWN; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Effect_Spawn[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Spawn[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Spawn[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Effect_Spawn[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Effect_Spawn[0].rhw = 1.0f;
		pVtx_Effect_Spawn[1].rhw = 1.0f;
		pVtx_Effect_Spawn[2].rhw = 1.0f;
		pVtx_Effect_Spawn[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Effect_Spawn[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Spawn[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Spawn[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Effect_Spawn[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Effect_Spawn[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Effect_Spawn[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Effect_Spawn[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Effect_Spawn[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Effect_Spawn += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Spawn->Unlock();

	//スポーンエフェクト情報初期設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_SPAWN; nCnt++)
	{
		g_aEffect_Spwan[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置初期化
		g_aEffect_Spwan[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量初期化
		g_aEffect_Spwan[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き初期化
		g_aEffect_Spwan[nCnt].bUse = false;							//使用判定を無くす
		g_aEffect_Spwan[nCnt].fLength = 0.0f;						//対角線情報を初期化
		g_aEffect_Spwan[nCnt].fAngle = 0.0f;						//角度情報を初期化
		g_aEffect_Spwan[nCnt].nColorA = 0;							//透明度初期化
	}
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Effect_Spawn(void)
{
	//テクスチャの破棄
	if (g_pTexture_Effect_Spawn != NULL)
	{
		g_pTexture_Effect_Spawn->Release();
		g_pTexture_Effect_Spawn = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Effect_Spawn != NULL)
	{
		g_pVtxBuff_Effect_Spawn->Release();
		g_pVtxBuff_Effect_Spawn = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Effect_Spawn(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Spawn;

	//敵(もや)情報へのポインタ
	ENEMY* pEnemy;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Spawn->Lock(0, 0, (void**)&pVtx_Effect_Spawn, 0);

	//敵情報を取得
	pEnemy = Getinfo_Enemy();

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_SPAWN; nCnt++)
	{
		//その使用判定がある時
		if (g_aEffect_Spwan[nCnt].bUse)
		{
			//移動
			g_aEffect_Spwan[nCnt].pos += g_aEffect_Spwan[nCnt].move;

			//回転
			g_aEffect_Spwan[nCnt].rot += D3DXVECTOR3(0.0f, 0.0f, ROTATE_SPD_EFFECT_SPAWN);

			pVtx_Effect_Spawn[0].pos.x = g_aEffect_Spwan[nCnt].pos.x + sinf(g_aEffect_Spwan[nCnt].rot.z - (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[0].pos.y = g_aEffect_Spwan[nCnt].pos.y + cosf(g_aEffect_Spwan[nCnt].rot.z - (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[1].pos.x = g_aEffect_Spwan[nCnt].pos.x + sinf(g_aEffect_Spwan[nCnt].rot.z + (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[1].pos.y = g_aEffect_Spwan[nCnt].pos.y + cosf(g_aEffect_Spwan[nCnt].rot.z + (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[2].pos.x = g_aEffect_Spwan[nCnt].pos.x + sinf(g_aEffect_Spwan[nCnt].rot.z - g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[2].pos.y = g_aEffect_Spwan[nCnt].pos.y + cosf(g_aEffect_Spwan[nCnt].rot.z - g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[3].pos.x = g_aEffect_Spwan[nCnt].pos.x + sinf(g_aEffect_Spwan[nCnt].rot.z + g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[3].pos.y = g_aEffect_Spwan[nCnt].pos.y + cosf(g_aEffect_Spwan[nCnt].rot.z + g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
		
			//カラーリング
			if (!pEnemy[nCnt].bFinishEffect)
			{
				//広がる
				g_aEffect_Spwan[nCnt].fLength++;

				g_aEffect_Spwan[nCnt].nColorA += CHANGE_SPD_COLORA_EFFECT_SPAWN;

				if (g_aEffect_Spwan[nCnt].nColorA >= 255)
				{
					g_aEffect_Spwan[nCnt].nColorA = 255;

					//消え始める
					pEnemy[nCnt].bFinishEffect = true;
				}
			}
			else
			{
				//縮む
				g_aEffect_Spwan[nCnt].fLength--;

				g_aEffect_Spwan[nCnt].nColorA -= CHANGE_SPD_COLORA_EFFECT_SPAWN;

				if (g_aEffect_Spwan[nCnt].nColorA <= 0)
				{
					g_aEffect_Spwan[nCnt].nColorA = 0;

					g_aEffect_Spwan[nCnt].bUse = false;
				}
			}

			pVtx_Effect_Spawn[0].col = D3DCOLOR_RGBA(255, 255, 255, g_aEffect_Spwan[nCnt].nColorA);
			pVtx_Effect_Spawn[1].col = D3DCOLOR_RGBA(255, 255, 255, g_aEffect_Spwan[nCnt].nColorA);
			pVtx_Effect_Spawn[2].col = D3DCOLOR_RGBA(255, 255, 255, g_aEffect_Spwan[nCnt].nColorA);
			pVtx_Effect_Spawn[3].col = D3DCOLOR_RGBA(255, 255, 255, g_aEffect_Spwan[nCnt].nColorA);
		}
		//バグ防止
		else
		{
			g_aEffect_Spwan[nCnt].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

			pVtx_Effect_Spawn[0].pos = g_aEffect_Spwan[nCnt].pos;
			pVtx_Effect_Spawn[1].pos = g_aEffect_Spwan[nCnt].pos;
			pVtx_Effect_Spawn[2].pos = g_aEffect_Spwan[nCnt].pos;
			pVtx_Effect_Spawn[3].pos = g_aEffect_Spwan[nCnt].pos;
		}

		pVtx_Effect_Spawn += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Spawn->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Effect_Spawn(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Effect_Spawn, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Effect_Spawn);

	//ポリゴンの描画
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_SPAWN; nCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//頂点を展開する関数
//************************************************
void SetPos_Vtx_Effect_Spawn(int nCntEnemy, D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Effect_Spawn;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Effect_Spawn->Lock(0, 0, (void**)&pVtx_Effect_Spawn, 0);

	//使用されていない番号を検知
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_EFFECT_SPAWN; nCnt++)
	{
		//その使用判定が無い時
		if (g_aEffect_Spwan[nCntEnemy].bUse == false)
		{
			//敵の位置に
			g_aEffect_Spwan[nCntEnemy].pos = pos;

			//敵の移動量をコピー
			g_aEffect_Spwan[nCntEnemy].move = move;

			//初期の向きを設定
			g_aEffect_Spwan[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//中心をもとに頂点座標の設定
			pVtx_Effect_Spawn[0].pos.x = g_aEffect_Spwan[nCntEnemy].pos.x + sinf(g_aEffect_Spwan[nCntEnemy].rot.z - (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[0].pos.y = g_aEffect_Spwan[nCntEnemy].pos.y + cosf(g_aEffect_Spwan[nCntEnemy].rot.z - (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[1].pos.x = g_aEffect_Spwan[nCntEnemy].pos.x + sinf(g_aEffect_Spwan[nCntEnemy].rot.z + (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[1].pos.y = g_aEffect_Spwan[nCntEnemy].pos.y + cosf(g_aEffect_Spwan[nCntEnemy].rot.z + (D3DX_PI - g_aEffect_Spwan[nCnt].fAngle)) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[2].pos.x = g_aEffect_Spwan[nCntEnemy].pos.x + sinf(g_aEffect_Spwan[nCntEnemy].rot.z - g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[2].pos.y = g_aEffect_Spwan[nCntEnemy].pos.y + cosf(g_aEffect_Spwan[nCntEnemy].rot.z - g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[3].pos.x = g_aEffect_Spwan[nCntEnemy].pos.x + sinf(g_aEffect_Spwan[nCntEnemy].rot.z + g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;
			pVtx_Effect_Spawn[3].pos.y = g_aEffect_Spwan[nCntEnemy].pos.y + cosf(g_aEffect_Spwan[nCntEnemy].rot.z + g_aEffect_Spwan[nCnt].fAngle) * g_aEffect_Spwan[nCnt].fLength;

			g_aEffect_Spwan[nCntEnemy].bUse = true;	//このやつの使用判定を出す

			//対角線の長さを設定
			g_aEffect_Spwan[nCntEnemy].fLength = sqrtf(SPAN_X_EFFECT_SPAWN * SPAN_X_EFFECT_SPAWN +
				SPAN_Y_EFFECT_SPAWN * SPAN_Y_EFFECT_SPAWN) * 0.5f;

			//対角線の角度を設定
			g_aEffect_Spwan[nCntEnemy].fAngle = atan2f(SPAN_X_EFFECT_SPAWN, SPAN_Y_EFFECT_SPAWN);

			//透明度初期設定
			g_aEffect_Spwan[nCntEnemy].nColorA = 30;

			////透明度変更判定
			//pEnemy[nCntEnemy].bFinishEffect = false;

			break;
		}

		pVtx_Effect_Spawn += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Effect_Spawn->Unlock();
}

////************************************************
////エフェクト消滅開始判定を引き渡す関数
////************************************************
//bool* Getinfo_Disappear_Effect(int nCnt)
//{
//	return &g_aEffect_Spwan[nCnt].bChangeColorA;
//}