#include <iostream>

#include <fstream>

#include <unordered_map>

#include <string>

#include <vector>
#include <algorithm>

using namespace std;

unordered_map<string, pair<unsigned long long, string>> nextState;

unordered_map<string, string> lefts;

unordered_map<string, string> rights;

string instructions;


void findNextZ(string s){
    string start =s;
    int total = 0;
    while (s[2]!='Z'||total==0) {

        char direction = instructions[total % instructions.size()];

        total++;

        if (direction == 'L') {

            s = lefts[s];

        }

        else {

            s = rights[s];

        }

    }
    nextState[start] = make_pair(total, s);
}

int main() {



    ifstream fin ("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/Day 8/input.txt");

    string s;


    int instructionCount = 0;

    getline(fin, instructions);

    getline(fin, s);

    while (getline(fin, s)) {

        string current = s.substr(0, 3);


        string l = s.substr(7, 3);

        string r = s.substr(12, 3);

        lefts[current] = l;

        rights[current] = r;

    }

    int total = 0;
    s="DVA";
    int prev = 0;
    while (true){

        char direction = instructions[total % instructions.size()];
        if (direction == 'L') {

            s = lefts[s];

        }

        else {

            s = rights[s];

        }
        total++;
        if (s[2]=='Z'){
            cout << total << " +" << total - prev <<endl;
            prev = total;
        }
    }
//
//    vector<pair<unsigned long long, string>> states;
//    for (auto& [key, value] : lefts){
//        if (key[2]=='A'||key[2]=='Z'){
//            findNextZ(key);
//        }
//        if (key[2]=='A'){
//            cout << key << endl;
//            states.push_back(nextState[key]);
//        }
//    }
//
//    sort(states.begin(), states.end(), greater<pair<unsigned long long, string>>());
//    while(states.front().first!=states.back().first){
//        pair<unsigned long long, string> state = states.back();
//
//        states.pop_back();
//        states.emplace_back(nextState[state.second].first+state.first, nextState[state.second].second);
//        sort(states.begin(), states.end(), greater<pair<unsigned long long, string>>());
//
//    }
//    cout << states.front().first << endl;
//
//




}
