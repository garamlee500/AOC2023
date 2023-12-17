// Day 13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


unsigned long long findRowScore(const vector<string>& s) {


    for (int row = 1; row < s.size(); row++) {

        int upPointer = row - 1;
        int downPointer = row;
        int bad = 0;        while (upPointer >= 0 && downPointer < s.size()) {

            for (int i = 0; i < s[0].size(); i++) {
                if (s[upPointer][i] != s[downPointer][i]) {
                    bad++;
                }
            }
            upPointer--;
            downPointer++;
        }
        if (bad==1) {
            return row * 100;
        }
    }
    return 0;
}

unsigned long long findColumnScore(const vector<string>& s)

{
    for (int column = 1; column < s[0].size(); column++) {


        int leftPointer = column - 1;
        int rightPointer = column;

        int bad = 0;

        while (leftPointer >= 0 && rightPointer < s[0].size()) {

            for (int j = 0; j < s.size(); j++) {
                if (s[j][leftPointer] != s[j][rightPointer]) {
                    bad++;
                }

            }

            leftPointer--;
            rightPointer++;
        }
        if (bad==1) {
            return column;
        }
    }
    return 0;
}


int main()
{
    ifstream fin("input.txt");
    unsigned long long total = 0;
    vector<string> current;
    string s1;

    while (true) {

        getline(fin, s1);
        if (!fin) {
            total += findRowScore(current) + findColumnScore(current);
            break;
        }
        if (s1==""){
            total += findRowScore(current) + findColumnScore(current);
            current.clear();
        }
        else {
            current.push_back(s1);
        }
    }
    cout << total << endl;
}
