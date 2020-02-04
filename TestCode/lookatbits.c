#include <stdio.h>
//#include <stdint.h>>
#include<inttypes.h>

void print64bits(uint64_t s){

  for (int i = 63; i >= 0; i--){
    printf("%d", ((1ULL << i) & s) ? 1 : 0);
  }
};

void print8bits(uint8_t s){

  for (int i = (8 - 1); i >= 0; i--){
    printf("%d", ((1ULL << i) & s) ? 1 : 0);
  }
};

int main(int argc, char *argv[]){
  
  //char c = 65;
  //int i = 65;
  //long int l = 65;
  //long long int m = 65;

  uint8_t a = 73;
  uint8_t b = 99;
  uint8_t c = (a ^ c);

  uint64_t s = 65;

  // sizeof() print outs bytes.
  //printf("%x\t%c\t%d\t%d\n",c, c, c, sizeof(c));
  //printf("%x\t%c\t%d\t%d\n",i, i, i, sizeof(i);
  //printf"%x\t%c\t%d\t%d\n",l, l, l, sizeof(l);
  
  //print64bits(s);
  printf("a = "); print8bits(a); printf("\n");
  printf("b = "); print8bits(b); printf("\n");
  printf("c = "); print8bits(c); printf("\n");

  printf("a = "); print8bits(a); printf("\n");
  printf("~a = "); print8bits(~a); printf("\n");

  //printf("\t%llx\t%lld\n",s, s);

  return 0;	
}
