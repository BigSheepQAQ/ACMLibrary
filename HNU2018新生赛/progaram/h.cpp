#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string>
#include<string.h>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<stack>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int a[maxn];
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]=-a[i];
	}
	sort(a+1,a+n+1);
	for(int i=2;i<=n;i++){
		a[i]+=a[i-1];
	}
	int ans=0;
	int l,r;
	for(int i=0;i<k;i++){
		cin>>l>>r;
		ans=min(ans,a[r]-a[l-1]);
	}
	cout<<-ans<<endl;
} 