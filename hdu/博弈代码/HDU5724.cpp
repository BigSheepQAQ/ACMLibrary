#include<bits/stdc++.h>
using namespace std;
const int N=20;
bool vis[N];
int sg[(1<<N)+5];
int n,m;
void init() {
    for(int i=0;i<(1<<20);i++) {
        memset(vis,0,sizeof(vis));
        int last=-1;
        for(int j=0;j<20;j++) {
            if(!(i&(1<<j))) last=j;
            else if(~last) vis[sg[i^(1<<j)^(1<<last)]]=1; 
        }
        for(int j=0;;j++) if(!vis[j]) {sg[i]=j;break;}
    }
}
int main() {
    int T;scanf("%d",&T);
    init();
    while(T--) {
        scanf("%d",&n);
        int ans=0;
        for(int i=1;i<=n;i++) {
            scanf("%d",&m);
            int tt=0;
            for(int j=1;j<=m;j++) {
                int x;scanf("%d",&x);
                tt|=(1<<(20-x));
            }
            ans^=sg[tt];
        }
        if(ans) puts("YES");
        else puts("NO");
    }
    return 0;
}
