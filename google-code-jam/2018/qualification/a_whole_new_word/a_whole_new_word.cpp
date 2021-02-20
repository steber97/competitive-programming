#include <iostream>
//#include <fstream>
#include <vector>
#include <math.h>
#include <string>
#include <cstdlib>
using namespace std;

/*
ifstream cin ("input");
ofstream cout ("output");
*/
const int N_LETTERS = 26;

class Tree_of_words{
    public:
        Tree_of_words(int level);
        Tree_of_words* children[N_LETTERS];
        Tree_of_words* parent;
        int local_counter;
        int level;

};

Tree_of_words::Tree_of_words(int level){
    this->local_counter = 1;
    this->level = level;
    for (int i = 0; i<N_LETTERS; i++){
        this->children[i] = NULL;
    }
}

int convert_letter_to_int(char c){
    return (int) c - (int) 'A';
}

char convert_int_to_letter(int c){
    int res = (int) 'A' + c;
    return (char) res;
}

int calculate_total_counter(Tree_of_words* tree, int max_level);
void take_input(int N, Tree_of_words* head_of_tree, int L, bool letter_per_level [][N_LETTERS]);
void calculate_letter_counter_per_level(long int letters_counter_per_level[], int L, bool letter_per_level[][N_LETTERS], long int & total_counter);


int main (){

    int T;
    cin >> T;
    for(int q = 1; q<=T; q++){

        int N, L;


        long int total_counter = 1;
        cin >> N >> L;
        long int letters_counter_per_level[L];
        bool letter_per_level[L][N_LETTERS];

        for (int i = 0; i<L; i++){
            for (int j = 0; j<N_LETTERS; j++){
                letter_per_level[i][j] = false;
            }
        }

        Tree_of_words* head_of_tree = new Tree_of_words(0);

        // take input.
        take_input(N, head_of_tree, L, letter_per_level);

        // calculate letter_per_level
        calculate_letter_counter_per_level(letters_counter_per_level, L, letter_per_level, total_counter);

        //cout << "total_counter= " <<  total_counter << endl;
        int my_permutations = calculate_total_counter(head_of_tree, L);
        //cout << "my permutations = " << my_permutations << endl;

        // If result is '-'
        if (my_permutations == total_counter){
            cout << "Case #" << q << ": " << "-" << endl;
        }
        // If result is not null.
        else{
            char my_res [L];
            bool total_finish = false;
            Tree_of_words * my_tree = head_of_tree;
            for (int i = 0; i<L && !total_finish; i++){
                bool finish = false;
                if (i < L-1){
                    for (int j = 0; j<N_LETTERS && !finish; j++){
                        int combination_from_this_level = 1;
                        for (int h = i+1; h<L; h++){
                            combination_from_this_level *= letters_counter_per_level[h];
                        }

                        if (letter_per_level[i][j]){
                            int combinations_next_level = 1;
                            if (my_tree->children[j] == NULL){
                                // it's a letter of the level, but no children like that on this level.
                                // Just fill with casual letters (taken from letter_per_level.
                                my_res[i] = convert_int_to_letter(j);
                                for (int h = i+1; h<L; h++){
                                    bool finish1 = false;
                                    for (int z = 0; z<N_LETTERS && !finish1; z++){
                                        if (letter_per_level[h][z]){
                                            my_res[h] = convert_int_to_letter(z);
                                            total_finish = true;
                                            finish1 = true;
                                        }
                                    }
                                }
                                finish = true;
                            }
                            else if (my_tree->children[j] != NULL){
                                combinations_next_level = my_tree->children[j]->local_counter;
                                if (combinations_next_level < combination_from_this_level){
                                    //cout << "letter found= " << convert_int_to_letter(j) << endl;
                                    my_tree = my_tree->children[j];
                                    finish = true;
                                    my_res[i] = convert_int_to_letter(j);

                                }
                            }
                        }
                    }
                }
                // If we are considering the last letter.
                else {
                    bool finish = false;
                    for (int j = 0; j<N_LETTERS and !finish; j++){
                        if (letter_per_level[i][j] and my_tree->children[j] == NULL){
                            finish = true;
                            my_res[i] = convert_int_to_letter(j);
                        }
                    }
                }
            }

            cout << "Case #" << q << ": " ;
            for (int i = 0; i<L; i++){
                cout << my_res[i];
            }
            cout << endl;

        }

    }
    return 0;

}

int calculate_total_counter(Tree_of_words* tree, int max_level){
    int res = 0;
    if (tree->level == max_level){
        return 1;
    }
    else{
        for (int i = 0; i<N_LETTERS; i++){
            if (tree->children[i] != NULL){
                res += calculate_total_counter(tree->children[i], max_level);
            }
        }
    }
    tree->local_counter = res;
    return res;
}

void take_input(int N, Tree_of_words* head_of_tree, int L, bool letter_per_level [][N_LETTERS]) {
    for (int i = 0; i<N; i++){
        string s;
        cin >> s;
        Tree_of_words* actual = head_of_tree;
        for (int j = 0; j< L; j++){
            int pos_letter = convert_letter_to_int(s[j]);
            letter_per_level[j][pos_letter] = true;
            if (actual->children[pos_letter] == NULL){
                actual->children[pos_letter] = new Tree_of_words(j+1);
            }
            actual = actual->children[pos_letter];
        }
    }
}

void calculate_letter_counter_per_level(long int letters_counter_per_level[], int L, bool letter_per_level[][N_LETTERS], long int & total_counter){
    for (int i = 0; i<L; i++){
        letters_counter_per_level[i] = 0;
        for (int j = 0; j<N_LETTERS; j++){
            if(letter_per_level[i][j]){
                letters_counter_per_level[i] ++;
            }
        }
        total_counter *= letters_counter_per_level[i];
        //cout << "letters_counter_per_level= " << letters_counter_per_level[i] << endl;
    }
}