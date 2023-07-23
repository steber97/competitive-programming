#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Contributor ;

class ContributorSkill {
    public: 
    Contributor* contributor;
    string name;
    int level;
    ContributorSkill(string name, int level, Contributor* contributor){

    };
};

class Contributor {
public:
int day;
unordered_map<string, ContributorSkill> skills;
vector<int> skill_levels;
string name;
    Contributor(vector<string> skill_names, vector<int> skill_levels, int day, string name){

    }


};

struct Class1Compare
{
   bool operator() (const ContributorSkill& lhs, const ContributorSkill& rhs) const
   {
       return lhs.level == rhs.level ? lhs.contributor->day < rhs.contributor->day : lhs.level < rhs.level;
   }
};



int main(){

    Contributor c1({}, {}, 1, "ciao");
    Contributor c2({}, {}, 1, "ciao2");

    ContributorSkill cs1("python", 4, &c1);
    ContributorSkill cs2 ("python", 6, &c2);

    std::map<ContributorSkill, ContributorSkill, Class1Compare> c2int;
    c2int.insert(cs1);
    c2int.insert(cs2);

    return 0;
}