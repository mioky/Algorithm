#include <string>
#include <vector>

using namespace std;

int solution(int m, int n, vector<string> board) {
	int answer = 0;
	bool flag = false;
	while (flag == false) {
		vector<vector<bool>> visit(m, vector<bool>(n));
		flag = true;
		for (int i = 0; i <m-1;i++) {
			for (int j = 0; j < n - 1; j++) {
				if (board[i][j] == 0)
					continue;
				if ((board[i][j] == board[i][j + 1])&& (board[i][j]== board[i + 1][j])&&(board[i][j]== board[i + 1][j + 1])) {
					visit[i][j] = 1;
					visit[i][j+1] = 1;
					visit[i+1][j] = 1;
					visit[i + 1][j + 1] = 1;
					flag = false;
				}
			}
		}

		for (int i = 0; i < m; i++) {	//제거
			for (int j = 0; j < n; j++) {
				if (visit[i][j]==1) {
					answer++;
					for (int k = i-1; k >=0; k--) {
						board[k + 1][j] = board[k][j];
						board[k][j] = 0;
					}
				}
			}
		}

	}

	return answer;
}
