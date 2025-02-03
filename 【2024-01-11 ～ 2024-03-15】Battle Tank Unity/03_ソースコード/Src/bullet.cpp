//************************************************
//
// 弾[bullet.cpp]
// Author：福田歩希
//
//************************************************

/*/ インクルードファイル /*/
#include "bullet.h"
// 中枢
#include "input.h"
#include "sound.h"
// 諸処理
#include "boss.h"
#include "camera.h"
#include "collision.h"
#include "effect.h"
#include "effect_burn.h"
#include "effect_sand.h"
#include "effect_smoke.h"
#include "enemy.h"
#include "explosion.h"
#include "game.h"
#include "item.h"
#include "object.h"
#include "player.h"
#include "shadow.h"
// デバッグ時
#ifdef _DEBUG
#include "debugproc.h"
#include "visible_sph.h"
#endif	// _DEBUG

/*---【マクロ定義】---*/
#define RPG_UP	(6.0f)
#define GRAVITY	(0.5f)
#define RPG_SPEED	(9.0f)
#define RPG_INCSPEED	(0.35f)
#define RPG_DEFSPEED	(0.1f)
//試しにRPGの当たり判定デカくしてる
//#define RPG_EXRADIUS	(5.0f)
/*---【グローバル変数】---*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			// テクスチャへのポインタ
Bullet g_Bullet[AMOUNT_BULLET];						// 弾情報

/*---【プロトタイプ宣言】---*/
void SubBullet(float rotY, D3DXVECTOR3 pos);	// 拡張：STG
void WideRangeCollision(int id);				// 拡張判定：RPG
void WideRangeDelete(int id);					// 拡張消滅：RPG

//************************************************
// 弾初期
//************************************************
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{ // 弾情報リセット
		g_Bullet[i].use = false;							// 使用フラグ
		g_Bullet[i].type = -1;								// タイプ
		g_Bullet[i].style = -1;								// スタイル
		g_Bullet[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
		g_Bullet[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量の初期化
		g_Bullet[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		g_Bullet[i].rad = 0;								// 半径
		g_Bullet[i].id_shadow = -1;							// 影の識別番号
		g_Bullet[i].id_sph = -1;							// 判定可視化の識別番号
		g_Bullet[i].RPG_Speed = 0.0f;						//ロケランの弾速
		g_Bullet[i].RPGBulletSpeed = 0.0f;					//弾の加速
		g_Bullet[i].startRPGfall = false;					//落下を開始するまでのインターバル
		g_Bullet[i].RPGammofallcount = 0;					//ロケランの落下するタイミング決める用
		g_Bullet[i].ShotRPG = false;						//発射したかどうか
	}

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\cannon.png",
		&g_pTextureBullet);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * AMOUNT_VTX * AMOUNT_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BULLET; i++, pVtx += AMOUNT_VTX)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SPAN_BULLET, SPAN_BULLET, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-SPAN_BULLET, -SPAN_BULLET, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SPAN_BULLET, -SPAN_BULLET, 0.0f);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//************************************************
// 弾破棄
//************************************************
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{ // テクスチャの破棄
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	if (g_pVtxBuffBullet != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//************************************************
// 弾生成
//************************************************
void CreateBullet(int type, int id)
{
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (g_Bullet[i].use)
		{ // 使用中ならコンティニュー
			continue;
		}

		Camera* pCamera = GetInfoCamera();	// カメラへのポインタ
		Player* pPlayer = GetInfoPlayer();	// プレイヤーへのポインタ

		g_Bullet[i].type = type;	// 弾にタイプを設定
		g_Bullet[i].use = true;		// 使用する

		// 向きをカメラの方向に
		g_Bullet[i].rot = pCamera[id].rot;

		// 武器識別番号格納
		int weapon = pPlayer[id].param.weapon;

		// 武器に応じて動作変更
		switch (weapon)
		{
			// 銃
		case styleGun:
			PlaySound(SOUND_LABEL_NOMALGUNSHOT);
			g_Bullet[i].style = styleGun;	// スタイル反映

			g_Bullet[i].pos =
			{
				pPlayer[id].offset_atk[weapon].mtx._41,
				pPlayer[id].offset_atk[weapon].mtx._42,
				pPlayer[id].offset_atk[weapon].mtx._43,
			};

			g_Bullet[i].rad = 4.0f;		// 大きさ：適量
			g_Bullet[i].remain = 20;	// 寿命

			break;

			// RPG
		case styleRPG:
			PlaySound(SOUND_LABEL_ROCKETLAUNCERSHOT);
			g_Bullet[i].move.y = RPG_UP;
			g_Bullet[i].style = styleRPG;	// スタイル反映

			g_Bullet[i].pos =
			{
				pPlayer[id].offset_atk[weapon].mtx._41,
				pPlayer[id].offset_atk[weapon].mtx._42,
				pPlayer[id].offset_atk[weapon].mtx._43,
			};

			g_Bullet[i].rad = 10.0f;	// 大きさ：適量
			g_Bullet[i].remain = 1000;	// 寿命

			break;

			// ガトリング
		case styleGut:
			PlaySound(SOUND_LABEL_MACHINEGUNSHOT);
			g_Bullet[i].style = styleGut;	// スタイル反映

			g_Bullet[i].pos =
			{
				pPlayer[id].offset_atk[weapon].mtx._41,
				pPlayer[id].offset_atk[weapon].mtx._42,
				pPlayer[id].offset_atk[weapon].mtx._43,
			};

			g_Bullet[i].rad = 3.0f;		// 大きさ：適量
			g_Bullet[i].remain = 10;	// 寿命

			break;

			// 散弾銃
		case styleShot:
			PlaySound(SOUND_LABEL_SHOTGUNSHOT);
			g_Bullet[i].style = styleShot;	// スタイル反映

			g_Bullet[i].pos =
			{
				pPlayer[id].offset_atk[weapon].mtx._41,
				pPlayer[id].offset_atk[weapon].mtx._42,
				pPlayer[id].offset_atk[weapon].mtx._43,
			};

			g_Bullet[i].rad = 7.5f;		// 大きさ：適量
			g_Bullet[i].remain = 5;	// 寿命

			SubBullet(g_Bullet[i].rot.y, g_Bullet[i].pos);	// 拡張射撃：2WAY

			break;
		}

		// 影を生成
		g_Bullet[i].id_shadow = CreateShadow(5.0f);

#ifdef _DEBUG

		// 当たり判定を可視化
		g_Bullet[i].id_sph = CreateVisibleSph(g_Bullet[i].rad, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), &g_Bullet[i].pos);

#endif	// _DEBUG 

		break;
	}
}

//************************************************
// 弾更新
//************************************************
void UpdateBullet(void)
{
	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (!g_Bullet[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// 移動
		MoveBullet(i);

		/*---【新しい影の追従】---*/
		TrackShadow(g_Bullet[i].id_shadow,
			g_Bullet[i].pos);

		// エフェクトを出す
		//SetEffect(g_Bullet[i].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.5f, 3.0f);

		// 当たり判定を行う
		CollisionBullet(i);

		// 消滅判定を行う
		DeleteBullet(i);

		if (g_Bullet[i].style == styleRPG && g_Bullet[i].remain == -99)
		{
			// 拡張判定
			WideRangeCollision(i);
		}
	}

	// 頂点を展開
	SetVtxBullet();
}

//************************************************
// 頂点情報を展開
//************************************************
void SetVtxBullet(void)
{
	// 頂点情報のポインタ
	VERTEX_3D* pVtx;

	// 頂点バッファをロックし頂点情報時へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_BULLET; i++, pVtx += AMOUNT_VTX)
	{
		if (!g_Bullet[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_Bullet[i].rad, g_Bullet[i].rad, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Bullet[i].rad, g_Bullet[i].rad, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_Bullet[i].rad, -g_Bullet[i].rad, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Bullet[i].rad, -g_Bullet[i].rad, 0.0f);
	}

	// 頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//************************************************
// 弾移動
//************************************************
void MoveBullet(int id)
{
	if (g_Bullet[id].style == styleGun)
	{ // 通常弾

		// 移動
		g_Bullet[id].pos.x += sinf(g_Bullet[id].rot.y) * 15.0f;
		g_Bullet[id].pos.z += cosf(g_Bullet[id].rot.y) * 15.0f;
	}
	else if (g_Bullet[id].style == styleRPG)
	{ // RPG弾

		//RPGにのみ重力を適用
		g_Bullet[id].move.y -= GRAVITY;
		g_Bullet[id].pos.y += g_Bullet[id].move.y;

		// 特別な情報を付与
		g_Bullet[id].RPG_Speed = RPG_SPEED;
		g_Bullet[id].RPGBulletSpeed += RPG_INCSPEED;
		g_Bullet[id].RPG_Speed += g_Bullet[id].RPGBulletSpeed;

		// 移動
		g_Bullet[id].pos.x += sinf(g_Bullet[id].rot.y) * cosf(g_Bullet[id].rot.x) * g_Bullet[id].RPG_Speed;

		g_Bullet[id].pos.z += cosf(g_Bullet[id].rot.y) * cosf(g_Bullet[id].rot.x) * g_Bullet[id].RPG_Speed;
	}
	else if (g_Bullet[id].style == styleGut)
	{ // ミニガン弾

		// 移動
		g_Bullet[id].pos.x += sinf(g_Bullet[id].rot.y) * 30.0f;
		g_Bullet[id].pos.z += cosf(g_Bullet[id].rot.y) * 30.0f;
	}
	else if (g_Bullet[id].style == styleShot)
	{ // 散弾銃弾

		// 移動
		g_Bullet[id].pos.x += sinf(g_Bullet[id].rot.y) * 30.0f;
		g_Bullet[id].pos.z += cosf(g_Bullet[id].rot.y) * 30.0f;
	}
}

//************************************************
// 弾消滅
//************************************************
void DeleteBullet(int id)
{
	if (CntDuration(&g_Bullet[id].remain) ||
		g_Bullet[id].pos.y - g_Bullet[id].rad <= 0.0f)
	{ // 残存時間が無くなるか地面に着弾すると

		/*---【ロケランのみ】---*/
		if (g_Bullet[id].style == styleRPG)
		{
			g_Bullet[id].remain = -99;	// 拡張突入

			return;
		}

		// 爆発
		SetExplosion(g_Bullet[id].pos, { 0.0f ,0.0f ,0.0f ,0.0f }, g_Bullet[id].rad * 5.0f, g_Bullet[id].rad * 5.0f);

		// 消滅
		g_Bullet[id].use = false;							// 使用フラグ
		g_Bullet[id].type = -1;								// タイプリセット
		g_Bullet[id].style = -1;							// スタイルリセット
		g_Bullet[id].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
		g_Bullet[id].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量の初期化
		g_Bullet[id].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
		g_Bullet[id].rad = 0;								// 半径
		g_Bullet[id].RPG_Speed = 0.0f;						//ロケランの弾速
		g_Bullet[id].RPGBulletSpeed = 0.0f;					//弾の加速
		g_Bullet[id].startRPGfall = false;					//落下を開始するまでのインターバル
		g_Bullet[id].RPGammofallcount = 0;					//ロケランの落下するタイミング決める用
		g_Bullet[id].ShotRPG = false;						//発射したかどうか

		// 影を消去
		DeleteShadow(g_Bullet[id].id_shadow);

#ifdef _DEBUG

		// 判定可視化を消去
		DeleteVisibleSph(g_Bullet[id].id_sph);

#endif	// _DEBUG

		// 役目を終えた数値もリセット
		g_Bullet[id].id_shadow = -1;
		g_Bullet[id].id_sph = -1;
	}
}

//************************************************
// 弾描画
//************************************************
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxTrans, mtxView;				// 計算用マトリックス

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
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < AMOUNT_BULLET; i++)
	{
		if (!g_Bullet[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Bullet[i].mtxWorld);

		// ビューマトリックス取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		// ポリゴンをカメラの正面に向け続ける
		D3DXMatrixInverse(&g_Bullet[i].mtxWorld, NULL, &mtxView);	// 逆行列を求める

		g_Bullet[i].mtxWorld._41 = 0.0f;
		g_Bullet[i].mtxWorld._42 = 0.0f;
		g_Bullet[i].mtxWorld._43 = 0.0f;

		// 位置を反映1
		D3DXMatrixTranslation(&mtxTrans,
			g_Bullet[i].pos.x,
			g_Bullet[i].pos.y,
			g_Bullet[i].pos.z);

		// 位置を反映2
		D3DXMatrixMultiply(&g_Bullet[i].mtxWorld,
			&g_Bullet[i].mtxWorld,
			&mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[i].mtxWorld);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBullet);

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

//************************************************
// 弾の当たり判定
//************************************************
void CollisionBullet(int id)
{
	// 弾のタイプに限らずオブジェクトとの衝突判定を行う
	Object* pObject = GetInfoObject();

	for (int i = 0; i < AMOUNT_OBJECT; i++, pObject++)
	{
		if (!pObject->use)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (CollisionSphAABB(g_Bullet[id].pos, g_Bullet[id].rad, pObject->model.aabb))
		{
			g_Bullet[id].remain = 0;	// 弾は消滅

			HitObject(i);	// 建物に衝突判定
		}
	}

	// switch制御では宣言を行えないためifで制御　←普通に可能みたいでした、今回はもうこのままいきます…
	if (g_Bullet[id].type == bulletPlayer)
	{ // 弾がプレイヤータイプなら
		Enemy* pEnemy = GetInfoEnemy();
		BOSS* pBoss = GetInfoBoss();

		for (int j = 0; j < AMOUNT_ENEMY; j++, pEnemy++)
		{ // エネミーとの判定を行う
			if (!pEnemy->use)
			{ // 未使用ならコンティニュー
				continue;
			}

			if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pEnemy->pos, pEnemy->param.rad))
			{ // 敵にヒットすると

				g_Bullet[id].remain = 0;	// 使用時間を無くす

				// 敵に被弾情報を付与
				if (pEnemy->param.state != stateRotate_e &&
					pEnemy->param.state != stateDamage_e &&
					pEnemy->param.state != stateDead_e)
				{ // 回転：負傷：死亡状態でないときのみ
					HitEnemy(j);

					if (pEnemy->param.style == Dragonfly)
					{ // 蜻蛉のみ特別にノックバックを与える
						pEnemy->move.x *= -1.0f;
						pEnemy->move.z *= -1.0f;
					}
				}
			}
		}

		for (int i = 0; i < MAX_BOSS; i++, pBoss++)
		{//ボスとの判定を行う
			if (!pBoss->use)
			{//未使用ならコンティニュー
				continue;
			}

			for (int j = 0; j < AMOUNT_BOSS_PARTS; j++)
			{
				if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pBoss->pos_sph[j], pBoss->rad[j]))
				{//ボスに当たると

					g_Bullet[id].remain = 0;	// 使用時間を無くす

					// 敵に被弾情報を付与
					if (pBoss->Param.state != stateDamage_b &&
						pBoss->Param.state != stateDead_b)
					{// 負傷状態と死亡状態でないときのみ
						HitBoss(i);
					}
				}
			}
		}
	}
	//else if (g_Bullet[id].type == bulletEnemy)
	//{ // 弾がエネミータイプなら

	//}
	//else if (g_Bullet[id].type == bulletBoss)
	//{// 弾がボスタイプなら
	//	Player* pPlayer = GetInfoPlayer(); // プレイヤーの情報を取得する

	//	for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++, pPlayer++)
	//	{
	//		if (!pPlayer->use)
	//		{//プレイヤーが死んでいたらコンティニュー
	//			continue;
	//		}

	//		if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pPlayer->pos, pPlayer->param.rad))
	//		{
	//			DamagePlayer(nCntPlayer);
	//		}
	//	}
	//}
}

//************************************************
// 弾情報を取得
//************************************************
Bullet* GetInfoBullet(void)
{
	return &g_Bullet[0];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// 拡張：STG
//************************************************
void SubBullet(float rotY, D3DXVECTOR3 pos)
{
	for (int way = 0; way < 2; way++)
	{
		for (int i = 0; i < AMOUNT_BULLET; i++)
		{
			if (g_Bullet[i].use)
			{ // 使用中ならコンティニュー
				continue;
			}

			g_Bullet[i].type = 0;		// 弾にタイプを設定
			g_Bullet[i].use = true;		// 使用する

			// 向きをカメラの方向に
			if (way == 0)
			{
				g_Bullet[i].rot.y = rotY + 0.45f;
			}
			else
			{
				g_Bullet[i].rot.y = rotY - 0.45f;
			}

			g_Bullet[i].style = styleShot;	// スタイルを指定

			g_Bullet[i].pos = pos;	// 位置はその時点のものを参照

			g_Bullet[i].rad = 7.5f;		// 大きさ：適量
			g_Bullet[i].remain = 5;	// 寿命

				// 影を生成
			g_Bullet[i].id_shadow = CreateShadow(5.0f);

#ifdef _DEBUG

			// 当たり判定を可視化
			g_Bullet[i].id_sph = CreateVisibleSph(g_Bullet[i].rad, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), &g_Bullet[i].pos);

#endif	// _DEBUG 

			break;
		}
	}
}

//************************************************
// 拡張判定：RPG
//************************************************
void WideRangeCollision(int id)
{
	g_Bullet[id].rad = 175.0f;	// 拡張突入

		// 弾のタイプに限らずオブジェクトとの衝突判定を行う
	Object* pObject = GetInfoObject();

	for (int i = 0; i < AMOUNT_OBJECT; i++, pObject++)
	{
		if (!pObject->use)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (CollisionSphAABB(g_Bullet[id].pos, g_Bullet[id].rad, pObject->model.aabb))
		{
			HitObject(i);	// 建物に衝突判定
		}
	}

	Enemy* pEnemy = GetInfoEnemy();
	BOSS* pBoss = GetInfoBoss();

	for (int i = 0; i < AMOUNT_ENEMY; i++, pEnemy++)
	{ // エネミーとの判定を行う
		if (!pEnemy->use)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pEnemy->pos, pEnemy->param.rad))
		{ // 敵にヒットすると

			// 敵に被弾情報を付与
			if (pEnemy->param.state != stateRotate_e &&
				pEnemy->param.state != stateDamage_e &&
				pEnemy->param.state != stateDead_e)
			{ // 回転：負傷：死亡状態でないときのみ
				HitEnemy(i);

				if (pEnemy->param.style == Dragonfly)
				{ // 蜻蛉のみ特別にノックバックを与える
					pEnemy->move.x *= -1.0f;
					pEnemy->move.z *= -1.0f;
				}
			}
		}
	}

	for (int i = 0; i < MAX_BOSS; i++, pBoss++)
	{//ボスとの判定を行う
		if (!pBoss->use)
		{//未使用ならコンティニュー
			continue;
		}

		for (int j = 0; j < AMOUNT_BOSS_PARTS; j++)
		{
			if (CollisionSph(g_Bullet[id].pos, g_Bullet[id].rad, pBoss->pos_sph[j], pBoss->rad[j]))
			{//ボスに当たると

				// 敵に被弾情報を付与
				if (pBoss->Param.state != stateDamage_b &&
					pBoss->Param.state != stateDead_b)
				{// 負傷状態と死亡状態でないときのみ
					HitBoss(i);
				}
			}
		}
	}

	// 消滅
	WideRangeDelete(id);
}

//************************************************
// 拡張消滅：RPG
//************************************************
void WideRangeDelete(int id)
{
	// 範囲出現
	CreateEffect_Burn(g_Bullet[id].pos, g_Bullet[id].rad);

	// 煙エフェクト
	for (int i = 0; i < 7; i++)
	{
		CreateEffect_Smoke(0, &g_Bullet[id].pos);
		CreateEffect_Smoke(1, &g_Bullet[id].pos);
	}

	// 爆発
	SetExplosion(g_Bullet[id].pos, { 0.0f, 0.0f, 0.0f, 0.0f }, 35.0f, 35.0f);

	// 消滅
	g_Bullet[id].use = false;							// 使用フラグ
	g_Bullet[id].type = -1;								// タイプリセット
	g_Bullet[id].style = -1;							// スタイルリセット
	//g_Bullet[id].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	g_Bullet[id].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量の初期化
	g_Bullet[id].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	g_Bullet[id].rad = 0;								// 半径
	g_Bullet[id].RPG_Speed = 0.0f;						//ロケランの弾速
	g_Bullet[id].RPGBulletSpeed = 0.0f;					//弾の加速
	g_Bullet[id].startRPGfall = false;					//落下を開始するまでのインターバル
	g_Bullet[id].RPGammofallcount = 0;					//ロケランの落下するタイミング決める用
	g_Bullet[id].ShotRPG = false;						//発射したかどうか

	// 影を消去
	DeleteShadow(g_Bullet[id].id_shadow);

#ifdef _DEBUG

	// 判定可視化を消去
	DeleteVisibleSph(g_Bullet[id].id_sph);

#endif	// _DEBUG

	// 役目を終えた数値もリセット
	g_Bullet[id].id_shadow = -1;
	g_Bullet[id].id_sph = -1;
}