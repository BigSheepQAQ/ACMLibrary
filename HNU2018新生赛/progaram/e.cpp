#include<bits/stdc++.h>
using namespace std;
long long ans,x,k,ex;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&x,&k);
        while(k--){
            scanf("%lld",&ex);
        }
        ans = 123456789098765432;
        ans -= (ans%x);
        printf("%lld\n",ans);
    }
    return 0;
}
