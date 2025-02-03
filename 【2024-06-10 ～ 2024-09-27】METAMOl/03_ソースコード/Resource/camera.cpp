//============================================================================
// 
// カメラ [camera.cpp]
// Author : 福田歩希
// 
//============================================================================

//****************************************************
// インクルードファイル
//****************************************************
#include "camera.h"
#include "utility.h"

// インプット取得用
#include "manager.h"

// デバイス取得用
#include "renderer.h"

// 追従地点参照用
#include "dummy.h"
#include "game.h"
#include "player.h"
#include "player_state.h"
#include "stagemaker.h"
#include "title.h"

//****************************************************
// 静的メンバ変数の初期化
//****************************************************
const float CCamera::DEFUALT_DISTANCE = 300.0f;	// 通常間距離

//============================================================================
// デフォルトコンストラクタ
//============================================================================
CCamera::CCamera() :
	m_pos{ 0.0f, 0.0f, 0.0f },			// 位置
	m_posTarget{ 0.0f, 0.0f, 0.0f },	// 目標位置
	m_posV{ 0.0f, 0.0f, 0.0f },			// 視点位置
	m_posTargetV{ 0.0f, 0.0f, 0.0f },	// 目標視点位置
	m_posR{ 0.0f, 0.0f, 0.0f },			// 注視点位置
	m_posTargetR{ 0.0f, 0.0f, 0.0f },	// 目標注視点位置
	m_rot{ 0.0f, 0.0f, 0.0f },			// 向き
	m_rotTarget{ 0.0f, 0.0f, 0.0f },	// 目標向き
	m_fDistance{ DEFUALT_DISTANCE },	// 視点 -> 注視点間の距離
	m_posBG{ 0.0f, 0.0f, 0.0f },		// 背景座標
	m_posTargetBG{ 0.0f, 0.0f, 0.0f },	// 背景目標座標
	m_posVBG{ 0.0f, 0.0f, 0.0f },		// 背景視点
	m_posRBG{ 0.0f, 0.0f, 0.0f },		// 背景注視点
	m_rotBG{ 0.0f, 0.0f, 0.0f },		// 背景向き
	m_rotTargetBG{ 0.0f, 0.0f, 0.0f },	// 背景目標向き
	m_fDistanceBG{ 25.0f },				// 背景視点 -> 注視点間の距離
	m_vecU{ 0.0f, 1.0f, 0.0f },			// 上方向ベクトル
	m_fAdjust{ 0.0f }					// 俯瞰度合
{
	D3DXMatrixIdentity(&m_mtxProjection);	// プロジェクションマトリックス
	D3DXMatrixIdentity(&m_mtxView);			// ビューマトリックス
}

//============================================================================
// デストラクタ
//============================================================================
CCamera::~CCamera()
{

}

//============================================================================
// 初期設定
//============================================================================
HRESULT CCamera::Init()
{
	// アンカーポイントを読み込む
	ImportAnchorPoint();

	//m_posBG = { 0.0f, -30.0f, -30.0f };

	return S_OK;
}

//============================================================================
// 更新処理
//============================================================================
void CCamera::Update()
{
	// スクリーン用の更新
	UpdateScreen();

	// 背景用の更新
	UpdateBG();

//#ifdef _DEBUG
//	// 座標をデバッグ表示
//	CRenderer::GetInstance()->SetDebugString("【背景カメラポイント】");
//	std::ostringstream oss;
//	oss << std::fixed << std::setprecision(2) << "p X:" << m_posBG.x << "\np Y:" << m_posBG.y << "\np Z:" << m_posBG.z << "\nr X:" << m_rotBG.x << "\nr Y:" << m_rotBG.y << "\nr Z:" << m_rotBG.z;
//	CRenderer::GetInstance()->SetDebugString(oss.str().c_str());
//#endif	// _DEBUG
}

//============================================================================
// 背景用カメラをセット
//============================================================================
void CCamera::SetCameraBG()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// 画面バッファクリア
	pDev->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(25, 25, 25, 0), 1.0f, 0);

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

#ifdef _DEBUG
	// 左右
	if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))
	{
		m_rotBG.y += 0.01f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_LEFT))
	{
		m_rotBG.y -= 0.01f;
	}

	// 上下
	if (CManager::GetKeyboard()->GetPress(DIK_UP))
	{
		m_rotBG.x += 0.01f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_DOWN))
	{
		m_rotBG.x -= 0.01f;
	}
#endif	// _DEBUG

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	//// 回転量減衰
	//m_rotTargetBG *= 0.8f;

	//// 回転量反映
	//m_rotBG += m_rotTargetBG * 0.5f;

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	//// 回転の制限
	//if (m_rotBG.y > D3DX_PI)
	//{
	//	m_rotBG.y = -D3DX_PI;
	//}
	//else if (m_rotBG.y < -D3DX_PI)
	//{
	//	m_rotBG.y = D3DX_PI;
	//}

	//if (m_rotBG.x + m_rotTargetBG.x > D3DX_PI * 0.48f)
	//{
	//	m_rotBG.x = D3DX_PI * 0.48f;
	//}
	//else if (m_rotBG.x + m_rotTargetBG.x < -D3DX_PI * 0.48f)
	//{
	//	m_rotBG.x = -D3DX_PI * 0.48f;
	//}

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

#ifdef _DEBUG
	if (CManager::GetKeyboard()->GetPress(DIK_T))
	{
		m_posBG.y += 0.5f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_G))
	{
		m_posBG.y += -0.5f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_H))
	{
		m_posBG.x += 0.5f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_F))
	{
		m_posBG.x += -0.5f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_U))
	{
		m_posBG.z += 0.5f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_J))
	{
		m_posBG.z += -0.5f;
	}

	if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD8))
	{
		m_fDistanceBG--;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_NUMPAD5))
	{
		m_fDistanceBG++;
	}
	else if(CManager::GetKeyboard()->GetTrigger(DIK_NUMPAD2))
	{
		m_fDistanceBG = 25.0f;
	}

	CRenderer::GetInstance()->SetDebugString("空間ズーム具合 : " + std::to_string(m_fDistanceBG));
#endif	// _DEBUG

	// 視点は対象物の後方に
	m_posVBG =
	{
		m_posBG.x - (sinf(m_rotBG.y) * cosf(m_rotBG.x) * (m_fDistanceBG)),
		m_posBG.y - (sinf(m_rotBG.x) * (m_fDistanceBG)),
		m_posBG.z - (cosf(m_rotBG.y) * cosf(m_rotBG.x) * (m_fDistanceBG))
	};

	// 注視点を対象物の前方に
	m_posRBG =
	{
		m_posBG.x + (sinf(m_rotBG.y) * cosf(m_rotBG.x) * m_fDistanceBG),
		m_posBG.y + (sinf(m_rotBG.x) * m_fDistanceBG),
		m_posBG.z + (cosf(m_rotBG.y) * cosf(m_rotBG.x) * m_fDistanceBG)
	};

	/////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	/* 空のマトリックスを用意 */
	D3DXMATRIX mtxView;

	/* ビュー行列を計算 */

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);

	// ビューマトリックスの生成
	D3DXMatrixLookAtLH(&mtxView,
		&m_posVBG,
		&m_posRBG,
		&m_vecU);

	// ビューマトリックスの設定
	pDev->SetTransform(D3DTS_VIEW,
		&mtxView);
}

//============================================================================
// カメラをセット
//============================================================================
void CCamera::SetCamera()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// 画面バッファクリア
	pDev->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(255, 255, 255, 0), 1.0f, 0);

	// プロジェクション行列を計算
	CalcMtxProjection();
	
	// ビュー行列を計算
	CalcMtxView();
}

//============================================================================
// 位置を取得
//============================================================================
D3DXVECTOR3 CCamera::GetPos()
{
	return m_pos;
}

//============================================================================
// 位置を設定
//============================================================================
void CCamera::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================================================================
// 目標位置を取得
//============================================================================
D3DXVECTOR3 CCamera::GetPosTarget()
{
	return m_posTarget;
}

//============================================================================
// 目標位置を設定
//============================================================================
void CCamera::SetPosTarget(D3DXVECTOR3 posTarget)
{
	m_posTarget = posTarget;
}

//============================================================================
// 向きを取得
//============================================================================
D3DXVECTOR3 CCamera::GetRot()
{
	return m_rot;
}

//============================================================================
// BG座標を取得
//============================================================================
D3DXVECTOR3 CCamera::GetPosBG()
{
	return m_posBG;
}

//============================================================================
// BG座標を設定
//============================================================================
void CCamera::SetPosBG(D3DXVECTOR3 Pos)
{
	m_posBG = Pos;
}

//============================================================================
// 間距離を取得
//============================================================================
float CCamera::GetDistance()
{
	return m_fDistance;
}

//============================================================================
// 間距離を設定
//============================================================================
void CCamera::SetDistance(float fDistance)
{
	m_fDistance = fDistance;
}

//============================================================================
// BG間距離を取得
//============================================================================
float CCamera::GetDistanceBG()
{
	return m_fDistanceBG;
}

//============================================================================
// BG間距離を設定
//============================================================================
void CCamera::SetDistanceBG(float fDistance)
{
	m_fDistanceBG = fDistance;
}

//============================================================================
// アンカーポイントを読み込む
//============================================================================
void CCamera::ImportAnchorPoint()
{
	//for (int i = 0; i < 10; i++)
	//{
	//	/* 仮にランダムな数値を設定 */
	//	D3DXVECTOR3 newPos = { CUtility::GetInstance()->GetRandomValue<float>() * 0.25f, CUtility::GetInstance()->GetRandomValue<float>() * 0.25f, -50.0f };
	//	D3DXVECTOR3 newRot = { 0.0f, 0.0f, 0.0f };

	//	// 数値情報を1つにまとめる
	//	AnchorPoint newAP = { newPos, newRot, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 180, false };

	//	// アンカーポインタ情報を追加
	//	m_vAnchorPoint.push_back(newAP);
	//}

	// アンカーポイント情報を展開
	std::ifstream Import{ "Data\\TXT\\AnchorPoint.txt" };

	if (!Import)
	{ // 展開失敗
#if 0
		assert(false);
#else

#ifdef _DEBUG
		CRenderer::GetInstance()->SetTimeString("【警告】アンカーポイント情報の読み込みに失敗しました", 300);
#endif	// _DEBUG

		return;
#endif
	}

	// テキストを格納
	std::string str;

	// ファイルを一行ずつ、情報を全て取得する
	while (std::getline(Import, str))
	{
		// 数値格納用
		D3DXVECTOR3 newPos = { 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 newRot = { 0.0f, 0.0f, 0.0f };
		int nNewNumStep{ 0 };

		// 数値となる文字列分離用
		std::string value[7];

		for (int i = 0; i < 7; i++)
		{
			// 数値部分のみ抽出する
			value[i] = str.substr(str.find(":") + 1, str.find(",") - (str.find(":") + 1));

			// 不必要になった部分を削除する
			str.erase(0, str.find(",") + 1);
		}

		// 抽出した数値を座標に変換
		newPos.x = std::stof(value[0]);
		newPos.y = std::stof(value[1]);
		newPos.z = std::stof(value[2]);
		newRot.x = std::stof(value[3]);
		newRot.y = std::stof(value[4]);
		newRot.z = std::stof(value[5]);
		nNewNumStep = std::stoi(value[6]);

		// 数値情報を1つにまとめる
		AnchorPoint newAP = { newPos, newRot, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, nNewNumStep, false };

		// アンカーポイントに追加
		m_vAnchorPoint.push_back(newAP);
	}
}

//============================================================================
// スクリーン用の更新
//============================================================================
void CCamera::UpdateScreen()
{
	// 間距離補正係数
	float fAdjustDistance{ 0.1f };

	// オブジェクト用ポインタ
	CObject* pObj{ nullptr };

	// プレイヤータイプのオブジェクトを取得
	pObj = CObject::FindObject(CObject::TYPE::PLAYER);

	if (pObj != nullptr)
	{ // プレイヤータイプの取得に成功

		// プレイヤークラスにダウンキャスト
		CPlayer* pPlayer = CUtility::GetInstance()->DownCast<CPlayer, CObject>(pObj);

		// プレイヤーの状態に応じて目標座標を補正
		if (CManager::GetScene()->GetMode() == CScene::MODE::GAME)
		{
			// カメラの目標座標をプレイヤー座標に
			m_posTarget = pPlayer->GetPos();

			// 状態に応じてカメラの挙動を変更
			if (typeid(*pPlayer->GetStateManager()->GetState()) == typeid(CPlayerStateDefault))
			{
				fAdjustDistance = CUtility::GetInstance()->AdjustToTarget<float>(fAdjustDistance, 0.5f, 0.1f);
			}
			else
			{
				fAdjustDistance = CUtility::GetInstance()->AdjustToTarget<float>(fAdjustDistance, 1.0f, 0.1f);
			}
		}
		else if (CManager::GetScene()->GetMode() == CScene::MODE::CHALLENGE)
		{
			static float fCoeff{ 5.0f };

			// プレイヤーの移動方向に寄せる
			m_posTarget = pPlayer->GetPos() + pPlayer->GetVelocity() * fCoeff;
			
			// 状態に応じてカメラの挙動を変更
			if (typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateFlying) &&
				typeid(*pPlayer->GetStateManager()->GetState()) != typeid(CPlayerStateRushing))
			{
				fCoeff = CUtility::GetInstance()->AdjustToTarget<float>(fCoeff, 5.0f, 0.1f);
			}
			else
			{
				fCoeff = CUtility::GetInstance()->AdjustToTarget<float>(fCoeff, 15.0f, 0.1f);
			}

			// カメラの間距離を広く設定
			m_fDistance = CUtility::GetInstance()->AdjustToTarget(m_fDistance, DEFUALT_DISTANCE * 2.0f, 0.05f);
		}
	}
	else
	{ // プレイヤータイプの取得に失敗

		// ダミータイプのオブジェクトを取得
		pObj = CObject::FindObject(CObject::TYPE::DUMMY);

		if (pObj != nullptr)
		{ // ダミータイプの取得に成功

			// ダミークラスにダウンキャスト
			CDummy* pDummy = CUtility::GetInstance()->DownCast<CDummy, CObject>(pObj);

			// 座標を設定
			m_pos = pDummy->GetPos();
			m_posTarget = pDummy->GetPos();
		}
	}

#ifdef _DEBUG
	// カメラ操作
	Control();
#endif	// _DEBUG

	// 回転
	Rotation();

	// 移動
	//Translation();

	// 座標を目標座標に補正
	m_pos = CUtility::GetInstance()->AdjustToTarget(m_pos, m_posTarget, fAdjustDistance);

	// ヨー角の範囲を制限
	RestrictYaw();

	// ピッチ角の範囲を制限
	RestrictPitch();

	// 視点位置を算出
	CalcPosV();

	// 注視点位置を算出
	CalcPosR();

#ifdef _DEBUG
	CRenderer::GetInstance()->SetDebugString("カメラ間距離 : " + std::to_string(m_fDistance));
	CRenderer::GetInstance()->SetDebugString("カメラZ座標 : " + std::to_string(m_pos.z));
#endif	// _DEBUG
}

//============================================================================
// カメラ操作
//============================================================================
void CCamera::Control()
{
	// ズームイン / アウト
	if (CManager::GetKeyboard()->GetPress(DIK_AT) && m_fDistance > 10.0f)
	{
		m_fDistance -= 10.0f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_COLON))
	{
		m_fDistance += 10.0f;
	}
	else if (CManager::GetKeyboard()->GetPress(DIK_BACKSLASH))
	{
		// 距離間リセット
		m_fDistance = 200.0f;
	}

	//// 左右
	//if (CManager::GetKeyboard()->GetPress(DIK_RIGHT))
	//{
	//	m_rotTarget.y += 0.02f;
	//}
	//else if (CManager::GetKeyboard()->GetPress(DIK_LEFT))
	//{
	//	m_rotTarget.y -= 0.02f;
	//}

	//// 上下
	//if (CManager::GetKeyboard()->GetPress(DIK_UP))
	//{
	//	m_rotTarget.x += 0.02f;
	//}
	//else if (CManager::GetKeyboard()->GetPress(DIK_DOWN))
	//{
	//	m_rotTarget.x -= 0.02f;
	//}
}

//============================================================================
// 回転
//============================================================================
void CCamera::Rotation()
{
	// 回転量減衰
	m_rotTarget *= 0.8f;

	// 回転量反映
	m_rot += m_rotTarget * 0.5f;
}

//============================================================================
// 移動
//============================================================================
void CCamera::Translation()
{
	// 追従度合
	float fTracking = 0.25f;

	// 移動量反映
	// posTargetに値を設定していない場合は数値がおかしくなります
	m_pos += (m_posTarget - m_pos) * fTracking;
}

//============================================================================
// ヨー角の範囲を制限
//============================================================================
void CCamera::RestrictYaw()
{
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}
}

//============================================================================
// ピッチ角の範囲を制限
//============================================================================
void CCamera::RestrictPitch()
{
	if (m_rot.x + m_rotTarget.x > D3DX_PI * 0.48f)
	{
		m_rot.x = D3DX_PI * 0.48f;
	}
	else if (m_rot.x + m_rotTarget.x < -D3DX_PI * 0.48f)
	{
		m_rot.x = -D3DX_PI * 0.48f;
	}
}

//============================================================================
// 視点位置を算出
//============================================================================
void CCamera::CalcPosV()
{
	// 視点は対象物の後方に
	m_posV =
	{
		m_pos.x - (sinf(m_rot.y) * cosf(m_rot.x) * (m_fDistance)),
		m_pos.y - (sinf(m_rot.x) * (m_fDistance)),
		m_pos.z - (cosf(m_rot.y) * cosf(m_rot.x) * (m_fDistance))
	};
}

//============================================================================
// 注視点位置を算出
//============================================================================
void CCamera::CalcPosR()
{
	// 注視点を対象物の前方に
	m_posR =
	{
		m_pos.x + (sinf(m_rot.y) * cosf(m_rot.x) * m_fDistance),
		m_pos.y + (sinf(m_rot.x) * m_fDistance),
		m_pos.z + (cosf(m_rot.y) * cosf(m_rot.x) * m_fDistance)
	};
}

//============================================================================
// 背景用の更新
//============================================================================
void CCamera::UpdateBG()
{
	// 現在のモードを取得
	CScene::MODE mode{ CManager::GetScene()->GetMode() };

	// アンカーポイントの番号
	static unsigned int nNumElement{ 0 };

	// 実数値 -> 目標数値への補間速度を格納
	float fCoeff{ 0.0f };

	if (mode == CScene::MODE::STAGE)
	{
		// 処理を行わない
		return;
	}
	else if (mode == CScene::MODE::GAME || mode == CScene::MODE::CHALLENGE)
	{
		// 背景用カメラの目標座標・目標向きを、保持している目標数値とは別途で固定する
		D3DXVECTOR3 posTarget = { -3.0f, 0.0f, 0.0f };
		D3DXVECTOR3 rotTarget = { 0.0f, 0.0f, 0.0f };

		// 補間速度を設定
		fCoeff = 0.1f;

		// 目標座標へ迫る
		m_posBG = CUtility::GetInstance()->AdjustToTarget(m_posBG, posTarget, fCoeff);

		// 目標向きへ迫る
		m_rotBG = CUtility::GetInstance()->AdjustToTarget(m_rotBG, rotTarget, fCoeff);

		// アンカーポイントの番号をリセット
		/* コメントアウトでゲーム開始時のポイントから続くように見える */
		nNumElement = 0;

		//// アンカーポイントへの増加量を、この座標から再計算する
		///* 実数値と目標数値が分かれている場合不要 */
		//for (auto&& it : m_vAnchorPoint)
		//{
		//	it.bSet = false;
		//}
	}
	else if (CManager::GetScene()->GetMode() == CScene::MODE::TITLE && CTitle::GetSelect() != 0)
	{
		// 背景用カメラの目標座標・目標向きを、保持している目標数値とは別途で固定する
		D3DXVECTOR3 posTarget = { -5.0f, 0.0f, -10.0f };
		D3DXVECTOR3 rotTarget = { 0.0f, 0.0f, 0.0f };

		// 補間速度を設定
		fCoeff = 0.1f;

		// 目標座標へ迫る
		m_posBG = CUtility::GetInstance()->AdjustToTarget(m_posBG, posTarget, fCoeff);

		// 目標向きへ迫る
		m_rotBG = CUtility::GetInstance()->AdjustToTarget(m_rotBG, rotTarget, fCoeff);

		// アンカーポイントの番号をリセット
		/* コメントアウトでゲーム開始時のポイントから続くように見える */
		nNumElement = 0;
	}
	else
	{
		// アンカーポイントが増加量設定を終えていなければ
		if (!m_vAnchorPoint[nNumElement].bSet)
		{
			// 割る数
			float nDivider{ static_cast<float>(m_vAnchorPoint[nNumElement].nNumStep) };

			// 増加量の設定を行う
			m_vAnchorPoint[nNumElement].stepPos = (m_vAnchorPoint[nNumElement].pos - m_posTargetBG) / nDivider;
			m_vAnchorPoint[nNumElement].stepRot = (m_vAnchorPoint[nNumElement].rot - m_rotTargetBG) / nDivider;

			// 設定を終了する
			m_vAnchorPoint[nNumElement].bSet = true;
		}

		if (fabsf(m_vAnchorPoint[nNumElement].pos.x - m_posTargetBG.x) >= 0.01f)
		{ // 目標地点との差がある程度あると

			// 補間していく
			m_posTargetBG += m_vAnchorPoint[nNumElement].stepPos;
			m_rotTargetBG += m_vAnchorPoint[nNumElement].stepRot;
		}
		else
		{ // ほとんど目標地点に到達で

			// このポイントでの増加量設定をリセットする
			m_vAnchorPoint[nNumElement].bSet = false;
			
			// 次のポイントへ進む
			nNumElement++;

			// 最後のポイントに到達したら最初へ戻る
			if (nNumElement >= m_vAnchorPoint.size())
			{
				nNumElement = 0;
			}

#ifdef _DEBUG
			CRenderer::GetInstance()->SetTimeString("次のアンカーポイント : " + std::to_string(nNumElement), 300);
#endif	// _DEBUG
		}

		// 補間速度を設定する
		fCoeff = 0.01f;

		// 目標座標へ迫る
		m_posBG = CUtility::GetInstance()->AdjustToTarget(m_posBG, m_posTargetBG, fCoeff);

		// 目標向きへ迫る
		m_rotBG = CUtility::GetInstance()->AdjustToTarget(m_rotBG, m_rotTargetBG, fCoeff);
	}

//#ifdef _DEBUG
//	// 次のアンカーポイントをデバッグ表示
//	CRenderer::GetInstance()->SetDebugString("【安価ポイント】");
//	std::ostringstream oss0;
//	oss0 << std::fixed << std::setprecision(2) << "p X:" << m_vAnchorPoint[nNumElement].pos.x << "\np Y:" << m_vAnchorPoint[nNumElement].pos.y << "\np Z:" << m_vAnchorPoint[nNumElement].pos.z << "\nr X:" << m_vAnchorPoint[nNumElement].rot.x << "\nr Y:" << m_vAnchorPoint[nNumElement].rot.y << "\nr Z:" << m_vAnchorPoint[nNumElement].rot.z;
//	CRenderer::GetInstance()->SetDebugString(oss0.str().c_str());
//
//	// 目標座標をデバッグ表示
//	CRenderer::GetInstance()->SetDebugString("【背景カメラ目標ポイント");
//	std::ostringstream oss1;
//	oss1 << std::fixed << std::setprecision(2) << "p X:" << m_posTargetBG.x << "\np Y:" << m_posTargetBG.y << "\np Z:" << m_posTargetBG.z << "\nr X:" << m_rotTargetBG.x << "\nr Y:" << m_rotTargetBG.y << "\nr Z:" << m_rotTargetBG.z;
//	CRenderer::GetInstance()->SetDebugString(oss1.str().c_str());
//#endif	// _DEBUG
}

//============================================================================
// プロジェクション行列計算
//============================================================================
void CCamera::CalcMtxProjection()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// プロジェクション行列の初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクション行列を生成
#if 1
	// 透視投影
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		5000.0f);	
#else
	// 平行投影
	D3DXMatrixOrthoLH(&m_mtxProjection,
		(float)SCREEN_WIDTH * 0.25f,
		(float)SCREEN_HEIGHT * 0.25f,
		10.0f,
		5000.0f);
#endif

	// プロジェクション行列の設定
	pDev->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

//============================================================================
// ビュー行列計算
//============================================================================
void CCamera::CalcMtxView()
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDev = CRenderer::GetInstance()->GetDeviece();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// 視点位置の調整用
	D3DXVECTOR3 posV = m_posV;
	D3DXVECTOR3 posR = m_posR;

	// カメラを俯瞰気味に
	//posV.y += m_fAdjust;

	// ビューマトリックスの生成
	D3DXMatrixLookAtLH(&m_mtxView,
		&posV,
		&posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDev->SetTransform(D3DTS_VIEW,
		&m_mtxView);
}