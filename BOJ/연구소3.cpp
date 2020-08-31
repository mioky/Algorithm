  
/* BOJ 17142
 * Completed
 * 
 * BFS로 바이러스를 확산시키고, DFS로 활성화 시킬 바이러스 선택
 * 3차원 배열을 사용해서 각 바이러스가 활성화되었을 때를 표현!
 *
 * Memory : 1224 KB
 * Time   : 8 ms
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int dfs(int pol[][50][50], int n, int m, int v, int depth, int len, int sel[]) { //depth = 0, len =0
	if (len == m) { //바이러스 선택이 다 되었다면
		int r = 0;
		for (int i = 0; i<n; i++) {
			for (int j = 0; j<n; j++) {
				int tmp = 10000;
				for (int k = 0; k<m; k++) { //선택 바이러스 갯수
					if (pol[sel[k]][i][j] != 0) //sel[k]번째 바이러스의 위치가 벽, 바이러스, 바이러스 퍼진 시간
						tmp = min(tmp, pol[sel[k]][i][j]);
				}
				r = max(r, tmp); //위 if문에 안 들어가면 tmp가 10000으로 return, 최대 시간을 찾기 위해 
			}
		}
		return r;
	}
	if (depth == v) { //depth와 바이러스 갯수가 같다면, 모두 확산이 안되었을 경우
		return 10000;
	}

	int a = dfs(pol, n, m, v, depth + 1, len, sel);
	sel[len] = depth;
	int b = dfs(pol, n, m, v, depth + 1, len + 1, sel);
	return min(a, b);
}

int main() {
	int n, m;
	int lab[50][50] = {};
	int pol[10][50][50] = {};
	int dy[4] = { -1, 0, 1, 0 }, dx[4] = { 0, -1, 0, 1 };
	vector<pair<int, int> > vir;
	scanf("%d %d", &n, &m);

	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			scanf("%d", &lab[i][j]); //map받기
			if (lab[i][j] == 2) {
				vir.push_back(make_pair(i, j)); //바이러스 위치 기록
			}
		}
	}

	// 벽 표기
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			if (lab[i][j] != 0) { //빈칸이 아니면
				for (int v = 0; v<vir.size(); v++) { //바이러스 갯수 
					pol[v][i][j] = -1; //
				}
			}
		}
	}

	// 바이러스 미리 전파
	for (int v = 0; v<vir.size(); v++) {
		queue<pair<int, pair<int, int> > > q;
		bool vis[50][50] = {};
		q.push(make_pair(0, make_pair(vir[v].first, vir[v].second))); // 0,(바이러스 위치)
		vis[vir[v].first][vir[v].second] = true; //처음에 바이러스 위치 방문 표시
		while (!q.empty()) { //q가 빌 때까지
			int t = q.front().first; //first
			int y = q.front().second.first; //y
			int x = q.front().second.second; //x
			q.pop();
			for (int d = 0; d<4; d++) { //동서남북
				int ay = y + dy[d];
				int ax = x + dx[d];
				if (ay >= 0 && ax >= 0 && ay < n && ax < n && lab[ay][ax] != 1 && !vis[ay][ax]) { //벽이 아니고, 방문하지 않았다면
					if (pol[v][ay][ax] != -1) //빈 공간이라면
						pol[v][ay][ax] = t + 1; //시간 넣기
					vis[ay][ax] = true; //방문 표시
					q.push(make_pair(t + 1, make_pair(ay, ax))); //확산된 위치에 시간과 위치 넣기
				}
			}
		}
	}

	// m 개 선택 후, 계산
	int sel[10] = {};
	int re = dfs(pol, n, m, vir.size(), 0, 0, sel); //확산 다 시켜 놓은 배열, 배열크기, 바이러스 선택 갯수, 바이러스 갯수,
	if (re == 10000) //확산이 안된 지역이 있다면
		printf("-1");
	else
		printf("%d", re);

	return 0;
}
