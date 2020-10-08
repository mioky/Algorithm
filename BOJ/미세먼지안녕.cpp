/* 2020.10.08
*
* BOJ 17144
* Completed!
*
* copy 배열을 하나 만들어서 확산시킴
* 공기순환 시뮬레이션 코드 실수하지 않기!
*
*
* Memory : 1132 KB
* Time   : 44 ms
*/
#include <cstdio>

int R, C, T;
int A[51][51];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
int air_x[2], air_y[2];
int _copy[51][51];
void Run() {

	for (int i = 0; i < R; i++) { //미세먼지 확산
		for (int j = 0; j < C; j++) {
			int count = 0; //확산 할 수 있는 공간
			if (A[i][j] > 0) { //미세먼지라면
				for (int k = 0; k < 4; k++) {
					int mov_x = j + dx[k];
					int mov_y = i + dy[k];
					if (mov_x < 0 || mov_x >= C || mov_y < 0 || mov_y >= R || A[mov_y][mov_x] == -1) continue;
					count++;
					_copy[mov_y][mov_x] += A[i][j] / 5;
				}
				_copy[i][j] += A[i][j] - ((A[i][j] / 5) * count);
			}
			else if (A[i][j] == -1)
				_copy[i][j] = -1;
			
		}
	}
	/////////////////////// 위 //////////////////////////////////////
	int temp = _copy[0][C-1];

	for (int i = 0; i <= air_y[0]; i++){
		if (_copy[air_y[0] - i][0] != -1) {
			_copy[air_y[0] - i][0] = _copy[air_y[0] - i -1][0];
		}
		_copy[i][C-1] = _copy[i + 1][C-1];
	}
	for (int i = 0; i < C - 2; i++) {
		_copy[air_y[0]][C - i - 1] = _copy[air_y[0]][C - i - 2];
		_copy[0][i] = _copy[0][i + 1];
	}
	_copy[air_y[0]][1] = 0;
	_copy[0][C - 2] = temp;
	///////////////////////////// 아래 ///////////////////////////
	temp = _copy[R - 1][C - 1];
	for (int i = 0; i < R - air_y[1]; i++) {
		if (_copy[air_y[1] + i][0] != -1) {
			_copy[air_y[1] + i][0] = _copy[air_y[1] + i + 1][0];
		}
		_copy[R - 1 - i][C - 1] = _copy[R - i - 2][C - 1];
	}
	for (int i = 0; i < C - 2; i++) {
		_copy[air_y[1]][C - i - 1] = _copy[air_y[1]][C - i -2];
		_copy[R - 1][i] = _copy[R - 1][i + 1];
	}
	_copy[air_y[1]][1] = 0;
	_copy[R - 1][C - 2] = temp;

	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) {
			A[i][j] = _copy[i][j];
			_copy[i][j] = 0;
		}
}

int main() {

	int air_idx = 0;
	int sum = 0;
	scanf("%d %d %d", &R, &C, &T);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d", &A[i][j]);
			if (A[i][j] == -1) {
				air_x[air_idx] = j;
				air_y[air_idx++] = i;
			}
		}
	}
	for (int i = 0; i < T; i++) {
		Run();
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (A[i][j] > 0) sum += A[i][j];
		}
	}
	printf("%d\n", sum);
	return 0;
}
