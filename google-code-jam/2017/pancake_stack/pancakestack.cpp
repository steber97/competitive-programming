//
// Created by stefano on 03/05/18.
//


#include <fstream>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

ifstream in ("input");
ofstream out("output");

struct Pancake{
    long int radius;
    long int height;
};

bool compare_pancake_radius(Pancake a, Pancake b){
    return a.radius < b.radius;
}

int main(){

    int T;
    in >> T;
    out << fixed;
    out.precision(8);

    // TODO: can be implemented with just 2 arrays.

    for (int q = 1; q <= T; q++){
        int N, K;
        in >> N >> K;

        Pancake pancakes[N];

        for (int i = 0; i < N; i++){
            in >> pancakes[i].radius >> pancakes[i].height;
        }
        // sort the pancakes in order of ascending radius.
        sort(pancakes, pancakes + N, compare_pancake_radius);

        long int mem [K][N];

        for (int i = K-1; i >= 0; i--){
            long int max = 0;
            for (int j = K - 1 - i; j < N - i; j++){
                //out << "radius: " << pancakes[j].radius << endl;
                //out << "height: " << pancakes[j].height << endl;
                long int val;
                if (i == K-1){
                    // first cycle, it doesn't have to look at the previous line.
                    val = 2 * (pancakes[j].radius * pancakes[j].height);
                    if (i == 0){
                        val += pancakes[j].radius * pancakes[j].radius;
                    }

                }
                else if (i == 0){
                    // It needs to add to val even the horizontal area.
                    val = 2 * pancakes[j].radius * pancakes[j].height +
                            mem[i+1][j-1] +
                            (pancakes[j].radius * pancakes[j].radius);
                }
                else {
                    // Only needs to add to the vertical area the previous value found.
                    val = 2 * (pancakes[j].radius * pancakes[j].height) +
                            (mem[i+1][j-1]);
                }
                //out << val << endl;
                if (val > max){
                    max = val;
                }
                mem[i][j] = max;

                //out << mem[i][j] << endl;
            }
        }

        out << "Case #" << q << ": " <<  (double)mem[0][N-1] * M_PI << endl;

    }

    return 0;
}