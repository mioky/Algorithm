/* 2020.10.01
*
* BOJ 14500
* Completed!
*
* ㅓ, ㅏ, ㅗ, ㅜ를 찾아야하기 때문에 방향까지 담은 visit배열을 사용
* 한 번 들렸던 곳, 같은 방향이면 예외처리!
* DFS를 사용해서 효율이 많이 떨어짐ㅜ 다른 알고리즘 찾아봐야할 듯
*
* Memory : 3308 KB
* Time   : 288 ms
*/
#include <cstdio>
#include <vector>

using namespace std;

#define MAX_SIZE 500

int N, M;
int map[MAX_SIZE][MAX_SIZE];
bool visit[MAX_SIZE][MAX_SIZE][5]; //방향까지 담은 것

int ans = 0;
int dx[5] = {0, -1,0,1,0 };
int dy[5] = {0, 0,-1,0,1 };
vector<pair<int,int>> max_num;

void DFS(int x, int y, int depth, int sum) {
	if (depth == 4) {
		ans = ans < sum ? sum : ans;
		return;
	}

	for (int i = 1; i < 5; i++) {
		int mov_x = x + dx[i];
		int mov_y = y + dy[i];
		if (mov_x < 0 || mov_y < 0 || mov_x >= M || mov_y >= N || visit[mov_y][mov_x][i]) continue;
		if (visit[mov_y][mov_x][0]) {
			DFS(mov_x, mov_y, depth, sum);
		}
		else {
			visit[mov_y][mov_x][i] = true;
			visit[mov_y][mov_x][0] = true;
			DFS(mov_x, mov_y, depth + 1, sum + map[mov_y][mov_x]);
			visit[mov_y][mov_x][i] = false;
			visit[mov_y][mov_x][0] = false;

		}

	}

}

int main() {
	int max_num1 = 0;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visit[i][j][0] = true;
			DFS(j, i, 1, map[i][j]);
			visit[i][j][0] = false;
		}
	}
	
	printf("%d", ans);
	return 0;
}
