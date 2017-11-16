#include <bits/stdc++.h>
using namespace std;

#define MAXN 150005
#define MAXBLK 390
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

int laststation [MAXN] [MAXBLK + 1];
VVI trains (MAXN);
int N, M, Q, first, last, stationtrack[MAXN], linenumbers[MAXN], rotations [MAXN], blocks [MAXBLK + 1], blocksize, l, r, x, a, stationnumber [MAXN], op, ans;

int main()
{
    memset(laststation, -1, sizeof laststation);
    scanf(" %d %d %d", &N, &M, &Q);
    // blocksize = int(sqrt(N));
    blocksize = MAXBLK;
    REP(i,0,N-1) {
        scanf(" %d", &linenumbers[i]);
        stationtrack[i] = stationnumber[linenumbers[i]];
        laststation[linenumbers[i]][i / blocksize] = stationtrack[i];
        stationnumber[linenumbers[i]]++;
    }
    REP(i,0,N-1) {
        scanf(" %d", &a);
        trains[linenumbers[i]].push_back(a);
        blocks[i / blocksize] += a;
    }
    REP(i,1,Q) {
        scanf(" %d", &op);
        if (op == 1) {
            scanf(" %d %d", &l, &r);
            l--; r--;
            ans = 0;
            for (int j = l / blocksize; j < r / blocksize; ++j)
                ans += blocks[j];
            for (int j = l / blocksize * blocksize; j < l; ++j)
                ans -= trains[linenumbers[j]][(stationtrack[j] - rotations[linenumbers[j]]) % stationnumber[linenumbers[j]]]; // mod ???
            for (int j = r / blocksize * blocksize; j <= r; ++j)
                ans += trains[linenumbers[j]][(stationtrack[j] - rotations[linenumbers[j]]) % stationnumber[linenumbers[j]]]; // negative
            printf("%d\n", ans);
        } else {
            first = -1;
            scanf(" %d", &x);
            for (int j = 0; j <= blocksize; ++j) {
                if (laststation[x][j] != -1) {
                    if (first == -1)
                        first = j;
                    else
                        blocks[j] += trains[x][(last - rotations[x]) % stationnumber[x]];
                    blocks[j] -= trains[x][(laststation[x][j] - rotations[x]) % stationnumber[x]];
                    last = laststation[x][j];
                }
            }
            blocks[first] += trains[x][(last - rotations[x]) % stationnumber[x]];
            rotations[x]++;
            if (rotations[x] > 0)
                rotations[x] -= stationnumber[x];
        }
    }
    return 0;
}
