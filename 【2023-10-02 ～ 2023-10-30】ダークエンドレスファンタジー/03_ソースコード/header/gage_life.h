////************************************************
////
////ライフゲージ処理、ヘッダファイル[bg.h]
////Author：福田歩希
////
////************************************************
//#ifndef _GAGE_LIFE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
//#define _GAGE_LIFE_H_	//(二重インクルード防止、マクロ定義する)
//
////マクロ定義
//
///*画像パス系*/
//#define	TEXTURE_GAGE_LIFE	"data\\TEX\\gage_life_f.png"
//#define	TEXTURE_GAGE_HEART	"data\\TEX\\heart.png"
//
//#define AMOUNT_POLYGON_GAGE_LIFE	(2)	//ライフゲージのポリゴン最大数
//#define AMOUNT_TEX_GAGE_LIFE	(2)	//ライフゲージのテクスチャ総数
//
//#define RADIUS_GAGE_LIFE_X	(200.0f)	//横半幅
//#define RADIUS_GAGE_LIFE_Y	(35.0f)	//縦半幅
//
//#define RADIUS_GAGE_HEART_X	(70.0f)	//横半幅
//#define RADIUS_GAGE_HEART_Y	(70.0f)	//縦半幅
//
//#define SPAN_EACH_GAGE_LIFE_X	(225.0f)	//ハートとゲージの位置ずれ
//#define SPAN_EACH_GAGE_LIFE_Y	(15.0f)	//ハートとゲージの位置ずれ
//
////#define SPD_CHANGE_TEX_GAGE_LIFE	(20)	//アニメーション速度
////#define AMOUNT_STYLE_TEX_GAGE_LIFE	(8)	//アニメーション用
//#define SPAN_CHANGE_TEX_GAGE_LIFE	(0.125f)	//アニメーション用
//
////ライフゲージのパーツ分け
//typedef enum
//{
//	GAGE_LIFE_STYLE_GAGE = 0,
//	GAGE_LIFE_STYLE_HEART,
//	GAGE_LIFE_STYLE_MAX,
//}GAGE_LIFE_STYLE;
//
////ライフゲージ情報の列挙型
//typedef struct
//{
//	int nStyle;			//種類
//	D3DXVECTOR3 pos;	//位置
//	D3DXVECTOR3 move;	//移動量
//	D3DXVECTOR3 rot;	//向き
//	D3DXCOLOR col;		//色
//	int nCntTex;		//テクスチャ変更
//	float fTexSpan[2];	//テクスチャ幅
//	float fRadius[2];	//半径
//	float fLength[2];	//対角線
//	float fAngle[2];	//角度
//}GAGE_LIFE;
//
////プロトタイプ宣言
//
///*生成*/
//void Init_Gage_Life(void);
//
///*破棄*/
//void Uninit_Gage_Life(void);
//
///*更新*/
//void Update_Gage_Life(void);
//
///*描画*/
//void Draw_Gage_Life(void);
//
///*ライフゲージにデータを付与*/
//void SetInfo_Gage_Life(void);
//
///*ライフゲージのバーテックスを更新*/
//void Update_Pos_Gage_Life(void);
//
///*背景のバーテックスカラーを更新*/
//void Update_Col_Gage_Life(void);
//
///*ライフゲージのテクスチャアニメーション処理*/
//void Update_Tex_Gage_Life(void);
//
///*ライフゲージのデータを取得*/
//GAGE_LIFE* GetInfo_Gage_Life(void);
//
//#endif