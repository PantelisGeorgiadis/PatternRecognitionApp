#include "stdafx.h"
#include "FastMath.h"
#include <cmath>

CFastMath::CFastMath()
{

}

CFastMath::~CFastMath()
{

}

double CFastMath::FastSqrt(double n)
{
	
	
// 	_asm fld qword ptr [esp+4]
// 	_asm fsqrt
// 	_asm ret 8
	return sqrt(n);

	
	
} 
