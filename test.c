#include <stdio.h>
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
    f2m_print_human(t,B);
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

  uint32_t r1[1]  = {0x0};
  uint32_t r2[1]  = {0x0,0x0};

  f2m_print_human(t,e);

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
  f2m_print_human(2,r2);
  initZero(t,r2); 

}

int main (int argc, const char* argv[] )
{
	hello_world();
	euqualstest();
	shifttest();
	multtest();
	
}
