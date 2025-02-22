//************************************************
//
// 爆破エフェクト[effect_burn.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "effect_burn.h"

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
#define MAX_EFFECT_BURN 256	// 爆破エフェクトの最大数

/*---【グローバル変数】---*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect_Burn = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureEffect_Burn = NULL;		// テクスチャへのポインタ
Effect_Burn g_Effect_Burn[MAX_EFFECT_BURN];			// 爆破エフェクト情報

/*---【プロトタイプ宣言】---*/

// 初期
void ImportTexEffect_Burn(void);		// テクスチャ取得
void CreateVtxBufferEffect_Burn(void);	// 頂点情報を生成

// 更新
void SetVtxEffect_Burn(void);	// 展開

void AnimationCnt_Burn(int id);		// 爆破：テクスチャカウント用

TextureSize SetTexEffect_Burn(int id);	// テクスチャ管理用

//************************************************
// 初期処理
//************************************************
void InitEffect_Burn(void)
{
	for (int i = 0; i < MAX_EFFECT_BURN; i++)
	{ // 爆破エフェクト情報リセット

		g_Effect_Burn[i].use = false;								// 使用フラグ
		g_Effect_Burn[i].pPos = nullptr;							// 対象位置
		g_Effect_Burn[i].pos_moved = { 0.0f, 0.0f, 0.0f };			// 変動位置
		g_Effect_Burn[i].pos = { 0.0f, 0.0f, 0.0f };				// 位置
		g_Effect_Burn[i].rot = { 0.0f, 0.0f, 0.0f };				// 向き
		g_Effect_Burn[i].span = { 0.0f, 0.0f };						// 大きさ用
		g_Effect_Burn[i].angle = 0.0f;									// 角度
		g_Effect_Burn[i].length = 0.0f;							// 対角線用
		g_Effect_Burn[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
		g_Effect_Burn[i].remain = 0;								// 寿命

		g_Effect_Burn[i].anima.row = 0;			// 行
		g_Effect_Burn[i].anima.column = 0;		// 列
		g_Effect_Burn[i].anima.id_pattern = 0;	// 現在のパターン
		g_Effect_Burn[i].anima.dur_cnt = 0;		// パターン遷移間隔
		g_Effect_Burn[i].anima.id_cnt = 0;		// 遷移カウンター
	}

	/*--------------------------------------------*/

	// テクスチャ情報を取得
	ImportTexEffect_Burn();

	// 頂点情報を生成
	CreateVtxBufferEffect_Burn();
}

//************************************************
// テクスチャ情報を読み込む
//************************************************
void ImportTexEffect_Burn(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	// テクスチャ画像の読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\effect_ring.png",
		&g_pTextureEffect_Burn);
}

//************************************************
// 頂点情報を生成
//************************************************
void CreateVtxBufferEffect_Burn(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * MAX_EFFECT_BURN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect_Burn,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffEffect_Burn->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_EFFECT_BURN; i++, pVtx += AMOUNT_VTX)
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
	g_pVtxBuffEffect_Burn->Unlock();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// 終了処理
//************************************************
void UninitEffect_Burn(void)
{
	if (g_pTextureEffect_Burn != NULL)
	{ // テクスチャの破棄

		g_pTextureEffect_Burn->Release();
		g_pTextureEffect_Burn = NULL;
	}

	if (g_pVtxBuffEffect_Burn != NULL)
	{ // 頂点バッファの破棄

		g_pVtxBuffEffect_Burn->Release();
		g_pVtxBuffEffect_Burn = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// 更新処理
//************************************************
void UpdateEffect_Burn(void)
{
	for (int i = 0; i < MAX_EFFECT_BURN; i++)
	{
		if (!g_Effect_Burn[i].use)
		{ // 未使用ならコンティニュー

			continue;
		}

		g_Effect_Burn[i].remain--;

		if (g_Effect_Burn[i].remain < 4)
		{
			g_Effect_Burn[i].span *= 0.8f;
		}

		if (g_Effect_Burn[i].remain < 0)
		{
			DeleteEffect_Burn(i);
		}

		// 綺麗に見えるよう少し浮かす
		g_Effect_Burn[i].pos.y = 1.0f;
	}

	// ポリゴンを展開
	SetVtxEffect_Burn();
}

//************************************************
// 爆破エフェクト展開
//************************************************
void SetVtxEffect_Burn(void)
{
	VERTEX_3D* pVtx;		// 頂点情報のポインタ
	TextureSize tex = {};	// テクスチャサイズ

	/*--------------------------------------------*/

	for (int i = 0; i < MAX_EFFECT_BURN; i++)
	{ // 頂点位置用の情報を算出

		if (!g_Effect_Burn[i].use)
		{ // 未使用ならコンティニュー

			continue;
		}

		// 角度を算出
		g_Effect_Burn[i].angle = atan2f(g_Effect_Burn[i].span.x, g_Effect_Burn[i].span.y);

		// 対角線を算出
		g_Effect_Burn[i].length = sqrtf(g_Effect_Burn[i].span.x * g_Effect_Burn[i].span.x + g_Effect_Burn[i].span.y * g_Effect_Burn[i].span.y);
	}

	/*--------------------------------------------*/

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffEffect_Burn->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < MAX_EFFECT_BURN; i++, pVtx += AMOUNT_VTX)
	{
		if (!g_Effect_Burn[i].use)
		{ // 未使用ならコンティニュー

			continue;
		}

		// 頂点の展開
		pVtx[0].pos =
		{
			sinf(g_Effect_Burn[i].rot.z - (D3DX_PI - g_Effect_Burn[i].angle)) * g_Effect_Burn[i].length,
			0.0f,
			-cosf(g_Effect_Burn[i].rot.z - (D3DX_PI - g_Effect_Burn[i].angle)) * g_Effect_Burn[i].length
		};

		pVtx[1].pos =
		{
			sinf(g_Effect_Burn[i].rot.z + (D3DX_PI - g_Effect_Burn[i].angle)) * g_Effect_Burn[i].length,
			0.0f,
			-cosf(g_Effect_Burn[i].rot.z + (D3DX_PI - g_Effect_Burn[i].angle)) * g_Effect_Burn[i].length
		};

		pVtx[2].pos =
		{
			sinf(g_Effect_Burn[i].rot.z - g_Effect_Burn[i].angle) * g_Effect_Burn[i].length,
			0.0f,
			-cosf(g_Effect_Burn[i].rot.z - g_Effect_Burn[i].angle) * g_Effect_Burn[i].length
		};

		pVtx[3].pos =
		{
			sinf(g_Effect_Burn[i].rot.z + g_Effect_Burn[i].angle) * g_Effect_Burn[i].length,
			0.0f,
			-cosf(g_Effect_Burn[i].rot.z + g_Effect_Burn[i].angle) * g_Effect_Burn[i].length
		};

		// カラー反映
		pVtx[0].col = g_Effect_Burn[i].col;
		pVtx[1].col = g_Effect_Burn[i].col;
		pVtx[2].col = g_Effect_Burn[i].col;
		pVtx[3].col = g_Effect_Burn[i].col;

		// テクスチャアニメーション管理
		tex = SetTexEffect_Burn(i);

		// テクスチャサイズ反映
		pVtx[0].tex = tex.size[0];
		pVtx[1].tex = tex.size[1];
		pVtx[2].tex = tex.size[2];
		pVtx[3].tex = tex.size[3];
	}

	g_pVtxBuffEffect_Burn->Unlock();
}

//************************************************
// テクスチャアニメーション管理
//************************************************
TextureSize SetTexEffect_Burn(int id)
{
	TextureSize tex = {};	// テクスチャサイズ格納

	// 爆破：5列 * 3行のパターンで計算
	float row = 1.0f / g_Effect_Burn[id].anima.row;			// 1つ当たりの行サイズ
	float column = 1.0f / g_Effect_Burn[id].anima.column;	// 1つ当たりの列サイズ

	// 爆破：テクスチャカウント用
	AnimationCnt_Burn(id);

	float x = 1.0f + (g_Effect_Burn[id].anima.id_pattern * 1.0f);
	float y = 1.0f;

	if (g_Effect_Burn[id].anima.id_pattern >= 5 &&
		g_Effect_Burn[id].anima.id_pattern < 10)
	{
		y = 2.0f;
	}
	else if (g_Effect_Burn[id].anima.id_pattern >= 10)
	{
		y = 3.0f;
	}

	tex = {
		D3DXVECTOR2(column * (x - 1.0f), row * (y - 1.0f)),
		D3DXVECTOR2(column * x, row * (y - 1.0f)),
		D3DXVECTOR2(column * (x - 1.0f), row * y),
		D3DXVECTOR2(column * x, row * y),
	};

	return tex;	// テクスチャサイズを渡す
}

//************************************************
// 爆破：テクスチャカウント用
//************************************************
void AnimationCnt_Burn(int id)
{
	if (g_Effect_Burn[id].anima.id_cnt < g_Effect_Burn[id].anima.dur_cnt)
	{ // 既定の間隔までカウント

		g_Effect_Burn[id].anima.id_cnt++;
	}
	else
	{ // 既定の間隔に達すると

		g_Effect_Burn[id].anima.id_cnt = 0;		// カウントリセット
		g_Effect_Burn[id].anima.id_pattern++;	// パターンを進める

		if (g_Effect_Burn[id].anima.id_pattern >= 15)
		{ // 15パターンに到達でリセット？

			g_Effect_Burn[id].anima.id_pattern = 0;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// 描画処理
//************************************************
void DrawEffect_Burn(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxTrans/*, mtxView*/;			// 計算用マトリックス

	// ライト反映を無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//// 深度テストの比較方法の変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//// 深度バッファに描画しない
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect_Burn, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < MAX_EFFECT_BURN; i++)
	{
		if (!g_Effect_Burn[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Effect_Burn[i].mtx);

		//// ビューマトリックス取得
		//pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//// ポリゴンをカメラの正面に向け続ける
		//D3DXMatrixInverse(&g_Effect_Burn[i].mtx, NULL, &mtxView);	// 逆行列を求める

		g_Effect_Burn[i].mtx._41 = 0.0f;
		g_Effect_Burn[i].mtx._42 = 0.0f;
		g_Effect_Burn[i].mtx._43 = 0.0f;

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Effect_Burn[i].pos.x,
			g_Effect_Burn[i].pos.y,
			g_Effect_Burn[i].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Effect_Burn[i].mtx,
			&g_Effect_Burn[i].mtx,
			&mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Effect_Burn[i].mtx);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureEffect_Burn);

		// ビルボードの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// ライト反映を有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//// 深度テストの比較方法の変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//// 深度バッファに書き込む
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//************************************************
// 爆破エフェクト生成
//************************************************
void CreateEffect_Burn(D3DXVECTOR3 pos , float rad)
{
	for (int i = 0; i < MAX_EFFECT_BURN; i++)
	{
		if (g_Effect_Burn[i].use)
		{ // 使用中ならコンティニュー
			continue;
		}

		g_Effect_Burn[i].use = true;
		g_Effect_Burn[i].pos = pos;	// 対象位置を取得

		g_Effect_Burn[i].span = { rad * 1.5f, rad * 1.5f };		// 大きさ：適量
		g_Effect_Burn[i].remain = -1;				// 寿命：無限
		g_Effect_Burn[i].anima.row = 3;				// 3行
		g_Effect_Burn[i].anima.column = 5;			// 5列
		g_Effect_Burn[i].anima.dur_cnt = 1;			// 遷移間隔：適量

		g_Effect_Burn[i].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	// 色
		g_Effect_Burn[i].remain = 25;

		break;	// 終了
	}
}

//************************************************
// 爆破エフェクト消滅
//************************************************
void DeleteEffect_Burn(int id)
{
	g_Effect_Burn[id].use = false;								// 使用フラグ
	g_Effect_Burn[id].pPos = nullptr;							// 対象位置
	g_Effect_Burn[id].pos_moved = { 0.0f, 0.0f, 0.0f };			// 変動位置
	g_Effect_Burn[id].pos = { 0.0f, 0.0f, 0.0f };				// 位置
	g_Effect_Burn[id].rot = { 0.0f, 0.0f, 0.0f };				// 向き
	g_Effect_Burn[id].span = { 0.0f, 0.0f };					// 大きさ用
	g_Effect_Burn[id].angle = 0.0f;								// 角度
	g_Effect_Burn[id].length = 0.0f;							// 対角線用
	g_Effect_Burn[id].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
	g_Effect_Burn[id].remain = 0;								// 寿命

	g_Effect_Burn[id].anima.row = 0;		// 総行数
	g_Effect_Burn[id].anima.column = 0;		// 総列数
	g_Effect_Burn[id].anima.id_pattern = 0;	// 現在のパターン
	g_Effect_Burn[id].anima.dur_cnt = 0;	// パターン遷移間隔
	g_Effect_Burn[id].anima.id_cnt = 0;		// 遷移カウンター
}