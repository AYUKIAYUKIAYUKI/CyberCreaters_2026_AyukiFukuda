//************************************************
//
//自機処理[player.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "attack_box.h"
#include "bomb.h"
#include "camera.h"
#include "effect_jump.h"
#include "particle.h"
#include "player.h"
#include "stage.h"
#include "tower.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Player[AMOUNT_TEX_PLAYER] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Player = NULL;	//頂点バッファのポインタ
PLAYER g_aPlayer;	//プレイヤー情報
PLAYER_BOX g_aPlayer_Box[PLAYER_STATE_MAX];	//プレイヤーボックス情報

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
		TEXTURE_CHARACTER_IDLE_PLAYER,
		&g_pTexture_Player[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_JUMP_PLAYER,
		&g_pTexture_Player[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_LAND_PLAYER,
		&g_pTexture_Player[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_RUN_PLAYER,
		&g_pTexture_Player[3]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_LIGHT1_PLAYER,
		&g_pTexture_Player[4]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_LIGHT2_PLAYER,
		&g_pTexture_Player[5]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_LIGHT3_PLAYER,
		&g_pTexture_Player[6]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_HEAVY1_PLAYER,
		&g_pTexture_Player[7]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_HEAVY2_PLAYER,
		&g_pTexture_Player[8]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_HEAVY3_PLAYER,
		&g_pTexture_Player[9]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_HURT1_PLAYER,
		&g_pTexture_Player[10]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CHARACTER_HURT2_PLAYER,
		&g_pTexture_Player[11]);

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
	pVtx_Player[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Player[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Player[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx_Player[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx_Player[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx_Player[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx_Player[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx_Player[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuff_Player->Unlock();

	//プレイヤー構造体の情報の初期化群
	g_aPlayer.nState = PLAYER_STATE_IDLE;
	g_aPlayer.BGpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.lastland = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_aPlayer.LR = 0;
	g_aPlayer.nCntTex = 0;
	g_aPlayer.nCntPattern = 0;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aPlayer.fTexSpan[nCnt] = 0.0f;
		g_aPlayer.fRadius[nCnt] = 0.0f;
		g_aPlayer.fLength[nCnt] = 0.0f;
		g_aPlayer.fAngle[nCnt] = 0.0f;
	}
	g_aPlayer.bLanding = false;
	g_aPlayer.nJumpTimes = 0;
	//g_aPlayer.nLife = 0;
	g_aPlayer.bFell = false;
	g_aPlayer.nLastATK = 0;
	g_aPlayer.bAfterATK = false;
	g_aPlayer.nCntAfterATK = 0;

	//プレイヤーボックスの初期化
	for (int nCnt = 0; nCnt < PLAYER_STATE_MAX; nCnt++)
	{
		for (int nCntHold = 0; nCntHold < 2; nCntHold++)
		{
			g_aPlayer_Box[nCnt].fRadius_Hold[nCntHold];
			g_aPlayer_Box[nCnt].fLength_Hold[nCntHold];
			g_aPlayer_Box[nCnt].fAngle_Hold[nCntHold];
		}
	}

	//プレイヤーボックスの算出
	CalcSize_Player_Box();

	//プレイヤー構造体に情報を付与
	SetInfo_Player();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Player(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEX_PLAYER; nCnt++)
	{
		if (g_pTexture_Player[nCnt] != NULL)
		{
			g_pTexture_Player[nCnt]->Release();
			g_pTexture_Player[nCnt] = NULL;
		}
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
	//キー入力で移動する
	Move_Pos_Player();
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
	switch (g_aPlayer.nState)
	{
	case PLAYER_STATE_IDLE:
		pDevice->SetTexture(0, g_pTexture_Player[0]);
		break;
	case PLAYER_STATE_JUMP:
		pDevice->SetTexture(0, g_pTexture_Player[1]);
		break;
	case PLAYER_STATE_FALL:
		pDevice->SetTexture(0, g_pTexture_Player[1]);
		break;
	case PLAYER_STATE_LAND:
		pDevice->SetTexture(0, g_pTexture_Player[2]);
		break;
	case PLAYER_STATE_RUN:
		pDevice->SetTexture(0, g_pTexture_Player[3]);
		break;
	case PLAYER_STATE_LIGHT1:
		pDevice->SetTexture(0, g_pTexture_Player[4]);
		break;
	case PLAYER_STATE_LIGHT2:
		pDevice->SetTexture(0, g_pTexture_Player[5]);
		break;
	case PLAYER_STATE_LIGHT3:
		pDevice->SetTexture(0, g_pTexture_Player[6]);
		break;
	case PLAYER_STATE_HEAVY1:
		pDevice->SetTexture(0, g_pTexture_Player[7]);
		break;
	case PLAYER_STATE_HEAVY2:
		pDevice->SetTexture(0, g_pTexture_Player[8]);
		break;
	case PLAYER_STATE_HEAVY3:
		pDevice->SetTexture(0, g_pTexture_Player[9]);
		break;
	case PLAYER_STATE_HURT1:
		pDevice->SetTexture(0, g_pTexture_Player[10]);
		break;
	case PLAYER_STATE_HURT2:
		pDevice->SetTexture(0, g_pTexture_Player[11]);
		break;
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, AMOUNT_COMBINEPOLYGON);
}

//************************************************
//プレイヤーの頂点サイズを算出関数
//************************************************
void CalcSize_Player_Box(void)
{
	for (int nCnt = 0; nCnt < PLAYER_STATE_MAX; nCnt++)
	{
		switch (nCnt)
		{
		case PLAYER_STATE_IDLE:
			//対角線の長さ
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X));

			//対角線の角度
			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f(RADIUS_PLAYER_X * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f(RADIUS_PLAYER_X * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_JUMP:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 1.1875f) * (RADIUS_PLAYER_X * 1.1875f)) +
				(((RADIUS_PLAYER_Y * 1.1875f) * 2.0f) * ((RADIUS_PLAYER_Y * 1.1875f) * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 1.1875f) * (RADIUS_PLAYER_X * 1.1875f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 1.1875f) * 2.0f, ((RADIUS_PLAYER_Y * 1.1875f) * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 1.1875f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_LAND:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 1.1f) * (RADIUS_PLAYER_X * 1.1f)) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 1.1f) * (RADIUS_PLAYER_X * 1.1f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 1.1f) * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 1.1f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_RUN:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X) +
				(((RADIUS_PLAYER_Y * 1.15f) * 2.0f) * ((RADIUS_PLAYER_Y * 1.15f) * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f(RADIUS_PLAYER_X * 2.0f, ((RADIUS_PLAYER_Y * 1.15f) * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f(RADIUS_PLAYER_X * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_LIGHT1:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 2.0f) * (RADIUS_PLAYER_X * 2.0f)) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 2.0f) * (RADIUS_PLAYER_X * 2.0f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 2.0f) * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 2.0f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_LIGHT2:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 1.75f) * (RADIUS_PLAYER_X * 1.75f)) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 1.75f) * (RADIUS_PLAYER_X * 1.75f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 1.75f) * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 1.75f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_LIGHT3:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 2.0f) * (RADIUS_PLAYER_X * 2.0f)) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 2.0f) * (RADIUS_PLAYER_X * 2.0f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 2.0f) * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 2.0f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_HEAVY1:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 2.3f) * (RADIUS_PLAYER_X * 2.3f)) +
				(((RADIUS_PLAYER_Y * 1.1f) * 2.0f) * ((RADIUS_PLAYER_Y * 1.1f) * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 2.3f) * (RADIUS_PLAYER_X * 2.3f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 2.3f) * 2.0f, ((RADIUS_PLAYER_Y * 1.1f) * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 2.3f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_HEAVY2:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 2.15f) * (RADIUS_PLAYER_X * 2.15f)) +
				(((RADIUS_PLAYER_Y) * 2.0f) * ((RADIUS_PLAYER_Y) * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 2.15f) * (RADIUS_PLAYER_X * 2.15f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 2.15f) * 2.0f, ((RADIUS_PLAYER_Y) * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 2.15f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_HEAVY3:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 3.0f) * (RADIUS_PLAYER_X * 3.0f)) +
				(((RADIUS_PLAYER_Y * 1.4f) * 2.0f) * ((RADIUS_PLAYER_Y * 1.4f) * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 3.0f) * (RADIUS_PLAYER_X * 3.0f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 3.0f) * 2.0f, ((RADIUS_PLAYER_Y * 1.4f) * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 3.0f) * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_HURT1:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf((RADIUS_PLAYER_X * RADIUS_PLAYER_X));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f(RADIUS_PLAYER_X * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f(RADIUS_PLAYER_X * 2.0f, 0.0f);
			break;
		case PLAYER_STATE_HURT2:
			g_aPlayer_Box[nCnt].fLength_Hold[0] = sqrtf(((RADIUS_PLAYER_X * 1.1f) * (RADIUS_PLAYER_X * 1.1f)) +
				((RADIUS_PLAYER_Y * 2.0f) * (RADIUS_PLAYER_Y * 2.0f)));
			g_aPlayer_Box[nCnt].fLength_Hold[1] = sqrtf(((RADIUS_PLAYER_X * 1.1f) * (RADIUS_PLAYER_X * 1.1f)));

			g_aPlayer_Box[nCnt].fAngle_Hold[0] = atan2f((RADIUS_PLAYER_X * 1.1f) * 2.0f, (RADIUS_PLAYER_Y * 2.0f) * 2.0f);
			g_aPlayer_Box[nCnt].fAngle_Hold[1] = atan2f((RADIUS_PLAYER_X * 1.1f) * 2.0f, 0.0f);
			break;
		}
	}
}

//************************************************
//プレイヤー構造体の情報を設定する関数
//************************************************
void SetInfo_Player(void)
{
	g_aPlayer.BGpos = D3DXVECTOR3(SCREEN_HALFWIDTH, SCREEN_HALFHEIGHT, 0.0f);
	g_aPlayer.pos = g_aPlayer.BGpos;
	g_aPlayer.oldpos = g_aPlayer.pos;
	g_aPlayer.fTexSpan[0] = 0.0f;
	g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
	g_aPlayer.fRadius[0] = RADIUS_PLAYER_X;
	g_aPlayer.fRadius[1] = RADIUS_PLAYER_Y;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aPlayer.fLength[nCnt] = g_aPlayer_Box[PLAYER_STATE_IDLE].fLength_Hold[nCnt];
		g_aPlayer.fAngle[nCnt] = g_aPlayer_Box[PLAYER_STATE_IDLE].fAngle_Hold[nCnt];
	}
	//g_aPlayer.nJumpTimes = AMOUNT_ABLE_JUMPS;
	//g_aPlayer.nLife = AMOUNT_MAX_LIFE_PLAYER;
}

//************************************************
//キー入力で移動する関数
//************************************************
void Move_Pos_Player(void)
{
	//過去の位置を記録
	g_aPlayer.oldpos = g_aPlayer.pos;

	//攻撃判定が出ている場合、時間を計測
	if (g_aPlayer.bAfterATK)
	{
		g_aPlayer.nCntAfterATK++;

		if (g_aPlayer.nLastATK == PLAYER_STATE_LIGHT1 ||
			g_aPlayer.nLastATK == PLAYER_STATE_LIGHT2 ||
			g_aPlayer.nLastATK == PLAYER_STATE_LIGHT3)
		{
			//一定時間経つと、攻撃後の判定を無くす
			if (g_aPlayer.nCntAfterATK > AMOUNT_CT_LIGHT_COMBO)
			{
				g_aPlayer.nLastATK = 0;
				g_aPlayer.bAfterATK = false;
				g_aPlayer.nCntAfterATK = 99;
			}
		}
		else
		{
			if (g_aPlayer.nCntAfterATK > AMOUNT_CT_HEAVY_COMBO)
			{
				g_aPlayer.nLastATK = 0;
				g_aPlayer.bAfterATK = false;
				g_aPlayer.nCntAfterATK = 99;
			}
		}
	}

	if (!g_aPlayer.bFell)
	{
		//被弾時は一切の操作を受け付けない
		if (g_aPlayer.nState != PLAYER_STATE_HURT1 &&
			g_aPlayer.nState != PLAYER_STATE_HURT2)
		{
			//攻撃
			if (GetKeyboardTrigger(DIK_O) || GetJoypadTrigger(JOYKEY_B))
			{
				SetInfo_Bomb();
			}

			//攻撃後の判定がなければ
			if (!g_aPlayer.bAfterATK)
			{
				//攻撃
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//ボックス初期化
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_LIGHT1_PLAYER;

					//弱1状態に
					g_aPlayer.nState = PLAYER_STATE_LIGHT1;
					g_aPlayer.nLastATK = PLAYER_STATE_LIGHT1;

					//攻撃判定を更新
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//攻撃ボックスを生成
					GiveInfo_Attack_Box(0);

					PlaySound(SOUND_LABEL_LIGHT1);
				}
			}
			//攻撃後の判定中に再攻撃で弱2へ派生
			else if (g_aPlayer.nLastATK == PLAYER_STATE_LIGHT1 &&
				g_aPlayer.bAfterATK && g_aPlayer.nCntAfterATK >= AMOUNT_CT_LIGHT)
			{
				//攻撃
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//ボックス初期化
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_LIGHT2_PLAYER;

					//弱2状態に
					g_aPlayer.nState = PLAYER_STATE_LIGHT2;
					g_aPlayer.nLastATK = PLAYER_STATE_LIGHT2;

					//攻撃判定を更新
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//攻撃ボックスを生成
					GiveInfo_Attack_Box(0);

					PlaySound(SOUND_LABEL_LIGHT2);
				}
			}
			//攻撃後の判定中に再攻撃で弱3へ派生
			else if (g_aPlayer.nLastATK == PLAYER_STATE_LIGHT2 &&
				g_aPlayer.bAfterATK && g_aPlayer.nCntAfterATK >= AMOUNT_CT_LIGHT)
			{
				//攻撃
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//ボックス初期化
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_LIGHT3_PLAYER;

					//弱3状態に
					g_aPlayer.nState = PLAYER_STATE_LIGHT3;
					g_aPlayer.nLastATK = PLAYER_STATE_LIGHT3;

					//攻撃判定を更新
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//攻撃ボックスを生成
					GiveInfo_Attack_Box(0);

					PlaySound(SOUND_LABEL_LIGHT3);
				}
			}
			//攻撃後の判定中に再攻撃で強1へ派生
			else if (g_aPlayer.nLastATK == PLAYER_STATE_LIGHT3 &&
				g_aPlayer.bAfterATK && g_aPlayer.nCntAfterATK >= AMOUNT_CT_HEAVY)
			{
				//攻撃
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//ボックス初期化
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_HEAVY1_PLAYER;

					//強1状態に
					g_aPlayer.nState = PLAYER_STATE_HEAVY1;
					g_aPlayer.nLastATK = PLAYER_STATE_HEAVY1;

					//攻撃判定を更新
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//攻撃ボックスを生成
					GiveInfo_Attack_Box(0);
				}
			}
			//攻撃後の判定中に再攻撃で強2へ派生
			else if (g_aPlayer.nLastATK == PLAYER_STATE_HEAVY1 &&
				g_aPlayer.bAfterATK && g_aPlayer.nCntAfterATK >= AMOUNT_CT_HEAVY)
			{
				//攻撃
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//ボックス初期化
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_HEAVY2_PLAYER;

					//強1状態に
					g_aPlayer.nState = PLAYER_STATE_HEAVY2;
					g_aPlayer.nLastATK = PLAYER_STATE_HEAVY2;

					//攻撃判定を更新
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//攻撃ボックスを生成
					GiveInfo_Attack_Box(0);
				}
			}
			//攻撃後の判定中に再攻撃で強3へ派生
			else if (g_aPlayer.nLastATK == PLAYER_STATE_HEAVY2 &&
				g_aPlayer.bAfterATK && g_aPlayer.nCntAfterATK >= AMOUNT_CT_HEAVY)
			{
				//攻撃
				if (GetKeyboardTrigger(DIK_I) || GetJoypadTrigger(JOYKEY_X))
				{
					//ボックス初期化
					g_aPlayer.nCntTex = 0;
					g_aPlayer.nCntPattern = 0;
					g_aPlayer.fTexSpan[0] = 0;
					g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_HEAVY3_PLAYER;

					//強1状態に
					g_aPlayer.nState = PLAYER_STATE_HEAVY3;
					g_aPlayer.nLastATK = PLAYER_STATE_HEAVY3;

					//攻撃判定を更新
					g_aPlayer.bAfterATK = true;
					g_aPlayer.nCntAfterATK = 0;

					//攻撃ボックスを生成
					GiveInfo_Attack_Box(0);

					PlaySound(SOUND_LABEL_HEAVY3_1);
				}
			}

			//ジャンプ可能な時
			if (g_aPlayer.nJumpTimes > 0)
			{
				if (GetKeyboardTrigger(DIK_SPACE) || GetJoypadTrigger(JOYKEY_A))
				{
					//攻撃時はそちらを優先
					if (g_aPlayer.nState != PLAYER_STATE_LIGHT1 &&
						g_aPlayer.nState != PLAYER_STATE_LIGHT2 &&
						g_aPlayer.nState != PLAYER_STATE_LIGHT3 &&
						g_aPlayer.nState != PLAYER_STATE_HEAVY1 &&
						g_aPlayer.nState != PLAYER_STATE_HEAVY2 &&
						g_aPlayer.nState != PLAYER_STATE_HEAVY3)
					{
						//ボックス初期化
						g_aPlayer.nCntTex = 0;
						g_aPlayer.nCntPattern = 0;
						g_aPlayer.fTexSpan[0] = 0.0f;
						g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_JUMP_PLAYER;
						//ジャンプ状態に
						g_aPlayer.nState = PLAYER_STATE_JUMP;

						//ジャンプ可能回数を消費
						g_aPlayer.nJumpTimes--;

						//移動量を加算
						g_aPlayer.move.y = -MOVE_SPD_PLAYER_Y;

						//ジャンプ回数に応じて特別な処理
						switch (g_aPlayer.nJumpTimes)
						{
						case AMOUNT_ABLE_JUMPS - 1:
							//効果音
							PlaySound(SOUND_LABEL_JUMP00);
							break;
						default:
							//効果音
							PlaySound(SOUND_LABEL_JUMP01);
							//エフェクト
							SetInfo_Effect_Jump(g_aPlayer.pos);
							break;
						}
					}
				}
			}

			//←へ移動
			if (GetKeyboardPress(DIK_A) || GetJoypadPress(JOYKEY_LEFT))
			{
				//攻撃時はそちらを優先
				if (g_aPlayer.nState != PLAYER_STATE_LIGHT1 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT2 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT3 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY1 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY2 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY3)
				{
					//ジャンプ中はそちらを優先
					if (g_aPlayer.nState != PLAYER_STATE_JUMP)
					{
						//それまで走行状態以外ならボックス初期化
						if (g_aPlayer.nState != PLAYER_STATE_RUN)
						{
							g_aPlayer.nCntTex = 0;
							g_aPlayer.nCntPattern = 0;
							g_aPlayer.fTexSpan[0] = 0;
							g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_RUN_PLAYER;
						}
						//走行状態に
						g_aPlayer.nState = PLAYER_STATE_RUN;
					}

					//←向きに
					g_aPlayer.move.x = -MOVE_SPD_PLAYER_X;
					g_aPlayer.LR = 1;
				}
				//弱攻撃+移動で移動補正
				else if (g_aPlayer.nState == PLAYER_STATE_LIGHT1 ||
					g_aPlayer.nState == PLAYER_STATE_LIGHT2 ||
					g_aPlayer.nState == PLAYER_STATE_LIGHT3)
				{
					//攻撃後一定期間のみ
					if (g_aPlayer.nCntAfterATK < 2)
					{
						g_aPlayer.move.x = -MOVE_SPD_ATK_PLAYER_X;
						g_aPlayer.LR = 1;
					}
				}
				//強攻撃+移動で移動補正
				else if (g_aPlayer.nState == PLAYER_STATE_HEAVY1 ||
					g_aPlayer.nState == PLAYER_STATE_HEAVY2)
				{
					//攻撃後一定期間のみ
					if (g_aPlayer.nCntAfterATK < 17)
					{
						g_aPlayer.move.x = -MOVE_SPD_ATK_PLAYER_X * 0.3f;
						g_aPlayer.LR = 1;
					}
				}
				//強攻撃+移動で移動補正
				else if (g_aPlayer.nState == PLAYER_STATE_HEAVY3)
				{
					//攻撃後一定期間のみ
					if (g_aPlayer.nCntAfterATK < 25)
					{
						g_aPlayer.move.x = -MOVE_SPD_ATK_PLAYER_X * 0.3f;
						g_aPlayer.LR = 1;
					}
				}
			}
			//→に移動
			else if (GetKeyboardPress(DIK_D) || GetJoypadPress(JOYKEY_RIGHT))
			{
				//攻撃時はそちらを優先
				if (g_aPlayer.nState != PLAYER_STATE_LIGHT1 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT2 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT3 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY1 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY2 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY3)
				{
					//ジャンプ中はそちらを優先
					if (g_aPlayer.nState != PLAYER_STATE_JUMP)
					{
						//それまで走行状態以外ならボックス初期化
						if (g_aPlayer.nState != PLAYER_STATE_RUN)
						{
							g_aPlayer.nCntTex = 0;
							g_aPlayer.nCntPattern = 0;
							g_aPlayer.fTexSpan[0] = 0;
							g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_RUN_PLAYER;
						}
						//走行状態に
						g_aPlayer.nState = PLAYER_STATE_RUN;
					}

					//→向きに
					g_aPlayer.move.x = MOVE_SPD_PLAYER_X;
					g_aPlayer.LR = 0;
				}
				//弱攻撃+移動で移動補正
				else if (g_aPlayer.nState == PLAYER_STATE_LIGHT1 ||
					g_aPlayer.nState == PLAYER_STATE_LIGHT2 ||
					g_aPlayer.nState == PLAYER_STATE_LIGHT3)
				{
					//攻撃後一定期間のみ
					if (g_aPlayer.nCntAfterATK < 2)
					{
						g_aPlayer.move.x = MOVE_SPD_ATK_PLAYER_X;
						g_aPlayer.LR = 0;
					}
				}
				//強攻撃+移動で移動補正
				else if (g_aPlayer.nState == PLAYER_STATE_HEAVY1 ||
					g_aPlayer.nState == PLAYER_STATE_HEAVY2)
				{
					//攻撃後一定期間のみ
					if (g_aPlayer.nCntAfterATK < 17)
					{
						g_aPlayer.move.x = MOVE_SPD_ATK_PLAYER_X * 0.3f;
						g_aPlayer.LR = 0;
					}
				}
				//強攻撃+移動で移動補正
				else if (g_aPlayer.nState == PLAYER_STATE_HEAVY3)
				{
					//攻撃後一定期間のみ
					if (g_aPlayer.nCntAfterATK < 25)
					{
						g_aPlayer.move.x = MOVE_SPD_ATK_PLAYER_X * 0.3f;
						g_aPlayer.LR = 0;
					}
				}
			}
			//左右の移動入力が無く
			else
			{
				//ジャンプ状態や着地状態を優先
				if (g_aPlayer.nState != PLAYER_STATE_JUMP &&
					g_aPlayer.nState != PLAYER_STATE_LAND &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT1 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT2 &&
					g_aPlayer.nState != PLAYER_STATE_LIGHT3 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY1 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY2 &&
					g_aPlayer.nState != PLAYER_STATE_HEAVY3)
				{
					//それまで待機状態以外ならボックス初期化
					if (g_aPlayer.nState != PLAYER_STATE_IDLE)
					{
						g_aPlayer.nCntTex = 0;
						g_aPlayer.nCntPattern = 0;
						g_aPlayer.fTexSpan[0] = 0;
						g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
					}
					//待機状態に
					g_aPlayer.nState = PLAYER_STATE_IDLE;
				}
			}
		}

		//攻撃状態(テクスチャ基準)に合わせて反動を付ける
		switch (g_aPlayer.nState)
		{
		case PLAYER_STATE_HEAVY1:
			if(g_aPlayer.nCntPattern == 3)
			{
				g_aPlayer.move.y += -MOVE_SPD_GRAVITY_Y * 1.5f;
				g_aPlayer.LR == 0 ? g_aPlayer.move.x += MOVE_SPD_ATK_PLAYER_X * 0.25f : g_aPlayer.move.x += -MOVE_SPD_ATK_PLAYER_X * 0.25f;
				PlaySound(SOUND_LABEL_HEAVY1);
			}
			break;
		case PLAYER_STATE_HEAVY2:
			if (g_aPlayer.nCntPattern == 5)
			{
				 g_aPlayer.move.y += -MOVE_SPD_GRAVITY_Y * 1.5f;
				 g_aPlayer.LR == 0 ? g_aPlayer.move.x += MOVE_SPD_ATK_PLAYER_X * 0.25f : g_aPlayer.move.x += -MOVE_SPD_ATK_PLAYER_X * 0.25f;
				 PlaySound(SOUND_LABEL_HEAVY2);
			}
			break;
		case PLAYER_STATE_HEAVY3:
			if (g_aPlayer.nCntPattern == 9)
			{
				g_aPlayer.move.y += -MOVE_SPD_GRAVITY_Y * 2.0f;
				g_aPlayer.LR == 0 ? g_aPlayer.move.x += MOVE_SPD_ATK_PLAYER_X * 0.4f : g_aPlayer.move.x += -MOVE_SPD_ATK_PLAYER_X * 0.4f;
				PlaySound(SOUND_LABEL_HEAVY3_2);
			}
			break;
		}

		//横移動慣性
		g_aPlayer.move.x = g_aPlayer.move.x * MOVE_SPD_BRAKE_X;

		//重力
		g_aPlayer.move.y = g_aPlayer.move.y + MOVE_SPD_GRAVITY_Y;
	}
	else
	{
		//移動量をクリア
		g_aPlayer.move.x = 0.0f;
		g_aPlayer.move.y = 0.0f;
	}

	//プレイヤーの位置とか設定
	Update_Pos_Player();
}

//************************************************
//プレイヤーの位置を設定する関数
//************************************************
void Update_Pos_Player(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Player;

	//裏の座標変更
	g_aPlayer.BGpos += g_aPlayer.move;
	//見かけの座標変更
	g_aPlayer.pos.y += g_aPlayer.move.y;

	//見かけの位置を調整する
	Adjust_Pos_Player();

	//地形との当たり判定
	if (!g_aPlayer.bFell)
	{
		HitDetection_Stage(0, HIT_TYPE_PLAYER, &g_aPlayer.pos, &g_aPlayer.oldpos, &g_aPlayer.move, &g_aPlayer.fRadius[0]);
	}

	//テクスチャアニメーション
	Update_Tex_Player();

	//状態に合わせてボックス調整
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aPlayer.fLength[nCnt] = g_aPlayer_Box[g_aPlayer.nState].fLength_Hold[nCnt];
		g_aPlayer.fAngle[nCnt] = g_aPlayer_Box[g_aPlayer.nState].fAngle_Hold[nCnt];
	}

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	pVtx_Player[0].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z - (D3DX_PI - g_aPlayer.fAngle[0])) * g_aPlayer.fLength[0];
	pVtx_Player[0].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z - (D3DX_PI - g_aPlayer.fAngle[0])) * g_aPlayer.fLength[0];
	pVtx_Player[1].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + (D3DX_PI - g_aPlayer.fAngle[0])) * g_aPlayer.fLength[0];
	pVtx_Player[1].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + (D3DX_PI - g_aPlayer.fAngle[0])) * g_aPlayer.fLength[0];
	pVtx_Player[2].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z - g_aPlayer.fAngle[1]) * g_aPlayer.fLength[1];
	pVtx_Player[2].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z - g_aPlayer.fAngle[1]) * g_aPlayer.fLength[1];
	pVtx_Player[3].pos.x = g_aPlayer.pos.x + sinf(g_aPlayer.rot.z + g_aPlayer.fAngle[1]) * g_aPlayer.fLength[1];
	pVtx_Player[3].pos.y = g_aPlayer.pos.y + cosf(g_aPlayer.rot.z + g_aPlayer.fAngle[1]) * g_aPlayer.fLength[1];

	//頂点バッファをアンロックする
	g_pVtxBuff_Player->Unlock();
}

//************************************************
//見かけの位置を調整する関数
//************************************************
void Adjust_Pos_Player(void)
{
	//裏の座標がセカイの←端に到達していると
	if (g_aPlayer.BGpos.x - g_aPlayer.fRadius[0] < 0.0f)
	{
		//端っこに戻す
		g_aPlayer.BGpos.x = g_aPlayer.fRadius[0];
		g_aPlayer.pos.x = g_aPlayer.BGpos.x;

		//移動量も無くす
		g_aPlayer.move.x = 0.0f;
	}
	//裏の座標がセカイの←端にとても近くなると
	else if (g_aPlayer.BGpos.x < SCREEN_HALFWIDTH)
	{
		//見かけの座標も同期
		g_aPlayer.pos.x = g_aPlayer.BGpos.x;
	}

	//裏の座標がセカイの→端に到達していると
	if (g_aPlayer.BGpos.x + g_aPlayer.fRadius[0] > SCREEN_WIDTH)
	{
		//端っこに戻す
		g_aPlayer.BGpos.x = SCREEN_WIDTH - g_aPlayer.fRadius[0];
		g_aPlayer.pos.x = g_aPlayer.BGpos.x;

		//移動量も無くす
		g_aPlayer.move.x = 0.0f;
	}
	//裏の座標がセカイの→端に近くなると
	else if (g_aPlayer.BGpos.x > SCREEN_HALFWIDTH)
	{
		//見かけの座標も同期
		g_aPlayer.pos.x = g_aPlayer.BGpos.x;
	}

	//落下すると
	if (g_aPlayer.pos.y >= SCREEN_HEIGHT + SCREEN_HALFHEIGHT)
	{
		//1度のみダメージ、移動量もクリア
		if (!g_aPlayer.bFell)
		{
			//g_aPlayer.nLife--;
			g_aPlayer.move.x = 0.0f;
			g_aPlayer.move.y = 0.0f;

			PlaySound(SOUND_LABEL_FALL);
		}

		//落下判定を出す
		g_aPlayer.bFell = true;
	}

	//落下判定中、強制移動
	if (g_aPlayer.bFell)
	{
		TOWER* pTower = GetInfo_Tower();

		//横移動
		if (g_aPlayer.BGpos.x > pTower->pos.x + FELL_RESET_AREA_X)
		{
			//このときのみ移動量を固定
			g_aPlayer.move.x = -FELL_RESET_MOVE_X;
		}
		else if (g_aPlayer.BGpos.x < pTower->pos.x - FELL_RESET_AREA_X)
		{
			//このときのみ移動量を固定
			g_aPlayer.move.x = FELL_RESET_MOVE_X;
		}
		else
		{
			g_aPlayer.move.x = 0.0f;
		}

		//縦移動
		if (g_aPlayer.BGpos.y > pTower->pos.y - FELL_RESET_AREA_Y)
		{
			//このときのみ移動量を固定
			g_aPlayer.move.y = FELL_RESET_MOVE_Y;
		}
		else
		{
			//上昇しすぎを防ぐ
			//g_aPlayer.move.y = 0.0f;
			g_aPlayer.BGpos.y = pTower->pos.y - FELL_RESET_AREA_Y;

			if (g_aPlayer.BGpos.x <= pTower->pos.x + FELL_RESET_AREA_X &&
				g_aPlayer.BGpos.x >= pTower->pos.x - FELL_RESET_AREA_X)
			{
				//落下判定を無くす
				g_aPlayer.bFell = false;
			}
		}

		//強制移動
		g_aPlayer.BGpos += g_aPlayer.move;
		g_aPlayer.pos = g_aPlayer.BGpos;
	}
}

//************************************************
//プレイヤーのテクスチャを動かす関数
//************************************************
void Update_Tex_Player(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Player;

	//テクスチャを変更
	switch (g_aPlayer.nState)
	{
	case PLAYER_STATE_IDLE:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_IDLE_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_IDLE_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_IDLE_PLAYER;
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_IDLE_PLAYER)
			{
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_JUMP:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_JUMP_PLAYER)
		{
			//一定量に達すると固定
			if (g_aPlayer.nCntPattern < AMOUNT_STYLE_TEX_JUMP_PLAYER)
			{
				g_aPlayer.nCntTex = 0;
				g_aPlayer.nCntPattern++;
				g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_JUMP_PLAYER;
				g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_JUMP_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_LAND:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_LAND_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_LAND_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_LAND_PLAYER;
			//1ループで終了
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_LAND_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_RUN:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_RUN_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_RUN_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_RUN_PLAYER;
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_RUN_PLAYER)
			{
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_RUN_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_LIGHT1:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_LIGHT1_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_LIGHT1_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_LIGHT1_PLAYER;
			//1ループで終了
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_LIGHT1_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_LIGHT2:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_LIGHT2_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_LIGHT2_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_LIGHT2_PLAYER;
			//1ループで終了
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_LIGHT2_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_LIGHT3:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_LIGHT3_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_LIGHT3_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_LIGHT3_PLAYER;
			//1ループで終了
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_LIGHT3_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_HEAVY1:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_HEAVY1_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_HEAVY1_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_HEAVY1_PLAYER;
			//1ループで終了
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_HEAVY1_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_HEAVY2:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_HEAVY2_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_HEAVY2_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_HEAVY2_PLAYER;
			//1ループで終了
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_HEAVY2_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_HEAVY3:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_HEAVY3_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_HEAVY3_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_HEAVY3_PLAYER;
			//1ループで終了
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_HEAVY3_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_HURT1:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_HURT1_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_HURT1_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_HURT1_PLAYER;
			//1ループで終了
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_HURT1_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	case PLAYER_STATE_HURT2:
		g_aPlayer.nCntTex++;
		if (g_aPlayer.nCntTex > SPD_CHANGE_TEX_HURT2_PLAYER)
		{
			g_aPlayer.nCntTex = 0;
			g_aPlayer.nCntPattern++;
			g_aPlayer.fTexSpan[0] += SPAN_CHANGE_TEX_HURT2_PLAYER;
			g_aPlayer.fTexSpan[1] += SPAN_CHANGE_TEX_HURT2_PLAYER;
			//1ループで終了
			if (g_aPlayer.nCntPattern >= AMOUNT_STYLE_TEX_HURT2_PLAYER)
			{
				g_aPlayer.nState = PLAYER_STATE_IDLE;
				g_aPlayer.nCntPattern = 0;
				g_aPlayer.fTexSpan[0] = 0;
				g_aPlayer.fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
			}
		}
		break;
	}

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Player->Lock(0, 0, (void**)&pVtx_Player, 0);

	if (g_aPlayer.LR == 0)
	{
		pVtx_Player[0].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[0], 0.0f);
		pVtx_Player[1].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[1], 0.0f);
		pVtx_Player[2].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[0], 1.0f);
		pVtx_Player[3].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[1], 1.0f);
	}
	else
	{
		pVtx_Player[0].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[1], 0.0f);
		pVtx_Player[1].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[0], 0.0f);
		pVtx_Player[2].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[1], 1.0f);
		pVtx_Player[3].tex = D3DXVECTOR2(g_aPlayer.fTexSpan[0], 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Player->Unlock();
}

//************************************************
//プレイヤー構造体のアドレスを渡す
//************************************************
PLAYER *GetInfo_Player(void)
{
	return &g_aPlayer;
}

//************************************************
//プレイヤーボックス構造体のアドレスを渡す
//************************************************
PLAYER_BOX* GetInfo_Player_Box(void)
{
	return &g_aPlayer_Box[0];
}

//************************************************
//プレイヤー位置情報のアドレスを渡す
//************************************************
D3DXVECTOR3 GetInfo_Pos_Player(void)
{
	return g_aPlayer.pos;
}