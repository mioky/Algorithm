#include <iostream>

using namespace std;
int T, n;
char board[3][3][6], as, di;
// 0:위(w) ,1:뒤(o), ,2:오(b) ,3:앞(r) ,4:왼(g) ,5:밑(y)
void st(int idx) {
	char tmpp[3];
	for (int i = 0; i < 3; i++)tmpp[i] = board[0][i][idx];
	for (int j = 0; j < 2; j++) {
		board[0][2 - j][idx] = board[j][0][idx];
		board[j][0][idx] = board[2][j][idx];
		board[2][j][idx] = board[2 - j][2][idx];
		board[2 - j][2][idx] = tmpp[2 - j];
	}
}
void rev(int idx) {
	char tmpp[3];
	for (int i = 0; i < 3; i++)tmpp[i] = board[0][i][idx];
	for (int j = 0; j < 2; j++) {
		board[0][j][idx] = board[j][2][idx];
		board[j][2][idx] = board[2][2 - j][idx];
		board[2][2 - j][idx] = board[2 - j][0][idx];
		board[2 - j][0][idx] = tmpp[j];
	}
}

void U(char Ua, char Ud) {
	char tmp[3];
	for (int i = 0; i < 3; i++)tmp[i] = board[2][i][1];
	if (Ud == '+') {
		st(0);
		for (int i = 0; i < 3; i++) {
			board[2][2 - i][1] = board[i][2][4];
			board[i][2][4] = board[0][i][3];
			board[0][i][3] = board[2 - i][0][2];
			board[2 - i][0][2] = tmp[2 - i];
		}
	}
	else {
		rev(0);
		for (int i = 0; i < 3; i++) {
			board[2][i][1] = board[i][0][2];
			board[i][0][2] = board[0][2 - i][3];
			board[0][2 - i][3] = board[2 - i][2][4];
			board[2 - i][2][4] = tmp[i];
		}
	}
}
void D(char Da, char Dd) {
	char tmp[3];
	for (int i = 0; i < 3; i++)tmp[i] = board[2][i][3];
	if (Dd == '+') {
		st(5);
		for (int i = 0; i < 3; i++) {
			board[2][2 - i][3] = board[2 - i][0][4];
			board[2 - i][0][4] = board[0][i][1];
			board[0][i][1] = board[i][2][2];
			board[i][2][2] = tmp[2 - i];
		}

	}
	else {
		rev(5);
		for (int i = 0; i < 3; i++) {
			board[2][i][3] = board[2 - i][2][2];
			board[2 - i][2][2] = board[0][2 - i][1];
			board[0][2 - i][1] = board[i][0][4];
			board[i][0][4] = tmp[i];
		}
	}
}
void F(char Fa, char Fd) {
	char tmp[3];
	for (int i = 0; i < 3; i++)tmp[i] = board[2][i][0];
	if (Fd == '+') {
		st(3);
		for (int i = 0; i < 3; i++) {
			board[2][2 - i][0] = board[2][2 - i][4];
			board[2][2 - i][4] = board[0][i][5];
			board[0][i][5] = board[2][2 - i][2];
			board[2][2 - i][2] = tmp[2 - i];
		}
	}
	else {
		rev(3);
		for (int i = 0; i < 3; i++) {
			board[2][i][0] = board[2][i][2];
			board[2][i][2] = board[0][2 - i][5];
			board[0][2 - i][5] = board[2][i][4];
			board[2][i][4] = tmp[i];
		}
	}
}
void B(char Ba, char Bd) {
	char tmp[3];
	for (int i = 0; i < 3; i++)tmp[i] = board[2][i][5];
	if (Bd == '+') {
		st(1);
		for (int i = 0; i < 3; i++) {
			board[2][2 - i][5] = board[0][i][4];
			board[0][i][4] = board[0][i][0];
			board[0][i][0] = board[0][i][2];
			board[0][i][2] = tmp[2 - i];
		}
	}
	else {
		rev(1);
		for (int i = 0; i < 3; i++) {
			board[2][i][5] = board[0][2 - i][2];
			board[0][2 - i][2] = board[0][2 - i][0];
			board[0][2 - i][0] = board[0][2 - i][4];
			board[0][2 - i][4] = tmp[i];
		}
	}
}
void L(char La, char Ld) {
	char tmp[3];
	for (int i = 0; i < 3; i++)tmp[i] = board[i][0][1];
	if (Ld == '+') {
		st(4);
		for (int i = 0; i < 3; i++) {
			board[2 - i][0][1] = board[2 - i][0][5];
			board[2 - i][0][5] = board[2 - i][0][3];
			board[2 - i][0][3] = board[2 - i][0][0];
			board[2 - i][0][0] = tmp[2 - i];
		}
	}
	else {
		rev(4);
		for (int i = 0; i < 3; i++) {
			board[i][0][1] = board[i][0][0];
			board[i][0][0] = board[i][0][3];
			board[i][0][3] = board[i][0][5];
			board[i][0][5] = tmp[i];
		}
	}
}
void R(char Ra, char Rd) {
	char tmp[3];
	for (int i = 0; i < 3; i++)tmp[i] = board[2 - i][2][1];
	if (Rd == '+') {
		st(2);
		for (int i = 0; i < 3; i++) {
			board[i][2][1] = board[i][2][0];
			board[i][2][0] = board[i][2][3];
			board[i][2][3] = board[i][2][5];
			board[i][2][5] = tmp[2 - i];
		}
	}
	else {
		rev(2);
		for (int i = 0; i < 3; i++) {
			board[2 - i][2][1] = board[2 - i][2][5];
			board[2 - i][2][5] = board[2 - i][2][3];
			board[2 - i][2][3] = board[2 - i][2][0];
			board[2 - i][2][0] = tmp[i];
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	while (T--) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				board[i][j][0] = 'w';
				board[i][j][1] = 'o';
				board[i][j][2] = 'b';
				board[i][j][3] = 'r';
				board[i][j][4] = 'g';
				board[i][j][5] = 'y';
			}
		}
		cin >> n;
		while (n--) {
			cin >> as >> di;
			if (as == 'U')U(as, di);
			else if (as == 'D')D(as, di);
			else if (as == 'F')F(as, di);
			else if (as == 'B')B(as, di);
			else if (as == 'L')L(as, di);
			else R(as, di);
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << board[i][j][0];
			}
			cout << '\n';
		}
	}
	return 0;
}
