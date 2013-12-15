#include <stdio.h>
#include <assert.h>
#include <stdint.h>

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
	testSquaring();
}
