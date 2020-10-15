/* 2020.10.15
*
* BOJ 14890
* Completed!
*
* 행끼리 열끼리 따로 나누지 않고, 맵 복사를 통해 해결 가능
*
*
* Memory : 1188 KB
* Time   : 0 ms
*/

#include <cstdio>
#define MAX_SIZE 100

int N, L;
int map[MAX_SIZE][MAX_SIZE];
int temp_map[MAX_SIZE][MAX_SIZE];
int ans = 0;

void Road() {

	for (int i = 0; i < N; i++) {
		int temp = map[i][0];
		int count = 1;
		bool check = false;
		for (int j = 1; j < N; j++) {
			if (temp == map[i][j]) {
				count++;
			}
			else if (temp - map[i][j] == -1) {
				if (count < L || count < 0) {
					check = true;
					break;
				}
				temp = map[i][j];
				count = 1;
			}
			else if (temp - map[i][j] == 1) {
				if (count < 0) {
					check = true;
					break;
				}
				count = 0;
				count -= L-1;
				temp = map[i][j];
			}
			else { //1 이상 차이가 난다면
				check = true;
				break;
			}
		}
		if(count < 0) check = true;
		if(!check) ans++;
	}
}

int main() {
	scanf("%d %d", &N, &L);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			temp_map[j][i] = map[i][j];
		}

	Road();
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			map[i][j] = temp_map[i][j];
	Road();
	printf("%d\n", ans);

	return 0;
}
