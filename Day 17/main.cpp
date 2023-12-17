#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <limits>
#include <functional>

using namespace std;

enum Direction{
    u, r, d, l
};

vector<vector<int>> grid;

template <class T, class IndexTracker>
class IndexedPriorityQueue{
private:
    vector<T> heap;
    function<bool(T, T)> itemComparator;
    IndexTracker itemIndices;
public:
    unsigned int size(){
        return heap.size();
    }

    explicit IndexedPriorityQueue(function<bool(T, T)> itemComparator):
            itemComparator(std::move(itemComparator)){}
    IndexedPriorityQueue(function<bool(T, T)> itemComparator, IndexTracker indexTracker):
            itemComparator(std::move(itemComparator)),
            itemIndices(std::move(indexTracker)){}

    bool itemPresent(T item, bool itemExistenceCheck=true){
        // itemExistenceCheck should allow inlining by compiler such that bounds checking can be avoided if the
        // item is known to have previously been processed.
        if (itemExistenceCheck){
            try {
                return itemIndices.at(item) != -1;
            }
            catch (const std::out_of_range&) {
                return false;
            }
        }
        else{
            return itemIndices[item] != -1;
        }

    }
    T peekTop(){
        return heap[0];
    }
    T popTop(){
        T topItem = peekTop();
        itemIndices[heap.back()] = 0;
        itemIndices[topItem] = -1;
        heap[0] = heap.back();
        heap.pop_back();
        unsigned int itemIndex = 0;

        // Loop until current item has no children
        while (itemIndex * 2 + 1 < heap.size()){
            // Check if current item has a second child
            if (itemIndex * 2 + 2 < heap.size()){
                // First child is less than second child
                if (itemComparator(heap[itemIndex*2+1], heap[itemIndex*2 + 2])){
                    // First child is less than current item
                    if (itemComparator(heap[itemIndex*2+1], heap[itemIndex])){
                        // Swap current item with first child
                        int tempHeapValue = heap[itemIndex*2+1];
                        itemIndices[tempHeapValue] = itemIndex;
                        heap[itemIndex*2+1] = heap[itemIndex];
                        itemIndices[heap[itemIndex]] = itemIndex*2+1;
                        heap[itemIndex] = tempHeapValue;
                        itemIndex = itemIndex*2+1;
                    }
                    else{
                        // Current item is less than both children - stop reheapify
                        return topItem;
                    }
                }
                    // Second child is less than first child
                else{
                    // Second child is less than current item
                    if (itemComparator(heap[itemIndex*2+2], heap[itemIndex])){
                        // Swap current item with second child
                        int tempHeapValue = heap[itemIndex*2+2];
                        itemIndices[tempHeapValue] = itemIndex;
                        heap[itemIndex*2+2] = heap[itemIndex];
                        itemIndices[heap[itemIndex]] = itemIndex*2+2;
                        heap[itemIndex] = tempHeapValue;
                        itemIndex = itemIndex*2+2;
                    }
                    else{
                        // Current item is less than both children - stop reheapify
                        return topItem;
                    }
                }
            }
                // Item only has one child
            else{
                // First child is less than current item
                if (itemComparator(heap[itemIndex*2+1], heap[itemIndex])){
                    // Swap current item with first child
                    int tempHeapValue = heap[itemIndex*2+1];
                    itemIndices[tempHeapValue] = itemIndex;
                    heap[itemIndex*2+1] = heap[itemIndex];
                    itemIndices[heap[itemIndex]] = itemIndex*2+1;
                    heap[itemIndex] = tempHeapValue;
                }
                // No more children regardless - stop reheapify
                return topItem;
            }
        }
        return topItem;
    }
    void reduceItem(T item){
        unsigned int itemIndex = itemIndices[item];
        while (itemIndex > 0){
            unsigned int parentItemIndex = (itemIndex-1)/2;
            // Check if current node is less than parent node - swap if case otherwise end procedure
            if (itemComparator(heap[itemIndex], heap[parentItemIndex])){
                int tempHeapValue = heap[itemIndex];
                itemIndices[tempHeapValue] = parentItemIndex;
                itemIndices[heap[parentItemIndex]] = itemIndex;
                heap[itemIndex] = heap[parentItemIndex];
                heap[parentItemIndex] = tempHeapValue;
                itemIndex = parentItemIndex;
            }
            else{
                return;
            }
        }
    }
    void insertItem(T item){
        itemIndices[item] = heap.size();
        heap.push_back(item);
        reduceItem(item);
    }
};


class DijkstraHeap{
private:
    IndexedPriorityQueue<int, vector<int>> priorityQueue;
public:
    unsigned int size(){
        return priorityQueue.size();
    }
    // nodeComparator - a function taking in two integers (nodeA, nodeB) and returns True if the current shortest path
    //      to nodeA from startNode is less than the current shortest path to nodeB from startNode, or False otherwise
    DijkstraHeap(unsigned int nodeCount, function<bool(int, int)> nodeComparator)
            : priorityQueue(IndexedPriorityQueue<int, vector<int>>(std::move(nodeComparator), vector<int>(nodeCount)))
    {
        for (unsigned int i = 0; i < nodeCount; i++) {
            // Insert nodes 0 to n - 1 to ensure vector<int> tracking node indices is not indexed out of bounds
            // Not particularly performance affecting since all nodes will need to be eventually added anyway
            priorityQueue.insertItem(i);
        }
    }
    bool nodePresent(int node){
        // We know all nodes have been processed at least once so itemExistenceCheck is not needed
        return priorityQueue.itemPresent(node, false);
    }
    int peekTop(){
        return priorityQueue.peekTop();
    }
    int popTop(){
        return priorityQueue.popTop();
    }
    void updateNode(int node) {
        priorityQueue.reduceItem(node);
    }
};

// y, x, direction moved count
int squareToNodeNum[1000][1000][11][4];
vector<tuple<int, int, int, int>> nodeNumToSquare;

// nextNode, length
vector<vector<pair<int, int>>> adjacencyList;



// y, x
pair<int, int> goForward(int y, int x, Direction direction){
    pair<int, int> result;

    switch(direction){
        case u:
            result = make_pair(y-1, x);
            break;
        case d:
            result = make_pair(y+1, x);
            break;
        case l:
            result = make_pair(y, x-1);
            break;
        case r:
            result=make_pair(y, x+1);
            break;
    }
    if (result.first < 0 || result.first >= grid.size() || result.second < 0||result.second >= grid[0].size()){
        return make_pair(-1,-1);
    }
    else{
        return result;
    }
}

pair<int, int> goLeft(int y, int x, Direction direction){
    switch(direction){
        case u:
            return goForward(y, x, l);
        case l:
            return goForward(y, x, d);
        case d:
            return goForward(y, x, r);
        case r:
            return goForward(y, x, u);

    }
}


pair<int, int> goRight(int y, int x, Direction direction){
    switch(direction){
        case u:
            return goForward(y, x, r);
        case l:
            return goForward(y, x, u);
        case d:
            return goForward(y, x, l);
        case r:
            return goForward(y, x, d);

    }
}

int main() {
    ifstream fin("/home/garam/OneDrive/Documents/Garam/Coding/C++/AOC2023/17/input.txt");
    string s;
    while (getline(fin, s)){
        grid.emplace_back();
        for (char c : s){
            grid.back().push_back(c-'0');
        }
    }

    for (int y = 0; y < grid.size(); y++){
        for (int x= 0; x < grid[0].size(); x++){
            for (int dMovedCount=0; dMovedCount < 11; dMovedCount++){
                for (int direction=0; direction < 4; direction++){
                    squareToNodeNum[y][x][dMovedCount][direction]=nodeNumToSquare.size();
                    nodeNumToSquare.emplace_back(y,x,dMovedCount,direction);
                }
            }
        }
    }
    vector<int> distances;
    for (int node = 0; node < nodeNumToSquare.size(); node++){
        distances.push_back(numeric_limits<int>::max());
        adjacencyList.emplace_back();
        tuple<int, int, int, int> square = nodeNumToSquare[node];
        int y=get<0>(square);
        int x = get<1>(square);
        int consequtive = get<2>(square);
        Direction direction = (Direction)get<3>(square);
        pair<int, int> nextSquare;
        if (consequtive<10){
            nextSquare = goForward(y, x, direction);
            if (nextSquare.first!=-1){
                adjacencyList[node].emplace_back(
                        squareToNodeNum[nextSquare.first][nextSquare.second][consequtive+1][direction],
                        grid[nextSquare.first][nextSquare.second]
                        );
            }
        }
        if (consequtive>3) {
            nextSquare = goLeft(y, x, direction);
            if (nextSquare.first != -1) {
                adjacencyList[node].emplace_back(
                        squareToNodeNum[nextSquare.first][nextSquare.second][1][(direction + 3) % 4],
                        grid[nextSquare.first][nextSquare.second]
                );
            }
            nextSquare = goRight(y, x, direction);
            if (nextSquare.first != -1) {
                adjacencyList[node].emplace_back(
                        squareToNodeNum[nextSquare.first][nextSquare.second][1][(direction + 1) % 4],
                        grid[nextSquare.first][nextSquare.second]
                );
            }
        }
    }
    distances[squareToNodeNum[0][0][0][r]]=0;
    DijkstraHeap dijkstraHeap(adjacencyList.size(),[&distances](int a, int b){return distances[a] < distances[b];} );


    while (dijkstraHeap.size()>0){
        int currentNode=dijkstraHeap.popTop();
        if (distances[currentNode]==numeric_limits<int>::max()){
            break;
        }
        for (pair<int, int> edge : adjacencyList[currentNode]){

            if (dijkstraHeap.nodePresent(edge.first)){
                if (distances[edge.first]> edge.second+distances[currentNode]){
                    distances[edge.first]= edge.second+distances[currentNode];
                    dijkstraHeap.updateNode(edge.first);
                }
            }
        }



    }
    int best = numeric_limits<int>::max();
    for (int direction = 0; direction < 4; direction++){
        for (int c = 0; c < 11; c++){
            best = min(best, distances[squareToNodeNum[grid.size()-1][grid[0].size()-1][c][d]]);
        }
    }
    cout << best << endl;

}
