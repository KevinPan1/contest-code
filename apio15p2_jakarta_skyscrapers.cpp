#include <bits/stdc++.h>
using namespace std;

#define MAXN 30005
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define INF 0x3f3f3f3f
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

PII nd;
priority_queue<PII,VPII,greater<PII> >que;
VVPII graph(MAXN);
set<PII> se;
int N,M,B,P,dist[MAXN],st,en;

int main()
{
    memset(dist,0x3f,sizeof dist);
    scanf("%d%d",&N,&M);
    REP(i,1,M){
        scanf("%d%d",&B,&P);
        if(i==1)
            st=B;
        if(i==2)
            en=B;
        if(se.count({B,P})) continue;
         se.insert({B,P});
        for(int j=B-P,k=1;j>=0;j-=P,k++){
            graph[B].PB({j,k});
         if(se.count({j,P})) break;
        }
        for(int j=B+P,k=1;j<N;j+=P,k++){
            graph[B].PB({j,k});
             if(se.count({j,P})) break;
        }
    }
    dist[st]=0;
    que.push({0,st});
    while(!que.empty()){
        nd=que.top(); que.pop();
        for(auto u:graph[nd.S]){
            if(dist[u.F]>nd.F+u.S){
                dist[u.F]=nd.F+u.S;
                que.push({dist[u.F],u.F});
            }
        }
    }
    if(dist[en]==INF)
        printf("-1");
    else
        printf("%d",dist[en]);
    return 0;
}
