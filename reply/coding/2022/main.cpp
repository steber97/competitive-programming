#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

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

bool sort_demons_by_decreasing_stamina_consumed(Demon* d1, Demon* d2){
    // return d1->stamina_consumed < d2->stamina_consumed;
    if (d1->partial_sum_fragments.size() > 0 && d2->partial_sum_fragments.size() > 0){
        return (*(d1->partial_sum_fragments.end() - 1) * float(d1->stamina_recovered + 1)) / (float(d1->stamina_consumed + 1)) >
               (*(d2->partial_sum_fragments.end() - 1) * float(d2->stamina_recovered + 1)) / (float(d2->stamina_consumed + 1));
    }
    else if (d1->partial_sum_fragments.size() > 0)
        return true;
    else if (d2->partial_sum_fragments.size() > 0)
        return false;
    else {
        return 1 / float(d1->stamina_consumed + 1) > 1 / float(d2->stamina_consumed + 1);
    }
}

void get_input(vector<Demon*>& demons, Pandora* pandora, int& turns, int& demons_number){
    
}

int main(){

    vector<Demon*> demons;

    Pandora* pandora;
    int turns;
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
    
    sort(demons.begin(), demons.end(), sort_demons_by_decreasing_stamina_consumed);
    
    int actual_turn = 0;
    int demon_iterator = 0;
    vector<DemonChallenged*> solution;
    vector<bool> demon_taken(demons.size(), false);
    int demons_taken_count = 0;
    vector<bool> demons_taken(demons.size(), false);
    vector<int> stamina_recovered_per_turn(turns, 0);
    
    while(actual_turn < turns){
        pandora->stamina += stamina_recovered_per_turn[actual_turn];
        pandora->stamina = min(pandora->max_stamina, pandora->stamina);
        
        if (demons[demon_iterator]->stamina_consumed <= pandora->stamina){
            demons_taken[demon_iterator] = true;
            solution.push_back(new DemonChallenged(demons[demon_iterator], actual_turn));
            if (actual_turn + demons[demon_iterator]->turns_to_wait < stamina_recovered_per_turn.size())
                stamina_recovered_per_turn[actual_turn + demons[demon_iterator]->turns_to_wait] += demons[demon_iterator]->stamina_recovered;
            demon_iterator ++;   
        }

        if (demon_iterator >= demons.size())
            break;
        actual_turn++;
    }

    for (int i = 0; i < solution.size(); i++)
        cout << solution[i]->demon->id << endl;
    return 0;
}