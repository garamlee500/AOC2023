#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <queue>

using namespace std;

// % or & or B
unordered_map<string, char> moduleTypes;

// for % types
unordered_map<string, bool> flipFlopStates;

// for & types
unordered_set<string> conjunctionModules;
unordered_map<string, vector<string>> inputModules;
unordered_map<string, unordered_map<string, bool>> inputModulesMemory;


unordered_map<string, vector<string>> outputModules;


string stateMarker(){
    string state;
    for (pair<string, bool> p : flipFlopStates){
        state += p.second?'1':'0';
    }
    for (pair<string, unordered_map<string, bool>> p : inputModulesMemory){
        for (pair<string, bool> p1 : p.second){
            state+=p1.second?'1':'0';
        }
    }
    return state;
}

unordered_map<string, int> firstSeen;

// High, lows
pair<unsigned long long, unsigned long long> processBroadcast(unsigned long long button, string test){
    unsigned long long lowCount=1;
    unsigned long long highCount=0;
    // input module, output module, isHigh
    queue<tuple<string, string, bool>> pulses;
    for (const string& output : outputModules["broadcaster"]){
        pulses.emplace("broadcaster", output, false);
        lowCount++;
    }
    int rxCount=0;
    int otherCount = 0;
    int rxHighCount=0;
    int otherCountHigh = 0;
    while (!pulses.empty()){
        tuple<string, string, bool> pulse = pulses.front();
        pulses.pop();
        string inputModule = get<0>(pulse);
        string outputModule = get<1>(pulse);
        bool isHigh = get<2>(pulse);

        if (moduleTypes[outputModule]=='%'){
            // flip flop
            if (isHigh){
                continue;
            }

            // low pulse received
            if (flipFlopStates[outputModule]){
                // turn off and send low pulse
                flipFlopStates[outputModule]=false;
                for (const string& nextOutput : outputModules[outputModule]){
                    pulses.emplace(outputModule, nextOutput, false);
                    lowCount++;
                    if (nextOutput==test){
                        otherCount++;
                    }

                    if (outputModule=="rx"){
                        rxCount++;
                    }
                }
            }
            else{
                // turn on and send high pulse

                flipFlopStates[outputModule]=true;
                for (const string& nextOutput : outputModules[outputModule]){
                    pulses.emplace(outputModule, nextOutput, true);
                    highCount++;
                    if (nextOutput==test){
                        otherCountHigh++;
                    }
                } if (outputModule=="rx"){
                    rxHighCount+=1;
                }
            }

        }
        else{
            // conjunction module
            inputModulesMemory[outputModule][inputModule] = isHigh;
            bool valid = true;
            for (pair<string, bool> p : inputModulesMemory[outputModule]){
                valid = valid && p.second;
            }
            if (valid){
                // send low pulse
                for (const string& nextOutput : outputModules[outputModule]){
                    pulses.emplace(outputModule, nextOutput, false);
                    lowCount++;
                    if (nextOutput==test){
                        otherCount++;
                    }
                }
                if (outputModule=="rx"){
                    rxCount++;
                }
                if (inputModule=="sg"){
                    cout << "what";
                }
            }
            else{
                // send high pulse
                for (const string& nextOutput : outputModules[outputModule]){
                    pulses.emplace(outputModule, nextOutput, true);
                    highCount++;
                    if (nextOutput==test){
                        otherCountHigh++;
                    }
                }
//                if (inputModule=="sg"){
//                    otherCount++;
//                }
                if (outputModule=="rx"){
                    rxHighCount+=1;
                }

            }
        }
    }
//    cout << rxCount << endl;
    if (otherCount>0)
        cout << "Button Press " << button << ": " << otherCount << ' ' << otherCountHigh << endl;

    if (rxCount==1){
        cout << button << endl;
    }
    return make_pair(lowCount, highCount);
}

int main() {
    ifstream fin ("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/20/input.txt");
    string s;
    while (getline(fin, s)){
        stringstream sin(s);
        string moduleName;
        char moduleType;
        sin >> moduleName;
        if (moduleName[0]=='%'){
            moduleType = '%';
            moduleName = moduleName.substr(1);
            flipFlopStates[moduleName]=false;
        }
        else if (moduleName[0]=='&'){
            moduleType = '&';
            moduleName = moduleName.substr(1);
            conjunctionModules.insert(moduleName);
        }
        else{
            moduleType='B';
        }
        sin >>s;
        moduleTypes[moduleName]= moduleType;
        while(true){
            sin >> s;
            if (!sin){
                break;
            }
            if (s.back()==','){
                s.pop_back();
            }
            outputModules[moduleName].push_back(s);
        }
    }

    for (pair<string, vector<string>> it : outputModules){
        for (const string& outputModule : it.second){
                inputModules[outputModule].push_back(it.first);
                inputModulesMemory[outputModule][it.first]=(false);

        }
    }
    unsigned long long buttonPresses = 0;
    unsigned long long lowTotal=0;
    unsigned long long highTotal = 0;
    unordered_set<string> requiredStates;
    queue<string> stateQueue;
    stateQueue.push("rx");
    requiredStates.insert("rx");
    while (stateQueue.size()>0){
        string current = stateQueue.front();
        stateQueue.pop();
        for (string input : inputModules[current]){
            if(!requiredStates.count(input)){
                requiredStates.insert(input);
                stateQueue.push(input);
            }
        }
//        cout << current << endl;ssf
    }

    string test;
    cin >> test;
    while (true){
        buttonPresses++;
        pair<unsigned long long, unsigned long long> p = processBroadcast(buttonPresses, test);
//        lowTotal+=p.first;
//        highTotal+=p.second;
        // cout << "Press " << buttonPresses << endl;
        // cout << p.first << ' ' << p.second << endl;
//        string state = stateMarker();
//        cout << state << endl;
//        if (buttonPresses==1000){
//            cout << lowTotal*highTotal << endl;
//        }
//        if (firstSeen.count(state)){
//            // seen before;
//            cout << "Cycle reached" << endl;
//            cout << "First seen at " << firstSeen[state] << "th press";
//            break;
//        }
//        else{
//            firstSeen[state] = buttonPresses;
//        }
    }
}
