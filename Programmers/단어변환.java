class Solution {
    
    boolean []visit = new boolean[50];
    int answer = 51;
    void DFS(String begin, String target, String[] words, int depth){
        if(begin.equals(target)){
            answer = answer > depth ? depth : answer;
            return;
        }
        for(int i=0; i<words.length; i++){
            if(!visit[i]){
                int diff = 0;
                for(int k=0; k<words[i].length(); k++){
                    if(begin.charAt(k) != words[i].charAt(k)){
                        diff++;
                    }
                    if(diff == 2) break;
                }
                if(diff == 1){
                    visit[i] = true;
                    //System.out.println(words[i]);
                    DFS(words[i], target, words, depth+1);
                    visit[i] = false;
                }
            }
        }
        
    }
    
    public int solution(String begin, String target, String[] words) {
        
        String a = "a";
        String b= "b";
        if(a.compareTo(b) > 0) System.out.println("a");
        else System.out.println("b");
        
        DFS(begin, target, words, 0);
        if(answer == 51) answer = 0;
        return answer;
    }
}
