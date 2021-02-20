#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

int main(){

    int test_cases;
    cin >> test_cases;
    for (int i = 0; i<test_cases; i++){
        int a;
        cin >> a;
        const int start_from = 10;
        const int x_value = 10;
        vector<bool> vect0 = false;
        vector<bool> vect1 = false;
        vector<bool> vect2 = false;
        bool vinto = false;
        for (int j = 1; j< ceil(double (a)/3) -1 && !vinto; j++ ) {
            
            bool cond = vector0[0] && vector0[1] && vector0[2];
            while (!cond && !vinto){
                cout << x_value << start_from + j << flush;
                cin >> x >> y;
                if (x == 0 && y == 0){
                    vinto = true;
                }
                else if (y == start_from + j -1){
                    vector0[x-x_value + 1] = true;
                    while (vector0[0] && vector0[1] && vector0[2]){
                        for (int k = 0; k<3; k++){
                            vector0[k] = vector1[k];
                            vector1[k] = vector2[k];
                            vector2[k] = false;
                        }
                    }
                    cond = true;
                }
                else if (y == start_from + j){
                    vector1[x-x_value + 1] = true;
                }
                else if (y == start_from +j + 1){
                    vector2[x-x_value + 1] = true;
                }
            }
        }
    }
    return 0;
}