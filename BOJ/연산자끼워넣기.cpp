/* 2020.08.31
 *
 * BOJ 14888
 * Completed!
 * 
 * 
 *
 * Memory : 1112 KB
 * Time   : 0 ms
 */

#include <cstdio>

int N;
int A[11]; //수열
int op[4]; //연산자
int _min = 1000000000;
int _max = -1000000000;

void DFS(int cnt, int total) { //DFS 인자는 인자내에서만 연산하고 그외에는 연산x
	if (cnt == N - 1) { //연산 종료
		if (_min > total) _min = total;
		if (_max < total) _max = total;
		return;
	}
	for (int i = 0; i < 4; i++) { //덧 , 뺄, 곱, 나
		if (op[i] != 0) { //연산이 남아 있다면
			op[i]--;
			if (i == 0) //덧
				DFS(cnt + 1, total+ A[cnt + 1]);
			else if(i == 1) //뺄
				DFS(cnt + 1, total - A[cnt + 1]);
			else if(i == 2) //곱
				DFS(cnt + 1, total * A[cnt + 1]);
			else //나
				DFS(cnt + 1, total / A[cnt + 1]);
			op[i]++;
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	for (int i = 0; i < 4; i++)
		scanf("%d", &op[i]);

	DFS(0, A[0]);

	printf("%d\n%d", _max, _min);
	return 0;
}
