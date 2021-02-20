#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){

    int T;
    cin >> T;
    for (int t = 1; t<=T; t++){

        int N, P;
        cin >> N >> P;
        vector<pair<int,int>> dimensions(N);
        int total_to_cover = double(P);
        double max_covered_with_diagonals = 0.0d;
        for (int i = 0;i<N; i++){
            cin >> dimensions[i].first >> dimensions[i].second;
            total_to_cover -= ( dimensions[i].first + dimensions[i].second ) * 2;
            max_covered_with_diagonals += 2 * (sqrt(dimensions[i].first * dimensions[i].first + dimensions[i].second * dimensions[i].second));
        }

        // max covered with diagonals is at most 70k, so it is small enough to perform knapsack
        // Now we do knapsack on total_to_cover, where weights are cutting by the short side, and values are cutting on the diagonal.

        double res;
        if (max_covered_with_diagonals < total_to_cover){
            res = double(P) - (double(total_to_cover) - max_covered_with_diagonals);
        }
        else{
            // perform knapsack

            res = 0;
            vector<vector<double>> DP(N, vector<double>(total_to_cover+1, 0.0d));

            for (int i = N-1; i>=0; i--){
                for(int j = 0; j<=total_to_cover; j++){
                    // base case:
                    if (i == N-1){
                        if (j < 2*min(dimensions[i].first, dimensions[i].second)){
                            DP[i][j] = 0.0d;
                        }
                        else{
                            DP[i][j] = 2.0d * sqrt(dimensions[i].first * dimensions[i].first + dimensions[i].second * dimensions[i].second);
                        }
                    }
                    else{
                        if (j < 2*(min(dimensions[i].first, dimensions[i].second)) ){
                            DP[i][j] = DP[i+1][j];
                        }
                        else{
                            DP[i][j] = max(
                                DP[i+1][j],   // Do not take it
                                2.0d * sqrt(dimensions[i].first * dimensions[i].first + dimensions[i].second * dimensions[i].second) + DP[i+1][j - 2*(min(dimensions[i].first, dimensions[i].second))]
                            );
                        }
                    }
                }
            }

            // 
            if (DP[0][total_to_cover] >= total_to_cover){
                res = double(P);
            }
            else{
                res = double(P) - double(double(total_to_cover) - DP[0][total_to_cover]);
            }

        }

        cout << "Case #" << t << ": " << setprecision(10) << fixed << res << endl;

    }
    return 0;
}