#include <bits/stdc++.h>
using namespace std;

#define MAXN 10005
#define MAXLOG 14
#define F first
#define S second

struct Node{
    int val,left,right;
}seg[MAXN*4];

string s;
vector<pair<int,int>>tree[MAXN];
pair<pair<int,int>,int>e[MAXN];
int t,N,a,b,cnt,h[MAXN],siz[MAXN],top[MAXN],heavy[MAXN],heavyedge[MAXN],label[MAXN],arr[MAXN],par[MAXN][MAXLOG];

int segquery(int x,int l,int r){
    if(seg[x].left>r||seg[x].right<l)
        return -1;
    if(seg[x].left>=l&&seg[x].right<=r)
        return seg[x].val;
    return max(segquery(x*2,l,r),segquery(x*2+1,l,r));
}

void segupdate(int x,int idx,int newVal){
    if(seg[x].left==seg[x].right){
        seg[x].val=newVal;
        return;
    }
    if(idx<=seg[x*2].right)
        segupdate(x*2,idx,newVal);
    else
        segupdate(x*2+1,idx,newVal);
    seg[x].val=max(seg[x*2].val,seg[x*2+1].val);
}

void segbuild(int x,int l,int r){
    seg[x].left=l;
    seg[x].right=r;
    if(l==r){
        seg[x].val=arr[l];
        return;
    }
    segbuild(x*2,l,(l+r)/2);
    segbuild(x*2+1,(l+r)/2+1,r);
    seg[x].val=max(seg[x*2].val,seg[x*2+1].val);
}

void dfs(int x,int p){
    int tsize=1,idx=-1,maxsiz=0;
    par[x][0]=p;
    for(auto u:tree[x]){
        if(u.F!=p){
            h[u.F]=h[x]+1;
            dfs(u.F,x);
            tsize+=siz[u.F];
            if(siz[u.F]>maxsiz){
                maxsiz=siz[u.F];
                idx=u.F;
                heavyedge[x]=u.S;
            }
        }
    }
    heavy[x]=idx;
    siz[x]=tsize;
}

void hld(int x,int p,int st,int w){
    label[x]=cnt;
    arr[cnt]=w;
    cnt++;
    top[x]=st;
    if(heavy[x]==-1)
        return;
    hld(heavy[x],x,st,heavyedge[x]);
    for(auto u:tree[x]){
        if(u.F!=p&&u.F!=heavy[x])
            hld(u.F,x,u.F,u.S);
    }
}

int lcaquery(int u,int v){
    if(h[v]<h[u])
        swap(u,v);
    for(int i=MAXLOG-1;i>=0;--i){
        if(par[v][i]!=-1&&h[par[v][i]]>=h[u])
            v=par[v][i];
    }
    if(v==u)
        return v;
    for(int i=MAXLOG-1;i>=0;--i){
        if(par[u][i]!=par[v][i]){
            u=par[u][i];
            v=par[v][i];
        }
    }
    return par[v][0];
}

void lcabuild(){
    for(int i=1;i<MAXLOG;++i){
        for(int j=1;j<=N;++j){
            if(par[j][i-1]!=-1)
                par[j][i]=par[par[j][i-1]][i-1];
        }
    }
}

int qtree(int u,int v){
    int a=top[u],b=top[v],ans=-1;
    while(1){
        if(u==v)
            return ans;
        if(a==b)
            return max(ans,segquery(1,min(label[u],label[v])+1,max(label[u],label[v])));
        if(u!=a){
            ans=max(ans,segquery(1,label[a]+1,label[u]));
            a=u=top[u];
        }
        ans=max(ans,arr[label[u]]);
        u=par[u][0];
        a=top[u];
    }
}

void init(){
    for(int i=1;i<=N;++i)
        tree[i].clear();
    for(int i=1;i<N;++i){
        tree[e[i].F.F].push_back({e[i].F.S,e[i].S});
        tree[e[i].F.S].push_back({e[i].F.F,e[i].S});
    }
    memset(par,-1,sizeof par);
    h[1]=cnt=0;
    dfs(1,-1);
    hld(1,0,1,0);
    lcabuild();
    segbuild(1,0,N-1);
}

int main()
{
    cin.tie(0);
    cin.sync_with_stdio(0);
    cin>>t;
    while(t--){
        cin>>N;
        for(int i=1;i<N;++i)
            cin>>e[i].F.F>>e[i].F.S>>e[i].S;
        init();
        while(true){
            cin>>s;
            if(s=="DONE") break;
            cin>>a>>b;
            if(s=="QUERY"){
                int temp=lcaquery(a,b);
                cout<<max(qtree(a,temp),qtree(b,temp))<<"\n";
            }else{
                if(h[e[a].F.F]>h[e[a].F.S]){
                    segupdate(1,label[e[a].F.F],b);
                    arr[label[e[a].F.F]]=b;
                }else{
                    segupdate(1,label[e[a].F.S],b);
                    arr[label[e[a].F.S]]=b;
                }
            }
        }
    }
    return 0;
}
