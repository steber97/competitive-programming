#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include <algorithm>

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
    sort(buildings.begin(), buildings.end(), sort_building_by_speed);
    unordered_map<int, unordered_set<int>> antennas_positions;
    for (int i = 0, antenna_counter=0; i < M; i++,antenna_counter++)
    {
        long x = 0;
        long y = 0;
        int j;
        int counter = 0;
        for (j = i * houses_per_antenna; j < min((i+1) * houses_per_antenna, N); j++)
        {
            counter++;
            x += buildings[j]->x;
            y += buildings[j]->y;
        }
        x /= counter;
        y /= counter;
        if (antennas_positions.find(x)==antennas_positions.end() || antennas_positions[x].find(y)==antennas_positions[x].end()){
            s.antennas_placed.push_back(
                new AntennaPlaced(antennas[antenna_counter], x, y));
            if (antennas_positions.find(x)==antennas_positions.end())
                antennas_positions[x] = unordered_set<int>();
            antennas_positions[x].insert(y);
        }
        else{
            antenna_counter--;
        }
    }
    s.print_solution();
    return 0;
}