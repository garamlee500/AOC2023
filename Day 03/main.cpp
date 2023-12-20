#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
using namespace std;


vector<string> grid;
map<pair<int, int>, vector<int>> gears;
bool isSymbol(char c){
    return c=='*';
}
int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/3/input.txt");
    string s;
    while(getline(fin, s)){
        grid.push_back(s);
    }
    int total = 0;
    for (int i = 0; i < grid.size(); i++){
        int number = 0;
        bool isNumber = false;
        bool isValid = false;
        vector<pair<int, int>> gearPositions;
        for (int j =0; j<grid[0].size(); j++){
            if (grid[i][j] >='0'&&grid[i][j] <='9'){
                if (!isNumber){
                    isNumber=true;
                    if (j>0&&isSymbol(grid[i][j-1])){
                        isValid=true;
                        gearPositions.emplace_back(i, j-1);
                    }
                    if (j>0&&i>0&&isSymbol(grid[i-1][j-1])){
                        isValid=true;
                        gearPositions.emplace_back(i-1, j-1);
                    }
                    if(j>0 && i < grid.size()-1&&isSymbol(grid[i+1][j-1])){
                        isValid=true;
                        gearPositions.emplace_back(i+1, j-1);

                    }
                }
                if (i>0&&isSymbol(grid[i-1][j])){
                    isValid=true;
                    gearPositions.emplace_back(i-1, j);

                }
                if (i<grid.size()-1&&isSymbol(grid[i+1][j])){
                    isValid=true;
                    gearPositions.emplace_back(i+1, j);

                }


                number*=10;
                number += grid[i][j]-'0';
            }
            else if (isNumber){
                isNumber=false;

                if (isSymbol(grid[i][j])){
                    isValid=true;
                    gearPositions.emplace_back(i, j);

                }
                if (i>0&&isSymbol(grid[i-1][j])){
                    isValid=true;
                    gearPositions.emplace_back(i-1, j);

                }
                if(i < grid.size()-1&&isSymbol(grid[i+1][j])){
                    isValid=true;
                    gearPositions.emplace_back(i+1, j);
                }
                if (isValid){
                    for (pair<int,int> p : gearPositions){
                        gears[p].push_back(number);
                    }
                }
                gearPositions.clear();
                number=0;
                isValid=false;
            }

        }

        int j = grid[0].size()-1;
        if (isNumber){
            isNumber=false;

            if (isSymbol(grid[i][j])){
                gearPositions.emplace_back(i, j);
            }
            if (i>0&&isSymbol(grid[i-1][j])){
                gearPositions.emplace_back(i-1, j);
            }
            if(i < grid.size()-1&&isSymbol(grid[i+1][j])){
                gearPositions.emplace_back(i+1, j);
            }
            if (isValid){
                for (pair<int,int> p : gearPositions){
                    gears[p].push_back(number);
                }
            }
            gearPositions.clear();

            number=0;
            isValid=false;
        }
    }
    for (auto const& [key, val] : gears){
        if (val.size()==2){
            total += val[0]*val[1];
        }
    }
    cout << total << endl;
}
