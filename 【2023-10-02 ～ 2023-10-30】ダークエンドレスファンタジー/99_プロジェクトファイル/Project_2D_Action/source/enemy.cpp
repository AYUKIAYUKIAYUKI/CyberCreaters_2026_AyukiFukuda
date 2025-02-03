//************************************************
//
//敵処理[enemy.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "attack_box_enemy.h"
#include "camera.h"
#include "enemy.h"
#include "particle.h"
#include "player.h"
#include "score.h"
#include "stage.h"
#include "tower.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Enemy[AMOUNT_TEX_ENEMY] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Enemy = NULL;	//頂点バッファのポインタ
ENEMY g_aEnemy[AMOUNT_POLYGON_ENEMY];	//敵情報
ENEMY_BOX g_aEnemy_Box[ENEMY_MAX][AMOUNT_POLYGON_ENEMY];	//敵ボックス情報
int g_nCTspawn;	//リジェネキャストタイム

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Enemy()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_00_MOVE,
		&g_pTexture_Enemy[0]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_00_ATK,
		&g_pTexture_Enemy[1]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_00_HURT,
		&g_pTexture_Enemy[2]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_00_DEATH,
		&g_pTexture_Enemy[3]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_01_IDLE,
		&g_pTexture_Enemy[4]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_01_MOVE,
		&g_pTexture_Enemy[5]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_01_ATK,
		&g_pTexture_Enemy[6]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_01_HURT,
		&g_pTexture_Enemy[7]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_01_DEATH,
		&g_pTexture_Enemy[8]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_02_IDLE,
		&g_pTexture_Enemy[9]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_02_MOVE,
		&g_pTexture_Enemy[10]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_02_ATK,
		&g_pTexture_Enemy[11]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_02_HURT,
		&g_pTexture_Enemy[12]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_02_DEATH,
		&g_pTexture_Enemy[13]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_03_IDLE,
		&g_pTexture_Enemy[14]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_03_MOVE,
		&g_pTexture_Enemy[15]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_03_ATK,
		&g_pTexture_Enemy[16]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_03_HURT,
		&g_pTexture_Enemy[17]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_03_DEATH,
		&g_pTexture_Enemy[18]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_IDLE,
		&g_pTexture_Enemy[19]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_MOVE,
		&g_pTexture_Enemy[20]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_ATK,
		&g_pTexture_Enemy[21]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_HURT,
		&g_pTexture_Enemy[22]);

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_04_DEATH,
		&g_pTexture_Enemy[23]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Enemy,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		//頂点座標の初期設定
		pVtx_Enemy[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Enemy[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Enemy[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Enemy[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Enemy[0].rhw = 1.0f;
		pVtx_Enemy[1].rhw = 1.0f;
		pVtx_Enemy[2].rhw = 1.0f;
		pVtx_Enemy[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Enemy[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Enemy[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Enemy[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Enemy[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx_Enemy[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Enemy[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Enemy[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Enemy[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Enemy += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy->Unlock();

	//敵構造体の情報の初期化群
	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		g_aEnemy[i].bUse = false;
		g_aEnemy[i].nStyle = 0;
		g_aEnemy[i].nState = 0;
		g_aEnemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEnemy[i].LR = 0;
		g_aEnemy[i].nCntTex = 0;
		g_aEnemy[i].nCntPattern = 0;
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aEnemy[i].fTexSpan[nCnt] = 0.0f;
			g_aEnemy[i].fRadius[nCnt] = 0.0f;
			g_aEnemy[i].fLength[nCnt] = 0.0f;
			g_aEnemy[i].fAngle[nCnt] = 0.0f;
		}
		g_aEnemy[i].fDisappear = 1.0f;
		g_aEnemy[i].nLife = 0;
		g_aEnemy[i].nCT = 0;
		g_aEnemy[i].bLockonP = false;
	}

	//敵ボックスの初期化
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
		{
			for (int nCntHold = 0; nCntHold < 2; nCntHold++)
			{
				g_aEnemy_Box[i][nCnt].fRadius_Hold[nCntHold];
				g_aEnemy_Box[i][nCnt].fLength_Hold[nCntHold];
				g_aEnemy_Box[i][nCnt].fAngle_Hold[nCntHold];
			}
		}
	}

	g_nCTspawn = AMOUN_RESPAWN_CT;

	//敵用見た目ボックスの生成
	CalcSize_Enemy_Box();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Enemy(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEX_ENEMY; nCnt++)
	{
		if (g_pTexture_Enemy[nCnt] != NULL)
		{
			g_pTexture_Enemy[nCnt]->Release();
			g_pTexture_Enemy[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Enemy != NULL)
	{
		g_pVtxBuff_Enemy->Release();
		g_pVtxBuff_Enemy = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Enemy(void)
{
	//フレームカウント
	g_nCTspawn++;

	//一定時間経過で新たな敵を出現させる
	if (g_nCTspawn >= AMOUN_RESPAWN_CT)
	{
		SetInfo_Enemy();
		g_nCTspawn = 0;
	}

	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		if (g_aEnemy[i].bUse)
		{
			//移動する
			Update_Pos_Enemy(i);

			//消滅処理
			Disapper_Enemy(i);
		}
	}
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Enemy(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Enemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		//敵の種類によって選別
		switch (g_aEnemy[i].nStyle)
		{
		case ENEMY_00:
			//敵の状態によってさらに選別
			switch (g_aEnemy[i].nState)
			{
			case ENEMY_00_STATE_MOVE:
				pDevice->SetTexture(0, g_pTexture_Enemy[0]);
				break;
			case ENEMY_00_STATE_ATK:
				pDevice->SetTexture(0, g_pTexture_Enemy[1]);
				break;
			case ENEMY_00_STATE_HURT:
				pDevice->SetTexture(0, g_pTexture_Enemy[2]);
				break;
			case ENEMY_00_STATE_DEATH:
				pDevice->SetTexture(0, g_pTexture_Enemy[3]);
				break;
			}
			break;
		case ENEMY_01:
			switch (g_aEnemy[i].nState)
			{
			case ENEMY_01_STATE_IDLE:
				pDevice->SetTexture(0, g_pTexture_Enemy[4]);
				break;
			case ENEMY_01_STATE_MOVE:
				pDevice->SetTexture(0, g_pTexture_Enemy[5]);
				break;
			case ENEMY_01_STATE_ATK:
				pDevice->SetTexture(0, g_pTexture_Enemy[6]);
				break;
			case ENEMY_01_STATE_HURT:
				pDevice->SetTexture(0, g_pTexture_Enemy[7]);
				break;
			case ENEMY_01_STATE_DEATH:
				pDevice->SetTexture(0, g_pTexture_Enemy[8]);
				break;
			}
			break;
		case ENEMY_02:
			switch (g_aEnemy[i].nState)
			{
			case ENEMY_02_STATE_IDLE:
				pDevice->SetTexture(0, g_pTexture_Enemy[9]);
				break;
			case ENEMY_02_STATE_MOVE:
				pDevice->SetTexture(0, g_pTexture_Enemy[10]);
				break;
			case ENEMY_02_STATE_ATK:
				pDevice->SetTexture(0, g_pTexture_Enemy[11]);
				break;
			case ENEMY_02_STATE_HURT:
				pDevice->SetTexture(0, g_pTexture_Enemy[12]);
				break;
			case ENEMY_02_STATE_DEATH:
				pDevice->SetTexture(0, g_pTexture_Enemy[13]);
				break;
			}
			break;
		case ENEMY_03:
			switch (g_aEnemy[i].nState)
			{
			case ENEMY_03_STATE_IDLE:
				pDevice->SetTexture(0, g_pTexture_Enemy[14]);
				break;
			case ENEMY_03_STATE_MOVE:
				pDevice->SetTexture(0, g_pTexture_Enemy[15]);
				break;
			case ENEMY_03_STATE_ATK:
				pDevice->SetTexture(0, g_pTexture_Enemy[16]);
				break;
			case ENEMY_03_STATE_HURT:
				pDevice->SetTexture(0, g_pTexture_Enemy[17]);
				break;
			case ENEMY_03_STATE_DEATH:
				pDevice->SetTexture(0, g_pTexture_Enemy[18]);
				break;
			}
			break;
		case ENEMY_04:
			switch (g_aEnemy[i].nState)
			{
			case ENEMY_04_STATE_IDLE:
				pDevice->SetTexture(0, g_pTexture_Enemy[19]);
				break;
			case ENEMY_04_STATE_MOVE:
				pDevice->SetTexture(0, g_pTexture_Enemy[20]);
				break;
			case ENEMY_04_STATE_ATK:
				pDevice->SetTexture(0, g_pTexture_Enemy[21]);
				break;
			case ENEMY_04_STATE_HURT:
				pDevice->SetTexture(0, g_pTexture_Enemy[22]);
				break;
			case ENEMY_04_STATE_DEATH:
				pDevice->SetTexture(0, g_pTexture_Enemy[23]);
				break;
			}
			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//敵の頂点サイズを算出関数
//************************************************
void CalcSize_Enemy_Box(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		switch (i)
		{
		case ENEMY_00:
			for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
			{
				switch (nCnt)
				{
				case ENEMY_00_STATE_MOVE:
					//対角線の長さ
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((175.0f * 175.0f) +
						(175.0f * 175.0f));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = g_aEnemy_Box[i][nCnt].fLength_Hold[0];

					//対角線の角度
					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(175.0f * 2.0f, 175.0f * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = g_aEnemy_Box[i][nCnt].fAngle_Hold[0];
					break;
				case ENEMY_00_STATE_ATK:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((175.0f * 175.0f) +
						(175.0f * 175.0f));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = g_aEnemy_Box[i][nCnt].fLength_Hold[0];

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(175.0f * 2.0f, 175.0f * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = g_aEnemy_Box[i][nCnt].fAngle_Hold[0];
					break;
				case ENEMY_00_STATE_HURT:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((175.0f * 175.0f) +
						(175.0f * 175.0f));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = g_aEnemy_Box[i][nCnt].fLength_Hold[0];

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(175.0f * 2.0f, 175.0f * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = g_aEnemy_Box[i][nCnt].fAngle_Hold[0];
					break;
				case ENEMY_00_STATE_DEATH:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((175.0f * 175.0f) +
						(175.0f * 175.0f));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = g_aEnemy_Box[i][nCnt].fLength_Hold[0];

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(175.0f * 2.0f, 175.0f * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = g_aEnemy_Box[i][nCnt].fAngle_Hold[0];
					break;
				}
			}
			break;
		case ENEMY_01:
			for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
			{
				switch (nCnt)
				{
				case ENEMY_01_STATE_IDLE:
					//対角線の長さ
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((200.0f * 200.0f) +
						((50.0f * 2.0f) * (50.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(200.0f * 200.0f);

					//対角線の角度
					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(200.0f * 2.0f, (50.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(200.0f * 2.0f, 0.0f);
					break;
				case ENEMY_01_STATE_MOVE:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((200.0f * 200.0f) +
						((50.0f * 2.0f) * (50.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(200.0f * 200.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(200.0f * 2.0f, (50.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(200.0f * 2.0f, 0.0f);
					break;
				case ENEMY_01_STATE_ATK:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((200.0f * 200.0f) +
						((50.0f * 2.0f) * (50.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(200.0f * 200.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(200.0f * 2.0f, (50.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(200.0f * 2.0f, 0.0f);
					break;
				case ENEMY_01_STATE_HURT:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((200.0f * 200.0f) +
						((50.0f * 2.0f) * (50.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(200.0f * 200.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(200.0f * 2.0f, (50.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(200.0f * 2.0f, 0.0f);
					break;
				case ENEMY_01_STATE_DEATH:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((200.0f * 200.0f) +
						((50.0f * 2.0f) * (50.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(200.0f * 200.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(200.0f * 2.0f, (50.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(200.0f * 2.0f, 0.0f);
					break;
				}
			}
			break;
		case ENEMY_02:
			for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
			{
				switch (nCnt)
				{
				case ENEMY_02_STATE_IDLE:
					//対角線の長さ
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((150.0f * 150.0f) +
						((40.0f * 2.0f) * (40.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(150.0f * 150.0f);

					//対角線の角度
					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(150.0f * 2.0f, (40.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(150.0f * 2.0f, 0.0f);
					break;
				case ENEMY_02_STATE_MOVE:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((150.0f * 150.0f) +
						((40.0f * 2.0f) * (40.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(150.0f * 150.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(150.0f * 2.0f, (40.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(150.0f * 2.0f, 0.0f);
					break;
				case ENEMY_02_STATE_ATK:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((150.0f * 150.0f) +
						((40.0f * 2.0f) * (40.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(150.0f * 150.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(150.0f * 2.0f, (40.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(150.0f * 2.0f, 0.0f);
					break;
				case ENEMY_02_STATE_HURT:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((150.0f * 150.0f) +
						((40.0f * 2.0f) * (40.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(150.0f * 150.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(150.0f * 2.0f, (40.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(150.0f * 2.0f, 0.0f);
					break;
				case ENEMY_02_STATE_DEATH:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((150.0f * 150.0f) +
						((40.0f * 2.0f) * (40.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(150.0f * 150.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(150.0f * 2.0f, (40.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(150.0f * 2.0f, 0.0f);
					break;
				}
			}
			break;
		case ENEMY_03:
			for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
			{
				switch (nCnt)
				{
				case ENEMY_03_STATE_IDLE:
					//対角線の長さ
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((160.0f * 160.0f) +
						((60.0f * 2.0f) * (60.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(160.0f * 160.0f);

					//対角線の角度
					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(160.0f * 2.0f, (60.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(160.0f * 2.0f, 0.0f);
					break;
				case ENEMY_03_STATE_MOVE:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((160.0f * 160.0f) +
						((60.0f * 2.0f) * (60.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(160.0f * 160.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(160.0f * 2.0f, (60.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(160.0f * 2.0f, 0.0f);
					break;
				case ENEMY_03_STATE_ATK:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((160.0f * 160.0f) +
						((60.0f * 2.0f) * (60.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(160.0f * 160.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(160.0f * 2.0f, (60.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(160.0f * 2.0f, 0.0f);
					break;
				case ENEMY_03_STATE_HURT:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((160.0f * 160.0f) +
						((60.0f * 2.0f) * (60.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(160.0f * 160.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(160.0f * 2.0f, (60.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(160.0f * 2.0f, 0.0f);
					break;
				case ENEMY_03_STATE_DEATH:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((160.0f * 160.0f) +
						((60.0f * 2.0f) * (60.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(160.0f * 160.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(160.0f * 2.0f, (60.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(160.0f * 2.0f, 0.0f);
					break;
				}
			}
			break;
		case ENEMY_04:
			for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
			{
				switch (nCnt)
				{
				case ENEMY_04_STATE_IDLE:
					//対角線の長さ
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((100.0f * 100.0f) +
						((55.0f * 2.0f) * (55.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(100.0f * 100.0f);

					//対角線の角度
					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(100.0f * 2.0f, (55.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(100.0f * 2.0f, 0.0f);
					break;
				case ENEMY_04_STATE_MOVE:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((100.0f * 100.0f) +
						((55.0f * 2.0f) * (55.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(100.0f * 100.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(100.0f * 2.0f, (55.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(100.0f * 2.0f, 0.0f);
					break;
				case ENEMY_04_STATE_ATK:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((100.0f * 100.0f) +
						((55.0f * 2.0f) * (55.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(100.0f * 100.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(100.0f * 2.0f, (55.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(100.0f * 2.0f, 0.0f);
					break;
				case ENEMY_04_STATE_HURT:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((100.0f * 100.0f) +
						((55.0f * 2.0f) * (55.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(100.0f * 100.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(100.0f * 2.0f, (55.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(100.0f * 2.0f, 0.0f);
					break;
				case ENEMY_04_STATE_DEATH:
					g_aEnemy_Box[i][nCnt].fLength_Hold[0] = sqrtf((100.0f * 100.0f) +
						((55.0f * 2.0f) * (55.0f * 2.0f)));
					g_aEnemy_Box[i][nCnt].fLength_Hold[1] = sqrtf(100.0f * 100.0f);

					g_aEnemy_Box[i][nCnt].fAngle_Hold[0] = atan2f(100.0f * 2.0f, (55.0f * 2.0f) * 2.0f);
					g_aEnemy_Box[i][nCnt].fAngle_Hold[1] = atan2f(100.0f * 2.0f, 0.0f);
					break;
				}
			}
			break;
		}
	}
}

//************************************************
//敵構造体の情報を設定する関数
//************************************************
void SetInfo_Enemy(void)
{
	for (int i = 0; i < AMOUNT_POLYGON_ENEMY; i++)
	{
		//空きを検索
		if (!g_aEnemy[i].bUse)
		{
			TOWER* pTower = GetInfo_Tower();
			int R = 0, YR = 0;
			float fReverse = 0.0f;

			//固定
			g_aEnemy[i].bUse = true;

			//種類はなにかな？
			int nStyle = rand() % 10;

			//マジで適当に振りわけ
			if (nStyle == 0 || nStyle == 5)
			{
				g_aEnemy[i].nStyle = ENEMY_00;
			}
			else if (nStyle == 1 || nStyle == 6)
			{
				g_aEnemy[i].nStyle = ENEMY_01;
			}
			else if (nStyle == 2 || nStyle == 7)
			{
				g_aEnemy[i].nStyle = ENEMY_02;
			}
			else if (nStyle == 3 || nStyle == 8)
			{
				g_aEnemy[i].nStyle = ENEMY_03;
			}
			else if (nStyle == 4)
			{
				g_aEnemy[i].nStyle = ENEMY_04;
			}

			//出現させる種類に合わせて設定分け
			switch (g_aEnemy[i].nStyle)
			{
			case ENEMY_00:

				//ランダム、ただし種類によってある程度頒布は差別化
				R = rand() % 2;
				YR = rand() % 10;
				fReverse = 1.0f;
				R == 1 ? 0 : fReverse *= -1.0f;
				g_aEnemy[i].pos = D3DXVECTOR3(pTower->pos.x + (2100.0f * fReverse), -210 + (150.0f * (float)YR), 0.0f);
				g_aEnemy[i].oldpos = g_aEnemy[i].pos;

				//初期向きは位置から決定
				g_aEnemy[i].LR = R;

				//テクスチャ幅は種類に依存
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_00;

				//当たり判定はほぼ同じに調整
				g_aEnemy[i].fRadius[0] = RADIUS_ENEMY_X;
				g_aEnemy[i].fRadius[1] = RADIUS_ENEMY_Y;

				//見た目ボックスも種類に依存
				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[ENEMY_00][ENEMY_00_STATE_MOVE].fLength_Hold[nCnt];
					g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[ENEMY_00][ENEMY_00_STATE_MOVE].fAngle_Hold[nCnt];
				}

				//ライフも種類に合わせて毎回固定
				g_aEnemy[i].nLife = AMOUNT_MAX_LIFE_ENEMY_00;

				/****************以下このフォーマットで分別**************/
				break;
			case ENEMY_01:

				R = rand() % 2;
				YR = rand() % 10;
				fReverse = 1.0f;
				R == 1 ? 0 : fReverse *= -1.0f;
				g_aEnemy[i].pos = D3DXVECTOR3(pTower->pos.x + ((990.0f + (YR * 100.0f)) * fReverse), -100.0f, 0.0f);
				g_aEnemy[i].oldpos = g_aEnemy[i].pos;

				g_aEnemy[i].LR = R;

				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_01;

				g_aEnemy[i].fRadius[0] = 40.0f;
				g_aEnemy[i].fRadius[1] = 40.0f;

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[ENEMY_01][ENEMY_01_STATE_IDLE].fLength_Hold[nCnt];
					g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[ENEMY_01][ENEMY_01_STATE_IDLE].fAngle_Hold[nCnt];
				}

				g_aEnemy[i].nLife = AMOUNT_MAX_LIFE_ENEMY_01;

				break;
			case ENEMY_02:

				R = rand() % 2;
				YR = rand() % 10;
				fReverse = 1.0f;
				R == 1 ? 0 : fReverse *= -1.0f;
				g_aEnemy[i].pos = D3DXVECTOR3(pTower->pos.x + ((990.0f + (YR * 100.0f)) * fReverse), -100.0f, 0.0f);
				g_aEnemy[i].oldpos = g_aEnemy[i].pos;

				g_aEnemy[i].LR = R;

				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_02;

				g_aEnemy[i].fRadius[0] = 30.0f;
				g_aEnemy[i].fRadius[1] = 30.0f;

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[ENEMY_02][ENEMY_02_STATE_IDLE].fLength_Hold[nCnt];
					g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[ENEMY_02][ENEMY_02_STATE_IDLE].fAngle_Hold[nCnt];
				}

				g_aEnemy[i].nLife = AMOUNT_MAX_LIFE_ENEMY_02;

				break;
			case ENEMY_03:

				R = rand() % 2;
				YR = rand() % 10;
				fReverse = 1.0f;
				R == 1 ? 0 : fReverse *= -1.0f;
				g_aEnemy[i].pos = D3DXVECTOR3(pTower->pos.x + ((990.0f + (YR * 30.0f)) * fReverse), -100.0f, 0.0f);
				g_aEnemy[i].oldpos = g_aEnemy[i].pos;

				g_aEnemy[i].LR = R;

				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_03;

				g_aEnemy[i].fRadius[0] = 40.0f;
				g_aEnemy[i].fRadius[1] = 50.0f;

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[ENEMY_03][ENEMY_03_STATE_IDLE].fLength_Hold[nCnt];
					g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[ENEMY_03][ENEMY_03_STATE_IDLE].fAngle_Hold[nCnt];
				}

				g_aEnemy[i].nLife = AMOUNT_MAX_LIFE_ENEMY_03;

				break;
			case ENEMY_04:

				R = rand() % 2;
				YR = rand() % 10;
				fReverse = 1.0f;
				R == 1 ? 0 : fReverse *= -1.0f;
				g_aEnemy[i].pos = D3DXVECTOR3(pTower->pos.x + ((990.0f + (YR * 30.0f)) * fReverse), -100.0f, 0.0f);
				g_aEnemy[i].oldpos = g_aEnemy[i].pos;

				g_aEnemy[i].LR = R;

				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_04;

				g_aEnemy[i].fRadius[0] = 40.0f;
				g_aEnemy[i].fRadius[1] = 40.0f;

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[ENEMY_04][ENEMY_04_STATE_IDLE].fLength_Hold[nCnt];
					g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[ENEMY_04][ENEMY_04_STATE_IDLE].fAngle_Hold[nCnt];
				}

				g_aEnemy[i].nLife = AMOUNT_MAX_LIFE_ENEMY_04;

				break;
			}

			//1体出現させたらループ終了
			break;
		}
	}
}

//************************************************
//敵の位置を設定する関数
//************************************************
void Update_Pos_Enemy(int i)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy;

	TOWER* pTower = GetInfo_Tower();

	//前回の位置を保持
	g_aEnemy[i].oldpos = g_aEnemy[i].pos;

	//重力
	if (g_aEnemy[i].nStyle != ENEMY_00 && g_aEnemy[i].nStyle != ENEMY_03)
	{
		//敵はふんわり
		g_aEnemy[i].move.y = g_aEnemy[i].move.y + (MOVE_SPD_GRAVITY_Y * 0.25f);
	}
	else if (g_aEnemy[i].nStyle == ENEMY_03)
	{
		g_aEnemy[i].move.y = g_aEnemy[i].move.y + (MOVE_SPD_GRAVITY_Y * 0.1f);
	}

	//移動量設定
	switch (g_aEnemy[i].nStyle)
	{
	case ENEMY_00:

		//被弾時はノックバックを優先するため移動量の固定をスルー
		if (g_aEnemy[i].nState != ENEMY_00_STATE_HURT)
		{
			g_aEnemy[i].nCT > 0 ? g_aEnemy[i].nCT-- : 0;

			//タワーへの向きを出す
			D3DXVECTOR3 Vector = pTower->pos - g_aEnemy[i].pos;

			//タワーへの方向を検知
			if (Vector.x > 0)
			{
				//ある程度近づくと止まる
				Vector.x < pTower->fRadius[0] * 1.5f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = 3.0f, g_aEnemy[i].LR = 0;
			}
			else if (Vector.x < 0)
			{
				Vector.x > -pTower->fRadius[0] * 1.5f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = -3.0f, g_aEnemy[i].LR = 1;
			}

			if (g_aEnemy[i].pos.y < pTower->pos.y - 100.0f)
			{
				g_aEnemy[i].move.y = 0.75f;
			}
			else if (g_aEnemy[i].pos.y > pTower->pos.y - 80.0f)
			{
				g_aEnemy[i].move.y = -0.75f;
			}

			//計算用に変換
			Vector.x < 0.0f ? Vector.x *= -1.0f : 0;
			Vector.y < 0.0f ? Vector.y *= -1.0f : 0;

			//タワーに近づいていて、攻撃状態でなくHPがあり、キャストタイムが消化済みである
			if (Vector.x < pTower->fRadius[1] &&
				Vector.y < pTower->fRadius[1] &&
				g_aEnemy[i].nState != ENEMY_00_STATE_ATK &&
				g_aEnemy[i].nLife > 0 && g_aEnemy[i].nCT <= 0)
			{
				//見た目ボックスを初期化
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern = 0;
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_ATK_ENEMY_00;
				//攻撃状態に変更
				g_aEnemy[i].nState = ENEMY_00_STATE_ATK;
			}
		}
		//死亡時
		else if (g_aEnemy[i].nState == ENEMY_00_STATE_DEATH)
		{
			g_aEnemy[i].move.x = 0.0f;
			g_aEnemy[i].move.y = 2.0f;
		}

		break;
	case ENEMY_01:

		//被弾時はノックバックを優先するため移動量の固定をスルー
		if (g_aEnemy[i].nState != ENEMY_01_STATE_HURT && g_aEnemy[i].nState != ENEMY_01_STATE_DEATH)
		{
			g_aEnemy[i].nCT > 0 ? g_aEnemy[i].nCT-- : 0;

			//タワーへの向きを出す
			D3DXVECTOR3 Vector = pTower->pos - g_aEnemy[i].pos;

			//タワーへの方向を検知
			if (Vector.x > 0)
			{
				//ある程度近づくと止まる
				Vector.x < pTower->fRadius[0] * 1.5f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = 3.0f, g_aEnemy[i].LR = 0;
			}
			else if (Vector.x < 0)
			{
				Vector.x > -pTower->fRadius[0] * 1.5f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = -3.0f, g_aEnemy[i].LR = 1;
			}

			//攻撃時は待機や移動の分別を無視
			if (g_aEnemy[i].nState != ENEMY_01_STATE_ATK)
			{
				if (g_aEnemy[i].move.x == 0.0f)
				{
					//それまで待機じゃないときはボックス初期化
					if (g_aEnemy[i].nState != ENEMY_01_STATE_IDLE)
					{
						//見た目ボックスを初期化
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_01;
					}
					//移動量無しで固定
					g_aEnemy[i].nState = ENEMY_01_STATE_IDLE;
				}
				else
				{
					//それまで移動じゃないときはボックス初期化
					if (g_aEnemy[i].nState != ENEMY_01_STATE_MOVE)
					{
						//見た目ボックスを初期化
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_01;
					}
					g_aEnemy[i].nState = ENEMY_01_STATE_MOVE;
				}
			}

			//計算用に変換
			Vector.x < 0.0f ? Vector.x *= -1.0f : 0;

			//タワーに近づいていて、攻撃状態でなくHPがあり、キャストタイムが消化済みである
			if (Vector.x < pTower->fRadius[1] &&
				g_aEnemy[i].nState != ENEMY_01_STATE_ATK &&
				g_aEnemy[i].nLife > 0 && g_aEnemy[i].nCT <= 0)
			{
				//見た目ボックスを初期化
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern = 0;
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_ATK_ENEMY_01;
				//攻撃状態に変更
				g_aEnemy[i].nState = ENEMY_01_STATE_ATK;
			}
		}
		//死亡時
		else if (g_aEnemy[i].nState == ENEMY_01_STATE_DEATH)
		{
			g_aEnemy[i].move.x = 0.0f;
			g_aEnemy[i].move.y = 2.0f;
		}

		break;
	case ENEMY_02:

		//被弾時はノックバックを優先するため移動量の固定をスルー
		if (g_aEnemy[i].nState != ENEMY_02_STATE_HURT && g_aEnemy[i].nState != ENEMY_02_STATE_DEATH)
		{
			g_aEnemy[i].nCT > 0 ? g_aEnemy[i].nCT-- : 0;

			//タワーへの向きを出す
			D3DXVECTOR3 Vector = pTower->pos - g_aEnemy[i].pos;

			//タワーへの方向を検知
			if (Vector.x > 0)
			{
				//ある程度近づくと止まる
				Vector.x < pTower->fRadius[0] * 1.4f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = 6.0f, g_aEnemy[i].LR = 0;
			}
			else if (Vector.x < 0)
			{
				Vector.x > -pTower->fRadius[0] * 1.4f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = -6.0f, g_aEnemy[i].LR = 1;
			}

			//攻撃時は待機や移動の分別を無視
			if (g_aEnemy[i].nState != ENEMY_02_STATE_ATK)
			{
				if (g_aEnemy[i].move.x == 0.0f)
				{
					//それまで待機じゃないときはボックス初期化
					if (g_aEnemy[i].nState != ENEMY_02_STATE_IDLE)
					{
						//見た目ボックスを初期化
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_02;
					}
					//移動量無しで固定
					g_aEnemy[i].nState = ENEMY_02_STATE_IDLE;
				}
				else
				{
					//それまで移動じゃないときはボックス初期化
					if (g_aEnemy[i].nState != ENEMY_02_STATE_MOVE)
					{
						//見た目ボックスを初期化
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_02;
					}
					g_aEnemy[i].nState = ENEMY_02_STATE_MOVE;
				}
			}

			//計算用に変換
			Vector.x < 0.0f ? Vector.x *= -1.0f : 0;

			//タワーに近づいていて、攻撃状態でなくHPがあり、キャストタイムが消化済みである
			if (Vector.x < pTower->fRadius[1] &&
				g_aEnemy[i].nState != ENEMY_02_STATE_ATK &&
				g_aEnemy[i].nLife > 0 && g_aEnemy[i].nCT <= 0)
			{
				//見た目ボックスを初期化
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern = 0;
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_ATK_ENEMY_02;
				//攻撃状態に変更
				g_aEnemy[i].nState = ENEMY_02_STATE_ATK;
			}
		}
		//死亡時
		else if (g_aEnemy[i].nState == ENEMY_02_STATE_DEATH)
		{
			g_aEnemy[i].move.x = 0.0f;
			g_aEnemy[i].move.y = 2.0f;
		}

		break;
	case ENEMY_03:

		//被弾時はノックバックを優先するため移動量の固定をスルー
		if (g_aEnemy[i].nState != ENEMY_03_STATE_HURT && g_aEnemy[i].nState != ENEMY_03_STATE_DEATH)
		{
			g_aEnemy[i].nCT > 0 ? g_aEnemy[i].nCT-- : 0;

			//タワーへの向きを出す
			D3DXVECTOR3 Vector = pTower->pos - g_aEnemy[i].pos;

			//タワーへの方向を検知
			if (Vector.x > 0)
			{
				//ある程度近づくと止まる
				Vector.x < pTower->fRadius[0] * 2.25f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = 2.0f, g_aEnemy[i].LR = 0;
			}
			else if (Vector.x < 0)
			{
				Vector.x > -pTower->fRadius[0] * 2.25f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = -2.0f, g_aEnemy[i].LR = 1;
			}

			//攻撃時は待機や移動の分別を無視
			if (g_aEnemy[i].nState != ENEMY_03_STATE_ATK)
			{
				if (g_aEnemy[i].move.x == 0.0f)
				{
					//それまで待機じゃないときはボックス初期化
					if (g_aEnemy[i].nState != ENEMY_03_STATE_IDLE)
					{
						//見た目ボックスを初期化
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_03;
					}
					//移動量無しで固定
					g_aEnemy[i].nState = ENEMY_03_STATE_IDLE;
				}
				else
				{
					//それまで移動じゃないときはボックス初期化
					if (g_aEnemy[i].nState != ENEMY_03_STATE_MOVE)
					{
						//見た目ボックスを初期化
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_03;
					}
					g_aEnemy[i].nState = ENEMY_03_STATE_MOVE;
				}
			}

			//計算用に変換
			Vector.x < 0.0f ? Vector.x *= -1.0f : 0;

			//タワーに近づいていて、攻撃状態でなくHPがあり、キャストタイムが消化済みである
			if (Vector.x < pTower->fRadius[1] * 1.75f &&
				g_aEnemy[i].nState != ENEMY_03_STATE_ATK &&
				g_aEnemy[i].nLife > 0 && g_aEnemy[i].nCT <= 0)
			{
				//見た目ボックスを初期化
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern = 0;
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_ATK_ENEMY_03;
				//攻撃状態に変更
				g_aEnemy[i].nState = ENEMY_03_STATE_ATK;
			}
		}
		//死亡時
		else if (g_aEnemy[i].nState == ENEMY_03_STATE_DEATH)
		{
			g_aEnemy[i].move.x = 0.0f;
			g_aEnemy[i].move.y = 2.0f;
		}

		break;
	case ENEMY_04:

		//被弾時はノックバックを優先するため移動量の固定をスルー
		if (g_aEnemy[i].nState != ENEMY_04_STATE_HURT && g_aEnemy[i].nState != ENEMY_04_STATE_DEATH)
		{
			g_aEnemy[i].nCT > 0 ? g_aEnemy[i].nCT-- : 0;

			//タワーへの向きを出す
			D3DXVECTOR3 Vector = pTower->pos - g_aEnemy[i].pos;

			//タワーへの方向を検知
			if (Vector.x > 0)
			{
				//ある程度近づくと止まる
				Vector.x < pTower->fRadius[0] * 4.0f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = 4.0f, g_aEnemy[i].LR = 0;
			}
			else if (Vector.x < 0)
			{
				Vector.x > -pTower->fRadius[0] * 4.0f ? g_aEnemy[i].move.x = 0.0f : g_aEnemy[i].move.x = -4.0f, g_aEnemy[i].LR = 1;
			}

			//攻撃時は待機や移動の分別を無視
			if (g_aEnemy[i].nState != ENEMY_04_STATE_ATK)
			{
				if (g_aEnemy[i].move.x == 0.0f)
				{
					//それまで待機じゃないときはボックス初期化
					if (g_aEnemy[i].nState != ENEMY_04_STATE_IDLE)
					{
						//見た目ボックスを初期化
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_04;
					}
					//移動量無しで固定
					g_aEnemy[i].nState = ENEMY_04_STATE_IDLE;
				}
				else
				{
					//それまで移動じゃないときはボックス初期化
					if (g_aEnemy[i].nState != ENEMY_04_STATE_MOVE)
					{
						//見た目ボックスを初期化
						g_aEnemy[i].nCntTex = 0;
						g_aEnemy[i].nCntPattern = 0;
						g_aEnemy[i].fTexSpan[0] = 0.0f;
						g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_04;
					}
					g_aEnemy[i].nState = ENEMY_04_STATE_MOVE;
				}
			}

			//計算用に変換
			Vector.x < 0.0f ? Vector.x *= -1.0f : 0;

			//タワーに近づいていて、攻撃状態でなくHPがあり、キャストタイムが消化済みである
			if (Vector.x < pTower->fRadius[1] * 3.0f &&
				g_aEnemy[i].nState != ENEMY_04_STATE_ATK &&
				g_aEnemy[i].nLife > 0 && g_aEnemy[i].nCT <= 0)
			{
				//見た目ボックスを初期化
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern = 0;
				g_aEnemy[i].fTexSpan[0] = 0.0f;
				g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_ATK_ENEMY_04;
				//攻撃状態に変更
				g_aEnemy[i].nState = ENEMY_04_STATE_ATK;
			}
		}
		//死亡時
		else if (g_aEnemy[i].nState == ENEMY_04_STATE_DEATH)
		{
			g_aEnemy[i].move.x = 0.0f;
			g_aEnemy[i].move.y = 2.0f;
		}

		break;
	}

	//移動
	g_aEnemy[i].pos += g_aEnemy[i].move;

	//見かけの位置を調整する
	Adjust_Pos_Enemy(i);

	//テクスチャアニメーション
	Update_Tex_Enemy(i);

	//ちじむ
	g_aEnemy[i].nLife <= 0 ? g_aEnemy[i].fDisappear *= 0.97f : 0;

	//状態に合わせてボックス調整
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		g_aEnemy[i].fLength[nCnt] = g_aEnemy_Box[g_aEnemy[i].nStyle][g_aEnemy[i].nState].fLength_Hold[nCnt] * g_aEnemy[i].fDisappear;
		g_aEnemy[i].fAngle[nCnt] = g_aEnemy_Box[g_aEnemy[i].nStyle][g_aEnemy[i].nState].fAngle_Hold[nCnt];
	}

	//地形との当たり判定
	if (g_aEnemy[i].nStyle != ENEMY_00)
	{
		HitDetection_Stage(i, HIT_TYPE_ENEMY, &g_aEnemy[i].pos, &g_aEnemy[i].oldpos, &g_aEnemy[i].move, &g_aEnemy[i].fRadius[0]);
	}

	//見かけ移動
	ConvertInfo_Screen(&g_aEnemy[i].pos);

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	pVtx_Enemy += AMOUNT_VTX * i;

	/*デバッグ用当たり判定可視化*/
	//g_aEnemy[i].fLength[0] = sqrtf((RADIUS_ENEMY_X * RADIUS_ENEMY_X) + (RADIUS_ENEMY_Y * RADIUS_ENEMY_Y));
	//g_aEnemy[i].fLength[1] = g_aEnemy[i].fLength[0];
	//g_aEnemy[i].fAngle[0] = atan2f(RADIUS_ENEMY_X * 2.0f, RADIUS_ENEMY_Y * 2.0f);
	//g_aEnemy[i].fAngle[1] = g_aEnemy[i].fAngle[0];

	pVtx_Enemy[0].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z - (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
	pVtx_Enemy[0].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z - (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
	pVtx_Enemy[1].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z + (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
	pVtx_Enemy[1].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z + (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
	pVtx_Enemy[2].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z - g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
	pVtx_Enemy[2].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z - g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
	pVtx_Enemy[3].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z + g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
	pVtx_Enemy[3].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z + g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy->Unlock();
}

//************************************************
//敵を倒したときの消滅処理関数
//************************************************
void Disapper_Enemy(int i)
{
	//HPが0で被弾状態が終わりそうなとき
	switch (g_aEnemy[i].nStyle)
	{
	case ENEMY_00:
		if (g_aEnemy[i].nLife <= 0 && g_aEnemy[i].nState == ENEMY_00_STATE_HURT &&
			g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_00 - 1)
		{
			//見た目ボックス初期化
			g_aEnemy[i].nCntTex = 0;
			g_aEnemy[i].nCntPattern = 0;
			g_aEnemy[i].fTexSpan[0] = 0.0f;
			g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_DEATH_ENEMY_00;

			//死亡状態に
			g_aEnemy[i].nState = ENEMY_00_STATE_DEATH;

			PlaySound(SOUND_LABEL_SLAY);
		}
		break;
	case ENEMY_01:
		if (g_aEnemy[i].nLife <= 0 && g_aEnemy[i].nState == ENEMY_01_STATE_HURT &&
			g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_01 - 1)
		{
			//見た目ボックス初期化
			g_aEnemy[i].nCntTex = 0;
			g_aEnemy[i].nCntPattern = 0;
			g_aEnemy[i].fTexSpan[0] = 0.0f;
			g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_DEATH_ENEMY_01;

			//死亡状態に
			g_aEnemy[i].nState = ENEMY_01_STATE_DEATH;

			PlaySound(SOUND_LABEL_SLAY);
		}
		break;
	case ENEMY_02:
		if (g_aEnemy[i].nLife <= 0 && g_aEnemy[i].nState == ENEMY_02_STATE_HURT &&
			g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_02 - 1)
		{
			//見た目ボックス初期化
			g_aEnemy[i].nCntTex = 0;
			g_aEnemy[i].nCntPattern = 0;
			g_aEnemy[i].fTexSpan[0] = 0.0f;
			g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_DEATH_ENEMY_02;

			//死亡状態に
			g_aEnemy[i].nState = ENEMY_02_STATE_DEATH;

			PlaySound(SOUND_LABEL_SLAY);
		}
		break;
	case ENEMY_03:
		if (g_aEnemy[i].nLife <= 0 && g_aEnemy[i].nState == ENEMY_03_STATE_HURT &&
			g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_03 - 1)
		{
			//見た目ボックス初期化
			g_aEnemy[i].nCntTex = 0;
			g_aEnemy[i].nCntPattern = 0;
			g_aEnemy[i].fTexSpan[0] = 0.0f;
			g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_DEATH_ENEMY_03;

			//死亡状態に
			g_aEnemy[i].nState = ENEMY_03_STATE_DEATH;

			PlaySound(SOUND_LABEL_SLAY);
		}
		break;
	case ENEMY_04:
		if (g_aEnemy[i].nLife <= 0 && g_aEnemy[i].nState == ENEMY_04_STATE_HURT &&
			g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_04 - 1)
		{
			//見た目ボックス初期化
			g_aEnemy[i].nCntTex = 0;
			g_aEnemy[i].nCntPattern = 0;
			g_aEnemy[i].fTexSpan[0] = 0.0f;
			g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_DEATH_ENEMY_04;

			//死亡状態に
			g_aEnemy[i].nState = ENEMY_04_STATE_DEATH;

			PlaySound(SOUND_LABEL_SLAY);
		}
		break;
	}

	if (g_aEnemy[i].nState == -1)
	{
		//情報をクリア
		g_aEnemy[i].bUse = false;
		g_aEnemy[i].nStyle = 0;
		g_aEnemy[i].nState = 0;
		g_aEnemy[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[i].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEnemy[i].LR = 0;
		g_aEnemy[i].nCntTex = 0;
		g_aEnemy[i].nCntPattern = 0;
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			g_aEnemy[i].fTexSpan[nCnt] = 0.0f;
			g_aEnemy[i].fRadius[nCnt] = 0.0f;
			g_aEnemy[i].fLength[nCnt] = 0.0f;
			g_aEnemy[i].fAngle[nCnt] = 0.0f;
		}
		g_aEnemy[i].fDisappear = 1.0f;
		g_aEnemy[i].nLife = 0;
		g_aEnemy[i].bLockonP = false;

		//頂点情報へのポインタ
		VERTEX_2D* pVtx_Enemy;

		//頂点バッファをロックして頂点情報のポインタを取得
		g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

		pVtx_Enemy += AMOUNT_VTX * i;

		pVtx_Enemy[0].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z - (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
		pVtx_Enemy[0].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z - (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
		pVtx_Enemy[1].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z + (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
		pVtx_Enemy[1].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z + (D3DX_PI - g_aEnemy[i].fAngle[0])) * g_aEnemy[i].fLength[0];
		pVtx_Enemy[2].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z - g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
		pVtx_Enemy[2].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z - g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
		pVtx_Enemy[3].pos.x = g_aEnemy[i].pos.x + sinf(g_aEnemy[i].rot.z + g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];
		pVtx_Enemy[3].pos.y = g_aEnemy[i].pos.y + cosf(g_aEnemy[i].rot.z + g_aEnemy[i].fAngle[1]) * g_aEnemy[i].fLength[1];

		//頂点バッファをアンロックする
		g_pVtxBuff_Enemy->Unlock();
	}
}

//************************************************
//位置でいろいろ調整する関数
//************************************************
void Adjust_Pos_Enemy(int i)
{
	//落下すると死亡
	if (g_aEnemy[i].pos.y >= SCREEN_HEIGHT + 100.0f)
	{
		g_aEnemy[i].nLife > 0 ? g_aEnemy[i].nLife = 0, PlaySound(SOUND_LABEL_FALL) : 0;

		switch (g_aEnemy[i].nStyle)
		{
		case ENEMY_00:
			//死なない
			break;
		case ENEMY_01:
			g_aEnemy[i].nState = ENEMY_01_STATE_DEATH;
			break;
		case ENEMY_02:
			g_aEnemy[i].nState = ENEMY_02_STATE_DEATH;
			break;
		case ENEMY_03:
			g_aEnemy[i].nState = ENEMY_03_STATE_DEATH;
			break;
		case ENEMY_04:
			g_aEnemy[i].nState = ENEMY_04_STATE_DEATH;
			break;
		}
	}
}

//************************************************
//敵のテクスチャを動かす関数
//************************************************
void Update_Tex_Enemy(int i)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy;

	//テクスチャを変更
	switch (g_aEnemy[i].nStyle)
	{
	case ENEMY_00:
		switch (g_aEnemy[i].nState)
		{
		case ENEMY_00_STATE_MOVE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_MOVE_ENEMY_00)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_MOVE_ENEMY_00;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_MOVE_ENEMY_00;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_MOVE_ENEMY_00)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_00;
				}
			}
			break;
		case ENEMY_00_STATE_ATK:

			//テクスチャのタイミングに合わせて攻撃ボックス生成
			if (g_aEnemy[i].nCntTex == 0 && g_aEnemy[i].nCntPattern == 6)
			{
				//敵の番号送信
				GiveInfo_Attack_Box_Enemy(i);
			}

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_ATK_ENEMY_00)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_ATK_ENEMY_00;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_ATK_ENEMY_00;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_ATK_ENEMY_00)
				{
					g_aEnemy[i].nState = ENEMY_00_STATE_MOVE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_00;
				}
			}
			break;
		case ENEMY_00_STATE_HURT:
			//パーティクルを飛ばす
			g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Setinfo_Particle(PARTICLE_BLOOD, g_aEnemy[i].pos, g_aEnemy[i].col);

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_HURT_ENEMY_00)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_HURT_ENEMY_00;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_HURT_ENEMY_00;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_00)
				{
					g_aEnemy[i].nState = ENEMY_00_STATE_MOVE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_00;

					//CTを設定
					AMOUNT_CT_ATK_ENEMY_00;
				}
			}
			break;
		case ENEMY_00_STATE_DEATH:
			
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_DEATH_ENEMY_00)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_DEATH_ENEMY_00;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_DEATH_ENEMY_00;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_DEATH_ENEMY_00)
				{
					//クリア
					g_aEnemy[i].nState = -1;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = 0;

					//スコア加算
					int* pScore = GetInfo_Score();
					pScore[SCORE_NEW] += 10;
				}
			}
			break;
		}
		break;
	case ENEMY_01:
		switch (g_aEnemy[i].nState)
		{
		case ENEMY_01_STATE_IDLE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_IDLE_ENEMY_01)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_IDLE_ENEMY_01;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_IDLE_ENEMY_01;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_IDLE_ENEMY_01)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_01;
				}
			}
			break;
		case ENEMY_01_STATE_MOVE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_MOVE_ENEMY_01)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_MOVE_ENEMY_01;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_MOVE_ENEMY_01;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_MOVE_ENEMY_01)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_01;
				}
			}
			break;
		case ENEMY_01_STATE_ATK:

			//テクスチャのタイミングに合わせて攻撃ボックス生成
			if (g_aEnemy[i].nCntTex == 0 && g_aEnemy[i].nCntPattern == 6)
			{
				//敵の番号送信
				GiveInfo_Attack_Box_Enemy(i);
			}

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_ATK_ENEMY_01)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_ATK_ENEMY_01;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_ATK_ENEMY_01;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_ATK_ENEMY_01)
				{
					g_aEnemy[i].nState = ENEMY_01_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_01;
				}
			}
			break;
		case ENEMY_01_STATE_HURT:
			//パーティクルを飛ばす
			g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Setinfo_Particle(PARTICLE_BLOOD, g_aEnemy[i].pos, g_aEnemy[i].col);

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_HURT_ENEMY_01)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_HURT_ENEMY_01;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_HURT_ENEMY_01;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_01)
				{
					g_aEnemy[i].nState = ENEMY_01_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_01;

					//CTを設定
					AMOUNT_CT_ATK_ENEMY_01;
				}
			}
			break;
		case ENEMY_01_STATE_DEATH:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_DEATH_ENEMY_01)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_DEATH_ENEMY_01;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_DEATH_ENEMY_01;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_DEATH_ENEMY_01)
				{
					//クリア
					g_aEnemy[i].nState = -1;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = 0;

					//スコア加算
					int* pScore = GetInfo_Score();
					pScore[SCORE_NEW] += 5;
				}
			}
			break;
		}
		break;
	case ENEMY_02:
		switch (g_aEnemy[i].nState)
		{
		case ENEMY_02_STATE_IDLE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_IDLE_ENEMY_02)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_IDLE_ENEMY_02;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_IDLE_ENEMY_02;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_IDLE_ENEMY_02)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_02;
				}
			}
			break;
		case ENEMY_02_STATE_MOVE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_MOVE_ENEMY_02)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_MOVE_ENEMY_02;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_MOVE_ENEMY_02;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_MOVE_ENEMY_02)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_02;
				}
			}
			break;
		case ENEMY_02_STATE_ATK:

			//テクスチャのタイミングに合わせて攻撃ボックス生成
			if (g_aEnemy[i].nCntTex == 0 && g_aEnemy[i].nCntPattern == 6)
			{
				//敵の番号送信
				GiveInfo_Attack_Box_Enemy(i);
			}

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_ATK_ENEMY_02)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_ATK_ENEMY_02;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_ATK_ENEMY_02;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_ATK_ENEMY_02)
				{
					g_aEnemy[i].nState = ENEMY_02_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_02;
				}
			}
			break;
		case ENEMY_02_STATE_HURT:
			//パーティクルを飛ばす
			g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Setinfo_Particle(PARTICLE_BLOOD, g_aEnemy[i].pos, g_aEnemy[i].col);

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_HURT_ENEMY_02)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_HURT_ENEMY_02;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_HURT_ENEMY_02;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_02)
				{
					g_aEnemy[i].nState = ENEMY_02_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_02;

					//CTを設定
					AMOUNT_CT_ATK_ENEMY_02;
				}
			}
			break;
		case ENEMY_02_STATE_DEATH:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_DEATH_ENEMY_02)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_DEATH_ENEMY_02;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_DEATH_ENEMY_02;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_DEATH_ENEMY_02)
				{
					//クリア
					g_aEnemy[i].nState = -1;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = 0;

					//スコア加算
					int* pScore = GetInfo_Score();
					pScore[SCORE_NEW] += 10;
				}
			}
			break;
		}
		break;
	case ENEMY_03:
		switch (g_aEnemy[i].nState)
		{
		case ENEMY_03_STATE_IDLE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_IDLE_ENEMY_03)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_IDLE_ENEMY_03;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_IDLE_ENEMY_03;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_IDLE_ENEMY_03)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_03;
				}
			}
			break;
		case ENEMY_03_STATE_MOVE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_MOVE_ENEMY_03)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_MOVE_ENEMY_03;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_MOVE_ENEMY_03;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_MOVE_ENEMY_03)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_03;
				}
			}
			break;
		case ENEMY_03_STATE_ATK:

			//テクスチャのタイミングに合わせて攻撃ボックス生成
			if (g_aEnemy[i].nCntTex == 0 && g_aEnemy[i].nCntPattern == 6)
			{
				//敵の番号送信
				GiveInfo_Attack_Box_Enemy(i);
			}

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_ATK_ENEMY_03)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_ATK_ENEMY_03;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_ATK_ENEMY_03;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_ATK_ENEMY_03)
				{
					g_aEnemy[i].nState = ENEMY_03_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_03;
				}
			}
			break;
		case ENEMY_03_STATE_HURT:
			//パーティクルを飛ばす
			g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Setinfo_Particle(PARTICLE_BLOOD, g_aEnemy[i].pos, g_aEnemy[i].col);

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_HURT_ENEMY_03)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_HURT_ENEMY_03;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_HURT_ENEMY_03;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_03)
				{
					g_aEnemy[i].nState = ENEMY_03_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_03;

					//CTを設定
					AMOUNT_CT_ATK_ENEMY_03;
				}
			}
			break;
		case ENEMY_03_STATE_DEATH:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_DEATH_ENEMY_03)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_DEATH_ENEMY_03;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_DEATH_ENEMY_03;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_DEATH_ENEMY_03)
				{
					//クリア
					g_aEnemy[i].nState = -1;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = 0;

					//スコア加算
					int* pScore = GetInfo_Score();
					pScore[SCORE_NEW] += 15;
				}
			}
			break;
		}
		break;
	case ENEMY_04:
		switch (g_aEnemy[i].nState)
		{
		case ENEMY_04_STATE_IDLE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_IDLE_ENEMY_04)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_IDLE_ENEMY_04;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_IDLE_ENEMY_04;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_IDLE_ENEMY_04)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_04;
				}
			}
			break;
		case ENEMY_04_STATE_MOVE:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_MOVE_ENEMY_04)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_MOVE_ENEMY_04;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_MOVE_ENEMY_04;
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_MOVE_ENEMY_04)
				{
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_MOVE_ENEMY_04;
				}
			}
			break;
		case ENEMY_04_STATE_ATK:

			//テクスチャのタイミングに合わせて攻撃ボックス生成
			if (g_aEnemy[i].nCntTex == 0 && g_aEnemy[i].nCntPattern == 6)
			{
				//敵の番号送信
				GiveInfo_Attack_Box_Enemy(i);
			}

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_ATK_ENEMY_04)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_ATK_ENEMY_04;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_ATK_ENEMY_04;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_ATK_ENEMY_04)
				{
					g_aEnemy[i].nState = ENEMY_04_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_04;
				}
			}
			break;
		case ENEMY_04_STATE_HURT:
			//パーティクルを飛ばす
			g_aEnemy[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Setinfo_Particle(PARTICLE_BLOOD, g_aEnemy[i].pos, g_aEnemy[i].col);

			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_HURT_ENEMY_04)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_HURT_ENEMY_04;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_HURT_ENEMY_04;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_HURT_ENEMY_04)
				{
					g_aEnemy[i].nState = ENEMY_04_STATE_IDLE;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_ENEMY_04;

					//CTを設定
					AMOUNT_CT_ATK_ENEMY_04;
				}
			}
			break;
		case ENEMY_04_STATE_DEATH:
			g_aEnemy[i].nCntTex++;
			if (g_aEnemy[i].nCntTex > SPD_CHANGE_TEX_DEATH_ENEMY_04)
			{
				g_aEnemy[i].nCntTex = 0;
				g_aEnemy[i].nCntPattern++;
				g_aEnemy[i].fTexSpan[0] += SPAN_CHANGE_TEX_DEATH_ENEMY_04;
				g_aEnemy[i].fTexSpan[1] += SPAN_CHANGE_TEX_DEATH_ENEMY_04;
				//1ループで終了
				if (g_aEnemy[i].nCntPattern >= AMOUNT_STYLE_TEX_DEATH_ENEMY_04)
				{
					//クリア
					g_aEnemy[i].nState = -1;
					g_aEnemy[i].nCntPattern = 0;
					g_aEnemy[i].fTexSpan[0] = 0;
					g_aEnemy[i].fTexSpan[1] = 0;

					//スコア加算
					int* pScore = GetInfo_Score();
					pScore[SCORE_NEW] += 20;
				}
			}
			break;
		}
		break;
	}

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	pVtx_Enemy += AMOUNT_VTX * i;

	if (g_aEnemy[i].LR == 0)
	{
		pVtx_Enemy[0].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[0], 0.0f);
		pVtx_Enemy[1].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[1], 0.0f);
		pVtx_Enemy[2].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[0], 1.0f);
		pVtx_Enemy[3].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[1], 1.0f);
	}
	else
	{
		pVtx_Enemy[0].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[1], 0.0f);
		pVtx_Enemy[1].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[0], 0.0f);
		pVtx_Enemy[2].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[1], 1.0f);
		pVtx_Enemy[3].tex = D3DXVECTOR2(g_aEnemy[i].fTexSpan[0], 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy->Unlock();
}

//************************************************
//敵構造体のアドレスを渡す
//************************************************
ENEMY* GetInfo_Enemy(void)
{
	return &g_aEnemy[0];
}