#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	while (scanf(" %d", &N) != EOF) {
		int x, cnt=0;
		for (int i = 0; i < 5; i++) {
			scanf(" %d", &x);
			if (x == N) cnt++;
		}
		printf("%d\n", cnt);
	}
	return 0;
}
