#include <stdio.h>
#define N 45001
int MK[N]={0},SQ[213];

int main(){
    int i,j,k,t,c;
    for(i=1;i<213;++i)SQ[i]=i*i;
    for(i=1;i<213;++i)
       for(j=i+1;j<213&&(k=SQ[i]+SQ[j])<N;++j)
         MK[k]=1;
    for(i=5;i<22501;++i)
        if(MK[i]==1)
          for(j=2;(k=j*i)<N;++j)
             MK[k]=j;
    scanf("%d",&t);
    while(t--){
       scanf("%d",&c);
       printf("%s\n",MK[c]?"Yes":"No");}
    return 0;}

   