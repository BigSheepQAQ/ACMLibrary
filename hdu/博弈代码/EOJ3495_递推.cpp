#include<bits/stdc++.h>
using namespace std;
const int N=21;
int c[(1<<N)];
int main() {
	int n;
	while(~scanf("%d",&n)) {
		memset(c,0,sizeof(c));
		int x,y;
		vector<int> G[N];
		for(int i=1;i<n;i++) {
			scanf("%d%d",&x,&y);
			--x;--y;
			G[x].push_back(y);
			G[y].push_back(x);
		}
		for(int sta=(1<<n)-1;sta>=0;sta--) {
			for(int i=0;i<n;i++) {
				if(sta&(1<<i)) {
					int flag=0;
					for(int j=0;j<(int)G[i].size();j++) {
						int to=G[i][j];
						if(!((1<<to)&sta)) flag=1;
					}
					if(flag) {
						if(c[sta]==0) c[sta^(1<<i)]=1;
					}	
				}
			}
		}
		if(c[0]) puts("First");
		else puts("Second");
	}
	return 0;
}
