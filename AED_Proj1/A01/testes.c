#include    <stdio.h>
#include <stdlib.h>
#define min(a,b,c) (a<b?(a<c?a:c):(b<c?b:c))

int main(){
    int a = 3;
    int b = 4;
    int c =10;
    int z = min(a,b,c);
    printf("%i \n",z);
    return 0;
}