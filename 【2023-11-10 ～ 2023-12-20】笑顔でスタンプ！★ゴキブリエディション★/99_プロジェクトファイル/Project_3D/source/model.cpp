//************************************************
//
//モデル[model.cpp]
//Author：福田歩希
//
//************************************************
#include "model.h"

#include "debugproc.h"

#include "collision.h"
#include "player.h"
#include "visible_rect.h"

//マクロ定義
#define AMOUNT_MODEL	(4)	//モデル数

//グローバル変数
LPD3DXMESH g_pMeshModel = NULL;	//メッシュ…頂点情報のポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;	//マテリアルへのポインタ
DWORD g_dwNumMatModel = 0;	//マテリアルの数
Model g_aModel[AMOUNT_MODEL];	//モデル情報

//************************************************
//モデル初期
//************************************************
void InitModel(int mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	g_dwNumMatModel = 0;	//マテリアルの数をクリア

	//どうしよう
	if (mode != MODE_TUTORIAL)
	{
		g_aModel[0].pos = D3DXVECTOR3(150.0f, 0.0f, 150.0f);
		g_aModel[1].pos = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
		g_aModel[2].pos = D3DXVECTOR3(150.0f, 0.0f, -150.0f);
		g_aModel[3].pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	}
	else
	{
		g_aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
		g_aModel[1].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
		g_aModel[2].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
		g_aModel[3].pos = D3DXVECTOR3(0.0f, 0.0f, 150.0f);
	}

	//モデルの初期
	for (int i = 0; i < AMOUNT_MODEL; i++)
	{
		g_aModel[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[i].aabb = {};
	}

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\model\\roach_home.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	UpdateModelAABB();
	for (int i = 0; i < AMOUNT_MODEL; i++)
	{
		//SetSizeVisible_Rect(g_aModel[i].aabb, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), &g_aModel[i].pos);
	}
}

//************************************************
//モデル破棄
//************************************************
void UninitModel(void)
{
	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//************************************************
//モデル更新
//************************************************
void UpdateModel(void)
{

}

//************************************************
//モデルAABB更新
//************************************************
void UpdateModelAABB(void)
{
	for (int i = 0; i < AMOUNT_MODEL; i++)
	{
		g_aModel[i].aabb.min =
		{
			g_aModel[i].pos.x - 15.0f,
			g_aModel[i].pos.y,
			g_aModel[i].pos.z - 15.0f
		};

		g_aModel[i].aabb.max =
		{
			g_aModel[i].pos.x + 15.0f,
			g_aModel[i].pos.y + 5.0f,
			g_aModel[i].pos.z + 15.0f
		};
	}
}

//************************************************
//モデルの当たり判定
//************************************************
void CollisionModel(void)
{
	int HitIdx = -1;

	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < AMOUNT_MODEL; i++)
	{
		if (CollisionAABB(pPlayer->aabb, g_aModel[i].aabb))
		{
			HitIdx = i;

			PrintDebugProc("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

			/* さらに、どの辺が当たっているのか判定 */
			int Type = CollisionAABB_Vtx(pPlayer->aabb, g_aModel[HitIdx].aabb);

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
				//pPlayer->pos = pPlayer->posOld;
				pPlayer->move =
				{
					-sinf(atan2f(pPlayer->move.x, pPlayer->move.z)),
					0.0f,
					-cosf(atan2f(pPlayer->move.x, pPlayer->move.z))
				};
			}
		}
	}
}

//************************************************
//モデル描画
//************************************************
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	D3DMATERIAL9 matDef;	//現在のマテリアル保存用

	D3DXMATERIAL* pMat;	//マテリアルデータへのポインタ

	for (int i = 0; i < AMOUNT_MODEL; i++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aModel[i].mtxWorld);

		//向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_aModel[i].rot.y,
			g_aModel[i].rot.x,
			g_aModel[i].rot.z);

		//向きを反映2
		D3DXMatrixMultiply(&g_aModel[i].mtxWorld,
			&g_aModel[i].mtxWorld,
			&mtxRot);

		//位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aModel[i].pos.x,
			g_aModel[i].pos.y,
			g_aModel[i].pos.z);

		//位置を反映2
		D3DXMatrixMultiply(&g_aModel[i].mtxWorld,
			&g_aModel[i].mtxWorld,
			&mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aModel[i].mtxWorld);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//モデルパーツの描画
			g_pMeshModel->DrawSubset(nCntMat);
		}

		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

Model* GetInfoModel(void)
{
	return &g_aModel[0];
}