#include <bits/stdc++.h>

using namespace std;

#define MAXN 205
#define MAXB 10005
int D, P, R, B;
int C[MAXN];
vector<int> G[MAXN];
bool in_bag_items[MAXN];

void build_bag_items(int v, set<int>& nodes) {
	nodes.insert(v);
	for (int i = 0; i < G[v].size(); i++)
		if (nodes.find(G[v][i]) == nodes.end())
			build_bag_items(G[v][i], nodes);
}

int dsp_bag[MAXB], ppp_bag[MAXB];
template<int bag[]> void insert_item(int maxweight, int W, int V) {
	for (int w = maxweight; w >= W; w--)
		bag[w] = max(bag[w], bag[w-W] + V);
}

int main() {
	while (scanf(" %d %d %d %d", &D, &P, &R, &B) != EOF) {
		/* Clear */
		for (int i = 0; i <= B; i++)
			dsp_bag[i] = ppp_bag[i] = 0;
		for (int i = 0; i < D+P; i++)
			G[i].clear(), in_bag_items[i] = false;

		/* Input */
		for (int i = 0; i < D; i++)
			scanf(" %d", &C[i]);
		for (int i = 0; i < P; i++)
			scanf(" %d", &C[D+i]);
		for (int i = 0; i < R; i++) {
			int a, b;
			scanf(" %d %d", &a, &b), a--, b--, b += D;
			G[a].push_back(b);
			G[b].push_back(a);
		}
	
		for (int i = 0; i < D+P; i++) {
			if (!in_bag_items[i]) {
				set<int> items;
				build_bag_items(i, items);
	
				int price = 0, dsp = 0, ppp = 0;
				for (set<int>::iterator it = items.begin(); it != items.end(); it++) {
					int v = *it;
					in_bag_items[v] = true;
					price += C[v];
					(v < D ? dsp++ : ppp++);
				}
	
				insert_item<dsp_bag>(B, 0, dsp);
				insert_item<ppp_bag>(B, 0, ppp);
				if (dsp < ppp) {
					insert_item<dsp_bag>(B, price, ppp - dsp);
				} else if (dsp > ppp) {
					insert_item<ppp_bag>(B, price, dsp - ppp);
				}
			}
		}
		printf("%d %d\n", dsp_bag[B], ppp_bag[B]);
	}
	return 0;
}


