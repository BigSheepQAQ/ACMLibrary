#include <bits/stdc++.h>
#define LL long long
using namespace std;
int main(void) {
    int n,l,t; cin>>n>>l>>t;//scanf("%d%d%d",&n,&l,&t);
    assert(0<=n&&n<=1000000);
    assert(2<=l&&l<=1000000000);
    assert(0<=t&&t<=1000000);
    int ans=0;
    for (int i=0;i<n;i++) {
        int x,d;
        cin>>x>>d;//scanf("%d%d",&x,&d);
        assert(x>0 && x<l);
        assert(1<=d && d<=2);
        x=x+(d==1?t:-t);
        if (x>0&&x<l) ans++;
    }
    printf("%d\n",ans+1);
    return 0;
}

