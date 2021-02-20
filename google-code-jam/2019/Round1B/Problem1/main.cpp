#include <iostream>
#include <vector>
#include <string>

using namespace std;
int LSOne(int b){
    return b & (-b);
}

class FenwickTree{
    private:
        vector<int> ft;
    public:
        FenwickTree(int n){
            ft.assign(n+1, 0);
        }

        int rsq(int b){
            int sum = 0;
            for (; b; b -= LSOne(b)){
                sum += ft[b];
            }
            return sum;
        }

        int rsq(int a, int b){
            if (a == 1)
                return rsq(b);
            return rsq(b) - rsq(a-1);
        }
        void adjust (int k, int v){
            for (; k<int(ft.size()); k += LSOne(k)){
                ft[k] += v;
            }
        }
        void print_fenwick_tree(){
            for (int i = 0; i<ft.size(); i++)
                cout << ft[i] << " ";
            cout << endl;
        }
};


int main(){

    int T;
    cin >> T;
    for (int t = 1; t<=T; t++){
        int N, Q;
        cin >> N >> Q;
        vector<vector<int>> mat(Q+1, vector<int>(Q+1, 0));
 /*
        FenwickTree ns_ft(Q);
        FenwickTree ew_ft(Q);
*/
        for (int i = 0; i<N; i++){
            int posx, posy;
            char orient;
            cin >> posx >> posy >> orient;
            
            if (orient == 'N'){
                for (int i =posy+1; i<=Q; i++){
                    for (int j = 0; j<=Q; j++){
                        mat[i][j] ++;
                    }
                }
            }

            if (orient == 'S'){
                for (int i = 0; i<posy; i++){
                    for (int j = 0; j<=Q; j++){
                        mat[i][j] ++;
                    }
                }
            }

            if (orient=='E'){
                for (int i =posx+1; i<=Q; i++){
                    for (int j = 0; j<=Q; j++){
                        mat[j][i] ++;
                    }
                }
            }

            if (orient == 'W'){
                for (int i =0; i<posx; i++){
                    for (int j = 0; j<=Q; j++){
                        mat[j][i] ++;
                    }
                }
            }
            
        }

        int posx_max = 0;
        int max_val = 0;
        int posy_max = 0;
        for (int i = 0; i<=Q; i++){
            for (int j = 0; j<=Q; j++){
                if (mat[i][j] > max_val){
                    max_val = mat[i][j];
                    posy_max = i;
                    posx_max = j;
                }
                else if (mat[i][j] == max_val && j < posx_max){
                    posx_max = j;
                    posy_max = i;
                }
                else if (mat[i][j] == max_val && j == posx_max && i < posy_max){
                    posy_max = i;
                }
            }
        }

        cout << "Case #"<< t << ": " << posx_max << " " << posy_max << endl;
    }
    return 0;
}