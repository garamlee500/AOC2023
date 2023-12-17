#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>



using namespace std;

vector<unsigned long long> counts{0};
int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/4/input.txt");
    unsigned long long total = 0;
    string s;

    for (int i = 1; i <=222217;i++){
        counts.push_back(1);
    }
    int cardNum=0;
    while (getline(fin, s)){
        cardNum++;
        vector<int> wins;
        vector<int> nums;
        stringstream s1(s);
        string nullthing;
        s1 >> nullthing >> nullthing;
        int x;
        for (int i = 0; i < 10; i++){
            s1 >> x;
            wins.push_back(x);
        }
        s1 >> nullthing;
        unsigned long long subTotal =0;
        for (int i = 0; i < 25; i++){
            s1 >> x;
            if (count(wins.begin(), wins.end(), x)){
                subTotal++;
            }
        }
        total+=counts[cardNum];
        for (int i = cardNum + 1; i <=min(cardNum+subTotal,static_cast<unsigned long long>(207)); i++){
            counts[i] += counts[cardNum];
        }
    }
    cout << total << endl;
}
