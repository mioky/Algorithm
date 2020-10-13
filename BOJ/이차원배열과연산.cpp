/* 2020.10.13
*
* BOJ 17140
* Completed!
*
* 
* 크게 어렵지 않음!
*
*
* Memory : 1216 KB
* Time   : 0 ms
*/

#include <cstdio>
#include <vector>
#include <algorithm>
#define MAX_SIZE 101

using namespace std;

int r, c, k;
int A[MAX_SIZE][MAX_SIZE];
int row = 3, col = 3;

void R_cal() {
	int temp_col = col;
	for (int i = 1; i <= row; i++) {
		bool visit[101] = { false, };
		vector<pair<int, int>> v; //등장 횟수
		for (int j = 1; j <= temp_col; j++) {
			if (A[i][j] != 0 && !visit[A[i][j]]) { //검사 안 한 것
				int count = 1;
				visit[A[i][j]] = true;
				for (int k = j + 1; k <= temp_col; k++) {
					if (A[i][j] == A[i][k]) count++;
				}
				v.push_back({ count, A[i][j] });
			}
		} //한 행 검사 끝
		sort(v.begin(), v.end());

		for (int j = 0; j < v.size(); j++) {
			if (j == 50) break; //100을 넘어가면 뒷 부분은 자르기
			A[i][(2 * j) + 1] = v[j].second; //번호
			A[i][(2 * j) + 2] = v[j].first; //등장 횟수
		}
		if ((v.size() * 2) < temp_col) {
			for (int k = 1; k <= temp_col - (v.size() * 2); k++)
				A[i][v.size() * 2 + k] = 0;
		}
		if (col < (v.size() * 2)) col = (v.size() * 2); //열 갯수 업데이트(등장횟수, 현재 번호)
		if (col > 100) col = 100; //10을 넘어가면 100 고정

	}
}

void C_cal() {
	int temp_row = row;

	for (int i = 1; i <= col; i++) {
		bool visit[101] = { false, };
		vector<pair<int, int>> v; //등장 횟수
		for (int j = 1; j <= temp_row; j++) {
			if (A[j][i] != 0&&!visit[A[j][i]]) { //검사 안 한 것
				int count = 1;
				visit[A[j][i]] = true;
				for (int k = j + 1; k <= temp_row; k++) {
					if (A[j][i] == A[k][i]) count++;
				}
				v.push_back({ count, A[j][i] });
			}
		} //한 행 검사 끝
		sort(v.begin(), v.end());

		for (int j = 0; j < v.size(); j++) {
			if (j == 50) break; //100을 넘어가면 뒷 부분은 자르기
			A[(2 * j)+1][i] = v[j].second; //번호
			A[(2 * j) +2][i] = v[j].first; //등장 횟수
		}

		if ((v.size() * 2) < temp_row) {
			for (int k = 1; k <= temp_row - (v.size() * 2); k++)
				A[v.size() * 2 + k][i] = 0;
		}
		if (row < (v.size() * 2)) row = (v.size() * 2); //열 갯수 업데이트(등장횟수, 현재 번호)
		if (row > 100) row = 100; //10을 넘어가면 100 고정

	}

}

int main() {

	int clk = 0;

	scanf("%d %d %d", &r, &c, &k); //
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			scanf("%d", &A[i][j]);

	while (clk!=101) {
		if (A[r][c] == k)
			break;
		if (row >= col)
			R_cal();
		else
			C_cal();
		clk++; //초 증가
		
	}

	if (clk == 101) printf("-1\n");
	else printf("%d", clk);
	return 0;
}
