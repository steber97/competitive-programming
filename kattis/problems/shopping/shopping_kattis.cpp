#include <vector>
#include <iostream>
#include <queue>
#include <bitset>
#include <cmath>
#include <cassert>  


using namespace std;

class Compare{
public:
    bool operator() (pair<int,long long> p1, pair<int,long long> p2)
    {
        return p1.second >= p2.second;
    }
};

void dijkstra(int shop, int start_node, vector<vector<pair<int,long long>>>& graph, vector<vector<long long>>& distances, vector<int> shops){
    
    
    priority_queue<pair<int,long long>, vector<pair<int,long long>>, Compare> pq; 

    vector<long long> distance(graph.size(), -1LL);
    distance[start_node] = 0LL;
    pq.push({start_node, 0LL});
    while(!pq.empty()){
        int node = pq.top().first;
        long long weight = pq.top().second;
        pq.pop();
        //assert(node < distance.size());
        if (distance[node] == weight){
            for (pair<int,long long> adj: graph[node]){
                if (distance[adj.first] == -1LL || (distance[adj.first] > (adj.second + weight))){
                    assert(adj.second + weight >= 0LL);
                    distance[adj.first] = adj.second + weight;
                    pq.push({adj.first, adj.second + weight});
                }
            }
        }
    }
    
    for (int i = 0; i<shops.size(); i++){
        distances[shop][i] = distance[shops[i]];
        distances[i][shop] = distance[shops[i]];
    }
}

long long till_the_end_permutation(int S, vector<vector<long long>>& distances, int taken, vector<int>& path, 
                                   long long weight, int posw, int still_to_take){
    
    if (still_to_take == 0){
        // Finish, now we add the distance from the last to 0
        return weight + distances[path[posw-1]][0];
    }
    else{
        // Try all possible permutations.
        long long max_res =  (long long)INT64_MAX;
        for (int i = 0; i<S+1; i++){
            if ((taken & (1<<i)) == 0){
                taken += (1<<i);
                path[posw] = i;
                max_res = min(
                    max_res,
                    till_the_end_permutation(S, distances,taken,path, weight+distances[path[posw-1]][i], posw+1, still_to_take-1)
                );
                taken -= (1<<i);
            }
        }
        return max_res;
    }
}

void first_permut(vector<vector<long long>>& DP, vector<int>& path, int taken, vector<vector<long long>>& distances, int posw, long long weight){
    
    if (posw == 5){
        // we have finished
        int pos_bitset = taken;
        long long total_weight = 0LL;
        weight += distances[path[4]][0];   // Add the weight to return back home.
        
        DP[path[0]][pos_bitset] = min(DP[path[0]][pos_bitset], weight);
    }
    else{
        for (int i = 0; i<DP.size(); i++){
            if ((taken & (1<<i)) == 0){
                taken += (1<<i);
                path[posw] = i;
                first_permut(DP, path, taken, distances, posw+1, weight + distances[path[posw-1]][path[posw]] );
                taken -= (1<<i);
            }
        }
    }
}

long long second_permut(vector<vector<long long>>& DP, vector<int>& path, int taken,
                  vector<vector<long long>>& distances, int second_permut_len, int posw,
                  vector<bool>& complementary_taken, long long cost_until_now){
    if (posw == second_permut_len){

        // int pos_dp_complementary_taken = convert_bitset_to_int(complementary_taken);
        int pos_dp_complementary_taken = ( ( (( 1 << (DP.size()) ) -1) ^ taken) & (( 1 << (DP.size()) ) -1)); 
        pos_dp_complementary_taken += 1;  // Is used because first element in taken is always true.
        long long dist_to_end = (long long)INT64_MAX;
        for (int j=0; j<DP.size(); j++){
            if ((taken & (1<<j)) == 0){
                //assert(DP[j][pos_dp_complementary_taken] != INT32_MAX);
                dist_to_end = min(
                    dist_to_end,
                    (DP[j][pos_dp_complementary_taken] + distances[path[second_permut_len-1]][j] ) 
                );
            }
        }
        return (dist_to_end == INT64_MAX? (long long)INT64_MAX :dist_to_end + cost_until_now);
    
    }
    else{
        long long best_res = INT64_MAX;
        for (int i = 0; i<DP.size(); i++){
            if ((taken & (1<<i)) == 0){
                taken += (1<<i);
                complementary_taken[i] = false;
                path[posw] = i;
                best_res = min(best_res, second_permut(DP, path, taken, distances, second_permut_len, posw+1,
                               complementary_taken, cost_until_now + distances[path[posw-1]][path[posw]]));
                taken-= (1<<i);
                complementary_taken[i] = true;
            }
        } 
        return best_res;
    }
    
}


int main(){

    //cout << "test " << t << endl;
    int N,M;
    cin >> N >> M;
    vector<vector<pair<int,long long>>> graph(N, vector<pair<int,long long>>());
    for (int i = 0; i<M; i++){
        int node1, node2;
        long long weight;
        cin >> node1 >> node2 >> weight;
        graph[node1].push_back({node2, weight});
        graph[node2].push_back({node1, weight});
    }
    int S;
    cin >> S;
    // the starting point is node 0;
    vector<int> shops(S+1);
    shops[0] = 0;
    vector<vector<long long>> distances(S+1,vector<long long>(S+1));
    for (int i = 1; i<=S; i++){
        cin >> shops[i];
    }

    for (int i = 0; i<S; i++){
        // we count only till S-1, as shop number S has already been counted;
        dijkstra(i, shops[i], graph, distances, shops);
    }
    
    if (S > 5){
        
        int first_permut_len = 5;
        int second_permut_len = S - 5;
        vector<bool> b;
        vector<vector<long long>> DP(S+1, vector<long long>(int(pow(2, S+1)), (long long)INT64_MAX));
        vector<int> path (first_permut_len);
        int taken = 0;

        for (int i = 1; i<=S; i++){
            taken += (1<<i);
            taken += 1;
            path[0] = i;
            first_permut(DP, path, taken, distances, 1, 0LL);  // The last number is posw, the position where to write the next shop in path.
            taken -= (1<<i);
            taken -= 1;
        }
        long long res = INT64_MAX;
        
        //path.resize (second_permut_len);
        taken = 0;
        vector<bool> complementary_taken(S+1, true);

        for (int i = 1; i<=S; i++){
            // try to do meet in the middle.
            
            taken += (1<<i);
            complementary_taken[i] = false;
            taken += 1;   // Like setting taken[0] = true;
            path[0] = i;
            res = min(res, second_permut(DP, path, taken, distances, second_permut_len, 1, complementary_taken, distances[0][path[0]]));
            taken -= (1<<i);  // like resetting taken[i] = false;
            taken -= 1;    // Like resetting taken[0] = false;
            complementary_taken[i] = true;
        }

        cout << res << endl;
    }
    else{
        int taken = 0;
        taken = 1; // Same as taken[0] = true;
        vector<int> path(S+1);
        path[0] = 0;
        long long weight = 0LL;
        int posw = 1;
        long long len_of_shortest_path = till_the_end_permutation(S, distances, taken, path, weight, posw, S);
        cout << len_of_shortest_path << endl;
        
    }
    return 0;
}  
