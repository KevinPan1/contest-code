#include <bits/stdc++.h>
using namespace std;

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

int arr [2000001];

struct Node{
    int left, right, op, bottom, top;
} tree [1 << 22];

void push_down(int x) {
    if (tree[x].op) {
        if (tree[x].left == tree[x].right) {
            arr[tree[x].left] = max(tree[x].top, arr[tree[x].left]);
            arr[tree[x].left] = min(tree[x].bottom, arr[tree[x].left]);
        } else {
            tree[x * 2].op = tree[x * 2 + 1].op = tree[x].op;

            tree[x * 2].top = max(tree[x * 2].top, tree[x].top);
            tree[x * 2].top = min(tree[x * 2].top, tree[x].bottom);
            tree[x * 2].bottom = min(tree[x * 2].bottom, tree[x].bottom);
            tree[x * 2].bottom = max(tree[x * 2].bottom, tree[x].top);

            tree[x * 2 + 1].top = max(tree[x * 2 + 1].top, tree[x].top);
            tree[x * 2 + 1].top = min(tree[x * 2 + 1].top, tree[x].bottom);
            tree[x * 2 + 1].bottom = min(tree[x * 2 + 1].bottom, tree[x].bottom);
            tree[x * 2 + 1].bottom = max(tree[x * 2 + 1].bottom, tree[x].top);

        }
        tree[x].bottom = INF;
        tree[x].top = tree[x].op = 0;
    }
}

void build(int l, int r, int x) {
    tree[x].left = l; tree[x].right = r, tree[x].bottom = INF;
    if (l == r)
        return;
    build(l, (l + r) / 2, x * 2);
    build((l + r) / 2 + 1, r, x * 2 + 1);
}

void update(int l, int r, int op, int newVal, int x) {
    push_down(x);
    if (tree[x].left > r || tree[x].right < l)
        return;
    if (tree[x].left >= l && tree[x].right <= r) {
        tree[x].op = op;
        if (op == 1) {
            tree[x].top = max(newVal, tree[x].top);
            tree[x].bottom = max(newVal, tree[x].bottom);
        } else {
            tree[x].top = min(newVal, tree[x].top);
            tree[x].bottom = min(newVal, tree[x].bottom);
        }
        push_down(x);
        return;
    }
    update(l, r, op, newVal, x * 2);
    update(l, r, op, newVal, x * 2 + 1);
}

int query(int idx, int x) {
    push_down(x);
    if (tree[x].left > idx || tree[x].right < idx)
        return 0;
    if (tree[x].left == idx && tree[x].right == idx)
        return arr[tree[x].left];
    return query(idx, x * 2) + query(idx, x * 2 + 1);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]) {
    build(0, n - 1, 1);
    REP(i,0,k-1)
        update(left[i], right[i], op[i], height[i], 1);
    REP(i,0,n-1)
        finalHeight[i] = query(i, 1);
}
