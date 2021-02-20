#include <iostream>
#include <vector>

using namespace std;

int main(){

    int T;
    cin >> T;

    for (int t=1; t<=T; t++){
        int R,C,H,V;
        cin >> R >> C >> H >> V;
        vector<vector<char>> mat (R, vector<char>(C));
        int total_chocolate = 0;
        for (int i = 0; i<R; i++){
            for (int j = 0; j<C; j++){
                cin >> mat[i][j] ;
                if (mat[i][j] == '@')
                    total_chocolate ++;
            }
        }
        bool possible = true;
        if (total_chocolate % ((H+1) * (V+1)) != 0){
            possible = false;
        }
        
        if (possible){
            int choc_per_piece = total_chocolate / ((H+1)*(V+1));
            vector<int> vertical_cuts(V);
            int posw = 0;   // pos w in vertical rows.
            int counter = 0;
            for (int i = 0; i<C && possible; i++){
                for (int j =0; j<R; j++){
                    counter += (mat[j][i] == '@' ? 1 : 0);
                }
                if (counter > total_chocolate / (V+1)){
                    possible = false;
                }
                else if (counter == (total_chocolate / (V+1))){
                    if (posw < vertical_cuts.size())
                        vertical_cuts[posw] = i;
                    posw++;
                    counter = 0;
                    
                }
            }
            if (possible){
                // DEBUG PRINT
                /*
                for (int i = 0; i<vertical_cuts.size(); i++){
                    cout << vertical_cuts[i] << " ";
                }
                cout << endl;*/
                vector<int> counter_cell(V+1, 0);
                int posw2 = 0;
                for (int i = 0; i<R && possible; i++){
                    posw2 = 0;
                    for (int j = 0; j<C; j++){
                        counter_cell[posw2] += (mat[i][j] == '@' ? 1 : 0);
                        if (posw2<vertical_cuts.size() && j == vertical_cuts[posw2]){
                            posw2 ++;
                        }
                    }
                    /*
                    for (int j = 0; j<counter_cell.size(); j++){
                        cout << counter_cell[j] << " ";
                    }
                    cout << endl;*/
                    bool finito = true;
                    for (int j = 0; j<V+1 && possible && finito; j++){
                        if (counter_cell[j] > choc_per_piece){
                            possible = false;
                        }
                        if (counter_cell[j] < choc_per_piece){
                            //cout << "Not finished" << endl;
                            finito = false;
                        } 
                    }

                    if (finito && possible){
                        //cout << "OK" << endl;
                        for (int k = 0; k<counter_cell.size(); k++){
                            counter_cell[k] = 0;
                        }
                    }
                }
            }
        }

        

        cout << "Case #" << t << ": " << (possible? "POSSIBLE" : "IMPOSSIBLE") << endl;
    }
    return 0;
}