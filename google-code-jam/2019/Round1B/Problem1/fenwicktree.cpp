#include <iostream>
#include <vector>
#include <string>

using namespace std;
int LSOne(int b){
    return b & (-b);
}

class FenwickTree{
    private:
        vector<int> ft;
    public:
        FenwickTree(int n){
            ft.assign(n+1, 0);
        }

        int rsq(int b){
            int sum = 0;
            for (; b; b -= LSOne(b)){
                sum += ft[b];
            }
            return sum;
        }

        int rsq(int a, int b){
            if (a == 1)
                return rsq(b);
            return rsq(b) - rsq(a-1);
        }
        void adjust (int k, int v){
            for (; k<int(ft.size()); k += LSOne(k)){
                ft[k] += v;
            }
        }
        void print_fenwick_tree(){
            for (int i = 0; i<ft.size(); i++)
                cout << ft[i] << " ";
            cout << endl;
        }
};


int main(){

    int T;
    cin >> T;
    for (int t = 1; t<=T; t++){
        int N, Q;
        cin >> N >> Q;
        FenwickTree ns_ft(Q+1);
        FenwickTree ew_ft(Q+1);

        for (int i = 0; i<N; i++){
            int posx, posy;
            char orient;
            cin >> posx >> posy >> orient;
            posx++;
            posy++;
            
            if (orient == 'N'){
                if (posy <= Q)
                    ns_ft.adjust(posy+1, 1);
            }

            if (orient == 'S'){
                if(posy > 1){
                    ns_ft.adjust(1, 1);
                    ns_ft.adjust(posy, -1);
                }
            }

            if (orient=='E'){
                if (posx <= Q)
                    ew_ft.adjust(posx+1, 1);
            }

            if (orient == 'W'){
                if (posx > 1){
                    ew_ft.adjust(1, 1);
                    ew_ft.adjust(posx, -1);
                }
            }
            
        }

        int max_y = 0;
        int posy_max = 0;
        for (int i = 1; i<=Q+1; i++){
            int temp = ns_ft.rsq(i);
            if (temp > max_y){
                max_y = temp;
                posy_max = i-1;
            }
        }

        int max_x = 0;
        int posx_max = 0;
        for (int i = 1; i<=Q+1; i++){
            int temp = ew_ft.rsq(i);
            if (temp > max_x){
                max_x = temp;
                posx_max = i-1;
            }
        }
        cout << "Case #"<< t << ": " << posx_max << " " << posy_max << endl;
    }
    return 0;
}