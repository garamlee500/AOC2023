#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


// [next charcter index][next counts index]
unsigned long long possibilityCounts[300][300];


unsigned long long possibilities(string s, const vector<int>& counts) {

    for (int i = 0; i <= s.size(); i++) {
        for (int j = 0; j <= counts.size(); j++) {
            possibilityCounts[i][j] = 0;
        }
    }
    possibilityCounts[0][0] = 1;
    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < counts.size(); j++){
            if (possibilityCounts[i][j] == 0) {
                continue;
            }

            for (int nextStart = i; nextStart + counts[j] - 1 < s.size(); nextStart++) {
                bool valid = true;
                for (int k = nextStart; k < nextStart + counts[j]; k++){
                    if (s[k] == '.') {
                        valid = false;
                        break;
                    }
                }

                if (valid && (nextStart + counts[j] == s.size() || s[nextStart + counts[j]] != '#')) {
                    possibilityCounts[min(nextStart + counts[j]+1, (int)s.size())][j + 1] += possibilityCounts[i][j];
                }

                if (s[nextStart] == '#') {
                    break;
                }
            }
        }
        // Process those at end
        bool valid = true;
        for (int k = i; k < s.size(); k++){
            if (s[k]=='#'){
                valid = false;
                break;
            }
        }
        if (valid){
            possibilityCounts[s.size()][counts.size()] += possibilityCounts[i][counts.size()];
        }
    }
    return possibilityCounts[s.size()][counts.size()];
}
vector<int> counts;

int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/12/input.txt");

    string s;
    string part1, part2;
    unsigned long long total = 0;
    while (getline(fin, s)) {
        counts.clear();
        stringstream s1(s);
        s1 >> part1;
        int x;

        while (true) {
            s1 >> x;
            if (!s1) {
                break;
            }
            counts.push_back(x);
            if (s1.peek() == ',') {
                s1.ignore();
            }
        }
        int countsSize = counts.size();
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < countsSize; j++) {
                counts.push_back(counts[j]);
            }
        }
        //cout << (part1+'?'+ part1 + '?'+ part1 + '?'+ part1 + '?'+ part1).size() << endl;
        //reverse(counts.begin(), counts.end());
        total += possibilities(part1+'?'+ part1 + '?'+ part1 + '?'+ part1 + '?'+ part1, counts);
//        cout << possibilities(part1 + '?' + part1 + '?' + part1 + '?' + part1 + '?' + part1, counts) << endl;
    }
    cout << total << endl;
}