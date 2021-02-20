#include <vector>
#include <iostream>

using namespace std;

int main(){

    int T;
    cin >> T;

    for (int t = 1; t<=T; t++){
        int n;
        cin >> n;
        vector<bool> lollipop_sold(n, false);
        vector<int> counter_lollipop_passed(n, 0);

        for (int i = 0; i<n; i++){
            int d;
            cin >> d;
            vector<int> lollipops(d);
            for (int j = 0; j<d; j++){
                cin >> lollipops[j];
                counter_lollipop_passed[lollipops[j]]++;
            }
            int chosen_lollipop = -1;

            for (int j = 0; j<d; j++){
                if (!lollipop_sold[lollipops[j]]){
                    if (chosen_lollipop == -1 || counter_lollipop_passed[chosen_lollipop] > counter_lollipop_passed[lollipops[j]]){
                        chosen_lollipop = lollipops[j];
                    }
                }
            }
            if (chosen_lollipop != -1){
                lollipop_sold[chosen_lollipop] = true;
            }
                
            cout << chosen_lollipop << endl << flush ;
        }
    }

    return 0;
}