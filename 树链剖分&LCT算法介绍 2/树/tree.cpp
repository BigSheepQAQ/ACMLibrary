#include <bits/stdc++.h>
using namespace std;

const int N=300005;

int ch[N][2],xo[N],a[N],rev[N],fa[N],st[N];

bool isroot(int x)//�ж�x�Ƿ���ڵ� 
{
 return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
}

void pushup(int x)//�ϴ�������� 
{
 xo[x]=xo[ch[x][0]]^xo[ch[x][1]]^a[x];
}

void pushdown(int x)//�´����:��ת��� 
{if(rev[x])
   {int l=ch[x][0],r=ch[x][1];
	rev[l]^=1;rev[r]^=1;
	swap(ch[l][0],ch[l][1]);
	swap(ch[r][0],ch[r][1]);
	rev[x]=0;
   }
}

void rotate(int x)//splay��ת 
{int l,r,y=fa[x],z=fa[y];
 if(ch[y][0]==x) l=0;else l=1;r=l^1;
 if(!isroot(y))
  {if(ch[z][0]==y) ch[z][0]=x;
   else ch[z][1]=x;
  }
 fa[x]=z;fa[y]=x;fa[ch[x][r]]=y;
 ch[y][l]=ch[x][r];ch[x][r]=y;
 pushup(y);pushup(x);
}

void splay(int x)//splay���� 
{int p=x,top=0,y,z;
 st[++top]=x;
 while(!isroot(p))
   {p=fa[p];
	st[++top]=p;
   }
 while(top) pushdown(st[top--]);
 while(!isroot(x))
   {y=fa[x];z=fa[y];
	if(!isroot(y))
	  {if(ch[y][0]==x^ch[z][0]==y) rotate(x);
	   else rotate(y);
	  }
	rotate(x);
   }
}

void access(int x)//��x�������ƫ���� 
{for(int y=0;x;y=x,x=fa[x])
   splay(x),ch[x][1]=y,pushup(x);
}

void makeroot(int x)//��x��ɸ� 
{access(x);
 splay(x);
 rev[x]=1;
 swap(ch[x][0],ch[x][1]);
}

int findroot(int x)
{access(x);
 splay(x);
 while(ch[x][0])
   {pushdown(x);
	x=ch[x][0];
   }
 return x;
}

void link(int x,int y)//x��y��һ����,���ߺ�y�Ǹ��ڵ� 
{if(findroot(x)!=findroot(y))
   makeroot(x),fa[x]=y;
}

void cut(int x,int y)//ɾ����(x,y),֮ǰy��x�ĸ��ڵ� 
{makeroot(x);
 access(y);
 splay(y);
 ch[y][0]=0;
 fa[x]=0;
 pushup(y);
}

int main()
{freopen("tree.in","r",stdin);
 freopen("tree.out","w",stdout);
 int n,m,i,x,y,c;
 scanf("%d %d",&n,&m);
 for(i=1;i<=n;i++) scanf("%d",&a[i]);
 for(i=1;i<=m;i++)
   {scanf("%d %d %d",&c,&x,&y);
	if(c==0)
	  {makeroot(x);
	   access(y);
	   splay(y);
	   printf("%d\n",xo[y]);
	  }
	if(c==1) link(x,y);
	if(c==2) cut(x,y);
	if(c==3) splay(x),xo[x]^=a[x]^y,a[x]=y;
   }
 return 0;
}
