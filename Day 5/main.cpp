#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

vector<pair<long long, long long>> seeds;
vector<vector<tuple<long long, long long, long long>>> mappings;
int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/5/input.txt");
    string s;
    getline (fin, s);

    stringstream s1(s);
    s1 >> s;

    long long seed1, seed2;
    while (true){
        s1 >> seed1 >> seed2;
        if (!s1){
            break;
        }
        seeds.emplace_back(seed1 , seed2);
    }
    long long a, b, c;
    while (getline(fin,s)){
        if (s.empty()){
            mappings.emplace_back();
            getline(fin, s);
            continue;
        }
        s1 =  stringstream (s);
        s1 >> a >> b >> c;
        mappings.back().emplace_back(a, b, c);
    }
    long long best = numeric_limits<long long>::max();




    for (const vector<tuple<long long, long long, long long>>& maps : mappings){
        vector<pair<long long, long long>> newSeeds;
        for (int i = 0; i < seeds.size(); i++){
            bool preserved = true;
            for(const tuple<long long, long long, long long>& t : maps){
                pair<long long, long long> seed = seeds[i];
                if (seed.first + seed.second - 1 < get<1>(t)
                        ||seed.first > get<1>(t)+ get<2>(t)-1){

                    // no overlap
                    continue;
                }

                if (seed.first>=get<1>(t) && seed.first+seed.second <= get<1>(t)+get<2>(t)){
                    // complete overlap
                    newSeeds.emplace_back(seed.first+get<0>(t)-get<1>(t),seed.second);
                    preserved=false;
                    break;
                }

                if (seed.first+seed.second <= get<1>(t)+get<2>(t)){
                    // right overlap of seed
                    preserved=false;
                    seeds.emplace_back(seed.first, get<1>(t)-seed.first);
                    newSeeds.emplace_back(get<1>(t) + get<0>(t)-get<1>(t),seed.first+seed.second-get<1>(t));
                }
                else{
                    // left overlap of seed
                    preserved =false;
                    newSeeds.emplace_back(seed.first + get<0>(t)-get<1>(t), get<2>(t)+get<1>(t)-seed.first);
                    seeds.emplace_back(get<2>(t)+get<1>(t), seed.second+seed.first-get<2>(t)-get<1>(t));
                }
            }

            if (preserved){
                newSeeds.emplace_back(seeds[i]);
            }
        }
        seeds=newSeeds;
    }
    sort(seeds.begin(), seeds.end());

    cout << best << endl;

}
