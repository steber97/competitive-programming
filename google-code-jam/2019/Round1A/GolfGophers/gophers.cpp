
#include <iostream>
#include <vector>

using namespace std;

vector<int> merge_vectors(vector<int>& v1, vector<int>& v_res){
    vector<int> res;
    int pos1 = 0; int pos2 = 0;

    if (v_res.size()==0){
        return v1;
    }

    while(pos1 < v1.size() && pos2 < v_res.size()){
        if (v1[pos1] == v_res[pos2]){
            res.push_back(v1[pos1]);
            pos1 ++;
            pos2 ++;
        }
        else if (v1[pos1] < v_res[pos2]){
            pos1++;
        }
        else{
            pos2 ++;
        }
    }
    
    
    return res;
}

void print_vector(vector<int>& v){
    cerr <<  "print vector " ;
    for (int i = 0; i<v.size(); i++){
        cerr << v[i] << " ";
    }
    cerr << endl;
    
}

int main(){

    int T, N, M;
    cin >> T >> N >> M;
    vector<int> primes = {18, 17, 13, 11, 7, 5, 3};
    for (int t =0; t<T; t++){
        bool finito = false;
        vector<int> v_res;
        //cerr << " " <<  t  << " " << flush;
        int round = 0; // Round
        while(!finito){
            if (round > 6){
                cerr << "tweak used " << endl;
                finito=true;
                print_vector(v_res);
                v_res.resize(1, v_res[0]);
                
            }
            
            else{

                cerr << v_res.size() << " ";
                for (int i=0; i<18; i++){
                    cout << primes[round] << ( i != 17 ? " " : "\n");
                    cout << flush;
                }
                vector<int> a (18);
                int total = 0;
                for (int i = 0; i<18; i++){
                    cin >> a[i];
                    total += a[i];
                }

                //cout << "read" << endl;
                vector<int> v1;
                //int j = (total % primes[round] == 0 ? int(total / primes[round]) : int(total / primes[round]) + 1 );
                int j = 0;
                while(M >= total + j * primes[round]){
                    
                    v1.push_back(total + j * primes[round]);
                    j++;
                }

                // now merge with v_res
                
                v_res = merge_vectors(v1, v_res);

                //print_vector(v_res);

                
            }

            if (v_res.size() == 1){
                cout << v_res[0] << endl;
                cout << flush;
                finito = true;  
            }
            else if (v_res.size() == 0){
                cout << 0 << endl << flush;
            }

            else{
                round++;
            }
        }
        // We need to read the response from the server
        int response;
        cin >> response;
        if (response == -1){
            exit(0);
        }
        else{
            // Do nothing
        }
    }
    return 0;
}