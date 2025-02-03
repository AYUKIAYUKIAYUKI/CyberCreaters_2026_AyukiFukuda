//============================================================================
// 
// オブジェクト管理、ヘッダファイル [object.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_	// 二重インクルード防止

//****************************************************
// オブジェクトクラス
//****************************************************
class CObject
{
public:

	static const int MAX_OBJ = 512;	// オブジェクトの最大数

	//****************************************************
	// オブジェクトの種類識別
	//****************************************************
	enum class TYPE
	{
		NONE = 0,		// 無し
		PLAYER,			// プレイヤー
		DUMMY,			// ダミー
		ENEMY,			// エネミー
		BULLET,			// 弾
		BLOCK,			// ブロック
		DESTRUCTIBLE,	// 可壊ブロック
		DEST_BIG,		// 可壊でかブロック
		SPIKES,			// トゲブロック
		SPIKES_MOVE,	// トゲ移動ブロック
		ITEM,			// アイテム
		START,			// スタート
		GOAL,			// ゴール
		ACHIEVE,		// アチーブ
		SQUARE,			// マス目
		TIMER,			// タイム
		RECORD,			// レコード
		BARRIER,		// バリア
		BARRIER_ANCHOR,	// バリアアンカー
		MAX,
	};

	//****************************************************
	// オブジェクトのレイヤー識別
	//****************************************************
	enum class LAYER
	{
		NONE = 0,	// 無し
		BG,			// 背景
		BACK,		// 後方
		MIDDLE,		// 中央
		FRONT,		// 前方
		UI,			// UI
		MAX,
	};

	CObject();												// デフォルトコンストラクタ
	CObject(int nPriority = static_cast<int>(LAYER::NONE));	// プライオリティ指定コンストラクタ
	virtual ~CObject() = 0;									// デストラクタ

	virtual HRESULT Init() = 0;	// 初期設定
	virtual void Uninit() = 0;	// 終了処理
	virtual void Update() = 0;	// 更新処理
	virtual void Draw() = 0;	// 描画処理
	void SetRelease();			// 解放予約設定
	void Release();				// 個別解放処理

	TYPE GetType();				// タイプを取得
	void SetType(TYPE type);	// タイプを設定

	CObject* GetPrev();	// 前のオブジェクトのポインタを取得
	CObject* GetNext();	// 次のオブジェクトのポインタを取得

	static void ReleaseAll();		// 全オブジェクト解放処理
	static void ReleaseBG();		// 背景オブジェクトのみ解放処理
	static void ReleaseScreen();		// スクリーン画面内の解放処理
	static void ReleaseUI();		// UIオブジェクトのみ解放処理
	static void UpdateAll();		// 全オブジェクト更新処理
	static void LateUpdateAll();	// 全オブジェクト後更新処理
	static void DrawAll();			// 全オブジェクト描画処理
	static void DrawBG();			// 背景オブジェクトのみ描画
	static void DrawScreen();		// スクリーン画面内の描画
	static void DrawUI();			// UIオブジェクトのみ描画

	static CObject* GetObject(int nPriority);	// 先頭オブジェクトのポインタ取得
	static CObject* FindObject(TYPE type);		// 特定タイプのオブジェクト探す
	static CObject** FindAllObject(TYPE type);	// 特定タイプのオブジェクトをすべて探す

private:

	static CObject* m_apFind[MAX_OBJ];						// 検索されたオブジェクト保持用
	static int m_nNumAll;									// オブジェクト総数
	static CObject* m_pTop[static_cast<int>(LAYER::MAX)];	// 先頭オブジェクトのポインタ
	static CObject* m_pCur[static_cast<int>(LAYER::MAX)];	// 終端オブジェクトのポインタ

	int m_nPriority;	// 描画優先度
	CObject* m_pPrev;	// 前のオブジェクトのポインタ
	CObject* m_pNext;	// 次のオブジェクトのポインタ
	TYPE m_type;		// タイプ識別 
	bool m_bDeath;		// 死亡フラグ
};

#endif // _OBJECT_H_