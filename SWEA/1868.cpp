#include <cstdio>
#include <queue>
#include <string>
#define MAX_SIZE 301

using namespace std;

int N;
char map[MAX_SIZE][MAX_SIZE]; //지뢰 -> *, 확인 안 된 곳 -> '.', 확인 된 곳 -> '-' 
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int ans = 0;

bool check(int x, int y) { //8방향에 지뢰가 있는지 없는지
	for (int i = 0; i < 8; i++) {
		int temp_x = x+dx[i];
		int temp_y = y+dy[i];
		if (temp_x < 0 || temp_y < 0 || temp_x >= N || temp_y >= N) continue; //범위를 벗어나면
		if (map[temp_y][temp_x] == '*') return false; //주위에 지뢰가 있다면
	}
	return true; //지뢰가 없다면
}

void Run() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == '.' && map[i][j] != '-' && check(j,i)) {
				map[i][j] = '-';
				queue<pair<int, int>> q;
				q.push({ j,i });
				map[i][j] = '-';
				while (!q.empty()) {
					int cur_x = q.front().first;
					int cur_y = q.front().second;
					q.pop();
					if (check(cur_x, cur_y)) { //지뢰가 없다면
						for (int k = 0; k < 8; k++) {
							int temp_x = cur_x + dx[k];
							int temp_y = cur_y + dy[k];
							if (temp_x < 0 || temp_y < 0 || temp_x >= N || temp_y >= N || map[temp_y][temp_x] == '-') continue; //범위를 벗어나면
							map[temp_y][temp_x] = '-'; //확인
							q.push({ temp_x, temp_y });
						}
					}
				}
				ans++; //클릭 한 번
			}
		}
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (map[i][j] == '.') ans++;
}

int main() {

	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		ans = 0;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%1s", &map[i][j]);
		Run();
		printf("#%d %d\n", t, ans);
	}

	return 0;
}
