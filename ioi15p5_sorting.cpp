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

int cycles(int a[],int b){
    int ans=0;
    bool vis[b];
    memset(vis,0,sizeof vis);
    for(int i=0;i<b;++i){
        if(!vis[i]){
            vis[i]=1;
            int x=a[i];
            while(x!=i){
                vis[x]=1;
                x=a[x];
            }
            ans++;
        }
    }
    return ans;
}

int st[MAXN],ecurr[MAXN],eloc[MAXN],acurr[MAXN],aloc[MAXN],cnt=0;

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]){
    int low=0,high=N;
    while(low<high){
        int mid=(low+high)/2;
        for(int i=0;i<N;++i)
            st[i]=S[i];
        for(int i=0;i<mid;++i)
            swap(st[X[i]],st[Y[i]]);
        if(N-cycles(st,N)<=mid)
            high=mid;
        else
            low=mid+1;
    }
    for(int i=0;i<N;++i){
        ecurr[i]=acurr[i]=S[i];
        eloc[S[i]]=aloc[S[i]]=i;
    }
    for(int i=0;i<N;++i)
        st[i]=S[i];
    for(int i=0;i<low;++i)
        swap(st[X[i]],st[Y[i]]);
    for(int i=0;i<low;++i){
        swap(ecurr[X[i]],ecurr[Y[i]]);
        swap(eloc[ecurr[X[i]]],eloc[ecurr[Y[i]]]);
        swap(acurr[X[i]],acurr[Y[i]]);
        swap(aloc[acurr[X[i]]],aloc[acurr[Y[i]]]);
        while(acurr[eloc[st[cnt]]]==cnt&&cnt<N)
            cnt++;
        if(cnt==N){
            P[i]=Q[i]=0;
            continue;
        }
        P[i]=eloc[st[cnt]];
        Q[i]=aloc[cnt];
        int temp=acurr[eloc[st[cnt]]];
        swap(acurr[eloc[st[cnt]]],acurr[aloc[cnt]]);
        swap(aloc[temp],aloc[cnt]);
    }
    return low;
}
