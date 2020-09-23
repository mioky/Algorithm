/* 2020.09.23
 *
 * BOJ 15686
 * Completed!
 * 
 * 
 * 조합을 위해 DFS 돌리는 방법!
 * DFS 인자 조심하기
 * house의 인덱스 크기를 잘못정해줘서 엄청 해맸다....;.;
 *
 * Memory : 1124 KB
 * Time   : 4 ms
 */

#include <cstdio>

#define MAX_SIZE 51
using namespace std;

struct pos1 {
	int x;
	int y;
};

int N, M;
int map[MAX_SIZE][MAX_SIZE];
int house_idx = 0;
int chicken_idx = 0;
int ans = 1e7;
bool visit[14];
pos1 house[MAX_SIZE*2];
pos1 chicken[MAX_SIZE];

void DFS(int depth, int idx) {
	if (depth > M) return;
	if (depth == M) {
		int sum = 0; 
		for (int i = 0; i < house_idx; i++) {
			int min_dis = 101;
			for (int j = 0; j < chicken_idx; j++) {
				if (visit[j]) { //폐업안된 것들 중에
					int temp_x = house[i].x - chicken[j].x;
					int temp_y = house[i].y - chicken[j].y;
					if (temp_x < 0) temp_x *= -1;
					if (temp_y < 0) temp_y *= -1;
					if(min_dis > temp_x + temp_y) min_dis = temp_x + temp_y;
				}
			}
			sum += min_dis;
		}
		if (ans > sum) ans = sum;
		return;
	}
	if (idx == chicken_idx) return;
	for (int i = idx; i < chicken_idx; i++) { //폐업안할 치킨 집
		if (!visit[i]) {
			visit[i] = true;
			DFS(depth + 1, i+1);
			visit[i] = false;
		}
	}
}

int main() {

	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++)
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) { //집
				house[house_idx].x = j;
				house[house_idx++].y = i;
			}
			else if (map[i][j] == 2) { //치킨집
				chicken[chicken_idx].x = j;
				chicken[chicken_idx++].y = i;
			}
		}
	DFS(0,0);
	printf("%d\n", ans);
	return 0;
}
