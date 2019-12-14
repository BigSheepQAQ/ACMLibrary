#include <stdio.h>
#define M 2019
int rt[2][32],et[8]={2,2,0,-4,-8,-8,0,16};
int FPow(int f,int n){
    int r=1,m=0;
    while(n){
        if(n&1)r=(r*rt[f][m])%M;
        m++;
        n>>=1;}
    return r;}
    
int cal(int n){
    int r1,r2;    
    r1=FPow(0,n);
    r2=((FPow(1,n/8)*et[n%8])%M+M)%M;
    return ((r1+r2)*505)%M;    
}           
int main(){
    int n,i;
    rt[0][0]=10;rt[1][0]=16;
    for(i=1;i<32;++i){
        rt[0][i]=(rt[0][i-1]*rt[0][i-1])%M;
        rt[1][i]=(rt[1][i-1]*rt[1][i-1])%M;}
    while(scanf("%d",&n)!=EOF&&n>0)
         printf("%d\n",cal(n));
    return 0;}


        
