#include <bits/stdc++.h>

using namespace std;

#define MAXN 105
#define oo 2000000000

int R, C;
int H[MAXN][MAXN];

struct Coordinate {
	int x, y;
	Coordinate(): x(0), y(0) {}
	Coordinate(int x, int y): x(x), y(y) {}
};

inline int getH(int i, int j) {
	if (i >= 0 && i < R && j >= 0 && j < C)
		return H[i][j];
	return 0; // Altura fora da area eh 0
}

// Only for the 4 horizontal directions (left-right, right-left, front-back, back-front)
int countFacesInHorDir(
	Coordinate startPos,      // Start pos in the H array
	Coordinate loopDirection, // Which direction to move in the loop/for
	Coordinate blockDirection // Which direction to look to check whether face is blocked or not
) {
	static const pair<int, int> _00 = make_pair(0, 0);
	pair<int, int> lastFace = _00;
	int faces = 0;

	for (
		int i = startPos.y, j = startPos.x;
		(i >= 0 && i < R) && (j >= 0 && j < C);
		i += loopDirection.y, j += loopDirection.x
	) {
		int v = getH(i, j),
			bv = getH(i + blockDirection.y, j + blockDirection.x);

		if (bv >= v) {
			lastFace = _00;
			continue;
		}

		if (bv >= lastFace.second || v <= lastFace.first)
			faces++;
		lastFace = make_pair(bv, v);
	}

	return faces;
}

bool vis[MAXN][MAXN];
void bfs(Coordinate startNode) {
	static const Coordinate directions[] = { Coordinate(0, 1), Coordinate(1, 0), Coordinate(0, -1), Coordinate(-1, 0) };
	static const int n_directions = sizeof(directions) / sizeof(Coordinate);

	vis[startNode.y][startNode.x] = true;
	queue<Coordinate> nodes;
	nodes.push(startNode);

	while (!nodes.empty()) {
		Coordinate v = nodes.front(); nodes.pop();

		for (int i = 0; i < n_directions; i++) {
			Coordinate u = Coordinate(v.x + directions[i].x, v.y + directions[i].y);

			if (getH(u.y, u.x) != getH(v.y, v.x)) continue; // alturas diferentes == faces diferentes
			if (vis[u.y][u.x]) continue; // ja foi incluido previamente

			vis[u.y][u.x] = true;
			nodes.push(u);
		}
	}
}

int countFacesUpDown() {
	/* Clear */
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			vis[i][j] = false;

	/* Count */
	int faces = 0;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (!vis[i][j])
				faces++, bfs(Coordinate(j, i));
	return faces;
}

inline int countFacesDownUp() { return 1; }

int main() {
	while (scanf(" %d %d", &R, &C) != EOF) {
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				scanf(" %d", &H[i][j]);

		int faces = countFacesDownUp() + countFacesUpDown();
		for (int j = 0; j < C; j++) {
			faces += countFacesInHorDir(Coordinate(j, 0), Coordinate(0, 1), Coordinate(-1, 0)); // left-right
			faces += countFacesInHorDir(Coordinate(j, 0), Coordinate(0, 1), Coordinate(+1, 0)); // right-left
		}
		for (int i = 0; i < R; i++) {
			faces += countFacesInHorDir(Coordinate(0, i), Coordinate(1, 0), Coordinate(0, -1)); // back-front
			faces += countFacesInHorDir(Coordinate(0, i), Coordinate(1, 0), Coordinate(0, +1)); // front-back
		}
		printf("%d\n", faces);
	}
	return 0;
}

