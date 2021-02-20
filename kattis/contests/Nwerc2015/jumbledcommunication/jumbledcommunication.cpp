#include <iostream>
#include <bitset>

using namespace std;

int main(){

    int N;
    cin >> N;

    for (int i = 0; i<N; i++){
        
        int n;
        cin >> n;
        bitset<8> b (n);
        //cout << b << endl;

        bitset<8> result;
        //cout << result << endl;
        int last = 0;
        for (int i = 0; i<8; i++){
            
            result[i] = b[i] ^ last;
            last = result[i];
            //cout << result << endl;
        }
        //cout << endl;
        cout << result.to_ullong() << " ";
    }
    return 0;
}