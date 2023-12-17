#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector < vector<pair<string, int>>> v;



void process(string s, int box) {

    box = 0;

    if (s.back() == '-') {
        string label = s.substr(0, s.size() - 1);

        for (char c : label){
            box+=c;
            box*=17;
            box%=256;
        }

        for (vector<pair<string, int>>::iterator it = v[box].begin(); it != v[box].end(); it++) {
            if (it->first == label) {
                v[box].erase(it);
                break;
            }
        }
    }
    else {
        string label = s.substr(0, s.size() - 2);

        for (char c : label){
            box+=c;
            box*=17;
            box%=256;
        }

        int num = stoi(s.substr(s.size() - 1));
        bool found = false;
        for (vector<pair<string, int>>::iterator it = v[box].begin(); it != v[box].end(); it++) {
            if (it->first == label) {
                v[box][it - v[box].begin()] = make_pair(label, num);
                found = true;
                break;
            }
        }
        if (!found) {
            v[box].emplace_back(label, num);
        }
    }

}

int main() {
    for (int i = 0; i < 256; i++) {

        v.emplace_back();
    }
    unsigned long long total = 0;
    unsigned long long subtotal = 0;
    string current = "";
    while (true) {
        char c = getchar();
        if (c == '\n') {
            total += subtotal;
            process(current, subtotal);
            break;
        }
        if (c == ',') {
            total += subtotal;
            subtotal = 0;
            process(current, subtotal);
            cout << current << endl;
            current = "";
            continue;
        }
        subtotal += c;
        subtotal *= 17;
        subtotal %= 256;
        current += c;

    }
    int result = 0;
    for (int i = 1; i <= v.size(); i++) {
        for (int j = 1; j <= v[i - 1].size(); j++) {
            result += i * j * v[i - 1][j - 1].second;
        }
    }
    cout << result << endl;
}