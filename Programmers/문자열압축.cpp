#include <string>
#include <vector>

using namespace std;

int solution(string s) {
	int answer = s.length();

	for (int i = 1; i <= s.length() / 2; i++) {
		int count = 1;
		string temp;
		string a, b;
		for (int j = 0; j<s.length(); j += i) {
			if (j + i + i > s.length()) {
				if (count != 1) temp += to_string(count) + s.substr(j);
				else temp += s.substr(j);
				break;
			}
			a = s.substr(j, i);
			b = s.substr(j + i, i);
			if (a == b)
				count++;
			else {
				if (count != 1) temp += to_string(count) + a;
				else temp += a;
				count = 1;
			}

		}
		answer = answer > temp.length() ? temp.length() : answer;
	}

	return answer;
}