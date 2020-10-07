/* 2020.10.07
*
* BOJ 16234
* Completed!
*
* 시간 미쳤다..! 다른 알고리즘으로 풀어봐야지ㅠㅠ
* BFS를 사용해서 문제를 풀었음.
* map을 한 번 검사했을 때 만들 수 있는 연합 -> count 한 번 증가
* 
*
*
* Memory : 1232 KB
* Time   : 300 ms
*/

#include <cstdio>
#include <queue>

using namespace std;

int N, L, R;
int A[51][51];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
int ans = 0;
struct pos {
	int x;
	int y;
};

bool BFS(bool visit[51][51], bool visit2[51][51]) {
	queue<pos> q;
	bool flag = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			bool flag2 = false;

			int unit_count = 0;
			int unit_sum = 0;
			q.push({ j,i });
			visit[i][j] = true;
			while (!q.empty()) {
				int cur_x = q.front().x;
				int cur_y = q.front().y;
				q.pop();
				if (visit2[cur_y][cur_x]) continue;
				unit_count++; //연합을 이루고 있는 칸의 개수
				unit_sum += A[cur_y][cur_x]; //연합의 인구수
				
				for (int k = 0; k < 4; k++) {
					int diff = 0;
					int mov_x = cur_x + dx[k];
					int mov_y = cur_y + dy[k];
					if (A[cur_y][cur_x] > A[mov_y][mov_x]) diff = A[cur_y][cur_x] - A[mov_y][mov_x];
					else diff = A[mov_y][mov_x] - A[cur_y][cur_x];
					if (mov_x < 0 || mov_x >= N || mov_y < 0 || mov_y >= N || visit[mov_y][mov_x] || diff < L || diff>R) continue;
					flag = true; //인구 이동
					flag2 = true;
					q.push({ mov_x,mov_y });
					visit[mov_y][mov_x] = true;
				}
			} 
			if (flag2) { //연합된 것이 있으면
				for (int m = 0; m < N; m++) {
					for (int n = 0; n < N; n++) {
						if (!visit2[m][n] && visit[m][n]) {
							visit2[m][n] = true;
							//visit[m][n] = false;
							A[m][n] = unit_sum / unit_count;
						}
					}
				}
				
			}
			else { //연합이 안됐다면 풀기
				visit[i][j] = false;
			}
		}
	}
	if (!flag) return false;
	else {
		ans++; //연합
		return true;
	}
}

int main() {

	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &A[i][j]);
		}
	}

	while(true){
		bool visit[51][51] = { false, };
		bool visit2[51][51] = { false, };

		//더 이상 인구이동이 없다면
		if (!BFS(visit,visit2)) {
			printf("%d\n", ans);
			return 0;
		}
		
	}

	return 0;
}
