#include <bits/stdc++.h>
using namespace std;

#define MAXN 400005
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

VVI tree(MAXN);
int N,a,b;
LL len[MAXN],cnt[MAXN],dia,way;

void dfs(int x,int par){
    for(size_t i=0;i<tree[x].size();++i){
        if(tree[x][i]!=par){
            dfs(tree[x][i],x);
            if(len[tree[x][i]]+len[x]+1>dia){
                dia=len[tree[x][i]]+len[x]+1;
                way=cnt[tree[x][i]]*cnt[x];
            }else if(len[tree[x][i]]+len[x]+1==dia)
                way+=cnt[tree[x][i]]*cnt[x];
            if(len[tree[x][i]]+1>len[x]){
                len[x]=len[tree[x][i]]+1;
                cnt[x]=cnt[tree[x][i]];
            }else if(len[tree[x][i]]+1==len[x])
                cnt[x]+=cnt[tree[x][i]];
        }
    }
}

int main()
{
    scanf("%d",&N);
    REP(i,1,N)
        cnt[i]=1;
    REP(i,1,N-1){
        scanf("%d%d",&a,&b);
        tree[a].PB(b);
        tree[b].PB(a);
    }
    dfs(1,0);
    printf("%lld %lld",dia+1,way);
    return 0;
}
