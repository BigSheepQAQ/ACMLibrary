#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int h[N],X[N],Y[N];
bool vis[N];
void init() {
    int cc=0;
    for(int i=2;i<N;i++) if(!vis[i]){
        h[i]=i+(++cc);
        vis[i]=1;if(h[i]<N) vis[h[i]]=1;
    }
    for(int i=1;i<N;i+=3) X[i]=1;
    for(int i=2;i<N;i+=3) Y[i]=i+1;
}
inline void G() {puts("B");}
inline void F() {puts("G");}
inline void E() {puts("D");}
int main() {
    init();
    int T;scanf("%d",&T);
    while(T--) {
        int t,x,y;scanf("%d%d%d",&t,&x,&y);
        if(t==1) if(x%2 && y%2) F();else G();
        else if(t==2) if(x==y) F();else G();
        else if(t==4) {
            if(x>y) swap(x,y);
            if(h[x]==y) F();else G();
        }
        else if(t==3) {
            if(x>y) swap(x,y);
            if(X[x]&&x==y) F();
            else if(Y[x]==y) G();
            else E();
        }
    }
    return 0;
}
