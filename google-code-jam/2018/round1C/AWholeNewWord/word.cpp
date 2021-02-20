#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node{
    vector<Node*> children = vector<Node*> (26, NULL);

    public:
    void insert_word(string word, int level, vector<vector<bool>>& char_is_present_at_level){
        if (level < word.size()){
            char char_at_level = word[level];
            if (children[char_at_level - 'A'] == NULL){
                children[char_at_level - 'A'] = new Node();
            }
            char_is_present_at_level[level][char_at_level-'A'] = true;
            children[char_at_level-'A']->insert_word(word, level+1, char_is_present_at_level);
        }
    }
    string find_missing_path(int level, string res, vector<vector<bool>>& char_is_present_at_level, const int L){
        if (level < L){
            for (int i = 0; i<char_is_present_at_level[level].size(); i++){
                if (char_is_present_at_level[level][i] == true && this->children[i] == NULL){
                    // Found result
                    //cout << "Found result" << endl;
                    res += char('A' + i);
                    for (int j = level+1; j<L; j++){
                        for (int k = 0; k<26; k++){
                            if (char_is_present_at_level[j][k]){
                                res += char('A' + k);
                                break;
                            }
                        }
                    }
                    return res;
                }
            }
        }
        string max_res = "";
        for (int i = 0; i<26; i++){
            if (this->children[i] != NULL){
                string temp_res = this->children[i]->find_missing_path(level+1, res+(char('A'+i)), char_is_present_at_level, L);
                if (max_res.size() < temp_res.size())
                    max_res = temp_res;
            }
        }
        return max_res;
    }

};

void print_char_is_present_at_level(vector<vector<bool>>& char_is_present_at_level){
    cout << "Char at level" << endl;
    for (int i = 0; i<char_is_present_at_level.size(); i++){
        for (int j = 0; j<char_is_present_at_level[i].size(); j++){
            if (char_is_present_at_level[i][j]){
                cout << char('A' + j) ;
            }
        }
        cout << endl;
    }
}

int main(){

    int T;
    cin >> T;
    for (int t = 1; t<=T; t++){

        Node* root = new Node();
        vector<string> input;
        int N,L;
        cin >> N >> L;

        vector<vector<bool>> char_is_present_at_level(L, vector<bool>(26, false));

        for (int i = 0; i<N; i++){
            string temp;
            cin >> temp;
            root->insert_word(temp, 0, char_is_present_at_level);
        }

        //print_char_is_present_at_level(char_is_present_at_level);
        
        string result = root->find_missing_path(0, "", char_is_present_at_level, L);
        if (result.size() == 0){
            result = "-";
        }
        cout << "Case #" << t << ": " << result << endl;

    }
    return 0;
}