import java.util.Arrays;
import java.util.Vector;
class Solution {
    boolean[] visit = new boolean[10000];
    Vector<String> v = new Vector<String>();
    boolean check = false;
    
    void DFS(String[][] tickets, int depth, String start){
        if(check) return;
        if(depth == tickets.length){
            check = true;
            return;
        }
        
        for(int i=0; i<tickets.length; i++){
            if(!visit[i] && tickets[i][0].equals(start)){
                System.out.println(tickets[i][0]);
                visit[i] = true;
                v.add(tickets[i][1]);
                
                DFS(tickets, depth+1, tickets[i][1]);
                if(check) return;
                visit[i] = false;
                int temp = v.size();
                v.remove(temp-1);
            }
        }
    }
    
    public String[] solution(String[][] tickets) {
        String[] answer = {};
        answer = new String[tickets.length+1];
        String[] temp = {};
        for(int i=0; i<tickets.length; i++){
            for(int j=0; j<tickets.length-1; j++){
                if(tickets[j][1].compareTo(tickets[j+1][1]) > 0){
                    temp = tickets[j];
                    tickets[j] = tickets[j+1];
                    tickets[j+1] = temp;
                }
            }
        }
        v.add("ICN");
        //sort(tickets.begin(), tickets.end());
        DFS(tickets, 0, "ICN");
        for(int i=0; i<v.size(); i++){
            answer[i] = v.get(i);// = v.get(i);
        }
        return answer;
    }
}
