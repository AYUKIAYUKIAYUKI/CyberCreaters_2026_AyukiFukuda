//************************************************
//
//攻撃ボックス処理[attack_box.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "attack_box.h"
#include "bomb.h"
#include "camera.h"
#include "enemy.h"
#include "particle.h"
#include "player.h"
#include "score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Attack_Box = NULL;	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Attack_Box = NULL;	//頂点バッファのポインタ
ATTACK_BOX g_aAttack_Box[AMOUNT_POLYGON_ATTACK_BOX];	//攻撃ボックス

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Attack_Box()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		"",
		&g_pTexture_Attack_Box);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ATTACK_BOX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Attack_Box,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Attack_Box;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Attack_Box->Lock(0, 0, (void**)&pVtx_Attack_Box, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Attack_Box[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Attack_Box[0].rhw = 1.0f;
		pVtx_Attack_Box[1].rhw = 1.0f;
		pVtx_Attack_Box[2].rhw = 1.0f;
		pVtx_Attack_Box[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Attack_Box[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);
		pVtx_Attack_Box[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);
		pVtx_Attack_Box[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);
		pVtx_Attack_Box[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.2f);

		//テクスチャ座標の初期設定
		pVtx_Attack_Box[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Attack_Box[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Attack_Box[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Attack_Box[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Attack_Box += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Attack_Box->Unlock();

	//攻撃ボックス構造体の情報の初期化群
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		g_aAttack_Box[nCnt].nMode = 0;
		g_aAttack_Box[nCnt].bUse = false;
		g_aAttack_Box[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aAttack_Box[nCnt].fRadius[nCnt2] = 0.0f;
			g_aAttack_Box[nCnt].fLength[nCnt2] = 0.0f;
			g_aAttack_Box[nCnt].fAngle[nCnt2] = 0.0f;
		}
		g_aAttack_Box[nCnt].nRemain = 0;
	}
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Attack_Box(void)
{
	//テクスチャの破棄
	if (g_pTexture_Attack_Box != NULL)
	{
		g_pTexture_Attack_Box->Release();
		g_pTexture_Attack_Box = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Attack_Box != NULL)
	{
		g_pVtxBuff_Attack_Box->Release();
		g_pVtxBuff_Attack_Box = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Attack_Box(void)
{
	//攻撃ボックスを展開
	Update_Pos_Attack_Box();

	//攻撃ボックスの残存時間を減少
	Disapper_Attack_Box();
}

//************************************************
//攻撃ボックスの情報を設定する関数
//************************************************
void GiveInfo_Attack_Box(int nMode)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		//1つ召喚
		if (!g_aAttack_Box[nCnt].bUse)
		{
			g_aAttack_Box[nCnt].nMode = nMode;
			g_aAttack_Box[nCnt].bUse = true;

			switch (g_aAttack_Box[nCnt].nMode)
			{
			case 0:
				Front_Player(nCnt);
				break;
			case 1:
				Front_Bomb(nCnt);
				break;
			}

			break;
		}
	}
}

//************************************************
//プレイヤー攻撃ボックスの情報を設定する関数
//************************************************
void Front_Player(int nCnt)
{
	PLAYER* pPlayer = GetInfo_Player();

	//攻撃モーションごとに差別化
	switch (pPlayer->nState)
	{
	case PLAYER_STATE_LIGHT1:

		//出現位置
		switch (pPlayer->LR)
		{
			//→
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
			//←
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		//サイズ
		g_aAttack_Box[nCnt].fRadius[0] = 70.0f;
		g_aAttack_Box[nCnt].fRadius[1] = pPlayer->fRadius[1];

		//対角線の長さ
		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		//対角線の角度
		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		//キャスト時間
		g_aAttack_Box[nCnt].nAppear = 2 * SPD_CHANGE_TEX_LIGHT1_PLAYER;

		//残存時間
		g_aAttack_Box[nCnt].nRemain = 10;

		//色
		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		/****************以下このフォーマットで分別**************/
		break;
	case PLAYER_STATE_LIGHT2:
		switch (pPlayer->LR)
		{
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		g_aAttack_Box[nCnt].fRadius[0] = 70.0f;
		g_aAttack_Box[nCnt].fRadius[1] = pPlayer->fRadius[1];

		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box[nCnt].nAppear = 1 * SPD_CHANGE_TEX_LIGHT1_PLAYER;
		g_aAttack_Box[nCnt].nRemain = 10;

		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PLAYER_STATE_LIGHT3:
		switch (pPlayer->LR)
		{
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		g_aAttack_Box[nCnt].fRadius[0] = 60.0f;
		g_aAttack_Box[nCnt].fRadius[1] = pPlayer->fRadius[1];

		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box[nCnt].nAppear = 1 * SPD_CHANGE_TEX_LIGHT1_PLAYER;
		g_aAttack_Box[nCnt].nRemain = 10;

		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PLAYER_STATE_HEAVY1:
		switch (pPlayer->LR)
		{
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 50.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 50.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		g_aAttack_Box[nCnt].fRadius[0] = 80.0f;
		g_aAttack_Box[nCnt].fRadius[1] = 60.0f;

		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box[nCnt].nAppear = 4 * SPD_CHANGE_TEX_HEAVY1_PLAYER;
		g_aAttack_Box[nCnt].nRemain = 20;

		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PLAYER_STATE_HEAVY2:
		switch (pPlayer->LR)
		{
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 50.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 50.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		g_aAttack_Box[nCnt].fRadius[0] = 80.0f;
		g_aAttack_Box[nCnt].fRadius[1] = 60.0f;

		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box[nCnt].nAppear = 7 * SPD_CHANGE_TEX_HEAVY2_PLAYER;
		g_aAttack_Box[nCnt].nRemain = 20;

		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	case PLAYER_STATE_HEAVY3:
		switch (pPlayer->LR)
		{
		case 0:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 60.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		case 1:
			g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 60.0f;
			g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
			break;
		}

		g_aAttack_Box[nCnt].fRadius[0] = 100.0f;
		g_aAttack_Box[nCnt].fRadius[1] = 80.0f;

		g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
			((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
		g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

		g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box[nCnt].nAppear = 11 * SPD_CHANGE_TEX_HEAVY3_PLAYER;
		g_aAttack_Box[nCnt].nRemain = 30;

		g_aAttack_Box[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		break;
	}
}

void Front_Bomb(int nCnt)
{
	BOMB* pBomb = GetInfo_Bomb();

	g_aAttack_Box[nCnt].pos.x = pBomb->pos.x;
	g_aAttack_Box[nCnt].pos.y = pBomb->pos.y;

	g_aAttack_Box[nCnt].fRadius[0] = 110.0f;
	g_aAttack_Box[nCnt].fRadius[1] = 60.0f;

	g_aAttack_Box[nCnt].fLength[0] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]) +
		((g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * (g_aAttack_Box[nCnt].fRadius[1] * 2.0f)));
	g_aAttack_Box[nCnt].fLength[1] = sqrtf((g_aAttack_Box[nCnt].fRadius[0] * g_aAttack_Box[nCnt].fRadius[0]));

	g_aAttack_Box[nCnt].fAngle[0] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, (g_aAttack_Box[nCnt].fRadius[1] * 2.0f) * 2.0f);
	g_aAttack_Box[nCnt].fAngle[1] = atan2f(g_aAttack_Box[nCnt].fRadius[0] * 2.0f, 0.0f);

	g_aAttack_Box[nCnt].nAppear = 0;
	g_aAttack_Box[nCnt].nRemain = 10;

	g_aAttack_Box[nCnt].nMode = 1;
}

//************************************************
//攻撃ボックスのポリゴンを展開する関数
//************************************************
void Update_Pos_Attack_Box(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Attack_Box;

	PLAYER* pPlayer = GetInfo_Player();
	BOMB* pBomb = GetInfo_Bomb();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Attack_Box->Lock(0, 0, (void**)&pVtx_Attack_Box, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		//キャスト済みかつ使用判定がでているもののみ出現
		if (g_aAttack_Box[nCnt].bUse && g_aAttack_Box[nCnt].nAppear <= 0)
		{
			//モード分け
			switch (g_aAttack_Box[nCnt].nMode)
			{
			case 0:
				//攻撃モーションごとに位置同期
				switch (pPlayer->nState)
				{
				case PLAYER_STATE_LIGHT1:
					switch (pPlayer->LR)
					{
						//→
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
						//←
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				case PLAYER_STATE_LIGHT2:
					switch (pPlayer->LR)
					{
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				case PLAYER_STATE_LIGHT3:
					switch (pPlayer->LR)
					{
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 30.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				case PLAYER_STATE_HEAVY1:
					switch (pPlayer->LR)
					{
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 50.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 50.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				case PLAYER_STATE_HEAVY2:
					switch (pPlayer->LR)
					{
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 50.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 50.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				case PLAYER_STATE_HEAVY3:
					switch (pPlayer->LR)
					{
					case 0:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x + 60.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					case 1:
						g_aAttack_Box[nCnt].pos.x = pPlayer->pos.x - 60.0f;
						g_aAttack_Box[nCnt].pos.y = pPlayer->pos.y;
						break;
					}
					break;
				}
				break;
			case 1:
				g_aAttack_Box[nCnt].pos.x = pBomb->pos.x;
				g_aAttack_Box[nCnt].pos.y = pBomb->pos.y;
				break;
			}

			//パーティクルを飛ばす
			Setinfo_Particle(PARTICLE_ATKED, g_aAttack_Box[nCnt].pos, g_aAttack_Box[nCnt].col);

			//疑似スクロール
			ConvertInfo_Screen(&g_aAttack_Box[nCnt].pos);

			//当たり判定
			HitDetection_Attack_Box(nCnt);

			pVtx_Attack_Box[0].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z - (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
			pVtx_Attack_Box[0].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z - (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
			pVtx_Attack_Box[1].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z + (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
			pVtx_Attack_Box[1].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z + (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
			pVtx_Attack_Box[2].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z - g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
			pVtx_Attack_Box[2].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z - g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
			pVtx_Attack_Box[3].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z + g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
			pVtx_Attack_Box[3].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z + g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
		}
		//キャスト経過
		else if (g_aAttack_Box[nCnt].bUse)
		{
			g_aAttack_Box[nCnt].nAppear--;
		}

		pVtx_Attack_Box += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Attack_Box->Unlock();
}

//************************************************
//攻撃ボックス終了関数
//************************************************
void Disapper_Attack_Box(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Attack_Box;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Attack_Box->Lock(0, 0, (void**)&pVtx_Attack_Box, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		//キャスト済みボックスが出てるとき
		if (g_aAttack_Box[nCnt].bUse && g_aAttack_Box[nCnt].nAppear <= 0)
		{
			//残存減少
			if (g_aAttack_Box[nCnt].nRemain > 0)
			{
				g_aAttack_Box[nCnt].nRemain--;
			}
			//消滅
			else
			{
				g_aAttack_Box[nCnt].bUse = false;
				g_aAttack_Box[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
				{
					g_aAttack_Box[nCnt].fRadius[nCnt2] = 0.0f;
					g_aAttack_Box[nCnt].fLength[nCnt2] = 0.0f;
					g_aAttack_Box[nCnt].fAngle[nCnt2] = 0.0f;
				}
				g_aAttack_Box[nCnt].nRemain = 0;
				g_aAttack_Box[nCnt].nAppear = 0;

				pVtx_Attack_Box[0].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z - (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
				pVtx_Attack_Box[0].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z - (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
				pVtx_Attack_Box[1].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z + (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
				pVtx_Attack_Box[1].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z + (D3DX_PI - g_aAttack_Box[nCnt].fAngle[0])) * g_aAttack_Box[nCnt].fLength[0];
				pVtx_Attack_Box[2].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z - g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
				pVtx_Attack_Box[2].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z - g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
				pVtx_Attack_Box[3].pos.x = g_aAttack_Box[nCnt].pos.x + sinf(g_aAttack_Box[nCnt].rot.z + g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
				pVtx_Attack_Box[3].pos.y = g_aAttack_Box[nCnt].pos.y + cosf(g_aAttack_Box[nCnt].rot.z + g_aAttack_Box[nCnt].fAngle[1]) * g_aAttack_Box[nCnt].fLength[1];
			}
		}

		pVtx_Attack_Box += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Attack_Box->Unlock();
}

//************************************************
//当たり判定関数
//************************************************
void HitDetection_Attack_Box(int nCnt)
{
	PLAYER* pPlayer = GetInfo_Player();
	ENEMY* pEnemy = GetInfo_Enemy();

	//攻撃ボックスとの当たり判定
	//プレイヤー生成のボックスのため、敵とボックスで判定
	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		if (pEnemy[i].bUse)
		{
			//種類に合わせて判定、状態分け
			switch (pEnemy[i].nStyle)
			{
			case ENEMY_00:
				//被弾状態で無く生きている場合のみ
				if (pEnemy[i].nState != ENEMY_00_STATE_HURT && pEnemy[i].nState != ENEMY_00_STATE_DEATH)
				{
					//敵に攻撃ボックス(本来の当たり判定)が触れている
					if (pEnemy[i].pos.x - pEnemy[i].fRadius[0] < g_aAttack_Box[nCnt].pos.x + g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.x + pEnemy[i].fRadius[0] > g_aAttack_Box[nCnt].pos.x - g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.y - pEnemy[i].fRadius[1] < g_aAttack_Box[nCnt].pos.y &&
						pEnemy[i].pos.y + pEnemy[i].fRadius[1] > g_aAttack_Box[nCnt].pos.y - (g_aAttack_Box[nCnt].fRadius[1] * 2.0f))
					{
						//ライフを減らす
						pEnemy[i].nLife--;

						if (pPlayer->nState == PLAYER_STATE_HEAVY1 ||
							pPlayer->nState == PLAYER_STATE_HEAVY2 ||
							pPlayer->nState == PLAYER_STATE_HEAVY3)
						{
							//おまけ
							pEnemy[i].nLife--;
						}

						//見た目ボックス初期化
						pEnemy[i].nCntTex = 0;
						pEnemy[i].nCntPattern = 0;
						pEnemy[i].fTexSpan[0] = 0.0f;
						pEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_HURT_ENEMY_00;

						//被弾状態に差し替えて、連続被弾を防止
						pEnemy[i].nState = ENEMY_00_STATE_HURT;

						switch (g_aAttack_Box[nCnt].nMode)
						{
						case 0:
							//プレイヤーの向きに合わせてノックバック
							pPlayer->LR == 0 ? pEnemy[i].move.x = 8.0f : pEnemy[i].move.x = -8.0f;
							break;
						case 1:
							//おまけ
							pEnemy[i].nLife--;

							if (pEnemy[i].pos.x < g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = -15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							else if (pEnemy[i].pos.x > g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = 15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							break;
						}

						//スコア加算
						int* pScore = GetInfo_Score();
						pScore[SCORE_NEW] += 2;

						PlaySound(SOUND_LABEL_HURT);
					}
				}
				break;
			case ENEMY_01:
				//被弾状態で無く生きている場合のみ
				if (pEnemy[i].nState != ENEMY_01_STATE_HURT && pEnemy[i].nState != ENEMY_01_STATE_DEATH)
				{
					if (pEnemy[i].pos.x - pEnemy[i].fRadius[0] < g_aAttack_Box[nCnt].pos.x + g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.x + pEnemy[i].fRadius[0] > g_aAttack_Box[nCnt].pos.x - g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.y - (pEnemy[i].fRadius[1] * 2.0f) < g_aAttack_Box[nCnt].pos.y + g_aAttack_Box[nCnt].fRadius[1] &&
						pEnemy[i].pos.y > g_aAttack_Box[nCnt].pos.y - g_aAttack_Box[nCnt].fRadius[1])
					{
						//ライフを減らす
						pEnemy[i].nLife--;

						if (pPlayer->nState == PLAYER_STATE_HEAVY1 ||
							pPlayer->nState == PLAYER_STATE_HEAVY2 ||
							pPlayer->nState == PLAYER_STATE_HEAVY3)
						{
							//おまけ
							pEnemy[i].nLife--;
						}

						//見た目ボックス初期化
						pEnemy[i].nCntTex = 0;
						pEnemy[i].nCntPattern = 0;
						pEnemy[i].fTexSpan[0] = 0.0f;
						pEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_HURT_ENEMY_01;

						//被弾状態に差し替えて、連続被弾を防止
						pEnemy[i].nState = ENEMY_01_STATE_HURT;

						switch (g_aAttack_Box[nCnt].nMode)
						{
						case 0:
							//プレイヤーの向きに合わせてノックバック
							pPlayer->LR == 0 ? pEnemy[i].move.x = 8.0f : pEnemy[i].move.x = -8.0f;
							break;
						case 1:
							//おまけ
							pEnemy[i].nLife--;

							if (pEnemy[i].pos.x < g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = -15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							else if (pEnemy[i].pos.x > g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = 15.0f;
								pEnemy[i].move.y = -6.0f;
							}
						}

						//スコア加算
						int* pScore = GetInfo_Score();
						pScore[SCORE_NEW] += 1;

						PlaySound(SOUND_LABEL_HURT);
					}
				}
				break;
			case ENEMY_02:
				//被弾状態で無く生きている場合のみ
				if (pEnemy[i].nState != ENEMY_02_STATE_HURT && pEnemy[i].nState != ENEMY_02_STATE_DEATH)
				{
					if (pEnemy[i].pos.x - pEnemy[i].fRadius[0] < g_aAttack_Box[nCnt].pos.x + g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.x + pEnemy[i].fRadius[0] > g_aAttack_Box[nCnt].pos.x - g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.y - (pEnemy[i].fRadius[1] * 2.0f) < g_aAttack_Box[nCnt].pos.y + g_aAttack_Box[nCnt].fRadius[1] &&
						pEnemy[i].pos.y > g_aAttack_Box[nCnt].pos.y - g_aAttack_Box[nCnt].fRadius[1])
					{
						//ライフを減らす
						pEnemy[i].nLife--;

						if (pPlayer->nState == PLAYER_STATE_HEAVY1 ||
							pPlayer->nState == PLAYER_STATE_HEAVY2 ||
							pPlayer->nState == PLAYER_STATE_HEAVY3)
						{
							//おまけ
							pEnemy[i].nLife--;
						}

						//見た目ボックス初期化
						pEnemy[i].nCntTex = 0;
						pEnemy[i].nCntPattern = 0;
						pEnemy[i].fTexSpan[0] = 0.0f;
						pEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_HURT_ENEMY_02;

						//被弾状態に差し替えて、連続被弾を防止
						pEnemy[i].nState = ENEMY_02_STATE_HURT;

						switch (g_aAttack_Box[nCnt].nMode)
						{
						case 0:
							//プレイヤーの向きに合わせてノックバック
							pPlayer->LR == 0 ? pEnemy[i].move.x = 8.0f : pEnemy[i].move.x = -8.0f;
							break;
						case 1:
							//おまけ
							pEnemy[i].nLife--;

							if (pEnemy[i].pos.x < g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = -15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							else if (pEnemy[i].pos.x > g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = 15.0f;
								pEnemy[i].move.y = -6.0f;
							}
						}

						//スコア加算
						int* pScore = GetInfo_Score();
						pScore[SCORE_NEW] += 2;

						PlaySound(SOUND_LABEL_HURT);
					}
				}
				break;
			case ENEMY_03:
				//被弾状態で無く生きている場合のみ
				if (pEnemy[i].nState != ENEMY_03_STATE_HURT && pEnemy[i].nState != ENEMY_03_STATE_DEATH)
				{
					if (pEnemy[i].pos.x - pEnemy[i].fRadius[0] < g_aAttack_Box[nCnt].pos.x + g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.x + pEnemy[i].fRadius[0] > g_aAttack_Box[nCnt].pos.x - g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.y - (pEnemy[i].fRadius[1] * 2.0f) < g_aAttack_Box[nCnt].pos.y + g_aAttack_Box[nCnt].fRadius[1] &&
						pEnemy[i].pos.y > g_aAttack_Box[nCnt].pos.y - g_aAttack_Box[nCnt].fRadius[1])
					{
						//ライフを減らす
						pEnemy[i].nLife--;

						if (pPlayer->nState == PLAYER_STATE_HEAVY1 ||
							pPlayer->nState == PLAYER_STATE_HEAVY2 ||
							pPlayer->nState == PLAYER_STATE_HEAVY3)
						{
							//おまけ
							pEnemy[i].nLife--;
						}

						//見た目ボックス初期化
						pEnemy[i].nCntTex = 0;
						pEnemy[i].nCntPattern = 0;
						pEnemy[i].fTexSpan[0] = 0.0f;
						pEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_HURT_ENEMY_03;

						//被弾状態に差し替えて、連続被弾を防止
						pEnemy[i].nState = ENEMY_03_STATE_HURT;

						switch (g_aAttack_Box[nCnt].nMode)
						{
						case 0:
							//プレイヤーの向きに合わせてノックバック
							pPlayer->LR == 0 ? pEnemy[i].move.x = 8.0f : pEnemy[i].move.x = -8.0f;
							break;
						case 1:
							//おまけ
							pEnemy[i].nLife--;

							if (pEnemy[i].pos.x < g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = -15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							else if (pEnemy[i].pos.x > g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = 15.0f;
								pEnemy[i].move.y = -6.0f;
							}
						}

						//スコア加算
						int* pScore = GetInfo_Score();
						pScore[SCORE_NEW] += 2;

						PlaySound(SOUND_LABEL_HURT);
					}
				}
				break;
			case ENEMY_04:
				//被弾状態で無く生きている場合のみ
				if (pEnemy[i].nState != ENEMY_04_STATE_HURT && pEnemy[i].nState != ENEMY_04_STATE_DEATH)
				{
					if (pEnemy[i].pos.x - pEnemy[i].fRadius[0] < g_aAttack_Box[nCnt].pos.x + g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.x + pEnemy[i].fRadius[0] > g_aAttack_Box[nCnt].pos.x - g_aAttack_Box[nCnt].fRadius[0] &&
						pEnemy[i].pos.y - (pEnemy[i].fRadius[1] * 2.0f) < g_aAttack_Box[nCnt].pos.y + g_aAttack_Box[nCnt].fRadius[1] &&
						pEnemy[i].pos.y > g_aAttack_Box[nCnt].pos.y - g_aAttack_Box[nCnt].fRadius[1])
					{
						//ライフを減らす
						pEnemy[i].nLife--;

						if (pPlayer->nState == PLAYER_STATE_HEAVY1 ||
							pPlayer->nState == PLAYER_STATE_HEAVY2 ||
							pPlayer->nState == PLAYER_STATE_HEAVY3)
						{
							//おまけ
							pEnemy[i].nLife--;
						}

						//見た目ボックス初期化
						pEnemy[i].nCntTex = 0;
						pEnemy[i].nCntPattern = 0;
						pEnemy[i].fTexSpan[0] = 0.0f;
						pEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_HURT_ENEMY_04;

						//被弾状態に差し替えて、連続被弾を防止
						pEnemy[i].nState = ENEMY_04_STATE_HURT;

						switch (g_aAttack_Box[nCnt].nMode)
						{
						case 0:
							//プレイヤーの向きに合わせてノックバック
							pPlayer->LR == 0 ? pEnemy[i].move.x = 8.0f : pEnemy[i].move.x = -8.0f;
							break;
						case 1:
							//おまけ
							pEnemy[i].nLife--;

							if (pEnemy[i].pos.x < g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = -15.0f;
								pEnemy[i].move.y = -6.0f;
							}
							else if (pEnemy[i].pos.x > g_aAttack_Box[nCnt].pos.x)
							{
								pEnemy[i].move.x = 15.0f;
								pEnemy[i].move.y = -6.0f;
							}
						}

						//スコア加算
						int* pScore = GetInfo_Score();
						pScore[SCORE_NEW] += 3;

						PlaySound(SOUND_LABEL_HURT);
					}
				}
				break;
			}
		}
	}
}

//************************************************
//攻撃ボックスのアドレスを渡す
//************************************************
ATTACK_BOX* GetInfo_Attack_Box(void)
{
	return &g_aAttack_Box[0];
}

//************************************************
//デバッグ用の攻撃ボックスの可視化
//************************************************
void Draw_Attack_Box_Debug(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Attack_Box, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ATTACK_BOX; nCnt++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexture_Attack_Box);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}