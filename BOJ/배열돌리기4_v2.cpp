/* 2020.10.16
*
* BOJ 17406
* Completed!
*
* 시뮬레이션
*
*
* Memory : 1184 KB
* Time   : 12 ms
*/

#include<cstdio>
#define MAX_SIZE 51

using namespace std;
//인덱스 1부터 시작
struct info {
	int r;
	int c;
	int s;
};

int N, M, K;
int A[MAX_SIZE][MAX_SIZE];
int back[6][MAX_SIZE][MAX_SIZE]; //백트래킹을 위함
info rotation[6]; //최대 6번 회전 정보
bool visit[6];
int result = 5001;
void move(int r, int c, int s) {

	for (int i = 1; i <= s; i++) {
		int temp1 = A[r - i][c - i];
		int temp2 = A[r - i][c + i];
		int temp3 = A[r + i][c + i];
		int temp4 = A[r + i][c - i];
		for (int j = 0; j < 2 * i - 1; j++) { //등차수열만큼 회정
			A[r - i][c + i - j] = A[r - i][c + i - j - 1];
			A[r + i - j][c + i] = A[r + i - j - 1][c + i];
			A[r + i][c - i + j] = A[r + i][c - i + j + 1];
			A[r - i + j][c - i] = A[r - i + j + 1][c - i];
		}
		A[r - i][c - i + 1] = temp1;
		A[r - i + 1][c + i] = temp2;
		A[r + i][c + i - 1] = temp3;
		A[r + i - 1][c - i] = temp4;
	}

}

void DFS(int depth) {
	if (depth == K) { //다 돌렸을 때
		int ans = 5001;
		for (int i = 1; i <= N; i++) {
			int sum = 0;
			for (int j = 1; j <= M; j++) {
				sum += A[i][j];
			}
			if (ans > sum) ans = sum;
		}
		result = result > ans ? ans : result; //ans는 배열 A값이고, result는 최종적인 최소 배열 A값
		return;
	}
	for (int i = 0; i < K; i++) {
		if (!visit[i]) { //회전 안시킨 것만
			for (int j = 1; j <= N; j++)
				for (int k = 1; k <= M; k++)
					back[depth][j][k] = A[j][k];
			visit[i] = true;
			move(rotation[i].r, rotation[i].c, rotation[i].s); //이동
			DFS(depth + 1);
			visit[i] = false;
			for (int j = 1; j <= N; j++)
				for (int k = 1; k <= M; k++)
					A[j][k] = back[depth][j][k]; //백트래킹
		}
	}
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	for (int i = 0; i < K; i++)
		scanf("%d %d %d", &rotation[i].r, &rotation[i].c, &rotation[i].s);

	DFS(0);
	printf("%d\n", result);
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
