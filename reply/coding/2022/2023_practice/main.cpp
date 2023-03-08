#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


using ll = long long;
using namespace std;

class Demone
{
    public:

    long long id;
    long long sc; // stamina consumata
    long long tr; // turni recupero
    long long sr; // stamina recuperata
    long long na; // turni guadagno frammenti
    std::vector<long long> frammenti;
    std::vector<ll> fragsum;

    Demone(ll id, ll sc, ll tr, ll sr, ll na, vector<ll> frammenti): id(id), sc(sc), tr(tr), sr(sr), frammenti(frammenti) {
        if (frammenti.size()>0){
            fragsum = vector<ll>();
            fragsum.push_back(frammenti[0]);
            for(int i = 1; i < frammenti.size(); i++){
                fragsum.push_back(*(fragsum.end()-1) + frammenti[i]);
            }
        }
        assert (frammenti.size()==fragsum.size());
    }

    bool operator< (const Demone & d) const
    {
        return (sc < d.sc);
    }

    string to_string() {
        return "id: " + std::to_string(this->id) + " " + std::to_string(this->sc);
    }

    ll compute_score_at_turn(ll turn, ll T) {
        if (fragsum.size()==0)
            return 0;
        if ((T - turn) >= fragsum.size()) {
            return *(fragsum.end()-1);
        }
        else{
            return fragsum[T-turn-1];
        }
    }


};

struct classcomp {
    bool operator() (const Demone* lhs, const Demone* rhs) const
    {
        if (lhs->sc != rhs->sc)
            return lhs->sc < rhs->sc;
        return lhs->id < rhs->id;
    }
};

class DemoneTurno
{
    long long turno;
    Demone & demone;
};

std::vector<Demone*> soluzione(std::vector<Demone*> & demoni, long long T, long long sI, long long sMax)
{
    std::vector<Demone*> soluz;

    set<Demone*, classcomp> demonTree;
    for(auto d: demoni) {
        demonTree.insert(d);
    }

    ll mystamina = sI;
    vector<ll> recover(T+1, 0);
    ll total_points = 0;
    for(ll t = 0; t<T; t++){
        mystamina += recover[t];
        mystamina = min(mystamina, sMax);
        Demone* cmp = new Demone(demoni.size(), mystamina, 0,0,0,{});
        auto itmax = demonTree.upper_bound(cmp);
        Demone* best = NULL;
        for(auto it = demonTree.begin(); it != itmax; it++) {
            Demone* d = *it;
            if (best == NULL)
                best = d;
            else{
                if (best->compute_score_at_turn(t, T) < d->compute_score_at_turn(t, T)) {
                    best = d;
                }
            }
        }
        if (best != NULL) {
            total_points += best->compute_score_at_turn(t,T);
            if ((t + best->tr) < T)
                recover[t + best->tr] += best->sr;
            demonTree.erase(best);
            soluz.push_back(best);
            mystamina -= best->sc;
            // cout << best->id << " " << best->compute_score_at_turn(t,T) << " " << t << endl;
        }

        delete(cmp);
    }

    return soluz;
}

void read_input(ll& si, ll& smax, ll& t, ll& d, vector<Demone*>& demons) {
    
    cin >> si >> smax >> t >> d;
    
    for (int i = 0; i < d; i++) {
        ll sc, tr, sr, na;
        cin >> sc >> tr >> sr >> na;
        vector<ll> fragments;
        for(int j = 0; j < na; j++) {
            ll f;
            cin >> f;
            fragments.push_back(f);
        }
        demons.push_back(new Demone(i, sc, tr, sr, na, fragments));
    }
}

int main()
{
    ll si, smax, t, d;
    vector<Demone*> demons;
    

    read_input(si, smax, t, d, demons);

    vector<Demone*> sol = soluzione(demons, t, si, smax);
    for(auto it: sol){
        cout << it->id << (it != *(sol.end()-1)? "\n" : "");
    }
}
