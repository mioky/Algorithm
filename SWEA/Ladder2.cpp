#include <cstdio>
#include <vector>
#define MAX_SIZE 101

using namespace std;

struct info {
	int num; //시작 위치
	int count; //이동 횟수
};

int map[MAX_SIZE][MAX_SIZE];
int dx[2] = { -1,1 };
info _min;

void move(vector<info> &v) {
	_min.num = 0;
	_min.count = 1e9;
	for (int i = 0; i < v.size(); i++) {
		int col = v[i].num;
		for (int row = 1; row<100; row++) {
			for (int dir = 0; dir < 2; dir++) {
				int temp_x = col + dx[dir];
				if (temp_x < 0 || temp_x >= 100 || map[row][temp_x] == 0) continue;
				col = temp_x;
				v[i].count++;
				while (col+dx[dir] >= 0 && col + dx[dir] < 100 && map[row][col + dx[dir]] != 0) { //좌우 이동
					col += dx[dir];
					v[i].count++;
				}
				break;
			}
		}
		
		if (_min.count > v[i].count) {
			_min.count = v[i].count;
			_min.num = v[i].num;
		}
		else if (_min.count == v[i].count) {
			if (_min.num < v[i].num) {
				_min.count = v[i].count;
				_min.num = v[i].num;
			}
		}
		
	}
}
int main() {
	freopen("Input.txt", "r", stdin);

	int T;

	for (int t = 1; t <= 10; t++) {
		scanf("%d", &T);
		vector<info> v;
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				scanf("%d", &map[i][j]);
				if (i == 0 && map[i][j] == 1) v.push_back({ j,0 });
			}
		}
		move(v);
		printf("#%d %d\n", T,_min.num);
	}
	return 0;
}