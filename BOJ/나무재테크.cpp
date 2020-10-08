#include <iostream>
#include <vector>
#include <algorithm>
#define max_int 11
#define max_val 1001

using namespace std;

int n, m, k, ground[max_int][max_int], a[max_int][max_int], dead[max_int][max_int], x, y, z, result;
int dx[] = { 0, 0, 1, -1, -1, -1, 1, 1 }, dy[] = { -1, 1, 0, 0, -1, 1, 1, -1 };


vector<int> v[max_int][max_int];

int main() {
	// 1. 입력, n 격자의 크기, m 나무의 개수, k 년수
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			// 각 칸의 양분을 입력받습니다.
			scanf("%d", &a[i][j]);
			// 초기 양분은 5로 초기화
			ground[i][j] = 5;
		}
	}

	// m 개의 나무 정보를 받습니다.
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &x, &y, &z);
		v[x][y].push_back(z);
		result++;
	}

	// 2. k년 동안 반복합니다.
	for (int year = 1; year <= k; year++) {

		// 초기화
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				// 나이가 어린 나무부터 먹을 수 있도록 정렬
				sort(v[i][j].begin(), v[i][j].end());
				//죽은 나무의 양분을 더해줍니다.
				ground[i][j] += dead[i][j];
				// 양분을 더했으면 초기화해줍니다.
				dead[i][j] = 0;
			}
		}

		// 봄, 여름
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 0; k<(int)v[i][j].size(); k++) {
					// 남은 양분이 나이보다 클때
					if (ground[i][j] >= v[i][j][k]) {
						ground[i][j] -= v[i][j][k];
						v[i][j][k] += 1;
					}
					// 남은 양분이 나이보다 작을때
					else {

						int idx = k;
						int size = (int)v[i][j].size();

						// 죽은 나무 인접 리스트에서 제거
						for (int l = size - 1; l >= idx; l--) {
							dead[i][j] += (v[i][j][l] / 2);
							v[i][j].pop_back();
							result--;
						}
						break;
					}
				}
			}
		}


		// 가을
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int s = 0; s<v[i][j].size(); s++) {
					int tree = v[i][j][s];
					// 나무의 나이가 5의 배수일때
					if (tree % 5 != 0) continue;

					// 인접한 8칸에 나이 1인 나무를 번식합니다.
					for (int k = 0; k<8; k++) {
						int nx = i + dx[k];
						int ny = j + dy[k];

						if (nx > n || nx < 1 || ny > n || ny < 1) continue;

						v[nx][ny].push_back(1);
						result++;
					}
				}
			}
		}

		// 겨울
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				// S2D2 기계가 양분을 더해줍니다.
				ground[i][j] += a[i][j];
			}
		}
	}

	// 3. 출력
	printf("%d\n", result);
}
/*
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, K;
int A[11][11]; //양분 정보
int B[11][11]; //양분 정보
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int tree_count = 0;
vector<int> v[11][11];

void ASSort() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (v[i][j].size() == 0) continue;
			sort(v[i][j].begin(), v[i][j].end());
		}
	}
}

void Spring() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (v[i][j].size() == 0) continue;
			vector<int> temp;
			int dead = 0;
			sort(v[i][j].begin(), v[i][j].end());
			for (int k = 0; k < v[i][j].size(); k++) {
				
				if (A[i][j] >= v[i][j][k]) { //공급할 양분이 있다면
					A[i][j] -= v[i][j][k]; //양분 감소
					temp.push_back(v[i][j][k] + 1); //나이 증가
				}
				else { //양분이 부족하면 -> Summer
					dead += v[i][j][k] / 2; //죽은 나무 나이를 2로 나눈 값을 양분으로 추가
					 //v[i][j].erase(v[i][j].begin() + k); //나무 제거
					//k--;
				}
			}
			v[i][j].clear();
			for (int k = 0; k < temp.size(); k++)
				v[i][j].push_back(temp[k]);
			A[i][j] += dead;
		}
	}
}
void Fall() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < v[i][j].size(); k++) {
				if (v[i][j][k] % 5 == 0) { //5의 배수이면
					for (int m = 0; m < 8; m++) {
						int cur_x = i + dx[m];
						int cur_y = j + dy[m];
						if (cur_x < 0 || cur_y < 0 || cur_x >= N || cur_y >= N) continue;
						v[cur_y][cur_x].push_back(1); //나이가 1인 나무 생성
					}
				}
			}
		}
	}
}
void Winter() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			A[i][j] += B[i][j]; //양분 추가
		}
	}
}

void Run() {

	for (int i = 0; i < K; i++) { //K년
		
		Spring(); //
		Fall();
		Winter();
	}
	tree_count = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			tree_count += v[i][j].size();
}

int main() {
	int x, y, z;
	scanf("%d %d %d", &N, &M, &K);

	for (int i = 0; i < N; i++) { //양분 정보
		for (int j = 0; j < N; j++) {
			scanf("%d", &B[i][j]); //실시간 양분 정보
			A[i][j] = 5; //추가할 양분 정보
		}
	}
	for (int i = 0; i < M; i++) { //나무 위치
		scanf("%d %d %d", &x, &y, &z);
		v[y-1][x-1].push_back(z);
	}
	Run();
	printf("%d", tree_count);
	return 0;
}*/
