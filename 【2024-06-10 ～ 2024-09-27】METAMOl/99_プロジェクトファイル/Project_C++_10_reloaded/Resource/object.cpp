//============================================================================
// 
// オブジェクト管理 [object.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "object.h"

// デバッグ表示用
#include "renderer.h"

//****************************************************
// 静的メンバの初期化
//****************************************************
CObject* CObject::m_apFind[MAX_OBJ];							// 検索されたオブジェクト保持用
int CObject::m_nNumAll = 0;										// オブジェクト総数
CObject* CObject::m_pTop[static_cast<int>(LAYER::MAX)] = {};	// 先頭オブジェクトのポインタ
CObject* CObject::m_pCur[static_cast<int>(LAYER::MAX)] = {};	// 終端オブジェクトのポインタ

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CObject::CObject() :
	m_nPriority{ static_cast<int>(LAYER::MAX) - 1 },	// 描画優先度
	m_pPrev{ nullptr },									// 前のオブジェクトのポインタ
	m_pNext{ nullptr },									// 次のオブジェクトのポインタ
	m_type(TYPE::NONE),									// タイプ識別
	m_bDeath{ false }									// 死亡フラグ
{
	// このオブジェクトをリストに登録
	if (m_pCur[m_nPriority] == nullptr)
	{ // 終端オブジェクトが無い (オブジェクトが1つも存在しない)

		// このオブジェクトを先頭と終端に登録
		m_pTop[m_nPriority] = this;
		m_pCur[m_nPriority] = this;
	}
	else
	{ // 終端オブジェクトがある

		// 現在の終端をこのオブジェクトの前として登録
		m_pPrev = m_pCur[m_nPriority];

		// 新たな終端としてこのオブジェクトを登録
		m_pCur[m_nPriority] = this;

		// 前のオブジェクトの次にこのオブジェクトを登録
		m_pPrev->m_pNext = this;
	}

	// 総数をカウントアップ
	m_nNumAll++;

	// オブジェクトの生成限度を超えたら
	if (m_nNumAll > MAX_OBJ)
	{
		assert(false);
	}
}

//============================================================================
// プライオリティ指定コンストラクタ
//============================================================================
CObject::CObject(int nPriority) :
	m_nPriority{ nPriority },	// 描画優先度
	m_pPrev{ nullptr },			// 前のオブジェクトのポインタ
	m_pNext{ nullptr },			// 次のオブジェクトのポインタ
	m_type(TYPE::NONE),			// タイプ識別
	m_bDeath{ false }			// 死亡フラグ
{
	// このオブジェクトをリストに登録
	if (m_pCur[nPriority] == nullptr)
	{ // 終端オブジェクトが無い (オブジェクトが1つも存在しない)
		
		// このオブジェクトを先頭と終端に登録
		m_pTop[nPriority] = this;
		m_pCur[nPriority] = this;
	}
	else
	{ // 終端オブジェクトがある

		// 現在の終端をこのオブジェクトの前として登録
		m_pPrev = m_pCur[nPriority];

		// 新たな終端としてこのオブジェクトを登録
		m_pCur[nPriority] = this;

		// 前のオブジェクトの次にこのオブジェクトを登録
		m_pPrev->m_pNext = this;
	}

	// 総数をカウントアップ
	m_nNumAll++;

	// オブジェクトの生成限度を超えたら
	if (m_nNumAll > 99999999)
	{
		assert(false);
	}
}

//============================================================================
// デストラクタ
//============================================================================
CObject::~CObject()
{
	
}

//============================================================================
// 解放設定
//============================================================================
void CObject::SetRelease()
{
	if (!m_bDeath)
	{
		m_bDeath = true;
	}
}

//============================================================================
// 解放処理
//============================================================================
void CObject::Release()
{
	int nPriority = m_nPriority;	// プライオリティをコピーしておく

	if (m_pPrev == nullptr)
	{ // 前のオブジェクトが無い (このオブジェクトが先頭)

		if (m_pNext == nullptr)
		{ // 次のオブジェクトが無い (オブジェクトが全て無くなる)
			
			m_pTop[nPriority] = nullptr;	// 先頭オブジェクトのポインタを初期化
			m_pCur[nPriority] = nullptr;	// 終端オブジェクトのポインタを初期化
		}
		else
		{ // 次のオブジェクトはある

			// 新たな先頭として次のオブジェクトを登録
			m_pTop[nPriority] = m_pNext;

			// 次のオブジェクトの前のポインタを初期化
			m_pNext->m_pPrev = nullptr;
		}
	}
	else
	{ // 前のオブジェクトがある

		if (m_pNext == nullptr)
		{ // 次のオブジェクトが無い (このオブジェクトが終端)

			// 新たな終端として前のオブジェクト登録
			m_pCur[nPriority] = m_pPrev;

			// 前のオブジェクトの次のポインタを初期化
			/* そもそも「このオブジェクトの次のポインタ(m_pNext)を渡す」という行為なら、中身の有無にかかわらずつながるのでは */
			m_pPrev->m_pNext = nullptr;
		}
		else
		{ // 次のオブジェクトもある

			// 前のオブジェクトの次にこのオブジェクトの次を登録
			m_pPrev->m_pNext = m_pNext;

			// 次のオブジェクトの前に
			m_pNext->m_pPrev = m_pPrev;
		}
	}

	Uninit();		// 終了処理
	delete this;	// メモリを解放
	m_nNumAll--;	// 総数をカウントダウン
}

//============================================================================
// タイプを取得
//============================================================================
CObject::TYPE CObject::GetType()
{
	return m_type;
}

//============================================================================
// タイプを設定
//============================================================================
void CObject::SetType(TYPE type)
{
	m_type = type;
}

//============================================================================
// 前のポインタを取得
//============================================================================
CObject* CObject::GetPrev()
{
	return m_pPrev;
}

//============================================================================
// 次のポインタを取得
//============================================================================
CObject* CObject::GetNext()
{
	return m_pNext;
}

//============================================================================
// 全解放処理
//============================================================================
void CObject::ReleaseAll()
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		// 先頭オブジェクトのポインタをコピー
		CObject* pObj = m_pTop[nCntPriority];

		// 次のオブジェクトが無くなるまで
		while (pObj != nullptr)
		{
			// 次のオブジェクトのポインタをコピー
			CObject* pNext = pObj->m_pNext;

			// 解放処理
			pObj->Release();

			// このオブジェクトを次のポインタで上書き
			pObj = pNext;
		}
	}
}

//============================================================================
// 背景のみ解放
//============================================================================
void CObject::ReleaseBG()
{
	// 描画優先度は背景のみ
	int nPriority = static_cast<int>(LAYER::BG);

	// 先頭オブジェクトのポインタをコピー
	CObject* pObj = m_pTop[nPriority];

	// 次のオブジェクトが無くなるまで
	while (pObj != nullptr)
	{
		// 次のオブジェクトのポインタをコピー
		CObject* pNext = pObj->m_pNext;

		// 解放処理
		pObj->Release();

		// このオブジェクトを次のポインタで上書き
		pObj = pNext;
	}
}

//============================================================================
// スクリーン画面内の解放
//============================================================================
void CObject::ReleaseScreen()
{
	for (int nCntPriority = static_cast<int>(LAYER::BACK); nCntPriority < static_cast<int>(LAYER::UI); nCntPriority++)
	{
		// 先頭オブジェクトのポインタをコピー
		CObject* pObj = m_pTop[nCntPriority];

		// 次のオブジェクトが無くなるまで
		while (pObj != nullptr)
		{
			// 次のオブジェクトのポインタをコピー
			CObject* pNext = pObj->m_pNext;

			// 解放処理
			pObj->Release();

			// 次のオブジェクトのポインタをコピー
			pObj = pNext;
		}
	}
}

//============================================================================
// UIのみ解放
//============================================================================
void CObject::ReleaseUI()
{
	// 描画優先度はUIのみ
	int nPriority = static_cast<int>(LAYER::UI);

	// 先頭オブジェクトのポインタをコピー
	CObject* pObj = m_pTop[nPriority];

	// 次のオブジェクトが無くなるまで
	while (pObj != nullptr)
	{
		// 次のオブジェクトのポインタをコピー
		CObject* pNext = pObj->m_pNext;

		// 解放処理
		pObj->Release();

		// このオブジェクトを次のポインタで上書き
		pObj = pNext;
	}
}

//============================================================================
// 全更新処理
//============================================================================
void CObject::UpdateAll()
{
#ifdef _DEBUG
	// オブジェクト数を表示
	CRenderer::GetInstance()->SetDebugString("現在のオブジェクト数:" + std::to_string(m_nNumAll));
#endif	// _DEBUG

	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		// 先頭オブジェクトのポインタをコピー
		CObject* pObj = m_pTop[nCntPriority];

		// 次のオブジェクトが無くなるまで
		while (pObj != nullptr)
		{
			// 次のオブジェクトのポインタをコピー
			CObject* pNext = pObj->m_pNext;

			// 更新処理
			pObj->Update();

			// 次のオブジェクトのポインタをコピー
			pObj = pNext;
		}
	}
}

//============================================================================
// 全後更新処理
//============================================================================
void CObject::LateUpdateAll()
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		// 先頭オブジェクトのポインタをコピー
		CObject* pObj = m_pTop[nCntPriority];

		// 次のオブジェクトが無くなるまで
		while (pObj != nullptr)
		{
			// 次のオブジェクトのポインタをコピー
			CObject* pNext = pObj->m_pNext;

			// 死亡フラグが出ていたら
			if (pObj->m_bDeath)
			{
				// 解放処理
				pObj->Release();
			}

			// 次のオブジェクトのポインタをコピー
			pObj = pNext;
		}
	}
}

//============================================================================
// 全描画処理
//============================================================================
void CObject::DrawAll()
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		// 先頭オブジェクトのポインタをコピー
		CObject* pObj = m_pTop[nCntPriority];

		// 次のオブジェクトが無くなるまで
		while (pObj != nullptr)
		{
			// 次のオブジェクトのポインタをコピー
			CObject* pNext = pObj->m_pNext;

			// 描画処理
			pObj->Draw();

			// 次のオブジェクトのポインタをコピー
			pObj = pNext;
		}
	}
}

//============================================================================
// 背景オブジェクトのみ描画
//============================================================================
void CObject::DrawBG()
{
	// 描画優先度は背景のみ
	int nPriority = static_cast<int>(LAYER::BG);

	// 先頭オブジェクトのポインタをコピー
	CObject* pObj = m_pTop[nPriority];

	// 次のオブジェクトが無くなるまで
	while (pObj != nullptr)
	{
		// 次のオブジェクトのポインタをコピー
		CObject* pNext = pObj->m_pNext;

		// 描画処理
		pObj->Draw();

		// 次のオブジェクトのポインタをコピー
		pObj = pNext;
	}
}

//============================================================================
// スクリーン画面内の描画
//============================================================================
void CObject::DrawScreen()
{
	for (int nCntPriority = static_cast<int>(LAYER::BACK); nCntPriority < static_cast<int>(LAYER::UI); nCntPriority++)
	{
		// 先頭オブジェクトのポインタをコピー
		CObject* pObj = m_pTop[nCntPriority];

		// 次のオブジェクトが無くなるまで
		while (pObj != nullptr)
		{
			// 次のオブジェクトのポインタをコピー
			CObject* pNext = pObj->m_pNext;

			// 描画処理
			pObj->Draw();

			// 次のオブジェクトのポインタをコピー
			pObj = pNext;
		}
	}
}

//============================================================================
// UIオブジェクトのみ描画
//============================================================================
void CObject::DrawUI()
{
	// 描画優先度はUIのみ
	int nPriority = static_cast<int>(LAYER::UI);

	// 先頭オブジェクトのポインタをコピー
	CObject* pObj = m_pTop[nPriority];

	// 次のオブジェクトが無くなるまで
	while (pObj != nullptr)
	{
		// 次のオブジェクトのポインタをコピー
		CObject* pNext = pObj->m_pNext;

		// 描画処理
		pObj->Draw();

		// 次のオブジェクトのポインタをコピー
		pObj = pNext;
	}
}

//============================================================================
// 先頭オブジェクトのポインタ取得
//============================================================================
CObject* CObject::GetObject(int nPriority)
{
	return m_pTop[nPriority];
}

//============================================================================
// 特定タイプのオブジェクトを探す
//============================================================================
CObject* CObject::FindObject(TYPE type)
{
	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		// 先頭オブジェクトのポインタをコピー
		CObject* pObj = m_pTop[nCntPriority];

		// 次のオブジェクトが無くなるまで
		while (pObj != nullptr)
		{
			if (pObj->GetType() == type)
			{
				// タイプ一致なら返す
				return pObj;
			}

			// 次のオブジェクトのポインタをコピー
			pObj = pObj->m_pNext;
		}
	}

	return nullptr;
}

//============================================================================
// 特定タイプのオブジェクトをすべて探す
//============================================================================
CObject** CObject::FindAllObject(TYPE type)
{
	// 検索の前に、保持していた情報を初期化
	for (int i = 0; i < MAX_OBJ; i++)
	{
		m_apFind[i] = nullptr;
	}

	// 検索した順番
	int nCntFind = 0;

	for (int nCntPriority = 0; nCntPriority < static_cast<int>(LAYER::MAX); nCntPriority++)
	{
		// 先頭オブジェクトのポインタをコピー
		CObject* pObj = m_pTop[nCntPriority];

		// 次のオブジェクトが無くなるまで
		while (pObj != nullptr)
		{
			if (pObj->GetType() == type)
			{
				// タイプ一致なら保持
				m_apFind[nCntFind] = pObj;

				// 検索の順番をカウントアップ
				nCntFind++;
			}

			// 次のオブジェクトのポインタをコピー
			pObj = pObj->m_pNext;
		}
	}

	return m_apFind;
}