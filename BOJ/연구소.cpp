/* 2020.10.06
*
* BOJ 14502
* Completed!
*
* 벽 세울 때 3중 포문 사용
* 
*
*
* Memory : 1112 KB
* Time   : 28 ms
*/
#include <cstdio>

using namespace std;

struct pos {
	int x;
	int y;
};

int N, M;
int map[9][9];
int temp_map[9][9];
pos virus[65];
pos _empty[65];
int empty_count = 0;
int virus_count = 0;
int temp_virus_count = 0;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
int ans = 65; //

void copy() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			temp_map[i][j] = map[i][j];
		}
	}
}

void BFS() {
	temp_virus_count = virus_count;

	for (int i = 0; i < temp_virus_count; i++) {
		for (int j = 0; j < 4; j++) {
			int mov_x = virus[i].x + dx[j];
			int mov_y = virus[i].y + dy[j];
			if (mov_x < 0 || mov_y < 0 || mov_x >= M || mov_y >= N || temp_map[mov_y][mov_x] != 0) continue;
			temp_map[mov_y][mov_x] = 2;
			virus[temp_virus_count].x = mov_x;
			virus[temp_virus_count++].y = mov_y;
		}
	}
	if (ans > temp_virus_count) ans = temp_virus_count; //퍼진 바이러스 갯수 최소화

}

int main() {

	int wall_count = 0;
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) {
				virus[virus_count].x = j;
				virus[virus_count++].y = i;
			}
			else if (map[i][j] == 1)
				wall_count++;
			else {
				_empty[empty_count].x = j;
				_empty[empty_count++].y = i;
			}
		}
	}
	for (int i = 0; i < empty_count-2; i++) {
		for (int j = i + 1; j < empty_count - 1; j++) {
			for (int k = j + 1; k < empty_count; k++) {
				copy();
				temp_map[_empty[i].y][_empty[i].x] = 1;
				temp_map[_empty[j].y][_empty[j].x] = 1;
				temp_map[_empty[k].y][_empty[k].x] = 1;
				BFS();
			}
		}
	}
	printf("%d\n", (N*M) - (ans+ wall_count + 3));
	return 0;
}
