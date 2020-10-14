/* 2020.10.13 ~ 10.14
*
* BOJ 17825
* Completed!
*
* 방향은 다르지만 중복되는 숫자들이 있었기 때문에 이 부분 예외처리에서 시간 많이 걸림
* 마지막 40에서는 blue가 달라도 값이 같으면 continue
* 백트래킹!
*
*
* Memory : 1112 KB
* Time   : 12 ms
*/
#include <cstdio>

struct info {
	int score; //현재 위치
	int blue; //몇 번째 파란색 칸
};

int num[10];
info horse[4];
int ans = 0;
info step[10];

int move(int depth, int idx) {

	int temp_num = num[depth];
	if (horse[idx].blue == 0) {
		horse[idx].score += (temp_num * 2);
		if (horse[idx].score == 10) horse[idx].blue = 10;
		else if (horse[idx].score == 20) horse[idx].blue = 20;
		else if (horse[idx].score == 30) horse[idx].blue = 30;
		else if (horse[idx].score > 40) return 0;
		return horse[idx].score;
	}
	if (horse[idx].blue == 10) {
		for (int i = 1; i <= temp_num; i++) {
			horse[idx].score += 3;
			if (horse[idx].score == 22) {
				horse[idx].score = 25;
				temp_num -= i; //남은 이동 횟수
				horse[idx].blue = 25;
				break;
			}
		}
	}
	else if (horse[idx].blue == 20) {
		for (int i = 1; i <= temp_num; i++) {
			horse[idx].score += 2;
			if (horse[idx].score == 26) {
				horse[idx].score = 25;
				temp_num -= i;
				horse[idx].blue = 25;
				break;
			}
		}
	}
	else if (horse[idx].blue == 30) {
		if (horse[idx].score == 30) {
			horse[idx].score = 28;
			temp_num--;
		}
		for (int i = 1; i <= temp_num; i++) {
			horse[idx].score -= 1;
			if (horse[idx].score == 25) {
				temp_num -= i;
				horse[idx].blue = 25;
				break;
			}
		}
	}
	if (horse[idx].blue == 25) {
		horse[idx].score += (temp_num * 5);
		if (horse[idx].score > 40) {
			return 0;
		}
	}
	return horse[idx].score;
}

void DFS(int depth, int sum) {

	if (depth == 10) {
		if (ans < sum) ans = sum; //최댓값
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (horse[i].score <= 40) { //도착지점에 안갔고, 이동한 위치에 말이 없다면
			int temp = horse[i].score;
			step[depth].blue = horse[i].blue;
			step[depth].score = temp;
			int temp_score = move(depth,i);
			
			bool flag = false;
			for (int j = 0; j < 4; j++) { //이동한 위치에 말이 존재한다면
				if (i != j && horse[i].score < 40 && horse[j].blue == horse[i].blue && horse[j].score == horse[i].score) {
					horse[i].score = temp;
					horse[i].blue = step[depth].blue;
					flag = true;
					break;
				}
				if (i != j &&horse[i].score == 40 && horse[j].score == horse[i].score) {
					horse[i].score = temp;
					horse[i].blue = step[depth].blue;
					flag = true;
					break;
				}
			}
			if (flag) continue;
			DFS(depth + 1, sum + temp_score);
			horse[i].score = step[depth].score;
			horse[i].blue = step[depth].blue;
			//백트래킹 -> 점수랑 플래그 되돌려야 함..
			
		}
	}
}

int main() {

	for (int i = 0; i < 10; i++)
		scanf("%d", &num[i]);
	
	DFS(0,0);
	printf("%d\n", ans);
	return 0;
}
