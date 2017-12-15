#include <bits/stdc++.h>
using namespace std;

#define MAXN 1005
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

stack<int>st;
bool vis[MAXN],tree[MAXN][MAXN];
PII e[MAXN];
VI graph[MAXN];
int n,r,a,b,dfn[MAXN],low[MAXN],cnt,comp[MAXN],num,leaf;

void tarjan(int x,int p){
    vis[x]=1;
    low[x]=dfn[x]=cnt++;
    st.push(x);
    for(int u:graph[x]){
        if(u!=p){
            if(!vis[u])
                tarjan(u,x);
            low[x]=min(low[x],low[u]);
        }
    }
    if(dfn[x]==low[x]){
        while(true){
            int temp=st.top();
            comp[temp]=num;
            st.pop();
            if(temp==x) break;
        }
        num++;
    }
}

void dfs(int x,int p){
    int ch=0;
    for(int i=0;i<num;++i){
        if(i!=p&&tree[x][i]){
            ch++;
            dfs(i,x);
        }
    }
    if(!x&&ch==1)
        leaf++;
    else if(x&&!ch)
        leaf++;
}

int main()
{
    scanf("%d%d",&n,&r);
    for(int i=0;i<r;++i){
        scanf("%d%d",&e[i].F,&e[i].S);
        graph[e[i].F].PB(e[i].S);
        graph[e[i].S].PB(e[i].F);
    }
    tarjan(1,0);
    for(int i=0;i<r;++i){
        if(comp[e[i].F]!=comp[e[i].S]&&!tree[comp[e[i].F]][comp[e[i].S]]){
            tree[comp[e[i].F]][comp[e[i].S]]=1;
            tree[comp[e[i].S]][comp[e[i].F]]=1;
        }
    }
    dfs(0,-1);
    printf("%d",(leaf+1)/2);
    return 0;
}
