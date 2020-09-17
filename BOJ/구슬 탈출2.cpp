/* 2020.09.17
*
* BOJ 13460
* Completed!
*
* Memory : 1984KB
* Time : 0ms
*
*
* 처음에 맵 전체를 움직이는 방향마다 카피를 해줘야하나 생각했었지만 그럴 필요x
* 현재 구슬의 위치만 파악하고 있으면 된다.
* 1. 동서남북 시작 방향 지정
* 2. 예외처리 및 구슬 굴리기(빨강, 파랑)
* 3. 구멍에 구슬이 들어갔는지 체크
* 4. 빨강과 파랑이 같은 위치라면 굴러간 count를 비교
* 5. 구멍에 들어가지 않았다면 방향 전환(이미 갔던 방향x 반대 방향x)
*
* 방향지정시 빨간 구슬이 벽에 부딪히지 않는 곳으로 예외처리해주면 안됨!
*
* scanf를 사용하면 메모리 1112KB나옴
*/

#include <iostream>
#define MAX_SIZE 10

using namespace std;

struct pos {
	int x;
	int y;
};

int N, M;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
char map[MAX_SIZE][MAX_SIZE];
int min_move = 11;
pos red, blue;

void DFS(int red_x, int red_y, int blue_x, int blue_y, int depth, int dir) {
	if (depth > 10) //10번 초과
		return; 
	if (min_move <= depth) 
		return;
	bool red_flag = false;
	bool blue_flag = false;
	int temp_red_x = red_x;
	int temp_red_y = red_y;
	int red_count = 0, blue_count = 0;
	/////////////////////////////////////////구슬 굴리기////////////////////////////////////////
	while (true) { //빨간 공 굴리기
		temp_red_x += dx[dir];
		temp_red_y += dy[dir];
		if (map[temp_red_y][temp_red_x] == '#') {
			temp_red_x -= dx[dir];
			temp_red_y -= dy[dir];
			break;
		}
		if (map[temp_red_y][temp_red_x] == 'O') {
			red_flag = true;
			break;
		}
		red_count++;
	}
	int temp_blue_x = blue_x;
	int temp_blue_y = blue_y;
	while (true) {
		temp_blue_x += dx[dir];
		temp_blue_y += dy[dir];
		if (map[temp_blue_y][temp_blue_x] == '#') {
			temp_blue_x -= dx[dir];
			temp_blue_y -= dy[dir];
			break;
		}
		if (map[temp_blue_y][temp_blue_x] == 'O') {
			blue_flag = true;
			break;
		}
		blue_count++;
	}
	/////////////////////////////////////////////////////////////////////////////////
	if (blue_flag) return; //파란 공이 빠지면
	if (red_flag){ 
		min_move = min_move > depth ? depth : min_move; //빨간 공만 빠지면
		return;
	}
	if (temp_red_x == temp_blue_x && temp_red_y == temp_blue_y) { //파란공과 빨간 공이 나란히 있다면
		if (red_count > blue_count) { //빨간공이 파란 공 뒤에 있었으면
			temp_red_x -= dx[dir];
			temp_red_y -= dy[dir];
		}
		else {
			temp_blue_x -= dx[dir];
			temp_blue_y -= dy[dir];
		}
	}
	for (int i = 0; i < 4; i++) { //방향 전환
		if (i==dir || i - dir == 2 || i - dir == -2) continue;
		DFS(temp_red_x, temp_red_y, temp_blue_x, temp_blue_y, depth + 1, i);
	}
}

int main() {

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R') {
				red.x = j;
				red.y = i;
			}
			else if (map[i][j] == 'B') {
				blue.x = j;
				blue.y = i;
			}
		}
	}
	
	for (int i = 0; i < 4; i++) {
		//if (map[red.y + dy[i]][red.x + dx[i]] != '#') {
			DFS(red.x, red.y, blue.x, blue.y, 1, i);
		//}
	}
	if (min_move == 11) cout << -1;
	else cout << min_move;
	return 0;
}
