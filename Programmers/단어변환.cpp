#include <string>
#include <vector>

using namespace std;
int answer = 51;
bool visit[50];

void DFS(string begin, string target, vector<string> words, int depth) {

	if (begin == target) {
		answer = answer > depth ? depth : answer;
		return;
	}
	for (int i = 0; i<words.size(); i++) {
		int count = 0;
		if (!visit[i]) {
			for (int j = 0; j<words[i].length(); j++) {
				if (begin[j] != words[i][j]) {
					count++;
					if (count == 2) break;
				}
			}
			if (count != 2) {
				visit[i] = true;
				DFS(words[i], target, words, depth + 1);
				visit[i] = false;
			}
		}
	}
}

int solution(string begin, string target, vector<string> words) {

	DFS(begin, target, words, 0);

	if (answer == 51) answer = 0;
	return answer;
} 
