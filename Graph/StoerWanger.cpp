#include <bits/stdc++.h>
using namespace std;

/* for finding the min cut of a graph without specifing the source or  the sink.
   all the edges are directed and no need to give  make any edge bidirectional.
*/

const int N = 1407;

// O(n^3) but faster, 1 indexed

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct StoerWagner {
    int n, idx[N];
    long long G[N][N], dis[N];

    bool vis[N];
    const long long inf = 1e18;

    StoerWagner() {}
    StoerWagner(int _n) {
        n = _n;
        memset(G, 0, sizeof G);
    }

    void add_edge(int u, int v, long long w) {  // undirected edge, multiple edges are merged into one edge
        if (u != v) {
            G[u][v] += w;
            G[v][u] += w;
        }
    }

    long long solve() {
        long long ans = inf;
        for (int i = 0; i < n; ++i) idx[i] = i + 1;
        shuffle(idx, idx + n, rnd);

        while (n > 1) {
            int t = 1, s = 0;
            for (int i = 1; i < n; ++i) {
                dis[idx[i]] = G[idx[0]][idx[i]];
                if (dis[idx[i]] > dis[idx[t]]) t = i;
            }

            memset(vis, 0, sizeof vis);
            vis[idx[0]] = true;

            for (int i = 1; i < n; ++i) {
                if (i == n - 1) {
                    if (ans > dis[idx[t]])
                        ans = dis[idx[t]];  // idx[s] - idx[t] is in two halves of the  mincut
                    if (ans == 0) return 0;
                    for (int j = 0; j < n; ++j) {
                        G[idx[s]][idx[j]] += G[idx[j]][idx[t]];
                        G[idx[j]][idx[s]] += G[idx[j]][idx[t]];
                    }
                    idx[t] = idx[--n];
                }

                vis[idx[t]] = true;
                s = t, t = -1;

                for (int j = 1; j < n; ++j) {
                    if (!vis[idx[j]]) {
                        dis[idx[j]] += G[idx[s]][idx[j]];
                        if (t == -1 || dis[idx[t]] < dis[idx[j]]) t = j;
                    }
                }
            }
        }
        return ans;
    }
};

int main() {
    int n;
    cin >> n;

    getchar();
    StoerWagner st(n);

    for (int i = 1; i <= n; i++) {
        string s;
        getline(cin, s);

        stringstream ss;
        ss << s;

        int x;
        while (ss >> x) {
            if (i > x + 1) st.add_edge(x + 1, i, 1);
        }
    }
    cout << st.solve() << endl;
}

// https://vjudge.net/problem/UVA-10989
// https://vjudge.net/problem/SPOJ-DISGRAPH
