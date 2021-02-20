#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(){

    // USE unsigned long long
    int T;
    cin >> T;
    for (int t = 1; t<=T; t++){
        int B,R,C;
        cin >> R >> B >> C;
        vector<tuple<unsigned long long,unsigned long long,unsigned long long>> cashiers(C);
        for (int i = 0; i<C; i++){
            int M,S,P;
            cin >> M >> S >> P;
            cashiers[i] = {M,S,P};
        }

        unsigned long long max_temp = 1000000000000000000 + 1000000005;

        // perform binary search of the answer.
        bool finish = false;
        unsigned long long current_time = max_temp / 2;
        unsigned long long min_val = 0;
        unsigned long long max_val = max_temp;
        while(min_val < max_val){
            // Try to satisfy all bits using current time seconds.
            vector<unsigned long long> cashiers_bits;
            unsigned long long number_of_bits_satisfied = 0;
            /*
            if (current_time < 20){
                cout << min_val << " " << current_time << " " << max_val << endl;
            }*/
            for (int i = 0; i<C; i++){
                long long bits_per_cashier ;
                if (current_time > get<2>(cashiers[i])){
                    bits_per_cashier = min(get<0>(cashiers[i]), ( (current_time - get<2>(cashiers[i])) / get<1>(cashiers[i])));
                }
                else{
                    bits_per_cashier = 0UL;
                }
                /*
                if (current_time < 20)
                    cout << bits_per_cashier << "\t";*/
                cashiers_bits.push_back(bits_per_cashier);
            }

            // Take only first R bits
            sort(cashiers_bits.begin(), cashiers_bits.end());
            for (int i = 0; i<R; i++){
                number_of_bits_satisfied += cashiers_bits[cashiers_bits.size()-1 - i];
            }
            /*
            if (current_time < 20)
                cout << endl;*/

            if (number_of_bits_satisfied >= B){
                max_val = current_time;
            }
            else{
                min_val = current_time + 1UL;
            }

            current_time = (unsigned long long) ((min_val + max_val) / 2);
        }

        cout << "Case #" << t << ": " << min_val << endl;
    }

    return 0;
}