#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;
vector<string> grid;


pair<int, int> goDown(int x, int y){
    if (y+1<grid.size()&&
        (grid[y+1][x]=='|'
         ||
         grid[y+1][x]=='L'
         ||
         grid[y+1][x]=='J'
         ||
         grid[y+1][x]=='S')){
        return make_pair(x, y+1);
    }
    return make_pair(-1, -1);

}

pair<int, int> goUp(int x, int y){
    // go up
    if (y>0){
        if (
            (grid[y-1][x]=='|'
             ||
             grid[y-1][x]=='F'
             ||
             grid[y-1][x]=='7'
             ||
             grid[y-1][x]=='S')){
            return make_pair(x, y-1);
        }

    }
    return make_pair(-1, -1);

}
pair<int, int> goLeft(int x, int y){

    if (x>0&&(
            grid[y][x-1]=='-'
            ||
            grid[y][x-1]=='L'
            ||
            grid[y][x-1]=='F'
            ||
            grid[y][x-1]=='S'

            )) {


        return make_pair(x - 1, y);
    }
    return make_pair(-1,-1);
}


pair<int, int> goRight(int x, int y){
    if (x+1<grid[0].size()&&
            (
                    grid[y][x+1]=='-'
                    ||
                            grid[y][x+1]=='J'
                   ||
                            grid[y][x+1]=='7'
                          ||
                            grid[y][x+1]=='S'


                    )){
        return make_pair(x+1, y);
    }
    return make_pair(-1, -1);
}

pair<int, int> nextSquare(int x, int y, int prevX, int prevY){
    if (grid[y][x]=='.'){
        return make_pair(-1,-1);
    }
    if (grid[y][x]=='|'){
        if (y > prevY){
            // go down
            return goDown(x, y);
        }
        else{
            return goUp(x,y);
        }
    }
    else if (grid[y][x]=='-'){
        if(x>prevX){
            return goRight(x, y);
        }
        else{
            return goLeft(x, y);
        }


    }
    else if (grid[y][x]=='L'){
        if (y>prevY){
            return goRight(x, y);
        }
        else{
            return goUp(x, y);
        }

    }
    else if (grid[y][x]=='J'){
        if (y>prevY){
            return goLeft(x, y);
        }
        else{
            return goUp(x, y);
        }
    }
    else if (grid[y][x]=='7'){
        if (y<prevY){
            return goLeft(x, y);
        }
        else{
            return goDown(x, y);
        }
    }
    else if (grid[y][x]=='F'){
        if (y<prevY){
            return goRight(x, y);
        }
        else{
            return goDown(x, y);
        }
    }
    return make_pair(-1, -1);
}

int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/10/input.txt");
    int startX, startY;
    string s;
    int y=0;
    while (getline(fin, s)){
        grid.push_back(s);
        for (int x = 0; x < s.size(); x++){
            if (s[x]=='S'){
                startX=x;
                startY=y;
            }
        }
        y++;
    }
    pair<int, int> previous = make_pair(startX,startY);
    pair<int, int> current = goUp(previous.first, previous.second);
    grid[startY][startX]='J';
    set<pair<int, int>> visited;
    visited.insert(current);
    visited.insert(previous);
    int loopLength=1;


    while (true){
        pair<int, int> next= nextSquare(current.first, current.second, previous.first, previous.second);
        if(next.first==startX&&next.second==startY){
            cout << loopLength << endl;
            break;
        }
        else if (visited.count(next)||next.first==-1){
            cout << "uh oh" << endl;
        }
        else{

            visited.insert(next);
            loopLength++;
            previous=current;
            current=next;
        }
    }
    int total = 0;
    for (y = 0; y < grid.size(); y++){
        bool inside = false;
        for (int x=0; x< grid[0].size();x++){
            if(visited.count(make_pair(x, y))){
                bool startUp=false;
                if (grid[y][x]=='L'){
                    startUp=true;
                }
                while(grid[y][x]!='|'&&grid[y][x]!='7'&&grid[y][x]!='J'){
                    x++;
                }
                if (grid[y][x]=='|'||((grid[y][x]=='7')==startUp)) {
                    inside = !inside;
                }
            }
            else{

                if (inside){
                    total++;
                }


            }
        }
    }
    cout << total << endl;
}
