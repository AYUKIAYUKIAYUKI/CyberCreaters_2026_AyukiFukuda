//************************************************
//
//敵(もや)処理[enemy.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "sound.h"
#include "block.h"
#include "effect_spawn.h"
#include "enemy.h"
#include "item.h"
#include "particle.h"
#include "player.h"
#include "score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Enemy = NULL;	//テクスチャのポインタを敵数分
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Enemy = NULL;	//頂点バッファのポインタ
ENEMY g_aEnemy[AMOUNT_POLYGON_ENEMY];	//敵の各情報格納
double g_aFileData[AMOUNT_POLYGON_ENEMY][AMOUNT_POLYGON_ENEMY] = {};	//ファイルからデータを格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Enemy(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_CLOUD_ENEMY,
		&g_pTexture_Enemy);

	//敵各情報の初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		g_aEnemy[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//敵の位置情報を初期化
		g_aEnemy[nCnt].fHalfSpanX = 0.0f;						//敵の半幅Xを初期化
		g_aEnemy[nCnt].fHalfSpanY = 0.0f;						//敵の半幅Yを初期化
		g_aEnemy[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の移動情報を初期化
		g_aEnemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//敵の向き情報を初期化
		g_aEnemy[nCnt].nColA = 0;								//透明度調整
		g_aEnemy[nCnt].state = ENEMYSTATE_NORMAL;				//初期から通常状態
		g_aEnemy[nCnt].nCntState = 0;							//カウント数を初期化
		g_aEnemy[nCnt].nLife = 0;								//ライフを初期化
		g_aEnemy[nCnt].bUse = false;							//使用判定を無くす
		g_aEnemy[nCnt].nCntSpawn = 0;							//いつ出現するか
		g_aEnemy[nCnt].bUseEffect = false;						//エフェクト使用判定を無くす
		g_aEnemy[nCnt].bFinishEffect = false;					//エフェクト終了判定
		g_aEnemy[nCnt].fLength = 0.0f;							//対角線の長さを初期化
		g_aEnemy[nCnt].fAngle = 0.0f;							//対角線の角度を初期化
	}

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

	//頂点座標の設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
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
	g_pVtxBuff_Enemy->Unlock();

	//ファイル情報格納用を初期化
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_ENEMY; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_ENEMY)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData[nCnt1][nCnt2] = {};
	}

	//敵情報を設定する
	Setinfo_Enemy();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Enemy(void)
{
	//テクスチャの破棄
	if (g_pTexture_Enemy != NULL)
	{
		g_pTexture_Enemy->Release();
		g_pTexture_Enemy = NULL;
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
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy;

	//プレイヤー情報へのポインタ
	PLAYER* pPlayer;

	//敵情報の取得
	pPlayer = Getinfo_Player();	//プレイヤー情報系の先頭アドレスが代入される

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//使用されている判定だった時
		if (g_aEnemy[nCnt].bUse == true)
		{
			//時間経過で登場
			if (g_aEnemy[nCnt].nCntSpawn > 0)
			{
				g_aEnemy[nCnt].nCntSpawn--;
			}
			else
			{
				//エフェクトが一度のみ出現する
				if (!g_aEnemy[nCnt].bUseEffect)
				{
					g_aEnemy[nCnt].bUseEffect = true;

					SetPos_Vtx_Effect_Spawn(nCnt, g_aEnemy[nCnt].pos, g_aEnemy[nCnt].move);
				}
				else
				{
					//状態に合わせて処理分岐
					switch (g_aEnemy[nCnt].state)
					{
						//通常時
					case ENEMYSTATE_NORMAL:

						/*何もしない*/

						break;

						//被弾時
					case ENEMYSTATE_DAMAGE:

						//状態継続時間を減らす
						g_aEnemy[nCnt].nCntState--;

						//状態が終わる時
						if (g_aEnemy[nCnt].nCntState <= 0)
						{
							//赤くなっているのを戻す
							pVtx_Enemy[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx_Enemy[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx_Enemy[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx_Enemy[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

							//通常処理に変更
							g_aEnemy[nCnt].state = ENEMYSTATE_NORMAL;
						}

						break;
					}

					//回転
					g_aEnemy[nCnt].rot.z += g_aEnemy[nCnt].move.z;

					//移動
					g_aEnemy[nCnt].pos.x += g_aEnemy[nCnt].move.x;
					g_aEnemy[nCnt].pos.y += g_aEnemy[nCnt].move.y;

					//プレイヤーが無敵時間外でこれ当たった時
					if (pPlayer->pos.x <= g_aEnemy[nCnt].pos.x + g_aEnemy[nCnt].fHalfSpanX + HALFSPAN_X_PLAYER - 40.0f &&
						pPlayer->pos.x >= g_aEnemy[nCnt].pos.x - g_aEnemy[nCnt].fHalfSpanX - HALFSPAN_X_PLAYER + 20.0f &&
						pPlayer->pos.y >= g_aEnemy[nCnt].pos.y - g_aEnemy[nCnt].fHalfSpanY - HALFSPAN_Y_PLAYER + 20.0f &&
						pPlayer->pos.y <= g_aEnemy[nCnt].pos.y + g_aEnemy[nCnt].fHalfSpanY + HALFSPAN_Y_PLAYER - 40.0f &&
						pPlayer->state == PLAYERSTATE_NORMAL)
					{
						//ヒット処理
						Hit_Player(1);
					}

					//あまりにも遠くへ行ってしまったら
					if (g_aEnemy[nCnt].pos.x <= -300.0f ||
						g_aEnemy[nCnt].pos.x >= 2300.0f)
					{
						//消滅処理
						Disapper_Enemy(nCnt);
					}

					//移動、回転を反映
					pVtx_Enemy[0].pos.x = g_aEnemy[nCnt].pos.x + sinf(g_aEnemy[nCnt].rot.z - (D3DX_PI - g_aEnemy[nCnt].fAngle)) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[0].pos.y = g_aEnemy[nCnt].pos.y + cosf(g_aEnemy[nCnt].rot.z - (D3DX_PI - g_aEnemy[nCnt].fAngle)) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[1].pos.x = g_aEnemy[nCnt].pos.x + sinf(g_aEnemy[nCnt].rot.z + (D3DX_PI - g_aEnemy[nCnt].fAngle)) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[1].pos.y = g_aEnemy[nCnt].pos.y + cosf(g_aEnemy[nCnt].rot.z + (D3DX_PI - g_aEnemy[nCnt].fAngle)) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[2].pos.x = g_aEnemy[nCnt].pos.x + sinf(g_aEnemy[nCnt].rot.z - g_aEnemy[nCnt].fAngle) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[2].pos.y = g_aEnemy[nCnt].pos.y + cosf(g_aEnemy[nCnt].rot.z - g_aEnemy[nCnt].fAngle) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[3].pos.x = g_aEnemy[nCnt].pos.x + sinf(g_aEnemy[nCnt].rot.z + g_aEnemy[nCnt].fAngle) * g_aEnemy[nCnt].fLength;
					pVtx_Enemy[3].pos.y = g_aEnemy[nCnt].pos.y + cosf(g_aEnemy[nCnt].rot.z + g_aEnemy[nCnt].fAngle) * g_aEnemy[nCnt].fLength;
				}
			}
		}

		pVtx_Enemy += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy->Unlock();
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

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY; nCnt++)
	{
		//敵が使用されている場合
		if (g_aEnemy[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexture_Enemy);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}
}

//************************************************
//敵情報設定処理関数
//************************************************
void Setinfo_Enemy(void)
{
	//データを分別する用
	int nLine = 0, nRow = 0;

	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(FILE_SET_ENEMY, "r");

	//データの一行目にある説明文字を飛ばす
	while (fgetc(pFile) != '\n');

	//ファイルが開けた
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_ENEMY)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		g_aEnemy[nCnt].pos.x = (float)g_aFileData[0][nCnt];		//X初期座標を取得
		g_aEnemy[nCnt].pos.y = (float)g_aFileData[1][nCnt];		//Y初期座標を取得
		g_aEnemy[nCnt].fHalfSpanX = (float)g_aFileData[2][nCnt];	//半幅X取得
		g_aEnemy[nCnt].fHalfSpanY = (float)g_aFileData[3][nCnt];	//半幅Y取得
		g_aEnemy[nCnt].move.x = (float)g_aFileData[4][nCnt];		//X移動量を取得
		g_aEnemy[nCnt].move.y = (float)g_aFileData[5][nCnt];		//Y移動量を取得
		g_aEnemy[nCnt].move.z = (float)g_aFileData[6][nCnt];		//Z移動量を取得
		g_aEnemy[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きを初期化
		g_aEnemy[nCnt].nColA = 255;							//透明度調整
		g_aEnemy[nCnt].state = ENEMYSTATE_NORMAL;			//通常状態を設定
		g_aEnemy[nCnt].nCntState = 255;						//継続時間を0に
		g_aEnemy[nCnt].nLife = (int)g_aFileData[7][nCnt];		//ライフを取得
		g_aEnemy[nCnt].bUse = true;							//この敵の使用判定を出す
		g_aEnemy[nCnt].nCntSpawn = (int)g_aFileData[8][nCnt];	//出現までに要する時間を取得
		g_aEnemy[nCnt].bUseEffect = false;					//エフェクト使用判定はまだ無い
		g_aEnemy[nCnt].bFinishEffect = false;				//エフェクト終了開始判定はまだ無い
		g_aEnemy[nCnt].fLength = (float)g_aFileData[9][nCnt];		//対角線取得
		g_aEnemy[nCnt].fAngle = (float)g_aFileData[10][nCnt];		//角度取得

		//ポインタをずらす
		pVtx_Enemy += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy->Unlock();
}

//************************************************
//敵(もや)への命中処理関数
//************************************************
void Hit_Cloud_Enemy(int nCntEnemy, int nDamage)
{
	//効果音を鳴らす
	PlaySound(SOUND_LABEL_SE_DAMAGE);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	//命中に伴いライフを減らす
	g_aEnemy[nCntEnemy].nLife -= nDamage;	//何体目の敵に、どれだけのダメージを与えるのか

	//敵を撃破
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//スコアを100増加
		Add_Score(100);

		//アイテムドロップ
		Setinfo_Item(g_aEnemy[nCntEnemy].pos, 1);

		//パーティクルを出す(適量)
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			Setinfo_Particle(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.5f, 0.0f, 0.5f, 0.5f));
		}

		//ポインタずらし
		pVtx_Enemy += AMOUNT_VTX * nCntEnemy;

		//状態変化しないのでここで脱色
		pVtx_Enemy[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//この敵の本体の使用を解除
		g_aEnemy[nCntEnemy].bUse = false;
	}
	//敵がまだ生きている
	else
	{
		//10点あげますよ
		Add_Score(10);

		//敵がダメージ状態に
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;

		//ダメージ状態継続時間設定
		g_aEnemy[nCntEnemy].nCntState = AMOUNT_CNT_STATE_ENEMY;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy->Unlock();
}

//************************************************
//敵情報の先頭アドレスを渡す関数
//************************************************
ENEMY* Getinfo_Enemy(void)
{
	return &g_aEnemy[0];	//敵情報の先頭アドレスを渡す
}

//************************************************
//使命を終えた敵の消滅処理関数
//************************************************
void Disapper_Enemy(int nCntEnemy)
{
	g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(-1000.0f, -1000.0f, 0.0f);	//敵の位置情報を初期化
	g_aEnemy[nCntEnemy].fHalfSpanX = 0.0f;						//敵の半幅Xを初期化
	g_aEnemy[nCntEnemy].fHalfSpanY = 0.0f;						//敵の半幅Yを初期化
	g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の移動情報を初期化
	g_aEnemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の向き情報を初期化
	g_aEnemy[nCntEnemy].nColA = 0;								//透明度初期化
	g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;				//初期から通常状態
	g_aEnemy[nCntEnemy].nCntState = 0;							//カウント数を初期化
	g_aEnemy[nCntEnemy].nLife = 0;								//ライフを初期化
	g_aEnemy[nCntEnemy].bUse = false;							//使用判定を無くす
	g_aEnemy[nCntEnemy].nCntSpawn = 0;							//いつ出現するか
	g_aEnemy[nCntEnemy].bUseEffect = false;						//エフェクト使用判定を無くす
	g_aEnemy[nCntEnemy].bFinishEffect = false;					//エフェクト終了判定を無くす
	g_aEnemy[nCntEnemy].fLength = 0.0f;							//対角線の長さを初期化
	g_aEnemy[nCntEnemy].fAngle = 0.0f;							//対角線の角度を初期化
}