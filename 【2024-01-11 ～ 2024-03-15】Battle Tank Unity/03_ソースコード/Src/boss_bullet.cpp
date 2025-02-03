//************************************************
//
// ボスの弾[boss_bullet.cpp]
// Author：葛西敬介
//
//************************************************

//include
#include "main.h"

#include "boss_bullet.h"
#include "collision.h"
#include "debugproc.h"
#include "object.h"
#include "player.h"
#include "shadow.h"
#include "visible_sph.h"

#include <stdlib.h>
#include <time.h>


//グローバル変数宣言
BOSSBULLET g_aBossBullet[MAX_BOSSBULLET];				// 弾の情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossBullet = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBossBullet = NULL;			// テクスチャへのポインタ
D3DXMATRIX g_mtxWorldBullet;							// ワールドマトリックス
int g_BulletType = 0;									// 弾の発射する種類
//************************************************
// ボスの弾の初期化処理
//************************************************
void InitBossBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();  //デバイスへのポインタ

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cannon.png", &g_pTextureBossBullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BOSSBULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBossBullet, NULL);

	VERTEX_3D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBossBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BOSSBULLET; nCntBullet++,pVtx += MAX_VARTEX)
	{
		g_aBossBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
		g_aBossBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		g_aBossBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
		g_aBossBullet[nCntBullet].fWidth = 0.0f;						// 弾の幅
		g_aBossBullet[nCntBullet].fHeight = 0.0f;						// 弾の高さ
		g_aBossBullet[nCntBullet].fLife = 0.0f;							// 弾の寿命
		g_aBossBullet[nCntBullet].id_sph = -1;							// 当たり判定の可視化番号
		g_aBossBullet[nCntBullet].rad = 0;								// 球の当たり判定用のサイズ
		g_aBossBullet[nCntBullet].id_shadow = -1;						// 影の識別番号
		g_aBossBullet[nCntBullet].nBulletIndex = 0;						// 弾の番号
		g_aBossBullet[nCntBullet].bUse = false;							// 弾を使用しているかどうか

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-MAX_BULLETSIZE, MAX_BULLETSIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(MAX_BULLETSIZE, MAX_BULLETSIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-MAX_BULLETSIZE, -MAX_BULLETSIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(MAX_BULLETSIZE, -MAX_BULLETSIZE, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBossBullet->Unlock();

	// 各種変数の初期化
	g_BulletType = 0;
}

//************************************************
// ボスの弾の終了処理
//************************************************
void UninitBossBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBossBullet != NULL)
	{
		g_pTextureBossBullet->Release();
		g_pTextureBossBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBossBullet != NULL)
	{
		g_pVtxBuffBossBullet->Release();
		g_pVtxBuffBossBullet = NULL;
	}

}

//************************************************
// ボスの弾の更新処理
//************************************************
void UpdateBossBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BOSSBULLET; nCntBullet++)
	{
		if (!g_aBossBullet[nCntBullet].bUse)
		{// 弾が使用されていなければコンティニュー
			continue;
		}

		//********************************************************
		// 以下の処理は弾が使用されているときにのみ適用されます
		//********************************************************

		MoveBossBullet(nCntBullet);			// 弾の移動

		/*---【新しい影の追従】---*/
		TrackShadow(g_aBossBullet[nCntBullet].id_shadow, 
			g_aBossBullet[nCntBullet].pos);

		CheckUseBossBullet(nCntBullet);		// 弾を使用しているかどうか

		CollisionBossBullet(nCntBullet);	// ボスの弾と建物の当たり判定

		BossBulletPlayerCollision(nCntBullet);	// ボスの弾とプレイヤーの当たり判定


	}
#ifdef _DEBUG

	PrintDebugProc("弾の座標 : %f %f %f\n", g_aBossBullet[0].pos.x, g_aBossBullet[0].pos.y, g_aBossBullet[0].pos.z);
	PrintDebugProc("弾の座標 : %f %f %f\n", g_aBossBullet[1].pos.x, g_aBossBullet[1].pos.y, g_aBossBullet[1].pos.z);
	PrintDebugProc("弾の座標 : %f %f %f\n", g_aBossBullet[2].pos.x, g_aBossBullet[2].pos.y, g_aBossBullet[2].pos.z);
	PrintDebugProc("弾の座標 : %f %f %f\n", g_aBossBullet[3].pos.x, g_aBossBullet[3].pos.y, g_aBossBullet[3].pos.z);
	//PrintDebugProc("弾の座標 : %f %f %f\n", g_aBossBullet[10].pos.x, g_aBossBullet[10].pos.y, g_aBossBullet[10].pos.z);
#endif
}

//************************************************
// ボスの弾の描画処理
//************************************************
void DrawBossBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxTrans, mtxView;				// 計算用マトリックス

	// ライト反映を無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	// アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBossBullet, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < MAX_BOSSBULLET; i++)
	{
		if (!g_aBossBullet[i].bUse)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBossBullet[i].mtxWorld);

		// ビューマトリックス取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// ポリゴンをカメラの正面に向け続ける
		D3DXMatrixInverse(&g_aBossBullet[i].mtxWorld, NULL, &mtxView);	// 逆行列を求める

		g_aBossBullet[i].mtxWorld._41 = 0.0f;
		g_aBossBullet[i].mtxWorld._42 = 0.0f;
		g_aBossBullet[i].mtxWorld._43 = 0.0f;

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_aBossBullet[i].pos.x,
			g_aBossBullet[i].pos.y,
			g_aBossBullet[i].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_aBossBullet[i].mtxWorld,
			&g_aBossBullet[i].mtxWorld,
			&mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBossBullet[i].mtxWorld);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBossBullet);

		// ビルボードの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}

	// ライト反映を有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//************************************************
// ボスの弾の移動処理
//************************************************
void MoveBossBullet(int id)
{
	g_aBossBullet[id].pos += g_aBossBullet[id].move;	// 弾の移動
}

//************************************************
// ボスの弾を使用しているかどうか
//************************************************
void CheckUseBossBullet(int id)
{
	g_aBossBullet[id].fLife--;	// 弾のライフを減らす

	if (g_aBossBullet[id].fLife <= 0.0f)
	{// ライフがなくなったら使用していない状態にする
		g_aBossBullet[id].bUse = false;
	}

	if (!g_aBossBullet[id].bUse)
	{
		// 判定可視化を消去
		DeleteVisibleSph(g_aBossBullet[id].id_sph);

		// 影を消去
		DeleteShadow(g_aBossBullet[id].id_shadow);

		// 役目を終えた数値もリセット
		g_aBossBullet[id].id_shadow = -1;
		g_aBossBullet[id].id_sph = -1;

	}
}

//************************************************
// ボスの弾の設定処理
//************************************************
void  SetBossBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fLife)
{// 引数の説明(弾の発射位置/弾の移動量/弾の寿命)

	VERTEX_3D* pVtx;  //頂点情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBossBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BOSSBULLET; nCntBullet++, pVtx += MAX_VARTEX)
	{
		if (!g_aBossBullet[nCntBullet].bUse)
		{
			g_aBossBullet[nCntBullet].pos = pos;						// 弾の発射位置
			g_aBossBullet[nCntBullet].move = move;						// 弾の移動量
			g_aBossBullet[nCntBullet].fLife = fLife;					// 弾の寿命
			g_aBossBullet[nCntBullet].rad = MAX_BULLETSIZE * 2;			// 弾の当たり判定の大きさ
			g_aBossBullet[nCntBullet].bUse = true;						// 使用している状態にする

			/*---【影を生成】---*/
			g_aBossBullet[nCntBullet].id_shadow = CreateShadow(20.0f);


#ifdef _DEBUG

			g_aBossBullet[nCntBullet].id_sph = CreateVisibleSph(20.0f, { 0.0f, 1.0f, 0.0f, 1.0f }, &g_aBossBullet[nCntBullet].pos);
#endif
			break;
		}
	}


	//頂点バッファをアンロックする
	g_pVtxBuffBossBullet->Unlock();

}

//************************************************
// ボスの弾の情報の取得
//************************************************
BOSSBULLET* GetBullet(void)
{
	return g_aBossBullet;
}

//************************************************
// ボスの弾と建物の当たり判定
//************************************************
void CollisionBossBullet(int id)
{
	// 弾のタイプに限らずオブジェクトとの衝突判定を行う
	Object* pObject = GetInfoObject();

	for (int nCntObject = 0; nCntObject < AMOUNT_OBJECT; nCntObject++, pObject++)
	{
		if (!pObject->use)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (CollisionSphAABB(g_aBossBullet[id].pos, g_aBossBullet[id].rad, pObject->model.aabb))
		{
			g_aBossBullet[id].fLife = 0.0f;	// 弾の寿命を0にする

			CheckUseBossBullet(id);	//弾の使用判定

			HitObject(nCntObject);	// 建物に衝突判定

		}

	}
}

//************************************************
// ボスの弾とプレイヤーの当たり判定
//************************************************
void BossBulletPlayerCollision(int id)
{
	Player* pPlayer = GetInfoPlayer();

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (!g_aBossBullet[id].bUse)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (CollisionSph(g_aBossBullet[id].pos, g_aBossBullet[id].rad, pPlayer[nCntPlayer].pos, pPlayer[nCntPlayer].param.rad))
		{
			g_aBossBullet[id].fLife = 0.0f;	// 弾の寿命を0にする

			CheckUseBossBullet(id);	//弾の使用判定
		}

		if (pPlayer[nCntPlayer].param.state == stateDamage_p ||
			pPlayer[nCntPlayer].param.state == stateDead_p)
		{ // 負傷：死亡状態ならコンティニュー
			continue;
		}

		if (CollisionSph(g_aBossBullet[id].pos, g_aBossBullet[id].rad, pPlayer[nCntPlayer].pos, pPlayer[nCntPlayer].param.rad))
		{
			// 被弾の処理
			HitPlayer(nCntPlayer);

			g_aBossBullet[id].fLife = 0.0f;	// 弾の寿命を0にする

			CheckUseBossBullet(id);	//弾の使用判定
		}

	}
}
