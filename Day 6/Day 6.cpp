// Day 6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
int main()
{
    

    int total=1;



    int time, d2, ways;


    time = 41;
    d2 = 214;
    ways = 0;
    for (int i = 0; i <= time; i++) {
        int d = (i) * (time - i);
        if (d > d2) {
            ways++;
        }
    }
    total *= ways;

    time = 96;
    d2 = 1789;
    ways = 0;
    for (int i = 0; i <= time; i++) {
        int d = (i) * (time - i);
        if (d > d2) {
            ways++;
        }
    }
    total *= ways;    
    time = 88;
    d2 = 1127;
    ways = 0;
    for (int i = 0; i <= time; i++) {
        int d = (i) * (time - i);
        if (d > d2) {
            ways++;
        }
    }
    total *= ways;


    time = 94;
    d2 = 1055;
    ways = 0;
    for (int i = 0; i <= time; i++) {
        int d = (i) * (time - i);
        if (d > d2) {
            ways++;
        }
    }
    total *= ways;

    cout << total << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
