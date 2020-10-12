/* 2020.10.12
*
* BOJ 17143
* Completed!
*
* 진짜 오래걸렸다.....
* 격자판에 상어 인덱스를 넣고, 그 인덱스에 대한 정보를 구조체로 만들어 주었음
* 상어 이동하는 부분에서 시간 진짜 많이걸림..ㅠㅠㅠ
* 상어끼리 잡아먹는 코드에서 조건을 잘 못만들어줘서 첫 번째 고비가 있었고,
* 상어 이동하는 부분을 for문으로 한 칸씩 이동시키는 부분에서 시간초과가 나서 
* 직접 거리 계산하는 코드로 대체함으로써 해결함 ㅠㅠㅠ 
*
* Memory : 1384 KB
* Time   : 28 ms
*/


#include <cstdio>
#define MAX_SIZE 101

struct info {
	int r; //row
	int c; //column
	int s; //속력
	int d; //이동 방향
	int z; //크기
};

int R, C, M;
int map[MAX_SIZE][MAX_SIZE];
info shark[12000]; //상어
int dx[5] = { 0,0,0,1,-1 }; //위, 아래, 오른쪽, 왼쪽
int dy[5] = { 0,-1,1,0,0 };


void move() { //상어 이동

	int check[12000] = { false, };

	for (int i = 1; i <= M; i++) { //상어 인덱스
		if (map[shark[i].r][shark[i].c] == 0||shark[i].r == -1) continue;
		if (!check[map[shark[i].r][shark[i].c]]) map[shark[i].r][shark[i].c] = 0; //현재 위치 상어 삭제
		check[i] = true;  //이동 완료

		int temp_s = shark[i].s;

		while (temp_s > 0) {
			if (shark[i].d == 1) {
				if (temp_s >= shark[i].r) {
					temp_s = temp_s - shark[i].r + 1;
					shark[i].r = 1;
					shark[i].d = 2;
				}
				else {
					shark[i].r -= temp_s;
					temp_s = 0;
				}
			}
			else if (shark[i].d == 2) {
				if (temp_s + shark[i].r > R) {
					temp_s = temp_s - (R - shark[i].r);
					shark[i].d = 1;
					shark[i].r = R;
				}
				else {
					shark[i].r += temp_s;
					temp_s = 0;
				}
			}
			else if (shark[i].d == 3) {
				if (temp_s + shark[i].c > C) {
					temp_s = temp_s - (C - shark[i].c);
					shark[i].d = 4;
					shark[i].c = C;
				}
				else {
					shark[i].c = shark[i].c + temp_s;
					temp_s = 0;
				}
			}
			else {
				if (shark[i].c <= temp_s) {
					temp_s = temp_s - shark[i].c + 1;
					shark[i].d = 3;
					shark[i].c = 1;
				}
				else {
					shark[i].c = shark[i].c - temp_s;
					temp_s = 0;
				}
			}
		}
		
		/////////////// 이 부분 시간초과 나는 것 같음///////////////////////
		/*for (int j = 0; j < shark[i].s; j++) {
			shark[i].r += dy[shark[i].d];
			shark[i].c += dx[shark[i].d];
			if (shark[i].r <1 || shark[i].c <1 || shark[i].r>R || shark[i].c >C) { //벽에 부딪히면 방향 전환
				if (shark[i].d == 3) shark[i].d = 4;
				else if (shark[i].d == 4) shark[i].d = 3;
				else if (shark[i].d == 1) shark[i].d = 2;
				else  shark[i].d = 1;
				shark[i].r += dy[shark[i].d]; //back
				shark[i].c += dx[shark[i].d];
				j--; 
			}
		} //이동 종료*/
		if (map[shark[i].r][shark[i].c] != 0 && check[map[shark[i].r][shark[i].c]]) { //도착한 곳에 다른 상어 존재하면서 그 상어의 이동이 끝났다면 크기 비교
			if (shark[map[shark[i].r][shark[i].c]].z < shark[i].z) {
				shark[map[shark[i].r][shark[i].c]].r = -1; //크기 작은 상어가 잡아 먹힘
				map[shark[i].r][shark[i].c] = i;
			}
			else { //map변경 x
				shark[i].r = -1;
			}
		}
		else { //
			map[shark[i].r][shark[i].c] = i; //이동 끝난 상어 값 저장
		}
	}
}

int main() {

	int sum = 0;

	scanf("%d %d %d", &R, &C, &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d %d %d", &shark[i].r, &shark[i].c, &shark[i].s, &shark[i].d, &shark[i].z);
		map[shark[i].r][shark[i].c] = i; //격자판에 상어 인덱스 새기기
	}
	
	for (int i = 1; i <= C; i++) {
		for (int j = 1; j <= R; j++) {
			if (map[j][i] != 0) {
				sum += shark[map[j][i]].z;
				shark[map[j][i]].r = -1; //상어 없어졌다는 뜻
				map[j][i] = 0; //상어 없애기
				break;
			}
		}
		move();
	}
	printf("%d\n", sum);
	
	return 0;
}
