#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

// #define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << " "; cout << endl
#define MAT(x) for (int u = 0; u < x.size(); u++) { for (int o = 0; o<x[u].size(); o++) cout << x[u][o] << " "; cout << endl;} cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define MAT(x)
#define COUT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<char> vc;
typedef vector<double> vd;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vc> vvc;
typedef vector<vvi> vvvi;
typedef vector<vd> vvd;
typedef vector<vector<long long>> vvll;
typedef vector<pair<int,ll>> vill;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<pair<ll,ll>> vllll;
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<vector<pair<int,ll>>> vvill;
typedef vector<vllll> vvllll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001 


vi split(string& s, char sep) {
    int j = 0;
    int prevend = 0;
    vi result;
    while(prevend < s.size()){
        while(j < s.size() && s[j] != sep)
            j++;
        int num = stoi(s.substr(prevend, j - prevend));
        result.push_back(num);
        prevend = j+1;
        j++;
    }
    return result;
}


class Node {
public:
    Node* left, *right;
    int value;

    void inorder() {
        if (this->left != NULL)
            this->left->inorder();
        cout << value << endl;
        if (this->right!=NULL)
            this->right->inorder();
    }

    ii fatina() {
        if (this->left == NULL && this->right == NULL)
            return {this->value, this->value};
        else {
            ii p1 = {INT32_MAX,INT32_MAX}, p2 = {INT32_MAX, INT32_MAX};
            ii res;
            if(this->left != NULL) {
                p1 = this->left->fatina();
            }
            if (this->right != NULL) {
                p2 = this->right->fatina(); 
            }

            if (p1.first == INT32_MAX)
                res = p2;
            else if (p2.first == INT32_MAX)
                res = p1;
            else {
                res = p1.first < p2.first ? p1 : (p1.first > p2.first ? p2 : (p1.second < p2.second ? p1 : p2));
            }

            res.first += this->value;
            return res;
        }
    }
};


Node* get_tree(vi& inorder, vi& postorder){
    VECT(inorder);VECT(postorder);
    if (inorder.size() == 0)
        return NULL;
    Node* root = new Node();
    root->value = *(postorder.end()-1);

    vi left_inorder, left_postorder,right_inorder, right_postorder;
    FOR(i,0,inorder.size()){
        if (inorder[i] == root->value){
            left_inorder = vi(inorder.begin(), inorder.begin()+i);
            left_postorder = vi(postorder.begin(), postorder.begin()+i);
            right_inorder = vi(inorder.begin()+i+1, inorder.end());
            right_postorder = vi(postorder.begin()+i, postorder.end()-1);

            root->left = get_tree(left_inorder, left_postorder);
            root->right = get_tree(right_inorder, right_postorder);
            break;
        }
    }

    return root;
}


int main(){
    while(!cin.eof()){
        string s1, s2;
        getline(cin, s1);
        if (s1.size()==0)
            break;
        getline(cin, s2);

        vi inorder = split(s1, ' ');
        vi postorder = split(s2, ' ');

        Node* root = get_tree(inorder, postorder);
        ii result = root->fatina();
        cout << result.second << endl;
        

    }
    return 0;
}