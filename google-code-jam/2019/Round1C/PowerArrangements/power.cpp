
#include <iostream>
#include <vector>

using namespace std;

int main(){

    int T,F;
    cin >> T >> F;
    
    
    
    for (int t = 0; t<T; t++){
        
        string result = "";
        vector<int> positions ;
        for (int i = 0; i<119; i++){
            positions.push_back(i);
        }
        vector<bool> char_put(5, false);
        for (int i = 1; i<=4; i++){
            vector<vector<int>> positions_for_letters(5, vector<int>());
            // every turn, ask for a different letter.
            for (int j = 0; j<positions.size(); j++){
                cout << ((positions[j]*5) + i) << endl << flush ;   // position i for every person to ask.
                char letter;
                cin >> letter;
                int pos_letter = letter  - 'A';
                positions_for_letters[pos_letter].push_back(positions[j]);
            }
            
            int min_size = 100;
            int min_pos = -1;
            //cerr << i << endl;
            for (int j = 0; j<positions_for_letters.size(); j++){
                if (i == 4){
                    // Last attempt, now we look for the zero.
                    if (!char_put[j] && positions_for_letters[j].size()==0){
                        min_pos = j;
                        break;
                    }
                }
                else{
                    //cerr << positions_for_letters[j].size() << " "  << min_size << endl;
                    if (positions_for_letters[j].size() < min_size && positions_for_letters[j].size() != 0){
                        min_size = positions_for_letters[j].size();
                        min_pos = j;
                    }
                }
            }

            // cerr << "min pos " << min_pos << endl;
            // for (int j = 0; j<positions_for_letters.size(); j++){
            //     cerr << positions_for_letters[j].size() << " "; 
            // }
            // cerr << endl;
            result += char('A'+min_pos);
            char_put[min_pos] = true;
            positions = positions_for_letters[min_pos];
            //positions_for_letters.resize(5, vector<int>(0));
        }
        for (int i = 0; i<5; i++){
            if (!char_put[i]){
                result += char('A'+i);
                break;
            }
        }
        cout << result << endl <<  flush;
        char response2;
        cin >> response2;
        if (response2 == 'N'){
            //cerr << "Something went wrong  " << result << endl;
            exit(1);
        }
    }
}