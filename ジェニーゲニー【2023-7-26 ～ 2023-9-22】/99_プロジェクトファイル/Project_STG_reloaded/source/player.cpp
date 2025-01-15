//************************************************
//
//自機処理[player.cpp]
//Author：福田歩希
//
//************************************************
#include "input.h"
#include "main.h"
#include "sound.h"
#include "bullet.h"
#include "life.h"
#include "particle.h"
#include "player.h"
#include "timer.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Player = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Player = NULL;	//頂点バッファのポインタ
PLAYER g_aPlayer;	//構造体の中の情報を引き渡す用
int g_nChoosingBulletStyle_Player = 0;	//選択している弾の種類
int g_nCnt_Shot_Vulkan = 0;	//バルカン発射用キャストタイム
int g_nColorR_Player = 0;	//色変更用
int g_nColorG_Player = 0;
int g_nColorB_Player = 0;
int g_nColorA_Player = 0;
int g_nCntIncreaseCapacity_Player = 0;	//キャパ回復用キャスト時間

float g_texLine = 0.0f;
int g_nCntLine = 0;
float g_texRow = 0.0f;
int g_nCntRow = 0;

bool g_bShooting = false;
int g_nCntShooting = 0;
int g_nCntShootingLine = 0;

/*デバッグ用無敵*/
bool STAR = false;
bool GOD = false;

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Player()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_PLAYER,
		&g_pTexture_Player);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Player,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Player;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	//頂点座標の初期設定
	pVtx_Player[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Player[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Player[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx_Player[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視錐台の拡大率(?)の初期設定
	pVtx_Player[0].rhw = 1.0f;
	pVtx_Player[1].rhw = 1.0f;
	pVtx_Player[2].rhw = 1.0f;
	pVtx_Player[3].rhw = 1.0f;

	//頂点カラーの初期設定
	pVtx_Player[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Player[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Player[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx_Player[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の初期設定
	pVtx_Player[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Player[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Player[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Player[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Player->Unlock();

	//構造体内情報を初期化
	g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//座標初期化
	g_aPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量初期化
	g_aPlayer.state = PLAYERSTATE_NORMAL;			//初期状態は通常
	g_aPlayer.nCntState = 0;						//状態継続時間初期化
	g_aPlayer.nLife = AMOUNT_LIFE_PLAYER;			//体力初期設定
	g_aPlayer.nCapacity = AMOUNT_CAPACITY_PLAYER;	//キャパシティ初期設定

	//選択している弾の種類を初期化
	g_nChoosingBulletStyle_Player = 0;

	//マシンガン用のキャストを初期化
	g_nCnt_Shot_Vulkan = 0;

	//色変更用変数の初期化
	g_nColorR_Player = 255;
	g_nColorG_Player = 255;
	g_nColorB_Player = 255;
	g_nColorA_Player = 255;
	
	//キャパ回復用キャスト初期化
	g_nCntIncreaseCapacity_Player = 0;

	//スポーン地点の設定
	g_aPlayer.pos = D3DXVECTOR3(POS_X_SPAWN_PLAYER, POS_Y_SPAWN_PLAYER, 0.0f);

	g_texLine = 0.0f;
	g_nCntLine = 0;
	g_texRow = 0.0f;
	g_nCntRow = 0;

	g_bShooting = false;
	g_nCntShooting = 0;
	g_nCntShootingLine = 0;

	//一度だけ展開しておく
	Update_Player();
	Draw_Player();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Player(void)
{
	//テクスチャの破棄
	if (g_pTexture_Player != NULL)
	{
		g_pTexture_Player->Release();
		g_pTexture_Player = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Player != NULL)
	{
		g_pVtxBuff_Player->Release();
		g_pVtxBuff_Player = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Player(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Player;

	//制限時間情報へのポインタ
	int* pTimer;

	//制限時間を代入
	pTimer = Getinfo_Timer();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	/**********デバッグ用処理あり***********/
	if (g_aPlayer.nCapacity <= AMOUNT_CAPACITY_PLAYER && !GOD)
	{
		g_nCntIncreaseCapacity_Player++;

		if (g_nCntIncreaseCapacity_Player >= AMOUNT_CNT_CAPACITY_PLAYER)
		{
			g_aPlayer.nCapacity++;

			g_nCntIncreaseCapacity_Player = 0;
		}

		if (g_aPlayer.nCapacity >= AMOUNT_CAPACITY_PLAYER)
		{
			g_aPlayer.nCapacity = AMOUNT_CAPACITY_PLAYER;
		}
	}

	/**********デバッグ用処理あり***********/
	if (GOD)
	{
		g_aPlayer.nCapacity = AMOUNT_CAPACITY_PLAYER;
	}

	//プレイヤーが生きているとき、または時間生存(要改善処理)
	if (g_aPlayer.state != PLAYERSTATE_DEATH && *pTimer > 0)
	{
		//左方
		if (GetKeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
		{
			if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
			{
				//左上入力をされた時
				g_aPlayer.move.x += sinf(-D3DX_PI * 0.75f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(-D3DX_PI * 0.75f) * MOVE_SPD_POS_PLAYER;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
			{
				//左下入力をされた時
				g_aPlayer.move.x += sinf(-D3DX_PI * 0.25f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(-D3DX_PI * 0.25f) * MOVE_SPD_POS_PLAYER;
			}
			else
			{
				//左のみ入力された時
				g_aPlayer.move.x += sinf(-D3DX_PI * 0.5f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(-D3DX_PI * 0.5f) * MOVE_SPD_POS_PLAYER;
			}
		}
		//右方
		else if (GetKeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true)
		{
			if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
			{
				//右上入力をされた時
				g_aPlayer.move.x += sinf(D3DX_PI * 0.75f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(D3DX_PI * 0.75f) * MOVE_SPD_POS_PLAYER;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
			{
				//右下入力をされた時
				g_aPlayer.move.x += sinf(D3DX_PI * 0.25f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(D3DX_PI * 0.25f) * MOVE_SPD_POS_PLAYER;
			}
			else
			{
				//右のみ入力された時
				g_aPlayer.move.x += sinf(D3DX_PI * 0.5f) * MOVE_SPD_POS_PLAYER;
				g_aPlayer.move.y += cosf(D3DX_PI * 0.5f) * MOVE_SPD_POS_PLAYER;
			}
		}
		//下降
		else if (GetKeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
		{
			g_aPlayer.move.x += sinf(D3DX_PI * 0.0f) * MOVE_SPD_POS_PLAYER;
			g_aPlayer.move.y += cosf(D3DX_PI * 0.0f) * MOVE_SPD_POS_PLAYER;
		}
		//上昇
		else if (GetKeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
		{
			g_aPlayer.move.x += sinf(D3DX_PI * 0.0f) * MOVE_SPD_POS_PLAYER;
			g_aPlayer.move.y += cosf(D3DX_PI * 1.0f) * MOVE_SPD_POS_PLAYER;
		}

		/*自由に変更できなくなり…*/
		////弾の種類変更
		//if (GetKeyboardTrigger(DIK_LEFT) == true)
		//{
		//	g_nChoosingBulletStyle_Player--;
		//}
		//else if (GetKeyboardTrigger(DIK_RIGHT) == true)
		//{
		//	g_nChoosingBulletStyle_Player++;
		//}

		////変更しすぎの時
		//if (g_nChoosingBulletStyle_Player < 0)
		//{
		//	//一番左に行くと一番右に戻る
		//	g_nChoosingBulletStyle_Player = BULLETSTYLE_WONDER;
		//}
		//else if (g_nChoosingBulletStyle_Player > BULLETSTYLE_WONDER)
		//{
		//	//一番右に行くと一番左に戻る
		//	g_nChoosingBulletStyle_Player = 0;
		//}

		//弾発射
		switch (g_nChoosingBulletStyle_Player)
		{
		case BULLETSTYLE_COMET:

			if (GetKeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_X) == true)
			{
				g_bShooting = true;

				g_nCntLine = 0;
				g_texRow = 2;

				//プレイヤー座標と選択している弾の種類を送る
				Setinfo_Bullet(g_aPlayer.pos, g_nChoosingBulletStyle_Player);
			}

			break;

		case BULLETSTYLE_REUNION:

			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{
				//プレイヤー座標と選択している弾の種類を送る
				Setinfo_Bullet(g_aPlayer.pos, g_nChoosingBulletStyle_Player);
			}

			break;

		case BULLETSTYLE_KING:

			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{
				//プレイヤー座標と選択している弾の種類を送る
				Setinfo_Bullet(g_aPlayer.pos, g_nChoosingBulletStyle_Player);
			}

			break;
		}
	}

	//X方向慣性
	if (g_aPlayer.pos.x - HALFSPAN_X_PLAYER - g_aPlayer.move.x >= SPAN_OUTSIDE_BORDER &&
		g_aPlayer.pos.x + HALFSPAN_X_PLAYER + g_aPlayer.move.x <= SCREEN_WIDTH - SPAN_OUTSIDE_BORDER)
	{
		//画面内にプレイヤーがいるとき横移動減衰
		g_aPlayer.move.x += (0.0f - g_aPlayer.move.x) * ATTENUATION_SPD_POS_PLAYER;
	}
	else if (g_aPlayer.pos.x - HALFSPAN_X_PLAYER <= SPAN_OUTSIDE_BORDER)
	{
		//左端にぶつかった瞬間、強制反発
		g_aPlayer.move.x = PUSHBACK_WALL_PLAYER;
	}
	else if (g_aPlayer.pos.x + HALFSPAN_X_PLAYER >= SCREEN_WIDTH - SPAN_OUTSIDE_BORDER)
	{
		//右端も
		g_aPlayer.move.x = -PUSHBACK_WALL_PLAYER;
	}

	//Y方向慣性
	if (g_aPlayer.pos.y - HALFSPAN_Y_PLAYER >= SPAN_OUTSIDE_BORDER &&
		g_aPlayer.pos.y + HALFSPAN_Y_PLAYER <= SCREEN_HEIGHT - SPAN_OUTSIDE_BORDER)
	{
		//画面内にプレイヤーがいるとき縦移動減衰
		g_aPlayer.move.y += (0.0f - g_aPlayer.move.y) * ATTENUATION_SPD_POS_PLAYER;
	}
	else if (g_aPlayer.pos.y - HALFSPAN_Y_PLAYER <= SPAN_OUTSIDE_BORDER)
	{
		//上端にぶつかった瞬間、強制反発
		g_aPlayer.move.y = PUSHBACK_WALL_PLAYER;
	}
	else if (g_aPlayer.pos.y + HALFSPAN_Y_PLAYER >= SCREEN_HEIGHT - SPAN_OUTSIDE_BORDER)
	{
		//下端にぶつかった瞬間、強制反発
		g_aPlayer.move.y = -PUSHBACK_WALL_PLAYER;
	}

	//位置情報を随時更新
	g_aPlayer.pos.x += g_aPlayer.move.x;
	g_aPlayer.pos.y += g_aPlayer.move.y;

	//座標の更新
	pVtx_Player[0].pos.x = g_aPlayer.pos.x - HALFSPAN_X_PLAYER;
	pVtx_Player[0].pos.y = g_aPlayer.pos.y - HALFSPAN_Y_PLAYER;
	pVtx_Player[1].pos.x = g_aPlayer.pos.x + HALFSPAN_X_PLAYER;
	pVtx_Player[1].pos.y = g_aPlayer.pos.y - HALFSPAN_Y_PLAYER;
	pVtx_Player[2].pos.x = g_aPlayer.pos.x - HALFSPAN_X_PLAYER;
	pVtx_Player[2].pos.y = g_aPlayer.pos.y + HALFSPAN_Y_PLAYER;
	pVtx_Player[3].pos.x = g_aPlayer.pos.x + HALFSPAN_X_PLAYER;
	pVtx_Player[3].pos.y = g_aPlayer.pos.y + HALFSPAN_Y_PLAYER;

	//プレイヤーの状態に合わせて処理分岐
	switch (g_aPlayer.state)
	{
		//通常時
	case PLAYERSTATE_NORMAL:

		//色を通常にセット
		g_nColorG_Player = 255;
		g_nColorB_Player = 255;
		g_nColorA_Player = 255;

		break;

		//被弾時
	case PLAYERSTATE_DAMAGE:

		//状態持続を減らす
		g_aPlayer.nCntState--;

		//経過した時
		if (g_aPlayer.nCntState <= 0)
		{
			//通常状態に変更
			g_aPlayer.state = PLAYERSTATE_NORMAL;
		}

		//色変更
		g_nColorG_Player *= -1;
		g_nColorB_Player *= -1;
		g_nColorA_Player *= -1;

		break;

	case PLAYERSTATE_DEATH:

		//色変更
		g_nColorR_Player -= 25;
		g_nColorG_Player -= 25;
		g_nColorB_Player -= 25;
		g_nColorA_Player -= 25;

		if (g_nColorR_Player < 30)
		{
			g_nColorR_Player = 30;
			g_nColorG_Player = 30;
			g_nColorB_Player = 30;
			g_nColorA_Player = 30;
		}

		break;
	}

	//色情報の更新
	pVtx_Player[0].col = D3DCOLOR_RGBA(g_nColorR_Player, g_nColorG_Player, g_nColorB_Player, g_nColorA_Player);
	pVtx_Player[1].col = D3DCOLOR_RGBA(g_nColorR_Player, g_nColorG_Player, g_nColorB_Player, g_nColorA_Player);
	pVtx_Player[2].col = D3DCOLOR_RGBA(g_nColorR_Player, g_nColorG_Player, g_nColorB_Player, g_nColorA_Player);
	pVtx_Player[3].col = D3DCOLOR_RGBA(g_nColorR_Player, g_nColorG_Player, g_nColorB_Player, g_nColorA_Player);

	//頂点バッファをアンロックする
	g_pVtxBuff_Player->Unlock();

	Animation_Player();

	///********デバッグ用*******/
	//if (GetKeyboardTrigger(DIK_4) == true)
	//{
	//	//ライフ減少
	//	g_aPlayer.nLife--;
	//}
	//if (GetKeyboardTrigger(DIK_5) == true && g_aPlayer.nLife < AMOUNT_LIFE_MAX)
	//{
	//	//ライフ増加
	//	g_aPlayer.nLife++;
	//}
	//if (GetKeyboardTrigger(DIK_6) == true)
	//{
	//	//無敵
	//	STAR = STAR ? false : true;
	//}
	//if (GetKeyboardTrigger(DIK_X) == true)
	//{
	//	//キャパシティ無限
	//	GOD = GOD ? false : true;
	//}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Player(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Player, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexture_Player);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//プレイヤー情報のアドレスを渡す関数
//************************************************
PLAYER *Getinfo_Player(void)
{
	return &g_aPlayer;	//PLAYER分の情報を引き渡す
}

//************************************************
//プレイヤーへの命中処理関数
//************************************************
void Hit_Player(int nDamage)
{
	//効果音を鳴らす
	PlaySound(SOUND_LABEL_SE_DAMAGE);

	//バイブ
	SetVibration(AMOUNT_CNT_STATE_PLAYER, 65535);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Player;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	//命中に伴いライフを減らす
	/********デバッグ用*********/
	if (!STAR)
	{
		g_aPlayer.nLife -= nDamage;
	}

	//プレイヤーがまだ生きている場合
	if (g_aPlayer.nLife > 0)
	{
		//プレイヤーをダメージ状態に
		g_aPlayer.state = PLAYERSTATE_DAMAGE;

		//ダメージ状態継続時間設定
		g_aPlayer.nCntState = AMOUNT_CNT_STATE_PLAYER;
	}
	//死んでしまったとき
	else
	{
		//プレイヤーを死亡状態に
		g_aPlayer.state = PLAYERSTATE_DEATH;

		//死亡状態継続時間設定
		g_aPlayer.nCntState = AMOUNT_CNT_STATE_PLAYER;

		g_nColorR_Player = 255;
		g_nColorG_Player = 255;
		g_nColorB_Player = 255;
		g_nColorA_Player = 255;
	}
}

//************************************************
//アイテムの取得処理処理関数
//************************************************
void GetItem_Player(int nIncreaseCapacity)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Player;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	//キャパシティを回復
	g_aPlayer.nCapacity += nIncreaseCapacity;

	//オーバー切り捨て
	g_aPlayer.nCapacity >= AMOUNT_CAPACITY_PLAYER ? g_aPlayer.nCapacity = AMOUNT_CAPACITY_PLAYER : 0;

	//頂点バッファをアンロックする
	g_pVtxBuff_Player->Unlock();
}

//************************************************
//弾の種類選択情報のアドレスを渡す関数
//************************************************
int* Getinfo_BulletStyle(void)
{
	return &g_nChoosingBulletStyle_Player;	//現在の弾の種類情報を引き渡す
}

//************************************************
//テクスチャアニメーション関数
//************************************************
void Animation_Player(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Player;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	//テクスチャ座標の初期設定
	if (!g_bShooting)
	{
		pVtx_Player[0].tex = D3DXVECTOR2(0.0f + (0.14285f * g_texLine), 0.0f + (0.33333f * g_texRow));
		pVtx_Player[1].tex = D3DXVECTOR2(0.14285f + (0.14285f * g_texLine), 0.0f + (0.33333f * g_texRow));
		pVtx_Player[2].tex = D3DXVECTOR2(0.0f + (0.14285f * g_texLine), 0.33333f + (0.33333f * g_texRow));
		pVtx_Player[3].tex = D3DXVECTOR2(0.14285f + (0.14285f * g_texLine), 0.33333f + (0.33333f * g_texRow));
	}
	else
	{
		//ポリゴンサイズの調整
		pVtx_Player[0].pos.x = g_aPlayer.pos.x - HALFSPAN_X_PLAYER;
		pVtx_Player[0].pos.y = g_aPlayer.pos.y - HALFSPAN_Y_PLAYER * 1.05f;
		pVtx_Player[1].pos.x = g_aPlayer.pos.x + HALFSPAN_X_PLAYER * 1.45f;
		pVtx_Player[1].pos.y = g_aPlayer.pos.y - HALFSPAN_Y_PLAYER * 1.05f;
		pVtx_Player[2].pos.x = g_aPlayer.pos.x - HALFSPAN_X_PLAYER;
		pVtx_Player[2].pos.y = g_aPlayer.pos.y + HALFSPAN_Y_PLAYER * 1.05f;
		pVtx_Player[3].pos.x = g_aPlayer.pos.x + HALFSPAN_X_PLAYER * 1.45f;
		pVtx_Player[3].pos.y = g_aPlayer.pos.y + HALFSPAN_Y_PLAYER * 1.05f;

		pVtx_Player[0].tex = D3DXVECTOR2(0.0f + (0.14285f * g_nCntShootingLine), 0.0f + (0.33333f * g_texRow));
		pVtx_Player[1].tex = D3DXVECTOR2(0.14285f + (0.14285f * g_nCntShootingLine), 0.0f + (0.33333f * g_texRow));
		pVtx_Player[2].tex = D3DXVECTOR2(0.0f + (0.14285f * g_nCntShootingLine), 0.33333f + (0.33333f * g_texRow));
		pVtx_Player[3].tex = D3DXVECTOR2(0.14285f + (0.14285f * g_nCntShootingLine), 0.33333f + (0.33333f * g_texRow));
	}

	if (g_bShooting)
	{
		g_nCntShooting++;

		if (g_nCntShooting > 2)
		{
			g_nCntShooting = 0;
			g_nCntShootingLine++;

			if (g_nCntShootingLine > 6)
			{
				g_bShooting = false;
				g_nCntShooting = 0;
				g_nCntShootingLine = 0;
				g_nCntLine = 0;
				g_texRow = 0;
			}
		}
	}
	else
	{
		g_nCntLine++;

		if (g_nCntLine > 5)
		{
			g_nCntLine = 0;

			g_texLine++;

			if (g_texLine > 7)
			{
				g_texLine = 0;

				g_texRow = (float)(rand() % 2);
			}
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Player->Unlock();
}