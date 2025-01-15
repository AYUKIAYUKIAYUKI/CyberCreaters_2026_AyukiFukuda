//************************************************
//
//敵用攻撃ボックス処理[attack_box_enemy.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "sound.h"
#include "attack_box_enemy.h"
#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "tower.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Attack_Box_Enemy[AMOUNT_TEX_BOX] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Attack_Box_Enemy = NULL;	//頂点バッファのポインタ
ATTACK_BOX_ENEMY g_aAttack_Box_Enemy[AMOUNT_POLYGON_ENEMY];	//敵攻撃ボックス

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Attack_Box_Enemy()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_NONE,
		&g_pTexture_Attack_Box_Enemy[BOX_MODE_NONE]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_BALL,
		&g_pTexture_Attack_Box_Enemy[BOX_MODE_FIRE]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_BALLEND,
		&g_pTexture_Attack_Box_Enemy[BOX_MODE_FIRE_END]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Attack_Box_Enemy,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Attack_Box_Enemy;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Attack_Box_Enemy->Lock(0, 0, (void**)&pVtx_Attack_Box_Enemy, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Attack_Box_Enemy[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box_Enemy[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box_Enemy[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Attack_Box_Enemy[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Attack_Box_Enemy[0].rhw = 1.0f;
		pVtx_Attack_Box_Enemy[1].rhw = 1.0f;
		pVtx_Attack_Box_Enemy[2].rhw = 1.0f;
		pVtx_Attack_Box_Enemy[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Attack_Box_Enemy[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.2f);
		pVtx_Attack_Box_Enemy[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.2f);
		pVtx_Attack_Box_Enemy[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.2f);
		pVtx_Attack_Box_Enemy[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.2f);

		//テクスチャ座標の初期設定
		pVtx_Attack_Box_Enemy[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Attack_Box_Enemy[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Attack_Box_Enemy[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Attack_Box_Enemy[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Attack_Box_Enemy += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Attack_Box_Enemy->Unlock();

	//敵攻撃ボックス構造体の情報の初期化群
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		g_aAttack_Box_Enemy[nCnt].nMode = BOX_MODE_NONE;
		g_aAttack_Box_Enemy[nCnt].bUse = false;
		g_aAttack_Box_Enemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box_Enemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box_Enemy[nCnt].fX = 0.0f;
		g_aAttack_Box_Enemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aAttack_Box_Enemy[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aAttack_Box_Enemy[nCnt].LR = 0;
		g_aAttack_Box_Enemy[nCnt].nCntTex = 0;
		g_aAttack_Box_Enemy[nCnt].nCntPattern = 0;
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aAttack_Box_Enemy[nCnt].fTexSpan[nCnt] = 0.0f;
			g_aAttack_Box_Enemy[nCnt].fRadius[nCnt2] = 0.0f;
			g_aAttack_Box_Enemy[nCnt].fLength[nCnt2] = 0.0f;
			g_aAttack_Box_Enemy[nCnt].fAngle[nCnt2] = 0.0f;
		}
		g_aAttack_Box_Enemy[nCnt].nRemain = 0;
	}
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Attack_Box_Enemy(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEX_BOX; nCnt++)
	{
		if (g_pTexture_Attack_Box_Enemy[nCnt] != NULL)
		{
			g_pTexture_Attack_Box_Enemy[nCnt]->Release();
			g_pTexture_Attack_Box_Enemy[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Attack_Box_Enemy != NULL)
	{
		g_pVtxBuff_Attack_Box_Enemy->Release();
		g_pVtxBuff_Attack_Box_Enemy = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Attack_Box_Enemy(void)
{
	//攻撃ボックスを展開
	Update_Pos_Attack_Box_Enemy();

	//攻撃ボックスの残存時間を減少
	Disapper_Attack_Box_Enemy();
}

//************************************************
//攻撃ボックスの情報を設定する関数
//************************************************
void GiveInfo_Attack_Box_Enemy(int i)
{
	//1つ召喚
	if (!g_aAttack_Box_Enemy[i].bUse)
	{
		g_aAttack_Box_Enemy[i].bUse = true;

		Front_Enemy(i);
	}
}

//************************************************
//敵攻撃ボックスの情報を設定する関数
//************************************************
void Front_Enemy(int i)
{
	ENEMY* pEnemy = GetInfo_Enemy();

	//敵ごとに差別化
	switch (pEnemy[i].nStyle)
	{
	case ENEMY_00:
		//出現位置
		switch (pEnemy[i].LR)
		{
			//→
		case 0:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x + 20.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y + 30.0f;
			break;
			//←
		case 1:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x - 20.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y + 30.0f;
			break;
		}

		//サイズ
		g_aAttack_Box_Enemy[i].fRadius[0] = 30.0f;
		g_aAttack_Box_Enemy[i].fRadius[1] = 30.0f;

		//対角線の長さ
		g_aAttack_Box_Enemy[i].fLength[0] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]) +
			((g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f)));
		g_aAttack_Box_Enemy[i].fLength[1] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]));

		//対角線の角度
		g_aAttack_Box_Enemy[i].fAngle[0] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box_Enemy[i].fAngle[1] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, 0.0f);

		//キャスト時間
		//g_aAttack_Box_Enemy[i].nAppear = 6 * SPD_CHANGE_TEX_ATK_ENEMY_00;
		g_aAttack_Box_Enemy[i].nAppear = 0;

		//残存時間
		g_aAttack_Box_Enemy[i].nRemain = 10;

		//攻撃キャストタイム設定
		pEnemy[i].nCT = AMOUNT_CT_ATK_ENEMY_00;

		/****************以下このフォーマットで分別**************/
		break;
	case ENEMY_01:
		switch (pEnemy[i].LR)
		{
		case 0:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x + 40.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		case 1:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x - 40.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		}

		g_aAttack_Box_Enemy[i].fRadius[0] = 30.0f;
		g_aAttack_Box_Enemy[i].fRadius[1] = 40.0f;

		g_aAttack_Box_Enemy[i].fLength[0] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]) +
			((g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f)));
		g_aAttack_Box_Enemy[i].fLength[1] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]));

		g_aAttack_Box_Enemy[i].fAngle[0] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box_Enemy[i].fAngle[1] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box_Enemy[i].nRemain = 10;

		pEnemy[i].nCT = AMOUNT_CT_ATK_ENEMY_01;

		break;
	case ENEMY_02:
		switch (pEnemy[i].LR)
		{
		case 0:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x + 30.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		case 1:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x - 30.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		}

		g_aAttack_Box_Enemy[i].fRadius[0] = 50.0f;
		g_aAttack_Box_Enemy[i].fRadius[1] = 40.0f;

		g_aAttack_Box_Enemy[i].fLength[0] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]) +
			((g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f)));
		g_aAttack_Box_Enemy[i].fLength[1] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]));

		g_aAttack_Box_Enemy[i].fAngle[0] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box_Enemy[i].fAngle[1] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box_Enemy[i].nRemain = 10;

		pEnemy[i].nCT = AMOUNT_CT_ATK_ENEMY_02;

		break;
	case ENEMY_03:
		switch (pEnemy[i].LR)
		{
		case 0:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x + 75.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		case 1:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x - 75.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		}

		g_aAttack_Box_Enemy[i].fRadius[0] = 80.0f;
		g_aAttack_Box_Enemy[i].fRadius[1] = 60.0f;

		g_aAttack_Box_Enemy[i].fLength[0] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]) +
			((g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f)));
		g_aAttack_Box_Enemy[i].fLength[1] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]));

		g_aAttack_Box_Enemy[i].fAngle[0] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box_Enemy[i].fAngle[1] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box_Enemy[i].nRemain = 10;

		pEnemy[i].nCT = AMOUNT_CT_ATK_ENEMY_03;

		break;
	case ENEMY_04:

		//炎モードに
		g_aAttack_Box_Enemy[i].nMode = BOX_MODE_FIRE;

		//向きを代入
		g_aAttack_Box_Enemy[i].LR = pEnemy[i].LR;

		switch (pEnemy[i].LR)
		{
		case 0:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x + 90.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		case 1:
			g_aAttack_Box_Enemy[i].pos.x = pEnemy[i].pos.x - 90.0f;
			g_aAttack_Box_Enemy[i].pos.y = pEnemy[i].pos.y - 10.0f;
			break;
		}

		g_aAttack_Box_Enemy[i].move.x = 6.0f;

		g_aAttack_Box_Enemy[i].nCntTex = 0;
		g_aAttack_Box_Enemy[i].nCntPattern = 0;

		g_aAttack_Box_Enemy[i].fTexSpan[0] = 0.0f;
		g_aAttack_Box_Enemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_FIRE_ENEMY_04;

		g_aAttack_Box_Enemy[i].fRadius[0] = 30.0f;
		g_aAttack_Box_Enemy[i].fRadius[1] = 30.0f;

		g_aAttack_Box_Enemy[i].fLength[0] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]) +
			((g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f)));
		g_aAttack_Box_Enemy[i].fLength[1] = sqrtf((g_aAttack_Box_Enemy[i].fRadius[0] * g_aAttack_Box_Enemy[i].fRadius[0]));

		g_aAttack_Box_Enemy[i].fAngle[0] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, (g_aAttack_Box_Enemy[i].fRadius[1] * 2.0f) * 2.0f);
		g_aAttack_Box_Enemy[i].fAngle[1] = atan2f(g_aAttack_Box_Enemy[i].fRadius[0] * 2.0f, 0.0f);

		g_aAttack_Box_Enemy[i].nAppear = 25;

		g_aAttack_Box_Enemy[i].nRemain = 35;

		pEnemy[i].nCT = AMOUNT_CT_ATK_ENEMY_04;

		break;
	}
}

//************************************************
//攻撃ボックスのポリゴンを展開する関数
//************************************************
void Update_Pos_Attack_Box_Enemy(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Attack_Box_Enemy;

	ENEMY* pEnemy = GetInfo_Enemy();

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Attack_Box_Enemy->Lock(0, 0, (void**)&pVtx_Attack_Box_Enemy, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//キャスト済みかつ使用判定がでているもののみ出現
		if (g_aAttack_Box_Enemy[nCnt].bUse && g_aAttack_Box_Enemy[nCnt].nAppear <= 0)
		{
			//種類ごとに位置同期
			switch (pEnemy[nCnt].nStyle)
			{
			case ENEMY_00:
				switch (pEnemy[nCnt].LR)
				{
				case 0:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x + 20.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y + 30.0f;
					break;
				case 1:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x - 20.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y + 30.0f;
					break;
				}
				break;
			case ENEMY_01:
				switch (pEnemy[nCnt].LR)
				{
				case 0:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x + 40.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				case 1:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x - 40.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				}
				break;
			case ENEMY_02:
				switch (pEnemy[nCnt].LR)
				{
				case 0:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x + 30.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				case 1:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x - 30.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				}
				break;
			case ENEMY_03:
				switch (pEnemy[nCnt].LR)
				{
				case 0:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x + 75.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				case 1:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x - 75.0f;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				}
				break;
			case ENEMY_04:
				g_aAttack_Box_Enemy[nCnt].fX += g_aAttack_Box_Enemy[nCnt].move.x;
				switch (pEnemy[nCnt].LR)
				{
				case 0:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x + 90.0f + g_aAttack_Box_Enemy[nCnt].fX;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				case 1:
					g_aAttack_Box_Enemy[nCnt].pos.x = pEnemy[nCnt].pos.x - 90.0f - g_aAttack_Box_Enemy[nCnt].fX;
					g_aAttack_Box_Enemy[nCnt].pos.y = pEnemy[nCnt].pos.y - 10.0f;
					break;
				}
				break;
			}

			//色
			Update_Col_Attack_Box_Enemy(nCnt);

			//テク
			Update_Tex_Attack_Box_Enemy(nCnt);

			//疑似スクロール
			ConvertInfo_Screen(&g_aAttack_Box_Enemy[nCnt].pos);

			//当たり判定
			HitDetection_Attack_Box_Enemy(nCnt);

			pVtx_Attack_Box_Enemy[0].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z - (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
			pVtx_Attack_Box_Enemy[0].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z - (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
			pVtx_Attack_Box_Enemy[1].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z + (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
			pVtx_Attack_Box_Enemy[1].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z + (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
			pVtx_Attack_Box_Enemy[2].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z - g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
			pVtx_Attack_Box_Enemy[2].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z - g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
			pVtx_Attack_Box_Enemy[3].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z + g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
			pVtx_Attack_Box_Enemy[3].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z + g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
		}
		//キャスト経過
		else if (g_aAttack_Box_Enemy[nCnt].bUse)
		{
			g_aAttack_Box_Enemy[nCnt].nAppear--;
		}

		pVtx_Attack_Box_Enemy += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Attack_Box_Enemy->Unlock();
}

//************************************************
//攻撃ボックス色間数
//************************************************
void Update_Col_Attack_Box_Enemy(int i)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Attack_Box_Enemy;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Attack_Box_Enemy->Lock(0, 0, (void**)&pVtx_Attack_Box_Enemy, 0);

	pVtx_Attack_Box_Enemy += AMOUNT_VTX * i;

	//そもそも表示するかどうか
	if (g_aAttack_Box_Enemy[i].nMode != BOX_MODE_FIRE &&
		g_aAttack_Box_Enemy[i].nMode != BOX_MODE_FIRE_END)
	{
		pVtx_Attack_Box_Enemy[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f);
		pVtx_Attack_Box_Enemy[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f);
		pVtx_Attack_Box_Enemy[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f);
		pVtx_Attack_Box_Enemy[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		pVtx_Attack_Box_Enemy[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Attack_Box_Enemy[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Attack_Box_Enemy[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Attack_Box_Enemy[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Attack_Box_Enemy->Unlock();
}

//************************************************
//敵のテクスチャを動かす関数
//************************************************
void Update_Tex_Attack_Box_Enemy(int i)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Attack_Box_Enemy;

	//テクスチャを変更
	switch (g_aAttack_Box_Enemy[i].nMode)
	{
	case BOX_MODE_FIRE:
		g_aAttack_Box_Enemy[i].nCntTex++;
		if (g_aAttack_Box_Enemy[i].nCntTex > SPD_CHANGE_TEX_FIRE_ENEMY_04)
		{
			g_aAttack_Box_Enemy[i].nCntTex = 0;
			g_aAttack_Box_Enemy[i].nCntPattern++;
			g_aAttack_Box_Enemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_FIRE_ENEMY_04;
			g_aAttack_Box_Enemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_FIRE_ENEMY_04;
			//1回
			if (g_aAttack_Box_Enemy[i].nCntPattern >= AMOUNT_STYLE_TEX_FIRE_ENEMY_04)
			{
				g_aAttack_Box_Enemy[i].nCntPattern = 0;
				g_aAttack_Box_Enemy[i].fTexSpan[0] = 0;
				g_aAttack_Box_Enemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_FIREEND_ENEMY_04;

				g_aAttack_Box_Enemy[i].nMode = BOX_MODE_FIRE_END;
			}
		}
		break;
	case BOX_MODE_FIRE_END:
		g_aAttack_Box_Enemy[i].nCntTex++;
		if (g_aAttack_Box_Enemy[i].nCntTex > SPD_CHANGE_TEX_FIREEND_ENEMY_04)
		{
			g_aAttack_Box_Enemy[i].nCntTex = 0;
			g_aAttack_Box_Enemy[i].nCntPattern++;
			g_aAttack_Box_Enemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_FIREEND_ENEMY_04;
			g_aAttack_Box_Enemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_FIREEND_ENEMY_04;
			//1回
			if (g_aAttack_Box_Enemy[i].nCntPattern >= AMOUNT_STYLE_TEX_FIREEND_ENEMY_04)
			{
				g_aAttack_Box_Enemy[i].nCntPattern = 0;
				g_aAttack_Box_Enemy[i].fTexSpan[0] = 0;
				g_aAttack_Box_Enemy[i].fTexSpan[1] = 0;

				g_aAttack_Box_Enemy[i].nMode = BOX_MODE_NONE;
			}
		}
		break;
	}
	
	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Attack_Box_Enemy->Lock(0, 0, (void**)&pVtx_Attack_Box_Enemy, 0);

	pVtx_Attack_Box_Enemy += AMOUNT_VTX * i;

	if (g_aAttack_Box_Enemy[i].LR == 0)
	{
		pVtx_Attack_Box_Enemy[0].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[0], 0.0f);
		pVtx_Attack_Box_Enemy[1].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[1], 0.0f);
		pVtx_Attack_Box_Enemy[2].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[0], 1.0f);
		pVtx_Attack_Box_Enemy[3].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[1], 1.0f);
	}
	else
	{
		pVtx_Attack_Box_Enemy[0].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[1], 0.0f);
		pVtx_Attack_Box_Enemy[1].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[0], 0.0f);
		pVtx_Attack_Box_Enemy[2].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[1], 1.0f);
		pVtx_Attack_Box_Enemy[3].tex = D3DXVECTOR2(g_aAttack_Box_Enemy[i].fTexSpan[0], 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Attack_Box_Enemy->Unlock();
}

//************************************************
//攻撃ボックス終了関数
//************************************************
void Disapper_Attack_Box_Enemy(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//キャスト済みボックスが出てるとき
		if (g_aAttack_Box_Enemy[nCnt].bUse && g_aAttack_Box_Enemy[nCnt].nAppear <= 0)
		{
			//残存減少
			if (g_aAttack_Box_Enemy[nCnt].nRemain > 0)
			{
				g_aAttack_Box_Enemy[nCnt].nRemain--;
			}
			//消滅
			else
			{
				g_aAttack_Box_Enemy[nCnt].nMode = BOX_MODE_NONE;
				g_aAttack_Box_Enemy[nCnt].bUse = false;
				g_aAttack_Box_Enemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aAttack_Box_Enemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_aAttack_Box_Enemy[nCnt].fX = 0.0f;
				g_aAttack_Box_Enemy[nCnt].LR = 0;
				g_aAttack_Box_Enemy[nCnt].nCntTex = 0;
				g_aAttack_Box_Enemy[nCnt].nCntPattern = 0;
				for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
				{
					g_aAttack_Box_Enemy[nCnt].fTexSpan[nCnt] = 0.0f;
					g_aAttack_Box_Enemy[nCnt].fRadius[nCnt2] = 0.0f;
					g_aAttack_Box_Enemy[nCnt].fLength[nCnt2] = 0.0f;
					g_aAttack_Box_Enemy[nCnt].fAngle[nCnt2] = 0.0f;
				}
				g_aAttack_Box_Enemy[nCnt].nRemain = 0;

				//頂点情報へのポインタ
				VERTEX_2D* pVtx_Attack_Box_Enemy;

				//頂点バッファをロックして頂点情報のポインタを取得
				g_pVtxBuff_Attack_Box_Enemy->Lock(0, 0, (void**)&pVtx_Attack_Box_Enemy, 0);

				pVtx_Attack_Box_Enemy += AMOUNT_VTX * nCnt;

				pVtx_Attack_Box_Enemy[0].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z - (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
				pVtx_Attack_Box_Enemy[0].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z - (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
				pVtx_Attack_Box_Enemy[1].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z + (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
				pVtx_Attack_Box_Enemy[1].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z + (D3DX_PI - g_aAttack_Box_Enemy[nCnt].fAngle[0])) * g_aAttack_Box_Enemy[nCnt].fLength[0];
				pVtx_Attack_Box_Enemy[2].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z - g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
				pVtx_Attack_Box_Enemy[2].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z - g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
				pVtx_Attack_Box_Enemy[3].pos.x = g_aAttack_Box_Enemy[nCnt].pos.x + sinf(g_aAttack_Box_Enemy[nCnt].rot.z + g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];
				pVtx_Attack_Box_Enemy[3].pos.y = g_aAttack_Box_Enemy[nCnt].pos.y + cosf(g_aAttack_Box_Enemy[nCnt].rot.z + g_aAttack_Box_Enemy[nCnt].fAngle[1]) * g_aAttack_Box_Enemy[nCnt].fLength[1];

				//頂点バッファをアンロックする
				g_pVtxBuff_Attack_Box_Enemy->Unlock();
			}
		}
	}
}

//************************************************
//当たり判定関数
//************************************************
void HitDetection_Attack_Box_Enemy(int nCnt)
{
	ENEMY* pEnemy = GetInfo_Enemy();
	PLAYER* pPlayer = GetInfo_Player();
	TOWER* pTower = GetInfo_Tower();

	//攻撃ボックスとの当たり判定
	//敵生成のボックスのため、プレイヤーとボックス、タワーとボックスで判定

	//プレイヤーにこの番号の攻撃ボックスが触れている
	if (pPlayer->pos.x - pPlayer->fRadius[0] < g_aAttack_Box_Enemy[nCnt].pos.x + g_aAttack_Box_Enemy[nCnt].fRadius[0] &&
		pPlayer->pos.x + pPlayer->fRadius[0] > g_aAttack_Box_Enemy[nCnt].pos.x - g_aAttack_Box_Enemy[nCnt].fRadius[0] &&
		pPlayer->pos.y - (pPlayer->fRadius[1] * 2.0f) < g_aAttack_Box_Enemy[nCnt].pos.y &&
		pPlayer->pos.y > g_aAttack_Box_Enemy[nCnt].pos.y - (g_aAttack_Box_Enemy[nCnt].fRadius[1] * 2.0f) &&
		pPlayer->nState != PLAYER_STATE_HURT1 && pPlayer->nState != PLAYER_STATE_HURT2)
	{
		//ライフを減らす
		//pPlayer->nLife--;

		//見た目ボックス初期化
		pPlayer->nCntTex = 0;
		pPlayer->nCntPattern = 0;
		pPlayer->fTexSpan[0] = 0.0f;
		pPlayer->fTexSpan[1] = SPAN_CHANGE_TEX_HURT1_PLAYER;

		//被弾状態に差し替えて、連続被弾を防止
		int n = rand() % 2;
		n == 0 ?
			pPlayer->nState = PLAYER_STATE_HURT1 :
			pPlayer->nState = PLAYER_STATE_HURT2;

		//この敵の向きに合わせてノックバック
		pEnemy[nCnt].LR == 0 ? pPlayer->move.x = 5.0f : pPlayer->move.x = -5.0f;
		pPlayer->move.y = -1.0f;

		PlaySound(SOUND_LABEL_PHURT);

		//貫通しない
		if (g_aAttack_Box_Enemy[nCnt].nMode == BOX_MODE_FIRE)
		{
			g_aAttack_Box_Enemy[nCnt].nCntPattern = 0;
			g_aAttack_Box_Enemy[nCnt].fTexSpan[0] = 0;
			g_aAttack_Box_Enemy[nCnt].fTexSpan[1] = SPAN_CHANGE_TEX_FIREEND_ENEMY_04;

			g_aAttack_Box_Enemy[nCnt].nMode = BOX_MODE_FIRE_END;

			g_aAttack_Box_Enemy[nCnt].nRemain = 5;
		}
	}

	//タワーにこの番号の攻撃ボックスが触れている
	if (pTower->pos.x - pTower->fRadius[0] < g_aAttack_Box_Enemy[nCnt].pos.x + g_aAttack_Box_Enemy[nCnt].fRadius[0] &&
		pTower->pos.x + pTower->fRadius[0] > g_aAttack_Box_Enemy[nCnt].pos.x - g_aAttack_Box_Enemy[nCnt].fRadius[0] &&
		pTower->pos.y - (pTower->fRadius[1] * 2.0f) < g_aAttack_Box_Enemy[nCnt].pos.y &&
		pTower->pos.y > g_aAttack_Box_Enemy[nCnt].pos.y - (g_aAttack_Box_Enemy[nCnt].fRadius[1] * 2.0f) &&
		pTower->nCT <= 0)
	{
		//ライフを減らす
		pTower->nLife--;

		//キャストタイム設定
		pTower->nCT = 90;

		PlaySound(SOUND_LABEL_THURT);
	}
}

//************************************************
//攻撃ボックスのアドレスを渡す
//************************************************
ATTACK_BOX_ENEMY* GetInfo_Attack_Box_Enemy(void)
{
	return &g_aAttack_Box_Enemy[0];
}

//************************************************
//デバッグ用の攻撃ボックスの可視化
//************************************************
void Draw_Attack_Box_Enemy_Debug(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Attack_Box_Enemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//テクスチャの設定
		switch (g_aAttack_Box_Enemy[nCnt].nMode)
		{
		case BOX_MODE_NONE:
			pDevice->SetTexture(0, g_pTexture_Attack_Box_Enemy[BOX_MODE_NONE]);
			break;
		case BOX_MODE_FIRE:
			pDevice->SetTexture(0, g_pTexture_Attack_Box_Enemy[BOX_MODE_FIRE]);
			break;
		case BOX_MODE_FIRE_END:
			pDevice->SetTexture(0, g_pTexture_Attack_Box_Enemy[BOX_MODE_FIRE_END]);
			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}