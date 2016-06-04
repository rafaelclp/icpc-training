#include <bits/stdc++.h>

using namespace std;

#define MAXN 1005
#define oolf 2000000000000000.0
#define EPS 1e-12

struct Edge {
	int u, A, B;
	Edge(): u(0), A(0), B(0) {}
	Edge(int u, int A, int B): u(u), A(A), B(B) {}
	inline double getCost(double t) { return A*t+B; }
};

vector<Edge> G[MAXN];
int N;

double dijkstra(double t, int startNode, int endNode) {
	static bool vis[MAXN];
	static double dis[MAXN];
	priority_queue< pair<double, int> > pq;

	for (int i = 0; i < N; i++)
		vis[i] = false, dis[i] = oolf;
	dis[startNode] = 0;
	pq.push(make_pair(0, startNode));

	while (!pq.empty()) {
		int v = -1;
		do {
			v = pq.top().second, pq.pop();
		} while (!pq.empty() && vis[v]);

		if (vis[v] || v == endNode) break;
		vis[v] = true;

		for (int i = 0; i < G[v].size(); i++) {
			Edge &e = G[v][i];
			if (!vis[e.u] && dis[e.u] > dis[v] + e.getCost(t)) {
				dis[e.u] = dis[v] + e.getCost(t);
				pq.push(make_pair(-dis[e.u], e.u));
			}
		}
	}

	return dis[endNode];
}

double ternarySearch() {
	double bestCost = 0;
	double tLeft = 0, tRight = 24*60;

	while (fabs(tRight - tLeft) >= EPS) {
		double tOneThird = (tRight - tLeft) / 3;
		double tLeftThird = tLeft + tOneThird;
		double tRightThird = tRight - tOneThird;

		double tLeftCost = dijkstra(tLeftThird, 0, N-1);
		double tRightCost = dijkstra(tRightThird, 0, N-1);
		
		if (tLeftCost < tRightCost)
			tLeft = tLeftThird;
		else
			tRight = tRightThird;

		bestCost = max(bestCost, max(tLeftCost, tRightCost));
	}

	return bestCost;
}

int main() {
	int M;
	while (scanf(" %d %d", &N, &M) != EOF) {
		for (int i = 0; i < N; i++)
			G[i].clear();

		while (M--) {
			int v, u, A, B;
			scanf(" %d %d %d %d", &v, &u, &A, &B), v--, u--;
			G[u].push_back(Edge(v, A, B));
			G[v].push_back(Edge(u, A, B));
		}

		printf("%.5lf\n", ternarySearch());
	}
	return 0;
}

