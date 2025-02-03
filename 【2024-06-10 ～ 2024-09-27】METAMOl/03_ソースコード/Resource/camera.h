//============================================================================
// 
// カメラ、ヘッダファイル [camera.h]
// Author : 福田歩希
// 
//============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_	// 二重インクルード防止

//****************************************************
// カメラクラス
//****************************************************
class CCamera
{
public:

	static const float DEFUALT_DISTANCE;	// 通常間距離

	CCamera();	// デフォルトコンストラクタ
	~CCamera();	// デストラクタ

	HRESULT Init();		// 初期設定
	void Update();		// 更新処理
	void SetCameraBG();	// 背景用カメラをセット
	void SetCamera();	// カメラをセット
	
	D3DXVECTOR3 GetPos();			// 位置を取得
	void SetPos(D3DXVECTOR3 pos);	// 位置を設定

	D3DXVECTOR3 GetPosTarget();					// 目標位置を取得
	void SetPosTarget(D3DXVECTOR3 posTarget);	// 目標位置を設定

	D3DXVECTOR3 GetRot();	// 向きを取得

	float GetDistance();				// 間距離を取得
	void SetDistance(float fDistance);	// 間距離を設定

	D3DXVECTOR3 GetPosBG();				// BG座標を取得
	void SetPosBG(D3DXVECTOR3 PosBG);	// BG座標を設定

	float GetDistanceBG();					// BG間距離を取得
	void SetDistanceBG(float fDistance);	// BG間距離を設定

private:

	//****************************************************
	// アンカーポイント構造体を定義
	//****************************************************
	struct AnchorPoint
	{
		D3DXVECTOR3 pos;		// 座標
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 stepRot;	// 向き増加量
		D3DXVECTOR3 stepPos;	// 座標増加量
		int nNumStep;			// ステップ数
		bool bSet;				// 増加量のセットフラグ
	};

	void ImportAnchorPoint();	// アンカーポイントを読み込む
	void UpdateScreen();		// スクリーン用の更新
	void Control();				// カメラ操作
	void Rotation();			// 回転
	void Translation();			// 移動
	void RestrictYaw();			// ヨー角の範囲を制限
	void RestrictPitch();		// ピッチ角の範囲を制限
	void CalcPosV();			// 視点位置を算出
	void CalcPosR();			// 注視点位置を算出
	void UpdateBG();			// 背景用の更新
	void CalcMtxProjection();	// プロジェクション行列計算
	void CalcMtxView();			// ビュー行列計算

	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_posTarget;					// 目標位置
	D3DXVECTOR3 m_posV;							// 視点位置
	D3DXVECTOR3 m_posTargetV;					// 目標視点位置
	D3DXVECTOR3 m_posR;							// 注視点位置
	D3DXVECTOR3 m_posTargetR;					// 目標注視点位置
	D3DXVECTOR3 m_rot;							// 向き
	D3DXVECTOR3 m_rotTarget;					// 目標向き
	float m_fDistance;							// 視点 -> 注視点間の距離
	std::vector<AnchorPoint> m_vAnchorPoint;	// アンカーポイント
	D3DXVECTOR3 m_posBG;						// 背景位置
	D3DXVECTOR3 m_posTargetBG;					// 背景目標位置
	D3DXVECTOR3 m_posVBG;						// 背景視点位置
	D3DXVECTOR3 m_posRBG;						// 背景注視点位置
	D3DXVECTOR3 m_rotBG;						// 背景向き
	D3DXVECTOR3 m_rotTargetBG;					// 背景目標向き
	float m_fDistanceBG;						// 背景視点 -> 注視点間の距離
	D3DXVECTOR3 m_vecU;							// 上方向ベクトル
	D3DXMATRIX m_mtxProjection;					// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;						// ビューマトリックス
	float m_fAdjust;							// 俯瞰度合
};

#endif // _CAMERA_H_