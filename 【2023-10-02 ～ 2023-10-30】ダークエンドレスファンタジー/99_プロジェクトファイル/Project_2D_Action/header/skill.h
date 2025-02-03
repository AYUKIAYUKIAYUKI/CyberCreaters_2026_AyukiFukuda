//************************************************
//
//スキル処理、ヘッダファイル[skill.h]
//Author：福田歩希
//
//************************************************
#ifndef _SKILL_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _SKILL_H_	//(二重インクルード防止、マクロ定義する)

//マクロ定義

/*画像パス系*/
#define	TEXTURE_SKILL	"data\\TEX\\skillicon01.png"
#define	TEXTURE_SKILL_CHARGE	"data\\TEX\\black.png"

#define AMOUNT_POLYGON_SKILL	(2)	//ライフゲージのポリゴン最大数
#define AMOUNT_TEX_SKILL	(2)	//ライフゲージのテクスチャ総数

//ライフゲージ情報の列挙型
typedef struct
{
	int nStyle;			//種類
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//向き
	D3DXCOLOR col;		//色
	int nCntTex;		//テクスチャ変更
	float fTexSpan[2];	//テクスチャ幅
	float fRadius[2];	//半径
	float fLength[2];	//対角線
	float fAngle[2];	//角度
}SKILL;

//プロトタイプ宣言

/*生成*/
void Init_Skill(void);

/*破棄*/
void Uninit_Skill(void);

/*更新*/
void Update_Skill(void);

/*描画*/
void Draw_Skill(void);

/*にデータを付与*/
void SetInfo_Skill(void);

/*のバーテックスを更新*/
void Update_Pos_Skill(void);

/*のバーテックスカラーを更新*/
void Update_Col_Skill(void);

/*のテクスチャアニメーション処理*/
//void Update_Tex_Skill(void);

/*のデータを取得*/
SKILL* GetInfo_Skill(void);

#endif