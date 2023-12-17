#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int predict_next(const vector<int>& v){
    bool zeroed = true;
    for (int x : v){
        if (x!=0){
            zeroed = false;
        }
    }

    if (zeroed){
        return 0;
    }

    vector<int> diff;
    for (int i = 0 ; i<v.size()-1;i++){
        diff.push_back(v[i+1]-v[i]);
    }
    return v.back()+ predict_next(diff);


}

int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/9/input.txt");
    string s;
    unsigned long long total = 0;
    while (getline(fin, s)){
        stringstream s1(s);
        vector<int> list;

        while(true){
            int x;
            s1 >> x;
            if (!s1){
                break;
            }
            list.push_back(x);
        }
        reverse(list.begin(), list.end());
        total+= predict_next(list);


    }
    cout << total << endl;

}
