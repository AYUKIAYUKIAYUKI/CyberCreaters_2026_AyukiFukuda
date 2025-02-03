//************************************************
//
// プレイヤー処理、ヘッダファイル[player.h]
// Author：福田歩希, kasai keisuke
//
//************************************************
#ifndef _PLAYER_H_	// このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _PLAYER_H_	// (二重インクルード防止、マクロ定義する)

/*/ インクルードファイル / */
#include "main.h"

#include "item.h"

/*/ マクロ定義 /*/
#define AMOUNT_PLAYER_PARTS	16		// プレイヤー最大モデル種数
#define SPD_STOPMOVE_PLAYER	0.9f	// ブレーキ力
#define SPD_MOVE_PLAYER	0.38f		// 移動速度
#define GUTRELOAD	(200)			// ミニガンのリロード時間
// プレイヤーの状態分け
typedef enum
{
	stateNormal_p = 0,	// 通常
	stateMove_p,		// 移動
	stateAtk_p,			// 攻撃
	stateDamage_p,		// 負傷
	stateDead_p,		// 死亡
	steteResurrect_p,	// 復活
	Max_playerstate,
}PlayerState;

// プレイヤーパラメータ情報
typedef struct
{
	int style;		// スタイル
	int state;		// 状態
	int dur;		// 状態継続
	int HP;			// 体力
	float SPD;		// 速度
	float rad;		// 球判定サイズ
	int weapon;		// 武器識別
	int motion_now;	// 再生モーション
	int motion_old;	// 過去モーション
}PlayerParam;

/*---【武器用拡張パラメータ】---*/
typedef struct
{
	int magazine;	// 残弾数
	int CT_input;	// 長押し期間
	int CT_reload;	// リロード期間
	int CT_recoil;	// 反動期間
	bool empty;		// 空になっている判定
} ParamForWeapon;

// プレイヤーが攻撃を放つ位置を保存…
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXMATRIX mtx;		// ワールドマトリックス
}OffsetPosAtk;

// プレイヤー用モデル情報
typedef struct
{
	int style;								// スタイル
	int weapon;								// 武器識別
	LPD3DXMESH pMesh;						// メッシュのポインタ
	LPD3DXBUFFER pBuffMat;					// マテリアルのポインタ
	DWORD NumMat;							// マテリアルの数
	D3DXVECTOR3 pos_offset;					// 位置オフセット
	D3DXVECTOR3 pos_moved;					// モーション後の変動位置
	D3DXVECTOR3 rot_offset;					// 向きオフセット
	D3DXVECTOR3 rot_moved;					// モーション後の変動向き
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	LPDIRECT3DTEXTURE9 pTex[AMOUNT_MAT];	// テクスチャのポインタ
	int IdxParent;							// 親パーツのインデックス
}PlayerModel;

// モーション時のパーツ目標動作用
typedef struct
{
	D3DXVECTOR3 pos;	// 目標位置格納
	D3DXVECTOR3 rot;	// 目標向き格納
}PlayerMotionDest;

// モーション時のキー用
typedef struct
{
	int amount_frame;							// キー単位の総フレーム数
	PlayerMotionDest dest[AMOUNT_PLAYER_PARTS];	// パーツの動作情報格納
}PlayerMotionKey;

// プレイヤーモーション用
typedef struct
{
	int loop;					// ループフラグ
	int amount_key;				// モーション単位の総キー数
	int id_key;					// 再生中のキー番号を格納
	int id_frame;				// 再生中のフレーム番号を格納
	PlayerMotionKey key[16];	// キー情報を格納
}PlayerMotion;

// プレイヤー情報
typedef struct
{
	bool use;								// 使用フラグ
	PlayerParam param;						// パラメータ
	ParamForWeapon PFW;						// 武器用パラメータ
	D3DXVECTOR3 pos;						// ワールド位置
	D3DXVECTOR3 pos_old;					// 過去の位置
	D3DXVECTOR3 move;						// 移動量
	D3DXVECTOR3 rot;						// 現在の向き
	D3DXVECTOR3 rot_goal;					// 目標の向き
	D3DXCOLOR col;							// 色変更用
	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	OffsetPosAtk offset_atk[Max_itemstyle];	// 攻撃を放つ位置を格納
	PlayerModel parts[AMOUNT_PLAYER_PARTS];	// モデルパーツ
	PlayerMotion motion[8];					// モーション情報
	int id_shadow;							// 影識別番号
	int id_sph;								// 判定識別番号格納
}Player;

/*/ プロトタイプ宣言 /*/
void InitPlayer(int joined);						// 初期
void CreatePlayer(int joined);						// プレイヤー生成
void SetSpawnPlayer(int joined);					// スポーン地点設定
void ImportModelPlayer(void);						// モデル取得
void ImportOffsetPlayer(FILE* pFile,
	int AmountModel);								// モデルオフセット取得
void ImportOffsetAtkPlayer(FILE* pFile);			// 攻撃位置のオフセット取得
void ImportTexPlayer(int AmountModel);				// モデルテクスチャ取得
void VerifyStylePlayer(int id);						// スタイル番号を照合
void ImportMotionPlayer(void);						// モーション取得
void UninitPlayer(void);							// 破棄
void UpdatePlayer(int id);							// 更新
void RotatePlayer(int id);							// 回転
void AdjustTurret(int id);							// 砲塔調整
void MovePlayer(int id);							// 移動
void DEBUG_MovePlayer(void);						// デバッグ移動
void TranslatePlayer(int id);						// 移動を反映
void HitObjectPlayer(int id);						// 壁に当たった時用
void AtkPlayer(int id);								// 攻撃
void HitPlayer(int id);								// 被弾時
void DamagePlayer(int id);							// 負傷
void DeadPlayer(int id);							// 死亡
void ResurrectPlayer(int id);						// 復活
void MotionPlayer(int id);							// モーション管理
void ChangeMotionPlayer(int id,
	int* pNow, int* pOld);							// モーション変更検知
void MoveMotionPlayer(int id,
	PlayerMotion* pMotion);							// モーション動作用
void CntMotionPlayer(int id,
	PlayerMotion* pMotion);							// モーションカウント用
void CalcMtxPlayer(void);							// 行列計算
void DrawPlayer(void);								// 描画
void ChangeDiffuseColPlayer(int player_id,
	int parts_id, int mat_id, D3DXMATERIAL* pMat);	// 拡散光の変更(ゴリ押し)
Player* GetInfoPlayer(void);						// プレイヤー情報を取得
void PrintDebugPlayer(void);						// プレイヤーのデバッグ表示

#endif