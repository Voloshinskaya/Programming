#pragma once
#ifndef _FAC_H_
	#include "fac.h"
#endif

int comb(int n, int k)
{
	return (fac(n)) / ((fac(k)) * (fac(n-k)));
}