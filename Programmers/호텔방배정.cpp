#include <string>
#include <vector>
#include <map>
using namespace std;
map<long long, long long> m;

long long Find(long long temp_x){
    if(m[temp_x] == 0) return temp_x;
    m[temp_x] = Find(m[temp_x]);
    return m[temp_x];
}

vector<long long> solution(long long k, vector<long long> room_number) {
    vector<long long> answer;
    for(long long x : room_number){
        long long y = Find(x);
        answer.push_back(y);
        m[y] = y+1;
    }
    return answer;
}
