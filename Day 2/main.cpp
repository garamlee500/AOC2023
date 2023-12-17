#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/2/input.txt");
    string s;
    int total =0;
    while (getline(fin, s)){
        stringstream s1(s);
        int minRed = 0;
        int minBlue=0;
        int minGreen =0;
        string part;
        int count;
        s1 >> part >> part;
        while (true){
            int reds=0;
            int blues = 0;
            int greens=0;
            s1 >> count >> part;
            if (part.substr(0, 3)=="red"){
                reds+=count;
            }
            else if (part.substr(0, 5)=="green"){
                greens+=count;
            }
            else if (part.substr(0, 4)=="blue"){
                blues+=count;
            }
            if (part[part.size()-1]==';'){
                minRed=max(reds, minRed);
                minBlue=max(blues, minBlue);
                minGreen=max(greens,minGreen);
                continue;
            }
            s1 >> count >> part;
            if(!s1){
                minRed=max(reds, minRed);
                minBlue=max(blues, minBlue);
                minGreen=max(greens,minGreen);
                break;
            }
            if (part.substr(0, 3)=="red"){
                reds+=count;
            }
            else if (part.substr(0, 5)=="green"){
                greens+=count;
            }
            else if (part.substr(0, 4)=="blue"){
                blues+=count;
            }
            if (part[part.size()-1]==';'){
                minRed=max(reds, minRed);
                minBlue=max(blues, minBlue);
                minGreen=max(greens,minGreen);
                continue;
            }
            s1 >> count >> part;
            if(!s1){
                minRed=max(reds, minRed);
                minBlue=max(blues, minBlue);
                minGreen=max(greens,minGreen);
                break;
            }
            if (part.substr(0, 3)=="red"){
                reds+=count;
            }
            else if (part.substr(0, 5)=="green"){
                greens+=count;
            }
            else if (part.substr(0, 4)=="blue"){
                blues+=count;
            }
            if (part[part.size()-1]==';'){
                minRed=max(reds, minRed);
                minBlue=max(blues, minBlue);
                minGreen=max(greens,minGreen);
                continue;

            }
            if (reds>12|greens>13|blues>14){
                minRed=max(reds, minRed);
                minBlue=max(blues, minBlue);
                minGreen=max(greens,minGreen);
                break;
            }
            minRed=max(reds, minRed);
            minBlue=max(blues, minBlue);
            minGreen=max(greens,minGreen);

            break;



        }
            total += minRed*minGreen*minBlue;

    }
    cout << total <<endl;
}
