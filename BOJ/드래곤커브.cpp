/* 2020.10.05
*
* BOJ 15685
* Completed!
*
* 패턴만 잘 찾으면 됨!
*
*
* Memory : 1184 KB
* Time   : 0 ms
*/
#include <cstdio>
#include <vector>

using namespace std;

int N;
int x, y, d, g;
int dx[4] = { 1,0,-1,0 }; //0->1, 1->2, 2->3, 3->0
int dy[4] = { 0,-1,0,1 };
bool visit[100][100];

void MOVE() {
	vector<int> dir;
	dir.push_back(d);
	visit[y][x] = true;
	x += dx[d];
	y += dy[d];
	visit[y][x] = true;
	for (int i = 0; i < g; i++) {
		for (int j = dir.size()-1; j >=0; j--) {
			int temp = (dir[j] + 1) % 4;
			x += dx[temp];
			y += dy[temp];
			visit[y][x] = true;
			dir.push_back(temp);
		}
	}
}

int main() {
	int ans = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d %d", &x, &y, &d, &g);
		MOVE();
	}
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (visit[i][j]) {
				if (!visit[i + 1][j] || !visit[i][j + 1] || !visit[i + 1][j + 1]) continue;
				ans++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
