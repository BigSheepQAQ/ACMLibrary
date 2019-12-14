#include<bits/stdc++.h>
using namespace std;

const int N=21;
int dp[(1<<N)+2];
int e[(1<<N)+2];
int n;
int dfs(int x) {
	if(~dp[x]) return dp[x];
	for(int i=0;i<n;i++) {
		if(x&(1<<i) && (e[i]&x)) {
			if(dfs(x^(1<<i))==0) return dp[x]=1;
		} 
	}
	return dp[x]=0;
}
int main() {
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n);
	for(int i=1;i<n;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		x--;y--;
		e[x]|=(1<<y);
		e[y]|=(1<<x);
	}
	if(dfs((1<<n)-1)==1) puts("First");
	else puts("Second");
	return 0;
}

