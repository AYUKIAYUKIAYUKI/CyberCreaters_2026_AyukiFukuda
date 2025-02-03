//============================================================================
// 
// 便利関数群、ヘッダファイル [utility.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _UTILITY_H_
#define _UTILITY_H_	// 二重インクルード防止

//****************************************************
// 便利関数群クラス
//****************************************************
class CUtility final
{
public:

	HRESULT Init();	// 初期設定
	void Release();	// 破棄

	static CUtility* GetInstance();	// 便利関数群を取得

	// 減算消滅
	template <typename T> bool DecrementUntilGone(T& base, T value);

	// 乗算消滅
	//template <typename T> bool DecayUntilGone(T& bas, T value);

	// 乱数生成
	template <typename T> T GetRandomValue();

	// ダウンキャスト
	template <typename T1, typename T2> T1* DownCast(T2* pBase);

	// 目標数値へ補正
	template <typename T> T AdjustToTarget(T base, T target, float fCoeff);

	// 重力落下
	void Gravity(D3DXVECTOR3& vec);

	// 球体同士の衝突判定
	bool OnlySphere(const D3DXVECTOR3& posSelf, const float& fRadiusSelf, const D3DXVECTOR3& posTarget, const float& fRadiusTarget);

	// 球体と立方体の衝突判定
	bool SphereAndCube(const D3DXVECTOR3& posSph, const float& fRadius, const D3DXVECTOR3& posCube, const D3DXVECTOR3& size);

	// 立方体同士の衝突判定
	bool OnlyCube(const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget);

	// 立方体同士の押し出し処理
	bool OnlyCube(D3DXVECTOR3& posDest, D3DXVECTOR3& velocity, const D3DXVECTOR3& posSelf, const D3DXVECTOR3& sizeSelf, const D3DXVECTOR3& posTarget, const D3DXVECTOR3& sizeTarget);

	// 構造物との当たり判定
	const type_info& CollisionToStructure();

private:

	static const float GRAVITY_FORCE;	// 重力

	CUtility();		// コンストラクタ
	~CUtility();	// デストラクタ

	void Create();	// 生成
	void Uninit();	// 終了処理

	static CUtility* m_pInstance;	// 便利関数群
};

//============================================================================
// 減算消滅
//============================================================================
template <typename T> bool CUtility::DecrementUntilGone(T& base, T value)
{
	if (base > 0)
	{
		base += value;

		return false;
	}

	return true;
}

//============================================================================
// 乱数生成
//============================================================================
template <typename T> T CUtility::GetRandomValue()
{
	// 数値の取る範囲を設定
	const int nRange = 180;

	// 倍の範囲からランダムな整数を生成
	int random{ rand() % (nRange * 2) };

	// もとの範囲を超えていた場合正負を反転
	if (random > nRange)
	{
		random %= nRange;
		random *= -1;
	}

	// 整数を指定された型にキャスト
	return static_cast<T>(random);
}

//============================================================================
// ダウンキャスト
//============================================================================
template <typename T1, typename T2> T1* CUtility::DownCast(T2* pBase)
{
	// 引数のオブジェクトを指定されたクラスにダウンキャスト
	T1* pObj{ dynamic_cast<T1*>(pBase) };

	// ダウンキャスト失敗
	if (!pObj)
	{
		assert(false);
	}

	return pObj;
}

//============================================================================
// 目標数値へ補正
//============================================================================
template <typename T> T CUtility::AdjustToTarget(T base, T target, float fCoeff)
{
	base += (target - base) * fCoeff;

	return base;
}

#endif // _UTILITY_H_