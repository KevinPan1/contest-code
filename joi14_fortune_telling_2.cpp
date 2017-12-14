#include <bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define INF 2147483647
#define EPS 1e-9
#define PI 3.141592653589793238462
#define MOD 1000000007
#define REP(i,a,b) for (int i = a; i <= b; i++)
typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<VI > VVI;
typedef vector<PII > VPII;
typedef vector<VPII > VVPII;
typedef map<int,int> MII;

struct Node{
    int left,right,val;
} tree[MAXN*18];

void push_up(int x){
    tree[x].val=max(tree[x*2].val,tree[x*2+1].val);
}

int query(int x,int l,int r){
    if(tree[x].left>=l&&tree[x].right<=r)
        return tree[x].val;
    if(tree[x].left>r||tree[x].right<l)
        return -INF;
    return max(query(x*2,l,r),query(x*2+1,l,r));
}

void update(int x,int idx,int newVal){
    if(tree[x].left==tree[x].right){
        tree[x].val=newVal;
        return;
    }
    if(idx<tree[x*2+1].left)
        update(x*2,idx,newVal);
    else
        update(x*2+1,idx,newVal);
    push_up(x);
}

void build(int x,int l,int r){
    tree[x].left=l;
    tree[x].right=r;
    if(l==r){
        tree[x].val=-INF;
        return;
    }
    build(x*2,l,(l+r)/2);
    build(x*2+1,(l+r)/2+1,r);
    push_up(x);
}

PII last[MAXN];
MII ma;
int N,K,arr[MAXN][2],arr2[MAXN*3],cnt=1,a,q[MAXN],flip[MAXN],BIT[MAXN*3],track;
LL ans;

void update2(int x,int v){
    while(x<=600005){
        BIT[x]+=v;
        x+=x&-x;
    }
}

int query2(int x){
    int sum=0;
    while(x){
        sum+=BIT[x];
        x-=x&-x;
    }
    return sum;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    cin>>N>>K;
    for(int i=0;i<N;++i){
        cin>>arr[i][0]>>arr[i][1];
        arr2[i]=arr[i][0];
        arr2[i+N]=arr[i][1];
    }
    for(int i=0;i<K;++i){
        cin>>q[i];
        arr2[i+2*N]=q[i];
    }
    sort(arr2,arr2+2*N+K);
    for(int i=0;i<N*2+K;++i){
        if(!ma[arr2[i]]){
            ma[arr2[i]]=cnt;
            cnt++;
        }
    }
    build(1,1,cnt-1);
    for(int i=0;i<K;++i)
        update(1,ma[q[i]],i+1);
    for(int i=0;i<N;++i){
        if(arr[i][0]==arr[i][1])
            last[i]={-1,i+1};
        else{
            int temp=query(1,ma[min(arr[i][0],arr[i][1])],ma[max(arr[i][0],arr[i][1])]-1);
            if(temp==-INF)
                last[i]={-1,i+1};
            else{
                last[i]={temp,i+1};
                if(arr[i][0]!=max(arr[i][0],arr[i][1]))
                    flip[i+1]++;
            }
        }
    }
    sort(last,last+N);
    track=K;
    for(int i=N-1;i>=0;i--){
        while(last[i].F<=K&&K){
            update2(ma[q[K-1]],1);
            K--;
        }
        int temp=ma[max(arr[last[i].S-1][0],arr[last[i].S-1][1])];
        if(temp==1)
            flip[last[i].S]+=track-K;
        else
            flip[last[i].S]+=track-K-query2(temp-1);
    }
    for(int i=1;i<=N;++i){
        if(flip[i]%2)
            ans+=1LL*arr[i-1][1];
        else
            ans+=1LL*arr[i-1][0];
    }
    cout<<ans;
    return 0;
}
