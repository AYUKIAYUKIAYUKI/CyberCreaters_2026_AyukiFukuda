//===============================================================================
//
//  3Dゲーム基礎(EffectSand.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "effect_sand.h"
#include "stdlib.h"
#include "debugproc.h"
#include "input.h"
#include <time.h>

//マクロ定義
//マクロ定義
#define MAX_EFFECT_SAND	(1024)
#define EFFECT_SAND_COOLTIME	(7)
#define NUM_EffectSand	(6)
#define MAX_EFFECT_EMUTTER	(3)

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float nSize;
	float fLength;
	float fAngle;
	int nType;
	bool bUse;
	int nAlpha;
}EffectSand;

//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureEffectSand[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffectSand = NULL;
D3DXMATRIX g_mtxWorldEffectSand;
EffectSand g_EffectSand[MAX_EFFECT_SAND];

int effectfrag[MAX_EFFECT_EMUTTER];
//======================================
//砂エフェクトの初期化処理
//======================================
void InitEffectSand(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT_SAND,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffectSand,
		NULL);
	//テクスチャの読み込み
	VERTEX_3D* pVtx;	//頂点情報のポインタ
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\s_effect.png",	
		&g_apTextureEffectSand[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\s_effect_a.png",
		&g_apTextureEffectSand[1]);
	for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
	{
		g_EffectSand[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EffectSand[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EffectSand[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_EffectSand[nCnt].nSize = 50;
		g_EffectSand[nCnt].fLength = sqrtf(g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize + g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize) / 2.0f;
		g_EffectSand[nCnt].fAngle = atan2f(g_EffectSand[nCnt].nSize, g_EffectSand[nCnt].nSize);
		g_EffectSand[nCnt].nType = 0;
		g_EffectSand[nCnt].bUse = false;
		g_EffectSand[nCnt].nAlpha = 255;

	}

	g_pVtxBuffEffectSand->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
	{


		//頂点座標の設定
		pVtx[0].pos.x = sinf(g_EffectSand[nCnt].rot.z - (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
		pVtx[0].pos.z = cosf(g_EffectSand[nCnt].rot.z - (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
		pVtx[0].pos.y = 50.0f;
		pVtx[1].pos.x = sinf(g_EffectSand[nCnt].rot.z + (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
		pVtx[1].pos.z = cosf(g_EffectSand[nCnt].rot.z + (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
		pVtx[1].pos.y = 50.0f;
		pVtx[2].pos.x = sinf(g_EffectSand[nCnt].rot.z - g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
		pVtx[2].pos.z = cosf(g_EffectSand[nCnt].rot.z - g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
		pVtx[2].pos.y = -50.0f;
		pVtx[3].pos.x = sinf(g_EffectSand[nCnt].rot.z + g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
		pVtx[3].pos.z = cosf(g_EffectSand[nCnt].rot.z + g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
		pVtx[3].pos.y = -50.0f;

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffEffectSand->Unlock();

	for (int i = 0; i < MAX_EFFECT_EMUTTER; i++)
	{
		effectfrag[i] = 0;
	}
}

//======================================
//砂エフェクトの終了処理
//======================================

void UninitEffectSand(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//テクスチャの破棄
		if (g_apTextureEffectSand[nCnt] != NULL)
		{
			g_apTextureEffectSand[nCnt]->Release();
			g_apTextureEffectSand[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEffectSand != NULL)
	{
		g_pVtxBuffEffectSand->Release();
		g_pVtxBuffEffectSand = NULL;
	}
}
//======================================
//砂エフェクトの更新処理
//======================================

void UpdateEffectSand(void)
{

	VERTEX_3D* pVtx;	//頂点情報のポインタ
	g_pVtxBuffEffectSand->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
	{
		if (g_EffectSand[nCnt].bUse == true)
		{
			g_EffectSand[nCnt].nSize -= 0.6f;

			g_EffectSand[nCnt].fLength = sqrtf(g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize + g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize) / 2.0f;
			g_EffectSand[nCnt].fAngle = atan2f(g_EffectSand[nCnt].nSize, g_EffectSand[nCnt].nSize);
			g_EffectSand[nCnt].nAlpha -= 5;
			//頂点座標の設定
			pVtx[0].pos.x = sinf(g_EffectSand[nCnt].rot.z - (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
			pVtx[0].pos.y = -cosf(g_EffectSand[nCnt].rot.z - (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
			pVtx[0].pos.z = 0;
			pVtx[1].pos.x = sinf(g_EffectSand[nCnt].rot.z + (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
			pVtx[1].pos.y = -cosf(g_EffectSand[nCnt].rot.z + (D3DX_PI - g_EffectSand[nCnt].fAngle)) * g_EffectSand[nCnt].fLength;
			pVtx[1].pos.z = -0;
			pVtx[2].pos.x = sinf(g_EffectSand[nCnt].rot.z - g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
			pVtx[2].pos.y = -cosf(g_EffectSand[nCnt].rot.z - g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
			pVtx[2].pos.z = 0;
			pVtx[3].pos.x = sinf(g_EffectSand[nCnt].rot.z + g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
			pVtx[3].pos.y = -cosf(g_EffectSand[nCnt].rot.z + g_EffectSand[nCnt].fAngle) * g_EffectSand[nCnt].fLength;
			pVtx[3].pos.z = -0;

			//頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, g_EffectSand[nCnt].nAlpha);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, g_EffectSand[nCnt].nAlpha);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, g_EffectSand[nCnt].nAlpha);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, g_EffectSand[nCnt].nAlpha);

			if (g_EffectSand[nCnt].nType == 0)
			{
				g_EffectSand[nCnt].rot.z -= 0.6f;
			}
			else
			{
				g_EffectSand[nCnt].rot.z += 0.6f;
			}
			if (g_EffectSand[nCnt].nSize < 10)
			{
				g_EffectSand[nCnt].bUse = false;
			}
	

		}
		pVtx += 4;
	}
	g_pVtxBuffEffectSand->Unlock();
	int Used = 0;
	for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
	{
		if (g_EffectSand[nCnt].bUse == true)
		{
			Used++;
		}
	}
	for (int i = 0; i < MAX_EFFECT_EMUTTER; i++)
	{
		if (effectfrag[i] <= EFFECT_SAND_COOLTIME)
		{
			effectfrag[i]++;
		}
	}

	//PrintDebugProc("使用しているエフェクト数：%d / %d\n", Used, MAX_EFFECT_SAND);
}


//======================================
//砂エフェクトの描画処理
//======================================
void DrawEffectSand(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//計算用マトリックス
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxView;

	//アルファテスト設定
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//Zアルファ
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	/*---【1度で済む設定をfor文の外に移しました：福田】---*/

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffectSand, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	/*----------------------------------------------------*/

	for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
	{
		if (g_EffectSand[nCnt].bUse == true)
		{
			//ワールドマトリックス
			D3DXMatrixIdentity(&g_mtxWorldEffectSand);

			//ビューマトリックスの取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面を向ける
			D3DXMatrixInverse(&g_mtxWorldEffectSand, NULL, &mtxView);//逆行列を求める
			g_mtxWorldEffectSand._41 = 0.0f;
			g_mtxWorldEffectSand._42 = 0.0f;
			g_mtxWorldEffectSand._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans,
				g_EffectSand[nCnt].pos.x,
				g_EffectSand[nCnt].pos.y,
				g_EffectSand[nCnt].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEffectSand,
				&g_mtxWorldEffectSand,
				&mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD,
				&g_mtxWorldEffectSand);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEffectSand[g_EffectSand[nCnt].nType]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCnt * 4,
				2);
		}
	}
	//通常の合成に戻す設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Zアルファ
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}
//======================================
//砂エフェクトの設置
//======================================
void SetEffectSand(D3DXVECTOR3 pos,int nType, float nSize,int nID)
{
	VERTEX_3D* pVtx;	//頂点情報のポインタ
	g_pVtxBuffEffectSand->Lock(0, 0, (void**)&pVtx, 0);
	if (effectfrag[nID] > EFFECT_SAND_COOLTIME)
	{
		effectfrag[nID] = 0;
		for (int nCnt = 0; nCnt < MAX_EFFECT_SAND; nCnt++)
		{
			if (g_EffectSand[nCnt].bUse == false)
			{
				g_EffectSand[nCnt].bUse = true;
				g_EffectSand[nCnt].pos = pos;
				g_EffectSand[nCnt].nType = nType;
				g_EffectSand[nCnt].nSize = nSize;
				g_EffectSand[nCnt].nAlpha = 255;

				g_EffectSand[nCnt].fLength = sqrtf(g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize + g_EffectSand[nCnt].nSize * g_EffectSand[nCnt].nSize) / 2.0f;
				g_EffectSand[nCnt].fAngle = atan2f(g_EffectSand[nCnt].nSize, g_EffectSand[nCnt].nSize);

				break;
			}
			pVtx += 4;

		}
	}

	g_pVtxBuffEffectSand->Unlock();

}
