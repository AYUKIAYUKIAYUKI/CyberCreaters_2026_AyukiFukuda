//============================================================================
// 
// テクスチャマネージャー、ヘッダファイル [texture_manager.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_	// 二重インクルード防止

//****************************************************
// テクスチャマネージャークラス
//****************************************************
class CTexture_Manager final
{
public:

	//****************************************************
	// テクスチャ識別
	//****************************************************
	enum class TYPE
	{
		BG_000 = 0,		// 背景000
		LOGO,			// タイトルロゴ
		NORMAL,			// ノーマルモード
		CHALLENGE,		// チャレンジモード
		SPEECH_N,		// ノーマルふきだし
		SPEECH_C,		// チャレンジふきだし
		CURSOR,			// カーソル
		BG_001,			// 背景001
		ARROW,			// 矢印
		RING,			// リング
		SQUARE_00,		// マス目1
		LEAF_00,		// 葉っぱ00
		LEAF_01,		// 葉っぱ01
		LEAF_02,		// 葉っぱ02
		LEAF_03,		// 葉っぱ03
		LEAF_04,		// 葉っぱ04
		NUMBER_00,		// 数字00
		LASTTIME,		// ラストタイム
		BESTTIME,		// ベストタイム
		LIMITTIME,		// 残り時間
		RECORDDEST,		// 破壊記録
		RECORDBEST,		// 最高記録
		RETRY,			// もう一度
		QUIT,			// やめる
		BACK,			// 戻るマーク
		FAILED,			// 失敗
		CROWN,			// 王冠
		TEXT00,			// テキスト00
		TEXT01,			// テキスト01
		TEXT02,			// テキスト02
		TEXT03,			// テキスト03
		TEXT04,			// テキスト04
		TEXT05,			// テキスト05
		TEXT06,			// テキスト06
		TEXT07,			// テキスト07
		TEXT08,			// テキスト08
		TEXT09,			// テキスト09
		TEXT10,			// テキスト10
		TEXT11,			// テキスト11
		TEXT12,			// テキスト12
		LHAND,			// 左手
		LHAND_SL,		// 左手SL
		LHAND_SR,		// 左手SR
		LHAND_SU,		// 左手SU
		LHAND_SD,		// 左手SD
		LHAND_JL,		// 左手JL
		LHAND_JR,		// 左手JR
		LHAND_JU,		// 左手JU
		LHAND_JD,		// 左手JD
		RHAND,			// 右手
		RHAND_A,		// 右手A
		RHAND_B,		// 右手B
		RHAND_X,		// 右手X
		RHAND_Y,		// 右手Y
		CNT,			// コントローラー
		CNT_M0,			// コントローラーM0
		CNT_M1,			// コントローラーM1
		CNT_M2,			// コントローラーM2
		CNT_M3,			// コントローラーM3
		CNT_B0,			// コントローラーB0
		CNT_B1,			// コントローラーB1
		BOARD_0,		// ボード0
		BOARD_1,		// ボード1
		BOARD_2,		// ボード3
		SPEECH,			// ふきだし
		MAX,
	};

	HRESULT Load();	// テクスチャ読込
	void Release();	// 解放

	LPDIRECT3DTEXTURE9 GetTexture(TYPE type);	// テクスチャを取得

	static CTexture_Manager* GetInstance();	// テクスチャマネージャーを取得

private:

	CTexture_Manager();		// コンストラクタ
	~CTexture_Manager();	// デストラクタ

	void Create();	// 生成
	void Unload();	// テクスチャ破棄

	LPDIRECT3DTEXTURE9 m_apTexTemp[static_cast<int>(TYPE::MAX)];	// テクスチャ情報

	static CTexture_Manager* m_pInstance;	// テクスチャマネージャー
};

#endif // _TEXTURE_MANAGER_H_