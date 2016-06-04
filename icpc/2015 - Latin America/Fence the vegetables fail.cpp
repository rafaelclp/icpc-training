/* Gambiarra bagarai... mas passou */
#include <bits/stdc++.h>

using namespace std;

typedef long long lint;

#define oo 2000000000
#define PLANT 1
#define EDGE 2

struct Coordinate {
	int x, y;
	Coordinate(): x(0), y(0) {}
	Coordinate(int x, int y): x(x), y(y) {}
};

struct Event {
	int type, y2;
	Coordinate coord;
	Event(int type, Coordinate coord, int y2): type(type), coord(coord), y2(y2) {}

	const bool operator<(const Event& o) const {
		if (coord.x != o.coord.x) return coord.x < o.coord.x;
		if (coord.y != o.coord.y) return coord.y < o.coord.y;
		if (y2 != o.y2) return y2 < o.y2;
		return type < o.type;
	}
};

int P, V;

#define START false
#define END true

typedef pair<int, int> pii;
set< pair<bool, pii> > segments;
void toggleSegment(int y1, int y2) {
	vector<pii> addSegments;
	vector<pii> remSegments;
	set< pair<bool, pii> >::iterator lb;

	// Remove intersection of segment starting BEFORE y1 with (y1, y2)
	lb = segments.lower_bound(make_pair(END, make_pair(-y1, -oo)));
	for (; lb != segments.end(); lb++) {
		int _y1 = -lb->second.first, _y2 = -lb->second.second;
		if (_y2 >= y1 && _y1 < y1) {
			remSegments.push_back(make_pair(_y1, _y2));
			if (_y1 < y1)
				addSegments.push_back(make_pair(_y1, y1));
			if (y2 < _y2)
				addSegments.push_back(make_pair(y2, _y2));
			y1 = _y2;
		}
		break;
	}

	// Remove intersection of segments starting AFTER y1 with (y1, y2)
	lb = segments.lower_bound(make_pair(START, make_pair(y1, -oo)));
	for (; lb != segments.end(); lb++) {
		if (lb->first != START) break;
		int _y1 = lb->second.first, _y2 = lb->second.second;
		if (_y1 >= y2) break;

		addSegments.push_back(make_pair(y1, _y1));
		if (_y2 <= y2) {
			remSegments.push_back(make_pair(_y1, _y2));
			y1 = _y2;
		} else {
			remSegments.push_back(make_pair(_y1, _y2));
			addSegments.push_back(make_pair(y2, _y2));
			y1 = _y2;
		}
	}
	if (y1 < y2)
		addSegments.push_back(make_pair(y1, y2));

	for (int i = 0; i < remSegments.size(); i++) {
		segments.erase(make_pair(START, make_pair(remSegments[i].first, remSegments[i].second)));
		segments.erase(make_pair(END, make_pair(-remSegments[i].first, -remSegments[i].second)));
	}
	for (int i = 0; i < addSegments.size(); i++) {
		if (addSegments[i].first != addSegments[i].second) {
			segments.insert(make_pair(START, make_pair(addSegments[i].first, addSegments[i].second)));
			segments.insert(make_pair(END, make_pair(-addSegments[i].first, -addSegments[i].second)));
		}
	}
}

bool isInside(int y) {
	set< pair<bool, pii> >::iterator lb = segments.lower_bound(make_pair(START, make_pair(y, -oo)));
	if (lb != segments.end() && lb->first == START && lb->second.first == y) return true;
	lb = segments.lower_bound(make_pair(END, make_pair(-y, -oo)));
	if (lb != segments.end() && lb->first == END && -lb->second.first <= y && -lb->second.second >= y) return true;
	return false;
}

vector<Event> events;
inline void addEvent(int type, Coordinate coord, int y2) {
	events.push_back(Event(type, coord, y2));
}

lint countPlantsInside() {
	lint plantsInside = 0;
	sort(events.begin(), events.end());

	for (int ev = 0; ev < events.size(); ev++) {
		Event &event = events[ev];
		int x = event.coord.x, y = event.coord.y, y2 = event.y2;
		int type = event.type;

		if (type == PLANT) {
			plantsInside += y2 * isInside(y);
		} else {
			toggleSegment(y, y2);
		}
	}
	return plantsInside;
}

#define PA(n) ((lint)(n)*(n+1)/2)

int main() {
	while (scanf(" %d %d", &P, &V) != EOF) {
		events.clear();
		segments.clear();
		int x, y;
		for (int i = 0; i < P; i++) {
			scanf(" %d %d", &x, &y);
			addEvent(PLANT, Coordinate(x, y), i+1);
		}
		int last_x, last_y, first_x, first_y;
		scanf(" %d %d", &first_x, &first_y);
		last_x = first_x, last_y = first_y;
		for (int i = 1; i < V; i++) {
			scanf(" %d %d", &x, &y);
			if (last_x == x) {
				addEvent(EDGE, Coordinate(x, min(y, last_y)), max(y, last_y));
			}
			last_x = x, last_y = y;
		}
		if (last_x == first_x)
			addEvent(EDGE, Coordinate(x, min(last_y, first_y)), max(last_y, first_y));

		if (V <= 2) {
			printf("%d\n", P);
			continue;
		}

		printf("%lld\n", PA(P) - countPlantsInside());
	}
	return 0;
}

