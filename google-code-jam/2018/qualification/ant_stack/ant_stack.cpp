#include <iostream>
//#include <fstream>
#include <vector>
#include <math.h>
using namespace std;

/*
ifstream cin ("input");
ofstream cout ("output");
*/
int main (){

    int T;
    cin >> T;

    for(int q = 1; q <= T; q++){
        int res = 0;

        int num_ant;
        int max_weight = 0;
        vector<int> ants;
        cin >> num_ant;
        for (int i = 0; i < num_ant; i++){
            int temp_ant;
            cin >> temp_ant;
            ants.push_back(temp_ant);
            if (max_weight < ants[i]){
                max_weight = ants[i];
            }
        }

        max_weight *= 6;

        //cout << max_weight << endl;

        int * mem1 = new int[max_weight+1];
        int * mem2;

        // Set mem1 for the first line.
        for (int i = 0; i<=max_weight; i++){
            mem1[i] = (ants[num_ant-1]*6 >= i)? 1 : 0;
        }
        /*
        for (int i = 0; i<max_weight+1; i++){
            cout << mem1[i] << "\t" ;
        }
        cout << endl;
        */

        for (int i = num_ant-2; i>=0; i--){
            mem2 = new int[max_weight+1];
            for (int j = 0; j<= max_weight; j++){
                int res1 = mem1[j];
                int res2 = 0;
                if (j <= ants[i]*6){
                    if (j + ants[i] <= max_weight){
                        res2 = 1 + mem1[j + ants[i]];
                    }
                    else {
                        res2 = 0;
                    }
                }
                mem2[j] = max(res1, res2);
            }
            /*
            for (int i = 0; i<max_weight+1; i++){
                cout << mem2[i] << "\t" ;
            }
            cout << endl; */
            delete(mem1);
            mem1 = mem2;
        }

        res = mem1[0];



        cout << "Case #" << q << ": " << res << endl;
    }

    return 0;
}