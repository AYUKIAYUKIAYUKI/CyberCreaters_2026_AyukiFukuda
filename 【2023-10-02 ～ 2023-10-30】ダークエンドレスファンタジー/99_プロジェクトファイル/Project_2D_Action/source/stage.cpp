//************************************************
//
//ステージオブジェクト処理(荒れ地)[stege.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "stage.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Stage[AMOUNT_TEX_STAGE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Stage = NULL;	//頂点バッファのポインタ
STAGE g_aStage[AMOUNT_POLYGON_STAGE];	//ステージ構造体
double g_aFileData_Satge_Object[AMOUNT_POLYGON_STAGE][AMOUNT_POLYGON_STAGE] = {};	//外部の情報を格納
double g_aInfo_Satge_Object[AMOUNT_POLYGON_STAGE][AMOUNT_POLYGON_STAGE] = {};	//オブジェクトの情報を格納
double g_aPosInfo_Satge_Object[AMOUNT_POLYGON_STAGE][AMOUNT_POLYGON_STAGE] = {};	//位置の情報を格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Stage()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_STAGE_OBJECT_BLOCK,
		&g_pTexture_Stage[0]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_STAGE_OBJECT_LEFT,
		&g_pTexture_Stage[1]);

	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_STAGE_OBJECT_RIGHT,
		&g_pTexture_Stage[2]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_STAGE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Stage,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Stage;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Stage->Lock(0, 0, (void**)&pVtx_Stage, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		//頂点座標の初期設定
		pVtx_Stage[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Stage[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Stage[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx_Stage[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//視錐台の拡大率(?)の初期設定
		pVtx_Stage[0].rhw = 1.0f;
		pVtx_Stage[1].rhw = 1.0f;
		pVtx_Stage[2].rhw = 1.0f;
		pVtx_Stage[3].rhw = 1.0f;

		//頂点カラーの初期設定
		pVtx_Stage[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Stage[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Stage[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx_Stage[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
		pVtx_Stage[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Stage[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Stage[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Stage[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx_Stage += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Stage->Unlock();

	//ステージ構造体の情報の初期化群
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		g_aStage[nCnt].nStyle = STAGE_OBJECT_STYLE_NONE;
		g_aStage[nCnt].bUse = false;
		g_aStage[nCnt].pos = D3DXVECTOR3(0.0f, -1000.0f, 0.0f);
		g_aStage[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aStage[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
		{
			g_aStage[nCnt].fRadius[nCnt2] = 0.0f;
			g_aStage[nCnt].fLength[nCnt2] = 0.0f;
			g_aStage[nCnt].fAngle[nCnt2] = 0.0f;
		}
	}

	//オブジェクト情報格納用初期化
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_STAGE; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_STAGE)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aInfo_Satge_Object[nCnt1][nCnt2] = {};
	}

	//位置情報格納用初期化
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_STAGE; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_STAGE)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aPosInfo_Satge_Object[nCnt1][nCnt2] = {};
	}

	/*要修正*/
	////ステージ構造体用の情報を取得
	//ReadInfo_Stage();

	////ステージ構造体用の位置を取得
	//ReadPosInfo_Stage();

	//読み取った情報をステージ構造体内に代入(旧)
	ReadInfo_Stage_Old();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Stage(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < AMOUNT_TEX_STAGE; nCnt++)
	{
		if (g_pTexture_Stage[nCnt] != NULL)
		{
			g_pTexture_Stage[nCnt]->Release();
			g_pTexture_Stage[nCnt] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Stage != NULL)
	{
		g_pVtxBuff_Stage->Release();
		g_pVtxBuff_Stage = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Stage(void)
{
	//ステージオブジェクトを展開
	Update_Pos_Stage();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Stage(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Stage, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		//テクスチャの設定
		switch (g_aStage[nCnt].nStyle)
		{
		case STAGE_OBJECT_STYLE_BLOCK:
			pDevice->SetTexture(0, g_pTexture_Stage[0]);
			break;
		case STAGE_OBJECT_STYLE_LEFT:
			pDevice->SetTexture(0, g_pTexture_Stage[1]);
			break;
		case STAGE_OBJECT_STYLE_RIGHT:
			pDevice->SetTexture(0, g_pTexture_Stage[2]);
			break;
		case STAGE_OBJECT_STYLE_LEFT_J:
			pDevice->SetTexture(0, g_pTexture_Stage[1]);
			break;
		case STAGE_OBJECT_STYLE_RIGHT_J:
			pDevice->SetTexture(0, g_pTexture_Stage[2]);
			break;
		}

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

//************************************************
//ステージ構造体の情報を設定する関数(旧)
//************************************************
void ReadInfo_Stage_Old(void)
{
	//データを分別する用
	int nLine = 0, nRow = 0, nMaxLine = 0;

	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(DATA_STAGE_OBJECT_OLD, "r");

	//ファイルのヘッダー文字を切り捨て、データが何列あるのかカウント
	while (fgetc(pFile) != '\n');

	//ファイルが開けた
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_Satge_Object[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= 17)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//読み取ったデータを代入
	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		g_aStage[nCnt].nStyle = (int)g_aFileData_Satge_Object[0][nCnt];
		g_aStage[nCnt].pos.x = (float)g_aFileData_Satge_Object[1][nCnt];
		g_aStage[nCnt].pos.y = (float)g_aFileData_Satge_Object[2][nCnt];
		g_aStage[nCnt].move.x = (float)g_aFileData_Satge_Object[3][nCnt];
		g_aStage[nCnt].move.y = (float)g_aFileData_Satge_Object[4][nCnt];
		g_aStage[nCnt].move.z = (float)g_aFileData_Satge_Object[5][nCnt];
		g_aStage[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, (float)g_aFileData_Satge_Object[6][nCnt]);
		g_aStage[nCnt].col = D3DXCOLOR((float)g_aFileData_Satge_Object[7][nCnt],
			(float)g_aFileData_Satge_Object[8][nCnt],
			(float)g_aFileData_Satge_Object[9][nCnt],
			(float)g_aFileData_Satge_Object[10][nCnt]);
		/*要修正ゾーン*/
		g_aStage[nCnt].fRadius[0] = (float)g_aFileData_Satge_Object[11][nCnt];	//横半幅
		g_aStage[nCnt].fRadius[1] = (float)g_aFileData_Satge_Object[12][nCnt];	//縦半幅
		g_aStage[nCnt].fLength[0] = (float)g_aFileData_Satge_Object[13][nCnt];
		g_aStage[nCnt].fLength[1] = (float)g_aFileData_Satge_Object[14][nCnt];
		g_aStage[nCnt].fAngle[0] = (float)g_aFileData_Satge_Object[15][nCnt];
		g_aStage[nCnt].fAngle[1] = (float)g_aFileData_Satge_Object[16][nCnt];
	}
}

//************************************************
//ステージ構造体の情報を読み取る関数
//************************************************
void ReadInfo_Stage(void)
{
	//データを分別する用
	int nLine = 0, nRow = STAGE_OBJECT_STYLE_BLOCK;

	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(DATA_STAGE_OBJECT, "r");

	//ファイルのヘッダー文字を切り捨て
	while (fgetc(pFile) != '\n');

	//ファイルが開けた
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aInfo_Satge_Object[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= 14)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}
}

//************************************************
//ステージ構造体の位置を読み取る関数
//************************************************
void ReadPosInfo_Stage(void)
{
	//データを分別する用
	int nCnt = 0, nLine = 0, nRow = 0;

	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(POS_STAGE_OBJECT, "r");

	//ファイルが開けた
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aPosInfo_Satge_Object[nLine][nRow]) != EOF)
		{
			//種類と位置情報のみ先行して代入
			g_aStage[nCnt].nStyle = (int)g_aPosInfo_Satge_Object[nLine][nRow];

			if (g_aStage[nCnt].nStyle != STAGE_OBJECT_STYLE_NONE)
			{
				g_aStage[nCnt].pos.x = (nLine * 70.0f) + 1000.0f;
				g_aStage[nCnt].pos.y = (nRow * 70.0f) + 105.0f;
			}
			else
			{
				g_aStage[nCnt].pos.x = 0.0f;
				g_aStage[nCnt].pos.y = 0.0f;
			}

			nLine++;

			if (nLine >= 26)
			{
				nLine = 0;
				nRow++;
			}

			nCnt++;
		}

		fclose(pFile);
	}
}

//************************************************
//ステージ構造体の情報を設定する関数
//************************************************
void SetInfo_Stage(void)
{
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		switch (g_aStage[nCnt].nStyle)
		{
		case STAGE_OBJECT_STYLE_BLOCK:
			g_aStage[nCnt].move.x = (float)g_aInfo_Satge_Object[0][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].move.y = (float)g_aInfo_Satge_Object[1][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].move.z = (float)g_aInfo_Satge_Object[2][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, (float)g_aInfo_Satge_Object[3][STAGE_OBJECT_STYLE_BLOCK]);
			g_aStage[nCnt].col = D3DXCOLOR((float)g_aInfo_Satge_Object[4][STAGE_OBJECT_STYLE_BLOCK],
				(float)g_aInfo_Satge_Object[5][STAGE_OBJECT_STYLE_BLOCK],
				(float)g_aInfo_Satge_Object[6][STAGE_OBJECT_STYLE_BLOCK],
				(float)g_aInfo_Satge_Object[7][STAGE_OBJECT_STYLE_BLOCK]);
			/*要修正ゾーン*/
			g_aStage[nCnt].fRadius[0] = (float)g_aInfo_Satge_Object[8][STAGE_OBJECT_STYLE_BLOCK];	//横半幅
			g_aStage[nCnt].fRadius[1] = (float)g_aInfo_Satge_Object[9][STAGE_OBJECT_STYLE_BLOCK];	//縦半幅
			g_aStage[nCnt].fLength[0] = (float)g_aInfo_Satge_Object[10][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].fLength[1] = (float)g_aInfo_Satge_Object[11][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].fAngle[0] = (float)g_aInfo_Satge_Object[12][STAGE_OBJECT_STYLE_BLOCK];
			g_aStage[nCnt].fAngle[1] = (float)g_aInfo_Satge_Object[13][STAGE_OBJECT_STYLE_BLOCK];
			break;
		}
	}
}

//************************************************
//ステージオブジェクトのポリゴンを展開する関数
//************************************************
void Update_Pos_Stage(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Stage;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Stage->Lock(0, 0, (void**)&pVtx_Stage, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		ConvertInfo_Screen(&g_aStage[nCnt].pos);

		pVtx_Stage[0].pos.x = g_aStage[nCnt].pos.x + sinf(g_aStage[nCnt].rot.z - (D3DX_PI - g_aStage[nCnt].fAngle[0])) * g_aStage[nCnt].fLength[0];
		pVtx_Stage[0].pos.y = g_aStage[nCnt].pos.y + cosf(g_aStage[nCnt].rot.z - (D3DX_PI - g_aStage[nCnt].fAngle[0])) * g_aStage[nCnt].fLength[0] - 5.0f;
		pVtx_Stage[1].pos.x = g_aStage[nCnt].pos.x + sinf(g_aStage[nCnt].rot.z + (D3DX_PI - g_aStage[nCnt].fAngle[0])) * g_aStage[nCnt].fLength[0];
		pVtx_Stage[1].pos.y = g_aStage[nCnt].pos.y + cosf(g_aStage[nCnt].rot.z + (D3DX_PI - g_aStage[nCnt].fAngle[0])) * g_aStage[nCnt].fLength[0] - 5.0f;
		pVtx_Stage[2].pos.x = g_aStage[nCnt].pos.x + sinf(g_aStage[nCnt].rot.z - g_aStage[nCnt].fAngle[1]) * g_aStage[nCnt].fLength[1];
		pVtx_Stage[2].pos.y = g_aStage[nCnt].pos.y + cosf(g_aStage[nCnt].rot.z - g_aStage[nCnt].fAngle[1]) * g_aStage[nCnt].fLength[1];
		pVtx_Stage[3].pos.x = g_aStage[nCnt].pos.x + sinf(g_aStage[nCnt].rot.z + g_aStage[nCnt].fAngle[1]) * g_aStage[nCnt].fLength[1];
		pVtx_Stage[3].pos.y = g_aStage[nCnt].pos.y + cosf(g_aStage[nCnt].rot.z + g_aStage[nCnt].fAngle[1]) * g_aStage[nCnt].fLength[1];

		pVtx_Stage += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Stage->Unlock();
}

//************************************************
//当たり判定関数
//************************************************
bool HitDetection_Stage(int nEnemy,int nType, D3DXVECTOR3* pos, D3DXVECTOR3* oldpos, D3DXVECTOR3* move, float fRadius[2])
{
	ENEMY* pEnemy = GetInfo_Enemy();
	PLAYER* pPlayer = GetInfo_Player();

	//着地判定を下げる
	pPlayer->bLanding = false;

	//これ何？
	bool b = false;

	/*当たり判定は、裏の座標で行う*/
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_STAGE; nCnt++)
	{
		//そのオブジェクトの持つ横幅範囲で
		if (pos->x - fRadius[0] < g_aStage[nCnt].pos.x + g_aStage[nCnt].fRadius[0] &&
			pos->x + fRadius[0] > g_aStage[nCnt].pos.x - g_aStage[nCnt].fRadius[0])
		{
			//↑へ、条件下
			if (oldpos->y > g_aStage[nCnt].pos.y &&	//過去の座標がこのオブジェクトより低所である
				move->y < 0.0f &&	//上昇中
				pos->y - (fRadius[1] * 2.0f) < g_aStage[nCnt].pos.y + g_aStage[nCnt].fRadius[1])	//現在の座標がこのオブジェクトより高所である
			{
				//位置をオブジェクトの下端に戻す
				pos->y = (fRadius[1] * 2.0f) + g_aStage[nCnt].pos.y + g_aStage[nCnt].fRadius[1];
				//プレイヤーのときのみ特別な処理を施す
				if (nType == HIT_TYPE_PLAYER)
				{
					pPlayer->BGpos.y = (fRadius[1] * 2.0f) + g_aStage[nCnt].pos.y + g_aStage[nCnt].fRadius[1];
				}

				//縦方向の移動量を無くす(バグ防止)
				move->y = 0.0f;
			}

			//↓へ、条件下
			if (oldpos->y < g_aStage[nCnt].pos.y &&	//過去の座標がこのオブジェクトより高所である
				move->y > 0.0f &&	//下降中
				pos->y > g_aStage[nCnt].pos.y - g_aStage[nCnt].fRadius[1])	//現在の座標がこのオブジェクトより低所であ
			{
				//プレイヤーのときのみ特別な処理を施す
				if (nType == HIT_TYPE_PLAYER)
				{
					//被弾時はそちらを最優先
					if (pPlayer->nState != PLAYER_STATE_HURT1 &&
						pPlayer->nState != PLAYER_STATE_HURT2)
					{
						//ジャンプ後なら着地状態に
						if (pPlayer->nState == PLAYER_STATE_JUMP)
						{
							pPlayer->nState = PLAYER_STATE_LAND;
							pPlayer->nCntTex = 0;
							pPlayer->nCntPattern = 0;
							pPlayer->fTexSpan[0] = 0;
							pPlayer->fTexSpan[1] = SPAN_CHANGE_TEX_LAND_PLAYER;
						}
						//ものによっては優先させるが、基本その他は待機状態に
						else if (pPlayer->nState != PLAYER_STATE_IDLE &&
							pPlayer->nState != PLAYER_STATE_LAND &&
							pPlayer->nState != PLAYER_STATE_RUN &&
							pPlayer->nState != PLAYER_STATE_LIGHT1 &&
							pPlayer->nState != PLAYER_STATE_LIGHT2 &&
							pPlayer->nState != PLAYER_STATE_LIGHT3 &&
							pPlayer->nState != PLAYER_STATE_HEAVY1 &&
							pPlayer->nState != PLAYER_STATE_HEAVY2 &&
							pPlayer->nState != PLAYER_STATE_HEAVY3)
						{
							pPlayer->nState = PLAYER_STATE_IDLE;
							pPlayer->nCntTex = 0;
							pPlayer->nCntPattern = 0;
							pPlayer->fTexSpan[0] = 0;
							pPlayer->fTexSpan[1] = SPAN_CHANGE_TEX_IDLE_PLAYER;
						}
					}

					//ジャンプ回数復活
					pPlayer->nJumpTimes = AMOUNT_ABLE_JUMPS;

					//最後に着地していた位置を記録
					pPlayer->lastland.x = g_aStage[nCnt].pos.x;
					pPlayer->lastland.y = g_aStage[nCnt].pos.y - g_aStage[nCnt].fRadius[1];
				}

				//位置をオブジェクトの上端に戻す
				pos->y = g_aStage[nCnt].pos.y - g_aStage[nCnt].fRadius[1];
				//プレイヤーのときのみ特別な処理を施す
				if (nType == HIT_TYPE_PLAYER)
				{
					pPlayer->BGpos.y = g_aStage[nCnt].pos.y - g_aStage[nCnt].fRadius[1];
				}

				//縦方向の移動量を無くす(バグ防止)
				move->y = 0.0f;

				//更に、このブロックが絶J崖だった場合、地面を歩くタイプの敵を必ずジャンプさせる
				if (nType == HIT_TYPE_ENEMY)
				{
					if (g_aStage[nCnt].nStyle == STAGE_OBJECT_STYLE_LEFT_J ||
						g_aStage[nCnt].nStyle == STAGE_OBJECT_STYLE_RIGHT_J)
					{
						switch (pEnemy[nEnemy].nStyle)
						{
						case ENEMY_01:
							pEnemy[nEnemy].move.y = -20.0f;
							break;
						case ENEMY_02:
							pEnemy[nEnemy].move.y = -18.0f;
							break;
						case ENEMY_03:
							pEnemy[nEnemy].move.y = -14.0f;
							break;
						case ENEMY_04:
							pEnemy[nEnemy].move.y = -20.0f;
							break;
						}
					}
				}
			}
		}

		//そのオブジェクトの持つ縦幅範囲内で
		if (pos->y - (fRadius[1] * 2.0f) < g_aStage[nCnt].pos.y + g_aStage[nCnt].fRadius[1] &&
			pos->y > g_aStage[nCnt].pos.y - g_aStage[nCnt].fRadius[1])
		{
			//←へ、条件下
			if (oldpos->x > g_aStage[nCnt].pos.x &&	//過去の座標がこのオブジェクトより右方である
				move->x < 0.0f &&	//左へ移動中
				pos->x - fRadius[0] < g_aStage[nCnt].pos.x + g_aStage[nCnt].fRadius[0])	//現在の座標がこのオブジェクトより左方である
			{
				//位置をオブジェクトの右端に戻す
				pos->x = g_aStage[nCnt].pos.x + g_aStage[nCnt].fRadius[0] + fRadius[0];

				//横方向の移動量を無くす(バグ防止)
				move->x = 0.0f;
			}

			//→へ、条件下
			if (oldpos->x < g_aStage[nCnt].pos.x &&	//過去の座標がこのオブジェクトより左方である
				move->x > 0.0f &&	//右へ移動中
				pos->x + fRadius[0] > g_aStage[nCnt].pos.x - g_aStage[nCnt].fRadius[0])	//現在の座標がこのオブジェクトより右方である
			{
				//位置をオブジェクトの左端に戻す
				pos->x = g_aStage[nCnt].pos.x - g_aStage[nCnt].fRadius[0] - fRadius[0];

				//横方向の移動量を無くす(バグ防止)
				move->x = 0.0f;
			}
		}
	}

	return b;
}

//************************************************
//ステージ構造体のアドレスを渡す
//************************************************
STAGE* GetInfo_Stage(void)
{
	return &g_aStage[0];
}