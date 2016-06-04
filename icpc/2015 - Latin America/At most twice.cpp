#include <bits/stdc++.h>

using namespace std;
typedef long long lint;

int restantes[10] = {2,2,2,2,2,2,2,2,2,2};
lint resolver(vector<int>& U, int idx=0, bool all_9=false, lint L=0) {
	if (idx == U.size())
		return L;
	for (int proximo = all_9 ? 9 : U[idx]; proximo >= 0; proximo--) {
		if (idx == 0 && proximo == 0)
			break;
		all_9 = (all_9 || proximo < U[idx]);
		if (restantes[proximo]) {
			restantes[proximo]--;
			lint L_solucao = resolver(U, idx + 1, all_9, L*10+proximo);
			restantes[proximo]++;
			if (L_solucao >= 0)
				return L_solucao;
		}
	}
	return -1;
}

int main() {
	lint U;

	while (scanf(" %lld", &U) != EOF) {
		vector<int> U_v, U_9v;
	
		for (lint i = U; i; i /= 10) {
			U_v.push_back(i%10);
			U_9v.push_back(9);
		}
	
		reverse(U_v.begin(), U_v.end());
		if (!U_9v.empty()) U_9v.pop_back();
	
		lint L = resolver(U_v);
		if (L < 0) L = resolver(U_9v);
	
		printf("%lld\n", L);
	}
	return 0;
}

