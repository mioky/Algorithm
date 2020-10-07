#include <cstdio>
int A[8], B[8],C[8],D[8];
int K; //회전 횟수
int num, dir; //번호 방향
bool check[4] = { false };
void Clock(int num2);
void Clock2(int num2);
void Clock(int num2){ //시계방향
	if (num2 == 1) {
		check[0] = true;
		if (A[2] != B[6] && !check[1]) { //방향이 다르다면
			Clock2(2);
		}
		int temp = A[0];
		A[0] = A[7];
		for (int i = 7; i > 1; i--)
			A[i] = A[i - 1];
		A[1] = temp;
	}
	else if (num2==2) {
		check[1] = true;
		if (B[2] != C[6] && !check[2]) { //방향이 다르다면
			Clock2(3);
		}
		if (B[6] != A[2] && !check[0]) {
			Clock2(1);
		}
		int temp = B[0];
		B[0] = B[7];
		for (int i = 7; i > 1; i--)
			B[i] = B[i - 1];
		B[1] = temp;
	}
	else if (num2==3) {
		check[2] = true;
		if (C[2] != D[6] && !check[3]) { //방향이 다르다면
			Clock2(4);
		}
		if (C[6] != B[2] && !check[1]) {
			Clock2(2);
		}
		int temp = C[0];
		C[0] = C[7];
		for (int i = 7; i > 1; i--)
			C[i] = C[i - 1];
		C[1] = temp;
	}
	else {
		check[3] = true;
		if (C[2] != D[6] && !check[2]) { //방향이 다르다면
			Clock2(3);
		}
		int temp = D[0];
		D[0] = D[7];
		for (int i = 7; i > 1; i--)
			D[i] = D[i - 1];
		D[1] = temp;
	}
}
void Clock2(int num2) {
	if (num2==1) {
		check[0] = true;
		if (A[2] != B[6] && !check[1]) { //방향이 다르다면
			Clock(2);
		}
		int temp = A[0];
		for (int i = 0; i < 7; i++)
			A[i] = A[i + 1];
		A[7] = temp;
	}
	else if (num2==2) {
		check[1] = true;
		if (B[2] != C[6] && !check[2]) { //방향이 다르다면
			Clock(3);
		}
		if (B[6] != A[2] && !check[0]) {
			Clock(1);
		}
		int temp = B[0];
		for (int i = 0; i < 7; i++)
			B[i] = B[i + 1];
		B[7] = temp;
	}
	else if (num2==3) {
		check[2] = true;
		if (C[2] != D[6] && !check[3]) { //방향이 다르다면
			Clock(4);
		}
		if (C[6] != B[2] && !check[1]) {
			Clock(2);
		}
		int temp = C[0];
		for (int i = 0; i < 7; i++)
			C[i] = C[i + 1];
		C[7] = temp;

	}
	else {
		check[3] = true;
		if (C[2] != D[6] && !check[2]) { //방향이 다르다면
			Clock(3);
		}
		int temp = D[0];
		for (int i = 0; i < 7; i++)
			D[i] = D[i + 1];
		D[7] = temp;
	}
}

int main() {
	for (int i = 0; i < 8; i++)
		scanf("%1d", &A[i]);
	for (int i = 0; i < 8; i++)
		scanf("%1d", &B[i]);
	for (int i = 0; i < 8; i++)
		scanf("%1d", &C[i]);
	for (int i = 0; i < 8; i++)
		scanf("%1d", &D[i]);
	scanf("%d", &K);
	for (int i = 0; i < K; i++) {
		scanf("%d%d", &num, &dir);
		if (dir == 1) //시계방향
			Clock(num);
		else
			Clock2(num);
		for (int j = 0; j < 4; j++)
			check[j] = false;
	}
	int sum = 0;
	if (A[0] == 1) sum += 1;
	if (B[0] == 1)sum += 2;
	if (C[0] == 1)sum += 4;
	if (D[0] == 1)sum += 8;
	printf("%d", sum);
	return 0;
}
