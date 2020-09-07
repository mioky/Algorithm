#include <stdio.h>

int n, m, a[8][8], all_cnt, ans;
int dx[] = { -1,0,1,0 }, dy[] = { 0,1,0,-1 };
int cx[8], cy[8], c_idx;

void f(int cx, int cy, int *qx, int *qy, int &q_idx, int i) {
	int nx = cx; //cctv위치
	int ny = cy;
	i %= 4; //0
	while (nx + dx[i] >= 0 && ny + dy[i] >= 0 && nx + dx[i] < n && ny + dy[i] < m && a[nx + dx[i]][ny + dy[i]] != 6) {
		nx += dx[i]; ny += dy[i];
		if (a[nx][ny] == 0) {
			a[nx][ny] = -1; //cctv에서 보이는 위치 -1로 만듦
			qx[q_idx] = nx; //나중에 -1을 0으로 바꾸기 위함
			qy[q_idx++] = ny;
		}
	}
}

void dfs(int d, int cnt) {
	if (d == c_idx) { //cctv 갯수에 도달하면 
		ans = ans > all_cnt - cnt ? all_cnt - cnt : ans; //빈공간갯수 - cctv
		return;
	}
	int type = a[cx[d]][cy[d]]; //cctv 위치
	if (type == 1) {
		int qx[15], qy[15], q_idx;
		for (int i = 0; i < 4; i++) { //동서남북
			q_idx = 0;
			f(cx[d], cy[d], qx, qy, q_idx, i);
			dfs(d + 1, cnt + q_idx); //CCTV갯수 증가, cctv로 보이는 곳 갯수
			while (q_idx--) a[qx[q_idx]][qy[q_idx]] = 0; //-1을 0으로 돌림
		}
	}
	else if (type == 2) {
		int qx[15], qy[15], q_idx;
		for (int i = 0; i < 2; i++) { //2가지 방향
			q_idx = 0;
			for (int j = 0; j < 4; j += 2) //양방향이기때문에
				f(cx[d], cy[d], qx, qy, q_idx, i + j);
			dfs(d + 1, cnt + q_idx); 
			while (q_idx--) a[qx[q_idx]][qy[q_idx]] = 0;
		}
	}
	else if (type == 3) {
		int qx[15], qy[15], q_idx = 0;
		for (int i = 0; i < 4; i += 2) {
			q_idx = 0;
			f(cx[d], cy[d], qx, qy, q_idx, i);
			for (int j = 1; j < 4; j += 2) {
				int nq_idx = q_idx;
				f(cx[d], cy[d], qx, qy, nq_idx, i + j);
				dfs(d + 1, cnt + nq_idx);
				while (nq_idx-- > q_idx)
					a[qx[nq_idx]][qy[nq_idx]] = 0;
			}
			while (q_idx--) a[qx[q_idx]][qy[q_idx]] = 0;
		}
	}
	else if (type == 4) {
		int qx[4][15], qy[4][15], q_idx[4] = { 0, }, all_idx = 0;
		for (int i = 0; i < 4; i++) {
			f(cx[d], cy[d], qx[i], qy[i], q_idx[i], i);
			all_idx += q_idx[i];
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < q_idx[i]; j++)
				a[qx[i][j]][qy[i][j]] = 0;
			dfs(d + 1, cnt + all_idx - q_idx[i]);
			for (int j = 0; j < q_idx[i]; j++)
				a[qx[i][j]][qy[i][j]] = -1;
		}
		for (int i = 0; i < 4; i++) for (int j = 0; j < q_idx[i]; j++)
			a[qx[i][j]][qy[i][j]] = 0;
	}
	else if (type == 5) {
		int qx[4][15], qy[4][15], q_idx[4] = { 0, }, all_idx = 0;
		for (int i = 0; i < 4; i++) {
			f(cx[d], cy[d], qx[i], qy[i], q_idx[i], i);
			all_idx += q_idx[i];
		}
		dfs(d + 1, cnt + all_idx);
		for (int i = 0; i < 4; i++) for (int j = 0; j < q_idx[i]; j++)
			a[qx[i][j]][qy[i][j]] = 0;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		scanf("%d", &a[i][j]);
		if (a[i][j] == 0) all_cnt++; //빈 공간 갯수
		else if (a[i][j] != 6) cx[c_idx] = i, cy[c_idx++] = j; //cctv 위치
	}
	ans = all_cnt;
	dfs(0, 0);
	printf("%d\n", ans);
	return 0;
}
