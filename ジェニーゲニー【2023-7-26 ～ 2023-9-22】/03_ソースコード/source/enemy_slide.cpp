//************************************************
//
//敵(移動)処理[enemy_slide.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "sound.h"
#include "block.h"
#include "effect_spawn.h"
#include "enemy_slide.h"
#include "item.h"
#include "particle.h"
#include "player.h"
#include "score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Enemy_Slide = NULL;	//テクスチャのポインタを敵数分
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Enemy_Slide = NULL;	//頂点バッファのポインタ
ENEMY_SLIDE g_aEnemy_Slide[AMOUNT_POLYGON_ENEMY_SLIDE];	//敵の各情報格納
double g_aFileData_Enemy_Slide[AMOUNT_POLYGON_ENEMY_SLIDE][AMOUNT_POLYGON_ENEMY_SLIDE] = {};	//ファイルからデータを格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Enemy_Slide(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_SLIDE,
		&g_pTexture_Enemy_Slide);

	//敵各情報の初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_SLIDE; nCnt++)
	{
		g_aEnemy_Slide[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の位置情報を初期化
		g_aEnemy_Slide[nCnt].fHalfSpanX = 0.0f;						//敵の半幅Xを初期化
		g_aEnemy_Slide[nCnt].fHalfSpanY = 0.0f;						//敵の半幅Yを初期化
		g_aEnemy_Slide[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の移動情報を初期化
		g_aEnemy_Slide[nCnt].nRute = 0;								//ルート分岐初期化
		g_aEnemy_Slide[nCnt].fHoldmoveX = 0.0f;						//移動量保持を初期化
		g_aEnemy_Slide[nCnt].fHoldmoveY = 0.0f;						//移動量保持を初期化
		g_aEnemy_Slide[nCnt].fTurn1 = 0.0f;							//移動をやめるタイミング1
		g_aEnemy_Slide[nCnt].fTurn2 = 0.0f;							//移動をやめるタイミング2
		g_aEnemy_Slide[nCnt].fDecreaseSPD = 0.0f;					//移動量の減衰速度
		//g_aEnemy_Slide[nCnt].bCharge = false;						//溜め期間
		g_aEnemy_Slide[nCnt].bTurning = false;						//方向転換
		g_aEnemy_Slide[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の向き情報を初期化
		g_aEnemy_Slide[nCnt].nColA = 0;								//透明度調整
		g_aEnemy_Slide[nCnt].state = ENEMYSTATE_SLIDE_NORMAL;		//初期から通常状態
		g_aEnemy_Slide[nCnt].nCntState = 0;							//カウント数を初期化
		g_aEnemy_Slide[nCnt].nLife = 0;								//ライフを初期化
		g_aEnemy_Slide[nCnt].bUse = false;							//使用判定を無くす
		g_aEnemy_Slide[nCnt].nCntSpawn = 0;							//いつ出現するか
		g_aEnemy_Slide[nCnt].bUseEffect = false;					//エフェクト使用判定を無くす
		g_aEnemy_Slide[nCnt].bFinishEffect = false;					//エフェクト終了判定
		g_aEnemy_Slide[nCnt].fLength = 0.0f;						//対角線の長さを初期化
		g_aEnemy_Slide[nCnt].fAngle = 0.0f;							//対角線の角度を初期化
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ENEMY_SLIDE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Enemy_Slide,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy_Slide->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	//頂点座標の設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_SLIDE; nCnt++)
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
		pVtx_Enemy[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の初期設定
		pVtx_Enemy[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx_Enemy[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx_Enemy[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx_Enemy[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//ポインタをずらす
		pVtx_Enemy += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy_Slide->Unlock();

	//ファイル情報格納用を初期化
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_ENEMY_SLIDE; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_ENEMY_SLIDE)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData_Enemy_Slide[nCnt1][nCnt2] = {};
	}

	//敵情報を設定する
	Setinfo_Enemy_Slide();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Enemy_Slide(void)
{
	//テクスチャの破棄
	if (g_pTexture_Enemy_Slide != NULL)
	{
		g_pTexture_Enemy_Slide->Release();
		g_pTexture_Enemy_Slide = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Enemy_Slide != NULL)
	{
		g_pVtxBuff_Enemy_Slide->Release();
		g_pVtxBuff_Enemy_Slide = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Enemy_Slide(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy_Slide;

	//プレイヤー情報へのポインタ
	PLAYER* pPlayer;

	//敵情報の取得
	pPlayer = Getinfo_Player();	//プレイヤー情報系の先頭アドレスが代入される

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy_Slide->Lock(0, 0, (void**)&pVtx_Enemy_Slide, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_SLIDE; nCnt++)
	{
		//使用されている判定だった時
		if (g_aEnemy_Slide[nCnt].bUse == true)
		{
			//時間経過で登場
			if (g_aEnemy_Slide[nCnt].nCntSpawn > 0)
			{
				g_aEnemy_Slide[nCnt].nCntSpawn--;
			}
			else
			{
				//状態に合わせて処理分岐
				switch (g_aEnemy_Slide[nCnt].state)
				{
					//通常時
				case ENEMYSTATE_SLIDE_NORMAL:

					/*何もしない*/

					break;

					//被弾時
				case ENEMYSTATE_SLIDE_DAMAGE:

					//状態継続時間を減らす
					g_aEnemy_Slide[nCnt].nCntState--;

					//状態が終わる時
					if (g_aEnemy_Slide[nCnt].nCntState <= 0)
					{
						//赤くなっているのを戻す
						pVtx_Enemy_Slide[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Enemy_Slide[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Enemy_Slide[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Enemy_Slide[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//通常処理に変更
						g_aEnemy_Slide[nCnt].state = ENEMYSTATE_SLIDE_NORMAL;
					}

					break;
				}

				//回転
				g_aEnemy_Slide[nCnt].rot.z += g_aEnemy_Slide[nCnt].move.z;

				//移動
				g_aEnemy_Slide[nCnt].pos.x += g_aEnemy_Slide[nCnt].move.x;
				g_aEnemy_Slide[nCnt].pos.y += g_aEnemy_Slide[nCnt].move.y;

				//ルートに合せて移動変化
				switch (g_aEnemy_Slide[nCnt].nRute)
				{
					//上から下
				case 0:

					//規定値を越えている間だけ移動量を増減
					if (g_aEnemy_Slide[nCnt].pos.y < g_aEnemy_Slide[nCnt].fTurn1)
					{
						g_aEnemy_Slide[nCnt].move.y += g_aEnemy_Slide[nCnt].fDecreaseSPD;
					}
					
					if (g_aEnemy_Slide[nCnt].pos.y > g_aEnemy_Slide[nCnt].fTurn2)
					{
						g_aEnemy_Slide[nCnt].move.y -= g_aEnemy_Slide[nCnt].fDecreaseSPD;
					}

					break;

					//下から上
				case 1:

					//規定値を越えている間だけ移動量を増減
					if (g_aEnemy_Slide[nCnt].pos.y > g_aEnemy_Slide[nCnt].fTurn1)
					{
						g_aEnemy_Slide[nCnt].move.y -= g_aEnemy_Slide[nCnt].fDecreaseSPD;
					}

					if (g_aEnemy_Slide[nCnt].pos.y < g_aEnemy_Slide[nCnt].fTurn2)
					{
						g_aEnemy_Slide[nCnt].move.y += g_aEnemy_Slide[nCnt].fDecreaseSPD;
					}

					break;
				}

				//プレイヤーが無敵時間外でこれ当たった時
				if (pPlayer->pos.x <= g_aEnemy_Slide[nCnt].pos.x + g_aEnemy_Slide[nCnt].fHalfSpanX + HALFSPAN_X_PLAYER - 40.0f &&
					pPlayer->pos.x >= g_aEnemy_Slide[nCnt].pos.x - g_aEnemy_Slide[nCnt].fHalfSpanX - HALFSPAN_X_PLAYER + 20.0f &&
					pPlayer->pos.y >= g_aEnemy_Slide[nCnt].pos.y - g_aEnemy_Slide[nCnt].fHalfSpanY - HALFSPAN_Y_PLAYER + 20.0f &&
					pPlayer->pos.y <= g_aEnemy_Slide[nCnt].pos.y + g_aEnemy_Slide[nCnt].fHalfSpanY + HALFSPAN_Y_PLAYER - 40.0f &&
					pPlayer->state == PLAYERSTATE_NORMAL)
				{
					//ヒット処理
					Hit_Player(1);
				}

				//移動、回転を反映
				pVtx_Enemy_Slide[0].pos.x = g_aEnemy_Slide[nCnt].pos.x + sinf(g_aEnemy_Slide[nCnt].rot.z - (D3DX_PI - g_aEnemy_Slide[nCnt].fAngle)) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[0].pos.y = g_aEnemy_Slide[nCnt].pos.y + cosf(g_aEnemy_Slide[nCnt].rot.z - (D3DX_PI - g_aEnemy_Slide[nCnt].fAngle)) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[1].pos.x = g_aEnemy_Slide[nCnt].pos.x + sinf(g_aEnemy_Slide[nCnt].rot.z + (D3DX_PI - g_aEnemy_Slide[nCnt].fAngle)) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[1].pos.y = g_aEnemy_Slide[nCnt].pos.y + cosf(g_aEnemy_Slide[nCnt].rot.z + (D3DX_PI - g_aEnemy_Slide[nCnt].fAngle)) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[2].pos.x = g_aEnemy_Slide[nCnt].pos.x + sinf(g_aEnemy_Slide[nCnt].rot.z - g_aEnemy_Slide[nCnt].fAngle) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[2].pos.y = g_aEnemy_Slide[nCnt].pos.y + cosf(g_aEnemy_Slide[nCnt].rot.z - g_aEnemy_Slide[nCnt].fAngle) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[3].pos.x = g_aEnemy_Slide[nCnt].pos.x + sinf(g_aEnemy_Slide[nCnt].rot.z + g_aEnemy_Slide[nCnt].fAngle) * g_aEnemy_Slide[nCnt].fLength;
				pVtx_Enemy_Slide[3].pos.y = g_aEnemy_Slide[nCnt].pos.y + cosf(g_aEnemy_Slide[nCnt].rot.z + g_aEnemy_Slide[nCnt].fAngle) * g_aEnemy_Slide[nCnt].fLength;
			}
		}

		pVtx_Enemy_Slide += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy_Slide->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Enemy_Slide(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Enemy_Slide, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_SLIDE; nCnt++)
	{
		//敵が使用されている場合
		if (g_aEnemy_Slide[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexture_Enemy_Slide);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}
}

//************************************************
//敵情報設定処理関数
//************************************************
void Setinfo_Enemy_Slide(void)
{
	//データを分別する用
	int nLine = 0, nRow = 0;

	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(FILE_SET_ENEMY_SLIDE, "r");

	//データの一行目にある説明文字を飛ばす
	while (fgetc(pFile) != '\n');

	//ファイルが開けた
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_Enemy_Slide[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_ENEMY_SLIDE)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy_Slide;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy_Slide->Lock(0, 0, (void**)&pVtx_Enemy_Slide, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		g_aEnemy_Slide[nCnt].pos.x = (float)g_aFileData_Enemy_Slide[0][nCnt];		//X初期座標を取得
		g_aEnemy_Slide[nCnt].pos.y = (float)g_aFileData_Enemy_Slide[1][nCnt];		//Y初期座標を取得
		g_aEnemy_Slide[nCnt].fHalfSpanX = (float)g_aFileData_Enemy_Slide[2][nCnt];	//半幅X取得
		g_aEnemy_Slide[nCnt].fHalfSpanY = (float)g_aFileData_Enemy_Slide[3][nCnt];	//半幅Y取得
		g_aEnemy_Slide[nCnt].move.x = (float)g_aFileData_Enemy_Slide[4][nCnt];		//X移動量を取得
		g_aEnemy_Slide[nCnt].move.y = (float)g_aFileData_Enemy_Slide[5][nCnt];		//Y移動量を取得
		g_aEnemy_Slide[nCnt].move.z = (float)g_aFileData_Enemy_Slide[6][nCnt];		//Z移動量を取得
		g_aEnemy_Slide[nCnt].nRute = (int)g_aFileData_Enemy_Slide[7][nCnt];			//ルート分岐
		g_aEnemy_Slide[nCnt].fHoldmoveX = g_aEnemy_Slide[nCnt].move.x;				//移動量保持を初期化
		g_aEnemy_Slide[nCnt].fHoldmoveY = g_aEnemy_Slide[nCnt].move.y;				//移動量保持を初期化
		g_aEnemy_Slide[nCnt].fTurn1 = (float)g_aFileData_Enemy_Slide[8][nCnt];		//移動をやめるタイミング1
		g_aEnemy_Slide[nCnt].fTurn2 = (float)g_aFileData_Enemy_Slide[9][nCnt];		//移動をやめるタイミング2
		g_aEnemy_Slide[nCnt].fDecreaseSPD = (float)g_aFileData_Enemy_Slide[10][nCnt];//移動量の減衰速度
		g_aEnemy_Slide[nCnt].bTurning = false;						//方向転換
		g_aEnemy_Slide[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きを初期化
		g_aEnemy_Slide[nCnt].nColA = 255;							//透明度調整
		g_aEnemy_Slide[nCnt].state = ENEMYSTATE_SLIDE_NORMAL;		//通常状態を設定
		g_aEnemy_Slide[nCnt].nCntState = 255;						//継続時間を0に
		g_aEnemy_Slide[nCnt].nLife = (int)g_aFileData_Enemy_Slide[11][nCnt];		//ライフを取得
		g_aEnemy_Slide[nCnt].bUse = true;							//この敵の使用判定を出す
		g_aEnemy_Slide[nCnt].nCntSpawn = (int)g_aFileData_Enemy_Slide[12][nCnt];	//出現までに要する時間を取得
		g_aEnemy_Slide[nCnt].bUseEffect = false;					//エフェクト使用判定はまだ無い
		g_aEnemy_Slide[nCnt].bFinishEffect = false;					//エフェクト終了開始判定はまだ無い
		g_aEnemy_Slide[nCnt].fLength = (float)g_aFileData_Enemy_Slide[13][nCnt];		//対角線取得
		g_aEnemy_Slide[nCnt].fAngle = (float)g_aFileData_Enemy_Slide[14][nCnt];			//角度取得

		//ポインタをずらす
		pVtx_Enemy_Slide += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy_Slide->Unlock();
}

//************************************************
//敵(移動)への命中処理関数
//************************************************
void Hit_Slide_Enemy(int nCntEnemy, int nDamage)
{
	//効果音を鳴らす
	PlaySound(SOUND_LABEL_SE_DAMAGE);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy_Slide;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy_Slide->Lock(0, 0, (void**)&pVtx_Enemy_Slide, 0);

	//命中に伴いライフを減らす
	g_aEnemy_Slide[nCntEnemy].nLife -= nDamage;	//何体目の敵に、どれだけのダメージを与えるのか

	//敵を撃破
	if (g_aEnemy_Slide[nCntEnemy].nLife <= 0)
	{
		//スコアを100増加
		Add_Score(100);

		//アイテムドロップ
		Setinfo_Item(g_aEnemy_Slide[nCntEnemy].pos, 1);

		//パーティクルを出す(適量)
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			Setinfo_Particle(g_aEnemy_Slide[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}

		//ポインタずらし
		pVtx_Enemy_Slide += AMOUNT_VTX * nCntEnemy;

		//状態変化しないのでここで脱色
		pVtx_Enemy_Slide[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy_Slide[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy_Slide[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy_Slide[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//この敵の本体の使用を解除
		g_aEnemy_Slide[nCntEnemy].bUse = false;
	}
	//敵がまだ生きている
	else
	{
		//10点あげますよ
		Add_Score(10);

		//敵がダメージ状態に
		g_aEnemy_Slide[nCntEnemy].state = ENEMYSTATE_SLIDE_DAMAGE;

		//ダメージ状態継続時間設定
		g_aEnemy_Slide[nCntEnemy].nCntState = AMOUNT_CNT_STATE_ENEMY_SLIDE;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy_Slide->Unlock();
}

//************************************************
//敵情報の先頭アドレスを渡す関数
//************************************************
ENEMY_SLIDE* Getinfo_Enemy_Slide(void)
{
	return &g_aEnemy_Slide[0];	//敵情報の先頭アドレスを渡す
}

//************************************************
//使命を終えた敵の消滅処理関数
//************************************************
void Disapper_Enemy_Slide(int nCntEnemy)
{
	g_aEnemy_Slide[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の位置情報を初期化
	g_aEnemy_Slide[nCntEnemy].fHalfSpanX = 0.0f;					//敵の半幅Xを初期化
	g_aEnemy_Slide[nCntEnemy].fHalfSpanY = 0.0f;					//敵の半幅Yを初期化
	g_aEnemy_Slide[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の移動情報を初期化
	g_aEnemy_Slide[nCntEnemy].nRute = 0;							//ルート分岐初期化
	g_aEnemy_Slide[nCntEnemy].fHoldmoveX = 0.0f;					//移動量保持を初期化
	g_aEnemy_Slide[nCntEnemy].fHoldmoveY = 0.0f;					//移動量保持を初期化
	g_aEnemy_Slide[nCntEnemy].fTurn1 = 0.0f;						//移動をやめるタイミング1
	g_aEnemy_Slide[nCntEnemy].fTurn2 = 0.0f;						//移動をやめるタイミング2
	g_aEnemy_Slide[nCntEnemy].fDecreaseSPD = 0.0f;					//移動量の減衰速度
	//g_aEnemy_Slide[nCntEnemy].bCharge = false;					//溜め期間
	g_aEnemy_Slide[nCntEnemy].bTurning = false;						//方向転換
	g_aEnemy_Slide[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の向き情報を初期化
	g_aEnemy_Slide[nCntEnemy].nColA = 0;							//透明度初期化
	g_aEnemy_Slide[nCntEnemy].state = ENEMYSTATE_SLIDE_NORMAL;		//初期から通常状態
	g_aEnemy_Slide[nCntEnemy].nCntState = 0;						//カウント数を初期化
	g_aEnemy_Slide[nCntEnemy].nLife = 0;							//ライフを初期化
	g_aEnemy_Slide[nCntEnemy].bUse = false;							//使用判定を無くす
	g_aEnemy_Slide[nCntEnemy].nCntSpawn = 0;						//いつ出現するか
	g_aEnemy_Slide[nCntEnemy].bUseEffect = false;					//エフェクト使用判定を無くす
	g_aEnemy_Slide[nCntEnemy].bFinishEffect = false;				//エフェクト終了判定を無くす
	g_aEnemy_Slide[nCntEnemy].fLength = 0.0f;						//対角線の長さを初期化
	g_aEnemy_Slide[nCntEnemy].fAngle = 0.0f;						//対角線の角度を初期化
}