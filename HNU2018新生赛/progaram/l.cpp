#include <stdio.h>
#define M 2019
#define L 4
#define LP(i) for(i=0;i<L;++i)

void Product(int x[L][L],int y[L][L],int z[L][L]){
     int i,j,k,w[L][L]={0};
     LP(i)LP(j)LP(k)w[i][j]=(w[i][j]+x[i][k]*y[k][j])%M;
     LP(i)LP(j)z[i][j]=w[i][j];}
     
void FPow(int n,int r[L][L]){
     int i,j,A[L][L]={{3,2,2,3},{3,3,2,2},{2,3,3,2},{2,2,3,3}};
     LP(i)LP(j)r[i][j]=i==j?1:0;
     while(n){
        if(n&1)Product(r,A,r);
        Product(A,A,A);
        n>>=1;}}

int cal(int n){
     int r[L][L];
     FPow(n,r);
     return (3*r[0][0]+3*r[0][1]+2*r[0][2]+2*r[0][3])%M;}
     
int main(){
    int n;
    while(scanf("%d",&n)!=EOF&&n>0)
         printf("%d\n",cal(n-1));
    return 0;}


        
