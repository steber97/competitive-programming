
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream in ("input");
ofstream out ("output");

struct activity {
    int start;
    int finish;
    bool j;
};



void get_input(pair<int, int> *att_c, pair< int, int> *att_j, int & Ac, int & Aj, int& tot_c, int& tot_j);
bool compare_activities_starting_hour(pair<int, int>, pair<int, int>);
void generate_total_activity(activity * total_activity, pair<int, int> *att_c, pair<int, int> *att_j, int Ac, int Aj);
void generate_list_equal(vector<int>& equal_c, vector<int>& equal_j, activity* total_activity, int Ac, int Aj, int & total_different_consecutive);
void print_equal(vector<int> equal_vect);
void print_att(pair<int, int> *att, int len);
void print_activity(activity* total_activity, int Ac, int Aj);
void calculate_equal(int & num_of_equal, vector <int> equal_vect, int tot_remaining);
bool test_total_activity(activity * total_activity, int Ac, int Aj);

int main(){

    int T;
    in >> T;

    for (int q = 1; q <= T; q++){
        int Ac, Aj;
        in >> Ac >> Aj;
        pair <int, int> att_c[Ac];
        pair<int, int> att_j[Aj];
        int tot_j = 720, tot_c = 720;
        get_input(att_c, att_j, Ac, Aj, tot_c, tot_j);


        /// Order activities per starting hour.
        sort(att_c, att_c + Ac, compare_activities_starting_hour);
        sort(att_j, att_j + Aj, compare_activities_starting_hour);

        //print_att(att_c, Ac);
        //print_att(att_j, Aj);

        activity total_activity[Ac + Aj];
        generate_total_activity(total_activity, att_c, att_j, Ac, Aj);

        /*
        if (!test_total_activity(total_activity, Ac, Aj)){
            return 25;
        }
         */
        //print_activity(total_activity, Ac, Aj);

        int total_different_consecutive = 0;
        vector<int> equal_c;
        vector<int> equal_j;

        generate_list_equal(equal_c, equal_j, total_activity, Ac, Aj, total_different_consecutive);
        sort(equal_c.begin(), equal_c.begin() + equal_c.size() );
        sort(equal_j.begin(), equal_j.begin() + equal_j.size() );

        //print_equal(equal_c);
        //print_equal(equal_j);

        int num_of_equal_c = equal_c.size();
        int num_of_equal_j = equal_j.size();

        calculate_equal(num_of_equal_c, equal_c, tot_c);
        calculate_equal(num_of_equal_j, equal_j, tot_j);

        //out << "tot_j= " << tot_j << endl;
        //out << "tot_c= " << tot_c << endl;
        //out << "total_different_consecutive= " << total_different_consecutive << endl;

        out << "Case #" << q <<": " << total_different_consecutive + num_of_equal_c * 2 + num_of_equal_j * 2 << endl;

    }

    return 0;
}

void get_input(pair<int, int>  *att_c, pair<int, int>  *att_j, int & Ac, int & Aj, int& tot_c, int& tot_j){
    /// returns the number of remaining C and J minutes available.
    for (int i = 0; i<Ac; i++){
        int start, finish;
        in >> start >> finish;
        att_c[i] = make_pair(start, finish);
        tot_c -= (att_c[i].second - att_c[i].first);
    }
    for (int j = 0; j<Aj; j++){
        int start, finish;
        in >> start >> finish;
        att_j[j] = make_pair(start, finish);
        tot_j -= (att_j[j].second - att_j[j].first);
    }
}

bool compare_activities_starting_hour(pair<int, int> el1, pair<int, int> el2){
    return el1.first < el2.first;
}

void generate_total_activity(activity * total_activity, pair<int, int>* att_c, pair<int, int>* att_j, int Ac, int Aj){
    int pos_r_c = 0, pos_r_j = 0;
    for (int i = 0; i<Ac + Aj; i++){
        if (pos_r_c < Ac && pos_r_j < Aj){
            if (att_c[pos_r_c].first < att_j[pos_r_j].first){
                // insert activity C
                total_activity[i].j = false;
                total_activity[i].start = att_c[pos_r_c].first;
                total_activity[i].finish = att_c[pos_r_c].second;
                pos_r_c ++;
            }
            else {
                // insert activity J
                total_activity[i].j = true;
                total_activity[i].start = att_j[pos_r_j].first;
                total_activity[i].finish = att_j[pos_r_j].second;
                pos_r_j ++;
            }
        }
        else if (pos_r_c >= Ac) {
            // insert activity J
            total_activity[i].j = true;
            total_activity[i].start = att_j[pos_r_j].first;
            total_activity[i].finish = att_j[pos_r_j].second;
            pos_r_j ++;
        }
        else {
            // insert activity J
            total_activity[i].j = false;
            total_activity[i].start = att_c[pos_r_c].first;
            total_activity[i].finish = att_c[pos_r_c].second;
            pos_r_c ++;
        }

    }
}

void generate_list_equal(vector<int>& equal_c, vector<int>& equal_j, activity* total_activity, int Ac, int Aj, int & total_different_consecutive){
    for (int i = 0; i < Ac + Aj; i++){
        int next = (i + 1) % (Ac + Aj);
        /*
        if (next >= Ac + Aj){
            exit(21);
        }
        */
        if (total_activity[i].j == total_activity[next].j){
            // If two consecutive activities are both of the same person:
            if (total_activity[i].j){
                // fill J
                equal_j.push_back((total_activity[next].start - total_activity[i].finish) >= 0?
                                  (total_activity[next].start - total_activity[i].finish) :
                                  (total_activity[next].start - total_activity[i].finish) + (1440));
            }
            else {
                // fill C
                equal_c.push_back((total_activity[next].start - total_activity[i].finish) >= 0?
                                  (total_activity[next].start - total_activity[i].finish) :
                                  (total_activity[next].start - total_activity[i].finish) + (1440));
            }
        }
        else {
            total_different_consecutive ++;
        }
    }
    /*
    if (total_different_consecutive + equal_c.size() + equal_j.size() != Ac + Aj){
        exit(22);
    }
    */
}

void print_equal(vector<int> equal_vect){
    for (int i = 0; i<equal_vect.size(); i++){
        out << equal_vect[i] << "\t";
    }
    out << endl;
}

void print_att(pair<int, int> *att, int len){
    for (int i = 0; i<len; i++){
        out << att[i].first << "\t" << att[i].second << endl;
    }
    out << endl;
}

void print_activity(activity* total_activity, int Ac, int Aj){
    for (int i = 0; i<Ac + Aj; i++){
        out << total_activity[i].start << "\t" << total_activity[i].finish << "\t" << total_activity[i].j << endl;
    }
    out << endl;
}

void calculate_equal(int & num_of_equal, vector <int> equal_vect, int tot_remaining){
    int i = 0;
    while(tot_remaining >= 0 && i < equal_vect.size()){
        if (tot_remaining - equal_vect[i] >= 0){
            num_of_equal --;
            tot_remaining -= equal_vect[i];
            i++;
        }
        else {
            tot_remaining -= equal_vect[i];
        }
    }

    //out << "equal gaps remaining= " << num_of_equal << endl;
}

bool test_total_activity(activity * total_activity, int Ac, int Aj){
    int attj = 0, attc = 0;
    int last_start = -1;
    bool res = true;
    for (int i = 0; i<Ac + Aj; i++){
        if (total_activity[i].j){
            attj ++;
        }
        else{
            attc++;
        }
        if (i >= 1){
            if (total_activity[i].start <= total_activity[i-1].start or total_activity[i].start < total_activity[i-1].finish){
                res = false;
            }
        }

    }
    if (attj != Aj or attc != Ac){
        res = false;
    }
    return res;
}