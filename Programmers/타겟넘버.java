class Solution {
    int answer = 0;
    boolean[] visit = new boolean[20];
    public void DFS(int[] numbers, int target, int depth, int sum){
        
        if(depth == numbers.length){
            if(sum == target) answer++;
            return;
        }
        
        DFS(numbers, target, depth+1, sum+numbers[depth]);
        DFS(numbers, target, depth+1, sum-numbers[depth]);

    }
    
    public int solution(int[] numbers, int target) {
        
        DFS(numbers,target, 0,0);
        visit[0] = true;
        for(int i=0; i<20; i++){
            System.out.println(visit[i]);
        }
        return answer;
    }
}
