#include <cstdio>

int N;
int T[15], P[15];
int ans = 0;

void DFS(int price, int day) { //이전 가격, 현재 날짜

	if (day > N) {
		return;
	}
	ans = ans < price ? price : ans;

	for (int i = day; i < N; i++) {
		DFS(price+P[i], i + T[i]);
	}
}

int main() {

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &T[i], &P[i]);

	DFS(0, 0);
	printf("%d\n", ans);
	return 0;
}
