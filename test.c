#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


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

  shiftLeft(&t,&a,count);

  if (f2m_is_equal(t,a,b)){
    	printf( "shiftLeft 1 PASSED\n" );
	
  } else {
    	printf( "shiftLeft 1 FAILED\n" );
  }

  uint32_t * ptr =   shiftLeft(&t,&a,count);
  uint32_t * array = (uint32_t *) ptr;

  if (f2m_is_equal(t,ptr,c)){
    	printf( "shiftLeft 2 PASSED\n" );
  } else {
    	printf( "shiftLeft 2 FAILED\n" );
	printf("t:%d\n",t);
	f2m_print(t,ptr);
  }
  
  
  
}

int main (int argc, const char* argv[] )
{
	hello_world();
	euqualstest();
	shifttest();
	
}
