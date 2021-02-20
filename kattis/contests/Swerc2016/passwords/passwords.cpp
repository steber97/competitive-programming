
#include <bits/stdc++.h>
#include <climits>

using namespace std;

#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define COUT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
typedef vector<string> vs;

#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define INF 100000000
// code taken from https://www.toptal.com/algorithms/aho-corasick-algorithm
class Vertex{
    public:
        Vertex(){
            Leaf = false;
            Parent = -1;
            SuffixLink = -1;
            WordID = -1;
            EndWordLink= -1;
        }

        // Links to the child vertexes in the trie:
        // Key: A single character
        // Value: The ID of vertex
        unordered_map<char,int> Children;

        // Flag that some word from the dictionary ends in this vertex
        bool Leaf;

        // Link to the parent vertex
        int Parent;

        // Char which moves us from the parent vertex to the current vertex
        char ParentChar;

        // Suffix link from current vertex (the equivalent of P[i] from the KMP algorithm)
        int SuffixLink;

        // Link to the leaf vertex of the maximum-length word we can make from the current prefix
        int EndWordLink;

        // If the vertex is the leaf, we store the ID of the word
        int WordID;

        void print_vertex(){
            COUT(Parent); 
            COUT("\t"); 
            COUT(Leaf); 
            COUT("\t"); 
            COUT(WordID);
            COUT("\t"); 
            COUT(SuffixLink);
            COUT("\t"); 
            COUT(EndWordLink); 
            COUT("\n");
        }
};

class Aho{
    public:
        vector<Vertex*> Trie;
        vector<int> WordsLength;
        int size = 0;
        int root = 0;

        Aho(){
            Init();
        }
        int suffix(int x, char c) {
            while(x != root && Trie[x]->Children.find(c) == Trie[x]->Children.end()) 
                x = Trie[x]->SuffixLink;
            
            if (Trie[x]->Children.find(c) != Trie[x]->Children.end())
                return Trie[x]->Children[c];
            return root;
        }

        void Init(){
            Trie.push_back(new Vertex());          
            size++;
        }

        void AddString(string s, int wordID){
            int curVertex = root;
            for (int i = 0; i < s.size(); ++i) // Iterating over the string's characters
            {
                
                if (Trie[curVertex]->Leaf){
                    break;
                }
                char c = s[i];

                // Checking if a vertex with this edge exists in the trie:
                if (Trie[curVertex]->Children.find(c) == Trie[curVertex]->Children.end()){
                    Trie.push_back(new Vertex());
                    
                    Trie[size]->SuffixLink = -1; // If not - add vertex
                    Trie[size]->Parent = curVertex;
                    Trie[size]->ParentChar = c;
                    Trie[curVertex]->Children[c] = size;
                    size++;
                }
                curVertex = (int)Trie[curVertex]->Children[c]; // Move to the new vertex in the trie
            }
            // Mark the end of the word and store its ID
            Trie[curVertex]->Leaf = true;
            Trie[curVertex]->WordID = wordID;
            WordsLength.push_back(s.size());
        }
        void PrepareAho(){
            queue<int> vertexQueue;
            vertexQueue.push(root);
            while (vertexQueue.size() > 0)
            {
                int curVertex = vertexQueue.front();
                vertexQueue.pop();
                CalcSuffLink(curVertex);

                for (pair<char,int> key : Trie[curVertex]->Children)
                {
                    vertexQueue.push((int)key.second);
                }
            }
        }

        void CalcSuffLink(int vertex)
        {
            // Processing root (empty string)
            if (vertex == root)
            { 
                Trie[vertex]->SuffixLink = root;
                Trie[vertex]->EndWordLink = root;
                return;
            }
            // Processing children of the root (one character substrings)
            if (Trie[vertex]->Parent == root)
            { 
                Trie[vertex]->SuffixLink = root;
                if (Trie[vertex]->Leaf) Trie[vertex]->EndWordLink = vertex;
                else Trie[vertex]->EndWordLink = Trie[Trie[vertex]->SuffixLink]->EndWordLink;
                return;
            }
            // Cases above are degenerate cases as for prefix function calculation; the
            // value is always 0 and links to the root vertex.

            // To calculate the suffix link for the current vertex, we need the suffix
            // link for the parent of the vertex and the character that moved us to the
            // current vertex.
            int curBetterVertex = Trie[Trie[vertex]->Parent]->SuffixLink;
            char chVertex = Trie[vertex]->ParentChar; 
            // From this vertex and its substring we will start to look for the maximum
            // prefix for the current vertex and its substring.
            
            while (true)
            {
                // If there is an edge with the needed char, we update our suffix link
                // and leave the cycle
                if (Trie[curBetterVertex]->Children.find(chVertex) != Trie[curBetterVertex]->Children.end())
                {
                        Trie[vertex]->SuffixLink = (int)Trie[curBetterVertex]->Children[chVertex];
                        break;
                }
                // Otherwise, we are jumping by suffix links until we reach the root
                // (equivalent of k == 0 in prefix function calculation) or we find a
                // better prefix for the current substring.
                if (curBetterVertex == root)
                { 
                        Trie[vertex]->SuffixLink = root;
                        break;
                }
                curBetterVertex = Trie[curBetterVertex]->SuffixLink; // Go back by sufflink
            }
            // When we complete the calculation of the suffix link for the current
            // vertex, we should update the link to the end of the maximum length word
            // that can be produced from the current substring.
            if (Trie[vertex]->Leaf)
                Trie[vertex]->EndWordLink = vertex; 
            else
                Trie[vertex]->EndWordLink = Trie[Trie[vertex]->SuffixLink]->EndWordLink;
        }
};

/*

*/

#define MODULUS 1000003

int A,B,N;
vector<string> black;

vector<char> mymap = {'o', 'i', '$', 'e', '$', 's', '$', 't', '$', '$'}; 

int compute_result(Aho& ahoAlg, int pos, bool lower, bool upper, bool number, int node, vector<vector<vector<vector<vector<int>>>>>& DP){
    
    if (ahoAlg.Trie[node]->Leaf){
        DP[pos][lower?1:0][upper?1:0][number?1:0][node] = 0;
        return 0;
    }
    
    if (pos == 0){
        if (lower and upper and number){
            DP[pos][lower?1:0][upper?1:0][number?1:0][node] = 1;
            return 1;
        }
        else{
            DP[pos][lower?1:0][upper?1:0][number?1:0][node] = 0;
            return 0;
        }
    }
    if (DP[pos][lower?1:0][upper?1:0][number?1:0][node] != -1){
        return DP[pos][lower?1:0][upper?1:0][number?1:0][node];
    }
    

    else{
        if (ahoAlg.Trie[node]->Leaf){
            DP[pos][lower?1:0][upper?1:0][number?1:0][node] = 0;
            return 0;
        }
        else{
            // advance with lower
            int res = 0;
            FOR(i,0,26){
                char c = 'a' + i;
                int next = ahoAlg.suffix(node, c);
                res += compute_result(ahoAlg, pos-1, true, upper, number, next, DP);
                res %= MODULUS;
            }
            // advance with upper
            FOR(i,0,26){
                char c = 'a' + i;  // Actually we are adding uppercase letters.
                int next = ahoAlg.suffix(node, c);
                res += compute_result(ahoAlg, pos-1, lower, true, number, next, DP);
                res %= MODULUS;
            }
            // advance with number
            FOR(i,0,10){
                char c = mymap[i];
                int next;
                if (c != '$'){
                    next = ahoAlg.suffix(node, c); 
                }
                else{
                    next = ahoAlg.root;
                }
                res += compute_result(ahoAlg, pos-1, lower, upper, true, next, DP);
                res %= MODULUS;
            }
            DP[pos][lower?1:0][upper?1:0][number?1:0][node] = res;
            return res;
        }
    }
}

void computeLPSArray(string pat, int M, int* lps) 
{ 
    // length of the previous longest prefix suffix 
    int len = 0; 
  
    lps[0] = 0; // lps[0] is always 0 
  
    // the loop calculates lps[i] for i = 1 to M-1 
    int i = 1; 
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else // (pat[i] != pat[len]) 
        { 
            // This is tricky. Consider the example. 
            // AAACAAAA and i = 7. The idea is similar 
            // to search step. 
            if (len != 0) { 
                len = lps[len - 1]; 
  
                // Also, note that we do not increment 
                // i here 
            } 
            else // if (len == 0) 
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 
  

bool KMPSearch(string pat, string txt) 
{ 
    int M = pat.size(); 
    int N = txt.size(); 
  
    // create lps[] that will hold the longest prefix suffix 
    // values for pattern 
    int lps[M]; 
  
    // Preprocess the pattern (calculate lps[] array) 
    computeLPSArray(pat, M, lps); 
  
    int i = 0; // index for txt[] 
    int j = 0; // index for pat[] 
    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
            return true;  
        } 
  
        // mismatch after j matches 
        else if (i < N && pat[j] != txt[i]) { 
            // Do not match lps[0..lps[j-1]] characters, 
            // they will match anyway 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    } 
    return false;
} 

bool mycompare(string& s1, string& s2){
    return s1.size() < s2.size();
}

int main(){

    cin >> A >> B >> N;
    FOR(i,0,N){
        string temp;
        cin >> temp;
        black.push_back(temp);
    }

    sort(black.begin(), black.end(), mycompare);
    vector<string> b2;
    if (black.size() > 0)
        b2.push_back(black[0]);
    FOR(i,1,N){
        bool already_in = false;
        FOR(k,0,b2.size()){
            already_in = KMPSearch( b2[k], black[i] );
            if(already_in){
                break;
            }
        }
        if (!already_in)
            b2.push_back(black[i]);
    }

    Aho ahoAlg;

    for (int i = 0; i < b2.size(); i++)
    {
        ahoAlg.AddString(b2[i], i); // Add all patterns to the structure
    }
    // Prepare algorithm for work (calculates all links in the structure):
    ahoAlg.PrepareAho();

    vector<vector<vector<vector<vector<int>>>>> DP (B+1, vector<vector<vector<vector<int>>>> (2, vector<vector<vector<int>>>(2, vector<vector<int>>(2, vector<int>(ahoAlg.Trie.size())))));

    // initialize
    FOR(i,0,B+1){
        FOR(j,0,2){
            FOR(k,0,2){
                FOR(l,0,2){
                    FOR(m,0,ahoAlg.Trie.size()){
                        DP[i][j][k][l][m] = -1;
                    }
                }
            }
        }
    }
    /*
    COUT("Parent"); 
    COUT("\t"); 
    COUT("Leaf"); 
    COUT("\t"); 
    COUT("WordID");
    COUT("\t"); 
    COUT("SuffixLink");
    COUT("\t"); 
    COUT("EndWordLink"); 
    COUT("\n");
    for(auto el: ahoAlg.Trie){
        el->print_vertex();
    }*/
    
    int res = 0;
    
    FOR (i, A, B+1){
        res += compute_result(ahoAlg, i, false, false, false, ahoAlg.root, DP);
        res %= MODULUS;
    }

    cout << res << endl;


    // Process the text. Output might be different; in my case, it's a count of
    // matches. We could instead return a structure with more detailed information.
    //int countOfMatches = ahoAlg.ProcessString(text);
        

    
    return 0;
}