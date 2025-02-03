//============================================================================
// 
// 疑似スクリーン、ヘッダファイル [fakescreen.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _FAKESCREEN_H_
#define _FAKESCREEN_H_	// 二重インクルード防止

//****************************************************
// インクルードファイル
//****************************************************
#include "scene.h"
#include "game_manager.h"

//****************************************************
// 疑似スクリーンクラス
//****************************************************
class CFakeScreen final
{
public:

	void Create();								// 生成
	HRESULT Init();								// 初期設定
	void Release();								// 解放
	void Uninit();								// 終了処理
	void Update();								// 更新処理
	void Draw();								// 描画処理
	void SetFade(CScene::MODE mode);			// モード設定
	void SetWave(CGameManager::PHASE phase);	// ウェーブ設定
	void StopWave(CGameManager::PHASE phase);	// ウェーブ停止&フェーズ移行
	void StopWave();							// ウェーブ停止

	LPDIRECT3DTEXTURE9 GetTexture();	// テクスチャ情報を取得
	LPDIRECT3DSURFACE9 GetSurface();	// サーフェイス情報を取得

	static CFakeScreen* GetInstance();	// 疑似スクリーンを取得

private:

	CFakeScreen();	// デフォルトコンストラクタ
	~CFakeScreen();	// デストラクタ

	static const int SPLIT_ALONG_X_AXIS;	// X軸方向の分割数
	static const int SPLIT_ALONG_Y_AXIS;	// Y軸方向の分割数

	void CalcMesh();			// メッシュ情報の計算
	HRESULT CreateVtxBuff();	// 頂点バッファの生成
	HRESULT CreateIdxBuff();	// インデックスバッファの生成
	HRESULT CreateTex();		// テクスチャの生成
	void FadeOut();				// フェードアウト
	void FadeIn();				// フェードイン
	void WaveOut();				// ウェーブアウト
	void Waving();				// ウェーブ継続
	void WaveIn();				// ウェーブイン
	void SetVtx();				// 頂点情報の設定

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	// インデックスバッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTex;			// テクスチャ情報のポインタ
	LPDIRECT3DSURFACE9 m_pSurface;		// サーフェイス情報のポインタ
	int m_nNumVtx;						// 頂点数
	int m_nNumPolygon;					// ポリゴン数
	int m_nNumDegenerated;				// 縮退ポリゴン数
	int m_nNumIndex;					// インデックス数宇
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_size;					// サイズ
	CScene::MODE m_NextMode;			// 次のモード
	CGameManager::PHASE m_NextPhase;	// 次のフェーズ
	bool m_bFadeOut;					// フェードアウト判定
	bool m_bFadeIn;						// フェードイン判定
	bool m_bWaveOut;					// ウェーブアウト判定
	bool m_bWaving;						// ウェーブ継続判定
	bool m_bWaveIn;						// ウェーブイン判定
	float m_fBrightness;				// 明度
	float m_fPosDistortion;				// 座標変動用
	float m_fAddDistortion;				// ゆがみ増加量

	static CFakeScreen* m_pInstance;	// 疑似スクリーン
};

#endif // _FAKESCREEN_H_