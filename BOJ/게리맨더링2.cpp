/* 2020.08.31
 *
 * BOJ 17779
 * Completed!
 * 
 * 구역의 조건을 코드화로 시키면 끝!
 * 조건이 복잡하니 실수하지 않도록 유의!
 *
 * Memory : 1112 KB
 * Time   : 16 ms
 */

#include <cstdio>
int A[21][21];
int N;
int count[6]; 
bool five[21][21] = { false };
int real_min = 10000000;
int _max;
int _min;
 
int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	for (int x = 1; x <= N - 2; x++) { //x
		for (int y = 2; y <= N - 1; y++) { //y
			for (int d1 = 1; d1 <= N - 2; d1++) { //d1
				if (1 > y - d1) break;
				for (int d2 = 1; d2 <= N - 2; d2++) { //d2
					if (x >= x + d1 + d2 || x + d1 + d2 > N || y + d2 > N)
						break;

					for (int r = 1; r <= N; r++) {
						for (int c = 1; c <= N; c++) {

							if (r < x + d1 && c <= y && !(r >= x && c >= y - (r - x)))
								count[1] += A[r][c];
							else if (r <= x + d2 && y < c && c <= N && !(r >= x && c <= y + (r - x)))
								count[2] += A[r][c];
							else if (x + d1 <= r && r <= N && c < y - d1 + d2 && !(r <= x + d1 + d2 && c >= (y - d1 + d2 - (x + d1 + d2 - r))))
								count[3] += A[r][c];
							else if (x + d2 < r && r <= N && y - d1 + d2 <= c && c <= N && !(r <= x + d1 + d2 && c <= (y - d1 + d2 + (x + d1 + d2 - r))))
								count[4] += A[r][c];
							else
								count[5] += A[r][c];
						}
					}
					_max = count[1];
					_min = count[1];
					count[1] = 0;
					for (int i = 2; i <= 5; i++) {
						_max = _max > count[i] ? _max : count[i];
						_min = _min < count[i] ? _min : count[i];
						count[i] = 0;
					}
					real_min = (_max - _min) < real_min ? (_max - _min) : real_min;
				}
			}
		}
	}
	printf("%d", real_min);
	return 0;
}
