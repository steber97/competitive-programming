//#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

ifstream cin ("input.txt");
ofstream cout ("output.txt");

vector <int> TroubleSort(vector<int> L){ 
    bool done = false;
    while (!done){
      done = true;
      for (int i = 0; i < L.size()-2; i++){
        if (L[i] > L[i+2]){
          done = false;
          int temp = L[i];
          L[i] = L[i+2];
          L[i+2] = temp;
        }
      }
    }
    return L;
}

int main(){
    int test_cases;
    cin >> test_cases;

    for (int i = 0; i<test_cases; i++){
        int len_of_list;
        cin>> len_of_list;
        vector<int> list_to_order;

        for (int j = 0; j<len_of_list; j++){
            int temp;
            cin >> temp;
            list_to_order.push_back(temp);
        }
        list_to_order = TroubleSort(list_to_order);
        for (int i = 0; i<list_to_order.size(); i++){
          cout << list_to_order[i] << "\t";
        }
        cout << endl << endl;
       
    }
    return 0;
}


