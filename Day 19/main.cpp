#include <iostream>
#include <fstream>
#include <utility>
#include <unordered_map>
#include <vector>
using namespace std;

enum Stat{
    x,m,a,s
};

struct Condition{
    Stat statType;
    int num;
    bool needsToBeGreater;
    Condition(Stat statType, int num, bool needsToBeGreater):
            statType(statType),
            num(num),
            needsToBeGreater(needsToBeGreater){}
    Condition(){
        statType=x;
        num=0;
        needsToBeGreater=false;
    }
};

struct Rule{
    bool isCondition;
    Condition condition;
    string nextState;
    Rule(bool isCondition, Condition condition, string nextState):
        isCondition(isCondition),
        condition(condition),
        nextState(std::move(nextState))
    {}
};

vector<string> split(const string& s, char delim){
    vector<string> result;
    string current;
    for (char c : s){
        if (c==delim){
            result.push_back(current);
            current="";
        }
        else{
            current+=c;
        }
    }
    result.push_back(current);
    return result;
}

unordered_map<string, vector<Rule>> rules;

bool isValid(const vector<int>& item){
    vector<Rule> currentRule = rules["in"];
    int index=0;

    while (true){
        if (currentRule[index].isCondition){
            if ((currentRule[index].condition.needsToBeGreater
            && item[currentRule[index].condition.statType] > currentRule[index].condition.num)
            ||
                    (
                            (!currentRule[index].condition.needsToBeGreater)
                            && item[currentRule[index].condition.statType] < currentRule[index].condition.num


                            )
            ){

                if (currentRule[index].nextState=="A"){
                    return true;
                }
                else if (currentRule[index].nextState=="R"){
                    return false;
                }
                currentRule = rules[currentRule[index].nextState];
                index = 0;

            }
            else{
                index++;
            }
        }
        else{
            if (currentRule[index].nextState=="R"){
                return false;
            }
            else if (currentRule[index].nextState=="A"){
                return true;
            }
            else{
                currentRule = rules[currentRule[index].nextState];
                index=0;
            }

        }


    }
}


// min, max values
unsigned long long howManyPossible(vector<pair<int, int>> bounds, string ruleName, int currentIndex){

    if (ruleName=="A"){
        unsigned long long subTotal = 1;
        for (const pair<int, int>& p : bounds){
            subTotal*=(p.second-p.first+1);
        }
        return subTotal;

    }
    else if (ruleName=="R"){
        return 0;
    }

    unsigned long long total = 0;

    while (!rules[ruleName][currentIndex].isCondition){
        if (rules[ruleName][currentIndex].nextState=="R"){
            return 0;
        }
        else if (rules[ruleName][currentIndex].nextState=="A"){
            unsigned long long subTotal = 1;
            for (const pair<int, int>& p : bounds){
                subTotal*=(p.second-p.first+1);
            }
            return subTotal;
        }
        else{
            ruleName= rules[ruleName][currentIndex].nextState;
            currentIndex=0;
        }
    }



    if (rules[ruleName][currentIndex].condition.needsToBeGreater){
        if (bounds[rules[ruleName][currentIndex].condition.statType].first > rules[ruleName][currentIndex].condition.num){
            // always true
            return howManyPossible(bounds, rules[ruleName][currentIndex].nextState, 0);
        }
        else if (bounds[rules[ruleName][currentIndex].condition.statType].second <= rules[ruleName][currentIndex].condition.num){
            // always false
            return howManyPossible(bounds, ruleName, currentIndex+1);
        }
        else{
            // sometimes true
            vector<pair<int, int>> newBounds1 = bounds;
            vector<pair<int, int>> newBounds2 = bounds;

            // smaller stuff
            newBounds1[rules[ruleName][currentIndex].condition.statType]= make_pair(bounds[rules[ruleName][currentIndex].condition.statType].first,

                                                                                    rules[ruleName][currentIndex].condition.num
                    );

            // bigger stuff
            newBounds2[rules[ruleName][currentIndex].condition.statType]= make_pair(rules[ruleName][currentIndex].condition.num+1,
                                                                                    bounds[rules[ruleName][currentIndex].condition.statType].second

            );
            return howManyPossible(newBounds1, ruleName, currentIndex+1)
            + howManyPossible(newBounds2, rules[ruleName][currentIndex].nextState, 0);

        }
    }
    else{
        if (bounds[rules[ruleName][currentIndex].condition.statType].second < rules[ruleName][currentIndex].condition.num){
            // always true
            return howManyPossible(bounds, rules[ruleName][currentIndex].nextState, 0);
        }
        else if (bounds[rules[ruleName][currentIndex].condition.statType].first >= rules[ruleName][currentIndex].condition.num){
            // always false
            return howManyPossible(bounds, ruleName, currentIndex+1);
        }
        else{
            // sometimes true
            vector<pair<int, int>> newBounds1 = bounds;
            vector<pair<int, int>> newBounds2 = bounds;

            // smaller stuff
            newBounds1[rules[ruleName][currentIndex].condition.statType]= make_pair(bounds[rules[ruleName][currentIndex].condition.statType].first,

                                                                                    rules[ruleName][currentIndex].condition.num-1
            );

            // bigger stuff
            newBounds2[rules[ruleName][currentIndex].condition.statType]= make_pair(rules[ruleName][currentIndex].condition.num,
                                                                                    bounds[rules[ruleName][currentIndex].condition.statType].second

            );
            return howManyPossible(newBounds2, ruleName, currentIndex+1)
                   + howManyPossible(newBounds1, rules[ruleName][currentIndex].nextState, 0);

        }
    }


}


int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/19/input.txt");
    string s1;

    while (true){
        getline(fin, s1);
        if (s1.empty()){
            break;
        }

        string ruleName;
        vector<Rule> ruleList;
        int index = 0;
        while (s1[index]!='{'){
            ruleName+=s1[index];
            index++;
        }
        vector<string> ruleStrings = split(s1.substr(index+1, s1.size()-2-index),',');
        for (string ruleString : ruleStrings){

            if (ruleString.find(':')==string::npos){
                ruleList.emplace_back(false, Condition(), ruleString);
                break;
            }
            Stat stat;
            switch(ruleString[0]){
                case 'x':
                    stat=x;
                    break;
                case 'm':
                    stat=m;
                    break;
                case 'a':
                    stat=a;
                    break;
                default:
                    stat=s;
                    break;
            }
            bool isGreater = ruleString[1]=='>';
            int num = 0;
            int index1 = 2;
            while (ruleString[index1]!=':'){
                num*=10;
                num+= ruleString[index1]-'0';
                index1++;
            }
            string nextStat = ruleString.substr(index1+1);

            ruleList.emplace_back(true, Condition(stat, num, isGreater), nextStat);
        }
        rules[ruleName]=ruleList;

    }

//    int total= 0;
//    while (getline(fin, s1)){
//        vector<string> itemStrings = split(s1.substr(1, s1.size()-2), ',');
//        vector<int> itemValues;
//        itemValues.reserve(itemStrings.size());
//        for (const string& s2 : itemStrings){
//            itemValues.push_back(stoi(s2.substr(2)));
//        }
//        if (isValid(itemValues)){
//            total += itemValues[0] + itemValues[1] + itemValues[2] + itemValues[3];
//        }
//    }
    cout << howManyPossible({make_pair(1, 4000), make_pair(1,4000), make_pair(1,4000), make_pair(1,4000)},
                            "in",
                            0
                            ) << endl;
}
