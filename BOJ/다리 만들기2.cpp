/* 2020.09.30
*
* BOJ 17472
* Completed!
*
* 섬 만들기 -> DFS
* 섬 거리구하기 -> 오른쪽, 아래만 구하면 됨
* 모든 섬이 연결되어 있는 지와 최단 거리 -> DFS
* 모든 섬이 연결되어 있는 지는 하나의 섬을 잡고 그 섬과 연결된 섬들을 방문 체크 후
* 방문 체크된 것들과 또 연결되어 있는 섬들을 찾아서 방문 체크!
* 모든 섬이 연결되어 있는 지를 어떻게 코드화시킬지 고민 많이 함 ;ㅅ;
*
* Memory : 1224 KB
* Time   : 0 ms
*/

#include <cstdio>
#include <queue>

using namespace std;

int N, M;
int map[10][10];
int Bridge[7][7];
bool Island_check[7];
int Island_count = 1;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
int ans = -1;

void DFS(int count, int Total) {
	if (count == Island_count - 1) {
		if (ans == -1) ans = Total;
		else ans = ans > Total ? Total : ans;
	}
	for (int i = 1; i <= Island_count; i++) {
		for (int j = 1; j <= Island_count; j++) {
			if (Island_check[i] && !Island_check[j] && Bridge[i][j] > 0) {
				Island_check[j] = true;
				DFS(count + 1, Total + Bridge[i][j]);
				Island_check[j] = false;
			}
		}
	}
}

void DISTANCE() { //섬끼리 최단 거리 구하기

	int i, j, count, a, b;
	for (i = 0; i < N; i++) {
		a = -1;
		for (j = 0; j < M - 1; j++) {
			if (map[i][j] > 0 && map[i][j + 1] == 0) {
				a = map[i][j] - 1;
				count = 0;
			}
			if (map[i][j] == 0) count++;
			if (a != -1 && map[i][j] == 0 && map[i][j + 1] > 0) {
				b = map[i][j + 1] - 1;
				if (a != b && count > 1 && (Bridge[a][b] == 0 || Bridge[a][b] > count)) {
					Bridge[a][b] = count;
					Bridge[b][a] = count;
				}
			}
		}
	}
	for (i = 0; i < M; i++) {
		a = -1;
		for (j = 0; j < N - 1; j++) {
			if (map[j][i] > 0 && map[j + 1][i] == 0) {
				a = map[j][i] - 1;
				count = 0;
			}
			if (map[j][i] == 0) count++;
			if (a != -1 && map[j][i] == 0 && map[j + 1][i] > 0) {
				b = map[j + 1][i] - 1;
				if (a != b && count > 1 && (Bridge[a][b] == 0 || Bridge[a][b] > count)) {
					Bridge[a][b] = count;
					Bridge[b][a] = count;
				}
			}
		}
	}
}

void MAKE() { //섬만들기

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1) {
				queue<pair<int, int>> q;
				q.push({ i,j });
				map[i][j] = ++Island_count; //2부터 시작
				while (!q.empty()) {
					int cur_x = q.front().second;
					int cur_y = q.front().first;
					q.pop();
					for (int k = 0; k < 4; k++) {
						int mov_x = cur_x + dx[k];
						int mov_y = cur_y + dy[k];
						if (mov_x < 0 || mov_y < 0 || mov_x >= M || mov_y >= N || map[mov_y][mov_x] == 0 || map[mov_y][mov_x] == Island_count) continue;
						map[mov_y][mov_x] = Island_count; //섬 번호 매기기
						q.push({ mov_y, mov_x }); //값 넣어주기
					}
				}
			}
		}
	}
}

int main() {

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	MAKE(); //BFS로 섬만들기
	DISTANCE(); //섬끼리 최단 거리 구하기
	Island_check[1] = true;
	DFS(1, 0); //모든 섬이 연결됐는지와 연결되어 있다면 최단거리 구하기
	printf("%d\n", ans);

	return 0;
}
