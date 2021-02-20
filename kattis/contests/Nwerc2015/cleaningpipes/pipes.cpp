#include <vector>
#include <iostream>
#include <queue>

using namespace std;

const double eps = 0.000000001;

#define DEBUG false  

struct point {
    int x,y;

    bool equals(point b){
        return ((this->x == b.x) and (this->y == b.y));
    }
};

struct Segment{
    point well, endpoint;  // first is x, second is y
};


int ccw(point a, point b, point c) {
   int temp = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
   return (temp == 0 ? 0 : (temp > 0 ? 1 : -1));
}

bool collinear(point a, point b, point c){
    double m = double(a.y - b.y) / double(a.x - b.x);
    return  (double (c.y) - double (m * double(c.x - a.x) + double(a.y)) ) < eps;
}

bool intersects(Segment a, Segment b){

    if (a.well.equals(b.well)) return false;
    if (a.endpoint.equals(b.endpoint)) return true;
    if ((ccw(a.well, a.endpoint, b.well) * ccw(a.well, a.endpoint, b.endpoint) <= 0) and (ccw(b.well, b.endpoint, a.well) * ccw(b.well, b.endpoint, a.endpoint) <= 0)){
        return true;
    }
    else
        return false;

}

int main(){

    int pipes_n, wells_n;
    cin >> wells_n >> pipes_n;

    vector<Segment> pipes(pipes_n);
    vector<point> wells(wells_n);

    for (int i = 0; i<wells_n;i++){
        cin >> wells[i].x >> wells[i].y;
    }

    for (int i =0; i<pipes_n; i++){
        int well;
        cin >> well;
        well --;        // Wells start counting from 1 :/
        cin >> pipes[i].endpoint.x >> pipes[i].endpoint.y;
        pipes[i].well.x = wells[well].x;
        pipes[i].well.y = wells[well].y;
    }

    vector<vector<int>> graph(pipes_n, vector<int>());
    for (int i = 0; i<pipes.size(); i++){
        // try to intersect it with all other pipes.
        for (int j = i+1; j<pipes.size(); j++){
            if (intersects(pipes[i], pipes[j])){
                // Fill edge in graph
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    vector<bool> visited(pipes_n, false);
    vector<int> color(pipes_n, -1);      // -1 means still not colored

    bool finish = false;
    for (int i =0 ; i<pipes_n && !finish; i++){
        if (!visited[i]){
            queue<int> q;
            q.push(i);
            color[i] = 1;     // 1 is black, 0 is white
            while(!q.empty() && !finish){
                int node = q.front();
                if (DEBUG)
                    cout << node << endl;
                q.pop();
                visited[node] = true;
                int my_color = color[node];
                int other_color = my_color == 1 ? 0 : 1;

                for (int j = 0; j<graph[node].size(); j++){
                    int adj = graph[node][j];
                    if (color[adj] == my_color){
                        finish = true;       // We lost
                        if (DEBUG)
                            cout << "lost with " << adj << endl;
                    }
                    else if (color[adj] == -1){
                        // we should color it using othercolor.
                        color[adj] = other_color;
                        q.push(adj);
                    }
                    // Else the color is ok and we have already put the adj node in the queue. Do nothing
                }
            }
        }
    }

    if (!finish)
        cout << "possible" << endl;
    else
        cout << "impossible" << endl;
    
    return 0;
}