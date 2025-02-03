//************************************************
//
// アイテム[item.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "item.h"
// 中枢
#include "input.h"
// 諸処理
#include "collision.h"
#include "effect_ring.h"
#include "player.h"
#include "sound.h"
//#include "weapon.h"
// デバッグ時
#ifdef _DEBUG
#include "debugproc.h"
#include "visible_sph.h"
#include <assert.h>
#endif	// _DEBUG

/*/ グローバル変数 /*/
ItemModel g_ItemModel[AMOUNT_MODEL_ITEM];	// アイテムモデル情報のひな形
Item g_Item[AMOUNT_ITEM];					// アイテム情報

//************************************************
// アイテム初期化処理
//************************************************
void InitItem(void)
{
	ItemModel* pModel = &g_ItemModel[0];	 // アイテムモデルのひな形へのポインタ

	for (int i = 0; i < AMOUNT_MODEL_ITEM; i++, pModel++)
	{ // アイテムモデル情報のひな形のリセット

		// スタイル
		pModel->style = -1;

		// モデル
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;

		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // マテリアル
			pModel->ColMat_offset[j] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pModel->pTex[j] = NULL;
		}

		// モデル座標
		pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/*--------------------------------------------*/

	Item* pItem = &g_Item[0];	// アイテム情報へのポインタ

	for (int i = 0; i < AMOUNT_ITEM; i++, pItem++)
	{ // アイテム情報のリセット

		pItem->use = false;	// 使用フラグ
		pItem->style = -1;	// スタイル
		pItem->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// モデル
		pItem->model.pMesh = NULL;
		pItem->model.pBuffMat = NULL;
		pItem->model.NumMat = 0;

		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // マテリアル
			pItem->model.ColMat_offset[j] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pItem->model.pTex[j] = NULL;
		}

		// モデル座標
		pItem->model.pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->model.pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->model.rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->model.rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 識別番号リセット
		pItem->id_effect = -1;	
		pItem->id_sph = -1;
	}

	// アイテム用のモデル情報を取得
	ImportModelItem();

	/*********************************************/

	///*---【試験的に配置】---*/
	//for (int i = 0; i < 20; i++)
	//{
	//	int aa = 0;

	//	if (i < 5)
	//	{
	//		aa = 0;
	//	}
	//	else if (i >= 5 && i < 10)
	//	{
	//		aa = 1;
	//	}
	//	else if (i >= 10 && i < 15)
	//	{
	//		aa = 2;
	//	}
	//	else if (i >= 15)
	//	{
	//		aa = 3;
	//	}

	//	CreateItem(aa);

	//	g_Item[i].pos = {
	//		-200.0f + 100.0f * (float)i + (-500.0f * (float)aa),
	//		0.0f,
	//		200.0f + 100.0f * (float)aa
	//	};	// 位置
	//}

	/*********************************************/
}

//************************************************
// モデル情報を読み込む
//************************************************
void ImportModelItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int AmountModel = 0;		// モデルの数を格納
	int id_Model = 0;			// モデルの識別用

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\ITEM\\item_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "アイテムモデル情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// 読み込むモデル数を取得する
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &AmountModel);
		}

#ifdef _DEBUG

		// エラー
		assert(AmountModel <= AMOUNT_MODEL_ITEM && "アイテムモデル情報が最大量を越えました");

#endif	// _DEBUG

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// 読み込むモデル名を取得する
			fscanf_s(pFile, "%s %s", &FileString[0], 2, &FileString[0], 128);

			// 読み込んだ情報をひな形にのみコピーする
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ItemModel[id_Model].pBuffMat,
				NULL,
				&g_ItemModel[id_Model].NumMat,
				&g_ItemModel[id_Model].pMesh);

			id_Model++; // パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}

	// ついでにパラメータを取得
	ImportParamItem(pFile, AmountModel);

	// ファイルを閉じる
	fclose(pFile);

	// 各モデルのテクスチャ情報を取得
	ImportTexItem(AmountModel);
}

//************************************************
// アイテムのパラメータ情報の読込み
//************************************************
void ImportParamItem(FILE* pFile, int AmountModel)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int i = 0;					// 汎用整数
	int style = 0;				// スタイルを格納
	float rad = 0;				// 判定サイズを格納

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // スタイルを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &style);
		}

		if (strcmp(&FileString[0], "RAD") == 0)
		{ // 判定サイズを取得
			fscanf_s(pFile, "%s %f", &FileString[0], 2, &rad);
		}

		if (strcmp(&FileString[0], "END_PARAMSET") == 0)
		{ // 取得した情報を反映

			g_ItemModel[i].style = style;
			g_ItemModel[i].rad = rad;

			i++;	// 次の番号へ

			if (i >= AmountModel)
			{ // モデルの最大数を越えると強制終了
				break;
			}
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{
			break;	// 終了
		}
	}
}

//************************************************
// モデルテクスチャ情報を読み込む
//************************************************
void ImportTexItem(int AmountModel)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int i = 0; i < AmountModel; i++)
	{
		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_ItemModel[i].pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int j = 0; j < (int)g_ItemModel[i].NumMat; j++)
		{
			// マテリアルの色オフセット
			g_ItemModel[i].ColMat_offset[j] = pMat[j].MatD3D.Diffuse;

			// マテリアルにテクスチャが設定されていれば読込み
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_ItemModel[i].pTex[j]);
			}
			else
			{
				g_ItemModel[i].pTex[j] = NULL;
			}
		}
	};
}

//************************************************
// アイテム生成
//************************************************
void CreateItem(int style, D3DXVECTOR3 pos)
{
	for (int i = 0; i < AMOUNT_ITEM; i++)
	{
		if (g_Item[i].use)
		{ // 使用中ならコンティニュー
			continue;
		}

		g_Item[i].use = true;		// 使用フラグ
		g_Item[i].style = style;	// スタイル

		// 位置を同期
		g_Item[i].pos = pos;
		g_Item[i].pos.y = 10.0f;

		// スタイル照合
		VerifyStyleItem(i);

		// エフェクト生成
		g_Item[i].id_effect = CreateEffect_Ring(&g_Item[i].pos);

#ifdef _DEBUG

		// 判定を可視化
		g_Item[i].id_sph = CreateVisibleSph(g_Item[i].model.rad, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), &g_Item[i].pos);

#endif	// _DEBUG

		break; // 終了
	}
}

//************************************************
// スタイル番号の照合
//************************************************
void VerifyStyleItem(int id)
{
	for (int i = 0; i < AMOUNT_MODEL_ITEM; i++)
	{
		// 各アイテムのスタイル番号と各パーツのスタイル番号を照合
		if (g_ItemModel[i].style == g_Item[id].style)
		{ // スタイル番号の一致しているモデルを有効化する
			g_Item[id].model = g_ItemModel[i];
		}
	}
}

//************************************************
// アイテム破棄
//************************************************
void UninitItem(void)
{
	for (int i = 0; i < AMOUNT_MODEL_ITEM; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_ItemModel[i].pTex[j] != NULL)
			{ // テクスチャの破棄
				g_ItemModel[i].pTex[j]->Release();
				g_ItemModel[i].pTex[j] = NULL;
			}
		}

		if (g_ItemModel[i].pMesh != NULL)
		{ // メッシュの破棄
			g_ItemModel[i].pMesh->Release();
			g_ItemModel[i].pMesh = NULL;
		}

		if (g_ItemModel[i].pBuffMat != NULL)
		{ // マテリアルの破棄
			g_ItemModel[i].pBuffMat->Release();
			g_ItemModel[i].pBuffMat = NULL;
		}
	}
}
//************************************************
// アイテム更新処理
//************************************************
void UpdateItem(void)
{
	for (int i = 0; i < AMOUNT_ITEM; i++)
	{
		if (!g_Item[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// 回転
		RotateItem(i);

		// 移動
		MoveItem(i);

		// 当たり判定
		CollisionItem(i);
	}

	// 最後に行列計算
	CalcMtxItem();	//!< バグを防ぐため最後に行うこと。
}

//************************************************
// 回転
//************************************************
void RotateItem(int id)
{
	g_Item[id].rot.y += 0.025f;	// クルクル
}

//************************************************
// 移動
//************************************************
void MoveItem(int id)
{
	g_Item[id].pos.y = 5.0f + cosf(g_Item[id].rot.y) * 7.0f; // 上下
}

//************************************************
// 当たり判定
//************************************************
void CollisionItem(int id)
{
	// プレイヤーとの判定を行う
	if (!g_Item[id].use)
	{ // 未使用ならリターン
		return;
	}

	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < MAX_PLAYER; i++, pPlayer++)
	{
		if (CollisionSph(g_Item[id].pos, g_Item[id].model.rad, pPlayer->pos, pPlayer->param.rad))
		{ // プレイヤーにヒットすると

			PlaySound(SOUND_LABEL_PICK_WEAPON);
			// アイテムを取得
			pPlayer->param.weapon = GetItem(id);

			// PFWを更新
			switch (pPlayer->param.weapon)
			{
			case styleGun:

				pPlayer->PFW.magazine = 20;	// 装填
				pPlayer->PFW.CT_reload = 0;	// リロードリセット
				pPlayer->PFW.empty = false;	// 空っぽ判定取り消し

				break;

			case styleRPG:

				pPlayer->PFW.magazine = 3;	// 装填
				pPlayer->PFW.CT_reload = 0;	// リロードリセット
				pPlayer->PFW.empty = false;	// 空っぽ判定取り消し

				break;

			case styleGut:

				pPlayer->PFW.magazine = 40;	// 装填
				pPlayer->PFW.CT_reload = 0;	// リロードリセット
				pPlayer->PFW.empty = false;	// 空っぽ判定取り消し

				break;

			case styleShot:

				pPlayer->PFW.magazine = 7;	// 装填
				pPlayer->PFW.CT_reload = 0;	// リロードリセット
				pPlayer->PFW.empty = false;	// 空っぽ判定取り消し

				break;
			}
		}
	}
}

//************************************************
// アイテムのワールドマトリックスを計算
//************************************************
void CalcMtxItem(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	Item* pItem = &g_Item[0];

	for (int i = 0; i < AMOUNT_ITEM; i++, pItem++)
	{
		if (!pItem->use)
		{ // 未使用ならでコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&pItem->mtxWorld);

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			pItem->rot.y,
			pItem->rot.x,
			pItem->rot.z);

		// 向きを反映2
		D3DXMatrixMultiply(&pItem->mtxWorld,
			&pItem->mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			pItem->pos.x,
			pItem->pos.y,
			pItem->pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&pItem->mtxWorld,
			&pItem->mtxWorld,
			&mtxTrans);
	}
}

//************************************************
// 取得
//************************************************
int GetItem(int id)
{
	// アイテム情報のリセット
	Item* pItem = &g_Item[id];	// アイテム情報へのポインタ
	int style = pItem->style;	// リセット前にスタイルを格納

	pItem->use = false;	// 使用フラグ
	pItem->style = -1;	// スタイル
	pItem->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pItem->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pItem->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// モデル
	pItem->model.pMesh = NULL;
	pItem->model.pBuffMat = NULL;
	pItem->model.NumMat = 0;

	for (int j = 0; j < AMOUNT_MAT; j++)
	{ // マテリアル
		pItem->model.ColMat_offset[j] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pItem->model.pTex[j] = NULL;
	}

	// モデル座標
	pItem->model.pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pItem->model.pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pItem->model.rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pItem->model.rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// エフェクトを消去
	DeleteEffect_Ring(pItem->id_effect);

#ifdef _DEBUG

	// 判定を削除
	DeleteVisibleSph(pItem->id_sph);

#endif	// _DEBUG

	pItem->id_effect = -1;
	pItem->id_sph = -1;

	return style;	// 取得したアイテムのスタイルを返す
}

//************************************************
// アイテム描画
//************************************************
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	for (int id_item = 0; id_item < AMOUNT_ITEM; id_item++)
	{
		if (!g_Item[id_item].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Item[id_item].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Item[id_item].model.pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int id_mat = 0; id_mat < (int)g_Item[id_item].model.NumMat; id_mat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[id_mat].MatD3D);

			//テクスチャの設定
			if (g_Item[id_item].model.pTex[id_mat] != NULL)
			{
				pDevice->SetTexture(0, g_Item[id_item].model.pTex[id_mat]);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			// オブジェクトパーツの描画
			g_Item[id_item].model.pMesh->DrawSubset(id_mat);
		}

		// 保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}