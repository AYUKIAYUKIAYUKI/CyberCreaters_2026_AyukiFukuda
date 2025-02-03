//============================================================================
// 
// ライト、ヘッダファイル [light.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _LIGHT_H_
#define _LIGHT_H_	// 二重インクルード防止

//****************************************************
// ライトクラス
//****************************************************
class CLight
{
public:

	CLight();	// デフォルトコンストラクタ
	~CLight();	// デストラクタ

	HRESULT Init();	// 初期設定
	void Update();	// 更新処理

private:

	void SetTempDirection();	// 向きのテンプレをセット
	void Create();				// 生成
	void ChangeID();			// 操作番号変更
	void Control();				// 操作
	void Reset();				// リセット
	void SetLight();			// ライトセット

	static const int MAX_LIGHT = 3;	// ライトの数

	D3DLIGHT9 m_light[MAX_LIGHT];			// ライト情報
	D3DXVECTOR3 m_tempDirection[MAX_LIGHT];	// ライトの向き
	int m_nID;								// ライト操作番号用
};

#endif // _LIGHT_H_