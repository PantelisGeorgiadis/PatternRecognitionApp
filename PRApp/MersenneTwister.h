#if !defined(AFX_MERSENNETWISTER_H__56F8A4B8_73B4_48AA_9AAB_B43F2DE44C21__INCLUDED_)
#define AFX_MERSENNETWISTER_H__56F8A4B8_73B4_48AA_9AAB_B43F2DE44C21__INCLUDED_

//  Random Number generator 'Mersenne Twister'						//                               
                                                                            
//  This random number generator is described in the article by		//               
//  M. Matsumoto & T. Nishimura, in:                                //          
//  ACM Transactions on Modeling and Computer Simulation,           //          
//  vol. 8, no. 1, 1998, pp. 3-30.                                  //          
//  Details on the initialization scheme can be found at            //          
//  http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html		//			

#define MERS_N   624
#define MERS_M   397
#define MERS_R   31
#define MERS_U   11
#define MERS_S   7
#define MERS_T   15
#define MERS_L   18
#define MERS_A   0x9908B0DF
#define MERS_B   0x9D2C5680
#define MERS_C   0xEFC60000

enum Architecture {LITTLEENDIAN, BIGENDIAN, NONIEEE};

class CMersenneTwister 
{ 
public:
	
	CMersenneTwister(unsigned long ulSeed) { RandomInit(ulSeed); }
	void RandomInit (unsigned long ulSeed);
	void RandomInitByArray (unsigned long ulSeeds[], int iLength);
	int IRandom (int iMin, int iMax);
	double Random (void);
	unsigned long BRandom (void);

protected:
	
	unsigned long mt[MERS_N];
	int mti;
	
	Architecture Arch;

};    

#endif 
