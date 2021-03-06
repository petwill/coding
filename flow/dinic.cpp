//http://acm.csie.org/ntujudge/problem.php?id=2581
//French Fries Festival
//dinic runs in O( V^2*E )

#define maxn 500
struct Edge{ int to, cap, rev; };
struct Dinic{
    vector<Edge> G[maxn];
    int dis[maxn], iter[maxn];
    void init(int n) {
        //zero based
    	for(int i = 0; i < n; i++) G[i].clear();
    }
    void addEdge(int from, int to, int cap) {
        vector<Edge>::iterator it;
        if( ( it=find_if( all(G[from]), [to](Edge& e) { return e.to == to; } )) != G[from].end() ) {
            it->cap += cap;
            return;
        }
    	G[from].pb(Edge{to, cap, (int)G[to].size()});
    	G[to].pb(Edge{from, 0, (int)G[from].size()-1});
        //if undirected 0 will be cap
    }
    bool bfs(int s, int t) {
    	memset(dis, -1, sizeof(dis));
    	queue<int> que;
    	que.push(s); dis[s] = 0;
    	while(!que.empty()) {
    		int tp = que.front(); que.pop();
    		for(Edge &e : G[tp]) {
    			if(e.cap > 0 && dis[e.to] == -1)
    				dis[e.to] = dis[tp] + 1, que.push(e.to);
    		}
    	}
    	return dis[t] != -1;
    }
    int dfs(int v, int t, int f) {
    	if( v == t ) return f;
    	for(int &i = iter[v]; i < G[v].size(); i++) {
    		Edge &e = G[v][i];
    		if(e.cap > 0 && dis[v] < dis[e.to]) {
    			int d = dfs(e.to, t, min(f, e.cap));
    			if(d > 0) {
    				e.cap -= d;
    				G[e.to][e.rev].cap += d;
    				f += d;
    				return d;
    			}
    		}
    	}
    	return 0;
    }
    int maxFlow(int s, int t) {
    	int ret = 0;
    	while( bfs(s, t) ) {
    		memset(iter, 0, sizeof(iter));
    		int f;
    		while((	f = dfs(s, t, inf) )> 0 )
    			ret += f;
    	}
    	return ret;
    }
}dinic, dinic2;
void solve() {
    int n,m,k; cin>>n>>m>>k;
    // flow problem with lower bounds;
    int s = 0, t = n+2, ss = n+3, tt = n+4;
    dinic.init( n+5 );
    dinic.addEdge(s, 1, k);
    dinic.addEdge(n+1, t, k);
    //
    int slb = 0;
    while(m--) {
        int l, r, a, b; scanf("%d %d %d %d", &l, &r, &a, &b);
        slb += a;
        r++;

        dinic.addEdge(l, r, b-a);
        dinic.addEdge(ss, r, a);
        dinic.addEdge(l, tt, a);
    }
    dinic2  = dinic;

    dinic.addEdge(t, s, k);
    int f1 = dinic.maxFlow(ss, tt);
    if( !all_of( all(dinic.G[ss]), [](Edge x) { return x.cap == 0; } ) ) {
        puts("-1"); return;
    }

    dinic2.addEdge(ss, s, 1e9);
    dinic2.addEdge(t, tt, 1e9);

    int f2 = dinic2.maxFlow(ss, tt);
    // maxflow in current graph is f2 - slb
    printf("%d\n", (f2 - slb)*n );
}
int main() {
    int t;cin>>t;
    while(t--)
        solve();
}
