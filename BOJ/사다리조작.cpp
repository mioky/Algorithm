/* 2020.09.07
 *
 * BOJ 15684
 * Completed!
 * 
 * 
 * 
 *
 * Memory : 1112 KB
 * Time   : 200 ms
 */
#include <cstdio>

int N, M, H;
int a, b;
int map[31][11];
int pos;
bool check = false;
int _min = 4;

bool Run() {
	for (int i = 1; i <= N; i++) {
		pos = i;
		for (int j = 1; j <= H; j++) {
			if (map[j][pos] == 1) { //오른쪽으로 이동
				pos += 1;
			}
			else if (pos != 1 && map[j][pos-1] == 1)
				pos -= 1;
		}
		if (pos != i)
			return false;
	}
	return true;
}

void DFS(int cnt, int line_cnt, int temp_i, int temp_j) {
	if (check) return;
	if (line_cnt == cnt) {
		check = Run();
		return;
	}
	for (int i = temp_i; i <= H; i++) {
		for (int j = temp_j-1; j < N; j++) {
			
				if (map[i][j] == 0&&map[i][j] != 1 && map[i][j - 1] != 1 && map[i][j + 1] != 1) {
					map[i][j] = 1;
					DFS(cnt + 1, line_cnt, i, j);
					map[i][j] = 0;
				
			}
		}
	}
}

int main() {
	scanf("%d%d%d", &N, &M, &H);
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &a, &b);
		map[a][b] = 1;
	}

	for (int i = 0; i <= 3; i++) {
		DFS(0, i, 1,1);
		if (check) {
			printf("%d", i);
			return 0;
		}
	}
	printf("%d", -1);

	return 0;

}
