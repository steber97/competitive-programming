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
        this->partial_sum_fragments[0] = this->fragments[0];
        for (int i = 1; i < this->fragments.size(); i++){
            this->partial_sum_fragments[i] = this->partial_sum_fragments[i-1] + this->fragments[i];
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
    Demon* demon;
    int turn;
};

void get_input(vector<Demon*>& demons, Pandora* pandora, int& turns, int& demons_number){
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
}

int main(){
    vector<Demon*> demons;
    Pandora* pandora;
    int turns;
    int demons_number;
    get_input(demons, pandora, turns, demons_number);
    
    
    return 0;
}