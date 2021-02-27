#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

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


void set_num_children(vi& parent, vi& indeg, vi& num_children){
    queue<int> q;
    vi indeg2(parent.size()) ;
    FOR(i,0,parent.size()){
        indeg2[i] = indeg[i];
        if (indeg[i] == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int n = q.front();
        num_children[n] ++;
        q.pop();
        if (parent[n] >= 0){
            num_children[parent[n]] += num_children[n];
            indeg2[parent[n]]--;
            if (indeg2[parent[n]]==0){
                q.push(parent[n]);
            }
        }
    }
}

void set_parent_depth(int i, vii& parent_depth, vi& indeg, vi& parent){
    if (parent[i] == -1){
        parent_depth[i] = {-1, 1};
    }
    else if (indeg[parent[i]] > 1){
        set_parent_depth(parent[i], parent_depth, indeg, parent);
        parent_depth[i] = {parent[i], 1};
    }
    else{
        set_parent_depth(parent[i], parent_depth, indeg, parent);
        if (parent[parent[i]] != -1){
            if (indeg[parent[i]] == 1 and indeg[parent[parent[i]]] == 1){
                parent_depth[i] = {parent_depth[parent[i]].first, parent_depth[parent[i]].second + 1};
            }
            else{
                parent_depth[i] = {parent[i], 1};
            }
        }
        else{
            parent_depth[i] = {parent[i], 1};
        }
    }
}


int main(){
    int n;
    cin >> n;
    vi parent(n);
    FOR(i,0,n){
        cin >> parent[i];
        parent[i] --;
    }
    
    vi num_children(n, 0);
    vi indeg(parent.size(), 0);
    FOR(i,0,parent.size()){
        if (parent[i] >= 0)
            indeg[parent[i]] ++;
    }
    set_num_children(parent, indeg, num_children);
    #ifdef TESTING
    cout << "parents" << endl;
    FOR(i,0,parent.size()){
        cout << i+1 << " " << parent[i] + 1 << endl;
    }
    #endif
    #ifdef TESTING
    cout << "num children" << endl;
    FOR(i,0,parent.size()){
        cout << i+1 << " " << num_children[i] << endl;
    }
    #endif
    VECT(indeg);

    vii parent_depth(parent.size(), {-1,-1});
    FOR(i,0,parent.size()){
        if (parent_depth[i].first == -1 && parent_depth[i].second == -1 && indeg[i] == 0){
            set_parent_depth(i, parent_depth, indeg, parent);
        }
    }
    #ifdef TESTING
    cout << "parent depth" << endl;
    FOR(i,0,n)
        cout << parent_depth[i].first << " " << parent_depth[i].second << endl;

    #endif


    int r;
    cin >> r;
    FOR(i,0,r){
        int l;
        cin >> l;
        vi query(l);
        unordered_map<int,int> nodes;
        unordered_set<int> queries;
        FOR(j,0,l){
            cin >> query[j]; query[j]--;
            if (queries.find(query[j]) == queries.end()){
                queries.insert(query[j]);
                nodes[query[j]] = 0;
                if (parent[query[j]] != -1){
                    if (indeg[parent[query[j]]] == 1){
                        if (nodes.find(parent_depth[query[j]].first) == nodes.end()){
                            nodes[parent_depth[query[j]].first] = INT16_MAX;
                        }
                        nodes[parent_depth[query[j]].first] = min(
                            parent_depth[query[j]].second,
                            nodes[parent_depth[query[j]].first]
                        );
                    }
                }
            }
        }
        #ifdef TESTING
        cout << "nodes: " << i << endl;
        for(ii k: nodes){
            cout << k.first << " " << k.second << endl;
        }
        #endif
        int res = 0;
        for (int q: queries){
            // move from parent to parent, and if no conflict is found, then we are OK!
            ii u = parent_depth[q];
            bool done = true;
            while(u.first != -1 && done){
                if (nodes.find(u.first) == nodes.end()){
                    u = parent_depth[u.first];
                }
                else if (nodes[u.first] > 0 && nodes[u.first] >= u.second){
                    u = parent_depth[u.first];
                }
                else{
                    done = false;
                }
            }
            if (done)
                res += num_children[q];
        }
        COUT("result");
        cout << res << endl;
        
    }
    return 0;    
}