#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>


using namespace std;
bool DEBUG = false;

class SegmentTree{
    private:
        vector<long long > A, st;
        int n;
        // to get right and let children in a heap fashion.
        int left(int p){
            return p * 2;
        }
        int right(int p){
            return p*2 + 1;
        }

        void build(int p, int l, int r){
            if (l > r){

            }
            else if (l == r){
                st[p] = l;
            }
            else{
                build(left(p), l, (l+r)/2);
                build(right(p), (l+r)/2 + 1, r);
                if (A[st[left(p)]] > A[st[right(p)]]){
                    st[p] = st[left(p)];
                }
                else{
                    st[p] = st[right(p)];
                }
            }
        }

        int rmq(int p, int l, int r, int i, int j){
            int res;
            if (i > r || j < l){
                // If out of range:
                res = -1;
            }
            else{
                if (l >=  i && r <= j){
                    res = st[p];
                }
                else{
                    int p1 = rmq(left(p), l, (l+r) / 2, i, j);
                    int p2 = rmq(right(p), (l+r)/2 + 1, r, i, j);
                    if (p1 == -1)
                        res = p2;
                    else if(p2 == -1)
                        res = p1;
                    else{
                        if(A[p1] >= A[p2])
                            res = p1;
                        else    
                            res = p2;
                    }
                }
            }
            //cout << l << " " << r << " " << res << endl;
            return res;
        }

    public:
        int rmq (int i, int j){
            return rmq(1, 0, n-1, i, j); 
        }


        void print_st(){
            for (int i: st){
                cout << i << " ";
            }
            cout << endl;
        }

        SegmentTree(const vector<long long> & vect){
            n = vect.size();
            A = vect;
            st.assign(4*n, 0);
            // Position 0 will always left empty in the st.
            build(1, 0, n-1);
            //print_st();
        }

};

int main(){

    int T;
    cin >> T;
    for (int t = 1; t<=T; t++){
        int N, K;
        cin >> N >> K;
        vector<long long> knight1(N);
        vector<long long> knight2(N);
        for (int i = 0; i<N; i++){
            cin >> knight1[i];
        }
        for (int i = 0; i<N; i++){
            cin >> knight2[i];
        }

        SegmentTree st1 (knight1);

        SegmentTree st2 (knight2);

        
        int result = 0;
        
        for (int i = 0; i<N; i++){
            for (int j = i; j<N; j++){
                int rmq1 = knight1[st1.rmq(i,j)];
                int rmq2 = knight2[st2.rmq(i,j)];

                //cout << rmq1 << " " << rmq2 << " " << i << " " << j << endl;

                if (abs(rmq1 - rmq2) <= K){
                    result ++;
                }
            }

        }
        
        cout << "Case #" << t << ": " << result << endl;
    }
    return 0;
}