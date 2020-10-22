import java.util.Queue;
import java.util.LinkedList;

class Solution {
    public int solution(int n, int[][] computers) {
        int answer = 0;
        boolean []visit = new boolean[200];
        
        for(int i=0; i<n; i++){
            if(!visit[i]){
                Queue<Integer> q = new LinkedList<>();  
                q.offer(i);
                visit[i] = true;
                answer++;
                while(q.size() != 0){
                    int temp = q.poll();
                   // q.pop();
                    for(int j=0; j<n; j++){
                        if(!visit[j] && computers[temp][j] == 1){
                            q.offer(j);
                            visit[j] = true;
                        }
                    }
                }
            }
            
        }
        return answer;
    }
}
