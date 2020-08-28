#include <cstdio>

int N, M, T, x, d, k;
int Circle[52][52];
int check[52][52] = { false };
int sum = 0;

void ave(float temp_ave1) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Circle[i][j] != 0) {
				if (Circle[i][j] > temp_ave1)
					Circle[i][j]--;
				else if (Circle[i][j] < temp_ave1)
					Circle[i][j]++;
			}
		}
	}
}

void adj() {
	int adj_check = false;
	float temp_ave = 0;
	int temp_count = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Circle[i][j] != 0) {
				if (Circle[i][j] == Circle[i][j%M + 1]) { //오른쪽 애랑 같은가?
					check[i][j] = true;
					check[i][j%M + 1] = true;
					adj_check = true;
				}
				if (Circle[i][j] == Circle[i + 1][j]) {
					check[i][j] = true;
					check[i + 1][j] = true;
					adj_check = true; //인접한 수가 있다!
				}
			}
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (check[i][j]) {
				Circle[i][j] = 0;
				check[i][j] = false;
			}
			else if (Circle[i][j] != 0) {
				temp_ave += Circle[i][j];
				temp_count++;
			}
		}
	}
	temp_ave /= temp_count; //평균

	if (!adj_check) ave(temp_ave);

}
void rotation() {
	for (int i = 1; i <= N / 2; i++) {
		if (i*x > N) break;
		for (int j = 0; j < k; j++) {
			if (d == 0) { //시계
				int temp = Circle[x*i][1];
				Circle[x*i][1] = Circle[x*i][M];
				for (int m = 0; m < M - 2; m++)
					Circle[x*i][M - m] = Circle[x*i][M - m - 1];
				Circle[x*i][2] = temp;
			}
			else { //반시계
				int temp = Circle[x*i][1];
				for (int m = 1; m <= M - 1; m++) {
					Circle[x*i][m] = Circle[x*i][m + 1];
				}
				Circle[x*i][M] = temp;
			}
		}
	}
	adj();
}

int main() {

	scanf("%d%d%d", &N, &M, &T);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &Circle[i][j]);
		}
	}
	for (int i = 0; i < T; i++) {
		scanf("%d%d%d", &x, &d, &k);
		rotation();
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (Circle[i][j] != 0)
				sum += Circle[i][j];
		}
	}
	printf("%d", sum);
	return 0;
}