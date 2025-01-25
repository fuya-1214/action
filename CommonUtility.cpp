//--------------------------------------------------------------------------
// チャプター5
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// CommonUtility class
#include "sstream"
#include "CommonUtility.h"

/*
*-------------------------------------------
* 四捨五入
* INPUT:
*    float val : int型に四捨五入するfloat値
* Output:
*    int : 四捨五入した値
*-------------------------------------------
*/
int CommonUtility::Round(float val)
{
	return static_cast<int>(round(val));
}

/*
*-----------------------------------------------------
* 四捨五入
* INPUT:
*    float val : POSITION型に四捨五入するPOSITION_F値
* Output:
*    int : 四捨五入した値
*-----------------------------------------------------
*/
POSITION CommonUtility::Round(POSITION_F val)
{
	POSITION rv;
	rv.x = Round(round(val.x));
	rv.y = Round(round(val.y));

	return rv;
}