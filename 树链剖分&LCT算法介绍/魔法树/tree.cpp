#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

typedef long long ll;
const int N=100001;

int e[N*2],nxt[N*2],head[N];
int dep[N],fa[N],siz[N],w[N],top[N],son[N],End[N];

struct A{
    ll sum,tag;
}t[N*4];

int n,C=0,edge=0;
void add(int x,int y){
    e[++edge]=y;
    nxt[edge]=head[x];
    head[x]=edge;
}

void dfs1(int x,int f,int d){//求size,dep,son,fa 
    dep[x]=d;fa[x]=f;siz[x]=1;
    int i,tp=0;
    for(i=head[x];i;i=nxt[i])
        if(e[i]!=fa[x]){
            dfs1(e[i],x,d+1);
            siz[x]+=siz[e[i]];
            if(siz[e[i]]>tp){tp=siz[e[i]];son[x]=e[i];}
        }
}

void dfs2(int x,int tp){//求dfs序,链的顶端节点 
    w[x]=++C;top[x]=tp;
    if(son[x]) dfs2(son[x],top[x]);
    for(int i=head[x];i;i=nxt[i])
        if(e[i]!=son[x]&&e[i]!=fa[x])
            dfs2(e[i],e[i]);
    End[x]=C;//x所在子树的最大dfs序 
}

void build(int x,int l,int r){//建立线段树 
    t[x].tag=t[x].sum=0;
    if(l==r) return;
    int M=l+r>>1;
    build(x<<1,l,M);
    build(x<<1|1,M+1,r);
}

void pushdown(int x,int l,int r){//在线段树中下传标记 
    if(t[x].tag){
        t[x<<1].tag+=t[x].tag;
        t[x<<1|1].tag+=t[x].tag;
        int M=l+r>>1;
        t[x<<1].sum+=(M-l+1)*t[x].tag;
        t[x<<1|1].sum+=(r-M)*t[x].tag;
        t[x].tag=0;
    }
}

void update(int x,int l,int r,int ql,int qr,int v){//在线段树中更新[ql,qr]节点权值加v 
    if(ql<=l&&qr>=r){
        t[x].sum+=(r-l+1)*v;
        t[x].tag+=v;
        return;
    }
    pushdown(x,l,r);
    int M=l+r>>1;
    if(ql<=M) update(x<<1,l,M,ql,qr,v);
    if(qr>M) update(x<<1|1,M+1,r,ql,qr,v);
    t[x].sum=t[x<<1].sum+t[x<<1|1].sum;
}

ll query(int x,int l,int r,int ql,int qr){//在线段树中查询[ql,qr]的权值和 
    if(ql<=l&&qr>=r) return t[x].sum;
    pushdown(x,l,r);
    int M=l+r>>1;ll sum=0;
    if(ql<=M) sum+=query(x<<1,l,M,ql,qr);
    if(qr>M) sum+=query(x<<1|1,M+1,r,ql,qr);
    return sum;
}

void upd(int x,int y,int z){//修改操作,见课件 
    int f1=top[x],f2=top[y],tmp;
    while(f1!=f2){
        if(dep[f1]<dep[f2]){
            tmp=f1;f1=f2;f2=tmp;
            tmp=x;x=y;y=tmp;
        }
        update(1,1,n,w[f1],w[x],z);
        x=fa[f1];f1=top[x];
    }
    if(dep[x]<dep[y]){tmp=x;x=y;y=tmp;}
    update(1,1,n,w[y],w[x],z);
}

int main()
{	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
    int i,x,y,m,z;char c;
    scanf("%d",&n);
    for(i=1;i<n;i++){
        scanf("%d %d",&x,&y);x++;y++;
        add(x,y);add(y,x);
    }
    dfs1(1,-1,1);
    dfs2(1,1);
    build(1,1,n);
    scanf("%d",&m);
    for(i=1;i<=m;i++){
        scanf("\n%c",&c);
        if(c=='A'){
            scanf("%d %d %d",&x,&y,&z);x++;y++;
            upd(x,y,z);
        }
        else{
            scanf("%d",&x);x++;
            printf("%lld\n",query(1,1,n,w[x],End[x]));
        }
    }
    return 0;
}

