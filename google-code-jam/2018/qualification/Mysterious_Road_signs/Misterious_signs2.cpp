//# include <iostream>
# include <fstream>
# include <vector>

using namespace std;

ifstream cin ("input.txt");
ofstream cout ("output.txt");


pair< int, int > start_with_N(int* , int* , int* , int* , int* , int* , int* , int, int);
pair< int, int > start_with_M(int* , int* , int* , int* , int* , int* , int* , int, int);

int main(){
    int T;
    cin >> T;
    for (int q = 1; q <= T; q++) {

        int S;
        cin >> S;
        int * D = new int[S];
        int * A = new int[S];
        int * B = new int[S];
        int * N = new int[S];
        int * M = new int[S];

        for (int i = 0; i < S; i++) {
            cin >> D[i] >> A[i] >> B[i];
            N[i] = D[i] - B[i];
            M[i] = D[i] + A[i];
        }

        int* consecutive_M = new int[S];
        int* consecutive_N = new int[S];

        for (int i = S-1; i>=0; i--){
            if (i == S-1){
                consecutive_M[i] = 1;
                consecutive_N[i] = 1;
            }
            else {
                if (M[i] == M[i+1]){
                    consecutive_M[i] = consecutive_M[i+1] + 1;
                }
                else {
                    consecutive_M[i] = 1;
                }
                if (N[i] == consecutive_N[i+1]){
                    consecutive_N[i] = consecutive_N[i+1] + 1;
                }
                else {
                    consecutive_N[i] = 1;
                }
            }
        }

        int res, number_of_sequences;
        res = 0;
        number_of_sequences = 0;

        pair < int, int > res1 = start_with_N(D, A, B, N, M, consecutive_M, consecutive_N, S, 1);
        //cout << res1.first << "\t" << res1.second << endl;
        pair < int, int > res2  = start_with_M(D, A, B, N, M, consecutive_M, consecutive_N, S, 1);
        //cout << "\t" << res2.first << "\t" << res2.second << endl;

        if (res1.first > res){
            res = res1.first;
            number_of_sequences = 1;
        }
        else if (res1.first == res){
            number_of_sequences += res1.second;
        }

        if (res2.first > res){
            res = res2.first;
            number_of_sequences = 1;
        }
        else if (res2.first == res){
            number_of_sequences += res2.second;
        }

        cout << res << "\t" << number_of_sequences << endl;

    }

    return 0;
}

pair< int, int > start_with_N(int* D, int* A, int* B, int* N, int* M, int* consecutive_M, int* consecutive_N, int S, int max_len){
    int number_of_sequences_with_max_len = 0;
    int max_length = 0;
    int temp_result;
    int n_temp, m_temp;
    bool m_fixed = false;
    int i = 0;
    for (int i = 0; i<S && i+max_len <= S; i++){
        n_temp = N[i];
        bool finished = false;
        int actual_len = 0;
        int j = i;
        while (!finished && j < S){
            if (n_temp == N[j]){
                int pos_new_m = j + consecutive_N[j];
                actual_len += consecutive_N[j];
                if (m_fixed){
                    if (M[pos_new_m] == m_temp){
                        actual_len += consecutive_M[pos_new_m];
                        j += consecutive_M[pos_new_m] + consecutive_N[j];
                    }
                    else {
                        finished = true;
                    }
                }

                else {
                    m_fixed = true;
                    m_temp = M[pos_new_m];
                    actual_len += consecutive_M[pos_new_m];
                    j += pos_new_m + consecutive_M[pos_new_m];
                }

            }
            else {
                finished = true;
            }
        }

        if (actual_len > max_length ){
            max_length = actual_len;
            number_of_sequences_with_max_len = 1;
        }
        else if (actual_len == max_length){
            number_of_sequences_with_max_len ++;
        }

    }
    return make_pair(max_length, number_of_sequences_with_max_len);
}

pair< int, int > start_with_M(int* D, int* A, int* B, int* N, int* M, int* consecutive_M, int* consecutive_N, int S, int max_len){
    int number_of_sequences_with_max_len = 0;
    int max_length = 0;
    int temp_result;
    int n_temp, m_temp;
    bool n_fixed = false;
    int i = 0;
    for (int i = 0; i<S && i+max_len <= S; i++){
        m_temp = M[i];
        bool finished = false;
        int actual_len = 0;
        int j = i;
        while (!finished && j < S){
            if (m_temp == M[j]){
                int pos_new_n = j + consecutive_M[j];
                actual_len += consecutive_M[j];
                if (n_fixed){
                    if (N[pos_new_n] == n_temp){
                        actual_len += consecutive_N[pos_new_n];
                        j += consecutive_N[pos_new_n] + consecutive_M[j];
                    }
                    else {
                        finished = true;
                    }
                }

                else {
                    n_fixed = true;
                    n_temp = N[pos_new_n];
                    actual_len += consecutive_N[pos_new_n];
                    j += pos_new_n + consecutive_N[pos_new_n];
                }

            }
            else {
                finished = true;
            }
        }

        if (actual_len > max_length ){
            max_length = actual_len;
            number_of_sequences_with_max_len = 1;
        }
        else if (actual_len == max_length){
            number_of_sequences_with_max_len ++;
        }

    }
    return make_pair(max_length, number_of_sequences_with_max_len);
}