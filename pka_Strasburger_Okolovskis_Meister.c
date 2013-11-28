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
 * Okolovskis, Aleksjes, Matr.-Nr
 * Meister, Patric, Matr.-Nr
 *
 */
 
#include <stdio.h>
#include <stdint.h>

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
  /* TODO */
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
		A[i] = 0;       
	}     
}

 /*
 * FUNCTION
 * Initializes the given array A with value 1
 *
 * INPUT
 *	t length of the Array
 *	array A
 */
void initOne(uint32_t t, uint32_t *A)
{
	A[0] = 1;
	uint32_t i;
	for(i = 1; i < t; i++)
	{
		A[i] = 0;       
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
	uint32_t i;
	for(i = t - 1; i >= 0; i--)
	{
		if(A[i] == 0)
		{
			continue;
		}
		
		uint32_t y;
		uint32_t shiftMask = 0x80000000;
		for(y = 31; y >= 0; y--)
		{
			if(A[i] & shiftMask)
			{
				return y + (i*32);
			}
			
			shiftMask >>= 1;
		}		
	}
}

 /*
 * FUNCTION
 * Calculates the square of an polynomial
 *
 * INPUT
 *	t length of the Arrays
 *	array A
 *  array B 
 * OUTPUT
 *
 * DESCRIPTION/REMARKS
 *
 */
 void poly_square(uint32_t t, uint32_t *A, uint32_t *B)
 {
	// Precomputation of lookup table T
	uint32_t T[256];
	initZero(256, T);
	int i;
	for(i = 0; i <= 255; i++)
	{
		int z;
		int shiftMask = 1;
		for(z = 0; z < 8; z++)
		{
			T[i] |= (i & shiftMask) << z;                 
			shiftMask = shiftMask << 1;
		}		
	}
     // squaring
	int mask = 0xFF;
	uint32_t y;
	for(y = 0; y < t; y++)
	{
		int b0 = A[y] & mask;
		int b1 = (A[y] >> 8) & mask;
		int b2 = (A[y] >> 16) & mask;		
		int b3 = (A[y] >> 24) & mask;
		
		B[2*y] = T[b1] | T[b0];
		B[2*y + 1] = T[b3] | T[b2];
	}
}

 /*
 * FUNCTION
 * Calculates the multiplicative inverse of polynomial A
 *
 * INPUT
 *	t length of the Arrays
 *	array A 
 *  array F
 *  array I
 *
 */
void poly_calculateInverse(uint32_t t, uint32_t *A, uint32_t *F, uint32_t *I)
{
	uint32_t u[t], v[t], g1[t], g2[t], one[t];

	copy(t, A, u);	
	copy(t, F, v);
	initOne(t, g1);	
	initZero(t, g2);	
	initOne(t, one);
	
	while(!f2m_is_equal(t, u, one) && !f2m_is_equal(t, v, one))
	{
		// u is divisible by z, if its lowest power is zero
		while(u[0] & 1 == 0)
		{
			// TODO
		}
		
		while(v[0] & 1 == 0)
		{
			// TODO
		}
		
		if(getDegree(t, u) > getDegree(t, v))
		{
			// TODO
		}
		else
		{
			// TODO
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
 *   main 
 */
int main(void)
{
  //srand(1);
  uint32_t a[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0xE1F3CD03};
  uint32_t b[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0xE1F3CD03};
  uint32_t i[6];
//  poly_calculateInverse(6, a, b, i);
//  poly_square(6, a, b);
//  printf("\ntest_ecc_b163: %d\n",test_ecc_b163());
  return 0;
}
