#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <set>

using namespace std;
enum Direction{
    u, l, d, r
};
vector<string> grid;

tuple<int, int, Direction> moveUp(tuple<int, int, Direction> pos){


    tuple<int, int, Direction> newPos= {get<0>(pos), get<1>(pos)-1, u};
    if (get<0>(newPos)<0||get<0>(newPos)>=grid[0].size()
    ||get<1>(newPos)<0||get<1>(newPos)>=grid.size()){
        return {-1,-1,u};
    }
    else{
        return newPos;
    }
}
tuple<int, int, Direction> moveLeft(tuple<int, int, Direction> pos){


    tuple<int, int, Direction> newPos= {get<0>(pos)-1, get<1>(pos), l};
    if (get<0>(newPos)<0||get<0>(newPos)>=grid[0].size()
        ||get<1>(newPos)<0||get<1>(newPos)>=grid.size()){
        return {-1,-1,u};
    }
    else{
        return newPos;
    }
}
tuple<int, int, Direction> moveRight(tuple<int, int, Direction> pos){


    tuple<int, int, Direction> newPos= {get<0>(pos)+1, get<1>(pos), r};
    if (get<0>(newPos)<0||get<0>(newPos)>=grid[0].size()
        ||get<1>(newPos)<0||get<1>(newPos)>=grid.size()){
        return {-1,-1,u};
    }
    else{
        return newPos;
    }
}
tuple<int, int, Direction> moveDown(tuple<int, int, Direction> pos){


    tuple<int, int, Direction> newPos= {get<0>(pos), get<1>(pos)+1, d};
    if (get<0>(newPos)<0||get<0>(newPos)>=grid[0].size()
        ||get<1>(newPos)<0||get<1>(newPos)>=grid.size()){
        return {-1,-1,u};
    }
    else{
        return newPos;
    }
}

tuple<int, int, Direction> moveBlind(tuple<int, int, Direction> pos){
    if (get<2>(pos)==u){
        return moveUp(pos);
    }
    else if (get<2>(pos)==d){
        return moveDown(pos);
    }
    else if (get<2>(pos)==l){
        return moveLeft(pos);
    }
    else{
        return moveRight(pos);
    }
}

pair<tuple<int, int, Direction>, tuple<int, int, Direction>> repos(tuple<int, int, Direction> pos) {
    if (grid[get<1>(pos)][get<0>(pos)] == '.') {
        return make_pair(moveBlind(pos), make_tuple(-1, -1, u));
    }
    if (grid[get<1>(pos)][get<0>(pos)] == '/') {
        if (get<2>(pos) == u) {
            return make_pair(moveRight(pos), make_tuple(-1, -1, u));
        }
        if (get<2>(pos) == r) {
            return make_pair(moveUp(pos), make_tuple(-1, -1, u));
        }
        if (get<2>(pos) == l) {
            return make_pair(moveDown(pos), make_tuple(-1, -1, u));
        }
        if (get<2>(pos) == d) {
            return make_pair(moveLeft(pos), make_tuple(-1, -1, u));
        }


    }
    if (grid[get<1>(pos)][get<0>(pos)] == '\\') {
        if (get<2>(pos) == u) {
            return make_pair(moveLeft(pos), make_tuple(-1, -1, u));
        }
        if (get<2>(pos) == r) {
            return make_pair(moveDown(pos), make_tuple(-1, -1, u));
        }
        if (get<2>(pos) == l) {
            return make_pair(moveUp(pos), make_tuple(-1, -1, u));
        }
        if (get<2>(pos) == d) {
            return make_pair(moveRight(pos), make_tuple(-1, -1, u));
        }


    }
    if (grid[get<1>(pos)][get<0>(pos)] == '|') {
        if(get<2>(pos)==r||get<2>(pos)==l){
            return make_pair(moveUp(pos), moveDown(pos));
        }
        else{
            return make_pair(moveBlind(pos),make_tuple(-1,-1,u));
        }
    }
    else{
        if(get<2>(pos)==u||get<2>(pos)==d){
            return make_pair(moveLeft(pos), moveRight(pos));
        }
        else{
            return make_pair(moveBlind(pos),make_tuple(-1,-1,u));
        }
    }
}


int main() {

    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/16/input.txt");
    string s;
    while (getline(fin, s)){
        grid.push_back(s);
    }
    int best = 0;

    for (int x = 0; x < grid[0].size(); x++){
        vector<tuple<int, int, Direction>> current = {{x,0,d}};
        set<tuple<int, int, Direction>> visited;
        set<tuple<int, int>> energised;

        energised.emplace(x,0);
        visited.emplace(x,0,d);
        while (current.size()>0){
            vector<tuple<int, int, Direction>> newPoses;

            for (const tuple<int, int, Direction>& pos : current){
                pair<tuple<int, int, Direction>, tuple<int, int, Direction>> newPos = repos(pos);
                if (get<0>(newPos.first)!=-1){

                    if (!visited.count(newPos.first)){
                        energised.emplace(get<0>(newPos.first),get<1>(newPos.first));
                        visited.insert(newPos.first);
                        newPoses.push_back(newPos.first);
                    }
                }
                if (get<0>(newPos.second)!=-1){

                    if (!visited.count(newPos.second)){
                        energised.emplace(get<0>(newPos.second),get<1>(newPos.second));
                        visited.insert(newPos.second);

                        newPoses.push_back(newPos.second);
                    }
                }
            }
            current=newPoses;
        }
        if (energised.size() > best) {
            best = energised.size();
            cout << best << endl;
        }
    }
    for (int x = 0; x < grid[0].size(); x++){
        vector<tuple<int, int, Direction>> current = {{x,grid.size()-1,u}};
        set<tuple<int, int, Direction>> visited;
        set<tuple<int, int>> energised;

        energised.emplace(x, grid.size()-1);
        visited.emplace(x, grid.size()-1,u);
        while (current.size()>0){
            vector<tuple<int, int, Direction>> newPoses;

            for (const tuple<int, int, Direction>& pos : current){
                pair<tuple<int, int, Direction>, tuple<int, int, Direction>> newPos = repos(pos);
                if (get<0>(newPos.first)!=-1){

                    if (!visited.count(newPos.first)){
                        energised.emplace(get<0>(newPos.first),get<1>(newPos.first));
                        visited.insert(newPos.first);
                        newPoses.push_back(newPos.first);
                    }
                }
                if (get<0>(newPos.second)!=-1){

                    if (!visited.count(newPos.second)){
                        energised.emplace(get<0>(newPos.second),get<1>(newPos.second));
                        visited.insert(newPos.second);

                        newPoses.push_back(newPos.second);
                    }
                }
            }
            current=newPoses;
        }
        if (energised.size() > best) {
            best = energised.size();
            cout << best << endl;
        }

    }
    for (int y = 0; y < grid[0].size(); y++){
        vector<tuple<int, int, Direction>> current = {{0,y,r}};
        set<tuple<int, int, Direction>> visited;
        set<tuple<int, int>> energised;

        energised.emplace(0, y);
        visited.emplace(0, y, r);
        while (current.size()>0){
            vector<tuple<int, int, Direction>> newPoses;

            for (const tuple<int, int, Direction>& pos : current){
                pair<tuple<int, int, Direction>, tuple<int, int, Direction>> newPos = repos(pos);
                if (get<0>(newPos.first)!=-1){

                    if (!visited.count(newPos.first)){
                        energised.emplace(get<0>(newPos.first),get<1>(newPos.first));
                        visited.insert(newPos.first);
                        newPoses.push_back(newPos.first);
                    }
                }
                if (get<0>(newPos.second)!=-1){

                    if (!visited.count(newPos.second)){
                        energised.emplace(get<0>(newPos.second),get<1>(newPos.second));
                        visited.insert(newPos.second);

                        newPoses.push_back(newPos.second);
                    }
                }
            }
            current=newPoses;
        }
        if (energised.size() > best) {
            best = energised.size();
            cout << best << endl;
        }

    }
    for (int y = 0; y < grid[0].size(); y++){
        vector<tuple<int, int, Direction>> current = {{grid[0].size()-1,y,l}};
        set<tuple<int, int, Direction>> visited;
        set<tuple<int, int>> energised;

        energised.emplace(grid[0].size()-1,y);
        visited.emplace(grid[0].size()-1,y,l);
        while (current.size()>0){
            vector<tuple<int, int, Direction>> newPoses;

            for (const tuple<int, int, Direction>& pos : current){
                pair<tuple<int, int, Direction>, tuple<int, int, Direction>> newPos = repos(pos);
                if (get<0>(newPos.first)!=-1){

                    if (!visited.count(newPos.first)){
                        energised.emplace(get<0>(newPos.first),get<1>(newPos.first));
                        visited.insert(newPos.first);
                        newPoses.push_back(newPos.first);
                    }
                }
                if (get<0>(newPos.second)!=-1){

                    if (!visited.count(newPos.second)){
                        energised.emplace(get<0>(newPos.second),get<1>(newPos.second));
                        visited.insert(newPos.second);

                        newPoses.push_back(newPos.second);
                    }
                }
            }
            current=newPoses;
        }
        if (energised.size() > best) {
            best = energised.size();
            cout << best << endl;
        }
    }

    cout << best << endl;
}
