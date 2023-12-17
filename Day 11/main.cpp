#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
vector<pair<int, int>> galaxies;
vector<string> grid;
vector<unsigned long long> emptyColumns;
vector<unsigned long long> emptyRows;
int main() {
    string s;
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/11/input.txt");

    while(getline(fin, s)){
        if(s.find('#')==string::npos){
            // empty
            emptyRows.push_back(grid.size());
        }
        grid.push_back(s);
    }

    for (int j = 0; j < grid[0].size(); j++){
        bool noGalaxy=true;
        for (int i =0; i < grid.size(); i++){

            if (grid[i][j]=='#'){
                noGalaxy=false;
                break;
            }
        }
        if (noGalaxy){
            emptyColumns.push_back(j);

        }
    }
    unsigned long long total = 0;
    for (int i =0;i < grid.size(); i++){
        for (int j = 0; j < grid[0].size(); j++){
            if (grid[i][j]=='#') {
                for (pair<int, int> &p: galaxies) {
                    total += abs(i - p.first) + abs(j - p.second);

                    for (int emptyRow : emptyRows){
                        if (emptyRow > min(i,p.first)&& emptyRow < max(i,p.first)){
                            total += 1e6-1;
                        }

                    }
                    for (int emptyColumn : emptyColumns){
                        if (emptyColumn > min(j,p.second)&& emptyColumn < max(j,p.second)){
                            total += 1e6-1;
                        }

                    }
                }

                galaxies.emplace_back(i, j);
            }
        }
    }
    cout << total << endl;
}
