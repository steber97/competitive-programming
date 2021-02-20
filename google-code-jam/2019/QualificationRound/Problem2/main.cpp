#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Very easy problem, we need to perform a Manhattan path without crossing a line drawn previously, which can only go south or east.
// To do so, as the grid is squared, if the line starts and end with different letters we perform a L path starting and ending with 
// inversed letters.
// Otherwise, we go in the opposite direction than the other line until we find a couple of letters with the same value, where we can cross.

// Solves both visible test cases.

int main(){

    int T;
    cin >> T;

    for (int t = 1; t<=T; t++){
        // For each test case:
        int len;
        cin >> len;
        string lydia;
        cin >> lydia;
        string result;
        if (lydia[0] != lydia[lydia.size()-1]){
            // base case, just perform a L shape path. We never cross lydia's path
            for (int i = 0; i<len-1; i++){
                result.push_back(lydia[lydia.size()-1]);
            }
            for (int i = 0; i<len-1; i++){
                result.push_back(lydia[0]);
            }
        }
        else{
            // It means that at some point we need to cross lydia's path. We do it where there are at least 2 characters with the same value (like EE) and we can cross there (with SS).
            int i = 1;
            int cross_position = 0;
            while(lydia[i] != lydia[i-1] || lydia[i] == lydia[0]){
                if (lydia[i] != lydia[0])
                    cross_position ++;
                i++;
            }
            // now i is the position where we can cross with a double letter.

            for (int j = 0; j<cross_position; j++){
                result.push_back( (lydia[0] == 'E' ? 'S' : 'E') );
            }
            for (int j = 0; j<len-1; j++){
                result.push_back(lydia[0]);
            }
            for (int j = cross_position; j<len-1; j++){
                result.push_back( (lydia[0] == 'E' ? 'S' : 'E') );
            }
        }

        cout << "Case #" << t << ": " << result << endl;
    }
    return 0;
}