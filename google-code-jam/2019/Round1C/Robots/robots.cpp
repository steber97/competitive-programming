#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

string recursive_win(vector<bool> & won, const vector<string>& robots, int posr){
    bool R,S,P;
    R = S = P = false;
    // Base case, we have finished
    bool finished = true;
    for (bool w: won){
        if (!w){
            finished = false;
            break;
        }
    }

    if (finished){
        return "";
    }

    vector<int> R_vect, S_vect, P_vect;
    for (int i = 0; i<robots.size(); i++){
        if (!won[i]){
            if (robots[i][posr % robots[i].size()] == 'R'){
                R = true;
                R_vect.push_back(i);
            }
            else if (robots[i][posr % robots[i].size()] == 'S'){
                S = true;
                S_vect.push_back(i);
            }
            else{
                P = true;
                P_vect.push_back(i);
            }
        }
    }
    
    if (R && S && P){
        return "IMPOSSIBLE";
    }
    else{
        string res;
        if (R && !S && !P){
            res = "P";
            for (int i = 0; i<R_vect.size(); i++){
                won[R_vect[i]]= true;
            }
            string res_temp = recursive_win(won, robots, posr+1);
            if (res_temp.compare("IMPOSSIBLE") == 0)
                return "IMPOSSIBLE";
            return res + res_temp;
        }
        else if (!R && S && !P){
            res = "R";
            for (int i = 0; i<S_vect.size(); i++){
                won[S_vect[i]]= true;
            }
            string res_temp = recursive_win(won, robots, posr+1);
            if (res_temp.compare("IMPOSSIBLE") == 0)
                return "IMPOSSIBLE";
            return res + res_temp;
        }
        else if  (!R && !S && P){
            res = "S";
            for (int i = 0; i<P_vect.size(); i++){
                won[P_vect[i]]= true;
            }
            string res_temp = recursive_win(won, robots, posr+1);
            if (res_temp.compare("IMPOSSIBLE") == 0)
                return "IMPOSSIBLE";
            return res + res_temp;
        }

        else if (R && S && !P){
            res = "R";
            for (int i = 0; i<S_vect.size(); i++){
                won[S_vect[i]] = true;
            }
            string res_temp = recursive_win(won, robots, posr+1);
            if (res_temp.compare("IMPOSSIBLE") == 0)
                return "IMPOSSIBLE";
            return res + res_temp;
        }else if (!R && S && P){
            res = "S";
            for (int i = 0; i<P_vect.size(); i++){
                won[P_vect[i]] = true;
            }
            string res_temp = recursive_win(won, robots, posr+1);
            if (res_temp.compare("IMPOSSIBLE") == 0)
                return "IMPOSSIBLE";
            return res + res_temp;
        }else if (R && !S && P){
            res = "P";
            for (int i = 0; i<R_vect.size(); i++){
                won[R_vect[i]] = true;
            }
            string res_temp = recursive_win(won, robots, posr+1);
            if (res_temp.compare("IMPOSSIBLE") == 0)
                return "IMPOSSIBLE";
            return res + res_temp;
        }


    }

}

int main(){
    int T;
    cin >> T;
    for (int t = 1; t<=T; t++){
        string result = "";
        int N;
        cin >> N;
        vector<string> robots(N);
        for (int i = 0; i<N; i++){
            cin >> robots[i];
        }
        vector<bool> won(N, false);

        result = recursive_win(won, robots, 0);
        
        cout << "Case #" << t << ": " << result << endl;
    }
    return 0;
}