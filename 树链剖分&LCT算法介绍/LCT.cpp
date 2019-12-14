int access(int v)
{int u=0;
 while (v)
   {splay(v);
    rightson[v]=u;
    update(v);
    u=v;
    v=father[v];
   }
 return u;
}

int lca(int u,int v)
{
	access(u);
	return access(v);
}

int findroot(int v)
{
	access(v);
	splay(v);
	int u=v;
	while (leftson[u]) 
	  u=leftson[u];
	return u;
}

void makeroot(int v)
{
	access(v);
	splay(v);
	reverse[v]^=1;
}

void link(int u,int v)
{
	makeroot(u);
	father[u]=v;
}

void cut(int u,int v)
{
	makeroot(u);
	access(v);
	splay(v);
	leftson[v]=0;
	father[u]=0;
}

bool isroot(int v)
{
	return leftson[father[v]]!=v && rightson[father[v]]!=v;
}

