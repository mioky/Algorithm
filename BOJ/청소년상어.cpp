/* 2020.10.10
*
* BOJ 19236
* Completed!
*
*  map에 물고기 번호담은 후, 그 번호에 대한 정보를 또 다시 구조체를 사용하여 만듦.
*  물고기 이동에서 이미 먹힌 물고기 처리를 안해줘서 오답이 계속 떴음.
*  상어이동시 DFS를 사용했는데 백트래킹 작업에서 조금 시간 걸림
*
* Memory : 1116 KB
* Time   : 0 ms
*/

#include <cstdio>

struct info {
	int x;
	int y;
	int dir;
};

info fish[17]; //물고기 이동을 위해
info temp_fish[17][17];
info shark;
int map[4][4];
int temp_map[17][4][4];
int dx[9] = { 0,0,-1,-1,-1,0,1,1,1 };
int dy[9] = { 0,-1,-1,0,1,1,1,0,-1 };
int ans = 0;
bool visit[17];

void fish_move(int depth) {
	
	for (int i = 1; i < 17; i++) {
		for (int j = 1; j <= 8; j++) {
			if (visit[i] || map[fish[i].y][fish[i].x] == 0 || map[fish[i].y][fish[i].x] == -1) break;
			int mov_x = fish[i].x + dx[fish[i].dir];
			int mov_y = fish[i].y + dy[fish[i].dir];
			int temp = map[mov_y][mov_x];
			if (mov_x < 0 || mov_y < 0 || mov_x >= 4 || mov_y >= 4 || map[mov_y][mov_x] == -1) {
				fish[i].dir = (fish[i].dir %8)+1; //반시계방향으로 45도 회전
				continue;
			}
			//map 먼저 변경
			int temp2 = map[mov_y][mov_x];
			map[mov_y][mov_x] = map[fish[i].y][fish[i].x];
			map[fish[i].y][fish[i].x] = temp2;
			//물고기 정보 변경(위치만 바꿔야 함)
			if (temp == 0) {
				fish[i].x = mov_x;
				fish[i].y = mov_y;
			}
			else {
				int x = mov_x;
				fish[temp].x = fish[i].x;
				fish[i].x = x;
				int y = fish[temp].y;
				fish[temp].y = fish[i].y;
				fish[i].y = y;
			}
			break; //이동을 완료했다면
		}
	}
	for (int i = 0; i < 17; i++)
		temp_fish[depth][i] = fish[i];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			temp_map[depth][i][j] = map[i][j];
}

void DFS(int x, int y, int shark_dir, int sum, int depth) {

	fish_move(depth);
	bool flag = false;
	int mov_x = x;
	int mov_y = y;
	for (int i = 0; i < 3; i++) { //4x4이기때문에 최대 3개 중 한 개 이동 가능
		mov_x += dx[shark_dir];
		mov_y += dy[shark_dir];
		if (mov_x < 0 || mov_y < 0 || mov_x >= 4 || mov_y >= 4 || map[mov_y][mov_x] == 0) 
			continue; //이동 불가
		flag = true;
		int temp_dir = fish[map[mov_y][mov_x]].dir;
		int temp_num = map[mov_y][mov_x]; //백트래킹을 위한 저장
		//map 정보 변경 -> 상어 위치에는 -1, 상어가 지나간 자리는 0
		visit[temp_num] = true;
		map[mov_y][mov_x] = -1; //상어
		map[y][x] = 0;
		DFS(mov_x, mov_y, temp_dir, sum + temp_num, depth + 1);
		//백트래킹 -> 물고기 이동 전
		visit[temp_num] = false;

		for (int i = 0; i < 17; i++)
			fish[i] = temp_fish[depth][i];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				map[i][j] = temp_map[depth][i][j];
	}
	if (!flag) {
		ans = ans < sum ? sum : ans;
	}
}

int main() {

	int temp_num, temp_dir, temp;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			scanf("%d %d", &temp_num, &temp_dir);
			if (i == 0 && j == 0) {
				visit[temp_num] = true;
				shark.x = j;
				shark.y = i;
				shark.dir = temp_dir;
				temp = temp_num;
				map[0][0] = -1; //-1은 상어를 의미
				continue;
			}
			fish[temp_num].x = j;
			fish[temp_num].y = i;
			fish[temp_num].dir = temp_dir;
			map[i][j] = temp_num; //맵에는 물고기 번호만 저장, 번호만 알면 위치와 방향알 수 있음
		}
	}

	DFS(shark.x, shark.y, shark.dir, temp,0);

	printf("%d\n", ans);

	return 0;
}
