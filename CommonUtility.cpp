//--------------------------------------------------------------------------
// �`���v�^�[5
// ���@���F����@����
//--------------------------------------------------------------------------
// CommonUtility class
#include "sstream"
#include "CommonUtility.h"

/*
*-------------------------------------------
* �l�̌ܓ�
* INPUT:
*    float val : int�^�Ɏl�̌ܓ�����float�l
* Output:
*    int : �l�̌ܓ������l
*-------------------------------------------
*/
int CommonUtility::Round(float val)
{
	return static_cast<int>(round(val));
}

/*
*-----------------------------------------------------
* �l�̌ܓ�
* INPUT:
*    float val : POSITION�^�Ɏl�̌ܓ�����POSITION_F�l
* Output:
*    int : �l�̌ܓ������l
*-----------------------------------------------------
*/
POSITION CommonUtility::Round(POSITION_F val)
{
	POSITION rv;
	rv.x = Round(round(val.x));
	rv.y = Round(round(val.y));

	return rv;
}