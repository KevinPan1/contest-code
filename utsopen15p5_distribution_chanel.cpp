#include <bits/stdc++.h>
using namespace std;

#define MAXN 100005
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
typedef pair<int, PII> PIPII;
typedef vector<int> VI;
typedef vector<VI > VVI;
typedef vector<PII > VPII;
typedef vector<VPII > VVPII;
typedef map<int,int> MII;

VVPII tree(MAXN);
bool u[MAXN];
PIPII e[MAXN];
int N,M,a,b,c,par[MAXN],ans,ans2,cnt,lca[MAXN][16],rmq[MAXN][16],h[MAXN];

void dfs(int u,int p){
    lca[u][0]=p;
    if(p+1) h[u]=h[p]+1;
    for(int i=1;i<16;++i){
        if(lca[u][i-1]+1)
            lca[u][i]=lca[lca[u][i-1]][i-1];
    }
    for(auto v:tree[u]){
        if(p-v.F){
            rmq[v.F][0]=v.S;
            dfs(v.F,u);
        }
    }
}

int query(int u,int v,int e){
    int big=0;
    if(h[u]<h[v]) swap(u,v);
    for(int i=15;i>=0;--i){
        if(lca[u][i]+1&&h[lca[u][i]]>=h[v]){
            if(e-rmq[u][i])
                big=max(big,rmq[u][i]);
            u=lca[u][i];
        }
    }
    if(u==v) return big;
    for(int i=15;i>=0;--i){
        if(lca[u][i]-lca[v][i]){
            if(e-rmq[u][i])
                big=max(rmq[u][i],big);
            if(e-rmq[v][i])
                big=max(rmq[v][i],big);
            u=lca[u][i]; v=lca[v][i];
        }
    }
    if(e-rmq[u][0])
        big=max(rmq[u][0],big);
    if(e-rmq[v][0])
        big=max(rmq[v][0],big);
    return big;
}

int find(int x){
    if(par[x]==x)
        return x;
    return find(par[x]);
}

bool merge(int a,int b){
    a=find(a); b=find(b);
    if(a-b){
        par[a]=b;
        return 1;
    }
    return 0;
}

void build(){
    REP(i,1,N)
        par[i]=i;
}

int main(){
    cin.tie(0);
    cin.sync_with_stdio(0);
    memset(lca,-1,sizeof lca);
    cin>>N>>M;
    build();
    REP(i,0,M-1){
        cin>>a>>b>>c;
        e[i]={c,{a,b}};
    }
    sort(e,e+M);
    REP(i,0,M-1){
        if(cnt==N-1)
            break;
        if(merge(e[i].S.F,e[i].S.S)){
            tree[e[i].S.F].PB({e[i].S.S,e[i].F});
            tree[e[i].S.S].PB({e[i].S.F,e[i].F});
            u[i]=1;
            cnt++;
            ans+=e[i].F;
        }
    }
    dfs(1,-1);
    REP(i,1,N){
        REP(j,1,15){
            if(lca[i][j-1]+1&&lca[lca[i][j-1]][j-1]+1)
                rmq[i][j]=max(rmq[i][j-1],rmq[lca[i][j-1]][j-1]);
        }
    }
    ans2=0x3f3f3f3f;
    for(int i=0;i<M;++i){
        if(!u[i]){
            int temp=query(e[i].S.F,e[i].S.S,e[i].F);
            if(temp)
                ans2=min(ans2,ans+e[i].F-temp);
        }
    }
    if(ans2==0x3f3f3f3f||N-1>M)
        cout<<"-1";
    else
        cout<<ans2;
    return 0;
}
