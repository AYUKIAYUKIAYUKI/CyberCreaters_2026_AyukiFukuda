//============================================================================
// 
// Xモデルマネージャー、ヘッダファイル [model_X_manager.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _MODEL_X_MANAGER_H_
#define _MODEL_X_MANAGER_H_	// 二重インクルード防止

//****************************************************
// Xモデルマネージャークラス
//****************************************************
class CModel_X_Manager final
{
public:

	//****************************************************
	// モデル識別
	//****************************************************
	enum class TYPE
	{
		KARIHAIKEI = 0,		// 仮背景
		ROOM,				// ROOM
		MONITOR,			// モニター
		VHS,				// VHS
		BOOKSELF,			// 本棚
		SPEAKER,			// スピーカー
		SPEAKER_BIG,		// でかスピーカー
		GRAMOPHONE,			// 蓄音機
		INDOOR_PLANTS,		// 観葉植物
		POSTER,				// ポスター
		MEMO_00,			// メモ00
		MEMO_01,			// メモ01
		LAMP,				// ランプ
		TV_STAND,			// テレビ台
		PLAYER_000,			// プレイヤー000
		PLAYER_001,			// プレイヤー001
		PLAYER_002,			// プレイヤー002
		PLAYER_003,			// プレイヤー003
		PLAYER_004,			// プレイヤー004
		PLAYER_005,			// プレイヤー005
		PLAYER_006,			// プレイヤー006
		PLAYER_007,			// プレイヤー007
		BLOCK_000,			// ブロック000
		IMPACT,				// 衝撃
		DESTRUCTIBLE,		// 可壊ブロック
		DEST_BIG,			// 可壊でかブロック
		DEST_BIG_DAMAGE,	// 可壊でかブロック(ダメージ)
		RUBBLE_00,			// がれき00
		RUBBLE_01,			// がれき01
		RUBBLE_BIG_00,		// でかがれき00
		RUBBLE_BIG_01,		// でかがれき01
		SPIKES,				// とげブロック
		SPIKES_MOVE,		// とげ移動ブロック
		ENEMY,				// エネミー
		BULLET_CORE,		// 弾 - 核
		START,				// スタート
		GOAL,				// ゴール
		ACHIEVE,			// アチーブ
		ACHIEVE_LOST,		// アチーブ(取得)
		LINE_X,				// X軸
		LINE_Y,				// Y軸
		RIPPLE00,			// 波紋00
		RIPPLE01,			// 波紋01
		RIPPLE02,			// 波紋02
		RIPPLE03,			// 波紋03
		STAR00,				// 星00
		STAR01,				// 星01
		PARTICLE00,			// 粒子00
		PARTICLE01,			// 粒子01
		PARTICLE02,			// 粒子02
		PARTICLE03,			// 粒子03
		CURSOR,				// カーソル
		BARRIER,			// バリア
		BARRIER_ANCHOR,		// バリアアンカー
		MAX,
	};

	//****************************************************
	// モデル情報の構造体の定義
	//****************************************************
	struct MODEL
	{
		D3DXVECTOR3 size;			// サイズ
		LPD3DXMESH pMesh;			// メッシュ情報
		LPD3DXBUFFER pBuffMat;		// マテリアル情報
		DWORD dwNumMat;				// マテリアルの数
		LPDIRECT3DTEXTURE9* ppTex;	// テクスチャ情報
	};

	HRESULT Load();	// モデル読込
	void Release();	// 解放

	MODEL* GetModel(TYPE type);	// モデルを取得

	static CModel_X_Manager* GetInstance();	// Xモデルマネージャーを取得

private:

	CModel_X_Manager();		// デフォルトコンストラクタ
	~CModel_X_Manager();	// デストラクタ

	void Create();									// 生成
	D3DXVECTOR3 ImportSize(std::string filename);	// サイズ読み込み
	void Unload();									// モデル破棄

	MODEL m_apModelTemp[static_cast<int>(TYPE::MAX)];	// Xモデル情報

	static CModel_X_Manager* m_pInstnce;	// Xモデルマネージャー
};

#endif // _MODEL_X_MANAGER_H_