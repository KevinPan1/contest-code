// problem: https://dmoj.ca/problem/dmpg17g2
// solution: maximum sub-segment sum problem with a segment tree

#include <bits/stdc++.h>
using namespace std;

#define MAXN 100005
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define INF -0x3f3f3f3f3f3f3f3f
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

struct Node{
    int left,right;
    LL pre,suff,maxx,tot;
} tree[MAXN*4];

char op;
int N, Q, a, b;
LL arr[MAXN];

void push_up(int x){
    tree[x].pre=max(tree[x*2].pre,tree[x*2].tot+tree[x*2+1].pre);
    tree[x].suff=max(tree[x*2+1].suff,tree[x*2+1].tot+tree[x*2].suff);
    tree[x].tot=tree[x*2].tot+tree[x*2+1].tot;
    tree[x].maxx=max(max(tree[x*2].maxx,tree[x*2+1].maxx),tree[x*2].suff+tree[x*2+1].pre);
}

void build(int x,int l,int r){
    tree[x].left=l;
    tree[x].right=r;
    if(l==r){
        tree[x].pre=tree[x].suff=tree[x].tot=tree[x].maxx=arr[l];
        return;
    }
    build(x*2,l,(l+r)/2);
    build(x*2+1,(l+r)/2+1,r);
    push_up(x);
}

void update(int x,int index,LL val){
    if(tree[x].left==tree[x].right){
        tree[x].pre=tree[x].suff=tree[x].tot=tree[x].maxx=val;
        return;
    }
    if(index>(tree[x].left+tree[x].right)/2)
        update(x*2+1,index,val);
    else
        update(x*2,index,val);
    push_up(x);
}

vector<LL>query(int x,int l,int r){
    if(tree[x].right<l||tree[x].left>r)
        return {INF,INF,INF,INF};
    if(tree[x].left>=l&&tree[x].right<=r)
        return {tree[x].pre,tree[x].suff,tree[x].tot,tree[x].maxx};
    vector<LL>temp1=query(x*2,l,r);
    vector<LL>temp2=query(x*2+1,l,r);
    if(temp1[0]==INF)
        return temp2;
    if(temp2[0]==INF)
        return temp1;
    return {max(temp1[0],temp1[2]+temp2[0]),max(temp2[1],temp2[2]+temp1[1]),temp1[2]+temp2[2],max(max(temp1[3],temp2[3]),temp1[1]+temp2[0])};
}

int main()
{
    scanf("%d%d",&N,&Q);
    REP(i,1,N)
        scanf("%lld",&arr[i]);
    build(1,1,N);
    REP(i,1,Q) {
        scanf(" %c %d%d",&op,&a,&b);
        if(op=='S'){
            update(1,a,b);
            arr[a]=b;
        }else
            printf("%lld\n",query(1,a,b)[3]);
    }
    return 0;
}
