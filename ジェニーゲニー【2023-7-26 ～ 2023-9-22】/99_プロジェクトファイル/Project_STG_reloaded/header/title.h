//************************************************
//
//タイトル表示処理、ヘッダファイル[title.h]
//Author：福田歩希
//
//************************************************3
#ifndef _TITLE_H_	//このマクロ定義が過去にされていなかったら1度のみ下の処理を通す
#define _TITLE_H _	//(二重インクルード防止、マクロ定義する)

#include "main.h"

//マクロ定義

/*画像パス系*/
#define	TEXTURE_SKY_TITLE	"data\\TEX\\00_title\\BG_Sky000.jpg"
#define	TEXTURE_CLOUD1_TITLE	"data\\TEX\\00_title\\cloud000.png"
#define	TEXTURE_CLOUD2_TITLE	"data\\TEX\\00_title\\cloud001.png"
#define	TEXTURE_CLOUD3_TITLE	"data\\TEX\\00_title\\cloud002.png"
#define	TEXTURE_ROSES_TITLE	"data\\TEX\\00_title\\roses000.png"
#define	TEXTURE_GARLAND2_TITLE	"data\\TEX\\00_title\\garland001.png"
#define	TEXTURE_GARLAND1_TITLE	"data\\TEX\\00_title\\garland000.png"
#define	TEXTURE_GEAR_TITLE	"data\\TEX\\00_title\\gears000.png"
#define	TEXTURE_PENDANT_TITLE	"data\\TEX\\00_title\\pendant000.png"
#define	TEXTURE_BROOCH_TITLE	"data\\TEX\\00_title\\brooch000.png"
#define	TEXTURE_KANZASHI_TITLE	"data\\TEX\\00_title\\kanzashi000.png"
#define	TEXTURE_CURTAIN_TITLE	"data\\TEX\\00_title\\curtain000.png"
#define	TEXTURE_PIGEON1_TITLE	"data\\TEX\\00_title\\pigeon000.png"
#define	TEXTURE_PIGEON2_TITLE	"data\\TEX\\00_title\\pigeon001.png"
#define	TEXTURE_GEARBIG_TITLE	"data\\TEX\\00_title\\gear000.png"
#define	TEXTURE_GEARFRAME_TITLE	"data\\TEX\\00_title\\gear002.png"
#define	TEXTURE_GEARSMALL_TITLE	"data\\TEX\\00_title\\gear001.png"
#define	TEXTURE_LOGO_TITLE	"data\\TEX\\00_title\\logo000.png"
#define	TEXTURE_PRESS_TITLE	"data\\TEX\\00_title\\title_text000.png"
#define	TEXTURE_WHITE_TITLE	"data\\TEX\\00_title\\whitebese.png"
#define	TEXTURE_BLACK_TITLE	"data\\TEX\\00_title\\blackbase.png"

#define AMOUNT_POLYGON_TITLE	(30)	//ポリゴン数
#define AMOUNT_TEXTURE_TITLE	(30)	//読込みテクスチャ数

#define AMOUNT_USING_TEX_BG_TITLE	(4)		//背景に使ってるテクスチャ数
#define MOVE_SPD_TEX_BG_TITLE	(0.0005f)	//背景のテクスチャ移動速度

#define SKIP_VTX_TO_WHITE_TITLE	(28)		//ホワイトベースポリゴンへ頂点をずらす用
#define CHANGE_SPD_WHITE_COLORA_TITLE	(25)	//ホワイトベースのcolA変更速度

#define SKIP_VTX_TO_LOGO_TITLE	(26)		//ロゴポリゴンへ頂点をずらす用
#define HALF_X_LOGO_TITLE	(462.75f)		//ロゴX全幅
#define MOVE_SPD_POS_LOGO_TITLE	(2.5f)		//ロゴ頂点座標移動速度
#define MOVE_SPD_TEX_LOGO_TITLE	(0.002375f)	//ロゴテクスチャ移動速度

#define AMOUNT_USING_TEX_ROSES_TITLE	(2)	//バラに使ってるテクスチャ数
#define SKIP_VTX_TO_ROSES_TITLE	(4)			//バラポリゴンへ頂点をずらす用
#define CHANGE_SPD_ROSES_COLORA_TITLE	(9)//バラのcolA変更速度

#define SKIP_VTX_TO_CURTAIN_TITLE	(14)	//カーテンポリゴンへ頂点をずらす用
#define MOVE_SPD_POS_CURTAIN_TITLE	(45.0f)	//カーテン頂点座標移動速度

#define AMOUNT_USING_TEX_GARLAND1_TITLE	(2)	//ガーランド1に使ってるテクスチャ数
#define SKIP_VTX_TO_GARLAND1_TITLE	(8)		//ガーランド1ポリゴンへ頂点をずらす用
#define MOVE_SPD_POS_GARLAND1_TITLE	(75.0f)	//ガーランド1頂点座標移動速度

#define SKIP_VTX_TO_KANZASHI_TITLE	(13)	//かんざしポリゴンへ頂点をずらす用
#define MOVE_SPD_POS_KANZASHI_TITLE	(75.0f)	//かんざし頂点座標移動速度

#define SKIP_VTX_TO_BROOCH_TITLE	(12)	//ブローチポリゴンへ頂点をずらす用
#define MOVE_SPD_POS_BROOCH_TITLE	(75.0f)	//ブローチ頂点座標移動速度

#define SKIP_VTX_TO_GEAR_TITLE	(11)	//歯車ポリゴンへ頂点をずらす用
#define MOVE_SPD_POS_GEAR_TITLE	(45.0f)	//歯車頂点座標移動速度

#define SKIP_VTX_TO_PENDANT_TITLE	(10)	//ペンダントポリゴンへ頂点をずらす用
#define MOVE_SPD_POS_PENDANT_TITLE	(30.0f)	//ペンダント頂点座標移動速度

#define AMOUNT_USING_TEX_GARLAND2_TITLE	(2)	//ガーランド2に使ってるテクスチャ数
#define SKIP_VTX_TO_GARLAND2_TITLE	(6)		//ガーランド2ポリゴンへ頂点をずらす用
#define MOVE_SPD_POS_GARLAND2_TITLE	(10.0f)	//ガーランド2頂点座標移動速度

#define AMOUNT_USING_TEX_GEARS_TITLE	(8)		//歯車群に使ってるテクスチャ数
#define AMOUNT_USING_TEX_GEARBIG_TITLE	(2)		//歯車大に使ってるテクスチャ数
#define AMOUNT_USING_TEX_GEARFRAME_TITLE	(4)	//歯車枠に使ってるテクスチャ数
#define AMOUNT_USING_TEX_GEARSMALL_TITLE	(2)	//歯車小に使ってるテクスチャ数
#define SKIP_VTX_TO_GEARS_TITLE	(18)			//歯車群ポリゴンへ頂点をずらす用
#define MOVE_SPD_POS_GEARS_TITLE		(10.0f)	//歯車群頂点座標移動速度
#define SPAN_GEARBIG_TITLE	(372.0f)			//歯車大全幅
#define HALFSPAN_GEARBIG_TITLE	(186.0f)		//歯車大半幅
#define SPAN_GEARFRAME_TITLE	(200.0f)		//歯枠大全幅
#define HALFSPAN_GEARFRAME_TITLE	(100.0f)	//歯枠大半幅
#define SPAN_GEARSMALL_TITLE	(206.0f)		//歯小大全幅
#define HALFSPAN_GEARSMALL_TITLE	(103.0f)	//歯小大半幅
#define ROTATE_SPD_GEARS_TITLE	(0.005f)		//歯車群回転速度

#define AMOUNT_USING_TEX_PIGEONS_TITLE	(2)	//偽ハトに使ってるテクスチャ数
#define SKIP_VTX_TO_PIGEONS_TITLE	(16)	//偽ハトポリゴンへ頂点をずらす用

#define SPAN_PIGEON1_X_TITLE	(336.0f)		//偽ハト1X全幅
#define HALF_SPAN_PIGEON1_X_TITLE	(168.0f)	//偽ハト1X半幅
#define SPAN_PIGEON1_Y_TITLE	(385.0f)		//偽ハト1Y全幅

#define SPAN_PIGEON2_X_TITLE	(420.0f)		//偽ハト2X全幅
#define HALF_SPAN_PIGEON2_X_TITLE	(210.0f)	//偽ハト2X半幅
#define SPAN_PIGEON2_Y_TITLE	(386.0f)		//偽ハト2Y全幅

#define MOVE_SPD_PIGEONS_1_TITLE	(6.0f)		//偽ハト群スライド移動速度

#define SKIP_VTX_TO_PRESS_TITLE	(27)		//プレスポリゴンへ頂点をずらす用
#define CHANGE_SPD_PRESS_COLORA_TITLE	(3)	//プレスのcolA変更速度

#define SKIP_VTX_TO_FADEOUT_TITLE	(29)	//ファードアウトポリゴンへ頂点をずらす用

#define MOVE_SPD_PIGEONS_1_X	(2.0f)
#define MOVE_SPD_PIGEONS_1_Y	(2.0f)
#define MOVE_SPD_PIGEONS_1_Z	(0.01f)
#define MOVE_SPD_PIGEONS_2_X	(2.0f)
#define MOVE_SPD_PIGEONS_2_Y	(2.0f)
#define MOVE_SPD_PIGEONS_2_Z	(0.01f)

//プロトタイプ宣言
void Init_Title(void);
void Uninit_Title(void);
void Update_Title(void);
void Draw_Title(void);
void SetPos_Vtx_Title(void);
void Flash_Animation_Title(void);
void BG_Animation_Title(void);
void TitleLogo_Animation_Title(void);
void Roses_Animation_Title(void);
void Curtain_Animation_Title(void);
void Garland1_Animation_Title(void);
void Kanzashi_Animation_Title(void);
void Brooch_Animation_Title(void);
void Gear_Animation_Title(void);
void Pendant_Animation_Title(void);
void Garland2_Animation_Title(void);
void Gears_Animation_Title(void);
void Gears_Rotate_Title(void);
void Pigeons_Animation_Title(void);
void Pigeons_Rotate_Title(void);
void Press_Animation_Title(void);
void Fadeout_Animation_Title(void);
//float Set_Volume_Title(void);
void Setinfo_TitleLogoEX_Title(void);
void TitleLogo_AnimationEX_Title(void);
bool* StartFadeout(void);

#endif