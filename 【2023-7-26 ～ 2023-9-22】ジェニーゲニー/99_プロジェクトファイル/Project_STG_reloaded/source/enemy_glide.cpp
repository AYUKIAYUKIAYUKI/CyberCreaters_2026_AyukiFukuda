//************************************************
//
//敵(飛翔)処理[enemy_glide.cpp]
//Author：福田歩希
//
//************************************************
#include "main.h"
#include "sound.h"
#include "block.h"
#include "effect_spawn.h"
#include "enemy_glide.h"
#include "item.h"
#include "particle.h"
#include "player.h"
#include "score.h"

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexture_Enemy_Glide = NULL;	//テクスチャのポインタを敵数分
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuff_Enemy_Glide = NULL;	//頂点バッファのポインタ
ENEMY_GLIDE g_aEnemy_Glide[AMOUNT_POLYGON_ENEMY_GLIDE];	//敵の各情報格納
double g_aFileData_Enemy_Glide[AMOUNT_POLYGON_ENEMY_GLIDE][AMOUNT_POLYGON_ENEMY_GLIDE] = {};	//ファイルからデータを格納

//************************************************
//ポリゴン初期化処理関数
//************************************************
void Init_Enemy_Glide(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへの取得
	pDevice = GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_ENEMY_GLIDE,
		&g_pTexture_Enemy_Glide);

	//敵各情報の初期化
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_GLIDE; nCnt++)
	{
		g_aEnemy_Glide[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の位置情報を初期化
		g_aEnemy_Glide[nCnt].fHalfSpanX = 0.0f;						//敵の半幅Xを初期化
		g_aEnemy_Glide[nCnt].fHalfSpanY = 0.0f;						//敵の半幅Yを初期化
		g_aEnemy_Glide[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の移動情報を初期化
		g_aEnemy_Glide[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の向き情報を初期化
		g_aEnemy_Glide[nCnt].nColA = 0;								//透明度調整
		g_aEnemy_Glide[nCnt].state = ENEMYSTATE_GLIDE_NORMAL;		//初期から通常状態
		g_aEnemy_Glide[nCnt].nCntState = 0;							//カウント数を初期化
		g_aEnemy_Glide[nCnt].nLife = 0;								//ライフを初期化
		g_aEnemy_Glide[nCnt].bUse = false;							//使用判定を無くす
		g_aEnemy_Glide[nCnt].nCntSpawn = 0;							//いつ出現するか
		g_aEnemy_Glide[nCnt].nCntChange = 0;						//いつ進路変更するか
		g_aEnemy_Glide[nCnt].bUseEffect = false;					//エフェクト使用判定を無くす
		g_aEnemy_Glide[nCnt].bFinishEffect = false;					//エフェクト終了判定
		g_aEnemy_Glide[nCnt].fDirection = 0.0f;						//方角を初期化
		g_aEnemy_Glide[nCnt].fTurningSPD = 0.0f;					//旋回速度を初期
		g_aEnemy_Glide[nCnt].fSizeCircle = 0.0f;					//円周幅を初期化
		g_aEnemy_Glide[nCnt].fLength = 0.0f;						//対角線の長さを初期化
		g_aEnemy_Glide[nCnt].fAngle = 0.0f;							//対角線の角度を初期化
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_POLYGON_ENEMY_GLIDE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuff_Enemy_Glide,
		NULL);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy_Glide->Lock(0, 0, (void**)&pVtx_Enemy, 0);

	//頂点座標の設定
	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_GLIDE; nCnt++)
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
	g_pVtxBuff_Enemy_Glide->Unlock();

	//ファイル情報格納用を初期化
	for (int nCnt1 = 0, nCnt2 = 0; nCnt2 < AMOUNT_POLYGON_ENEMY_GLIDE; nCnt1++)
	{
		if (nCnt1 >= AMOUNT_POLYGON_ENEMY_GLIDE)
		{
			nCnt1 = 0;
			nCnt2++;
		}

		g_aFileData_Enemy_Glide[nCnt1][nCnt2] = {};
	}

	//敵情報を設定する
	Setinfo_Enemy_Glide();
}

//************************************************
//ポリゴン終了処理関数
//************************************************
void Uninit_Enemy_Glide(void)
{
	//テクスチャの破棄
	if (g_pTexture_Enemy_Glide != NULL)
	{
		g_pTexture_Enemy_Glide->Release();
		g_pTexture_Enemy_Glide = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuff_Enemy_Glide != NULL)
	{
		g_pVtxBuff_Enemy_Glide->Release();
		g_pVtxBuff_Enemy_Glide = NULL;
	}
}

//************************************************
//ポリゴン更新処理関数
//************************************************
void Update_Enemy_Glide(void)
{
	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy_Glide;

	//プレイヤー情報へのポインタ
	PLAYER* pPlayer;

	//敵情報の取得
	pPlayer = Getinfo_Player();	//プレイヤー情報系の先頭アドレスが代入される

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy_Glide->Lock(0, 0, (void**)&pVtx_Enemy_Glide, 0);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_GLIDE; nCnt++)
	{
		//使用されている判定だった時
		if (g_aEnemy_Glide[nCnt].bUse == true)
		{
			//時間経過で登場
			if (g_aEnemy_Glide[nCnt].nCntSpawn > 0)
			{
				g_aEnemy_Glide[nCnt].nCntSpawn--;
			}
			else
			{
				//状態に合わせて処理分岐
				switch (g_aEnemy_Glide[nCnt].state)
				{
					//通常時
				case ENEMYSTATE_GLIDE_NORMAL:

					/*何もしない*/

					break;

					//被弾時
				case ENEMYSTATE_GLIDE_DAMAGE:

					//状態継続時間を減らす
					g_aEnemy_Glide[nCnt].nCntState--;

					//状態が終わる時
					if (g_aEnemy_Glide[nCnt].nCntState <= 0)
					{
						//赤くなっているのを戻す
						pVtx_Enemy_Glide[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Enemy_Glide[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Enemy_Glide[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
						pVtx_Enemy_Glide[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

						//通常処理に変更
						g_aEnemy_Glide[nCnt].state = ENEMYSTATE_GLIDE_NORMAL;
					}

					break;
				}

				//回転
				g_aEnemy_Glide[nCnt].rot.z += g_aEnemy_Glide[nCnt].move.z;

				//移動
				if (g_aEnemy_Glide[nCnt].nCntChange > 0)
				{
					g_aEnemy_Glide[nCnt].nCntChange--;

					g_aEnemy_Glide[nCnt].pos.x += g_aEnemy_Glide[nCnt].move.x;
					g_aEnemy_Glide[nCnt].pos.y += g_aEnemy_Glide[nCnt].move.y;
				}
				else
				{
					//横には流れていきます
					g_aEnemy_Glide[nCnt].pos.x += g_aEnemy_Glide[nCnt].move.x;

					g_aEnemy_Glide[nCnt].fDirection > -D3DX_PI ?
						g_aEnemy_Glide[nCnt].fDirection += g_aEnemy_Glide[nCnt].fTurningSPD :
						g_aEnemy_Glide[nCnt].fDirection = D3DX_PI;

					g_aEnemy_Glide[nCnt].pos.x += sinf(g_aEnemy_Glide[nCnt].fDirection) * g_aEnemy_Glide[nCnt].fSizeCircle;
					g_aEnemy_Glide[nCnt].pos.y += cosf(g_aEnemy_Glide[nCnt].fDirection) * g_aEnemy_Glide[nCnt].fSizeCircle;
				}

				//プレイヤーが無敵時間外でこれ当たった時
				if (pPlayer->pos.x <= g_aEnemy_Glide[nCnt].pos.x + g_aEnemy_Glide[nCnt].fHalfSpanX + HALFSPAN_X_PLAYER - 40.0f &&
					pPlayer->pos.x >= g_aEnemy_Glide[nCnt].pos.x - g_aEnemy_Glide[nCnt].fHalfSpanX - HALFSPAN_X_PLAYER + 20.0f &&
					pPlayer->pos.y >= g_aEnemy_Glide[nCnt].pos.y - g_aEnemy_Glide[nCnt].fHalfSpanY - HALFSPAN_Y_PLAYER + 20.0f &&
					pPlayer->pos.y <= g_aEnemy_Glide[nCnt].pos.y + g_aEnemy_Glide[nCnt].fHalfSpanY + HALFSPAN_Y_PLAYER - 40.0f &&
					pPlayer->state == PLAYERSTATE_NORMAL)
				{
					//ヒット処理
					Hit_Player(1);
				}

				//移動、回転を反映
				pVtx_Enemy_Glide[0].pos.x = g_aEnemy_Glide[nCnt].pos.x + sinf(g_aEnemy_Glide[nCnt].rot.z - (D3DX_PI - g_aEnemy_Glide[nCnt].fAngle)) * g_aEnemy_Glide[nCnt].fLength;
				pVtx_Enemy_Glide[0].pos.y = g_aEnemy_Glide[nCnt].pos.y + cosf(g_aEnemy_Glide[nCnt].rot.z - (D3DX_PI - g_aEnemy_Glide[nCnt].fAngle)) * g_aEnemy_Glide[nCnt].fLength;
				pVtx_Enemy_Glide[1].pos.x = g_aEnemy_Glide[nCnt].pos.x + sinf(g_aEnemy_Glide[nCnt].rot.z + (D3DX_PI - g_aEnemy_Glide[nCnt].fAngle)) * g_aEnemy_Glide[nCnt].fLength;
				pVtx_Enemy_Glide[1].pos.y = g_aEnemy_Glide[nCnt].pos.y + cosf(g_aEnemy_Glide[nCnt].rot.z + (D3DX_PI - g_aEnemy_Glide[nCnt].fAngle)) * g_aEnemy_Glide[nCnt].fLength;
				pVtx_Enemy_Glide[2].pos.x = g_aEnemy_Glide[nCnt].pos.x + sinf(g_aEnemy_Glide[nCnt].rot.z - g_aEnemy_Glide[nCnt].fAngle) * g_aEnemy_Glide[nCnt].fLength;
				pVtx_Enemy_Glide[2].pos.y = g_aEnemy_Glide[nCnt].pos.y + cosf(g_aEnemy_Glide[nCnt].rot.z - g_aEnemy_Glide[nCnt].fAngle) * g_aEnemy_Glide[nCnt].fLength;
				pVtx_Enemy_Glide[3].pos.x = g_aEnemy_Glide[nCnt].pos.x + sinf(g_aEnemy_Glide[nCnt].rot.z + g_aEnemy_Glide[nCnt].fAngle) * g_aEnemy_Glide[nCnt].fLength;
				pVtx_Enemy_Glide[3].pos.y = g_aEnemy_Glide[nCnt].pos.y + cosf(g_aEnemy_Glide[nCnt].rot.z + g_aEnemy_Glide[nCnt].fAngle) * g_aEnemy_Glide[nCnt].fLength;
			}
		}

		pVtx_Enemy_Glide += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy_Glide->Unlock();
}

//************************************************
//ポリゴン描画処理関数
//************************************************
void Draw_Enemy_Glide(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスへのポインタ取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuff_Enemy_Glide, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < AMOUNT_POLYGON_ENEMY_GLIDE; nCnt++)
	{
		//敵が使用されている場合
		if (g_aEnemy_Glide[nCnt].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexture_Enemy_Glide);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
		}
	}
}

//************************************************
//敵情報設定処理関数
//************************************************
void Setinfo_Enemy_Glide(void)
{
	//データを分別する用
	int nLine = 0, nRow = 0;

	//ファイルポインタを宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(FILE_SET_ENEMY_GLIDE, "r");

	//データの一行目にある説明文字を飛ばす
	while (fgetc(pFile) != '\n');

	//ファイルが開けた
	if (pFile != NULL)
	{
		while (fscanf_s(pFile, "%lf,", &g_aFileData_Enemy_Glide[nLine][nRow]) != EOF)
		{
			nLine++;

			if (nLine >= AMOUNT_DATA_ENEMY_GLIDE)
			{
				nLine = 0;
				nRow++;
			}
		}

		fclose(pFile);
	}

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy_Glide;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy_Glide->Lock(0, 0, (void**)&pVtx_Enemy_Glide, 0);

	for (int nCnt = 0; nCnt < nRow; nCnt++)
	{
		g_aEnemy_Glide[nCnt].pos.x = (float)g_aFileData_Enemy_Glide[0][nCnt];		//X初期座標を取得
		g_aEnemy_Glide[nCnt].pos.y = (float)g_aFileData_Enemy_Glide[1][nCnt];		//Y初期座標を取得
		g_aEnemy_Glide[nCnt].fHalfSpanX = (float)g_aFileData_Enemy_Glide[2][nCnt];	//半幅X取得
		g_aEnemy_Glide[nCnt].fHalfSpanY = (float)g_aFileData_Enemy_Glide[3][nCnt];	//半幅Y取得
		g_aEnemy_Glide[nCnt].move.x = (float)g_aFileData_Enemy_Glide[4][nCnt];		//X移動量を取得
		g_aEnemy_Glide[nCnt].move.y = (float)g_aFileData_Enemy_Glide[5][nCnt];		//Y移動量を取得
		g_aEnemy_Glide[nCnt].move.z = (float)g_aFileData_Enemy_Glide[6][nCnt];		//Z移動量を取得
		g_aEnemy_Glide[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向きを初期化
		g_aEnemy_Glide[nCnt].nColA = 255;							//透明度調整
		g_aEnemy_Glide[nCnt].state = ENEMYSTATE_GLIDE_NORMAL;		//通常状態を設定
		g_aEnemy_Glide[nCnt].nCntState = 255;						//継続時間を0に
		g_aEnemy_Glide[nCnt].nLife = (int)g_aFileData_Enemy_Glide[7][nCnt];		//ライフを取得
		g_aEnemy_Glide[nCnt].bUse = true;							//この敵の使用判定を出す
		g_aEnemy_Glide[nCnt].nCntSpawn = (int)g_aFileData_Enemy_Glide[8][nCnt];	//出現までに要する時間を取得
		g_aEnemy_Glide[nCnt].nCntChange = (int)g_aFileData_Enemy_Glide[9][nCnt];//進路変更までに要する時間を取得
		g_aEnemy_Glide[nCnt].bUseEffect = false;					//エフェクト使用判定はまだ無い
		g_aEnemy_Glide[nCnt].bFinishEffect = false;					//エフェクト終了開始判定はまだ無い
		g_aEnemy_Glide[nCnt].fDirection = (float)g_aFileData_Enemy_Glide[10][nCnt];		//方角取得
		g_aEnemy_Glide[nCnt].fTurningSPD = (float)g_aFileData_Enemy_Glide[11][nCnt];	//旋回速度
		g_aEnemy_Glide[nCnt].fSizeCircle = (float)g_aFileData_Enemy_Glide[12][nCnt];	//円周幅
		g_aEnemy_Glide[nCnt].fLength = (float)g_aFileData_Enemy_Glide[13][nCnt];		//対角線取得
		g_aEnemy_Glide[nCnt].fAngle = (float)g_aFileData_Enemy_Glide[14][nCnt];			//角度取得

		//ポインタをずらす
		pVtx_Enemy_Glide += AMOUNT_VTX;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy_Glide->Unlock();
}

//************************************************
//敵(飛翔)への命中処理関数
//************************************************
void Hit_Glide_Enemy(int nCntEnemy, int nDamage)
{
	//効果音を鳴らす
	PlaySound(SOUND_LABEL_SE_DAMAGE);

	//頂点情報へのポインタ
	VERTEX_2D* pVtx_Enemy_Glide;

	//頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuff_Enemy_Glide->Lock(0, 0, (void**)&pVtx_Enemy_Glide, 0);

	//命中に伴いライフを減らす
	g_aEnemy_Glide[nCntEnemy].nLife -= nDamage;	//何体目の敵に、どれだけのダメージを与えるのか

	//敵を撃破
	if (g_aEnemy_Glide[nCntEnemy].nLife <= 0)
	{
		//スコアを100増加
		Add_Score(100);

		//アイテムドロップ
		Setinfo_Item(g_aEnemy_Glide[nCntEnemy].pos, 1);

		//パーティクルを出す(適量)
		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			Setinfo_Particle(g_aEnemy_Glide[nCntEnemy].pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}

		//ポインタずらし
		pVtx_Enemy_Glide += AMOUNT_VTX * nCntEnemy;

		//状態変化しないのでここで脱色
		pVtx_Enemy_Glide[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy_Glide[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy_Glide[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx_Enemy_Glide[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//この敵の本体の使用を解除
		g_aEnemy_Glide[nCntEnemy].bUse = false;
	}
	//敵がまだ生きている
	else
	{
		//10点あげますよ
		Add_Score(10);

		//敵がダメージ状態に
		g_aEnemy_Glide[nCntEnemy].state = ENEMYSTATE_GLIDE_DAMAGE;

		//ダメージ状態継続時間設定
		g_aEnemy_Glide[nCntEnemy].nCntState = AMOUNT_CNT_STATE_ENEMY_GLIDE;
	}

	//頂点バッファをアンロックする
	g_pVtxBuff_Enemy_Glide->Unlock();
}

//************************************************
//敵情報の先頭アドレスを渡す関数
//************************************************
ENEMY_GLIDE* Getinfo_Enemy_Glide(void)
{
	return &g_aEnemy_Glide[0];	//敵情報の先頭アドレスを渡す
}

//************************************************
//使命を終えた敵の消滅処理関数
//************************************************
void Disapper_Enemy_Glide(int nCntEnemy)
{
	g_aEnemy_Glide[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の位置情報を初期化
	g_aEnemy_Glide[nCntEnemy].fHalfSpanX = 0.0f;					//敵の半幅Xを初期化
	g_aEnemy_Glide[nCntEnemy].fHalfSpanY = 0.0f;					//敵の半幅Yを初期化
	g_aEnemy_Glide[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の移動情報を初期化
	g_aEnemy_Glide[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//敵の向き情報を初期化
	g_aEnemy_Glide[nCntEnemy].nColA = 0;							//透明度初期化
	g_aEnemy_Glide[nCntEnemy].state = ENEMYSTATE_GLIDE_NORMAL;		//初期から通常状態
	g_aEnemy_Glide[nCntEnemy].nCntState = 0;						//カウント数を初期化
	g_aEnemy_Glide[nCntEnemy].nLife = 0;							//ライフを初期化
	g_aEnemy_Glide[nCntEnemy].bUse = false;							//使用判定を無くす
	g_aEnemy_Glide[nCntEnemy].nCntSpawn = 0;						//いつ出現するか
	g_aEnemy_Glide[nCntEnemy].nCntChange = 0;						//いつ進路変更するか
	g_aEnemy_Glide[nCntEnemy].bUseEffect = false;					//エフェクト使用判定を無くす
	g_aEnemy_Glide[nCntEnemy].bFinishEffect = false;				//エフェクト終了判定を無くす
	g_aEnemy_Glide[nCntEnemy].fDirection = 0.0f;					//方角を初期化
	g_aEnemy_Glide[nCntEnemy].fTurningSPD = 0.0f;					//旋回速度を初期化
	g_aEnemy_Glide[nCntEnemy].fSizeCircle = 0.0f;					//円周幅を初期化
	g_aEnemy_Glide[nCntEnemy].fLength = 0.0f;						//対角線の長さを初期化
	g_aEnemy_Glide[nCntEnemy].fAngle = 0.0f;						//対角線の角度を初期化
}