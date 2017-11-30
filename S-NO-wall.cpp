// problem: https://dmoj.ca/problem/year2016p8
// segment tree with lazy propagation, store prefix, suffix and maximum length of longest sequence of 1's and combine answers
// similar to the maximum sub-segment sum in a segment tree problem

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
typedef pair<PII, PII> PPIIPII;
typedef vector<int> VI;
typedef vector<VI > VVI;
typedef vector<PII > VPII;
typedef vector<VPII > VVPII;
typedef map<int,int> MII;

int arr[MAXN],N,Q,op,l,r;

struct Node{
    int left,right,pre,suf,lazy;
    PII maxx;
} tree[400005];

void push_down(int x){
    if(tree[x].lazy!=-1){
        if(tree[x].lazy==0)
            tree[x].pre=tree[x].suf=tree[x].maxx.F=0;
        else
            tree[x].pre=tree[x].suf=tree[x].maxx.F=(tree[x].right-tree[x].left+1); // remove later
        tree[x].maxx.S=tree[x].left;
        if(tree[x].left!=tree[x].right)
            tree[x*2].lazy=tree[x*2+1].lazy=tree[x].lazy;
        tree[x].lazy=-1;
    }
}

void push_up(int x){
    tree[x].pre=tree[x*2].pre;
    if(tree[x*2].pre==tree[x*2].right-tree[x*2].left+1)
        tree[x].pre+=tree[x*2+1].pre;
    tree[x].suf=tree[x*2+1].suf;
    if(tree[x*2+1].suf==tree[x*2+1].right-tree[x*2+1].left+1)
        tree[x].suf+=tree[x*2].suf;
    tree[x].maxx=tree[x*2].maxx;
    if(tree[x*2].suf+tree[x*2+1].pre>tree[x].maxx.F)
        tree[x].maxx={tree[x*2].suf+tree[x*2+1].pre,tree[x*2].right-tree[x*2].suf+1};
    if(tree[x*2+1].maxx.F>tree[x].maxx.F)
        tree[x].maxx=tree[x*2+1].maxx;
}

void build(int x,int l,int r){
    tree[x].left=l;
    tree[x].right=r;
    tree[x].lazy=-1;
    if(l==r){
        tree[x].pre=tree[x].suf=arr[l];
        tree[x].maxx={arr[l],l};
        return;
    }
    build(x*2,l,(l+r)/2);
    build(x*2+1,(l+r)/2+1,r);
    push_up(x);
}

void update(int x,int l,int r,int val){
    push_down(x);
    if(tree[x].left>=l&&tree[x].right<=r){
        tree[x].lazy=val;
        push_down(x);
        return;
    }
    if(tree[x].left>r||tree[x].right<l)
        return;
    update(x*2,l,r,val);
    update(x*2+1,l,r,val);
    push_up(x);
}

PPIIPII query(int x,int l,int r){
    push_down(x);
    if(tree[x].left>=l&&tree[x].right<=r)
        return {{tree[x].pre, tree[x].suf},tree[x].maxx};
    if(tree[x].left>r||tree[x].right<l)
        return {{0,0},{0,tree[x].left}};
    PPIIPII ans1=query(x*2,l,r);
    PPIIPII ans2=query(x*2+1,l,r);
    PPIIPII temp;
    if(ans1.F.F==0)
        temp.F.F=ans2.F.F;
    else if(ans1.F.F==tree[x*2].right-tree[x*2].left+1)
        temp.F.F=ans1.F.F+ans2.F.F;
    else
        temp.F.F=ans1.F.F;
    if(ans2.F.S==0)
        temp.F.S=ans1.F.S;
    else if(ans2.F.S==tree[x*2+1].right-tree[x*2+1].left+1)
        temp.F.S=ans2.F.S+ans1.F.S;
    else
        temp.F.S=ans2.F.S;
    if(ans1.S.F==0)
        temp.S=ans2.S;
    else if(ans2.S.F==0)
        temp.S=ans1.S;
    else{
        temp.S=ans1.S;
        if(ans1.F.S+ans2.F.F>temp.S.F){
            temp.S.F=ans1.F.S+ans2.F.F;
            temp.S.S=tree[x*2].right-tree[x*2].suf+1;
        }
        if(ans2.S.F>temp.S.F)
            temp.S=ans2.S;
    }
    return temp;
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    cin>>N>>Q;
    build(1,0,N-1);
    REP(i,1,Q){
        cin>>op;
        if(op==0){
            cin>>l>>r;
            l--; r--;
            update(1,l,r,0);
            PPIIPII temp=query(1,0,N-1);
            cout<<temp.S.F<<"\n";
        }else if(op==1){
            cin>>l>>r;
            l--; r--;
            update(1,l,r,1);
            PPIIPII temp=query(1,0,N-1);
            cout<<temp.S.F<<"\n";
        }else{
            PPIIPII temp=query(1,0,N-1);
            update(1,temp.S.S,temp.S.S+temp.S.F-1,0);
        }
    }
    return 0;
}
