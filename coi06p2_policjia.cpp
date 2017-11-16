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

VVI graph (MAXN);
bool vis [MAXN];
int N, E, Q, a, b, c, op, g1, g2, counter, dfn[MAXN], low[MAXN], dfe[MAXN], st, en, depth[MAXN], sparse[20][MAXN], power2[20];

void tarjan(int x, int par){
    sparse[0][x]=par;
    vis[x]=dfn[x]=low[x]=++counter;
    for(size_t i = 0; i < graph[x].size(); ++i) {
        if(!vis[graph[x][i]]) {
            depth[graph[x][i]] = depth[x] + 1;
            tarjan(graph[x][i], x);
            low[x]=min(low[x],low[graph[x][i]]);
        } else if (graph[x][i] != par)
            low[x]=min(low[x],dfn[graph[x][i]]);
    }
    dfe[x]=++counter;
}

bool wg1(int x) {
    return dfn[x] >= dfn[en] && dfe[x] <= dfe[en];
}

int dirans(int x) {
    for(int i=17; i>=0; i--) {
        if (depth[x] - power2[i] >= depth[en]+1)
            x=sparse[i][x];
    }
    return x;
}

int main()
{
    memset(sparse, -1, sizeof sparse);
    power2[0]=1;
    REP(i,1,17)
        power2[i]=power2[i-1]*2;
    scanf(" %d %d", &N, &E);
    REP(i,1,E){
        scanf(" %d %d", &a, &b);
        graph[a].PB(b);
        graph[b].PB(a);
    }
    tarjan(1, -1);
    REP(i,1,17){
        REP(j,1,N){
            if(sparse[i-1][j]!=-1 && sparse[i-1][sparse[i-1][j]]!=-1)
                sparse[i][j] = sparse[i-1][sparse[i-1][j]];
        }
    }
    scanf(" %d", &Q);
    REP(i,1,Q){
        scanf(" %d", &op);
        if (op == 1) {
            scanf(" %d %d %d %d", &a, &b, &g1, &g2);
            if (dfn[g1] > dfn[g2]) {
                st = g2; en = g1;
            } else {
                st = g1; en = g2;
            }
            if (low[en] <= dfn[st] || (wg1(a)&&wg1(b)) || (!(wg1(a)||wg1(b))))
                printf("yes\n");
            else
                printf("no\n");
        } else {
            scanf("%d%d%d",&a, &b, &c);
            en = c;
            if (!(wg1(a)||wg1(b))) {
                printf("yes\n");
            } else if (wg1(a)&&wg1(b)) {
                int x = dirans(a); int y = dirans(b);
                if ((x==y)||(low[x] < dfn[en]&&low[y]<dfn[en]))
                    printf("yes\n");
                else
                    printf("no\n");
            }
            else if ((wg1(a)&&low[dirans(a)]<dfn[en]) || (wg1(b)&&low[dirans(b)]<dfn[en]))
                printf("yes\n");
            else
                printf("no\n");
        }
    }
    return 0;
}
