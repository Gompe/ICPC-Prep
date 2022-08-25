#include<vector>
#include<cstdio>
#include<iostream>
#include<cmath>
#include<queue>
#define numm ch-48
#define pd putchar(' ')
#define pn putchar('\n')
#define pb push_back
#define fi first
#define se second
#define fre1 freopen("1.txt","r",stdin)
#define fre2 freopen("2.txt","w",stdout)
using namespace std;
template <typename T>
void read(T &res) {
    bool flag=false;char ch;
    while(!isdigit(ch=getchar())) (ch=='-')&&(flag=true);
    for(res=numm;isdigit(ch=getchar());res=(res<<1)+(res<<3)+numm);
    flag&&(res=-res);
}
template <typename T>
void write(T x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int maxn=110;
const int N=1010;
const int M=10010;
const int inf=0x3f3f3f3f;
typedef long long ll;
struct edge{ int v,w; };
vector<edge>e[N];
int sum[N],vis[N],dis[N];
int spfa(int n) {
    sum[1]++;
    dis[1]=0;
    queue<int>que;
    que.push(1);
    while(!que.empty()) {
        int u=que.front();que.pop();
        vis[u]=false;
        for(int i=0;i<e[u].size();i++) {
            edge x=e[u][i];
            int v=x.v;
            if(dis[v]>dis[u]+x.w) {
                dis[v]=dis[u]+x.w;
                if(!vis[v]) {
                    if(++sum[v] > n) return -1;
                    que.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    return dis[n]==inf ? -2 : dis[n];
}
int main()
{
    int n,ml,md;
    while(scanf("%d%d%d",&n,&ml,&md)!=EOF) {
        for(int i=1;i<=n;i++)
        vis[i]=false,dis[i]=inf,sum[i]=0,e[i].clear();
        for(int i=1;i<=ml;i++){    /// d[B]-d[A]<=D
            int a,b,d;
            read(a),read(b),read(d);
            e[a].pb((edge){b,d});
        }
        for(int i=1;i<=md;i++) {    /// d[A]-d[B]<=-D
            int a,b,d;
            read(a),read(b),read(d);
            e[b].pb((edge){a,-d});
        }
        for(int i=1;i<n;i++)    /// d[i]-d[i+1]<=0
            e[i+1].pb((edge){i,0});
        write(spfa(n)),pn;
    }
    return 0;
}
