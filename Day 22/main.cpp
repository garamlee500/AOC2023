#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct Cube{
    int x1, y1,z1,x2,y2,z2, index;
    Cube(int x1, int y1, int z1, int x2, int y2, int z2, int index):
    x1(x1),
    y1(y1),
    z1(z1),
    x2(x2),
    y2(y2),
    z2(z2),
    index(index)
    {
        //teehee
    }

    bool twoDoverlap(Cube cube) const{
        return min(x1, x2) <= max(cube.x1, cube.x2) && min(cube.x1, cube.x2) <= max(x1, x2)
        && min(y1, y2) <= max(cube.y1, cube.y2) && min(cube.y1, cube.y2) <= max(y1, y2);
    }

    int onTop(Cube cube) const{
        // finds at what z angle the cube on top should rest
        // -1 if no overlap
        if (!twoDoverlap(cube)){
            return -1;
        }

        if (min(cube.z1, cube.z2) <= max(z1, z2)){
            return -1;
        }
        return max(z1, z2) + 1;
    }
};

vector<string> split(const string& s){
    vector<string> result;
    string current;
    for (char c : s){
        if (c>='0'&&c<='9'){
            current+=c;
        }
        else{
            result.push_back(current);
            current="";
        }
    }
    result.push_back(current);
    return result;

}
vector<Cube> cubes;
unordered_set<int> crucialCubes;
unordered_map<int, vector<int>> crucialCubeLinks;
int main() {
    string s;
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/22/input.txt");
    int index=0;
    while (getline (fin, s)){
        vector<string> coords = split(s);
        cubes.emplace_back(stoi(coords[0]),stoi(coords[1]),stoi(coords[2]),stoi(coords[3]),stoi(coords[4]),stoi(coords[5]), index);
        index++;
    }

    sort (cubes. begin(), cubes.end(), [](Cube a, Cube b){return a.z1 < b.z1;});
    vector<Cube> newCubes;
    for (Cube cube : cubes){
        vector<int> supportCubes;
        int currentHeight = 1;
        for (Cube underCube : newCubes){
            int newHeight = underCube.onTop(cube);

            if (newHeight==currentHeight){
                supportCubes.push_back(underCube.index);
            }
            else if (newHeight >currentHeight){
                currentHeight=newHeight;
                supportCubes={underCube.index};
            }
        }

        if (supportCubes.size()==1){
            crucialCubes.insert(supportCubes[0]);
        }


        int fallHeight = min(cube.z1, cube.z2)-currentHeight;
        cube.z1 -=fallHeight;
        cube.z2-=fallHeight;
        newCubes.push_back(cube);
    }



    int total = 0;
    cubes = newCubes;
    sort (cubes. begin(), cubes.end(), [](Cube a, Cube b){return a.z1 < b.z1;});
    for (int crucial : crucialCubes){
        newCubes.clear();
        for (Cube cube : cubes){
            if (cube.index==crucial){
                continue;
            }
            vector<int> supportCubes;
            int currentHeight = 1;
            for (Cube underCube : newCubes){
                int newHeight = underCube.onTop(cube);

                if (newHeight==currentHeight){
                    supportCubes.push_back(underCube.index);
                }
                else if (newHeight >currentHeight){
                    currentHeight=newHeight;
                    supportCubes={underCube.index};
                }
            }

            int fallHeight = min(cube.z1, cube.z2)-currentHeight;
            if (fallHeight > 0){
                total++;
            }
            cube.z1 -=fallHeight;
            cube.z2-=fallHeight;
            newCubes.push_back(cube);
        }

    }
    cout << total << endl;
}
