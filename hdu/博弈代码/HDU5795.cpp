#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
using namespace std;
const int inf=(1<<30)-1;
const int maxn=100010;
#define REP(i,n) for(int i=(0);i<(n);i++)
typedef long long ll;
int SG(int x){
    if(x%8==0) return x-1;
    if(x%8==7) return x+1;
    return x;
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        int sum=0;
        int x;
        for(int i=1;i<=n;i++) scanf("%d",&x),sum^=SG(x);
        printf(sum?"First player wins.":"Second player wins.");
        puts("");
    }
    return 0;
}
