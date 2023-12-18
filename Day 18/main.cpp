#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <cmath>
using namespace std;



// from stackoverflow
unsigned long hex2dec(string hex)
{
    unsigned long result = 0;
    for (int i=0; i<hex.length(); i++) {
        if (hex[i]>=48 && hex[i]<=57)
        {
            result += (hex[i]-48)*pow(16,hex.length()-i-1);
        } else if (hex[i]>=65 && hex[i]<=70) {
            result += (hex[i]-55)*pow(16,hex.length( )-i-1);
        } else if (hex[i]>=97 && hex[i]<=102) {
            result += (hex[i]-87)*pow(16,hex.length()-i-1);
        }
    }
    return result;
}
enum Direction{
    u,l,d,r
};
map<string, Direction> directionStrings{
        {"R", r},
        {"U",u},
        {"L",l},
        {"D",d}
};
set<pair<long long, long long>> edges;
vector<tuple<Direction, long long, string>> instructions;

int xAmount(Direction direction){
    switch(direction){
        case u:
            return 0;
        case d:
            return 0;
        case l:
            return -1;
        case r:
            return 1;
    }
}
int yAmount(Direction direction){
    switch(direction){
        case u:
            return -1;
        case d:
            return 1;
        case l:
            return 0;
        case r:
            return 0;
    }
}


int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/18/input.txt");

    string s;
    int quartersTaken=0;

    while (getline(fin, s)){
        stringstream sin(s);
        sin >> s;
        Direction direction = directionStrings[s];
        sin >> s;
        int amount = stoi(s);
        sin >> s;
        s=s.substr(2,s.size()-3);
        amount = hex2dec(s.substr(0, 5));
        switch(s.back()){
            case '0':
                direction = r;
                break;
            case '1':
                direction = d;
                break;
            case '2':
                direction = l;
                break;
            case '3':
                direction = u;
                break;
        }
//        cout << direction << ' ' << amount << endl;
        instructions.emplace_back(direction, amount, s);

        //instructions.emplace_back(direction, amount, s.substr(2,s.size()-3));

    }
    long long y = 0;
    long long x= 0;
    vector<pair<long long, long long>> corners;
    vector<pair<long long, long long>> newCorners;
    corners.emplace_back(0,0);
    newCorners.emplace_back(0,0);
    for (int i = 0; i < instructions.size() -1;i ++){
        // gone down u -> r-> d-> l->u
        if ((get<0>(instructions[i])-get<0>(instructions[i+1])+4)%4==1){
            quartersTaken+=3;

        }
        else{
            // gone up u -> l -> d ->r
            quartersTaken+=1;
        }
        int newX = x + xAmount(get<0>(instructions[i]))*get<1>(instructions[i]);
        int newY = y + yAmount(get<0>(instructions[i]))*get<1>(instructions[i]);
        if (newX!=x){
            // x moved
            quartersTaken += (abs(newX-x)-1)*2;
        }
        else{
            quartersTaken+=(abs(newY-y)-1)*2;
        }





        corners.emplace_back(newX, newY);

        x=newX;
        y=newY;
    }
    long long newX = x + xAmount(get<0>(instructions.back()))*get<1>(instructions.back());
    long long newY = y + yAmount(get<0>(instructions.back()))*get<1>(instructions.back());
    if (newX!=x){
        // x moved
        quartersTaken += (abs(newX-x)-1)*2;
    }
    else{
        quartersTaken+=(abs(newY-y)-1)*2;
    }

    if ((get<0>(instructions.back())-get<0>(instructions[0])+4)%4==1){
        quartersTaken+=3;

    }
    else{
        // gone up u -> l -> d ->r
        quartersTaken+=1;
    }

    long long doubledArea = 0;
    for (int i = 0; i < corners.size();i++){
        doubledArea+=corners[i].second*(corners[(i+corners.size()-1)%corners.size()].first - corners[(i+1)%corners.size()].first);
    }
    cout << doubledArea/2 + quartersTaken/4 << endl;
//    cout << quartersTaken << endl;

//
//    int currentX=0;
//    int currentY=0;
//    int minY=0, minX=0;
//    edges.emplace(0,0);

//    for (tuple<Direction, int, string> instruction : instructions){
//        Direction direction = get<0>(instruction);
//        int amount = get<1>(instruction);
//        for (int i = 0; i < amount; i++){
//            currentX += xAmount(direction);
//            currentY += yAmount(direction);
//            edges.emplace(currentX, currentY);
//            minY=min(currentY,minY);
//            minX=min(currentX, minX);
//        }
//    }
//    set<pair<int, int>> newEdges;
//    int maxX=0, maxY=0;
//    for (pair<int, int> p : edges){
//        newEdges.emplace(p.first-minX,p.second-minY);
//        maxX=max(maxX, p.first-minX);
//        maxY=max(maxY, p.second-minY);
//    }
//
//
//    edges=newEdges;
    // visualise
//    for (int y= 0; y <= maxY; y++) {
//        for (int x = 0; x <= maxX; x++) {
//            if (edges.count(make_pair(x, y))){
//                cout << '#';
//            }
//            else{
//                cout << '.';
//            }
//
//        }
//        cout << endl;
//    }
//
//    set<pair<int, int>> interior;
//    // known to be inside
//    interior.emplace(11,1);
//    queue<pair<int, int>> nextInsides;
//    nextInsides.emplace(11, 1);
//    while (!nextInsides.empty()){
//        pair<int, int> current = nextInsides.front();
//        nextInsides.pop();
//        int x=  current.first;
//        int y = current.second;
//        int newX, newY;
//
//        for (Direction direction = u; direction <= r; direction=(Direction)((int)direction+1)){
//            newX = x+ xAmount(direction);
//            newY = y+ yAmount(direction);
//            if (!interior.count(make_pair(newX, newY)) && !edges.count(make_pair(newX, newY))){
//                interior.emplace(newX, newY);
//                nextInsides.emplace(newX, newY);
//            }
//        }
//
//
//    }
//    cout << interior.size() + edges.size() << endl;
}
