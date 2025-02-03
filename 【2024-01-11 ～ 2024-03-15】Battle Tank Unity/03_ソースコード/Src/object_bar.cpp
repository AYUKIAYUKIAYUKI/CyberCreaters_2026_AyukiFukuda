//************************************************
//
// 構造物の体力ゲージ[object_bar.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "object_bar.h"

// システム系
#include "sound.h"

// 諸処理
#include "game.h"

// デバッグ用
#ifdef _DEBUG
#include "debugproc.h"
#include <assert.h>
#endif // _DEBUG

/*---【マクロ定義】---*/
#define MAX_OBJECT_BAR 512	// 構造物の体力ゲージの最大数

/*---【グローバル変数】---*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObject_Bar = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureObject_Bar = NULL;			// テクスチャへのポインタ
Object_Bar g_Object_Bar[MAX_OBJECT_BAR];				// 構造物の体力ゲージ情報

/*---【プロトタイプ宣言】---*/

// 初期
void ImportTexObject_Bar(void);			// テクスチャ取得
void CreateVtxBufferObject_Bar(void);	// 頂点情報を生成

// 更新
void SetVtxObject_Bar(void);	// 展開

void DeleteObject_Bar(int id);	// 消去

//************************************************
// 初期処理
//************************************************
void InitObject_Bar(void)
{
	for (int i = 0; i < MAX_OBJECT_BAR; i++)
	{ // 構造物の体力ゲージ情報リセット

		g_Object_Bar[i].use = false;								// 使用フラグ
		g_Object_Bar[i].dur = 0;									// 寿命
		g_Object_Bar[i].pos = { 0.0f, 0.0f, 0.0f };					// 位置
		g_Object_Bar[i].move = { 0.0f, 0.0f, 0.0f };				// 移動量
		g_Object_Bar[i].rot = { 0.0f, 0.0f, 0.0f };					// 向き
		g_Object_Bar[i].span = { 0.0f, 0.0f };						// 大きさ用
		g_Object_Bar[i].HPspan = 0.0f;								// 体力の大きさ割合
		g_Object_Bar[i].angle = 0.0f;								// 角度
		g_Object_Bar[i].length = 0.0f;								// 対角線用
		g_Object_Bar[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
		g_Object_Bar[i].HPcol = 0.0f;								// 体力の色割合
	}

	/*--------------------------------------------*/

	// テクスチャ情報を取得
	ImportTexObject_Bar();

	// 頂点情報を生成
	CreateVtxBufferObject_Bar();
}

//************************************************
// テクスチャ情報を読み込む
//************************************************
void ImportTexObject_Bar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	// テクスチャ画像の読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\bright.png",
		&g_pTextureObject_Bar);
}

//************************************************
// 頂点情報を生成
//************************************************
void CreateVtxBufferObject_Bar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * MAX_OBJECT_BAR,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffObject_Bar,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffObject_Bar->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_OBJECT_BAR; i++, pVtx += AMOUNT_VTX)
	{ // 頂点情報のリセット

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffObject_Bar->Unlock();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// 終了処理
//************************************************
void UninitObject_Bar(void)
{
	if (g_pTextureObject_Bar != NULL)
	{ // テクスチャの破棄

		g_pTextureObject_Bar->Release();
		g_pTextureObject_Bar = NULL;
	}

	if (g_pVtxBuffObject_Bar != NULL)
	{ // 頂点バッファの破棄

		g_pVtxBuffObject_Bar->Release();
		g_pVtxBuffObject_Bar = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// 更新処理
//************************************************
void UpdateObject_Bar(void)
{
	for (int i = 0; i < MAX_OBJECT_BAR; i++)
	{
		if (g_Object_Bar[i].dur <= 0)
		{ // 継続時間が無ければコンティニュー

			continue;
		}

		// 残存期間更新
		CntDuration(&g_Object_Bar[i].dur);
	}

	// ポリゴンを展開
	SetVtxObject_Bar();
}

//************************************************
// 構造物の体力ゲージ消去
//************************************************
void DeleteObject_Bar(int id)
{
	g_Object_Bar[id].use = false;								// 使用フラグ
	g_Object_Bar[id].dur = 0;									// 寿命
	g_Object_Bar[id].pos = { 0.0f, 0.0f, 0.0f };				// 位置
	g_Object_Bar[id].move = { 0.0f, 0.0f, 0.0f };				// 移動量
	g_Object_Bar[id].rot = { 0.0f, 0.0f, 0.0f };				// 向き
	g_Object_Bar[id].span = { 0.0f, 0.0f };						// 大きさ用
	g_Object_Bar[id].HPspan = 0.0f;								// 体力の大きさ割合
	g_Object_Bar[id].angle = 0.0f;								// 角度
	g_Object_Bar[id].length = 0.0f;								// 対角線用
	g_Object_Bar[id].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	g_Object_Bar[id].HPcol = 0.0f;								// 体力の色割合
}

//************************************************
// 構造物の体力ゲージ展開
//************************************************
void SetVtxObject_Bar(void)
{
	VERTEX_3D* pVtx;		// 頂点情報のポインタ
	TextureSize tex = {};	// テクスチャサイズ

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_OBJECT_BAR; i++)
	{ // 頂点位置用の情報を算出

		if (g_Object_Bar[i].dur <= 0)
		{ // 継続時間が無ければコンティニュー

			continue;
		}

		// 角度を算出
		g_Object_Bar[i].angle = atan2f(g_Object_Bar[i].span.x, g_Object_Bar[i].span.y);

		// 対角線を算出
		g_Object_Bar[i].length = sqrtf(g_Object_Bar[i].span.x * g_Object_Bar[i].span.x + g_Object_Bar[i].span.y * g_Object_Bar[i].span.y);
	}

	/*--------------------------------------------*/

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffObject_Bar->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_OBJECT_BAR; i++, pVtx += AMOUNT_VTX)
	{
		if (g_Object_Bar[i].dur <= 0)
		{ // 継続時間が無ければコンティニュー

			continue;
		}

		// 頂点の展開
		pVtx[0].pos =
		{
			sinf(g_Object_Bar[i].rot.z - (D3DX_PI - g_Object_Bar[i].angle)) * g_Object_Bar[i].length,
			-cosf(g_Object_Bar[i].rot.z - (D3DX_PI - g_Object_Bar[i].angle)) * g_Object_Bar[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			sinf(g_Object_Bar[i].rot.z + (D3DX_PI - g_Object_Bar[i].angle)) * g_Object_Bar[i].length,
			-cosf(g_Object_Bar[i].rot.z + (D3DX_PI - g_Object_Bar[i].angle)) * g_Object_Bar[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			sinf(g_Object_Bar[i].rot.z - g_Object_Bar[i].angle) * g_Object_Bar[i].length,
			-cosf(g_Object_Bar[i].rot.z - g_Object_Bar[i].angle) * g_Object_Bar[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			sinf(g_Object_Bar[i].rot.z + g_Object_Bar[i].angle) * g_Object_Bar[i].length,
			-cosf(g_Object_Bar[i].rot.z + g_Object_Bar[i].angle) * g_Object_Bar[i].length,
			0.0f
		};

		// カラー反映
		pVtx[0].col = g_Object_Bar[i].col;
		pVtx[1].col = g_Object_Bar[i].col;
		pVtx[2].col = g_Object_Bar[i].col;
		pVtx[3].col = g_Object_Bar[i].col;
	}

	g_pVtxBuffObject_Bar->Unlock();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// 描画処理
//************************************************
void DrawObject_Bar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxTrans, mtxView;				// 計算用マトリックス

	// ライト反映を無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 深度テストの比較方法の変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// 深度バッファに描画しない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffObject_Bar, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < MAX_OBJECT_BAR; i++)
	{
		if (g_Object_Bar[i].dur <= 0)
		{ // 継続時間が無ければコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Object_Bar[i].mtx);

		// ビューマトリックス取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// ポリゴンをカメラの正面に向け続ける
		D3DXMatrixInverse(&g_Object_Bar[i].mtx, NULL, &mtxView);	// 逆行列を求める

		g_Object_Bar[i].mtx._41 = 0.0f;
		g_Object_Bar[i].mtx._42 = 0.0f;
		g_Object_Bar[i].mtx._43 = 0.0f;

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Object_Bar[i].pos.x,
			g_Object_Bar[i].pos.y,
			g_Object_Bar[i].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Object_Bar[i].mtx,
			&g_Object_Bar[i].mtx,
			&mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Object_Bar[i].mtx);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureObject_Bar);

		// ビルボードの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// ライト反映を有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// 深度テストの比較方法の変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// 深度バッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// 構造物の体力ゲージ生成
//************************************************
int CreateObject_Bar(int HP)
{
	int id = 0;	// 識別番号用

	for (int i = 0; i < MAX_OBJECT_BAR; i++)
	{
		if (g_Object_Bar[i].use)
		{ // 使用中ならコンティニュー
			continue;
		}

		g_Object_Bar[i].use = true;
		//g_Object_Bar[i].pPos = pPos;	// 対象位置を付与

		g_Object_Bar[i].span = { 70.0f, 10.0f };		// 大きさ
		g_Object_Bar[i].HPspan = 70.0f / (float)HP;	// 体力の大きさ割合を算出しておく

		g_Object_Bar[i].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);	// 色
		g_Object_Bar[i].HPcol = 1.0f / (float)HP;	// 体力の色割合を算出しておく

		id = i;	// 識別番号格納

		break;	// 終了
	}

	return id;	// 一応識別番号を渡す
}

//************************************************
// 構造物の体力ゲージ更新
//************************************************
void EnableObject_Bar(int HP, int id, D3DXVECTOR3 pos)
{
	// HPに応じてゲージを縮小
	g_Object_Bar[id].span.x = g_Object_Bar[id].HPspan * (float)HP;

	// 色も変更しておく
	g_Object_Bar[id].col.g = g_Object_Bar[id].HPcol * (float)HP;
	g_Object_Bar[id].col.r = 1.5f - g_Object_Bar[id].col.g;

	// 表示期間を設定
	g_Object_Bar[id].dur = 240;

	// 位置を同期
	g_Object_Bar[id].pos = pos;
	g_Object_Bar[id].pos.y = 30.0f;
}