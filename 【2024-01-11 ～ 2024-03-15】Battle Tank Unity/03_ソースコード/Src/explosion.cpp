//************************************************
//
// 爆発処理[explosion.cpp]
// Author：葛西敬介
//************************************************

//include
#include "explosion.h"
#include "sound.h"
#include "main.h"

//グローバル変数宣言
Explosion g_aExplosion[MAX_EXPLOSION];					//爆発の情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;			//テクスチャへのポインタ

//=======================================================================
//爆発の初期化処理
//=======================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスへのポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion.png", &g_pTextureExplosion);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffExplosion, NULL);

	VERTEX_3D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		Explosion* pExplosion = &g_aExplosion[nCntExplosion]; //配列をポインタに渡す

		pExplosion->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		pExplosion->col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//色
		pExplosion->fHeight = 0.0f;								//高さ
		pExplosion->fWidth = 0.0f;								//幅
		pExplosion->fLength = 0.0f;								//対角線の長さ
		pExplosion->nCounterAnim = 0;							//アニメーションカウンター
		pExplosion->nPatternAnim = 0;							//アニメーションパターンNo.
		pExplosion->bUse = false;								//使用しているかどうか

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();

}

//=======================================================================
//爆発の終了処理
//=======================================================================
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

}

//=======================================================================
//爆発の更新処理
//=======================================================================
void UpdateExplosion(void)
{
	VERTEX_3D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		Explosion* pExplosion = &g_aExplosion[nCntExplosion];

		if (pExplosion->bUse)
		{
			pExplosion->pos = pExplosion->pos;
			pExplosion->fWidth = pExplosion->fWidth;
			pExplosion->fHeight = pExplosion->fHeight;

			//対角線の長さを決める
			pExplosion->fLength = sqrtf(pExplosion->fWidth * pExplosion->fWidth + pExplosion->fHeight * pExplosion->fHeight) / 2.0f;

			//頂点座標の設定
			pVtx[0].pos.x = -pExplosion->fLength;
			pVtx[0].pos.y = pExplosion->fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = pExplosion->fLength;
			pVtx[1].pos.y = pExplosion->fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = -pExplosion->fLength;
			pVtx[2].pos.y = -pExplosion->fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = pExplosion->fLength;
			pVtx[3].pos.y = -pExplosion->fLength;
			pVtx[3].pos.z = 0.0f;

			//法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aExplosion[nCntExplosion].nCounterAnim++;//アニメーションカウンターの加算

			if (g_aExplosion[nCntExplosion].nCounterAnim >= 3)
			{
				g_aExplosion[nCntExplosion].nPatternAnim++;//アニメーションパターンの加算
				g_aExplosion[nCntExplosion].nCounterAnim = 0;
			}
			if (g_aExplosion[nCntExplosion].nPatternAnim >= 8)
			{
				g_aExplosion[nCntExplosion].bUse = false;
			}

			//更新処理
			pVtx[0].tex.x = g_aExplosion[nCntExplosion].nPatternAnim / 8.0f;
			pVtx[1].tex.x = (g_aExplosion[nCntExplosion].nPatternAnim + 1) / 8.0f;
			pVtx[2].tex.x = g_aExplosion[nCntExplosion].nPatternAnim / 8.0f;
			pVtx[3].tex.x = (g_aExplosion[nCntExplosion].nPatternAnim + 1) / 8.0f;

		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();

}

//=======================================================================
//爆発の描画処理
//=======================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスへのポインタ

	D3DXMATRIX mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;		//ビューマトリックス取得用

	/*---【1度で済む設定をfor文の外に移しました：福田】---*/

	Explosion* pExplosion = &g_aExplosion[0];	// 爆発情報のポインタ

	// ライト反映を無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 深度テストの比較方法の変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// 深度バッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	/*----------------------------------------------------*/

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pExplosion->mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&pExplosion->mtxWorld, NULL, &mtxView);

			//逆行列を求める
			pExplosion->mtxWorld._41 = 0.0f;
			pExplosion->mtxWorld._42 = 0.0f;
			pExplosion->mtxWorld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, pExplosion->pos.x, pExplosion->pos.y, pExplosion->pos.z);

			D3DXMatrixMultiply(&pExplosion->mtxWorld, &pExplosion->mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pExplosion->mtxWorld);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			//ビルボードの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);

		}

	}

	/*---【1度で済む設定をfor文の外に移しました：福田】---*/

	// ライト反映を有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// 深度バッファの比較方法の変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	// 深度バッファに描画する
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	/*----------------------------------------------------*/
}

//=======================================================================
//爆発の設定処理
//=======================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	PlaySound(SOUND_LABEL_EXPLOSION);
	VERTEX_3D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pVtx += 4)
	{
		Explosion* pExplosion = &g_aExplosion[nCntExplosion];
		if (!pExplosion->bUse)
		{
			pExplosion->pos = pos;			//位置
			pExplosion->col = col;			//頂点カラー
			pExplosion->fWidth = fWidth;	//幅
			pExplosion->fHeight = fHeight;	//高さ
			pExplosion->nPatternAnim = 0;	//アニメーションパターンNo.
			pExplosion->nCounterAnim = 0;	//アニメーションカウンター
			pExplosion->bUse = true;

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(pExplosion->pos.x - pExplosion->fWidth, pExplosion->pos.y - pExplosion->fHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pExplosion->pos.x + pExplosion->fWidth, pExplosion->pos.y - pExplosion->fHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pExplosion->pos.x - pExplosion->fWidth, pExplosion->pos.y + pExplosion->fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pExplosion->pos.x + pExplosion->fWidth, pExplosion->pos.y + pExplosion->fHeight, 0.0f);

			//頂点カラーの設定
			pVtx[0].col = pExplosion->col;
			pVtx[1].col = pExplosion->col;
			pVtx[2].col = pExplosion->col;
			pVtx[3].col = pExplosion->col;


			break;

		}

	}

	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();

}

//=======================================================================
//爆発の情報を取得
//=======================================================================
Explosion* GetExplosion(void)
{
	return g_aExplosion;
}
