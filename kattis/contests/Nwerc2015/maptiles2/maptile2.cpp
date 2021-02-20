#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){

    string N;
    cin >> N;

    int res1 = N.size();

    cout << res1 << " ";

    long long num_cells = pow(4, res1);

    long long posy_min = 0;
    long long posy_max = pow(2, res1)-1;

    long long posx_min = 0;
    long long posx_max = pow(2, res1)-1;

    for (int i = 0; i<res1; i++){
        char c = N[i];

        if (c == '1'){
            // top right
            posx_min = ((posx_min + posx_max) / 2) + 1;
            posy_max = (posy_max + posy_min) / 2 ;
        }
        else if (c == '2'){
            // bottom left
            posx_max = ((posx_max + posx_min) / 2);
            posy_min = ((posy_max + posy_min) / 2) + 1;
        }
        else if (c == '3'){
            // bottom right
            posx_min = ((posx_max + posx_min) / 2) + 1;
            posy_min = ((posy_max + posy_min) / 2) + 1;
        }
        else if (c == '0'){
            // top left
            posx_max = ((posx_max + posx_min) / 2);
            posy_max = ((posy_max + posy_min) / 2);
        }

    }

    cout << posx_min << " " << posy_min << endl;

    return 0;
}