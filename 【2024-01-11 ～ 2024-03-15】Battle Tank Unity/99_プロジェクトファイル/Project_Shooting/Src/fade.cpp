//===============================================================================
//
//  3Dチーム制作版(fade.cpp)
//								制作：元地弘汰
// 
//===============================================================================
#include "main.h"
#include <time.h>
#include "fade.h"
#include "sound.h"

#define USE_FADE_POLY	(10)
#define FADE_ANIM_POS_X	(SCREEN_WIDTH * 0.5)
#define FADE_ANIM_GEAR_HALFSIZE	(160)
typedef enum
{
	TEXTYPE_TWALLL = 0,
	TEXTYPE_TWALLR,
	TEXTYPE_GEAR_L,
	TEXTYPE_GEAR_R,
	TEXTYPE_GEAR_CHAIN,
	TEXTYPE_WALLGEAR,
	TEXTYPE_MAX
}TEXTYPE_FADE;

//テクスチャ列挙
static const char* FadeTex[TEXTYPE_MAX]
{
	"data\\TEXTURE\\Title\\TwallL.png",			//左壁
	"data\\TEXTURE\\Title\\TwallR.png",			//右壁
	"data\\TEXTURE\\SelectCnt\\gear_l.png",		//左ギア
	"data\\TEXTURE\\SelectCnt\\gear_r.png",		//右ギア
	"data\\TEXTURE\\Title\\gear_chain.png",		//鎖
	"data\\TEXTURE\\Title\\gear.png",			//中央ギア
};

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	float fHeight;
	float fWidth;
	float fAngle;
	float fLength;
	int Type;
}FADE_ANIM;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureFade[TEXTYPE_MAX] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;

FADE_ANIM g_FadeAnim[USE_FADE_POLY];
FADE g_Fade;
float g_FadeAnimGear[2];

//===============================================================================
//フェードの初期化処理
//===============================================================================
void InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *USE_FADE_POLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);
	VERTEX_2D* pVtx;	//頂点情報のポインタ

	//頂点バッファをロックして、頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < TEXTYPE_MAX; i++)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			FadeTex[i],
			&g_pTextureFade[i]);
	}
	for (int i = 0; i < USE_FADE_POLY; i++)
	{
		g_FadeAnim[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一応初期化
		switch (i)
		{
		case 0:
			g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_POS_X, SCREEN_HEIGHT / 2, 0);
			g_FadeAnim[i].fWidth = SCREEN_WIDTH;
			g_FadeAnim[i].fHeight = SCREEN_HEIGHT;
			g_FadeAnim[i].Type = TEXTYPE_TWALLL;
			break;
		case 1:
			g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_POS_X, SCREEN_HEIGHT / 2, 0);
			g_FadeAnim[i].fWidth = SCREEN_WIDTH;
			g_FadeAnim[i].fHeight = SCREEN_HEIGHT;
			g_FadeAnim[i].Type = TEXTYPE_TWALLR;
			break;
		case 2:
			g_FadeAnim[i].pos = D3DXVECTOR3(0, 0.0f, 0);
			g_FadeAnim[i].fWidth = FADE_ANIM_GEAR_HALFSIZE;
			g_FadeAnim[i].fHeight = FADE_ANIM_GEAR_HALFSIZE;
			g_FadeAnim[i].Type = TEXTYPE_GEAR_L;
			break;
		case 3:
			g_FadeAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);
			g_FadeAnim[i].fWidth = FADE_ANIM_GEAR_HALFSIZE;
			g_FadeAnim[i].fHeight = FADE_ANIM_GEAR_HALFSIZE;
			g_FadeAnim[i].Type = TEXTYPE_GEAR_R;
			break;
		case 4:
			g_FadeAnim[i].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0);
			g_FadeAnim[i].fWidth = FADE_ANIM_GEAR_HALFSIZE;
			g_FadeAnim[i].fHeight = FADE_ANIM_GEAR_HALFSIZE;
			g_FadeAnim[i].Type = TEXTYPE_GEAR_R;
			break;
		case 5:
			g_FadeAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
			g_FadeAnim[i].fWidth = FADE_ANIM_GEAR_HALFSIZE;
			g_FadeAnim[i].fHeight = FADE_ANIM_GEAR_HALFSIZE;
			g_FadeAnim[i].Type = TEXTYPE_GEAR_L;
			break;
		case 6:
			g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_GEAR_HALFSIZE / 3, SCREEN_HEIGHT / 2, 0);
			g_FadeAnim[i].fWidth = 25;
			g_FadeAnim[i].fHeight = SCREEN_HEIGHT;
			g_FadeAnim[i].Type = TEXTYPE_GEAR_CHAIN;
			break;
		case 7:
			g_FadeAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH - (FADE_ANIM_GEAR_HALFSIZE / 3), SCREEN_HEIGHT / 2, 0);
			g_FadeAnim[i].fWidth = 25;
			g_FadeAnim[i].fHeight = SCREEN_HEIGHT;
			g_FadeAnim[i].Type = TEXTYPE_GEAR_CHAIN;
			break;
		case 8:
			g_FadeAnim[i].pos = D3DXVECTOR3(-FADE_ANIM_POS_X - 140, SCREEN_HEIGHT / 2 - 20, 0);
			g_FadeAnim[i].fWidth = 450;
			g_FadeAnim[i].fHeight = 450;
			g_FadeAnim[i].Type = TEXTYPE_WALLGEAR;
			break;
		case 9:
			g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_POS_X + 1240, SCREEN_HEIGHT / 2 + 80, 0);
			g_FadeAnim[i].fWidth = 400;
			g_FadeAnim[i].fHeight = 400;
			g_FadeAnim[i].Type = TEXTYPE_WALLGEAR;
			break;

		}
		g_FadeAnim[i].fAngle = atan2f(g_FadeAnim[i].fWidth, g_FadeAnim[i].fHeight);
		g_FadeAnim[i].fLength = sqrtf(g_FadeAnim[i].fWidth * g_FadeAnim[i].fWidth + g_FadeAnim[i].fHeight * g_FadeAnim[i].fHeight) / 2;
	}
	
	for (int nCnt = 0; nCnt < USE_FADE_POLY; nCnt++)
	{

		//頂点座標の設定
		pVtx[0].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z - (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
		pVtx[0].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z - (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z + (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
		pVtx[1].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z + (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z - g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
		pVtx[2].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z - g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z + g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
		pVtx[3].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z + g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
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
	g_pVtxBuffFade->Unlock();
	g_Fade.bUse = false;
	g_Fade.bFinish = false;
	g_FadeAnimGear[0] = 0.0f;
	g_FadeAnimGear[1] = 0.0f;
}

//===============================================================================
//フェードの終了処理
//===============================================================================
void UninitFade(void)
{
	StopSound();
	for (int i = 0; i < TEXTYPE_MAX; i++)
	{
		//テクスチャの破棄
		if (g_pTextureFade[i] != NULL)
		{
			g_pTextureFade[i]->Release();
			g_pTextureFade[i] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
//===============================================================================
//フェードの更新処理
//===============================================================================
void UpdateFade(void)
{
	if (g_Fade.bUse)
	{
		if (g_Fade.nType == FADE_OUT)
		{
			if (g_Fade.bSoundUse[0] == false)
			{
				PlaySound(SOUND_LABEL_FADE_OPEN);
				g_Fade.bSoundUse[0] = true;
			}
			if (g_FadeAnim[0].pos.x < FADE_ANIM_POS_X)
			{
				g_FadeAnim[0].pos.x += SCREEN_WIDTH / 80;
				g_FadeAnim[2].rot.z += 0.06f;
				g_FadeAnim[4].rot.z += 0.06f;
				g_FadeAnimGear[0] -= 0.025f;
			}
			if (g_FadeAnim[1].pos.x > FADE_ANIM_POS_X)
			{
				g_FadeAnim[1].pos.x -= SCREEN_WIDTH / 80;
				g_FadeAnim[3].rot.z -= 0.06f;
				g_FadeAnim[5].rot.z -= 0.06f;
				g_FadeAnimGear[1] += 0.025f;
			}
			if (g_FadeAnim[0].pos.x >= FADE_ANIM_POS_X && g_FadeAnim[1].pos.x <= FADE_ANIM_POS_X)
			{
				if (g_Fade.bSoundUse[1] == false)
				{
					PlaySound(SOUND_LABEL_FADE_GEAR);
					g_Fade.bSoundUse[1] = true;
				}
				if (g_FadeAnim[8].rot.z > -3.14f * 1.5f)
				{
					g_FadeAnim[8].rot.z -= (3.14f * 0.02f);
					g_FadeAnim[9].rot.z += (3.14f * 0.02f);
				}
				else
				{
					g_Fade.bFinish = true;
				}
			}
		}
		else
		{
			if (g_Fade.bSoundUse[1] == false)
			{
				PlaySound(SOUND_LABEL_FADE_GEAR);
				g_Fade.bSoundUse[1] = true;
			}
			if (g_FadeAnim[8].rot.z < 3.14f * 1.5f)
			{
				g_FadeAnim[8].rot.z += (3.14f * 0.02f);
				g_FadeAnim[9].rot.z -= (3.14f * 0.02f);
			}
			else
			{
				if (g_Fade.bSoundUse[0] == false)
				{
					PlaySound(SOUND_LABEL_FADE_OPEN);
					g_Fade.bSoundUse[0] = true;
				}
				if (g_FadeAnim[0].pos.x > -(SCREEN_WIDTH / 2) + 256)
				{
					g_FadeAnim[0].pos.x -= 25.6f;
					g_FadeAnim[2].rot.z -= 0.06f;
					g_FadeAnim[4].rot.z -= 0.06f;
					g_FadeAnimGear[0] += 0.025f;
				}
				if (g_FadeAnim[1].pos.x < (SCREEN_WIDTH / 2) + (SCREEN_WIDTH - 256))
				{
					g_FadeAnim[1].pos.x += 25.6f;
					g_FadeAnim[3].rot.z += 0.06f;
					g_FadeAnim[5].rot.z += 0.06f;
					g_FadeAnimGear[1] -= 0.025f;
				}
				if (g_FadeAnim[0].pos.x < -(SCREEN_WIDTH / 2) + 256 && g_FadeAnim[1].pos.x >(SCREEN_WIDTH / 2) - 256)
				{
					g_Fade.bUse = false;
				}

			}
		}
		//初期壁とギアの相対座標
		g_FadeAnim[8].pos = g_FadeAnim[0].pos + D3DXVECTOR3(-140, -100, 0);
		g_FadeAnim[9].pos = g_FadeAnim[1].pos + D3DXVECTOR3(120, +160, 0);

		VERTEX_2D* pVtx;	//頂点情報のポインタ

		//頂点バッファをロックして、頂点情報へのポインタを取得
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < USE_FADE_POLY; nCnt++)
		{

			//頂点座標の設定
			pVtx[0].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z - (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
			pVtx[0].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z - (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
			pVtx[0].pos.z = 0.0f;
			pVtx[1].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z + (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
			pVtx[1].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z + (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
			pVtx[1].pos.z = 0.0f;
			pVtx[2].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z - g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
			pVtx[2].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z - g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
			pVtx[2].pos.z = 0.0f;
			pVtx[3].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z + g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
			pVtx[3].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z + g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
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

			if (nCnt == 6 || nCnt == 7)
			{
				//テクスチャ座標の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + g_FadeAnimGear[nCnt - 6]);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + g_FadeAnimGear[nCnt - 6]);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + g_FadeAnimGear[nCnt - 6]);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + g_FadeAnimGear[nCnt - 6]);
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
		g_pVtxBuffFade->Unlock();
		if (g_Fade.bFinish == true)
		{
			g_Fade.bUse = false;
			SetMode(g_Fade.mode);
		}
	}
}

//===============================================================================
//フェードの描画処理
//===============================================================================
void DrawFade(void)
{
	if (g_Fade.bUse)
	{
		LPDIRECT3DDEVICE9 pDevice;
		//デバイスの取得
		pDevice = GetDevice();
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));
		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		for (int i = 0; i < USE_FADE_POLY; i++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureFade[g_FadeAnim[i].Type]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * i,
				2);
		}
	}
}

//===============================================================================
//フェードの設定処理
//===============================================================================
void SetFade(int nType,MODE mode)	//フェードイン/アウト、移行するモード(フェードインなら無視)
{
	if (!g_Fade.bUse)
	{
		g_Fade.bSoundUse[0] = false;
		g_Fade.bSoundUse[1] = false;
		g_Fade.nType = nType;
		g_Fade.bUse = true;
		g_Fade.bFinish = false;
		if (nType == FADE_IN)
		{
			for (int i = 0; i < USE_FADE_POLY; i++)
			{
				g_FadeAnim[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一応初期化
				switch (i)
				{
				case 0:
					g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_POS_X, SCREEN_HEIGHT / 2, 0);
					break;
				case 1:
					g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_POS_X, SCREEN_HEIGHT / 2, 0);
					break;
				case 2:
					g_FadeAnim[i].pos = D3DXVECTOR3(0, 0.0f, 0);
					break;
				case 3:
					g_FadeAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);
					break;
				case 4:
					g_FadeAnim[i].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0);
					break;
				case 5:
					g_FadeAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
					break;
				case 6:
					g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_GEAR_HALFSIZE / 3, SCREEN_HEIGHT / 2, 0);
					break;
				case 7:
					g_FadeAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH - (FADE_ANIM_GEAR_HALFSIZE / 3), SCREEN_HEIGHT / 2, 0);
					break;
	/*			case 8:
					g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_POS_X - 30, SCREEN_HEIGHT / 2 - 20, 0);
					break;
				case 9:
					g_FadeAnim[i].pos = D3DXVECTOR3(300, -200, 0);
					break;*/

				}
				g_FadeAnim[i].fAngle = atan2f(g_FadeAnim[i].fWidth, g_FadeAnim[i].fHeight);
				g_FadeAnim[i].fLength = sqrtf(g_FadeAnim[i].fWidth * g_FadeAnim[i].fWidth + g_FadeAnim[i].fHeight * g_FadeAnim[i].fHeight) / 2;
			}
		}
		else
		{
			g_Fade.mode = mode;
			for (int i = 0; i < USE_FADE_POLY; i++)
			{
				g_FadeAnim[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//一応初期化
				switch (i)
				{
				case 0:
					g_FadeAnim[i].pos = D3DXVECTOR3(-(FADE_ANIM_POS_X), SCREEN_HEIGHT / 2, 0);
					break;
				case 1:
					g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_POS_X + SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0);
					break;
				case 2:
					g_FadeAnim[i].pos = D3DXVECTOR3(0, 0.0f, 0);
					break;
				case 3:
					g_FadeAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);
					break;
				case 4:
					g_FadeAnim[i].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0);
					break;
				case 5:
					g_FadeAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
					break;
				case 6:
					g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_GEAR_HALFSIZE / 3, SCREEN_HEIGHT / 2, 0);
					break;
				case 7:
					g_FadeAnim[i].pos = D3DXVECTOR3(SCREEN_WIDTH - (FADE_ANIM_GEAR_HALFSIZE / 3), SCREEN_HEIGHT / 2, 0);
					break;
		/*		case 8:
					g_FadeAnim[i].pos = D3DXVECTOR3(FADE_ANIM_POS_X - 30, SCREEN_HEIGHT / 2 - 20, 0);
					break;
				case 9:
					g_FadeAnim[i].pos = D3DXVECTOR3(300, -200, 0);
					break;*/

				}
				g_FadeAnim[i].fAngle = atan2f(g_FadeAnim[i].fWidth, g_FadeAnim[i].fHeight);
				g_FadeAnim[i].fLength = sqrtf(g_FadeAnim[i].fWidth * g_FadeAnim[i].fWidth + g_FadeAnim[i].fHeight * g_FadeAnim[i].fHeight) / 2;
			}
		}

		VERTEX_2D* pVtx;	//頂点情報のポインタ
		//頂点バッファをロックして、頂点情報へのポインタを取得
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);


		for (int nCnt = 0; nCnt < USE_FADE_POLY; nCnt++)
		{

			//頂点座標の設定
			pVtx[0].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z - (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
			pVtx[0].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z - (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z + (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
			pVtx[1].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z + (D3DX_PI - g_FadeAnim[nCnt].fAngle)) * g_FadeAnim[nCnt].fLength;
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z - g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
			pVtx[2].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z - g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_FadeAnim[nCnt].pos.x + sinf(g_FadeAnim[nCnt].rot.z + g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
			pVtx[3].pos.y = g_FadeAnim[nCnt].pos.y + cosf(g_FadeAnim[nCnt].rot.z + g_FadeAnim[nCnt].fAngle) * g_FadeAnim[nCnt].fLength;
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
		g_pVtxBuffFade->Unlock();
	}
}

