#include<bits/stdc++.h>
using namespace std;
const long long ha = 1e9+7;
long long f[100010];

int main(){
    f[0]=f[1]=1;
    for (int i=2;i<=100000;++i){
        f[i]=(((i-1)*f[i-2])%ha+(i*f[i-1])%ha)%ha;
    }
    int n;
    cin>>n;
    cout<<f[n]<<"\n";
    return 0;
}
