
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;



int Aug(int l, vector<int>& vis, vector<vector<int>>& graph, vector<int>& match){
    if (vis[l])
        return 0;
    vis[l] = 1;
    for (int j=0; j<graph[l].size(); j++){
        int r = graph[l][j];
        if (match[r] == -1 || Aug(match[r], vis, graph, match)){
            match[r] = l;
            return 1;
        }
    }
    return 0;
}

int main(){

    int n;
    cin >> n;
    vector<pair<long long, long long>> v(n);

    vector<vector<int>> graph(n);

    int counter = n;

    unordered_map<long long, int> map_results_to_pos_in_graph;
    unordered_map<int,long long> reverse_map;

    for (int i = 0;i<n; i++){
        cin >> v[i].first >> v[i].second;
        
        long long sum = v[i].first + v[i].second;
        long long diff = v[i].first - v[i].second;
        long long mul = v[i].first * v[i].second;

        if (map_results_to_pos_in_graph.find(sum) == map_results_to_pos_in_graph.end()){
            reverse_map[counter] = sum;
            map_results_to_pos_in_graph[sum] = counter;
            counter ++;
        }
        if (map_results_to_pos_in_graph.find(diff) == map_results_to_pos_in_graph.end()){
            reverse_map[counter] = diff;
            map_results_to_pos_in_graph[diff] = counter;
            counter ++;
        }
        if (map_results_to_pos_in_graph.find(mul) == map_results_to_pos_in_graph.end()){
            reverse_map[counter] = mul;
            map_results_to_pos_in_graph[mul] = counter;
            counter ++;
        }
        graph[i].push_back(map_results_to_pos_in_graph[sum]);
        graph[i].push_back(map_results_to_pos_in_graph[diff]);
        graph[i].push_back(map_results_to_pos_in_graph[mul]);
    }

    // size is the number of vertices in the bipartite graph.
    vector<int> match(counter, -1);
    int MCBC = 0;
    for (int l = 0; l<n; l++){   // n is the size of the left set.
        vector<int> vis(n, 0);      // reset before each recursion.
        MCBC += Aug(l, vis, graph, match);
    }

    if (MCBC < n){
        cout << "impossible" << endl;
    }
    else{   
        vector<pair<char, long long>> result(n);
        for (int i = 0; i<match.size(); i++){
            if (match[i] != -1){
                if (v[match[i]].first + v[match[i]].second == reverse_map[i]){
                    result[match[i]] = {'+', v[match[i]].first + v[match[i]].second};
                }
                else if (v[match[i]].first - v[match[i]].second == reverse_map[i]){
                    result[match[i]] = {'-',v[match[i]].first - v[match[i]].second};
                }   
                else if (v[match[i]].first * v[match[i]].second == reverse_map[i]){
                    result[match[i]] = {'*',v[match[i]].first * v[match[i]].second};
                }
            }
        }

        for (int i = 0; i<n; i++){
            cout << v[i].first << " " << result[i].first << " " << v[i].second << " = " <<  result[i].second << endl;
        }
    }
    


    return 0;
}