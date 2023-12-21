#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>

using namespace std;
vector<string> grid;


pair<int, int> normalise (pair<int, int> p){
    return make_pair(((p.first%(int)grid[0].size())+(int)grid[0].size())%(int)grid[0].size(), ((p.second%(int)grid.size())+(int)grid.size())%(int)grid.size());
}
char accessGrid(pair<int, int> p){
    return grid[normalise(p).second][normalise(p).first];
}
vector<pair<int, int>> directions{
        make_pair(-1,0),
        make_pair(1,0),
        make_pair(0,1),
        make_pair(0, -1)
};

pair<int, int> add (pair<int, int> p1, pair<int, int> p2){
    return make_pair(p1.first+p2.first, p2.second+p1.second);
}


bool inBounds(pair<int, int> p){
    return p.first>=0&&p.second>=0&&p.first<grid[0].size()&&p.second<grid.size();
}




// start y/x, endy end x, all normalised
// odd moves found by squareCount - even moves
unsigned long long goLeftCost[200][200][200];
unsigned long long evenMoveLeftCount[200];

unsigned long long goRightCost[200][200][200];
unsigned long long evenMoveRightCount[200];

unsigned long long goUpCost[200][200][200];
unsigned long long evenMoveUpCount[200];


unsigned long long goDownCost[200][200][200];
unsigned long long evenMoveDownCount[200];
unsigned long long squareCount=0;

// shifts every tile
unsigned long long oddSquareCount=0;
unsigned long long evenSquareCount=0;
void processLeft(){

    for (int startY=0; startY < grid.size();startY++){
        int startX=0;
        unsigned long long hitSquares=0;
        unsigned long long evenMoves=0;
        unsigned long long movesMade=0;
        queue<pair<int, int>> current;
        set<pair<int, int>> allHit;
        current.emplace(startX, startY);
        allHit.emplace(startX, startY);
        while (!current.empty()) {
            movesMade++;
            queue<pair<int, int>> newCurrent;

            while (!current.empty()) {
                pair<int, int> p = current.front();
                current.pop();


                for (pair<int, int> direction: directions) {
                    pair<int, int> newPoint = add(p, direction);
                    if (!allHit.count(newPoint) && accessGrid(newPoint) != '#') {
                        allHit.insert(newPoint);
                        newCurrent.push(newPoint);

                        pair<int, int> normalised = add(newPoint, make_pair(grid[0].size(), 0));

                        if (inBounds(normalised)) {
                            hitSquares++;
                            if (movesMade%2==0){
                                evenMoves++;
                            }
                            goLeftCost[startY][normalised.second][normalised.first]=movesMade;
                        }
                    }
                }
            }
            current=newCurrent;
        }

    }
}


int main() {
    ifstream fin ("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/21/input.txt");
    string s;
    int startY;
    int startX;
    while (getline(fin, s)){
        grid.push_back(s);
    }
    for (int y = 0; y < grid.size(); y++){
        for (int x =0; x < grid[0].size(); x++){
            if (grid[y][x]=='S'){
                startY=y;
                startX=x;
            }
            if (grid[y][x]!='#'){

            }

        }
    }

    //processLeft();
    set<pair<int, int>> allMet;
    queue<pair<int, int>> current;

    int allOddCount = 0;



    // 7397 odd steps from bottom start
    // 7428 from top start
    // 7443 from left start
    // 7427 from right start

    // 6521 from br start
    // 6514 from bl start
    // 6513 from tl start
    // 6549 from tr start
    current.emplace(65, 65);
    //current.emplace(66,131);
    allMet.emplace(65,65);
    int moveCount = 0;
//    while (true) {
//        int x, y;
//        cin >> x >> y;
//        cout << normalise(make_pair(x, y)).first << ' '  << normalise(make_pair(x, y)).second << endl;
//    }
    int oddCount = 0;
    while (true){
        moveCount++;
        queue<pair<int, int>> newCurrent;
        while (!current.empty()){

            pair<int, int> p =current.front();
            current.pop();

            for (pair<int, int> direction : directions){
                if (!allMet.count(add(direction,p))&& accessGrid(add(direction, p))!='#'){
                    squareCount++;
                    newCurrent.push(add(direction, p));
                    allMet.insert(add(direction, p));
                    if (moveCount%2==1){
                        oddCount++;
                    }
//
//                    if ((add(direction, p).first+ add(direction,p).second)%2==1){
//                        oddSquareCount++;
//
//                    }
                }
            }
        }
        current=newCurrent;

        if (moveCount%262==65) {
            cout  << (moveCount-65)/262  << ' '<< oddCount << endl;
        }
    }
    cout << squareCount << ' ' << oddCount << endl;
//
//    // all met at even steps
//    unsigned long long evenCount=0;
//    current.emplace(startX,startY);
//    allMet.emplace(startX, startY);
//    for (int i = 0; i < 26501365; i++){
//
//        set<pair<int, int>> newCurrent;
//        for (pair<int, int> p : current){
//            for (pair<int, int> direction : directions){
//
//                if (accessGrid(add(p,direction))!='#'){
//
//                    if (!allMet.count(add(direction, p))) {
//                        newCurrent.insert(add(direction, p));
//                        allMet.insert(add(direction, p));
//                        if (i%2==0){
//                            evenCount++;
//                        }
//
//                        if (normalise(add(direction,p))== make_pair(startX, startY)){
//
//                            cout << i << endl;
//                        }
//                    }
//                }
//            }
//
//
//        }
//        //cout << evenCount << endl;
//        current=newCurrent;
////        for (int y = 0; y < grid.size(); y++){
////            for (int x =0; x < grid[0].size(); x++){
////                if (current.count(make_pair(x, y))){
////                    cout << 'O';
////                }
////                else{
////                    cout << grid[y][x];
////                }
////            }
////            cout << endl;
////        }
//
//    }







}
