//************************************************
//
//壁生成[wall.cpp]
//Author：福田歩希
//
//************************************************
#include "wall.h"

#include "debugproc.h"

#include "bullet.h"
#include "player.h"
#include "visible_rect.h"

//マクロ定義
#define	AMOUNT_WALL	(4)	//壁の数
#define SPAN_WALL	(100.0f)	//壁のサイズ

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall;	//テクスチャへのポインタ
Wall g_aWall[AMOUNT_WALL];	//壁情報

//************************************************
//壁初期
//************************************************
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//グローバル変数の初期設定
	g_pVtxBuffWall = NULL;
	g_pTextureWall = NULL;

	/* ReadInfoの変わり */
	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		switch (i)
		{
		case 0:
			g_aWall[i].pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
			break;
		case 1:
			g_aWall[i].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
			break;
		case 2:
			g_aWall[i].pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
			break;
		case 3:
			g_aWall[i].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
			break;
		}
	
		g_aWall[i].rot = D3DXVECTOR3(0.0f, 0.0f + ((D3DX_PI * 0.5f) * i), 0.0f);
	
		g_aWall[i].aabb.min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[i].aabb.max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}


	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\KabeTex.bmp",
		&g_pTextureWall);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		//頂点座標の設定
		/* テスト用 */
		pVtx[0].pos = D3DXVECTOR3(-SPAN_WALL, SPAN_WALL * 0.5f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_WALL, SPAN_WALL * 0.5f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_WALL, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_WALL, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//頂点バッファをアンロック
	g_pVtxBuffWall->Unlock();

	//当たり判定を可視化
	UpdateWallAABB();
	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		//SetSizeVisible_Rect(g_aWall[i].aabb, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), &g_aWall[i].pos);
	}
}

//************************************************
//壁破棄
//************************************************
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//************************************************
//壁更新
//************************************************
void UpdateWall(void)
{
	g_aWall[0].pos.x += 0.1f;

	//壁AABB更新
	UpdateWallAABB();
}

//************************************************
//壁AABB更新
//************************************************
void UpdateWallAABB(void)
{
	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		g_aWall[i].aabb.min =
		{
			g_aWall[i].pos.x - (SPAN_WALL * fabsf(cosf(g_aWall[i].rot.y))),
			g_aWall[i].pos.y,
			g_aWall[i].pos.z - (SPAN_WALL * fabsf(sinf(g_aWall[i].rot.y)))
		};

		g_aWall[i].aabb.max =
		{
			g_aWall[i].pos.x + (SPAN_WALL * fabsf(cosf(g_aWall[i].rot.y))),
			g_aWall[i].pos.y + SPAN_WALL * 0.5f,
			g_aWall[i].pos.z + (SPAN_WALL * fabsf(sinf(g_aWall[i].rot.y)))
		};

		//PrintDebugProc("壁[%d]のAABB：( %f ~ %f, %f ~ %f, %f ~ %f, )\n", i, g_aWall[i].aabb.min.x, g_aWall[i].aabb.max.x, g_aWall[i].aabb.min.y, g_aWall[i].aabb.max.y, g_aWall[i].aabb.min.z, g_aWall[i].aabb.max.z);
	}
}

//************************************************
//壁の当たり判定
//************************************************
void CollisionWall(void)
{
	int HitIdx = -1;

	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		PrintDebugProc("%d番目の方向：[%f]\n", i, atan2f(g_aWall[i].pos.x - pPlayer->pos.x, g_aWall[i].pos.z - pPlayer->pos.z));

		if (CollisionAABB(pPlayer->aabb, g_aWall[i].aabb))
		{
			HitIdx = i;

			PrintDebugProc("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

			/* さらに、どの辺が当たっているのか判定 */
			int Type = CollisionAABB_Vtx(pPlayer->aabb, g_aWall[HitIdx].aabb);

			if (Type == Xside)
			{
				pPlayer->pos.x = pPlayer->posOld.x;
				pPlayer->move.x = 0.0f;
			}
			else if (Type == Zside)
			{
				pPlayer->pos.z = pPlayer->posOld.z;
				pPlayer->move.z = 0.0f;
			}
			else if (Type == OnlyVtx)
			{
				bool Xside = false;

				if (atan2f(g_aWall[HitIdx].pos.x - pPlayer->pos.x, g_aWall[HitIdx].pos.z - pPlayer->pos.z) < -0.7853975f &&
					atan2f(g_aWall[HitIdx].pos.x - pPlayer->pos.x, g_aWall[HitIdx].pos.z - pPlayer->pos.z) > -2.3561925f)
				{
					pPlayer->pos.x = pPlayer->posOld.x;
					pPlayer->move.x = 0.0f;

					Xside = true;
				}

				//if (atan2f(g_aWall[HitIdx].pos.x - pPlayer->pos.x, g_aWall[HitIdx].pos.z - pPlayer->pos.z) > 0.7853975f &&
				//	atan2f(g_aWall[HitIdx].pos.x - pPlayer->pos.x, g_aWall[HitIdx].pos.z - pPlayer->pos.z) < 2.3561925f)
				//{
				//	pPlayer->pos.x = pPlayer->posOld.x;
				//	pPlayer->move.x = 0.0f;
				//
				//	Xside = true;
				//}

				if (!Xside)
				{
					pPlayer->pos.z = pPlayer->posOld.z;
					pPlayer->move.z = 0.0f;
				}
			}
		}
	}
}

//************************************************
//壁描画
//************************************************
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int i = 0; i < AMOUNT_WALL; i++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aWall[i].mtxWorld);

		//向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aWall[i].rot.y,
			g_aWall[i].rot.x,
			g_aWall[i].rot.z);

		//向きを反映2
		D3DXMatrixMultiply(&g_aWall[i].mtxWorld,
			&g_aWall[i].mtxWorld,
			&mtxRot);

		//位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aWall[i].pos.x,
			g_aWall[i].pos.y,
			g_aWall[i].pos.z);

		//位置を反映2
		D3DXMatrixMultiply(&g_aWall[i].mtxWorld,
			&g_aWall[i].mtxWorld,
			&mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[i].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureWall);

		//壁の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}