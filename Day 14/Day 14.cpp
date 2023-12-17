#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> grid;
int performCycle() {
	// n
	for (int y = 1; y < grid.size(); y++) {
		for (int y1 = y; y1 >= 1; y1--) {

			for (int x = 0; x < grid[0].size(); x++) {

				if (grid[y1 - 1][x] == '.' && grid[y1][x] == 'O') {
					grid[y1 - 1][x] = 'O';
					grid[y1][x] = '.';
				}
			}
		}
	}

	//w
	for (int x = 1; x < grid[0].size(); x++) {
		for (int x1 = x; x1 >= 1; x1--) {
			for (int y = 0; y < grid.size(); y++) {
				if (grid[y][x1 - 1] == '.' && grid[y][x1] == 'O') {
					grid[y][x1 - 1] = 'O';
					grid[y][x1] = '.';
				}
			}
		}
	}

	// s
	for (int y = grid.size() - 2; y >= 0; y--) {
		for (int y1 = y; y1 <=grid.size()-2; y1++) {

			for (int x = 0; x < grid[0].size(); x++) {

				if (grid[y1 + 1][x] == '.' && grid[y1][x] == 'O') {
					grid[y1 + 1][x] = 'O';
					grid[y1][x] = '.';
				}
			}
		}
	}

	// e
	for (int x = grid[0].size()-2; x >= 0; x--) {
		for (int x1 = x; x1 <= grid[0].size()-2; x1++) {
			for (int y = 0; y < grid.size(); y++) {
				if (grid[y][x1 + 1] == '.' && grid[y][x1] == 'O') {
					grid[y][x1 + 1] = 'O';
					grid[y][x1] = '.';
				}
			}
		}
	}



	unsigned long long total = 0;
	for (int y = 0; y < grid.size(); y++) {
		for (int x = 0; x < grid[0].size(); x++) {

			if (grid[y][x] == 'O') {
				total += grid.size() - y;
			}
		}
	}

	return total;




}


int main() {

	string s;
	ifstream fin("input.txt");
	while (getline(fin, s)) {
		grid.push_back(s);
	}


	
	for (int i = 1; i < 1000; i++) {
		cout << i << ' ' << performCycle() << endl;
	}	


}