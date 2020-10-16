/* 2020.10.16
*
* BOJ 16236
* Completed!
*
* BFS사용
*
*
* Memory : 1228 KB
* Time   : 4 ms
*/
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int map[20][20];
int N;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
int baby_x, baby_y;
int baby_size = 2;
int ans = 0;

void move() {

	int eat_count = 0;
	while (true) {
		vector<pair<int, pair<int, int>>>v; //크기 비교
		queue<pair<int, pair<int, int>>>q;
		bool visit[20][20] = { false, };
		q.push({ 0,{baby_y, baby_x} }); //이동 횟수
		visit[baby_y][baby_x] = true;
		bool flag = false;
		while (!q.empty()) { //큐가 비면
			int mov_x = q.front().second.second;
			int mov_y = q.front().second.first;
			int cur_count = q.front().first; //현재 거리
			q.pop();
			for (int i = 0; i < 4; i++) {
				int cur_x = mov_x + dx[i];
				int cur_y = mov_y + dy[i];
				if (cur_x < 0 || cur_y <0 || cur_x >= N || cur_y >= N || map[cur_y][cur_x] > baby_size || visit[cur_y][cur_x]) continue;
				if (map[cur_y][cur_x] != 0 && map[cur_y][cur_x] < baby_size) { //먹을 수 있는 물고기가 존재한다면 
					v.push_back({ cur_count + 1,{ cur_y,cur_x } });
				}
				q.push({ cur_count + 1,{ cur_y,cur_x } }); //크기가 같으면 지나갈 수 있음
				visit[cur_y][cur_x] = true;
			}
		}
		if (v.size() == 0) return; //먹을 수 있는게 없다면
		sort(v.begin(), v.end());
		baby_y = v[0].second.first;
		baby_x = v[0].second.second;
		ans += v[0].first;
		map[baby_y][baby_x] = 0;
		eat_count++;
		if (baby_size == eat_count) {
			eat_count = 0;
			baby_size++;
		}
	}
	

}

int main() {

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				baby_x = j;
				baby_y = i;
				map[i][j] = 0;
			}
		}

	move();
	printf("%d\n", ans);

	return 0;
}
