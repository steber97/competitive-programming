#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include <algorithm>
#include <queue>

using namespace std;

class Building{
public:
    int x,y,latency,speed,id;
    Building(int x, int y, int latency, int speed, int id)
    {
        this->x = x;
        this->y = y;
        this->latency = latency;
        this->speed = speed;
        this->id = id;
    }
    Building(){};
};

class Antenna{
    public:
    int range, speed, id;
    Antenna(int range, int speed, int id)
    {
        this->range = range;
        this->speed = speed;
        this->id = id;
    }
    Antenna(){};
};

class AntennaPlaced{
    public:
    Antenna* antenna;
    int x,y;
    AntennaPlaced(Antenna* antenna, int x, int y)
    {
        this->antenna = antenna;
        this->x = x;
        this->y = y;
    }
    AntennaPlaced(){};
};

class Solution{
    public:
    vector<AntennaPlaced*> antennas_placed;
    void print_solution(){
        cout << antennas_placed.size() << endl;
        for (int i = 0; i < antennas_placed.size(); i++)
        {
            cout << antennas_placed[i]->antenna->id << " " <<
                     antennas_placed[i]->x << " " <<
                     antennas_placed[i]->y << endl;
        }
    }
};

bool sort_antennas_by_speed(Antenna* a1, Antenna* a2)
{
    return a1->speed > a2->speed;
}

bool sort_building_by_speed(Building* b1, Building* b2)
{
    return b1->speed > b2->speed;
}

int main(){
    int W, H;
    cin >> W >> H;
    int N, M, R;
    cin >> N >> M >> R;
    vector<Building*> buildings(N);
    for (int i = 0; i < N; i++){
        int x, y, latency, speed;
        cin >> x >> y >> latency >> speed;
        buildings[i] = new Building(x, y, latency, speed, i);
    }
    vector<Antenna*> antennas(M);
    for (int i = 0; i<M; i++){
        int speed, range;
        cin >> range >> speed;
        antennas[i] = new Antenna(range, speed, i);
    }


    // Solution 1
    Solution s;
    // map y, x
    int houses_per_antenna = N / M;
    sort(antennas.begin(), antennas.end(), sort_antennas_by_speed);
    vector<Building*> buildings_sorted(buildings);
    sort(buildings_sorted.begin(), buildings_sorted.end(), sort_building_by_speed);
    unordered_map<int, unordered_set<int>> antennas_positions;
    vector<bool> building_served(buildings.size(), false);
    int antenna_index = 0;
    vector<vector<bool>> map_covered(H, vector<bool>(W, false));
    vector<vector<int>> buildings_on_map(H, vector<int>(W, -1));
    for (int i = 0; i < buildings.size(); i++){
        buildings_on_map[buildings[i]->y][buildings[i]->x] = buildings[i]->id;
    }
    for (int i = 0; i < buildings_sorted.size(); i++){
        if (antenna_index == antennas.size())
            break;
        if (!building_served[buildings_sorted[i]->id]){
            s.antennas_placed.push_back(
                new AntennaPlaced(antennas[antenna_index], buildings_sorted[i]->x, buildings_sorted[i]->y));
            
            // position y, x
            queue<pair<int,int>> q;
            q.push({buildings_sorted[i]->y, buildings_sorted[i]->x});
            while(!q.empty()){
                pair<int, int> pos = q.front(); 
                q.pop();
                map_covered[pos.first][pos.second] = true;
                if (buildings_on_map[pos.first][pos.second] != -1){
                    // we have a building here!
                    building_served[buildings_on_map[pos.first][pos.second]] = true;
                }
                for(int k = -1; k < 2; k++){
                    for (int l = -1; l < 2; l++){
                        if (pos.first + k >= 0 && pos.first + k < H && pos.second + l >= 0 && pos.second + l < W){
                            if ((!map_covered[pos.first + k][pos.second + l]) && 
                                    (abs(pos.first + k - buildings_sorted[i]->y) + abs(pos.second + l - buildings_sorted[i]->x) <= antennas[antenna_index]->range)){
                                map_covered[pos.first + k][pos.second + l] = true;
                                q.push({pos.first + k, pos.second + l});
                            }
                        }
                    }
                }
            }
            antenna_index++;
        }
    }
    s.print_solution();
    return 0;
}