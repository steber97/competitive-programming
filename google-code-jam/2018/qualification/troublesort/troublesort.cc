#include <iostream>
//#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

//ifstream cin ("input.txt");
//ofstream cout("output.txt");


int solve(vector<int> list_to_order_odd, vector<int> list_to_order_even){
    int res = -1;
    int last_even = 0;
    
    for (int i = 0; i<list_to_order_even.size() && res == -1; i++){
        if (last_even > list_to_order_odd[i]){
            res = (i-1) * 2 + 1; // even mistakes are listed as i*2 + 1.
        }
        else if(list_to_order_even[i] < list_to_order_odd[i]){
            res = (i) * 2;
        }
        last_even = list_to_order_even[i];
    }
    if (res == -1){
        if (list_to_order_odd.size() > list_to_order_even.size()){
            if (list_to_order_odd[list_to_order_odd.size()-1] < list_to_order_even[list_to_order_even.size()-1]){
                res = (list_to_order_even.size() -1) *2 + 1;
            }
        }
    }
    return res;
}

int main(int argc, char** argv){

    int test_cases;
    cin >> test_cases;

    for (int i = 0; i<test_cases; i++){
        int len_of_list;
        cin>> len_of_list;
        vector<int> list_to_order_odd;
        vector<int> list_to_order_even;

        for (int j = 0; j<len_of_list; j++){
            int temp;
            cin >> temp;
            if ((j+1)%2 == 0){
                // even number of the list.
                list_to_order_even.push_back(temp);
            }
            else {
                list_to_order_odd.push_back(temp);
            }
        }
        sort(list_to_order_odd.begin(), list_to_order_odd.end());
        sort(list_to_order_even.begin(), list_to_order_even.end()); 
        int res = solve(list_to_order_odd, list_to_order_even);

        if (res < 0){
            cout << "Case #" << i+1<<": OK" << endl;
        }
        else{
            cout << "Case #" << i+1<<": " << res << endl;
        }
    }
    return 0;
}