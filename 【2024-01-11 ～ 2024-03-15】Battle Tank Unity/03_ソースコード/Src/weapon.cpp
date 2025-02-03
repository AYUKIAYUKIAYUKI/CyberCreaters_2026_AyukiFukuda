//************************************************
//
// 武器表示[weapon.cpp]
// Author：福田歩希
//
//************************************************

/*---【インクルードファイル】---*/
#include "weapon.h"

// システム
#include "sound.h"

// 諸処理
#include "game.h"
#include "player.h"

// デバッグ用
#ifdef _DEBUG
#include <assert.h>
#endif // _DEBUG

/*---【マクロ定義】---*/
#define AMOUNT_WEAPON 32	// 武器表示の最大数

/*---【テクスチャ分類】---*/
typedef enum
{
	TEXTURE_TYPE_WEAPON_PFW1 = 0,	// 下地
	TEXTURE_TYPE_WEAPON_PFW2,		// 窓
	TEXTURE_TYPE_WEAPON_PFW3,		// 歯車
	TEXTURE_TYPE_WEAPON_GUN,		// 銃
	TEXTURE_TYPE_WEAPON_RPG,		// RPG
	TEXTURE_TYPE_WEAPON_GUT,		// ミニガン
	TEXTURE_TYPE_WEAPON_SHOT,		// 散弾銃
	TEXTURE_TYPE_WEAPON_MAX
} TEXTURE_TYPE_WEAPON;

/*---【グローバル変数】---*/
LPDIRECT3DTEXTURE9 g_pTextureWeapon[TEXTURE_TYPE_WEAPON_MAX] = {};	// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWeapon = NULL;					// 頂点バッファのポインタ
UI g_Weapon[AMOUNT_WEAPON];											// 武器表示用情報
float g_RotZ_Goal[AMOUNT_WEAPON] = {};								// 特別に

int g_CT_startWeapon = 0;	// 武器表示が登場するまでの遅延用

/*---【プロトタイプ宣言】---*/
void ImportTexWeapon(void);			// テクスチャを取得
void ImportInfoWeapon(int joined);	// 設定情報を取得
void CreateVtxWeapon(void);			// 頂点バッファの生成

void ChangePFW4(int id, int tex);			// 武器変更
void AnimationManagerWeapon_First(void);	// アニメーション特別管理
void AnimationManagerWeapon(void);			// アニメーション管理
void PlayAnimationWeapon(int i, int type);	// アニメーション再生
void StopAnimationWeapon(int i, int type);	// アニメーション停止

void VibrationSmallWeapon(int i);	// 振動：小
void VibrationBigWeapon(int i);		// 振動：大
void ChangeRedWeapon(int i);		// 赤く
void FadeAppearWeapon(int i);		// 出現
void LikeaGummyWeapon(int i);		// ブニョ
void AppealtoFrontWeapon(int i);	// チラチラ
void SlideUpWeapon(int i);			// 上スライドイン
void SlideDownWeapon(int i);		// 下
void SlideLeftWeapon(int i);		// 左
void SlideRightWeapon(int i);		// 右
void DisSlideUpWeapon(int i);		// 上スライドアウト
void DisSlideDownWeapon(int i);		// 下
void DisSlideLeftWeapon(int i);		// 左
void DisSlideRightWeapon(int i);	// 右

void SetVtxWeapon(void);		// 展開
void DrawNormalWeapon(void);	// 通常描画

//************************************************
// 初期処理
//************************************************
void InitWeapon(int joined)
{
	g_CT_startWeapon = 0;	// 武器表示が登場するまでの遅延用

	for (int i = 0; i < AMOUNT_WEAPON; i++)
	{ // Weapon表示リセット
		g_Weapon[i].use = false;
		g_Weapon[i].textype = -1;
		g_Weapon[i].pos = { 0.0f, 0.0f, 0.0f };
		g_Weapon[i].move = { 0.0f, 0.0f, 0.0f };
		g_Weapon[i].rot = { 0.0f, 0.0f, 0.0f };
		g_Weapon[i].span = { 0.0f, 0.0f };
		g_Weapon[i].angle = 0;
		g_Weapon[i].length = 0;
		g_Weapon[i].col = { 1.0f, 1.0f, 1.0f, 1.0f };

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{ // アニメーション情報リセット
			g_Weapon[i].play[j].use = false;
			g_Weapon[i].play[j].dur = 0;
			g_Weapon[i].play[j].pos = { 0.0f, 0.0f, 0.0f };
			g_Weapon[i].play[j].move = { 0.0f, 0.0f, 0.0f };
			g_Weapon[i].play[j].rot = { 0.0f, 0.0f, 0.0f };
			g_Weapon[i].play[j].span = { 0.0f, 0.0f };
			g_Weapon[i].play[j].col = { 0.0f, 0.0f, 0.0f, 0.0f };
		}

		g_RotZ_Goal[i] = 0.0f;
	}

	// テクスチャを読み込む
	ImportTexWeapon();

	// 情報を取得する
	ImportInfoWeapon(joined);

	// 通常頂点バッファの生成
	CreateVtxWeapon();

	/**********************************/

	g_CT_startWeapon = 30;	// 武器表示が登場するまでの遅延用

	/**********************************/
}

//************************************************
// 終了処理
//************************************************
void UninitWeapon(void)
{
	for (int i = 0; i < TEXTURE_TYPE_WEAPON_MAX; i++)
	{
		if (g_pTextureWeapon[i] != NULL)
		{ // テクスチャの破棄
			g_pTextureWeapon[i]->Release();
			g_pTextureWeapon[i] = NULL;
		}
	}

	if (g_pVtxBuffWeapon != NULL)
	{ // 頂点バッファの破棄
		g_pVtxBuffWeapon->Release();
		g_pVtxBuffWeapon = NULL;
	}
}

//************************************************
// 更新処理
//************************************************
void UpdateWeapon(int joined)
{
	Player* pPlayer = GetInfoPlayer();

	for (int i = 0; i < joined; i++)
	{
		// 武器テクスチャ反映
		ChangePFW4(i, pPlayer[i].param.weapon);
	}

	// アニメーション特別管理
	AnimationManagerWeapon_First();

	// アニメーション管理
	AnimationManagerWeapon();

	// 通常展開
	SetVtxWeapon();
}

//************************************************
// 描画処理
//************************************************
void DrawWeapon(void)
{
	// 通常描画
	DrawNormalWeapon();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// テクスチャを読み込む
//************************************************
void ImportTexWeapon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// テクスチャ画像の読込み用
	const char* pFileName[TEXTURE_TYPE_WEAPON_MAX] =
	{
		"data\\TEXTURE\\PFW1.png",
		"data\\TEXTURE\\PFW2.png",
		"data\\TEXTURE\\PFW3.png",
		"data\\TEXTURE\\gun.png",
		"data\\TEXTURE\\rpg.png",
		"data\\TEXTURE\\gut.png",
		"data\\TEXTURE\\shot.png",
	};

	for (int i = 0; i < TEXTURE_TYPE_WEAPON_MAX; i++)
	{ // テクスチャの生成

		if (pFileName[i] == NULL)
		{
			break;	// 画像が無くなっても終了
		}

		D3DXCreateTextureFromFile(pDevice,
			pFileName[i],
			&g_pTextureWeapon[i]);
	}
}

//************************************************
// 設定情報を読み込む
//************************************************
void ImportInfoWeapon(int joined)
{
	// ファイルデータ読込み用
	FILE* pFile = NULL;
	char str[128] = {};		// 文章を格納
	int set = 0;			// 何人用か
	int i = 0;				// 汎用整数
	int textype = 0;		// テクスチャ情報を取得
	D3DXVECTOR3 pos = {};	// 位置を格納
	D3DXVECTOR3 rot = {};	// 向きを格納
	D3DXVECTOR2 span = {};	// 大きさを格納
	D3DXCOLOR col = {};		// 色を格納

	// Weapon情報を展開する
	if (fopen_s(&pFile, "data\\TXT\\UI\\weapon.txt", "r") != 0)
	{
#ifdef _DEBUG

		// エラー
		assert(false && "武器用配置情報の展開に失敗");

#endif	// _DEBUG：ファイル展開の合否
	}

	while (fscanf_s(pFile, "%s", &str[0], 128) != EOF)
	{
		if (strcmp(&str[0], "SET") == 0)
		{ // 参加人数を取得
			fscanf_s(pFile, "%s %d", &str[0], 2, &set);
		}

		if (set != joined)
		{ // 対応するセットのみを取得
			continue;
		}

		if (strcmp(&str[0], "TEXTYPE") == 0)
		{ // テクスチャタイプを取得
			fscanf_s(pFile, "%s %d", &str[0], 2, &textype);
		}

		if (strcmp(&str[0], "POS") == 0)
		{ // 位置を取得
			fscanf_s(pFile, "%s %f %f %f", &str[0], 2, &pos.x, &pos.y, &pos.z);
		}

		if (strcmp(&str[0], "ROT") == 0)
		{ // 向きを取得
			fscanf_s(pFile, "%s %f %f %f", &str[0], 2, &rot.x, &rot.y, &rot.z);
		}

		if (strcmp(&str[0], "SPAN") == 0)
		{ // 大きさを取得
			fscanf_s(pFile, "%s %f %f", &str[0], 2, &span.x, &span.y);
		}

		if (strcmp(&str[0], "COL") == 0)
		{ // 色を取得
			fscanf_s(pFile, "%s %f %f %f %f", &str[0], 2, &col.r, &col.g, &col.b, &col.a);
		}

		if (strcmp(&str[0], "END_PARAMSET") == 0)
		{ // 取得した情報を反映

			g_Weapon[i].use = true;
			g_Weapon[i].textype = textype;
			g_Weapon[i].pos = pos;
			g_Weapon[i].rot = rot;
			g_Weapon[i].span = span;
			g_Weapon[i].col = col;

			i++;	// 次の番号へ
		}

		if (strcmp(&str[0], "END_SCRIPT") == 0)
		{
			break;	// 終了
		}
	}

	// ファイルを閉じる
	fclose(pFile);
}

//************************************************
// 頂点バッファの生成
//************************************************
void CreateVtxWeapon(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * AMOUNT_VTX * AMOUNT_WEAPON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWeapon,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffWeapon->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_WEAPON; i++, pVtx += AMOUNT_VTX)
	{
		// 頂点座標の初期設定
		pVtx[0].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[1].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[2].pos = { 0.0f, 0.0f, 0.0f };
		pVtx[3].pos = { 0.0f, 0.0f, 0.0f };

		// 除算数の初期設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の初期設定
		pVtx[0].tex = { 0.0f, 0.0f };
		pVtx[1].tex = { 1.0f, 0.0f };
		pVtx[2].tex = { 0.0f, 1.0f };
		pVtx[3].tex = { 1.0f, 1.0f };
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffWeapon->Unlock();
}

////************************************************
//// アニメーション選択
////************************************************
//void SelectAnimationWeapon(void)
//{
//	int i = g_select;	// 識別簡略化
//
//	// 再生するアニメーションを変更する
//	if (GetKeyboardTrigger(DIK_1))
//	{
//		g_animaType > 0 ? g_animaType-- : g_animaType = ANIMATION_TYPE_MAX - 1;
//	}
//	else if (GetKeyboardTrigger(DIK_2))
//	{
//		g_animaType < ANIMATION_TYPE_MAX - 1 ? g_animaType++ : g_animaType = 0;
//	}
//
//	// 対応するアニメーションを再生
//	if (GetKeyboardTrigger(DIK_3))
//	{
//		switch (g_animaType)
//		{
//		case ANIMATION_TYPE_VIBSMALL:
//
//			g_Weapon[i].play[ANIMATION_TYPE_VIBSMALL].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_VIBSMALL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_VIBBIG:
//
//			g_Weapon[i].play[ANIMATION_TYPE_VIBBIG].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_VIBBIG].dur = 15;
//
//			break;
//
//		case ANIMATION_TYPE_RED:
//
//			g_Weapon[i].play[ANIMATION_TYPE_RED].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_RED].dur = 20;
//
//			break;
//
//		case ANIMATION_TYPE_FADE:
//
//			g_Weapon[i].play[ANIMATION_TYPE_FADE].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_FADE].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_GUMMY:
//
//			g_Weapon[i].play[ANIMATION_TYPE_GUMMY].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_GUMMY].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_APPEAL:
//
//			g_Weapon[i].play[ANIMATION_TYPE_APPEAL].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_APPEAL].dur = 30;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEUP:
//
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDEUP].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDEUP].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDEDOWN:
//
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDEDOWN].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDEDOWN].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDELEFT:
//
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDELEFT].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDELEFT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_SLIDERIGHT:
//
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDERIGHT].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_SLIDERIGHT].dur = 60;
//
//			break;
//
//		case ANIMATION_TYPE_DISUP:
//
//			g_Weapon[i].play[ANIMATION_TYPE_DISUP].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_DISUP].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISDOWN:
//
//			g_Weapon[i].play[ANIMATION_TYPE_DISDOWN].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_DISDOWN].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISLEFT:
//
//			g_Weapon[i].play[ANIMATION_TYPE_DISLEFT].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_DISLEFT].dur = 40;
//
//			break;
//
//		case ANIMATION_TYPE_DISRIGHT:
//
//			g_Weapon[i].play[ANIMATION_TYPE_DISRIGHT].use = true;
//			g_Weapon[i].play[ANIMATION_TYPE_DISRIGHT].dur = 40;
//
//			break;
//		}
//	}
//}

//************************************************
// 武器変更
//************************************************
void ChangePFW4(int id, int tex)
{
	if (g_Weapon[4 + (id * 4) - 1].textype - 3 != tex)
	{ // 異なる指定がされているときのみ

		// テクスチャ指定
		g_Weapon[4 + (id * 4) - 1].textype = tex + 3;

		// アニメーション
		g_Weapon[4 + (id * 4) - 1].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Weapon[4 + (id * 4) - 1].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}
}

//************************************************
// アニメーション特別管理
//************************************************
void AnimationManagerWeapon_First(void)
{
	g_CT_startWeapon > 0 ? g_CT_startWeapon-- : g_CT_startWeapon = 0;

	if (g_CT_startWeapon == 1)
	{
		g_Weapon[0].play[ANIMATION_TYPE_FADE].use = true;
		g_Weapon[0].play[ANIMATION_TYPE_FADE].dur = 60;

		g_Weapon[0].col = { 1.0f, 1.0f, 1.0f, 1.0f };
	}

	for (int i = 0; i < AMOUNT_WEAPON - 1; i++)
	{
		if (!g_Weapon[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (g_Weapon[i].play[ANIMATION_TYPE_FADE].dur == 55)
		{
			g_Weapon[i + 1].play[ANIMATION_TYPE_FADE].use = true;
			g_Weapon[i + 1].play[ANIMATION_TYPE_FADE].dur = 60;

			g_Weapon[i + 1].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}

	for (int i = 0; i < AMOUNT_WEAPON - 2; i++)
	{
		if (!g_Weapon[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		if (g_Weapon[i + 1].play[ANIMATION_TYPE_FADE].dur == 55)
		{
			g_Weapon[i + 2].play[ANIMATION_TYPE_FADE].use = true;
			g_Weapon[i + 2].play[ANIMATION_TYPE_FADE].dur = 60;

			g_Weapon[i + 2].col = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
	}
}

//************************************************
// アニメーション管理
//************************************************
void AnimationManagerWeapon(void)
{
	for (int i = 0; i < AMOUNT_WEAPON; i++)
	{
		if (!g_Weapon[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		// どのアニメーションを再生するのか選別
		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			if (g_Weapon[i].play[j].use)
			{
				// 対応するアニメーションを再生する
				PlayAnimationWeapon(i, j);
			}
		}
	}
}

//************************************************
// 種類に対応したアニメーション再生
//************************************************
void PlayAnimationWeapon(int id, int type)
{
	switch (type)
	{
	case ANIMATION_TYPE_VIBSMALL:

		VibrationSmallWeapon(id);	// 振動：小

		break;

	case ANIMATION_TYPE_VIBBIG:

		VibrationBigWeapon(id);	// 振動：大

		break;

	case ANIMATION_TYPE_RED:

		ChangeRedWeapon(id);	// 赤くなる

		break;

	case ANIMATION_TYPE_FADE:

		FadeAppearWeapon(id);	// フェード

		break;

	case ANIMATION_TYPE_GUMMY:

		LikeaGummyWeapon(id);	// ブニョ

		break;

	case ANIMATION_TYPE_APPEAL:

		AppealtoFrontWeapon(id);	// バンっ

		break;

	case ANIMATION_TYPE_SLIDEUP:

		SlideUpWeapon(id);	// 上スライドイン

		break;

	case ANIMATION_TYPE_SLIDEDOWN:

		SlideDownWeapon(id);	// 下スライドイン

		break;

	case ANIMATION_TYPE_SLIDELEFT:

		SlideLeftWeapon(id);	// 左スライドイン

		break;

	case ANIMATION_TYPE_SLIDERIGHT:

		SlideRightWeapon(id);	// 右スライドイン

		break;

	case ANIMATION_TYPE_DISUP:

		DisSlideUpWeapon(id);	// 上スライドアウト

		break;

	case ANIMATION_TYPE_DISDOWN:

		DisSlideDownWeapon(id);	// 下スライドアウト

		break;

	case ANIMATION_TYPE_DISLEFT:

		DisSlideLeftWeapon(id);	// 左スライドアウト

		break;

	case ANIMATION_TYPE_DISRIGHT:

		DisSlideRightWeapon(id);	// 右スライドアウト

		break;
	}
}

//************************************************
// アニメーション停止
//************************************************
void StopAnimationWeapon(int id, int type)
{
	g_Weapon[id].play[type] =
	{
		false,
		0,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
	};
}

//************************************************
// 振動：小
//************************************************
void VibrationSmallWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_VIBSMALL].pos =
	{
		(float)(rand() % 10),
		(float)(rand() % 10),
		0.0f
	};

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_VIBSMALL].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_VIBSMALL);
	}
}

//************************************************
// 振動：大
//************************************************
void VibrationBigWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_VIBBIG].pos =
	{
		(float)(rand() % 30),
		(float)(rand() % 30),
		0.0f
	};

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_VIBBIG].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_VIBBIG);
	}
}

//************************************************
// 赤くなる
//************************************************
void ChangeRedWeapon(int id)
{
	if (g_Weapon[id].play[ANIMATION_TYPE_RED].dur > 10)
	{
		g_Weapon[id].play[ANIMATION_TYPE_RED].col.g += -0.1f;
		g_Weapon[id].play[ANIMATION_TYPE_RED].col.b += -0.1f;
	}
	else
	{
		g_Weapon[id].play[ANIMATION_TYPE_RED].col.g += 0.1f;
		g_Weapon[id].play[ANIMATION_TYPE_RED].col.b += 0.1f;
	}

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_RED].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_RED);
	}
}

//************************************************
// 出現
//************************************************
void FadeAppearWeapon(int id)
{
	if (g_Weapon[id].play[ANIMATION_TYPE_FADE].dur >= 40)
	{
		g_Weapon[id].play[ANIMATION_TYPE_FADE].col.a = -1.0f;
	}
	else
	{
		g_Weapon[id].play[ANIMATION_TYPE_FADE].col.a = (-1.0f / (40 - g_Weapon[id].play[ANIMATION_TYPE_FADE].dur));
	}

	if (g_Weapon[id].play[ANIMATION_TYPE_FADE].dur == 40)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].use = true;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur = 30;
	}

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_FADE].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_FADE);
	}
}

//************************************************
// ブニョ
//************************************************
void LikeaGummyWeapon(int id)
{
	if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur > 25)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur > 20 &&
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur <= 25)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur > 15 &&
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur <= 20)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.x += 2;

		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur > 10 &&
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur <= 15)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y += 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y -= 2;
	}
	else if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur > 5 &&
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur <= 10)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}
	else if (g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur <= 5)
	{
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.x -= 2;

		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].pos.y -= 2;
		g_Weapon[id].play[ANIMATION_TYPE_GUMMY].span.y += 2;
	}

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_GUMMY].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_GUMMY);
	}
}

//************************************************
// チラチラ
//************************************************
void AppealtoFrontWeapon(int id)
{
	if (g_Weapon[id].play[ANIMATION_TYPE_APPEAL].dur == 30)
	{
		g_Weapon[id].play[ANIMATION_TYPE_APPEAL].col.a = -1.0f;
	}

	g_Weapon[id].play[ANIMATION_TYPE_APPEAL].col.a *= -1.0f;

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_APPEAL].dur))
	{
		g_Weapon[id].play[ANIMATION_TYPE_APPEAL].col.a = 0.0f;

		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_APPEAL);
	}
}

//************************************************
// 上スライドイン
//************************************************
void SlideUpWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_SLIDEUP].pos.y = (2000.0f / (60 - g_Weapon[id].play[ANIMATION_TYPE_SLIDEUP].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_SLIDEUP].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_SLIDEUP);
	}
}

//************************************************
// 下スライドイン
//************************************************
void SlideDownWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_SLIDEDOWN].pos.y = (-2000.0f / (60 - g_Weapon[id].play[ANIMATION_TYPE_SLIDEDOWN].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_SLIDEDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_SLIDEDOWN);
	}
}

//************************************************
// 左スライドイン
//************************************************
void SlideLeftWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_SLIDELEFT].pos.x = (-2000.0f / (60 - g_Weapon[id].play[ANIMATION_TYPE_SLIDELEFT].dur)) + (2000.0f / 60);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_SLIDELEFT].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_SLIDELEFT);
	}
}

//************************************************
// 右スライドイン
//************************************************
void SlideRightWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_SLIDERIGHT].pos.x = (2000.0f / (60 - g_Weapon[id].play[ANIMATION_TYPE_SLIDERIGHT].dur)) + (-2000.0f / 60);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_SLIDERIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_SLIDERIGHT);
	}
}

//************************************************
// 上スライドアウト
//************************************************
void DisSlideUpWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_DISUP].pos.y = (-2000.0f / g_Weapon[id].play[ANIMATION_TYPE_DISUP].dur) + (2000.0f / 40);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_DISUP].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_DISUP);
	}
}

//************************************************
// 下スライドアウト
//************************************************
void DisSlideDownWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_DISDOWN].pos.y = (2000.0f / g_Weapon[id].play[ANIMATION_TYPE_DISDOWN].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_DISDOWN].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_DISDOWN);
	}
}

//************************************************
// 左スライドアウト
//************************************************
void DisSlideLeftWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_DISLEFT].pos.x = (-2000.0f / g_Weapon[id].play[ANIMATION_TYPE_DISLEFT].dur) + (2000.0f / 40);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_DISLEFT].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_DISLEFT);
	}
}

//************************************************
// 右スライドアウト
//************************************************
void DisSlideRightWeapon(int id)
{
	g_Weapon[id].play[ANIMATION_TYPE_DISRIGHT].pos.x = (2000.0f / g_Weapon[id].play[ANIMATION_TYPE_DISRIGHT].dur) + (-2000.0f / 40);

	if (CntDuration(&g_Weapon[id].play[ANIMATION_TYPE_DISRIGHT].dur))
	{
		// アニメーションを停止
		StopAnimationWeapon(id, ANIMATION_TYPE_DISRIGHT);
	}
}

//************************************************
// 頂点を展開
//************************************************
void SetVtxWeapon(void)
{
	AnimationParam general[AMOUNT_WEAPON] = {};	// 再生用情報をまとめる

	for (int i = 0; i < AMOUNT_WEAPON; i++)
	{ // 頂点位置用の情報を算出

		if (!g_Weapon[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		for (int j = 0; j < ANIMATION_TYPE_MAX; j++)
		{
			// 再生用の疑似情報をまとめる
			general[i].move += g_Weapon[i].play[j].move;
			general[i].pos += g_Weapon[i].play[j].pos;
			general[i].rot += g_Weapon[i].play[j].rot;
			general[i].span += g_Weapon[i].play[j].span;
			general[i].col += g_Weapon[i].play[j].col;
		}

		// 角度を算出
		g_Weapon[i].angle = atan2f(g_Weapon[i].span.x + general[i].span.x, g_Weapon[i].span.y + general[i].span.y);

		// 対角線を算出
		g_Weapon[i].length = sqrtf((g_Weapon[i].span.x + general[i].span.x) * (g_Weapon[i].span.x + general[i].span.x) +
			(g_Weapon[i].span.y + general[i].span.y) * (g_Weapon[i].span.y + general[i].span.y));

		// 回転量に慣性
		if (g_RotZ_Goal[i] != 0.0f)
		{ // 少なくとも回転の見込みがあるもの

			g_RotZ_Goal[i] *= 0.9f;
			g_Weapon[i].rot.z += g_RotZ_Goal[i];
		}
	}

	/*--------------------------------------------*/

	VERTEX_2D* pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックして頂点情報のポインタを取得
	g_pVtxBuffWeapon->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < AMOUNT_WEAPON; i++, pVtx += AMOUNT_VTX)
	{ // 頂点座標の設定
		pVtx[0].pos =
		{
			g_Weapon[i].pos.x + general[i].pos.x + sinf((g_Weapon[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Weapon[i].angle)) * g_Weapon[i].length,
			g_Weapon[i].pos.y + general[i].pos.y + cosf((g_Weapon[i].rot.z + general[i].rot.z) - (D3DX_PI - g_Weapon[i].angle)) * g_Weapon[i].length,
			0.0f
		};

		pVtx[1].pos =
		{
			g_Weapon[i].pos.x + general[i].pos.x + sinf((g_Weapon[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Weapon[i].angle)) * g_Weapon[i].length,
			g_Weapon[i].pos.y + general[i].pos.y + cosf((g_Weapon[i].rot.z + general[i].rot.z) + (D3DX_PI - g_Weapon[i].angle)) * g_Weapon[i].length,
			0.0f
		};

		pVtx[2].pos =
		{
			g_Weapon[i].pos.x + general[i].pos.x + sinf((g_Weapon[i].rot.z + general[i].rot.z) - (g_Weapon[i].angle)) * g_Weapon[i].length,
			g_Weapon[i].pos.y + general[i].pos.y + cosf((g_Weapon[i].rot.z + general[i].rot.z) - (g_Weapon[i].angle)) * g_Weapon[i].length,
			0.0f
		};

		pVtx[3].pos =
		{
			g_Weapon[i].pos.x + general[i].pos.x + sinf((g_Weapon[i].rot.z + general[i].rot.z) + (g_Weapon[i].angle)) * g_Weapon[i].length,
			g_Weapon[i].pos.y + general[i].pos.y + cosf((g_Weapon[i].rot.z + general[i].rot.z) + (g_Weapon[i].angle)) * g_Weapon[i].length,
			0.0f
		};

		// 色の反映
		pVtx[0].col = g_Weapon[i].col + general[i].col;
		pVtx[1].col = g_Weapon[i].col + general[i].col;
		pVtx[2].col = g_Weapon[i].col + general[i].col;
		pVtx[3].col = g_Weapon[i].col + general[i].col;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffWeapon->Unlock();
}

//************************************************
// 通常描画処理
//************************************************
void DrawNormalWeapon(void)
{
	// デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int textype = 0;

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffWeapon, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < AMOUNT_WEAPON; i++)
	{
		if (!g_Weapon[i].use)
		{ // 未使用ならコンティニュー
			continue;
		}

		textype = g_Weapon[i].textype;

		pDevice->SetTexture(0, g_pTextureWeapon[textype]);

		// テストの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * AMOUNT_VTX, AMOUNT_COMBINEPOLYGON);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//************************************************
// 歯車回転
//************************************************
void RotatePFW3(int id, float pw)
{
	g_RotZ_Goal[3 + (id * 4) - 1] += pw;
}