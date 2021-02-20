
#include <iostream>
#include <vector>

using namespace std;

int main(){

    int T;
    cin >> T;
    cerr << T;
    for (int t = 1; t<=T; t++){
        int n,b,f;
        cin >> n >> b >> f;
        
        bool finito = false;
        // Accepts 3 values, 1 means found the error, -1 means found one which is actually working, 0 means undecided.
        vector<int> workers_state(n, 0);
        vector<int> result;

        // 1 giro: dividi in gruppi da 16.
        int dist = 32;

        while(!finito){
            dist /= 2;
            int pos = 0;
            vector<int> guess(n);
            vector<int> distance_expected;
            int write = 1;  // Switches among 1 and 0
            int count = 0;
            while(pos < n){
                distance_expected.push_back(0);
                for (int i = 0; i<dist && pos < n; i++){
                    guess[pos] = write;
                    pos ++;
                    distance_expected[count] ++;
                }
                //cout << distance_expected[count] << endl;
                write = write == 1 ? 0 : 1;
                count ++;
            }

            for (int i = 0; i<guess.size();i++){
                cout << guess[i];
            }
            cout << endl;
            cout.flush();

            // Accepts first response
            string response;
            cin >> response;

            vector<int> prediction(count, 0);
            count = 0;
            pos = 0;
            int pos2 = 0;
            write = 1;
            while(pos2 < n-b){
                int num = 0;
                for (int i = 0; i<distance_expected[count] && int(response[pos2]-'0') == write; i++){
                    pos2 ++;
                    num ++;
                }
                if (num == 0){
                    for (int i = 0; i<distance_expected[count]; i++){
                        result.push_back(pos + i);
                        if (result.size() == b){
                            finito = true;
                        }
                    }
                }
                pos += distance_expected[count];
                write = write == 1 ? 0 : 1;
                prediction[count] = num;
                //cout << prediction[count] << endl;
                count++;
            }

            //finito = true;
        }

        for (int i = 0; i<result.size(); i++){
            cout << result[i] << (i != result.size()-1?" ":"");
        }
        cout << endl;
        cout.flush();
        // Create 2nd vector:

        int response_from_server ;
        cin >> response_from_server;
        if (response_from_server != 1)
            exit(1);
        
    }
    exit(0);
    return 0;
}