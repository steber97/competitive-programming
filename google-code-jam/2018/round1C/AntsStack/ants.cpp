
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(){

    int T;
    cin >> T;
    for (int t = 1; t<=T; t++){
        int N;
        cin >> N;
        vector<long long> ants(N);
        map<long long,int> weights;
        for (int i = 0; i<N; i++){
            cin >> ants[i];
        }

        int res = 0;
        for (int i = 0; i<N; i++){
            map<long long, int>::iterator myit = weights.lower_bound(6L * ants[i]);
            long long plus_weight;
            int height_reached;
            if (weights.size() == 0){
                plus_weight = 0L;
                height_reached = 0;
            }
            else if (myit == weights.end()){
                myit--;
                plus_weight = myit->first;
                height_reached = myit->second;
            }
            else if (myit == weights.begin() && myit->first > 6L*ants[i]){
                plus_weight = 0L;
                height_reached = 0;
            }
            else {
                if (myit->first > 6L * ants[i])
                    myit --;
                plus_weight = myit->first;
                height_reached = myit->second;
            }

            
            res = max(
                res,
                height_reached + 1
            );
            
            //cout << myit->first << " " << myit->second << " " << res << " " << endl;
            
            weights[plus_weight + ants[i]] = res;
        }
        cout << "Case #" << t << ": " << res << endl;

    }
    return 0;
}

