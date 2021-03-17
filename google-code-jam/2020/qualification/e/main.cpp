#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// #define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << endl; cout << endl
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
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

vi take_three_ints(int N, int K){
    /**
     * Returns the three integers in a vector.
     * First integer is the one that occurs N-2 times, the other twos are simple integers.
     * The other two integers must be different from each other and from the first.
     * If result has size 1 then it is not possible.
     */ 
    vi result(3);
    bool found = false;
    FOR(i,1,N+1){
        FOR(j,1,N+1){
            FOR(p,1,N+1){
                if(i*(N-2) + j + p == K and
                 ((i==j and j==p) or (i!=j and i!=p and p!=j) or (i != j and j == p))){
                    result = {i,j,p};
                    return result;
                }
            }
        }
    }
    result = {-1};
    return result;
}

vi find_augmenting_path(int i, vi& matching, vvi& graph, vi& matching2){
    /*
        matching works 2->1
        matching2 works 1->2
    */
    queue<int> q;
    // Parents is indexed by bipartition 1 -> bipartition 2
    vi parent(matching.size(), -1);
    q.push(i);
    vi result(0);
    // VECT(matching);
    vb visited(matching.size(), false);
    visited[i] = true;
    while(!q.empty()){
        int n = q.front(); q.pop();
        FOR(j,0,graph[n].size()){
            if (matching[graph[n][j]] == -1){
                // Found an augmenting path.
                // The result, which is an augmenting path, oscillates between bip1 and bip2.
                result.push_back(graph[n][j]);
                int start = n;
                while(start != i) {
                    result.push_back(start);
                    result.push_back(matching2[start]);
                    start = parent[start];
                }
                result.push_back(i);
                reverse(result.begin(), result.end());
                return result;
            }
        }
        FOR(j,0,graph[n].size()){
            if (!visited[matching[graph[n][j]]]){
                q.push(matching[graph[n][j]]);
                parent[matching[graph[n][j]]] = n;
                visited[matching[graph[n][j]]] = true;
            }
        }
    }
    return result;
}

vi find_perfect_matching(vvi& graph){
    // matching has entries: index=number(2nd bipartition) -> cell (1st bipartition)
    // graph has index cell (1st bipartition) -> vector<int> adj (numbers 2nd bipartition)
    // In order to find a perfect matching, we need to find exactly N augmenting paths.
    // Every augmenting path increases the bipartite matching by 1.
    // When matching has size 0, it has not been possible to find a perfect matching.
    vi matching21(graph.size(), -1);
    vi matching12(graph.size(), -1);
    FOR(l,0,graph.size()){
        bool found = false;
        FOR(i,0,graph.size()){
            if (matching12[i] == -1){
                // We look for an augmenting path starting from each of the N vertices in the cells bipartition
                vi augmenting_path = find_augmenting_path(i, matching21, graph, matching12);
                if (augmenting_path.size() > 0){
                    COUT("augmenting path"); COUT(endl);
                    VECT(augmenting_path);
                    // we have found an augmenting path
                    // the augmenting path is made in this way: g1, g2, g1, g2 
                    // where g1 and g2 are any element of the first or second bipartition.
                    // It must always have even size.
                    assert(augmenting_path.size()%2==0);
                    for (int j = 1; j < augmenting_path.size(); j+=2){
                        matching21[augmenting_path[j]] = augmenting_path[j-1];
                        matching12[augmenting_path[j-1]] = augmenting_path[j];
                    }
                    found = true;
                    break;  // Look for another augmenting path.
                }
            }
        }
        if (!found){
            matching21.resize(0);
            return matching21;
        }

        VECT(matching21);
    }
    return matching21;
}

vvi build_graph(vector<unordered_set<int>>& columns, int i, vi& three_ints){
    vvi graph(columns.size(), vi());
    if (i == 0){
        // special case, we must have in the first two positions three_ints[2], three_ints[0]
        graph[0].push_back(three_ints[2]);
        graph[1].push_back(three_ints[0]);
        columns[0].insert(three_ints[2]);
        columns[1].insert(three_ints[0]);
        FOR(j,2,columns.size()){
            FOR(l,0,columns.size()){
                if (l!=three_ints[0] and l!=three_ints[2]){
                    graph[j].push_back(l);
                }
            }
        }
    }
    else if (i == 1){
        // special case, we must have in the first two positions three_ints[0], three_ints[1]
        graph[0].push_back(three_ints[0]);
        graph[1].push_back(three_ints[1]);
        columns[0].insert(three_ints[0]);
        columns[1].insert(three_ints[1]);
        FOR(j,2,columns.size()){
            FOR(l,0,columns.size()){
                if (l!=three_ints[0] and l!=three_ints[1] and columns[j].find(l)==columns[j].end()){
                    graph[j].push_back(l);
                }
            }
        }
    }
    else{
        FOR(l,0,columns.size()){
            if(l==i){
                // diagonal, we must put three_ints[0];
                graph[l].push_back(three_ints[0]);
                columns[l].insert(three_ints[0]);
            }
            else{
                FOR(j,0,columns.size()){
                    if (columns[l].find(j) == columns[l].end())
                        graph[l].push_back(j);
                }
            }
        }
    }
    return graph;
}

int main(){

    int T;
    cin >> T;
    FOR(t,0,T){
        vvi result;
        int N,K;
        cin >> N >> K;
        if(N==2){
            // Only possible cases
            if (K == 2){
                cout << "Case #" << t+1 << ": POSSIBLE" << endl;
                cout << "1 2" << endl << "2 1" << endl;
                continue;
            }
            if (K==4){
                cout << "Case #" << t+1 << ": POSSIBLE" << endl;
                cout << "2 1" << endl << "1 2" << endl;
                continue;
            }
        }
        vi three_ints = take_three_ints(N, K);
        if (three_ints.size()==1){
            cout << "Case #" << t+1 << ": IMPOSSIBLE" << endl;
            continue;
        }
        if (three_ints[0] == three_ints[1] and three_ints[1] == three_ints[2]){
            // fill with the diagonal strategy
            vvi result(N, vi(N));
            FOR(i,0,N){
                int val = three_ints[0] + i > N ? ((three_ints[0] + i) % N) : three_ints[0]+i;
                FOR(j,0,N){
                    result[j][(j+i)%N] = val;
                }
            }
            cout << "Case #" << t+1 << ": POSSIBLE" << endl;
            FOR(i,0,N){
                FOR(j,0,N)
                    cout << result[i][j] << " ";
                cout << endl;
            }                
            continue;
        }
        FOR(i,0,three_ints.size())
            three_ints[i]--;
        VECT(three_ints);
        // Contains the forbidden elements for the column.
        vector<unordered_set<int>> columns(N);
        FOR(i,0,N) // Insert the diagonal elements in every column.
            columns[i].insert(three_ints[0]);
        bool finish = true;
        FOR(i,0,N){
            // For every row
            vi row(N);
            vvi graph = build_graph(columns, i, three_ints);
            #ifdef TESTING
            cout << "Graph" << endl;
            FOR(x,0,N){
                FOR(y,0,graph[x].size()){
                    cout << graph[x][y] << " ";
                }
                cout << endl;
            }
            #endif
            vi matching = find_perfect_matching(graph);
            if (matching.size()==0){
                cout << "Case #" << t+1 << ": IMPOSSIBLE" << endl;
                finish = false;
                break;
            }
            else{
                FOR(j,0,matching.size()){
                    row[matching[j]] = j;
                    columns[matching[j]].insert(j);
                }
                result.push_back(row);
            }
        }
        if(finish){
            cout << "Case #" << t+1 << ": POSSIBLE" << endl;
            FOR(i,0,N){
                FOR(j,0,N){
                    cout << result[i][j] + 1 << (j != N-1?" ":"");
                }
                cout << endl;
            }    
        }

    }
    return 0;
}