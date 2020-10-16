/* 2020.10.16
*
* BOJ 3190
* Completed!
*
* vector사용
* push_back은 맨 뒤에 값을 넣는 것이기때문에 insert 함수사용
* pair<int, int>일 때는 v.insert(시작위치, {y,x}) 이렇게 사용
*
* Memory : 1216 KB
* Time   : 0 ms
*/
#include <cstdio>
#include <vector>
#define MAX_SIZE 100 
using namespace std;

int N, K, L;
int map[MAX_SIZE][MAX_SIZE];
int sec[MAX_SIZE]; //sec초가 끝난 뒤
char dir[MAX_SIZE]; //해당 방향으로 회전
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
vector<pair<int, int>> snake; //뱀의 위치 저장
int snake_dir = 0; //뱀의 방향
int _count = 0;

void move() {
	int idx = 0;
	snake.push_back({ 0,0 });
	while (true) {
		if (sec[idx] == _count) { //해당 시간에 방향 회전
			if (dir[idx] == 'L') {
				if (snake_dir == 0)
					snake_dir = 3;
				else snake_dir -= 1;
			}
			else {
				snake_dir = (snake_dir + 1) % 4; //
			}
			idx++;
		}
		int mov_x = snake[0].second + dx[snake_dir];
		int mov_y = snake[0].first + dy[snake_dir];
		if (mov_x < 0 || mov_y < 0 || mov_x >= N || mov_y >= N || map[mov_y][mov_x] == 1) break; //벽, 몸통 부딪히면 종료
		if (map[mov_y][mov_x] != 2) { //사과 존재x
			map[snake[snake.size() - 1].first][snake[snake.size() - 1].second] = 0; //꼬리 자르기
			snake.pop_back();
		}
		map[mov_y][mov_x] = 1;
		snake.insert(snake.begin(), {mov_y, mov_x}); //머리 넣기

		_count++; //초 증가

	}

}

int main() {
	int x, y;
	scanf("%d %d", &N, &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &y, &x);
		map[--y][--x] = 2; //2는 사과
	}
	scanf("%d", &L);
	for (int i = 0; i < L; i++) {
		scanf("%d %c", &sec[i], &dir[i]);
	}
	map[0][0] = 1; //뱀은 1
	move();
	printf("%d\n", _count+1);
	return 0;
}
