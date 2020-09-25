#include <string>
#include <vector>

using namespace std;
bool check(int mid, vector<int> stones, int k){
    int count =0;
    for(int i=0; i<stones.size(); i++){
        if(stones[i]-mid <= 0)
            count++;
        else{
            count =0;
        }
        if(count == k)
            return false;
    }
    return true;
}
int solution(vector<int> stones, int k) {
    int lo = 1;
    int ho = 200000000;
    while(lo <= ho){
        int mid = (lo+ho)/2;
        if(check(mid,stones,k)){
            lo = mid+1;
        }
        else
            ho = mid-1;
    }
    return lo;
}
