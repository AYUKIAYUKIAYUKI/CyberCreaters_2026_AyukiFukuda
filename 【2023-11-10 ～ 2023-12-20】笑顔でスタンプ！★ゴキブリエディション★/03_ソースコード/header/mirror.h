////************************************************
////
////鏡面効果、ヘッダファイル[mirror.h]
////Author：福田歩希
////
////************************************************
//#include "main.h"
//#include "DxLib.h"
//#include <math.h>
//
//#define MIRROR_SCREEN_WIDTH	(1980)	//鏡に映る映像の取得に使用するスクリーンの横解像度
//#define MIRROR_SCREEN_HEIGHT	(1080)	//鏡に映る映像の取得に使用するスクリーンの縦解像度
//#define MIRROR_POINTNUM	(64)	// 鏡の描画に使用する面の頂点分割数
//#define MIRROR_NUM	(1)	// 鏡の数
//
//FLOAT4 MirrorScreenPosW[MIRROR_NUM][4];	// 鏡に映る映像の取得に使用するクリーンの中の鏡の四隅の座標( 同次座標 )