#include <bits/stdc++.h>

using namespace std;

#define MAXL 100005
#define MAXN MAXL
#define oo 2000000000

template<class T> struct segtree {
	static T pool[]; static int poolIdx; static void free() { poolIdx = 0; }
	inline void alloc(int size) { t = pool+poolIdx; poolIdx += (n=size)<<1; }
	int n; T *t;
	inline T op(T &lval, T &rval) { return min(lval, rval); }
	inline void build(vector<T> &v) {
		alloc(v.size()); for (int i = 0; i < n; i++) t[i+n] = v[i];
		for (int i = n - 1; i > 0; i--) t[i] = op(t[i<<1], t[i<<1|1]);
	}
	inline void modify(int p, const T &val) {
		for (t[p += n] = val; p >>= 1; ) t[p] = op(t[p<<1], t[p<<1|1]);
	}
	inline T query(int l, int r) {
		T res = oo;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l&1) res = op(res, t[l++]);
			if (r&1) res = op(t[--r], res);
		}
		return res;
	}
};
template<class T> T segtree<T>::pool[2*MAXN];
template<class T> int segtree<T>::poolIdx;


struct Item {
	int S, C;
	Item(): S(0), C(0) {}
	Item(int S, int C): S(S), C(C) {}
};

int N;
vector<Item> shops[MAXL];
segtree<int> dp;
int C[MAXL], A[MAXL];

int findMaxLevel(int l, int S) {
	int *pos = upper_bound(A+l, A+N, S + (l ? A[l-1] : 0));
	return (int)(pos - A);
}

int main() {
	int M;
	while (scanf(" %d %d", &N, &M) != EOF) {
		// INPUT
		for (int i = 0; i < N; i++) {
			scanf(" %d", &C[i]);
			A[i] = (i ? A[i-1] : 0) + C[i];
			shops[i].clear();
		}
		C[N] = 0, A[N] = A[N-1];
		shops[N].clear();

		while (M--) {
			int L, S, C;
			scanf(" %d %d %d", &L, &S, &C), L--;
			shops[L].push_back(Item(S, C));
		}

		// SOLUTION
		segtree<int>::free();
		dp.alloc(N+1);
		dp.modify(N, 0);
		for (int l = N-1; l >= 0; l--) {
			int mincost = oo;
			for (int i = 0; i < shops[l].size(); i++) {
				int S = shops[l][i].S, C = shops[l][i].C;
				mincost = min(mincost, dp.query(l+1, findMaxLevel(l, S) + 1) + C);
			}
			dp.modify(l, mincost);
		}
		printf("%d\n", dp.t[dp.n] == oo ? -1 : dp.t[dp.n]); // dp.t[n+x] gets index x
	}
	return 0;
}

