//************************************************
//
//弾[bullet.cpp]
//Author：福田歩希
//
//************************************************
#include "bullet.h"

#include "input.h"
#include "sound.h"

#include "camera.h"
#include "collision.h"
#include "particle.h"
#include "player.h"
#include "effect.h"
#include "enemy.h"
#include "score.h"
#include "shadow.h"
#include "visible_sphere.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;	//テクスチャへのポインタ
Bullet g_aBullet[AMOUNT_BULLET];	//弾情報
bool g_bZTest = false;	//Zテスト切り替え
bool g_bATest = true;	//アルファテスト切り替え

//************************************************
//弾初期
//************************************************
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//弾情報初期設定
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		g_aBullet[i].bUse = false;
		g_aBullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[i].fPA = 0.0f;
		g_aBullet[i].fRadius = SPAN_BULLET;
		g_aBullet[i].nRemain = 0;
	}

	g_bZTest = false;	//Zテスト切り替え
	g_bATest = true;	//アルファテスト切り替え

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\texture\\bullet01.png",
		&g_pTextureBullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_BULLET, -SPAN_BULLET, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_BULLET, -SPAN_BULLET, 0.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += AMOUNT_VTX;
	}

	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//************************************************
//弾破棄
//************************************************
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//************************************************
//弾設定
//************************************************
void SetInfoBullet(void)
{
	//Camera* pCamera = GetInfoCamera();
	Player* pPlayer = GetInfoPlayer();
	int nIdx = 0;

	for (int step = 0; step < 3; step++)
	{
		for (int i = 0; i < AMOUNT_BULLET; i++)
		{
			nIdx = i;

			if (g_aBullet[i].bUse) continue;

			g_aBullet[i].bUse = true;
			g_aBullet[i].pos = pPlayer->pos;
			//g_aBullet[i].rot = pCamera->rot;	//方位
			g_aBullet[i].rot = pPlayer->rot;
			//g_aBullet[i].fPA = pCamera->fPA;	//極

			if (!pPlayer->bMUKIMUKI)
			{
				g_aBullet[i].nRemain = 5;
			}
			else
			{
				g_aBullet[i].nRemain = 20;
			}

			if (step == 0)
			{
				g_aBullet[nIdx].rot.y -= 0.1f;
			}

			if (step == 2)
			{
				g_aBullet[nIdx].rot.y += 0.1f;
			}

			//当たり判定の可視化
			//SetSizeVisible_Sphere(g_aBullet[i].fRadius, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), &g_aBullet[i].pos);

			/*プレイヤーの先端から発射されるように、少し前進させておく*/
			g_aBullet[i].pos.x += sinf(g_aBullet[i].rot.y) * cosf(g_aBullet[i].fPA) * 15.0f;
			g_aBullet[i].pos.y += (sinf(g_aBullet[i].fPA) * 15.0f);
			g_aBullet[i].pos.z += cosf(g_aBullet[i].rot.y) * cosf(g_aBullet[i].fPA) * 15.0f;

			break;
		}
	}
}

//************************************************
//弾更新
//************************************************
void UpdateBullet(void)
{
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (g_aBullet[i].bUse)
		{
			//移動
			g_aBullet[i].pos.x += sinf(g_aBullet[i].rot.y) * cosf(g_aBullet[i].fPA) * SPD_BULLET;
			g_aBullet[i].pos.y += sinf(g_aBullet[i].fPA) * SPD_BULLET;
			g_aBullet[i].pos.z += cosf(g_aBullet[i].rot.y) * cosf(g_aBullet[i].fPA) * SPD_BULLET;

			//エフェクトを常に出す
			SetInfoEffect(EffectStyleBullet, g_aBullet[i].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.9f));

			//消滅判定を行う
			DisappearBullet(i);
		}
	}

	//Zテスト切り替え
	if (GetKeyboardTrigger(DIK_F2))
	{
		g_bZTest = !g_bZTest;
	}

	//アルファテスト切り替え
	if (GetKeyboardTrigger(DIK_F3))
	{
		g_bATest = !g_bATest;
	}
}

//************************************************
//弾消滅
//************************************************
void DisappearBullet(int nCnt)
{
	//残存時間減少
	g_aBullet[nCnt].nRemain--;

	//残存時間が無くなると消滅
	if (g_aBullet[nCnt].nRemain < 0)
	{
		g_aBullet[nCnt].bUse = false;

		//当たり判定可視化にも消滅処理を行う
		//DisappearVisible_Sphere(&g_aBullet[nCnt].pos);

		//パーティクルを出す
		for (int ii = 0; ii < 20; ii++)
		{
			SetInfoParticle(g_aBullet[nCnt].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.9f), 3.0f);
		}
	}
}

//************************************************
//弾描画
//************************************************
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//ライトをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (g_bZTest)
	{
		//Z位置の比較方法の変更
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

		//Zバッファに書き込まない
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	if (g_bATest)
	{
		//アルファテストを有効
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	}

	D3DXMATRIX mtxTrans;	//計算用マトリックス

	//ビューマトリックス取得
	D3DXMATRIX mtxView;

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (g_aBullet[i].bUse)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aBullet[i].mtxWorld);

			//ビューマトリックス取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラの正面に向け続ける
			D3DXMatrixInverse(&g_aBullet[i].mtxWorld, NULL, &mtxView);	//逆行列を求める

			g_aBullet[i].mtxWorld._41 = 0.0f;
			g_aBullet[i].mtxWorld._42 = 0.0f;
			g_aBullet[i].mtxWorld._43 = 0.0f;

			//位置を反映1
			D3DXMatrixTranslation(&mtxTrans,
				g_aBullet[i].pos.x,
				g_aBullet[i].pos.y,
				g_aBullet[i].pos.z);

			//位置を反映2
			D3DXMatrixMultiply(&g_aBullet[i].mtxWorld,
				&g_aBullet[i].mtxWorld,
				&mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[i].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ビルボードの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}

	//ライトをオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	if (g_bZTest)
	{
		//Z位置の比較方法の変更
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

		//Zバッファに書き込む
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	if (g_bATest)
	{
		//アルファテストを無効に戻す
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//************************************************
//弾の当たり判定
//************************************************
void CollisionBullet(int nMode, int nCnt)
{
	Enemy* pEnemy = GetInfoEnemy();
	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (!g_aBullet[i].bUse) continue;

		switch (nMode)
		{
			//敵
		case CollisionModeEnemy:

			if (CollisionSphere(pEnemy[nCnt].pos, pEnemy[nCnt].fRadius, g_aBullet[i].pos, g_aBullet[i].fRadius))
			{
				//ダメージ状態に
				if (pEnemy[nCnt].nState == EnemyStateDash || pEnemy[nCnt].nState == EnemyStateATK)
				{
					pEnemy[nCnt].nState = EnemyStateDamage;
					pEnemy[nCnt].nNowMotion = EnemyMotionStateNormal;
					pEnemy[nCnt].move.x = sinf(g_aBullet[i].rot.y) * 10.0f;
					pEnemy[nCnt].move.z = cosf(g_aBullet[i].rot.y) * 10.0f;
					pEnemy[nCnt].nLife--;
					pEnemy[nCnt].nCntState = 20;

					pPlayer->nEnegy += 10;

					Add_Score(13);

					PlaySound(SOUND_LABEL_HIT);

					g_aBullet[i].nRemain = 0;
				}
			}

			break;

			//壁
		case CollisionModeWall:
			break;
		}
	}
}

//************************************************
//弾情報を取得
//************************************************
Bullet* GetInfoBullet(void)
{
	return &g_aBullet[0];
}