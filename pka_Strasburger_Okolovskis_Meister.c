/* 
 * LECTURE 
 *   Implementierung moderner Public-Key-Algorithmen
 *   by Michael Braun, Wintersemester 2013/2014
 *
 * PRACTICAL
 *   Implementation of an Ansi C library for elliptic curves 
 *   over binary fields.
 *
 * TEAM
 * Strasburger, Martin, 729235
 * Okolovskis, Aleksjes, 717782
 * Meister, Patric, Matr.-Nr
 *
 */
 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

const uint32_t WORD = 32;


 /*
 * FUNCTION
 * 
 *
 * INPUT
 *
 *
 * OUTPUT
 *
 * DESCRIPTION/REMARKS
 * 
 */


uint32_t * shiftLeft(
	       uint32_t *t, 
	       uint32_t *A, 
	       uint32_t shiftcount
	       
	       )
{
	uint32_t i, upperMask;
	//uint32_t *out;
	upperMask = 0xFFFFFFFF;

        uint32_t carries = A[*t-1] & (upperMask << WORD-shiftcount);
	
	
	if (carries > 0 ){
	  uint32_t* out = malloc((*t+1)*sizeof(uint32_t));
          out[*t] = carries >> (WORD-shiftcount);
	  for(i = *t-1; i >0;i--)
	    {
	      out[i] =  (upperMask) & (A[i] << shiftcount);
	      out[i] |= (upperMask) & (A[i-1] >> (WORD-shiftcount));
	    }
	  out[0] = A[0] << shiftcount;
	  (*t)++;
	  return out;
	} else {
	  for(i = *t-1; i > 0;i--)
	    {
	      A[i] = A[i] << shiftcount;
	      A[i] |= (A[i-1] >> (WORD-shiftcount)); 
	    }
	 A[0] = A[0] << shiftcount; 
	 return NULL;
	}
}





/*
 * Lookup table required for squaring
 */
uint32_t* lookup_table = NULL;

/*
 * FUNCTION
 *   f2m_rand
 *
 * INPUT
 *   + length t of array A
 *   + bit length m of value represented by A
 *
 * OUTPUT
 *   + random m-bit value in array A
 * 
 * RETURN
 *   -
 * 
 * DESCRIPTION/REMARKS
 *   The random number generator "rand()" is used. The memory of A must
 *   already be allocated before the function is called.
 */
void f2m_rand(
  uint32_t t,
  uint32_t m,
  uint32_t *A
)
{
  uint32_t i;
  for (i = 0; i < t-1; i++) A[i] = rand();
  A[t-1] = rand() & (0xFFFFFFFF >> (32 - m % 32));
}

/*
 * FUNCTION
 *   f2m_print
 *
 * INPUT
 *   + length t of array A
 *   + array A 
 *
 * OUTPUT
 *   -
 * 
 * RETURN
 *   -
 * 
 * DESCRIPTION/REMARKS
 *   The function prints the array A in hexadecimal representation
 *   onto the sceen. The least significant bit is aligned to the
 *   right hand side.
 */
void f2m_print_human(
  uint32_t t,
	uint32_t *A
)
{ 
  uint32_t i;
  bool first = true;
  printf("f(z) = ");
  for (i=t;i>0;) {
    i--;
    uint32_t j; 
    uint32_t mask = 0x80000000;
    for(j=0; j < 32 ; j++){
      if (A[i]&(mask>>j)){
	if (first) {
	  first = false;
	} else {
	  printf(" + ");
	}
	int exp = i*32+(31-j);
	if (exp == 0) {
	   printf("1");
	} else if (exp == 1){
	   printf("z");
	}else {
	  printf("z^%d",exp);
	}
      }
    }
  }
  if (first) {
    printf("0");
  }
  printf("\n");
}


/*
 * FUNCTION
 *   f2m_print
 *
 * INPUT
 *   + length t of array A
 *   + array A 
 *
 * OUTPUT
 *   -
 * 
 * RETURN
 *   -
 * 
 * DESCRIPTION/REMARKS
 *   The function prints the array A in hexadecimal representation
 *   onto the sceen. The least significant bit is aligned to the
 *   right hand side.
 */
void f2m_print(
  uint32_t t,
	uint32_t *A
)
{ 
  uint32_t i;
  printf("0x");
  for (i = 0; i < t; i++) printf("%.8X ",A[t-i-1]);
}


/* 
 * FUNCTION 
 *   f2m_is_equal
   *
   * INPUT
   *   + length t of all arrays
   *   + array A 
   *   + array B
   * 
   * OUTPUT
   *   -
   *
   * RETURN 
   *   + 1 (=true) if the content of A and B is equal
   *   + 0 (=false) otherwise
   *
   * DESCRIPTION/REMARKS
   *   -
   */
  uint32_t f2m_is_equal(
    uint32_t t,
    uint32_t *A,
    uint32_t *B
  )
  {
    uint32_t i;
    for (i = 0; i < t; i++) if (A[i] != B[i]) return 0;
    return 1;
  }

  /* 
   * FUNCTION 
   *   Creates of copy of a polynomial
   *
   * INPUT
   *   + length t of all arrays
   *   + array A 
   *   + array B
   */
  void copy(uint32_t t, uint32_t *A, uint32_t *B)
  {	
	  uint32_t i;
	  for(i = 0; i < t; i++)
	  {
		  B[i] = A[i];
	  }
  }


 /* 
   * FUNCTION 
   *  Initalizes an Array with Zeros
   *
   * INPUT
   *   + length t of array
   *   + array A 
   */

void init_zero(uint32_t t, uint32_t *A)
{
  uint32_t i;
  for(i = 0; i < t; i++){
      A[i] = 0 ;
  }
}

  /* 
   * FUNCTION 
   *   Multiplies to Polynomial 
   *
   * INPUT
   *   A as Poly
   *   B as Poly
   *   C as Result 
   *   + array length of A as tA
   *   + array length of B as tB
   *
   * DESCRIPTION/REMARKS
   *   The memory of C must already be allocated before the function is called.
   *   C musst allso been zero initaliced
   */
void f2m_mult (
	       uint32_t t,
	       uint32_t *A,
	       uint32_t *B,
	       uint32_t *C
	       )
{
  uint32_t * B_copy = (uint32_t *) malloc(t*sizeof(uint32_t));
  copy(t,B,B_copy);
  uint32_t t_b_copy = t;  

  uint32_t k,j;
  for (k=0;k<WORD;k++){
     for (j=0;j<t;j++){
       uint32_t working_bit = A[j]&(0x1<<k);
	 if (working_bit>0){
	   uint32_t truncated_c_index;
     //  f2m_print(2*t,C);
     //  printf("\n");
     //  f2m_print(t_b_copy,B_copy);
     //  printf("\n");
       for (truncated_c_index = j;truncated_c_index < (t_b_copy+j); truncated_c_index++){

	     C[truncated_c_index] = (uint32_t) (C[truncated_c_index] ^ B_copy[truncated_c_index-j]);

	   }
	  
	 //	 C{j} := C{j} XOR B
       }
     }
     if (k != (WORD-1)){
       uint32_t* ptr = shiftLeft(&t_b_copy,B_copy,1);
       if (ptr){
	  free(B_copy);
	  B_copy = ptr;
       }
     }
  }
  free(B_copy);

  //C=0;
  //FOR k := 0 TO W-1 DO
  //   FOR j := 0 TO t-1 DO
  //      IF BIT(A[j], k) = 1 THEN
  //       C{j} := C{j} XOR B 
  // IFk≠W-1THENB:=B<<1
  //RETURN (C)
}
 
/*
* FUNCTION
*   Reduces the result of a polynomial multiplication
*
* INPUT
*   C as Poly
*
* OUTPUT
*   -
*
* DESCRIPTION/REMARKS
*   C must be a result of a polynomial multiplication (Grade < 2m - 2)
*/
void f2m_reduce(uint32_t *C)
{
	uint32_t j, t;

	for (j = 10; j > 5; j--)
	{
		t = C[j];
		C[j - 6] = C[j - 6] ^ (t << 29);
		C[j - 5] = C[j - 5] ^ (t << 4) ^ (t << 3) ^ (t) ^ (t >> 3);
		C[j - 4] = C[j - 4] ^ (t >> 28) ^ (t >> 29);
	}

	t = (C[5] >> 3) << 3;
	C[0] = C[0] ^ (t << 4) ^ (t << 3) ^ (t) ^ (t >> 3);
	C[1] = C[1] ^ (t >> 28) ^ (t >> 29);
	C[5] = C[5] & 0x7;
	//return 0;
}



 /*
 * FUNCTION
 * Initializes the given array A with value 0
 *
 * INPUT
 *	t length of the Array
 *	array A
 */
void initZero(uint32_t t, uint32_t *A)
{
	uint32_t i;
	for(i = 0; i < t; i++)
	{
		A[i] = 0x0;       
	}     
}

 /*
 * FUNCTION
 * Determines the degree of the given polynomial
 *
 * INPUT
 *	t length of the Array
 *	array A
 *  
 * OUTPUT
 * degree of polynomial A
 */
uint32_t getDegree(uint32_t t, uint32_t *A)
{
	int i, y;
	uint32_t shiftMask;
	for(i = t - 1; i >= 0; i--)
	{
		if(A[i] == 0)
		{
			continue;
		}	
		   
		shiftMask = 0x80000000;
		for(y = 31; y >= 0; y--)
		{   
			if(A[i] & shiftMask)
			{
				return y + (i*32);
			}
			
			shiftMask >>= 1;
		}	    
	}

  return 0;	
}

 /*
 * FUNCTION
 * Performs a right shift of the given Array A ( division by z)
 *
 * INPUT
 *	t length of the Array
 *	array A
 * 
 */
void shiftRight(uint32_t t, uint32_t *A)
{
	uint32_t i, lowerMask;
	lowerMask = 1;

	for(i = 0; i < t - 1;i++)
	{
		A[i] >>= 1;
		// preserve lowermost bit of next word
		A[i] |= (A[i+1] & lowerMask) << 31;
	}
	
	// no carry for highest index, saves one loop
	A[t-1] >>= 1;
}

/*
* FUNCTION
* Initializes the lookup table required for function f2m_square
* 
* INPUT
* 
* OUTPUT
* 
* DESCRIPTION/REMARKS
* Is called automatically at first invocation of f2m_square
*/
void initLookupTable()
{
	lookup_table = malloc(256* sizeof(uint32_t));	
	
	// Precomputation of lookup table T
	initZero(256, lookup_table);
	uint32_t i, z, shiftMask;
	for(i = 1; i <= 255; i++)
	{
		shiftMask = 1;
		for(z = 0; z < 8; z++)
		{
			lookup_table[i] |= (i & shiftMask) << z;          
			shiftMask = shiftMask << 1;
		}		
	}
}

 /*
 * FUNCTION
 * Calculates the square of an polynomial
 *
 * INPUT
 *	t length of the Array A
 *	array A
 *  array B 
 * OUTPUT
 *
 * DESCRIPTION/REMARKS
 * Array B must be initialized with the length 2*t.
 */
 void f2m_square(uint32_t t, uint32_t *A, uint32_t *B)
 {	     
	// init lookup table
	if(!lookup_table)
	{	
		initLookupTable();
	}
 
	uint32_t i, b0, b1, b2, b3, tmp;
	for(i = 0; i < t; i++)
	{
		b0 = A[i] & 0xFF;
		tmp = A[i] >> 8;
		b1 = tmp & 0xFF; 
		tmp >>= 8;
		b2 = tmp & 0xFF;		
		tmp >>= 8;
		b3 = tmp & 0xFF;
		
		B[2*i] = (lookup_table[b1] << 16) | lookup_table[b0];
		B[2*i + 1] = (lookup_table[b3] << 16) | lookup_table[b2];
	}
}

 /*
 * FUNCTION
 * Adds polynomial A to polynomial B
 *
 * INPUT
 *	t length of the Arrays
 *	array A 
 *  array F
 *  array C
 */
void f2m_Add(uint32_t t, uint32_t *A, uint32_t *B, uint32_t *C)
{
	uint32_t i;
	for(i = 0; i < t; i++)
	{
		C[i] = A[i] ^ B[i];
	}
}

 /*
 * FUNCTION
 * Calculates the multiplicative inverse of polynomial A
 *
 * INPUT
 *	t length of the Arrays
 *	array A 
 *  array F (irreducibel polynom
 *  array I (result)
 */
void f2m_calculateInverse(uint32_t t, uint32_t *A, uint32_t *F, uint32_t *I)
{
	// init local variables
	uint32_t i, u[t], v[t], g1[t], g2[t], one[t], zero[t];
	for(i = 0; i < t; i++)
	{
		u[i] = A[i];
		v[i] = F[i];
		g1[i] = 0x0;
		g2[i] = 0x0;
		zero[i] = 0x0;
		one[i] = 0x0;
	}
	
	g1[0] = 0x1;
	one[0] = 0x1;
	
	while(!f2m_is_equal(t, u, one) && !f2m_is_equal(t, v, one))
	{    	
		// u is divisible by z, if its lowest power is zero.
		while(!f2m_is_equal(t, u, zero) && (u[0] & 1) == 0)
		{
			// division by z is performed by right shift
			shiftRight(t, u);
			if((g1[0] & 1) == 0)
			{
				shiftRight(t, g1);
			}
			else
			{
				// g1 + f
				f2m_Add(t, g1, F, g1);
				// divide by z
				shiftRight(t, g1);
			}
		}
		
		while(!f2m_is_equal(t, v, zero) && (v[0] & 1) == 0)
		{
			shiftRight(t, v);
			if((g2[0] & 1) == 0)
			{
				shiftRight(t, g2);
			}
			else
			{
				f2m_Add(t, g2, F, g2);
				shiftRight(t, g2);
			}
		}
		
		if(getDegree(t, u) > getDegree(t, v))
		{
			f2m_Add(t, u, v, u);
			f2m_Add(t, g1, g2, g1);
		}
		else
		{
			f2m_Add(t, v, u, v);
			f2m_Add(t, g2, g1, g2);
		}
	}
	
	if(f2m_is_equal(t, u, one))
	{
		copy(t, g1, I);
	}
	else
	{
		copy(t, g2, I);
	}
}

/*
* FUNCTION
*   mult_scalar
*
* INPUT
*   + extension degree m of the binary field 
*   + irreducible polynom F to generate the finite field
*   + elliptic curve parameter a
*   + elliptic curve parameter b
*   + scalar d with maximum bitlength m
*   + x-coordinate xP of point P
*   + y-coordinate yP of point P
*
* OUTPUT
*   + x-coordinate xQ of point Q
*   + y-coordinate yQ of point Q
*
* RETURN
*   -
*
* DESCRIPTION/REMARKS
*   The function calculates the point Q = dP
*/
void mult_scalar(
uint32_t m,
uint32_t *F,
uint32_t *a,
uint32_t *b,
uint32_t *d,
uint32_t *xP,
uint32_t *yP,
uint32_t *xQ,
uint32_t *yQ  
)
{
	// calculate t (size of Arrays)
	uint32_t t = (m/32) + 1;
	
	// init 
	uint32_t Xq[t], Zq[t], Xr[t], Zr[t];	
	uint32_t y;
	for(y = 0; y < t; y++)
	{
		//Zq = 0
		Zq[y] = 0x0;
		Zr[y] = 0x0;
		Xq[y] = 0x0;
		//Xr = xp
		Xr[y] = xP[y];
	}

	// Zr = 1, Xq = 1
	Zr[0] = 0x1;
	Xq[0] = 0x1;

	// helper variables
	uint32_t t2 = t*2;
	
	// PADD (both cases)
	uint32_t XrZqPLUSXqZr[t];
	uint32_t XqZr[t2], XrZq[t2], XqZrXrZq[t2], XrZqPLUSXqZrSquared[t2], xpXrZqPLUSXqZrSquared[t2];
	
	// PDOUBLE d[i] == 1
	uint32_t XrSquard[t2], ZrSquard[t2], XrSquardZrSquard[t2], XrPow4[t2], ZrPow4[t2], bZrPow4[t2];
	
	// PDOUBLE d[i] == 0
	uint32_t XqSquard[t2], ZqSquard[t2], XqSquardZqSquard[t2], XqPow4[t2], ZqPow4[t2], bZqPow4[t2];
	
	int i;
	for(i = t - 1; i > 0; i--)
	{
		uint32_t bitMask = 0x80000000;
		int y;
		for(y = 31; y >= 0; y--)
		{
			initZero(t, XrZqPLUSXqZr);
		
			// init helper variables
			uint32_t z;
			for(z = 0; z < t2; z++)
			{
				// PADD
				XqZr[z] = 0x0;
				XrZq[z] = 0x0;
				XqZrXrZq[z] = 0x0;
				XrZqPLUSXqZrSquared[z] = 0x0;
				xpXrZqPLUSXqZrSquared[z] = 0x0;
				
				// PDOUBLE d[i] == 1
				XrSquard[z] = 0x0;
				ZrSquard[z] = 0x0;
				XrPow4[z] = 0x0;
				ZrPow4[z] = 0x0;
				XrSquardZrSquard[z] = 0x0;
				bZrPow4[z] = 0x0;
				
				// PDOUBLE d[i] == 0
				XqSquard[z] = 0x0;
				ZqSquard[z] = 0x0;
				XqPow4[z] = 0x0;
				ZqPow4[z] = 0x0;
				XqSquardZqSquard[z] = 0x0;
				bZqPow4[z] = 0x0;
			}
			
			if(d[i] & bitMask == 1)
			{	
				// (Xq, Zq) = PADD(xP, Xq, Zq, Xr, Zr)
				// Xq = xp*(Xr*Zq + Xq*Zr) ^2 + Xq*Zr*Xr*Zq
				// Zq = (Xr*Zq + Xq*Zr) ^ 2
				
				// Xq*Zr, length = t*2			
				f2m_mult(t, Xq, Zr, XqZr);			
						
				// Xr*Zq, length = t*2
				f2m_mult(t, Xr, Zq, XrZq);
						
				f2m_reduce(XqZr);
				f2m_reduce(XrZq);
			                 
				// XqZr*XrZq, length = t*2
				f2m_mult(t, XqZr, XrZq, XqZrXrZq);
				f2m_reduce(XqZrXrZq);
				
				// (Xr*Zq + Xq*Zr) ^ 2, length = t*2
				f2m_Add(t, XqZr, XrZq, XrZqPLUSXqZr);
				f2m_square(t, XrZqPLUSXqZr, XrZqPLUSXqZrSquared);
				f2m_reduce(XrZqPLUSXqZrSquared);
				
				// Zq result
				copy(t, XrZqPLUSXqZrSquared, Zq);
				
				// xP * (Xr*Zq + Xq*Zr) ^ 2, length = t*2
				f2m_mult(t, xP, XrZqPLUSXqZrSquared, xpXrZqPLUSXqZrSquared);
				f2m_reduce(xpXrZqPLUSXqZrSquared);
				
				// (Xr*Zq + Xq*Zr) ^ 2 + XqZr*XrZq = Xq result
				f2m_Add(t, xpXrZqPLUSXqZrSquared, XqZrXrZq, Xq);
				
				// (Xr, Zr) = PDOUBLE (b, Xr, Zr)
				// Xr = (Xr^2)^2 + b*(Zr^2)^2
				// Zr = Xr^2 * Zr^2

				// Xr^2
				f2m_square(t, Xr, XrSquard);
				f2m_reduce(XrSquard);
				
				// Zr^2
				f2m_square(t, Zr, ZrSquard);
				f2m_reduce(ZrSquard);				
				
				// ZrSquard * XrSquard				
				f2m_mult(t, XrSquard, ZrSquard, XrSquardZrSquard);
				f2m_reduce(XrSquardZrSquard);
				
				// Zr result
				copy(t, XrSquardZrSquard, Zr);
				
				// XrSquard ^ 2 = Xr ^ 4
				f2m_square(t, XrSquard, XrPow4);
				f2m_reduce(XrPow4);
				
				// ZrSquard ^ 2 = Zr ^ 4
				f2m_square(t, ZrSquard, ZrPow4);
				f2m_reduce(ZrPow4);
				
				// b * Zr ^ 4
				f2m_mult(t, b, ZrPow4, bZrPow4);
				f2m_reduce(bZrPow4);
				
				// Xr =  Xr ^ 4 + b * Zr ^ 4 result
				f2m_Add(t, XrPow4, bZrPow4, Xr);
			}
			else
			{
				// (Xr, Zr) = PADD(xP, Xr, Zr, Xq, Zq)
				// Xr = xp(XqZr + XrZq) ^2 + XrZqXqZr
				// Zr = (XqZr + XrZq) ^2

				// Xr*Zq
				f2m_mult(t, Xr, Zq, XrZq);
				f2m_reduce(XrZq);

				// Xq*Zr
				f2m_mult(t, Xq, Zr, XqZr);		
				f2m_reduce(XqZr);
								
				// XqZr*XrZq, length = t*2
				f2m_mult(t, XqZr, XrZq, XqZrXrZq);
				f2m_reduce(XqZrXrZq);
				
				// (Xr*Zq + Xq*Zr) ^ 2, length = t*2
				f2m_Add(t, XqZr, XrZq, XrZqPLUSXqZr);
				f2m_square(t, XrZqPLUSXqZr, XrZqPLUSXqZrSquared);
				f2m_reduce(XrZqPLUSXqZrSquared);
				
				// Zr result
				copy(t, XrZqPLUSXqZrSquared, Zr);
				
				// xP * (Xr*Zq + Xq*Zr) ^ 2, length = t*2
				f2m_mult(t, xP, XrZqPLUSXqZrSquared, xpXrZqPLUSXqZrSquared);
				f2m_reduce(xpXrZqPLUSXqZrSquared);
				
				// Xr result
				f2m_Add(t, xpXrZqPLUSXqZrSquared, XqZrXrZq, Xr);

				// (Xq, Zq) = PDOUBLE (b, Xq, Zq)
				// Xq = (Xq^2)^2 + b*(Zq^2)^2
				// Zq = Xq^2 * Zq^2

				// Xq^2
				f2m_square(t, Xq, XqSquard);
				f2m_reduce(XqSquard);
				
				// Zq^2
				f2m_square(t, Zq, ZqSquard);
				f2m_reduce(ZqSquard);
				
				// Xq^2 * Zq^2 
				f2m_mult(t, XqSquard, ZqSquard, XqSquardZqSquard);
				f2m_reduce(XqSquardZqSquard);
				
				// Zq result
				copy(t, XqSquardZqSquard, Zq);
				
				// Xq^2 ^2 = Xq ^ 4
				f2m_square(t, XqSquard, XqPow4);
				f2m_reduce(XqPow4);
				
				// Zq^2 ^2 = Zq ^ 4
				f2m_square(t, ZqSquard, ZqPow4);
				f2m_reduce(ZqPow4);
				
				// Zq ^ 4 * b
				f2m_mult(t, b, ZqPow4, bZqPow4);
				f2m_reduce(bZqPow4);
				
				// Xq = Xq^4 + b * Zq^4
				f2m_Add(t, XqPow4, bZqPow4, Xq);
			}

			bitMask >>= 1;
		}
	} 
	
	// determin yq
	
	// (Xq / Zq + xp)	
	// Zq^-1
	uint32_t ZqInverse[t];
	initZero(t, ZqInverse);
	f2m_calculateInverse(t, Zq, F, ZqInverse);
	
	// Xq * Zq^-1 = Xq / Zq
	uint32_t Xq_ZqInverse[t2];
	initZero(t2, Xq_ZqInverse);
	f2m_mult(t, Xq, ZqInverse, Xq_ZqInverse);
	f2m_reduce(Xq_ZqInverse);
	
	// Xq / Zq + xP
	uint32_t Xq_ZqInverse_PLUS_xP[t];
	initZero(t, Xq_ZqInverse_PLUS_xP);
	f2m_Add(t, Xq_ZqInverse, xP, Xq_ZqInverse_PLUS_xP);
	
	// (Xr / Zr + xp)	
	// Zr^-1
	uint32_t ZrInverse[t];
	initZero(t, ZrInverse);
	f2m_calculateInverse(t, Zr, F, ZrInverse);
	
	// Xr * Zr^-1 = Xr / Zr
	uint32_t Xr_ZrInverse[t2];
	initZero(t2, Xr_ZrInverse);
	f2m_mult(t, Xr, ZrInverse, Xr_ZrInverse);
	f2m_reduce(Xr_ZrInverse);
	
	// Xr / Zr + xP
	uint32_t Xr_ZrInverse_PLUS_xP[t];
	initZero(t, Xr_ZrInverse_PLUS_xP);
	f2m_Add(t, Xr_ZrInverse, xP, Xr_ZrInverse_PLUS_xP);	
	
	
	// xp^2
	uint32_t xPSquared[t2];
	initZero(t2, xPSquared);
	f2m_square(t, xP, xPSquared);
	f2m_reduce(xPSquared);
	
	// (Xq / Zq + xp) * (Xr / Zr + xp)
	uint32_t term1[t2];
	initZero(t2, term1);
	f2m_mult(t, Xr_ZrInverse_PLUS_xP, Xq_ZqInverse_PLUS_xP, term1);
	f2m_reduce(term1);
	
	// (Xq / Zq + xp) * (Xr / Zr + xp) + xp^2
	uint32_t term2[t];
	initZero(t, term2);
	f2m_Add(t, term1, xPSquared, term2);

	// (Xq / Zq + xp) * (Xr / Zr + xp) + xp^2 + yp
	uint32_t term3[t];
	initZero(t, term3);
	f2m_Add(t, term2, yP, term3);
	
	// (Xq / Zq + xp) *[(Xq / Zq + xp) * (Xr / Zr + xp) + xp^2 + yp]
	uint32_t term4[t2];
	initZero(t2, term4);
	f2m_mult(t, Xq_ZqInverse_PLUS_xP, term3, term4);
	f2m_reduce(term4);
	
	// (Xq / Zq + xp) *[(Xq / Zq + xp) * (Xr / Zr + xp) + xp^2 + yp] + yp
	uint32_t term5[t];
	initZero(t, term5);
	f2m_Add(t, term4, yP, term5);
	
	// xp^-1
	uint32_t xPInverse[t];
	initZero(t, xPInverse);
	f2m_calculateInverse(t, xP, F, xPInverse);
	
	// yq result
	uint32_t result[t2];
	initZero(t2, result);
	f2m_mult(t, xPInverse, term5, result);
	f2m_reduce(result);
	copy(t, result, yQ);
	
	// TODO Rückrechnung von xq
} 

/* 
 * FUNCTION 
 *   test_ecc_b163
 *
 * INPUT
 *   -
 *
 * OUTPUT
 *   -
 *
 * RETURN 
 *   + 0 if test passed
 *   + 1 if test failed
 *
 * DESCRIPTION/REMARKS
 *   The function generates random values a(z) 
 *   from the binary field generated by the polynomial
 *   f(z) = z^163 + z^7 + z^6 + z^3 + 1.
 *   We have: 11001001 = 0xC9.
 */
uint32_t test_ecc_b163()
{
  uint32_t 
		
  m = 163, /* extension degree of binary field */
  t = 6, /* number of 32-bit words needed to store finite field element */
		
  i, /* iteration variable */
		
  xQ[6], /* public key Q */
  yQ[6],
  d[6], /* private key d */
		
  xC[6], /* challenge C */
  yC[6],
  k[6], /* random scalar for challenge generation */
		
  xR[6], /* response R */
  yR[6],
		
  xV[6], /* verification point C */
  yV[6],
	
  f[6] = {0x000000C9, 0x00000000, 0x00000000, 
		  0x00000000, 0x00000000, 0x00000008}, /* irreducible polynomial */
	  
  a[6] = {0x00000001, 0x00000000, 0x00000000, 
		  0x00000000, 0x00000000, 0x00000000}, /* ec parameter a */
		
  b[6] = {0x4A3205FD, 0x512F7874, 0x1481EB10,
          0xB8C953CA, 0x0A601907, 0x00000002}, /* ec parameter b */ 
		
  xP[6] = {0xE8343E36, 0xD4994637, 0xA0991168,
           0x86A2D57E, 0xF0EBA162, 0x00000003}, /* x-coord. of base point */
						 
  yP[6] = {0x797324F1, 0xB11C5C0C, 0xA2CDD545,
           0x71A0094F, 0xD51FBC6C, 0x00000000}, /* y-coord. of base point */
						 
  n[6] = {0xA4234C33, 0x77E70C12, 0x000292FE, 
          0x00000000, 0x00000000, 0x00000004}; /* order of base point */
	
  printf("\n************************************************************\n");
  printf("test: scalar multiplication of EC over GF(2^163)\n");
  printf("\nirreducible polynomial to generate GF(2^163)\n");
  printf("f  = ");f2m_print(t,f); printf("\n");
  printf("\nparameter b to determine elliptic curve E of GF(2^163)\n");
  printf("E: y^2 + xy = x^3 + ax^2 + b\n");
  printf("a  = ");f2m_print(t,a); printf("\n");
  printf("b  = ");f2m_print(t,b); printf("\n");
  printf("\nbase point P\n");
  printf("xP = ");f2m_print(t,xP); printf("\n");
  printf("yP = ");f2m_print(t,yP); printf("\n");
  printf("\norder of base point P\n");
  printf("n  = ");f2m_print(t,n); printf("\n");

  for (i = 0; i < 10; i++) {
    printf("************************************************************\n");
    printf("test %d\n",i);	
    printf("************************************************************\n");
	printf("generate random private key d and corresponding\n");
	printf("public key Q with Q = d * P\n");
	f2m_rand(t,m,d);
	mult_scalar(m,f,a,b,d,xP,yP,xQ,yQ);
	printf("d  = ");f2m_print(t,d); printf("\n");
	printf("xQ = ");f2m_print(t,xQ); printf("\n");
	printf("yQ = ");f2m_print(t,yQ); printf("\n");
		
	printf("************************************************************\n");
	printf("generate random scalar d and challenge C\n");
	printf("with C = k * P\n");
	f2m_rand(t,m,k);
	mult_scalar(m,f,a,b,k,xP,yP,xC,yC);
	printf("k  = ");f2m_print(t,k); printf("\n");
	printf("xC = ");f2m_print(t,xC); printf("\n");
	printf("yC = ");f2m_print(t,yC); printf("\n");

	printf("************************************************************\n");
	printf("generate response R with R = d * C = d * k * P \n");
	mult_scalar(m,f,a,b,d,xC,yC,xR,yR);
	printf("xR = ");f2m_print(t,xR); printf("\n");
	printf("yR = ");f2m_print(t,yR); printf("\n");

	printf("************************************************************\n");
	printf("generate verification point V with V = k * Q = k * d * P\n");
	mult_scalar(m,f,a,b,k,xQ,yQ,xV,yV);
	printf("xV = ");f2m_print(t,xV); printf("\n");
	printf("yV = ");f2m_print(t,yV); printf("\n");
	  if (!f2m_is_equal(t,xV,xR) || !f2m_is_equal(t,yV,yR)) return 1;
  }
  printf("************************************************************\n");
  printf("test scalar multiplications...\n");
  for (i = 0; i < 10000; i++) mult_scalar(m,f,a,b,n,xP,yP,xQ,yQ);
  return 0;
}

/* 
 * FUNCTION
 *   main 
 */
#ifdef TESTING
#else
int main(void)
{	
	//system("pause");
	printf("\ntest_ecc_b163: %d\n",test_ecc_b163());
	return 0;
}
#endif

void hello_world(void){
	printf( "\nHello World\n\n" );
}
