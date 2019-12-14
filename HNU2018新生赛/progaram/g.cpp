#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main(void) {
    int T; scanf("%d",&T);
    while (T--) {
        ll a,b,c,d;
        scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
        if (a==(1ll<<61)&&b==(1ll<<61)&&c==(1ll<<61)&&d==(1ll<<61)) {
            printf("%llu\n",(1ull<<63));
        } else printf("%lld\n",a+b+c+d);
    }
    return 0;
}