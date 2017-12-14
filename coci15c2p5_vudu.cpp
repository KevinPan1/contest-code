#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000005
#define F first
#define S second
typedef long long LL;

pair<LL,int>temp[MAXN];
int N,BIT[MAXN];
LL P,arr[MAXN],cnt=1,ans;

void update(int x,int v){
    while(x<=N){
        BIT[x]+=v;
        x+=x&-x;
    }
}

LL query(int x){
    LL sum=0;
    while(x){
        sum+=BIT[x];
        x-=x&-x;
    }
    return sum;
}

int main()
{
    scanf("%d",&N);
    for(int i=0;i<N;++i)
        scanf("%lld",&arr[i]);
    scanf("%lld",&P);
    for(int i=0;i<N;++i){
        arr[i]-=P;
        if(i)
            arr[i]+=arr[i-1];
        if(arr[i]>=0)
            ans++;
        temp[i]={arr[i],i};
    }
    sort(temp,temp+N);
    for(int i=0;i<N;++i){
        if(i&&temp[i].S!=temp[i-1].S)
            cnt++;
        arr[temp[i].S]=cnt;
    }
    for(int i=0;i<N;++i){
        ans+=query(arr[i]);
        update(arr[i],1);
    }
    printf("%lld",ans);
    return 0;
}
