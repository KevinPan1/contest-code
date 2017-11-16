#include <bits/stdc++.h>
using namespace std;

#define MAXN 100001
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

VI radii;
PII childheights [MAXN], distChild [MAXN];
bool visited [MAXN];
VVPII graph (MAXN);
int h [MAXN], f [MAXN], g[MAXN], counter, maxDiameter;

int dfs4(int x, int par) {
    int temp = INF;
    for (size_t i = 0; i < graph[x].size(); ++i) {
        if (graph[x][i].first != par)
            temp = min(dfs4(graph[x][i].F, x), temp);
    }
    maxDiameter = max(max(h[x], g[x]), maxDiameter);
    return min(max(h[x], g[x]), temp);
}

void dfs3(int x, int par, int lastDist) {
    if (par != -1)
        g[x] = max(f[x], g[par] + lastDist); // check
    for (size_t i = 0; i < graph[x].size(); ++i) {
        if (graph[x][i].first != par)
            dfs3(graph[x][i].F, x, graph[x][i].S);
    }
}

void dfs2(int x, int par, int lastDist) {
    if (par != -1 && childheights[par].F != -1 && childheights[par].F != x)
        f[x] = distChild[par].F + lastDist + h[childheights[par].F];
    else if (par != -1 && childheights[par].S != -1 && childheights[par].S != x)
        f[x] = distChild[par].S + lastDist + h[childheights[par].S];
    for (size_t i = 0; i < graph[x].size(); ++i) {
        if (graph[x][i].first != par)
            dfs2(graph[x][i].F, x, graph[x][i].S);
    }
}

int dfs1(int x, int par) {
    visited[x] = 1;
    int height = 0;
    for (size_t i = 0; i < graph[x].size(); ++i) {
        if (graph[x][i].first != par) {
            int temp = dfs1(graph[x][i].F, x) + graph[x][i].S;
            height = max(height, temp);
            if (childheights[x].F == -1) {
                childheights[x].F = graph[x][i].F;
                distChild[x].F = graph[x][i].S;
            } else if(temp > h[childheights[x].F] + distChild[x].F) {
                childheights[x].S = childheights[x].F;
                distChild[x].S = distChild[x].F;
                childheights[x].F = graph[x][i].F;
                distChild[x].F = graph[x][i].S;
            }
            else if (childheights[x].S == -1) {
                childheights[x].S = graph[x][i].F;
                distChild[x].S = graph[x][i].S;
            } else if (temp > h[childheights[x].S] + distChild[x].S) {
                childheights[x].S = graph[x][i].F;
                distChild[x].S = graph[x][i].S;
            }
        }
    }
    return h[x] = height;
}

int findRadius(int x) {
    dfs1(x, -1);
    dfs2(x, -1, 0);
    dfs3(x, -1, 0);
    return dfs4(x, -1);
}

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
    memset(childheights, -1, sizeof childheights);
    REP(i,0,M-1) {
        graph[A[i]].PB({B[i], T[i]});
        graph[B[i]].PB({A[i], T[i]});
    }
    REP(i,0,N-1) {
        if (!visited[i]) {
            radii.PB(findRadius(i));
            counter++;

        }
    }
    sort(radii.rbegin(), radii.rend());
    if (counter == 1) {
        return maxDiameter;
    } else if (counter == 2)
        return max(maxDiameter, radii[0] + radii[1] + L);
    else
        return max(maxDiameter, max(radii[0] + radii[1] + L, radii[1] + radii[2] + 2 * L));
}

int N, M, L, A [MAXN], B [MAXN], T [MAXN];

int main()
{
    scanf(" %d %d %d", &N, &M, &L);
    REP(i,0,M-1)
        scanf(" %d %d %d", &A[i], &B[i], &T[i]);
    printf("%d", travelTime(N, M, L, A, B, T));
    return 0;
}
