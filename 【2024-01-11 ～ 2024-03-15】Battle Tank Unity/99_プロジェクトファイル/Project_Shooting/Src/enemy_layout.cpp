#ifdef _DEBUG	// 一番下まで

//************************************************
//
// エネミー配置用[enemy_layout.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "enemy_layout.h"

// システム系
#include "input.h"

// 諸処理
#include "debugproc.h"
#include "enemy_camera.h"
#include <assert.h>

/*---【マクロ定義】---*/
#define MAX_EN 256		// 最大配置数
#define MAX_MODELEN 42	// 最大モデル数

/*---【グローバル変数】---*/
EnemyModel g_modelEN[MAX_MODELEN];	// 敵用モデル
Enemy g_EN[MAX_EN];					// 敵配置用情報
Enemy g_tempEN;						// 仮の敵配置情用

bool g_OW_EN = false;	// 配置：上書きモード切り替え
int g_selectEN = 0;		// 上書き時の選択番号

/*---【プロトタイプ宣言】---*/
void ClearInfo_modelEN(void);	// 敵用モデルをクリア
void ClearInfo_EN(void);		// 敵配置情報をクリア
void ClearInfo_tempEN(void);	// 仮の敵配置情報をクリア

void ImportInfo_modelEN(void);								// 敵用モデルを取得
void ImportOffset_modelEN(FILE* pFile, int AmountModel);	// 敵用モデルオフセットを取得
void ImportLayout_EN(void);									// 敵配置情報を取得
void VerifyStyle_EN(int id);								// スタイルを照合
void VerifyStyle_tempEN(void);								// 仮想敵のスタイルを照合

void Uninit_modelEN(void);	// 敵用モデルの破棄

int GetMaxEnabled(void);	// 使用数を取得
void Delete_EN(void);		// 消去
void SortArray_EN(void);	// 配列ソート
void ChangeSelect_EN(void);	// 対象を変更
void ChangeStyle_EN(void);	// スタイルを変更
void ChangeParam_EN(void);	// パラメータを変更
void Rotate_EN(void);		// 回転
void Translate_EN(void);	// 移動
void CalcMtx_EN(void);		// 敵の行列計算
void CalcMtx_tempEN(void);	// 仮想敵の行列計算
void Save_tempEN(void);		// 仮想敵を保存

void Draw_modelEN(void);	// 敵用モデルの描画
void Draw_tempEN(void);		// 仮想の敵用モデルの描画

void ExportLayout_EN(void);	// 配置情報を保存
void PrintDebug_EN(void);	// デバッグ表示

//************************************************
// 初期
//************************************************
void Init_EN(void)
{
	g_OW_EN = false;	// 配置：上書きモード切り替え
	g_selectEN = 0;		// 上書き時の選択番号

	// 敵用モデルをクリア
	ClearInfo_modelEN();

	// 敵配置情報をクリア
	ClearInfo_EN();

	// 仮の敵配置情報をクリア
	ClearInfo_tempEN();

	// 敵用モデルの取得
	ImportInfo_modelEN();

	// 敵配置情報を取得
	ImportLayout_EN();

	// 仮想敵のスタイル照合
	VerifyStyle_tempEN();
}

//************************************************
// 終了
//************************************************
void Uninit_EN(void)
{
	// 敵用モデルを破棄
	Uninit_modelEN();
}

//************************************************
// 更新
//************************************************
void Update_EN(void)
{
	if (GetKeyboardTrigger(DIK_F3))
	{
		// 配置情報を保存
		ExportLayout_EN();
	}

	if (GetKeyboardTrigger(DIK_F5))
	{
		// 配置：上書きモード変更
		g_OW_EN = !g_OW_EN;
	}

	// 消去
	Delete_EN();

	// 対象を変更
	ChangeSelect_EN();

	// スタイルを変更
	ChangeStyle_EN();

	// パラメータを変更
	ChangeParam_EN();

	// 回転
	Rotate_EN();

	// 移動
	Translate_EN();

	// 行列計算
	CalcMtx_EN();

	// 仮想の行列計算
	CalcMtx_tempEN();

	// 保存
	Save_tempEN();

	// デバッグ表示
	PrintDebug_EN();
}

//************************************************
// 描画
//************************************************
void Draw_EN(void)
{
	// 敵用モデルの描画
	Draw_modelEN();

	// 仮想の敵用モデルの描画
	Draw_tempEN();
}

//************************************************
// 敵配置情報の取得
//************************************************
Enemy GetInfo_targetEN(void)
{
	Enemy* pEN = nullptr;	// 操作識別用

	// モードに応じて参照対象を変更
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	return *pEN;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// 敵用モデルをクリア
//************************************************
void ClearInfo_modelEN(void)
{
	EnemyModel* pModel = &g_modelEN[0];

	for (int i = 0; i < MAX_MODELEN; i++)
	{ // エネミー用モデル情報のひな形のリセット

		// スタイル
		pModel->style = 0;

		// モデル
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;

		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // マテリアル
			pModel->pTex[j] = NULL;
		}

		// モデル座標
		pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 親インデックス
		pModel->IdxParent = -1;
	}
}

//************************************************
// 敵配置情報をクリア
//************************************************
void ClearInfo_EN(void)
{
	Enemy* pEnemy = &g_EN[0];

	for (int i = 0; i < MAX_EN; i++, pEnemy++)
	{
		// 使用フラグ
		pEnemy->use = false;

		// パラメータ
		pEnemy->param =
		{
			0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, { 0.0f, 0.0f, 0.0f } ,0 ,0		// メンバー情報はヘッダファイルを確認して下さい
		};

		// 座標系
		pEnemy->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEnemy->size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 色
		pEnemy->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		for (int j = 0; j < MAX_MODELEN; j++)
		{ // 各パーツ情報をリセット
			EnemyModel* pModel = &pEnemy->parts[j];

			// モデル
			pModel->pMesh = NULL;
			pModel->pBuffMat = NULL;
			pModel->NumMat = 0;

			for (int k = 0; k < AMOUNT_MAT; k++)
			{ // マテリアル
				pModel->pTex[k] = NULL;
			}

			// モデル座標
			pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 親インデックス
			pModel->IdxParent = -1;
		}

		// 識別番号
		pEnemy->id_shadow = 0;
		pEnemy->id_sph = 0;
	}
}

//************************************************
// 仮の敵配置情報をクリア
//************************************************
void ClearInfo_tempEN(void)
{
	// 使用フラグ
	g_tempEN.use = false;

	// パラメータ
	g_tempEN.param =
	{
		0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, { 0.0f, 0.0f, 0.0f } ,0 ,0	// メンバー情報はヘッダファイルを確認して下さい
	};

	// 座標系
	g_tempEN.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_tempEN.pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_tempEN.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_tempEN.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_tempEN.rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_tempEN.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 色
	g_tempEN.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int j = 0; j < MAX_MODELEN; j++)
	{ // 各パーツ情報をリセット
		EnemyModel* pModel = &g_tempEN.parts[j];

		// モデル
		pModel->pMesh = NULL;
		pModel->pBuffMat = NULL;
		pModel->NumMat = 0;

		for (int k = 0; k < AMOUNT_MAT; k++)
		{ // マテリアル
			pModel->pTex[k] = NULL;
		}

		// モデル座標
		pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 親インデックス
		pModel->IdxParent = -1;
	}

	// 識別番号
	g_tempEN.id_shadow = 0;
	g_tempEN.id_sph = 0;
}

//************************************************
// 敵用モデルを取得
//************************************************
void ImportInfo_modelEN(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int AmountModel = 0;		// モデルの数を格納
	int id_Model = 0;			// モデルの識別用

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_model.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "エネミーモデル情報の展開に失敗");

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
		assert(AmountModel < MAX_MODELEN && "エネミーモデルモデル情報が最大量を越えました");

#endif

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// 読み込むモデル名を取得する
			fscanf_s(pFile, "%s %s", &FileString[0], 2, &FileString[0], 128);

			// 読み込んだ情報をひな形にのみコピーする
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_modelEN[id_Model].pBuffMat,
				NULL,
				&g_modelEN[id_Model].NumMat,
				&g_modelEN[id_Model].pMesh);

			id_Model++; // パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}

	// 各モデルのオフセット情報を取得
	ImportOffset_modelEN(pFile, AmountModel);
}

//************************************************
// 敵用モデルオフセットを取得
//************************************************
void ImportOffset_modelEN(FILE* pFile, int AmountModel)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int Style = -1;				// このパーツのスタイルを格納
	int IdxParent = -1;			// 親のインデックスを格納
	D3DXVECTOR3 pos = {};		// 位置のオフセットを格納
	D3DXVECTOR3 rot = {};		// 向きのオフセットを格納
	int id_Model = 0;			// モデルの識別用

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // このパーツのスタイルを取得	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &Style);
		}

		if (strcmp(&FileString[0], "PARENT") == 0)
		{ // 親のインデックスを取得	
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &IdxParent);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置のオフセットを取得	
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きのオフセットを取得	
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARTSSET") == 0)
		{
			// 読み込んだ情報をひな形にのみコピーする
			g_modelEN[id_Model].style = Style;
			g_modelEN[id_Model].IdxParent = IdxParent;
			g_modelEN[id_Model].pos_offset = pos;
			g_modelEN[id_Model].rot_offset = rot;

			id_Model++; // パーツを進める

			if (id_Model == AmountModel)
			{ // モデル数分読み取り終わると終了
				break;
			}
		}
	}
}

//************************************************
// 配置情報を取得
//************************************************
void ImportLayout_EN(void)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int i = 0;					// 汎用整数
	int phase = 0;				// フェーズ情報格納
	int appear = 0;				// 出現タイミングを格納
	int style = 0;				// スタイルを格納
	int hp = 0;					// ライフを格納
	float spd = 0;				// 速度を格納
	float rad = 0;				// 判定サイズを格納
	D3DXVECTOR3 pos, rot;		// 位置と向きを格納

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_param.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "エネミーパラメータ情報の展開に失敗");

#else

		return;

#endif	// _DEBUG
	}

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "PHASE") == 0)
		{ // 出現フェーズを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &phase);
		}

		if (strcmp(&FileString[0], "APPEAR") == 0)
		{ // 出現タイミングを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &appear);
		}

		if (strcmp(&FileString[0], "STYLE") == 0)
		{ // スタイルを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &style);
		}

		if (strcmp(&FileString[0], "HP") == 0)
		{ // ライフを取得
			fscanf_s(pFile, "%s %d", &FileString[0], 2, &hp);
		}

		if (strcmp(&FileString[0], "SPD") == 0)
		{ // 速度を取得
			fscanf_s(pFile, "%s %f", &FileString[0], 2, &spd);
		}

		if (strcmp(&FileString[0], "RAD") == 0)
		{ // 判定サイズを取得
			fscanf_s(pFile, "%s %f", &FileString[0], 2, &rad);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置を取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きを取得
			fscanf_s(pFile, "%s %f %f %f", &FileString[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&FileString[0], "END_PARAMSET") == 0)
		{ // 取得した情報を反映

			g_EN[i].param =
			{
				phase, appear, style, 0, 0, -1, hp, spd, rad, { 0.0f, 0.0f, 0.0f }, 0, 0
			};
			g_EN[i].pos = pos;
			g_EN[i].rot = rot;

			g_EN[i].use = true;	// これにより描画状態となる

			// スタイル番号を照合
			VerifyStyle_EN(i);

			i++;	// 次の番号へ

			if (i >= MAX_EN)
			{ // 敵の最大数を越えると強制終了
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
// スタイル番号の照合
//************************************************
void VerifyStyle_EN(int id)
{
	for (int i = 0; i < MAX_MODELEN; i++)
	{
		if (g_EN[id].param.style == g_modelEN[i].style)
		{ // 各エネミーのスタイルと全パーツのスタイルを照合

			g_EN[id].parts[i] = g_modelEN[i];	// 番号の一致しているパーツのみ有効化
		}
		else
		{ // それ以外の余計なものは削除

			// モデル
			g_EN[id].parts[i].pMesh = NULL;
			g_EN[id].parts[i].pBuffMat = NULL;
			g_EN[id].parts[i].NumMat = 0;

			for (int j = 0; j < AMOUNT_MAT; j++)
			{ // マテリアル

				g_EN[id].parts[i].pTex[j] = NULL;
			}

			// モデル座標
			g_EN[id].parts[i].pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_EN[id].parts[i].pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_EN[id].parts[i].rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_EN[id].parts[i].rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 親インデックス
			g_EN[id].parts[i].IdxParent = -1;
		}
	}
}

//************************************************
// 仮想敵のスタイル番号の照合
//************************************************
void VerifyStyle_tempEN(void)
{
	for (int i = 0; i < MAX_MODELEN; i++)
	{
		if (g_tempEN.param.style == g_modelEN[i].style)
		{ // 各エネミーのスタイルと全パーツのスタイルを照合

			g_tempEN.parts[i] = g_modelEN[i];	// 番号の一致しているパーツのみ有効化
		}
		else
		{ // それ以外の余計なものは削除

			// モデル
			g_tempEN.parts[i].pMesh = NULL;
			g_tempEN.parts[i].pBuffMat = NULL;
			g_tempEN.parts[i].NumMat = 0;

			for (int j = 0; j < AMOUNT_MAT; j++)
			{ // マテリアル

				g_tempEN.parts[i].pTex[j] = NULL;
			}

			// モデル座標
			g_tempEN.parts[i].pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_tempEN.parts[i].pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_tempEN.parts[i].rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_tempEN.parts[i].rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 親インデックス
			g_tempEN.parts[i].IdxParent = -1;
		}
	}
}

//************************************************
// 使用数を取得
//************************************************
int GetMaxEnabled(void)
{
	int max = 0;	// 最大数格納

	// 使用されている総数を取得
	for (int i = 0; i < MAX_EN; i++)
	{
		if (g_EN[i].use)
		{
			max++;
		}
	}

	return max;
}

//************************************************
// 敵のモデル情報を破棄
//************************************************
void Uninit_modelEN(void)
{
	for (int i = 0; i < MAX_MODELEN; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_modelEN[i].pTex[j] != NULL)
			{ // テクスチャの破棄

				g_modelEN[i].pTex[j]->Release();
				g_modelEN[i].pTex[j] = NULL;
			}
		}

		if (g_modelEN[i].pMesh != NULL)
		{ // メッシュの破棄

			g_modelEN[i].pMesh->Release();
			g_modelEN[i].pMesh = NULL;
		}

		if (g_modelEN[i].pBuffMat != NULL)
		{ // マテリアルの破棄

			g_modelEN[i].pBuffMat->Release();
			g_modelEN[i].pBuffMat = NULL;
		}
	}
}

//************************************************
// 消去
//************************************************
void Delete_EN(void)
{
	if (!g_OW_EN)
	{ // 上書きモードでなければリターン

		return;
	}

	if (GetKeyboardTrigger(DIK_BACK))
	{
		int max = GetMaxEnabled();	// 使用数を取得

		if (max <= 0)
		{ // 何も使用されていなければ終了

			return;
		}

		g_EN[g_selectEN].use = false;

		// パラメータ
		g_EN[g_selectEN].param =
		{
			0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, { 0.0f, 0.0f, 0.0f } ,0 ,0	// メンバー情報はヘッダファイルを確認して下さい
		};

		// 座標系
		g_EN[g_selectEN].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EN[g_selectEN].pos_old = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EN[g_selectEN].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EN[g_selectEN].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EN[g_selectEN].rot_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EN[g_selectEN].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 色
		g_EN[g_selectEN].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		for (int i = 0; i < MAX_MODELEN; i++)
		{ // 各パーツ情報をリセット
			
			EnemyModel* pModel = &g_EN[g_selectEN].parts[i];

			// モデル
			pModel->pMesh = NULL;
			pModel->pBuffMat = NULL;
			pModel->NumMat = 0;

			for (int j = 0; j < AMOUNT_MAT; j++)
			{ // マテリアル

				pModel->pTex[j] = NULL;
			}

			// モデル座標
			pModel->pos_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->pos_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pModel->rot_moved = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 親インデックス
			pModel->IdxParent = -1;
		}

		// 識別番号
		g_EN[g_selectEN].id_shadow = 0;
		g_EN[g_selectEN].id_sph = 0;

		if (g_selectEN == max - 1)
		{ // 消去予定の番が最高番の場合、選択を1つ戻しておく

			g_selectEN = max - 2;
		}
	}

	// 配列ソート
	SortArray_EN();
}

//************************************************
// 配列ソート
//************************************************
void SortArray_EN(void)
{
	for (int i = 0; i < MAX_EN - 1; i++)
	{
		if (!g_EN[i].use && g_EN[i + 1].use)
		{ // この番が未使用で、次の番が使用中の場合

			// 情報を反転させていく
			Enemy EN = g_EN[i];
			g_EN[i] = g_EN[i + 1];
			g_EN[i + 1] = EN;
		}
	}
}

//************************************************
// 対象を変更
//************************************************
void ChangeSelect_EN(void)
{
	if (!g_OW_EN)
	{ // 上書きモードでなければリターン

		return;
	}

	int max = GetMaxEnabled();	// 使用数を取得

	if (GetKeyboardTrigger(DIK_PERIOD))
	{
		g_selectEN < max - 1 ? g_selectEN++ : g_selectEN = 0;
	}
	else if (GetKeyboardTrigger(DIK_COMMA))
	{
		g_selectEN > 0 ? g_selectEN-- : g_selectEN = max - 1;
	}

	if (GetKeyboardPress(DIK_Z))
	{
		g_selectEN < max - 1 ? g_selectEN++ : g_selectEN = 0;
	}
	else if (GetKeyboardPress(DIK_X))
	{
		g_selectEN > 0 ? g_selectEN-- : g_selectEN = max - 1;
	}
}

//************************************************
// スタイルを変更
//************************************************
void ChangeStyle_EN(void)
{
	Enemy* pEN = nullptr;	// 操作識別用

	// モードに応じて操作対象を変更
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	int max = 3;	// 最大数格納

	// スタイルの変更
	if (GetKeyboardTrigger(DIK_RSHIFT))
	{
		pEN->param.style < max - 1 ? pEN->param.style++ : pEN->param.style = 0;

		g_OW_EN ? VerifyStyle_EN(g_selectEN) : VerifyStyle_tempEN();
	}
	else if (GetKeyboardTrigger(DIK_LSHIFT))
	{
		pEN->param.style > 0 ? pEN->param.style-- : pEN->param.style = max - 1;

		g_OW_EN ? VerifyStyle_EN(g_selectEN) : VerifyStyle_tempEN();
	}

	assert(pEN->param.style >= 0 && pEN->param.style < max && "スタイルの変更失敗");
}

//************************************************
// パラメータを変更
//************************************************
void ChangeParam_EN(void)
{
	Enemy* pEN = nullptr;	// 操作識別用

	// モードに応じて操作対象を変更
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	// フェーズを変更
	if (GetKeyboardTrigger(DIK_1))
	{
		pEN->param.phase > 0 ? pEN->param.phase-- : pEN->param.phase = 4;
	}
	else if (GetKeyboardTrigger(DIK_2))
	{
		pEN->param.phase < 4 ? pEN->param.phase++ : pEN->param.phase = 0;
	}

	// 出現CTを変更
	if (GetKeyboardTrigger(DIK_3))
	{
		if (pEN->param.appear > 0)
		{
			pEN->param.appear--;
		}
	}
	else if (GetKeyboardTrigger(DIK_4))
	{
		pEN->param.appear++;
	}

	// 出現CTを大幅変更
	if (GetKeyboardPress(DIK_5))
	{
		if (pEN->param.appear > 0)
		{
			pEN->param.appear--;
		}
	}
	else if (GetKeyboardPress(DIK_6))
	{
		pEN->param.appear++;
	}

	// 体力を変更
	if (GetKeyboardTrigger(DIK_7))
	{
		if (pEN->param.HP > 0)
		{
			pEN->param.HP--;
		}
	}
	else if (GetKeyboardTrigger(DIK_8))
	{
		pEN->param.HP++;
	}

	// 速度を変更
	if (GetKeyboardTrigger(DIK_9))
	{
		if (pEN->param.SPD > 0.0f)
		{
			pEN->param.SPD -= 1.0f;
		}
	}
	else if (GetKeyboardTrigger(DIK_0))
	{
		pEN->param.SPD += 1.0f;
	}
}

//************************************************
// 回転
//************************************************
void Rotate_EN(void)
{
	Enemy* pEN = nullptr;	// 操作識別用

	// モードに応じて操作対象を変更
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	// X軸に回転
	if (GetKeyboardPress(DIK_R))
	{
		pEN->rot.x += 0.05f;
	}
	else if (GetKeyboardPress(DIK_F))
	{
		pEN->rot.x -= 0.05f;
	}
	else if (GetKeyboardTrigger(DIK_V))
	{
		pEN->rot.x = 0.0f;
	}

	// Y軸に回転
	if (GetKeyboardPress(DIK_T))
	{
		pEN->rot.y += 0.05f;
	}
	else if (GetKeyboardPress(DIK_G))
	{
		pEN->rot.y -= 0.05f;
	}
	else if (GetKeyboardTrigger(DIK_B))
	{
		pEN->rot.y = 0.0f;
	}

	// Z軸に回転
	if (GetKeyboardPress(DIK_Y))
	{
		pEN->rot.z += 0.05f;
	}
	else if (GetKeyboardPress(DIK_H))
	{
		pEN->rot.z -= 0.05f;
	}
	else if (GetKeyboardTrigger(DIK_N))
	{
		pEN->rot.z = 0.0f;
	}

	// X軸に一定値
	if (GetKeyboardTrigger(DIK_U))
	{
		pEN->rot.x += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_J))
	{
		pEN->rot.x -= D3DX_PI * 0.025f;
	}

	// Y軸に一定値
	if (GetKeyboardTrigger(DIK_I))
	{
		pEN->rot.y += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_K))
	{
		pEN->rot.y -= D3DX_PI * 0.025f;
	}

	// Z軸に一定値
	if (GetKeyboardTrigger(DIK_O))
	{
		pEN->rot.z += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_L))
	{
		pEN->rot.z -= D3DX_PI * 0.025f;
	}
}

//************************************************
// 移動
//************************************************
void Translate_EN(void)
{
	Enemy* pEN = nullptr;				// 操作識別用
	bool move = false;					// 移動用
	float X = 0.0f;						// 左右の移動成分
	float Z = 0.0f;						// 前後の移動成分
	const ENC* pENC = GetInfo_ENC();	// カメラ情報を取得

	// モードに応じて操作対象を変更
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	// 左右
	if (GetKeyboardPress(DIK_A))
	{
		X = -1.0f;
	}
	else if (GetKeyboardPress(DIK_D))
	{
		X = 1.0f;
	}

	// 前後
	if (GetKeyboardPress(DIK_W))
	{
		Z = 1.0f;
	}
	else if (GetKeyboardPress(DIK_S))
	{
		Z = -1.0f;
	}

	// 上下
	if (GetKeyboardPress(DIK_LBRACKET))
	{
		pEN->pos.y += 5.0f;
	}
	else if (GetKeyboardPress(DIK_RBRACKET))
	{
		pEN->pos.y -= 5.0f;
	}
	else if (GetKeyboardTrigger(DIK_YEN))
	{
		pEN->pos.y = 0.0f;
	}

	// intへのキャストを利用して小数部分を切り捨てるため警告無効化
#pragma warning(disable:4244)

	// 端数調整
	if (GetKeyboardTrigger(DIK_MINUS))
	{
		pEN->pos.x = (int)pEN->pos.x;
	}
	else if (GetKeyboardTrigger(DIK_CIRCUMFLEX))
	{
		pEN->pos.z = (int)pEN->pos.z;
	}

#pragma warning(default:4244)

	// 左右一定値
	if (GetKeyboardTrigger(DIK_NUMPAD4))
	{
		X = -1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD6))
	{
		X = 1.0f;
	}

	// 前後一定値
	if (!GetKeyboardPress(DIK_LALT))
	{ /*---【デバッグ表示のスクロールとの兼ね合いのため】---*/

		if (GetKeyboardTrigger(DIK_NUMPAD8))
		{
			Z = 1.0f;
		}
		else if (GetKeyboardTrigger(DIK_NUMPAD5))
		{
			Z = -1.0f;
		}
	}

	// 上下一定値
	if (GetKeyboardTrigger(DIK_NUMPAD2))
	{
		pEN->pos.y += 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD0))
	{
		pEN->pos.y -= 1.0f;
	}

	if (X != 0.0f || Z != 0.0f)
	{ // 何かを入力していれば移動している判定
		move = true;
	}

	if (move)
	{
		// 移動量と目標方角を設定
		pEN->pos.x += sinf(atan2f(X, Z) + pENC->rot.y) * 5.0f;
		pEN->pos.z += cosf(atan2f(X, Z) + pENC->rot.y) * 5.0f;
	}
}

//************************************************
// 敵配置用の行列を計算
//************************************************
void CalcMtx_EN(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	for (int enemy_id = 0; enemy_id < MAX_EN; enemy_id++)
	{
		if (!g_EN[enemy_id].use)
		{ // この番の使用フラグが無しでコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_EN[enemy_id].mtxWorld);

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_EN[enemy_id].rot.y,
			g_EN[enemy_id].rot.x,
			g_EN[enemy_id].rot.z);

		// 向きを反映2
		D3DXMatrixMultiply(&g_EN[enemy_id].mtxWorld,
			&g_EN[enemy_id].mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_EN[enemy_id].pos.x,
			g_EN[enemy_id].pos.y,
			g_EN[enemy_id].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_EN[enemy_id].mtxWorld,
			&g_EN[enemy_id].mtxWorld,
			&mtxTrans);

		for (int Ps_id = 0; Ps_id < MAX_MODELEN; Ps_id++)
		{
			if (g_EN[enemy_id].parts[Ps_id].pMesh == NULL)
			{ // 空っぽならコンティニュー
				continue;
			}

			// この番パーツの「親パーツ」のインデックスを保存
			int IdxParent = g_EN[enemy_id].parts[Ps_id].IdxParent;

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_EN[enemy_id].parts[Ps_id].mtxWorld);

			// 向きを反映1
			D3DXMatrixRotationYawPitchRoll(&mtxRot,
				g_EN[enemy_id].parts[Ps_id].rot_offset.y,
				g_EN[enemy_id].parts[Ps_id].rot_offset.x,
				g_EN[enemy_id].parts[Ps_id].rot_offset.z);

			// 向きを反映2
			D3DXMatrixMultiply(&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&mtxRot);

			// 位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				g_EN[enemy_id].parts[Ps_id].pos_offset.x,
				g_EN[enemy_id].parts[Ps_id].pos_offset.y,
				g_EN[enemy_id].parts[Ps_id].pos_offset.z);

			// 位置を反映
			D3DXMatrixMultiply(&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&mtxTrans);

			D3DXMATRIX mtxParent = {};

			// 親のワールドマトリックスを取得
			if (IdxParent == -1)
			{ //メインパーツのみワールド座標に直結
				mtxParent = g_EN[enemy_id].mtxWorld;
			}
			else
			{ //その他パーツはそれぞれの親パーツへ付随
				mtxParent = g_EN[enemy_id].parts[IdxParent].mtxWorld;
			}

			// パーツごとのワールドマトリックスを算出
			D3DXMatrixMultiply(&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&g_EN[enemy_id].parts[Ps_id].mtxWorld,
				&mtxParent);
		}
	}
}

//************************************************
// 仮想敵の行列計算
//************************************************
void CalcMtx_tempEN(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_tempEN.mtxWorld);

	// 向きを反映1
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		g_tempEN.rot.y,
		g_tempEN.rot.x,
		g_tempEN.rot.z);

	// 向きを反映2
	D3DXMatrixMultiply(&g_tempEN.mtxWorld,
		&g_tempEN.mtxWorld,
		&mtxRot);

	// 位置を反映1
	D3DXMatrixTranslation(&mtxTrans,
		g_tempEN.pos.x,
		g_tempEN.pos.y,
		g_tempEN.pos.z);

	// 位置を反映2
	D3DXMatrixMultiply(&g_tempEN.mtxWorld,
		&g_tempEN.mtxWorld,
		&mtxTrans);

	for (int Ps_id = 0; Ps_id < MAX_MODELEN; Ps_id++)
	{
		if (g_tempEN.parts[Ps_id].pMesh == NULL)
		{ // 空っぽならコンティニュー
			continue;
		}

		// この番パーツの「親パーツ」のインデックスを保存
		int IdxParent = g_tempEN.parts[Ps_id].IdxParent;

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_tempEN.parts[Ps_id].mtxWorld);

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_tempEN.parts[Ps_id].rot_offset.y,
			g_tempEN.parts[Ps_id].rot_offset.x,
			g_tempEN.parts[Ps_id].rot_offset.z);

		// 向きを反映2
		D3DXMatrixMultiply(&g_tempEN.parts[Ps_id].mtxWorld,
			&g_tempEN.parts[Ps_id].mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_tempEN.parts[Ps_id].pos_offset.x,
			g_tempEN.parts[Ps_id].pos_offset.y,
			g_tempEN.parts[Ps_id].pos_offset.z);

		// 位置を反映
		D3DXMatrixMultiply(&g_tempEN.parts[Ps_id].mtxWorld,
			&g_tempEN.parts[Ps_id].mtxWorld,
			&mtxTrans);

		D3DXMATRIX mtxParent = {};

		// 親のワールドマトリックスを取得
		if (IdxParent == -1)
		{ //メインパーツのみワールド座標に直結
			mtxParent = g_tempEN.mtxWorld;
		}
		else
		{ //その他パーツはそれぞれの親パーツへ付随
			mtxParent = g_tempEN.parts[IdxParent].mtxWorld;
		}

		// パーツごとのワールドマトリックスを算出
		D3DXMatrixMultiply(&g_tempEN.parts[Ps_id].mtxWorld,
			&g_tempEN.parts[Ps_id].mtxWorld,
			&mtxParent);
	}
}

//************************************************
// 仮想敵を保存
//************************************************
void Save_tempEN(void)
{
	if (g_OW_EN)
	{ // 配置モードでなければリターン

		return;
	}

	// 仮想敵を、通常の敵として配置
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		for (int i = 0; i < MAX_EN; i++)
		{
			if (g_EN[i].use)
			{ // 使用されていればコンティニュー
				continue;
			}

			g_EN[i] = g_tempEN;	// 新たに情報を保存

			g_EN[i].use = true;	// このモデルの使用判定を出す

			break;
		}
	}
}

//************************************************
// 敵用モデルの描画
//************************************************
void Draw_modelEN(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	for (int id_enemy = 0; id_enemy < MAX_EN; id_enemy++)
	{
		if (!g_EN[id_enemy].use)
		{ // この番の使用フラグが無しでコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_EN[id_enemy].mtxWorld);

		for (int id_Ps = 0; id_Ps < MAX_MODELEN; id_Ps++)
		{
			if (g_EN[id_enemy].parts[id_Ps].pMesh == NULL)
			{ // パーツが未使用ならコンティニュー
				continue;
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_EN[id_enemy].parts[id_Ps].mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_EN[id_enemy].parts[id_Ps].pBuffMat->GetBufferPointer();

			for (int id_mat = 0; id_mat < (int)g_EN[id_enemy].parts[id_Ps].NumMat; id_mat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[id_mat].MatD3D);

				// テクスチャの設定
				if (g_EN[id_enemy].parts[id_Ps].pTex[id_mat] != NULL)
				{
					pDevice->SetTexture(0, g_EN[id_enemy].parts[id_Ps].pTex[id_mat]);
				}
				else
				{
					pDevice->SetTexture(0, NULL);
				}

				// モデルパーツの描画
				g_EN[id_enemy].parts[id_Ps].pMesh->DrawSubset(id_mat);
			}

			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//************************************************
// 仮想の敵用モデルの描画
//************************************************
void Draw_tempEN(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_tempEN.mtxWorld);

	for (int id_Ps = 0; id_Ps < MAX_MODELEN; id_Ps++)
	{
		if (g_tempEN.parts[id_Ps].pMesh == NULL)
		{ // パーツが未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_tempEN.parts[id_Ps].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_tempEN.parts[id_Ps].pBuffMat->GetBufferPointer();

		for (int id_mat = 0; id_mat < (int)g_tempEN.parts[id_Ps].NumMat; id_mat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[id_mat].MatD3D);

			// テクスチャの設定
			if (g_tempEN.parts[id_Ps].pTex[id_mat] != NULL)
			{
				pDevice->SetTexture(0, g_tempEN.parts[id_Ps].pTex[id_mat]);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			// モデルパーツの描画
			g_tempEN.parts[id_Ps].pMesh->DrawSubset(id_mat);
		}

		// 保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//************************************************
// 配置情報を保存
//************************************************
void ExportLayout_EN(void)
{
	FILE* pFile = NULL;
	D3DXVECTOR3 rot = {};	// 計算用

	// 保存するファイルを指定、無ければ作成
	fopen_s(&pFile, "data\\TXT\\ENEMY\\enemy_param_export.txt", "w");
 
	for (int phase = 0; phase < 5; phase++)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# フェーズ [ %d ]\n", phase);
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		for (int i = 0; i < MAX_EN; i++)
		{
			if (!g_EN[i].use)
			{ // 未使用ならコンティニュー
				continue;
			}

			if (g_EN[i].param.phase != phase)
			{ // フェーズが異なればコンティニュー
				continue;
			}

			// 弧度を度数に変換
			rot = (g_EN[i].rot * 180.0f) / D3DX_PI;

			fprintf(pFile, "PARAMSET\n");
			fprintf(pFile, "	PHASE = %d\n", g_EN[i].param.phase);
			fprintf(pFile, "	APPEAR = %d\n", g_EN[i].param.appear);
			fprintf(pFile, "	STYLE = %d\n", g_EN[i].param.style);
			fprintf(pFile, "	HP = %d\n", g_EN[i].param.HP);
			fprintf(pFile, "	SPD = %.1f\n", g_EN[i].param.SPD);

			if (g_EN[i].param.style == Dragonfly)
			{ // 蜻蛉のみ

				fprintf(pFile, "	RAD = %.1f\n", 30.0f);
			}
			else
			{ // それ以外

				fprintf(pFile, "	RAD = %.1f\n", 40.0f);
			}

			fprintf(pFile, "	POS = %.1f %.1f %.1f\n", g_EN[i].pos.x, g_EN[i].pos.y, g_EN[i].pos.z);
			fprintf(pFile, "	ROT = %.1f %.1f %.1f\n", rot.x, rot.y, rot.z);
			fprintf(pFile, "END_PARAMSET\n\n");
		}
	}

	fprintf(pFile, "END_SCRIPT\n");

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// デバッグ表示
//************************************************
void PrintDebug_EN(void)
{
	Enemy* pEN = nullptr;	// 操作識別用

	// モードに応じて参照対象を変更
	!g_OW_EN ? pEN = &g_tempEN : pEN = &g_EN[g_selectEN];

	char Test[32] = {};	// 汎用文字列

	PrintDebugProc("\n　【敵配置情報】\n");
	PrintDebugProc("━━━━━━━━━━━━━━\n");
	g_OW_EN ? sprintf(Test, "上書き") : sprintf(Test, "配置");
	PrintDebugProc("　編集モード：[ %s ] \n", &Test[0]);
	PrintDebugProc("━━━━━━━━━━━━━━\n");
	PrintDebugProc("　上書き時の選択番号：%d\n\n", g_selectEN);

	PrintDebugProc("　敵の使用合計数：%d\n\n", GetMaxEnabled());

	PrintDebugProc("　フェーズ：[ %d ] \n", pEN->param.phase);
	PrintDebugProc("　出現CT：[ %d ] \n", pEN->param.appear);
	PrintDebugProc("　スタイル：[ %d ] \n", pEN->param.style);
	PrintDebugProc("　体力：[ %d ] \n", pEN->param.HP);
	PrintDebugProc("　速度：[ %f ] \n", pEN->param.SPD);
	PrintDebugProc("　位置：[ %f , %f , %f ] \n", pEN->pos.x, pEN->pos.y, pEN->pos.z);
	PrintDebugProc("　向き：[ %f , %f , %f ] \n", pEN->rot.x, pEN->rot.y, pEN->rot.z);
	PrintDebugProc("━━━━━━━━━━━━━━\n");
}

#endif	// _DEBUG