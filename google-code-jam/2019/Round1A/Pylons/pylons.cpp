
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int main(){
    
    int T;
    cin >> T;
    for (int t = 1; t<=T; t++){
        int n, m;
        bool possible = true;
        cin >> n >> m;
        int h = max(n,m);  // This will be at least 4
        int l = min(n,m);
        
        vector<pair<int,int>> res;
        if (n <= 3 && m <=3){
            possible = false;
        }
        if (h == 4 && l == 2){
            possible = false;
        }
        if (possible){
            
            bool reverse = false;
            if (n < m){
                reverse = true;
            }
            int last_y = 0;
            vector<bool> start_from_here(h+1, false);
            vector<bool> finish_here(h+1, false);
            for (int i = 1; i<=h; i++){
                // start from i.
                if (l == 2){

                    int coord_y = i;
                    int pos_max, pos_min;
                    if (h % 2 == 0){
                        if (coord_y <= h/2){
                            pos_min = coord_y;
                            pos_max = coord_y + h/2;
                        }
                        else{
                            pos_min = coord_y - h/2;
                            pos_max = coord_y;
                        }
                    }
                    else{
                        if (coord_y <= h/2){
                            pos_min = coord_y;
                            pos_max = coord_y + h/2 + 1;
                        }
                        else{
                            pos_max = coord_y;
                            pos_min = coord_y - (h/2);
                        }
                    }
                    for (int j = 1; j<=l; j++){
                        if (reverse){
                            res.push_back({j, coord_y});
                        }
                        else{
                            res.push_back({coord_y, j});
                        }
                        
                        coord_y = (coord_y == pos_min ? pos_max : pos_min);
                        
                    }
                }
                else{
                    int coord_y = last_y + 1;    
                    if (coord_y > h || start_from_here[coord_y]){
                        bool found = false;
                        for (int k = 1; k<=h; k++){
                            if (!start_from_here[k] && k - 1 != h - l && k+1!= h+l){
                                coord_y = k;
                                found = true;
                                break;
                            }
                        }
                        if (found == false){

                            cout << coord_y << endl;
                            cout << n << " " << m << endl;

                            for (int i = 0; i<res.size(); i++){
                                cout << res[i].first << " " << res[i].second << endl;
                            }
                            exit(1);
                        }
                    }
                    start_from_here[coord_y] = true;
                    int pos_max, pos_min;
                    if (h % 2 == 0){
                        if (coord_y <= h/2){
                            pos_min = coord_y;
                            pos_max = coord_y + h/2;
                        }
                        else{
                            pos_min = coord_y - h/2;
                            pos_max = coord_y;
                        }
                    }
                    else{
                        if (coord_y <= h/2){
                            pos_min = coord_y;
                            pos_max = coord_y + h/2 + 1;
                        }
                        else{
                            pos_max = coord_y;
                            pos_min = coord_y - (h/2);
                        }
                    }
                    for (int j = 1; j<=l; j++){
                        if (reverse){
                            res.push_back({j, coord_y});
                        }
                        else{
                            res.push_back({coord_y, j});
                        }
                        if (j != l)    
                            coord_y = (coord_y == pos_min ? pos_max : pos_min);
                    }
                    finish_here[coord_y] = true;
                    last_y = coord_y;

                }
            }


        }
        
        cout << "Case #" << t << ": " << (possible ? "POSSIBLE" : "IMPOSSIBLE") << endl;
        if (possible){

            for (int i = 0; i<res.size(); i++){
                cout << res[i].first << " " << res[i].second << endl;
            }
        }
    }
    return 0;
}