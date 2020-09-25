/* 2020.09.25
*
* BOJ 3190
* Completed!
*
* 뱀의 몸의 위치들을 배열에 저장한 후, 이동할 때마다 뱀의 위치도 반복문을 통해 변경!
* 몸을 오른쪽 왼쪽 회전하는 것을 동서남북 배열로 해결!
* 뱀의 위치 이동때문에 푸는데 조금 걸림
* 알고리즘 자체는 오래 걸리지 않음
*
* Memory : 1228 KB
* Time   : 0 ms
*/

#include <cstdio>
#define MAX_SIZE 100

struct pos {
	int x;
	int y;
};

int N, K, l;
int map[MAX_SIZE][MAX_SIZE] = { 0, };
int sec[MAX_SIZE];
char dir[MAX_SIZE];
pos snake[MAX_SIZE*MAX_SIZE];
int dx[4] = { 1,0,-1,0 }; //동남서북
int dy[4] = { 0,1,0,-1 };

int move() {
	int ans = 0; int snake_count = 1;
	int cur_dir = 0; //동
	while (true) {
		for (int i = 0; i < l; i++) {
			if (sec[i] == ans) { //시간되면 방향 회전
				if (dir[i] == 'D') {
					cur_dir = (cur_dir+1)%4;
					break;
				}
				else {
					cur_dir = (cur_dir + 3) % 4;
					break;
				}
			}
		}
		int cur_x = snake[0].x + dx[cur_dir]; //머리 이동
		int cur_y = snake[0].y + dy[cur_dir];
		
		if (cur_x < 0 || cur_y < 0 || cur_x >= N || cur_y >= N || map[cur_y][cur_x] == 1) return ans+1;
		
		if (map[cur_y][cur_x] == 2) { //사과
			snake_count++;
		}
		else {
			map[snake[snake_count - 1].y][snake[snake_count - 1].x] = 0;
		}
		map[cur_y][cur_x] = 1;
		for (int i = snake_count - 1; i >0; i--) {
			snake[i].x = snake[i - 1].x;
			snake[i].y = snake[i - 1].y;
		}
		snake[0].x = cur_x;
		snake[0].y = cur_y;
		ans++;
	}

}

int main() {

	scanf("%d %d", &N, &K);
	int row, col;
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &row, &col);
		map[row - 1][col - 1] = 2; //사과
	}
	scanf("%d", &l);
	for (int i = 0; i < l; i++)
		scanf("%d %c", &sec[i], &dir[i]);
	map[0][0] = 1; //뱀 존재
	snake[0].x = 0, snake[0].y = 0;
	printf("%d", move());
	return 0;
}
