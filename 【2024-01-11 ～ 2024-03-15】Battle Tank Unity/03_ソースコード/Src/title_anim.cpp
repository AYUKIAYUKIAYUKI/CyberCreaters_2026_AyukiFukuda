//===============================================================================
//
//  タイトル画面アニメーション処理(title_anim.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "title_anim.h"
#include "input.h"

#define SELECT_USE_POLY	(11)
#define TITLE_ANIM_POS_X	(SCREEN_WIDTH * 0.5)
#define TITLE_ANIM_GEAR_HALFSIZE	(160)

//テクスチャ割り当て(順は下に記述)
typedef enum
{
	TEXTYPE_TWALLL = 0,
	TEXTYPE_TWALLR,
	TEXTYPE_GEAR_L,
	TEXTYPE_GEAR_R,
	TEXTYPE_GEAR_CHAIN,
	TEXTYPE_WALLGEAR,
	TEXTYPE_TITLE,
	TEXTYPE_MAX
}TEXTYPE_ANIM;
//テクスチャ列挙
static const char* TAnimCnt[TEXTYPE_MAX]
{
	"data\\TEXTURE\\Title\\TwallL.png",			//左壁
	"data\\TEXTURE\\Title\\TwallR.png",			//右壁
	"data\\TEXTURE\\SelectCnt\\gear_l.png",		//左ギア
	"data\\TEXTURE\\SelectCnt\\gear_r.png",		//右ギア
	"data\\TEXTURE\\Title\\gear_chain.png",		//鎖
	"data\\TEXTURE\\Title\\gear.png",			//中央ギア
	"data\\TEXTURE\\Title\\TitleText.png",		//タイトル命
};

//プレイヤーセレクト用構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fHeight;
	float fWidth;
	float fAngle;
	float fLength;
	int Type;
}TITEL_ANIM;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitleAnim[TEXTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleAnim = NULL;
float TitleAnimGear[2];
bool bUseTitleAnim;		//アニメーション判定用
bool TitleAnimFinish;
TITEL_ANIM TitleAnim[SELECT_USE_POLY];			//プレイヤー選択構造体

//===============================================================================
//人数選択画面の初期化処理
//===============================================================================
void InitTitleAnim(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	for (int i = 0; i < TEXTYPE_MAX; i++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			TAnimCnt[i],
			&g_pTextureTitleAnim[i]);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * SELECT_USE_POLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleAnim,
		NULL);

	for (int i = 0; i < SELECT_USE_POLY; i++)
	{
		TitleAnim[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一応初期化
		switch (i)
		{
		case 0:
			TitleAnim[i].pos = D3DXVECTOR3(TITLE_ANIM_POS_X, SCREEN_HEIGHT / 2, 0);
			TitleAnim[i].fWidth = SCREEN_WIDTH;
			TitleAnim[i].fHeight = SCREEN_HEIGHT;
			TitleAnim[i].Type = TEXTYPE_TWALLL;
			break;
		case 1:
			TitleAnim[i].pos = D3DXVECTOR3(TITLE_ANIM_POS_X, SCREEN_HEIGHT / 2, 0);
			TitleAnim[i].fWidth = SCREEN_WIDTH;
			TitleAnim[i].fHeight = SCREEN_HEIGHT;
			TitleAnim[i].Type = TEXTYPE_TWALLR;
			break;
		case 2:
			TitleAnim[i].pos = D3DXVECTOR3(0, 0.0f, 0);
			TitleAnim[i].fWidth = TITLE_ANIM_GEAR_HALFSIZE;
			TitleAnim[i].fHeight = TITLE_ANIM_GEAR_HALFSIZE;
			TitleAnim[i].Type = TEXTYPE_GEAR_L;
			break;
		case 3:
			TitleAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);
			TitleAnim[i].fWidth = TITLE_ANIM_GEAR_HALFSIZE;
			TitleAnim[i].fHeight = TITLE_ANIM_GEAR_HALFSIZE;
			TitleAnim[i].Type = TEXTYPE_GEAR_R;
			break;
		case 4:
			TitleAnim[i].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0);
			TitleAnim[i].fWidth = TITLE_ANIM_GEAR_HALFSIZE;
			TitleAnim[i].fHeight = TITLE_ANIM_GEAR_HALFSIZE;
			TitleAnim[i].Type = TEXTYPE_GEAR_R;
			break;
		case 5:
			TitleAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
			TitleAnim[i].fWidth = TITLE_ANIM_GEAR_HALFSIZE;
			TitleAnim[i].fHeight = TITLE_ANIM_GEAR_HALFSIZE;
			TitleAnim[i].Type = TEXTYPE_GEAR_L;
			break;
		case 6:
			TitleAnim[i].pos = D3DXVECTOR3(TITLE_ANIM_GEAR_HALFSIZE / 3, SCREEN_HEIGHT / 2, 0);
			TitleAnim[i].fWidth = 25;
			TitleAnim[i].fHeight = SCREEN_HEIGHT;
			TitleAnim[i].Type = TEXTYPE_GEAR_CHAIN;
			break;
		case 7:
			TitleAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH - (TITLE_ANIM_GEAR_HALFSIZE / 3), SCREEN_HEIGHT / 2, 0);
			TitleAnim[i].fWidth = 25;
			TitleAnim[i].fHeight = SCREEN_HEIGHT;
			TitleAnim[i].Type = TEXTYPE_GEAR_CHAIN;
			break;
		case 8:
			TitleAnim[i].pos = D3DXVECTOR3(TITLE_ANIM_POS_X - 140, SCREEN_HEIGHT / 2 - 20, 0);
			TitleAnim[i].fWidth = 450;
			TitleAnim[i].fHeight = 450;
			TitleAnim[i].Type = TEXTYPE_WALLGEAR;
			break;
		case 9:
			TitleAnim[i].pos = D3DXVECTOR3(520, -200, 0);
			TitleAnim[i].fWidth = 720;
			TitleAnim[i].fHeight = 420;
			TitleAnim[i].Type = TEXTYPE_TITLE;
			break;
		case 10:
			TitleAnim[i].pos = D3DXVECTOR3(TITLE_ANIM_POS_X + 240, SCREEN_HEIGHT / 2 + 80, 0);
			TitleAnim[i].fWidth = 400;
			TitleAnim[i].fHeight = 400;
			TitleAnim[i].Type = TEXTYPE_WALLGEAR;

		}
		TitleAnim[i].fAngle = atan2f(TitleAnim[i].fWidth, TitleAnim[i].fHeight);
		TitleAnim[i].fLength = sqrtf(TitleAnim[i].fWidth * TitleAnim[i].fWidth + TitleAnim[i].fHeight * TitleAnim[i].fHeight) / 2;
	}
	VERTEX_2D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	g_pVtxBuffTitleAnim->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < SELECT_USE_POLY; nCnt++)
	{

		//頂点座標の設定
		pVtx[0].pos.x = TitleAnim[nCnt].pos.x + sinf(TitleAnim[nCnt].rot.z - (D3DX_PI - TitleAnim[nCnt].fAngle)) * TitleAnim[nCnt].fLength;
		pVtx[0].pos.y = TitleAnim[nCnt].pos.y + cosf(TitleAnim[nCnt].rot.z - (D3DX_PI - TitleAnim[nCnt].fAngle)) * TitleAnim[nCnt].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = TitleAnim[nCnt].pos.x + sinf(TitleAnim[nCnt].rot.z + (D3DX_PI - TitleAnim[nCnt].fAngle)) * TitleAnim[nCnt].fLength;
		pVtx[1].pos.y = TitleAnim[nCnt].pos.y + cosf(TitleAnim[nCnt].rot.z + (D3DX_PI - TitleAnim[nCnt].fAngle)) * TitleAnim[nCnt].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = TitleAnim[nCnt].pos.x + sinf(TitleAnim[nCnt].rot.z - TitleAnim[nCnt].fAngle) * TitleAnim[nCnt].fLength;
		pVtx[2].pos.y = TitleAnim[nCnt].pos.y + cosf(TitleAnim[nCnt].rot.z - TitleAnim[nCnt].fAngle) * TitleAnim[nCnt].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = TitleAnim[nCnt].pos.x + sinf(TitleAnim[nCnt].rot.z + TitleAnim[nCnt].fAngle) * TitleAnim[nCnt].fLength;
		pVtx[3].pos.y = TitleAnim[nCnt].pos.y + cosf(TitleAnim[nCnt].rot.z + TitleAnim[nCnt].fAngle) * TitleAnim[nCnt].fLength;
		pVtx[3].pos.z = 0.0f;

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファのアンロック
	g_pVtxBuffTitleAnim->Unlock();
	TitleAnimGear[0] = 0.0f;
	TitleAnimGear[1] = 0.0f;
	bUseTitleAnim = false;
	TitleAnimFinish = false;
}
//===============================================================================
//人数選択画面の終了処理
//===============================================================================
void UninitTitleAnim(void)
{
	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		//テクスチャの破棄
		if (g_pTextureTitleAnim[nCnt] != NULL)
		{
			g_pTextureTitleAnim[nCnt]->Release();
			g_pTextureTitleAnim[nCnt] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitleAnim != NULL)
	{
		g_pVtxBuffTitleAnim->Release();
		g_pVtxBuffTitleAnim = NULL;
	}
}

//===============================================================================
//人数選択画面の更新処理
//===============================================================================
void UpdateTitleAnim(void)
{
	if (TitleAnim[8].rot.z < 3.14f * 1.5f)
	{
		TitleAnim[8].rot.z += (3.14f * 0.02f);
		TitleAnim[10].rot.z -= (3.14f * 0.02f);
	}
	else
	{
		if (TitleAnim[0].pos.x > -(SCREEN_WIDTH / 2) + 256)
		{//壁開くアニメーションの左側
			TitleAnim[0].pos.x -= 25.6f;	//左壁
			TitleAnim[2].rot.z -= 0.06f;	//左上歯車
			TitleAnim[4].rot.z -= 0.06f;	//左下歯車
			TitleAnimGear[0] += 0.025f;		//左鎖アニメーション
		}
		if (TitleAnim[1].pos.x < (SCREEN_WIDTH / 2) + (SCREEN_WIDTH - 256))
		{//壁開くアニメーションの右側
			TitleAnim[1].pos.x += 25.6f;	//右壁
			TitleAnim[3].rot.z += 0.06f;	//右上歯車
			TitleAnim[5].rot.z += 0.06f;	//右下歯車
			TitleAnimGear[1] -= 0.025f;		//右鎖アニメーション
		}
		if (TitleAnim[0].pos.x < -(SCREEN_WIDTH / 2) + 256 && TitleAnim[1].pos.x >(SCREEN_WIDTH / 2) - 256)
		{
			if (TitleAnim[9].pos.y < 75)
			{
				TitleAnim[9].pos.y += 7.5f;
			}
			else
			{
				TitleAnimFinish = true;
			}
		}
	}
	//初期壁とギアの相対座標
	TitleAnim[8].pos = TitleAnim[0].pos + D3DXVECTOR3(-140, -100, 0);
	TitleAnim[10].pos = TitleAnim[1].pos + D3DXVECTOR3(120, +160, 0);

	VERTEX_2D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	g_pVtxBuffTitleAnim->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < SELECT_USE_POLY; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = TitleAnim[nCnt].pos.x + sinf(TitleAnim[nCnt].rot.z - (D3DX_PI - TitleAnim[nCnt].fAngle)) * TitleAnim[nCnt].fLength;
		pVtx[0].pos.y = TitleAnim[nCnt].pos.y + cosf(TitleAnim[nCnt].rot.z - (D3DX_PI - TitleAnim[nCnt].fAngle)) * TitleAnim[nCnt].fLength;
		pVtx[0].pos.z = 0.0f;
		pVtx[1].pos.x = TitleAnim[nCnt].pos.x + sinf(TitleAnim[nCnt].rot.z + (D3DX_PI - TitleAnim[nCnt].fAngle)) * TitleAnim[nCnt].fLength;
		pVtx[1].pos.y = TitleAnim[nCnt].pos.y + cosf(TitleAnim[nCnt].rot.z + (D3DX_PI - TitleAnim[nCnt].fAngle)) * TitleAnim[nCnt].fLength;
		pVtx[1].pos.z = 0.0f;
		pVtx[2].pos.x = TitleAnim[nCnt].pos.x + sinf(TitleAnim[nCnt].rot.z - TitleAnim[nCnt].fAngle) * TitleAnim[nCnt].fLength;
		pVtx[2].pos.y = TitleAnim[nCnt].pos.y + cosf(TitleAnim[nCnt].rot.z - TitleAnim[nCnt].fAngle) * TitleAnim[nCnt].fLength;
		pVtx[2].pos.z = 0.0f;
		pVtx[3].pos.x = TitleAnim[nCnt].pos.x + sinf(TitleAnim[nCnt].rot.z + TitleAnim[nCnt].fAngle) * TitleAnim[nCnt].fLength;
		pVtx[3].pos.y = TitleAnim[nCnt].pos.y + cosf(TitleAnim[nCnt].rot.z + TitleAnim[nCnt].fAngle) * TitleAnim[nCnt].fLength;
		pVtx[3].pos.z = 0.0f;

		if (nCnt == 6 || nCnt == 7)
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + TitleAnimGear[nCnt - 6]);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + TitleAnimGear[nCnt - 6]);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + TitleAnimGear[nCnt - 6]);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + TitleAnimGear[nCnt - 6]);
		}
		else
		{
			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		pVtx += 4;
	}
	//頂点バッファのアンロック
	g_pVtxBuffTitleAnim->Unlock();
}
//===============================================================================
//人数選択画面系の描画
//===============================================================================
void DrawTitleAnim(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleAnim, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャの設定
	for (int nCnt = 0; nCnt < SELECT_USE_POLY; nCnt++)
	{
		pDevice->SetTexture(0, g_pTextureTitleAnim[TitleAnim[nCnt].Type]);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			4 * nCnt,
			2);
	}
}

//===============================================================================
//アニメーションが終わったことを返す関数
//===============================================================================
bool ReturnTitleAnimFinish(void)
{
	return TitleAnimFinish;
}

//===============================================================================
//別のcppからアニメーションを作動させる関数
//===============================================================================
void TitlePlateFade(void)
{
	if (TitleAnim[9].pos.y > -225)
	{
		TitleAnim[9].pos.y -= 22.5f;
	}
}