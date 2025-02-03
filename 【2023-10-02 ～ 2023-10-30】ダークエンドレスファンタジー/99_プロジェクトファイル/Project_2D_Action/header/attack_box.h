//************************************************
//
//攻撃ボックス処理、ヘッダファイル[attack_box.h]
//Author：福田歩希
//
//************************************************
#ifndef _ATTACK_BOX_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _ATTACK_BOX_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義
#define AMOUNT_POLYGON_ATTACK_BOX	(16)	//プレイヤー攻撃ボックスのポリゴン総数

#define RADIUS_ATTACK_BOX_X	(100.0f)	//横半幅
#define RADIUS_ATTACK_BOX_Y	(100.0f)	//縦半幅

//攻撃ボックスの情報の構造型
typedef struct
{
	int nMode;
	bool bUse;			//使用判定
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//回転
	D3DXCOLOR col;		//色
	float fRadius[2];	//半径
	float fLength[2];	//対角線
	float fAngle[2];	//角度
	int nAppear;		//生成時間
	int nRemain;		//残存時間
}ATTACK_BOX;

//プロトタイプ宣言

/*生成*/
void Init_Attack_Box(void);

/*破棄*/
void Uninit_Attack_Box(void);

/*更新*/
void Update_Attack_Box(void);

/*攻撃ボックスにデータを付与*/
void GiveInfo_Attack_Box(int nCnt);

/*プレイヤー用の攻撃ボックスを調整*/
void Front_Player(int nCnt);

void Front_Bomb(int nCnt);

/*攻撃ボックスのバーテックスを更新*/
void Update_Pos_Attack_Box(void);

/*攻撃ボックスの残存時間が減少*/
void Disapper_Attack_Box(void);

/*当たり判定*/
void HitDetection_Attack_Box(int i);

/*攻撃ボックスのデータを取得*/
ATTACK_BOX* GetInfo_Attack_Box(void);

/*デバッグ用攻撃ボックス可視化描画*/
void Draw_Attack_Box_Debug(void);

#endif