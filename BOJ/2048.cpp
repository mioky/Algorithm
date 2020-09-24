/* 2020.09.24
*
* BOJ 12100
* Completed!
*
* map copy하는 방법
* 동서남북 확인을 rotation함수를 사용하고, 한 방향으로만 이동시키면 됨!!
*
*
* Memory : 1112 KB
* Time   : 4 ms
*/

#include <cstdio>
#include <cstring>
using namespace std;

int N;
int map[20][20];
int ans = 0;

void rotation(int m[20][20]) {
	int temp[20][20] = { 0, };
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			temp[i][j] = m[N - j - 1][i];
	memcpy(m, temp, sizeof(temp));
}

void move(int map[20][20]) {
	int tmp[20][20] = { 0, };

	for (int x = 0; x < N; x++) {
		int flag = 0; int loc = -1;

		for (int y = 0; y <N; y++) {
			if (map[y][x] == 0) continue;
			if (flag == 1 && tmp[loc][x] == map[y][x]) {
				tmp[loc][x] *= 2;
				flag = 0;
			}
			else {
				tmp[++loc][x] = map[y][x];
				flag = 1;
			}
		}

		for (++loc; loc < N; loc++) {
			tmp[loc][x] = 0;
		}
	}

	memcpy(map, tmp, sizeof(tmp));
}


void DFS(int m[20][20], int depth) {
	if (depth == 5) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				ans = ans < m[i][j] ? m[i][j] : ans;
		return;
	}
	for (int i = 0; i < 4; i++) {
		int backup_map[20][20] = { 0, };
		memcpy(backup_map, m, sizeof(backup_map));

		move(backup_map);
		DFS(backup_map, depth + 1);
		rotation(m);
	}
}

int main() {

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &map[i][j]);

	DFS(map, 0);
	printf("%d\n", ans);
	return 0;
}
