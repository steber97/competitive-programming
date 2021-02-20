#include <bits/stdc++.h>
#include <climits>
#include <cmath>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define COUT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

int convert_pair_to_int(ii t){
    return t.first * MODULUS + t.second;
}

bool mycompare(tuple<int,int,int,double> t1, tuple<int,int,int,double> t2){
    return get<3>(t1) < get<3>(t2);
}

void compute_best(){

}

int main(){

    int N;
    cin >> N;

    ii eve;
    cin >> eve.first >> eve.second;

    int win=0, lose=0, tied=0, second_zero_win = 0, first_zero_win = 0, first_zero_lose = 0, second_zero_lose = 0, always_win = 0, always_lose = 0;

    unordered_map<int, int> first, second;
    vii others(N-1);
    FOR(i,0,N-1){
        cin >> others[i].first >> others[i].second;
        //COUT(others[i].first); COUT(" "); COUT(others[i].second);COUT(endl);
        if (others[i].first == eve.first and others[i].second == eve.second)
            tied ++;
        else if (others[i].first >= eve.first and others[i].second >= eve.second){
            lose++;
            if (others[i].first == eve.first and others[i].second > eve.second)
                second_zero_win ++;
            else if (others[i].first > eve.first and others[i].second == eve.second)
                first_zero_win ++;
            else
                always_lose ++;
        }
        else if (others[i].first <= eve.first and others[i].second <= eve.second){
            win ++;
            if (others[i].first == eve.first and others[i].second < eve.second)
                second_zero_lose ++;
            else if (others[i].first < eve.first and others[i].second == eve.second)
                first_zero_lose ++;
            if (others[i].first < eve.first and others[i].second < eve.second)
                always_win ++;
        }
        else{
            ii y = {eve.first - others[i].first, others[i].second - eve.second};

            y = {y.first>0?y.first:-y.first, y.second>0?y.second:-y.second};
            
            int temp_gcd = __gcd(y.first, y.second);
            y = {y.first / temp_gcd, y.second / temp_gcd};
            int conv_int = convert_pair_to_int(y);
            if (eve.first > others[i].first){
                //COUT("Add to first"); COUT(endl);
                if (first.find(conv_int) == first.end())
                    first[conv_int] = 0;
                first[conv_int] ++;
            }
            else{
                //COUT("add to second"); COUT(endl);
                if(second.find(conv_int) == second.end())
                    second[conv_int] = 0;
                second[conv_int] ++;
            }
        
        }
    }
    

    vector<tuple<int,int,int,double>> first_v, second_v;
    for(pair<int,int> el: first){
        int el1 = el.first / MODULUS;
        int el2 = el.first - ( el.first/MODULUS ) * MODULUS;
        first_v.push_back(make_tuple(el1, el2, el.second, double(el1) / double(el2)));
    }


    for(pair<int,int> el: second){

        int el1 = el.first / MODULUS;
        int el2 = el.first - ( el.first/MODULUS ) * MODULUS;
        //COUT (el1); COUT(" "); COUT(el2); COUT(endl);
        second_v.push_back(make_tuple(el1, el2, el.second, double(el1) / double(el2)));
    }

    sort(first_v.begin(), first_v.end(), mycompare);
    sort(second_v.begin(), second_v.end(), mycompare);

    FOR(i,1,second_v.size()){
        get<2>(second_v[i]) = get<2>(second_v[i]) + get<2>(second_v[i-1]);
    }

    
    for(int i = first_v.size()-2; i>=0; i--){
        get<2>(first_v[i]) = get<2>(first_v[i]) + get<2>(first_v[i+1]);
    }

    FOR(i,0,first_v.size()){
        //COUT(get<3>(first_v[i])); COUT("\t"); COUT(get<2>(first_v[i])); COUT(endl);
    }
    //COUT(endl);

    FOR(i,0,second_v.size()){
        //COUT(get<3>(second_v[i])); COUT("\t"); COUT(get<2>(second_v[i]));  COUT(endl);
    }
    //COUT(endl);

    VALUE (always_win);
    VALUE(tied);
    VALUE(win);
    VALUE(first_zero_win);
    VALUE(second_zero_win);

    VALUE(first_zero_lose);
    VALUE(second_zero_lose);
    VALUE(lose);
    
    int j=0,i=0;
    int best = N-win;
    int worst = N-always_win;
    if (first_v.size() > 0 and second_v.size()>0){
        worst = 100001;
        while(i!=first_v.size() or j!=second_v.size()){
            int temp_res = 0;
            int temp_res2 = 0;
            if (i == first_v.size()){
                // first is finished
                temp_res = 0 + get<2>(second_v[j]);
                temp_res2 = 0 + (j > 0 ? get<2>(second_v[j-1]) : 0);     // we lose against the last
                j++;
            }
            else if (j == second_v.size()){
                // second is finished
                temp_res = get<2>(second_v[j-1]) + get<2>(first_v[i]);
                temp_res2 = get<2>(second_v[j-1]) + (i < first_v.size()-1 ? get<2>(first_v[i+1]) : 0);     // we lose against the last
                i++;
            }
            else{
                if(abs(get<3>(first_v[i]) - get<3>(second_v[j])) < DELTA ) {
                    // take both
                    temp_res = get<2>(first_v[i]) + get<2>(second_v[j]);
                    temp_res2 = (i  < first_v.size()-1 ? get<2>(first_v[i+1]):0) + (j>0?get<2>(second_v[j-1]):0);
                    i++; j++;
                }
                else if(get<3>(first_v[i]) <get<3>(second_v[j]) ){
                    // take i
                    temp_res = get<2>(first_v[i]) + (j > 0 ? get<2>(second_v[j-1]) : 0);
                    temp_res2 = (i<(first_v.size()-1)?get<2>(first_v[i+1]):0) + (j > 0? get<2>(second_v[j-1]) : 0);
                    i++;
                }
                else{
                    // take j
                    temp_res = get<2>(first_v[i]) + get<2>(second_v[j]);
                    temp_res2 = (i > 0 ? get<2>(first_v[i]) : get<2>(first_v[0])) + (j>0? get<2>(second_v[j-1]) : 0);
                    j++;
                }
            }
            temp_res += win + tied;
            temp_res2 += always_win + first_zero_lose + second_zero_lose;  // We lose against the tied
            //COUT(i); COUT(" "); COUT(j); COUT(" "); COUT(temp_res); COUT (" "); COUT(temp_res2); COUT (endl);
            best = min(best, N-temp_res); 
            worst = min(worst, temp_res2);
            

        }
        worst = N - worst;
    }

    else if (second_v.size() != 0){
        best = min(best, N - get<2>(second_v[0]) - win - tied);
        worst = N - win;
    }
    else if (first_v.size() != 0){
        best = min(best, N - get<2>(first_v[first_v.size()-1]) - win - tied);
        worst = N - win;
    }

    // try to put the first to zero

    COUT(worst);COUT(endl);
    
    best = min(best, N - first_zero_win - (second_v.size() > 0? get<2>(second_v[second_v.size()-1]) : 0) - tied - win );
    worst = max(worst, first_zero_lose + (first_v.size()>0?get<2>(first_v[0]):0) + tied + lose + 1);
    

    // try to put second to zero
    best = min(best, N - second_zero_win - (first_v.size() > 0 ? get<2>(first_v[0]) : 0) - tied - win);
    worst = max(worst, second_zero_lose + (second_v.size()>0?get<2>(second_v[second_v.size()-1]): 0) + tied + lose + 1);
    
    cout << best << " " << worst <<endl;

    return 0;
}