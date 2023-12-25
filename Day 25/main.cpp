#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <queue>

using namespace std;

unordered_map<string, unordered_set<string>> edges;
int main() {
    // 3 edges must be removed by hand
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/25/input.txt");
    string s;
    while (getline(fin, s)){
        stringstream s1(s);
        string bit, start;
        s1 >> start;
        start.pop_back();
        while (true){
            s1 >> bit;
            if (!s1){
                break;
            }
            edges[start].insert(bit);
            edges[bit].insert(start);

        }


    }

    unordered_set<string> visited;
    queue<string> remain;
    visited.insert("kkp");
    remain.emplace("kkp");
    while (!remain.empty()){
        string current = remain.front();
        remain.pop();
        for (const string& s1 : edges[current]){
            if (!visited.count(s1)){
                visited.insert(s1);
                remain.push(s1);
            }
        }

    }
    cout << visited.size() << '*' << edges.size()-visited.size() << "=" << (edges.size()-visited.size())*visited.size() << endl;
}
