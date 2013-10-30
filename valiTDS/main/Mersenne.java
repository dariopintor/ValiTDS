package main;

/**
 * Mersenne Twister:
 * <P>
 * This is a Java version of the C-program for MT19937: Integer version.
 * genrand() generates one pseudorandom unsigned integer (32bit)
 * which is uniformly distributed among 0 to 2^32-1  for each
 * call. sgenrand(seed) set initial values to the working area
 * of 624 words. Before genrand(), sgenrand(seed) must be
 * called once. (seed is any 32-bit integer except for 0).
 * Orignally Coded by Takuji Nishimura, considering the suggestions by
 * Topher Cooper and Marc Rieffel in July-Aug. 1997.
 * More information can be found at
 * <A HREF="http://www.math.keio.ac.jp/matumoto/emt.html">http://www.math.keio.ac.jp/matumoto/emt.html</A>.
 * <P>
 * Translated to Java by Michael Lecuyer January 30, 1999
 * Copyright (C) 1999 Michael Lecuyer
 * <P>
 * This library is free software; you can redistribute it and or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later
 * version.
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Library General Public License for more details.
 * You should have received a copy of the GNU Library General
 * Public License along with this library; if not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307  USA
 * <P>
 * Makoto Matsumoto and Takuji Nishimura, the original authors
 * ask "When you use this, send an email to: matumoto@math.keio.ac.jp
 * with an appropriate reference to your work"  You might also point
 * out this was a translation.
 *	<P>
 * REFERENCE
 * M. Matsumoto and T. Nishimura,
 * "Mersenne Twister: A 623-Dimensionally Equidistributed Uniform
 * Pseudo-Random Number Generator",
 * ACM Transactions on Modeling and Computer Simulation,
 * Vol. 8, No. 1, January 1998, pp 3--30.
 *  http://www.axlradius.com/freestuff/Mersenne.java
 */

public class Mersenne
{
	// Period parameters
	private static final int N = 624;
	private static final int M = 397;
	private static final int MATRIX_A = 0x9908b0df;   //	private static final * constant vector a
	private static final int UPPER_MASK = 0x80000000; // most significant w-r bits
	private static final int LOWER_MASK = 0x7fffffff; // least significant r bits


	// Tempering parameters
	private static final int TEMPERING_MASK_B = 0x9d2c5680;
	private static final int TEMPERING_MASK_C = 0xefc60000;
	private static final int UMASK = 0xffffffff;	// unsigned mask for promoting int -> long

	// #define TEMPERING_SHIFT_U(y)  (y >>> 11)
	// #define TEMPERING_SHIFT_S(y)  (y << 7)
	// #define TEMPERING_SHIFT_T(y)  (y << 15)
	// #define TEMPERING_SHIFT_L(y)  (y >>> 18)

	private int mt[]; // the array for the state vector
	private int mti; // mti==N+1 means mt[N] is not initialized
	private int mag01[];
	

	/**
	* Constructor using the default seed.
	*/
	public Mersenne()
	{
		sgenrand(4357);
	}

	/**
	* Constructor using a given seed.
	*
	* @param seed generator starting number, often the time of day.
	*/
	public Mersenne(int seed)
	{
		sgenrand(seed);
	}

	/**
	* Initalize the pseudo random number generator.
	*
	* @param seed from constructor
	*
	*/
	private void sgenrand(int seed)
	{
		mt = new int[N];

		// setting initial seeds to mt[N] using
		// the generator Line 25 of Table 1 in
		// [KNUTH 1981, The Art of Computer Programming
		//    Vol. 2 (2nd Ed.), pp102]
		mt[0]= seed & 0xffffffff;

		for (mti = 1; mti < N; mti++)
			mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;

		// mag01[x] = x * MATRIX_A  for x=0,1
		mag01 = new int[2];
		mag01[0] = 0x0;
		mag01[1] = MATRIX_A;
	}

	/**
	* Generate the next random number.
	*/
	public int genrand()
	{
		int y;

		if (mti >= N)	// generate N words at one time
		{
			int kk;

			for (kk = 0; kk < N - M; kk++)
			{
				y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
				mt[kk] = mt[kk+M] ^ (y >>> 1) ^ mag01[y & 0x1];
			}
			for (; kk < N-1; kk++)
			{
				y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
				mt[kk] = mt[kk+(M-N)] ^ (y >>> 1) ^ mag01[y & 0x1];
			}
			y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
			mt[N-1] = mt[M-1] ^ (y >>> 1) ^ mag01[y & 0x1];

			mti = 0;
		}
  
		y = mt[mti++];
		y ^= y >>> 11;								// TEMPERING_SHIFT_U(y)
		y ^= (y << 7) & TEMPERING_MASK_B;	// TEMPERING_SHIFT_S(y)
		y ^= (y << 15) & TEMPERING_MASK_C;	// TEMPERING_SHIFT_T(y)
		y ^= (y >>> 18);							// TEMPERING_SHIFT_L(y)

		return y; 
	}

//	void initGenRand()
//	{
//	time_t hora;
//	tm * ptm;
//	time(&hora);
//	ptm = gmtime(&hora);
//	sgenrand( (ptm->tm_hour - 2) * (ptm->tm_min + 1) * (ptm->tm_sec + 1) );
//	/*
//	for (j=0; j<1000; j++) {
//	printf("%12u ", genrand());
//	if (j%8==7) printf("\n");
//	}
//	printf("\n");
//	*/
//	}
	
	/**
	* This main() outputs first 1000 generated numbers
	
	public static void main(String args[])
	{ 
		int j;

		Mersenne r = new Mersenne();

		for (j = 0; j < 1000; j++)
		{
			System.out.print((((long)(r.genrand())) & 0xffffffffL) + " ");
			if (j%8==7) System.out.println();
		}
		System.out.println();
	}
	*/

}