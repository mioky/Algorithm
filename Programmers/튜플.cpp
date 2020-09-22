#include <string>
#include <vector>
#include <algorithm>
#define MAX 100001

using namespace std;
bool com(vector<int>a, vector<int>b){
    return a.size() < b.size();
}
vector<int> solution(string s) {
    vector<int> answer;
    vector<vector<int> >temp;
    
    for(int i=0; i<s.length(); i++){
        vector<int> temp_num;
        int a = 0;
        if(s[i] >= '0' && s[i] <= '9'){
            while(true){
                if(s[i] == '}'){
                    temp_num.push_back(a);
                    break;
                }
                else if(s[i] == ','){
                    temp_num.push_back(a);
                    a=0;
                }
                else{ //숫자면
                    a *= 10;
                    a += s[i] - '0';
                }
                i++;
            }
            temp.push_back(temp_num);
        }
    }
    bool visit[MAX] = {false};
    sort(temp.begin(), temp.end(), com);
    for(int i=0; i<temp.size(); i++){
        for(int j=0; j<temp[i].size(); j++){
            if(!visit[temp[i][j]]){
                visit[temp[i][j]] = true;
                answer.push_back(temp[i][j]);
            }
        }
    }
    return answer;
}
