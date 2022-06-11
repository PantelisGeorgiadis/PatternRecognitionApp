#include "stdafx.h"
#include "MersenneTwister.h"

void CMersenneTwister::RandomInit (unsigned long ulSeed){
	
	mt[0]= ulSeed;
	for (mti=1;mti<MERS_N;mti++){
		mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
	}
	
	union{
		double f; 
		unsigned long i[2];
	} convert;

	convert.f = 1.0;
	if (convert.i[1] == 0x3FF00000){
		Arch = LITTLEENDIAN;
	}
	else if (convert.i[0] == 0x3FF00000){
		Arch = BIGENDIAN;
	}
	else{
		Arch = NONIEEE;
	}

}

void CMersenneTwister::RandomInitByArray (unsigned long ulSeeds[], int iLength){
	
	int i, j, k;
	
	RandomInit(19650218UL);
	
	if (iLength <= 0){
		return;
	}
	i = 1;
	j = 0;
	k = (MERS_N > iLength ? MERS_N : iLength);
	
	for (;k;k--){
		mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1664525UL)) + ulSeeds[j] + j;
		i++; 
		j++;
		if (i >= MERS_N){
			mt[0] = mt[MERS_N - 1];
			i=1;
		}
		if (j >= iLength){
			j=0;
		}
	}
	for (k=(MERS_N - 1);k;k--){
		mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1566083941UL)) - i;
		if (++i >= MERS_N){
			mt[0] = mt[MERS_N - 1];
			i=1;
		}
	}
	mt[0] = 0x80000000UL;

} 

unsigned long CMersenneTwister::BRandom (void) {

	unsigned long y;
	
	if (mti >= MERS_N){
		const unsigned long LOWER_MASK = (1LU << MERS_R) - 1; 
		const unsigned long UPPER_MASK = -1L  << MERS_R;  
		static const unsigned long mag01[2] = {0, MERS_A};
		
		int kk;
		for (kk=0;kk<MERS_N-MERS_M;kk++){    
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + MERS_M] ^ (y >> 1) ^ mag01[y & 1];
		}
		
		for (;kk<(MERS_N - 1);kk++){    
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + (MERS_M - MERS_N)] ^ (y >> 1) ^ mag01[y & 1];
		}      
		
		y = (mt[MERS_N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[MERS_N - 1] = mt[MERS_M - 1] ^ (y >> 1) ^ mag01[y & 1];
		mti = 0;
	}
	
	y = mt[mti++];
	y ^=  y >> MERS_U;
	y ^= (y << MERS_S) & MERS_B;
	y ^= (y << MERS_T) & MERS_C;
	y ^=  y >> MERS_L;
	
	return y;

}

double CMersenneTwister::Random (void) {
	
	union {
		double f; 
		unsigned long i[2];
	} convert;
	
	unsigned long r = BRandom();

	switch (Arch){
		case LITTLEENDIAN:
			convert.i[0] =  r << 20;
			convert.i[1] = (r >> 12) | 0x3FF00000;
			return convert.f - 1.0;
		case BIGENDIAN:
			convert.i[1] =  r << 20;
			convert.i[0] = (r >> 12) | 0x3FF00000;
			return convert.f - 1.0;
		case NONIEEE: 
		default:
	;} 
	
	return (double)r * (1. / ((double)(unsigned long)(-1L) + 1.));

}

int CMersenneTwister::IRandom (int iMin, int iMax){
	
	int r; 
	r = int((iMax - iMin + 1) * Random()) + iMin;
	if (r > iMax){
		r = iMax;
	}
	if (iMax < iMin){
		return 0x80000000;
	}
	
	return r;

}


