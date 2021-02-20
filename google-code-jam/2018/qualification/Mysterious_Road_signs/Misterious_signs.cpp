//
// Created by stefano on 29/04/18.
//

#include <iostream>
//#include <fstream>
#include <vector>

#define NOT_SET -1000100

using namespace std;

//ifstream cin ("input.txt");
//ofstream cout ("output.txt");

int calculate_result(vector< int* > , int);

int main(){
    int T;
    cin >> T;
    for (int q = 1; q <= T; q++){

        int S;
        cin >> S;
        vector < int * > signs; // vector in this order: D, A, B, N, M

        for (int i = 0; i<S; i++){
            int D, A, B, N, M;
            cin >> D >> A >> B;
            N = D - B;
            M = D + A;
            int * temp= new int[5];
            temp[0] = D;
            temp[1] = A;
            temp[2] = B;
            temp[3] = N;
            temp[4] = M;

            signs.push_back(temp);
        }
        /*
        for (int i = 0; i< signs.size(); i++){
            for (int j = 0; j < 5; j++){
                cout << signs[i][j] << "\t";
            }
            cout << endl;
        }
        */

        int max_sequence = 0;
        int number_of_sequences = 0;

        for (int i = S-1; i>=0; i--){
            if ((i != S-1) && (signs[i][3] == signs[i+1][3]) && (signs[i][4] == signs[i+1][4])){
                ;
            }
            else{
                int temp = calculate_result(signs, i);
                //cout << "temp= " << temp << endl;
                if (temp > max_sequence){
                    max_sequence = temp;
                    number_of_sequences = 1;
                }
                else if (temp == max_sequence){
                    number_of_sequences ++;
                }
            }

        }

        cout << "Case #" << q << ": " << max_sequence << "\t" << number_of_sequences << endl;
    }

    return 0;
}

int calculate_result(vector< int* > signs, int i){
    int first_couple[2];
    int second_couple[2];
    bool valid1 = true;
    bool valid2 = true;
    int max_sequence = 0;
    int count_solutions = 0;
    // vector in this order: D, A, B, N, M

    //cout << signs[i][3] << "\t" << signs[i][4] << endl;

    first_couple[0] = signs[i][3]; // set N
    first_couple[1] = NOT_SET;
    second_couple[1] = signs[i][4]; // set M
    second_couple[0] = NOT_SET;

    bool finished = false;
    int res = 1;
    for (int j = i-1; j >= 0 && !finished; j--){
        if ((first_couple[0] == signs[j][3] || first_couple[1] == signs[j][4]) && valid1){
        }
        else if (first_couple[1] == NOT_SET && valid1){
            first_couple[1] = signs[j][4];
        }
        else {
            valid1 = false;
        }
        if ((second_couple[0] == signs[j][3] || second_couple[1] == signs[j][4]) && valid2){
        }
        else if (second_couple[0] == NOT_SET && valid2){
            second_couple[0] = signs[j][3];
        }
        else {
            valid2 = false;
        }
        if (!valid1 && !valid2){
            finished = true;
        }
        else {
            res ++;
        }
        /*
        cout << res << endl;
        cout << "first_couple: " << first_couple[0] << "\t" << first_couple[1] << endl;
        cout << "second_couple: " <<second_couple[0] << "\t" << second_couple[1] << endl;
        */
    }
    return res;
}