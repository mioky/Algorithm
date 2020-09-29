/* 2020.09.29
*
* BOJ 13458
* Completed!
*
* long long 사용할 줄 알아야됨! 입출력 %lld  
* int의 최대값은 2147483647 로 약 20억
* 감독관의 총 수는 백만 * 백만 이 되어 1조 (정수 범위 초과)
* long long의 최대값은 9백경
*
* 1. 벡터로 했을 때
* Memory : 7328 KB
* Time   : 160 ms
* 
* 2. 배열로 했을 때
* Memory : 4900KB
* Time : 172 ms
*/

#include <cstdio>
#include <vector>

using namespace std;

int main() {

	int N, B, C;
	long long num = 0;
	long long Total = 0;
	vector<int>arr;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		arr.push_back(num);
	}

	scanf("%d %d", &B, &C);

	for (int i = 0; i < N; i++) {
		arr[i] -= B;
		Total++; //총감독관
		if (arr[i] <= 0) continue;
		if (arr[i] <= C) {
			Total++;
			continue;
		}
		Total += arr[i] / C;
		if (arr[i] % C > 0) Total++;
	}
	printf("%lld\n", Total);

	return 0;
}
/*

#include <cstdio>

using namespace std;

int main() {

	int N, B, C;
	long long Total = 0;
	int arr[1000000];

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}

	scanf("%d %d", &B, &C);

	for (int i = 0; i < N; i++) {
		arr[i] -= B;
		Total++; //총감독관
		if (arr[i] <= 0) continue;
		if (arr[i] <= C) {
			Total++;
			continue;
		}
		Total += arr[i] / C;
		if (arr[i] % C > 0) Total++;
	}
	printf("%lld\n", Total);

	return 0;
}*/
