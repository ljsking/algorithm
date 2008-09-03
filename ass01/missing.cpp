#include <stdio.h>
#include <algorithm>
int *v=new int[9999];int main(){FILE *i=fopen("missing.inp","r");int *d=v;while(!feof(i))fscanf(i,"%d",d++);std::sort(v+2,--d);for(v=v+2;v!=d-1;v++)if(*v+1!=*(v+1))fprintf(fopen("missing.out","w"),"%d",*v+1);return 0;}