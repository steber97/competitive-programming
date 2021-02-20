#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <cmath>
#define DEBUG false

using namespace std;

#define INF 1000

class Edge{
    public:
    int start, end, people, time;
    Edge(int start, int end, int people, int time) {
        this->start = start;
        this->end = end;
        this->people = people;
        this->time = time;
    }
};

int get_node_index(int node, int time, int total_nodes){
    return node + total_nodes * time;
}

long long get_index_in_map(int node1, int node2){
    return (long long)(node1 * (long long)(1000000) ) + (long long)(node2);
}

int bfs(vector<vector<int>>& graph, unordered_map<long long,int>&cap_mat, int source, int sink, vector<bool>& visited, int parent[]){
    int res = 10000000;
    queue<int> my_queue;
    my_queue.push(source);

    bool reached_sink = false;
    
    while(!my_queue.empty() && !reached_sink){
        
        int node = my_queue.front();
        if (DEBUG)
            cout << "node visited " << node << endl;
        my_queue.pop();
        if (node == sink){
            if (DEBUG)
                cout << "reached sink" << endl;
            reached_sink = true;
        }
        for (int i = 0; i<graph[node].size() && !reached_sink; i++){
            
            if (!visited[graph[node][i]] && cap_mat[get_index_in_map(node, graph[node][i]) ] > 0){
                visited[graph[node][i]] = true;
                my_queue.push(graph[node][i]);
                parent[graph[node][i]] = node;
            }
        }
    }

    if (reached_sink){
        int temp = sink;
        
        while(temp != source){
            int temp2 = parent[temp];
            res = min(res, cap_mat[get_index_in_map(temp2, temp)]);
            temp = temp2;
        }
    }
    else {
        res = 0;
    }

    return res;
}

int fordFulkerson(vector<vector<int>>& graph, unordered_map<long long, int>& cap_mat, int source, int sink){
    // wrapper for DFS algorithm
    // bitset.
    int temp_flow = 1;
    int max_flow = 0;
    int N = graph.size();
    while(temp_flow != 0){
        vector<bool> visited(N, false);

        visited[source] = true;

        int parent[N];
        parent[source] = source;
        temp_flow = bfs(graph, cap_mat, source, sink, visited, parent);
        max_flow += temp_flow;
        if (temp_flow != 0){
            // fill edges.
            int temp = sink;
            while(temp != source){
                int temp2 = parent[temp];
                cap_mat[get_index_in_map(temp2, temp)] -= temp_flow;
                temp = temp2;
            }
        }
    }
    
    return max_flow;
}

void print_graph(vector<vector<int>>& flow_graph){
    for (int i = 0; i<flow_graph.size(); i++){
        cout << i << ": " ;
        for (int j = 0; j<flow_graph[i].size(); j++){
            cout << flow_graph[i][j] << "\t";
        }
        cout<< endl;
    }
}

int main(){

    int T;
    cin >> T;

    for (int t = 1; t<=T; t++){
        // per each test case
        int locat;
        cin >> locat;
        int start, num_peop, time;
        cin >> start >> num_peop >> time;
        int num_safe_loc;
        cin >> num_safe_loc;

        vector<int> safe_loc;
        vector<bool> safe_loc_bool(locat+1, false);
        bool finish = false;
        for (int i = 0; i<num_safe_loc; i++){
            int temp;
            cin >> temp;
            safe_loc.push_back(temp);
            safe_loc_bool[temp] = true;
            if (temp == start){
                cout << num_peop << endl;
                finish = true;
            }
        }

        // If we start from a safe point, then no need to further check! :)
        if (finish)
            continue;
        vector<Edge> edges;
        int num_edges;
        cin >> num_edges;

        for (int i = 0; i<num_edges; i++){
            int start, end, people, time;
            cin >> start >> end >> people >> time;
            edges.push_back(Edge(start, end, people, time));
        }   

        vector<vector<int>> flow_graph(locat * (time+1) + 1, vector<int>());    // 1 node per each location and time, plus the sink

        unordered_map<long long, int> weight_map;

        for (int ti = 0; ti<=time; ti++){
            if (ti < time-1){
                // Put edges to pass from time to time+1 of the same node.
                for (int l = 1; l<=locat; l++){
                    if (!safe_loc_bool[l]){
                        int node1 = get_node_index(l, ti, locat);
                        int node2 = get_node_index(l, ti+1, locat);
                        flow_graph[node1].push_back(node2);
                        weight_map[get_index_in_map(node1, node2)] = INF;
                    }
                    
                }
            }

            // Put edges to pass from node1 to node2 + some time of every edge in the initial graph.
            for (Edge e: edges){
                if (ti + e.time <= time){
                    if (!safe_loc_bool[e.start]){
                        int node1 = get_node_index(e.start, ti, locat);
                        int node2;
                        if (safe_loc_bool[e.end]){
                            node2 = 0;
                            //node2 = get_node_index(e.end, ti+e.time, locat);
                        }
                        else{
                            node2 = get_node_index(e.end, ti+e.time, locat);
                        }
                        flow_graph[node1].push_back(node2);
                        if (node2 == 0){
                            if (weight_map.find(get_index_in_map(node1, node2)) == weight_map.end()){
                                weight_map[get_index_in_map(node1, node2)] = e.people; 
                            }
                            else{
                                weight_map[get_index_in_map(node1, node2)] += e.people;  
                            }
                        }
                        else{
                            weight_map[get_index_in_map(node1, node2)] = e.people;  
                        }
                    }
                }
            }    

            // Put edges to the sink (NODE 0 is the sink)
            
            for (int safe: safe_loc){
                int node1 = get_node_index(safe, ti, locat);
                int node2 = 0;   // the sink

                flow_graph[node1].push_back(node2);
                weight_map[get_index_in_map(node1, node2)] = INF;
            }
        }

        if (DEBUG)
            print_graph(flow_graph);

        int result = fordFulkerson(flow_graph, weight_map, start, 0);

        cout << min(result, num_peop) << endl;   



    }
    return 0;
}