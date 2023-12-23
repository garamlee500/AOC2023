#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;
int startY=0, startX=1, endY= 140, endX=139;
vector<string> grid;


bool inBounds(int x, int y){
    return x>=0&&y>=0&&x<grid[0].size()&&y<grid.size();
}

// x, y
vector<pair<int, int>> edges[150][150];
//vector<tuple<int, int, int>> longEdges[150][150];
// nodeNum, length
vector<pair<int, int>> newEdges[1000];
vector<pair<int, int>> reverseNodeNums;


vector<pair<int, int>> reverseEdges[150][150];


map<pair<int, int>, int> nodeNums;

pair<pair<int, int>, int> nextJunction(int x, int y, int prevX, int prevY){
    int length =1;
    while (edges[x][y].size()<=2&&edges[x][y].size()!=1){
        length++;
        for (pair<int, int> p : edges[x][y]){
            if (p.first!=prevX||p.second!=prevY){
                prevX=x;
                prevY=y;
                x=p.first;
                y=p.second;
                break;
            }
        }
    }
    return make_pair(make_pair(x, y), length);
}


void findLongEdge(int x, int y){
    if (edges[x][y].size()==2||grid[y][x]=='#'){
        return;
    }
    if(!nodeNums.count(make_pair(x, y))){
        nodeNums[make_pair(x, y)] = reverseNodeNums.size();
        reverseNodeNums.emplace_back(x, y);
    }

    for (pair<int, int> p : edges[x][y]){

        pair<pair<int,int>, int> p1 = nextJunction(p.first, p.second, x, y);
        if (!nodeNums.count(p1.first)){
            nodeNums[p1.first] = reverseNodeNums.size();
            reverseNodeNums.push_back(p1.first);

        }
        newEdges[nodeNums[make_pair(x, y)]].emplace_back(nodeNums[p1.first], p1.second);

        if (x<p1.first.first || (x==p1.first.first&&y<p1.first.second) )
            cout << "\"(" << x << ',' << y << ")\" -> \"(" << p1.first.first << "," << p1.first.second << ")\" [weight=" << p1.second << "][dir=none][label=" << p1.second << "]" << endl;

    }




}
void connect(int currentX, int currentY){

    if (grid[currentY][currentX]=='.'||true){
        if (inBounds(currentX-1, currentY)&&grid[currentY][currentX-1]!='#'){
            edges[currentX][currentY].emplace_back(currentX-1, currentY);
            reverseEdges[currentX-1][currentY].emplace_back(currentX,currentY);
        }
    }
    if (grid[currentY][currentX]=='.'||true){
        if (inBounds(currentX+1, currentY)&&grid[currentY][currentX+1]!='#'){
            edges[currentX][currentY].emplace_back(currentX+1, currentY);
            reverseEdges[currentX+1][currentY].emplace_back(currentX,currentY);

        }
    }
    if (grid[currentY][currentX]=='.'||true){
        if (inBounds(currentX, currentY-1)&&grid[currentY-1][currentX]!='#'){
            edges[currentX][currentY].emplace_back(currentX, currentY-1);
            reverseEdges[currentX][currentY-1].emplace_back(currentX,currentY);

        }
    }

    if (grid[currentY][currentX]=='.'||true){
        if (inBounds(currentX, currentY+1)&&grid[currentY+1][currentX]!='#'){
            edges[currentX][currentY].emplace_back(currentX, currentY+1);
            reverseEdges[currentX][currentY+1].emplace_back(currentX,currentY);

        }
    }
}

int longest2(int nodeNum, set<int> visited){
    visited.insert(nodeNum);
    if (nodeNum==nodeNums[make_pair(endX, endY)]){
        return 0;
    }
    int best = -1;
    for (pair<int, int> edge :newEdges[nodeNum]){
        if (!visited.count(edge.first)){
            int sub = longest2(edge.first,visited);
            if (sub>=0) {
                best = max(best, edge.second + sub);
            }
        }
    }
//    if (best==6746){
//        cout << visited.size()<<endl;
//        for (int x : visited){
//            cout << reverseNodeNums[x].first << ' ' << reverseNodeNums[x].second << endl;
//        }
//    }
    return best;
}
int longest(int x, int y, set<pair<int, int>> visited){
    int length = 0;
    while (true){
        if (x==endX&&y==endY){
            return length;
        }

        int connectedCount = 0;
        for (pair<int, int> p : edges[x][y]){
            if (!visited.count(p)){
                connectedCount+=1;
            }
        }
        if (connectedCount==0){
            return -1;
        }
        if (connectedCount==1){
            for (pair<int, int> p : edges[x][y]){
                if (!visited.count(p)){
                    length++;
                    x=p.first;
                    y=p.second;
                    visited.emplace(x, y);
                }
            }
            continue;
        }
        else{
            length++;

            int best = 0;

            for (pair<int, int> p : edges[x][y]){
                if (!visited.count(p)){
                    set<pair<int, int>> newUnvisited = visited;
                    newUnvisited.insert(p);
                    best = max(best, longest(p.first, p.second, newUnvisited));
                }
            }
            return length+ best;
        }

    }
    return length;

}


int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/23/input.txt");
    string s;
    while (getline(fin, s)) {
        grid.push_back(s);
    }

    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[0].size(); x++) {
            connect(x, y);
        }
    }
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[0].size(); x++) {
            findLongEdge(x, y);
        }
    }
    cout << longest2(nodeNums[make_pair(startX,startY)], set<int>()) << endl;
}
