#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;

class Demon{
public: 
    int stamina_consumed;
    int turns_to_wait;
    int stamina_recovered;
    int turns_fragments;
    vector<int> fragments;
    vector<int> partial_sum_fragments;
    int id;

    Demon(){}

    Demon(int stamina_consumed, int turns_to_wait, int stamina_recovered, int turns_fragments, vector<int>& fragments, int id){
        this->stamina_consumed = stamina_consumed;
        this->turns_to_wait = turns_to_wait;
        this->stamina_recovered = stamina_recovered;
        this->turns_fragments = turns_fragments;
        this->fragments = vector<int>(fragments);
        this->id = id;
        this->partial_sum_fragments = vector<int>(this->fragments.size());
        if (this->fragments.size() > 0){
            this->partial_sum_fragments[0] = this->fragments[0];
            for (int i = 1; i < this->fragments.size(); i++){
                this->partial_sum_fragments[i] = this->partial_sum_fragments[i-1] + this->fragments[i];
            }
        }
    }

    void print_demon(){
        cout << "Demon " << this->id << ": Sc " << this->stamina_consumed << ", Tr: " << this->turns_to_wait << " Sr: " << this->stamina_recovered << endl;
        for (int i = 0; i < this->fragments.size(); i++) {
            cout << fragments[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < this->fragments.size(); i++) {
            cout << partial_sum_fragments[i] << " ";
        }
        cout << endl;
    }
};

class Pandora {
public:
    int stamina;
    int max_stamina;
    Pandora(int stamina, int stamina_max){
        this->stamina = stamina;
        this->max_stamina = stamina_max;
    }
};

class DemonChallenged {
    public:
        Demon* demon;
        int turn;
        DemonChallenged(Demon* demon, int turn){
            this->demon = demon;
            this->turn = turn;
        };
};

// class DemonCompare
// {
// public:
//     int turn;
//     int max_turn;
//     DemonCompare(int turn, int max_turn){
//         this->turn = turn;
//         this->max_turn = max_turn;
//     };
//     bool operator()(const Demon* d1, const Demon* d2) {
//         if (d1->partial_sum_fragments.size() > 0 && d2->partial_sum_fragments.size() > 0){
//             int p1 = d1->partial_sum_fragments.size() - 1;
//             int p3 = d2->partial_sum_fragments.size() - 1;
//             int p2 = this->max_turn - this->turn;
//             assert ( min(p1, p2) < d1->partial_sum_fragments.size() && min(p1, p2) >= 0);
//             assert ( min(p3, p2) < d2->partial_sum_fragments.size() && min(p3, p2) >= 0);
//             // cout << p1 << " " << p2 << " " << p3 << " " << d1->partial_sum_fragments.size() <<  " " << d2->partial_sum_fragments.size() << endl;
//             // cout << d1->partial_sum_fragments.at(min(p1, p2)) << endl;
//             // cout << d2->partial_sum_fragments.at(min(p3, p2)) << endl;
//             return d1->partial_sum_fragments.at(min(p1, p2)) > d2->partial_sum_fragments.at(min(p3, p2));
//         }
//         else if (d1->partial_sum_fragments.size() > 0){
//             return true;
//         }
//         else if (d2->partial_sum_fragments.size() > 0){
//             return false;
//         }
//         return true;
//     };///This would handle the comparison using the is_case_sensitive flag
    
// };

int turns;
int actual_turn;
bool compare_demons(Demon* d1, Demon* d2){
    if (d1->partial_sum_fragments.size() > 0 && d2->partial_sum_fragments.size() > 0){
        int p1 = d1->partial_sum_fragments.size() - 1;
        int p3 = d2->partial_sum_fragments.size() - 1;
        int p2 = turns - actual_turn;
        return d1->partial_sum_fragments.at(min(p1, p2)) / float(d1->stamina_consumed+1.0) >
         d2->partial_sum_fragments.at(min(p3, p2)) / (float(d2->stamina_consumed+1.0));
    }
    else if (d1->partial_sum_fragments.size() > 0){
        return true;
    }
    else if (d2->partial_sum_fragments.size() > 0){
        return false;
    }

    return d1->id < d2->id;
}

void get_input(vector<Demon*>& demons, Pandora* pandora, int& turns, int& demons_number){
    
}

int main(){

    vector<Demon*> demons;

    Pandora* pandora;
    int demons_number;
    int stamina_init, stamina_max;
    cin >> stamina_init >> stamina_max >> turns >> demons_number;
    pandora = new Pandora(stamina_init, stamina_max);
    
    for (int i = 0; i < demons_number; i++){
        int stamina_consumed, turns_recover, stamina_recovered, number_of_fragments;
        cin >> stamina_consumed >> turns_recover >> stamina_recovered >> number_of_fragments;
        vector<int> fragments(number_of_fragments);
        
        for (int j = 0; j < number_of_fragments; j++){
            cin >> fragments[j];
        }
        
        demons.push_back(new Demon(stamina_consumed, turns_recover, stamina_recovered, number_of_fragments, fragments, i));
    }
    
    
    actual_turn = 0;
    int demon_iterator = 0;
    vector<DemonChallenged*> solution;
    vector<bool> demon_taken(demons.size(), false);
    int demons_taken_count = 0;
    vector<bool> demons_taken(demons.size(), false);
    vector<int> stamina_recovered_per_turn(turns, 0);
    
    while(actual_turn < turns){
        sort(demons.begin(), demons.end(), compare_demons);
        pandora->stamina += stamina_recovered_per_turn.at(actual_turn);
        pandora->stamina = min(pandora->max_stamina, pandora->stamina);
        for (int i = 0; i < demons.size(); i++){
            if (!demons_taken.at(demons[i]->id)){
                if (demons[i]->stamina_consumed <= pandora->stamina){
                    demons_taken.at(demons[i]->id) = true;
                    solution.push_back(new DemonChallenged(demons[i], actual_turn));
                    if (actual_turn + demons[i]->turns_to_wait < stamina_recovered_per_turn.size())
                        stamina_recovered_per_turn[actual_turn + demons[i]->turns_to_wait] += demons[i]->stamina_recovered;
                    break;
                }
            }
        }
        actual_turn++;
        if (actual_turn % 1000 == 0)
            cerr << actual_turn << endl;
    }

    for (int i = 0; i < solution.size(); i++)
        cout << solution[i]->demon->id << endl;
    return 0;
}