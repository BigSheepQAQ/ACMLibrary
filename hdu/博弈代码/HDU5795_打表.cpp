#include<bits/stdc++.h>
using namespace std;

int sg[110];
bool vis[110];
int main() {
	sg[0]=0;
	for(int n=1;n<=20;n++) {
		memset(vis,0,sizeof(vis));
		for(int i=1;i<n;i++) {
			for(int j=1;j<n-i;j++) {
				int k=n-i-j;
				if(k<=0) continue;
				vis[sg[i]^sg[j]^sg[k]]=1;
			}
		}
		for(int i=0;i<n;i++) vis[sg[i]]=1;
		int p=0;
		while(vis[p]) p++;
		sg[n]=p;
	}
	for(int i=1;i<=20;i++) printf("%d ",sg[i]);
	return 0;
}
