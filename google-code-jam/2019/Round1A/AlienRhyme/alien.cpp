
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


class Node{
    
    public:
    vector<int> words;
    int depth;
    vector<Node* > children = vector<Node*> (26, NULL);

    Node(int depth){
        this->depth = depth;
    }

    void insert(int i, const string& word, int word_n ){
        //cout << word[i] << endl;
        this->words.push_back(word_n);
        if (i == word.size())
            ; // BREAK
        else {
            if (this->children[word[i] - 'A'] == NULL){
                this->children[word[i] - 'A'] = new Node(i+1);
            }

            this->children[word[i]-'A']->insert(i+1, word, word_n);
        }
    }
};


bool compare(pair<int, Node*>& p1, pair<int, Node*>& p2){
    return p1.first > p2.first;
}


void fill_vector(vector<pair<int, Node*>>& vector_with_nodes_and_rhymes, Node* node, Node* root){
    if (node != root && node->words.size() > 1){
        vector_with_nodes_and_rhymes.push_back({node->depth, node});
    }

    for (int i = 0; i<26; i++){
        if (node->children[i] != NULL){
            fill_vector(vector_with_nodes_and_rhymes, node->children[i], root);
        }
    }
}

void print_vector(vector<pair<int, Node*>> vect){
    for (int i = 0; i<vect.size(); i++){
        for (int j = 0; j<vect[i].second->words.size(); j++){
            cout << vect[i].second->words[j] << "\t";
        }
        cout << endl;
    }
}

void print_words(vector<string>& words){
    for (int i = 0; i<words.size(); i++){
        cout << words[i] << endl;
    }
}

void delete_tree(Node* node){
    for (int i = 0; i<26; i++){
        if (node->children[i] != NULL){
            delete_tree(node->children[i]);
        }
    }
    delete(node);
}

int main(){

    int T ;
    cin >> T;
    for (int t = 1; t<=T; t++){
        int n;
        cin >> n;
        vector<string> words (n);
        for (int i = 0; i<n; i++){
            string temp;
            cin >> temp;
            words[i].resize(temp.size());
            for (int j = temp.size()-1; j >= 0; j --){
                words[i][j] = temp[temp.size()-1-j]; 
            }
        }

        //print_words(words);

        Node * root = new Node(0);
        vector<bool> taken(n, false);

        for (int i = 0; i<n; i++){
            root->insert(0, words[i], i);
        }

        vector<pair<int, Node*>> nodes_and_rhyme_len;
        
        fill_vector(nodes_and_rhyme_len, root, root);
        sort(nodes_and_rhyme_len.begin(), nodes_and_rhyme_len.end(), compare);
        //print_vector(nodes_and_rhyme_len);

        // Now we compute the result
        int result = 0;
        for (int i = 0;i<nodes_and_rhyme_len.size(); i++){
            int words_taken = 0;
            int word1, word2;
            for (int j = 0; j<nodes_and_rhyme_len[i].second->words.size(); j++){
                if (taken[nodes_and_rhyme_len[i].second->words[j]] == false){
                    words_taken ++;
                    if (words_taken == 2){
                        word2 = nodes_and_rhyme_len[i].second->words[j];
                        taken[word1] = true;
                        taken[word2] = true;
                        result += 2;
                        break;
                    }
                    if (words_taken == 1){
                        word1 = nodes_and_rhyme_len[i].second->words[j];
                    }
                }
                
            }
        }

        // NEED TO DELETE THE TREE!!
        delete_tree(root);

        cout << "Case #" << t << ": " << result << endl;
    
    }
    return 0;
}