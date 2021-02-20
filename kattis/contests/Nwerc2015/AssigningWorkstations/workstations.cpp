#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define DEBUG false

bool compare_my(pair<int,int> p1, pair<int,int> p2){
    return p1.first < p2.first;
}

int main(){
    int N, E;
    cin >> N >> E;

    vector<pair<int,int>> workers(N);
    for (int i = 0; i<N; i++){
        cin >> workers[i].first >> workers[i].second;
    }

    sort(workers.begin(), workers.end(), compare_my);
    priority_queue<int, vector<int>, ::greater<int> > pq;
    int activations = 0;
    for (int i = 0; i<N; i++){
        if (DEBUG) cout << workers[i].first << " " << workers[i].second << endl;
        bool served = false;
        while(!served){
            if (DEBUG) cout << (pq.empty() ? -1 : pq.top()) << endl;
            // serve all workers.
            if (pq.empty()){
                // if the pq is empty, then we are obliged to assign manually the workstation.
                pq.push(workers[i].first + workers[i].second + E);
                activations ++;
                served = true;
            }
            else if (pq.top() - E > workers[i].first){
                pq.push(workers[i].first + workers[i].second + E);
                served = true;
                activations ++;
            }
            else if (workers[i].first <= pq.top() && workers[i].first >= pq.top()-E ){
                pq.pop();
                pq.push(workers[i].first + workers[i].second + E);
                served = true;
            }
            else {
                // Means that the current top is useless
                pq.pop();
            }
        }
    }

    cout << N - activations << endl;

    return 0;
}