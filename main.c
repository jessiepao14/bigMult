#include <stdio.h>
#define __STDC_FORMAT_MACROS
#include<inttypes.h>
#include<limits.h>
#include<string.h>

void printFunc64(uint64_t as[], int sz)
{ 
  for(int j=sz-1; j>=0; j--)
  {
    printf("%016lx ",as[j]);
  }
  printf("\n");
}

uint64_t mult(uint32_t bsNum, uint32_t digit)	
{						
  return ((uint64_t)bsNum * (uint64_t) digit);				
}			
	
uint64_t add(uint32_t resNum, uint32_t s)		
{				
  return ((uint64_t)resNum + (uint64_t)s);				        
}

uint32_t lo(uint64_t s)
{
    return (s & 0xffffffff);
}

uint32_t hi(uint64_t s)
{
    return (s >> 32);
}

void partialProd32(uint32_t as[], const int sz_a, uint32_t bs[], const int sz_b, uint32_t digit, int offset)
{
  uint32_t low = 0;
  uint32_t high = 0;
  uint64_t pps = 0;
  uint64_t addTemp = 0;
  int j =0;
  uint32_t hiTempRes = 0;
  for (; j < sz_b; j++)
	{ 
	  pps = mult(bs[j], digit);
    addTemp = add (as[offset], lo(pps)); 
    as[offset] = lo(addTemp); 
    uint32_t temp = hi(addTemp) + hi(pps);
    uint64_t tempRes = add(as[offset+1], temp) + hiTempRes;
    hiTempRes = hi(tempRes); 
    uint32_t loTempRes = lo(tempRes);
    as[offset+1] = loTempRes;
    offset++;
	}
}

void bigMult64(uint64_t a[], int sz_a, uint64_t b[], int sz_b, uint64_t c[], int sz_c)
{
  int j;
  for (j=0; j < sz_a; j++)
  {
    a[j] = 0;
  }
   
  uint32_t *des = (uint32_t *) a;
  uint32_t *as = (uint32_t *) b;
  uint32_t *bs = (uint32_t*) c;
  
  int k;
  for(k=0; k<sz_c*2; k++)
  { 
    partialProd32(des, sz_a*2, as, sz_b*2, bs[k], k);
  }

  uint64_t *final_a = (uint64_t *) des;
  uint64_t *final_b = (uint64_t *) as;
  uint64_t *final_c = (uint64_t*) bs;

  printf("FINAL ANSWER: \n");
  printFunc64(final_a,sz_a);
}

int main(void) 
{
  uint64_t a_64[3] = {0x1235456765434545,0x2335423453456531,0x4567456765456789};
  uint64_t b_64[4] = {0x0,0x0,0x0,0x1};
  uint64_t dest[7];
  bigMult64(dest,7,a_64,3,b_64,4); 


  return 0;
}