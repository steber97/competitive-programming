#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>

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
    unordered_map<int, unordered_set<int>> positions_antennas;
    for (int i = 0; i < M; i++)
    {
        while(true)
        {
            int x = int(rand() % W);
            int y = int(rand() % H);
            assert(x >= 0 && x < W);
            assert(y >= 0 && y < H);
            if (positions_antennas.find(y)==positions_antennas.end() || 
                    positions_antennas[y].find(x) == positions_antennas[y].end()){
                s.antennas_placed.push_back(new AntennaPlaced(antennas[i], x, y));
                if (positions_antennas.find(y) == positions_antennas.end())
                    positions_antennas[y] = unordered_set<int>();
                positions_antennas[y].insert(x);
                break;
            }
            
        }
    }
    s.print_solution();
    return 0;
}