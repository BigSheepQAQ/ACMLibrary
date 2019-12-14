#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int oo=1000000000;

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,root,top;
int ans[100005],s[100005];
int fa[100005],c[100005][2];
int v[100005],mn[100005],size[100005],pos[100005];
bool rev[100005];

struct data{int pos,v;}a[100005];
inline bool operator<(data a,data b){return a.pos<b.pos;}
inline bool cmp(data a,data b){return a.v<b.v||(a.v==b.v&&a.pos<b.pos);}

void update(int x)//上传标记 
{
	int l=c[x][0],r=c[x][1];
	mn[x]=v[x];pos[x]=x;
	if(mn[l]<mn[x]){mn[x]=mn[l];pos[x]=pos[l];}
	if(mn[r]<mn[x]){mn[x]=mn[r];pos[x]=pos[r];}
	size[x]=size[l]+size[r]+1;
}
void pushdown(int x)//下传标记 
{
    int l=c[x][0],r=c[x][1];
	rev[x]^=1;rev[l]^=1;rev[r]^=1;
	swap(c[x][0],c[x][1]);
}
void rotate(int x,int &k)//旋转 
{
    int y=fa[x],z=fa[y],l,r;
    if(c[y][0]==x)l=0;else l=1;r=l^1;
    if(y==k)k=x;
    else {if(c[z][0]==y)c[z][0]=x;else c[z][1]=x;}
    fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
    c[y][l]=c[x][r];c[x][r]=y;
    update(y);update(x);
}
void splay(int x,int &k)
{
	top=0;s[++top]=x;
    for(int i=x;fa[i];i=fa[i])
        s[++top]=fa[i];
    for(int i=top;i;i--)//从上到下下传翻转标记 
        if(rev[s[i]])pushdown(s[i]);
    while(x!=k)
    {
        int y=fa[x],z=fa[y];
        if(y!=k)
        {    
            if(c[y][0]==x^c[z][0]==y)
                rotate(x,k);
            else rotate(y,k);
        }
        rotate(x,k);
    }
}
int find(int x,int rk)//查找第rk个元素 
{
	if(rev[x])pushdown(x);
	int l=c[x][0],r=c[x][1];
	if(size[l]+1==rk)return x;
	else if(size[l]>=rk)return find(l,rk);
	else return find(r,rk-size[l]-1);
}
int querymn(int L,int R)//查询区间中最小值 
{
	int x=find(root,L),y=find(root,R+2);
	splay(x,root);splay(y,c[x][1]);
	int z=c[y][0];
	return pos[z];
}
void rever(int L,int R)//将区间[L,R]翻转 
{
	int x=find(root,L),y=find(root,R+2);
	splay(x,root);splay(y,c[x][1]);
	int z=c[y][0];
	rev[z]^=1;
}
void build(int l,int r,int f)
{
	if(l>r)return;
	if(l==r)
	{
		fa[l]=f;size[l]=1;
		mn[l]=v[l]=a[l].v;pos[l]=l;
		if(l<f)c[f][0]=l;
		else c[f][1]=l;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid-1,mid);build(mid+1,r,mid);
	fa[mid]=f;v[mid]=a[mid].v;update(mid);
	if(mid<f)c[f][0]=mid;
	else c[f][1]=mid;
}
int main()
{   freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	n=read();
	a[1].v=a[n+2].v=oo;mn[0]=oo;
	for(int i=2;i<=n+1;i++)
	{
		a[i].v=read();
		a[i].pos=i;
	}
	sort(a+2,a+n+2,cmp);//按权值排序从小到大,权值相同按位置从小到大排序 
	for(int i=2;i<=n+1;i++)a[i].v=i-1;
	sort(a+2,a+n+2);
	build(1,n+2,0);
	root=(n+3)>>1;
	for(int i=1;i<=n;i++)
	{
		int x=querymn(i,n);
		splay(x,root);
		ans[i]=size[c[x][0]];
		rever(i,ans[i]);
		
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d",ans[i]);
		if(i!=n)printf(" ");
	}
	return 0;
}
