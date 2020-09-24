/* 2020.09.24
*
* BOJ 14499
* Completed!
*
* 주사위 굴리는 패턴만 구하면 됨
*
*
* Memory : 1112 KB
* Time   : 0 ms
*/

#include <cstdio>

int map[20][20];
int dice[7] = { 0, };
int dy[5] = { 0,1,-1,0,0 }; // 0,동서남북
int dx[5] = { 0,0,0,-1,1 };
int N, M, x, y; //현재 위치

bool move(int dir) { //이동 방향, 현재 위치

	int mov_x = x + dx[dir];
	int mov_y = y + dy[dir];
	if (mov_x < 0 || mov_x >= N || mov_y < 0 || mov_y >= M) 
		return false;
	x += dx[dir];
	y += dy[dir];
	if (dir == 1) { //동
		int temp = dice[1];
		dice[1] = dice[3];
		dice[3] = dice[6];
		dice[6] = dice[4];
		dice[4] = temp;
	}
	else if (dir == 2) { //서
		int temp = dice[1];
		dice[1] = dice[4];
		dice[4] = dice[6];
		dice[6] = dice[3];
		dice[3] = temp;
	}
	else if (dir == 3) { //북
		int temp = dice[1];
		dice[1] = dice[2];
		dice[2] = dice[6];
		dice[6] = dice[5];
		dice[5] = temp;
	}
	else { //남
		int temp = dice[1];
		dice[1] = dice[5];
		dice[5] = dice[6];
		dice[6] = dice[2];
		dice[2] = temp;
	}

	if (map[x][y] == 0) {
		map[x][y] = dice[1];
	}
	else {
		dice[1] = map[x][y];
		map[x][y] = 0;
	}

	return true;
}

int main() {

	int K, dir;
	scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	for (int i = 0; i < K; i++) {
		scanf("%d", &dir);
		if(move(dir)) printf("%d\n",dice[6]);
	}

	return 0;
}
