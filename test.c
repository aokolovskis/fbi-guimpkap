#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t * shiftLeft(	       uint32_t *t,	       uint32_t *A,  uint32_t shiftcount );
f2m_mult (uint32_t t, uint32_t *A,uint32_t *B,uint32_t *C );

void testeqprint(char * testname,uint32_t testnr,uint32_t *t,uint32_t *A,uint32_t *B){
  if (f2m_is_equal(t,A,B)){
    printf( "%s %d PASSED\n",testname,testnr);
  } else {
    printf( "%s %d FAILED\n",testname,testnr);
    printf("    A: ");
    f2m_print(t,A);
    printf("       ");
    f2m_print_human(t,A);
    printf("\n");
    printf("    B: ");
    f2m_print(t,B);
    printf("       ");
    f2m_print_human(t,B);
    printf("\n");
  }
}

void euqualstest(){
  uint32_t t = 2;
  uint32_t a[2] = {0x00000001,0x80000000};
  uint32_t b[2] = {0x00000001,0x80000000};
  if (f2m_is_equal(2,a,b)){
    	printf( "euqualstest 1 PASSED\n" );
  } else {
    	printf( "euqualstest 1 FAILED\n" );
  }
}

void shifttest(){
  uint32_t t = 2;
  uint32_t a[2] = {0x00000001,0x40000000};
  uint32_t count = 1;

  
  uint32_t b[2] = {0x00000002,0x80000000};
  uint32_t c[3] = {0x00000004,0x00000000,0x00000001};

  shiftLeft(&t,a,count);

  if (f2m_is_equal(t,a,b)){
    	printf( "shiftLeft 1 PASSED\n" );
	
  } else {
    	printf( "shiftLeft 1 FAILED\n" );
  }

  uint32_t * ptr =   shiftLeft(&t,a,count);
  if (ptr !=  NULL){
    if (f2m_is_equal(t,ptr,c)){
    	printf( "shiftLeft 2 PASSED\n" );
    } else {
      printf( "shiftLeft 2 FAILED\n" );
      printf("t:%d\n",t);
      f2m_print(t,ptr);
    }
  } else {
    printf( "shiftLeft 2 FAILED\n" );
    printf("t:%d\n",t);
  }

  uint32_t e[4] = {0x00000000,0x00000002,0x80000000};
  shiftLeft(&t,ptr,31);
   if (f2m_is_equal(t,ptr,e)){
     printf( "shiftLeft 3 PASSED\n" );
    } else {
     printf( "shiftLeft 3 FAILED\n" );
   }

   uint32_t f[4] = {0x00000000,0x00000004,0x00000000,0x00000001};
   uint32_t * a_ptr =   shiftLeft(&t,ptr,1);
  
  if (ptr !=  NULL){
    if (f2m_is_equal(t,a_ptr,f)){
    	printf( "shiftLeft 4 PASSED\n" );
    } else {
      printf( "shiftLeft 4 FAILED\n" );
      f2m_print(3,ptr);
      printf("\n");
      printf("t:%d\n",t);
      f2m_print(t,a_ptr);
      printf("\n");
      f2m_print(4,f);
    }
  } else {
    printf( "shiftLeft 3 FAILED\n" );
    printf("t:%d\n",t);
  }
  
}


void multtest(){
  uint32_t t = 1;
  uint32_t testnr = 1;
  uint32_t z[1] = {0x0};
  uint32_t a[1] = {0x00000001};  //1
  uint32_t b[1] = {0x00000002};  //z
  uint32_t c[1] = {0x00000003};  //z+1
  uint32_t d[1] = {0x00000006};  
  uint32_t e[1] = {0x00000007}; //z^3+z+1 
  
  uint32_t f[1] = {0x80000000};
  uint32_t g[1] = {0x00000002};
  uint32_t h[2] = {0x0,0x00000001};





  uint32_t j[6] = { 0xA9, 0x100, 0x0, 0x0, 0x0, 0x0 };
  uint32_t k[12] = { 0x4441, 0x0, 0x10000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0  };


  uint32_t r1[1]  = {0x0};
  uint32_t r2[2]  = {0x0,0x0};
  uint32_t r12[12] ;
  initZero(12,r12);



  

  f2m_mult (t,z,z, r1);
  testeqprint("multtest",testnr++,t,z,r1);
  initZero(t,r1);  

  f2m_mult (t,a,b, r1);
  testeqprint("multtest",testnr++,t,b,r1);
  initZero(t,r1);

  f2m_mult (t,a,c, r1);
  testeqprint("multtest",testnr++,t,c,r1);
  initZero(t,r1);

  f2m_mult (t,b,c, r1);
  testeqprint("multtest",testnr++,t,d,r1);
  initZero(t,r1); 
  
  f2m_mult (t,f,g, r2);
  testeqprint("multtest",testnr++,2,h,r2);
  initZero(t,r2); 


  f2m_mult (6,j,j, r12);
  testeqprint("multtest",testnr++,12,k,r12);
  initZero(12,r12);




}


void testSquaring()
{
	printf("Testing squaring\n");
	
	//Test 1
	
	// x^40 + x^7 + x^5 + x^3 + 1
	uint32_t input1[6] = { 0xA9, 0x100, 0x0, 0x0, 0x0, 0x0 };
	uint32_t result1[12];
	f2m_square(6, input1, result1);	
	// x^80 + x^14 + x^10 + x^6 + 1
	uint32_t validResult1[12] = { 0x4441, 0x0, 0x10000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
	assert(f2m_is_equal(12, result1, validResult1));
	
	//Test 2
	
	// x^112 + x^32 + x^16 + x^8 + x^4 + x^2 + x^1
	uint32_t input2[6] = { 0x10116, 0x1, 0x0, 0x10000, 0x0, 0x0 };
	uint32_t result2[12];
	f2m_square(6, input2, result2);
	// x^224 + x^64 + x^32 + x^16 + x^8 + x^4 + x^2
	uint32_t validResult2[12] = { 0x10114, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0 };
	assert(f2m_is_equal(12, result2, validResult2));
	
	//Test3
	
	// x^191 + x^112 + x^32 + x^30 + x^29 + x^27 + x^26 +x^23 +x^21 +x^18 +x^17 +x^14 +x^13 +x^12 +x^7 +x^6 + x^3 + x^2 +x^1 + 1
	uint32_t input3[6] = { 0x6CA670CF, 0x1, 0x0, 0x10000, 0x0, 0x80000000 };
	uint32_t result3[12];
	f2m_square(6, input3, result3);
	// x^382 + x^224 + x^64 + x^60 + x^58 +x^52 + x^46 + x^42 + x^38 + x^36  +x^34 + x^28 + x^26 + x^14 +x^12 + x^6 + x^4 + x^2 + 1 
	uint32_t validResult3[12] = { 0x15005055, 0x14504414, 0x1, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x40000000 };
	assert(f2m_is_equal(12, result3, validResult3));
	
	printf("Tests passed\n");
}

void testInvers()
{
	// TODO
}

int main (int argc, const char* argv[] )
{
	hello_world();
	euqualstest();
	shifttest();
	multtest();
	testSquaring();
}
