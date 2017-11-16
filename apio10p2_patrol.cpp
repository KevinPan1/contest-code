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
typedef vector<int> VI;
typedef vector<VI > VVI;
typedef vector<PII > VPII;
typedef vector<VPII > VVPII;
typedef map<int,int> MII;

VVPII graph(MAXN);
int N,K,a,b,dist[MAXN],pre[MAXN],st,en,maxd,maxl,len1[MAXN],len2[MAXN],ans;

void dfs2(int x){
    bool flag=false;
    for(size_t i=0;i<graph[x].size();++i){
        if(pre[x]!=graph[x][i].F){
            flag=true;
            pre[graph[x][i].F]=x;
            dfs2(graph[x][i].F);
            if(len1[graph[x][i].F]+graph[x][i].S>len1[x]){
                len2[x]=len1[x];
                len1[x]=len1[graph[x][i].F]+graph[x][i].S;
            }else if(len1[graph[x][i].F]+graph[x][i].S>len2[x])
                len2[x]=len1[graph[x][i].F]+graph[x][i].S;
        }
    }
    if(!flag)
        len1[x]=0;
    ans=max(max(max(ans,len1[x]+len2[x]),len1[x]),len2[x]);
}

void dfs(int x){
    for(size_t i=0;i<graph[x].size();++i){
        if(pre[x]!=graph[x][i].F){
            pre[graph[x][i].F]=x;
            dist[graph[x][i].F]=dist[x]+1;
            dfs(graph[x][i].F);
        }
    }
    if(dist[x]>maxd){
        maxd=dist[x];
        maxl=x;
    }
}

int main()
{
    scanf("%d%d",&N,&K);
    REP(i,1,N-1){
        scanf("%d%d",&a,&b);
        graph[a].PB({b,1});
        graph[b].PB({a,1});
    }
    dfs(1);
    maxd=dist[maxl]=pre[maxl]=0;
    dfs(maxl);
    if (K==1){
        printf("%d",2*(N-1)-maxd+1);
        return 0;
    }
    while(pre[maxl]){
        for(size_t i=0;i<graph[maxl].size();++i){
            if (graph[maxl][i].F==pre[maxl]){
                for(size_t j=0;j<graph[graph[maxl][i].F].size();++j){
                    if(graph[graph[maxl][i].F][j].F==maxl){
                        graph[graph[maxl][i].F][j].S=-1;
                        break;
                    }
                }
                graph[maxl][i].S=-1;
                maxl=graph[maxl][i].F;
                break;
            }
        }
    }
    pre[1]=0;
    dfs2(1);
    printf("%d",2*(N-1)-maxd-ans+2);
    return 0;
}
