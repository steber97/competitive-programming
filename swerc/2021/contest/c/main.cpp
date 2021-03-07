#include  <bits/stdc++.h>
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp> 
// #include <ext/pb_ds/tree_policy.hpp> 
 
// using namespace __gnu_pbds;
 
#define mp make_pair
#define fi first
#define se second
#define all(v) v.begin(),v.end()
#define allarr(a) a , a + n
#define ll long long
#define ull unsigned long long 
#define pb push_back
#define fastio ios_base::sync_with_stdio(false) ; cin.tie(NULL); cout.tie(NULL)
#define sz(x)  (int)x.size() 
typedef pair<int, int> pi;
typedef pair<double,double> pd; 
typedef pair<ll,ll> pll; 
typedef pair<int,pi> trp ;
typedef vector<pi> vpi;
typedef vector<pll> vpll ;

const int MAXN = 1005 ;
const double eps = 1e-7; 

pd mid(pd a , pd b ){
  return (pd){(a.fi+b.fi)/2.0,(b.se+a.se)/2.0}; 
}

double dist(pd a , pd b){
  return sqrt( ( a.fi - b.fi )*( a.fi - b.fi ) + ( a.se - b.se )*( a.se - b.se ) ) ; 
}

bool intersect(pd a,pd b,double  r){
    // Modify this
  return (dist(a,b) < r*2.0) && (abs(dist(a,b) - r*2.0) > eps) ;
}
int par [1005];
int find_set(int u){
    if( par[u] == u )return u ;
    return par[u]=find_set(par[u]);
}
void union_set(int u , int v ){
    u = find_set(u);
    v = find_set(v);
    if( u != v ) 
    par[u] = v;
}
int main(){
  int N ; 
  double end_x , end_y ; 
  cin >> end_x >> end_y ;   
  cin >> N ; 

  vector<pd> pts ; 

  for(int i = 0 ; i < N ; i++ ){
    double x , y ; 
    cin >> x >> y ;
    pts.pb({x,y}) ;
  }


  double l = 0 , r  = 2e6 , ans = -1e9 ; 

  while ( abs(r-l) > eps ){
    double ra = ( l + r ) / 2.0 ;

    for(int i=0;i<N;i++){
      par[i] = i ; 
    }


    for(int i = 0 ; i < N ; i++ ){
      for(int j = i + 1 ; j < N ; j++ ){
        if( intersect(pts[i],pts[j],ra) ){
          union_set(i,j); 
        }
      }
    }

    bool no_sol = 0;
    for(int i = 0 ; i < N ; i++ ){
      set<int> s; 
      for(int j = 0 ; j < N ; j++ ){
        if(find_set(j)==i){
            // Modify this
          if( (end_y - pts[j].se < ra) && (abs(end_y - pts[j].se - ra) > eps ) )s.insert(1); 
          if( (pts[j].se < ra) && (abs(pts[j].se - ra) > eps) )s.insert(3); 
          if( (pts[j].fi < ra) && (abs(pts[j].fi - ra) > eps) )s.insert(2); 
          if( (end_x - pts[j].fi < ra) && (abs(end_x - pts[j].fi - ra) > eps) )s.insert(4); 
        }    
      }

      //  1_
      // 2|  |4
      //    3
      //
      if( s.count(1) + s.count(4) == 2 || s.count(2)+s.count(3) == 2 || s.count(1)+s.count(3)==2 || s.count(2)+s.count(4)==2){
        no_sol = 1 ; 
        break ;   
      }
    }
    if( no_sol ){
      r = ra ; 
    }else{
      l = ra  ; 
      ans = ra ; 
    }

  }
  cout << setprecision(6) << fixed << ans << endl; 

}