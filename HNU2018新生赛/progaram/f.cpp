#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll ten[20],dp[20][100][2];
ll gao(ll n,int f,int p) {
    if (f==520) {
//        printf("n=%lld, f=%d, p=%d\n",n,f,p);
//        printf("ans = %lld\n",n+1);
        return n+1;
    }
    ll ans=0;
    if (p<=2) {
        for (int i=0;i<=n;i++) {
            if (f==52 && i<10) ans++;
            if (f==5 && i==20) ans++;
        }
    } else {
        ll o=n/ten[p-1];
//        printf("n=%lld, f=%d, p=%d\n",n,f,p);
        for (int i=0;i<o*10;i++) {
            if (f==52 && i<10) ans += dp[p][i][0];
            if (f==5 && i==20) ans += dp[p][i][0];
            ans += dp[p][i][1];
        }
        int nf;
        if (o==5) nf=5;
        else if (f==5 && o==2) nf=52;
        else if (f==52 && o==0) nf=520;
        else nf=0;
        ans += gao(n-o*ten[p-1],nf,p-1);
    }
//    printf("n=%lld, f=%d, p=%d\n",n,f,p);
//    printf("ans = %lld\n",ans);
    return ans;
}
int main(void) {
//    freopen("z.in","r",stdin);
    ten[0]=1; for (int i=1;i<=18;i++) ten[i]=ten[i-1]*10;
    dp[1][0][0]=1;
    for (int i=0;i<100;i++) dp[2][i][0]=1;
    for (int i=3;i<=19;i++) {
        for (int j=0;j<100;j++) {
            for (int k=j%10*10;k<j%10*10+10;k++) {
                if (j*10+k%10==520) dp[i][j][1]+=dp[i-1][k][0];
                else dp[i][j][0]+=dp[i-1][k][0];
                dp[i][j][1]+=dp[i-1][k][1];
            }
//            printf("dp[%d][%02d] = %lld %lld\n",i,j,dp[i][j][0],dp[i][j][1]);
        }
    }
    int T; scanf("%d",&T);
    while (T--) {
        ll n;
        scanf("%lld",&n);
        int p=0; for (ll x=n;x;x/=10) p++;
        ll ans=gao(n,0,p);
        printf("%lld\n",ans);
    }
    return 0;
}
