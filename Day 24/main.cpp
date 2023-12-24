#include <iostream>
#include <fstream>
#include <vector>
#include "eigen-3.4.0/Eigen/Dense"

using Eigen::Matrix;

using namespace std;
 long long minimum = 200000000000000;
 long long maximum =400000000000000;
struct Line{
    long long x0, y0, z0, x1, y1, z1;
    Line(long long x0, long long y0, long long z0, long long x1, long long y1, long long z1):
            x0(x0),
            y0(y0),
            z0(z0),
            x1(x1),
            y1(y1),
            z1(z1)
    {}

    bool collide(Line line){

        Matrix<long double, 2, 2> inputs;
        inputs << x1, -line.x1,y1, -line.y1 ;
        Eigen::Vector<long double, 2> outputs;
        outputs << line.x0-x0, line.y0-y0;
        Eigen::Vector<long double, 2> x = inputs.colPivHouseholderQr().solve(outputs);

        long double t0 = x[0];
        long double t1 = x[1];

        bool a_solution_exists = (inputs*x).isApprox(outputs, 1e-5);
        if (!a_solution_exists){
            return false;
        }
        if (t0<0||t1<0){
            return false;
        }
        return x0+t0*x1>=minimum&&x0+t0*x1<=maximum&&y0+t0*y1>=minimum&&y0+t0*y1<=maximum;

    }

};


vector<long long> split(const string& s){
    vector<long long> result;
    string current;
    for (char c : s){

        if ((c>='0' && c<='9') || c=='-'){
            current+=c;
        }
        else if (!current.empty()){
            result.push_back(stol(current));
            current="";
        }
    }
    result.push_back(stol(current));
    return result;
}

vector<Line> lines;
int main() {
    string s;
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/24/input.txt");
    while (getline(fin, s)){
        vector<long long> terms= split(s);
        lines.emplace_back(terms[0],terms[1],terms[2],terms[3],terms[4],terms[5]);
    }
    int total = 0;

    for (int i = 0; i < lines.size()-1;i++){
        for (int j = i + 1; j < lines.size(); j++){
            if (lines[i].collide(lines[j])){
                total++;
            }
        }
    }
    cout << total << endl;

}
