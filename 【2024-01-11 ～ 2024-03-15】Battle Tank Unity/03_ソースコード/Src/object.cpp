//************************************************
//
// オブジェクト[object.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "object.h"

// 諸処理
#include "effect_smoke.h"
#include "item.h"
#include "object_bar.h"
#include "sound.h"

// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#include "editcamera.h"
#include "input.h"
#include "visible_box.h"
#include <assert.h>
#endif	// _DEBUG

/*---【マクロ定義】---*/
#define OBJECT_EX 1	// オブジェクト情報の管理分岐

/*---【グローバル変数】---*/
Object g_Object[AMOUNT_OBJECT];					// オブジェクト情報用
Object g_PreObject;								// 仮想のオブジェクト情報用
Object g_GizmoObject;							// ギズモモデル用
//Object g_StageObject;							// ステージモデル用
ObjectModel g_ObjectModel[AMOUNT_MODEL_OBJECT];	// オブジェクトモデル情報の原型
D3DXVECTOR3 g_ObjectMove[AMOUNT_OBJECT];		// 振動用移動幅
int g_MaxModel = 0;								// モデル総種類数格納
int g_MaxObject = 0;							// 既存モデル総数格納
bool g_TrackAA = true;							// 移動モード識別
bool g_Overwrite = false;						// 編集モード識別
int g_obj_id = 0;								// 選択している既存オブジェクト識別

/*---【プロトタイプ宣言】---*/
void ClearObject(void);			// オブジェクト情報をクリア
void ClearPreObject(void);		// 仮想のオブジェクト情報をクリア
void ClearGizmoObject(void);	// ギズモモデル情報をクリア
//void ClearStageObject(void);	// ステージモデル情報をクリア
void ClearObjectModel(void);	// オブジェクトモデル情報の原型をクリア

void ImportModelObject(void);			// オブジェクトモデル取得
void ImportModelBoxObject(int id,
	char* str);							// バウンディングボックスを形成
void ImportLayoutObject(FILE* pFile);	// モデル配置情報取得
void ImportLayoutObjectEX(FILE* pFile);	// モデル配置情報+α取得
void ImportTexObject(void);				// モデルテクスチャを読込み
void VerifyTypeObject(int id_Model);	// オブジェクト種類の照合
void AdjustAABBObject(int id_Model);	// AABBサイズの調整
void ImportGizmoModelObject(void);		// ギズモモデル取得
//void ImportStageModelObject(void);	// ステージモデル取得

void UninitGizmoObject(void);	// ギズモモデルの破棄
//void UninitStageObject(void);	// ステージモデルの破棄

void UpdateAABB(int id);		// 判定を更新
void DamageObject(int id);		// 被ダメっぽく
void DeadObject(int id);		// 壊れる感じ
void DeadDeleteObject(int id);	// 選択式で無い消去
void ResurrectObject(int id);	// 復活

void UpdateEditObject(void);			// エディットモード時の更新処理
int GetInfoMaxObject(void);				// 現在の配置モデル数を取得
void DeleteObject(void);				// 既存オブジェクトを消去
void SortArrayObject(void);				// 既存オブジェクトをソート
void ChangeTargetObject(void);			// 対象を変更
void ChangeTypeObject(Object* pObject);	// 種類を変更
void ChangeHPObject(Object* pObject);	// 体力を変更
void ChangeDEFObject(Object* pObject);	// 防御力を変更
void VerifyTypePreObject(void);			// 仮想オブジェクト種類の照合
void RotateObject(Object* pObject);		// オブジェクトの回転
void TranslateObject(Object* pObject);	// オブジェクトの移動
void SavePreObject(void);				// 仮想オブジェクトを保存
void TrackGizmoObject(Object* pObject);	// ギズモモデルを追従
void CalcMtxObject(void);				// 既存オブジェクト用マトリックスの計算
void CalcMtxPreObject(int mode);		// 仮想オブジェクト用マトリックスの計算
void ExportLayoutObject(void);			// モデル配置情報保存
void ExportLayoutObjectEX(void);		// モデル配置情報+α保存

void DrawPreObject(int mode);	// 仮想のオブジェクトの描画(ギズモ含む)

void PrintDebugObject(void);	// デバッグ表示
void PrintDebugObjectEX(void);	// デバッグ表示+α

//************************************************
// オブジェクト初期
//************************************************
void InitObject(void)
{
	g_MaxModel = 0;			// モデル総種類数リセット
	g_MaxObject = 0;		// 既存モデル数リセット
	g_TrackAA = true;		// 移動モード：平行
	g_Overwrite = false;	// 編集モード：通常
	g_obj_id = 0;			// 現在の選択オブジェクト

	// オブジェクト情報をクリア
	ClearObject();

#ifdef _DEBUG

	// 仮想のオブジェクト情報をリセット
	ClearPreObject();

	// ギズモ情報をリセット
	ClearGizmoObject();

#endif // _DEBUG

	// ステージモデルのクリア
	//ClearStageObject();

	// オブジェクトモデル情報の原型をクリア
	ClearObjectModel();

	// オブジェクト用のモデル情報を取得
	ImportModelObject();

#ifdef _DEBUG

	g_PreObject.model = g_ObjectModel[0];	//!< 仮想のオブジェクト情報にモデル情報を1つセット(描画エラー回避)

#endif // _DEBUG
}

//************************************************
// オブジェクト破棄
//************************************************
void UninitObject(void)
{
	for (int i = 0; i < AMOUNT_MODEL_OBJECT; i++)
	{
		for (int j = 0; j < AMOUNT_MAT; j++)
		{
			if (g_ObjectModel[i].pTex[j] != NULL)
			{ // テクスチャの破棄
				g_ObjectModel[i].pTex[j]->Release();
				g_ObjectModel[i].pTex[j] = NULL;
			}
		}

		if (g_ObjectModel[i].pMesh != NULL)
		{ // メッシュの破棄
			g_ObjectModel[i].pMesh->Release();
			g_ObjectModel[i].pMesh = NULL;
		}

		if (g_ObjectModel[i].pBuffMat != NULL)
		{ // マテリアルの破棄
			g_ObjectModel[i].pBuffMat->Release();
			g_ObjectModel[i].pBuffMat = NULL;
		}
	}

	// ギズモ破棄
	UninitGizmoObject();
}

//************************************************
// オブジェクト更新
//************************************************
void UpdateObject(bool LayoutEdit)
{
#ifdef _DEBUG

	if (LayoutEdit)
	{ // 編集モードでなければ処理を行わない
		UpdateEditObject();
	}

#endif	// _DEBUG

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (!g_Object[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// 判定を更新
		UpdateAABB(i);

		// 被ダメ
		DamageObject(i);

		// 死亡？
		DeadObject(i);

		// 復活
		ResurrectObject(i);
	}

	// モードに関わらず既存オブジェクトは最後に行列計算
	CalcMtxObject();
}

//************************************************
// オブジェクト描画
//************************************************
void DrawObject(bool LayoutEdit)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;							// マテリアルデータへのポインタ

	for (int obj_id = 0; obj_id < AMOUNT_OBJECT; obj_id++)
	{
		if (!g_Object[obj_id].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Object[obj_id].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Object[obj_id].model.pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int mat_id = 0; mat_id < (int)g_Object[obj_id].model.NumMat; mat_id++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[mat_id].MatD3D);

			//テクスチャの設定
			if (g_Object[obj_id].model.pTex[mat_id] != NULL)
			{
				pDevice->SetTexture(0, g_Object[obj_id].model.pTex[mat_id]);
			}
			else
			{
				pDevice->SetTexture(0, NULL);
			}

			// オブジェクトパーツの描画
			g_Object[obj_id].model.pMesh->DrawSubset(mat_id);
		}

		// 保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

	/*--------------------------------------------*/

	//// ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &g_StageObject.mtxWorld);

	//// 現在のマテリアルを取得
	//pDevice->GetMaterial(&matDef);

	//// マテリアルデータへのポインタを取得
	//pMat = (D3DXMATERIAL*)g_StageObject.model.pBuffMat->GetBufferPointer();

	//// 法線の正規化
	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//// そのパーツの持つマテリアル分回す
	//for (int mat_id = 0; mat_id < (int)g_StageObject.model.NumMat; mat_id++)
	//{
	//	// マテリアルの設定
	//	pDevice->SetMaterial(&pMat[mat_id].MatD3D);

	//	//テクスチャの設定
	//	if (g_StageObject.model.pTex[mat_id] != NULL)
	//	{
	//		pDevice->SetTexture(0, g_StageObject.model.pTex[mat_id]);
	//	}
	//	else
	//	{
	//		pDevice->SetTexture(0, NULL);
	//	}

	//	// オブジェクトパーツの描画
	//	g_StageObject.model.pMesh->DrawSubset(mat_id);
	//}

	//// 法線の正規化
	//pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

	//// 保存していたマテリアルを戻す
	//pDevice->SetMaterial(&matDef);

#ifdef _DEBUG

	if (LayoutEdit)
	{
		// 仮想オブジェクトを描画
		if (!g_Overwrite)
		{
			DrawPreObject(0);
		}

		// ギズモを描画
		DrawPreObject(1);
	}

#endif	// _DEBUG
}

//************************************************
// オブジェクトの被弾
//************************************************
void HitObject(int id)
{
	if (g_Object[id].param.state == STATE_DAMAGE_OBJECT ||
		g_Object[id].param.state == STATE_DEAD_OBJECT)
	{ // 被弾？：死亡？状態なら被弾しない
		return;
	}

	// 被弾状態でなければ被弾
	g_Object[id].param.state = STATE_DAMAGE_OBJECT;	// 被弾状態に

	g_Object[id].param.dur = 15;	// 継続時間
	g_Object[id].param.HP--;

	// 体力ゲージを表示
	EnableObject_Bar(g_Object[id].param.HP, g_Object[id].id_bar, g_Object[id].pos);
}

//************************************************
// オブジェクト情報を取得
//************************************************
Object* GetInfoObject(void)
{
	return &g_Object[0];
}

//************************************************
// ギズモ情報を取得
//************************************************
Object* GetInfoGizmoObject(void)
{
	return &g_GizmoObject;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// オブジェクト情報をクリア
//************************************************
void ClearObject(void)
{
	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{ // オブジェクトの情報のリセット
		g_Object[i].use = false;
		g_Object[i].type = 0;
		g_Object[i].param = {};
		g_Object[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Object[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Object[i].size = { 0.0f, 0.0f, 0.0f };
		g_Object[i].model.pMesh = NULL;
		g_Object[i].model.pBuffMat = NULL;
		g_Object[i].model.NumMat = 0;
		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // テクスチャ情報のリセット
			g_Object[i].model.pTex[j] = NULL;
		}
		g_Object[i].model.aabb = {};
		g_Object[i].id_bar = 0;
		g_Object[i].id_shadow = 0;
		g_Object[i].id_box = 0;

		// 振動用情報もリセット
		g_ObjectMove[i] = { 0.0f, 0.0f, 0.0f };
	}
}

//************************************************
// 仮想のオブジェクトをクリア
//************************************************
void ClearPreObject(void)
{
	// 仮想のオブジェクトの情報のリセット
	g_PreObject.use = false;
	g_PreObject.type = 0;
	g_PreObject.param = {};
	g_PreObject.pos = { 0.0f, 0.0f, 0.0f };
	g_PreObject.rot = { 0.0f, 0.0f, 0.0f };
	g_PreObject.size = { 0.0f, 0.0f, 0.0f };
	g_PreObject.model.pMesh = NULL;
	g_PreObject.model.pBuffMat = NULL;
	g_PreObject.model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // テクスチャ情報をリセット
		g_PreObject.model.pTex[i] = NULL;
	}
	g_PreObject.model.aabb = {};
	g_PreObject.id_shadow = 0;
	g_PreObject.id_box = 0;
}

//************************************************
// ギズモモデル情報をクリア
//************************************************
void ClearGizmoObject(void)
{
	// ギズモ情報のリセット
	g_GizmoObject.use = false;
	g_GizmoObject.type = 0;
	g_GizmoObject.param = {};
	g_GizmoObject.pos = { 0.0f, 0.0f, 0.0f };
	g_GizmoObject.rot = { 0.0f, 0.0f, 0.0f };
	g_GizmoObject.size = { 0.0f, 0.0f, 0.0f };
	g_GizmoObject.model.pMesh = NULL;
	g_GizmoObject.model.pBuffMat = NULL;
	g_GizmoObject.model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // テクスチャ情報をリセット
		g_GizmoObject.model.pTex[i] = NULL;
	}
	g_GizmoObject.model.aabb = {};
	g_GizmoObject.id_shadow = 0;
	g_GizmoObject.id_box = 0;
}

////************************************************
//// ステージモデルの情報をクリア
////************************************************
//void ClearStageObject(void)
//{
//	// ステージ情報のリセット
//	g_StageObject.use = false;
//	g_StageObject.type = 0;
//	g_StageObject.param = {};
//	g_StageObject.pos = { 0.0f, 0.0f, 0.0f };
//	g_StageObject.rot = { 0.0f, 0.0f, 0.0f };
//	g_StageObject.size = { 0.0f, 0.0f, 0.0f };
//	g_StageObject.model.pMesh = NULL;
//	g_StageObject.model.pBuffMat = NULL;
//	g_StageObject.model.NumMat = 0;
//	for (int i = 0; i < AMOUNT_MAT; i++)
//	{ // テクスチャ情報をリセット
//		g_StageObject.model.pTex[i] = NULL;
//	}
//	g_StageObject.model.aabb = {};
//	g_StageObject.id_shadow = 0;
//	g_StageObject.id_box = 0;
//}

//************************************************
// オブジェクトモデル情報の原型をクリア
//************************************************
void ClearObjectModel(void)
{
	for (int i = 0; i < AMOUNT_MODEL_OBJECT; i++)
	{ // オブジェクト用モデル情報の原型のリセット
		g_ObjectModel[i].pMesh = NULL;
		g_ObjectModel[i].pBuffMat = NULL;
		g_ObjectModel[i].NumMat = 0;
		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // テクスチャの情報のリセット
			g_ObjectModel[i].pTex[j] = NULL;
		}
		g_ObjectModel[i].aabb = {};
	}
}

//************************************************
// オブジェクトモデル情報を読み込む
//************************************************
void ImportModelObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	int id_Model = 0;			// モデルの識別用

	/*--------------------------------------------*/

#ifdef OBJECT_EX

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_import_EX.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "オブジェクトモデル情報+αの展開に失敗");

#endif	// _DEBUG

		return;
	}

#else

	// モデル情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_import.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "オブジェクトモデル情報の展開に失敗");

#endif	// _DEBUG

		return;
	}

#endif	// OBJECT_EX

	/*--------------------------------------------*/

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "AMOUNT_MODEL") == 0)
		{
			// 読み込むモデル数を取得する
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%d", &g_MaxModel);
		}

#ifdef _DEBUG

		// エラー
		assert(g_MaxModel < AMOUNT_MODEL_OBJECT && "オブジェクトモデル情報が最大量を越えました");

#endif	// _DEBUG

		if (strcmp(&FileString[0], "MODEL_FILENAME") == 0)
		{
			// 読み込むモデル名を取得する
			fscanf_s(pFile, "%s", &FileString[0], 128);
			fscanf_s(pFile, "%s", &FileString[0], 128);

			// モデルからバウンディングボックスを形成する
			ImportModelBoxObject(id_Model, &FileString[0]);

			// 読み込んだ情報を原型にのみコピーする
			D3DXLoadMeshFromX(&FileString[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_ObjectModel[id_Model].pBuffMat,
				NULL,
				&g_ObjectModel[id_Model].NumMat,
				&g_ObjectModel[id_Model].pMesh);

			id_Model++; // パーツを進める

			if (id_Model == g_MaxModel)
			{ // 総モデル種類数分読み取り終わると終了
				break;
			}
		}
	}

	/*--------------------------------------------*/

	// 各モデルのテクスチャ情報を取得
	ImportTexObject();

	/*--------------------------------------------*/

	// 各モデルの配置情報を取得
#if OBJECT_EX 

	ImportLayoutObjectEX(pFile);

#else

	ImportLayoutObject(pFile);

#endif	// OBJECT_EX 

	// ファイルを閉じる
	fclose(pFile);

	// ステージモデルを読み込む
	//ImportStageModelObject();

	/*--------------------------------------------*/

#ifdef _DEBUG

	// ギズモモデルを読み込む
	ImportGizmoModelObject();

#endif
}

//************************************************
// バウンディングボックスを形成
//************************************************
void ImportModelBoxObject(int id, char* str)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char FileString[128] = {};	// 文章を格納
	char* result = nullptr;		// 分離した文章を格納
	int i = 0;					// 汎用整数
	D3DXVECTOR3 min = {};		// 最小地点格納
	D3DXVECTOR3 max = {};		// 最大地点格納
	D3DXVECTOR3 vec = {};		// 各軸へのベクトルを格納

	// 比較処理用に数値を入れておく
	min = { FLT_MAX, FLT_MAX, FLT_MAX };
	max = { FLT_MIN, FLT_MIN, FLT_MIN };

	// モデルそのものを展開する
	if (fopen_s(&pFile, str, "r") != 0)
	{
		return;
	}

	// 頂点情報を読み込み始めるところまでスキップ
	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "Mesh") == 0)
		{
			i++;	// ゴミを回避
		}

		if (i >= 2)
		{
			break;
		}
	}

	// 数値を比較していく
	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		int set = 0;						// いくつセットで区切るかカウント
		int len = strlen(&FileString[0]);	// 文字列の長さを取得

		for (i = 0; i < len; i++)
		{
			if (FileString[i] == ';')
			{ // 文字列が、区切り文字「;」を含んでいる数をカウント
				set++;
			}
		}

		// 区切り文字を3つ検出した場合のみ
		if (set == 3)
		{
			i = 0;	// 整数をリセット

			// 文字列から数値を抽出していく
			result = strtok(FileString, ";");
			vec.x = (float)atof(result);

			while (result != NULL)
			{
				result = strtok(NULL, ";");

				// 分解していく中で、取り出す数値は3つのみ
				switch (i)
				{
				case 0:
					vec.y = (float)atof(result);
					break;

				case 1:
					vec.z = (float)atof(result);
					break;
				}

				i++;
			}

			// 各軸の最大・最小地点を更新
			if (min.x > vec.x)
			{
				min.x = vec.x;
			}

			if (min.y > vec.y)
			{
				min.y = vec.y;
			}

			if (min.z > vec.z)
			{
				min.z = vec.z;
			}

			if (max.x < vec.x)
			{
				max.x = vec.x;
			}

			if (max.y < vec.y)
			{
				max.y = vec.y;
			}

			if (max.z < vec.z)
			{
				max.z = vec.z;
			}
		}

		// 区切り文字を4つ検出した場合のみ
		if (set == 4)
		{
			// 各軸の最大・最小を結ぶ線分の半径を保存
			vec =
			{
				(fabsf(min.x) + fabsf(max.x)) * 0.5f,
				(fabsf(min.y) + fabsf(max.y)) * 0.5f,
				(fabsf(min.z) + fabsf(max.z)) * 0.5f,
			};

			// ベクトルの情報をコピー
			g_ObjectModel[id].aabb.vec = vec;

			break;	// 比較処理終了
		}
	}

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// モデルテクスチャ情報を読み込む
//************************************************
void ImportTexObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int i = 0; i < g_MaxModel; i++)
	{
		// マテリアルデータへのポインタを取得
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_ObjectModel[i].pBuffMat->GetBufferPointer();

		// そのパーツの持つマテリアル分回す
		for (int j = 0; j < (int)g_ObjectModel[i].NumMat; j++)
		{
			// マテリアルにテクスチャが設定されていれば読込み
			if (pMat[j].pTextureFilename != NULL)
			{
				D3DXCreateTextureFromFileA(pDevice,
					pMat[j].pTextureFilename,
					&g_ObjectModel[i].pTex[j]);
			}
			else
			{
				g_ObjectModel[i].pTex[j] = NULL;
			}
		}
	}

	//D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_StageObject.model.pBuffMat->GetBufferPointer();

	//// そのパーツの持つマテリアル分回す
	//for (int i = 0; i < (int)g_StageObject.model.NumMat; i++)
	//{
	//	// マテリアルにテクスチャが設定されていれば読込み
	//	if (pMat[i].pTextureFilename != NULL)
	//	{
	//		D3DXCreateTextureFromFileA(pDevice,
	//			pMat[i].pTextureFilename,
	//			&g_StageObject.model.pTex[i]);
	//	}
	//	else
	//	{
	//		g_StageObject.model.pTex[i] = NULL;
	//	}
	//}
}

//************************************************
// モデル配置情報を読み込む
//************************************************
void ImportLayoutObject(FILE* pFile)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int Type = -1;				// モデルの種類格納
	D3DXVECTOR3 pos = {};		// 位置を格納
	D3DXVECTOR3 rot = {};		// 向き格納
	int id_Model = 0;			// モデルの識別用

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "TYPE") == 0)
		{ // このモデルの種類を取得	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%d", &Type);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置を取得	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きを取得	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);

			// 度数を弧度に変換
			rot = (rot * D3DX_PI) / 180.0f;
		}

		if (strcmp(&FileString[0], "END_MODELSET") == 0)
		{
#ifdef _DEBUG

			// エラー
			assert(Type != -1 && "オブジェクトモデルの種類情報の読込みに失敗");

#endif	// _DEBUG

			// 読み込んだ配置情報を該当順番のオブジェクトへコピーする
			g_Object[id_Model].use = true;
			g_Object[id_Model].type = Type;
			g_Object[id_Model].param.state = 0;
			g_Object[id_Model].pos = pos;
			g_Object[id_Model].rot = rot;

			VerifyTypeObject(id_Model);	// 種類の照合

			AdjustAABBObject(id_Model);	// AABBサイズの調整

#ifdef _DEBUG

			// 箱の判定の可視化
			g_Object[id_Model].id_box = CreateVisibleBox(&g_Object[id_Model].model.aabb, { 0.0f, 1.0f, 1.0f, 1.0f });

#endif // _DEBUG

			id_Model++; // コピーしたら次へ
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{ // 終了
			break;
		}
	}
}

//************************************************
// モデル配置情報+αを読み込む
//************************************************
void ImportLayoutObjectEX(FILE* pFile)
{
	// ファイルデータ読込み用
	char FileString[128] = {};	// 文章を格納
	int Type = -1;				// モデルの種類格納
	int hp = 0;					// 体力を格納
	int def = 0;				// 防御力を格納
	D3DXVECTOR3 pos = {};		// 位置を格納
	D3DXVECTOR3 rot = {};		// 向き格納
	int id_Model = 0;			// モデルの識別用

	while (fscanf_s(pFile, "%s", &FileString[0], 128) != EOF)
	{
		if (strcmp(&FileString[0], "TYPE") == 0)
		{ // このモデルの種類を取得	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%d", &Type);
		}

		if (strcmp(&FileString[0], "HP") == 0)
		{ // 体力を取得	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%d", &hp);
		}

		if (strcmp(&FileString[0], "DEF") == 0)
		{ // 防御力を取得	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%d", &def);
		}

		if (strcmp(&FileString[0], "POS") == 0)
		{ // 位置を取得	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&FileString[0], "ROT") == 0)
		{ // 向きを取得	
			fscanf_s(pFile, "%s", &FileString[0], 2);
			fscanf_s(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);

			// 度数を弧度に変換
			rot = (rot * D3DX_PI) / 180.0f;
		}

		if (strcmp(&FileString[0], "END_MODELSET") == 0)
		{
#ifdef _DEBUG

			// エラー
			assert(Type != -1 && "オブジェクトモデルの種類情報の読込みに失敗");

#endif	// _DEBUG

			// 読み込んだ配置情報を該当順番のオブジェクトへコピーする
			g_Object[id_Model].use = true;
			g_Object[id_Model].type = Type;
			g_Object[id_Model].param.state = 0;
			g_Object[id_Model].param.HP = 7;
			g_Object[id_Model].param.DEF = def;
			g_Object[id_Model].pos = pos;
			g_Object[id_Model].rot = rot;

			VerifyTypeObject(id_Model);	// 種類の照合

			// 体力ゲージの生成
			g_Object[id_Model].id_bar = CreateObject_Bar(g_Object[id_Model].param.HP);

			AdjustAABBObject(id_Model);	// AABBサイズの調整

#ifdef _DEBUG

			// 箱の判定の可視化
			if (Type == 9 ||
				Type == 10)
			{
				g_Object[id_Model].id_box = CreateVisibleBox(&g_Object[id_Model].model.aabb, { 0.5f, 0.0f, 0.5f, 1.0f });
			}
			else
			{
				g_Object[id_Model].id_box = CreateVisibleBox(&g_Object[id_Model].model.aabb, { 0.0f, 1.0f, 1.0f, 1.0f });
			}

#endif // _DEBUG

			id_Model++; // コピーしたら次へ
		}

		if (strcmp(&FileString[0], "END_SCRIPT") == 0)
		{ // 終了
			break;
		}
	}
}

//************************************************
// オブジェクト種類の照合
//************************************************
void VerifyTypeObject(int id_Model)
{
	for (int i = 0; i < g_MaxModel; i++)
	{
		if (g_Object[id_Model].type == i)
		{ // 各オブジェクトの種類を照合
			g_Object[id_Model].model = g_ObjectModel[i];	//!< 番号の一致しているモデル情報をコピー
		}
	}
}

//************************************************
// AABBサイズの調整
//************************************************
void AdjustAABBObject(int id_Model)
{
	// 次回の制作では修正します
	if (g_Object[id_Model].rot.y >= (D3DX_PI * 0.5f) * 0.5f &&
		g_Object[id_Model].rot.y <= (D3DX_PI * 1.5f) * 0.5f)
	{
		float copy = g_Object[id_Model].model.aabb.vec.x;
		g_Object[id_Model].model.aabb.vec.x = g_Object[id_Model].model.aabb.vec.z;
		g_Object[id_Model].model.aabb.vec.z = copy;
	}
	else if(g_Object[id_Model].rot.y <= (-D3DX_PI * 0.5f) * 0.5f &&
		g_Object[id_Model].rot.y >= (-D3DX_PI * 1.5f) * 0.5f)
	{
		float copy = g_Object[id_Model].model.aabb.vec.x;
		g_Object[id_Model].model.aabb.vec.x = g_Object[id_Model].model.aabb.vec.z;
		g_Object[id_Model].model.aabb.vec.z = copy;
	}
}

//************************************************
// ギズモモデル情報を読み込む
//************************************************
void ImportGizmoModelObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	D3DXLoadMeshFromX("data\\MODEL\\OBJECT\\Gizmo.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_GizmoObject.model.pBuffMat,
		NULL,
		&g_GizmoObject.model.NumMat,
		&g_GizmoObject.model.pMesh);
}

////************************************************
//// ステージモデル情報を読み込む
////************************************************
//void ImportStageModelObject(void)
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
//
//	D3DXLoadMeshFromX("data\\MODEL\\OBJECT\\con_stage.x",
//		D3DXMESH_SYSTEMMEM,
//		pDevice,
//		NULL,
//		&g_StageObject.model.pBuffMat,
//		NULL,
//		&g_StageObject.model.NumMat,
//		&g_StageObject.model.pMesh);
//
//	g_StageObject.use = true;
//	g_StageObject.pos = { 0.0f, 0.0f, 0.0f};
//}

//************************************************
// ギズモモデルの破棄
//************************************************
void UninitGizmoObject(void)
{
	if (g_GizmoObject.model.pMesh != NULL)
	{ // メッシュの破棄
		g_GizmoObject.model.pMesh->Release();
		g_GizmoObject.model.pMesh = NULL;
	}

	if (g_GizmoObject.model.pBuffMat != NULL)
	{ // マテリアルの破棄
		g_GizmoObject.model.pBuffMat->Release();
		g_GizmoObject.model.pBuffMat = NULL;
	}
}

////************************************************
//// ステージモデルの破棄
////************************************************
//void UninitStageObject(void)
//{
//	for (int i = 0; i < AMOUNT_MAT; i++)
//	{
//		if (g_StageObject.model.pTex[i] != NULL)
//		{ // テクスチャの破棄
//			g_StageObject.model.pTex[i]->Release();
//			g_StageObject.model.pTex[i] = NULL;
//		}
//	}
//
//	if (g_StageObject.model.pMesh != NULL)
//	{ // メッシュの破棄
//		g_StageObject.model.pMesh->Release();
//		g_StageObject.model.pMesh = NULL;
//	}
//
//	if (g_StageObject.model.pBuffMat != NULL)
//	{ // マテリアルの破棄
//		g_StageObject.model.pBuffMat->Release();
//		g_StageObject.model.pBuffMat = NULL;
//	}
//}

//************************************************
// 判定を更新
//************************************************
void UpdateAABB(int id)
{
	// 位置を同期
	g_Object[id].model.aabb.pos = g_Object[id].pos;

	// Y軸を補正
	g_Object[id].model.aabb.pos.y += g_Object[id].model.aabb.vec.y;
}

//************************************************
// 被ダメっぽく
//************************************************
void DamageObject(int id)
{
	if (g_Object[id].param.state != STATE_DAMAGE_OBJECT)
	{ // 被弾状態でなければ
		return;
	}

	// 震える
	int tf = rand() % 2;

	if (tf == 0)
	{
		g_ObjectMove[id].x += (float)(rand() % 5);
		g_ObjectMove[id].z += (float)(rand() % 5);
	}
	else
	{
		g_ObjectMove[id].x += -(float)(rand() % 5);
		g_ObjectMove[id].z += -(float)(rand() % 5);
	}

	// 振動移動制限
	if (g_ObjectMove[id].x > 10.0f)
	{
		g_ObjectMove[id].x = 10.0f;
	}
	else if (g_ObjectMove[id].x < -10.0f)
	{
		g_ObjectMove[id].x = -10.0f;
	}

	if (g_ObjectMove[id].z > 10.0f)
	{
		g_ObjectMove[id].z = 10.0f;
	}
	else if (g_ObjectMove[id].z < -10.0f)
	{
		g_ObjectMove[id].z = -10.0f;
	}

	// 継続時間減少
	g_Object[id].param.dur--;

	// 煙(大)エフェクト
	CreateEffect_Smoke(1, &g_Object[id].pos);

	if (g_Object[id].param.dur <= 0)
	{ // 期間終了で

		// 震えていたものをリセット
		if (g_ObjectMove[id].x != 0.0f)
		{
			g_ObjectMove[id].x = 0.0f;
		}
		else if (g_ObjectMove[id].z != 0.0f)
		{
			g_ObjectMove[id].z = 0.0f;
		}

		if (g_Object[id].param.HP <= 0)
		{ // 体力が完全に無くなっている場合

			// 死亡状態に変更する
			g_Object[id].param.state = STATE_DEAD_OBJECT;

			PlaySound(SOUND_LABEL_EXPLOSION_1);

			// ランダムなアイテムが出現
			int stran = rand() % 4;
			CreateItem(stran, g_Object[id].pos);
		}
		else
		{
			// 状態を通常に戻す
			g_Object[id].param.state = STATE_NORMAL_OBJECT;
		}
	}
}

//************************************************
// 壊れる感じ
//************************************************
void DeadObject(int id)
{
	if (g_Object[id].param.state != STATE_DEAD_OBJECT)
	{ // 死亡状態でなければ
		return;
	}

	// 震える
	int tf = rand() % 2;

	if (tf == 0)
	{
		g_ObjectMove[id].x += (float)(rand() % 5);
		g_ObjectMove[id].z += (float)(rand() % 5);
	}
	else
	{
		g_ObjectMove[id].x += -(float)(rand() % 5);
		g_ObjectMove[id].z += -(float)(rand() % 5);
	}

	// 振動移動制限
	if (g_ObjectMove[id].x > 10.0f)
	{
		g_ObjectMove[id].x = 10.0f;
	}
	else if (g_ObjectMove[id].x < -10.0f)
	{
		g_ObjectMove[id].x = -10.0f;
	}

	if (g_ObjectMove[id].z > 10.0f)
	{
		g_ObjectMove[id].z = 10.0f;
	}
	else if (g_ObjectMove[id].z < -10.0f)
	{
		g_ObjectMove[id].z = -10.0f;
	}

	// 沈降
	g_ObjectMove[id].y -= 3.0f;

	// 煙エフェクト
	CreateEffect_Smoke(0, &g_Object[id].pos);
	CreateEffect_Smoke(1, &g_Object[id].pos);

	for (int i = 0; i < AMOUNT_MODEL_OBJECT; i++)
	{
		if (g_Object[id].type != i)
		{ // モデルが一致していなければコンティニュー
			continue;
		}

		if ((g_Object[id].pos.y + g_ObjectMove[id].y) + (g_ObjectModel[i].aabb.vec.y * 2.0f) < -5.0f)
		{ // モデルのてっぺんが地面の下に沈むと

			// 使用しない
			DeadDeleteObject(id);
		}
	}
}

//************************************************
// 選択式でない消去
//************************************************
void DeadDeleteObject(int id)
{
#ifdef _DEBUG

	// 箱の可視化を消去
	DeleteVisibleBox(g_Object[id].id_box);

#endif // _DEBUG

	// オブジェクトの情報のリセット
	g_Object[id].use = false;
	g_Object[id].type = 0;
	g_Object[id].param = {};
	//g_Object[id].pos = { 0.0f, 0.0f, 0.0f };	// 煙エフェクト用に位置だけは…
	g_Object[id].rot = { 0.0f, 0.0f, 0.0f };
	g_Object[id].size = { 0.0f, 0.0f, 0.0f };
	g_Object[id].model.pMesh = NULL;
	g_Object[id].model.pBuffMat = NULL;
	g_Object[id].model.NumMat = 0;
	for (int i = 0; i < AMOUNT_MAT; i++)
	{ // テクスチャ情報のリセット
		g_ObjectModel[id].pTex[i] = NULL;
	}
	g_Object[id].model.aabb = {};
	g_Object[id].id_bar = 0;
	g_Object[id].id_shadow = 0;
	g_Object[id].id_box = 0;
}

//************************************************
// 復活
//************************************************
void ResurrectObject(int id)
{
	// 引数の未参照に警告が出るのを抑制
	g_Object[id];
}

//************************************************
// エディットモード時の更新
//************************************************
void UpdateEditObject(void)
{
#ifdef _DEBUG

	Object* pObject = nullptr;	// 仮想・既存オブジェクト識別用
	int Loop = 1;				// 汎用ループ回数

	// 移動モードを変更する
	if (GetKeyboardTrigger(DIK_F4))
	{
		g_TrackAA = !g_TrackAA;
	}

	// 編集モードを変更する
	if (GetKeyboardTrigger(DIK_F5))
	{
		g_Overwrite = !g_Overwrite;
	}

	// 現在の配置モデル数を取得
	g_MaxObject = GetInfoMaxObject();

	if (GetKeyboardPress(DIK_SPACE))
	{ // 押下で移動や回転の速度上昇
		Loop = 4;
	}

	/*--------------------------------------------*/

	// モードに応じて取得するオブジェクトを識別する
	if (g_Overwrite)
	{
		pObject = &g_Object[g_obj_id];
	}
	else
	{
		pObject = &g_PreObject;
	}

	// 既存のオブジェクトを削除
	DeleteObject();

	// 対象の変更
	ChangeTargetObject();

	// 種類を変更
	ChangeTypeObject(pObject);

#if OBJECT_EX

	// 体力を変更
	ChangeHPObject(pObject);

	// 防御力を変更
	ChangeDEFObject(pObject);

#endif	// OBJECT_EX

	// トランスフォーム
	for (int i = 0; i < Loop; i++)
	{
		// オブジェクトの回転
		RotateObject(pObject);

		// オブジェクトの移動
		TranslateObject(pObject);
	}

	// 仮想オブジェクトを保存
	SavePreObject();

	// ギズモモデルを追従
	TrackGizmoObject(pObject);

	// 最後に行列算
	CalcMtxPreObject(0);	// 仮想オブジェクト
	CalcMtxPreObject(1);	// ギズモモデル

	// モデルの配置情報を保存する
	if (GetKeyboardTrigger(DIK_F3))
	{
#if OBJECT_EX 

		ExportLayoutObjectEX();

#else

		ExportLayoutObject();

#endif	// OBJECT_EX 
	}


	// デバッグ表示
#if OBJECT_EX 

	PrintDebugObjectEX();

#else

	PrintDebugObject();

#endif	// OBJECT_EX 

#endif	// _DEBUG
}

//************************************************
// 現在の配置モデル数を取得
//************************************************
int GetInfoMaxObject(void)
{
	int value = 0;	// カウント用

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (g_Object[i].use)
		{ // 使用されていればカウント
			value++;
		}
	}

	return value;
}

//************************************************
// 既存オブジェクトを消去
//************************************************
void DeleteObject(void)
{
#ifdef _DEBUG

	int i = g_obj_id;	// 識別簡略化

	if (g_Overwrite && GetKeyboardTrigger(DIK_BACK))
	{
		// 箱の可視化を消去
		DeleteVisibleBox(g_Object[i].id_box);

		// オブジェクトの情報のリセット
		g_Object[i].use = false;
		g_Object[i].type = 0;
		g_Object[i].param = {};
		g_Object[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Object[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Object[i].size = { 0.0f, 0.0f, 0.0f };
		g_Object[i].model.pMesh = NULL;
		g_Object[i].model.pBuffMat = NULL;
		g_Object[i].model.NumMat = 0;
		for (int j = 0; j < AMOUNT_MAT; j++)
		{ // テクスチャ情報のリセット
			g_Object[i].model.pTex[j] = NULL;
		}
		g_Object[i].model.aabb = {};
		g_Object[i].id_bar = 0;
		g_Object[i].id_shadow = 0;
		g_Object[i].id_box = 0;

		if (g_obj_id == g_MaxObject)
		{ // 消去予定の番が最高番の場合、選択を1つ戻しておく
			g_obj_id = g_MaxObject - 1;
		}
	}

	// 配列をソート
	SortArrayObject();

#endif	// _DEBUG
}

//************************************************
// 既存オブジェクトをソート
//************************************************
void SortArrayObject(void)
{
	for (int i = 0; i < AMOUNT_OBJECT - 1; i++)
	{
		if (!g_Object[i].use && g_Object[i + 1].use)
		{ // この番が未使用で、次の番が使用中の場合

			// 情報を反転させていく
			Object object = g_Object[i];
			g_Object[i] = g_Object[i + 1];
			g_Object[i + 1] = object;
		}
	}
}

//************************************************
// 対象を変更
//************************************************
void ChangeTargetObject(void)
{
#ifdef _DEBUG

	if (g_Overwrite)
	{ // 上書きモード時のみ
		if (GetKeyboardTrigger(DIK_PERIOD))
		{
			g_obj_id < g_MaxObject - 1 ? g_obj_id++ : g_obj_id = 0;
		}
		else if (GetKeyboardTrigger(DIK_COMMA))
		{
			g_obj_id > 0 ? g_obj_id-- : g_obj_id = g_MaxObject - 1;
		}

		if (GetKeyboardPress(DIK_Z))
		{
			g_obj_id < g_MaxObject - 1 ? g_obj_id++ : g_obj_id = 0;
		}
		else if (GetKeyboardPress(DIK_X))
		{
			g_obj_id > 0 ? g_obj_id-- : g_obj_id = g_MaxObject - 1;
		}
	}

#endif	// _DEBUG
}

//************************************************
// 種類を変更
//************************************************
void ChangeTypeObject(Object* pObject)
{
#ifdef _DEBUG

	// 種類の変更
	if (GetKeyboardTrigger(DIK_RSHIFT))
	{
		pObject->type < g_MaxModel - 1 ? pObject->type++ : pObject->type = 0;

		g_Overwrite ? VerifyTypeObject(g_obj_id) : VerifyTypePreObject();
	}
	else if (GetKeyboardTrigger(DIK_LSHIFT))
	{
		pObject->type > 0 ? pObject->type-- : pObject->type = g_MaxModel - 1;

		g_Overwrite ? VerifyTypeObject(g_obj_id) : VerifyTypePreObject();
	}

	assert(pObject->type >= 0 && pObject->type < g_MaxModel && "オブジェクトモデルの種類の変更失敗");

#endif // _DEBUG
}

//************************************************
// 体力を変更
//************************************************
void ChangeHPObject(Object* pObject)
{
#ifdef _DEBUG

	// 体力の変更
	if (GetKeyboardTrigger(DIK_Q) && pObject->param.HP > 0)
	{
		pObject->param.HP--;
	}
	else if (GetKeyboardTrigger(DIK_E))
	{
		pObject->param.HP++;
	}

#endif // _DEBUG
}

//************************************************
// 防御力を変更
//************************************************
void ChangeDEFObject(Object* pObject)
{
#ifdef _DEBUG

	// 防御力の変更
	if (GetKeyboardTrigger(DIK_Z) && pObject->param.DEF > 0)
	{
		pObject->param.DEF--;
	}
	else if (GetKeyboardTrigger(DIK_C))
	{
		pObject->param.DEF++;
	}

#endif // _DEBUG
}

//************************************************
// 種類の照合(仮想)
//************************************************
void VerifyTypePreObject(void)
{
	for (int i = 0; i < g_MaxModel; i++)
	{
		if (g_PreObject.type == i)
		{ // 各仮想オブジェクトの種類を照合
			g_PreObject.model = g_ObjectModel[i];	//!< 番号の一致しているモデル情報をコピー
		}
	}
}

//************************************************
// オブジェクトの回転
//************************************************
void RotateObject(Object* pObject)
{
#ifdef _DEBUG

	// X軸に回転
	if (GetKeyboardPress(DIK_R))
	{
		pObject->rot.x += 0.01f;
	}
	else if (GetKeyboardPress(DIK_F))
	{
		pObject->rot.x -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_V))
	{
		pObject->rot.x = 0.0f;
	}

	// Y軸に回転
	if (GetKeyboardPress(DIK_T))
	{
		pObject->rot.y += 0.01f;
	}
	else if (GetKeyboardPress(DIK_G))
	{
		pObject->rot.y -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_B))
	{
		pObject->rot.y = 0.0f;
	}

	// Z軸に回転
	if (GetKeyboardPress(DIK_Y))
	{
		pObject->rot.z += 0.01f;
	}
	else if (GetKeyboardPress(DIK_H))
	{
		pObject->rot.z -= 0.01f;
	}
	else if (GetKeyboardTrigger(DIK_N))
	{
		pObject->rot.z = 0.0f;
	}

	// X軸に一定値
	if (GetKeyboardTrigger(DIK_U))
	{
		pObject->rot.x += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_J))
	{
		pObject->rot.x -= D3DX_PI * 0.025f;
	}

	// Y軸に一定値
	if (GetKeyboardTrigger(DIK_I))
	{
		pObject->rot.y += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_K))
	{
		pObject->rot.y -= D3DX_PI * 0.025f;
	}

	// Z軸に一定値
	if (GetKeyboardTrigger(DIK_O))
	{
		pObject->rot.z += D3DX_PI * 0.025f;
	}
	else if (GetKeyboardTrigger(DIK_L))
	{
		pObject->rot.z -= D3DX_PI * 0.025f;
	}

#endif	// _DEBUG
}

//************************************************
// オブジェクトの移動
//************************************************
void TranslateObject(Object* pObject)
{
#ifdef _DEBUG

	bool move = false;
	float X = 0.0f;
	float Z = 0.0f;
	const EditCamera* pCamera = GetInfoEditCamera();

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
		pObject->pos.y += 1.0f;
	}
	else if (GetKeyboardPress(DIK_RBRACKET))
	{
		pObject->pos.y -= 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_YEN))
	{
		pObject->pos.y = 0.0f;
	}

	// intへのキャストを利用して小数部分を切り捨てるため警告無効化
#pragma warning(disable:4244)

	// 端数調整
	if (GetKeyboardTrigger(DIK_MINUS))
	{
		pObject->pos.x = (int)pObject->pos.x;
	}
	else if (GetKeyboardTrigger(DIK_CIRCUMFLEX))
	{
		pObject->pos.z = (int)pObject->pos.z;
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
		pObject->pos.y += 1.0f;
	}
	else if (GetKeyboardTrigger(DIK_NUMPAD0))
	{
		pObject->pos.y -= 1.0f;
	}

	if (X != 0.0f || Z != 0.0f)
	{ // 何かを入力していれば移動している判定
		move = true;
	}

	if (move)
	{
		// 移動量と目標方角を設定
		if (g_TrackAA)
		{
			pObject->pos.x += sinf(atan2f(X, Z));
			pObject->pos.z += cosf(atan2f(X, Z));
		}
		else
		{
			pObject->pos.x += sinf(atan2f(X, Z) + pCamera->rot.y);
			pObject->pos.z += cosf(atan2f(X, Z) + pCamera->rot.y);
		}
	}

#endif	// _DEBUG
}

//************************************************
// 仮想オブジェクトを保存
//************************************************
void SavePreObject(void)
{
#ifdef _DEBUG

	// 仮想のオブジェクトを、通常オブジェクトとして配置
	if (!g_Overwrite && GetKeyboardTrigger(DIK_RETURN))
	{
		for (int i = 0; i < AMOUNT_OBJECT; i++)
		{
			if (g_Object[i].use)
			{ // 使用されていればコンティニュー
				continue;
			}

			g_Object[i] = g_PreObject;	// 新たに情報を保存

			g_Object[i].use = true;		// このモデルの使用判定を出す

			// 箱の判定を可視化
			g_Object[i].id_box = CreateVisibleBox(&g_Object[i].model.aabb, { 0.0f, 1.0f, 1.0f, 1.0f });

			break;
		}
	}

#endif // _DEBUG
}

//************************************************
// ギズモモデルを追従
//************************************************
void TrackGizmoObject(Object* pObject)
{
#ifdef _DEBUG

	EditCamera* pEditCamera = GetInfoEditCamera();	// 編集カメラ情報取得

	// 既存位置にギズモを付属
	g_GizmoObject.pos = pObject->pos;

	// 既存向きにギズモを付属
	if (!g_TrackAA)
	{ // 直交モード時のみ
		g_GizmoObject.rot.y = pEditCamera->rot.y;
	}
	else
	{
		if (g_GizmoObject.rot.y != 0.0f)
		{
			g_GizmoObject.rot.y = 0.0f;
		}
	}

#endif	// _DEBUG
}

//************************************************
// 既存オブジェクト用マトリックスの計算
//************************************************
void CalcMtxObject(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	// 計算用マトリックス

	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (!g_Object[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Object[i].mtxWorld);

		// 向きを反映1
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			g_Object[i].rot.y,
			g_Object[i].rot.x,
			g_Object[i].rot.z);

		// 向きを反映2
		D3DXMatrixMultiply(&g_Object[i].mtxWorld,
			&g_Object[i].mtxWorld,
			&mtxRot);

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Object[i].pos.x + g_ObjectMove[i].x,
			g_Object[i].pos.y + g_ObjectMove[i].y,
			g_Object[i].pos.z + g_ObjectMove[i].z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Object[i].mtxWorld,
			&g_Object[i].mtxWorld,
			&mtxTrans);
	}

	// ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&g_StageObject.mtxWorld);

	////スケールを変更1
	//D3DXMatrixScaling(&mtxScale,
	//	g_StageObject.size.x + 18.0f,
	//	g_StageObject.size.y + 18.0f,
	//	g_StageObject.size.z + 18.0f);

	////スケールを変更2
	//D3DXMatrixMultiply(&g_StageObject.mtxWorld,
	//	&g_StageObject.mtxWorld,
	//	&mtxScale);

	//// 位置を反映1
	//D3DXMatrixTranslation(&mtxTrans,
	//	g_StageObject.pos.x,
	//	g_StageObject.pos.y - 1992.5f,
	//	g_StageObject.pos.z);

	//// 位置を反映2
	//D3DXMatrixMultiply(&g_StageObject.mtxWorld,
	//	&g_StageObject.mtxWorld,
	//	&mtxTrans);
}

//************************************************
// 仮想オブジェクト用マトリックスの計算
//************************************************
void CalcMtxPreObject(int mode)
{
#ifdef _DEBUG

	//LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;		// 計算用マトリックス
	Object* pObject = nullptr;

	switch (mode)
	{
	case 0:

		// 仮想オブジェクト
		pObject = &g_PreObject;

		break;

	case 1:

		// ギズモモデル
		pObject = &g_GizmoObject;

		break;

	default:

		// エラー
		assert(false && "仮想オブジェクトのマトリックス計算異常");

		break;
	}

	/*--------------------------------------------*/

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&pObject->mtxWorld);

	if (mode == 1)
	{ // ギズモモードの場合ズーム率に合わせて拡縮
		EditCamera* pEditCamera = GetInfoEditCamera();	// 編集カメラ情報取得

		// 距離を取得
		float DistanceSize = (pEditCamera->distance * 0.005f);

		//スケールを変更1
		D3DXMatrixScaling(&mtxScale,
			pObject->size.x + DistanceSize,
			pObject->size.y + DistanceSize,
			pObject->size.z + DistanceSize);

		//スケールを変更2
		D3DXMatrixMultiply(&pObject->mtxWorld,
			&pObject->mtxWorld,
			&mtxScale);
	}

	// 向きを反映1
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		pObject->rot.y,
		pObject->rot.x,
		pObject->rot.z);

	// 向きを反映2
	D3DXMatrixMultiply(&pObject->mtxWorld,
		&pObject->mtxWorld,
		&mtxRot);

	// 位置を反映1
	D3DXMatrixTranslation(&mtxTrans,
		pObject->pos.x,
		pObject->pos.y,
		pObject->pos.z);

	// 位置を反映2
	D3DXMatrixMultiply(&pObject->mtxWorld,
		&pObject->mtxWorld,
		&mtxTrans);

#endif // _DEBUG
}

//************************************************
// 仮想のオブジェクト描画
//************************************************
void DrawPreObject(int mode)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	Object* pObject = nullptr;

	switch (mode)
	{
	case 0:

		// 仮想オブジェクト
		pObject = &g_PreObject;

		break;

	case 1:

		// ギズモ
		pObject = &g_GizmoObject;

		//Z位置の比較方法の変更
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	// 常に深度テストに合格

		break;

	default:

#ifdef _DEBUG

		// エラー
		assert(false && "仮想オブジェクトの描画モード異常");

#endif	// _DEBUG

		break;
	}

	/*--------------------------------------------*/

	D3DMATERIAL9 matDef;							// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;								// マテリアルデータへのポインタ

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &pObject->mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pObject->model.pBuffMat->GetBufferPointer();

	// そのパーツの持つマテリアル分回す
	for (int i = 0; i < (int)pObject->model.NumMat; i++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//テクスチャの設定
		if (pObject->model.pTex[i] != NULL)
		{
			pDevice->SetTexture(0, pObject->model.pTex[i]);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		// オブジェクトパーツの描画
		pObject->model.pMesh->DrawSubset(i);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	if (mode == 1)
	{ // ギズモ描画モードの場合
		//Z位置の比較方法の修正
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}

//************************************************
// モデル配置情報を保存する
//************************************************
void ExportLayoutObject(void)
{
	FILE* pFile = NULL;
	D3DXVECTOR3 rot = {};	// 計算用

	// 保存するファイルを用意
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_export.txt", "w") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "オブジェクトモデル配置保存用のファイルの用意に失敗");

#else

		return;

#endif	// _DEBUG
	}

	// ビューワーで使いまわしやすいフォーマットで書き出しておく…
	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# モデル配置情報\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");

	// モデルの種類、位置、向きを、置いた分だけ書き出す
	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (!g_Object[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// 弧度を度数に変換
		rot = (g_Object[i].rot * 180.0f) / D3DX_PI;

		fprintf(pFile, "MODELSET\n");
		fprintf(pFile, "	TYPE = %d\n", g_Object[i].type);
		fprintf(pFile, "	POS = %.1f %.1f %.1f\n", g_Object[i].pos.x, g_Object[i].pos.y, g_Object[i].pos.z);
		fprintf(pFile, "	ROT = %.1f %.1f %.1f\n", rot.x, rot.y, rot.z);
		fprintf(pFile, "END_MODELSET\n\n");
	}

	// 終了
	fprintf(pFile, "END_SCRIPT\n");

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// モデル配置情報+αを保存する
//************************************************
void ExportLayoutObjectEX(void)
{
	FILE* pFile = NULL;
	D3DXVECTOR3 rot = {};	// 計算用

	// 保存するファイルを用意
	if (fopen_s(&pFile, "data\\TXT\\OBJECT\\model_export_EX.txt", "w") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "オブジェクトモデル配置+α保存用のファイルの用意に失敗");

#else

		return;

#endif	// _DEBUG
	}

	// ビューワーで使いまわしやすいフォーマットで書き出しておく…
	fprintf(pFile, "#------------------------------------------------------------------------------\n");
	fprintf(pFile, "# モデル配置情報\n");
	fprintf(pFile, "#------------------------------------------------------------------------------\n");

	// モデルの種類、位置、向きを、置いた分だけ書き出す
	for (int i = 0; i < AMOUNT_OBJECT; i++)
	{
		if (!g_Object[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// 弧度を度数に変換
		rot = (g_Object[i].rot * 180.0f) / D3DX_PI;

		fprintf(pFile, "MODELSET\n");
		fprintf(pFile, "	TYPE = %d\n", g_Object[i].type);
		fprintf(pFile, "	HP = %d\n", g_Object[i].param.HP);
		fprintf(pFile, "	DEF = %d\n", g_Object[i].param.DEF);
		fprintf(pFile, "	POS = %.1f %.1f %.1f\n", g_Object[i].pos.x, g_Object[i].pos.y, g_Object[i].pos.z);
		fprintf(pFile, "	ROT = %.1f %.1f %.1f\n", rot.x, rot.y, rot.z);
		fprintf(pFile, "END_MODELSET\n\n");
	}

	// 終了
	fprintf(pFile, "END_SCRIPT\n");

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// オブジェクトの情報をデバッグ表示
//************************************************
void PrintDebugObject(void)
{
#ifdef _DEBUG

	char Test[32] = {};	// 汎用文字列

	PrintDebugProc("\n　【オブジェクト情報】\n");
	PrintDebugProc("━━━━━━━━━━━\n");

	g_TrackAA ? sprintf(Test, "軸平行") : sprintf(Test, "カメラ");

	PrintDebugProc("　移動モード：[ %s ]\n", &Test[0]);
	PrintDebugProc("━━━━━━━━━━━\n");

	g_Overwrite ? sprintf(Test, "上書き") : sprintf(Test, "通常");

	PrintDebugProc("　編集モード：[ %s ] \n", &Test[0]);
	PrintDebugProc("━━━━━━━━━━━\n");

	PrintDebugProc("　モデルの配置数：%d\n\n", g_MaxObject);

	if (!g_Overwrite)
	{
		PrintDebugProc("　モデルの種類：%d\n\n", g_PreObject.type);
		PrintDebugProc("　位置：%f %f %f\n", g_PreObject.pos.x, g_PreObject.pos.y, g_PreObject.pos.z);
		PrintDebugProc("　向き：%f %f %f\n", g_PreObject.rot.x, g_PreObject.rot.y, g_PreObject.rot.z);
	}
	else
	{
		PrintDebugProc("　現在の選択：(%d)：%d\n\n", g_MaxObject, g_obj_id);
		PrintDebugProc("　モデルの種類：%d\n\n", g_Object[g_obj_id].type);
		PrintDebugProc("　位置：%f %f %f\n", g_Object[g_obj_id].pos.x, g_Object[g_obj_id].pos.y, g_Object[g_obj_id].pos.z);
		PrintDebugProc("　向き：%f %f %f\n", g_Object[g_obj_id].rot.x, g_Object[g_obj_id].rot.y, g_Object[g_obj_id].rot.z);
	}

	PrintDebugProc("━━━━━━━━━━━\n");

#endif	// _DEBUG
}

//************************************************
// オブジェクトの情報をデバッグ表示+α
//************************************************
void PrintDebugObjectEX(void)
{
#ifdef _DEBUG

	char Test[32] = {};	// 汎用文字列

	PrintDebugProc("\n　【オブジェクト情報+α】\n");
	PrintDebugProc("━━━━━━━━━━━\n");

	g_TrackAA ? sprintf(Test, "軸平行") : sprintf(Test, "カメラ");

	PrintDebugProc("　移動モード：[ %s ]\n", &Test[0]);
	PrintDebugProc("━━━━━━━━━━━\n");

	g_Overwrite ? sprintf(Test, "上書き") : sprintf(Test, "通常");

	PrintDebugProc("　編集モード：[ %s ] \n", &Test[0]);
	PrintDebugProc("━━━━━━━━━━━\n");

	PrintDebugProc("　モデルの配置数：%d\n\n", g_MaxObject);

	if (!g_Overwrite)
	{
		PrintDebugProc("　モデルの種類：%d\n\n", g_PreObject.type);
		PrintDebugProc("　体力：%d\n", g_PreObject.param.HP);
		PrintDebugProc("　防御力：%d\n\n", g_PreObject.param.DEF);
		PrintDebugProc("　位置：%f %f %f\n", g_PreObject.pos.x, g_PreObject.pos.y, g_PreObject.pos.z);
		PrintDebugProc("　向き：%f %f %f\n", g_PreObject.rot.x, g_PreObject.rot.y, g_PreObject.rot.z);
	}
	else
	{
		PrintDebugProc("　現在の選択：(%d)：%d\n\n", g_MaxObject, g_obj_id);
		PrintDebugProc("　モデルの種類：%d\n\n", g_Object[g_obj_id].type);
		PrintDebugProc("　体力：%d\n", g_Object[g_obj_id].param.HP);
		PrintDebugProc("　防御力：%d\n\n", g_Object[g_obj_id].param.DEF);
		PrintDebugProc("　位置：%f %f %f\n", g_Object[g_obj_id].pos.x, g_Object[g_obj_id].pos.y, g_Object[g_obj_id].pos.z);
		PrintDebugProc("　向き：%f %f %f\n", g_Object[g_obj_id].rot.x, g_Object[g_obj_id].rot.y, g_Object[g_obj_id].rot.z);
	}

	PrintDebugProc("━━━━━━━━━━━\n");

#endif	// _DEBUG
}

/*---【拡張】---*/

//************************************************
// 仮
//************************************************
//void ooooo(void)
//{
//	// モデルのタイプが特定のとき
//
//	// プレイヤーの誰かが
//	
//	// 一定範囲に近づいているなら
//
//	// 弾薬補給
//}