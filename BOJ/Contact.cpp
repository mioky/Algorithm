#include <cstdio>
#include <queue>
#include <vector>

#define MAX_SIZE 1000

using namespace std;

int to[MAX_SIZE];
int from[MAX_SIZE];
bool visit[MAX_SIZE];
int data_len, start;
int max_num=0;

void BFS() {

	queue<int> q;
	q.push(start);
	visit[start] = true;
	while (!q.empty()) {
		int queSize = q.size();
		max_num = 0;
		for (int i = 0; i < queSize; i++) { //같은 깊이에서 비교하기 위해
			int num = q.front(); 
			q.pop();
			if (max_num < num) { //같은 깊이에서 가장 큰 숫자 찾기
				max_num = num;
			}
			for (int i = 0; i < data_len / 2; i++) {
				if (num == from[i] && !visit[to[i]]) {
					q.push(to[i]);
					visit[to[i]] = true;
				}
			}
		}
	}
}

int main() {
	//freopen("Input.txt", "r", stdin);

	for (int t = 1; t <= 10; t++) {
		scanf("%d %d", &data_len, &start);
		for (int i = 0; i < data_len / 2; i++) {
			scanf("%d %d", &from[i], &to[i]);
		}

		BFS();
		for (int i = 0; i < 100; i++)
			visit[i] = false;
		printf("#%d %d\n", t, max_num);
	}
	return 0;
}