#include <bits/stdc++.h>

using namespace std;

int main() {
	static const int cards[] = {10000, 1000, 100, 10, 1},
		n_cards = sizeof(cards) / sizeof(int);
	int N, M;
	while (scanf(" %d %d", &N, &M) != EOF) {
		int extra_points = 0;
		while (M--) {
			int B, D, sum = 0, x;
			scanf(" %d %d", &B, &D);
			for (int i = 1; i < N; i++)
				scanf(" %d", &x), sum += x;
			int D_points = sum + D <= B ? D : 0;
			for (int i = 0; i < n_cards; i++) {
				if (sum + cards[i] <= B) {
					extra_points += cards[i] - D_points;
					break;
				}
			}
		}
		printf("%d\n", extra_points);
	}
	return 0;
}


