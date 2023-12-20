// Day 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;



vector<char> values = {'J','2','3','4','5','6','7','8','9','T','Q','K','A' };

int getHandScore(string s) {
    unordered_map<char, int> cardCounts;

    for (char c : s) {
        cardCounts[c]++;
    }

    if (cardCounts.size() == 1) {
        return 7;
    }

    if (cardCounts.size() == 2) {
        if (cardCounts.begin()->second == 1 || cardCounts.begin()->second == 4) {

            if (cardCounts['J'] > 0) {
                return 7;
            }
            return 6;
        }
        else {
            if (cardCounts['J'] > 0) {
                return 7;
            }
            return 5;
        }

    }

    if (cardCounts.size() == 3) {
        if (cardCounts.begin()->second == 3 || next(cardCounts.begin())->second == 3 || next(next(cardCounts.begin()))->second == 3) {
            if (cardCounts['J'] > 0) {
                return 6;
            }


            return 4;
        }
        if (cardCounts['J'] == 2) {
            return 6;
        }
        if (cardCounts['J'] == 1) {
            return 5;
        }

        return 3;
    }

    if (cardCounts.size() == 4) {
        if (cardCounts['J'] > 0) {
            return 4;
        }
        return 2;
    }

    if (cardCounts['J'] > 0) {
        return 2;
    }    return 1;
}
bool compareHands(string a, string b) {
    int scoreA = getHandScore(a);
    int scoreB = getHandScore(b);


    if (scoreA < scoreB) {
        return true;
    }
    else if (scoreA > scoreB) {
        return false;
    }


    for (int i = 0; i < 5; i++) {
        if (find(values.begin(), values.end(), a[i]) > find(values.begin(), values.end(), b[i])) {
            return false;
        }
        else if (find(values.begin(), values.end(), a[i]) < find(values.begin(), values.end(), b[i])) {
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream fin("input.txt");
    vector<pair<string, int>> hands;

    string s;
    while (getline(fin, s)) {
        hands.emplace_back
        (
            s.substr(0, 5),
            stoi(s.substr(6, s.size() - 6))
        );
    }
    sort(hands.begin(), hands.end(), [](pair<string, int> p1, pair<string, int>p2){return compareHands(p1.first, p2.first); });
    unsigned long long total = 0;
    for (unsigned long long i = 0; i < hands.size(); i++) {
        total += (i + 1) * hands[i].second;
    }
    cout << total << endl;
}

