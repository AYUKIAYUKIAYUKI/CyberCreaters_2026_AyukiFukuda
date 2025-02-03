//============================================================================
// 
// ステージメーカー [stagemaker.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "stagemaker.h"
#include "utility.h"

// キーボード取得用
#include "manager.h"

// デバッグ表示用
#include "renderer.h"

// オブジェクト配置用
#include "achievement.h"
#include "barrier_anchor.h"
#include "block.h"
#include "block_destructible.h"
#include "block_destructible_big.h"
#include "block_spikes.h"
#include "block_spikes_move.h"
#include "dummy.h"
#include "enemy.h"
#include "goal.h"
#include "line.h"
#include "start.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
CStageMaker* CStageMaker::m_pInstance = nullptr;	// ステージメーカーのポインタ

//============================================================================
// 生成
//============================================================================
void CStageMaker::Create()
{
	if (m_pInstance != nullptr)
	{ // 二重生成禁止
		assert(false);
	}

	// インスタンスを生成
	m_pInstance = DBG_NEW CStageMaker{};
}

//============================================================================
// 初期設定
//============================================================================
void CStageMaker::Init()
{

}

//============================================================================
// 解放
//============================================================================
void CStageMaker::Release()
{
	if (m_pInstance != nullptr)
	{
		// 終了処理
		m_pInstance->Uninit();

		// メモリを解放
		delete m_pInstance;

		// ポインタを初期化
		m_pInstance = nullptr;
	}
}

//============================================================================
// 終了処理
//============================================================================
void CStageMaker::Uninit()
{

}

//============================================================================
// 更新処理
//============================================================================
void CStageMaker::Update()
{
	// 操作
	Control();

	// モデルパターン譲渡用
	int nPattern = 0;

	// 配置モードなら現在のモデル、編集モードならそれ以外を指定
	m_bModify ? nPattern = -1 : nPattern = m_nPattern;
	
	// モデルを設定
	m_pDummy->ChangeModel(nPattern);
}

//============================================================================
// チャレンジステージ読み込み
//============================================================================
void CStageMaker::Import()
{
	// ステージ保存情報を展開
	std::ifstream Import("Data\\TXT\\STAGE\\Stage_CH.txt");

	if (!Import)
	{ // 展開に失敗
		assert(false);
	}

	// 文章格納先
	std::string str;

	// テキストを読み取る
	while (std::getline(Import, str))
	{
		// 座標格納先
		D3DXVECTOR3 pos = {};

		// 数値となる文字格納先
		std::string str_pos[3];

		for (int i = 0; i < 3; i++)
		{
			// 数値部分のみ抽出する
			str_pos[i] = str.substr(str.find(":") + 1, str.find(",") - (str.find(":") + 1));

			// 不必要になった部分を削除する
			str.erase(0, str.find(",") + 1);
		}

		// 抽出した数値を座標に変換
		pos.x = std::stof(str_pos[0]);
		pos.y = std::stof(str_pos[1]);
		pos.z = std::stof(str_pos[2]);

		// 種類を識別する文字格納先
		std::string str_type;

		// 種類を抽出する
		str_type = str.substr(str.find(":") + 1, str.find(",") - (str.find(":") + 1));

		// 種類に応じて生成する
		if (str_type == "block")
		{ // ブロック
			CBlock::Create(pos);
		}
		else if (str_type == "destructible")
		{ // 可壊ブロック
			CBlockDestructible::Create(pos);
		}
		else if (str_type == "dest_big")
		{ // 可壊でかブロック
			CBlockDestructibleBig::Create(pos);
		}
		else if (str_type == "spikes")
		{ // とげブロック
			CBlockSpikes::Create(pos);
		}
		else if (str_type == "spikes_move")
		{ // とげ移動ブロック
			float fAngleInit{ std::stof(str.substr(str.find("i:") + 2, str.find(","))) };
			float fAdder{ std::stof(str.substr(str.find("a:") + 2, str.find(","))) };
			float fCoeff{ std::stof(str.substr(str.find("c:") + 2, str.find(","))) };
			CBlockSpikesMove::Create(pos, fAngleInit, fAdder, fCoeff);
		}
		else if (str_type == "enemy")
		{ // エネミー
			CEnemy::Create(pos);
		}
		else if (str_type == "start")
		{ // スタート
			CStart::Create(pos);
		}
		else if (str_type == "goal")
		{ // ゴール
			CGoal::Create(pos);
		}
		else if (str_type == "archieve")
		{ // アチーブ
			CAchieve::Create(pos);
		}
		else if (str_type == "anchor")
		{ // バリアアンカー
			CBarrier_Anchor::Create(pos);
		}
		else
		{ // 不明
			assert(false);
		}
	}

	Import.close();	// ファイルを閉じる
}

//============================================================================
// ステージ読み込み
//============================================================================
void CStageMaker::Import(std::string path)
{
	// ステージ保存情報を展開
	std::ifstream Import(path);

	if (!Import)
	{ // 展開に失敗
		assert(false);
	}

	// 文章格納先
	std::string str;

	// テキストを読み取る
	while (std::getline(Import, str))
	{
		// 座標格納先
		D3DXVECTOR3 pos = {};

		// 数値となる文字格納先
		std::string str_pos[3];

		for (int i = 0; i < 3; i++)
		{
			// 数値部分のみ抽出する
			str_pos[i] = str.substr(str.find(":") + 1, str.find(",") - (str.find(":") + 1));

			// 不必要になった部分を削除する
			str.erase(0, str.find(",") + 1);
		}

		// 抽出した数値を座標に変換
		pos.x = std::stof(str_pos[0]);
		pos.y = std::stof(str_pos[1]);
		pos.z = std::stof(str_pos[2]);

		// 種類を識別する文字格納先
		std::string str_type;

		// 種類を抽出する
		str_type = str.substr(str.find(":") + 1, str.find(",") - (str.find(":") + 1));

		// 種類に応じて生成する
		if (str_type == "block")
		{ // ブロック
			CBlock::Create(pos);
		}
		else if (str_type == "destructible")
		{ // 可壊ブロック
			CBlockDestructible::Create(pos);
		}
		else if (str_type == "dest_big")
		{ // 可壊でかブロック
			CBlockDestructibleBig::Create(pos);
		}
		else if (str_type == "spikes")
		{ // とげブロック
			CBlockSpikes::Create(pos);
		}
		else if (str_type == "spikes_move")
		{ // とげ移動ブロック
			float fAngleInit{ std::stof(str.substr(str.find("i:") + 2, str.find(","))) };
			float fAdder{ std::stof(str.substr(str.find("a:") + 2, str.find(","))) };
			float fCoeff{ std::stof(str.substr(str.find("c:") + 2, str.find(","))) };
			CBlockSpikesMove::Create(pos, fAngleInit, fAdder, fCoeff);
		}
		else if (str_type == "enemy")
		{ // エネミー
			CEnemy::Create(pos);
		}
		else if (str_type == "start")
		{ // スタート
			CStart::Create(pos);
		}
		else if (str_type == "goal")
		{ // ゴール
			CGoal::Create(pos);
		}
		else if (str_type == "archieve")
		{ // アチーブ
			CAchieve::Create(pos);
		}
		else if (str_type == "anchor")
		{ // バリアアンカー
			CBarrier_Anchor::Create(pos);
		}
		else
		{ // 不明
			assert(false);
		}
	}

	Import.close();	// ファイルを閉じる
}

//============================================================================
// 配置物の種類を参照
//============================================================================
int& CStageMaker::GetPatternRef()
{
	return m_nPattern;
}

//============================================================================
// 取得
//============================================================================
CStageMaker* CStageMaker::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		// 生成
		m_pInstance->Create();
	}

	return m_pInstance;
}

//============================================================================
// コンストラクタ
//============================================================================
CStageMaker::CStageMaker() :
	m_nPattern{ 0 },		// 構造物の種類識別
	m_fAngleInit{ 0.0f },	// 初期角度
	m_fAdder{ 0.0f },		// 増加量
	m_fCoeff{ 1.0f },		// 反映係数
	m_bModify{ false },		// 編集切り替え
	m_nID{ 0 },				// 編集する構造物を識別
	m_pDummy{ nullptr }		// 構造物のダミー情報
{
	// ステージデバッグモードのみ
	if (CManager::GetScene()->GetMode() == CScene::MODE::STAGE)
	{
		// 構造物のダミーを生成
		m_pDummy = CDummy::Create();

		// ダミー取得失敗
		if (!m_pDummy)
		{
			assert(false);
		}

		// グリッドラインを生成
		CLine::CreateGrid();
	}
}

//============================================================================
// デストラクタ
//============================================================================
CStageMaker::~CStageMaker()
{

}

//============================================================================
// 操作
//============================================================================
void CStageMaker::Control()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_F2))
	{
		// セーフチェック用
		bool bSafe{ true };

		// スタートタイプのオブジェクトを取得
		CObject* pStart = CObject::FindObject(CObject::TYPE::START);

		// ゴールタイプのオブジェクトを取得
		CObject* pGoal = CObject::FindObject(CObject::TYPE::GOAL);

		// アチーブタイプのオブジェクトを取得
		CObject* pAchieve = CObject::FindObject(CObject::TYPE::ACHIEVE);

		// バリアアンカータグをすべて取得
		CObject** pObject{ CObject::FindAllObject(CObject::TYPE::BARRIER_ANCHOR) };

		// オブジェクト数をカウント
		int nCntObj{ 0 };

		for (nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// オブジェクトの情報が無くなったら終了
			if (pObject[nCntObj] == nullptr)
			{
				break;
			}
		}

		// スタートオブジェクトの発見に失敗
		if (pStart == nullptr)
		{
			bSafe = false;
			CRenderer::GetInstance()->SetTimeString("【スタートを配置してください！】", 180);
		}

		// ゴールオブジェクトの発見に失敗
		if (pGoal == nullptr)
		{
			bSafe = false;
			CRenderer::GetInstance()->SetTimeString("【ゴールを配置してください！】", 180);
		}

		// アチーブオブジェクトの発見に失敗
		if (pAchieve == nullptr)
		{
			bSafe = false;
			CRenderer::GetInstance()->SetTimeString("【アチーブを配置してください！】", 180);
		}
		
		// バリアアンカーオブジェクトの発見に失敗
		if (nCntObj < 2)
		{
			bSafe = false;
			CRenderer::GetInstance()->SetTimeString("【バリアアンカーを2つ配置してください！】", 180);
		}

		if (bSafe)
		{
			// ステージ書き出し
			Export();
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_F3))
	{
		// ステージ読み込み (仮)
		Import("Data\\TXT\\stage.txt");
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_SPACE))
	{
		// 編集切り替え
		m_bModify = !m_bModify;
	}

	if (!m_bModify)
	{
		CRenderer::GetInstance()->SetDebugString("現在のモード -> 配置");

		// ダミー操作
		m_pDummy->Control();

		// 操作反映
		m_pDummy->Update();

		if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
		{
			// 設置
			Register();
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD4))
		{
			m_nPattern > 0 ? m_nPattern-- : m_nPattern = 9;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD6))
		{
			m_nPattern < 9 ? m_nPattern++ : m_nPattern = 0;
		}

		CRenderer::GetInstance()->SetDebugString("現在の構造物の種類:" + std::to_string(m_nPattern));
	}
	else
	{
		CRenderer::GetInstance()->SetDebugString("現在のモード -> 編集");

		if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD0))
		{
			m_nID = 0;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD4))
		{
			m_nID--;
		}
		else if (CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD6))
		{
			m_nID++;
		}
		else if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD8))
		{
			m_nID++;
		}

		CRenderer::GetInstance()->SetDebugString("現在の構造物のID:" + std::to_string(m_nID));

		if (CManager::GetKeyboard()->GetPress(DIK_RCONTROL))
		{
			// 一斉編集
			ModifyAll();
		}
		else
		{
			// 編集
			Modify();
		}
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_F4))
	{
		// とげ移動ブロックの角度を一斉リセット
		CBlockSpikesMove::ResetAngleAll();
	}
}

//============================================================================
// とげ用操作
//============================================================================
void CStageMaker::ControlSpikes()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_R))
	{
		m_fAngleInit += D3DX_PI * 0.1f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_F))
	{
		m_fAngleInit += D3DX_PI * -0.1f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_V))
	{
		m_fAngleInit = 0.0f;
	}

	if (m_fAngleInit > D3DX_PI)
	{
		m_fAngleInit += -D3DX_PI * 2.0f;
	}
	else if (m_fAngleInit < -D3DX_PI)
	{
		m_fAngleInit += D3DX_PI * 2.0f;
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_T))
	{
		m_fAdder += 0.01f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_G))
	{
		m_fAdder += -0.01f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_B))
	{
		m_fAdder = 0.0f;
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_Y))
	{
		m_fCoeff += 1.0f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_H))
	{
		m_fCoeff += -1.0f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_N))
	{
		m_fCoeff = 1.0f;
	}

	CRenderer::GetInstance()->SetDebugString("初期角度 : " + std::to_string(m_fAngleInit));
	CRenderer::GetInstance()->SetDebugString("増加量 : " + std::to_string(m_fAdder));
	CRenderer::GetInstance()->SetDebugString("反映係数 : " + std::to_string(m_fCoeff));
}

//============================================================================
// 設置
//============================================================================
void CStageMaker::Register()
{
	// ダミーの位置を取得
	D3DXVECTOR3 pos = m_pDummy->GetPos();

	// ダミーの位置にオブジェクト生成
	switch (m_nPattern)
	{
	case 0:
		CBlock::Create(pos);
		break;

	case 1:
		CBlockDestructible::Create(pos);
		break;

	case 2:
		CBlockDestructibleBig::Create(pos);
		break;

	case 3:
		CBlockSpikes::Create(pos);
		break;

	case 4:
		CBlockSpikesMove::Create(pos, m_fAngleInit, m_fAdder, m_fCoeff);
		break;

	case 5:
		CEnemy::Create(pos);
		break;

	case 6:

		// スタートタイプのオブジェクトを検索
		if (!CObject::FindObject(CObject::TYPE::START))
		{
			CStart::Create(pos);
		}
		else
		{
			CRenderer::GetInstance()->SetTimeString("【スタートはすでに配置されています】", 60);
		}

		break;

	case 7:

		// ゴールタイプのオブジェクトを検索
		if (!CObject::FindObject(CObject::TYPE::GOAL))
		{
			CGoal::Create(pos);
		}
		else
		{
			CRenderer::GetInstance()->SetTimeString("【ゴールはすでに配置されています】", 60);
		}

		break;

	case 8:

		// アチーブタイプのオブジェクトを検索
		if (!CObject::FindObject(CObject::TYPE::ACHIEVE))
		{
			CAchieve::Create(pos);
		}
		else
		{
			CRenderer::GetInstance()->SetTimeString("【アチーブはすでに配置されています】", 60);
		}

		break;

	case 9:
	{
		// バリアアンカータグをすべて取得
		CObject** pObject{ CObject::FindAllObject(CObject::TYPE::BARRIER_ANCHOR) };

		// オブジェクト数をカウント
		int nCntObj{ 0 };

		for (nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
		{
			// オブジェクトの情報が無くなったら終了
			if (pObject[nCntObj] == nullptr)
			{
				break;
			}
		}

		if (nCntObj < 2)
		{
			CBarrier_Anchor::Create(pos);
		}
		else
		{
			CRenderer::GetInstance()->SetTimeString("【バリアアンカーはすでに2つ配置されています】", 60);
		}
	}
		break;

	default:
		assert(false);
		break;
	}
}

//============================================================================
// 編集
//============================================================================
void CStageMaker::Modify()
{
	// オブジェクトリストの先頭を取得
	CObject* pObj = CObject::GetObject(static_cast<int>(CObject::LAYER::MIDDLE));

	// 編集するIDまでオブジェクトを検索する
	for (int i = 0; i < m_nID; i++)
	{
		// オブジェクトがなければ検索終了
		if (!pObj)
		{
			break;
		}

		// 次のオブジェクトのポインタをコピー
		CObject* pNext = pObj->GetNext();

		// 次のオブジェクトを代入
		pObj = pNext;
	}

	// オブジェクトが見つからなければ終了
	if (pObj == nullptr)
	{
		return;
	}

	if (CManager::GetKeyboard()->GetTrigger(DIK_BACK))
	{
		// 削除
		pObj->SetRelease();

		return;
	}

	// オブジェクトをXオブジェクトにダウンキャスト
	CObject_X* pX = CUtility::GetInstance()->DownCast<CObject_X, CObject>(pObj);

	if (typeid(*pX) == typeid(CStart))
	{ // このオブジェクトがスタートオブジェクトなら

		// Xオブジェクトをスタートオブジェクトにダウンキャスト
		CStart* pStart = CUtility::GetInstance()->DownCast<CStart, CObject_X>(pX);

		// ダミーの座標をオブジェクトの座標に同期
		m_pDummy->SetPos(pStart->GetActualPos());

		// ダミー操作
		m_pDummy->Control();

		// 操作反映
		m_pDummy->Update();

		// 座標を反映
		pStart->SetActualPos(m_pDummy->GetPos());
		pStart->SetPos(m_pDummy->GetPos());
		pStart->Update();
	}
	else if (typeid(*pX) == typeid(CGoal))
	{ // このオブジェクトがゴールオブジェクトなら

		// Xオブジェクトをゴールオブジェクトにダウンキャスト
		CGoal* pGoal = CUtility::GetInstance()->DownCast<CGoal, CObject_X>(pX);

		// ダミーの座標をオブジェクトの座標に同期
		m_pDummy->SetPos(pGoal->GetActualPos());

		// ダミー操作
		m_pDummy->Control();

		// 操作反映
		m_pDummy->Update();

		// 座標を反映
		pGoal->SetActualPos(m_pDummy->GetPos());
		pGoal->SetPos(m_pDummy->GetPos());
		pGoal->Update();
	}
	else if (typeid(*pX) == typeid(CBlockSpikesMove))
	{ // このオブジェクトがとげ移動ブロックなら

		// Xオブジェクトをとげ移動ブロックにダウンキャスト
		CBlockSpikesMove* pSpikeMove = CUtility::GetInstance()->DownCast<CBlockSpikesMove, CObject_X>(pX);

		// ダミーの座標をオブジェクトの座標に同期
		m_pDummy->SetPos(pSpikeMove->GetPosHold());

		// ダミー操作
		m_pDummy->Control();

		// 操作反映
		m_pDummy->Update();

		// 座標・追加数値を反映
		pSpikeMove->SetPosHold(m_pDummy->GetPos());

		// 設定されていた追加情報を取得
		m_fAngleInit = pSpikeMove->GetAngleInit();
		m_fAdder = pSpikeMove->GetAdder();
		m_fCoeff = pSpikeMove->GetCoeff();
	
		// とげ用操作
		ControlSpikes();

		// 変更した追加情報を反映
		pSpikeMove->SetAngleInit(m_fAngleInit);
		pSpikeMove->SetAdder(m_fAdder);
		pSpikeMove->SetCoeff(m_fCoeff);
	}
	else
	{
		// ダミーの座標をオブジェクトの座標に同期
		m_pDummy->SetPos(pX->GetPos());

		// ダミー操作
		m_pDummy->Control();

		// 操作反映
		m_pDummy->Update();

		// 座標を反映
		pX->SetPos(m_pDummy->GetPos());
		pX->Update();
	}
}

//============================================================================
// 一斉編集
//============================================================================
void CStageMaker::ModifyAll()
{
	// 操作用座標
	D3DXVECTOR3 ControlPos{ 0.0f, 0.0f, 0.0f };

	// Y軸方向にグリッド移動
	if (CManager::GetKeyboard()->GetTrigger(DIK_W))
	{
		ControlPos.y += 5.0f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_S))
	{
		ControlPos.y += -5.0f;
	}

	// X方向にグリッド移動
	if (CManager::GetKeyboard()->GetTrigger(DIK_A))
	{
		ControlPos.x += -5.0f;
	}
	else if (CManager::GetKeyboard()->GetTrigger(DIK_D))
	{
		ControlPos.x += 5.0f;
	}

	// オブジェクトリストの先頭を取得
	CObject* pObj = CObject::GetObject(static_cast<int>(CObject::LAYER::MIDDLE));

	// オブジェクトがなくなるまで
	while (pObj)
	{
		// 次のオブジェクトのポインタをコピー
		CObject* pNext = pObj->GetNext();

		// オブジェクトをXオブジェクトにダウンキャスト
		CObject_X* pX = CUtility::GetInstance()->DownCast<CObject_X, CObject>(pObj);

		// 
		pX->SetPos(pX->GetPos() + ControlPos);

		// 次のオブジェクトを代入
		pObj = pNext;
	}
}

//============================================================================
// ステージ書き出し
//============================================================================
void CStageMaker::Export()
{
	// ステージ配置情報を書き出し展開
	std::ofstream Export("Data\\TXT\\stage.txt");

	// スタートオブジェクトを取得
	CStart* pStart = CUtility::GetInstance()->DownCast<CStart, CObject>(CObject::FindObject(CObject::TYPE::START));

	// 情報を書き出す
	Output(Export, pStart->GetActualPos(), "start");

	// ゴールオブジェクトを取得
	CGoal* pGoal = CUtility::GetInstance()->DownCast<CGoal, CObject>(CObject::FindObject(CObject::TYPE::GOAL));

	// 情報を書き出す
	Output(Export, pGoal->GetActualPos(), "goal");

	// アチーブタイプのオブジェクトをすべて取得
	CObject** pObject{ CObject::FindAllObject(CObject::TYPE::ACHIEVE) };

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// アチーブクラスへダウンキャスト
		CAchieve* pAchieve = CUtility::GetInstance()->DownCast<CAchieve, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pAchieve->GetPos(), "archieve");
	}

	// バリアアンカータグをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::BARRIER_ANCHOR);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// バリアアンカーへダウンキャスト
		CBarrier_Anchor* pAnchor = CUtility::GetInstance()->DownCast<CBarrier_Anchor, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pAnchor->GetPos(), "anchor");
	}

	// ブロックタイプのオブジェクトをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::BLOCK);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// ブロッククラスへダウンキャスト
		CBlock* pBlock = CUtility::GetInstance()->DownCast<CBlock, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pBlock->GetPos(), "block");
	}

	// 可壊ブロックタイプのオブジェクトをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::DESTRUCTIBLE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// 可壊ブロッククラスへダウンキャスト
		CBlockDestructible* pDestructible = CUtility::GetInstance()->DownCast<CBlockDestructible, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pDestructible->GetPos(), "destructible");
	}

	// 可壊でかブロックタイプのオブジェクトをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::DEST_BIG);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// 可壊でかブロッククラスへダウンキャスト
		CBlockDestructibleBig* pDestructible = CUtility::GetInstance()->DownCast<CBlockDestructibleBig, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pDestructible->GetPos(), "dest_big");
	}

	// とげブロックタイプのオブジェクトをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// とげブロッククラスへダウンキャスト
		CBlockSpikes* pDestructible = CUtility::GetInstance()->DownCast<CBlockSpikes, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pDestructible->GetPos(), "spikes");
	}

	// とげ移動ブロックタイプのオブジェクトをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::SPIKES_MOVE);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// とげ移動ブロッククラスへダウンキャスト
		CBlockSpikesMove* pSpike_Move = CUtility::GetInstance()->DownCast<CBlockSpikesMove, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pSpike_Move->GetPosHold(), "spikes_move", pSpike_Move->GetAngleInit(), pSpike_Move->GetAdder(), pSpike_Move->GetCoeff());
	}

	// エネミータイプのオブジェクトをすべて取得
	pObject = CObject::FindAllObject(CObject::TYPE::ENEMY);

	for (int nCntObj = 0; nCntObj < CObject::MAX_OBJ; nCntObj++)
	{
		// オブジェクトの情報が無くなったら終了
		if (pObject[nCntObj] == nullptr)
		{
			break;
		}

		// エネミーブロッククラスへダウンキャスト
		CEnemy* pEnemy = CUtility::GetInstance()->DownCast<CEnemy, CObject>(pObject[nCntObj]);

		// 情報を書き出す
		Output(Export, pEnemy->GetPos(), "enemy");
	}

	Export.close();	// ファイルを閉じる

	// デバッグ表示の期間を設定
	CRenderer::GetInstance()->SetTimeString("【ステージを書き出しました】", 180);
}

//============================================================================
// 情報書き出し
//============================================================================
void CStageMaker::Output(std::ofstream& file, D3DXVECTOR3 pos, std::string str)
{
	// 座標を書き出す
	file << std::fixed << std::setprecision(1) << "X:" << pos.x << ",";
	file << std::fixed << std::setprecision(1) << "Y:" << pos.y << ",";
	file << std::fixed << std::setprecision(1) << "Z:" << pos.z << ",";

	// 種類を書き出す
	file << "type:" << str << "," << std::endl;
}

//============================================================================
// 情報書き出し
//============================================================================
void CStageMaker::Output(std::ofstream& file, D3DXVECTOR3 pos, std::string str, float fAngleInit, float fAdder, float fCoeff)
{
	// 座標を書き出す
	file << std::fixed << std::setprecision(1) << "X:" << pos.x << ",";
	file << std::fixed << std::setprecision(1) << "Y:" << pos.y << ",";
	file << std::fixed << std::setprecision(1) << "Z:" << pos.z << ",";

	// 種類を書き出す
	file << "type:" << str << ",";

	// 追加数値を書き出す
	file << std::fixed << std::setprecision(3) << "i:" << fAngleInit << ",";
	file << std::fixed << std::setprecision(3) << "a:" << fAdder << ",";
	file << std::fixed << std::setprecision(3) << "c:" << fCoeff << "," << std::endl;
}