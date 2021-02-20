//#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

ifstream cin ("input.txt");
ofstream cout ("output.txt");

class list_of_values{
    public:
        bool S;
        int val;
        int cardinality;
        list_of_values* next;
        list_of_values* prev;
};

void print_list_compact(list_of_values* tail){
    list_of_values* temp = tail;
    cout << "Printing list_compact: " << endl;
    while(temp != NULL){
        cout << "S: " << temp->S << endl;
        cout << "card: " << temp->cardinality << endl;
        cout << "val: " <<temp->val << endl << endl;
        temp = temp->prev;
    }
}

pair<list_of_values*, int> create_command_list_compact(string list_of_commands, list_of_values* tail, int damage_to_resist){
    list_of_values* head;
    head = tail;
    int value = 1;
    int min_damage_made = 0;
    int damage_made = 0;
    char last_char_seen = list_of_commands[0];
    for (int i=0; i<list_of_commands.size(); ){
        int counter = 0;
        list_of_values* temp = new list_of_values();
        while(list_of_commands[i] == last_char_seen && i<list_of_commands.size()){
            i++;
            counter++;
        }
        
        temp->S = list_of_commands[i-1] == 'S'? true : false;
        
        value = (!temp->S)? value * pow(2, counter) : value;
        temp->val = value;
        temp->cardinality = counter;
        temp->prev = head;
        temp->next = NULL;
        if (temp->S){
            damage_made += temp->cardinality * temp->val;
            min_damage_made += temp->cardinality;
        }
        if (i < list_of_commands.size()){
            last_char_seen = list_of_commands[i];
        }
        
        if (head == NULL){
            tail = temp;
            head = temp;
            tail->prev = NULL;
        }
        else {
            head-> next = temp;
        }
        head = temp;
    }

    if (min_damage_made > damage_to_resist){
        // If the result is IMPOSSIBLE, then return NULL as the head.
        list_of_values* temp = NULL;
        return make_pair(temp, damage_made);
    }
    else {
        return make_pair(head, damage_made);
    }
}

int solve(list_of_values* tail, const int damage_to_resist, int damage_made){
    int res = 0;
    list_of_values* actual_pos = tail;
    // if damage_made == damage_to_resist we survive.
    //cout << "damage_made: " << damage_made << endl;
    //cout << "damage_to_resist: " << damage_to_resist << endl;
    
    while(damage_made > damage_to_resist){
        if (actual_pos->S){
            int total_gain_with_1_step = (actual_pos->cardinality * actual_pos->val) / 2;
            if (damage_made - total_gain_with_1_step <= damage_to_resist){
                // decide how many S should be changed place.
                
                res += ceil(double (double(damage_made - damage_to_resist) / (actual_pos->val / 2)));
                damage_made = 0;
            }
            else{
                // move every S by 1 C.
                damage_made -= (actual_pos->cardinality * actual_pos->val) / 2;
                actual_pos->prev->cardinality --;
                actual_pos->prev->val /= 2;
                actual_pos->val /= 2;
                res += actual_pos->cardinality;
                if (actual_pos->prev->cardinality == 0){
                    actual_pos->prev->prev->cardinality += actual_pos->cardinality;
                    actual_pos = actual_pos->prev->prev;
                    if (actual_pos == NULL){
                        damage_made = 0;
                    }
                    else {
                        delete(actual_pos->next->next);
                        delete(actual_pos->next);
                    }
                    
                }
            }
        }
        else{
            actual_pos = actual_pos->prev;
        }
        //print_list_compact(actual_pos);
        //cout << "damage_made: " << damage_made << endl;
        //cout << "damage_to_resist: " << damage_to_resist << endl;
        //cout << "damage_made: " << damage_made << endl;
        
    }
    
    return res;
}

int main(int argc, char** argv){

    int test_cases;
    cin >> test_cases;
    for(int i = 0; i<test_cases; i++){
        int damage_to_resist;
        string list_of_commands;
        list_of_values* tail = NULL;
        cin >> damage_to_resist;
        cin >> list_of_commands;
        //cout << list_of_commands << endl;
        int total_damage_made;
        // The function actually returns the head, in this way we turn the list from bottom to top.
        pair<list_of_values*,int> my_pair = create_command_list_compact(list_of_commands, tail, damage_to_resist);
        tail = my_pair.first;
        total_damage_made = my_pair.second;
        //print_list_compact(tail);
        //cout << total_damage_made << endl;

        if (tail == NULL){
            cout << "Case #" << i+1 << ": IMPOSSIBLE"<< endl;
        }
        else{
             int res = solve(tail, damage_to_resist, total_damage_made);
             cout << "Case #" << i+1 << ": " << res << endl;
        }
       
        
    }
    return 0;
}