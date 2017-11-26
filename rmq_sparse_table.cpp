// solves the classical rmq problem with sparse tables 
// build: O(NlogN)
// query: O(1)
#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000000
#define LOGMAXN 20

int N,arr[MAXN],rmq[MAXN][LOGMAXN];

int query(int l,int r){ // returns index of rmq
    int mlog=int(log2(r-l+1));
    if(arr[rmq[mlog][l]]<=arr[rmq[mlog][r-(1<<mlog)+1]])
        return rmq[mlog][l];
    return rmq[mlog][r-(1<<mlog)+1];
}

int main()
{
    cin>>N;
    for(int i=0;i<N;++i)
        cin>>arr[i];
    for(int i=0;i<N;++i) // initialize rmq row 0 with initial array values
        rmq[0][i]=i;
    for(int i=1;1<<i<=N;++i){ // build rmq, each row contain answer to subarray size 2^i starting at index j
        for(int j=0;j+(1<<i)-1<N;++j){
            if(arr[rmq[i-1][j]]<=arr[rmq[i-1][j+(1<<(i-1))]]) // if left subarray rmq < right subarray rmq
                rmq[i][j]=rmq[i-1][j]; // update index
            else
                rmq[i][j]=rmq[i-1][j+(1<<(i-1))];
        }
    }
    int a,b;
    while(true){
        cin>>a>>b;
        cout<<query(a,b)<<endl;
    }
    return 0;
}
