
#include <iostream>
#include <cstring>

using namespace std;

// Problem 1 for Google Code Jam, must print 2 very long numbers (10^100) such that their sum equals N and they haven't any 4 digit.
// Passes both test cases (not hidden), but unsure about the very long test case (which actually scores only one point).

pair<char,char> return_pair_of_chars(int num){
    switch (num){
        case 0:
            return {'0','0'};
        case 1:
            return {'1','0'};
        case 2:
            return {'1','1'};
        case 3:
            return {'2','1'};
        case 4:
            return {'3','1'};
        case 5:
            return {'3','2'};
        case 6:
            return {'3','3'};
        case 7:
            return {'5','2'};
        case 8:
            return {'5','3'};
        case 9:
            return {'6','3'};
    }
}


int main(){

    int T;
    cin >> T;

    for (int t = 1; t<=T; t++){
        string A,B;

        string N;
        cin >> N;

        for (int i = 0; i<N.size(); i++){
            int val = N[i] - '0';
            pair<char,char> p = return_pair_of_chars(val);
            if (A.size() != 0 || p.first != '0')
                A.push_back(p.first);
            if (B.size() != 0 || p.second != '0')
                B.push_back(p.second);
            
        }

        cout << "Case #" << t <<": " << A << " " << B << endl;
    }

    return 0;
}