//************************************************
//
//弾の処理[bullet.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "sound.h"
#include "block.h"
#include "breakblock.h"
#include "bullet.h"
#include "effect_bullet.h"
#include "effect_comet.h"
#include "enemy.h"
#include "enemy_glide.h"
#include "enemy_slide.h"
#include "enemy_spiral.h"
#include "particle.h"
#include "player.h"
#include "score.h"
#include "slideblock.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Bullet[AMOUNT_TEXTURE_BULLET] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Bullet = NULL;	//頂点バッファのポインタ
BULLET g_aBullet[AMOUNT_POLYGON_BULLET];	//弾の各情報
int g_nChangeRute_Bullet = 0;	//方向分岐用
D3DXVECTOR3 g_NowVector_Bullet[AMOUNT_POLYGON_ENEMY] = {};	//弾から敵へのベクトル格納
float g_fRadius_Bullet = 0.0f;	//弾の半径を格納
float g_fRadius_EnemyCore_Bullet = 0.0f;	//敵の本体の半径を格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Bullet(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Bullet;

	//敵情報へのポインタ
	ENEMY* pEnemy;

	//敵情報の取得
	pEnemy = Getinfo_Enemy();	//敵情報系の先頭アドレスが代入される

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_COMET_BULLET,
		&g_pTexture_Bullet[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_REUNION_1_BULLET,
		&g_pTexture_Bullet[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_REUNION_2_BULLET,
		&g_pTexture_Bullet[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_KING_BULLET,
		&g_pTexture_Bullet[3]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_BULLET,
	D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Bullet,
		NULL);

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bullet->Lock(0, 0, (void**)&pVtx_Bullet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BULLET; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Bullet[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bullet[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bullet[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Bullet[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Bullet[0].rhw = 1.0f;
		pVtx_Bullet[1].rhw = 1.0f;
		pVtx_Bullet[2].rhw = 1.0f;
		pVtx_Bullet[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Bullet += AMOUNT_VTX;	//頂点情報のポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Bullet->Unlock();

	//弾情報の初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BULLET; nCnt++)
	{
		g_aBullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置情報を初期化
		g_aBullet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量を初期化
		g_aBullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きを初期化
		g_aBullet[nCnt].nRemain = REMAIN_TIME_BULLET;			//弾の残存時間を決める
		g_aBullet[nCnt].bUse = false;							//弾の使用判定を無くす
		g_aBullet[nCnt].type = BULLETTYPE_NONE;					//弾の分類を無くす
		g_aBullet[nCnt].style = BULLETSTYLE_COMET;				//弾の種類を通常弾に変更
		g_aBullet[nCnt].rute = BULLETRUTE_NONE;					//弾道の分岐を初期化
		g_aBullet[nCnt].fLength = 0.0f;							//弾の対角線を格納
		g_aBullet[nCnt].fAngle = 0.0f;							//弾の角度を格納
		g_aBullet[nCnt].nDamage = 0;							//弾の攻撃力を初期化
		g_aBullet[nCnt].nPattern = 0;							//パターンカウント
		g_aBullet[nCnt].fTexX = 0.0f;							//テクスチャ座標を初期化
		g_aBullet[nCnt].fTexY = 0.0f;							//テクスチャ座標を初期化
	}

	//方向分岐初期化
	g_nChangeRute_Bullet = 0;

	//平均的な弾の半径の長さを算出する
	g_fRadius_Bullet = sqrtf(HALFSPAN_X_BULLET * HALFSPAN_X_BULLET +
		HALFSPAN_Y_BULLET * HALFSPAN_Y_BULLET) * APPARENTSPAN_RADIUS_BULLET;

	//敵(もや)の半径の長さを算出する
	g_fRadius_EnemyCore_Bullet = sqrtf(pEnemy[0].fHalfSpanX * pEnemy[0].fHalfSpanX +
		pEnemy[0].fHalfSpanY * pEnemy[0].fHalfSpanY) * APPARENTSPAN_RADIUS_BULLET;
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Bullet(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEXTURE_BULLET; nCnt++)
	{
		if (g_pTexture_Bullet[nCnt] != NULL)
		{
			g_pTexture_Bullet[nCnt]->Release();
			g_pTexture_Bullet[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Bullet != NULL)
	{
		g_pVtxBuff_Bullet->Release();
		g_pVtxBuff_Bullet = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Bullet(void)
{	
	//弾情報のためのループ
	for (int nCnt = 0; nCnt< AMOUNT_POLYGON_BULLET; nCnt++)
	{
		//プレイヤーの弾の処理
		if (g_aBullet[nCnt].bUse && g_aBullet[nCnt].type == BULLETTYPE_PLAYER)
		{
			//弾の種類によって処理変化
			Sort_BulletStyle(nCnt);

			//弾が画面の外へ出たとき
			if (g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET <= 0.0f ||
				g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET >= SCREEN_WIDTH)
			{
				//今回の弾の使用判定を無くす
				g_aBullet[nCnt].bUse = false;
			}

			//当たり判定シリーズ
			HitDetection_Cloud_Enemy(nCnt);
			HitDetection_Glide_Enemy(nCnt);
			HitDetection_Slide_Enemy(nCnt);
			HitDetection_Spiral_Enemy(nCnt);
			HitDetection_Block(nCnt);
			HitDetection_SlideBlock(nCnt);
			HitDetection_BreakBlock(nCnt);
		}
		//敵の弾の処理
		else if (g_aBullet[nCnt].bUse == true && g_aBullet[nCnt].type == BULLETTYPE_ENEMY)
		{

		}
		/*弾の使用が解除されたとき残存する座標情報を遠くへ…(バグ防止)*/
		else
		{
			g_aBullet[nCnt].pos.x = DUMMY_POS_BULLET;
		}
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Bullet(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Bullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BULLET; nCnt++)
	{
		//弾が使用されている番号を検知
		if (g_aBullet[nCnt].bUse == true)
		{
			//テクスチャの設定
			switch (g_aBullet[nCnt].style)
			{
			case BULLETSTYLE_COMET:

				pDevice->SetTexture(0, g_pTexture_Bullet[0]);

				break;

			case BULLETSTYLE_REUNION:

				if (g_aBullet[nCnt].rute == BULLETRUTE_UP)
				{
					pDevice->SetTexture(0, g_pTexture_Bullet[1]);
				}
				else if (g_aBullet[nCnt].rute == BULLETRUTE_DOWN)
				{
					pDevice->SetTexture(0, g_pTexture_Bullet[2]);
				}

				break;

			case BULLETSTYLE_KING:

				pDevice->SetTexture(0, g_pTexture_Bullet[3]);

				break;
			}
		
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}
}

//************************************************
//プレイヤーの弾丸発射処理関数
//************************************************
void Setinfo_Bullet(D3DXVECTOR3 pos, int nSetBulletStyle)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Bullet;

	//プレイヤー情報へのポインタ
	PLAYER* pPlayer;

	//プレイヤー情報の取得
	pPlayer = Getinfo_Player();	//プレイヤー情報系の先頭アドレスが代入される
	
	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bullet->Lock(0, 0, (void**)&pVtx_Bullet, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_BULLET; nCnt++)
	{
		//使用されていない弾の番号を検知した時
		if (g_aBullet[nCnt].bUse == false)
		{
			//スタイル番号に応じ弾の種類選定
			switch (nSetBulletStyle)
			{
			case 0:

				g_aBullet[nCnt].style = BULLETSTYLE_COMET;

				break;

			case 1:

				g_aBullet[nCnt].style = BULLETSTYLE_REUNION;

				break;

			case 2:

				g_aBullet[nCnt].style = BULLETSTYLE_KING;

				break;
			}

			//弾の種類によって情報が変化
			switch (g_aBullet[nCnt].style)
			{
			case BULLETSTYLE_COMET:

				if (pPlayer->nCapacity >= AMOUNT_DECREASE_CAPACITY_COMET_BULLET)
				{
					//プレイヤーの中心位置を弾の中心位置に設定
					g_aBullet[nCnt].pos = pos;

					//ちょいプレイヤーの右に出る
					g_aBullet[nCnt].pos.x += HALFSPAN_X_PLAYER;

					//中心をもとに弾の頂点座標を展開
					pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET;
					pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET;
					pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET;
					pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET;
					pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET;
					pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET;
					pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET;
					pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET;

					//移動量を設定
					g_aBullet[nCnt].move = D3DXVECTOR3(MOVE_SPD_POS_BULLET, 0.0f, 0.0f);

					//回転方向をランダムに
					int i = rand() % 2;
					i == 0 ? g_aBullet[nCnt].move.z = ROTATE_SPD_BULLET : g_aBullet[nCnt].move.z = -ROTATE_SPD_BULLET;

					g_aBullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きを初期化
					g_aBullet[nCnt].nRemain = REMAIN_TIME_BULLET;	//弾の残存時間を決める
					g_aBullet[nCnt].bUse = true;					//弾の使用判定を出す
					g_aBullet[nCnt].type = BULLETTYPE_PLAYER;		//この時発射した弾をプレイヤーのものとする
					g_aBullet[nCnt].rute = BULLETRUTE_NONE;			//弾道の分岐を無しにセット
					
					//対角線の長さを設定
					g_aBullet[nCnt].fLength = sqrtf(SPAN_X_BULLET * SPAN_X_BULLET +
						SPAN_Y_BULLET * SPAN_Y_BULLET) * 0.5f;

					//対角線の角度を設定
					g_aBullet[nCnt].fAngle = atan2f(SPAN_Y_BULLET, SPAN_Y_BULLET);

					g_aBullet[nCnt].nDamage = AMOUNT_DAMAGE_BULLET;	//攻撃力をセット
					g_aBullet[nCnt].nPattern = 0;					//パターンカウント
					g_aBullet[nCnt].fTexX = 0.0f;					//テクスチャ座標を初期化
					g_aBullet[nCnt].fTexY = 0.0f;					//テクスチャ座標を初期化

					//色を通常色に
					pVtx_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					//テクスチャを上手いこと調整
					pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx_Bullet[1].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET, 0.0f);
					pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f, PER_ONE_TEX_Y_COMET_BULLET);
					pVtx_Bullet[3].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET, PER_ONE_TEX_Y_COMET_BULLET);

					pPlayer->nCapacity -= AMOUNT_DECREASE_CAPACITY_COMET_BULLET;	//キャパを消費

					//効果音を鳴らす
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}

				break;

			case BULLETSTYLE_REUNION:

				if (pPlayer->nCapacity >= AMOUNT_DECREASE_CAPACITY_REUNION_BULLET)
				{
					g_nChangeRute_Bullet++;

					g_aBullet[nCnt].pos = pos;	//プレイヤーの中心位置を弾の中心位置に設定

					//中心をもとに弾の頂点座標を展開
					pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET * 0.5f;
					pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET * 0.5f;
					pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET * 0.5f;
					pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET * 0.5f;
					pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET * 0.5f;
					pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET * 0.5f;
					pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET * 0.5f;
					pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET * 0.5f;

					//移動量を設定
					g_aBullet[nCnt].move = D3DXVECTOR3(MOVE_SPD_POS_BULLET, MOVE_SPD_POS_BULLET, 0.0f);

					g_aBullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きを初期化
					g_aBullet[nCnt].nRemain = REMAIN_REUNION_TIME_BULLET;	//リユニオン用の残存時間を決める
					g_aBullet[nCnt].bUse = true;				//弾の使用判定を出す
					g_aBullet[nCnt].type = BULLETTYPE_PLAYER;	//この時発射した弾をプレイヤーのものとする

					switch (g_nChangeRute_Bullet)
					{
					case 1:

						g_aBullet[nCnt].rute = BULLETRUTE_UP;	//弾道の分岐を上にセット

						//色を通常色に
						pVtx_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//テクスチャを通常に
						pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
						pVtx_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
						pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
						pVtx_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

						break;

					case 2:

						g_aBullet[nCnt].rute = BULLETRUTE_DOWN;	//弾道の分岐を下にセット

						//色を通常色に
						pVtx_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//テクスチャを通常に
						pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
						pVtx_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
						pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
						pVtx_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

						break;
					}

					//対角線の長さを設定
					g_aBullet[nCnt].fLength = sqrtf(SPAN_X_BULLET * SPAN_X_BULLET +
						SPAN_Y_BULLET * SPAN_Y_BULLET) * 0.5f;

					//対角線の角度を設定
					g_aBullet[nCnt].fAngle = atan2f(SPAN_Y_BULLET, SPAN_Y_BULLET);

					g_aBullet[nCnt].nDamage = AMOUNT_DAMAGE_BULLET;			//攻撃力をセット
					g_aBullet[nCnt].nPattern = 0;							//パターンカウント
					g_aBullet[nCnt].fTexX = 0.0f;							//テクスチャ座標を初期化
					g_aBullet[nCnt].fTexY = 0.0f;							//テクスチャ座標を初期化

					if (g_nChangeRute_Bullet < AMOUNT_USING_POLYGON_REUNION_BULLET)
					{
						//この種類の弾を出すときもう一発自動で出す
						Setinfo_Bullet(pos, nSetBulletStyle);

						//弾道分岐カウントの増加をリセット
						g_nChangeRute_Bullet = 0;
					}

					pPlayer->nCapacity -= AMOUNT_DECREASE_CAPACITY_REUNION_BULLET;	//キャパを消費

					//効果音を鳴らす
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}

				break;

			case BULLETSTYLE_KING:

				if (pPlayer->nCapacity >= AMOUNT_DECREASE_CAPACITY_KING_BULLET)
				{
					g_aBullet[nCnt].pos = pos;	//プレイヤーの中心位置を弾の中心位置に設定

					//中心をもとに弾の頂点座標を展開
					pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_KNIFE_X_BULLET;
					pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_KNIFE_Y_BULLET;
					pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_KNIFE_X_BULLET;
					pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_KNIFE_Y_BULLET;
					pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_KNIFE_X_BULLET;
					pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_KNIFE_Y_BULLET;
					pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_KNIFE_X_BULLET;
					pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_KNIFE_Y_BULLET;

					//移動量を設定
					g_aBullet[nCnt].move = D3DXVECTOR3(MOVE_SPD_POS_BULLET, MOVE_SPD_POS_BULLET, 0.0f);

					g_aBullet[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きを初期化
					g_aBullet[nCnt].nRemain = REMAIN_TIME_BULLET;	//弾の残存時間を決める
					g_aBullet[nCnt].bUse = true;					//弾の使用判定を出す
					g_aBullet[nCnt].type = BULLETTYPE_PLAYER;		//この時発射した弾をプレイヤーのものとする
					g_aBullet[nCnt].rute = BULLETRUTE_NONE;			//弾道の分岐を無しにセット
			
					//対角線の長さを設定
					g_aBullet[nCnt].fLength = 0.0f;

					//対角線の角度を設定
					g_aBullet[nCnt].fAngle = 0.0f;

					g_aBullet[nCnt].nDamage = AMOUNT_KNIFE_DAMAGE_BULLET;	//ナイフ用攻撃力をセット
					g_aBullet[nCnt].nPattern = 0;					//パターンカウント
					g_aBullet[nCnt].fTexX = 0.0f;					//テクスチャ座標を初期化
					g_aBullet[nCnt].fTexY = 0.0f;					//テクスチャ座標を初期化

					//色を通常色に
					pVtx_Bullet[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx_Bullet[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					//テクスチャを通常に
					pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx_Bullet[1].tex = D3DXVECTOR2(1.0f, 0.0f);
					pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx_Bullet[3].tex = D3DXVECTOR2(1.0f, 1.0f);

					pPlayer->nCapacity -= AMOUNT_DECREASE_CAPACITY_KING_BULLET;	//キャパを消費

					//効果音を鳴らす
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
				}

				break;
			}

			break;
		}

		pVtx_Bullet += AMOUNT_VTX;	//頂点情報のポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Bullet->Unlock();
}

//************************************************
//弾と敵で最も短い距離のものを出す関数
//************************************************
//void CalcNearlyVector_Bullet(int nCnt)
//{
//	//敵情報へのポインタ
//	ENEMY* pEnemy;
//
//	//敵情報の取得
//	pEnemy = Getinfo_Enemy();	//敵情報系の先頭アドレスが代入される
//
//	float fMinDistance = FLT_MAX;
//	float fDistance;
//	int nEnemyNearest = 0;
//
//	//敵の数分、処理を回す
//	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_POLYGON_ENEMY; nCntEnemy++)
//	{
//		//使用されている全ての敵への距離を取得
//		if (pEnemy[nCntEnemy].bUse == true)
//		{
//			g_NowVector_Bullet[nCntEnemy] = pEnemy[nCntEnemy].pos - g_aBullet[nCnt].pos;
//
//			fDistance = g_NowVector_Bullet[nCntEnemy].x * g_NowVector_Bullet[nCntEnemy].x + g_NowVector_Bullet[nCntEnemy].y * g_NowVector_Bullet[nCntEnemy].y;
//
//			if (fMinDistance > fDistance)
//			{
//				fMinDistance = fDistance;
//				nEnemyNearest = nCntEnemy;
//			}
//		}
//	}
//
//	g_aBullet[nCnt].nTarget = nEnemyNearest;
//}

//************************************************
//弾処理分別関数
//************************************************
void Sort_BulletStyle(int nCnt)
{
	switch (g_aBullet[nCnt].style)
	{
	case BULLETSTYLE_COMET:

		Updateinfo_Comet(nCnt);

		break;

	case BULLETSTYLE_REUNION:

		Updateinfo_Reunion(nCnt);

		break;

	case BULLETSTYLE_KING:

		Updateinfo_King(nCnt);

		break;
	}
}

//************************************************
//通常弾処理関数
//************************************************
void Updateinfo_Comet(int nCnt)
{
	//ポインタ
	VERTEX_2D* pVtx_Bullet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bullet->Lock(0, 0, (void**)&pVtx_Bullet, 0);

	//その順番のヤツにスキップ
	pVtx_Bullet += AMOUNT_VTX * nCnt;

	//弾の残存時間を減らす
	g_aBullet[nCnt].nRemain--;

	//残存時間が0
	if (g_aBullet[nCnt].nRemain <= 0)
	{
		SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, 0.0f);

		g_aBullet[nCnt].pos = D3DXVECTOR3(-1000.0f, -1000.0f, 0.0f);

		//今回の弾の使用判定を無くす
		g_aBullet[nCnt].bUse = false;
	}

	//移動
	g_aBullet[nCnt].pos.x += g_aBullet[nCnt].move.x;

	//弾道エフェクト
	Setinfo_Effect_Bullet(g_aBullet[nCnt].pos, g_aBullet[nCnt].move, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	//回転
	g_aBullet[nCnt].rot.z += g_aBullet[nCnt].move.z;

	//最後に弾の移動量に合わせて頂点も更新
	pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x + sinf(g_aBullet[nCnt].rot.z - (D3DX_PI - g_aBullet[nCnt].fAngle)) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y + cosf(g_aBullet[nCnt].rot.z - (D3DX_PI - g_aBullet[nCnt].fAngle)) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + sinf(g_aBullet[nCnt].rot.z + (D3DX_PI - g_aBullet[nCnt].fAngle)) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y + cosf(g_aBullet[nCnt].rot.z + (D3DX_PI - g_aBullet[nCnt].fAngle)) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x + sinf(g_aBullet[nCnt].rot.z - g_aBullet[nCnt].fAngle) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + cosf(g_aBullet[nCnt].rot.z - g_aBullet[nCnt].fAngle) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + sinf(g_aBullet[nCnt].rot.z + g_aBullet[nCnt].fAngle) * g_aBullet[nCnt].fLength;
	pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + cosf(g_aBullet[nCnt].rot.z + g_aBullet[nCnt].fAngle) * g_aBullet[nCnt].fLength;

	//テクスチャを上手いこと調整
	pVtx_Bullet[0].tex = D3DXVECTOR2(0.0f + g_aBullet[nCnt].fTexX, 0.0f + g_aBullet[nCnt].fTexY);
	pVtx_Bullet[1].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET + g_aBullet[nCnt].fTexX, 0.0f + g_aBullet[nCnt].fTexY);
	pVtx_Bullet[2].tex = D3DXVECTOR2(0.0f + g_aBullet[nCnt].fTexX, PER_ONE_TEX_Y_COMET_BULLET + g_aBullet[nCnt].fTexY);
	pVtx_Bullet[3].tex = D3DXVECTOR2(PER_ONE_TEX_X_COMET_BULLET + g_aBullet[nCnt].fTexX, PER_ONE_TEX_Y_COMET_BULLET + g_aBullet[nCnt].fTexY);

	//テクスチャ変化遅延
	g_aBullet[nCnt].nPattern++;

	//テクスチャが変化
	if (g_aBullet[nCnt].nPattern > CHEANGE_SPD_TEX_COMET_BULLET)
	{
		g_aBullet[nCnt].fTexX += PER_ONE_TEX_X_COMET_BULLET;

		if (g_aBullet[nCnt].fTexX >= 1.0f)
		{
			g_aBullet[nCnt].fTexX = 0.0f;

			g_aBullet[nCnt].fTexY += PER_ONE_TEX_Y_COMET_BULLET;

			if (g_aBullet[nCnt].fTexY >= 1.0f)
			{
				g_aBullet[nCnt].fTexY = 0.0f;
			}
		}

		g_aBullet[nCnt].nPattern = 0;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Bullet->Unlock();
}

//************************************************
//強化弾処理関数
//************************************************
void Updateinfo_Reunion(int nCnt)
{
	//ポインタ
	VERTEX_2D* pVtx_Bullet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bullet->Lock(0, 0, (void**)&pVtx_Bullet, 0);

	//その順番のヤツにスキップ
	pVtx_Bullet += AMOUNT_VTX * nCnt;

	//移動量変化
	g_aBullet[nCnt].move.x = sinf(D3DX_PI * g_aBullet[nCnt].fAngle);
	g_aBullet[nCnt].move.y = cosf(D3DX_PI * g_aBullet[nCnt].fAngle);

	switch (g_aBullet[nCnt].rute)
	{
	case BULLETRUTE_UP:

		//弾の角度が変動
		g_aBullet[nCnt].fAngle += MOVE_ANGLE_REUNION_BULLET;

		g_aBullet[nCnt].pos.x -= g_aBullet[nCnt].move.x * MOVE_SPD_POS_BULLET;
		g_aBullet[nCnt].pos.y += g_aBullet[nCnt].move.y * MOVE_SPD_POS_BULLET;

		break;

	case BULLETRUTE_DOWN:

		//弾の角度が変動
		g_aBullet[nCnt].fAngle += MOVE_ANGLE_REUNION_BULLET;

		g_aBullet[nCnt].pos.x -= g_aBullet[nCnt].move.x * MOVE_SPD_POS_BULLET;
		g_aBullet[nCnt].pos.y -= g_aBullet[nCnt].move.y * MOVE_SPD_POS_BULLET;

		break;
	}

	//弾の残存時間を減らす
	g_aBullet[nCnt].nRemain--;

	//残存時間が0
	if (g_aBullet[nCnt].nRemain <= 0)
	{
		//今回の弾の使用判定を無くす
		g_aBullet[nCnt].bUse = false;
	}

	//最後に弾の移動量に合わせて頂点も更新
	pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET * 0.5f;
	pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET * 0.5f;
	pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET * 0.5f;
	pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_Y_BULLET * 0.5f;
	pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_X_BULLET * 0.5f;
	pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET * 0.5f;
	pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_X_BULLET * 0.5f;
	pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_Y_BULLET * 0.5f;

	//頂点バッファをアンロックする
	g_pVtxBuff_Bullet->Unlock();
}

//************************************************
//一撃必殺弾処理関数
//************************************************
void Updateinfo_King(int nCnt)
{
	//ポインタ
	VERTEX_2D* pVtx_Bullet;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Bullet->Lock(0, 0, (void**)&pVtx_Bullet, 0);

	//その順番のヤツにスキップ
	pVtx_Bullet += AMOUNT_VTX * nCnt;

	//中心位置位置が移動し
	g_aBullet[nCnt].pos.x += g_aBullet[nCnt].move.x;

	//弾の残存時間を減らす
	g_aBullet[nCnt].nRemain--;

	//残存時間が0
	if (g_aBullet[nCnt].nRemain <= 0)
	{
		//今回の弾の使用判定を無くす
		g_aBullet[nCnt].bUse = false;
	}

	//最後に弾の移動量に合わせて頂点も更新
	pVtx_Bullet[0].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_KNIFE_X_BULLET;
	pVtx_Bullet[0].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_KNIFE_Y_BULLET;
	pVtx_Bullet[1].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_KNIFE_X_BULLET;
	pVtx_Bullet[1].pos.y = g_aBullet[nCnt].pos.y - HALFSPAN_KNIFE_Y_BULLET;
	pVtx_Bullet[2].pos.x = g_aBullet[nCnt].pos.x - HALFSPAN_KNIFE_X_BULLET;
	pVtx_Bullet[2].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_KNIFE_Y_BULLET;
	pVtx_Bullet[3].pos.x = g_aBullet[nCnt].pos.x + HALFSPAN_KNIFE_X_BULLET;
	pVtx_Bullet[3].pos.y = g_aBullet[nCnt].pos.y + HALFSPAN_KNIFE_Y_BULLET;

	//頂点バッファをアンロックする
	g_pVtxBuff_Bullet->Unlock();
}

//************************************************
//敵(もや)への当たり判定処理関数
//************************************************
void HitDetection_Cloud_Enemy(int nCnt)
{
	ENEMY* pEnemy;

	pEnemy = Getinfo_Enemy();

	//敵(もや)の数分、当たり判定処理を回す
	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_POLYGON_ENEMY; nCntEnemy++)
	{
		//敵が使用されている時
		if (pEnemy[nCntEnemy].bUse == true && pEnemy[nCntEnemy].nCntSpawn <= 0)
		{
			//弾が円形の時
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//弾の位置から敵の位置へのベクトルを格納
				D3DXVECTOR3 CollisionVector = pEnemy[nCntEnemy].pos - g_aBullet[nCnt].pos;

				//弾の位置と敵の位置の距離
				float fDistance = sqrtf(CollisionVector.x * CollisionVector.x + CollisionVector.y * CollisionVector.y);

				//敵の本体の持つ当たり判定内に弾が入った時
				if (fDistance < g_fRadius_Bullet + g_fRadius_EnemyCore_Bullet)
				{
					//弾の使用を解除
					g_aBullet[nCnt].bUse = false;

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//消滅エフェクト
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pEnemy[nCntEnemy].move.x);
					}

					//ダメージ量を送る
					if (pEnemy[nCntEnemy].state != ENEMYSTATE_DAMAGE)
					{
						Hit_Cloud_Enemy(nCntEnemy, g_aBullet[nCnt].nDamage);
					}
				}
			}
			//ナイフの時
			else
			{
				if (g_aBullet[nCnt].pos.x <= pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].fHalfSpanX + HALFSPAN_KNIFE_X_BULLET &&
					g_aBullet[nCnt].pos.x >= pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].fHalfSpanX - HALFSPAN_KNIFE_X_BULLET &&
					g_aBullet[nCnt].pos.y >= pEnemy[nCntEnemy].pos.y - pEnemy[nCntEnemy].fHalfSpanY - HALFSPAN_KNIFE_Y_BULLET &&
					g_aBullet[nCnt].pos.y <= pEnemy[nCntEnemy].pos.y + pEnemy[nCntEnemy].fHalfSpanY + HALFSPAN_KNIFE_Y_BULLET)
				{
					//弾の使用を解除
					g_aBullet[nCnt].bUse = false;

					//ダメージ量を送る
					Hit_Cloud_Enemy(nCntEnemy, g_aBullet[nCnt].nDamage);

					//10点あげますよ
					Add_Score(AMOUNT_ADD_SCORE_BULLET);
				}
			}
		}
	}
}

//************************************************
//敵(飛翔)への当たり判定処理関数
//************************************************
void HitDetection_Glide_Enemy(int nCnt)
{
	ENEMY_GLIDE* pEnemy_Glide;

	pEnemy_Glide = Getinfo_Enemy_Glide();

	//敵(飛翔)の数分、当たり判定処理を回す
	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_POLYGON_ENEMY_GLIDE; nCntEnemy++)
	{
		//敵が使用されている時
		if (pEnemy_Glide[nCntEnemy].bUse == true && pEnemy_Glide[nCntEnemy].nCntSpawn <= 0)
		{
			//弾と敵が円形の時
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//弾の位置から敵の位置へのベクトルを格納
				D3DXVECTOR3 CollisionVector = pEnemy_Glide[nCntEnemy].pos - g_aBullet[nCnt].pos;

				//弾の位置と敵の位置の距離
				float fDistance = sqrtf(CollisionVector.x * CollisionVector.x + CollisionVector.y * CollisionVector.y);

				//敵の本体の持つ当たり判定内に弾が入った時
				if (fDistance < g_fRadius_Bullet + g_fRadius_EnemyCore_Bullet)
				{
					//弾の使用を解除
					g_aBullet[nCnt].bUse = false;

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//消滅エフェクト
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pEnemy_Glide[nCntEnemy].move.x);
					}

					//その時の敵の番号とダメージ量を送る(敵の種類に応じて変更予定)
					if (pEnemy_Glide[nCntEnemy].state != ENEMYSTATE_DAMAGE)
					{
						Hit_Glide_Enemy(nCntEnemy, g_aBullet[nCnt].nDamage);
					}
				}
			}
		}
	}
}

//************************************************
//敵(移動)への当たり判定処理関数
//************************************************
void HitDetection_Slide_Enemy(int nCnt)
{
	ENEMY_SLIDE* pEnemy_Slide;

	pEnemy_Slide = Getinfo_Enemy_Slide();

	//敵(移動)の数分、当たり判定処理を回す
	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_POLYGON_ENEMY_SLIDE; nCntEnemy++)
	{
		//敵が使用されている時
		if (pEnemy_Slide[nCntEnemy].bUse == true && pEnemy_Slide[nCntEnemy].nCntSpawn <= 0)
		{
			//弾と敵が円形の時
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//敵の本体の持つ当たり判定内に弾が入った時
				if (g_aBullet[nCnt].pos.x <= pEnemy_Slide[nCntEnemy].pos.x + pEnemy_Slide[nCntEnemy].fHalfSpanX + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.x >= pEnemy_Slide[nCntEnemy].pos.x - pEnemy_Slide[nCntEnemy].fHalfSpanX - g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y <= pEnemy_Slide[nCntEnemy].pos.y + pEnemy_Slide[nCntEnemy].fHalfSpanY + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y >= pEnemy_Slide[nCntEnemy].pos.y - pEnemy_Slide[nCntEnemy].fHalfSpanY - g_fRadius_Bullet)
				{
					//弾の使用を解除
					g_aBullet[nCnt].bUse = false;

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//消滅エフェクト
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pEnemy_Slide[nCntEnemy].move.x);
					}

					//ダメージ量を送る
					if (pEnemy_Slide[nCntEnemy].state != ENEMYSTATE_DAMAGE)
					{
						Hit_Slide_Enemy(nCntEnemy, g_aBullet[nCnt].nDamage);
					}
				}
			}
		}
	}
}

//************************************************
//敵(貫通)への当たり判定処理関数
//************************************************
void HitDetection_Spiral_Enemy(int nCnt)
{
	ENEMY_SPIRAL* pEnemy_Spiral;

	pEnemy_Spiral = Getinfo_Enemy_Spiral();

	//敵(移動)の数分、当たり判定処理を回す
	for (int nCntEnemy = 0; nCntEnemy < AMOUNT_POLYGON_ENEMY_SPIRAL; nCntEnemy++)
	{
		//敵が使用されている時
		if (pEnemy_Spiral[nCntEnemy].bUse == true && pEnemy_Spiral[nCntEnemy].nCntSpawn <= 0)
		{
			//弾と敵が円形の時
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//敵の本体の持つ当たり判定内に弾が入った時
				if (g_aBullet[nCnt].pos.x <= pEnemy_Spiral[nCntEnemy].pos.x + pEnemy_Spiral[nCntEnemy].fHalfSpanX + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.x >= pEnemy_Spiral[nCntEnemy].pos.x - pEnemy_Spiral[nCntEnemy].fHalfSpanX - g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y <= pEnemy_Spiral[nCntEnemy].pos.y + pEnemy_Spiral[nCntEnemy].fHalfSpanY + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y >= pEnemy_Spiral[nCntEnemy].pos.y - pEnemy_Spiral[nCntEnemy].fHalfSpanY - g_fRadius_Bullet)
				{
					//弾の使用を解除
					g_aBullet[nCnt].bUse = false;

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//消滅エフェクト
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pEnemy_Spiral[nCntEnemy].move.x);
					}

					//ダメージ量を送る
					if (pEnemy_Spiral[nCntEnemy].state != ENEMYSTATE_DAMAGE)
					{
						Hit_Spiral_Enemy(nCntEnemy, g_aBullet[nCnt].nDamage);
					}
				}
			}
		}
	}
}

//************************************************
//ブロックへの当たり判定処理関数
//************************************************
void HitDetection_Block(int nCnt)
{
	BLOCK* pBlock;

	pBlock = Getinfo_Block();

	//ブロックの数分当たり判定を回す
	for (int nCntBlock = 0; nCntBlock < AMOUNT_POLYGON_BLOCK; nCntBlock++)
	{
		//ブロックの使用されている時
		if (pBlock[nCntBlock].bUse && pBlock[nCntBlock].nCntSpawn <= 0)
		{
			//弾が円形の時
			if (g_aBullet[nCnt].pos.x <= pBlock[nCntBlock].pos.x + pBlock[nCntBlock].fHalfSpanX + g_fRadius_Bullet &&
				g_aBullet[nCnt].pos.x >= pBlock[nCntBlock].pos.x - pBlock[nCntBlock].fHalfSpanX - g_fRadius_Bullet &&
				g_aBullet[nCnt].pos.y <= pBlock[nCntBlock].pos.y + pBlock[nCntBlock].fHalfSpanY + g_fRadius_Bullet &&
				g_aBullet[nCnt].pos.y >= pBlock[nCntBlock].pos.y - pBlock[nCntBlock].fHalfSpanY - g_fRadius_Bullet)
			{
				//弾の使用を解除
				g_aBullet[nCnt].bUse = false;

				if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
				{
					//消滅エフェクト
					SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pBlock[nCntBlock].move.x);
				}
			}
		}
	}
}

//************************************************
//スライドブロックへの当たり判定処理関数
//************************************************
void HitDetection_SlideBlock(int nCnt)
{
	SLIDEBLOCK* pSlideBlock;

	pSlideBlock = Getinfo_SlideBlock();

	//スライドブロックの数分当たり判定を回す
	for (int nCntSlideBlock = 0; nCntSlideBlock < AMOUNT_POLYGON_SLIDEBLOCK; nCntSlideBlock++)
	{
		//スライドブロックが使用されている時
		if (pSlideBlock[nCntSlideBlock].bUse && pSlideBlock[nCntSlideBlock].nCntSpawn <= 0)
		{
			//弾が円形の時
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//ブロックに当たった
				if (g_aBullet[nCnt].pos.x <= pSlideBlock[nCntSlideBlock].pos.x + pSlideBlock[nCntSlideBlock].fHalfSpanX + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.x >= pSlideBlock[nCntSlideBlock].pos.x - pSlideBlock[nCntSlideBlock].fHalfSpanX - g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y <= pSlideBlock[nCntSlideBlock].pos.y + pSlideBlock[nCntSlideBlock].fHalfSpanY + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y >= pSlideBlock[nCntSlideBlock].pos.y - pSlideBlock[nCntSlideBlock].fHalfSpanY - g_fRadius_Bullet)
				{
					//弾の使用を解除
					g_aBullet[nCnt].bUse = false;

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//消滅エフェクト
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pSlideBlock[nCntSlideBlock].move.x);
					}
				}
			}
		}
	}
}

//************************************************
//ブレイクブロックへの当たり判定処理関数
//************************************************
void HitDetection_BreakBlock(int nCnt)
{
	BREAKBLOCK* pBreakBlock;

	pBreakBlock = Getinfo_BreakBlock();

	//ブレイクブロックの数分当たり判定を回す
	for (int nCntBreakBlock = 0; nCntBreakBlock < AMOUNT_POLYGON_BREAKBLOCK; nCntBreakBlock++)
	{
		//ブレイクブロックの使用されている時
		if (pBreakBlock[nCntBreakBlock].bUse && pBreakBlock[nCntBreakBlock].nCntSpawn <= 0)
		{
			//弾が円形の時
			if (g_aBullet[nCnt].style != BULLETSTYLE_KING)
			{
				//ブロックに当たった
				if (g_aBullet[nCnt].pos.x <= pBreakBlock[nCntBreakBlock].pos.x + pBreakBlock[nCntBreakBlock].fHalfSpanX + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.x >= pBreakBlock[nCntBreakBlock].pos.x - pBreakBlock[nCntBreakBlock].fHalfSpanX - g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y <= pBreakBlock[nCntBreakBlock].pos.y + pBreakBlock[nCntBreakBlock].fHalfSpanY + g_fRadius_Bullet &&
					g_aBullet[nCnt].pos.y >= pBreakBlock[nCntBreakBlock].pos.y - pBreakBlock[nCntBreakBlock].fHalfSpanY - g_fRadius_Bullet)
				{
					//弾の使用を解除
					g_aBullet[nCnt].bUse = false;

					Hit_BreakBlock(nCntBreakBlock, g_aBullet[nCnt].nDamage);

					if (g_aBullet[nCnt].style == BULLETSTYLE_COMET)
					{
						//消滅エフェクト
						SetPos_Vtx_Effect_Comet(g_aBullet[nCnt].pos, pBreakBlock[nCntBreakBlock].move.x);
					}
				}
			}
		}
	}
}