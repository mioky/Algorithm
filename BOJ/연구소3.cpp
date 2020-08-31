#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int dfs(int pol[][50][50], int n, int m, int v, int depth, int len, int sel[]) { //depth = 0, len =0
	if (len == m) { //���̷��� ������ �� �Ǿ��ٸ�
		int r = 0;
		for (int i = 0; i<n; i++) {
			for (int j = 0; j<n; j++) {
				int tmp = 10000;
				for (int k = 0; k<m; k++) { //���� ���̷��� ����
					if (pol[sel[k]][i][j] != 0) //sel[k]��° ���̷����� ��ġ�� ��, ���̷���, ���̷��� ���� �ð�
						tmp = min(tmp, pol[sel[k]][i][j]);
				}
				r = max(r, tmp); //�� if���� �� ���� tmp�� 10000���� return, �ִ� �ð��� ã�� ���� 
			}
		}
		return r;
	}
	if (depth == v) { //depth�� ���̷��� ������ ���ٸ�, ��� Ȯ���� �ȵǾ��� ���
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
			scanf("%d", &lab[i][j]); //map�ޱ�
			if (lab[i][j] == 2) {
				vir.push_back(make_pair(i, j)); //���̷��� ��ġ ���
			}
		}
	}

	// �� ǥ��
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			if (lab[i][j] != 0) { //��ĭ�� �ƴϸ�
				for (int v = 0; v<vir.size(); v++) { //���̷��� ���� 
					pol[v][i][j] = -1; //
				}
			}
		}
	}

	// ���̷��� �̸� ����
	for (int v = 0; v<vir.size(); v++) {
		queue<pair<int, pair<int, int> > > q;
		bool vis[50][50] = {};
		q.push(make_pair(0, make_pair(vir[v].first, vir[v].second))); // 0,(���̷��� ��ġ)
		vis[vir[v].first][vir[v].second] = true; //ó���� ���̷��� ��ġ �湮 ǥ��
		while (!q.empty()) { //q�� �� ������
			int t = q.front().first; //first
			int y = q.front().second.first; //y
			int x = q.front().second.second; //x
			q.pop();
			for (int d = 0; d<4; d++) { //��������
				int ay = y + dy[d];
				int ax = x + dx[d];
				if (ay >= 0 && ax >= 0 && ay < n && ax < n && lab[ay][ax] != 1 && !vis[ay][ax]) { //���� �ƴϰ�, �湮���� �ʾҴٸ�
					if (pol[v][ay][ax] != -1) //�� �����̶��
						pol[v][ay][ax] = t + 1; //�ð� �ֱ�
					vis[ay][ax] = true; //�湮 ǥ��
					q.push(make_pair(t + 1, make_pair(ay, ax))); //Ȯ��� ��ġ�� �ð��� ��ġ �ֱ�
				}
			}
		}
	}

	// m �� ���� ��, ���
	int sel[10] = {};
	int re = dfs(pol, n, m, vir.size(), 0, 0, sel); //Ȯ�� �� ���� ���� �迭, �迭ũ��, ���̷��� ���� ����, ���̷��� ����,
	if (re == 10000) //Ȯ���� �ȵ� ������ �ִٸ�
		printf("-1");
	else
		printf("%d", re);

	return 0;
}