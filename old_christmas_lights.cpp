#include <bits/stdc++.h>
using namespace std;

#define MAXN 100005
#define MAXLOG 17
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

deque<PII>minn,maxx;
int N,K,arr[MAXN],Q,a,b,pos,L[MAXN],R[MAXN],rmq[MAXLOG][MAXN],ansst,ansl,ans2;

int query(int a,int b){
    int mlog=log2(b-a+1);
    if(R[rmq[mlog][a]]>=R[rmq[mlog][b-(1<<mlog)+1]])
        return rmq[mlog][a];
    return rmq[mlog][b-(1<<mlog)+1];
}

int main()
{
    scanf("%d%d",&N,&K);
    for(int i=0;i<N;++i){
        scanf("%d",&arr[i]);
        while(!minn.empty()&&arr[i]<minn.back().F)
            minn.pop_back();
        minn.push_back({arr[i],i});
        while(!maxx.empty()&&arr[i]>maxx.back().F)
            maxx.pop_back();
        maxx.push_back({arr[i],i});
        while(maxx.front().F-minn.front().F>K){
            if(minn.front().S==pos)
                minn.pop_front();
            if(maxx.front().S==pos)
                maxx.pop_front();
            R[pos]=i-pos;
            pos++;
        }
        L[i]=i-pos+1;
    }
    for(int i=pos;i<N;++i)
        R[i]=N-i;
    for(int i=0;i<N;++i)
        rmq[0][i]=i;
    for(int i=1;(1<<i)<=N;++i){
        for(int j=0;j+(1<<i)-1<N;++j){
            if(R[rmq[i-1][j]]>=R[rmq[i-1][j+(1<<(i-1))]])
                rmq[i][j]=rmq[i-1][j];
            else
                rmq[i][j]=rmq[i-1][j+(1<<(i-1))];
        }
    }
    scanf("%d",&Q);
    for(int i=0;i<Q;++i){
        scanf("%d%d",&a,&b);
        a--; b--;
        ansl=min(L[b],b-a+1);
        ansst=max(b-L[b]+1,a);
        if(ansst==a){
            printf("%d %d\n",ansst+1,ansst+ansl);
            continue;
        }
        ans2=query(a,ansst-1);
        if(min(R[ans2],b-ans2+1)>=ansl){
            ansl=min(R[ans2],b-ans2+1);
            ansst=ans2;
        }
        printf("%d %d\n",ansst+1,ansst+ansl);
    }
    return 0;
}
